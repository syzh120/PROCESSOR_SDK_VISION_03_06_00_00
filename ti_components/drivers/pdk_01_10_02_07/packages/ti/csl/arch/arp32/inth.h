/*
 *  Copyright (C) 2014-2018 Texas Instruments Incorporated - http://www.ti.com/
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions
 *  are met:
 *
 *    Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 *    Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the
 *    distribution.
 *
 *    Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 *  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 *  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 *  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 *  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 *  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 *  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 *  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */
/**
 *  \file  inth.h
 *
 *  \brief INTH library specifies all the interrupts and API's for
 *         interrupt handling such as interrupt set up, enable & disable.
 */

#ifndef INTH_H
#define INTH_H

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <ti/csl/arch/arp32/interrupt.h>

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */

/**
 * \brief   function pointer to interrupt handlers
 *
 * \param   None
 *
 * \return  None
 *
 **/

typedef void (*INTH_Handler_t)(uint32_t parm1);

/**
 * \brief Specifies the type of interrupt
 */
typedef enum INTH_Type_label
{
    INTH_TYPE_MAX1 = 0   /*this should not be used any more */

} INTH_Type_t, *pINTH_Type_t;    /**< INTH_Type_t, *pINTH_Type_t */

/**
 * \brief Copy from INTCTL
 */
typedef enum INTH_InterruptKind_label
{
    INTH_TYPE_IRQ = 0,                            /**< IRQ */
    INTH_TYPE_FIQ = 1,                            /**< FIQ */
    INTH_TYPE_MAX = INTH_TYPE_FIQ                 /**< Max for interrupt type */
} INTH_InterruptKind_t;


/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

#define INTH_DEFAULT_INTERRUPT_KIND     (INTH_TYPE_IRQ)    /**< INTH_TYPE_IRQ */
#define INTH_DEFAULT_PRIORITY           (INTH_INT4)        /**< INTH_INT4     */

#define EVE_INT00             0             /**< event - EVE_INT00           */
#define EVE_INT01             1             /**< event - EVE_INT01           */
#define EVE_INT02             2             /**< event - EVE_INT02           */
#define EVE_INT03             3             /**< event - EVE_INT03           */
#define EVE_INT04             4             /**< event - EVE_INT04           */
#define EVE_INT05             5             /**< event - EVE_INT05           */
#define EVE_INT06             6             /**< event - EVE_INT06           */
#define EVE_INT07             7             /**< event - EVE_INT07           */
#define TPCC_INTG             8             /**< event - TPCC_INTG           */
#define TPCC_INT0             9             /**< event - TPCC_INT0           */
#define TPCC_INT1            10             /**< event - TPCC_INT1           */
#define TPCC_INT2            11             /**< event - TPCC_INT2           */
#define TPCC_INT3            12             /**< event - TPCC_INT3           */
#define TPCC_INT4            13             /**< event - TPCC_INT4           */
#define TPCC_INT5            14             /**< event - TPCC_INT5           */
#define TPCC_INT6            15             /**< event - TPCC_INT6           */
#define TPCC_INT7            16             /**< event - TPCC_INT7           */
#define SCTM_TIMEVNTINT0     17             /**< event - SCTM_TIMEVNTINT0    */
#define SCTM_TIMEVNTINT1     18             /**< event - SCTM_TIMEVNTINT1    */
#define VCOP_DONE            19             /**< event - VCOP_DONE           */
#define VCOP_ERR_INT         20             /**< event - VCOP_ERR_INT        */
#define MMU0_INT             21             /**< event - MMU0_INT            */
#define MMU1_INT             22             /**< event - MMU1_INT            */
#define TPCC_ERRINT          23             /**< event - TPCC_ERRINT         */
#define TPTC_ERRINT0         24             /**< event - TPTC_ERRINT0        */
#define TPTC_ERRINT1         25             /**< event - TPTC_ERRINT1        */
#define NOC_ERRINT           26             /**< event - NOC_ERRINT          */
#define EVE_MSW_ERR_INT      27             /**< event - EVE_MSW_ERR_INT     */
#define EVE_ED_ERR_INT       28             /**< event - EVE_ED_ERR_INT      */
#define MLB0_INT             29             /**< event - MLB0_INT            */
#define MLB1_INT             30             /**< event - MLB1_INT            */
#define RESERVED0            31             /**< event - RESERVED0           */

