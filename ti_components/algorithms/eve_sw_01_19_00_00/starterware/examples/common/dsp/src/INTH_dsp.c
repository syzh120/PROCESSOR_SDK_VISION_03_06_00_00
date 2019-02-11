/*
*
* Copyright (c) 2003-2017 Texas Instruments Incorporated
*
* All rights reserved not granted herein.
*
* Limited License.
*
* Texas Instruments Incorporated grants a world-wide, royalty-free, non-exclusive
* license under copyrights and patents it now or hereafter owns or controls to make,
* have made, use, import, offer to sell and sell ("Utilize") this software subject to the
* terms herein.  With respect to the foregoing patent license, such license is granted
* solely to the extent that any such patent is necessary to Utilize the software alone.
* The patent license shall not apply to any combinations which include this software,
* other than combinations with devices manufactured by or for TI ("TI Devices").
* No hardware patent is licensed hereunder.
*
* Redistributions must preserve existing copyright notices and reproduce this license
* (including the above copyright notice and the disclaimer and (if applicable) source
* code license limitations below) in the documentation and/or other materials provided
* with the distribution
*
* Redistribution and use in binary form, without modification, are permitted provided
* that the following conditions are met:
*
* *       No reverse engineering, decompilation, or disassembly of this software is
* permitted with respect to any software provided in binary form.
*
* *       any redistribution and use are licensed by TI for use only with TI Devices.
*
* *       Nothing shall obligate TI to provide you with source code for the software
* licensed and provided to you in object code.
*
* If software source code is provided to you, modification and redistribution of the
* source code are permitted provided that the following conditions are met:
*
* *       any redistribution and use of the source code, including any resulting derivative
* works, are licensed by TI for use only with TI Devices.
*
* *       any redistribution and use of any object code compiled from the source code
* and any resulting derivative works, are licensed by TI for use only with TI Devices.
*
* Neither the name of Texas Instruments Incorporated nor the names of its suppliers
*
* may be used to endorse or promote products derived from this software without
* specific prior written permission.
*
* DISCLAIMER.
*
* THIS SOFTWARE IS PROVIDED BY TI AND TI'S LICENSORS "AS IS" AND ANY EXPRESS
* OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
* OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
* IN NO EVENT SHALL TI AND TI'S LICENSORS BE LIABLE FOR ANY DIRECT, INDIRECT,
* INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
* BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
* DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY
* OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
* OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
* OF THE POSSIBILITY OF SUCH DAMAGE.
*
*/


/* ============================================================================
* STANDARD INCLUDE FILES
* =============================================================================
*/

/* ============================================================================
* PROJECT SPECIFIC INCLUDE FILES
* =============================================================================
*/
#include <c6x.h>

#include "GlobalTypes.h"
#include "baseaddress.h"
#include "common_utils.h"
#include "dsp_utils.h"
#include "ICRegAcM.h"
#include "INTH_dsp.h"          /* NOTE: Use header from common folder,    */
                           /*       since all functions are cross     */
                           /*       platform compatible               */


/* ============================================================================
* LOCAL TYPES AND DEFINITIONS
* =============================================================================
*/

  /* number of IVA2 interrupt handlers 0..127*/
  #define INTH_INT_TABLE_SIZE     128

  /* number of IVA2 interrupt handlers 0..95*/
  #define INTH_INT_NUM_MAX     INTH_INT_TABLE_SIZE - 1


/* ============================================================================
* GLOBAL VARIABLES DECLARATIONS
* =============================================================================
*/

    /* L2 Interrupt Vector Table */
    // #pragma DATA_SECTION ( inth_IrqHandler, ".l2_int" )
    INTH_Handler_t inth_IrqHandler[INTH_INT_TABLE_SIZE];

    UWORD32 INTH_intRouting[16];
