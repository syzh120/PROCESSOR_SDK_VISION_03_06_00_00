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
           global int* inPtr,
           global int* outPtr,
           int rows,
           int cols,
           int inPitch,
           int outPitch
)
{
    int rowIdx;
    int colIdx;
    int height = rows;
    int wordWidth = cols;
    global int* inputPtr = inPtr;
    global int* outputPtr = outPtr;

    for(rowIdx = 0; rowIdx < height ; rowIdx++)
    {
        for(colIdx = 0; colIdx < wordWidth ; colIdx++)
        {
            *(outputPtr+colIdx) = *(inputPtr+colIdx);
        }
        inputPtr += (inPitch >> 2);
        outputPtr += (outPitch >> 2);
    }
}



