#ifndef _TI_eve_integral_image_kernel_h_
#define _TI_eve_integral_image_kernel_h_

/* Parameter Register Block */
extern unsigned short __pblock_eve_integral_image_reset_accv[10];

/* Basic Runner Function */
void eve_integral_image_reset_accv(
   __vptr_uint32 acc_v_ptr,
   unsigned int blk_h);
/* Custom Runner Function */
void eve_integral_image_reset_accv_custom(
   __vptr_uint32 acc_v_ptr,
   unsigned int blk_h,
   unsigned short pblock[]);

/* Parameter Block Initialization Function */
unsigned int eve_integral_image_reset_accv_init(
   __vptr_uint32 acc_v_ptr,
   unsigned int blk_h,
   unsigned short pblock[]);

/* VCOP VLOOP Execution Function */
void eve_integral_image_reset_accv_vloops(
   unsigned short pblock[]);

/* Parameter Register Count */
#define PARAM_SIZE_eve_integral_image_reset_accv ((unsigned int)10)
unsigned int eve_integral_image_reset_accv_param_count(void);
/* Internal Value Count */
#define CTRL_SIZE_eve_integral_image_reset_accv ((unsigned int)0)
unsigned int eve_integral_image_reset_accv_ctrl_count(void);

/***********************************************************/
/* Parameter Register Block */
extern unsigned short __pblock_eve_integral_image_reset_acch[10];

/* Basic Runner Function */
void eve_integral_image_reset_acch(
   __vptr_uint32 acc_h_ptr,
   unsigned int blk_w);
/* Custom Runner Function */
void eve_integral_image_reset_acch_custom(
   __vptr_uint32 acc_h_ptr,
   unsigned int blk_w,
   unsigned short pblock[]);

/* Parameter Block Initialization Function */
unsigned int eve_integral_image_reset_acch_init(
   __vptr_uint32 acc_h_ptr,
   unsigned int blk_w,
   unsigned short pblock[]);

/* VCOP VLOOP Execution Function */
void eve_integral_image_reset_acch_vloops(
   unsigned short pblock[]);

/* Parameter Register Count */
#define PARAM_SIZE_eve_integral_image_reset_acch ((unsigned int)10)
unsigned int eve_integral_image_reset_acch_param_count(void);
/* Internal Value Count */
#define CTRL_SIZE_eve_integral_image_reset_acch ((unsigned int)0)
unsigned int eve_integral_image_reset_acch_ctrl_count(void);

/***********************************************************/
/* Parameter Register Block */
extern unsigned short __pblock_eve_integral_image_u8_int_int[64];

/* Basic Runner Function */
void eve_integral_image_u8_int_int(
   unsigned int blk_w,
   unsigned int blk_h,
   unsigned int in_width,
   __vptr_uint32 acc_h_ptr,
   __vptr_uint32 acc_v_ptr,
   __vptr_uint8 in_ptr,
   __vptr_uint32 B0_ptr,
   __vptr_uint32 B1_ptr,
   __vptr_uint32 C0_ptr,
   __vptr_uint32 C1_ptr,
   __vptr_uint32 out_ptr,
   __vptr_uint32 out_acc_h_ptr);
/* Custom Runner Function */
void eve_integral_image_u8_int_int_custom(
   unsigned int blk_w,
   unsigned int blk_h,
   unsigned int in_width,
   __vptr_uint32 acc_h_ptr,
   __vptr_uint32 acc_v_ptr,
   __vptr_uint8 in_ptr,
   __vptr_uint32 B0_ptr,
   __vptr_uint32 B1_ptr,
   __vptr_uint32 C0_ptr,
   __vptr_uint32 C1_ptr,
   __vptr_uint32 out_ptr,
   __vptr_uint32 out_acc_h_ptr,
   unsigned short pblock[]);

/* Parameter Block Initialization Function */
unsigned int eve_integral_image_u8_int_int_init(
   unsigned int blk_w,
   unsigned int blk_h,
   unsigned int in_width,
   __vptr_uint32 acc_h_ptr,
   __vptr_uint32 acc_v_ptr,
   __vptr_uint8 in_ptr,
   __vptr_uint32 B0_ptr,
   __vptr_uint32 B1_ptr,
   __vptr_uint32 C0_ptr,
   __vptr_uint32 C1_ptr,
   __vptr_uint32 out_ptr,
   __vptr_uint32 out_acc_h_ptr,
   unsigned short pblock[]);

/* VCOP VLOOP Execution Function */
void eve_integral_image_u8_int_int_vloops(
   unsigned short pblock[]);

/* Parameter Register Count */
#define PARAM_SIZE_eve_integral_image_u8_int_int ((unsigned int)64)
unsigned int eve_integral_image_u8_int_int_param_count(void);
/* Internal Value Count */
#define CTRL_SIZE_eve_integral_image_u8_int_int ((unsigned int)0)
unsigned int eve_integral_image_u8_int_int_ctrl_count(void);

/***********************************************************/
/* Parameter Register Block */
extern unsigned short __pblock_eve_integral_image_u16_int_int[60];

/* Basic Runner Function */
void eve_integral_image_u16_int_int(
   unsigned int blk_w,
   unsigned int blk_h,
   unsigned int in_width,
   __vptr_uint32 acc_h_ptr,
   __vptr_uint32 acc_v_ptr,
   __vptr_uint16 in_ptr,
   __vptr_uint32 B0_ptr,
   __vptr_uint32 B1_ptr,
   __vptr_uint32 C0_ptr,
   __vptr_uint32 C1_ptr,
   __vptr_uint32 out_ptr);
/* Custom Runner Function */
void eve_integral_image_u16_int_int_custom(
   unsigned int blk_w,
   unsigned int blk_h,
   unsigned int in_width,
   __vptr_uint32 acc_h_ptr,
   __vptr_uint32 acc_v_ptr,
   __vptr_uint16 in_ptr,
   __vptr_uint32 B0_ptr,
   __vptr_uint32 B1_ptr,
   __vptr_uint32 C0_ptr,
   __vptr_uint32 C1_ptr,
   __vptr_uint32 out_ptr,
   unsigned short pblock[]);

/* Parameter Block Initialization Function */
unsigned int eve_integral_image_u16_int_int_init(
   unsigned int blk_w,
   unsigned int blk_h,
   unsigned int in_width,
   __vptr_uint32 acc_h_ptr,
   __vptr_uint32 acc_v_ptr,
   __vptr_uint16 in_ptr,
   __vptr_uint32 B0_ptr,
   __vptr_uint32 B1_ptr,
   __vptr_uint32 C0_ptr,
   __vptr_uint32 C1_ptr,
   __vptr_uint32 out_ptr,
   unsigned short pblock[]);

/* VCOP VLOOP Execution Function */
void eve_integral_image_u16_int_int_vloops(
   unsigned short pblock[]);

/* Parameter Register Count */
#define PARAM_SIZE_eve_integral_image_u16_int_int ((unsigned int)60)
unsigned int eve_integral_image_u16_int_int_param_count(void);
/* Internal Value Count */
#define CTRL_SIZE_eve_integral_image_u16_int_int ((unsigned int)0)
unsigned int eve_integral_image_u16_int_int_ctrl_count(void);

/***********************************************************/
#endif

