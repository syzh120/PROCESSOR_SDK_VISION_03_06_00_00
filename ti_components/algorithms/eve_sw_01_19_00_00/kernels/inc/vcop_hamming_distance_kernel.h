#ifndef _TI_vcop_hamming_distance_kernel_h_
#define _TI_vcop_hamming_distance_kernel_h_

/* Parameter Register Block */
extern unsigned short __pblock_vcop_hamming_distance[62];

/* Basic Runner Function */
void vcop_hamming_distance(
   __vptr_uint32 pString1,
   __vptr_uint32 pString2,
   __vptr_uint8 pStringByte1,
   __vptr_uint8 pStringByte2,
   unsigned int xsize,
   unsigned int ysize,
   unsigned int mode,
   unsigned int xpitch,
   __vptr_uint32 pHammingDistance,
   __vptr_uint16 pScratch);
/* Custom Runner Function */
void vcop_hamming_distance_custom(
   __vptr_uint32 pString1,
   __vptr_uint32 pString2,
   __vptr_uint8 pStringByte1,
   __vptr_uint8 pStringByte2,
   unsigned int xsize,
   unsigned int ysize,
   unsigned int mode,
   unsigned int xpitch,
   __vptr_uint32 pHammingDistance,
   __vptr_uint16 pScratch,
   unsigned short pblock[]);

/* Parameter Block Initialization Function */
unsigned int vcop_hamming_distance_init(
   __vptr_uint32 pString1,
   __vptr_uint32 pString2,
   __vptr_uint8 pStringByte1,
   __vptr_uint8 pStringByte2,
   unsigned int xsize,
   unsigned int ysize,
   unsigned int mode,
   unsigned int xpitch,
   __vptr_uint32 pHammingDistance,
   __vptr_uint16 pScratch,
   unsigned short pblock[]);

/* VCOP VLOOP Execution Function */
void vcop_hamming_distance_vloops(
   unsigned short pblock[]);

/* Parameter Register Count */
#define PARAM_SIZE_vcop_hamming_distance ((unsigned int)62)
unsigned int vcop_hamming_distance_param_count(void);
/* Internal Value Count */
#define CTRL_SIZE_vcop_hamming_distance ((unsigned int)0)
unsigned int vcop_hamming_distance_ctrl_count(void);

/***********************************************************/
/* Parameter Register Block */
extern unsigned short __pblock_vcop_hamming_distance_multiple_32[48];

/* Basic Runner Function */
void vcop_hamming_distance_multiple_32(
   __vptr_uint32 pString1,
   __vptr_uint32 pString2,
   unsigned int xsize,
   unsigned int ysize,
   unsigned int mode,
   unsigned int xpitch,
   __vptr_uint32 pHammingDistance,
   __vptr_uint16 pScratch);
/* Custom Runner Function */
void vcop_hamming_distance_multiple_32_custom(
   __vptr_uint32 pString1,
   __vptr_uint32 pString2,
   unsigned int xsize,
   unsigned int ysize,
   unsigned int mode,
   unsigned int xpitch,
   __vptr_uint32 pHammingDistance,
   __vptr_uint16 pScratch,
   unsigned short pblock[]);

/* Parameter Block Initialization Function */
unsigned int vcop_hamming_distance_multiple_32_init(
   __vptr_uint32 pString1,
   __vptr_uint32 pString2,
   unsigned int xsize,
   unsigned int ysize,
   unsigned int mode,
   unsigned int xpitch,
   __vptr_uint32 pHammingDistance,
   __vptr_uint16 pScratch,
   unsigned short pblock[]);

/* VCOP VLOOP Execution Function */
void vcop_hamming_distance_multiple_32_vloops(
   unsigned short pblock[]);

/* Parameter Register Count */
#define PARAM_SIZE_vcop_hamming_distance_multiple_32 ((unsigned int)48)
unsigned int vcop_hamming_distance_multiple_32_param_count(void);
/* Internal Value Count */
#define CTRL_SIZE_vcop_hamming_distance_multiple_32 ((unsigned int)0)
unsigned int vcop_hamming_distance_multiple_32_ctrl_count(void);

/***********************************************************/
/* Parameter Register Block */
extern unsigned short __pblock_vcop_hamming_distance_size_lt_32[26];

/* Basic Runner Function */
void vcop_hamming_distance_size_lt_32(
   __vptr_uint8 pStringByte1,
   __vptr_uint8 pStringByte2,
   unsigned int xsize,
   unsigned int ysize,
   unsigned int mode,
   unsigned int xpitch,
   __vptr_uint32 pHammingDistance);
/* Custom Runner Function */
void vcop_hamming_distance_size_lt_32_custom(
   __vptr_uint8 pStringByte1,
   __vptr_uint8 pStringByte2,
   unsigned int xsize,
   unsigned int ysize,
   unsigned int mode,
   unsigned int xpitch,
   __vptr_uint32 pHammingDistance,
   unsigned short pblock[]);

/* Parameter Block Initialization Function */
unsigned int vcop_hamming_distance_size_lt_32_init(
   __vptr_uint8 pStringByte1,
   __vptr_uint8 pStringByte2,
   unsigned int xsize,
   unsigned int ysize,
   unsigned int mode,
   unsigned int xpitch,
   __vptr_uint32 pHammingDistance,
   unsigned short pblock[]);

/* VCOP VLOOP Execution Function */
void vcop_hamming_distance_size_lt_32_vloops(
   unsigned short pblock[]);

/* Parameter Register Count */
#define PARAM_SIZE_vcop_hamming_distance_size_lt_32 ((unsigned int)26)
unsigned int vcop_hamming_distance_size_lt_32_param_count(void);
/* Internal Value Count */
#define CTRL_SIZE_vcop_hamming_distance_size_lt_32 ((unsigned int)0)
unsigned int vcop_hamming_distance_size_lt_32_ctrl_count(void);

/***********************************************************/
#endif

