/*
 *  @file       SharedMemoryAllocator.c
 *
 *  ============================================================================
 *
 */
/*
 *  Copyright (c) 2012, Texas Instruments Incorporated
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

#define SH_MEM_BLOCK1_START 0xBA300000
#define SH_MEM_BLOCK1_SIZE  0x5A00000

#define SH_MEM_BLOCK2_START 0x9DB00000
#define SH_MEM_BLOCK2_SIZE  0x1000000

#define SHM_PAGE_SIZE       0x1000
struct _iofunc_attr;
#define RESMGR_HANDLE_T struct _iofunc_attr
#define THREAD_POOL_PARAM_T dispatch_context_t

/*QNX specific header include */
#include <errno.h>
#include <unistd.h>
#include <stdio.h>
#include <malloc.h>
#include <devctl.h>
#include <sys/iofunc.h>
#include <sys/dispatch.h>
#include <sys/mman.h>
#include <sys/select.h>
#include <sys/procmgr.h>
#include <sys/slog.h>

/* Module headers */
#include <ti/shmemallocator/SharedMemoryAllocator.h>
#include <pthread.h>

/** ============================================================================
 *  Structs
 *  ============================================================================
 */
struct sharedMemobj{
    void *pa_shm;
    void *va_shm;
    int  size;
    int  pid;
    int blockID;
    struct sharedMemobj *prev;
    struct sharedMemobj *next;
};
typedef struct sharedMemobj SharedMem_Obj;

struct {
    ulong addr;
    uint len;
}blocks[MAX_BLOCKS_IDX+1] = {
    {SH_MEM_BLOCK1_START, SH_MEM_BLOCK1_SIZE},
    {SH_MEM_BLOCK2_START, SH_MEM_BLOCK2_SIZE}
};

pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

/** ============================================================================
 *  Globals
 *  ============================================================================
 */
static SharedMem_Obj *allocListHdr_blk[MAX_BLOCKS_IDX+1];
static SharedMem_Obj *freeListHdr_blk[MAX_BLOCKS_IDX+1];
static SharedMem_Obj *lastNode;

/** ============================================================================
 *  Function prototypes
 *  ============================================================================
 */
void initSHM(void);
void modifyFreeList(SharedMem_Obj *node, void *dstPtr, int size);
void removeFromFreeList(SharedMem_Obj *node, int del);
void addTofreeList(SharedMem_Obj *node);
void addToAllocList(SharedMem_Obj *node);

int removeFromAllocList(SharedMem_Obj *node, int unmap);
int alloc_shm(int size, int blockID, uint alignment, int pid);
void *getVAforPID(void *dstPtr, int size, int pid);
int free_shm(void* argPtr, int blockID, uint pid, int unmap);
void checkIntegrity(int blockID);
void releaseSHMforPID(int pid);

extern void * mmap_peer(pid_t pid, void *addr, size_t len, int prot, int flags, int fd, off_t off);
extern int munmap_peer(pid_t pid, void *addr, size_t len);

/** ============================================================================
 *  Functions
 *  ============================================================================
 */

void releaseSHMforPID(int pid)
{
    pthread_mutex_lock(&lock);

    int i;
    SharedMem_Obj *temp;
    void* addr;
    int blockID;

    for(i=0; i<=MAX_BLOCKS_IDX; i++) {
        temp = allocListHdr_blk[i];
        while(temp) {
            if(temp->pid == pid) {
                addr = temp->va_shm;
                blockID = temp->blockID;
                temp = temp->next;
                free_shm(addr, blockID, pid, 0);
            }
            else {
                temp = temp->next;
            }
        }
    }
    pthread_mutex_unlock(&lock);
}

void *getVAforPID(void *dstPtr, int size, int pid)
{
    void *vaPTR = mmap_peer(pid, NULL, size, PROT_NOCACHE|PROT_READ|PROT_WRITE,
                            MAP_SHARED|MAP_PHYS,
                            NOFD,
                            (off_t)dstPtr);
    if(vaPTR == MAP_FAILED){
        slogf (42, _SLOG_DEBUG1, "Mapping VA PTR failed %p\n",vaPTR);
    }

    return vaPTR;
}

