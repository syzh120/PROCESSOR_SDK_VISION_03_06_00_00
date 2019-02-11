/*
 *  @file       ti-ipc.c
 *
 *  @brief      fileops handler for ti-ipc component.
 *
 *
 *  @ver
 *
 *  ============================================================================
 *
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
 *  Contact information for paper mail:
 *  Texas Instruments
 *  Post Office Box 655303
 *  Dallas, Texas 75265
 *  Contact information:
 *  http://www-k.ext.ti.com/sc/technical-support/product-information-centers.htm?
 *  DCMP=TIHomeTracking&HQS=Other+OT+home_d_contact
 *  ============================================================================
 *
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
#include <devctl.h>

/* Module headers */
#include <ti/ipc/ti_ipc.h>
#include <ti/ipc/MessageQCopy.h>
#include <_MessageQCopy.h>
#include <_MessageQCopyDefs.h>
#include "OsalSemaphore.h"
#include "std_qnx.h"
#include <pthread.h>

#include "ti-ipc.h"

#define PRIORITY_REALTIME_LOW 29

/* Rate (in us) at which to check if setup is completed during recovery */
#define RECOVERY_POLL_RATE    100000

#define TIIPC_DEVICE_NAME "/dev/tiipc"


/* structure to hold rpmsg-rpc device information */
typedef struct named_device {
    iofunc_mount_t      mattr;
    iofunc_attr_t       cattr;
    int                 resmgr_id;
    iofunc_funcs_t      mfuncs;
    resmgr_connect_funcs_t  cfuncs;
    resmgr_io_funcs_t   iofuncs;
} named_device_t;

/* ti-ipc device structure */
typedef struct ti_ipc_dev {
    dispatch_t       * dpp;
    thread_pool_t    * tpool;
    named_device_t     ti_ipc;
} ti_ipc_dev_t;

/*!
 *  @brief  ti ipc instance object
 */
typedef struct ti_ipc_object_tag {
    MessageQCopy_Handle     mq;
    UInt32                  addr;
    UInt32                  remoteAddr;
    UInt16                  procId;
    pid_t                   pid;
    bool                    isValid;
    iofunc_notify_t         notify[3];
} ti_ipc_object;

/*!
 *  @brief  Keeps the information related to Event.
 */
typedef struct ipc_EventState_tag {
    List_Handle            bufList;
    /*!< Head of received event list. */
    ti_ipc_object         *ipc;
    /*!< ipc instacne. */
    UInt32                 refCount;
    /*!< Reference count, used when multiple Notify_registerEvent are called
         from same process space (multi threads/processes). */
    WaitingReaders_t *     head;
    /*!< Waiting readers head. */
    WaitingReaders_t *     tail;
    /*!< Waiting readers tail. */
} ipc_EventState;

/*!
 *  @brief  Per-connection information
 */
typedef struct ti_ipc_ocb {
    iofunc_ocb_t      hdr;
    pid_t             pid;
    ti_ipc_object *   ipc;
} ti_ipc_ocb_t;

/*!
 *  @brief  ti_ipc Module state object
 */
typedef struct ti_ipc_ModuleObject_tag {
    Bool                 isSetup;
    /*!< Indicates whether the module has been already setup */
    IGateProvider_Handle gateHandle;
    /*!< Handle of gate to be used for local thread safety */
    ipc_EventState eventState [MAX_PROCESSES];
    /*!< List for all user processes registered. */
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
    ti_ipc_dev_t *dev;
    /*!< device for this module */
} ti_ipc_ModuleObject;

/*!
 *  @brief  Structure of Event Packet read from notify kernel-side.
 */
typedef struct ipc_EventPacket_tag {
    List_Elem          element;
    /*!< List element header */
    UInt32             pid;
    /* Processor identifier */
    ti_ipc_object *    obj;
    /*!< Pointer to the channel associated with this callback */
    UInt32             len;
    /*!< Length of the data associated with event. */
    UInt8              data[MessageQCopy_BUFSIZE];
    /*!< Data associated with event. */
    UInt32             src;
    /*!< Src endpoint associated with event. */
    struct ipc_EventPacket * next;
    struct ipc_EventPacket * prev;
} ipc_EventPacket ;


/** ============================================================================
 *  Globals
 *  ============================================================================
 */
/*!
 *  @var    ti_ipc_state
 *
 *  @brief  ti-ipc state object variable
 */
static ti_ipc_ModuleObject ti_ipc_state =
{
    .gateHandle = NULL,
    .isSetup = FALSE,
    .nt = 0,
    .lock = PTHREAD_MUTEX_INITIALIZER,
    .cond = PTHREAD_COND_INITIALIZER,
    .head = NULL,
    .tail = NULL,
    .run  = 0,
    .dev  = NULL
};

static MsgList_t *nl_cache;
static int num_nl = 0;
static WaitingReaders_t *wr_cache;
static int num_wr = 0;

extern dispatch_t * ipc_dpp;


/** ============================================================================
 *  Internal functions
 *  ============================================================================
 */

/*
 * Instead of constantly allocating and freeing the uBuf structures
 * we just cache a few of them, and recycle them instead.
 * The cache count is set with CACHE_NUM in rpmsg-omxdrv.h.
 */
static ipc_EventPacket *uBuf_cache;
static int num_uBuf = 0;

static void flush_uBuf()
{
    ipc_EventPacket *uBuf = NULL;

    while(uBuf_cache) {
        num_uBuf--;
        uBuf = uBuf_cache;
        uBuf_cache = (ipc_EventPacket *)uBuf_cache->next;
        Memory_free(NULL, uBuf, sizeof(*uBuf));
    }
}

static ipc_EventPacket *get_uBuf()
{
    ipc_EventPacket *uBuf;
    uBuf = uBuf_cache;
    if (uBuf != NULL) {
        uBuf_cache = (ipc_EventPacket *)uBuf_cache->next;
        num_uBuf--;
    } else {
        uBuf = Memory_alloc(NULL, sizeof(ipc_EventPacket), 0, NULL);
    }
    return(uBuf);
}

static void put_uBuf(ipc_EventPacket * uBuf)
{
    if (num_uBuf >= CACHE_NUM) {
        Memory_free(NULL, uBuf, sizeof(*uBuf));
    } else {
        uBuf->next = (struct ipc_EventPacket *)uBuf_cache;
        uBuf_cache = uBuf;
        num_uBuf++;
    }
    return;
}

