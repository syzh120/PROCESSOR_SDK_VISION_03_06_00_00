#include <stdio.h>
#include <stdint.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#include "edma3_drv.h"

#ifdef DEBUG
#define debug_printf(fmt, args...) printf(fmt, args...)
#else
#define debug_printf(fmt, args...)
#endif

/* MAX ACOUNT */
#define MAX_ACOUNT					(64u)
/* MAX BCOUNT */
#define MAX_BCOUNT					(1u)
/* MAX CCOUNT */
#define MAX_CCOUNT					(1u)
/**
 * Buffers (src and dest) are needed for mem-2-mem data transfers.
 * This define is for the MAXIMUM size and hence the maximum data
 * which could be transferred using the sample test cases below.
 */
#define MAX_BUFFER_SIZE				(MAX_ACOUNT * MAX_BCOUNT * MAX_CCOUNT)

#define SRCADDR (0x0C000000)
#define DSTADDR (0x0C100000)
signed char *srcBuff1;
signed char *dstBuff1;

/* OPT Field specific defines */
#define OPT_SYNCDIM_SHIFT                   (0x00000002u)
#define OPT_TCC_MASK                        (0x0003F000u)
#define OPT_TCC_SHIFT                       (0x0000000Cu)
#define OPT_ITCINTEN_SHIFT                  (0x00000015u)
#define OPT_TCINTEN_SHIFT                   (0x00000014u)

/* Flag variable to check transfer completion on channel 1 */
volatile short irqRaised1 = 0;
/* Flag variable to check transfer completion on channel 2 */
volatile short irqRaised2 = 0;

/**
 * Shadow Region on which the executable is runnig. Its value is populated
 * with the DSP Instance Number here in this case.
 */
unsigned int region_id;

extern EDMA3_DRV_GblConfigParams sampleEdma3GblCfgParams[];
extern EDMA3_DRV_InstanceInitConfig sampleInstInitConfig[][EDMA3_MAX_REGIONS];

sem_t mutex;
static int dev_mem_fd;

uint32_t edma3_mmap(uint32_t addr, uint32_t size)
{
        uint32_t virt_addr;
        uint32_t page_size;
        page_size = sysconf(_SC_PAGE_SIZE);
        if (size%page_size)
        {
                debug_printf("Size does not align with page size. Size given: %d\n", size);
                return 0;
        }
        if ((uint32_t)addr % page_size)
        {
                debug_printf("Address does not align with page size. Address given: 0x%08x\n", (uint32_t) addr);
                return 0;
        }
        virt_addr = (uint32_t) mmap(0, size, (PROT_READ|PROT_WRITE), MAP_SHARED, dev_mem_fd, (off_t)addr);
        if (virt_addr == -1)
        {
                debug_printf("mmap failed!\n");
                return 0;
        }
        return virt_addr;
}

int setupEdmaConfig(EDMA3_DRV_GblConfigParams *cfg)
{
	int i;
	cfg->globalRegs = (uint32_t *)edma3_mmap((uint32_t)cfg->globalRegs, 0x8000);
	for (i = 0; i < EDMA3_MAX_TC; i++)
	{
		if (cfg->tcRegs[i] != NULL)
			cfg->tcRegs[i] =(uint32_t *)edma3_mmap((uint32_t)cfg->tcRegs[i], 0x1000);
	}
    return 1;
}

/* Callback function 1 */
void callback1 (unsigned int tcc, EDMA3_RM_TccStatus status,
                        void *appData)
    {
    (void)tcc;
    (void)appData;

    switch (status)
        {
        case EDMA3_RM_XFER_COMPLETE:
            /* Transfer completed successfully */
            irqRaised1 = 1;
            break;
        case EDMA3_RM_E_CC_DMA_EVT_MISS:
            /* Transfer resulted in DMA event miss error. */
            irqRaised1 = -1;
            break;
        case EDMA3_RM_E_CC_QDMA_EVT_MISS:
            /* Transfer resulted in QDMA event miss error. */
            irqRaised1 = -2;
            break;
        default:
            break;
        }
    }