void initSHM(void)
{
    int i;
    for(i=0; i<=MAX_BLOCKS_IDX; i++) {
        if(!freeListHdr_blk[i]) {
            freeListHdr_blk[i]= malloc(sizeof(SharedMem_Obj));
            freeListHdr_blk[i]->pa_shm = (void *)blocks[i].addr;
            freeListHdr_blk[i]->va_shm = NULL;
            freeListHdr_blk[i]->size = blocks[i].len;
            freeListHdr_blk[i]->blockID = i;
            freeListHdr_blk[i]->next = NULL;
            freeListHdr_blk[i]->prev = NULL;
            allocListHdr_blk[i] = NULL;
        }
    }
}

void deinitSHM(void)
{
    int i;
    SharedMem_Obj *temp, *temp1;

    for(i=0; i<MAX_BLOCKS_IDX; i++) {
        if(freeListHdr_blk[i]) {
            temp = freeListHdr_blk[i];
            temp1 = freeListHdr_blk[i]->next;
            while(temp1) {
                free(temp);
                temp = temp1;
                temp1 = temp1->next;
            }
            free(temp);
            freeListHdr_blk[i] = NULL;
        }
    }
    for(i=0; i<MAX_BLOCKS_IDX; i++) {
        if(allocListHdr_blk[i]) {
            temp = allocListHdr_blk[i];
            temp1 = allocListHdr_blk[i]->next;
            while(temp1) {
                free(temp);
                temp = temp1;
                temp1 = temp1->next;
            }
            free(temp);
            allocListHdr_blk[i] = NULL;
        }
    }
}

void modifyFreeList(SharedMem_Obj *node, void *dstPtr, int size)
{
    SharedMem_Obj *newNode1 = NULL;
    SharedMem_Obj *newNode2 = NULL;

    if(dstPtr > node->pa_shm) {
        newNode1 = malloc(sizeof(SharedMem_Obj));
        newNode1->size = (dstPtr - node->pa_shm);
        newNode1->pa_shm = node->pa_shm;
        newNode1->blockID = node->blockID;
    }
    if((dstPtr - node->pa_shm)+size < node->size) {
        newNode2 = malloc(sizeof(SharedMem_Obj));
        newNode2->pa_shm = dstPtr+size;
        newNode2->size = node->size - size - (dstPtr - node->pa_shm);
        newNode2->blockID = node->blockID;
    }
    removeFromFreeList(node, 1);
    if(newNode1)
        addTofreeList(newNode1);
    if(newNode2)
        addTofreeList(newNode2);
}

void removeFromFreeList(SharedMem_Obj *node, int del)
{
    if(node == freeListHdr_blk[node->blockID]) {
        freeListHdr_blk[node->blockID] = freeListHdr_blk[node->blockID]->next;
        if(freeListHdr_blk[node->blockID])
            freeListHdr_blk[node->blockID]->prev = NULL;
    } else {
        if(node->next) {
            node->next->prev = node->prev;
        }
        node->prev->next = node->next;
    }
    if(del)
        free(node);
    return;
}

void addToAllocList(SharedMem_Obj *node)
{
    SharedMem_Obj *temp = allocListHdr_blk[node->blockID];
    if(!temp) {
        node->next = NULL;
        node->prev = NULL;
        allocListHdr_blk[node->blockID] = node;
    } else {
        while(temp->next) {
            temp = temp->next;
        }
        temp->next = node;
        node->next = NULL;
        node->prev = temp;
    }
    lastNode = node;

    return;
}

