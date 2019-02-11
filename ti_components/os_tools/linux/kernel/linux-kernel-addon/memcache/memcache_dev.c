/*
 *******************************************************************************
 *
 * Copyright (C) 2015 Texas Instruments Incorporated - http://www.ti.com/
 * ALL RIGHTS RESERVED
 *
 *******************************************************************************
 */

#include <dev_memcache_priv.h>
DMA_Dev gDMA_dev;

#if !defined(dmac_map_area)
#if defined(MULTI_CACHE)
#define dmac_map_area			cpu_cache.dma_map_area
#else
#define dmac_map_area                   __glue(_CACHE,_dma_map_area)
/* Add prototypes for dmac_map_area */
void dmac_map_area(const void *, size_t, int);
#endif
#endif
int DMA_devOpen(struct inode *inode, struct file *filp)
{
  int status=0;
  int minor, major;

  minor = iminor(inode);
  major = imajor(inode);

#ifdef DMA_DEBUG
  printk(KERN_INFO "DMA: DMA_devOpen()   , %4d, %2d \n", major, minor);
#endif

  return status;                /* success */
}

int DMA_devRelease(struct inode *inode, struct file *filp)
{
#ifdef DMA_DEBUG
  printk(KERN_INFO "DMA: DMA_devRelease()\n");
#endif
  return 0;
}


int DMA_devMmap (struct file * filp, struct vm_area_struct * vma)
{
    if (remap_pfn_range (vma,
                         vma->vm_start,
                         vma->vm_pgoff,
                         vma->vm_end - vma->vm_start,
                         vma->vm_page_prot)) {
        return -EAGAIN;
    }

    return 0;
}

long DMA_devIoctl(struct file *filp, unsigned int cmd, unsigned long arg)
{
  int status=0;
  unsigned int size;
  DMA_MmapPrm      mmapPrm;
  DMA_CacheInvPrm  cacheInvPrm;
  DMA_CacheWbPrm   cacheWbPrm;

#ifdef DMA_DEBUG
  printk(KERN_INFO "DMA: DMA_devIoctl()\n");
#endif

  if(!DMA_IOCTL_CMD_IS_VALID(cmd))
    return -1;

  cmd = DMA_IOCTL_CMD_GET(cmd);

  switch(cmd)
  {
    case DMA_CMD_MMAP:

      status = down_interruptible(&gDMA_dev.semLock);

      status = copy_from_user(&mmapPrm, (void*)arg, sizeof(mmapPrm));
      if(status==0) {

        #ifdef DMA_DEBUG
        printk(KERN_INFO "DMA: IOCTL: DMA_CMD_MMAP (0x%08x, %d) ### \n", mmapPrm.physAddr, mmapPrm.size);
        #endif

        if(mmapPrm.mapType==OSA_DMA_MMAP_TYPE_NOCACHE)
        {
                #ifdef DMA_DEBUG
                printk(KERN_INFO "DMA: ### ioremap_nocache() ### \n");
                #endif

                mmapPrm.virtAddr
                    = (unsigned int)ioremap_nocache(
                        mmapPrm.physAddr,
                        mmapPrm.size
                        );
        }
        if(mmapPrm.mapType==OSA_DMA_MMAP_TYPE_CACHE)
        {
                #ifdef DMA_DEBUG
                printk(KERN_INFO "DMA: ### ioremap_cache() ### \n");
                #endif

                mmapPrm.virtAddr
                    = (unsigned int)ioremap_cache(
                        mmapPrm.physAddr,
                        mmapPrm.size
                        );
        }
        if(mmapPrm.mapType==OSA_DMA_MMAP_TYPE_WRITE_COMBINED)
        {
                #ifdef DMA_DEBUG
                printk(KERN_INFO "DMA: ### ioremap_wc() ### \n");
                #endif


                mmapPrm.virtAddr
                    = (unsigned int)ioremap_wc(
                        mmapPrm.physAddr,
                        mmapPrm.size
                        );
        }

        if(status==0) {
          status = copy_to_user((void*)arg, &mmapPrm, sizeof(mmapPrm));
        }
      }

      up(&gDMA_dev.semLock);

      break;

      case DMA_CMD_CACHEINV:
          status = down_interruptible(&gDMA_dev.semLock);
          status = copy_from_user(&cacheInvPrm, (void*)arg, sizeof(cacheInvPrm));
          if(status==0) {
             outer_inv_range(cacheInvPrm.physAddr, cacheInvPrm.physAddr + cacheInvPrm.size);
             dmac_map_area((void *)cacheInvPrm.virtAddr, cacheInvPrm.size, DMA_FROM_DEVICE);
          }
          up(&gDMA_dev.semLock);
         break;

      case DMA_CMD_CACHEWB:
          status = down_interruptible(&gDMA_dev.semLock);
          status = copy_from_user(&cacheWbPrm, (void*)arg, sizeof(cacheWbPrm));
          if(status==0) {
              size = (cacheWbPrm.virtAddrEnd - cacheWbPrm.virtAddrStart);
              dmac_map_area((void *)cacheWbPrm.virtAddrStart, size, DMA_TO_DEVICE);
              outer_clean_range(cacheWbPrm.physAddrStart, cacheWbPrm.physAddrStart + size);
          }
          up(&gDMA_dev.semLock);
         break;

      default:
         status = -1;
         break;
  }

  return status;
}


