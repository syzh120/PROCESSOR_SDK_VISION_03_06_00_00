#ifndef _TI_vcop_select_list_elements_kernel_h_
#define _TI_vcop_select_list_elements_kernel_h_

/* Parameter Register Block */
extern unsigned short __pblock_vcop_select_list_elements[30];

/* Basic Runner Function */
void vcop_select_list_elements(
   __vptr_uint32 inputList,
   __vptr_uint32 outputList,
   __vptr_uint8 selectionMask,
   __vptr_uint16 ouputListSize,
   unsigned short listSize,
   unsigned short selectionMaskSize);
/* Custom Runner Function */
void vcop_select_list_elements_custom(
   __vptr_uint32 inputList,
   __vptr_uint32 outputList,
   __vptr_uint8 selectionMask,
   __vptr_uint16 ouputListSize,
   unsigned short listSize,
   unsigned short selectionMaskSize,
   unsigned short pblock[]);

/* Parameter Block Initialization Function */
unsigned int vcop_select_list_elements_init(
   __vptr_uint32 inputList,
   __vptr_uint32 outputList,
   __vptr_uint8 selectionMask,
   __vptr_uint16 ouputListSize,
   unsigned short listSize,
   unsigned short selectionMaskSize,
   unsigned short pblock[]);

/* VCOP VLOOP Execution Function */
void vcop_select_list_elements_vloops(
   unsigned short pblock[]);

/* Parameter Register Count */
#define PARAM_SIZE_vcop_select_list_elements ((unsigned int)30)
unsigned int vcop_select_list_elements_param_count(void);
/* Internal Value Count */
#define CTRL_SIZE_vcop_select_list_elements ((unsigned int)0)
unsigned int vcop_select_list_elements_ctrl_count(void);

/***********************************************************/
/* Parameter Register Block */
extern unsigned short __pblock_vcop_select_list_elements_param_block_update[12];

/* Basic Runner Function */
void vcop_select_list_elements_param_block_update(
   __vptr_uint16 pBlock,
   unsigned short pReg4Val,
   unsigned short pReg14Val);
/* Custom Runner Function */
void vcop_select_list_elements_param_block_update_custom(
   __vptr_uint16 pBlock,
   unsigned short pReg4Val,
   unsigned short pReg14Val,
   unsigned short pblock[]);

/* Parameter Block Initialization Function */
unsigned int vcop_select_list_elements_param_block_update_init(
   __vptr_uint16 pBlock,
   unsigned short pReg4Val,
   unsigned short pReg14Val,
   unsigned short pblock[]);

/* VCOP VLOOP Execution Function */
void vcop_select_list_elements_param_block_update_vloops(
   unsigned short pblock[]);

/* Parameter Register Count */
#define PARAM_SIZE_vcop_select_list_elements_param_block_update ((unsigned int)12)
unsigned int vcop_select_list_elements_param_block_update_param_count(void);
/* Internal Value Count */
#define CTRL_SIZE_vcop_select_list_elements_param_block_update ((unsigned int)0)
unsigned int vcop_select_list_elements_param_block_update_ctrl_count(void);

/***********************************************************/
#endif