int removeFromAllocList(SharedMem_Obj *node, int unmap)
{
    int status = 0;
    if(unmap) {
        status = munmap_peer(node->pid, node->va_shm, node->size);
        if(status < 0) {
            slogf (42, _SLOG_DEBUG1, "##unmapping VA for PID failed, process %u alive?\n", node->pid);
            return -1;
        }
    }
    if(node->prev) {
       node->prev->next = node->next;
    }
    if(node->next) {
        node->next->prev = node->prev;
    }
    if(node == allocListHdr_blk[node->blockID]) {
        allocListHdr_blk[node->blockID] = node->next;
        if(allocListHdr_blk[node->blockID])
            allocListHdr_blk[node->blockID]->prev = NULL;
    }
    addTofreeList(node);

    return 0;
}

void addTofreeList(SharedMem_Obj *node)
{
    SharedMem_Obj* temp = freeListHdr_blk[node->blockID];
    SharedMem_Obj* temp1 = NULL;
    int added = 0;

    if(!freeListHdr_blk[node->blockID]) {
        freeListHdr_blk[node->blockID] = node;
        freeListHdr_blk[node->blockID]->prev = NULL;
        freeListHdr_blk[node->blockID]->next = NULL;
        return;
    }
    if(node->pa_shm < freeListHdr_blk[node->blockID]->pa_shm) {
        if((node->pa_shm + node->size) == freeListHdr_blk[node->blockID]->pa_shm) {
            node->size = node->size + freeListHdr_blk[node->blockID]->size;
            node->next = freeListHdr_blk[node->blockID]->next;
            if(freeListHdr_blk[node->blockID]->next)
               freeListHdr_blk[node->blockID]->next->prev = node;
            free(freeListHdr_blk[node->blockID]);
        }
        else {
            node->next = freeListHdr_blk[node->blockID];
            freeListHdr_blk[node->blockID]->prev = node;
        }
        freeListHdr_blk[node->blockID] = node;
        freeListHdr_blk[node->blockID]->prev = NULL;
        return;
    }
    while(temp->next) {
        if((temp->pa_shm + temp->size == node->pa_shm) && (temp->pa_shm + temp->size + node->size == temp->next->pa_shm)) {
            temp1 = temp->next;
            temp->size += (temp1->size + node->size);
            temp->next = temp1->next;
            if(temp1->next)
                temp1->next->prev = temp;
            free(node);
            free (temp1);
            return;
        }

        if(node->pa_shm < temp->next->pa_shm) {
            if(temp->pa_shm + temp->size == node->pa_shm) {
                added = 1;
                temp->size = temp->size + node->size;
            }
            else if(node->pa_shm + node->size == temp->next->pa_shm) {
                temp->next->pa_shm = node->pa_shm;
                temp->next->size = temp->next->size + node->size;
                added = 1;
            }
            if(added) {
                free(node);
            }
            else {
                temp->next->prev = node;
                node->next = temp->next;
                temp->next = node;
                node->prev = temp;
            }
            return;
        }
        temp = temp->next;
    }
    if(temp->pa_shm + temp->size == node->pa_shm) {
        temp->size += node->size;
        free(node);
    }
    else {
        temp->next = node;
        node->prev = temp;
        node->next = NULL;
    }
}

