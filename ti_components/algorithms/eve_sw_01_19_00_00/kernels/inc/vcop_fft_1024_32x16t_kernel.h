#ifndef _TI_vcop_fft_1024_32x16t_kernel_h_
#define _TI_vcop_fft_1024_32x16t_kernel_h_

/* Parameter Register Block */
extern unsigned short __pblock_vcop_fft_1024_32x16t_stage1_0[38];

/* Basic Runner Function */
void vcop_fft_1024_32x16t_stage1_0(
   __vptr_int32 Pin_xyL0_0123,
   __vptr_int32 Pin_xyL0_4567,
   __vptr_int32 Pin_xyL1_0123,
   __vptr_int32 Pin_xyL1_4567,
   __vptr_int32 Pin_xyL2_0123,
   __vptr_int32 Pin_xyL2_4567,
   __vptr_int32 Pin_xyL3_0123,
   __vptr_int32 Pin_xyL3_4567,
   __vptr_int32 Pou_xyL0_0123,
   __vptr_int32 Pou_xyL0_4567,
   __vptr_int32 Pou_xyL1_0123,
   __vptr_int32 Pou_xyL1_4567,
   __vptr_int32 Pou_xyL2_0123,
   __vptr_int32 Pou_xyL2_4567,
   __vptr_int32 Pou_xyL3_0123,
   __vptr_int32 Pou_xyL3_4567);
/* Custom Runner Function */
void vcop_fft_1024_32x16t_stage1_0_custom(
   __vptr_int32 Pin_xyL0_0123,
   __vptr_int32 Pin_xyL0_4567,
   __vptr_int32 Pin_xyL1_0123,
   __vptr_int32 Pin_xyL1_4567,
   __vptr_int32 Pin_xyL2_0123,
   __vptr_int32 Pin_xyL2_4567,
   __vptr_int32 Pin_xyL3_0123,
   __vptr_int32 Pin_xyL3_4567,
   __vptr_int32 Pou_xyL0_0123,
   __vptr_int32 Pou_xyL0_4567,
   __vptr_int32 Pou_xyL1_0123,
   __vptr_int32 Pou_xyL1_4567,
   __vptr_int32 Pou_xyL2_0123,
   __vptr_int32 Pou_xyL2_4567,
   __vptr_int32 Pou_xyL3_0123,
   __vptr_int32 Pou_xyL3_4567,
   unsigned short pblock[]);

/* Parameter Block Initialization Function */
unsigned int vcop_fft_1024_32x16t_stage1_0_init(
   __vptr_int32 Pin_xyL0_0123,
   __vptr_int32 Pin_xyL0_4567,
   __vptr_int32 Pin_xyL1_0123,
   __vptr_int32 Pin_xyL1_4567,
   __vptr_int32 Pin_xyL2_0123,
   __vptr_int32 Pin_xyL2_4567,
   __vptr_int32 Pin_xyL3_0123,
   __vptr_int32 Pin_xyL3_4567,
   __vptr_int32 Pou_xyL0_0123,
   __vptr_int32 Pou_xyL0_4567,
   __vptr_int32 Pou_xyL1_0123,
   __vptr_int32 Pou_xyL1_4567,
   __vptr_int32 Pou_xyL2_0123,
   __vptr_int32 Pou_xyL2_4567,
   __vptr_int32 Pou_xyL3_0123,
   __vptr_int32 Pou_xyL3_4567,
   unsigned short pblock[]);

/* VCOP VLOOP Execution Function */
void vcop_fft_1024_32x16t_stage1_0_vloops(
   unsigned short pblock[]);

/* Parameter Register Count */
#define PARAM_SIZE_vcop_fft_1024_32x16t_stage1_0 ((unsigned int)38)
unsigned int vcop_fft_1024_32x16t_stage1_0_param_count(void);
/* Internal Value Count */
#define CTRL_SIZE_vcop_fft_1024_32x16t_stage1_0 ((unsigned int)0)
unsigned int vcop_fft_1024_32x16t_stage1_0_ctrl_count(void);

/***********************************************************/
/* Parameter Register Block */
extern unsigned short __pblock_vcop_fft_1024_32x16t_stage1_1[26];

