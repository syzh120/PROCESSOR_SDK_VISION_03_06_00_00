#ifndef _TI_UYVY_to_YUVpl_kernel_h_
#define _TI_UYVY_to_YUVpl_kernel_h_

/* Parameter Register Block */
extern unsigned short __pblock_eve_UYVY_to_YUVpl[20];

/* Basic Runner Function */
void eve_UYVY_to_YUVpl(
   __vptr_uint16 in1_ptr,
   int width,
   int line_pitch,
   int height,
   __vptr_uint8 optr_Y,
   __vptr_uint8 optr_Cr,
   __vptr_uint8 optr_Cb);
/* Custom Runner Function */
void eve_UYVY_to_YUVpl_custom(
   __vptr_uint16 in1_ptr,
   int width,
   int line_pitch,
   int height,
   __vptr_uint8 optr_Y,
   __vptr_uint8 optr_Cr,
   __vptr_uint8 optr_Cb,
   unsigned short pblock[]);

/* Parameter Block Initialization Function */
unsigned int eve_UYVY_to_YUVpl_init(
   __vptr_uint16 in1_ptr,
   int width,
   int line_pitch,
   int height,
   __vptr_uint8 optr_Y,
   __vptr_uint8 optr_Cr,
   __vptr_uint8 optr_Cb,
   unsigned short pblock[]);

/* VCOP VLOOP Execution Function */
void eve_UYVY_to_YUVpl_vloops(
   unsigned short pblock[]);

/* Parameter Register Count */
#define PARAM_SIZE_eve_UYVY_to_YUVpl ((unsigned int)20)
unsigned int eve_UYVY_to_YUVpl_param_count(void);
/* Internal Value Count */
#define CTRL_SIZE_eve_UYVY_to_YUVpl ((unsigned int)0)
unsigned int eve_UYVY_to_YUVpl_ctrl_count(void);

/***********************************************************/
#endif