int alloc_shm(int size, int blockID, uint alignment, int pid)
{
    void *phy_addr = NULL;
    void *vir_addr = NULL;
    SharedMem_Obj* temp = NULL;
    SharedMem_Obj* node = NULL;
    SharedMem_Obj* newNode = NULL;

    if(!freeListHdr_blk[blockID]) {
        slogf (42, _SLOG_DEBUG1, "\nalloc_shm failed:No free mem available in block{%d} !!!\n", blockID);
        return -1;
    }

    temp  = freeListHdr_blk[blockID];
    if(size%SHM_PAGE_SIZE)
        size += (SHM_PAGE_SIZE - (size%SHM_PAGE_SIZE));
    while (temp) {
        if(alignment) {
            phy_addr = (void*)(((uint)((temp->pa_shm + alignment-1))/alignment)*alignment);
            if((phy_addr + size) == (temp->pa_shm + temp->size))
                break;
            else {
                if((phy_addr + size) < (temp->pa_shm + temp->size)){
                    if(!node || (node->size < temp->size)) {
                        node = temp;
                    }
                }
                phy_addr = NULL;
            }
        }
        else if(temp->size == size) {
            phy_addr = temp->pa_shm;
            break;
        }
        else if(temp->size > size) {
            if(!node || (node->size < temp->size)) {
                node = temp;
            }
        }
        temp = temp->next;
    }
    if(phy_addr) {
        vir_addr = getVAforPID(phy_addr, size, pid);
        if(vir_addr == MAP_FAILED)
            return -1;
        removeFromFreeList(temp, 0);
        temp->va_shm = vir_addr;
        temp->pid = pid;
        addToAllocList(temp);
        return 0;

    }
    else if(node){
        if(alignment)
            phy_addr = (void*)(((uint)((node->pa_shm + alignment-1))/alignment)*alignment);
        else
            phy_addr = node->pa_shm;

        vir_addr = getVAforPID(phy_addr, size, pid);
        if(vir_addr == MAP_FAILED)
            return -1;
        modifyFreeList(node, phy_addr, size);
        newNode = malloc(sizeof(SharedMem_Obj));
        newNode->va_shm = vir_addr;
        newNode->pa_shm = phy_addr;
        newNode->pid = pid;
        newNode->blockID = blockID;
        newNode->size = size;
        addToAllocList(newNode);

        return 0;
    }
    else {
        slogf (42, _SLOG_DEBUG1, "\nalloc_shm failed:buf of size(%d) not available !!!\n", size);
        return -1;
    }
}

int free_shm(void* argPtr, int blockId, uint pid, int unmap)
{
    int ret = 0;
    SharedMem_Obj* temp = allocListHdr_blk[blockId];

    while(temp) {
        if((temp->va_shm == argPtr) && temp->pid == pid) {
            ret = removeFromAllocList(temp, unmap);
            if(ret < 0)
                return -1;
            break;
        }
        temp = temp->next;
    }
    if(temp == NULL)
        ret = -1;

    return ret;
}

void checkIntegrity(int blockID)
{
    SharedMem_Obj *t_alloc = allocListHdr_blk[blockID];
    SharedMem_Obj *t_free = freeListHdr_blk[blockID];
    int size = blocks[blockID].len;

    slogf (42, _SLOG_DEBUG1, "\n## checkIntegrity ##\n");
    while(t_alloc && t_free) {
        if(t_alloc->pa_shm > t_free->pa_shm) {
            while(t_free && t_free->pa_shm < t_alloc->pa_shm) {
                slogf (42, _SLOG_DEBUG1, "## FL(0x%0x - 0x%0x)\n",
                       (unsigned int)t_free->pa_shm,
                       t_free->size);

                size -= t_free->size;
                t_free = t_free->next;
            }
        }
        else {
            while(t_alloc && t_alloc->pa_shm < t_free->pa_shm) {
                slogf (42, _SLOG_DEBUG1, "## AL(0x%0x - 0x%0x)\n",
                       (unsigned int)t_alloc->pa_shm,
                       t_alloc->size);

                size -= t_alloc->size;
                t_alloc = t_alloc->next;
            }
        }
    }
    while(t_alloc) {
        slogf (42, _SLOG_DEBUG1, "## AL(0x%0x - 0x%0x)\n",
               (unsigned int)t_alloc->pa_shm,
               t_alloc->size);

        size -= t_alloc->size;
        t_alloc = t_alloc->next;
    }
    while(t_free) {
        slogf (42, _SLOG_DEBUG1, "## FL(0x%0x - 0x%0x)\n",
               (unsigned int)t_free->pa_shm,
               t_free->size);

        size -= t_free->size;
        t_free = t_free->next;
    }
    slogf (42, _SLOG_DEBUG1, "##checkIntegrity - size = 0x%0x\n", size);
}

