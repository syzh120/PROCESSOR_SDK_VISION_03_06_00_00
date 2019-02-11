#ifndef _TI_vcop_disparity_hammingDistance32_row_kernel_h_
#define _TI_vcop_disparity_hammingDistance32_row_kernel_h_

/* Parameter Register Block */
extern unsigned short __pblock_vcop_disparity_hammingDistance32_first_row_firstCall[94];

/* Basic Runner Function */
void vcop_disparity_hammingDistance32_first_row_firstCall(
   __vptr_uint32 pLeft,
   __vptr_uint32 pRight,
   unsigned short leftStride,
   unsigned short rightStride,
   unsigned char winWidth,
   unsigned char winHeight,
   __vptr_uint8 pDisparityOutput,
   __vptr_uint16 pMinCostOutput,
   __vptr_uint16 pAllCostOutput,
   unsigned short allCostOutputStride,
   unsigned short width,
   unsigned char numDisparities,
   unsigned char disparityStep,
   __vptr_uint8 pCollateMask,
   __vptr_uint16 pOffset,
   __vptr_int16 pScratch0,
   __vptr_int16 pCarryOverOut,
   unsigned short scratchStride);
/* Custom Runner Function */
void vcop_disparity_hammingDistance32_first_row_firstCall_custom(
   __vptr_uint32 pLeft,
   __vptr_uint32 pRight,
   unsigned short leftStride,
   unsigned short rightStride,
   unsigned char winWidth,
   unsigned char winHeight,
   __vptr_uint8 pDisparityOutput,
   __vptr_uint16 pMinCostOutput,
   __vptr_uint16 pAllCostOutput,
   unsigned short allCostOutputStride,
   unsigned short width,
   unsigned char numDisparities,
   unsigned char disparityStep,
   __vptr_uint8 pCollateMask,
   __vptr_uint16 pOffset,
   __vptr_int16 pScratch0,
   __vptr_int16 pCarryOverOut,
   unsigned short scratchStride,
   unsigned short pblock[]);

/* Parameter Block Initialization Function */
unsigned int vcop_disparity_hammingDistance32_first_row_firstCall_init(
   __vptr_uint32 pLeft,
   __vptr_uint32 pRight,
   unsigned short leftStride,
   unsigned short rightStride,
   unsigned char winWidth,
   unsigned char winHeight,
   __vptr_uint8 pDisparityOutput,
   __vptr_uint16 pMinCostOutput,
   __vptr_uint16 pAllCostOutput,
   unsigned short allCostOutputStride,
   unsigned short width,
   unsigned char numDisparities,
   unsigned char disparityStep,
   __vptr_uint8 pCollateMask,
   __vptr_uint16 pOffset,
   __vptr_int16 pScratch0,
   __vptr_int16 pCarryOverOut,
   unsigned short scratchStride,
   unsigned short pblock[]);

/* VCOP VLOOP Execution Function */
void vcop_disparity_hammingDistance32_first_row_firstCall_vloops(
   unsigned short pblock[]);

/* Parameter Register Count */
#define PARAM_SIZE_vcop_disparity_hammingDistance32_first_row_firstCall ((unsigned int)94)
unsigned int vcop_disparity_hammingDistance32_first_row_firstCall_param_count(void);
/* Internal Value Count */
#define CTRL_SIZE_vcop_disparity_hammingDistance32_first_row_firstCall ((unsigned int)0)
unsigned int vcop_disparity_hammingDistance32_first_row_firstCall_ctrl_count(void);

/***********************************************************/
/* Parameter Register Block */
extern unsigned short __pblock_vcop_disparity_hammingDistance32_first_row[80];

/* Basic Runner Function */
void vcop_disparity_hammingDistance32_first_row(
   __vptr_uint32 pLeft,
   __vptr_uint32 pRight,
   unsigned short leftStride,
   unsigned short rightStride,
   unsigned char winWidth,
   unsigned char winHeight,
   __vptr_uint8 pDisparityOutput,
   __vptr_uint16 pMinCostOutput,
   __vptr_uint16 pAllCostOutput,
   unsigned short allCostOutputStride,
   unsigned short width,
   unsigned char numDisparities,
   unsigned char disparityStep,
   __vptr_uint8 pCollateMask,
   __vptr_uint16 pOffset,
   __vptr_int16 pScratch0,
   __vptr_int16 pCarryOverIn,
   __vptr_int16 pCarryOverOut,
   unsigned short scratchStride);