//	UWORD32 INTH_combined[4];

    UWORD32 _ISR_Table[16] = {

           0x00000000, 0x00000000, 0x00000000, 0x00000000,
           0x00000000, 0x00000000, 0x00000000, 0x00000000,
           0x00000000, 0x00000000, 0x00000000, 0x00000000,
           0x00000000, 0x00000000, 0x00000000, 0x00000000
    };

		/* This is used but, referenced  from intvect.asm */
    UWORD32 IRQ_intTable[16];

/* ============================================================================
* LOCAL VARIABLES DECLARATIONS
* =============================================================================
*/

      /* array of interrupt counter */
      static UWORD32 inth_IrqCount[INTH_INT_TABLE_SIZE];


/* ============================================================================
* LOCAL FUNCTIONS PROTOTYPES
* =============================================================================
*/
void scanCombined( UWORD8 *intNo, UWORD32 flag, UWORD32 combNo );
//static inline ReturnCode_t IRQ_globalEnable();
static inline ReturnCode_t IRQ_globalDisable(UWORD32 *const gie);

interrupt void INTH_L1IRQ4Handler  (void);
interrupt void INTH_L1IRQ5Handler  (void);
interrupt void INTH_L1IRQ6Handler  (void);
interrupt void INTH_L1IRQ7Handler  (void);
interrupt void INTH_L1IRQ8Handler  (void);
interrupt void INTH_L1IRQ9Handler  (void);
interrupt void INTH_L1IRQ10Handler (void);
interrupt void INTH_L1IRQ11Handler (void);
interrupt void INTH_L1IRQ12Handler (void);
interrupt void INTH_L1IRQ13Handler (void);
interrupt void INTH_L1IRQ14Handler (void);
interrupt void INTH_L1IRQ15Handler (void);

/*==================== Function Separator =============================*/

ReturnCode_t EVE_HOST_INTH_InterruptSetup( const UWORD8               intVector,
                                  const INTH_Handler_t       intHandler,
                                  const INTH_InterruptKind_t intKind,
                                  const INTH_Priority_t      intPriority)
{

    ReturnCode_t returnCode;
    UWORD32      L1int;
    UWORD32      uTmp;
    UWORD32      pos;
    UWORD32      rgs;

    returnCode = RET_OK;
    L1int = 0;

    /* Setup Priority */
    if ( intPriority != INTH_DEFAULT_PRIORITY )
    {
        L1int = (UWORD32)intPriority;
        if ( (L1int < 8) ||
             (L1int > 15)   )
        {
            L1int = 0;
//            RES_Set(0x1000 | RES_BAD);
            returnCode = RET_FAIL;
        }
        else
        {
            if ( INTH_intRouting[L1int] )
            {
                L1int = 0;
//                RES_Set(0x1100 | RES_BAD);
                returnCode = RET_FAIL;
            }
            else
            {
                INTH_intRouting[L1int] = intVector;
            }
        }
    }

    if ( returnCode == RET_OK )
    {
        /* reset counter and install handler */
        inth_IrqCount[intVector] = 0;
        inth_IrqHandler[intVector] = intHandler;
    }

    /* Setup Mux */
    if ( L1int )
    {
        uTmp = L1int >> 2;
        pos  = L1int & 0x3;
        switch ( uTmp )
        {
            case 0:
                break;
            case 1:
                rgs = ICINTMUX1ReadRegister32( IC_U_BASE, 0 );
                rgs &= ~(0x7F << (pos * 8));
                rgs |= intVector << (pos * 8);
                ICINTMUX1WriteRegister32( IC_U_BASE, 0, rgs );
                break;
            case 2:
                rgs = ICINTMUX2ReadRegister32( IC_U_BASE, 0 );
                rgs &= ~(0x7F << (pos * 8));
                rgs |= intVector << (pos * 8);
                ICINTMUX2WriteRegister32( IC_U_BASE, 0, rgs );
                break;
            case 3:
                rgs = ICINTMUX3ReadRegister32( IC_U_BASE, 0 );
                rgs &= ~(0x7F << (pos * 8));
                rgs |= intVector << (pos * 8);
                ICINTMUX3WriteRegister32( IC_U_BASE, 0, rgs );
                break;
        }
    }

    return returnCode;

} /* EVE_HOST_INTH_InterruptSetup() */