/* Basic Runner Function */
void vcop_fft_1024_32x16t_stage1_1(
   __vptr_uint16 inp1_l,
   __vptr_int16 inp1_h,
   __vptr_int16 CS,
   __vptr_int32 out);
/* Custom Runner Function */
void vcop_fft_1024_32x16t_stage1_1_custom(
   __vptr_uint16 inp1_l,
   __vptr_int16 inp1_h,
   __vptr_int16 CS,
   __vptr_int32 out,
   unsigned short pblock[]);

/* Parameter Block Initialization Function */
unsigned int vcop_fft_1024_32x16t_stage1_1_init(
   __vptr_uint16 inp1_l,
   __vptr_int16 inp1_h,
   __vptr_int16 CS,
   __vptr_int32 out,
   unsigned short pblock[]);

/* VCOP VLOOP Execution Function */
void vcop_fft_1024_32x16t_stage1_1_vloops(
   unsigned short pblock[]);

/* Parameter Register Count */
#define PARAM_SIZE_vcop_fft_1024_32x16t_stage1_1 ((unsigned int)26)
unsigned int vcop_fft_1024_32x16t_stage1_1_param_count(void);
/* Internal Value Count */
#define CTRL_SIZE_vcop_fft_1024_32x16t_stage1_1 ((unsigned int)0)
unsigned int vcop_fft_1024_32x16t_stage1_1_ctrl_count(void);

/***********************************************************/
/* Parameter Register Block */
extern unsigned short __pblock_vcop_fft_1024_32x16t_stage2_0[38];

/* Basic Runner Function */
void vcop_fft_1024_32x16t_stage2_0(
   __vptr_int32 Pin_xyL0_0123,
   __vptr_int32 Pin_xyL0_4567,
   __vptr_int32 Pin_xyL1_0123,
   __vptr_int32 Pin_xyL1_4567,
   __vptr_int32 Pin_xyL2_0123,
   __vptr_int32 Pin_xyL2_4567,
   __vptr_int32 Pin_xyL3_0123,
   __vptr_int32 Pin_xyL3_4567,
   __vptr_int32 Pou_xyL0_0123,
   __vptr_int32 Pou_xyL0_4567,
   __vptr_int32 Pou_xyL1_0123,
   __vptr_int32 Pou_xyL1_4567,
   __vptr_int32 Pou_xyL2_0123,
   __vptr_int32 Pou_xyL2_4567,
   __vptr_int32 Pou_xyL3_0123,
   __vptr_int32 Pou_xyL3_4567);
/* Custom Runner Function */
void vcop_fft_1024_32x16t_stage2_0_custom(
   __vptr_int32 Pin_xyL0_0123,
   __vptr_int32 Pin_xyL0_4567,
   __vptr_int32 Pin_xyL1_0123,
   __vptr_int32 Pin_xyL1_4567,
   __vptr_int32 Pin_xyL2_0123,
   __vptr_int32 Pin_xyL2_4567,
   __vptr_int32 Pin_xyL3_0123,
   __vptr_int32 Pin_xyL3_4567,
   __vptr_int32 Pou_xyL0_0123,
   __vptr_int32 Pou_xyL0_4567,
   __vptr_int32 Pou_xyL1_0123,
   __vptr_int32 Pou_xyL1_4567,
   __vptr_int32 Pou_xyL2_0123,
   __vptr_int32 Pou_xyL2_4567,
   __vptr_int32 Pou_xyL3_0123,
   __vptr_int32 Pou_xyL3_4567,
   unsigned short pblock[]);

/* Parameter Block Initialization Function */
unsigned int vcop_fft_1024_32x16t_stage2_0_init(
   __vptr_int32 Pin_xyL0_0123,
   __vptr_int32 Pin_xyL0_4567,
   __vptr_int32 Pin_xyL1_0123,
   __vptr_int32 Pin_xyL1_4567,
   __vptr_int32 Pin_xyL2_0123,
   __vptr_int32 Pin_xyL2_4567,
   __vptr_int32 Pin_xyL3_0123,
   __vptr_int32 Pin_xyL3_4567,
   __vptr_int32 Pou_xyL0_0123,
   __vptr_int32 Pou_xyL0_4567,
   __vptr_int32 Pou_xyL1_0123,
   __vptr_int32 Pou_xyL1_4567,
   __vptr_int32 Pou_xyL2_0123,
   __vptr_int32 Pou_xyL2_4567,
   __vptr_int32 Pou_xyL3_0123,
   __vptr_int32 Pou_xyL3_4567,
   unsigned short pblock[]);

