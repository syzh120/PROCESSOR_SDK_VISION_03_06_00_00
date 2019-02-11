#ifndef _TI_vcop_ncc_kernel_h_
#define _TI_vcop_ncc_kernel_h_

/* Parameter Register Block */
extern unsigned short __pblock_vcop_slidingSum[100];

/* Basic Runner Function */
void vcop_slidingSum(
   __vptr_uint8 pInput,
   unsigned short inputStride,
   unsigned short windowWidth,
   unsigned short windowHeight,
   unsigned short computeWidth,
   unsigned short computeHeight,
   __vptr_int32 pScratch,
   unsigned short scratchStride,
   __vptr_uint32 pSum,
   unsigned short sumStride,
   __vptr_uint16 pOffset,
   __vptr_int32 pScratchLine);
/* Custom Runner Function */
void vcop_slidingSum_custom(
   __vptr_uint8 pInput,
   unsigned short inputStride,
   unsigned short windowWidth,
   unsigned short windowHeight,
   unsigned short computeWidth,
   unsigned short computeHeight,
   __vptr_int32 pScratch,
   unsigned short scratchStride,
   __vptr_uint32 pSum,
   unsigned short sumStride,
   __vptr_uint16 pOffset,
   __vptr_int32 pScratchLine,
   unsigned short pblock[]);

/* Parameter Block Initialization Function */
unsigned int vcop_slidingSum_init(
   __vptr_uint8 pInput,
   unsigned short inputStride,
   unsigned short windowWidth,
   unsigned short windowHeight,
   unsigned short computeWidth,
   unsigned short computeHeight,
   __vptr_int32 pScratch,
   unsigned short scratchStride,
   __vptr_uint32 pSum,
   unsigned short sumStride,
   __vptr_uint16 pOffset,
   __vptr_int32 pScratchLine,
   unsigned short pblock[]);

/* VCOP VLOOP Execution Function */
void vcop_slidingSum_vloops(
   unsigned short pblock[]);

/* Parameter Register Count */
#define PARAM_SIZE_vcop_slidingSum ((unsigned int)100)
unsigned int vcop_slidingSum_param_count(void);
/* Internal Value Count */
#define CTRL_SIZE_vcop_slidingSum ((unsigned int)0)
unsigned int vcop_slidingSum_ctrl_count(void);

/***********************************************************/
/* Parameter Register Block */
extern unsigned short __pblock_vcop_ncc[60];

/* Basic Runner Function */
void vcop_ncc(
   __vptr_uint8 pOrgImg,
   unsigned short orgImgWidth,
   unsigned short orgImgHeight,
   unsigned short orgImgPitch,
   __vptr_int16 pTempImg,
   unsigned short tempImgWidth,
   unsigned short tempImgHeight,
   unsigned short tempImgPitch,
   __vptr_uint32 pSum,
   __vptr_uint16 pSumL,
   __vptr_uint16 pSumH,
   unsigned short sumStride,
   unsigned char sizeQshift,
   unsigned char qShift,
   __vptr_int32 pOutNumCC,
   __vptr_uint32 pOutDenomVar,
   unsigned short outPitch);
/* Custom Runner Function */
void vcop_ncc_custom(
   __vptr_uint8 pOrgImg,
   unsigned short orgImgWidth,
   unsigned short orgImgHeight,
   unsigned short orgImgPitch,
   __vptr_int16 pTempImg,
   unsigned short tempImgWidth,
   unsigned short tempImgHeight,
   unsigned short tempImgPitch,
   __vptr_uint32 pSum,
   __vptr_uint16 pSumL,
   __vptr_uint16 pSumH,
   unsigned short sumStride,
   unsigned char sizeQshift,
   unsigned char qShift,
   __vptr_int32 pOutNumCC,
   __vptr_uint32 pOutDenomVar,
   unsigned short outPitch,
   unsigned short pblock[]);

/* Parameter Block Initialization Function */
unsigned int vcop_ncc_init(
   __vptr_uint8 pOrgImg,
   unsigned short orgImgWidth,
   unsigned short orgImgHeight,
   unsigned short orgImgPitch,
   __vptr_int16 pTempImg,
   unsigned short tempImgWidth,
   unsigned short tempImgHeight,
   unsigned short tempImgPitch,
   __vptr_uint32 pSum,
   __vptr_uint16 pSumL,
   __vptr_uint16 pSumH,
   unsigned short sumStride,
   unsigned char sizeQshift,
   unsigned char qShift,
   __vptr_int32 pOutNumCC,
   __vptr_uint32 pOutDenomVar,
   unsigned short outPitch,
   unsigned short pblock[]);

/* VCOP VLOOP Execution Function */
void vcop_ncc_vloops(
   unsigned short pblock[]);

/* Parameter Register Count */
#define PARAM_SIZE_vcop_ncc ((unsigned int)60)
unsigned int vcop_ncc_param_count(void);
/* Internal Value Count */
#define CTRL_SIZE_vcop_ncc ((unsigned int)0)
unsigned int vcop_ncc_ctrl_count(void);

/***********************************************************/
/* Parameter Register Block */
extern unsigned short __pblock_vcop_ncc_qShift8[60];