/*
 * Instead of constantly allocating and freeing the notifier structures
 * we just cache a few of them, and recycle them instead.
 * The cache count is set with CACHE_NUM in ti-ipc.h.
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
/* The following functions are used for list/waiting reader management */
static MsgList_t *find_nl(int index)
{
    MsgList_t *item=NULL;
    item = ti_ipc_state.head;
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
        if (ti_ipc_state.head == NULL) {
            ti_ipc_state.head = item;
            ti_ipc_state.tail = item;
            item->prev = NULL;
        }
        else {
            item->prev = ti_ipc_state.tail;
            ti_ipc_state.tail->next = item;
            ti_ipc_state.tail = item;
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
    if (ti_ipc_state.head == item) {
        // removing head
        ti_ipc_state.head = item->next;
        if (ti_ipc_state.head != NULL) {
            ti_ipc_state.head->prev = NULL;
        }
        else {
            // removing head and tail
            ti_ipc_state.tail = NULL;
        }
    }
    else {
        item->prev->next = item->next;
        if (item->next != NULL) {
            item->next->prev = item->prev;
        }
        else {
            // removing tail
            ti_ipc_state.tail = item->prev;
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
    if (ti_ipc_state.eventState [index].head == NULL) {
        ti_ipc_state.eventState [index].head = item;
        ti_ipc_state.eventState [index].tail = item;
    }
    else {
        ti_ipc_state.eventState [index].tail->next = item;
        ti_ipc_state.eventState [index].tail = item;
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
    if (ti_ipc_state.eventState [index].head) {
        item = ti_ipc_state.eventState [index].head;
        ti_ipc_state.eventState [index].head =
                                     ti_ipc_state.eventState [index].head->next;
        if (ti_ipc_state.eventState [index].head == NULL) {
            ti_ipc_state.eventState [index].tail = NULL;
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
    if (ti_ipc_state.eventState [index].head) {
        item = ti_ipc_state.eventState [index].head;
        while (item) {
            if (item->rcvid == rcvid) {
                /* remove item from list */
                if (prev)
                    prev->next = item->next;
                if (item == ti_ipc_state.eventState [index].head)
                    ti_ipc_state.eventState [index].head = item->next;
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
    if (ti_ipc_state.head == NULL) {
        return(0);
    }
    temp = ti_ipc_state.head;
    while (temp) {
        if (ti_ipc_state.eventState [temp->index].head) {
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
    ipc_EventPacket * uBuf     = NULL;

    uBuf = (ipc_EventPacket *) List_get (ti_ipc_state.eventState [index].bufList);

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
    pthread_mutex_lock(&ti_ipc_state.lock);
    while (ti_ipc_state.run) {
        status = find_available_reader_and_event(&index, &item);
        if ( (status == 0) || (item == NULL) ) {
            status = pthread_cond_wait(&ti_ipc_state.cond, &ti_ipc_state.lock);
            if ((status != EOK) && (status != EINTR)) {
                // false wakeup
                break;
            }
            status = find_available_reader_and_event(&index, &item);
            if ( (status == 0) || (item == NULL) ) {
                continue;
            }
        }
        pthread_mutex_unlock(&ti_ipc_state.lock);
        // we have unlocked, and now we have an event to deliver
        // we deliver one event at a time, relock, check and continue
        deliver_notification(index, item->rcvid);
        pthread_mutex_lock(&ti_ipc_state.lock);
        put_wr(item);
    }
    pthread_mutex_unlock(&ti_ipc_state.lock);
    return(NULL);
}


/*!
 *  @brief      Attach a process to ti-ipc user support framework.
 *
 *  @param      obj    TI IPC instance
 *
 *  @sa         _ti_ipc_detach
 */
static
Int
_ti_ipc_attach (ti_ipc_object * obj)
{
    Int32                status   = EOK;
    Bool                 flag     = FALSE;
    Bool                 isInit   = FALSE;
    List_Object *        bufList  = NULL;
    IArg                 key      = 0;
    List_Params          listparams;
    UInt32               i;

    GT_1trace (curTrace, GT_ENTER, "_ti_ipc_attach", obj);

    key = IGateProvider_enter (ti_ipc_state.gateHandle);
    for (i = 0 ; (i < MAX_PROCESSES) ; i++) {
        if (ti_ipc_state.eventState [i].ipc == obj) {
            ti_ipc_state.eventState [i].refCount++;
            isInit = TRUE;
            status = EOK;
            break;
        }
    }

    if (isInit == FALSE) {
        List_Params_init (&listparams);
        bufList = List_create (&listparams) ;
        /* Search for an available slot for user process. */
        for (i = 0 ; i < MAX_PROCESSES ; i++) {
            if (ti_ipc_state.eventState [i].ipc == NULL) {
                ti_ipc_state.eventState [i].ipc = obj;
                ti_ipc_state.eventState [i].refCount = 1;
                ti_ipc_state.eventState [i].bufList = bufList;
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
                              "_ti_ipc_attach",
                              status,
                              "Maximum number of supported user"
                                  " clients have already been "
                                  "registered.");
            if (bufList != NULL) {
                List_delete (&bufList);
            }
        }
    }
    IGateProvider_leave (ti_ipc_state.gateHandle, key);

    GT_1trace (curTrace, GT_LEAVE, "_ti_ipc_attach", status);

    /*! @retval Notify_S_SUCCESS Operation successfully completed. */
    return status ;
}


 /*!
 *  @brief      This function adds a data to a registered process.
 *
 *  @param      obj       Instance object associated with the client
 *  @param      src       Source address (endpoint) sending the data
 *  @param      pid       Process ID associated with the client
 *  @param      data      Data to be added
 *  @param      len       Length of data to be added
 *
 *  @sa
 */
Int
_ti_ipc_addBufByPid (ti_ipc_object *  obj,
                     UInt32           src,
                     UInt32           pid,
                     void *           data,
                     UInt32           len)
{
    Int32                   status = EOK;
    Bool                    flag   = FALSE;
    ipc_EventPacket *  uBuf   = NULL;
    IArg                    key;
    UInt32                  i;
    WaitingReaders_t *item;
    MsgList_t *msgItem;

    GT_assert (curTrace, (ti_ipc_state.isSetup == TRUE));

    key = IGateProvider_enter (ti_ipc_state.gateHandle);
    /* Find the registration for this callback */
    for (i = 0 ; i < MAX_PROCESSES ; i++) {
        if (ti_ipc_state.eventState [i].ipc == obj) {
            flag = TRUE;
            break;
        }
    }
    IGateProvider_leave (ti_ipc_state.gateHandle, key);

#if !defined(IPC_BUILD_OPTIMIZE)
    if (flag != TRUE) {
        /*! @retval ENOMEM Could not find a registered handler
                                      for this process. */
        status = -ENOMEM;
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "_ti_ipc_addBufByPid",
                             status,
                             "Could not find a registered handler "
                             "for this process.!");
    }
    else {
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */
        /* Allocate memory for the buf */
        pthread_mutex_lock(&ti_ipc_state.lock);
        uBuf = get_uBuf();
        pthread_mutex_unlock(&ti_ipc_state.lock);

#if !defined(IPC_BUILD_OPTIMIZE)
        if (uBuf == NULL) {
            /*! @retval Notify_E_MEMORY Failed to allocate memory for event
                                packet for received callback. */
            status = -ENOMEM;
            GT_setFailureReason (curTrace,
                                 GT_4CLASS,
                                 "_ti_ipc_addBufByPid",
                                 status,
                                 "Failed to allocate memory for event"
                                 " packet for received callback.!");
        }
        else {
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */
            List_elemClear (&(uBuf->element));
            GT_assert (curTrace,
                       (ti_ipc_state.eventState [i].bufList != NULL));

            if (data) {
                Memory_copy(uBuf->data, data, len);
            }
            uBuf->len = len;

            List_put (ti_ipc_state.eventState [i].bufList,
                      &(uBuf->element));
            pthread_mutex_lock(&ti_ipc_state.lock);
            item = dequeue_waiting_reader(i);
            if (item) {
                // there is a waiting reader
                deliver_notification(i, item->rcvid);
                put_wr(item);
                pthread_mutex_unlock(&ti_ipc_state.lock);
                status = EOK;
            }
            else {
                if (enqueue_notify_list(i) < 0) {
                    pthread_mutex_unlock(&ti_ipc_state.lock);
                    status = -ENOMEM;
                    GT_setFailureReason (curTrace,
                                  GT_4CLASS,
                                  "_ti_ipc_addBufByPid",
                                  status,
                                  "Failed to allocate memory for notifier");
                }
                else {
                    msgItem = find_nl(i);
                    /* TODO: obj could be NULL in some cases  */
                    if (obj && msgItem) {
                        if (IOFUNC_NOTIFY_INPUT_CHECK(obj->notify,
                                                      msgItem->num_events, 0)) {
                            iofunc_notify_trigger(obj->notify,
                                                  msgItem->num_events,
                                                  IOFUNC_NOTIFY_INPUT);
                        }
                    }
                    status = EOK;
                    pthread_cond_signal(&ti_ipc_state.cond);
                    pthread_mutex_unlock(&ti_ipc_state.lock);
                }
            }
#if !defined(IPC_BUILD_OPTIMIZE)
        }
    }
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */

    GT_1trace (curTrace, GT_LEAVE, "_ti_ipc_addBufByPid", status);

    return status;
}


/*!
 *  @brief      This function implements the callback registered with
 *              MessageQCopy_create for each client.  This function
 *              adds the message from the remote proc to a list
 *              where it is routed to the appropriate waiting reader.
 *
 *  @param      handle    Destinatino MessageQCopy_Handle instance for the msg
 *  @param      data      Message buffer
 *  @param      len       Length of the message data
 *  @param      priv      Private information given when callback was registered
 *  @param      src       Source address of the message
 *  @param      srcProc   Source proc of the message
 *
 *  @sa
 */
Void
_ti_ipc_cb (MessageQCopy_Handle handle, void * data, int len, void * priv,
            UInt32 src, UInt16 srcProc)
{
#if !defined(IPC_BUILD_OPTIMIZE)
    Int32                   status = 0;
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */
    ti_ipc_object * obj = NULL;

    if (ti_ipc_state.isSetup == FALSE) {
        /* If module is not setup (e.g. in recovery), drop the received msg */
        GT_0trace(curTrace, GT_3CLASS,
            "_ti_ipc_cb: Module not setup. Dropping incoming msg.");
        return;
    }

    obj = (ti_ipc_object *) priv;

#if !defined(IPC_BUILD_OPTIMIZE)
    status =
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */
             _ti_ipc_addBufByPid (obj,
                                  src,
                                  obj->pid,
                                  data,
                                  len);
#if !defined(IPC_BUILD_OPTIMIZE)
    if (status < 0) {
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "_ti_ipc_cb",
                             status,
                             "Failed to add callback packet for pid");
    }
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */
}

 /**
  * Handler for ocb_calloc() requests.
  *
  * Special handler for ocb_calloc() requests that we export for control.  An
  * open request from the client will result in a call to our special ocb_calloc
  * handler.  This function allocates client-specific information.
  *
  * \param ctp       Thread's associated context information.
  * \param device    Device attributes structure.
  *
  * \return Pointer to an iofunc_ocb_t OCB structure.
  */

IOFUNC_OCB_T *
ti_ipc_ocb_calloc (resmgr_context_t * ctp, IOFUNC_ATTR_T * device)
{
    ti_ipc_ocb_t * ocb = NULL;
    ti_ipc_object * obj = NULL;

    /* Wait for module to be setup during recovery */
    while (ti_ipc_state.isSetup == FALSE) {
        usleep(RECOVERY_POLL_RATE);
    }

    /* Allocate the OCB */
    ocb = (ti_ipc_ocb_t *) calloc (1, sizeof (ti_ipc_ocb_t));
    if (ocb == NULL){
        errno = ENOMEM;
        return (NULL);
    }

    ocb->pid = ctp->info.pid;

    /* Allocate memory for the rpmsg object. */
    obj = Memory_calloc (NULL, sizeof (ti_ipc_object), 0u, NULL);
    if (obj == NULL) {
        errno = ENOMEM;
        free(ocb);
        return (NULL);
    }
    else if (_ti_ipc_attach(obj) < 0) {
        errno = ENOMEM;
        Memory_free(NULL, obj, sizeof(ti_ipc_object));
        free(ocb);
        return (NULL);
    }
    else {
        ocb->ipc = obj;
        IOFUNC_NOTIFY_INIT(obj->notify);
        obj->addr = MessageQCopy_ADDRANY;
        obj->remoteAddr = MessageQCopy_ADDRANY;
        obj->procId = MultiProc_INVALIDID;
        obj->mq = NULL;
        obj->isValid = TRUE;
    }

    return (IOFUNC_OCB_T *)(ocb);
}


/*!
 *  @brief      Detach a process from ti-ipc user support framework.
 *
 *  @param      obj    TI IPC instance
 *  @param      force  Tells if detach should be forced even if conditions
 *                     are not met.
 *
 *  @sa         _ti_ipc_attach
 */
static
Int
_ti_ipc_detach (ti_ipc_object * obj, Bool force)
{
    Int32                status    = EOK;
    Int32                tmpStatus = EOK;
    Bool                 flag      = FALSE;
    List_Object *        bufList   = NULL;
    UInt32               i;
    IArg                 key;
    MsgList_t          * item;
    WaitingReaders_t   * wr        = NULL;
    struct _msg_info     info;

    GT_1trace (curTrace, GT_ENTER, "_ti_ipc_detach", obj);

    key = IGateProvider_enter (ti_ipc_state.gateHandle);

    for (i = 0 ; i < MAX_PROCESSES ; i++) {
        if (ti_ipc_state.eventState [i].ipc == obj) {
            if (ti_ipc_state.eventState [i].refCount == 1) {
                ti_ipc_state.eventState [i].refCount = 0;

                flag = TRUE;
                break;
            }
            else {
                ti_ipc_state.eventState [i].refCount--;
                status = EOK;
                break;
            }
        }
    }
    IGateProvider_leave (ti_ipc_state.gateHandle, key);

    if (flag == TRUE) {
        key = IGateProvider_enter (ti_ipc_state.gateHandle);
        /* Last client being unregistered for this process. */
        ti_ipc_state.eventState [i].ipc = NULL;

        /* Store in local variable to delete outside lock. */
        bufList = ti_ipc_state.eventState [i].bufList;

        ti_ipc_state.eventState [i].bufList = NULL;

        IGateProvider_leave (ti_ipc_state.gateHandle, key);
    }

    if (flag != TRUE) {
#if !defined(IPC_BUILD_OPTIMIZE)
        if (i == MAX_PROCESSES) {
            /*! @retval Notify_E_NOTFOUND The specified user process was
                     not found registered with Notify Driver module. */
            status = -ENOMEM;
            GT_setFailureReason (curTrace,
                              GT_4CLASS,
                              "_ti_ipc_detach",
                              status,
                              "The specified user process was not found"
                              " registered with rpmsg Driver module.");
        }
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */
    }
    else {
        if (bufList != NULL) {
            /* Dequeue waiting readers and reply to them */
            pthread_mutex_lock(&ti_ipc_state.lock);
            while ((wr = dequeue_waiting_reader(i)) != NULL) {
                /* Check if rcvid is still valid */
                if (MsgInfo(wr->rcvid, &info) != -1) {
                    put_wr(wr);
                    pthread_mutex_unlock(&ti_ipc_state.lock);
                    MsgError(wr->rcvid, EINTR);
                    pthread_mutex_lock(&ti_ipc_state.lock);
                }
            }
            /* Check for pending ionotify/select calls */
            if (obj) {
                if (IOFUNC_NOTIFY_INPUT_CHECK(obj->notify, 1, 0)) {
                    iofunc_notify_trigger(obj->notify, 1, IOFUNC_NOTIFY_INPUT);
                }
            }

            /* Free event packets for any received but unprocessed events. */
            while ((item = find_nl(i)) != NULL) {
                if (dequeue_notify_list_item(item) >= 0) {
                    ipc_EventPacket * uBuf = NULL;

                    uBuf = (ipc_EventPacket *) List_get (bufList);

                    /*  Let the check remain at run-time. */
                    if (uBuf != NULL) {
                        put_uBuf(uBuf);
                    }
                }
            }
            pthread_mutex_unlock(&ti_ipc_state.lock);

            /* Last client being unregistered with Notify module. */
            List_delete (&bufList);
        }

#if !defined(IPC_BUILD_OPTIMIZE)
        if ((tmpStatus < 0) && (status >= 0)) {
            status =  tmpStatus;
            GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "_ti_ipc_detach",
                             status,
                             "Failed to delete termination semaphore!");
        }
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */
    }

    GT_1trace (curTrace, GT_LEAVE, "_ti_ipc_detach", status);

    /*! @retval Notify_S_SUCCESS Operation successfully completed */
    return status;
}

 /**
  * Handler for ocb_free() requests.
  *
  * Special handler for ocb_free() requests that we export for control.  A
  * close request from the client will result in a call to our special ocb_free
  * handler.  This function frees any client-specific information that was
  * allocated.
  *
  * \param i_ocb     OCB associated with client's session.
  *
  * \return POSIX errno value.
  *
  * \retval None.
  */

void
ti_ipc_ocb_free (IOFUNC_OCB_T * i_ocb)
{
    ti_ipc_ocb_t * ocb = (ti_ipc_ocb_t *)i_ocb;
    ti_ipc_object * obj;

    if (ocb) {
        if (ocb->ipc) {
            pthread_mutex_lock(&ti_ipc_state.lock);
            obj = ocb->ipc;
            /* TBD: Notification to remote core of endpoint closure? */
            if (obj->mq) {
                /* Only delete mq if recovery did not do so */
                MessageQCopy_delete (&obj->mq);
                obj->mq = NULL;
            }

            /*
             * If recovery happened and connection is no longer valid,
             * ti_ipc_destroy would have already performed detach. So only
             * need to detach if it is still valid
             */
            if (obj->isValid) {
                pthread_mutex_unlock(&ti_ipc_state.lock);
                _ti_ipc_detach(ocb->ipc, FALSE);
            }
            else {
                pthread_mutex_unlock(&ti_ipc_state.lock);
            }

            Memory_free (NULL, obj, sizeof(ti_ipc_object));
        }
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
ti_ipc_close_ocb (resmgr_context_t *ctp, void *reserved, RESMGR_OCB_T *ocb)
{
    ti_ipc_ocb_t * ipc_ocb = (ti_ipc_ocb_t *)ocb;
    iofunc_notify_remove(ctp, ipc_ocb->ipc->notify);
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

int
ti_ipc_read(resmgr_context_t *ctp, io_read_t *msg, RESMGR_OCB_T *i_ocb)
{
    Int status;
    Bool                    flag     = FALSE;
    Int                  retVal   = EOK;
    UInt32                  i;
    MsgList_t          * item;
    Int                  nonblock;
    ti_ipc_ocb_t * ocb = (ti_ipc_ocb_t *)i_ocb;
    ti_ipc_object * obj = ocb->ipc;

    if ((status = iofunc_read_verify(ctp, msg, i_ocb, &nonblock)) != EOK)
        return (status);

    pthread_mutex_lock(&ti_ipc_state.lock);

    if (!obj->isValid) {
        pthread_mutex_unlock(&ti_ipc_state.lock);
        /* this connection was shutdown due to recovery */
        return ESHUTDOWN;
    }

    if (obj->addr == MessageQCopy_ADDRANY) {
        pthread_mutex_unlock(&ti_ipc_state.lock);
        return ENOTCONN;
    }

    for (i = 0 ; i < MAX_PROCESSES ; i++) {
        if (ti_ipc_state.eventState [i].ipc == obj) {
            flag = TRUE;
            break;
        }
    }

    /* Let the check remain at run-time. */
    if (flag == TRUE) {
        /* Let the check remain at run-time for handling any run-time
        * race conditions.
        */
        if (ti_ipc_state.eventState [i].bufList != NULL) {
            item = find_nl(i);
            if (dequeue_notify_list_item(item) < 0) {
                if (nonblock) {
                    pthread_mutex_unlock(&ti_ipc_state.lock);
                    return EAGAIN;
                }
                else {
                    retVal = enqueue_waiting_reader(i, ctp->rcvid);
                    if (retVal == EOK) {
                        pthread_cond_signal(&ti_ipc_state.cond);
                        pthread_mutex_unlock(&ti_ipc_state.lock);
                        return(_RESMGR_NOREPLY);
                    }
                    retVal = ENOMEM;
                }
            }
            else {
                deliver_notification(i, ctp->rcvid);
                pthread_mutex_unlock(&ti_ipc_state.lock);
                return(_RESMGR_NOREPLY);
            }
        }
    }

    pthread_mutex_unlock(&ti_ipc_state.lock);

    /*! @retval Number-of-bytes-read Number of bytes read. */
    return retVal;
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
  * \retval ENOTCONN Remote address has not been set.
  * \retval ENOMEM   Not enough memory to perform the write.
  * \retval EIO      MessageQCopy_send failed.
  * \retval EINVAL   msg->i.bytes is negative.
  */

int
ti_ipc_write(resmgr_context_t *ctp, io_write_t *msg, RESMGR_OCB_T *io_ocb)
{
    int status;
    char buf[MessageQCopy_BUFSIZE];
    int bytes;
    ti_ipc_ocb_t * ocb = (ti_ipc_ocb_t *)io_ocb;
    ti_ipc_object * obj = ocb->ipc;

    if ((status = iofunc_write_verify(ctp, msg, io_ocb, NULL)) != EOK) {
        return (status);
    }

    pthread_mutex_lock(&ti_ipc_state.lock);

    if (!obj->isValid) {
        pthread_mutex_unlock(&ti_ipc_state.lock);
        /* this connection was shutdown due to recovery */
        return ESHUTDOWN;
    }

    if (obj->remoteAddr == MessageQCopy_ADDRANY) {
        pthread_mutex_unlock(&ti_ipc_state.lock);
        return ENOTCONN;
    }

    bytes = ((int64_t) msg->i.nbytes) > MessageQCopy_BUFSIZE ?
            MessageQCopy_BUFSIZE : msg->i.nbytes;
    if (bytes < 0) {
        pthread_mutex_unlock(&ti_ipc_state.lock);
        return EINVAL;
    }
    _IO_SET_WRITE_NBYTES (ctp, bytes);

    status = resmgr_msgread(ctp, buf, bytes, sizeof(msg->i));
    if (status != bytes) {
        pthread_mutex_unlock(&ti_ipc_state.lock);
        return (errno);
    }

    status = MessageQCopy_send(obj->procId, MultiProc_self(), obj->remoteAddr,
                                   obj->addr, buf, bytes, TRUE);

    pthread_mutex_unlock(&ti_ipc_state.lock);

    if (status < 0) {
        return (EIO);
    }

    return(EOK);
}

 /**
  * Handler for TIIPC_IOCSETLOCAL requests.
  *
  * Handles TIIPC_IOCSETLOCAL requests to set the local endpoint address.
  *
  * \param ctp     Thread's associated context information.
  * \param msg     The actual devctl() message.
  * \param io_ocb  OCB associated with client's session.
  *
  * \return POSIX errno value.
  *
  * \retval EOK      Success.
  * \retval EISCONN  Local address is already set.
  * \retval ENOMEM   Not enough memory to create the endpoint.
  * \retval EINVAL   ctp->info.msglen or ctp->info.dstmsglen is not big enough.
  */
static
Int
_ti_ipc_set_local(resmgr_context_t *ctp, io_devctl_t *msg, ti_ipc_ocb_t *ocb)
{
    Int status = EOK;
    tiipc_local_params * cargs = (tiipc_local_params *)(_DEVCTL_DATA (msg->i));
    tiipc_local_params * out = (tiipc_local_params *)(_DEVCTL_DATA (msg->o));
    ti_ipc_object * obj = ocb->ipc;

    if ((ctp->info.msglen - sizeof(msg->i) < sizeof(tiipc_local_params)) ||
        (ctp->info.dstmsglen - sizeof(msg->o) < sizeof (tiipc_local_params))) {
        status = (EINVAL);
    }
    else if (obj->mq) {
        /* already a local endpoint associated with this instance */
        status = (EISCONN);
    }
    else {
        if (cargs->local_addr == TIIPC_ADDRANY) {
            cargs->local_addr = MessageQCopy_ADDRANY;
        }
        /* Create the local endpoint based on the request */
        obj->mq = MessageQCopy_create (cargs->local_addr, NULL, _ti_ipc_cb,
                                       obj, &obj->addr);
        if (obj->mq == NULL) {
            status = (ENOMEM);
        }
        else {
            out->local_addr = obj->addr;
            msg->o.ret_val = EOK;
            status = (_RESMGR_PTR(ctp, &msg->o, sizeof(msg->o) +\
                                  sizeof(tiipc_local_params)));
        }
    }

    return status;
}

 /**
  * Handler for TIIPC_IOCGETLOCAL requests.
  *
  * Handles TIIPC_IOCGETLOCAL requests to get the local endpoint address info.
  *
  * \param ctp     Thread's associated context information.
  * \param msg     The actual devctl() message.
  * \param io_ocb  OCB associated with client's session.
  *
  * \return POSIX errno value.
  *
  * \retval EOK      Success.
  * \retval EINVAL   ctp->info.dstmsglen is not big enough.
  */
static
Int
_ti_ipc_get_local(resmgr_context_t *ctp, io_devctl_t *msg, ti_ipc_ocb_t *ocb)
{
    Int status = EOK;
    tiipc_local_params * out = (tiipc_local_params *)(_DEVCTL_DATA (msg->o));
    ti_ipc_object * obj = ocb->ipc;

    if (ctp->info.dstmsglen - sizeof(msg->o) < sizeof (tiipc_local_params)) {
        status = (EINVAL);
    }
    else {
        if (obj->addr == MessageQCopy_ADDRANY)
            out->local_addr = TIIPC_ADDRANY;
        else
            out->local_addr = obj->addr;
        msg->o.ret_val = EOK;
        status = (_RESMGR_PTR(ctp, &msg->o, sizeof(msg->o) +\
                              sizeof(tiipc_local_params)));
    }

    return status;
}

 /**
  * Handler for TIIPC_IOCSETREMOTE requests.
  *
  * Handles TIIPC_IOCSETREMOTE requests to set the remote endpoint address and
  * proc ID used for write() commands.
  *
  * \param ctp     Thread's associated context information.
  * \param msg     The actual devctl() message.
  * \param io_ocb  OCB associated with client's session.
  *
  * \return POSIX errno value.
  *
  * \retval EOK      Success.
  * \retval EISCONN  Remote address is already set.
  * \retval ENOMEM   Not enough memory to create the endpoint.
  * \retval EINVAL   ctp->info.msglen or ctp->info.dstmsglen is not big enough
  *                  or the specified remote proc ID is invalid.
  */
static
Int
_ti_ipc_set_remote(resmgr_context_t *ctp, io_devctl_t *msg, ti_ipc_ocb_t *ocb)
{
    Int status = EOK;
    tiipc_remote_params * cargs =
                                 (tiipc_remote_params *)(_DEVCTL_DATA (msg->i));
    ti_ipc_object *obj = ocb->ipc;

    if ((ctp->info.msglen - sizeof(msg->i) < sizeof (tiipc_remote_params)) ||
        (ctp->info.dstmsglen - sizeof(msg->o) < sizeof (tiipc_remote_params))) {
        status = (EINVAL);
    }
    else if (obj->remoteAddr != MessageQCopy_ADDRANY) {
        /* already a remote endpoint associated with this instance */
        status = (EISCONN);
    }
    else if (cargs->remote_proc == MultiProc_self() ||
             cargs->remote_proc >= MultiProc_getNumProcessors()) {
        /* Don't support sending to self and remote proc ID must be valid */
        status = (EINVAL);
    }
    else {
        obj->remoteAddr = cargs->remote_addr;
        obj->procId = cargs->remote_proc;
        msg->o.ret_val = EOK;
        status = (_RESMGR_PTR(ctp, &msg->o, sizeof(msg->o) +\
                              sizeof(tiipc_remote_params)));
    }

    return status;
}

 /**
  * Handler for TIIPC_IOCGETREMOTE requests.
  *
  * Handles TIIPC_IOCGETREMOTE requests to get the remote endpoint address info.
  *
  * \param ctp     Thread's associated context information.
  * \param msg     The actual devctl() message.
  * \param io_ocb  OCB associated with client's session.
  *
  * \return POSIX errno value.
  *
  * \retval EOK      Success.
  * \retval EINVAL   ctp->info.dstmsglen is not big enough.
  */
static
Int
_ti_ipc_get_remote(resmgr_context_t *ctp, io_devctl_t *msg, ti_ipc_ocb_t *ocb)
{
    Int status = EOK;
    tiipc_remote_params * out = (tiipc_remote_params *)(_DEVCTL_DATA (msg->o));
    ti_ipc_object * obj = ocb->ipc;

    if (ctp->info.dstmsglen - sizeof(msg->i) < sizeof (tiipc_remote_params)) {
        status = (EINVAL);
    }
    else {
        if (obj->remoteAddr == MessageQCopy_ADDRANY)
            out->remote_addr = TIIPC_ADDRANY;
        else
            out->remote_addr = obj->remoteAddr;
        out->remote_proc = obj->procId;
        msg->o.ret_val = EOK;
        status = (_RESMGR_PTR(ctp, &msg->o, sizeof(msg->o) +\
                              sizeof(tiipc_remote_params)));
    }

    return status;
}

 /**
  * Handler for devctl() requests.
  *
  * Handles special devctl() requests that we export for control.  A devctl()
  * request will perform different functions depending on the dcmd.
  *
  * \param ctp     Thread's associated context information.
  * \param msg     The actual devctl() message.
  * \param i_ocb   OCB associated with client's session.
  *
  * \return POSIX errno value.
  *
  * \retval EOK      Success.
  * \retval other    Fail.
  */
static
Int
ti_ipc_devctl(resmgr_context_t *ctp, io_devctl_t *msg, IOFUNC_OCB_T *i_ocb)
{
    Int status = 0;
    ti_ipc_ocb_t *ocb = (ti_ipc_ocb_t *)i_ocb;

    if ((status = iofunc_devctl_default(ctp, msg, &ocb->hdr)) != _RESMGR_DEFAULT)
        return(_RESMGR_ERRNO(status));
    status = 0;

    if (!ocb->ipc->isValid) {
        return ESHUTDOWN;
    }

    switch (msg->i.dcmd)
    {
        case TIIPC_IOCSETLOCAL:
            /* Must be called before receiving messages */
            status = _ti_ipc_set_local (ctp, msg, ocb);
            break;
        case TIIPC_IOCGETLOCAL:
            status = _ti_ipc_get_local (ctp, msg, ocb);
            break;
        case TIIPC_IOCSETREMOTE:
            /* Must be called before sending messages */
            status = _ti_ipc_set_remote (ctp, msg, ocb);
            break;
        case TIIPC_IOCGETREMOTE:
            status = _ti_ipc_get_remote (ctp, msg, ocb);
            break;
        default:
            status = (ENOSYS);
            break;
    }

    return status;
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

int
ti_ipc_read_unblock(resmgr_context_t *ctp, io_pulse_t *msg, iofunc_ocb_t *i_ocb)
{
    UInt32                  i;
    Bool                    flag     = FALSE;
    WaitingReaders_t      * wr;
    ti_ipc_ocb_t * ocb = (ti_ipc_ocb_t *)i_ocb;
    ti_ipc_object * obj = ocb->ipc;

    for (i = 0 ; i < MAX_PROCESSES ; i++) {
        if (ti_ipc_state.eventState [i].ipc == obj) {
            flag = TRUE;
            break;
        }
    }

    /*  Let the check remain at run-time. */
    if (flag == TRUE) {
        /* Let the check remain at run-time for handling any run-time
         * race conditions.
         */
        pthread_mutex_lock(&ti_ipc_state.lock);
        if (ti_ipc_state.eventState [i].bufList != NULL) {
            wr = find_waiting_reader(i, ctp->rcvid);
            if (wr) {
                put_wr(wr);
                pthread_mutex_unlock(&ti_ipc_state.lock);
                return (EINTR);
            }
        }
        pthread_mutex_unlock(&ti_ipc_state.lock);
    }

    return _RESMGR_NOREPLY;
}

 /**
  * Handler for unblock() requests.
  *
  * Handles unblock request for the client which is requesting to no longer be
  * blocked on the ti-ipc driver.
  *
  * \param ctp     Thread's associated context information.
  * \param msg     The pulse message.
  * \param ocb     OCB associated with client's session.
  *
  * \return POSIX errno value.
  *
  * \retval EINTR    The rcvid has been unblocked.
  */

int
ti_ipc_unblock(resmgr_context_t *ctp, io_pulse_t *msg, RESMGR_OCB_T *ocb)
{
    int status = _RESMGR_NOREPLY;
    struct _msg_info info;

    /*
     * Try to run the default unblock for this message.
     */
    if ((status = iofunc_unblock_default(ctp,msg, ocb)) != _RESMGR_DEFAULT) {
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

    if (ti_ipc_read_unblock(ctp, msg, ocb) != _RESMGR_NOREPLY) {
           return _RESMGR_ERRNO(EINTR);
    }

    return _RESMGR_ERRNO(EINTR);
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

Int
ti_ipc_notify( resmgr_context_t *ctp, io_notify_t *msg, RESMGR_OCB_T *ocb)
{
    ti_ipc_ocb_t * ipc_ocb = (ti_ipc_ocb_t *)ocb;
    int trig;
    int i = 0;
    Bool flag = FALSE;
    MsgList_t * item = NULL;
    int status = EOK;
    ti_ipc_object * obj = ipc_ocb->ipc;

    trig = _NOTIFY_COND_OUTPUT; /* clients can give us data */

    for (i = 0 ; i < MAX_PROCESSES ; i++) {
        if (ti_ipc_state.eventState [i].ipc == obj) {
            flag = TRUE;
            break;
        }
    }

    pthread_mutex_lock(&ti_ipc_state.lock);
    if (!obj->isValid) {
         /*
          * connection is no longer valid after recovery.
          * unblock all select calls
          */
         trig |= _NOTIFY_COND_INPUT;
    }
    /* Let the check remain at run-time. */
    else if (flag == TRUE) {
        /* Let the check remain at run-time for handling any run-time
        * race conditions.
        */
        if (ti_ipc_state.eventState [i].bufList != NULL) {
            item = find_nl(i);
            if (item && item->num_events > 0) {
                trig |= _NOTIFY_COND_INPUT;
            }
        }
    }
    status = iofunc_notify(ctp, msg, ipc_ocb->ipc->notify, trig, NULL, NULL);
    pthread_mutex_unlock(&ti_ipc_state.lock);
    return status;
}

 /**
  * Initializes and attaches ti-ipc resource manager functions to an
  * ti-ipc device name.
  *
  * \param num     The number to append to the end of the device name.
  *
  * \return Pointer to the created ti_ipc_dev_t device.
  */

static
ti_ipc_dev_t *
_init_device ()
{
    iofunc_attr_t  * attr;
    resmgr_attr_t    resmgr_attr;
    ti_ipc_dev_t *   dev = NULL;

    dev = malloc(sizeof(*dev));
    if (dev == NULL) {
        return NULL;
    }

    memset(&resmgr_attr, 0, sizeof resmgr_attr);
    resmgr_attr.nparts_max = 10;
    resmgr_attr.msg_max_size = 2048;
    memset(&dev->ti_ipc.mattr, 0, sizeof(iofunc_mount_t));
    dev->ti_ipc.mattr.flags = ST_NOSUID | ST_NOEXEC;
    dev->ti_ipc.mattr.conf = IOFUNC_PC_CHOWN_RESTRICTED |
                              IOFUNC_PC_NO_TRUNC |
                              IOFUNC_PC_SYNC_IO;
    dev->ti_ipc.mattr.funcs = &dev->ti_ipc.mfuncs;
    memset(&dev->ti_ipc.mfuncs, 0, sizeof(iofunc_funcs_t));
    dev->ti_ipc.mfuncs.nfuncs = _IOFUNC_NFUNCS;
    dev->ti_ipc.mfuncs.ocb_calloc = ti_ipc_ocb_calloc;
    dev->ti_ipc.mfuncs.ocb_free = ti_ipc_ocb_free;
    iofunc_func_init(_RESMGR_CONNECT_NFUNCS, &dev->ti_ipc.cfuncs,
                     _RESMGR_IO_NFUNCS, &dev->ti_ipc.iofuncs);
    iofunc_attr_init(attr = &dev->ti_ipc.cattr, S_IFCHR | 0777, NULL, NULL);
    dev->ti_ipc.iofuncs.unblock = ti_ipc_unblock;
    dev->ti_ipc.iofuncs.devctl = ti_ipc_devctl;
    dev->ti_ipc.iofuncs.notify = ti_ipc_notify;
    dev->ti_ipc.iofuncs.close_ocb = ti_ipc_close_ocb;
    dev->ti_ipc.iofuncs.read = ti_ipc_read;
    dev->ti_ipc.iofuncs.write = ti_ipc_write;
    attr->mount = &dev->ti_ipc.mattr;
    iofunc_time_update(attr);

    if (-1 == (dev->ti_ipc.resmgr_id =
        resmgr_attach(ipc_dpp, &resmgr_attr,
                      TIIPC_DEVICE_NAME, _FTYPE_ANY, 0,
                      &dev->ti_ipc.cfuncs,
                      &dev->ti_ipc.iofuncs, attr))) {
        free(dev);
        return(NULL);
    }

    return(dev);
}

 /**
  * Detaches an ti-ipc resource manager device name.
  *
  * \param dev     The device to detach.
  *
  * \return POSIX errno value.
  */

static
Void
_deinit_device (ti_ipc_dev_t * dev)
{
    resmgr_detach(ipc_dpp, dev->ti_ipc.resmgr_id, 0);

    free (dev);

    return;
}

/*!
 *  @brief  Module setup function.
 *
 *  @sa     ti_ipc_destroy
 */
Int
ti_ipc_setup (bool recover)
{
    UInt16 i;
    List_Params  listparams;
    Int status = 0;
    Error_Block eb;
    pthread_attr_t thread_attr;
    struct sched_param sched_param;

    GT_0trace (curTrace, GT_ENTER, "ti_ipc_setup");

    Error_init(&eb);

    List_Params_init (&listparams);
    if (!recover) {
        ti_ipc_state.gateHandle = (IGateProvider_Handle)
                     GateSpinlock_create ((GateSpinlock_Handle) NULL, &eb);
#if !defined(IPC_BUILD_OPTIMIZE)
        if (ti_ipc_state.gateHandle == NULL) {
            status = -ENOMEM;
            GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "_ti_ipc_setup",
                             status,
                             "Failed to create spinlock gate!");
            goto exit;
        }
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */
    }

    for (i = 0 ; i < MAX_PROCESSES ; i++) {
        ti_ipc_state.eventState [i].bufList = NULL;
        ti_ipc_state.eventState [i].ipc = NULL;
        ti_ipc_state.eventState [i].refCount = 0;
        ti_ipc_state.eventState [i].head = NULL;
        ti_ipc_state.eventState [i].tail = NULL;
    }

    pthread_attr_init(&thread_attr );
    sched_param.sched_priority = PRIORITY_REALTIME_LOW;
    pthread_attr_setinheritsched(&thread_attr, PTHREAD_EXPLICIT_SCHED);
    pthread_attr_setschedpolicy(&thread_attr, SCHED_RR);
    pthread_attr_setschedparam(&thread_attr, &sched_param);

    ti_ipc_state.run = TRUE;
    if (pthread_create(&ti_ipc_state.nt,
                       &thread_attr, notifier_thread, NULL) == EOK) {
        pthread_setname_np(ti_ipc_state.nt, "tiipc-notifier");
        /* create a /dev/tiipc instance for users to open */
        if (!ti_ipc_state.dev)
            ti_ipc_state.dev = _init_device();
        if (ti_ipc_state.dev == NULL) {
            Osal_printf("Failed to create tiipc");
            ti_ipc_state.run = FALSE;
        }
        else {
            ti_ipc_state.isSetup = TRUE;
        }
    }
    else {
        ti_ipc_state.run = FALSE;
    }
    pthread_attr_destroy(&thread_attr);

exit:
    GT_0trace (curTrace, GT_LEAVE, "ti_ipc_setup");
    return status;
}


/*!
 *  @brief  Module destroy function.
 *
 *  @sa     ti_ipc_setup
 */
Void
ti_ipc_destroy (bool recover)
{
    ipc_EventPacket * packet;
    UInt32                  i;
    List_Handle             bufList;
    ti_ipc_object      * obj = NULL;
    WaitingReaders_t      * wr = NULL;
    struct _msg_info        info;

    GT_0trace (curTrace, GT_ENTER, "_ti_ipc_destroy");

    if (!recover) {
        _deinit_device(ti_ipc_state.dev);
        ti_ipc_state.dev = NULL;
    }

    ti_ipc_state.isSetup = FALSE;

    for (i = 0 ; i < MAX_PROCESSES ; i++) {
        pthread_mutex_lock(&ti_ipc_state.lock);
        obj = ti_ipc_state.eventState[i].ipc;
        if (obj != NULL) {
            /* This is recovery.  Need to mark mq structures as invalid */
            obj->isValid = FALSE;
            if (obj->mq) {
                MessageQCopy_delete(&obj->mq);
                obj->mq = NULL;
            }
        }
        bufList = ti_ipc_state.eventState [i].bufList;

        ti_ipc_state.eventState [i].bufList = NULL;
        ti_ipc_state.eventState [i].ipc = NULL;
        ti_ipc_state.eventState [i].refCount = 0;
        if (bufList != NULL) {
            /* Dequeue waiting readers and reply to them */
            while ((wr = dequeue_waiting_reader(i)) != NULL) {
                /* Check if rcvid is still valid */
                if (MsgInfo(wr->rcvid, &info) != -1) {
                    put_wr(wr);
                    pthread_mutex_unlock(&ti_ipc_state.lock);
                    MsgError(wr->rcvid, EINTR);
                    pthread_mutex_lock(&ti_ipc_state.lock);
                }
            }
            /* Check for pending ionotify/select calls */
            if (obj) {
                if (IOFUNC_NOTIFY_INPUT_CHECK(obj->notify, 1, 0)) {
                    iofunc_notify_trigger(obj->notify, 1, IOFUNC_NOTIFY_INPUT);
                }
            }
            pthread_mutex_unlock(&ti_ipc_state.lock);

            /* Free event packets for any received but unprocessed events. */
            while (List_empty (bufList) != TRUE){
                packet = (ipc_EventPacket *)
                              List_get (bufList);
                if (packet != NULL){
                    Memory_free (NULL, packet, sizeof(*packet));
                }
            }
            List_delete (&(bufList));
        }
        else {
            pthread_mutex_unlock(&ti_ipc_state.lock);
        }
    }

    /* Free the cached list */
    pthread_mutex_lock(&ti_ipc_state.lock);
    flush_uBuf();
    pthread_mutex_unlock(&ti_ipc_state.lock);

    if ((!recover) && (ti_ipc_state.gateHandle != NULL)) {
        GateSpinlock_delete ((GateSpinlock_Handle *)
                                       &(ti_ipc_state.gateHandle));
    }

    ti_ipc_state.run = FALSE;
    // run through and destroy the thread, and all outstanding
    // notify structures
    pthread_mutex_lock(&ti_ipc_state.lock);
    pthread_cond_signal(&ti_ipc_state.cond);
    pthread_mutex_unlock(&ti_ipc_state.lock);
    pthread_join(ti_ipc_state.nt, NULL);
    pthread_mutex_lock(&ti_ipc_state.lock);
    while (ti_ipc_state.head != NULL) {
        int index;
        WaitingReaders_t *item;
        index = dequeue_notify_list_item(ti_ipc_state.head);
        if (index < 0)
            break;
        item = dequeue_waiting_reader(index);
        while (item) {
            put_wr(item);
            item = dequeue_waiting_reader(index);
        }
    }
    ti_ipc_state.head = NULL ;
    ti_ipc_state.tail = NULL ;
    pthread_mutex_unlock(&ti_ipc_state.lock);

    GT_0trace (curTrace, GT_LEAVE, "_ti_ipc_destroy");
}
