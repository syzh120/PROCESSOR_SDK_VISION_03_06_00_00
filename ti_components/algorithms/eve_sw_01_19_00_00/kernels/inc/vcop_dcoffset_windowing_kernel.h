#ifndef _TI_vcop_dcoffset_windowing_kernel_h_
#define _TI_vcop_dcoffset_windowing_kernel_h_

/* Parameter Register Block */
extern unsigned short __pblock_vcop_interference_zero_out_kernel[16];

/* Basic Runner Function */
void vcop_interference_zero_out_kernel(
   __vptr_int16 inputData,
   __vptr_int16 outputData,
   unsigned short interferenceThreshold,
   unsigned short numPoints,
   unsigned short numOfLines,
   unsigned short inputPitch,
   unsigned short outputPitch);
/* Custom Runner Function */
void vcop_interference_zero_out_kernel_custom(
   __vptr_int16 inputData,
   __vptr_int16 outputData,
   unsigned short interferenceThreshold,
   unsigned short numPoints,
   unsigned short numOfLines,
   unsigned short inputPitch,
   unsigned short outputPitch,
   unsigned short pblock[]);

/* Parameter Block Initialization Function */
unsigned int vcop_interference_zero_out_kernel_init(
   __vptr_int16 inputData,
   __vptr_int16 outputData,
   unsigned short interferenceThreshold,
   unsigned short numPoints,
   unsigned short numOfLines,
   unsigned short inputPitch,
   unsigned short outputPitch,
   unsigned short pblock[]);

/* VCOP VLOOP Execution Function */
void vcop_interference_zero_out_kernel_vloops(
   unsigned short pblock[]);

/* Parameter Register Count */
#define PARAM_SIZE_vcop_interference_zero_out_kernel ((unsigned int)16)
unsigned int vcop_interference_zero_out_kernel_param_count(void);
/* Internal Value Count */
#define CTRL_SIZE_vcop_interference_zero_out_kernel ((unsigned int)0)
unsigned int vcop_interference_zero_out_kernel_ctrl_count(void);

/***********************************************************/
/* Parameter Register Block */
extern unsigned short __pblock_vcop_dcoffset_kernel[34];

/* Basic Runner Function */
void vcop_dcoffset_kernel(
   __vptr_int16 inputData,
   __vptr_int32 scratchBuf,
   __vptr_uint16 pScatterIndex,
   __vptr_int16 dcOffsetBuf,
   unsigned short inputPitch,
   unsigned short transposeStride,
   unsigned short numPoints,
   unsigned short numOfLines,
   unsigned short shift);
/* Custom Runner Function */
void vcop_dcoffset_kernel_custom(
   __vptr_int16 inputData,
   __vptr_int32 scratchBuf,
   __vptr_uint16 pScatterIndex,
   __vptr_int16 dcOffsetBuf,
   unsigned short inputPitch,
   unsigned short transposeStride,
   unsigned short numPoints,
   unsigned short numOfLines,
   unsigned short shift,
   unsigned short pblock[]);

/* Parameter Block Initialization Function */
unsigned int vcop_dcoffset_kernel_init(
   __vptr_int16 inputData,
   __vptr_int32 scratchBuf,
   __vptr_uint16 pScatterIndex,
   __vptr_int16 dcOffsetBuf,
   unsigned short inputPitch,
   unsigned short transposeStride,
   unsigned short numPoints,
   unsigned short numOfLines,
   unsigned short shift,
   unsigned short pblock[]);

/* VCOP VLOOP Execution Function */
void vcop_dcoffset_kernel_vloops(
   unsigned short pblock[]);

/* Parameter Register Count */
#define PARAM_SIZE_vcop_dcoffset_kernel ((unsigned int)34)
unsigned int vcop_dcoffset_kernel_param_count(void);
/* Internal Value Count */
#define CTRL_SIZE_vcop_dcoffset_kernel ((unsigned int)0)
unsigned int vcop_dcoffset_kernel_ctrl_count(void);

/***********************************************************/
/* Parameter Register Block */
extern unsigned short __pblock_vcop_windowing_kernel[26];

/* Basic Runner Function */
void vcop_windowing_kernel(
   __vptr_int16 inputData,
   __vptr_int16 winCoefficients,
   __vptr_int16 dcOffsetBuf,
   __vptr_int16 outputData,
   unsigned short numPoints,
   unsigned short numOfLines,
   unsigned short scaleFactor,
   unsigned short saturationLimit,
   unsigned short inputPitch,
   unsigned short outputPitch);
/* Custom Runner Function */
void vcop_windowing_kernel_custom(
   __vptr_int16 inputData,
   __vptr_int16 winCoefficients,
   __vptr_int16 dcOffsetBuf,
   __vptr_int16 outputData,
   unsigned short numPoints,
   unsigned short numOfLines,
   unsigned short scaleFactor,
   unsigned short saturationLimit,
   unsigned short inputPitch,
   unsigned short outputPitch,
   unsigned short pblock[]);

