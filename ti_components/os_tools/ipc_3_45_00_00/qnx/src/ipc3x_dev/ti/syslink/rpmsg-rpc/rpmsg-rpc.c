/*
 *  Copyright (c) 2013-2015, Texas Instruments Incorporated
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions
 *  are met:
 *
 *  *  Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *
 *  *  Redistributions in binary form must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in the
 *     documentation and/or other materials provided with the distribution.
 *
 *  *  Neither the name of Texas Instruments Incorporated nor the names of
 *     its contributors may be used to endorse or promote products derived
 *     from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 *  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 *  THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 *  PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 *  CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 *  EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 *  PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 *  OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 *  WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 *  OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 *  EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */


/* Standard headers */
#include <ti/syslink/Std.h>

/* OSAL & Utils headers */
#include <ti/syslink/utils/List.h>
#include <ti/syslink/utils/String.h>
#include <ti/syslink/utils/Trace.h>
#include <ti/syslink/utils/Memory.h>
#include <ti/syslink/utils/IGateProvider.h>
#include <ti/syslink/utils/GateSpinlock.h>
#include <_MultiProc.h>

/*QNX specific header include */
#include <errno.h>
#include <unistd.h>
#include <sys/iofunc.h>
#include <sys/dispatch.h>
#include <sys/netmgr.h>
#include <sys/mman.h>
#include <devctl.h>

/* Module headers */
#include <ti/syslink/ProcMgr.h>
#include <ti/ipc/rpmsg_rpc.h>
#include <ti/ipc/MessageQCopy.h>
#include <_MessageQCopy.h>
#include <_MessageQCopyDefs.h>
#include "OsalSemaphore.h"
#include "std_qnx.h"
#include <pthread.h>

#include "rpmsg-rpc.h"
#include <rpmsg.h>

#define PRIORITY_REALTIME_LOW 29

extern int mem_offset64_peer(pid_t pid, const uintptr_t addr, size_t len,
                             off64_t *offset, size_t *contig_len);

static MsgList_t *nl_cache;
static int num_nl = 0;
static WaitingReaders_t *wr_cache;
static int num_wr = 0;

/*
 * Instead of constantly allocating and freeing the notifier structures
 * we just cache a few of them, and recycle them instead.
 * The cache count is set with CACHE_NUM in rpmsg-rpc.h.
 */

static MsgList_t *get_nl()
{
    MsgList_t *item;
    item = nl_cache;
    if (item != NULL) {
        nl_cache = nl_cache->next;
        num_nl--;
    } else {
        item = Memory_alloc(NULL, sizeof(MsgList_t), 0, NULL);
    }
    return(item);
}

static void put_nl(MsgList_t *item)
{
    if (num_nl >= CACHE_NUM) {
        Memory_free(NULL, item, sizeof(*item));
    } else {
        item->next = nl_cache;
        nl_cache = item;
        num_nl++;
    }
    return;
}

static WaitingReaders_t *get_wr()
{
    WaitingReaders_t *item;
    item = wr_cache;
    if (item != NULL) {
        wr_cache = wr_cache->next;
        num_wr--;
    } else {
        item = Memory_alloc(NULL, sizeof(WaitingReaders_t), 0, NULL);
    }
    return(item);
}

static void put_wr(WaitingReaders_t *item)
{
    if (num_wr >= CACHE_NUM) {
        Memory_free(NULL, item, sizeof(*item));
    } else {
        item->next = wr_cache;
        wr_cache = item;
        num_wr++;
    }
    return;
}

/* structure to hold rpmsg-rpc device information */
typedef struct named_device {
    iofunc_mount_t      mattr;
    iofunc_attr_t       cattr;
    int                 resmgr_id;
    pthread_mutex_t     mutex;
    iofunc_funcs_t      mfuncs;
    resmgr_connect_funcs_t  cfuncs;
    resmgr_io_funcs_t   iofuncs;
    char device_name[_POSIX_PATH_MAX];
} named_device_t;

/* rpmsg-rpc device structure */
typedef struct rpmsg_rpc_dev {
    dispatch_t       * dpp;
    thread_pool_t    * tpool;
    named_device_t     rpmsg_rpc;
} rpmsg_rpc_dev_t;

/*!
 *  @brief  Remote connection object
 */
typedef struct rpmsg_rpc_conn_object {
    rpmsg_rpc_dev_t *   dev;
    MessageQCopy_Handle mq;
    UInt32              addr;
    UInt16              procId;
    ProcMgr_Handle      procH;
    UInt32              numFuncs;
    Bool                destroy;
} rpmsg_rpc_conn_object;

/*!
 *  @brief  rpc instance object
 */
typedef struct rpmsg_rpc_object_tag {
    MessageQCopy_Handle     mq;
    rpmsg_rpc_conn_object * conn;
    UInt32                  addr;
    UInt32                  remoteAddr;
    UInt16                  procId;
    pid_t                   pid;
    Bool                    created;
    iofunc_notify_t         notify[3];
} rpmsg_rpc_object;

/*!
 *  @brief  Structure of Event callback argument passed to register fucntion.
 */
typedef struct rpmsg_rpc_EventCbck_tag {
    List_Elem          element;
    /*!< List element header */
    rpmsg_rpc_object * rpc;
    /*!< User rpc info pointer. Passed back to user callback function */
    UInt32             pid;
    /*!< Process Identifier for user process. */
} rpmsg_rpc_EventCbck ;

/*!
 *  @brief  Structure of Fxn Info for reverse translations.
 */
typedef struct rpmsg_rpc_FxnInfo_tag {
    List_Elem              element;
    /*!< List element header */
    UInt16                 msgId;
    /*!< Unique msgId of the rpc fxn call */
    struct rppc_function   func;
    /*!< rpc function information. */
} rpmsg_rpc_FxnInfo ;

/*!
 *  @brief  Keeps the information related to Event.
 */
typedef struct rpmsg_rpc_EventState_tag {
    List_Handle            bufList;
    /*!< Head of received event list. */
    List_Handle            fxnList;
    /*!< Head of received msg list. */
    UInt32                 pid;
    /*!< User process ID. */
    rpmsg_rpc_object *     rpc;
    /*!< User rpc comp. */
    UInt32                 refCount;
    /*!< Reference count, used when multiple Notify_registerEvent are called
         from same process space (multi threads/processes). */
    WaitingReaders_t *     head;
    /*!< Waiting readers head. */
    WaitingReaders_t *     tail;
    /*!< Waiting readers tail. */
} rpmsg_rpc_EventState;

/*!
 *  @brief  Per-connection information
 */
typedef struct rpmsg_rpc_ocb {
    iofunc_ocb_t        hdr;
    pid_t               pid;
    rpmsg_rpc_object *  rpc;
} rpmsg_rpc_ocb_t;

typedef struct rpmsg_rpc_name {
    char name[RPMSG_NAME_SIZE];
}rpmsg_rpc_name_t;

static struct rpmsg_rpc_name rpmsg_rpc_names[] = {
        {.name = "rpmsg-rpc"},
};

#define NUM_RPMSG_RPC_QUEUES sizeof(rpmsg_rpc_names)/sizeof(*rpmsg_rpc_names)

/*!
 *  @brief  rpmsg-rpc Module state object
 */
typedef struct rpmsg_rpc_ModuleObject_tag {
    Bool                 isSetup;
    /*!< Indicates whether the module has been already setup */
    Bool                 openRefCount;
    /*!< Open reference count. */
    IGateProvider_Handle gateHandle;
    /*!< Handle of gate to be used for local thread safety */
    rpmsg_rpc_EventState eventState [MAX_PROCESSES];
    /*!< List for all user processes registered. */
    rpmsg_rpc_conn_object * objects [MAX_CONNS];
    /*!< List of all remote connections. */
    MessageQCopy_Handle mqHandle[NUM_RPMSG_RPC_QUEUES];
    /*!< Local mq handle associated with this module */
    UInt32 endpoint[NUM_RPMSG_RPC_QUEUES];
    /*!< Local endpoint associated with the mq handle */
    OsalSemaphore_Handle sem;
    /*!< Handle to semaphore used for rpc instance connection notifications */
    pthread_t nt;
    /*!< notifier thread */
    pthread_mutex_t lock;
    /*!< protection between notifier and event */
    pthread_cond_t  cond;
    /*!< protection between notifier and event */
    MsgList_t *head;
    /*!< list head */
    MsgList_t *tail;
    /*!< list tail */
    int run;
    /*!< notifier thread must keep running */
} rpmsg_rpc_ModuleObject;

/*!
 *  @brief  Structure of Event Packet read from notify kernel-side.
 */
typedef struct rpmsg_rpc_EventPacket_tag {
    List_Elem          element;
    /*!< List element header */
    UInt32             pid;
    /* Processor identifier */
    rpmsg_rpc_object * obj;
    /*!< Pointer to the channel associated with this callback */
    UInt8              data[MessageQCopy_BUFSIZE];
    /*!< Data associated with event. */
    UInt32             len;
    /*!< Length of the data associated with event. */
    UInt32             src;
    /*!< Src endpoint associated with event. */
    struct rpmsg_rpc_EventPacket * next;
    struct rpmsg_rpc_EventPacket * prev;
} rpmsg_rpc_EventPacket ;


/*
 * Instead of constantly allocating and freeing the uBuf structures
 * we just cache a few of them, and recycle them instead.
 * The cache count is set with CACHE_NUM in rpmsg-rpc.h.
 */
static rpmsg_rpc_EventPacket *uBuf_cache;
static int num_uBuf = 0;

static void flush_uBuf()
{
    rpmsg_rpc_EventPacket *uBuf = NULL;

    while(uBuf_cache) {
        num_uBuf--;
        uBuf = uBuf_cache;
        uBuf_cache = (rpmsg_rpc_EventPacket *)uBuf_cache->next;
        Memory_free(NULL, uBuf, sizeof(*uBuf));
    }
}

static rpmsg_rpc_EventPacket *get_uBuf()
{
    rpmsg_rpc_EventPacket *uBuf;
    uBuf = uBuf_cache;
    if (uBuf != NULL) {
        uBuf_cache = (rpmsg_rpc_EventPacket *)uBuf_cache->next;
        num_uBuf--;
    } else {
        uBuf = Memory_alloc(NULL, sizeof(rpmsg_rpc_EventPacket), 0, NULL);
    }
    return(uBuf);
}

