#ifndef _TI_vcop_copy_new_lk_xy_kernel_h_
#define _TI_vcop_copy_new_lk_xy_kernel_h_

/* Parameter Register Block */
extern unsigned short __pblock_vcop_copy_new_lk_xy[30];

/* Basic Runner Function */
void vcop_copy_new_lk_xy(
   __vptr_int16 pInput_A,
   __vptr_int16 pOutput_B,
   __vptr_uint8 currValidPoints,
   __vptr_uint32 pBaseAddrList,
   __vptr_uint32 pValidAddrList,
   __vptr_uint32 pOutAddrList,
   __vptr_uint32 pValidOutAddrList,
   __vptr_int16 pLocalX,
   __vptr_int16 pLocalY,
   __vptr_int16 pLocalXY,
   unsigned short numKeyPoints);
/* Custom Runner Function */
void vcop_copy_new_lk_xy_custom(
   __vptr_int16 pInput_A,
   __vptr_int16 pOutput_B,
   __vptr_uint8 currValidPoints,
   __vptr_uint32 pBaseAddrList,
   __vptr_uint32 pValidAddrList,
   __vptr_uint32 pOutAddrList,
   __vptr_uint32 pValidOutAddrList,
   __vptr_int16 pLocalX,
   __vptr_int16 pLocalY,
   __vptr_int16 pLocalXY,
   unsigned short numKeyPoints,
   unsigned short pblock[]);

/* Parameter Block Initialization Function */
unsigned int vcop_copy_new_lk_xy_init(
   __vptr_int16 pInput_A,
   __vptr_int16 pOutput_B,
   __vptr_uint8 currValidPoints,
   __vptr_uint32 pBaseAddrList,
   __vptr_uint32 pValidAddrList,
   __vptr_uint32 pOutAddrList,
   __vptr_uint32 pValidOutAddrList,
   __vptr_int16 pLocalX,
   __vptr_int16 pLocalY,
   __vptr_int16 pLocalXY,
   unsigned short numKeyPoints,
   unsigned short pblock[]);

/* VCOP VLOOP Execution Function */
void vcop_copy_new_lk_xy_vloops(
   unsigned short pblock[]);

/* Parameter Register Count */
#define PARAM_SIZE_vcop_copy_new_lk_xy ((unsigned int)30)
unsigned int vcop_copy_new_lk_xy_param_count(void);
/* Internal Value Count */
#define CTRL_SIZE_vcop_copy_new_lk_xy ((unsigned int)0)
unsigned int vcop_copy_new_lk_xy_ctrl_count(void);

/***********************************************************/
#endif

