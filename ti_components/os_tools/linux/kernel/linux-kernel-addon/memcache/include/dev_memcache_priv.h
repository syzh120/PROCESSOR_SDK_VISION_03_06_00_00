/*
 *******************************************************************************
 *
 * Copyright (C) 2015 Texas Instruments Incorporated - http://www.ti.com/
 * ALL RIGHTS RESERVED
 *
 *******************************************************************************
 */

#ifndef _DEV_DMA_PRIV_H_
#define _DEV_DMA_PRIV_H_

#include <dev_memcache.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/fs.h>           /* everything... */
#include <linux/cdev.h>
#include <linux/mm.h>
#include <linux/interrupt.h>
#include <linux/kernel.h>       /* printk() */
#include <linux/slab.h>         /* kmalloc() */
#include <asm/uaccess.h>        /* copy_*_user */
#include <linux/platform_data/edma.h>
#include <asm/io.h>
#include <asm/cacheflush.h>
#include <linux/dma-mapping.h>

#ifdef DEBUG
#define FUNCDBG(format, a...) \
        printk( KERN_INFO "DRV :%s:%d: " format, __func__, __LINE__, ## a )
#else
#define FUNCDBG(...)
#endif

#define FUNCMSG(format, a...) \
        printk( KERN_INFO "DRV :%s:%d: " format, __func__, __LINE__, ## a )

#define FUNCERR(format, a...) \
    printk( KERN_ERR " DRV ERR :%s:%d: " format, __func__, __LINE__, ## a)

typedef struct {

  struct cdev cdev;             /* Char device structure    */
  int     major;
  struct semaphore semLock;
} DMA_Dev;

extern DMA_Dev gDMA_dev;

#endif /* _DEV_DMA_PRIV_H_  */

