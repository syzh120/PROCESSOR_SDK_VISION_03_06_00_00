#ifndef _TI_vcop_disparity_postprocess_kernel_h_
#define _TI_vcop_disparity_postprocess_kernel_h_

/* Parameter Register Block */
extern unsigned short __pblock_vcop_disparity_genPrevAndNextMinCost[42];

/* Basic Runner Function */
void vcop_disparity_genPrevAndNextMinCost(
   __vptr_uint8 disparity,
   __vptr_uint16 allCost,
   __vptr_uint16 prevMinCostOutput,
   __vptr_uint16 nextMinCostOutput,
   __vptr_uint16 scratchIndex,
   unsigned short width,
   unsigned short allCostStride,
   unsigned char numDisparities,
   unsigned char disparityStep,
   unsigned char disparityStepShift);
/* Custom Runner Function */
void vcop_disparity_genPrevAndNextMinCost_custom(
   __vptr_uint8 disparity,
   __vptr_uint16 allCost,
   __vptr_uint16 prevMinCostOutput,
   __vptr_uint16 nextMinCostOutput,
   __vptr_uint16 scratchIndex,
   unsigned short width,
   unsigned short allCostStride,
   unsigned char numDisparities,
   unsigned char disparityStep,
   unsigned char disparityStepShift,
   unsigned short pblock[]);

/* Parameter Block Initialization Function */
unsigned int vcop_disparity_genPrevAndNextMinCost_init(
   __vptr_uint8 disparity,
   __vptr_uint16 allCost,
   __vptr_uint16 prevMinCostOutput,
   __vptr_uint16 nextMinCostOutput,
   __vptr_uint16 scratchIndex,
   unsigned short width,
   unsigned short allCostStride,
   unsigned char numDisparities,
   unsigned char disparityStep,
   unsigned char disparityStepShift,
   unsigned short pblock[]);

/* VCOP VLOOP Execution Function */
void vcop_disparity_genPrevAndNextMinCost_vloops(
   unsigned short pblock[]);

/* Parameter Register Count */
#define PARAM_SIZE_vcop_disparity_genPrevAndNextMinCost ((unsigned int)42)
unsigned int vcop_disparity_genPrevAndNextMinCost_param_count(void);
/* Internal Value Count */
#define CTRL_SIZE_vcop_disparity_genPrevAndNextMinCost ((unsigned int)0)
unsigned int vcop_disparity_genPrevAndNextMinCost_ctrl_count(void);

/***********************************************************/
/* Parameter Register Block */
extern unsigned short __pblock_vcop_disparity_hammingDistance_row_right_left_firstCall[44];

/* Basic Runner Function */
void vcop_disparity_hammingDistance_row_right_left_firstCall(
   __vptr_uint16 allCostOutput,
   __vptr_uint8 rlDisparityOutput,
   __vptr_uint16 rlMinCostOutput,
   __vptr_uint8 prevRlDisparityOutput,
   __vptr_uint16 prevRlMinCostOutput,
   __vptr_uint16 rlAllCostOutput,
   __vptr_uint8 rlDisparityScratch,
   __vptr_uint16 rlMinCostScratch,
   unsigned short allCostStride,
   unsigned short rlAllCostStride,
   unsigned short width,
   unsigned char numDisparities,
   unsigned char disparityStep);
/* Custom Runner Function */
void vcop_disparity_hammingDistance_row_right_left_firstCall_custom(
   __vptr_uint16 allCostOutput,
   __vptr_uint8 rlDisparityOutput,
   __vptr_uint16 rlMinCostOutput,
   __vptr_uint8 prevRlDisparityOutput,
   __vptr_uint16 prevRlMinCostOutput,
   __vptr_uint16 rlAllCostOutput,
   __vptr_uint8 rlDisparityScratch,
   __vptr_uint16 rlMinCostScratch,
   unsigned short allCostStride,
   unsigned short rlAllCostStride,
   unsigned short width,
   unsigned char numDisparities,
   unsigned char disparityStep,
   unsigned short pblock[]);

