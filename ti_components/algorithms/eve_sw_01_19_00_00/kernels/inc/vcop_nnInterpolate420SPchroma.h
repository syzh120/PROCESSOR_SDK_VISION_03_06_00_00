#ifndef _TI_vcop_nnInterpolate420SPchroma_h_
#define _TI_vcop_nnInterpolate420SPchroma_h_

/* Parameter Register Block */
extern unsigned short __pblock_vcop_nnInterpolate420SPchroma[36];

/* Basic Runner Function */
void vcop_nnInterpolate420SPchroma(
   __vptr_uint8 src,
   __vptr_uint16 dst,
   unsigned short numMappedPixels,
   __vptr_uint16 tluIndexArray,
   __vptr_uint16 scatterStoreArray,
   __vptr_uint8 scratchHbuf8b,
   __vptr_uint16 scratchHbuf16b,
   long sat_high,
   long sat_high_set,
   long sat_low,
   long sat_low_set,
   unsigned short dst_end_offset);
/* Custom Runner Function */
void vcop_nnInterpolate420SPchroma_custom(
   __vptr_uint8 src,
   __vptr_uint16 dst,
   unsigned short numMappedPixels,
   __vptr_uint16 tluIndexArray,
   __vptr_uint16 scatterStoreArray,
   __vptr_uint8 scratchHbuf8b,
   __vptr_uint16 scratchHbuf16b,
   long sat_high,
   long sat_high_set,
   long sat_low,
   long sat_low_set,
   unsigned short dst_end_offset,
   unsigned short pblock[]);

/* Parameter Block Initialization Function */
unsigned int vcop_nnInterpolate420SPchroma_init(
   __vptr_uint8 src,
   __vptr_uint16 dst,
   unsigned short numMappedPixels,
   __vptr_uint16 tluIndexArray,
   __vptr_uint16 scatterStoreArray,
   __vptr_uint8 scratchHbuf8b,
   __vptr_uint16 scratchHbuf16b,
   long sat_high,
   long sat_high_set,
   long sat_low,
   long sat_low_set,
   unsigned short dst_end_offset,
   unsigned short pblock[]);

/* VCOP VLOOP Execution Function */
void vcop_nnInterpolate420SPchroma_vloops(
   unsigned short pblock[]);

/* Parameter Register Count */
#define PARAM_SIZE_vcop_nnInterpolate420SPchroma ((unsigned int)36)
unsigned int vcop_nnInterpolate420SPchroma_param_count(void);
/* Internal Value Count */
#define CTRL_SIZE_vcop_nnInterpolate420SPchroma ((unsigned int)0)
unsigned int vcop_nnInterpolate420SPchroma_ctrl_count(void);

/***********************************************************/
/* Parameter Register Block */
extern unsigned short __pblock_vcop_nnInterpolate420SPchromaBB[16];

/* Basic Runner Function */
void vcop_nnInterpolate420SPchromaBB(
   __vptr_uint8 src,
   __vptr_uint8 dst,
   unsigned short outputBlockSize,
   __vptr_uint16 tluIndexArray,
   long sat_high,
   long sat_high_set,
   long sat_low,
   long sat_low_set);
/* Custom Runner Function */
void vcop_nnInterpolate420SPchromaBB_custom(
   __vptr_uint8 src,
   __vptr_uint8 dst,
   unsigned short outputBlockSize,
   __vptr_uint16 tluIndexArray,
   long sat_high,
   long sat_high_set,
   long sat_low,
   long sat_low_set,
   unsigned short pblock[]);

/* Parameter Block Initialization Function */
unsigned int vcop_nnInterpolate420SPchromaBB_init(
   __vptr_uint8 src,
   __vptr_uint8 dst,
   unsigned short outputBlockSize,
   __vptr_uint16 tluIndexArray,
   long sat_high,
   long sat_high_set,
   long sat_low,
   long sat_low_set,
   unsigned short pblock[]);

/* VCOP VLOOP Execution Function */
void vcop_nnInterpolate420SPchromaBB_vloops(
   unsigned short pblock[]);

/* Parameter Register Count */
#define PARAM_SIZE_vcop_nnInterpolate420SPchromaBB ((unsigned int)16)
unsigned int vcop_nnInterpolate420SPchromaBB_param_count(void);
/* Internal Value Count */
#define CTRL_SIZE_vcop_nnInterpolate420SPchromaBB ((unsigned int)0)
unsigned int vcop_nnInterpolate420SPchromaBB_ctrl_count(void);

/***********************************************************/
#endif

