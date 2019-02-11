#include <vcop\vcop.h>

typedef unsigned char uchar;

#pragma DATA_SECTION(__pblock_vcop_select_list_elements, ".vcop_parameter_block")
#pragma DATA_ALIGN(__pblock_vcop_select_list_elements, __ALIGNOF__(int));
unsigned short __pblock_vcop_select_list_elements[30];

unsigned int vcop_select_list_elements_param_count(void)
{
   return 30u;
}

unsigned int vcop_select_list_elements_ctrl_count(void)
{
   return 0u;
}

unsigned int vcop_select_list_elements_init(
   __vptr_uint32 inputList,
   __vptr_uint32 outputList,
   __vptr_uint8 selectionMask,
   __vptr_uint16 ouputListSize,
   unsigned short listSize,
   unsigned short selectionMaskSize,
   unsigned short pblock[])
{
   int __offset = 0;
   /* Loop 1 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), (1)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), ((listSize / selectionMaskSize))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), ((selectionMaskSize / (8u)))-1u);
   __vcop_pblock_init32(pblock, __offset+_PREG(6), (uchar *)selectionMask);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)outputList);
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)ouputListSize);
   __vcop_pblock_init16(pblock, __offset+_PREG(12), 32);
   __vcop_pblock_init16(pblock, __offset+_PREG(13), (selectionMaskSize*sizeof(*inputList)) -(8u*sizeof(*inputList))*(((selectionMaskSize / (8u)))-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(14),  -(selectionMaskSize*sizeof(*inputList))*(((listSize / selectionMaskSize))-1u) -(8u*sizeof(*inputList))*(((selectionMaskSize / (8u)))-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(15), 8);
   __vcop_pblock_init16(pblock, __offset+_PREG(16),  -(8u*sizeof(*selectionMask))*(((selectionMaskSize / (8u)))-1u));
   __vcop_pblock_init32(pblock, __offset+_PREG(18), 0);
   __vcop_pblock_init32(pblock, __offset+_PREG(20), (uchar *)inputList);
   __offset += 20;

   /* Loop 2 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), (1)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), (7)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(6), 2);
   __vcop_pblock_init16(pblock, __offset+_PREG(7), -12);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)ouputListSize+sizeof(*ouputListSize));
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)ouputListSize);
   __offset += 10;

   return 30u;
}

void vcop_select_list_elements_vloops(
   unsigned short pblock[])
{
   /* Kernel-wide Vector Registers */
   #pragma VCC_VREG("VListData", 16);
   #pragma VCC_VREG("VMask", 17);
   #pragma VCC_VREG("VOutputListSize", 18);
   #pragma VCC_VREG("VSelectionMask", 19);

   __vcop_param(&pblock[0]);

   /* VLOOP 1 Start */

   /* VLOOP Local Vector Registers */
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("addr0", "A0");
   #pragma EVE_REG("inAddr", "A1");
   #pragma EVE_REG("selectionMaskAddr", "A2");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("k", "I2");
   #pragma EVE_REG("i", "I3");
   #pragma EVE_REG("j", "I4");
   

   __vcop_vloop(__vcop_compute(), 10u, 10u, 1u);
   __vcop_vinit(__vcop_sizeW(), __vcop_once(), _PREG(18), _VREG(18));
   __vcop_vagen(_AGEN(0), _PREG(0), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(1), _PREG(12), _PREG(13), _PREG(14), _PREG(0));
   __vcop_vagen(_AGEN(2), _PREG(15), _PREG(16), _PREG(16), _PREG(0));
   __vcop_vload(__vcop_sizeWU(), __vcop_npt(), _PREG(20), _AGEN(1), _VREG(16), __vcop_alws());
   __vcop_vload(__vcop_sizeBU(), __vcop_npt(), _PREG(6), _AGEN(2), _VREG(19), __vcop_alws());
   __vcop_vadd(_VREG(18), _VREG(19), _VREG(18));
   __vcop_vstore(__vcop_predicate(_VREG(19)), __vcop_sizeWU(), __vcop_collat(), __vcop_alws(), _VREG(16), _PREG(8), _AGEN(0), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeHU(), __vcop_npt(), __vcop_last_i34(), _VREG(18), _PREG(10), _AGEN(0), _PREG(0));
   __vcop_vloop_end(1u);

   /* VLOOP 2 Start */

   /* VLOOP Local Vector Registers */
   #pragma VCC_VREG("VnumElems", 20);
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("addr0", "A0");
   #pragma EVE_REG("Addr1", "A1");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("i", "I3");
   #pragma EVE_REG("j", "I4");
   

   __vcop_vloop(__vcop_compute(), 6u, 5u, 2u);
   __vcop_vagen(_AGEN(0), _PREG(0), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(1), _PREG(6), _PREG(7), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeHU(), __vcop_1pt(), _PREG(8), _AGEN(1), _VREG(20), __vcop_alws());
   __vcop_vadd(_VREG(18), _VREG(20), _VREG(18));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeHU(), __vcop_1pt(), __vcop_last_i4(), _VREG(18), _PREG(10), _AGEN(0), _PREG(0));
   __vcop_vloop_end(2u);

}