static void put_uBuf(rpmsg_rpc_EventPacket * uBuf)
{
    if (num_uBuf >= CACHE_NUM) {
        Memory_free(NULL, uBuf, sizeof(*uBuf));
    } else {
        uBuf->next = (struct rpmsg_rpc_EventPacket *)uBuf_cache;
        uBuf_cache = uBuf;
        num_uBuf++;
    }
    return;
}

/** ============================================================================
 *  Function Prototypes
 *  ============================================================================
 */
int
_rpmsg_rpc_translate (ProcMgr_Handle handle, char *data, pid_t pid,
                      bool reverse);

/** ============================================================================
 *  Globals
 *  ============================================================================
 */
/*!
 *  @var    rpmsg_rpc_state
 *
 *  @brief  rpmsg-rpc state object variable
 */
static rpmsg_rpc_ModuleObject rpmsg_rpc_state =
{
    .gateHandle = NULL,
    .isSetup = FALSE,
    .openRefCount = 0,
    .nt = 0,
    .lock = PTHREAD_MUTEX_INITIALIZER,
    .cond = PTHREAD_COND_INITIALIZER,
    .head = NULL,
    .tail = NULL,
    .run  = 0
};

static uint16_t msg_id = 0xFFFF;

extern dispatch_t * ipc_dpp;


static MsgList_t *find_nl(int index)
{
    MsgList_t *item=NULL;
    item = rpmsg_rpc_state.head;
    while (item) {
        if (item->index == index)
            return(item);
        item = item->next;
    }
    return(item);
}

/* we have the right locks when calling this function */
/*!
 *  @brief      Function to enqueue a notify list item.
 *
 *  @param      index    Index of the client process associated with the item.
 *
 *  @sa         find_nl
 *              get_nl
 */
static int enqueue_notify_list(int index)
{
    MsgList_t *item;
    item = find_nl(index);
    if (item == NULL) {
        item = get_nl();
        if (item == NULL) {
            return(-1);
        }
        item->next = NULL;
        item->index = index;
        item->num_events=1;
        if (rpmsg_rpc_state.head == NULL) {
            rpmsg_rpc_state.head = item;
            rpmsg_rpc_state.tail = item;
            item->prev = NULL;
        }
        else {
            item->prev = rpmsg_rpc_state.tail;
            rpmsg_rpc_state.tail->next = item;
            rpmsg_rpc_state.tail = item;
        }
    }
    else {
        item->num_events++;
    }
    return(0);
}

/* we have the right locks when calling this function */
/*!
 *  @brief      Function to dequeue a notify list item.
 *
 *  @param      item     The item to remove.
 *
 *  @sa         put_nl
 */
static inline int dequeue_notify_list_item(MsgList_t *item)
{
    int index;
    if (item == NULL) {
        return(-1);
    }
    index = item->index;
    item->num_events--;
    if (item->num_events > 0) {
        return(index);
    }
    if (rpmsg_rpc_state.head == item) {
        // removing head
        rpmsg_rpc_state.head = item->next;
        if (rpmsg_rpc_state.head != NULL) {
            rpmsg_rpc_state.head->prev = NULL;
        }
        else {
            // removing head and tail
            rpmsg_rpc_state.tail = NULL;
        }
    }
    else {
        item->prev->next = item->next;
        if (item->next != NULL) {
            item->next->prev = item->prev;
        }
        else {
            // removing tail
            rpmsg_rpc_state.tail = item->prev;
        }
    }
    put_nl(item);
    return(index);
}

/* we have the right locks when calling this function */
/*!
 *  @brief      Function to add a waiting reader to the list.
 *
 *  @param      index    Index of the client process waiting reader to add.
 *  @param      rcvid    Receive ID of the client process that was passed
 *                       when the client called read().
 *
 *  @sa         None
 */
static int enqueue_waiting_reader(int index, int rcvid)
{
    WaitingReaders_t *item;
    item = get_wr();
    if (item == NULL) {
        return(-1);
    }
    item->rcvid = rcvid;
    item->next = NULL;
    if (rpmsg_rpc_state.eventState [index].head == NULL) {
        rpmsg_rpc_state.eventState [index].head = item;
        rpmsg_rpc_state.eventState [index].tail = item;
    }
    else {
        rpmsg_rpc_state.eventState [index].tail->next = item;
        rpmsg_rpc_state.eventState [index].tail = item;
    }
    return(EOK);
}

/* we have the right locks when calling this function */
/* caller frees item */
/*!
 *  @brief      Function to remove a waiting reader from the list.
 *
 *  @param      index    Index of the client process waiting reader to dequeue.
 *
 *  @sa         None
 */
static WaitingReaders_t *dequeue_waiting_reader(int index)
{
    WaitingReaders_t *item = NULL;
    if (rpmsg_rpc_state.eventState [index].head) {
        item = rpmsg_rpc_state.eventState [index].head;
        rpmsg_rpc_state.eventState [index].head = rpmsg_rpc_state.eventState [index].head->next;
        if (rpmsg_rpc_state.eventState [index].head == NULL) {
            rpmsg_rpc_state.eventState [index].tail = NULL;
        }
    }
    return(item);
}

/*!
 *  @brief      Function find a specified waiting reader.
 *
 *  @param      index    Index of the client process waiting for the message.
 *  @param      rcvid    Receive ID of the client process that was passed
 *                       when the client called read().
 *
 *  @sa         None
 */

static WaitingReaders_t *find_waiting_reader(int index, int rcvid)
{
    WaitingReaders_t *item = NULL;
    WaitingReaders_t *prev = NULL;
    if (rpmsg_rpc_state.eventState [index].head) {
        item = rpmsg_rpc_state.eventState [index].head;
        while (item) {
            if (item->rcvid == rcvid) {
                /* remove item from list */
                if (prev)
                    prev->next = item->next;
                if (item == rpmsg_rpc_state.eventState [index].head)
                    rpmsg_rpc_state.eventState [index].head = item->next;
                break;
            }
            else {
                prev = item;
                item = item->next;
            }
        }
    }
    return item;
}

/*!
 *  @brief      Function used to check if there is a waiting reader with an
 *              event (message) ready to be delivered.
 *
 *  @param      index    Index of the client process waiting for the message.
 *  @param      item     Pointer to the waiting reader.
 *
 *  @sa         dequeue_notify_list_item
 *              dequeue_waiting_reader
 */

static int find_available_reader_and_event(int *index, WaitingReaders_t **item)
{
    MsgList_t *temp;
    if (rpmsg_rpc_state.head == NULL) {
        return(0);
    }
    temp = rpmsg_rpc_state.head;
    while (temp) {
        if (rpmsg_rpc_state.eventState [temp->index].head) {
            // event and reader found
            if (dequeue_notify_list_item(temp) >= 0) {
                *index = temp->index;
                *item = dequeue_waiting_reader(temp->index);
            }
            else {
                /* error occurred, return 0 as item has not been set */
                return(0);
            }
            return(1);
        }
        temp = temp->next;
    }
    return(0);
}

/*!
 *  @brief      Function used to deliver the notification to the client that
 *              it has received a message.
 *
 *  @param      index    Index of the client process receiving hte message.
 *  @param      rcvid    Receive ID of the client process that was passed
 *                       when the client called read().
 *
 *  @sa         put_uBuf
 */

static void deliver_notification(int index, int rcvid)
{
    int err = EOK;
    rpmsg_rpc_EventPacket * uBuf     = NULL;

    uBuf = (rpmsg_rpc_EventPacket *) List_get (rpmsg_rpc_state.eventState [index].bufList);

    /*  Let the check remain at run-time. */
    if (uBuf != NULL) {
        err = MsgReply(rcvid, uBuf->len, uBuf->data, uBuf->len);
        if (err == -1)
            perror("deliver_notification: MsgReply");
        /* Free the processed event callback packet. */
        put_uBuf(uBuf);
    }
    else {
        MsgReply(rcvid, EOK, NULL, 0);
    }
    return;
}

/*!
 *  @brief      Thread used for notifying waiting readers of messages.
 *
 *  @param      arg    Thread-specific private arg.
 *
 *  @sa         find_available_reader_and_event
 *              deliver_notification
 *              put_wr
 */
static void *notifier_thread(void *arg)
{
    int status;
    int index;
    WaitingReaders_t *item = NULL;
    pthread_mutex_lock(&rpmsg_rpc_state.lock);
    while (rpmsg_rpc_state.run) {
        status = find_available_reader_and_event(&index, &item);
        if ( (status == 0) || (item == NULL) ) {
            status = pthread_cond_wait(&rpmsg_rpc_state.cond, &rpmsg_rpc_state.lock);
            if ((status != EOK) && (status != EINTR)) {
                // false wakeup
                break;
            }
            status = find_available_reader_and_event(&index, &item);
            if ( (status == 0) || (item == NULL) ) {
                continue;
            }
        }
        pthread_mutex_unlock(&rpmsg_rpc_state.lock);
        // we have unlocked, and now we have an event to deliver
        // we deliver one event at a time, relock, check and continue
        deliver_notification(index, item->rcvid);
        pthread_mutex_lock(&rpmsg_rpc_state.lock);
        put_wr(item);
    }
    pthread_mutex_unlock(&rpmsg_rpc_state.lock);
    return(NULL);
}


static
Int
_rpmsg_rpc_create(resmgr_context_t *ctp, io_devctl_t *msg, rpmsg_rpc_ocb_t *ocb)
{
    Int status = EOK;
    struct rppc_create_instance * cargs =
        (struct rppc_create_instance *)(_DEVCTL_DATA (msg->i));
    struct rppc_msg_header * msg_hdr = NULL;
    rpmsg_rpc_object * rpc = ocb->rpc;
    Char * msg_data = NULL;
    UInt8 buf[sizeof(struct rppc_create_instance) + sizeof(struct rppc_msg_header)];

    if (rpc->created == TRUE) {
        GT_0trace(curTrace, GT_4CLASS, "Already created.");
        status = (EINVAL);
    }
    else if ((ctp->info.msglen - sizeof(msg->i)) <
             sizeof (struct rppc_create_instance)) {
        status = (EINVAL);
    }
    else if (String_nlen(cargs->name, 47) == -1) {
        status = (EINVAL);
    }
    else {
        msg_hdr = (struct rppc_msg_header *)buf;
        msg_hdr->msg_type = RPPC_MSG_CREATE_INSTANCE;
        msg_hdr->msg_len = sizeof(struct rppc_create_instance);
        msg_data = (Char *)((UInt32)msg_hdr + sizeof(struct rppc_msg_header));
        Memory_copy(msg_data, cargs, sizeof(struct rppc_create_instance));

        status = MessageQCopy_send (rpc->conn->procId, // remote procid
                                    MultiProc_self(), // local procid
                                    rpc->conn->addr, // remote server
                                    rpc->addr, // local address
                                    buf, // connect msg
                                    sizeof(buf), // msg size
                                    TRUE); // wait for available bufs
        if (status != MessageQCopy_S_SUCCESS) {
            GT_0trace(curTrace, GT_4CLASS, "Failed to send create message.");
            status = (EIO);
        }
        else {
            status = OsalSemaphore_pend(rpmsg_rpc_state.sem, 5000);
            if (rpc->created == TRUE) {
                msg->o.ret_val = EOK;
                status = (_RESMGR_PTR(ctp, &msg->o, sizeof(msg->o)));
            }
            else if (status < 0) {
                GT_0trace(curTrace, GT_4CLASS, "Semaphore pend failed.");
                status = (EIO);
            }
            else {
                status = (ETIMEDOUT);
            }
        }
    }

    return status;
}