/* Parameter Block Initialization Function */
unsigned int vcop_disparity_hammingDistance_row_right_left_firstCall_init(
   __vptr_uint16 allCostOutput,
   __vptr_uint8 rlDisparityOutput,
   __vptr_uint16 rlMinCostOutput,
   __vptr_uint8 prevRlDisparityOutput,
   __vptr_uint16 prevRlMinCostOutput,
   __vptr_uint16 rlAllCostOutput,
   __vptr_uint8 rlDisparityScratch,
   __vptr_uint16 rlMinCostScratch,
   unsigned short allCostStride,
   unsigned short rlAllCostStride,
   unsigned short width,
   unsigned char numDisparities,
   unsigned char disparityStep,
   unsigned short pblock[]);

/* VCOP VLOOP Execution Function */
void vcop_disparity_hammingDistance_row_right_left_firstCall_vloops(
   unsigned short pblock[]);

/* Parameter Register Count */
#define PARAM_SIZE_vcop_disparity_hammingDistance_row_right_left_firstCall ((unsigned int)44)
unsigned int vcop_disparity_hammingDistance_row_right_left_firstCall_param_count(void);
/* Internal Value Count */
#define CTRL_SIZE_vcop_disparity_hammingDistance_row_right_left_firstCall ((unsigned int)0)
unsigned int vcop_disparity_hammingDistance_row_right_left_firstCall_ctrl_count(void);

/***********************************************************/
/* Parameter Register Block */
extern unsigned short __pblock_vcop_disparity_hammingDistance_row_right_left[86];

/* Basic Runner Function */
void vcop_disparity_hammingDistance_row_right_left(
   __vptr_uint16 allCostOutput,
   __vptr_uint8 rlDisparityOutput,
   __vptr_uint16 rlMinCostOutput,
   __vptr_uint8 prevRlDisparityOutput,
   __vptr_uint16 prevRlMinCostOutput,
   __vptr_uint16 rlAllCostOutput,
   __vptr_uint8 rlDisparityScratch,
   __vptr_uint16 rlMinCostScratch,
   unsigned short allCostStride,
   unsigned short rlAllCostStride,
   unsigned short width,
   unsigned char numDisparities,
   unsigned char disparityStep);
/* Custom Runner Function */
void vcop_disparity_hammingDistance_row_right_left_custom(
   __vptr_uint16 allCostOutput,
   __vptr_uint8 rlDisparityOutput,
   __vptr_uint16 rlMinCostOutput,
   __vptr_uint8 prevRlDisparityOutput,
   __vptr_uint16 prevRlMinCostOutput,
   __vptr_uint16 rlAllCostOutput,
   __vptr_uint8 rlDisparityScratch,
   __vptr_uint16 rlMinCostScratch,
   unsigned short allCostStride,
   unsigned short rlAllCostStride,
   unsigned short width,
   unsigned char numDisparities,
   unsigned char disparityStep,
   unsigned short pblock[]);

/* Parameter Block Initialization Function */
unsigned int vcop_disparity_hammingDistance_row_right_left_init(
   __vptr_uint16 allCostOutput,
   __vptr_uint8 rlDisparityOutput,
   __vptr_uint16 rlMinCostOutput,
   __vptr_uint8 prevRlDisparityOutput,
   __vptr_uint16 prevRlMinCostOutput,
   __vptr_uint16 rlAllCostOutput,
   __vptr_uint8 rlDisparityScratch,
   __vptr_uint16 rlMinCostScratch,
   unsigned short allCostStride,
   unsigned short rlAllCostStride,
   unsigned short width,
   unsigned char numDisparities,
   unsigned char disparityStep,
   unsigned short pblock[]);

/* VCOP VLOOP Execution Function */
void vcop_disparity_hammingDistance_row_right_left_vloops(
   unsigned short pblock[]);

/* Parameter Register Count */
#define PARAM_SIZE_vcop_disparity_hammingDistance_row_right_left ((unsigned int)86)
unsigned int vcop_disparity_hammingDistance_row_right_left_param_count(void);
/* Internal Value Count */
#define CTRL_SIZE_vcop_disparity_hammingDistance_row_right_left ((unsigned int)0)
unsigned int vcop_disparity_hammingDistance_row_right_left_ctrl_count(void);

/***********************************************************/
#endif