void vcop_select_list_elements(
   __vptr_uint32 inputList,
   __vptr_uint32 outputList,
   __vptr_uint8 selectionMask,
   __vptr_uint16 ouputListSize,
   unsigned short listSize,
   unsigned short selectionMaskSize)
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_select_list_elements_init(inputList, outputList, selectionMask, ouputListSize, listSize, selectionMaskSize, __pblock_vcop_select_list_elements);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_select_list_elements_vloops(__pblock_vcop_select_list_elements);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

void vcop_select_list_elements_custom(
   __vptr_uint32 inputList,
   __vptr_uint32 outputList,
   __vptr_uint8 selectionMask,
   __vptr_uint16 ouputListSize,
   unsigned short listSize,
   unsigned short selectionMaskSize,
   unsigned short pblock[])
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_select_list_elements_init(inputList, outputList, selectionMask, ouputListSize, listSize, selectionMaskSize, pblock);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_select_list_elements_vloops(pblock);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

#pragma DATA_SECTION(__pblock_vcop_select_list_elements_param_block_update, ".vcop_parameter_block")
#pragma DATA_ALIGN(__pblock_vcop_select_list_elements_param_block_update, __ALIGNOF__(int));
unsigned short __pblock_vcop_select_list_elements_param_block_update[12];

unsigned int vcop_select_list_elements_param_block_update_param_count(void)
{
   return 12u;
}

unsigned int vcop_select_list_elements_param_block_update_ctrl_count(void)
{
   return 0u;
}

unsigned int vcop_select_list_elements_param_block_update_init(
   __vptr_uint16 pBlock,
   unsigned short pReg4Val,
   unsigned short pReg14Val,
   unsigned short pblock[])
{
   int __offset = 0;
   /* Loop 1 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), (1)-1u);
   __vcop_pblock_init32(pblock, __offset+_PREG(6), (uchar *)pBlock+4U);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)pBlock+24U);
   __vcop_pblock_init32(pblock, __offset+_PREG(10), pReg4Val);
   __vcop_pblock_init32(pblock, __offset+_PREG(12), pReg14Val);
   __offset += 12;

   return 12u;
}

void vcop_select_list_elements_param_block_update_vloops(
   unsigned short pblock[])
{
   /* Kernel-wide Vector Registers */
   #pragma VCC_VREG("VPreg14Val", 16);
   #pragma VCC_VREG("VPreg4Val", 17);

   __vcop_param(&pblock[0]);

   /* VLOOP 1 Start */

   /* VLOOP Local Vector Registers */
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("addr0", "A0");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("i", "I4");
   

   __vcop_vloop(__vcop_compute(), 6u, 6u, 1u);
   __vcop_vinit(__vcop_sizeW(), __vcop_once(), _PREG(10), _VREG(17));
   __vcop_vinit(__vcop_sizeW(), __vcop_once(), _PREG(12), _VREG(16));
   __vcop_vagen(_AGEN(0), _PREG(0), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeHU(), __vcop_1pt(), __vcop_alws(), _VREG(17), _PREG(6), _AGEN(0), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeHU(), __vcop_1pt(), __vcop_alws(), _VREG(16), _PREG(8), _AGEN(0), _PREG(0));
   __vcop_vloop_end(1u);

}

void vcop_select_list_elements_param_block_update(
   __vptr_uint16 pBlock,
   unsigned short pReg4Val,
   unsigned short pReg14Val)
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_select_list_elements_param_block_update_init(pBlock, pReg4Val, pReg14Val, __pblock_vcop_select_list_elements_param_block_update);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_select_list_elements_param_block_update_vloops(__pblock_vcop_select_list_elements_param_block_update);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

void vcop_select_list_elements_param_block_update_custom(
   __vptr_uint16 pBlock,
   unsigned short pReg4Val,
   unsigned short pReg14Val,
   unsigned short pblock[])
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_select_list_elements_param_block_update_init(pBlock, pReg4Val, pReg14Val, pblock);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_select_list_elements_param_block_update_vloops(pblock);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

