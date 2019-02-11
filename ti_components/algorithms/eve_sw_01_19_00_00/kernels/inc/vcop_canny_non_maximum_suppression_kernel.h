#ifndef _TI_vcop_canny_non_maximum_suppression_kernel_h_
#define _TI_vcop_canny_non_maximum_suppression_kernel_h_

/* Parameter Register Block */
extern unsigned short __pblock_vcop_canny_bin_indexing[20];

/* Basic Runner Function */
void vcop_canny_bin_indexing(
   __vptr_int16 pGx,
   __vptr_int16 pGy,
   __vptr_uint8 pIndex,
   unsigned short computeWidth,
   unsigned short computeHeight,
   unsigned short pitch);
/* Custom Runner Function */
void vcop_canny_bin_indexing_custom(
   __vptr_int16 pGx,
   __vptr_int16 pGy,
   __vptr_uint8 pIndex,
   unsigned short computeWidth,
   unsigned short computeHeight,
   unsigned short pitch,
   unsigned short pblock[]);

/* Parameter Block Initialization Function */
unsigned int vcop_canny_bin_indexing_init(
   __vptr_int16 pGx,
   __vptr_int16 pGy,
   __vptr_uint8 pIndex,
   unsigned short computeWidth,
   unsigned short computeHeight,
   unsigned short pitch,
   unsigned short pblock[]);

/* VCOP VLOOP Execution Function */
void vcop_canny_bin_indexing_vloops(
   unsigned short pblock[]);

/* Parameter Register Count */
#define PARAM_SIZE_vcop_canny_bin_indexing ((unsigned int)20)
unsigned int vcop_canny_bin_indexing_param_count(void);
/* Internal Value Count */
#define CTRL_SIZE_vcop_canny_bin_indexing ((unsigned int)0)
unsigned int vcop_canny_bin_indexing_ctrl_count(void);

/***********************************************************/
/* Parameter Register Block */
extern unsigned short __pblock_vcop_canny_nms_max_cases[30];

/* Basic Runner Function */
void vcop_canny_nms_max_cases(
   __vptr_uint16 pMag,
   __vptr_uint16 pCase1Max,
   __vptr_uint16 pCase2Max,
   __vptr_uint16 pCase3Max,
   __vptr_uint16 pCase4Max,
   unsigned short computeWidth,
   unsigned short computeHeight,
   unsigned short pitch);
/* Custom Runner Function */
void vcop_canny_nms_max_cases_custom(
   __vptr_uint16 pMag,
   __vptr_uint16 pCase1Max,
   __vptr_uint16 pCase2Max,
   __vptr_uint16 pCase3Max,
   __vptr_uint16 pCase4Max,
   unsigned short computeWidth,
   unsigned short computeHeight,
   unsigned short pitch,
   unsigned short pblock[]);

/* Parameter Block Initialization Function */
unsigned int vcop_canny_nms_max_cases_init(
   __vptr_uint16 pMag,
   __vptr_uint16 pCase1Max,
   __vptr_uint16 pCase2Max,
   __vptr_uint16 pCase3Max,
   __vptr_uint16 pCase4Max,
   unsigned short computeWidth,
   unsigned short computeHeight,
   unsigned short pitch,
   unsigned short pblock[]);

/* VCOP VLOOP Execution Function */
void vcop_canny_nms_max_cases_vloops(
   unsigned short pblock[]);

/* Parameter Register Count */
#define PARAM_SIZE_vcop_canny_nms_max_cases ((unsigned int)30)
unsigned int vcop_canny_nms_max_cases_param_count(void);
/* Internal Value Count */
#define CTRL_SIZE_vcop_canny_nms_max_cases ((unsigned int)0)
unsigned int vcop_canny_nms_max_cases_ctrl_count(void);

/***********************************************************/
/* Parameter Register Block */
extern unsigned short __pblock_vcop_canny_nms_double_thresholding[34];

/* Basic Runner Function */
void vcop_canny_nms_double_thresholding(
   __vptr_uint8 pIndex,
   __vptr_uint16 pCase1Max,
   __vptr_uint16 pCase2Max,
   __vptr_uint16 pCase3Max,
   __vptr_uint16 pCase4Max,
   __vptr_uint8 pOutVal,
   unsigned char lowThreshold,
   unsigned char highThreshold,
   unsigned short width,
   unsigned short height,
   unsigned short pitch,
   unsigned short outputPitch);
/* Custom Runner Function */
void vcop_canny_nms_double_thresholding_custom(
   __vptr_uint8 pIndex,
   __vptr_uint16 pCase1Max,
   __vptr_uint16 pCase2Max,
   __vptr_uint16 pCase3Max,
   __vptr_uint16 pCase4Max,
   __vptr_uint8 pOutVal,
   unsigned char lowThreshold,
   unsigned char highThreshold,
   unsigned short width,
   unsigned short height,
   unsigned short pitch,
   unsigned short outputPitch,
   unsigned short pblock[]);

/* Parameter Block Initialization Function */
unsigned int vcop_canny_nms_double_thresholding_init(
   __vptr_uint8 pIndex,
   __vptr_uint16 pCase1Max,
   __vptr_uint16 pCase2Max,
   __vptr_uint16 pCase3Max,
   __vptr_uint16 pCase4Max,
   __vptr_uint8 pOutVal,
   unsigned char lowThreshold,
   unsigned char highThreshold,
   unsigned short width,
   unsigned short height,
   unsigned short pitch,
   unsigned short outputPitch,
   unsigned short pblock[]);

/* VCOP VLOOP Execution Function */
void vcop_canny_nms_double_thresholding_vloops(
   unsigned short pblock[]);

/* Parameter Register Count */
#define PARAM_SIZE_vcop_canny_nms_double_thresholding ((unsigned int)34)
unsigned int vcop_canny_nms_double_thresholding_param_count(void);
/* Internal Value Count */
#define CTRL_SIZE_vcop_canny_nms_double_thresholding ((unsigned int)0)
unsigned int vcop_canny_nms_double_thresholding_ctrl_count(void);

/***********************************************************/
#endif

