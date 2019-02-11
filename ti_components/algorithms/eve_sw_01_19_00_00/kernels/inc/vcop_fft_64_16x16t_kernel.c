#include <vcop\vcop.h>

typedef unsigned char uchar;

#pragma DATA_SECTION(__pblock_vcop_fft_64_16x16t_stage_1, ".vcop_parameter_block")
#pragma DATA_ALIGN(__pblock_vcop_fft_64_16x16t_stage_1, __ALIGNOF__(int));
unsigned short __pblock_vcop_fft_64_16x16t_stage_1[120];

unsigned short __ctrl_vcop_fft_64_16x16t_stage_1[1];

unsigned int vcop_fft_64_16x16t_stage_1_param_count(void)
{
   return 120u;
}

unsigned int vcop_fft_64_16x16t_stage_1_ctrl_count(void)
{
   return 1u;
}

unsigned int vcop_fft_64_16x16t_stage_1_init(
   __vptr_int16_arr Pxi0,
   __vptr_int16_arr Pxi1,
   __vptr_int16_arr Pxi2,
   __vptr_int16_arr Pxi3,
   __vptr_int16_arr PCS1,
   __vptr_int16_arr PCS2,
   __vptr_int16_arr PCS3,
   unsigned short bfys_per_grp[],
   unsigned short grps[],
   unsigned short passes,
   unsigned short pinc3[],
   unsigned short pinc4[],
   unsigned short ptnc3[],
   unsigned short ptnc4[],
   unsigned short pblock[])
{
   int I0;
   int __offset = 0;
   /* Loop 1 PREGS */

   __ctrl_vcop_fft_64_16x16t_stage_1[0] = passes - 1;
   for (I0 = 0; I0 < passes; I0++)
   {
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), (grps[I0])-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), (bfys_per_grp[I0])-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(6), __vcop_store_round_sat(SM_NONE,0,RM_TRUNC,15));
   __vcop_pblock_init16(pblock, __offset+_PREG(7), (pinc4[I0]));
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)Pxi2[I0]);
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)Pxi3[I0]);
   __vcop_pblock_init32(pblock, __offset+_PREG(12), (uchar *)PCS1[I0]);
   __vcop_pblock_init32(pblock, __offset+_PREG(14), (uchar *)PCS2[I0]);
   __vcop_pblock_init32(pblock, __offset+_PREG(16), (uchar *)PCS3[I0]);
   __vcop_pblock_init16(pblock, __offset+_PREG(18), (pinc3[I0]) -(pinc4[I0])*((bfys_per_grp[I0])-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(19), (ptnc4[I0]));
   __vcop_pblock_init16(pblock, __offset+_PREG(20), (ptnc3[I0]) -(ptnc4[I0])*((bfys_per_grp[I0])-1u));
   __vcop_pblock_init32(pblock, __offset+_PREG(22), (uchar *)Pxi0[I0]);
   __vcop_pblock_init32(pblock, __offset+_PREG(24), (uchar *)Pxi1[I0]);
   __offset += 24;
   }


   return 120u;
}