/*==================== Function Separator =============================*/

ReturnCode_t EVE_HOST_INTH_InterruptEnable( const UWORD8 intVector)
{

    ReturnCode_t returnCode = RET_OK;
    UWORD32 intr;
    UWORD32 uTmp;
    UWORD32 rgs;

    for ( intr = 4; intr < 16; intr ++ )
    {
        if ( INTH_intRouting[intr] == intVector )
        {
            IER |= 1 << intr;
               return returnCode;
        }
    }

    uTmp = intVector >> 5;
    switch ( uTmp )
    {
        case 0:
            rgs = ICEVTMASK0ReadRegister32( IC_U_BASE, 0 );
            rgs &= ~( 1 << (intVector & 0x1F) );
            ICEVTMASK0WriteRegister32(IC_U_BASE, 0, rgs );
            break;
        case 1:
            rgs = ICEVTMASK1ReadRegister32( IC_U_BASE, 0 );
            rgs &= ~( 1 << (intVector & 0x1F) );
            ICEVTMASK1WriteRegister32(IC_U_BASE, 0, rgs );
            break;
        case 2:
            rgs = ICEVTMASK2ReadRegister32( IC_U_BASE, 0 );
            rgs &= ~( 1 << (intVector & 0x1F) );
            ICEVTMASK2WriteRegister32(IC_U_BASE, 0, rgs );
            break;
        case 3:
            rgs = ICEVTMASK3ReadRegister32( IC_U_BASE, 0 );
            rgs &= ~( 1 << (intVector & 0x1F ));
            ICEVTMASK3WriteRegister32(IC_U_BASE, 0, rgs );
            break;
        default:
//            RES_Set(RES_BAD);
            returnCode = RET_FAIL;
            break;
    }

    return returnCode;

} /* EVE_HOST_INTH_InterruptEnable() */


/*==================== Function Separator =============================*/

ReturnCode_t EVE_HOST_INTH_InterruptDisable( const UWORD8 intVector)
{

    ReturnCode_t returnCode = RET_OK;
    UWORD32 intr;
    UWORD32 uTmp;
    UWORD32 rgs;

    for ( intr = 4; intr < 16; intr ++ )
    {
        if ( INTH_intRouting[intr] == intVector )
        {
            IER &= ~(1 << intr);
            return returnCode;
        }
    }

    uTmp = intVector >> 5;
    switch ( uTmp )
    {
        case 0:
            rgs = ICEVTMASK0ReadRegister32( IC_U_BASE, 0 );
            rgs |= 1 << (intVector & 0x1F);
            ICEVTMASK0WriteRegister32(IC_U_BASE, 0, rgs );
            break;
        case 1:
            rgs = ICEVTMASK1ReadRegister32( IC_U_BASE, 0 );
            rgs |= 1 << (intVector & 0x1F);
            ICEVTMASK1WriteRegister32(IC_U_BASE, 0, rgs );
            break;
        case 2:
            rgs = ICEVTMASK2ReadRegister32( IC_U_BASE, 0 );
            rgs |= 1 << (intVector & 0x1F);
            ICEVTMASK2WriteRegister32(IC_U_BASE, 0, rgs );
            break;
        case 3:
            rgs = ICEVTMASK3ReadRegister32( IC_U_BASE, 0 );
            rgs |= 1 << (intVector & 0x1F);
            ICEVTMASK3WriteRegister32(IC_U_BASE, 0, rgs );
            break;
        default:
//            RES_Set(RES_BAD);
            returnCode = RET_FAIL;
            break;
    }



    return returnCode;

} /* EVE_HOST_INTH_InterruptDisable() */