/* VCOP VLOOP Execution Function */
void vcop_fft_1024_32x16t_stage2_0_vloops(
   unsigned short pblock[]);

/* Parameter Register Count */
#define PARAM_SIZE_vcop_fft_1024_32x16t_stage2_0 ((unsigned int)38)
unsigned int vcop_fft_1024_32x16t_stage2_0_param_count(void);
/* Internal Value Count */
#define CTRL_SIZE_vcop_fft_1024_32x16t_stage2_0 ((unsigned int)0)
unsigned int vcop_fft_1024_32x16t_stage2_0_ctrl_count(void);

/***********************************************************/
/* Parameter Register Block */
extern unsigned short __pblock_vcop_fft_1024_32x16t_stage2_1[28];

/* Basic Runner Function */
void vcop_fft_1024_32x16t_stage2_1(
   __vptr_uint16 inp1_l,
   __vptr_int16 inp1_h,
   __vptr_int16 CS,
   __vptr_int32 out);
/* Custom Runner Function */
void vcop_fft_1024_32x16t_stage2_1_custom(
   __vptr_uint16 inp1_l,
   __vptr_int16 inp1_h,
   __vptr_int16 CS,
   __vptr_int32 out,
   unsigned short pblock[]);

/* Parameter Block Initialization Function */
unsigned int vcop_fft_1024_32x16t_stage2_1_init(
   __vptr_uint16 inp1_l,
   __vptr_int16 inp1_h,
   __vptr_int16 CS,
   __vptr_int32 out,
   unsigned short pblock[]);

/* VCOP VLOOP Execution Function */
void vcop_fft_1024_32x16t_stage2_1_vloops(
   unsigned short pblock[]);

/* Parameter Register Count */
#define PARAM_SIZE_vcop_fft_1024_32x16t_stage2_1 ((unsigned int)28)
unsigned int vcop_fft_1024_32x16t_stage2_1_param_count(void);
/* Internal Value Count */
#define CTRL_SIZE_vcop_fft_1024_32x16t_stage2_1 ((unsigned int)0)
unsigned int vcop_fft_1024_32x16t_stage2_1_ctrl_count(void);

/***********************************************************/
/* Parameter Register Block */
extern unsigned short __pblock_vcop_fft_1024_32x16t_stage3_0[42];

/* Basic Runner Function */
void vcop_fft_1024_32x16t_stage3_0(
   __vptr_int32 Pin_xyL0_0123,
   __vptr_int32 Pin_xyL0_4567,
   __vptr_int32 Pin_xyL1_0123,
   __vptr_int32 Pin_xyL1_4567,
   __vptr_int32 Pin_xyL2_0123,
   __vptr_int32 Pin_xyL2_4567,
   __vptr_int32 Pin_xyL3_0123,
   __vptr_int32 Pin_xyL3_4567,
   __vptr_int32 Pou_xyL0_0123,
   __vptr_int32 Pou_xyL0_4567,
   __vptr_int32 Pou_xyL1_0123,
   __vptr_int32 Pou_xyL1_4567,
   __vptr_int32 Pou_xyL2_0123,
   __vptr_int32 Pou_xyL2_4567,
   __vptr_int32 Pou_xyL3_0123,
   __vptr_int32 Pou_xyL3_4567);
/* Custom Runner Function */
void vcop_fft_1024_32x16t_stage3_0_custom(
   __vptr_int32 Pin_xyL0_0123,
   __vptr_int32 Pin_xyL0_4567,
   __vptr_int32 Pin_xyL1_0123,
   __vptr_int32 Pin_xyL1_4567,
   __vptr_int32 Pin_xyL2_0123,
   __vptr_int32 Pin_xyL2_4567,
   __vptr_int32 Pin_xyL3_0123,
   __vptr_int32 Pin_xyL3_4567,
   __vptr_int32 Pou_xyL0_0123,
   __vptr_int32 Pou_xyL0_4567,
   __vptr_int32 Pou_xyL1_0123,
   __vptr_int32 Pou_xyL1_4567,
   __vptr_int32 Pou_xyL2_0123,
   __vptr_int32 Pou_xyL2_4567,
   __vptr_int32 Pou_xyL3_0123,
   __vptr_int32 Pou_xyL3_4567,
   unsigned short pblock[]);