void vcop_fft_64_16x16t_stage_1_vloops(
   unsigned short pblock[])
{
   /* Kernel-wide Vector Registers */

   __vcop_param(&pblock[0]);

   /* VLOOP 1 Start */

   /* VLOOP Local Vector Registers */
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("Addr_in", "A0");
   #pragma EVE_REG("Addr_tw", "A1");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I0", "I0");
   #pragma EVE_REG("I3", "I3");
   #pragma EVE_REG("I4", "I4");
   

   __vcop_rpt(__ctrl_vcop_fft_64_16x16t_stage_1[0]);
   __vcop_vloop(__vcop_compute(), 50u, 12u, 1u);
   __vcop_vagen(_AGEN(0), _PREG(7), _PREG(18), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(1), _PREG(19), _PREG(20), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeH(), __vcop_dintrlv(), _PREG(22), _AGEN(0), _VPAIR(0,1), __vcop_alws());
   __vcop_vload(__vcop_sizeH(), __vcop_dintrlv(), _PREG(24), _AGEN(0), _VPAIR(2,3), __vcop_alws());
   __vcop_vload(__vcop_sizeH(), __vcop_dintrlv(), _PREG(8), _AGEN(0), _VPAIR(4,5), __vcop_alws());
   __vcop_vload(__vcop_sizeH(), __vcop_dintrlv(), _PREG(10), _AGEN(0), _VPAIR(6,7), __vcop_alws());
   __vcop_vload(__vcop_sizeH(), __vcop_dintrlv(), _PREG(12), _AGEN(1), _VPAIR(8,9), __vcop_alws());
   __vcop_vload(__vcop_sizeH(), __vcop_dintrlv(), _PREG(14), _AGEN(1), _VPAIR(10,11), __vcop_alws());
   __vcop_vload(__vcop_sizeH(), __vcop_dintrlv(), _PREG(16), _AGEN(1), _VPAIR(12,13), __vcop_alws());
   __vcop_vmove(_VREG(0), _VREG(0));
   __vcop_vmove(_VREG(4), _VREG(4));
   __vcop_vaddsub(_VREG(0), _VREG(4));
   __vcop_vmove(_VREG(1), _VREG(1));
   __vcop_vmove(_VREG(5), _VREG(5));
   __vcop_vaddsub(_VREG(1), _VREG(5));
   __vcop_vmove(_VREG(2), _VREG(2));
   __vcop_vmove(_VREG(6), _VREG(6));
   __vcop_vaddsub(_VREG(2), _VREG(6));
   __vcop_vmove(_VREG(3), _VREG(3));
   __vcop_vmove(_VREG(7), _VREG(7));
   __vcop_vaddsub(_VREG(3), _VREG(7));
   __vcop_vmove(_VREG(0), _VREG(0));
   __vcop_vmove(_VREG(2), _VREG(2));
   __vcop_vaddsub(_VREG(0), _VREG(2));
   __vcop_vmove(_VREG(4), _VREG(4));
   __vcop_vmove(_VREG(7), _VREG(7));
   __vcop_vaddsub(_VREG(4), _VREG(7));
   __vcop_vmove(_VREG(1), _VREG(1));
   __vcop_vmove(_VREG(3), _VREG(3));
   __vcop_vaddsub(_VREG(1), _VREG(3));
   __vcop_vmove(_VREG(5), _VREG(5));
   __vcop_vmove(_VREG(6), _VREG(6));
   __vcop_vaddsub(_VREG(5), _VREG(6));
   __vcop_vmpy(_VREG(2), _VREG(11), _VREG(14), _PREG(0));
   __vcop_vmpy(_VREG(3), _VREG(11), _VREG(15), _PREG(0));
   __vcop_vmadd(_VREG(3), _VREG(10), _VREG(14), _PREG(0));
   __vcop_vmsub(_VREG(2), _VREG(10), _VREG(15), _PREG(0));
   __vcop_vmpy(_VREG(4), _VREG(9), _VREG(10), _PREG(0));
   __vcop_vmpy(_VREG(6), _VREG(9), _VREG(11), _PREG(0));
   __vcop_vmpy(_VREG(7), _VREG(13), _VREG(2), _PREG(0));
   __vcop_vmpy(_VREG(5), _VREG(13), _VREG(3), _PREG(0));
   __vcop_vmadd(_VREG(6), _VREG(8), _VREG(10), _PREG(0));
   __vcop_vmsub(_VREG(4), _VREG(8), _VREG(11), _PREG(0));
   __vcop_vmadd(_VREG(5), _VREG(12), _VREG(2), _PREG(0));
   __vcop_vmsub(_VREG(7), _VREG(12), _VREG(3), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeH(), __vcop_intrlv(), __vcop_alws(), _VPAIR(0,1), _PREG(22), _AGEN(0), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeH(), __vcop_intrlv(), __vcop_alws(), _VPAIR(10,11), _PREG(24), _AGEN(0), _PREG(6));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeH(), __vcop_intrlv(), __vcop_alws(), _VPAIR(14,15), _PREG(8), _AGEN(0), _PREG(6));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeH(), __vcop_intrlv(), __vcop_alws(), _VPAIR(2,3), _PREG(10), _AGEN(0), _PREG(6));
   __vcop_vloop_end(1u);

}