/*==================== Function Separator =============================*/
ReturnCode_t EVE_HOST_INTH_IntCountGet( const UWORD8   intVector,
                               UWORD32 *const pIntCount  )
{

    ReturnCode_t returnCode = RET_OK;

//    CHECK_INPUT_PARAM(pIntCount, NULL, RET_BAD_NULL_PARAM, RES_INTH_BASE + RES_INVALID_INPUT_PARAM);

//    CHECK_INPUT_RANGE_MIN0(intVector, INTH_INT_NUM_MAX, RET_INVALID_ID, RES_INTH_BASE + RES_INVALID_INPUT_PARAM);

    /* return count value */
    *pIntCount = inth_IrqCount[intVector];

    return returnCode;

} /* INTH_GetIntCount() */


/*==================== Function Separator =============================*/

ReturnCode_t EVE_HOST_INTH_IntCountClear( const UWORD8 intVector )
{

    ReturnCode_t returnCode = RET_OK;

//    CHECK_INPUT_RANGE_MIN0(intVector, INTH_INT_NUM_MAX, RET_INVALID_ID, RES_INTH_BASE + RES_INVALID_INPUT_PARAM);

    /* return count value */
    inth_IrqCount[intVector] = 0;

    return returnCode;

} /* INTH_ClearIntCount() */


/*==================== Function Separator =============================*/
void INTH_IRQHandler( UWORD8 L1intNumber )

{

    UWORD8  intNumber[32];

    UWORD32 FlagLatch;
	UWORD32 pass;

    intNumber[0] = 0;

    switch ( L1intNumber )
    {
	    case 4:
		    FlagLatch = ICMEVTFLAG0ReadRegister32( IC_U_BASE ,0 );
			ICEVTCLR0WriteRegister32(IC_U_BASE, 0, FlagLatch);
		    scanCombined(intNumber, FlagLatch, 0);
            break;
		case 5:
            FlagLatch = ICMEVTFLAG1ReadRegister32( IC_U_BASE ,0 );
            ICEVTCLR1WriteRegister32(IC_U_BASE, 0, FlagLatch);
            scanCombined(intNumber, FlagLatch, 1);
            break;
        case 6:
            FlagLatch = ICMEVTFLAG2ReadRegister32( IC_U_BASE ,0 );
		    ICEVTCLR2WriteRegister32(IC_U_BASE, 0, FlagLatch);
		    scanCombined(intNumber, FlagLatch, 2);
		    break;
		case 7:
		    FlagLatch = ICMEVTFLAG3ReadRegister32( IC_U_BASE ,0 );
		    ICEVTCLR3WriteRegister32(IC_U_BASE, 0, FlagLatch);
		    scanCombined(intNumber, FlagLatch, 3);
		    break;
		default:
			intNumber[0] = INTH_intRouting[L1intNumber];
			intNumber[1] = 0;
			pass = intNumber[0] >> 5;
			ICEVTCLR0WriteRegister32(IC_U_BASE + pass * 4, 0,
					                 1 << (intNumber[0] - ( pass << 5 )) );
			break;
	}


    /* Process all active interrupts */
	pass = 0;
	while (	 intNumber[pass] ) {
        /* increment interrupt counter */
        inth_IrqCount[intNumber[pass]]++;

        if (inth_IrqHandler[intNumber[pass]])
        {
            /* call regitered interrupt handler */
            inth_IrqHandler[intNumber[pass]](intNumber[pass]);
        }

		pass ++;
    }

    /* Clear Combined Event Flag */
	if ( L1intNumber < 8 )
	{
	    ICEVTCLR0WriteRegister32(IC_U_BASE, 0, 1 << L1intNumber );
	}


}  /* INTH_IRQHandler() */


/*==================== Function Separator =============================*/
/*
   Function removes IRQ Entry from INTH_intRouting[] table and
   uninitializes IRQ Handler.
*/
ReturnCode_t EVE_HOST_INTH_InterruptUninstall( const UWORD8 intVector )
{
    UWORD32      L1int;


    /* Find and clean interrupt entry in INTH_intRouting table */
    for (L1int = 8; L1int<16; L1int++)
    {
       if (INTH_intRouting[L1int] == intVector)
       {
          /*reset interrupt routing entry*/
          INTH_intRouting[L1int] = 0;

          /*reset counter and deinstall handler*/
          inth_IrqCount[intVector] = 0;
          inth_IrqHandler[intVector] = NULL;

          return RET_OK;
       }
    }

    return RET_FAIL;
} /* EVE_HOST_INTH_InterruptSetup() */


