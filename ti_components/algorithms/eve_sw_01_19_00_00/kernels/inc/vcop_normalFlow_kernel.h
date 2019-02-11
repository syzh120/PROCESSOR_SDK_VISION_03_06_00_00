#ifndef _TI_vcop_normalFlow_kernel_h_
#define _TI_vcop_normalFlow_kernel_h_

/* Parameter Register Block */
extern unsigned short __pblock_vcop_normalFlow[38];

/* Basic Runner Function */
void vcop_normalFlow(
   __vptr_int16 imDiff,
   __vptr_int16 Emag,
   __vptr_int16 LUT,
   __vptr_int16 E,
   __vptr_int16 TLU_m_inv,
   int T,
   short numEls,
   __vptr_int16 normalFlowU,
   __vptr_int16 normalFlowV);
/* Custom Runner Function */
void vcop_normalFlow_custom(
   __vptr_int16 imDiff,
   __vptr_int16 Emag,
   __vptr_int16 LUT,
   __vptr_int16 E,
   __vptr_int16 TLU_m_inv,
   int T,
   short numEls,
   __vptr_int16 normalFlowU,
   __vptr_int16 normalFlowV,
   unsigned short pblock[]);

/* Parameter Block Initialization Function */
unsigned int vcop_normalFlow_init(
   __vptr_int16 imDiff,
   __vptr_int16 Emag,
   __vptr_int16 LUT,
   __vptr_int16 E,
   __vptr_int16 TLU_m_inv,
   int T,
   short numEls,
   __vptr_int16 normalFlowU,
   __vptr_int16 normalFlowV,
   unsigned short pblock[]);

/* VCOP VLOOP Execution Function */
void vcop_normalFlow_vloops(
   unsigned short pblock[]);

/* Parameter Register Count */
#define PARAM_SIZE_vcop_normalFlow ((unsigned int)38)
unsigned int vcop_normalFlow_param_count(void);
/* Internal Value Count */
#define CTRL_SIZE_vcop_normalFlow ((unsigned int)0)
unsigned int vcop_normalFlow_ctrl_count(void);

/***********************************************************/
#endif