void vcop_fft_64_16x16t_stage_1(
   __vptr_int16_arr Pxi0,
   __vptr_int16_arr Pxi1,
   __vptr_int16_arr Pxi2,
   __vptr_int16_arr Pxi3,
   __vptr_int16_arr PCS1,
   __vptr_int16_arr PCS2,
   __vptr_int16_arr PCS3,
   unsigned short bfys_per_grp[],
   unsigned short grps[],
   unsigned short passes,
   unsigned short pinc3[],
   unsigned short pinc4[],
   unsigned short ptnc3[],
   unsigned short ptnc4[])
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_fft_64_16x16t_stage_1_init(Pxi0, Pxi1, Pxi2, Pxi3, PCS1, PCS2, PCS3, bfys_per_grp, grps, passes, pinc3, pinc4, ptnc3, ptnc4, __pblock_vcop_fft_64_16x16t_stage_1);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_fft_64_16x16t_stage_1_vloops(__pblock_vcop_fft_64_16x16t_stage_1);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

void vcop_fft_64_16x16t_stage_1_custom(
   __vptr_int16_arr Pxi0,
   __vptr_int16_arr Pxi1,
   __vptr_int16_arr Pxi2,
   __vptr_int16_arr Pxi3,
   __vptr_int16_arr PCS1,
   __vptr_int16_arr PCS2,
   __vptr_int16_arr PCS3,
   unsigned short bfys_per_grp[],
   unsigned short grps[],
   unsigned short passes,
   unsigned short pinc3[],
   unsigned short pinc4[],
   unsigned short ptnc3[],
   unsigned short ptnc4[],
   unsigned short pblock[])
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_fft_64_16x16t_stage_1_init(Pxi0, Pxi1, Pxi2, Pxi3, PCS1, PCS2, PCS3, bfys_per_grp, grps, passes, pinc3, pinc4, ptnc3, ptnc4, pblock);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_fft_64_16x16t_stage_1_vloops(pblock);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

#pragma DATA_SECTION(__pblock_vcop_fft_64_16x16t_stage2, ".vcop_parameter_block")
#pragma DATA_ALIGN(__pblock_vcop_fft_64_16x16t_stage2, __ALIGNOF__(int));
unsigned short __pblock_vcop_fft_64_16x16t_stage2[24];

unsigned int vcop_fft_64_16x16t_stage2_param_count(void)
{
   return 24u;
}

unsigned int vcop_fft_64_16x16t_stage2_ctrl_count(void)
{
   return 0u;
}