/* Parameter Block Initialization Function */
unsigned int vcop_fft_1024_32x16t_stage3_0_init(
   __vptr_int32 Pin_xyL0_0123,
   __vptr_int32 Pin_xyL0_4567,
   __vptr_int32 Pin_xyL1_0123,
   __vptr_int32 Pin_xyL1_4567,
   __vptr_int32 Pin_xyL2_0123,
   __vptr_int32 Pin_xyL2_4567,
   __vptr_int32 Pin_xyL3_0123,
   __vptr_int32 Pin_xyL3_4567,
   __vptr_int32 Pou_xyL0_0123,
   __vptr_int32 Pou_xyL0_4567,
   __vptr_int32 Pou_xyL1_0123,
   __vptr_int32 Pou_xyL1_4567,
   __vptr_int32 Pou_xyL2_0123,
   __vptr_int32 Pou_xyL2_4567,
   __vptr_int32 Pou_xyL3_0123,
   __vptr_int32 Pou_xyL3_4567,
   unsigned short pblock[]);

/* VCOP VLOOP Execution Function */
void vcop_fft_1024_32x16t_stage3_0_vloops(
   unsigned short pblock[]);

/* Parameter Register Count */
#define PARAM_SIZE_vcop_fft_1024_32x16t_stage3_0 ((unsigned int)42)
unsigned int vcop_fft_1024_32x16t_stage3_0_param_count(void);
/* Internal Value Count */
#define CTRL_SIZE_vcop_fft_1024_32x16t_stage3_0 ((unsigned int)0)
unsigned int vcop_fft_1024_32x16t_stage3_0_ctrl_count(void);

/***********************************************************/
/* Parameter Register Block */
extern unsigned short __pblock_vcop_fft_1024_32x16t_stage3_1[30];

/* Basic Runner Function */
void vcop_fft_1024_32x16t_stage3_1(
   __vptr_uint16 inp1_lx,
   __vptr_int16 inp1_hx,
   __vptr_uint16 inp1_ly,
   __vptr_int16 inp1_hy,
   __vptr_int16 C,
   __vptr_int16 S,
   __vptr_int32 out_x,
   __vptr_int32 out_y);
/* Custom Runner Function */
void vcop_fft_1024_32x16t_stage3_1_custom(
   __vptr_uint16 inp1_lx,
   __vptr_int16 inp1_hx,
   __vptr_uint16 inp1_ly,
   __vptr_int16 inp1_hy,
   __vptr_int16 C,
   __vptr_int16 S,
   __vptr_int32 out_x,
   __vptr_int32 out_y,
   unsigned short pblock[]);

/* Parameter Block Initialization Function */
unsigned int vcop_fft_1024_32x16t_stage3_1_init(
   __vptr_uint16 inp1_lx,
   __vptr_int16 inp1_hx,
   __vptr_uint16 inp1_ly,
   __vptr_int16 inp1_hy,
   __vptr_int16 C,
   __vptr_int16 S,
   __vptr_int32 out_x,
   __vptr_int32 out_y,
   unsigned short pblock[]);

/* VCOP VLOOP Execution Function */
void vcop_fft_1024_32x16t_stage3_1_vloops(
   unsigned short pblock[]);

/* Parameter Register Count */
#define PARAM_SIZE_vcop_fft_1024_32x16t_stage3_1 ((unsigned int)30)
unsigned int vcop_fft_1024_32x16t_stage3_1_param_count(void);
/* Internal Value Count */
#define CTRL_SIZE_vcop_fft_1024_32x16t_stage3_1 ((unsigned int)0)
unsigned int vcop_fft_1024_32x16t_stage3_1_ctrl_count(void);

/***********************************************************/
/* Parameter Register Block */
extern unsigned short __pblock_vcop_fft_1024_32x16t_stage4_0[38];