/* Basic Runner Function */
void vcop_ncc_qShift8(
   __vptr_uint8 pOrgImg,
   unsigned short orgImgWidth,
   unsigned short orgImgHeight,
   unsigned short orgImgPitch,
   __vptr_int16 pTempImg,
   unsigned short tempImgWidth,
   unsigned short tempImgHeight,
   unsigned short tempImgPitch,
   __vptr_uint32 pSum,
   __vptr_uint16 pSumL,
   __vptr_uint16 pSumH,
   unsigned short sumStride,
   unsigned char sizeQshift,
   unsigned char qShift,
   __vptr_int32 pOutNumCC,
   __vptr_uint32 pOutDenomVar,
   unsigned short outPitch);
/* Custom Runner Function */
void vcop_ncc_qShift8_custom(
   __vptr_uint8 pOrgImg,
   unsigned short orgImgWidth,
   unsigned short orgImgHeight,
   unsigned short orgImgPitch,
   __vptr_int16 pTempImg,
   unsigned short tempImgWidth,
   unsigned short tempImgHeight,
   unsigned short tempImgPitch,
   __vptr_uint32 pSum,
   __vptr_uint16 pSumL,
   __vptr_uint16 pSumH,
   unsigned short sumStride,
   unsigned char sizeQshift,
   unsigned char qShift,
   __vptr_int32 pOutNumCC,
   __vptr_uint32 pOutDenomVar,
   unsigned short outPitch,
   unsigned short pblock[]);

/* Parameter Block Initialization Function */
unsigned int vcop_ncc_qShift8_init(
   __vptr_uint8 pOrgImg,
   unsigned short orgImgWidth,
   unsigned short orgImgHeight,
   unsigned short orgImgPitch,
   __vptr_int16 pTempImg,
   unsigned short tempImgWidth,
   unsigned short tempImgHeight,
   unsigned short tempImgPitch,
   __vptr_uint32 pSum,
   __vptr_uint16 pSumL,
   __vptr_uint16 pSumH,
   unsigned short sumStride,
   unsigned char sizeQshift,
   unsigned char qShift,
   __vptr_int32 pOutNumCC,
   __vptr_uint32 pOutDenomVar,
   unsigned short outPitch,
   unsigned short pblock[]);

/* VCOP VLOOP Execution Function */
void vcop_ncc_qShift8_vloops(
   unsigned short pblock[]);

/* Parameter Register Count */
#define PARAM_SIZE_vcop_ncc_qShift8 ((unsigned int)60)
unsigned int vcop_ncc_qShift8_param_count(void);
/* Internal Value Count */
#define CTRL_SIZE_vcop_ncc_qShift8 ((unsigned int)0)
unsigned int vcop_ncc_qShift8_ctrl_count(void);

/***********************************************************/
/* Parameter Register Block */
extern unsigned short __pblock_vcop_ncc_qShift0[60];

/* Basic Runner Function */
void vcop_ncc_qShift0(
   __vptr_uint8 pOrgImg,
   unsigned short orgImgWidth,
   unsigned short orgImgHeight,
   unsigned short orgImgPitch,
   __vptr_int16 pTempImg,
   unsigned short tempImgWidth,
   unsigned short tempImgHeight,
   unsigned short tempImgPitch,
   __vptr_uint32 pSum,
   __vptr_uint16 pSumL,
   __vptr_uint16 pSumH,
   unsigned short sumStride,
   unsigned char sizeQshift,
   unsigned char qShift,
   __vptr_int32 pOutNumCC,
   __vptr_uint32 pOutDenomVar,
   unsigned short outPitch);
/* Custom Runner Function */
void vcop_ncc_qShift0_custom(
   __vptr_uint8 pOrgImg,
   unsigned short orgImgWidth,
   unsigned short orgImgHeight,
   unsigned short orgImgPitch,
   __vptr_int16 pTempImg,
   unsigned short tempImgWidth,
   unsigned short tempImgHeight,
   unsigned short tempImgPitch,
   __vptr_uint32 pSum,
   __vptr_uint16 pSumL,
   __vptr_uint16 pSumH,
   unsigned short sumStride,
   unsigned char sizeQshift,
   unsigned char qShift,
   __vptr_int32 pOutNumCC,
   __vptr_uint32 pOutDenomVar,
   unsigned short outPitch,
   unsigned short pblock[]);

/* Parameter Block Initialization Function */
unsigned int vcop_ncc_qShift0_init(
   __vptr_uint8 pOrgImg,
   unsigned short orgImgWidth,
   unsigned short orgImgHeight,
   unsigned short orgImgPitch,
   __vptr_int16 pTempImg,
   unsigned short tempImgWidth,
   unsigned short tempImgHeight,
   unsigned short tempImgPitch,
   __vptr_uint32 pSum,
   __vptr_uint16 pSumL,
   __vptr_uint16 pSumH,
   unsigned short sumStride,
   unsigned char sizeQshift,
   unsigned char qShift,
   __vptr_int32 pOutNumCC,
   __vptr_uint32 pOutDenomVar,
   unsigned short outPitch,
   unsigned short pblock[]);

/* VCOP VLOOP Execution Function */
void vcop_ncc_qShift0_vloops(
   unsigned short pblock[]);

/* Parameter Register Count */
#define PARAM_SIZE_vcop_ncc_qShift0 ((unsigned int)60)
unsigned int vcop_ncc_qShift0_param_count(void);
/* Internal Value Count */
#define CTRL_SIZE_vcop_ncc_qShift0 ((unsigned int)0)
unsigned int vcop_ncc_qShift0_ctrl_count(void);

/***********************************************************/
#endif