static
Int
_rpmsg_rpc_destroy(resmgr_context_t *ctp, io_devctl_t *msg,
                   rpmsg_rpc_ocb_t *ocb)
{
    Int status = EOK;
    struct rppc_msg_header * hdr = NULL;
    rpmsg_rpc_object * rpc = ocb->rpc;
    UInt8 buf[sizeof(struct rppc_instance_handle) + sizeof(struct rppc_msg_header)];
    struct rppc_instance_handle * instance = NULL;

    if (rpc->created != TRUE) {
        GT_0trace(curTrace, GT_4CLASS, "Already destroyed.");
        status = (EINVAL);
    }
    else if (!rpc->conn->destroy) {
        hdr = (struct rppc_msg_header *)buf;
        hdr->msg_type = RPPC_MSG_DESTROY_INSTANCE;
        hdr->msg_len = sizeof(struct rppc_instance_handle);
        instance = (struct rppc_instance_handle *)((UInt32)hdr + sizeof(struct rppc_msg_header));
        instance->endpoint_address = rpc->remoteAddr;
        instance->status = 0;

        status = MessageQCopy_send (rpc->conn->procId, // remote procid
                                    MultiProc_self(), // local procid
                                    rpc->conn->addr, // remote server
                                    rpc->addr, // local address
                                    buf, // connect msg
                                    sizeof(buf), // msg size
                                    TRUE); // wait for available bufs
        if (status != MessageQCopy_S_SUCCESS) {
            GT_0trace(curTrace, GT_4CLASS, "Failed to send disconnect message.");
            status = (EIO);
        }
        else {
            status = OsalSemaphore_pend(rpmsg_rpc_state.sem, 5000);
            if (rpc->created != FALSE || status < 0) {
                GT_0trace(curTrace, GT_4CLASS, "Semaphore pend failed.");
                status = (EIO);
            }
            else {
                status = (ETIMEDOUT);
            }
        }
    }
    else {
        /* This is the shutdown, remote proc has already been stopped,
         * so just set created to false. */
        rpc->created = FALSE;
    }

    return status;
}


Int
rpmsg_rpc_devctl(resmgr_context_t *ctp, io_devctl_t *msg, IOFUNC_OCB_T *i_ocb)
{
    Int status = 0;
    rpmsg_rpc_ocb_t *ocb = (rpmsg_rpc_ocb_t *)i_ocb;

    if ((status = iofunc_devctl_default(ctp, msg, &ocb->hdr)) != _RESMGR_DEFAULT)
        return(_RESMGR_ERRNO(status));
    status = 0;

    switch (msg->i.dcmd)
    {
        case RPPC_IOC_CREATE:
            status = _rpmsg_rpc_create (ctp, msg, ocb);
            break;
#if 0
        case RPPC_IOC_DESTROY:
            status = _rpmsg_rpc_destroy (ctp, msg, ocb);
            break;
#endif
        default:
            status = (ENOSYS);
            break;
    }

    return status;
}


/*!
 *  @brief      Attach a process to rpmsg-rpc user support framework.
 *
 *  @param      pid    Process identifier
 *
 *  @sa         _rpmsg_rpc_detach
 */
static
Int
_rpmsg_rpc_attach (rpmsg_rpc_object * rpc)
{
    Int32                status   = EOK;
    Bool                 flag     = FALSE;
    Bool                 isInit   = FALSE;
    List_Object *        bufList  = NULL;
    List_Object *        fxnList  = NULL;
    IArg                 key      = 0;
    List_Params          listparams;
    UInt32               i;

    GT_1trace (curTrace, GT_ENTER, "_rpmsg_rpc_attach", rpc);

    key = IGateProvider_enter (rpmsg_rpc_state.gateHandle);
    for (i = 0 ; (i < MAX_PROCESSES) ; i++) {
        if (rpmsg_rpc_state.eventState [i].rpc == rpc) {
            rpmsg_rpc_state.eventState [i].refCount++;
            isInit = TRUE;
            status = EOK;
            break;
        }
    }

    if (isInit == FALSE) {
        List_Params_init (&listparams);
        bufList = List_create (&listparams) ;
        fxnList = List_create (&listparams) ;
        /* Search for an available slot for user process. */
        for (i = 0 ; i < MAX_PROCESSES ; i++) {
            if (rpmsg_rpc_state.eventState [i].rpc == NULL) {
                rpmsg_rpc_state.eventState [i].rpc = rpc;
                rpmsg_rpc_state.eventState [i].refCount = 1;
                rpmsg_rpc_state.eventState [i].bufList = bufList;
                rpmsg_rpc_state.eventState [i].fxnList = fxnList;
                flag = TRUE;
                break;
            }
        }

        /* No free slots found. Let this check remain at run-time,
         * since it is dependent on user environment.
         */
        if (flag != TRUE) {
            /*! @retval Notify_E_RESOURCE Maximum number of
             supported user clients have already been registered. */
            status = -ENOMEM;
            GT_setFailureReason (curTrace,
                              GT_4CLASS,
                              "rpmsgDrv_attach",
                              status,
                              "Maximum number of supported user"
                                  " clients have already been "
                                  "registered.");
            if (bufList != NULL) {
                List_delete (&bufList);
            }
            if (fxnList != NULL) {
                List_delete (&fxnList);
            }
        }
    }
    IGateProvider_leave (rpmsg_rpc_state.gateHandle, key);

    GT_1trace (curTrace, GT_LEAVE, "_rpmsg_rpc_attach", status);

    /*! @retval Notify_S_SUCCESS Operation successfully completed. */
    return status ;
}


 /*!
 *  @brief      This function adds a data to a registered process.
 *
 *  @param      dce       RPC object associated with the client
 *  @param      src       Source address (endpoint) sending the data
 *  @param      pid       Process ID associated with the client
 *  @param      data      Data to be added
 *  @param      len       Length of data to be added
 *
 *  @sa
 */
Int
_rpmsg_rpc_addBufByPid (rpmsg_rpc_object *rpc,
                        UInt32             src,
                        UInt32             pid,
                        UInt16             msgId,
                        void *             data,
                        UInt32             len)
{
    Int32                   status = EOK;
    Bool                    flag   = FALSE;
    rpmsg_rpc_EventPacket * uBuf   = NULL;
    IArg                    key;
    UInt32                  i;
    WaitingReaders_t *item;
    MsgList_t *msgItem;
    List_Elem * elem = NULL;
    List_Elem * temp = NULL;

    GT_5trace (curTrace,
               GT_ENTER,
               "_rpmsg_rpc_addBufByPid",
               rpc,
               src,
               pid,
               data,
               len);

    GT_assert (curTrace, (rpmsg_rpc_state.isSetup == TRUE));

    key = IGateProvider_enter (rpmsg_rpc_state.gateHandle);
    /* Find the registration for this callback */
    for (i = 0 ; i < MAX_PROCESSES ; i++) {
        if (rpmsg_rpc_state.eventState [i].rpc == rpc) {
            flag = TRUE;
            break;
        }
    }
    IGateProvider_leave (rpmsg_rpc_state.gateHandle, key);

#if !defined(IPC_BUILD_OPTIMIZE)
    if (flag != TRUE) {
        /*! @retval ENOMEM Could not find a registered handler
                                      for this process. */
        status = -ENOMEM;
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "_rpmsgDrv_addBufByPid",
                             status,
                             "Could not find a registered handler "
                             "for this process.!");
    }
    else {
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */
        /* Allocate memory for the buf */
        pthread_mutex_lock(&rpmsg_rpc_state.lock);
        uBuf = get_uBuf();
        pthread_mutex_unlock(&rpmsg_rpc_state.lock);

#if !defined(IPC_BUILD_OPTIMIZE)
        if (uBuf == NULL) {
            /*! @retval Notify_E_MEMORY Failed to allocate memory for event
                                packet for received callback. */
            status = -ENOMEM;
            GT_setFailureReason (curTrace,
                                 GT_4CLASS,
                                 "_rpmsgDrv_addBufByPid",
                                 status,
                                 "Failed to allocate memory for event"
                                 " packet for received callback.!");
        }
        else {
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */
            key = IGateProvider_enter (rpmsg_rpc_state.gateHandle);
            List_traverse_safe(elem, temp, rpmsg_rpc_state.eventState [i].fxnList) {
                if (((rpmsg_rpc_FxnInfo *)elem)->msgId == msgId) {
                    List_remove(rpmsg_rpc_state.eventState [i].fxnList, elem);
                    break;
                }
            }
            IGateProvider_leave (rpmsg_rpc_state.gateHandle, key);

            if (elem != (List_Elem *)rpmsg_rpc_state.eventState [i].fxnList) {
                struct rppc_function * function;
                function = &(((rpmsg_rpc_FxnInfo *)elem)->func);
                _rpmsg_rpc_translate(NULL, (char *)function, pid, true);
                Memory_free(NULL, elem, sizeof(rpmsg_rpc_FxnInfo) +\
                            RPPC_TRANS_SIZE(function->num_translations));
            }

            List_elemClear (&(uBuf->element));
            GT_assert (curTrace,
                       (rpmsg_rpc_state.eventState [i].bufList != NULL));

            if (data) {
                Memory_copy(uBuf->data, data, len);
            }
            uBuf->len = len;

            List_put (rpmsg_rpc_state.eventState [i].bufList,
                      &(uBuf->element));
            pthread_mutex_lock(&rpmsg_rpc_state.lock);
            item = dequeue_waiting_reader(i);
            if (item) {
                // there is a waiting reader
                deliver_notification(i, item->rcvid);
                put_wr(item);
                pthread_mutex_unlock(&rpmsg_rpc_state.lock);
                status = EOK;
            }
            else {
                if (enqueue_notify_list(i) < 0) {
                    pthread_mutex_unlock(&rpmsg_rpc_state.lock);
                    status = -ENOMEM;
                    GT_setFailureReason (curTrace,
                                  GT_4CLASS,
                                  "_rpmsgDrv_addBufByPid",
                                  status,
                                  "Failed to allocate memory for notifier");
                }
                else {
                    msgItem = find_nl(i);
                    /* TODO: rpc could be NULL in some cases  */
                    if (rpc && msgItem) {
                        if (IOFUNC_NOTIFY_INPUT_CHECK(rpc->notify, msgItem->num_events, 0)) {
                            iofunc_notify_trigger(rpc->notify, msgItem->num_events, IOFUNC_NOTIFY_INPUT);
                        }
                    }
                    status = EOK;
                    pthread_cond_signal(&rpmsg_rpc_state.cond);
                    pthread_mutex_unlock(&rpmsg_rpc_state.lock);
                }
            }
#if !defined(IPC_BUILD_OPTIMIZE)
        }
    }
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */

    GT_1trace (curTrace, GT_LEAVE, "_rpmsgDrv_addBufByPid", status);

    return status;
}