/* ============================================================================
* LOCAL FUNCTIONS
* =============================================================================
*/

/*==================== Function Separator =============================*/
void scanCombined( UWORD8 *intNo, UWORD32 flag, UWORD32 combNo)
{

    UWORD32 i, count;

    count = 0;
    for ( i = 0; i < 32; i ++ )
    {
	    if ( flag & ( 1 << i ) )
		{
		    intNo[count++] = i + combNo * 32;
		}
    }

    intNo[count] = 0;

} /* scanCombined() */


/*==================== Function Separator =============================*/

void INTH_Init(void)
{

    UWORD32 count;
		UWORD32 mask;

    /* Now, enable the 4,5,6, and 7 bits of IER
		   These involve the default priority mode which uses the interrupt
			 combiner */

    mask = 0x000000f2;
	IER |= mask;

   /* Clear all entries in L2 interrupt handler */
    for ( count = 0; count < INTH_INT_TABLE_SIZE; count ++ )
	  {
        inth_IrqHandler[count] = NULL;
    }

    /* Clear Routing Table */
    for ( count = 0; count < 16; count ++ )
	  {
	      INTH_intRouting[count] = 0;
	  }


    /* Route combined inputs */
    INTH_intRouting[4] = INTH_INT_ID_EVT0;
    INTH_intRouting[5] = INTH_INT_ID_EVT1;
    INTH_intRouting[6] = INTH_INT_ID_EVT2;
    INTH_intRouting[7] = INTH_INT_ID_EVT3;

    /* Configure IC */
    /* Remove all inputs from combiner */
    ICEVTMASK0WriteRegister32(IC_U_BASE, 0, 0xFFFFFFFF );
    ICEVTMASK1WriteRegister32(IC_U_BASE, 0, 0xFFFFFFFF );
    ICEVTMASK2WriteRegister32(IC_U_BASE, 0, 0xFFFFFFFF );
    ICEVTMASK3WriteRegister32(IC_U_BASE, 0, 0xFFFFFFFF );

    /* Program the interrupt selector here,
		   the first 4 interrupt output of the interrupt selector is
			 routed from the interrupt combiner
			 Each of these interrupt line cater to 32 event input lines
			 Below is the mapping -
			 0 bit -> 0-31 event lines
			 1 bit -> 32-63 event lines
			 2 bit -> 64-95 event lines
			 3 bit -> 96-127 event lines
			 */
    ICINTMUX1WriteRegister32( IC_U_BASE, 0, 0x03020100 );
    /* Route unused EVT 119 to other interrupt inputs */
    ICINTMUX2WriteRegister32( IC_U_BASE, 0, 0x77777777 );
    ICINTMUX3WriteRegister32( IC_U_BASE, 0, 0x77777777 );

    /* Clear Dropped interrupts */
    ICINTXCLRWriteRegister32( IC_U_BASE, 0, 1 );

    /* Enable NMI */
//    __nmiEnable;

    /* Enable Combiner Interrupts */
    EVE_HOST_INTH_InterruptEnable( INTH_INT_ID_EVT0 );
    EVE_HOST_INTH_InterruptEnable( INTH_INT_ID_EVT1 );
    EVE_HOST_INTH_InterruptEnable( INTH_INT_ID_EVT2 );
    EVE_HOST_INTH_InterruptEnable( INTH_INT_ID_EVT3 );

	_ISR_Table[4]   =  (UWORD32)INTH_L1IRQ4Handler;
	_ISR_Table[5]   =  (UWORD32)INTH_L1IRQ5Handler;
	_ISR_Table[6]   =  (UWORD32)INTH_L1IRQ6Handler;
    _ISR_Table[7]   =  (UWORD32)INTH_L1IRQ7Handler;
    _ISR_Table[8]   =  (UWORD32)INTH_L1IRQ8Handler;
    _ISR_Table[9]   =  (UWORD32)INTH_L1IRQ9Handler;
    _ISR_Table[10]  =  (UWORD32)INTH_L1IRQ10Handler;
    _ISR_Table[11]  =  (UWORD32)INTH_L1IRQ11Handler;
    _ISR_Table[12]  =  (UWORD32)INTH_L1IRQ12Handler;
    _ISR_Table[13]  =  (UWORD32)INTH_L1IRQ13Handler;
    _ISR_Table[14]  =  (UWORD32)INTH_L1IRQ14Handler;
    _ISR_Table[15]  =  (UWORD32)INTH_L1IRQ15Handler;

    /* Enable the Global Interrupt Enable bit in CSR register of GEM*/
    CSR |= 0x00000001;


} /* INTH_InitIntTable() */

