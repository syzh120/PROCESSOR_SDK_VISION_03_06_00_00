#ifndef _TI_vcop_image_pyramid_uv_u8_kernel_h_
#define _TI_vcop_image_pyramid_uv_u8_kernel_h_

/* Parameter Register Block */
extern unsigned short __pblock_vcop_image_pyramid_uv_u8[20];

/* Basic Runner Function */
void vcop_image_pyramid_uv_u8(
   __vptr_uint8 pIn,
   unsigned short inCols,
   unsigned short inRows,
   __vptr_uint8 pOut);
/* Custom Runner Function */
void vcop_image_pyramid_uv_u8_custom(
   __vptr_uint8 pIn,
   unsigned short inCols,
   unsigned short inRows,
   __vptr_uint8 pOut,
   unsigned short pblock[]);

/* Parameter Block Initialization Function */
unsigned int vcop_image_pyramid_uv_u8_init(
   __vptr_uint8 pIn,
   unsigned short inCols,
   unsigned short inRows,
   __vptr_uint8 pOut,
   unsigned short pblock[]);

/* VCOP VLOOP Execution Function */
void vcop_image_pyramid_uv_u8_vloops(
   unsigned short pblock[]);

/* Parameter Register Count */
#define PARAM_SIZE_vcop_image_pyramid_uv_u8 ((unsigned int)20)
unsigned int vcop_image_pyramid_uv_u8_param_count(void);
/* Internal Value Count */
#define CTRL_SIZE_vcop_image_pyramid_uv_u8 ((unsigned int)0)
unsigned int vcop_image_pyramid_uv_u8_ctrl_count(void);

/***********************************************************/
#endif