unsigned int vcop_fft_64_16x16t_stage2_init(
   __vptr_int16 Pxi0,
   __vptr_int16 Pxi1,
   __vptr_int16 Pxi2,
   __vptr_int16 Pxi3,
   __vptr_int16 PCS1,
   __vptr_int16 PCS2,
   __vptr_int16 PCS3,
   unsigned short bfys_per_grp,
   unsigned short grps,
   unsigned short pinc3,
   unsigned short pinc4,
   unsigned short ptnc3,
   unsigned short ptnc4,
   unsigned short pblock[])
{
   int __offset = 0;
   /* Loop 1 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), (grps)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), (bfys_per_grp)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(6), __vcop_store_round_sat(SM_NONE,0,RM_TRUNC,15));
   __vcop_pblock_init16(pblock, __offset+_PREG(7), (pinc4));
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)Pxi2);
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)Pxi3);
   __vcop_pblock_init32(pblock, __offset+_PREG(12), (uchar *)PCS1);
   __vcop_pblock_init32(pblock, __offset+_PREG(14), (uchar *)PCS2);
   __vcop_pblock_init32(pblock, __offset+_PREG(16), (uchar *)PCS3);
   __vcop_pblock_init16(pblock, __offset+_PREG(18), (pinc3) -(pinc4)*((bfys_per_grp)-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(19), (ptnc4));
   __vcop_pblock_init16(pblock, __offset+_PREG(20), (ptnc3) -(ptnc4)*((bfys_per_grp)-1u));
   __vcop_pblock_init32(pblock, __offset+_PREG(22), (uchar *)Pxi0);
   __vcop_pblock_init32(pblock, __offset+_PREG(24), (uchar *)Pxi1);
   __offset += 24;

   return 24u;
}

void vcop_fft_64_16x16t_stage2_vloops(
   unsigned short pblock[])
{
   /* Kernel-wide Vector Registers */

   __vcop_param(&pblock[0]);

   /* VLOOP 1 Start */

   /* VLOOP Local Vector Registers */
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("Addr_in", "A0");
   #pragma EVE_REG("Addr_tw", "A1");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I3", "I3");
   #pragma EVE_REG("I4", "I4");
   

   __vcop_vloop(__vcop_compute(), 54u, 12u, 1u);
   __vcop_vagen(_AGEN(0), _PREG(7), _PREG(18), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(1), _PREG(19), _PREG(20), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeH(), __vcop_dintrlv(), _PREG(22), _AGEN(0), _VPAIR(0,1), __vcop_alws());
   __vcop_vload(__vcop_sizeH(), __vcop_dintrlv(), _PREG(24), _AGEN(0), _VPAIR(4,5), __vcop_alws());
   __vcop_vload(__vcop_sizeH(), __vcop_dintrlv(), _PREG(8), _AGEN(0), _VPAIR(2,3), __vcop_alws());
   __vcop_vload(__vcop_sizeH(), __vcop_dintrlv(), _PREG(10), _AGEN(0), _VPAIR(6,7), __vcop_alws());
   __vcop_vload(__vcop_sizeH(), __vcop_dintrlv(), _PREG(12), _AGEN(1), _VPAIR(8,9), __vcop_alws());
   __vcop_vload(__vcop_sizeH(), __vcop_dintrlv(), _PREG(14), _AGEN(1), _VPAIR(10,11), __vcop_alws());
   __vcop_vload(__vcop_sizeH(), __vcop_dintrlv(), _PREG(16), _AGEN(1), _VPAIR(12,13), __vcop_alws());
   __vcop_vintrlv4(_VREG(0), _VREG(2));
   __vcop_vintrlv4(_VREG(4), _VREG(6));
   __vcop_vintrlv4(_VREG(1), _VREG(3));
   __vcop_vintrlv4(_VREG(5), _VREG(7));
   __vcop_vmove(_VREG(0), _VREG(0));
   __vcop_vmove(_VREG(4), _VREG(4));
   __vcop_vaddsub(_VREG(0), _VREG(4));
   __vcop_vmove(_VREG(1), _VREG(1));
   __vcop_vmove(_VREG(5), _VREG(5));
   __vcop_vaddsub(_VREG(1), _VREG(5));
   __vcop_vmove(_VREG(2), _VREG(2));
   __vcop_vmove(_VREG(6), _VREG(6));
   __vcop_vaddsub(_VREG(2), _VREG(6));
   __vcop_vmove(_VREG(3), _VREG(3));
   __vcop_vmove(_VREG(7), _VREG(7));
   __vcop_vaddsub(_VREG(3), _VREG(7));
   __vcop_vmove(_VREG(0), _VREG(0));
   __vcop_vmove(_VREG(2), _VREG(2));
   __vcop_vaddsub(_VREG(0), _VREG(2));
   __vcop_vmove(_VREG(4), _VREG(4));
   __vcop_vmove(_VREG(7), _VREG(7));
   __vcop_vaddsub(_VREG(4), _VREG(7));
   __vcop_vmove(_VREG(1), _VREG(1));
   __vcop_vmove(_VREG(3), _VREG(3));
   __vcop_vaddsub(_VREG(1), _VREG(3));
   __vcop_vmove(_VREG(5), _VREG(5));
   __vcop_vmove(_VREG(6), _VREG(6));
   __vcop_vaddsub(_VREG(5), _VREG(6));
   __vcop_vmpy(_VREG(2), _VREG(11), _VREG(14), _PREG(0));
   __vcop_vmpy(_VREG(3), _VREG(11), _VREG(15), _PREG(0));
   __vcop_vmadd(_VREG(3), _VREG(10), _VREG(14), _PREG(0));
   __vcop_vmsub(_VREG(2), _VREG(10), _VREG(15), _PREG(0));
   __vcop_vmpy(_VREG(4), _VREG(9), _VREG(10), _PREG(0));
   __vcop_vmpy(_VREG(6), _VREG(9), _VREG(11), _PREG(0));
   __vcop_vmpy(_VREG(7), _VREG(13), _VREG(2), _PREG(0));
   __vcop_vmpy(_VREG(5), _VREG(13), _VREG(3), _PREG(0));
   __vcop_vmadd(_VREG(6), _VREG(8), _VREG(10), _PREG(0));
   __vcop_vmsub(_VREG(4), _VREG(8), _VREG(11), _PREG(0));
   __vcop_vmadd(_VREG(5), _VREG(12), _VREG(2), _PREG(0));
   __vcop_vmsub(_VREG(7), _VREG(12), _VREG(3), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeH(), __vcop_intrlv(), __vcop_alws(), _VPAIR(0,1), _PREG(22), _AGEN(0), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeH(), __vcop_intrlv(), __vcop_alws(), _VPAIR(14,15), _PREG(24), _AGEN(0), _PREG(6));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeH(), __vcop_intrlv(), __vcop_alws(), _VPAIR(10,11), _PREG(8), _AGEN(0), _PREG(6));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeH(), __vcop_intrlv(), __vcop_alws(), _VPAIR(2,3), _PREG(10), _AGEN(0), _PREG(6));
   __vcop_vloop_end(1u);

}