/*!
 *  @brief      This function implements the callback registered with
 *              MessageQCopy_create for each client.  This function
 *              adds the message from the remote proc to a list
 *              where it is routed to the appropriate waiting reader.
 *
 *  @param      procId    processor Id from which interrupt is received
 *  @param      lineId    Interrupt line ID to be used
 *  @param      eventId   eventId registered
 *  @param      arg       argument to call back
 *  @param      payload   payload received
 *
 *  @sa
 */
Void
_rpmsg_rpc_cb (MessageQCopy_Handle handle, void * data, int len, void * priv,
               UInt32 src, UInt16 srcProc)
{
#if !defined(IPC_BUILD_OPTIMIZE)
    Int32                   status = 0;
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */
    rpmsg_rpc_object * rpc = NULL;
    struct rppc_msg_header * msg_hdr = NULL;
    struct rppc_instance_handle * instance;
    struct rppc_packet * packet = NULL;

    GT_6trace (curTrace,
               GT_ENTER,
               "_rpmsg_rpc_cb",
               handle,
               data,
               len,
               priv,
               src,
               srcProc);

    if (len < sizeof(struct rppc_msg_header)) {
        status = EINVAL;
        GT_setFailureReason(curTrace, GT_4CLASS, "_rpmsg_rpc_cb", status,
                            "len is smaller than sizeof rppc_msg_header");
        return;
    }

    rpc = (rpmsg_rpc_object *) priv;
    msg_hdr = (struct rppc_msg_header *)data;

    switch (msg_hdr->msg_type) {
        case RPPC_MSG_INSTANCE_CREATED:
            if (msg_hdr->msg_len != sizeof(struct rppc_instance_handle)) {
                status = EINVAL;
                rpc->created = FALSE;
                GT_setFailureReason(curTrace, GT_4CLASS, "_rpmsg_rpc_cb",
                                    status, "msg_len is invalid");
            }
            else {
                instance = (struct rppc_instance_handle *)
                          ((UInt32)msg_hdr + sizeof(struct rppc_msg_header));
                rpc->remoteAddr = instance->endpoint_address;
                if (instance->status != 0) {
                    rpc->created = FALSE;
                }
                else {
                    rpc->created = TRUE;
                }
            }
            /* post the semaphore to have the ioctl reply */
            OsalSemaphore_post(rpmsg_rpc_state.sem);
            break;
        case RPPC_MSG_INSTANCE_DESTROYED:
            if (msg_hdr->msg_len != sizeof(struct rppc_instance_handle)) {
                status = EINVAL;
                rpc->created = FALSE;
                GT_setFailureReason(curTrace, GT_4CLASS, "_rpmsg_rpc_cb",
                                    status, "msg_len is invalid");
            }
            else {
                instance = (struct rppc_instance_handle *)
                          ((UInt32)msg_hdr + sizeof(struct rppc_msg_header));
                rpc->remoteAddr = instance->endpoint_address;
                if (instance->status != 0) {
                    rpc->created = TRUE;
                }
                else {
                    rpc->created = FALSE;
                }
            }
            /* post the semaphore to have the ioctl reply */
            OsalSemaphore_post(rpmsg_rpc_state.sem);
            break;

        case RPPC_MSG_CALL_FUNCTION:
            if ((len != sizeof(struct rppc_msg_header) + msg_hdr->msg_len) ||
                (msg_hdr->msg_len < sizeof(struct rppc_packet))) {
                status = EINVAL;
                GT_setFailureReason(curTrace, GT_4CLASS, "_rpmsg_rpc_cb",
                                    status, "msg_len is invalid");
            }
            packet = (struct rppc_packet *)((UInt32)msg_hdr + sizeof(struct rppc_msg_header));
            if (len != sizeof(struct rppc_msg_header) + sizeof(struct rppc_packet) + packet->data_size) {
                status = EINVAL;
                GT_setFailureReason(curTrace, GT_4CLASS, "_rpmsg_rpc_cb",
                                    status, "msg_len is invalid");
            }
#if !defined(IPC_BUILD_OPTIMIZE)
            status =
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */
            _rpmsg_rpc_addBufByPid (rpc,
                                    src,
                                    rpc->pid,
                                    packet->msg_id,
                                    &packet->fxn_id,
                                    sizeof(packet->fxn_id) + sizeof(packet->result));
#if !defined(IPC_BUILD_OPTIMIZE)
            if (status < 0) {
                GT_setFailureReason (curTrace,
                                     GT_4CLASS,
                                     "_rpmsg_rpc_cb",
                                     status,
                                     "Failed to add callback packet for pid");
            }
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */
            break;
        default:
            break;
    }

    GT_0trace (curTrace, GT_LEAVE, "_rpmsg_rpc_cb");
}

 /**
  * Handler for ocb_calloc() requests.
  *
  * Special handler for ocb_calloc() requests that we export for control.  An
  * open request from the client will result in a call to our special ocb_calloc
  * handler.  This function attaches the client's pid using _rpmsg_dce_attach
  * and allocates client-specific information.  This function creates an
  * endpoint for the client to communicate with the dCE server on the
  * remote core also.
  *
  * \param ctp       Thread's associated context information.
  * \param device    Device attributes structure.
  *
  * \return Pointer to an iofunc_ocb_t OCB structure.
  */

IOFUNC_OCB_T *
rpmsg_rpc_ocb_calloc (resmgr_context_t * ctp, IOFUNC_ATTR_T * device)
{
    rpmsg_rpc_ocb_t *ocb = NULL;
    rpmsg_rpc_object *obj = NULL;
    struct _msg_info cl_info;
    rpmsg_rpc_dev_t * dev = NULL;
    int i = 0;
    Bool found = FALSE;
    char path1[20];
    char path2[20];

    GT_2trace (curTrace, GT_ENTER, "rpmsg_rpc_ocb_calloc",
               ctp, device);

    /* Allocate the OCB */
    ocb = (rpmsg_rpc_ocb_t *) calloc (1, sizeof (rpmsg_rpc_ocb_t));
    if (ocb == NULL){
        errno = ENOMEM;
        return (NULL);
    }

    ocb->pid = ctp->info.pid;

    /* Allocate memory for the rpmsg object. */
    obj = Memory_calloc (NULL, sizeof (rpmsg_rpc_object), 0u, NULL);
    if (obj == NULL) {
        errno = ENOMEM;
        free(ocb);
        return (NULL);
    }
    else {
        ocb->rpc = obj;
        IOFUNC_NOTIFY_INIT(obj->notify);
        obj->created = FALSE;
        /* determine conn and procId for communication based on which device
         * was opened */
        MsgInfo(ctp->rcvid, &cl_info);
        resmgr_pathname(ctp->id, 0, path1, sizeof(path1));
        for (i = 0; i < MAX_CONNS; i++) {
            if (rpmsg_rpc_state.objects[i] != NULL) {
                dev = rpmsg_rpc_state.objects[i]->dev;
                resmgr_pathname(dev->rpmsg_rpc.resmgr_id, 0, path2,
                                sizeof(path2));
                if (!strcmp(path1, path2)) {
                    found = TRUE;
                    break;
                }
            }
        }
        if (found) {
            obj->conn = rpmsg_rpc_state.objects[i];
            obj->procId = obj->conn->procId;
            obj->pid = ctp->info.pid;
            obj->mq = MessageQCopy_create (MessageQCopy_ADDRANY, NULL,
                                           _rpmsg_rpc_cb, obj, &obj->addr);
            if (obj->mq == NULL) {
                errno = ENOMEM;
                free(obj);
                free(ocb);
                return (NULL);
            }
            else {
                if (_rpmsg_rpc_attach (ocb->rpc) < 0) {
                    errno = ENOMEM;
                    MessageQCopy_delete (&obj->mq);
                    free(obj);
                    free(ocb);
                    return (NULL);
                }
            }
        }
    }

    GT_1trace (curTrace, GT_LEAVE, "rpmsg_rpc_ocb_calloc", ocb);

    return (IOFUNC_OCB_T *)(ocb);
}


/*!
 *  @brief      Detach a process from rpmsg-rpc user support framework.
 *
 *  @param      pid    Process identifier
 *
 *  @sa         _rpmsg_rpc_attach
 */