EDMA3_DRV_Result edma3_test(
                                    EDMA3_DRV_Handle hEdma,
                                    unsigned int acnt,
                                    unsigned int bcnt,
                                    unsigned int ccnt,
                                    EDMA3_DRV_SyncType syncType)
    {
    EDMA3_DRV_Result result = EDMA3_DRV_SOK;
    EDMA3_DRV_PaRAMRegs paramSet = {0,0,0,0,0,0,0,0,0,0,0,0};
    unsigned int chId = 0;
    unsigned int tcc = 0;
    int i;
    unsigned int count;
    unsigned int Istestpassed = 0u;
    unsigned int numenabled = 0;
    unsigned int BRCnt = 0;
    int srcbidx = 0, desbidx = 0;
    int srccidx = 0, descidx = 0;

	srcBuff1 = (signed char*) edma3_mmap(SRCADDR, 0x100000);
	dstBuff1 = (signed char*) edma3_mmap(DSTADDR, 0x100000);

    /* Initalize source and destination buffers */
    for (count = 0u; count < (acnt*bcnt*ccnt); count++)
        {
        srcBuff1[count] = (int)count;
        /**
         * No need to initialize the destination buffer as it is being invalidated.
        dstBuff1[count] = initval;
        */
        }


#ifdef EDMA3_ENABLE_DCACHE
    /*
    * Note: These functions are required if the buffer is in DDR.
    * For other cases, where buffer is NOT in DDR, user
    * may or may not require the below functions.
    */
    /* Flush the Source Buffer */
    if (result == EDMA3_DRV_SOK)
        {
        result = Edma3_CacheFlush((unsigned int)srcBuff1, (acnt*bcnt*ccnt));
        }

    /* Invalidate the Destination Buffer */
    if (result == EDMA3_DRV_SOK)
        {
        result = Edma3_CacheInvalidate((unsigned int)dstBuff1, (acnt*bcnt*ccnt));
        }
#endif  /* EDMA3_ENABLE_DCACHE */


    /* Set B count reload as B count. */
    BRCnt = bcnt;

    /* Setting up the SRC/DES Index */
    srcbidx = (int)acnt;
    desbidx = (int)acnt;
    if (syncType == EDMA3_DRV_SYNC_A)
        {
        /* A Sync Transfer Mode */
        srccidx = (int)acnt;
        descidx = (int)acnt;
        }
    else
        {
        /* AB Sync Transfer Mode */
        srccidx = ((int)acnt * (int)bcnt);
        descidx = ((int)acnt * (int)bcnt);
        }


    /* Setup for Channel 1*/
    tcc = EDMA3_DRV_TCC_ANY;
    chId = EDMA3_DRV_DMA_CHANNEL_ANY;

    /* Request any DMA channel and any TCC */
    if (result == EDMA3_DRV_SOK)
        {
        result = EDMA3_DRV_requestChannel (hEdma, &chId, &tcc,
                                        (EDMA3_RM_EventQueue)0,
                                            &callback1, NULL);
	}

    if (result == EDMA3_DRV_SOK)
        {
        /* Fill the PaRAM Set with transfer specific information */
        paramSet.srcAddr    = SRCADDR;
        paramSet.destAddr   = DSTADDR;

        /**
         * Be Careful !!!
         * Valid values for SRCBIDX/DSTBIDX are between .32768 and 32767
         * Valid values for SRCCIDX/DSTCIDX are between .32768 and 32767
         */
        paramSet.srcBIdx    = srcbidx;
        paramSet.destBIdx   = desbidx;
        paramSet.srcCIdx    = srccidx;
        paramSet.destCIdx   = descidx;

        /**
         * Be Careful !!!
         * Valid values for ACNT/BCNT/CCNT are between 0 and 65535.
         * ACNT/BCNT/CCNT must be greater than or equal to 1.
         * Maximum number of bytes in an array (ACNT) is 65535 bytes
         * Maximum number of arrays in a frame (BCNT) is 65535
         * Maximum number of frames in a block (CCNT) is 65535
         */
        paramSet.aCnt       = acnt;
        paramSet.bCnt       = bcnt;
        paramSet.cCnt       = ccnt;

        /* For AB-synchronized transfers, BCNTRLD is not used. */
        paramSet.bCntReload = BRCnt;

        paramSet.linkAddr   = 0xFFFFu;

        /* Src & Dest are in INCR modes */
        paramSet.opt &= 0xFFFFFFFCu;
        /* Program the TCC */
        paramSet.opt |= ((tcc << OPT_TCC_SHIFT) & OPT_TCC_MASK);

        /* Enable Intermediate & Final transfer completion interrupt */
        paramSet.opt |= (1 << OPT_ITCINTEN_SHIFT);
        paramSet.opt |= (1 << OPT_TCINTEN_SHIFT);

        if (syncType == EDMA3_DRV_SYNC_A)
            {
            paramSet.opt &= 0xFFFFFFFBu;
            }
        else
            {
            /* AB Sync Transfer Mode */
            paramSet.opt |= (1 << OPT_SYNCDIM_SHIFT);
            }

        /* Now, write the PaRAM Set. */
        result = EDMA3_DRV_setPaRAM(hEdma, chId, &paramSet);
        }


    /*
     * Since the transfer is going to happen in Manual mode of EDMA3
     * operation, we have to 'Enable the Transfer' multiple times.
     * Number of times depends upon the Mode (A/AB Sync)
     * and the different counts.
     */
    if (result == EDMA3_DRV_SOK)
        {
        /*Need to activate next param*/
        if (syncType == EDMA3_DRV_SYNC_A)
            {
            numenabled = bcnt * ccnt;
            }
        else
            {
            /* AB Sync Transfer Mode */
            numenabled = ccnt;
            }

        for (i = 0; i < numenabled; i++)
            {

            /*
             * Now enable the transfer as many times as calculated above.
             */
            result = EDMA3_DRV_enableTransfer (hEdma, chId,
                                                EDMA3_DRV_TRIG_MODE_MANUAL);
            if (result != EDMA3_DRV_SOK)
                {
                printf ("edma3_test: EDMA3_DRV_enableTransfer " \
                                    "Failed, error code: %d\n", result);
                break;
                }
                EDMA3_DRV_waitAndClearTcc(hEdma,chId);
                printf("Transfer completed!\n");
            }
        }


    /* Match the Source and Destination Buffers. */
    if (EDMA3_DRV_SOK == result)
        {
        for (i = 0; i < (acnt*bcnt*ccnt); i++)
            {
            if (srcBuff1[i] != dstBuff1[i])
                {
                Istestpassed = 0u;
                printf("edma3_test: Data write-read matching" \
                                     "FAILED at i = %d\n", i);
                break;
                }
            }
        if (i == (acnt*bcnt*ccnt))
            {
            Istestpassed = 1u;
            }


        /* Free the previously allocated channel. */
        result = EDMA3_DRV_freeChannel (hEdma, chId);
        if (result != EDMA3_DRV_SOK)
            {
            printf("edma3_test: EDMA3_DRV_freeChannel() FAILED, " \
                                "error code: %d\n", result);
            }
        }


    if(Istestpassed == 1u)
        {
        printf("edma3_test PASSED\n");
        }
    else
        {
        printf("edma3_test FAILED\n");
        printf("result is: %d\n",result);
        //result = ((EDMA3_DRV_SOK == result) ? NULL : result);
                                //EDMA3_DATA_MISMATCH_ERROR : result);
        }


    return result;
}