/* Parameter Block Initialization Function */
unsigned int vcop_windowing_kernel_init(
   __vptr_int16 inputData,
   __vptr_int16 winCoefficients,
   __vptr_int16 dcOffsetBuf,
   __vptr_int16 outputData,
   unsigned short numPoints,
   unsigned short numOfLines,
   unsigned short scaleFactor,
   unsigned short saturationLimit,
   unsigned short inputPitch,
   unsigned short outputPitch,
   unsigned short pblock[]);

/* VCOP VLOOP Execution Function */
void vcop_windowing_kernel_vloops(
   unsigned short pblock[]);

/* Parameter Register Count */
#define PARAM_SIZE_vcop_windowing_kernel ((unsigned int)26)
unsigned int vcop_windowing_kernel_param_count(void);
/* Internal Value Count */
#define CTRL_SIZE_vcop_windowing_kernel ((unsigned int)0)
unsigned int vcop_windowing_kernel_ctrl_count(void);

/***********************************************************/
/* Parameter Register Block */
extern unsigned short __pblock_vcop_windowing_with_transpose_kernel[24];

/* Basic Runner Function */
void vcop_windowing_with_transpose_kernel(
   __vptr_int16 inputData,
   __vptr_int16 winCoefficients,
   __vptr_int16 outputData,
   __vptr_uint16 pScatterIndex,
   unsigned short inputPitch,
   unsigned short transposePitch,
   unsigned short numPoints,
   unsigned short numOfLines,
   unsigned short scaleFactor,
   unsigned short saturationLimit);
/* Custom Runner Function */
void vcop_windowing_with_transpose_kernel_custom(
   __vptr_int16 inputData,
   __vptr_int16 winCoefficients,
   __vptr_int16 outputData,
   __vptr_uint16 pScatterIndex,
   unsigned short inputPitch,
   unsigned short transposePitch,
   unsigned short numPoints,
   unsigned short numOfLines,
   unsigned short scaleFactor,
   unsigned short saturationLimit,
   unsigned short pblock[]);

/* Parameter Block Initialization Function */
unsigned int vcop_windowing_with_transpose_kernel_init(
   __vptr_int16 inputData,
   __vptr_int16 winCoefficients,
   __vptr_int16 outputData,
   __vptr_uint16 pScatterIndex,
   unsigned short inputPitch,
   unsigned short transposePitch,
   unsigned short numPoints,
   unsigned short numOfLines,
   unsigned short scaleFactor,
   unsigned short saturationLimit,
   unsigned short pblock[]);

/* VCOP VLOOP Execution Function */
void vcop_windowing_with_transpose_kernel_vloops(
   unsigned short pblock[]);

/* Parameter Register Count */
#define PARAM_SIZE_vcop_windowing_with_transpose_kernel ((unsigned int)24)
unsigned int vcop_windowing_with_transpose_kernel_param_count(void);
/* Internal Value Count */
#define CTRL_SIZE_vcop_windowing_with_transpose_kernel ((unsigned int)0)
unsigned int vcop_windowing_with_transpose_kernel_ctrl_count(void);

/***********************************************************/
/* Parameter Register Block */
extern unsigned short __pblock_vcop_sign_extension_kernel[14];

/* Basic Runner Function */
void vcop_sign_extension_kernel(
   __vptr_uint16 inputData,
   __vptr_int16 outputData,
   unsigned short numPoints,
   unsigned short numOfLines,
   unsigned short inputPitch,
   unsigned short outputPitch,
   unsigned short inBits);
/* Custom Runner Function */
void vcop_sign_extension_kernel_custom(
   __vptr_uint16 inputData,
   __vptr_int16 outputData,
   unsigned short numPoints,
   unsigned short numOfLines,
   unsigned short inputPitch,
   unsigned short outputPitch,
   unsigned short inBits,
   unsigned short pblock[]);

/* Parameter Block Initialization Function */
unsigned int vcop_sign_extension_kernel_init(
   __vptr_uint16 inputData,
   __vptr_int16 outputData,
   unsigned short numPoints,
   unsigned short numOfLines,
   unsigned short inputPitch,
   unsigned short outputPitch,
   unsigned short inBits,
   unsigned short pblock[]);

/* VCOP VLOOP Execution Function */
void vcop_sign_extension_kernel_vloops(
   unsigned short pblock[]);

/* Parameter Register Count */
#define PARAM_SIZE_vcop_sign_extension_kernel ((unsigned int)14)
unsigned int vcop_sign_extension_kernel_param_count(void);
/* Internal Value Count */
#define CTRL_SIZE_vcop_sign_extension_kernel ((unsigned int)0)
unsigned int vcop_sign_extension_kernel_ctrl_count(void);

/***********************************************************/
#endif

