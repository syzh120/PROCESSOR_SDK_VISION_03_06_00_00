#ifndef _TI_vcop_deInterleaveYUV422ILE_h_
#define _TI_vcop_deInterleaveYUV422ILE_h_

/* Parameter Register Block */
extern unsigned short __pblock_vcop_deInterleaveYUV422ILE[16];

/* Basic Runner Function */
void vcop_deInterleaveYUV422ILE(
   __vptr_uint8 src,
   __vptr_uint8 dst,
   __vptr_uint8 dst_u,
   __vptr_uint8 dst_v,
   unsigned short size);
/* Custom Runner Function */
void vcop_deInterleaveYUV422ILE_custom(
   __vptr_uint8 src,
   __vptr_uint8 dst,
   __vptr_uint8 dst_u,
   __vptr_uint8 dst_v,
   unsigned short size,
   unsigned short pblock[]);

/* Parameter Block Initialization Function */
unsigned int vcop_deInterleaveYUV422ILE_init(
   __vptr_uint8 src,
   __vptr_uint8 dst,
   __vptr_uint8 dst_u,
   __vptr_uint8 dst_v,
   unsigned short size,
   unsigned short pblock[]);

/* VCOP VLOOP Execution Function */
void vcop_deInterleaveYUV422ILE_vloops(
   unsigned short pblock[]);

/* Parameter Register Count */
#define PARAM_SIZE_vcop_deInterleaveYUV422ILE ((unsigned int)16)
unsigned int vcop_deInterleaveYUV422ILE_param_count(void);
/* Internal Value Count */
#define CTRL_SIZE_vcop_deInterleaveYUV422ILE ((unsigned int)0)
unsigned int vcop_deInterleaveYUV422ILE_ctrl_count(void);

/***********************************************************/
#endif