typedef struct shmem_ocb {
    iofunc_ocb_t       ocb;
    pid_t              pid;
} shmem_ocb_t;

IOFUNC_OCB_T *
ocb_calloc (resmgr_context_t * ctp, IOFUNC_ATTR_T * device)
{
    shmem_ocb_t *ocb = NULL;

    /* Allocate the OCB */
    ocb = (shmem_ocb_t *) calloc (1, sizeof (shmem_ocb_t));
    if (ocb == NULL){
        errno = ENOMEM;
        return (NULL);
    }

    ocb->pid = ctp->info.pid;

    return (IOFUNC_OCB_T *)(ocb);
}

void
ocb_free (IOFUNC_OCB_T * i_ocb)
{
    shmem_ocb_t * ocb = (shmem_ocb_t *)i_ocb;

    if (ocb) {
        releaseSHMforPID(ocb->pid);
        free (ocb);
    }
}

int
SharedMemAllDrv_devctl(resmgr_context_t * ctp, io_devctl_t * msg,
                        iofunc_ocb_t * ocb)
{
    pthread_mutex_lock(&lock);

    int status = _RESMGR_ERRNO (EOK);
    int dcmd = msg->i.dcmd;
    msg->o.ret_val = EOK;
    SHMAllocatorDrv_CmdArgs *cargs       =
                             (SHMAllocatorDrv_CmdArgs *)(_DEVCTL_DATA (msg->i));
    SHMAllocatorDrv_CmdArgs *output      =
                             (SHMAllocatorDrv_CmdArgs *)(_DEVCTL_DATA (msg->o));
    switch (dcmd)
    {
        case CMD_SHMALLOCATOR_ALLOC:
        {
            status = alloc_shm(cargs->size, cargs->blockID, cargs->alignment, ctp->info.pid);

            if(status == -1) {
                output->result.blockID = -1;
                output->result.phy_addr = NULL;
                output->result.vir_addr = NULL;
                output->apiStatus = -1;
            }
            else {
                output->result.blockID = cargs->blockID;
                output->result.phy_addr = (unsigned long)lastNode->pa_shm;
                output->result.vir_addr = (unsigned long)lastNode->va_shm;
                output->result.size = lastNode->size;
                output->apiStatus = 0;
            }
        }
        break;
        case CMD_SHMALLOCATOR_RELEASE:
        {
            status = free_shm((void *)cargs->result.vir_addr, cargs->blockID,
                              ctp->info.pid, 1);
            if(status == 0) {
                output->apiStatus = 0;
            }
            else {
                output->apiStatus = -1;
            }

            break;
        }
        default:
        {
            slogf (42, _SLOG_DEBUG1, "SharedMemAllDrv_devctl: Bad request!!\n");
            status = -1;
        }
        break;
    }
#ifdef DEBUG_SHM
            checkIntegrity(cargs->blockID);
#endif

    pthread_mutex_unlock(&lock);
    return (_RESMGR_PTR (ctp, &msg->o,
                         sizeof (msg->o) + sizeof(SHMAllocatorDrv_CmdArgs)));
}

static resmgr_connect_funcs_t    connect_funcs;
static resmgr_io_funcs_t         io_funcs;
static iofunc_mount_t            mattr;
static iofunc_funcs_t            ocb_funcs;
static iofunc_attr_t             attr;