/* Basic Runner Function */
void vcop_fft_1024_32x16t_stage4_0(
   __vptr_int32 Pin_xL0_01234567,
   __vptr_int32 Pin_yL0_01234567,
   __vptr_int32 Pin_xL1_01234567,
   __vptr_int32 Pin_yL1_01234567,
   __vptr_int32 Pin_xL2_01234567,
   __vptr_int32 Pin_yL2_01234567,
   __vptr_int32 Pin_xL3_01234567,
   __vptr_int32 Pin_yL3_01234567,
   __vptr_int32 Pou_xL0_01234567,
   __vptr_int32 Pou_yL0_01234567,
   __vptr_int32 Pou_xL1_01234567,
   __vptr_int32 Pou_yL1_01234567,
   __vptr_int32 Pou_xL2_01234567,
   __vptr_int32 Pou_yL2_01234567,
   __vptr_int32 Pou_xL3_01234567,
   __vptr_int32 Pou_yL3_01234567);
/* Custom Runner Function */
void vcop_fft_1024_32x16t_stage4_0_custom(
   __vptr_int32 Pin_xL0_01234567,
   __vptr_int32 Pin_yL0_01234567,
   __vptr_int32 Pin_xL1_01234567,
   __vptr_int32 Pin_yL1_01234567,
   __vptr_int32 Pin_xL2_01234567,
   __vptr_int32 Pin_yL2_01234567,
   __vptr_int32 Pin_xL3_01234567,
   __vptr_int32 Pin_yL3_01234567,
   __vptr_int32 Pou_xL0_01234567,
   __vptr_int32 Pou_yL0_01234567,
   __vptr_int32 Pou_xL1_01234567,
   __vptr_int32 Pou_yL1_01234567,
   __vptr_int32 Pou_xL2_01234567,
   __vptr_int32 Pou_yL2_01234567,
   __vptr_int32 Pou_xL3_01234567,
   __vptr_int32 Pou_yL3_01234567,
   unsigned short pblock[]);

/* Parameter Block Initialization Function */
unsigned int vcop_fft_1024_32x16t_stage4_0_init(
   __vptr_int32 Pin_xL0_01234567,
   __vptr_int32 Pin_yL0_01234567,
   __vptr_int32 Pin_xL1_01234567,
   __vptr_int32 Pin_yL1_01234567,
   __vptr_int32 Pin_xL2_01234567,
   __vptr_int32 Pin_yL2_01234567,
   __vptr_int32 Pin_xL3_01234567,
   __vptr_int32 Pin_yL3_01234567,
   __vptr_int32 Pou_xL0_01234567,
   __vptr_int32 Pou_yL0_01234567,
   __vptr_int32 Pou_xL1_01234567,
   __vptr_int32 Pou_yL1_01234567,
   __vptr_int32 Pou_xL2_01234567,
   __vptr_int32 Pou_yL2_01234567,
   __vptr_int32 Pou_xL3_01234567,
   __vptr_int32 Pou_yL3_01234567,
   unsigned short pblock[]);

/* VCOP VLOOP Execution Function */
void vcop_fft_1024_32x16t_stage4_0_vloops(
   unsigned short pblock[]);

/* Parameter Register Count */
#define PARAM_SIZE_vcop_fft_1024_32x16t_stage4_0 ((unsigned int)38)
unsigned int vcop_fft_1024_32x16t_stage4_0_param_count(void);
/* Internal Value Count */
#define CTRL_SIZE_vcop_fft_1024_32x16t_stage4_0 ((unsigned int)0)
unsigned int vcop_fft_1024_32x16t_stage4_0_ctrl_count(void);

/***********************************************************/
/* Parameter Register Block */
extern unsigned short __pblock_vcop_fft_1024_32x16t_stage4_1[28];

/* Basic Runner Function */
void vcop_fft_1024_32x16t_stage4_1(
   __vptr_uint16 inp1_lx,
   __vptr_int16 inp1_hx,
   __vptr_uint16 inp1_ly,
   __vptr_int16 inp1_hy,
   __vptr_int16 CS,
   __vptr_int32 out_x,
   __vptr_int32 out_y);
