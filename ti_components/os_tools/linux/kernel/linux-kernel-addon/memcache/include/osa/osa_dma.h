/*
 *******************************************************************************
 *
 * Copyright (C) 2015 Texas Instruments Incorporated - http://www.ti.com/
 * ALL RIGHTS RESERVED
 *
 *******************************************************************************
 */

#ifndef _OSA_DMA_H_
#define _OSA_DMA_H_

#define OSA_DMA_MMAP_TYPE_NOCACHE           (0)
#define OSA_DMA_MMAP_TYPE_CACHE             (1)
#define OSA_DMA_MMAP_TYPE_WRITE_COMBINED    (2)

#ifndef KERNEL_LEVEL
int OSA_dmaInit();
int OSA_dmaExit();

unsigned char *OSA_dmaMapMem(unsigned char *physAddr, unsigned int size, unsigned int mapType);
int OSA_dmaUnmapMem(unsigned char *virtAddr, unsigned int size);
#endif

#endif  /* _OSA_DMA_H_ */

