#ifndef _TI_vcop_hough_for_lines_kernel_h_
#define _TI_vcop_hough_for_lines_kernel_h_

/* Parameter Register Block */
extern unsigned short __pblock_vcop_hough_for_lines[46];

/* Basic Runner Function */
void vcop_hough_for_lines(
   __vptr_uint16 pEdgeMapList,
   __vptr_int16 pCosSinThetaMulNormQ15,
   __vptr_uint16 intermIndexArray,
   __vptr_uint16 votedRhoArray8Copy,
   unsigned short listSize,
   unsigned short rhoMaxLength);
/* Custom Runner Function */
void vcop_hough_for_lines_custom(
   __vptr_uint16 pEdgeMapList,
   __vptr_int16 pCosSinThetaMulNormQ15,
   __vptr_uint16 intermIndexArray,
   __vptr_uint16 votedRhoArray8Copy,
   unsigned short listSize,
   unsigned short rhoMaxLength,
   unsigned short pblock[]);

/* Parameter Block Initialization Function */
unsigned int vcop_hough_for_lines_init(
   __vptr_uint16 pEdgeMapList,
   __vptr_int16 pCosSinThetaMulNormQ15,
   __vptr_uint16 intermIndexArray,
   __vptr_uint16 votedRhoArray8Copy,
   unsigned short listSize,
   unsigned short rhoMaxLength,
   unsigned short pblock[]);

/* VCOP VLOOP Execution Function */
void vcop_hough_for_lines_vloops(
   unsigned short pblock[]);

/* Parameter Register Count */
#define PARAM_SIZE_vcop_hough_for_lines ((unsigned int)46)
unsigned int vcop_hough_for_lines_param_count(void);
/* Internal Value Count */
#define CTRL_SIZE_vcop_hough_for_lines ((unsigned int)0)
unsigned int vcop_hough_for_lines_ctrl_count(void);

/***********************************************************/
/* Parameter Register Block */
extern unsigned short __pblock_vcop_merge_voted_rho_array[28];

/* Basic Runner Function */
void vcop_merge_voted_rho_array(
   __vptr_uint16 votedRhoArray8Copy,
   __vptr_uint16 votedRhoArray,
   __vptr_uint16 interimTransposeBuf1,
   __vptr_uint16 interimTransposeBuf2,
   __vptr_uint16 offsetArray,
   unsigned short rhoMaxLength);
/* Custom Runner Function */
void vcop_merge_voted_rho_array_custom(
   __vptr_uint16 votedRhoArray8Copy,
   __vptr_uint16 votedRhoArray,
   __vptr_uint16 interimTransposeBuf1,
   __vptr_uint16 interimTransposeBuf2,
   __vptr_uint16 offsetArray,
   unsigned short rhoMaxLength,
   unsigned short pblock[]);

/* Parameter Block Initialization Function */
unsigned int vcop_merge_voted_rho_array_init(
   __vptr_uint16 votedRhoArray8Copy,
   __vptr_uint16 votedRhoArray,
   __vptr_uint16 interimTransposeBuf1,
   __vptr_uint16 interimTransposeBuf2,
   __vptr_uint16 offsetArray,
   unsigned short rhoMaxLength,
   unsigned short pblock[]);

/* VCOP VLOOP Execution Function */
void vcop_merge_voted_rho_array_vloops(
   unsigned short pblock[]);

/* Parameter Register Count */
#define PARAM_SIZE_vcop_merge_voted_rho_array ((unsigned int)28)
unsigned int vcop_merge_voted_rho_array_param_count(void);
/* Internal Value Count */
#define CTRL_SIZE_vcop_merge_voted_rho_array ((unsigned int)0)
unsigned int vcop_merge_voted_rho_array_ctrl_count(void);

/***********************************************************/
#endif