#define EVE_EVT_INT0         32             /**< event - EVE_EVT_INT0        */
#define EVE_EVT_INT1         33             /**< event - EVE_EVT_INT1        */
#define EVE_EVT_INT2         34             /**< event - EVE_EVT_INT2        */
#define EVE_EVT_INT3         35             /**< event - EVE_EVT_INT3        */
#define EVE_EVT_INT4         36             /**< event - EVE_EVT_INT4        */
#define EVE_EVT_INT5         37             /**< event - EVE_EVT_INT5        */
#define EVE_EVT_INT6         38             /**< event - EVE_EVT_INT6        */
#define EVE_EVT_INT7         39             /**< event - EVE_EVT_INT7        */
#define EVE_EVT_INT8         40             /**< event - EVE_EVT_INT8        */
#define EVE_EVT_INT9         41             /**< event - EVE_EVT_INT9        */
#define EVE_EVT_INT10        42             /**< event - EVE_EVT_INT10       */
#define EVE_EVT_INT11        43             /**< event - EVE_EVT_INT11       */
#define EVE_EVT_INT12        44             /**< event - EVE_EVT_INT12       */
#define EVE_EVT_INT13        45             /**< event - EVE_EVT_INT13       */
#define EVE_EVT_INT14        46             /**< event - EVE_EVT_INT14       */
#define EVE_EVT_INT15        47             /**< event - EVE_EVT_INT15       */
#define EVE_INT1_0           48             /**< event - EVE_INT1_0          */
#define EVE_INT1_1           49             /**< event - EVE_INT1_1          */
#define EVE_INT1_2           50             /**< event - EVE_INT1_2          */
#define EVE_INT1_3           51             /**< event - EVE_INT1_3          */
#define EVE_INT1_4           52             /**< event - EVE_INT1_4          */
#define EVE_INT1_5           53             /**< event - EVE_INT1_5          */
#define EVE_INT1_6           54             /**< event - EVE_INT1_6          */
#define EVE_INT1_7           55             /**< event - EVE_INT1_7          */
#define EVE_INT1_8           56             /**< event - EVE_INT1_8          */
#define EVE_INT1_9           57             /**< event - EVE_INT1_9          */
#define EVE_INT1_10          58             /**< event - EVE_INT1_10         */
#define EVE_INT1_11          59             /**< event - EVE_INT1_11         */
#define MLB2_INT             60             /**< event - MLB2_INT            */
#define MLB3_INT             61             /**< event - MLB3_INT            */
#define MLB4_INT             62             /**< event - MLB4_INT            */
#define RESERVED1            63             /**< event - RESERVED1           */

#define EVE_GPIN_0           64             /**< event - EVE_GPIN_0          */
#define EVE_GPIN_1           65             /**< event - EVE_GPIN_1          */
#define EVE_GPIN_2           66             /**< event - EVE_GPIN_2          */
#define EVE_GPIN_3           67             /**< event - EVE_GPIN_3          */
#define EVE_GPIN_4           68             /**< event - EVE_GPIN_4          */
#define EVE_GPIN_5           69             /**< event - EVE_GPIN_5          */
#define EVE_GPIN_6           70             /**< event - EVE_GPIN_6          */
#define EVE_GPIN_7           71             /**< event - EVE_GPIN_7          */
#define EVE_GPIN_8           72             /**< event - EVE_GPIN_8          */
#define EVE_GPIN_9           73             /**< event - EVE_GPIN_9          */
#define EVE_GPIN_10          74             /**< event - EVE_GPIN_10         */
#define EVE_GPIN_11          75             /**< event - EVE_GPIN_11         */
#define EVE_GPIN_12          76             /**< event - EVE_GPIN_12         */
#define EVE_GPIN_13          77             /**< event - EVE_GPIN_13         */
#define EVE_GPIN_14          78             /**< event - EVE_GPIN_14         */
#define EVE_GPIN_15          79             /**< event - EVE_GPIN_15         */
#define EVE_GPIN_16          80             /**< event - EVE_GPIN_16         */
#define EVE_GPIN_17          81             /**< event - EVE_GPIN_17         */
#define EVE_GPIN_18          82             /**< event - EVE_GPIN_18         */
#define EVE_GPIN_19          83             /**< event - EVE_GPIN_19         */
#define EVE_GPIN_20          84             /**< event - EVE_GPIN_20         */
#define EVE_GPIN_21          85             /**< event - EVE_GPIN_21         */
#define EVE_GPIN_22          86             /**< event - EVE_GPIN_22         */
#define EVE_GPIN_23          87             /**< event - EVE_GPIN_23         */
#define EVE_GPIN_24          88             /**< event - EVE_GPIN_24         */
#define EVE_GPIN_25          89             /**< event - EVE_GPIN_25         */
#define EVE_GPIN_26          90             /**< event - EVE_GPIN_26         */
#define EVE_GPIN_27          91             /**< event - EVE_GPIN_27         */
#define EVE_GPIN_28          92             /**< event - EVE_GPIN_28         */
#define EVE_GPIN_29          93             /**< event - EVE_GPIN_29         */
#define EVE_GPIN_30          94             /**< event - EVE_GPIN_30         */
#define EVE_GPIN_31          95             /**< event - EVE_GPIN_31         */