static
Int
_rpmsg_rpc_detach (rpmsg_rpc_object * rpc)
{
    Int32                status    = EOK;
    Int32                tmpStatus = EOK;
    Bool                 flag      = FALSE;
    List_Object *        bufList   = NULL;
    List_Object *        fxnList   = NULL;
    UInt32               i;
    IArg                 key;
    MsgList_t          * item;
    WaitingReaders_t   * wr        = NULL;
    struct _msg_info     info;

    GT_1trace (curTrace, GT_ENTER, "rpmsg_rpc_detach", rpc);

    key = IGateProvider_enter (rpmsg_rpc_state.gateHandle);

    for (i = 0 ; i < MAX_PROCESSES ; i++) {
        if (rpmsg_rpc_state.eventState [i].rpc == rpc) {
            if (rpmsg_rpc_state.eventState [i].refCount == 1) {
                rpmsg_rpc_state.eventState [i].refCount = 0;

                flag = TRUE;
                break;
            }
            else {
                rpmsg_rpc_state.eventState [i].refCount--;
                status = EOK;
                break;
            }
        }
    }
    IGateProvider_leave (rpmsg_rpc_state.gateHandle, key);

    if (flag == TRUE) {
        key = IGateProvider_enter (rpmsg_rpc_state.gateHandle);
        /* Last client being unregistered for this process. */
        rpmsg_rpc_state.eventState [i].rpc = NULL;

        /* Store in local variable to delete outside lock. */
        bufList = rpmsg_rpc_state.eventState [i].bufList;

        rpmsg_rpc_state.eventState [i].bufList = NULL;

        /* Store in local variable to delete outside lock. */
        fxnList = rpmsg_rpc_state.eventState [i].fxnList;

        rpmsg_rpc_state.eventState [i].fxnList = NULL;

        IGateProvider_leave (rpmsg_rpc_state.gateHandle, key);
    }

    if (flag != TRUE) {
#if !defined(IPC_BUILD_OPTIMIZE)
        if (i == MAX_PROCESSES) {
            /*! @retval Notify_E_NOTFOUND The specified user process was
                     not found registered with Notify Driver module. */
            status = -ENOMEM;
            GT_setFailureReason (curTrace,
                              GT_4CLASS,
                              "rpmsg_rpc_detach",
                              status,
                              "The specified user process was not found"
                              " registered with rpmsg Driver module.");
        }
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */
    }
    else {
        if (bufList != NULL) {
            /* Dequeue waiting readers and reply to them */
            pthread_mutex_lock(&rpmsg_rpc_state.lock);
            while ((wr = dequeue_waiting_reader(i)) != NULL) {
                /* Check if rcvid is still valid */
                if (MsgInfo(wr->rcvid, &info) != -1) {
                    put_wr(wr);
                    pthread_mutex_unlock(&rpmsg_rpc_state.lock);
                    MsgError(wr->rcvid, EINTR);
                    pthread_mutex_lock(&rpmsg_rpc_state.lock);
                }
            }
            /* Check for pending ionotify/select calls */
            if (rpc) {
                if (IOFUNC_NOTIFY_INPUT_CHECK(rpc->notify, 1, 0)) {
                    iofunc_notify_trigger(rpc->notify, 1, IOFUNC_NOTIFY_INPUT);
                }
            }

            /* Free event packets for any received but unprocessed events. */
            while ((item = find_nl(i)) != NULL) {
                if (dequeue_notify_list_item(item) >= 0) {
                    rpmsg_rpc_EventPacket * uBuf = NULL;

                    uBuf = (rpmsg_rpc_EventPacket *) List_get (bufList);

                    /*  Let the check remain at run-time. */
                    if (uBuf != NULL) {
                        put_uBuf(uBuf);
                    }
                }
            }
            pthread_mutex_unlock(&rpmsg_rpc_state.lock);

            /* Last client being unregistered with Notify module. */
            List_delete (&bufList);
        }
        if (fxnList != NULL) {
            key = IGateProvider_enter (rpmsg_rpc_state.gateHandle);
            rpmsg_rpc_FxnInfo * fxnInfo = NULL;
            while ((fxnInfo = (rpmsg_rpc_FxnInfo *)List_dequeue (fxnList))) {
                Memory_free (NULL, fxnInfo, sizeof(rpmsg_rpc_FxnInfo) +\
                             RPPC_TRANS_SIZE(fxnInfo->func.num_translations));
            }
            IGateProvider_leave (rpmsg_rpc_state.gateHandle, key);
            List_delete (&fxnList);
        }

#if !defined(IPC_BUILD_OPTIMIZE)
        if ((tmpStatus < 0) && (status >= 0)) {
            status =  tmpStatus;
            GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "rpmsg_rpc_detach",
                             status,
                             "Failed to delete termination semaphore!");
        }
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */
    }

    GT_1trace (curTrace, GT_LEAVE, "rpmsg_rpc_detach", status);

    /*! @retval Notify_S_SUCCESS Operation successfully completed */
    return status;
}

 /**
  * Handler for ocb_free() requests.
  *
  * Special handler for ocb_free() requests that we export for control.  A
  * close request from the client will result in a call to our special ocb_free
  * handler.  This function detaches the client's pid using _rpmsg_dce_detach
  * and frees any client-specific information that was allocated.
  *
  * \param i_ocb     OCB associated with client's session.
  *
  * \return POSIX errno value.
  *
  * \retval None.
  */

void
rpmsg_rpc_ocb_free (IOFUNC_OCB_T * i_ocb)
{
    rpmsg_rpc_ocb_t * ocb = (rpmsg_rpc_ocb_t *)i_ocb;
    rpmsg_rpc_object *obj;

    if (ocb && ocb->rpc) {
        obj = ocb->rpc;
        if (obj->created == TRUE) {
            /* Need to disconnect this device */
            _rpmsg_rpc_destroy(NULL, NULL, ocb);
        }
        _rpmsg_rpc_detach(ocb->rpc);
        if (obj->mq) {
            MessageQCopy_delete (&obj->mq);
            obj->mq = NULL;
        }
        free (obj);
        free (ocb);
    }
}

 /**
  * Handler for close_ocb() requests.
  *
  * This function removes the notification entries associated with the current
  * client.
  *
  * \param ctp       Thread's associated context information.
  * \param reserved  This argument must be NULL.
  * \param ocb       OCB associated with client's session.
  *
  * \return POSIX errno value.
  *
  * \retval EOK      Success.
  */

Int
rpmsg_rpc_close_ocb (resmgr_context_t *ctp, void *reserved, RESMGR_OCB_T *ocb)
{
    rpmsg_rpc_ocb_t * rpc_ocb = (rpmsg_rpc_ocb_t *)ocb;
    iofunc_notify_remove(ctp, rpc_ocb->rpc->notify);
    return (iofunc_close_ocb_default(ctp, reserved, ocb));
}

 /**
  * Handler for read() requests.
  *
  * Handles special read() requests that we export for control.  A read
  * request will get a message from the remote processor that is associated
  * with the client that is calling read().
  *
  * \param ctp     Thread's associated context information.
  * \param msg     The actual read() message.
  * \param ocb     OCB associated with client's session.
  *
  * \return POSIX errno value.
  *
  * \retval EOK      Success.
  * \retval EAGAIN   Call is non-blocking and no messages available.
  * \retval ENOMEM   Not enough memory to preform the read.
  */

int rpmsg_rpc_read(resmgr_context_t *ctp, io_read_t *msg, RESMGR_OCB_T *ocb)
{
    Int status;
    rpmsg_rpc_ocb_t * rpc_ocb = (rpmsg_rpc_ocb_t *)ocb;
    rpmsg_rpc_object * rpc = rpc_ocb->rpc;
    Bool                    flag     = FALSE;
    Int                  retVal   = EOK;
    UInt32                  i;
    MsgList_t          * item;
    Int                  nonblock;

    if ((status = iofunc_read_verify(ctp, msg, ocb, &nonblock)) != EOK)
        return (status);

    if (rpc->created != TRUE) {
        return (ENOTCONN);
    }

    for (i = 0 ; i < MAX_PROCESSES ; i++) {
        if (rpmsg_rpc_state.eventState [i].rpc == rpc) {
            flag = TRUE;
            break;
        }
    }

    /* Let the check remain at run-time. */
    if (flag == TRUE) {
        /* Let the check remain at run-time for handling any run-time
        * race conditions.
        */
        if (rpmsg_rpc_state.eventState [i].bufList != NULL) {
            pthread_mutex_lock(&rpmsg_rpc_state.lock);
            item = find_nl(i);
            if (dequeue_notify_list_item(item) < 0) {
                if (nonblock) {
                    pthread_mutex_unlock(&rpmsg_rpc_state.lock);
                    return EAGAIN;
                }
                else {
                    retVal = enqueue_waiting_reader(i, ctp->rcvid);
                    if (retVal == EOK) {
                        pthread_cond_signal(&rpmsg_rpc_state.cond);
                        pthread_mutex_unlock(&rpmsg_rpc_state.lock);
                        return(_RESMGR_NOREPLY);
                    }
                    retVal = ENOMEM;
                    pthread_mutex_unlock(&rpmsg_rpc_state.lock);
                }
            }
            else {
                deliver_notification(i, ctp->rcvid);
                pthread_mutex_unlock(&rpmsg_rpc_state.lock);
                return(_RESMGR_NOREPLY);
            }
        }
    }

    /*! @retval Number-of-bytes-read Number of bytes read. */
    return retVal;
}

 /**
  * Unblock read calls
  *
  * This function checks if the client is blocked on a read call and if so,
  * unblocks the client.
  *
  * \param ctp     Thread's associated context information.
  * \param msg     The pulse message.
  * \param ocb     OCB associated with client's session.
  *
  * \return POSIX errno value.
  *
  * \retval EINTR    The client has been unblocked.
  * \retval other    The client has not been unblocked or the client was not
  *                  blocked.
  */

int rpmsg_rpc_read_unblock(resmgr_context_t *ctp, io_pulse_t *msg, iofunc_ocb_t *ocb)
{
    UInt32                  i;
    Bool                    flag     = FALSE;
    WaitingReaders_t      * wr;
    rpmsg_rpc_ocb_t * rpc_ocb = (rpmsg_rpc_ocb_t *)ocb;
    rpmsg_rpc_object * rpc = rpc_ocb->rpc;

    for (i = 0 ; i < MAX_PROCESSES ; i++) {
        if (rpmsg_rpc_state.eventState [i].rpc == rpc) {
            flag = TRUE;
            break;
        }
    }

    /*  Let the check remain at run-time. */
    if (flag == TRUE) {
        /* Let the check remain at run-time for handling any run-time
         * race conditions.
         */
        if (rpmsg_rpc_state.eventState [i].bufList != NULL) {
            pthread_mutex_lock(&rpmsg_rpc_state.lock);
            wr = find_waiting_reader(i, ctp->rcvid);
            if (wr) {
                put_wr(wr);
                pthread_mutex_unlock(&rpmsg_rpc_state.lock);
                return (EINTR);
            }
            pthread_mutex_unlock(&rpmsg_rpc_state.lock);
        }
    }

    return _RESMGR_NOREPLY;
}

