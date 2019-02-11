#ifndef _TI_vcop_multipoint_harrisScore_u16_kernel_h_
#define _TI_vcop_multipoint_harrisScore_u16_kernel_h_

/* Parameter Register Block */
extern unsigned short __pblock_vcop_multipoint_harrisScore_7x7_u16[160];

/* Basic Runner Function */
void vcop_multipoint_harrisScore_7x7_u16(
   __vptr_uint8 pImgBlocks_A,
   __vptr_uint16 harrisScore_C,
   unsigned short numPoints,
   unsigned short inputStride,
   unsigned short interBlockOffset,
   unsigned short sensitivityParam,
   short start_idx,
   __vptr_uint16 seq_array_C,
   __vptr_int32 vertSumX2_C,
   __vptr_int32 vertSumY2_B,
   __vptr_int32 vertSumXY_C,
   __vptr_int32 Ixx_A,
   __vptr_int32 Iyy_C,
   __vptr_int32 Ixy_A,
   __vptr_uint16 Ixx_l,
   __vptr_uint16 Iyy_l,
   __vptr_uint16 Ixy_l,
   __vptr_int16 Ixx_h,
   __vptr_int16 Iyy_h,
   __vptr_int16 Ixy_h,
   __vptr_uint32 detL_C,
   __vptr_int32 detH_C,
   __vptr_int32 pBlock);
/* Custom Runner Function */
void vcop_multipoint_harrisScore_7x7_u16_custom(
   __vptr_uint8 pImgBlocks_A,
   __vptr_uint16 harrisScore_C,
   unsigned short numPoints,
   unsigned short inputStride,
   unsigned short interBlockOffset,
   unsigned short sensitivityParam,
   short start_idx,
   __vptr_uint16 seq_array_C,
   __vptr_int32 vertSumX2_C,
   __vptr_int32 vertSumY2_B,
   __vptr_int32 vertSumXY_C,
   __vptr_int32 Ixx_A,
   __vptr_int32 Iyy_C,
   __vptr_int32 Ixy_A,
   __vptr_uint16 Ixx_l,
   __vptr_uint16 Iyy_l,
   __vptr_uint16 Ixy_l,
   __vptr_int16 Ixx_h,
   __vptr_int16 Iyy_h,
   __vptr_int16 Ixy_h,
   __vptr_uint32 detL_C,
   __vptr_int32 detH_C,
   __vptr_int32 pBlock,
   unsigned short pblock[]);

/* Parameter Block Initialization Function */
unsigned int vcop_multipoint_harrisScore_7x7_u16_init(
   __vptr_uint8 pImgBlocks_A,
   __vptr_uint16 harrisScore_C,
   unsigned short numPoints,
   unsigned short inputStride,
   unsigned short interBlockOffset,
   unsigned short sensitivityParam,
   short start_idx,
   __vptr_uint16 seq_array_C,
   __vptr_int32 vertSumX2_C,
   __vptr_int32 vertSumY2_B,
   __vptr_int32 vertSumXY_C,
   __vptr_int32 Ixx_A,
   __vptr_int32 Iyy_C,
   __vptr_int32 Ixy_A,
   __vptr_uint16 Ixx_l,
   __vptr_uint16 Iyy_l,
   __vptr_uint16 Ixy_l,
   __vptr_int16 Ixx_h,
   __vptr_int16 Iyy_h,
   __vptr_int16 Ixy_h,
   __vptr_uint32 detL_C,
   __vptr_int32 detH_C,
   __vptr_int32 pBlock,
   unsigned short pblock[]);

/* VCOP VLOOP Execution Function */
void vcop_multipoint_harrisScore_7x7_u16_vloops(
   unsigned short pblock[]);

/* Parameter Register Count */
#define PARAM_SIZE_vcop_multipoint_harrisScore_7x7_u16 ((unsigned int)160)
unsigned int vcop_multipoint_harrisScore_7x7_u16_param_count(void);
/* Internal Value Count */
#define CTRL_SIZE_vcop_multipoint_harrisScore_7x7_u16 ((unsigned int)0)
unsigned int vcop_multipoint_harrisScore_7x7_u16_ctrl_count(void);

/***********************************************************/
#endif

