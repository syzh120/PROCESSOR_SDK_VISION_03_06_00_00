/*
 *  Copyright 2003 by Texas Instruments Incorporated.
 *  All rights reserved. Property of Texas Instruments Incorporated.
 *  Restricted rights to use, duplicate or disclose this code are
 *  granted through contract.
 *
 *  @(#) XDAS 2.51.00 11-29-2003 (xdas-2.50.00.9)
 */
/*
 *  ======== alg_control.c ========
 *  ALG_control implementation.  This is common to all implementations
 *  of the ALG module.
 */
/* #include <GenericComDataType.h>                                            */
/* #include <H264VEncDataTypes.h>                                             */
#include <xdc/std.h>
#include <ti/sdo/fc/utils/api/alg.h>
#include <ti/xdais/ialg.h>

/*
 *  ======== ALG_control ========
 */
Int ALG_control(ALG_Handle alg, IALG_Cmd cmd, IALG_Status * statusPtr)
{
  if (alg && alg->fxns->algControl) {
    return (alg->fxns->algControl(alg, cmd, statusPtr));
  }

  return (IALG_EFAIL);
}