#define EVE_GPIN_32          96             /**< event - EVE_GPIN_32         */
#define EVE_GPIN_33          97             /**< event - EVE_GPIN_33         */
#define EVE_GPIN_34          98             /**< event - EVE_GPIN_34         */
#define EVE_GPIN_35          99             /**< event - EVE_GPIN_35         */
#define EVE_GPIN_36         100             /**< event - EVE_GPIN_36         */
#define EVE_GPIN_37         101             /**< event - EVE_GPIN_37         */
#define EVE_GPIN_38         102             /**< event - EVE_GPIN_38         */
#define EVE_GPIN_39         103             /**< event - EVE_GPIN_39         */
#define EVE_GPIN_40         104             /**< event - EVE_GPIN_40         */
#define EVE_GPIN_41         105             /**< event - EVE_GPIN_41         */
#define EVE_GPIN_42         106             /**< event - EVE_GPIN_42         */
#define EVE_GPIN_43         107             /**< event - EVE_GPIN_43         */
#define EVE_GPIN_44         108             /**< event - EVE_GPIN_44         */
#define EVE_GPIN_45         109             /**< event - EVE_GPIN_45         */
#define EVE_GPIN_46         110             /**< event - EVE_GPIN_46         */
#define EVE_GPIN_47         111             /**< event - EVE_GPIN_47         */
#define EVE_GPIN_48         112             /**< event - EVE_GPIN_48         */
#define EVE_GPIN_49         113             /**< event - EVE_GPIN_49         */
#define EVE_GPIN_50         114             /**< event - EVE_GPIN_50         */
#define EVE_GPIN_51         115             /**< event - EVE_GPIN_51         */
#define EVE_GPIN_52         116             /**< event - EVE_GPIN_52         */
#define EVE_GPIN_53         117             /**< event - EVE_GPIN_53         */
#define EVE_GPIN_54         118             /**< event - EVE_GPIN_54         */
#define EVE_GPIN_55         119             /**< event - EVE_GPIN_55         */
#define EVE_GPIN_56         120             /**< event - EVE_GPIN_56         */
#define EVE_GPIN_57         121             /**< event - EVE_GPIN_57         */
#define EVE_GPIN_58         122             /**< event - EVE_GPIN_58         */
#define EVE_GPIN_59         123             /**< event - EVE_GPIN_59         */
#define EVE_GPIN_60         124             /**< event - EVE_GPIN_60         */
#define EVE_GPIN_61         125             /**< event - EVE_GPIN_61         */
#define EVE_GPIN_62         126             /**< event - EVE_GPIN_62         */
#define EVE_GPIN_63         127             /**< event - EVE_GPIN_63         */

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/**
 * \brief   Set up the interrupt
 *
 * \param   intVector      interrupt vector
 *          intHandler     interrupt handler pointer
 *          intKind        interrupt type
 *          intPriority    interrupt priority
 *
 * \return  Returns whether the passed parameter is OK or NOT
 *                    STW_SOK                  No errors
 *                    STW_EFAIL                Bad Parameter passed
 *
 **/
int32_t EVE_INTH_InterruptSetup( const uint8_t               intVector,
                                  const uint32_t       intHandler,
                                  const INTH_InterruptKind_t intKind,
                                  const INTH_Priority_t      intPriority);

/**
 * \brief   Enable the interrupt
 *
 * \param   intVector      interrupt vector
 *
 * \return  Returns whether the passed parameter is OK or NOT
 *                    STW_SOK                  No errors
 *                    STW_EFAIL                Bad Parameter passed
 *
 **/
int32_t EVE_INTH_InterruptEnable( const uint8_t   intVector);

/**
 * \brief   Disable the interrupt
 *
 * \param   intVector      interrupt vector
 *
 * \return  Returns whether the passed parameter is OK or NOT
 *                    STW_SOK                  No errors
 *                    STW_EFAIL                Bad Parameter passed
 *
 **/
int32_t EVE_INTH_InterruptDisable( const uint8_t   intVector);

/**
 * \brief   Enable interrupt handler lock
 *
 * \param   Null
 *
 * \return  Null
 *
 **/
void EVE_INTH_LockEnable(void);

/**
 * \brief   Register interrupt handler
 *
 * \param   intVector  interrupt number
 * \param   intHandler interrupt handler function
 * \param   arg argument to interrupt handler
 *
 * \return  Null
 *
 **/
void EVE_INTH_InterruptRegister(const uint8_t  intVector,
                                const uint32_t intHandler,
                                const void *   arg);

/**
 * \brief   Unregister interrupt handler
 *
 * \param   intVector  interrupt number
 *
 * \return  Null
 *
 **/
void EVE_INTH_InterruptUnregister(const uint8_t intVector);

/**
 * \brief   Set interrupt priority
 *
 * \param   intVector  interrupt number
 * \param   intPriority interrupt priority
 *
 * \return  Null
 *
 **/

void EVE_INTH_InterruptPrioritySet(uint16_t intVector,
                                   uint16_t intPriority);


#ifdef __cplusplus
}
#endif

#endif    /* INTH_H */
