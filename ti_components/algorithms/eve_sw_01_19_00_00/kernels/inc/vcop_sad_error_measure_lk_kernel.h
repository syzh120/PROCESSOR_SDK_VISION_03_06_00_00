#ifndef _TI_vcop_sad_error_measure_lk_kernel_h_
#define _TI_vcop_sad_error_measure_lk_kernel_h_

/* Parameter Register Block */
extern unsigned short __pblock_vcop_sad_error_measure_lk[62];

/* Basic Runner Function */
void vcop_sad_error_measure_lk(
   __vptr_uint8 pPrevBiLinImg_A,
   __vptr_uint8 pCurrBiLinImg_B,
   __vptr_uint16 pNewXYList_X,
   __vptr_uint16 pOutErrorMeasure_C,
   unsigned short inputStride,
   unsigned short frmWidth,
   unsigned short frmHeight,
   unsigned short blkWidth,
   unsigned short blkHeight,
   unsigned short numKeyPoints,
   unsigned short shiftValue,
   __vptr_uint16 scratch_a,
   unsigned short sadThreshold,
   __vptr_uint16 numInvalidPointsWbuf,
   __vptr_uint16 numInvalidPointsIbuf);
/* Custom Runner Function */
void vcop_sad_error_measure_lk_custom(
   __vptr_uint8 pPrevBiLinImg_A,
   __vptr_uint8 pCurrBiLinImg_B,
   __vptr_uint16 pNewXYList_X,
   __vptr_uint16 pOutErrorMeasure_C,
   unsigned short inputStride,
   unsigned short frmWidth,
   unsigned short frmHeight,
   unsigned short blkWidth,
   unsigned short blkHeight,
   unsigned short numKeyPoints,
   unsigned short shiftValue,
   __vptr_uint16 scratch_a,
   unsigned short sadThreshold,
   __vptr_uint16 numInvalidPointsWbuf,
   __vptr_uint16 numInvalidPointsIbuf,
   unsigned short pblock[]);

/* Parameter Block Initialization Function */
unsigned int vcop_sad_error_measure_lk_init(
   __vptr_uint8 pPrevBiLinImg_A,
   __vptr_uint8 pCurrBiLinImg_B,
   __vptr_uint16 pNewXYList_X,
   __vptr_uint16 pOutErrorMeasure_C,
   unsigned short inputStride,
   unsigned short frmWidth,
   unsigned short frmHeight,
   unsigned short blkWidth,
   unsigned short blkHeight,
   unsigned short numKeyPoints,
   unsigned short shiftValue,
   __vptr_uint16 scratch_a,
   unsigned short sadThreshold,
   __vptr_uint16 numInvalidPointsWbuf,
   __vptr_uint16 numInvalidPointsIbuf,
   unsigned short pblock[]);

/* VCOP VLOOP Execution Function */
void vcop_sad_error_measure_lk_vloops(
   unsigned short pblock[]);

/* Parameter Register Count */
#define PARAM_SIZE_vcop_sad_error_measure_lk ((unsigned int)62)
unsigned int vcop_sad_error_measure_lk_param_count(void);
/* Internal Value Count */
#define CTRL_SIZE_vcop_sad_error_measure_lk ((unsigned int)0)
unsigned int vcop_sad_error_measure_lk_ctrl_count(void);

/***********************************************************/
#endif

