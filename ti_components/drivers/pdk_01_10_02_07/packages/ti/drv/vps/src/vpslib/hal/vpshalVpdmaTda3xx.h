/* =============================================================================
 *   Copyright (c) Texas Instruments Incorporated 2013-2015
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
 */

/**
 * \file vpshalVpdmaTda3xx.h
 *
 * \brief VPS VPDMA HAL header file
 * This file exposes the HAL APIs of the VPS VPDMA.
 *
 */

#ifndef VPSHAL_VPDMA_TDA3XX_H_
#define VPSHAL_VPDMA_TDA3XX_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

/* None */

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/**
 *  Enum for channel numbers. These channel numbers will be directly
 *  used by the list manager clients to configure data descriptor
 */
typedef enum
{
    VPSHAL_VPDMA_CHANNEL_INVALID             = (-(int32_t)1),
    VPSHAL_VPDMA_CHANNEL_PRI_LUMA            = 0,       /* 0   */
    VPSHAL_VPDMA_CHANNEL_PRI_CHROMA          = 1,       /* 1   */
    VPSHAL_VPDMA_CHANNEL_PRI_FLD1_LUMA       = 2,       /* 2   */
    VPSHAL_VPDMA_CHANNEL_PRI_FLD1_CHROMA     = 3,       /* 3   */
    VPSHAL_VPDMA_CHANNEL_PRI_FLD2_LUMA       = 4,       /* 4   */
    VPSHAL_VPDMA_CHANNEL_PRI_FLD2_CHROMA     = 5,       /* 5   */
    VPSHAL_VPDMA_CHANNEL_PRI_MV0             = 12,      /* 12  */
    VPSHAL_VPDMA_CHANNEL_PRI_MV_OUT          = 15,      /* 15  */
    VPSHAL_VPDMA_CHANNEL_WB0                 = 17,      /* 17  */
    VPSHAL_VPDMA_CHANNEL_S0_MULT_PORTA_SRC0  = 38,      /* 38  */
    VPSHAL_VPDMA_CHANNEL_S0_MULT_PORTA_SRC1  = 39,      /* 39  */
    VPSHAL_VPDMA_CHANNEL_S0_MULT_PORTA_SRC2  = 40,      /* 40  */
    VPSHAL_VPDMA_CHANNEL_S0_MULT_PORTA_SRC3  = 41,      /* 41  */
    VPSHAL_VPDMA_CHANNEL_S0_MULT_PORTA_SRC4  = 42,      /* 42  */
    VPSHAL_VPDMA_CHANNEL_S0_MULT_PORTA_SRC5  = 43,      /* 43  */
    VPSHAL_VPDMA_CHANNEL_S0_MULT_PORTA_SRC6  = 44,      /* 44  */
    VPSHAL_VPDMA_CHANNEL_S0_MULT_PORTA_SRC7  = 45,      /* 45  */
    VPSHAL_VPDMA_CHANNEL_S0_MULT_PORTA_SRC8  = 46,      /* 46  */
    VPSHAL_VPDMA_CHANNEL_S0_MULT_PORTA_SRC9  = 47,      /* 47  */
    VPSHAL_VPDMA_CHANNEL_S0_MULT_PORTA_SRC10 = 48,      /* 48  */
    VPSHAL_VPDMA_CHANNEL_S0_MULT_PORTA_SRC11 = 49,      /* 49  */
    VPSHAL_VPDMA_CHANNEL_S0_MULT_PORTA_SRC12 = 50,      /* 50  */
    VPSHAL_VPDMA_CHANNEL_S0_MULT_PORTA_SRC13 = 51,      /* 51  */
    VPSHAL_VPDMA_CHANNEL_S0_MULT_PORTA_SRC14 = 52,      /* 52  */
    VPSHAL_VPDMA_CHANNEL_S0_MULT_PORTA_SRC15 = 53,      /* 53  */
    VPSHAL_VPDMA_CHANNEL_S0_MULT_PORTB_SRC0  = 54,      /* 54  */
    VPSHAL_VPDMA_CHANNEL_S0_MULT_PORTB_SRC1  = 55,      /* 55  */
    VPSHAL_VPDMA_CHANNEL_S0_MULT_PORTB_SRC2  = 56,      /* 56  */
    VPSHAL_VPDMA_CHANNEL_S0_MULT_PORTB_SRC3  = 57,      /* 57  */
    VPSHAL_VPDMA_CHANNEL_S0_MULT_PORTB_SRC4  = 58,      /* 58  */
    VPSHAL_VPDMA_CHANNEL_S0_MULT_PORTB_SRC5  = 59,      /* 59  */
    VPSHAL_VPDMA_CHANNEL_S0_MULT_PORTB_SRC6  = 60,      /* 60  */
    VPSHAL_VPDMA_CHANNEL_S0_MULT_PORTB_SRC7  = 61,      /* 61  */
    VPSHAL_VPDMA_CHANNEL_S0_MULT_PORTB_SRC8  = 62,      /* 62  */
    VPSHAL_VPDMA_CHANNEL_S0_MULT_PORTB_SRC9  = 63,      /* 63  */
    VPSHAL_VPDMA_CHANNEL_S0_MULT_PORTB_SRC10 = 64,      /* 64  */
    VPSHAL_VPDMA_CHANNEL_S0_MULT_PORTB_SRC11 = 65,      /* 65  */
    VPSHAL_VPDMA_CHANNEL_S0_MULT_PORTB_SRC12 = 66,      /* 66  */
    VPSHAL_VPDMA_CHANNEL_S0_MULT_PORTB_SRC13 = 67,      /* 67  */
    VPSHAL_VPDMA_CHANNEL_S0_MULT_PORTB_SRC14 = 68,      /* 68  */
    VPSHAL_VPDMA_CHANNEL_S0_MULT_PORTB_SRC15 = 69,      /* 69  */
    VPSHAL_VPDMA_CHANNEL_S0_MULT_ANCA_SRC0   = 70,      /* 70  */
    VPSHAL_VPDMA_CHANNEL_S0_MULT_ANCA_SRC1   = 71,      /* 71  */
    VPSHAL_VPDMA_CHANNEL_S0_MULT_ANCA_SRC2   = 72,      /* 72  */
    VPSHAL_VPDMA_CHANNEL_S0_MULT_ANCA_SRC3   = 73,      /* 73  */
    VPSHAL_VPDMA_CHANNEL_S0_MULT_ANCA_SRC4   = 74,      /* 74  */
    VPSHAL_VPDMA_CHANNEL_S0_MULT_ANCA_SRC5   = 75,      /* 75  */
    VPSHAL_VPDMA_CHANNEL_S0_MULT_ANCA_SRC6   = 76,      /* 76  */
    VPSHAL_VPDMA_CHANNEL_S0_MULT_ANCA_SRC7   = 77,      /* 77  */
    VPSHAL_VPDMA_CHANNEL_S0_MULT_ANCA_SRC8   = 78,      /* 78  */
    VPSHAL_VPDMA_CHANNEL_S0_MULT_ANCA_SRC9   = 79,      /* 79  */
    VPSHAL_VPDMA_CHANNEL_S0_MULT_ANCA_SRC10  = 80,      /* 80  */
    VPSHAL_VPDMA_CHANNEL_S0_MULT_ANCA_SRC11  = 81,      /* 81  */
    VPSHAL_VPDMA_CHANNEL_S0_MULT_ANCA_SRC12  = 82,      /* 82  */
    VPSHAL_VPDMA_CHANNEL_S0_MULT_ANCA_SRC13  = 83,      /* 83  */
    VPSHAL_VPDMA_CHANNEL_S0_MULT_ANCA_SRC14  = 84,      /* 84  */
    VPSHAL_VPDMA_CHANNEL_S0_MULT_ANCA_SRC15  = 85,      /* 85  */
    VPSHAL_VPDMA_CHANNEL_S0_MULT_ANCB_SRC0   = 86,      /* 86  */
    VPSHAL_VPDMA_CHANNEL_S0_MULT_ANCB_SRC1   = 87,      /* 87  */
    VPSHAL_VPDMA_CHANNEL_S0_MULT_ANCB_SRC2   = 88,      /* 88  */
    VPSHAL_VPDMA_CHANNEL_S0_MULT_ANCB_SRC3   = 89,      /* 89  */
    VPSHAL_VPDMA_CHANNEL_S0_MULT_ANCB_SRC4   = 90,      /* 90  */
    VPSHAL_VPDMA_CHANNEL_S0_MULT_ANCB_SRC5   = 91,      /* 91  */
    VPSHAL_VPDMA_CHANNEL_S0_MULT_ANCB_SRC6   = 92,      /* 92  */
    VPSHAL_VPDMA_CHANNEL_S0_MULT_ANCB_SRC7   = 93,      /* 93  */
    VPSHAL_VPDMA_CHANNEL_S0_MULT_ANCB_SRC8   = 94,      /* 94  */
    VPSHAL_VPDMA_CHANNEL_S0_MULT_ANCB_SRC9   = 95,      /* 95  */
    VPSHAL_VPDMA_CHANNEL_S0_MULT_ANCB_SRC10  = 96,      /* 96  */
    VPSHAL_VPDMA_CHANNEL_S0_MULT_ANCB_SRC11  = 97,      /* 97  */
    VPSHAL_VPDMA_CHANNEL_S0_MULT_ANCB_SRC12  = 98,      /* 98  */
    VPSHAL_VPDMA_CHANNEL_S0_MULT_ANCB_SRC13  = 99,      /* 99  */
    VPSHAL_VPDMA_CHANNEL_S0_MULT_ANCB_SRC14  = 100,     /* 100 */
    VPSHAL_VPDMA_CHANNEL_S0_MULT_ANCB_SRC15  = 101,     /* 101 */
    VPSHAL_VPDMA_CHANNEL_S0_PORTA_LUMA       = 102,     /* 102 */
    VPSHAL_VPDMA_CHANNEL_S0_PORTA_CHROMA     = 103,     /* 103 */
    VPSHAL_VPDMA_CHANNEL_S0_PORTB_LUMA       = 104,     /* 104 */
    VPSHAL_VPDMA_CHANNEL_S0_PORTB_CHROMA     = 105,     /* 105 */
    VPSHAL_VPDMA_CHANNEL_S0_PORTA_RGB        = 106,     /* 106 */
    VPSHAL_VPDMA_CHANNEL_S0_PORTB_RGB        = 107,     /* 107 */
    VPSHAL_VPDMA_CHANNEL_S1_MULT_PORTA_SRC0  = 108,     /* 108 */
    VPSHAL_VPDMA_CHANNEL_S1_MULT_PORTA_SRC1  = 109,     /* 109 */
    VPSHAL_VPDMA_CHANNEL_S1_MULT_PORTA_SRC2  = 110,     /* 110 */
    VPSHAL_VPDMA_CHANNEL_S1_MULT_PORTA_SRC3  = 111,     /* 111 */
    VPSHAL_VPDMA_CHANNEL_S1_MULT_PORTA_SRC4  = 112,     /* 112 */
    VPSHAL_VPDMA_CHANNEL_S1_MULT_PORTA_SRC5  = 113,     /* 113 */
    VPSHAL_VPDMA_CHANNEL_S1_MULT_PORTA_SRC6  = 114,     /* 114 */
    VPSHAL_VPDMA_CHANNEL_S1_MULT_PORTA_SRC7  = 115,     /* 115 */
    VPSHAL_VPDMA_CHANNEL_S1_MULT_PORTA_SRC8  = 116,     /* 116 */
    VPSHAL_VPDMA_CHANNEL_S1_MULT_PORTA_SRC9  = 117,     /* 117 */
    VPSHAL_VPDMA_CHANNEL_S1_MULT_PORTA_SRC10 = 118,     /* 118 */
    VPSHAL_VPDMA_CHANNEL_S1_MULT_PORTA_SRC11 = 119,     /* 119 */
    VPSHAL_VPDMA_CHANNEL_S1_MULT_PORTA_SRC12 = 120,     /* 120 */
    VPSHAL_VPDMA_CHANNEL_S1_MULT_PORTA_SRC13 = 121,     /* 121 */
    VPSHAL_VPDMA_CHANNEL_S1_MULT_PORTA_SRC14 = 122,     /* 122 */
    VPSHAL_VPDMA_CHANNEL_S1_MULT_PORTA_SRC15 = 123,     /* 123 */
    VPSHAL_VPDMA_CHANNEL_S1_MULT_PORTB_SRC0  = 124,     /* 124 */
    VPSHAL_VPDMA_CHANNEL_S1_MULT_PORTB_SRC1  = 125,     /* 125 */
    VPSHAL_VPDMA_CHANNEL_S1_MULT_PORTB_SRC2  = 126,     /* 126 */
    VPSHAL_VPDMA_CHANNEL_S1_MULT_PORTB_SRC3  = 127,     /* 127 */
    VPSHAL_VPDMA_CHANNEL_S1_MULT_PORTB_SRC4  = 128,     /* 128 */
    VPSHAL_VPDMA_CHANNEL_S1_MULT_PORTB_SRC5  = 129,     /* 129 */
    VPSHAL_VPDMA_CHANNEL_S1_MULT_PORTB_SRC6  = 130,     /* 130 */
    VPSHAL_VPDMA_CHANNEL_S1_MULT_PORTB_SRC7  = 131,     /* 131 */
    VPSHAL_VPDMA_CHANNEL_S1_MULT_PORTB_SRC8  = 132,     /* 132 */
    VPSHAL_VPDMA_CHANNEL_S1_MULT_PORTB_SRC9  = 133,     /* 133 */
    VPSHAL_VPDMA_CHANNEL_S1_MULT_PORTB_SRC10 = 134,     /* 134 */
    VPSHAL_VPDMA_CHANNEL_S1_MULT_PORTB_SRC11 = 135,     /* 135 */
    VPSHAL_VPDMA_CHANNEL_S1_MULT_PORTB_SRC12 = 136,     /* 136 */
    VPSHAL_VPDMA_CHANNEL_S1_MULT_PORTB_SRC13 = 137,     /* 137 */
    VPSHAL_VPDMA_CHANNEL_S1_MULT_PORTB_SRC14 = 138,     /* 138 */
    VPSHAL_VPDMA_CHANNEL_S1_MULT_PORTB_SRC15 = 139,     /* 139 */
    VPSHAL_VPDMA_CHANNEL_S1_MULT_ANCA_SRC0   = 140,     /* 140 */
    VPSHAL_VPDMA_CHANNEL_S1_MULT_ANCA_SRC1   = 141,     /* 141 */
    VPSHAL_VPDMA_CHANNEL_S1_MULT_ANCA_SRC2   = 142,     /* 142 */
    VPSHAL_VPDMA_CHANNEL_S1_MULT_ANCA_SRC3   = 143,     /* 143 */
    VPSHAL_VPDMA_CHANNEL_S1_MULT_ANCA_SRC4   = 144,     /* 144 */
    VPSHAL_VPDMA_CHANNEL_S1_MULT_ANCA_SRC5   = 145,     /* 145 */
    VPSHAL_VPDMA_CHANNEL_S1_MULT_ANCA_SRC6   = 146,     /* 146 */
    VPSHAL_VPDMA_CHANNEL_S1_MULT_ANCA_SRC7   = 147,     /* 147 */
    VPSHAL_VPDMA_CHANNEL_S1_MULT_ANCA_SRC8   = 148,     /* 148 */
    VPSHAL_VPDMA_CHANNEL_S1_MULT_ANCA_SRC9   = 149,     /* 149 */
    VPSHAL_VPDMA_CHANNEL_S1_MULT_ANCA_SRC10  = 150,     /* 150 */
    VPSHAL_VPDMA_CHANNEL_S1_MULT_ANCA_SRC11  = 151,     /* 151 */
    VPSHAL_VPDMA_CHANNEL_S1_MULT_ANCA_SRC12  = 152,     /* 152 */
    VPSHAL_VPDMA_CHANNEL_S1_MULT_ANCA_SRC13  = 153,     /* 153 */
    VPSHAL_VPDMA_CHANNEL_S1_MULT_ANCA_SRC14  = 154,     /* 154 */
    VPSHAL_VPDMA_CHANNEL_S1_MULT_ANCA_SRC15  = 155,     /* 155 */
    VPSHAL_VPDMA_CHANNEL_S1_MULT_ANCB_SRC0   = 156,     /* 156 */
    VPSHAL_VPDMA_CHANNEL_S1_MULT_ANCB_SRC1   = 157,     /* 157 */
    VPSHAL_VPDMA_CHANNEL_S1_MULT_ANCB_SRC2   = 158,     /* 158 */
    VPSHAL_VPDMA_CHANNEL_S1_MULT_ANCB_SRC3   = 159,     /* 159 */
    VPSHAL_VPDMA_CHANNEL_S1_MULT_ANCB_SRC4   = 160,     /* 160 */
    VPSHAL_VPDMA_CHANNEL_S1_MULT_ANCB_SRC5   = 161,     /* 161 */
    VPSHAL_VPDMA_CHANNEL_S1_MULT_ANCB_SRC6   = 162,     /* 162 */
    VPSHAL_VPDMA_CHANNEL_S1_MULT_ANCB_SRC7   = 163,     /* 163 */
    VPSHAL_VPDMA_CHANNEL_S1_MULT_ANCB_SRC8   = 164,     /* 164 */
    VPSHAL_VPDMA_CHANNEL_S1_MULT_ANCB_SRC9   = 165,     /* 165 */
    VPSHAL_VPDMA_CHANNEL_S1_MULT_ANCB_SRC10  = 166,     /* 166 */
    VPSHAL_VPDMA_CHANNEL_S1_MULT_ANCB_SRC11  = 167,     /* 167 */
    VPSHAL_VPDMA_CHANNEL_S1_MULT_ANCB_SRC12  = 168,     /* 168 */
    VPSHAL_VPDMA_CHANNEL_S1_MULT_ANCB_SRC13  = 169,     /* 169 */
    VPSHAL_VPDMA_CHANNEL_S1_MULT_ANCB_SRC14  = 170,     /* 170 */
    VPSHAL_VPDMA_CHANNEL_S1_MULT_ANCB_SRC15  = 171,     /* 171 */
    VPSHAL_VPDMA_CHANNEL_S1_PORTA_LUMA       = 172,     /* 172 */
    VPSHAL_VPDMA_CHANNEL_S1_PORTA_CHROMA     = 173,     /* 173 */
    VPSHAL_VPDMA_CHANNEL_S1_PORTB_LUMA       = 174,     /* 174 */
    VPSHAL_VPDMA_CHANNEL_S1_PORTB_CHROMA     = 175,     /* 175 */
    VPSHAL_VPDMA_CHANNEL_S1_PORTA_RGB        = 176,     /* 176 */
    VPSHAL_VPDMA_CHANNEL_S1_PORTB_RGB        = 177,     /* 177 */
    VPSHAL_VPDMA_CHANNEL_NUM_CHANNELS        = 192
} VpsHal_VpdmaChannel;