/**
  * Handler for unblock() requests.
  *
  * Handles unblock request for the client which is requesting to no longer be
  * blocked on the rpmsg-rpc driver.
  *
  * \param ctp     Thread's associated context information.
  * \param msg     The pulse message.
  * \param ocb     OCB associated with client's session.
  *
  * \return POSIX errno value.
  *
  * \retval EINTR    The rcvid has been unblocked.
  */

int rpmsg_rpc_unblock(resmgr_context_t *ctp, io_pulse_t *msg, RESMGR_OCB_T *ocb)
{
    int status = _RESMGR_NOREPLY;
    struct _msg_info        info;

    /*
     * Try to run the default unblock for this message.
     */
    if ((status = iofunc_unblock_default(ctp,msg,ocb)) != _RESMGR_DEFAULT) {
        return status;
    }

    /*
     * Check if rcvid is still valid and still has an unblock
     * request pending.
     */
    if (MsgInfo(ctp->rcvid, &info) == -1 ||
        !(info.flags & _NTO_MI_UNBLOCK_REQ)) {
        return _RESMGR_NOREPLY;
    }

    if (rpmsg_rpc_read_unblock(ctp, msg, ocb) != _RESMGR_NOREPLY) {
           return _RESMGR_ERRNO(EINTR);
    }

    return _RESMGR_ERRNO(EINTR);
}


uint32_t
_rpmsg_rpc_pa2da(ProcMgr_Handle handle, uint32_t pa)
{
    Int status = 0;
    uint32_t da;

    status = ProcMgr_translateAddr(handle, (Ptr *)&da,
                                   ProcMgr_AddrType_SlaveVirt,
                                   (Ptr)pa, ProcMgr_AddrType_MasterPhys);
    if (status >= 0) {
        return da;
    }
    else {
        return 0;
    }
}

int
_rpmsg_rpc_translate(ProcMgr_Handle handle, char *data, pid_t pid, bool reverse)
{
    int status = EOK;
    struct rppc_function * function = NULL;
    struct rppc_param_translation * translation = NULL;
    int i = 0;
    off64_t phys_addr;
    off64_t paddr[RPPC_MAX_PARAMETERS];
    uint32_t ipu_addr;
    size_t phys_len = 0;
    uintptr_t ptr;
    void * vptr[RPPC_MAX_PARAMETERS];
    uint32_t idx = 0;

    function = (struct rppc_function *)data;
    memset(vptr, 0, sizeof(void *) * RPPC_MAX_PARAMETERS);
    memset(paddr, 0, sizeof(off64_t) * RPPC_MAX_PARAMETERS);

    translation = (struct rppc_param_translation *)function->translations;
    for (i = 0; i < function->num_translations; i++) {
        idx = translation[i].index;
        if (idx >= function->num_params) {
            status = -EINVAL;
            break;
        }
        if (translation[i].offset + sizeof(uint32_t) > function->params[idx].size) {
            status = -EINVAL;
            break;
        }
        if (!vptr[idx]) {
            /* get the physical address of ptr */
            status = mem_offset64_peer(pid,
                                       reverse ? function->params[idx].base : function->params[idx].data,
                                       function->params[idx].size,
                                       &paddr[idx], &phys_len);
            if (status >= 0 && phys_len == function->params[idx].size) {
                /* map into my process space */
                vptr[idx] = mmap64(NULL, function->params[idx].size,
                                   PROT_NOCACHE | PROT_READ | PROT_WRITE,
                                   MAP_PHYS | MAP_SHARED, NOFD, paddr[idx]);
                if (vptr[idx] == MAP_FAILED) {
                    vptr[idx] = 0;
                    status = -ENOMEM;
                    break;
                }
            }
            else {
                status = -EINVAL;
                break;
            }
        }
        /* Get physical address of the contents */
        ptr = (uint32_t)vptr[idx] + translation[i].offset;
        if (reverse) {
            *(uint32_t *)ptr = translation[i].base;
        }
        else {
            translation[i].base = *(uint32_t *)ptr;
            status = mem_offset64_peer(pid, *(uint32_t *)ptr, sizeof(uint32_t),
                                       &phys_addr, &phys_len);
            if (status >= 0 && phys_len == sizeof(uint32_t)) {
                /* translate pa2da */
                if ((ipu_addr =
                        _rpmsg_rpc_pa2da(handle, (uint32_t)phys_addr)) != 0)
                    /* update vptr contents */
                    *(uint32_t *)ptr = ipu_addr;
                else {
                    status = -EINVAL;
                    break;
                }
            }
            else {
                status = -EINVAL;
                break;
            }
        }
    }

    /* No need to do this for reverse translations */
    for (i = 0; i < function->num_params && status >= 0 && !reverse; i++) {
        if (function->params[i].type == RPPC_PARAM_TYPE_PTR) {
            if (paddr[i]) {
                phys_addr = paddr[i];
            }
            else {
                /* translate the param pointer */
                status = mem_offset64_peer(pid,
                                           (uintptr_t)(function->params[i].data),
                                           function->params[i].size, &phys_addr,
                                           &phys_len);
            }
            if (status >= 0) {
                if ((ipu_addr =
                            _rpmsg_rpc_pa2da(handle, (uint32_t)phys_addr)) != 0) {
                    function->params[i].base = function->params[i].data;
                    function->params[i].data = ipu_addr;
                }
                else {
                    status = -EINVAL;
                    break;
                }
            }
            else {
                status = -EINVAL;
                break;
            }
        }
    }

    for (i = 0; i < function->num_params; i++) {
        if (vptr[i])
            munmap(vptr[i], function->params[i].size);
    }

    return status;
}

 /**
  * Handler for write() requests.
  *
  * Handles special write() requests that we export for control.  A write()
  * request will send a message to the remote processor which is associated with
  * the client.
  *
  * \param ctp     Thread's associated context information.
  * \param msg     The actual write() message.
  * \param io_ocb  OCB associated with client's session.
  *
  * \return POSIX errno value.
  *
  * \retval EOK      Success.
  * \retval ENOMEM   Not enough memory to preform the write.
  * \retval EIO      MessageQCopy_send failed.
  * \retval EINVAL   msg->i.bytes is negative.
  */

int
rpmsg_rpc_write(resmgr_context_t *ctp, io_write_t *msg, RESMGR_OCB_T *io_ocb)
{
    int status;
    char buf[MessageQCopy_BUFSIZE];
    int bytes;
    rpmsg_rpc_ocb_t * ocb = (rpmsg_rpc_ocb_t *)io_ocb;
    rpmsg_rpc_object * rpc = ocb->rpc;
    struct rppc_msg_header * msg_hdr = NULL;
    struct rppc_packet *packet = NULL;
    struct rppc_function *function = NULL;
    char usr_msg[MessageQCopy_BUFSIZE];
    int i = 0;
    rpmsg_rpc_EventState * event_state = NULL;
    rpmsg_rpc_FxnInfo * fxn_info = NULL;
    IArg key = 0;

    if ((status = iofunc_write_verify(ctp, msg, io_ocb, NULL)) != EOK) {
        return (status);
    }

    bytes = ((int64_t) msg->i.nbytes) + sizeof(struct rppc_msg_header) > MessageQCopy_BUFSIZE ?
            MessageQCopy_BUFSIZE - sizeof(struct rppc_msg_header) : msg->i.nbytes;
    if (bytes < 0) {
        return EINVAL;
    }
    _IO_SET_WRITE_NBYTES (ctp, bytes);

    for (i = 0 ; i < MAX_PROCESSES ; i++) {
        if (rpmsg_rpc_state.eventState [i].rpc == rpc) {
            break;
        }
    }
    if (i == MAX_PROCESSES) {
        return EINVAL;
    }
    event_state = &rpmsg_rpc_state.eventState[i];

    msg_hdr = (struct rppc_msg_header *)buf;
    packet = (struct rppc_packet *)((UInt32)msg_hdr + sizeof(struct rppc_msg_header));

    status = resmgr_msgread(ctp, usr_msg, bytes, sizeof(msg->i));
    if (status != bytes) {
        return (errno);
    }
    else if (bytes < sizeof(struct rppc_function)) {
        return (EINVAL);
    }
    function = (struct rppc_function *)usr_msg;

    if (bytes < RPPC_PARAM_SIZE(function->num_translations)) {
         return (EINVAL);
    }

    /* check that we're in the correct state */
    if (rpc->created != TRUE) {
        return (EINVAL);
    }

    /* store the fxn info for use with reverse translation */
    fxn_info = Memory_alloc (NULL, sizeof(rpmsg_rpc_FxnInfo) +\
                             RPPC_TRANS_SIZE(function->num_translations),
                             0, NULL);
    List_elemClear(&(fxn_info->element));
    Memory_copy (&(fxn_info->func), function,
                 RPPC_PARAM_SIZE(function->num_translations));

    status = _rpmsg_rpc_translate(rpc->conn->procH, (char *)&(fxn_info->func),
                                  ctp->info.pid, false);
    if (status < 0) {
        Memory_free(NULL, fxn_info, sizeof(rpmsg_rpc_FxnInfo) +\
                    RPPC_TRANS_SIZE(function->num_translations));
        return -status;
    }

    msg_hdr->msg_type = RPPC_MSG_CALL_FUNCTION;
    msg_hdr->msg_len = sizeof(struct rppc_packet);

    /* initialize the packet structure */
    packet->desc = RPPC_DESC_EXEC_SYNC;
    packet->msg_id = msg_id == 0xFFFF ? msg_id = 1 : ++(msg_id);
    packet->flags = (0x8000);//OMAPRPC_POOLID_DEFAULT;
    packet->fxn_id = RPPC_SET_FXN_IDX(function->fxn_id);
    packet->result = 0;
    packet->data_size = 0;

    for (i = 0; i < function->num_params; i++) {
        ((UInt32 *)(packet->data))[i*2] = function->params[i].size;
        ((UInt32 *)(packet->data))[(i*2)+1] = fxn_info->func.params[i].data;
        packet->data_size += (sizeof(UInt32) * 2);
    }
    msg_hdr->msg_len += packet->data_size;

    fxn_info->msgId = packet->msg_id;
    key = IGateProvider_enter (rpmsg_rpc_state.gateHandle);
    List_enqueue(event_state->fxnList, &(fxn_info->element));
    IGateProvider_leave (rpmsg_rpc_state.gateHandle, key);

    status = MessageQCopy_send(rpc->conn->procId, MultiProc_self(),
                              rpc->remoteAddr, rpc->addr, buf,
                              msg_hdr->msg_len + sizeof(struct rppc_msg_header),
                              TRUE);
    if (status < 0) {
        key = IGateProvider_enter (rpmsg_rpc_state.gateHandle);
        List_remove(event_state->fxnList, &(fxn_info->element));
        IGateProvider_leave (rpmsg_rpc_state.gateHandle, key);
        Memory_free(NULL, fxn_info, sizeof(rpmsg_rpc_FxnInfo) +\
                    RPPC_TRANS_SIZE(function->num_translations));
        return (EIO);
    }

    return(EOK);
}



 /**
  * Handler for notify() requests.
  *
  * Handles special notify() requests that we export for control.  A notify
  * request results from the client calling select().
  *
  * \param ctp     Thread's associated context information.
  * \param msg     The actual notify() message.
  * \param ocb     OCB associated with client's session.
  *
  * \return POSIX errno value.
  */

