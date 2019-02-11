#ifndef _TI_vcop_horizontal_non_max_suppression_kernel_h_
#define _TI_vcop_horizontal_non_max_suppression_kernel_h_

/* Parameter Register Block */
extern unsigned short __pblock_vcop_horizontal_non_max_suppression[116];

/* Basic Runner Function */
void vcop_horizontal_non_max_suppression(
   __vptr_uint32 pInXY,
   unsigned short num_corners,
   unsigned short max_corners,
   __vptr_uint16 Score,
   __vptr_uint32 pack_XY,
   __vptr_uint16 nms_X_Score,
   __vptr_uint8 Id_list);
/* Custom Runner Function */
void vcop_horizontal_non_max_suppression_custom(
   __vptr_uint32 pInXY,
   unsigned short num_corners,
   unsigned short max_corners,
   __vptr_uint16 Score,
   __vptr_uint32 pack_XY,
   __vptr_uint16 nms_X_Score,
   __vptr_uint8 Id_list,
   unsigned short pblock[]);

/* Parameter Block Initialization Function */
unsigned int vcop_horizontal_non_max_suppression_init(
   __vptr_uint32 pInXY,
   unsigned short num_corners,
   unsigned short max_corners,
   __vptr_uint16 Score,
   __vptr_uint32 pack_XY,
   __vptr_uint16 nms_X_Score,
   __vptr_uint8 Id_list,
   unsigned short pblock[]);

/* VCOP VLOOP Execution Function */
void vcop_horizontal_non_max_suppression_vloops(
   unsigned short pblock[]);

/* Parameter Register Count */
#define PARAM_SIZE_vcop_horizontal_non_max_suppression ((unsigned int)116)
unsigned int vcop_horizontal_non_max_suppression_param_count(void);
/* Internal Value Count */
#define CTRL_SIZE_vcop_horizontal_non_max_suppression ((unsigned int)0)
unsigned int vcop_horizontal_non_max_suppression_ctrl_count(void);

/***********************************************************/
#endif