void vcop_fft_64_16x16t_stage2(
   __vptr_int16 Pxi0,
   __vptr_int16 Pxi1,
   __vptr_int16 Pxi2,
   __vptr_int16 Pxi3,
   __vptr_int16 PCS1,
   __vptr_int16 PCS2,
   __vptr_int16 PCS3,
   unsigned short bfys_per_grp,
   unsigned short grps,
   unsigned short pinc3,
   unsigned short pinc4,
   unsigned short ptnc3,
   unsigned short ptnc4)
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_fft_64_16x16t_stage2_init(Pxi0, Pxi1, Pxi2, Pxi3, PCS1, PCS2, PCS3, bfys_per_grp, grps, pinc3, pinc4, ptnc3, ptnc4, __pblock_vcop_fft_64_16x16t_stage2);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_fft_64_16x16t_stage2_vloops(__pblock_vcop_fft_64_16x16t_stage2);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

void vcop_fft_64_16x16t_stage2_custom(
   __vptr_int16 Pxi0,
   __vptr_int16 Pxi1,
   __vptr_int16 Pxi2,
   __vptr_int16 Pxi3,
   __vptr_int16 PCS1,
   __vptr_int16 PCS2,
   __vptr_int16 PCS3,
   unsigned short bfys_per_grp,
   unsigned short grps,
   unsigned short pinc3,
   unsigned short pinc4,
   unsigned short ptnc3,
   unsigned short ptnc4,
   unsigned short pblock[])
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_fft_64_16x16t_stage2_init(Pxi0, Pxi1, Pxi2, Pxi3, PCS1, PCS2, PCS3, bfys_per_grp, grps, pinc3, pinc4, ptnc3, ptnc4, pblock);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_fft_64_16x16t_stage2_vloops(pblock);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

#pragma DATA_SECTION(__pblock_vcop_fft_64_16x16t_stage3, ".vcop_parameter_block")
#pragma DATA_ALIGN(__pblock_vcop_fft_64_16x16t_stage3, __ALIGNOF__(int));
unsigned short __pblock_vcop_fft_64_16x16t_stage3[16];

unsigned int vcop_fft_64_16x16t_stage3_param_count(void)
{
   return 16u;
}

unsigned int vcop_fft_64_16x16t_stage3_ctrl_count(void)
{
   return 0u;
}

