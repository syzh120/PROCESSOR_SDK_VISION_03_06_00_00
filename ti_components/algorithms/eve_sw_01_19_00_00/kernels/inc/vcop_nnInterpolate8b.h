#ifndef _TI_vcop_nnInterpolate8b_h_
#define _TI_vcop_nnInterpolate8b_h_

/* Parameter Register Block */
extern unsigned short __pblock_vcop_nnInterpolate8b[38];

/* Basic Runner Function */
void vcop_nnInterpolate8b(
   __vptr_uint8 src,
   __vptr_uint8 dst,
   unsigned short outputBlockSize,
   __vptr_uint16 tluIndexArray,
   __vptr_uint8 fracArray,
   __vptr_uint16 scratch,
   __vptr_uint16 stride_ptr,
   unsigned char QShift,
   long sat_high,
   long sat_high_set,
   long sat_low,
   long sat_low_set);
/* Custom Runner Function */
void vcop_nnInterpolate8b_custom(
   __vptr_uint8 src,
   __vptr_uint8 dst,
   unsigned short outputBlockSize,
   __vptr_uint16 tluIndexArray,
   __vptr_uint8 fracArray,
   __vptr_uint16 scratch,
   __vptr_uint16 stride_ptr,
   unsigned char QShift,
   long sat_high,
   long sat_high_set,
   long sat_low,
   long sat_low_set,
   unsigned short pblock[]);

/* Parameter Block Initialization Function */
unsigned int vcop_nnInterpolate8b_init(
   __vptr_uint8 src,
   __vptr_uint8 dst,
   unsigned short outputBlockSize,
   __vptr_uint16 tluIndexArray,
   __vptr_uint8 fracArray,
   __vptr_uint16 scratch,
   __vptr_uint16 stride_ptr,
   unsigned char QShift,
   long sat_high,
   long sat_high_set,
   long sat_low,
   long sat_low_set,
   unsigned short pblock[]);

/* VCOP VLOOP Execution Function */
void vcop_nnInterpolate8b_vloops(
   unsigned short pblock[]);

/* Parameter Register Count */
#define PARAM_SIZE_vcop_nnInterpolate8b ((unsigned int)38)
unsigned int vcop_nnInterpolate8b_param_count(void);
/* Internal Value Count */
#define CTRL_SIZE_vcop_nnInterpolate8b ((unsigned int)0)
unsigned int vcop_nnInterpolate8b_ctrl_count(void);

/***********************************************************/
#endif

