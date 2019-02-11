#ifndef _TI_vcop_prune_big_list_kernel_h_
#define _TI_vcop_prune_big_list_kernel_h_

/* Parameter Register Block */
extern unsigned short __pblock_vcop_prune_big_list[42];

/* Basic Runner Function */
void vcop_prune_big_list(
   __vptr_uint32 inList_A,
   __vptr_uint16 inSortedIndexList_B,
   __vptr_uint32 inSortedIndexList32_B,
   __vptr_uint32 outList_C,
   __vptr_uint32 nonBestNSize_C,
   unsigned short threshold,
   unsigned short bestN);
/* Custom Runner Function */
void vcop_prune_big_list_custom(
   __vptr_uint32 inList_A,
   __vptr_uint16 inSortedIndexList_B,
   __vptr_uint32 inSortedIndexList32_B,
   __vptr_uint32 outList_C,
   __vptr_uint32 nonBestNSize_C,
   unsigned short threshold,
   unsigned short bestN,
   unsigned short pblock[]);

/* Parameter Block Initialization Function */
unsigned int vcop_prune_big_list_init(
   __vptr_uint32 inList_A,
   __vptr_uint16 inSortedIndexList_B,
   __vptr_uint32 inSortedIndexList32_B,
   __vptr_uint32 outList_C,
   __vptr_uint32 nonBestNSize_C,
   unsigned short threshold,
   unsigned short bestN,
   unsigned short pblock[]);

/* VCOP VLOOP Execution Function */
void vcop_prune_big_list_vloops(
   unsigned short pblock[]);

/* Parameter Register Count */
#define PARAM_SIZE_vcop_prune_big_list ((unsigned int)42)
unsigned int vcop_prune_big_list_param_count(void);
/* Internal Value Count */
#define CTRL_SIZE_vcop_prune_big_list ((unsigned int)0)
unsigned int vcop_prune_big_list_ctrl_count(void);

/***********************************************************/
#endif

