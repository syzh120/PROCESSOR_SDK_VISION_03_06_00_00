#ifndef _TI_vcop_calc_new_lk_xy_kernel_h_
#define _TI_vcop_calc_new_lk_xy_kernel_h_

/* Parameter Register Block */
extern unsigned short __pblock_vcop_calc_new_lk_xy[70];

/* Basic Runner Function */
void vcop_calc_new_lk_xy(
   __vptr_uint16 IxItL_a,
   __vptr_uint16 IyItL_b,
   __vptr_int16 IxItH_a,
   __vptr_int16 IyItH_b,
   __vptr_int16 Ix2_a,
   __vptr_int16 Iy2_b,
   __vptr_int16 Ixy_c,
   __vptr_int16 X_c,
   __vptr_int16 Y_c,
   __vptr_int16 localXY_b,
   __vptr_int16 frameXY_b,
   __vptr_uint16 numValidPoints,
   __vptr_uint8 currValidPoints,
   __vptr_uint32 pBaseAddrList,
   __vptr_uint32 pValidAddrList,
   __vptr_uint32 pOutAddrList,
   __vptr_uint32 pValidOutAddrList,
   __vptr_int32 vx,
   __vptr_int32 vy,
   unsigned short qFormatePel,
   unsigned short minErrValue,
   unsigned char searchRange,
   unsigned short n);
/* Custom Runner Function */
void vcop_calc_new_lk_xy_custom(
   __vptr_uint16 IxItL_a,
   __vptr_uint16 IyItL_b,
   __vptr_int16 IxItH_a,
   __vptr_int16 IyItH_b,
   __vptr_int16 Ix2_a,
   __vptr_int16 Iy2_b,
   __vptr_int16 Ixy_c,
   __vptr_int16 X_c,
   __vptr_int16 Y_c,
   __vptr_int16 localXY_b,
   __vptr_int16 frameXY_b,
   __vptr_uint16 numValidPoints,
   __vptr_uint8 currValidPoints,
   __vptr_uint32 pBaseAddrList,
   __vptr_uint32 pValidAddrList,
   __vptr_uint32 pOutAddrList,
   __vptr_uint32 pValidOutAddrList,
   __vptr_int32 vx,
   __vptr_int32 vy,
   unsigned short qFormatePel,
   unsigned short minErrValue,
   unsigned char searchRange,
   unsigned short n,
   unsigned short pblock[]);

/* Parameter Block Initialization Function */
unsigned int vcop_calc_new_lk_xy_init(
   __vptr_uint16 IxItL_a,
   __vptr_uint16 IyItL_b,
   __vptr_int16 IxItH_a,
   __vptr_int16 IyItH_b,
   __vptr_int16 Ix2_a,
   __vptr_int16 Iy2_b,
   __vptr_int16 Ixy_c,
   __vptr_int16 X_c,
   __vptr_int16 Y_c,
   __vptr_int16 localXY_b,
   __vptr_int16 frameXY_b,
   __vptr_uint16 numValidPoints,
   __vptr_uint8 currValidPoints,
   __vptr_uint32 pBaseAddrList,
   __vptr_uint32 pValidAddrList,
   __vptr_uint32 pOutAddrList,
   __vptr_uint32 pValidOutAddrList,
   __vptr_int32 vx,
   __vptr_int32 vy,
   unsigned short qFormatePel,
   unsigned short minErrValue,
   unsigned char searchRange,
   unsigned short n,
   unsigned short pblock[]);

/* VCOP VLOOP Execution Function */
void vcop_calc_new_lk_xy_vloops(
   unsigned short pblock[]);

/* Parameter Register Count */
#define PARAM_SIZE_vcop_calc_new_lk_xy ((unsigned int)70)
unsigned int vcop_calc_new_lk_xy_param_count(void);
/* Internal Value Count */
#define CTRL_SIZE_vcop_calc_new_lk_xy ((unsigned int)0)
unsigned int vcop_calc_new_lk_xy_ctrl_count(void);

/***********************************************************/
#endif