Int rpmsg_rpc_notify( resmgr_context_t *ctp, io_notify_t *msg, RESMGR_OCB_T *ocb)
{
    rpmsg_rpc_ocb_t * rpc_ocb = (rpmsg_rpc_ocb_t *)ocb;
    rpmsg_rpc_object * rpc = rpc_ocb->rpc;
    int trig;
    int i = 0;
    Bool flag = FALSE;
    MsgList_t * item = NULL;
    int status = EOK;

    trig = _NOTIFY_COND_OUTPUT; /* clients can give us data */

    for (i = 0 ; i < MAX_PROCESSES ; i++) {
        if (rpmsg_rpc_state.eventState [i].rpc == rpc) {
            flag = TRUE;
            break;
        }
    }

    pthread_mutex_lock(&rpmsg_rpc_state.lock);
    /* Let the check remain at run-time. */
    if (flag == TRUE) {
        /* Let the check remain at run-time for handling any run-time
        * race conditions.
        */
        if (rpmsg_rpc_state.eventState [i].bufList != NULL) {
            item = find_nl(i);
            if (item && item->num_events > 0) {
                trig |= _NOTIFY_COND_INPUT;
            }
        }
    }
    status = iofunc_notify(ctp, msg, rpc_ocb->rpc->notify, trig, NULL, NULL);
    pthread_mutex_unlock(&rpmsg_rpc_state.lock);
    return status;
}

 /**
  * Detaches an rpmsg-dce resource manager device name.
  *
  * \param dev     The device to detach.
  *
  * \return POSIX errno value.
  */

static
Void
_deinit_rpmsg_rpc_device (rpmsg_rpc_dev_t * dev)
{
    resmgr_detach(ipc_dpp, dev->rpmsg_rpc.resmgr_id, _RESMGR_DETACH_CLOSE);

    pthread_mutex_destroy(&dev->rpmsg_rpc.mutex);

    free (dev);

    return;
}

 /**
  * Initializes and attaches rpmsg-dce resource manager functions to an
  * rpmsg-dce device name.
  *
  * \param num     The number to append to the end of the device name.
  *
  * \return Pointer to the created rpmsg_dce_dev_t device.
  */

static
rpmsg_rpc_dev_t *
_init_rpmsg_rpc_device (char * name)
{
    iofunc_attr_t  * attr;
    resmgr_attr_t    resmgr_attr;
    rpmsg_rpc_dev_t * dev = NULL;

    dev = malloc(sizeof(*dev));
    if (dev == NULL) {
        return NULL;
    }

    memset(&resmgr_attr, 0, sizeof resmgr_attr);
    resmgr_attr.nparts_max = 10;
    resmgr_attr.msg_max_size = 2048;
    memset(&dev->rpmsg_rpc.mattr, 0, sizeof(iofunc_mount_t));
    dev->rpmsg_rpc.mattr.flags = ST_NOSUID | ST_NOEXEC;
    dev->rpmsg_rpc.mattr.conf = IOFUNC_PC_CHOWN_RESTRICTED |
                              IOFUNC_PC_NO_TRUNC |
                              IOFUNC_PC_SYNC_IO;
    dev->rpmsg_rpc.mattr.funcs = &dev->rpmsg_rpc.mfuncs;
    memset(&dev->rpmsg_rpc.mfuncs, 0, sizeof(iofunc_funcs_t));
    dev->rpmsg_rpc.mfuncs.nfuncs = _IOFUNC_NFUNCS;
    dev->rpmsg_rpc.mfuncs.ocb_calloc = rpmsg_rpc_ocb_calloc;
    dev->rpmsg_rpc.mfuncs.ocb_free = rpmsg_rpc_ocb_free;
    iofunc_func_init(_RESMGR_CONNECT_NFUNCS, &dev->rpmsg_rpc.cfuncs,
                     _RESMGR_IO_NFUNCS, &dev->rpmsg_rpc.iofuncs);
    iofunc_attr_init(attr = &dev->rpmsg_rpc.cattr, S_IFCHR | 0777, NULL, NULL);
    dev->rpmsg_rpc.iofuncs.devctl = rpmsg_rpc_devctl;
    dev->rpmsg_rpc.iofuncs.notify = rpmsg_rpc_notify;
    dev->rpmsg_rpc.iofuncs.close_ocb = rpmsg_rpc_close_ocb;
    dev->rpmsg_rpc.iofuncs.read = rpmsg_rpc_read;
    dev->rpmsg_rpc.iofuncs.write = rpmsg_rpc_write;
    dev->rpmsg_rpc.iofuncs.unblock = rpmsg_rpc_read_unblock;
    attr->mount = &dev->rpmsg_rpc.mattr;
    iofunc_time_update(attr);
    pthread_mutex_init(&dev->rpmsg_rpc.mutex, NULL);

    snprintf (dev->rpmsg_rpc.device_name, _POSIX_PATH_MAX, "/dev/%s", name);
    if (-1 == (dev->rpmsg_rpc.resmgr_id =
        resmgr_attach(ipc_dpp, &resmgr_attr,
                      dev->rpmsg_rpc.device_name, _FTYPE_ANY, 0,
                      &dev->rpmsg_rpc.cfuncs,
                      &dev->rpmsg_rpc.iofuncs, attr))) {
        pthread_mutex_destroy(&dev->rpmsg_rpc.mutex);
        free(dev);
        return(NULL);
    }

    return(dev);
}

/**
 * Callback passed to MessageQCopy_registerNotify.
 *
 * This callback is called when a remote processor creates a MessageQCopy
 * handle with the same name as the local MessageQCopy handle and then
 * calls NameMap_register to notify the HOST of the handle.
 *
 * \param handle    The remote handle.
 * \param procId    The remote proc ID of the remote handle.
 * \param endpoint  The endpoint address of the remote handle.
 *
 * \return None.
 */

static
Void
_rpmsg_rpc_notify_cb (MessageQCopy_Handle handle, UInt16 procId,
                      UInt32 endpoint, Char * desc, Bool create)
{
    Int status = 0, i = 0, j = 0;
    Bool found = FALSE;
    rpmsg_rpc_conn_object * obj = NULL;
    char msg[512];
    struct rppc_msg_header * msg_hdr = (struct rppc_msg_header *)msg;

    for (i = 0; i < MAX_CONNS; i++) {
        if (rpmsg_rpc_state.objects[i] == NULL) {
            found = TRUE;
            break;
        }
    }

    for (j = 0; j < NUM_RPMSG_RPC_QUEUES; j++) {
        if (rpmsg_rpc_state.mqHandle[j] == handle) {
            break;
        }
    }

    if (found && j < NUM_RPMSG_RPC_QUEUES) {
        /* found a space to save this mq handle, allocate memory */
        obj = Memory_calloc (NULL, sizeof (rpmsg_rpc_conn_object), 0x0, NULL);
        if (obj) {
            /* store the object in the module info */
            rpmsg_rpc_state.objects[i] = obj;

            /* store the mq info in the object */
            obj->mq = handle;
            obj->procId = procId;
            status = ProcMgr_open(&obj->procH, obj->procId);
            if (status < 0) {
                Osal_printf("Failed to open handle to proc %d", procId);
                Memory_free(NULL, obj, sizeof(rpmsg_rpc_object));
            }
            else {
                obj->addr = endpoint;

                /* create a /dev/rpmsg-rpc instance for users to open */
                obj->dev = _init_rpmsg_rpc_device(desc);
                if (obj->dev == NULL) {
                    Osal_printf("Failed to create %s", desc);
                    ProcMgr_close(&obj->procH);
                    Memory_free(NULL, obj, sizeof(rpmsg_rpc_object));
                }
            }
        }

        /* Send a message to query the chan info. Handle creating of the conn
         * in the callback */
        msg_hdr->msg_type = RPPC_MSG_QUERY_CHAN_INFO;
        msg_hdr->msg_len = 0;
        status = MessageQCopy_send(procId, MultiProc_self(), endpoint,
                                   rpmsg_rpc_state.endpoint[j],
                                   msg, sizeof(struct rppc_msg_header),
                                   TRUE);
    }
}

 /**
  * Callback passed to MessageQCopy_create for the module.
  *
  * This callback is called when a message is received for the rpmsg-dce
  * module.  This callback will never be called, since each client connection
  * gets it's own endpoint for message passing.
  *
  * \param handle    The local MessageQCopy handle.
  * \param data      Data message
  * \param len       Length of data message
  * \param priv      Private information for the endpoint
  * \param src       Remote endpoint sending this message
  * \param srcProc   Remote proc ID sending this message
  *
  * \return None.
  */

static
Void
_rpmsg_rpc_module_cb (MessageQCopy_Handle handle, void * data, int len,
                      void * priv, UInt32 src, UInt16 srcProc)
{
    Int status = 0, i = 0, j = 0;
    rpmsg_rpc_conn_object * obj = NULL;
    struct rppc_msg_header * msg_hdr = (struct rppc_msg_header *)data;

    Osal_printf ("_rpmsg_rpc_module_cb callback");

    for (i = 0; i < MAX_CONNS; i++) {
        if (rpmsg_rpc_state.objects[i] != NULL &&
            rpmsg_rpc_state.objects[i]->addr == src) {
            obj = rpmsg_rpc_state.objects[i];
            break;
        }
    }

    for (j = 0; j < NUM_RPMSG_RPC_QUEUES; j++) {
        if (rpmsg_rpc_state.mqHandle[j] == handle) {
            break;
        }
    }

    if (obj && j < NUM_RPMSG_RPC_QUEUES) {
        switch (msg_hdr->msg_type) {
            case RPPC_MSG_CHAN_INFO:
            {
                struct rppc_channel_info * chan_info =
                                      (struct rppc_channel_info *)(msg_hdr + 1);
                obj->numFuncs = chan_info->num_funcs;
                /* TODO: Query the info about each function */
                break;
            }
            default:
                status = EINVAL;
                GT_setFailureReason(curTrace, GT_4CLASS, "_rpmsg_rpc_module_cb",
                                    status, "invalid msg_type received");
                break;
        }
    }
}


