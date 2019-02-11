#include <vcop\vcop.h>

typedef unsigned char uchar;

#pragma DATA_SECTION(__pblock_vcop_normalFlow, ".vcop_parameter_block")
#pragma DATA_ALIGN(__pblock_vcop_normalFlow, __ALIGNOF__(int));
unsigned short __pblock_vcop_normalFlow[38];

unsigned int vcop_normalFlow_param_count(void)
{
   return 38u;
}

unsigned int vcop_normalFlow_ctrl_count(void)
{
   return 0u;
}

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
   unsigned short pblock[])
{
   int __offset = 0;
   /* Loop 1 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), (numEls/(8))-1u);
   __vcop_pblock_init32(pblock, __offset+_PREG(6), (uchar *)TLU_m_inv);
   __vcop_pblock_init16(pblock, __offset+_PREG(8), 16);
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)Emag);
   __vcop_pblock_init32(pblock, __offset+_PREG(12), (uchar *)LUT);
   __offset += 12;

   /* Loop 2 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), (numEls/(8u))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(6), __vcop_store_round_sat(SM_NONE,0,RM_TRUNC,7));
   __vcop_pblock_init16(pblock, __offset+_PREG(7), __vcop_vop_round(2, 8));
   __vcop_pblock_init32(pblock, __offset+_PREG(8), 0);
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)Emag);
   __vcop_pblock_init32(pblock, __offset+_PREG(12), (uchar *)imDiff);
   __vcop_pblock_init32(pblock, __offset+_PREG(14), (uchar *)TLU_m_inv);
   __vcop_pblock_init32(pblock, __offset+_PREG(16), (uchar *)E);
   __vcop_pblock_init32(pblock, __offset+_PREG(18), (uchar *)normalFlowU);
   __vcop_pblock_init32(pblock, __offset+_PREG(20), (uchar *)normalFlowV);
   __vcop_pblock_init16(pblock, __offset+_PREG(22), 16);
   __vcop_pblock_init16(pblock, __offset+_PREG(23), 32);
   __vcop_pblock_init32(pblock, __offset+_PREG(24), -8);
   __vcop_pblock_init32(pblock, __offset+_PREG(26), T);
   __offset += 26;

   return 38u;
}

void vcop_normalFlow_vloops(
   unsigned short pblock[])
{
   /* Kernel-wide Vector Registers */
   #pragma VCC_VREG("Ex_1", 16);
   #pragma VCC_VREG("Ex_2", 17);
   #pragma VCC_VREG("Ey_1", 18);
   #pragma VCC_VREG("Ey_2", 19);
   #pragma VCC_VREG("R0", 20);
   #pragma VCC_VREG("R1", 21);
   #pragma VCC_VREG("R2", 22);
   #pragma VCC_VREG("R3", 23);
   #pragma VCC_VREG("Vdst", 24);
   #pragma VCC_VREG("Vindex", 25);
   #pragma VCC_VREG("Vpred", 26);
   #pragma VCC_VREG("Vtabledata", 27);
   #pragma VCC_VREG("d", 28);
   #pragma VCC_VREG("d_1", 29);
   #pragma VCC_VREG("ex", 30);
   #pragma VCC_VREG("exd", 31);
   #pragma VCC_VREG("ey", 32);
   #pragma VCC_VREG("eyd", 33);
   #pragma VCC_VREG("im", 34);
   #pragma VCC_VREG("im_1", 35);
   #pragma VCC_VREG("m", 36);
   #pragma VCC_VREG("m_inv", 37);

   __vcop_param(&pblock[0]);

   /* VLOOP 1 Start */

   /* VLOOP Local Vector Registers */
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("index_addr", "A0");
   #pragma EVE_REG("out_addr", "A2");
   #pragma EVE_REG("table_addr", "A1");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I1", "I4");
   

   __vcop_vloop(__vcop_tablelkup(), 7u, 6u, 1u);
   __vcop_vagen(_AGEN(0), _PREG(8), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(2), _PREG(8), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(1), _PREG(0), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeH(), __vcop_npt(), _PREG(10), _AGEN(0), _VREG(25), __vcop_alws());
   __vcop_vtbload(__vcop_sizeH(), __vcop_tableinfo(8, 1), _PREG(12), _AGEN(1), _VREG(25), _VREG(27), _PREG(0), __vcop_alws());
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeH(), __vcop_npt(), __vcop_alws(), _VREG(27), _PREG(6), _AGEN(2), _PREG(0));
   __vcop_vloop_end(1u);

   /* VLOOP 2 Start */

   /* VLOOP Local Vector Registers */
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("Addr", "A0");
   #pragma EVE_REG("Addr1", "A1");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I1", "I4");
   

   __vcop_vloop(__vcop_compute(), 19u, 13u, 2u);
   __vcop_vinit(__vcop_sizeW(), __vcop_once(), _PREG(24), _VREG(20));
   __vcop_vinit(__vcop_sizeW(), __vcop_once(), _PREG(26), _VREG(22));
   __vcop_vinit(__vcop_sizeW(), __vcop_once(), _PREG(8), _VREG(23));
   __vcop_vagen(_AGEN(0), _PREG(22), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(1), _PREG(23), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeH(), __vcop_npt(), _PREG(10), _AGEN(0), _VREG(36), __vcop_alws());
   __vcop_vload(__vcop_sizeH(), __vcop_npt(), _PREG(12), _AGEN(0), _VREG(34), __vcop_alws());
   __vcop_vload(__vcop_sizeH(), __vcop_npt(), _PREG(14), _AGEN(0), _VREG(37), __vcop_alws());
   __vcop_vload(__vcop_sizeH(), __vcop_dintrlv(), _PREG(16), _AGEN(1), _VPAIR(16,18), __vcop_alws());
   __vcop_vmpy(_VREG(16), _VREG(37), _VREG(17), _PREG(7));
   __vcop_vmpy(_VREG(18), _VREG(37), _VREG(19), _PREG(7));
   __vcop_vsub(_VREG(23), _VREG(34), _VREG(35));
   __vcop_vmpy(_VREG(35), _VREG(37), _VREG(28), _PREG(7));
   __vcop_vmpy(_VREG(17), _VREG(28), _VREG(31), _PREG(0));
   __vcop_vmpy(_VREG(19), _VREG(28), _VREG(33), _PREG(0));
   __vcop_vcmpgt(_VREG(36), _VREG(22), _VREG(26));
   __vcop_vstore(__vcop_predicate(_VREG(26)), __vcop_sizeH(), __vcop_npt(), __vcop_alws(), _VREG(31), _PREG(18), _AGEN(0), _PREG(6));
   __vcop_vstore(__vcop_predicate(_VREG(26)), __vcop_sizeH(), __vcop_npt(), __vcop_alws(), _VREG(33), _PREG(20), _AGEN(0), _PREG(6));
   __vcop_vloop_end(2u);

}

void vcop_normalFlow(
   __vptr_int16 imDiff,
   __vptr_int16 Emag,
   __vptr_int16 LUT,
   __vptr_int16 E,
   __vptr_int16 TLU_m_inv,
   int T,
   short numEls,
   __vptr_int16 normalFlowU,
   __vptr_int16 normalFlowV)
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_normalFlow_init(imDiff, Emag, LUT, E, TLU_m_inv, T, numEls, normalFlowU, normalFlowV, __pblock_vcop_normalFlow);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_normalFlow_vloops(__pblock_vcop_normalFlow);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

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
   unsigned short pblock[])
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_normalFlow_init(imDiff, Emag, LUT, E, TLU_m_inv, T, numEls, normalFlowU, normalFlowV, pblock);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_normalFlow_vloops(pblock);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

