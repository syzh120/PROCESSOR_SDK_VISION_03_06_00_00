#ifndef _TI_vcop_harrisScore_7x7_kernel_h_
#define _TI_vcop_harrisScore_7x7_kernel_h_

/* Parameter Register Block */
extern unsigned short __pblock_vcop_harrisScore_7x7_1[74];

/* Basic Runner Function */
void vcop_harrisScore_7x7_1(
   __vptr_int16 gradX,
   __vptr_int16 gradY,
   unsigned int width,
   unsigned int height,
   unsigned int srcPitch,
   unsigned int dstPitch,
   __vptr_int32 XX,
   __vptr_int32 YY,
   __vptr_int32 XY);
/* Custom Runner Function */
void vcop_harrisScore_7x7_1_custom(
   __vptr_int16 gradX,
   __vptr_int16 gradY,
   unsigned int width,
   unsigned int height,
   unsigned int srcPitch,
   unsigned int dstPitch,
   __vptr_int32 XX,
   __vptr_int32 YY,
   __vptr_int32 XY,
   unsigned short pblock[]);

/* Parameter Block Initialization Function */
unsigned int vcop_harrisScore_7x7_1_init(
   __vptr_int16 gradX,
   __vptr_int16 gradY,
   unsigned int width,
   unsigned int height,
   unsigned int srcPitch,
   unsigned int dstPitch,
   __vptr_int32 XX,
   __vptr_int32 YY,
   __vptr_int32 XY,
   unsigned short pblock[]);

/* VCOP VLOOP Execution Function */
void vcop_harrisScore_7x7_1_vloops(
   unsigned short pblock[]);

/* Parameter Register Count */
#define PARAM_SIZE_vcop_harrisScore_7x7_1 ((unsigned int)74)
unsigned int vcop_harrisScore_7x7_1_param_count(void);
/* Internal Value Count */
#define CTRL_SIZE_vcop_harrisScore_7x7_1 ((unsigned int)0)
unsigned int vcop_harrisScore_7x7_1_ctrl_count(void);

/***********************************************************/
/* Parameter Register Block */
extern unsigned short __pblock_vcop_harrisScore_7x7_2[78];

/* Basic Runner Function */
void vcop_harrisScore_7x7_2(
   int width,
   int height,
   unsigned int srcPitch,
   unsigned int dstPitch,
   __vptr_int16 outm,
   unsigned short k,
   __vptr_int32 XX,
   __vptr_int32 YY,
   __vptr_int32 XY,
   __vptr_uint16 XXl,
   __vptr_uint16 YYl,
   __vptr_uint16 XYl,
   __vptr_int16 XXh,
   __vptr_int16 YYh,
   __vptr_int16 XYh,
   __vptr_uint32 detL,
   __vptr_int32 detH);
/* Custom Runner Function */
void vcop_harrisScore_7x7_2_custom(
   int width,
   int height,
   unsigned int srcPitch,
   unsigned int dstPitch,
   __vptr_int16 outm,
   unsigned short k,
   __vptr_int32 XX,
   __vptr_int32 YY,
   __vptr_int32 XY,
   __vptr_uint16 XXl,
   __vptr_uint16 YYl,
   __vptr_uint16 XYl,
   __vptr_int16 XXh,
   __vptr_int16 YYh,
   __vptr_int16 XYh,
   __vptr_uint32 detL,
   __vptr_int32 detH,
   unsigned short pblock[]);

/* Parameter Block Initialization Function */
unsigned int vcop_harrisScore_7x7_2_init(
   int width,
   int height,
   unsigned int srcPitch,
   unsigned int dstPitch,
   __vptr_int16 outm,
   unsigned short k,
   __vptr_int32 XX,
   __vptr_int32 YY,
   __vptr_int32 XY,
   __vptr_uint16 XXl,
   __vptr_uint16 YYl,
   __vptr_uint16 XYl,
   __vptr_int16 XXh,
   __vptr_int16 YYh,
   __vptr_int16 XYh,
   __vptr_uint32 detL,
   __vptr_int32 detH,
   unsigned short pblock[]);

/* VCOP VLOOP Execution Function */
void vcop_harrisScore_7x7_2_vloops(
   unsigned short pblock[]);

/* Parameter Register Count */
#define PARAM_SIZE_vcop_harrisScore_7x7_2 ((unsigned int)78)
unsigned int vcop_harrisScore_7x7_2_param_count(void);
/* Internal Value Count */
#define CTRL_SIZE_vcop_harrisScore_7x7_2 ((unsigned int)0)
unsigned int vcop_harrisScore_7x7_2_ctrl_count(void);

/***********************************************************/
#endif