/* Custom Runner Function */
void vcop_disparity_hammingDistance32_first_row_custom(
   __vptr_uint32 pLeft,
   __vptr_uint32 pRight,
   unsigned short leftStride,
   unsigned short rightStride,
   unsigned char winWidth,
   unsigned char winHeight,
   __vptr_uint8 pDisparityOutput,
   __vptr_uint16 pMinCostOutput,
   __vptr_uint16 pAllCostOutput,
   unsigned short allCostOutputStride,
   unsigned short width,
   unsigned char numDisparities,
   unsigned char disparityStep,
   __vptr_uint8 pCollateMask,
   __vptr_uint16 pOffset,
   __vptr_int16 pScratch0,
   __vptr_int16 pCarryOverIn,
   __vptr_int16 pCarryOverOut,
   unsigned short scratchStride,
   unsigned short pblock[]);

/* Parameter Block Initialization Function */
unsigned int vcop_disparity_hammingDistance32_first_row_init(
   __vptr_uint32 pLeft,
   __vptr_uint32 pRight,
   unsigned short leftStride,
   unsigned short rightStride,
   unsigned char winWidth,
   unsigned char winHeight,
   __vptr_uint8 pDisparityOutput,
   __vptr_uint16 pMinCostOutput,
   __vptr_uint16 pAllCostOutput,
   unsigned short allCostOutputStride,
   unsigned short width,
   unsigned char numDisparities,
   unsigned char disparityStep,
   __vptr_uint8 pCollateMask,
   __vptr_uint16 pOffset,
   __vptr_int16 pScratch0,
   __vptr_int16 pCarryOverIn,
   __vptr_int16 pCarryOverOut,
   unsigned short scratchStride,
   unsigned short pblock[]);

/* VCOP VLOOP Execution Function */
void vcop_disparity_hammingDistance32_first_row_vloops(
   unsigned short pblock[]);

/* Parameter Register Count */
#define PARAM_SIZE_vcop_disparity_hammingDistance32_first_row ((unsigned int)80)
unsigned int vcop_disparity_hammingDistance32_first_row_param_count(void);
/* Internal Value Count */
#define CTRL_SIZE_vcop_disparity_hammingDistance32_first_row ((unsigned int)0)
unsigned int vcop_disparity_hammingDistance32_first_row_ctrl_count(void);

/***********************************************************/
/* Parameter Register Block */
extern unsigned short __pblock_vcop_disparity_hammingDistance32_nth_row_firstCall[150];

/* Basic Runner Function */
void vcop_disparity_hammingDistance32_nth_row_firstCall(
   __vptr_uint32 pLeft_prevRow,
   __vptr_uint32 pLeft_lastRow,
   __vptr_uint32 pRight_prevRow,
   __vptr_uint32 pRight_lastRow,
   unsigned short leftStride,
   unsigned short rightStride,
   unsigned char winWidth,
   unsigned char winHeight,
   __vptr_uint8 pDisparityOutput,
   __vptr_uint16 pMinCostOutput,
   __vptr_uint16 pAllCostOutput,
   unsigned short allCostOutputStride,
   unsigned short width,
   unsigned char numDisparities,
   unsigned char disparityStep,
   __vptr_uint8 pCollateMask,
   __vptr_uint16 pOffset,
   __vptr_int16 pScratch0,
   __vptr_int16 pScratch1,
   __vptr_int16 pScratch2,
   __vptr_int16 pCarryOverOut,
   unsigned short scratchStride);
/* Custom Runner Function */
void vcop_disparity_hammingDistance32_nth_row_firstCall_custom(
   __vptr_uint32 pLeft_prevRow,
   __vptr_uint32 pLeft_lastRow,
   __vptr_uint32 pRight_prevRow,
   __vptr_uint32 pRight_lastRow,
   unsigned short leftStride,
   unsigned short rightStride,
   unsigned char winWidth,
   unsigned char winHeight,
   __vptr_uint8 pDisparityOutput,
   __vptr_uint16 pMinCostOutput,
   __vptr_uint16 pAllCostOutput,
   unsigned short allCostOutputStride,
   unsigned short width,
   unsigned char numDisparities,
   unsigned char disparityStep,
   __vptr_uint8 pCollateMask,
   __vptr_uint16 pOffset,
   __vptr_int16 pScratch0,
   __vptr_int16 pScratch1,
   __vptr_int16 pScratch2,
   __vptr_int16 pCarryOverOut,
   unsigned short scratchStride,
   unsigned short pblock[]);

/* Parameter Block Initialization Function */
unsigned int vcop_disparity_hammingDistance32_nth_row_firstCall_init(
   __vptr_uint32 pLeft_prevRow,
   __vptr_uint32 pLeft_lastRow,
   __vptr_uint32 pRight_prevRow,
   __vptr_uint32 pRight_lastRow,
   unsigned short leftStride,
   unsigned short rightStride,
   unsigned char winWidth,
   unsigned char winHeight,
   __vptr_uint8 pDisparityOutput,
   __vptr_uint16 pMinCostOutput,
   __vptr_uint16 pAllCostOutput,
   unsigned short allCostOutputStride,
   unsigned short width,
   unsigned char numDisparities,
   unsigned char disparityStep,
   __vptr_uint8 pCollateMask,
   __vptr_uint16 pOffset,
   __vptr_int16 pScratch0,
   __vptr_int16 pScratch1,
   __vptr_int16 pScratch2,
   __vptr_int16 pCarryOverOut,
   unsigned short scratchStride,
   unsigned short pblock[]);

