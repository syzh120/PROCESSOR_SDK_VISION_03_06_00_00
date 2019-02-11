#ifndef _TI_vcop_fast9_score_kernel_h_
#define _TI_vcop_fast9_score_kernel_h_

/* Parameter Register Block */
extern unsigned short __pblock_vcop_fast9_score_kernel[80];

/* Basic Runner Function */
void vcop_fast9_score_kernel(
   __vptr_uint32 pIn,
   __vptr_uint32 pTemp_buf,
   __vptr_uint32 pTemp,
   __vptr_uint8 pTemp1,
   unsigned int nFeatures,
   signed char Thr,
   __vptr_uint8 Index,
   __vptr_uint8 Offset_Out,
   __vptr_uint16 BScore,
   __vptr_uint16 DScore,
   __vptr_uint16 Score,
   __vptr_uint32 updateOutPtr);
/* Custom Runner Function */
void vcop_fast9_score_kernel_custom(
   __vptr_uint32 pIn,
   __vptr_uint32 pTemp_buf,
   __vptr_uint32 pTemp,
   __vptr_uint8 pTemp1,
   unsigned int nFeatures,
   signed char Thr,
   __vptr_uint8 Index,
   __vptr_uint8 Offset_Out,
   __vptr_uint16 BScore,
   __vptr_uint16 DScore,
   __vptr_uint16 Score,
   __vptr_uint32 updateOutPtr,
   unsigned short pblock[]);

/* Parameter Block Initialization Function */
unsigned int vcop_fast9_score_kernel_init(
   __vptr_uint32 pIn,
   __vptr_uint32 pTemp_buf,
   __vptr_uint32 pTemp,
   __vptr_uint8 pTemp1,
   unsigned int nFeatures,
   signed char Thr,
   __vptr_uint8 Index,
   __vptr_uint8 Offset_Out,
   __vptr_uint16 BScore,
   __vptr_uint16 DScore,
   __vptr_uint16 Score,
   __vptr_uint32 updateOutPtr,
   unsigned short pblock[]);

/* VCOP VLOOP Execution Function */
void vcop_fast9_score_kernel_vloops(
   unsigned short pblock[]);

/* Parameter Register Count */
#define PARAM_SIZE_vcop_fast9_score_kernel ((unsigned int)80)
unsigned int vcop_fast9_score_kernel_param_count(void);
/* Internal Value Count */
#define CTRL_SIZE_vcop_fast9_score_kernel ((unsigned int)0)
unsigned int vcop_fast9_score_kernel_ctrl_count(void);

/***********************************************************/
/* Parameter Register Block */
extern unsigned short __pblock_vcop_fast9_thresh_score[104];

/* Basic Runner Function */
void vcop_fast9_thresh_score(
   __vptr_uint32 pIn,
   __vptr_uint32 pTemp_buf,
   __vptr_uint32 pTemp,
   __vptr_uint8 pTemp1,
   unsigned int nFeatures,
   signed char Thr,
   __vptr_uint8 Index,
   __vptr_uint8 Offset_Out,
   __vptr_uint8 BScore,
   __vptr_uint8 DScore,
   __vptr_uint16 Score_B,
   __vptr_uint16 Score_D,
   __vptr_uint16 Score,
   __vptr_uint32 updateOutPtr);
/* Custom Runner Function */
void vcop_fast9_thresh_score_custom(
   __vptr_uint32 pIn,
   __vptr_uint32 pTemp_buf,
   __vptr_uint32 pTemp,
   __vptr_uint8 pTemp1,
   unsigned int nFeatures,
   signed char Thr,
   __vptr_uint8 Index,
   __vptr_uint8 Offset_Out,
   __vptr_uint8 BScore,
   __vptr_uint8 DScore,
   __vptr_uint16 Score_B,
   __vptr_uint16 Score_D,
   __vptr_uint16 Score,
   __vptr_uint32 updateOutPtr,
   unsigned short pblock[]);

/* Parameter Block Initialization Function */
unsigned int vcop_fast9_thresh_score_init(
   __vptr_uint32 pIn,
   __vptr_uint32 pTemp_buf,
   __vptr_uint32 pTemp,
   __vptr_uint8 pTemp1,
   unsigned int nFeatures,
   signed char Thr,
   __vptr_uint8 Index,
   __vptr_uint8 Offset_Out,
   __vptr_uint8 BScore,
   __vptr_uint8 DScore,
   __vptr_uint16 Score_B,
   __vptr_uint16 Score_D,
   __vptr_uint16 Score,
   __vptr_uint32 updateOutPtr,
   unsigned short pblock[]);

/* VCOP VLOOP Execution Function */
void vcop_fast9_thresh_score_vloops(
   unsigned short pblock[]);

/* Parameter Register Count */
#define PARAM_SIZE_vcop_fast9_thresh_score ((unsigned int)104)
unsigned int vcop_fast9_thresh_score_param_count(void);
/* Internal Value Count */
#define CTRL_SIZE_vcop_fast9_thresh_score ((unsigned int)0)
unsigned int vcop_fast9_thresh_score_ctrl_count(void);

/***********************************************************/
#endif

