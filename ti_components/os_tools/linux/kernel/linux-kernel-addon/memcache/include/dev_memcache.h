/*
 *******************************************************************************
 *
 * Copyright (C) 2015 Texas Instruments Incorporated - http://www.ti.com/
 * ALL RIGHTS RESERVED
 *
 *******************************************************************************
 */

#ifndef _DEV_DMA_H_
#define _DEV_DMA_H_

#include <linux/ioctl.h>
#include <osa_dma.h>

#define DMA_DRV_NAME  "/dev/memcache"
//#define DMA_DEBUG

#define DMA_DRV_MAGICNUM       (0xDA)

#define DMA_CMD_MMAP           (0x07)
#define DMA_CMD_CACHEINV       (0x08)
#define DMA_CMD_CACHEWB        (0x09)

#define DMA_IOCTL_CMD_MAKE(cmd)     ( _IO( DMA_DRV_MAGICNUM, cmd) )
#define DMA_IOCTL_CMD_GET(cmd)      ( _IOC_NR(cmd) )
#define DMA_IOCTL_CMD_IS_VALID(cmd) ( (_IOC_TYPE(cmd) == DMA_DRV_MAGICNUM ) ? 1 : 0)

typedef struct {

  unsigned int physAddr;
  unsigned int size;
  unsigned int virtAddr;
  unsigned int mapType;

} DMA_MmapPrm;

typedef struct {

  unsigned int virtAddr;
  unsigned int physAddr;
  unsigned int size;

} DMA_CacheInvPrm;

typedef struct {

  unsigned int virtAddrStart;
  unsigned int virtAddrEnd;
  unsigned int physAddrStart;

} DMA_CacheWbPrm;

int  DMA_devInit(void);
void DMA_devExit(void);

#endif

