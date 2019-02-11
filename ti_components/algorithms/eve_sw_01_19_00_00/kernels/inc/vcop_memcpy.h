#ifndef _TI_vcop_memcpy_h_
#define _TI_vcop_memcpy_h_

/* Parameter Register Block */
extern unsigned short __pblock_vcop_memcpy[10];

/* Basic Runner Function */
void vcop_memcpy(
   __vptr_uint32 src,
   __vptr_uint32 dst,
   unsigned short blockSize);
/* Custom Runner Function */
void vcop_memcpy_custom(
   __vptr_uint32 src,
   __vptr_uint32 dst,
   unsigned short blockSize,
   unsigned short pblock[]);

/* Parameter Block Initialization Function */
unsigned int vcop_memcpy_init(
   __vptr_uint32 src,
   __vptr_uint32 dst,
   unsigned short blockSize,
   unsigned short pblock[]);

/* VCOP VLOOP Execution Function */
void vcop_memcpy_vloops(
   unsigned short pblock[]);

/* Parameter Register Count */
#define PARAM_SIZE_vcop_memcpy ((unsigned int)10)
unsigned int vcop_memcpy_param_count(void);
/* Internal Value Count */
#define CTRL_SIZE_vcop_memcpy ((unsigned int)0)
unsigned int vcop_memcpy_ctrl_count(void);

/***********************************************************/
/* Parameter Register Block */
extern unsigned short __pblock_vcop_memcpy2d[12];

/* Basic Runner Function */
void vcop_memcpy2d(
   __vptr_uint16 src,
   __vptr_uint16 dst,
   unsigned short width,
   unsigned short height,
   unsigned short pitch);
/* Custom Runner Function */
void vcop_memcpy2d_custom(
   __vptr_uint16 src,
   __vptr_uint16 dst,
   unsigned short width,
   unsigned short height,
   unsigned short pitch,
   unsigned short pblock[]);

/* Parameter Block Initialization Function */
unsigned int vcop_memcpy2d_init(
   __vptr_uint16 src,
   __vptr_uint16 dst,
   unsigned short width,
   unsigned short height,
   unsigned short pitch,
   unsigned short pblock[]);

/* VCOP VLOOP Execution Function */
void vcop_memcpy2d_vloops(
   unsigned short pblock[]);

/* Parameter Register Count */
#define PARAM_SIZE_vcop_memcpy2d ((unsigned int)12)
unsigned int vcop_memcpy2d_param_count(void);
/* Internal Value Count */
#define CTRL_SIZE_vcop_memcpy2d ((unsigned int)0)
unsigned int vcop_memcpy2d_ctrl_count(void);

/***********************************************************/
#endif