int
main(int argc, char *const argv[])
{
    /* declare variables we'll be using */
    resmgr_attr_t        resmgr_attr;
    dispatch_t           *dpp;
    int                  id;
    int                  ret = 0;
    struct stat          sbuf;
    thread_pool_attr_t   tattr;
    thread_pool_t        *tpool;
    sigset_t             set;

    /* Obtain I/O privity */
    ret = ThreadCtl_r (_NTO_TCTL_IO, 0);
    if (ret)
    {
        fprintf(stderr, "Unable to obtain I/O privity");
        return -1;
    }

    /* Only let one run. */
    if (-1 != stat("/dev/shmemallocator", &sbuf)) {
        return -1;
    }

    initSHM();

    /* initialize dispatch interface */
    if((dpp = dispatch_create()) == NULL) {
        fprintf(stderr,
                "%s: Unable to allocate dispatch handle.\n",
                argv[0]);
        return -1;
    }

    /* Initialize the thread pool */
    memset (&tattr, 0x00, sizeof (thread_pool_attr_t));
    tattr.handle = dpp;
    tattr.context_alloc = dispatch_context_alloc;
    tattr.context_free = dispatch_context_free;
    tattr.block_func = dispatch_block;
    tattr.unblock_func = dispatch_unblock;
    tattr.handler_func = dispatch_handler;
    tattr.lo_water = 2;
    tattr.hi_water = 8;
    tattr.increment = 1;
    tattr.maximum = 50;

    /* initialize resource manager attributes */
    memset(&resmgr_attr, 0, sizeof resmgr_attr);
    resmgr_attr.nparts_max = 10;
    resmgr_attr.msg_max_size = 16384;
    memset(&mattr, 0, sizeof(iofunc_mount_t));
    mattr.flags = 0;
    mattr.conf = IOFUNC_PC_CHOWN_RESTRICTED | IOFUNC_PC_NO_TRUNC | IOFUNC_PC_SYNC_IO;
    mattr.dev = 0;
    mattr.blocksize=0;
    mattr.funcs = &ocb_funcs;
    memset(&ocb_funcs, 0, sizeof(iofunc_funcs_t));
    ocb_funcs.nfuncs = _IOFUNC_NFUNCS;
    ocb_funcs.ocb_calloc = ocb_calloc;
    ocb_funcs.ocb_free = ocb_free;
    memset(&io_funcs, 0, sizeof(resmgr_io_funcs_t));
    iofunc_func_init(_RESMGR_CONNECT_NFUNCS, &connect_funcs, _RESMGR_IO_NFUNCS, &io_funcs);
    io_funcs.devctl = SharedMemAllDrv_devctl;

    iofunc_attr_init(&attr, S_IFNAM | 0777 , 0, 0);
    attr.mount = &mattr;

    if ( ( tpool = thread_pool_create(&tattr,0) ) == NULL )
        return -1;

    if (-1 != stat("/dev/shmemallocator", &sbuf)) {
        return -1;
    }

    /* attach our device name */
    id = resmgr_attach(
            dpp,            /* dispatch handle        */
            &resmgr_attr,   /* resource manager attrs */
            "/dev/shmemallocator",   /* device name            */
            _FTYPE_ANY,     /* open type              */
            0,              /* flags                  */
            &connect_funcs, /* connect routines       */
            &io_funcs,      /* I/O routines           */
            &attr);         /* handle                 */
    if(id == -1) {
        fprintf(stderr, "%s: Unable to attach name.\n", argv[0]);
        return -1;
    }

    /* background the process */
    procmgr_daemon(0, PROCMGR_DAEMON_NOCLOSE|PROCMGR_DAEMON_NODEVNULL);
    thread_pool_start( tpool );

    /* Mask out unecessary signals */
    sigfillset (&set);
    sigdelset (&set, SIGINT);
    sigdelset (&set, SIGTERM);
    pthread_sigmask (SIG_BLOCK, &set, NULL);

    /* Wait for one of these signals */
    sigemptyset (&set);
    sigaddset (&set, SIGINT);
    sigaddset (&set, SIGQUIT);
    sigaddset (&set, SIGTERM);

    /* Wait for a signal */
    while (1)
    {
        switch (SignalWaitinfo (&set, NULL))
        {
            case SIGTERM:
            case SIGQUIT:
            case SIGINT:
                goto done;
            default:
                break;
        }
    }

done:
    /* Received SIGTERM: clean up */
    resmgr_detach(dpp, id, _RESMGR_DETACH_ALL);

    deinitSHM();

    return 0;
}
