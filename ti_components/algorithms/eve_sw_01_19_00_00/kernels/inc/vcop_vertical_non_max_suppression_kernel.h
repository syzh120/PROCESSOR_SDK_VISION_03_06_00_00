#ifndef _TI_vcop_vertical_non_max_suppression_kernel_h_
#define _TI_vcop_vertical_non_max_suppression_kernel_h_

/* Parameter Register Block */
extern unsigned short __pblock_vcop_vertical_non_max_suppression_kernel[114];

/* Basic Runner Function */
void vcop_vertical_non_max_suppression_kernel(
   __vptr_uint32 pack_XY,
   unsigned short num_corners,
   unsigned short max_corners,
   __vptr_uint16 nms_X_Score,
   __vptr_uint16 nms_id,
   __vptr_uint16 nms_Y_Score,
   __vptr_uint16 nms_Y_XY,
   __vptr_uint32 nms_Y1_XY,
   __vptr_uint32 nms_Score,
   __vptr_uint8 Id_list);
/* Custom Runner Function */
void vcop_vertical_non_max_suppression_kernel_custom(
   __vptr_uint32 pack_XY,
   unsigned short num_corners,
   unsigned short max_corners,
   __vptr_uint16 nms_X_Score,
   __vptr_uint16 nms_id,
   __vptr_uint16 nms_Y_Score,
   __vptr_uint16 nms_Y_XY,
   __vptr_uint32 nms_Y1_XY,
   __vptr_uint32 nms_Score,
   __vptr_uint8 Id_list,
   unsigned short pblock[]);

/* Parameter Block Initialization Function */
unsigned int vcop_vertical_non_max_suppression_kernel_init(
   __vptr_uint32 pack_XY,
   unsigned short num_corners,
   unsigned short max_corners,
   __vptr_uint16 nms_X_Score,
   __vptr_uint16 nms_id,
   __vptr_uint16 nms_Y_Score,
   __vptr_uint16 nms_Y_XY,
   __vptr_uint32 nms_Y1_XY,
   __vptr_uint32 nms_Score,
   __vptr_uint8 Id_list,
   unsigned short pblock[]);

/* VCOP VLOOP Execution Function */
void vcop_vertical_non_max_suppression_kernel_vloops(
   unsigned short pblock[]);

/* Parameter Register Count */
#define PARAM_SIZE_vcop_vertical_non_max_suppression_kernel ((unsigned int)114)
unsigned int vcop_vertical_non_max_suppression_kernel_param_count(void);
/* Internal Value Count */
#define CTRL_SIZE_vcop_vertical_non_max_suppression_kernel ((unsigned int)0)
unsigned int vcop_vertical_non_max_suppression_kernel_ctrl_count(void);

/***********************************************************/
#endif

