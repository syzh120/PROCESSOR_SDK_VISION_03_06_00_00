#ifndef _TI_vcop_weight_computation_kernel_h_
#define _TI_vcop_weight_computation_kernel_h_

/* Parameter Register Block */
extern unsigned short __pblock_vcop_weight_computation[20];

/* Basic Runner Function */
void vcop_weight_computation(
   __vptr_uint16 pXYList_A,
   __vptr_uint16 pOutWts_B,
   unsigned short numKeyPoints,
   unsigned short qFormatMaxFactor,
   unsigned short truncateBits,
   unsigned short outputStride);
/* Custom Runner Function */
void vcop_weight_computation_custom(
   __vptr_uint16 pXYList_A,
   __vptr_uint16 pOutWts_B,
   unsigned short numKeyPoints,
   unsigned short qFormatMaxFactor,
   unsigned short truncateBits,
   unsigned short outputStride,
   unsigned short pblock[]);

/* Parameter Block Initialization Function */
unsigned int vcop_weight_computation_init(
   __vptr_uint16 pXYList_A,
   __vptr_uint16 pOutWts_B,
   unsigned short numKeyPoints,
   unsigned short qFormatMaxFactor,
   unsigned short truncateBits,
   unsigned short outputStride,
   unsigned short pblock[]);

/* VCOP VLOOP Execution Function */
void vcop_weight_computation_vloops(
   unsigned short pblock[]);

/* Parameter Register Count */
#define PARAM_SIZE_vcop_weight_computation ((unsigned int)20)
unsigned int vcop_weight_computation_param_count(void);
/* Internal Value Count */
#define CTRL_SIZE_vcop_weight_computation ((unsigned int)0)
unsigned int vcop_weight_computation_ctrl_count(void);

/***********************************************************/
#endif

