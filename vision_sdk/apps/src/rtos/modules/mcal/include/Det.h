/* ======================================================================
 *   Copyright (C) 2015-2017 Texas Instruments Incorporated
 *
 *   All rights reserved. Property of Texas Instruments Incorporated.
 *   Restricted rights to use, duplicate or disclose this code are
 *   granted through contract.
 *
 *   The program may not be used without the written permission
 *   of Texas Instruments Incorporated or against the terms and conditions
 *   stipulated in the agreement under which this program has been
 *   supplied.
 * ==================================================================== */

/**
 *  \file     MemMap.h
 *
 *  \brief    This file contains cover page for generating doxygen
 *            API documentation.
 */

/*
 * Development Error Tracer driver
 *
 */

#ifndef DET_H
#define DET_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "Std_Types.h"
/*TI_INSPECTED 63 D : MISRAC_2012_R8.6
 * "Reason - Definition for below prototyped procedure
 *  is external to lib, defined in app." */
Std_ReturnType Det_ReportError(uint16 ModuleId, uint8 InstanceId, uint8 ApiId,
                               uint8 ErrorId);
#ifdef __cplusplus
}
#endif

#endif /*DET_H*/