struct file_operations gDMA_devFileOps = {
  owner: THIS_MODULE,
  open: DMA_devOpen,
  release: DMA_devRelease,
  unlocked_ioctl: DMA_devIoctl,
  mmap: DMA_devMmap
};

int DMA_devInit(void)
{
  int     result;
  dev_t   dev = 0;

#ifdef DMA_DEBUG
  printk(KERN_INFO "DMA: DMA_devInit() \n");
#endif

  result = alloc_chrdev_region(&dev, 0, 1, DMA_DRV_NAME);

  if (result < 0) {
    FUNCERR( "DMA: can't get device major num \n");
    return result;
  }

  gDMA_dev.major = MAJOR(dev);

  sema_init(&gDMA_dev.semLock, 1);

  cdev_init(&gDMA_dev.cdev, &gDMA_devFileOps);

  gDMA_dev.cdev.owner = THIS_MODULE;
  gDMA_dev.cdev.ops = &gDMA_devFileOps;

  result = cdev_add(&gDMA_dev.cdev, dev, 1);

  if (result)
    FUNCERR( "DMA: Error [%d] while adding device [%s] \n", result, DMA_DRV_NAME);

  printk(KERN_INFO "DMA: Module install successful, device major num = %d \n", gDMA_dev.major);

  return result;
}

void DMA_devExit(void)
{
  dev_t   devno = MKDEV(gDMA_dev.major, 0);

#ifdef DMA_DEBUG
  printk(KERN_INFO "DMA: DMA_devExit() \n");
#endif

  cdev_del(&gDMA_dev.cdev);

  unregister_chrdev_region(devno, 1);
}



#if  !defined(dmac_map_range)
#if !defined(MULTI_CACHE)

//#warning "dmac_map_range is *not* #defined, using work-around for asm cache functions"

#ifdef CONFIG_CPU_ARM926T

/*
 * The following assembly functions were taken from
 *     arch/arm/mm/proc-arm926.S
 * Since we can't use the C preprocessor to evaluate #defines, the
 * code that was taken is the code encapsulated by
 *     #ifndef CONFIG_CPU_DCACHE_WRITETHROUGH
 *     ...
 *     #endif
 * (note that this is #ifndef, i.e., #if !defined)
 */

/*
 * the cache line size of the I and D cache
 */
/*
 * Leave here for documentation purposes, but we don't use it since
 * asm("") statements won't get preprocessed (inside a string).
 */
#define CACHE_DLINESIZE 32

asm("\n \
        .global arm926_dma_map_area\n \
arm926_dma_map_area:\n \
        add     r1, r1, r0\n \
@        cmp     r2, #DMA_TO_DEVICE\n \
        cmp     r2, #1\n \
        beq     arm926_dma_clean_range\n \
        bcs     arm926_dma_inv_range\n \
        b       arm926_dma_flush_range\n \
");