interrupt void INTH_L1IRQ4Handler (void) {
    UWORD32 gie;
	  IRQ_globalDisable(&gie);
	  INTH_IRQHandler(4);
 //   IRQ_globalEnable();
    return;
}

interrupt void INTH_L1IRQ5Handler (void) {
    UWORD32 gie;
	  IRQ_globalDisable(&gie);
	  INTH_IRQHandler(5);
   // IRQ_globalEnable();
    return;
}

interrupt void INTH_L1IRQ6Handler (void) {
    UWORD32 gie;
	  IRQ_globalDisable(&gie);
	  INTH_IRQHandler(6);
  //  IRQ_globalEnable();
    return;
}

interrupt void INTH_L1IRQ7Handler (void) {
    UWORD32 gie;
	  IRQ_globalDisable(&gie);
	  INTH_IRQHandler(7);
  ///  IRQ_globalEnable();
    return;
}

interrupt void INTH_L1IRQ8Handler (void) {
    UWORD32 gie;
	  IRQ_globalDisable(&gie);
	  INTH_IRQHandler(8);
   // IRQ_globalEnable();
    return;
}

interrupt void INTH_L1IRQ9Handler (void) {
    UWORD32 gie;
	  IRQ_globalDisable(&gie);
	  INTH_IRQHandler(9);
   // IRQ_globalEnable();
    return;
}


interrupt void INTH_L1IRQ10Handler (void) {
    UWORD32 gie;
	  IRQ_globalDisable(&gie);
	  INTH_IRQHandler(10);
   // IRQ_globalEnable();
    return;
}

interrupt void INTH_L1IRQ11Handler (void) {
    UWORD32 gie;
	  IRQ_globalDisable(&gie);
	  INTH_IRQHandler(11);
   // IRQ_globalEnable();
    return;
}


interrupt void INTH_L1IRQ12Handler (void) {
    UWORD32 gie;
	  IRQ_globalDisable(&gie);
	  INTH_IRQHandler(12);
   // IRQ_globalEnable();
    return;
}


interrupt void INTH_L1IRQ13Handler (void) {
    UWORD32 gie;
	  IRQ_globalDisable(&gie);
	  INTH_IRQHandler(13);
   // IRQ_globalEnable();
    return;
}


interrupt void INTH_L1IRQ14Handler (void) {
    UWORD32 gie;
	  IRQ_globalDisable(&gie);
	  INTH_IRQHandler(14);
//    IRQ_globalEnable();
    return;
}


interrupt void INTH_L1IRQ15Handler (void) {
    UWORD32 gie;
	  IRQ_globalDisable(&gie);
	  INTH_IRQHandler(15);
  //  IRQ_globalEnable();
    return;
}

/*
static inline ReturnCode_t IRQ_globalEnable() {
  CSR |= 0x00000001;
  CHIP_FSET(CSR,GIE,1);
  return RET_OK;
}
*/

static inline ReturnCode_t IRQ_globalDisable(UWORD32 *gie) {

	*gie =  CSR & 0x1;
  CSR &= ~0x00000001;
  return RET_OK;
}



/* EOF */