/* Custom Runner Function */
void vcop_fft_1024_32x16t_stage4_1_custom(
   __vptr_uint16 inp1_lx,
   __vptr_int16 inp1_hx,
   __vptr_uint16 inp1_ly,
   __vptr_int16 inp1_hy,
   __vptr_int16 CS,
   __vptr_int32 out_x,
   __vptr_int32 out_y,
   unsigned short pblock[]);

/* Parameter Block Initialization Function */
unsigned int vcop_fft_1024_32x16t_stage4_1_init(
   __vptr_uint16 inp1_lx,
   __vptr_int16 inp1_hx,
   __vptr_uint16 inp1_ly,
   __vptr_int16 inp1_hy,
   __vptr_int16 CS,
   __vptr_int32 out_x,
   __vptr_int32 out_y,
   unsigned short pblock[]);

/* VCOP VLOOP Execution Function */
void vcop_fft_1024_32x16t_stage4_1_vloops(
   unsigned short pblock[]);

/* Parameter Register Count */
#define PARAM_SIZE_vcop_fft_1024_32x16t_stage4_1 ((unsigned int)28)
unsigned int vcop_fft_1024_32x16t_stage4_1_param_count(void);
/* Internal Value Count */
#define CTRL_SIZE_vcop_fft_1024_32x16t_stage4_1 ((unsigned int)0)
unsigned int vcop_fft_1024_32x16t_stage4_1_ctrl_count(void);

/***********************************************************/
/* Parameter Register Block */
extern unsigned short __pblock_vcop_fft_1024_32x16t_stage5[40];

/* Basic Runner Function */
void vcop_fft_1024_32x16t_stage5(
   __vptr_int32 Pxi0,
   __vptr_int32 Pyi0,
   __vptr_int32 Pxi1,
   __vptr_int32 Pyi1,
   __vptr_int32 Pxi2,
   __vptr_int32 Pyi2,
   __vptr_int32 Pxi3,
   __vptr_int32 Pyi3,
   __vptr_int32 Pox0,
   __vptr_int32 Poy0,
   __vptr_int32 Pox1,
   __vptr_int32 Poy1,
   __vptr_int32 Pox2,
   __vptr_int32 Poy2,
   __vptr_int32 Pox3,
   __vptr_int32 Poy3);
/* Custom Runner Function */
void vcop_fft_1024_32x16t_stage5_custom(
   __vptr_int32 Pxi0,
   __vptr_int32 Pyi0,
   __vptr_int32 Pxi1,
   __vptr_int32 Pyi1,
   __vptr_int32 Pxi2,
   __vptr_int32 Pyi2,
   __vptr_int32 Pxi3,
   __vptr_int32 Pyi3,
   __vptr_int32 Pox0,
   __vptr_int32 Poy0,
   __vptr_int32 Pox1,
   __vptr_int32 Poy1,
   __vptr_int32 Pox2,
   __vptr_int32 Poy2,
   __vptr_int32 Pox3,
   __vptr_int32 Poy3,
   unsigned short pblock[]);

/* Parameter Block Initialization Function */
unsigned int vcop_fft_1024_32x16t_stage5_init(
   __vptr_int32 Pxi0,
   __vptr_int32 Pyi0,
   __vptr_int32 Pxi1,
   __vptr_int32 Pyi1,
   __vptr_int32 Pxi2,
   __vptr_int32 Pyi2,
   __vptr_int32 Pxi3,
   __vptr_int32 Pyi3,
   __vptr_int32 Pox0,
   __vptr_int32 Poy0,
   __vptr_int32 Pox1,
   __vptr_int32 Poy1,
   __vptr_int32 Pox2,
   __vptr_int32 Poy2,
   __vptr_int32 Pox3,
   __vptr_int32 Poy3,
   unsigned short pblock[]);

/* VCOP VLOOP Execution Function */
void vcop_fft_1024_32x16t_stage5_vloops(
   unsigned short pblock[]);

/* Parameter Register Count */
#define PARAM_SIZE_vcop_fft_1024_32x16t_stage5 ((unsigned int)40)
unsigned int vcop_fft_1024_32x16t_stage5_param_count(void);
/* Internal Value Count */
#define CTRL_SIZE_vcop_fft_1024_32x16t_stage5 ((unsigned int)0)
unsigned int vcop_fft_1024_32x16t_stage5_ctrl_count(void);

/***********************************************************/
#endif