/*
 *      dma_inv_range(start, end)
 *
 *      Invalidate (discard) the specified virtual address range.
 *      May not write back any entries.  If 'start' or 'end'
 *      are not cache line aligned, those lines must be written
 *      back.
 *
 *      - start - virtual start address
 *      - end   - virtual end address
 *
 * (same as v4wb)
ENTRY(arm926_dma_inv_range)
 */
asm("\n \
	.global arm926_dma_inv_range\n \
arm926_dma_inv_range:\n \
@        tst     r0, #CACHE_DLINESIZE - 1\n \
        tst     r0, #32 - 1\n \
        mcrne   p15, 0, r0, c7, c10, 1          @ clean D entry\n \
@        tst     r1, #CACHE_DLINESIZE - 1\n \
        tst     r1, #32 - 1\n \
        mcrne   p15, 0, r1, c7, c10, 1          @ clean D entry\n \
@        bic     r0, r0, #CACHE_DLINESIZE - 1\n \
        bic     r0, r0, #32 - 1\n \
1:      mcr     p15, 0, r0, c7, c6, 1           @ invalidate D entry\n \
@        add     r0, r0, #CACHE_DLINESIZE\n \
        add     r0, r0, #32\n \
        cmp     r0, r1\n \
        blo     1b\n \
        mcr     p15, 0, r0, c7, c10, 4          @ drain WB\n \
        mov     pc, lr\n \
");

/*
 *      dma_clean_range(start, end)
 *
 *      Clean the specified virtual address range.
 *
 *      - start - virtual start address
 *      - end   - virtual end address
 *
 * (same as v4wb)
ENTRY(arm926_dma_clean_range)
 */
asm("\n \
	.global arm926_dma_clean_range\n \
arm926_dma_clean_range:\n \
@        bic     r0, r0, #CACHE_DLINESIZE - 1\n \
        bic     r0, r0, #32 - 1\n \
1:      mcr     p15, 0, r0, c7, c10, 1          @ clean D entry\n \
@        add     r0, r0, #CACHE_DLINESIZE\n \
        add     r0, r0, #32\n \
        cmp     r0, r1\n \
        blo     1b\n \
        mcr     p15, 0, r0, c7, c10, 4          @ drain WB\n \
        mov     pc, lr\n \
");

/*
 *      dma_flush_range(start, end)
 *
 *      Clean and invalidate the specified virtual address range.
 *
 *      - start - virtual start address
 *      - end   - virtual end address
ENTRY(arm926_dma_flush_range)
 */
asm("\n \
	.global arm926_dma_flush_range\n \
arm926_dma_flush_range:\n \
@        bic     r0, r0, #CACHE_DLINESIZE - 1\n \
        bic     r0, r0, #32 - 1\n \
1:\n \
        mcr     p15, 0, r0, c7, c14, 1          @ clean+invalidate D entry\n \
@        add     r0, r0, #CACHE_DLINESIZE\n \
        add     r0, r0, #32\n \
        cmp     r0, r1\n \
        blo     1b\n \
        mcr     p15, 0, r0, c7, c10, 4          @ drain WB\n \
        mov     pc, lr\n \
");

#else  /* CONFIG_CPU_ARM926T */

/*
 *	v7_dma_inv_range(start,end)
 *
 *	Invalidate the data cache within the specified region; we will
 *	be performing a DMA operation in this region and we want to
 *	purge old data in the cache.
 *
 *	- start   - virtual start address of region
 *	- end     - virtual end address of region
 */
asm("\n \
	.global v7_dma_inv_range\n \
v7_dma_inv_range:\n \
@	dcache_line_size r2, r3\n \
        mrc     p15, 0, r3, c0, c0, 1         @ read ctr\n \
        lsr     r3, r3, #16\n \
        and     r3, r3, #0xf                @ cache line size encoding\n \
        mov     r2, #4                        @ bytes per word\n \
        mov     r2, r2, lsl r3            @ actual cache line size\n \
\n \
	sub	r3, r2, #1\n \
	tst	r0, r3\n \
	bic	r0, r0, r3\n \
@ #ifdef CONFIG_ARM_ERRATA_764369\n \
@ 	ALT_SMP(W(dsb))\n \
@ 	ALT_UP(W(nop))\n \
@ #endif\n \
	mcrne	p15, 0, r0, c7, c14, 1		@ clean & invalidate D / U line\n \
	tst	r1, r3\n \
	bic	r1, r1, r3\n \
	mcrne	p15, 0, r1, c7, c14, 1		@ clean & invalidate D / U line\n \
1:\n \
	mcr	p15, 0, r0, c7, c6, 1		@ invalidate D / U line\n \
	add	r0, r0, r2\n \
	cmp	r0, r1\n \
	blo	1b\n \
	dsb\n \
	mov	pc, lr\n \
");