/* VCOP VLOOP Execution Function */
void vcop_disparity_hammingDistance32_nth_row_firstCall_vloops(
   unsigned short pblock[]);

/* Parameter Register Count */
#define PARAM_SIZE_vcop_disparity_hammingDistance32_nth_row_firstCall ((unsigned int)150)
unsigned int vcop_disparity_hammingDistance32_nth_row_firstCall_param_count(void);
/* Internal Value Count */
#define CTRL_SIZE_vcop_disparity_hammingDistance32_nth_row_firstCall ((unsigned int)0)
unsigned int vcop_disparity_hammingDistance32_nth_row_firstCall_ctrl_count(void);

/***********************************************************/
/* Parameter Register Block */
extern unsigned short __pblock_vcop_disparity_hammingDistance32_nth_row[128];

/* Basic Runner Function */
void vcop_disparity_hammingDistance32_nth_row(
   __vptr_uint32 pLeft_prevRow,
   __vptr_uint32 pLeft_lastRow,
   __vptr_uint32 pRight_prevRow,
   __vptr_uint32 pRight_lastRow,
   unsigned short leftStride,
   unsigned short rightStride,
   unsigned char winWidth,
   unsigned char winHeight,
   __vptr_uint8 pDisparityOutput,
   __vptr_uint16 pMinCostOutput,
   __vptr_uint16 pAllCostOutput,
   unsigned short allCostOutputStride,
   unsigned short width,
   unsigned char numDisparities,
   unsigned char disparityStep,
   __vptr_uint8 pCollateMask,
   __vptr_uint16 pOffset,
   __vptr_int16 pScratch0,
   __vptr_int16 pScratch1,
   __vptr_int16 pScratch2,
   __vptr_int16 pCarryOverIn,
   __vptr_int16 pCarryOverOut,
   unsigned short scratchStride);
/* Custom Runner Function */
void vcop_disparity_hammingDistance32_nth_row_custom(
   __vptr_uint32 pLeft_prevRow,
   __vptr_uint32 pLeft_lastRow,
   __vptr_uint32 pRight_prevRow,
   __vptr_uint32 pRight_lastRow,
   unsigned short leftStride,
   unsigned short rightStride,
   unsigned char winWidth,
   unsigned char winHeight,
   __vptr_uint8 pDisparityOutput,
   __vptr_uint16 pMinCostOutput,
   __vptr_uint16 pAllCostOutput,
   unsigned short allCostOutputStride,
   unsigned short width,
   unsigned char numDisparities,
   unsigned char disparityStep,
   __vptr_uint8 pCollateMask,
   __vptr_uint16 pOffset,
   __vptr_int16 pScratch0,
   __vptr_int16 pScratch1,
   __vptr_int16 pScratch2,
   __vptr_int16 pCarryOverIn,
   __vptr_int16 pCarryOverOut,
   unsigned short scratchStride,
   unsigned short pblock[]);

/* Parameter Block Initialization Function */
unsigned int vcop_disparity_hammingDistance32_nth_row_init(
   __vptr_uint32 pLeft_prevRow,
   __vptr_uint32 pLeft_lastRow,
   __vptr_uint32 pRight_prevRow,
   __vptr_uint32 pRight_lastRow,
   unsigned short leftStride,
   unsigned short rightStride,
   unsigned char winWidth,
   unsigned char winHeight,
   __vptr_uint8 pDisparityOutput,
   __vptr_uint16 pMinCostOutput,
   __vptr_uint16 pAllCostOutput,
   unsigned short allCostOutputStride,
   unsigned short width,
   unsigned char numDisparities,
   unsigned char disparityStep,
   __vptr_uint8 pCollateMask,
   __vptr_uint16 pOffset,
   __vptr_int16 pScratch0,
   __vptr_int16 pScratch1,
   __vptr_int16 pScratch2,
   __vptr_int16 pCarryOverIn,
   __vptr_int16 pCarryOverOut,
   unsigned short scratchStride,
   unsigned short pblock[]);

/* VCOP VLOOP Execution Function */
void vcop_disparity_hammingDistance32_nth_row_vloops(
   unsigned short pblock[]);

/* Parameter Register Count */
#define PARAM_SIZE_vcop_disparity_hammingDistance32_nth_row ((unsigned int)128)
unsigned int vcop_disparity_hammingDistance32_nth_row_param_count(void);
/* Internal Value Count */
#define CTRL_SIZE_vcop_disparity_hammingDistance32_nth_row ((unsigned int)0)
unsigned int vcop_disparity_hammingDistance32_nth_row_ctrl_count(void);

/***********************************************************/
#endif

