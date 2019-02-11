/*
 *******************************************************************************
 *
 * Copyright (C) 2013 Texas Instruments Incorporated - http://www.ti.com/
 * ALL RIGHTS RESERVED
 *
 *******************************************************************************
 */
/*__attribute__((reqd_work_group_size(1,1,1))) */
#include "edmamgr.h"
kernel
void Copy(
           global int4* inPtr,
           global int4* outPtr,
           int rows,
           int cols,
           int inPitch,
           int outPitch
)
{
#ifndef EDMA_COPY
	int gidx = get_global_id(0);
	int gidy = get_global_id(1);

    {
    outPtr[gidx+gidy*outPitch] = inPtr[gidx+gidy*inPitch];
    }
#else

	EdmaMgr_Handle ev=EdmaMgr_alloc(1);

    EdmaMgr_copy1D1D(ev, (void*)(inPtr),
    (void*)(outPtr), (cols << 2)*rows);
    EdmaMgr_wait(ev);
    EdmaMgr_free(ev);
#endif

}