int main()
{
	EDMA3_DRV_Result edma3Result = EDMA3_DRV_E_INVALID_PARAM;
	EDMA3_DRV_GblConfigParams *globalConfig = NULL;
	EDMA3_DRV_InstanceInitConfig *instanceConfig = NULL;
	EDMA3_DRV_InitConfig initCfg;
	EDMA3_RM_MiscParam miscParam;
	EDMA3_DRV_Handle hEdma = NULL;
	int edma3Id = 0;
	if ((dev_mem_fd = open("/dev/mem", (O_RDWR | O_SYNC))) == -1)
	{
		debug_printf("Failed to open /dev/mem \n");
		return -1;
	}

	globalConfig = &sampleEdma3GblCfgParams[0];
	setupEdmaConfig(globalConfig);
	edma3Result = EDMA3_DRV_create(edma3Id, globalConfig, (void *) &miscParam);
	/* configuration structure for the Driver */
	instanceConfig = &sampleInstInitConfig[edma3Id][0];

	initCfg.isMaster = TRUE;
	/* Choose shadow region according to the DSP# */
	initCfg.regionId = (EDMA3_RM_RegionId)0;
	/*Saving the regionId for using it in the sample_cs.c file */
	region_id = (EDMA3_RM_RegionId)0;
	/* Driver instance specific config NULL */
	initCfg.drvInstInitConfig = instanceConfig;
	initCfg.gblerrCb = NULL;
	initCfg.gblerrData = NULL;

	/* Open the Driver Instance */
	hEdma = EDMA3_DRV_open (edma3Id, (const EDMA3_DRV_InitConfig *) &initCfg, &edma3Result);
	if (hEdma) printf("hEdma opened!\n");
	else printf("edma open failed!\n");
	if (edma3Result == EDMA3_DRV_SOK) printf("edmaResult is ok\n");
	else printf("edma open result not okay\n");
	edma3_test(hEdma, MAX_ACOUNT, MAX_BCOUNT, MAX_CCOUNT, EDMA3_DRV_SYNC_A);
	
	close(dev_mem_fd);
	return 0;
}

void edma3OsProtectEntry (unsigned int edma3InstanceId, int level, unsigned int *intState)
{
}

void edma3OsProtectExit (unsigned int edma3InstanceId,
                        int level, unsigned int intState) {}

EDMA3_DRV_Result Edma3_CacheInvalidate(unsigned int mem_start_ptr,
                           unsigned int    num_bytes) {return EDMA3_DRV_SOK;}

EDMA3_DRV_Result Edma3_CacheFlush(unsigned int mem_start_ptr,
                      unsigned int num_bytes) {return EDMA3_DRV_SOK;}

EDMA3_DRV_Result edma3OsSemCreate() 
{
    sem_init(&mutex, 0, 1);
    return EDMA3_DRV_SOK;
}

EDMA3_DRV_Result edma3OsSemDelete() 
{
    sem_destroy(&mutex);
    return EDMA3_DRV_SOK;
}

EDMA3_DRV_Result edma3OsSemTake(EDMA3_OS_Sem_Handle hSem, int32_t mSecTimeout) 
{
    sem_post(&mutex);
    return EDMA3_DRV_SOK;
}

EDMA3_DRV_Result edma3OsSemGive(EDMA3_OS_Sem_Handle hSem) 
{
    sem_wait(&mutex);
    return EDMA3_DRV_SOK;
}

