#ifndef _TI_vcop_weight_address_bilinear_interpolation_kernel_h_
#define _TI_vcop_weight_address_bilinear_interpolation_kernel_h_

/* Parameter Register Block */
extern unsigned short __pblock_vcop_weight_address_bilinear_interpolation[52];

/* Basic Runner Function */
void vcop_weight_address_bilinear_interpolation(
   __vptr_uint16 pXList_A,
   __vptr_uint16 pYList_A,
   __vptr_uint32 pBaseAddrList_B,
   __vptr_uint32 pOutAddrList_B,
   __vptr_uint16 pOutWts_C,
   __vptr_uint32 pOutBaseAddress_C,
   __vptr_uint16 pParamBlkOffsetVec_C,
   unsigned short numKeyPoints,
   unsigned short qFormatMaxFactor,
   unsigned short truncateBits,
   unsigned short qShift,
   unsigned short blkStride,
   unsigned short outputStride);
/* Custom Runner Function */
void vcop_weight_address_bilinear_interpolation_custom(
   __vptr_uint16 pXList_A,
   __vptr_uint16 pYList_A,
   __vptr_uint32 pBaseAddrList_B,
   __vptr_uint32 pOutAddrList_B,
   __vptr_uint16 pOutWts_C,
   __vptr_uint32 pOutBaseAddress_C,
   __vptr_uint16 pParamBlkOffsetVec_C,
   unsigned short numKeyPoints,
   unsigned short qFormatMaxFactor,
   unsigned short truncateBits,
   unsigned short qShift,
   unsigned short blkStride,
   unsigned short outputStride,
   unsigned short pblock[]);

/* Parameter Block Initialization Function */
unsigned int vcop_weight_address_bilinear_interpolation_init(
   __vptr_uint16 pXList_A,
   __vptr_uint16 pYList_A,
   __vptr_uint32 pBaseAddrList_B,
   __vptr_uint32 pOutAddrList_B,
   __vptr_uint16 pOutWts_C,
   __vptr_uint32 pOutBaseAddress_C,
   __vptr_uint16 pParamBlkOffsetVec_C,
   unsigned short numKeyPoints,
   unsigned short qFormatMaxFactor,
   unsigned short truncateBits,
   unsigned short qShift,
   unsigned short blkStride,
   unsigned short outputStride,
   unsigned short pblock[]);

/* VCOP VLOOP Execution Function */
void vcop_weight_address_bilinear_interpolation_vloops(
   unsigned short pblock[]);

/* Parameter Register Count */
#define PARAM_SIZE_vcop_weight_address_bilinear_interpolation ((unsigned int)52)
unsigned int vcop_weight_address_bilinear_interpolation_param_count(void);
/* Internal Value Count */
#define CTRL_SIZE_vcop_weight_address_bilinear_interpolation ((unsigned int)0)
unsigned int vcop_weight_address_bilinear_interpolation_ctrl_count(void);

/***********************************************************/
#endif