/*
 *	v7_dma_clean_range(start,end)
 *	- start   - virtual start address of region
 *	- end     - virtual end address of region
 */
asm("\n \
	.global v7_dma_clean_range\n \
v7_dma_clean_range:\n \
@	dcache_line_size r2, r3\n \
        mrc     p15, 0, r3, c0, c0, 1         @ read ctr\n \
        lsr     r3, r3, #16\n \
        and     r3, r3, #0xf                @ cache line size encoding\n \
        mov     r2, #4                        @ bytes per word\n \
        mov     r2, r2, lsl r3            @ actual cache line size\n \
\n \
	sub	r3, r2, #1\n \
	bic	r0, r0, r3\n \
@ #ifdef CONFIG_ARM_ERRATA_764369\n \
@ 	ALT_SMP(W(dsb))\n \
@ 	ALT_UP(W(nop))\n \
@ #endif\n \
1:\n \
	mcr	p15, 0, r0, c7, c10, 1		@ clean D / U line\n \
	add	r0, r0, r2\n \
	cmp	r0, r1\n \
	blo	1b\n \
	dsb\n \
	mov	pc, lr\n \
");

/*
 *	v7_dma_flush_range(start,end)
 *	- start   - virtual start address of region
 *	- end     - virtual end address of region
 */
asm("\n \
	.global v7_dma_flush_range\n \
v7_dma_flush_range:\n \
@	dcache_line_size r2, r3\n \
        mrc     p15, 0, r3, c0, c0, 1         @ read ctr\n \
        lsr     r3, r3, #16\n \
        and     r3, r3, #0xf                @ cache line size encoding\n \
        mov     r2, #4                        @ bytes per word\n \
        mov     r2, r2, lsl r3            @ actual cache line size\n \
\n \
	sub	r3, r2, #1\n \
	bic	r0, r0, r3\n \
@ #ifdef CONFIG_ARM_ERRATA_764369\n \
@ 	ALT_SMP(W(dsb))\n \
@ 	ALT_UP(W(nop))\n \
@ #endif\n \
1:\n \
	mcr	p15, 0, r0, c7, c14, 1		@ clean & invalidate D / U line\n \
	add	r0, r0, r2\n \
	cmp	r0, r1\n \
	blo	1b\n \
	dsb\n \
	mov	pc, lr\n \
");

/*
 *	dma_map_area(start, size, dir)
 *	- start	- kernel virtual start address
 *	- size	- size of region
 *	- dir	- DMA direction
 */
asm("\n \
	.global v7_dma_map_area\n \
v7_dma_map_area:\n \
	add	r1, r1, r0\n \
@        cmp     r2, #DMA_TO_DEVICE\n \
        cmp     r2, #1\n \
        beq     v7_dma_clean_range\n \
        bcs     v7_dma_inv_range\n \
        b       v7_dma_flush_range\n \
");

/*
 *	dma_unmap_area(start, size, dir)
 *	- start	- kernel virtual start address
 *	- size	- size of region
 *	- dir	- DMA direction
 */
asm("\n \
	.global v7_dma_unmap_area\n \
v7_dma_unmap_area:\n \
	add	r1, r1, r0\n \
@	teq	r2, #DMA_TO_DEVICE\n \
	teq	r2, #1\n \
	bne	v7_dma_inv_range\n \
	mov	pc, lr\n \
");

#endif /* CONFIG_CPU_ARM926T */

#endif /* !defined(MULTI_CACHE) */

#endif /* dmac_map_range */