unsigned int vcop_fft_64_16x16t_stage3_init(
   __vptr_int16 Pxi0,
   __vptr_int16 Pxi1,
   __vptr_int16 Pxi2,
   __vptr_int16 Pxi3,
   unsigned short bfys_per_grp,
   unsigned short grps,
   unsigned short pinc3,
   unsigned short pinc4,
   unsigned short pblock[])
{
   int __offset = 0;
   /* Loop 1 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), (grps)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), (bfys_per_grp)-1u);
   __vcop_pblock_init32(pblock, __offset+_PREG(6), (uchar *)Pxi1);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)Pxi2);
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)Pxi3);
   __vcop_pblock_init16(pblock, __offset+_PREG(12), (pinc4));
   __vcop_pblock_init16(pblock, __offset+_PREG(13), (pinc3) -(pinc4)*((bfys_per_grp)-1u));
   __vcop_pblock_init32(pblock, __offset+_PREG(14), 1);
   __vcop_pblock_init32(pblock, __offset+_PREG(16), (uchar *)Pxi0);
   __offset += 16;

   return 16u;
}

void vcop_fft_64_16x16t_stage3_vloops(
   unsigned short pblock[])
{
   /* Kernel-wide Vector Registers */

   __vcop_param(&pblock[0]);

   /* VLOOP 1 Start */

   /* VLOOP Local Vector Registers */
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("Addr_in", "A0");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I3", "I3");
   #pragma EVE_REG("I4", "I4");
   

   __vcop_vloop(__vcop_compute(), 41u, 8u, 1u);
   __vcop_vinit(__vcop_sizeW(), __vcop_once(), _PREG(14), _VREG(0));
   __vcop_vagen(_AGEN(0), _PREG(12), _PREG(13), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeH(), __vcop_dintrlv(), _PREG(16), _AGEN(0), _VPAIR(2,3), __vcop_alws());
   __vcop_vload(__vcop_sizeH(), __vcop_dintrlv(), _PREG(6), _AGEN(0), _VPAIR(4,5), __vcop_alws());
   __vcop_vload(__vcop_sizeH(), __vcop_dintrlv(), _PREG(8), _AGEN(0), _VPAIR(6,7), __vcop_alws());
   __vcop_vload(__vcop_sizeH(), __vcop_dintrlv(), _PREG(10), _AGEN(0), _VPAIR(8,9), __vcop_alws());
   __vcop_vintrlv4(_VREG(2), _VREG(6));
   __vcop_vintrlv4(_VREG(4), _VREG(8));
   __vcop_vintrlv4(_VREG(3), _VREG(7));
   __vcop_vintrlv4(_VREG(5), _VREG(9));
   __vcop_vintrlv4(_VREG(2), _VREG(4));
   __vcop_vintrlv4(_VREG(6), _VREG(8));
   __vcop_vintrlv2(_VREG(2), _VREG(4));
   __vcop_vintrlv2(_VREG(6), _VREG(8));
   __vcop_vintrlv4(_VREG(2), _VREG(4));
   __vcop_vintrlv4(_VREG(6), _VREG(8));
   __vcop_vdintrlv(_VREG(2), _VREG(6));
   __vcop_vdintrlv(_VREG(4), _VREG(8));
   __vcop_vintrlv4(_VREG(3), _VREG(5));
   __vcop_vintrlv4(_VREG(7), _VREG(9));
   __vcop_vintrlv2(_VREG(3), _VREG(5));
   __vcop_vintrlv2(_VREG(7), _VREG(9));
   __vcop_vintrlv4(_VREG(3), _VREG(5));
   __vcop_vintrlv4(_VREG(7), _VREG(9));
   __vcop_vdintrlv(_VREG(3), _VREG(7));
   __vcop_vdintrlv(_VREG(5), _VREG(9));
   __vcop_vaddsub(_VREG(2), _VREG(4));
   __vcop_vaddsub(_VREG(3), _VREG(5));
   __vcop_vaddsub(_VREG(6), _VREG(8));
   __vcop_vaddsub(_VREG(7), _VREG(9));
   __vcop_vaddsub(_VREG(2), _VREG(6));
   __vcop_vaddsub(_VREG(3), _VREG(7));
   __vcop_vaddsub(_VREG(4), _VREG(9));
   __vcop_vaddsub(_VREG(5), _VREG(8));
   __vcop_vswap(_VREG(0), _VREG(8), _VREG(5));
   __vcop_vswap(_VREG(0), _VREG(8), _VREG(9));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeH(), __vcop_intrlv(), __vcop_alws(), _VPAIR(2,3), _PREG(16), _AGEN(0), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeH(), __vcop_intrlv(), __vcop_alws(), _VPAIR(4,5), _PREG(6), _AGEN(0), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeH(), __vcop_intrlv(), __vcop_alws(), _VPAIR(6,7), _PREG(8), _AGEN(0), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeH(), __vcop_intrlv(), __vcop_alws(), _VPAIR(8,9), _PREG(10), _AGEN(0), _PREG(0));
   __vcop_vloop_end(1u);

}

void vcop_fft_64_16x16t_stage3(
   __vptr_int16 Pxi0,
   __vptr_int16 Pxi1,
   __vptr_int16 Pxi2,
   __vptr_int16 Pxi3,
   unsigned short bfys_per_grp,
   unsigned short grps,
   unsigned short pinc3,
   unsigned short pinc4)
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_fft_64_16x16t_stage3_init(Pxi0, Pxi1, Pxi2, Pxi3, bfys_per_grp, grps, pinc3, pinc4, __pblock_vcop_fft_64_16x16t_stage3);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_fft_64_16x16t_stage3_vloops(__pblock_vcop_fft_64_16x16t_stage3);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