/**
 *  VpsHal_VpdmaClient
 *  \brief Enum for the client used by the VPDMA (in the VIP)
 */
typedef enum
{
    VPSHAL_VPDMA_CLIENT_INVALID = (-(int32_t)1),
    /**< Invalid value, used as boundary */
    VPSHAL_VPDMA_CLIENT_VIP_S0_LO_Y = 34,
    /**< VIP slice 0 Luma Low output port */
    VPSHAL_VPDMA_CLIENT_VIP_S0_LO_UV = 35,
    /**< VIP slice 0 Chroma Low output port */
    VPSHAL_VPDMA_CLIENT_VIP_S0_UP_Y = 36,
    /**< VIP slice 0 Luma High output port */
    VPSHAL_VPDMA_CLIENT_VIP_S0_UP_UV = 37,
    /**< VIP slice 0 Chroma High output port */
    VPSHAL_VPDMA_CLIENT_VIP_S1_LO_Y = 38,
    /**< VIP slice 1 Luma Low output port */
    VPSHAL_VPDMA_CLIENT_VIP_S1_LO_UV = 39,
    /**< VIP slice 1 Chroma Low output port */
    VPSHAL_VPDMA_CLIENT_VIP_S1_UP_Y = 40,
    /**< VIP slice 1 Luma High output port */
    VPSHAL_VPDMA_CLIENT_VIP_S1_UP_UV = 41,
    /**< VIP slice 1 Chroma High output port */
    VPSHAL_VPDMA_CLIENT_VIP_S0_ANC_A = 58,
    /**< VIP slice 0 Ancilary A output port */
    VPSHAL_VPDMA_CLIENT_VIP_S0_ANC_B = 59,
    /**< VIP slice 0 Ancilary B output port */
    VPSHAL_VPDMA_CLIENT_VIP_S1_ANC_A = 60,
    /**< VIP slice 1 Ancilary A output port */
    VPSHAL_VPDMA_CLIENT_VIP_S1_ANC_B = 61,
    /**< VIP slice 1 Ancilary B output port */
    VPSHAL_VPDMA_CLIENT_MAX = 62
                              /**< Enumeration Guard */
}VpsHal_VpdmaClient;

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/* None */

#ifdef __cplusplus
}
#endif

#endif /* End of #ifndef VPSHAL_VPDMA_TDA3XX_H_ */
