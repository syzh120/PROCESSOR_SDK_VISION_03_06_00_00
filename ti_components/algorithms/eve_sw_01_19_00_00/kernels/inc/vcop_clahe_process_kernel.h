#ifndef _TI_vcop_clahe_process_kernel_h_
#define _TI_vcop_clahe_process_kernel_h_

/* Parameter Register Block */
extern unsigned short __pblock_clahe_make_8way_look_up_kernel[10];

/* Basic Runner Function */
void clahe_make_8way_look_up_kernel(
   __vptr_uint32 inLuts,
   __vptr_uint32 outLuts,
   unsigned short histSize);
/* Custom Runner Function */
void clahe_make_8way_look_up_kernel_custom(
   __vptr_uint32 inLuts,
   __vptr_uint32 outLuts,
   unsigned short histSize,
   unsigned short pblock[]);

/* Parameter Block Initialization Function */
unsigned int clahe_make_8way_look_up_kernel_init(
   __vptr_uint32 inLuts,
   __vptr_uint32 outLuts,
   unsigned short histSize,
   unsigned short pblock[]);

/* VCOP VLOOP Execution Function */
void clahe_make_8way_look_up_kernel_vloops(
   unsigned short pblock[]);

/* Parameter Register Count */
#define PARAM_SIZE_clahe_make_8way_look_up_kernel ((unsigned int)10)
unsigned int clahe_make_8way_look_up_kernel_param_count(void);
/* Internal Value Count */
#define CTRL_SIZE_clahe_make_8way_look_up_kernel ((unsigned int)0)
unsigned int clahe_make_8way_look_up_kernel_ctrl_count(void);

/***********************************************************/
/* Parameter Register Block */
extern unsigned short __pblock_clahe_look_up_and_interpolate_kernel[48];

/* Basic Runner Function */
void clahe_look_up_and_interpolate_kernel(
   __vptr_uint8 inBuf,
   __vptr_uint8 inLut,
   __vptr_uint16 xWgtBuf,
   __vptr_uint16 yWgtBuf,
   __vptr_uint8 tempBuf,
   __vptr_uint8 outBuf,
   unsigned short inWidth,
   unsigned short inHeight,
   unsigned short inPitch,
   unsigned short tablePitch,
   unsigned short numTab);
/* Custom Runner Function */
void clahe_look_up_and_interpolate_kernel_custom(
   __vptr_uint8 inBuf,
   __vptr_uint8 inLut,
   __vptr_uint16 xWgtBuf,
   __vptr_uint16 yWgtBuf,
   __vptr_uint8 tempBuf,
   __vptr_uint8 outBuf,
   unsigned short inWidth,
   unsigned short inHeight,
   unsigned short inPitch,
   unsigned short tablePitch,
   unsigned short numTab,
   unsigned short pblock[]);

/* Parameter Block Initialization Function */
unsigned int clahe_look_up_and_interpolate_kernel_init(
   __vptr_uint8 inBuf,
   __vptr_uint8 inLut,
   __vptr_uint16 xWgtBuf,
   __vptr_uint16 yWgtBuf,
   __vptr_uint8 tempBuf,
   __vptr_uint8 outBuf,
   unsigned short inWidth,
   unsigned short inHeight,
   unsigned short inPitch,
   unsigned short tablePitch,
   unsigned short numTab,
   unsigned short pblock[]);

/* VCOP VLOOP Execution Function */
void clahe_look_up_and_interpolate_kernel_vloops(
   unsigned short pblock[]);

/* Parameter Register Count */
#define PARAM_SIZE_clahe_look_up_and_interpolate_kernel ((unsigned int)48)
unsigned int clahe_look_up_and_interpolate_kernel_param_count(void);
/* Internal Value Count */
#define CTRL_SIZE_clahe_look_up_and_interpolate_kernel ((unsigned int)0)
unsigned int clahe_look_up_and_interpolate_kernel_ctrl_count(void);

/***********************************************************/
#endif