void vcop_fft_64_16x16t_stage3_custom(
   __vptr_int16 Pxi0,
   __vptr_int16 Pxi1,
   __vptr_int16 Pxi2,
   __vptr_int16 Pxi3,
   unsigned short bfys_per_grp,
   unsigned short grps,
   unsigned short pinc3,
   unsigned short pinc4,
   unsigned short pblock[])
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_fft_64_16x16t_stage3_init(Pxi0, Pxi1, Pxi2, Pxi3, bfys_per_grp, grps, pinc3, pinc4, pblock);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_fft_64_16x16t_stage3_vloops(pblock);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

#pragma DATA_SECTION(__pblock_vcop_fft_digit_rev_64, ".vcop_parameter_block")
#pragma DATA_ALIGN(__pblock_vcop_fft_digit_rev_64, __ALIGNOF__(int));
unsigned short __pblock_vcop_fft_digit_rev_64[16];

unsigned int vcop_fft_digit_rev_64_param_count(void)
{
   return 16u;
}

unsigned int vcop_fft_digit_rev_64_ctrl_count(void)
{
   return 0u;
}

unsigned int vcop_fft_digit_rev_64_init(
   __vptr_int32 Px,
   __vptr_uint16 digit_rev,
   __vptr_int32 Py,
   unsigned short pblock[])
{
   int __offset = 0;
   /* Loop 1 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), (4)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), (2)-1u);
   __vcop_pblock_init32(pblock, __offset+_PREG(6), (uchar *)Py);
   __vcop_pblock_init16(pblock, __offset+_PREG(8), 16);
   __vcop_pblock_init16(pblock, __offset+_PREG(9), -16);
   __vcop_pblock_init16(pblock, __offset+_PREG(10), 128);
   __vcop_pblock_init16(pblock, __offset+_PREG(11), -96);
   __vcop_pblock_init16(pblock, __offset+_PREG(12), 64);
   __vcop_pblock_init32(pblock, __offset+_PREG(14), (uchar *)Px);
   __vcop_pblock_init32(pblock, __offset+_PREG(16), (uchar *)digit_rev);
   __offset += 16;

   return 16u;
}

void vcop_fft_digit_rev_64_vloops(
   unsigned short pblock[])
{
   /* Kernel-wide Vector Registers */

   __vcop_param(&pblock[0]);

   /* VLOOP 1 Start */

   /* VLOOP Local Vector Registers */
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("Addr_d", "A0");
   #pragma EVE_REG("Addr_in", "A1");
   #pragma EVE_REG("Addr_o", "A2");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I3", "I3");
   #pragma EVE_REG("I4", "I4");
   

   __vcop_vloop(__vcop_compute(), 7u, 8u, 1u);
   __vcop_vagen(_AGEN(0), _PREG(8), _PREG(9), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(1), _PREG(10), _PREG(11), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(2), _PREG(0), _PREG(12), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeW(), __vcop_npt(), _PREG(14), _AGEN(1), _VREG(2), __vcop_alws());
   __vcop_vload(__vcop_sizeHU(), __vcop_npt(), _PREG(16), _AGEN(0), _VREG(0), __vcop_alws());
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeW(), __vcop_sdda(_VREG(0)), __vcop_alws(), _VREG(2), _PREG(6), _AGEN(2), _PREG(0));
   __vcop_vloop_end(1u);

}

void vcop_fft_digit_rev_64(
   __vptr_int32 Px,
   __vptr_uint16 digit_rev,
   __vptr_int32 Py)
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_fft_digit_rev_64_init(Px, digit_rev, Py, __pblock_vcop_fft_digit_rev_64);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_fft_digit_rev_64_vloops(__pblock_vcop_fft_digit_rev_64);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

void vcop_fft_digit_rev_64_custom(
   __vptr_int32 Px,
   __vptr_uint16 digit_rev,
   __vptr_int32 Py,
   unsigned short pblock[])
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_fft_digit_rev_64_init(Px, digit_rev, Py, pblock);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_fft_digit_rev_64_vloops(pblock);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