/*!
 *  @brief  Module setup function.
 *
 *  @sa     rpmsg_rpc_destroy
 */
Int
rpmsg_rpc_setup (Void)
{
    UInt16 i;
    List_Params  listparams;
    Int status = 0;
    Error_Block eb;
    pthread_attr_t thread_attr;
    struct sched_param sched_param;

    GT_0trace (curTrace, GT_ENTER, "rpmsg_rpc_setup");

    Error_init(&eb);

    List_Params_init (&listparams);
    rpmsg_rpc_state.gateHandle = (IGateProvider_Handle)
                     GateSpinlock_create ((GateSpinlock_Handle) NULL, &eb);
#if !defined(IPC_BUILD_OPTIMIZE)
    if (rpmsg_rpc_state.gateHandle == NULL) {
        status = -ENOMEM;
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "_rpmsg_rpc_setup",
                             status,
                             "Failed to create spinlock gate!");
    }
    else {
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */
        for (i = 0 ; i < MAX_PROCESSES ; i++) {
            rpmsg_rpc_state.eventState [i].bufList = NULL;
            rpmsg_rpc_state.eventState [i].rpc = NULL;
            rpmsg_rpc_state.eventState [i].refCount = 0;
            rpmsg_rpc_state.eventState [i].head = NULL;
            rpmsg_rpc_state.eventState [i].tail = NULL;
        }

        pthread_attr_init(&thread_attr);
        sched_param.sched_priority = PRIORITY_REALTIME_LOW;
        pthread_attr_setinheritsched(&thread_attr, PTHREAD_EXPLICIT_SCHED);
        pthread_attr_setschedpolicy(&thread_attr, SCHED_RR);
        pthread_attr_setschedparam(&thread_attr, &sched_param);

        rpmsg_rpc_state.run = TRUE;
        if (pthread_create(&rpmsg_rpc_state.nt, &thread_attr, notifier_thread, NULL) == EOK) {
            pthread_setname_np(rpmsg_rpc_state.nt, "rpmsg-rpc-notifier");
            /* Initialize the driver mapping array. */
            Memory_set (&rpmsg_rpc_state.objects,
                        0,
                        (sizeof (rpmsg_rpc_conn_object *)
                         *  MAX_CONNS));
            for (i = 0; i < NUM_RPMSG_RPC_QUEUES; i++) {
                /* create a local handle and register for notifications with MessageQCopy */
                rpmsg_rpc_state.mqHandle[i] = MessageQCopy_create (
                                                   MessageQCopy_ADDRANY,
                                                   rpmsg_rpc_names[i].name,
                                                   _rpmsg_rpc_module_cb,
                                                   NULL,
                                                   &rpmsg_rpc_state.endpoint[i]);
                if (rpmsg_rpc_state.mqHandle[i] == NULL) {
                    /*! @retval RPC_FAIL Failed to create MessageQCopy handle! */
                    status = -ENOMEM;
                    GT_setFailureReason (curTrace,
                                         GT_4CLASS,
                                         "rpmsg_rpc_setup",
                                         status,
                                         "Failed to create MessageQCopy handle!");
                    break;
                }
                else {
                    /* TBD: This could be replaced with a messageqcopy_open type call, one for
                     * each core */
                    status = MessageQCopy_registerNotify (rpmsg_rpc_state.mqHandle[i],
                                                        _rpmsg_rpc_notify_cb);
                    if (status < 0) {
                        MessageQCopy_delete (&rpmsg_rpc_state.mqHandle[i]);
                        /*! @retval RPC_FAIL Failed to register MQCopy handle! */
                        status = -ENOMEM;
                        GT_setFailureReason (curTrace,
                                             GT_4CLASS,
                                             "rpmsg_rpc_setup",
                                             status,
                                             "Failed to register MQCopy handle!");
                        break;
                    }
                }
            }
            if (status >= 0){
                rpmsg_rpc_state.sem = OsalSemaphore_create(OsalSemaphore_Type_Binary);
                if (rpmsg_rpc_state.sem == NULL) {
                    //MessageQCopy_unregisterNotify();
                    /*! @retval RPC_FAIL Failed to register MQCopy handle! */
                    status = -ENOMEM;
                    GT_setFailureReason (curTrace,
                                         GT_4CLASS,
                                         "rpmsg_rpc_setup",
                                         status,
                                         "Failed to register MQCopy handle!");
                }
            }
            if (status >= 0) {
                rpmsg_rpc_state.isSetup = TRUE;
            }
            else {
                for (; i > 0; --i) {
                    MessageQCopy_delete (&rpmsg_rpc_state.mqHandle[i]);
                }
                rpmsg_rpc_state.run = FALSE;
            }
        }
        else {
            rpmsg_rpc_state.run = FALSE;
        }
        pthread_attr_destroy(&thread_attr);
#if !defined(IPC_BUILD_OPTIMIZE)
    }
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */

    GT_0trace (curTrace, GT_LEAVE, "rpmsg_rpc_setup");
    return status;
}


/*!
 *  @brief  Module destroy function.
 *
 *  @sa     rpmsg_rpc_setup
 */
Void
rpmsg_rpc_destroy (Void)
{
    rpmsg_rpc_EventPacket * packet;
    UInt32                  i;
    List_Handle             bufList;
    rpmsg_rpc_object      * rpc = NULL;
    WaitingReaders_t      * wr = NULL;
    struct _msg_info        info;

    GT_0trace (curTrace, GT_ENTER, "rpmsg_rpc_destroy");

    for (i = 0; i < MAX_CONNS; i++) {
        if (rpmsg_rpc_state.objects[i]) {
            rpmsg_rpc_conn_object * obj = rpmsg_rpc_state.objects[i];
            obj->destroy = TRUE;
            _deinit_rpmsg_rpc_device(obj->dev);
            ProcMgr_close(&obj->procH);
            Memory_free(NULL, obj, sizeof(rpmsg_rpc_conn_object));
            rpmsg_rpc_state.objects[i] = NULL;
        }
    }

    for (i = 0 ; i < MAX_PROCESSES ; i++) {
        rpc = NULL;
        if (rpmsg_rpc_state.eventState [i].rpc != NULL) {
            /* This is recovery.  Need to mark rpc structures as invalid */
            rpc = rpmsg_rpc_state.eventState[i].rpc;
            MessageQCopy_delete(&rpc->mq);
            rpc->mq = NULL;
        }
        bufList = rpmsg_rpc_state.eventState [i].bufList;

        rpmsg_rpc_state.eventState [i].bufList = NULL;
        rpmsg_rpc_state.eventState [i].rpc = NULL;
        rpmsg_rpc_state.eventState [i].refCount = 0;
        if (bufList != NULL) {
            /* Dequeue waiting readers and reply to them */
            pthread_mutex_lock(&rpmsg_rpc_state.lock);
            while ((wr = dequeue_waiting_reader(i)) != NULL) {
                /* Check if rcvid is still valid */
                if (MsgInfo(wr->rcvid, &info) != -1) {
                    put_wr(wr);
                    pthread_mutex_unlock(&rpmsg_rpc_state.lock);
                    MsgError(wr->rcvid, EINTR);
                    pthread_mutex_lock(&rpmsg_rpc_state.lock);
                }
            }
            /* Check for pending ionotify/select calls */
            if (rpc) {
                if (IOFUNC_NOTIFY_INPUT_CHECK(rpc->notify, 1, 0)) {
                    iofunc_notify_trigger(rpc->notify, 1, IOFUNC_NOTIFY_INPUT);
                }
            }
            pthread_mutex_unlock(&rpmsg_rpc_state.lock);

            /* Free event packets for any received but unprocessed events. */
            while (List_empty (bufList) != TRUE){
                packet = (rpmsg_rpc_EventPacket *)
                              List_get (bufList);
                if (packet != NULL){
                    Memory_free (NULL, packet, sizeof(*packet));
                }
            }
            List_delete (&(bufList));
        }
    }

    /* Free the cached list */
    flush_uBuf();

    if (rpmsg_rpc_state.sem) {
        OsalSemaphore_delete(&rpmsg_rpc_state.sem);
    }

    for (i = 0; i < NUM_RPMSG_RPC_QUEUES; i++) {
        if (rpmsg_rpc_state.mqHandle[i]) {
            //MessageQCopy_unregisterNotify();
            MessageQCopy_delete(&rpmsg_rpc_state.mqHandle[i]);
        }
    }

    if (rpmsg_rpc_state.gateHandle != NULL) {
        GateSpinlock_delete ((GateSpinlock_Handle *)
                                       &(rpmsg_rpc_state.gateHandle));
    }

    rpmsg_rpc_state.isSetup = FALSE ;
    rpmsg_rpc_state.run = FALSE;
    // run through and destroy the thread, and all outstanding
    // rpc structures
    pthread_mutex_lock(&rpmsg_rpc_state.lock);
    pthread_cond_signal(&rpmsg_rpc_state.cond);
    pthread_mutex_unlock(&rpmsg_rpc_state.lock);
    pthread_join(rpmsg_rpc_state.nt, NULL);
    pthread_mutex_lock(&rpmsg_rpc_state.lock);
    while (rpmsg_rpc_state.head != NULL) {
        int index;
        WaitingReaders_t *item;
        index = dequeue_notify_list_item(rpmsg_rpc_state.head);
        if (index < 0)
            break;
        item = dequeue_waiting_reader(index);
        while (item) {
            put_wr(item);
            item = dequeue_waiting_reader(index);
        }
    }
    rpmsg_rpc_state.head = NULL ;
    rpmsg_rpc_state.tail = NULL ;
    pthread_mutex_unlock(&rpmsg_rpc_state.lock);

    GT_0trace (curTrace, GT_LEAVE, "_rpmsgDrv_destroy");
}
