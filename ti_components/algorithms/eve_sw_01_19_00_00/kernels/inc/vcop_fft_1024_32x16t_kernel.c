#include <vcop\vcop.h>

typedef unsigned char uchar;

#pragma DATA_SECTION(__pblock_vcop_fft_1024_32x16t_stage1_0, ".vcop_parameter_block")
#pragma DATA_ALIGN(__pblock_vcop_fft_1024_32x16t_stage1_0, __ALIGNOF__(int));
unsigned short __pblock_vcop_fft_1024_32x16t_stage1_0[38];

unsigned int vcop_fft_1024_32x16t_stage1_0_param_count(void)
{
   return 38u;
}

unsigned int vcop_fft_1024_32x16t_stage1_0_ctrl_count(void)
{
   return 0u;
}

unsigned int vcop_fft_1024_32x16t_stage1_0_init(
   __vptr_int32 Pin_xyL0_0123,
   __vptr_int32 Pin_xyL0_4567,
   __vptr_int32 Pin_xyL1_0123,
   __vptr_int32 Pin_xyL1_4567,
   __vptr_int32 Pin_xyL2_0123,
   __vptr_int32 Pin_xyL2_4567,
   __vptr_int32 Pin_xyL3_0123,
   __vptr_int32 Pin_xyL3_4567,
   __vptr_int32 Pou_xyL0_0123,
   __vptr_int32 Pou_xyL0_4567,
   __vptr_int32 Pou_xyL1_0123,
   __vptr_int32 Pou_xyL1_4567,
   __vptr_int32 Pou_xyL2_0123,
   __vptr_int32 Pou_xyL2_4567,
   __vptr_int32 Pou_xyL3_0123,
   __vptr_int32 Pou_xyL3_4567,
   unsigned short pblock[])
{
   int __offset = 0;
   /* Loop 1 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), (32)-1u);
   __vcop_pblock_init32(pblock, __offset+_PREG(6), (uchar *)Pin_xyL1_0123);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)Pin_xyL1_4567);
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)Pin_xyL2_0123);
   __vcop_pblock_init32(pblock, __offset+_PREG(12), (uchar *)Pin_xyL2_4567);
   __vcop_pblock_init32(pblock, __offset+_PREG(14), (uchar *)Pin_xyL3_0123);
   __vcop_pblock_init32(pblock, __offset+_PREG(16), (uchar *)Pin_xyL3_4567);
   __vcop_pblock_init32(pblock, __offset+_PREG(18), (uchar *)Pou_xyL0_0123);
   __vcop_pblock_init32(pblock, __offset+_PREG(20), (uchar *)Pou_xyL0_4567);
   __vcop_pblock_init32(pblock, __offset+_PREG(22), (uchar *)Pou_xyL1_0123);
   __vcop_pblock_init32(pblock, __offset+_PREG(24), (uchar *)Pou_xyL1_4567);
   __vcop_pblock_init32(pblock, __offset+_PREG(26), (uchar *)Pou_xyL2_0123);
   __vcop_pblock_init32(pblock, __offset+_PREG(28), (uchar *)Pou_xyL2_4567);
   __vcop_pblock_init32(pblock, __offset+_PREG(30), (uchar *)Pou_xyL3_0123);
   __vcop_pblock_init32(pblock, __offset+_PREG(32), (uchar *)Pou_xyL3_4567);
   __vcop_pblock_init16(pblock, __offset+_PREG(34), 64);
   __vcop_pblock_init32(pblock, __offset+_PREG(36), (uchar *)Pin_xyL0_0123);
   __vcop_pblock_init32(pblock, __offset+_PREG(38), (uchar *)Pin_xyL0_4567);
   __offset += 38;

   return 38u;
}

void vcop_fft_1024_32x16t_stage1_0_vloops(
   unsigned short pblock[])
{
   /* Kernel-wide Vector Registers */

   __vcop_param(&pblock[0]);

   /* VLOOP 1 Start */

   /* VLOOP Local Vector Registers */
   #pragma VCC_VREG("VXY_L0_0123", 16);
   #pragma VCC_VREG("VXY_L0_4567", 17);
   #pragma VCC_VREG("VXY_L1_0123", 18);
   #pragma VCC_VREG("VXY_L1_4567", 19);
   #pragma VCC_VREG("VXY_L2_0123", 20);
   #pragma VCC_VREG("VXY_L2_4567", 21);
   #pragma VCC_VREG("VXY_L3_0123", 22);
   #pragma VCC_VREG("VXY_L3_4567", 23);
   #pragma VCC_VREG("VX_L0_01234567", 24);
   #pragma VCC_VREG("VX_L1_01234567", 25);
   #pragma VCC_VREG("VX_L2_01234567", 26);
   #pragma VCC_VREG("VX_L3_01234567", 27);
   #pragma VCC_VREG("VY_L0_01234567", 28);
   #pragma VCC_VREG("VY_L1_01234567", 29);
   #pragma VCC_VREG("VY_L2_01234567", 30);
   #pragma VCC_VREG("VY_L3_01234567", 31);
   #pragma VCC_VREG("V_x0r", 32);
   #pragma VCC_VREG("V_xt1", 33);
   #pragma VCC_VREG("V_xt2", 34);
   #pragma VCC_VREG("V_xt3", 35);
   #pragma VCC_VREG("V_y0i", 36);
   #pragma VCC_VREG("V_yt1", 37);
   #pragma VCC_VREG("V_yt2", 38);
   #pragma VCC_VREG("V_yt3", 39);
   #pragma VCC_VREG("Vxh0", 40);
   #pragma VCC_VREG("Vxh1", 41);
   #pragma VCC_VREG("Vxh20", 42);
   #pragma VCC_VREG("Vxh21", 43);
   #pragma VCC_VREG("Vxl0", 44);
   #pragma VCC_VREG("Vxl1", 45);
   #pragma VCC_VREG("Vxl20", 46);
   #pragma VCC_VREG("Vxl21", 47);
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("Addr_in", "A0");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I3", "I4");
   

   __vcop_vloop(__vcop_compute(), 54u, 19u, 1u);
   __vcop_vagen(_AGEN(0), _PREG(34), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeW(), __vcop_npt(), _PREG(36), _AGEN(0), _VREG(16), __vcop_alws());
   __vcop_vload(__vcop_sizeW(), __vcop_npt(), _PREG(38), _AGEN(0), _VREG(17), __vcop_alws());
   __vcop_vload(__vcop_sizeW(), __vcop_npt(), _PREG(6), _AGEN(0), _VREG(18), __vcop_alws());
   __vcop_vload(__vcop_sizeW(), __vcop_npt(), _PREG(8), _AGEN(0), _VREG(19), __vcop_alws());
   __vcop_vload(__vcop_sizeW(), __vcop_npt(), _PREG(10), _AGEN(0), _VREG(20), __vcop_alws());
   __vcop_vload(__vcop_sizeW(), __vcop_npt(), _PREG(12), _AGEN(0), _VREG(21), __vcop_alws());
   __vcop_vload(__vcop_sizeW(), __vcop_npt(), _PREG(14), _AGEN(0), _VREG(22), __vcop_alws());
   __vcop_vload(__vcop_sizeW(), __vcop_npt(), _PREG(16), _AGEN(0), _VREG(23), __vcop_alws());
   __vcop_vmove(_VREG(16), _VREG(24));
   __vcop_vmove(_VREG(17), _VREG(28));
   __vcop_vdintrlv(_VREG(24), _VREG(28));
   __vcop_vmove(_VREG(18), _VREG(25));
   __vcop_vmove(_VREG(19), _VREG(29));
   __vcop_vdintrlv(_VREG(25), _VREG(29));
   __vcop_vmove(_VREG(20), _VREG(26));
   __vcop_vmove(_VREG(21), _VREG(30));
   __vcop_vdintrlv(_VREG(26), _VREG(30));
   __vcop_vmove(_VREG(22), _VREG(27));
   __vcop_vmove(_VREG(23), _VREG(31));
   __vcop_vdintrlv(_VREG(27), _VREG(31));
   __vcop_vmove(_VREG(24), _VREG(40));
   __vcop_vmove(_VREG(26), _VREG(44));
   __vcop_vaddsub(_VREG(40), _VREG(44));
   __vcop_vmove(_VREG(28), _VREG(41));
   __vcop_vmove(_VREG(30), _VREG(45));
   __vcop_vaddsub(_VREG(41), _VREG(45));
   __vcop_vmove(_VREG(25), _VREG(42));
   __vcop_vmove(_VREG(27), _VREG(46));
   __vcop_vaddsub(_VREG(42), _VREG(46));
   __vcop_vmove(_VREG(29), _VREG(43));
   __vcop_vmove(_VREG(31), _VREG(47));
   __vcop_vaddsub(_VREG(43), _VREG(47));
   __vcop_vmove(_VREG(40), _VREG(32));
   __vcop_vmove(_VREG(42), _VREG(34));
   __vcop_vaddsub(_VREG(32), _VREG(34));
   __vcop_vmove(_VREG(44), _VREG(33));
   __vcop_vmove(_VREG(47), _VREG(35));
   __vcop_vaddsub(_VREG(33), _VREG(35));
   __vcop_vmove(_VREG(41), _VREG(36));
   __vcop_vmove(_VREG(43), _VREG(38));
   __vcop_vaddsub(_VREG(36), _VREG(38));
   __vcop_vmove(_VREG(45), _VREG(39));
   __vcop_vmove(_VREG(46), _VREG(37));
   __vcop_vaddsub(_VREG(39), _VREG(37));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeW(), __vcop_npt(), __vcop_alws(), _VREG(32), _PREG(18), _AGEN(0), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeW(), __vcop_npt(), __vcop_alws(), _VREG(36), _PREG(20), _AGEN(0), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeW(), __vcop_npt(), __vcop_alws(), _VREG(33), _PREG(22), _AGEN(0), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeW(), __vcop_npt(), __vcop_alws(), _VREG(37), _PREG(24), _AGEN(0), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeW(), __vcop_npt(), __vcop_alws(), _VREG(34), _PREG(26), _AGEN(0), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeW(), __vcop_npt(), __vcop_alws(), _VREG(38), _PREG(28), _AGEN(0), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeW(), __vcop_npt(), __vcop_alws(), _VREG(35), _PREG(30), _AGEN(0), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeW(), __vcop_npt(), __vcop_alws(), _VREG(39), _PREG(32), _AGEN(0), _PREG(0));
   __vcop_vloop_end(1u);

}

void vcop_fft_1024_32x16t_stage1_0(
   __vptr_int32 Pin_xyL0_0123,
   __vptr_int32 Pin_xyL0_4567,
   __vptr_int32 Pin_xyL1_0123,
   __vptr_int32 Pin_xyL1_4567,
   __vptr_int32 Pin_xyL2_0123,
   __vptr_int32 Pin_xyL2_4567,
   __vptr_int32 Pin_xyL3_0123,
   __vptr_int32 Pin_xyL3_4567,
   __vptr_int32 Pou_xyL0_0123,
   __vptr_int32 Pou_xyL0_4567,
   __vptr_int32 Pou_xyL1_0123,
   __vptr_int32 Pou_xyL1_4567,
   __vptr_int32 Pou_xyL2_0123,
   __vptr_int32 Pou_xyL2_4567,
   __vptr_int32 Pou_xyL3_0123,
   __vptr_int32 Pou_xyL3_4567)
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_fft_1024_32x16t_stage1_0_init(Pin_xyL0_0123, Pin_xyL0_4567, Pin_xyL1_0123, Pin_xyL1_4567, Pin_xyL2_0123, Pin_xyL2_4567, Pin_xyL3_0123, Pin_xyL3_4567, Pou_xyL0_0123, Pou_xyL0_4567, Pou_xyL1_0123, Pou_xyL1_4567, Pou_xyL2_0123, Pou_xyL2_4567, Pou_xyL3_0123, Pou_xyL3_4567, __pblock_vcop_fft_1024_32x16t_stage1_0);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_fft_1024_32x16t_stage1_0_vloops(__pblock_vcop_fft_1024_32x16t_stage1_0);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

void vcop_fft_1024_32x16t_stage1_0_custom(
   __vptr_int32 Pin_xyL0_0123,
   __vptr_int32 Pin_xyL0_4567,
   __vptr_int32 Pin_xyL1_0123,
   __vptr_int32 Pin_xyL1_4567,
   __vptr_int32 Pin_xyL2_0123,
   __vptr_int32 Pin_xyL2_4567,
   __vptr_int32 Pin_xyL3_0123,
   __vptr_int32 Pin_xyL3_4567,
   __vptr_int32 Pou_xyL0_0123,
   __vptr_int32 Pou_xyL0_4567,
   __vptr_int32 Pou_xyL1_0123,
   __vptr_int32 Pou_xyL1_4567,
   __vptr_int32 Pou_xyL2_0123,
   __vptr_int32 Pou_xyL2_4567,
   __vptr_int32 Pou_xyL3_0123,
   __vptr_int32 Pou_xyL3_4567,
   unsigned short pblock[])
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_fft_1024_32x16t_stage1_0_init(Pin_xyL0_0123, Pin_xyL0_4567, Pin_xyL1_0123, Pin_xyL1_4567, Pin_xyL2_0123, Pin_xyL2_4567, Pin_xyL3_0123, Pin_xyL3_4567, Pou_xyL0_0123, Pou_xyL0_4567, Pou_xyL1_0123, Pou_xyL1_4567, Pou_xyL2_0123, Pou_xyL2_4567, Pou_xyL3_0123, Pou_xyL3_4567, pblock);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_fft_1024_32x16t_stage1_0_vloops(pblock);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

#pragma DATA_SECTION(__pblock_vcop_fft_1024_32x16t_stage1_1, ".vcop_parameter_block")
#pragma DATA_ALIGN(__pblock_vcop_fft_1024_32x16t_stage1_1, __ALIGNOF__(int));
unsigned short __pblock_vcop_fft_1024_32x16t_stage1_1[26];

unsigned int vcop_fft_1024_32x16t_stage1_1_param_count(void)
{
   return 26u;
}

unsigned int vcop_fft_1024_32x16t_stage1_1_ctrl_count(void)
{
   return 0u;
}

unsigned int vcop_fft_1024_32x16t_stage1_1_init(
   __vptr_uint16 inp1_l,
   __vptr_int16 inp1_h,
   __vptr_int16 CS,
   __vptr_int32 out,
   unsigned short pblock[])
{
   int __offset = 0;
   /* Loop 1 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), (32)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), (3)-1u);
   __vcop_pblock_init32(pblock, __offset+_PREG(6), (uchar *)inp1_l);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)inp1_h+2*(8u/2)*sizeof(*out));
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)inp1_l+2*(8u/2)*sizeof(*out));
   __vcop_pblock_init32(pblock, __offset+_PREG(12), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(14), __vcop_vop_round(1, 15));
   __vcop_pblock_init16(pblock, __offset+_PREG(15), __vcop_vop_round(3, 1));
   __vcop_pblock_init32(pblock, __offset+_PREG(16), (uchar *)out);
   __vcop_pblock_init32(pblock, __offset+_PREG(18), (uchar *)out+2*(8u/2)*sizeof(*out));
   __vcop_pblock_init16(pblock, __offset+_PREG(20), 2048);
   __vcop_pblock_init16(pblock, __offset+_PREG(21), -4032);
   __vcop_pblock_init16(pblock, __offset+_PREG(22), 32);
   __vcop_pblock_init32(pblock, __offset+_PREG(24), (uchar *)CS);
   __vcop_pblock_init32(pblock, __offset+_PREG(26), (uchar *)inp1_h);
   __offset += 26;

   return 26u;
}

void vcop_fft_1024_32x16t_stage1_1_vloops(
   unsigned short pblock[])
{
   /* Kernel-wide Vector Registers */

   __vcop_param(&pblock[0]);

   /* VLOOP 1 Start */

   /* VLOOP Local Vector Registers */
   #pragma VCC_VREG("VA", 16);
   #pragma VCC_VREG("VB", 17);
   #pragma VCC_VREG("VC", 18);
   #pragma VCC_VREG("VE", 19);
   #pragma VCC_VREG("VF", 20);
   #pragma VCC_VREG("VG", 21);
   #pragma VCC_VREG("Vacc2", 22);
   #pragma VCC_VREG("Vacc4", 23);
   #pragma VCC_VREG("Vacc6", 24);
   #pragma VCC_VREG("Vacc8", 25);
   #pragma VCC_VREG("Vout0", 26);
   #pragma VCC_VREG("Vout1", 27);
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("Addr_in", "A0");
   #pragma EVE_REG("Addr_iw", "A1");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I3", "I3");
   #pragma EVE_REG("I4", "I4");
   

   __vcop_vloop(__vcop_compute(), 20u, 13u, 1u);
   __vcop_vinit(__vcop_sizeW(), __vcop_alws(), _PREG(12), _VREG(26));
   __vcop_vinit(__vcop_sizeW(), __vcop_alws(), _PREG(12), _VREG(27));
   __vcop_vagen(_AGEN(0), _PREG(20), _PREG(21), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(1), _PREG(22), _PREG(22), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeH(), __vcop_dintrlv(), _PREG(24), _AGEN(1), _VPAIR(21,18), __vcop_alws());
   __vcop_vload(__vcop_sizeH(), __vcop_ds2(), _PREG(26), _AGEN(0), _VREG(16), __vcop_alws());
   __vcop_vload(__vcop_sizeHU(), __vcop_ds2(), _PREG(6), _AGEN(0), _VREG(17), __vcop_alws());
   __vcop_vload(__vcop_sizeH(), __vcop_ds2(), _PREG(8), _AGEN(0), _VREG(19), __vcop_alws());
   __vcop_vload(__vcop_sizeHU(), __vcop_ds2(), _PREG(10), _AGEN(0), _VREG(20), __vcop_alws());
   __vcop_vmadd(_VREG(17), _VREG(18), _VREG(26), _PREG(14));
   __vcop_vmadd(_VREG(20), _VREG(18), _VREG(27), _PREG(14));
   __vcop_vmadd(_VREG(20), _VREG(21), _VREG(26), _PREG(14));
   __vcop_vmsub(_VREG(17), _VREG(21), _VREG(27), _PREG(14));
   __vcop_vmadd(_VREG(16), _VREG(18), _VREG(26), _PREG(15));
   __vcop_vmsub(_VREG(16), _VREG(21), _VREG(27), _PREG(15));
   __vcop_vmadd(_VREG(19), _VREG(21), _VREG(26), _PREG(15));
   __vcop_vmadd(_VREG(19), _VREG(18), _VREG(27), _PREG(15));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeW(), __vcop_npt(), __vcop_alws(), _VREG(26), _PREG(16), _AGEN(0), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeW(), __vcop_npt(), __vcop_alws(), _VREG(27), _PREG(18), _AGEN(0), _PREG(0));
   __vcop_vloop_end(1u);

}

void vcop_fft_1024_32x16t_stage1_1(
   __vptr_uint16 inp1_l,
   __vptr_int16 inp1_h,
   __vptr_int16 CS,
   __vptr_int32 out)
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_fft_1024_32x16t_stage1_1_init(inp1_l, inp1_h, CS, out, __pblock_vcop_fft_1024_32x16t_stage1_1);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_fft_1024_32x16t_stage1_1_vloops(__pblock_vcop_fft_1024_32x16t_stage1_1);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

void vcop_fft_1024_32x16t_stage1_1_custom(
   __vptr_uint16 inp1_l,
   __vptr_int16 inp1_h,
   __vptr_int16 CS,
   __vptr_int32 out,
   unsigned short pblock[])
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_fft_1024_32x16t_stage1_1_init(inp1_l, inp1_h, CS, out, pblock);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_fft_1024_32x16t_stage1_1_vloops(pblock);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

#pragma DATA_SECTION(__pblock_vcop_fft_1024_32x16t_stage2_0, ".vcop_parameter_block")
#pragma DATA_ALIGN(__pblock_vcop_fft_1024_32x16t_stage2_0, __ALIGNOF__(int));
unsigned short __pblock_vcop_fft_1024_32x16t_stage2_0[38];

unsigned int vcop_fft_1024_32x16t_stage2_0_param_count(void)
{
   return 38u;
}

unsigned int vcop_fft_1024_32x16t_stage2_0_ctrl_count(void)
{
   return 0u;
}

unsigned int vcop_fft_1024_32x16t_stage2_0_init(
   __vptr_int32 Pin_xyL0_0123,
   __vptr_int32 Pin_xyL0_4567,
   __vptr_int32 Pin_xyL1_0123,
   __vptr_int32 Pin_xyL1_4567,
   __vptr_int32 Pin_xyL2_0123,
   __vptr_int32 Pin_xyL2_4567,
   __vptr_int32 Pin_xyL3_0123,
   __vptr_int32 Pin_xyL3_4567,
   __vptr_int32 Pou_xyL0_0123,
   __vptr_int32 Pou_xyL0_4567,
   __vptr_int32 Pou_xyL1_0123,
   __vptr_int32 Pou_xyL1_4567,
   __vptr_int32 Pou_xyL2_0123,
   __vptr_int32 Pou_xyL2_4567,
   __vptr_int32 Pou_xyL3_0123,
   __vptr_int32 Pou_xyL3_4567,
   unsigned short pblock[])
{
   int __offset = 0;
   /* Loop 1 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), (4)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), (8)-1u);
   __vcop_pblock_init32(pblock, __offset+_PREG(6), (uchar *)Pin_xyL1_0123);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)Pin_xyL1_4567);
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)Pin_xyL2_0123);
   __vcop_pblock_init32(pblock, __offset+_PREG(12), (uchar *)Pin_xyL2_4567);
   __vcop_pblock_init32(pblock, __offset+_PREG(14), (uchar *)Pin_xyL3_0123);
   __vcop_pblock_init32(pblock, __offset+_PREG(16), (uchar *)Pin_xyL3_4567);
   __vcop_pblock_init32(pblock, __offset+_PREG(18), (uchar *)Pou_xyL0_0123);
   __vcop_pblock_init32(pblock, __offset+_PREG(20), (uchar *)Pou_xyL0_4567);
   __vcop_pblock_init32(pblock, __offset+_PREG(22), (uchar *)Pou_xyL1_0123);
   __vcop_pblock_init32(pblock, __offset+_PREG(24), (uchar *)Pou_xyL1_4567);
   __vcop_pblock_init32(pblock, __offset+_PREG(26), (uchar *)Pou_xyL2_0123);
   __vcop_pblock_init32(pblock, __offset+_PREG(28), (uchar *)Pou_xyL2_4567);
   __vcop_pblock_init32(pblock, __offset+_PREG(30), (uchar *)Pou_xyL3_0123);
   __vcop_pblock_init32(pblock, __offset+_PREG(32), (uchar *)Pou_xyL3_4567);
   __vcop_pblock_init16(pblock, __offset+_PREG(34), 64);
   __vcop_pblock_init16(pblock, __offset+_PREG(35), 1600);
   __vcop_pblock_init32(pblock, __offset+_PREG(36), (uchar *)Pin_xyL0_0123);
   __vcop_pblock_init32(pblock, __offset+_PREG(38), (uchar *)Pin_xyL0_4567);
   __offset += 38;

   return 38u;
}

void vcop_fft_1024_32x16t_stage2_0_vloops(
   unsigned short pblock[])
{
   /* Kernel-wide Vector Registers */

   __vcop_param(&pblock[0]);

   /* VLOOP 1 Start */

   /* VLOOP Local Vector Registers */
   #pragma VCC_VREG("OXY_L0_0123", 16);
   #pragma VCC_VREG("OXY_L0_4567", 17);
   #pragma VCC_VREG("OXY_L1_0123", 18);
   #pragma VCC_VREG("OXY_L1_4567", 19);
   #pragma VCC_VREG("OXY_L2_0123", 20);
   #pragma VCC_VREG("OXY_L2_4567", 21);
   #pragma VCC_VREG("OXY_L3_0123", 22);
   #pragma VCC_VREG("OXY_L3_4567", 23);
   #pragma VCC_VREG("VXY_L0_0123", 24);
   #pragma VCC_VREG("VXY_L0_4567", 25);
   #pragma VCC_VREG("VXY_L1_0123", 26);
   #pragma VCC_VREG("VXY_L1_4567", 27);
   #pragma VCC_VREG("VXY_L2_0123", 28);
   #pragma VCC_VREG("VXY_L2_4567", 29);
   #pragma VCC_VREG("VXY_L3_0123", 30);
   #pragma VCC_VREG("VXY_L3_4567", 31);
   #pragma VCC_VREG("VX_L0_01234567", 32);
   #pragma VCC_VREG("VX_L1_01234567", 33);
   #pragma VCC_VREG("VX_L2_01234567", 34);
   #pragma VCC_VREG("VX_L3_01234567", 35);
   #pragma VCC_VREG("VY_L0_01234567", 36);
   #pragma VCC_VREG("VY_L1_01234567", 37);
   #pragma VCC_VREG("VY_L2_01234567", 38);
   #pragma VCC_VREG("VY_L3_01234567", 39);
   #pragma VCC_VREG("V_x0r", 40);
   #pragma VCC_VREG("V_xt1", 41);
   #pragma VCC_VREG("V_xt2", 42);
   #pragma VCC_VREG("V_xt3", 43);
   #pragma VCC_VREG("V_y0i", 44);
   #pragma VCC_VREG("V_yt1", 45);
   #pragma VCC_VREG("V_yt2", 46);
   #pragma VCC_VREG("V_yt3", 47);
   #pragma VCC_VREG("Vxh0", 48);
   #pragma VCC_VREG("Vxh1", 49);
   #pragma VCC_VREG("Vxh20", 50);
   #pragma VCC_VREG("Vxh21", 51);
   #pragma VCC_VREG("Vxl0", 52);
   #pragma VCC_VREG("Vxl1", 53);
   #pragma VCC_VREG("Vxl20", 54);
   #pragma VCC_VREG("Vxl21", 55);
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("Addr_in", "A0");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I3", "I3");
   #pragma EVE_REG("I4", "I4");
   

   __vcop_vloop(__vcop_compute(), 42u, 19u, 1u);
   __vcop_vagen(_AGEN(0), _PREG(34), _PREG(35), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeW(), __vcop_npt(), _PREG(36), _AGEN(0), _VREG(32), __vcop_alws());
   __vcop_vload(__vcop_sizeW(), __vcop_npt(), _PREG(38), _AGEN(0), _VREG(36), __vcop_alws());
   __vcop_vload(__vcop_sizeW(), __vcop_npt(), _PREG(6), _AGEN(0), _VREG(33), __vcop_alws());
   __vcop_vload(__vcop_sizeW(), __vcop_npt(), _PREG(8), _AGEN(0), _VREG(37), __vcop_alws());
   __vcop_vload(__vcop_sizeW(), __vcop_npt(), _PREG(10), _AGEN(0), _VREG(34), __vcop_alws());
   __vcop_vload(__vcop_sizeW(), __vcop_npt(), _PREG(12), _AGEN(0), _VREG(38), __vcop_alws());
   __vcop_vload(__vcop_sizeW(), __vcop_npt(), _PREG(14), _AGEN(0), _VREG(35), __vcop_alws());
   __vcop_vload(__vcop_sizeW(), __vcop_npt(), _PREG(16), _AGEN(0), _VREG(39), __vcop_alws());
   __vcop_vmove(_VREG(32), _VREG(48));
   __vcop_vmove(_VREG(34), _VREG(52));
   __vcop_vaddsub(_VREG(48), _VREG(52));
   __vcop_vmove(_VREG(36), _VREG(49));
   __vcop_vmove(_VREG(38), _VREG(53));
   __vcop_vaddsub(_VREG(49), _VREG(53));
   __vcop_vmove(_VREG(33), _VREG(50));
   __vcop_vmove(_VREG(35), _VREG(54));
   __vcop_vaddsub(_VREG(50), _VREG(54));
   __vcop_vmove(_VREG(37), _VREG(51));
   __vcop_vmove(_VREG(39), _VREG(55));
   __vcop_vaddsub(_VREG(51), _VREG(55));
   __vcop_vmove(_VREG(48), _VREG(40));
   __vcop_vmove(_VREG(50), _VREG(42));
   __vcop_vaddsub(_VREG(40), _VREG(42));
   __vcop_vmove(_VREG(52), _VREG(41));
   __vcop_vmove(_VREG(55), _VREG(43));
   __vcop_vaddsub(_VREG(41), _VREG(43));
   __vcop_vmove(_VREG(49), _VREG(44));
   __vcop_vmove(_VREG(51), _VREG(46));
   __vcop_vaddsub(_VREG(44), _VREG(46));
   __vcop_vmove(_VREG(53), _VREG(47));
   __vcop_vmove(_VREG(54), _VREG(45));
   __vcop_vaddsub(_VREG(47), _VREG(45));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeW(), __vcop_npt(), __vcop_alws(), _VREG(40), _PREG(18), _AGEN(0), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeW(), __vcop_npt(), __vcop_alws(), _VREG(44), _PREG(20), _AGEN(0), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeW(), __vcop_npt(), __vcop_alws(), _VREG(41), _PREG(22), _AGEN(0), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeW(), __vcop_npt(), __vcop_alws(), _VREG(45), _PREG(24), _AGEN(0), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeW(), __vcop_npt(), __vcop_alws(), _VREG(42), _PREG(26), _AGEN(0), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeW(), __vcop_npt(), __vcop_alws(), _VREG(46), _PREG(28), _AGEN(0), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeW(), __vcop_npt(), __vcop_alws(), _VREG(43), _PREG(30), _AGEN(0), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeW(), __vcop_npt(), __vcop_alws(), _VREG(47), _PREG(32), _AGEN(0), _PREG(0));
   __vcop_vloop_end(1u);

}

void vcop_fft_1024_32x16t_stage2_0(
   __vptr_int32 Pin_xyL0_0123,
   __vptr_int32 Pin_xyL0_4567,
   __vptr_int32 Pin_xyL1_0123,
   __vptr_int32 Pin_xyL1_4567,
   __vptr_int32 Pin_xyL2_0123,
   __vptr_int32 Pin_xyL2_4567,
   __vptr_int32 Pin_xyL3_0123,
   __vptr_int32 Pin_xyL3_4567,
   __vptr_int32 Pou_xyL0_0123,
   __vptr_int32 Pou_xyL0_4567,
   __vptr_int32 Pou_xyL1_0123,
   __vptr_int32 Pou_xyL1_4567,
   __vptr_int32 Pou_xyL2_0123,
   __vptr_int32 Pou_xyL2_4567,
   __vptr_int32 Pou_xyL3_0123,
   __vptr_int32 Pou_xyL3_4567)
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_fft_1024_32x16t_stage2_0_init(Pin_xyL0_0123, Pin_xyL0_4567, Pin_xyL1_0123, Pin_xyL1_4567, Pin_xyL2_0123, Pin_xyL2_4567, Pin_xyL3_0123, Pin_xyL3_4567, Pou_xyL0_0123, Pou_xyL0_4567, Pou_xyL1_0123, Pou_xyL1_4567, Pou_xyL2_0123, Pou_xyL2_4567, Pou_xyL3_0123, Pou_xyL3_4567, __pblock_vcop_fft_1024_32x16t_stage2_0);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_fft_1024_32x16t_stage2_0_vloops(__pblock_vcop_fft_1024_32x16t_stage2_0);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

void vcop_fft_1024_32x16t_stage2_0_custom(
   __vptr_int32 Pin_xyL0_0123,
   __vptr_int32 Pin_xyL0_4567,
   __vptr_int32 Pin_xyL1_0123,
   __vptr_int32 Pin_xyL1_4567,
   __vptr_int32 Pin_xyL2_0123,
   __vptr_int32 Pin_xyL2_4567,
   __vptr_int32 Pin_xyL3_0123,
   __vptr_int32 Pin_xyL3_4567,
   __vptr_int32 Pou_xyL0_0123,
   __vptr_int32 Pou_xyL0_4567,
   __vptr_int32 Pou_xyL1_0123,
   __vptr_int32 Pou_xyL1_4567,
   __vptr_int32 Pou_xyL2_0123,
   __vptr_int32 Pou_xyL2_4567,
   __vptr_int32 Pou_xyL3_0123,
   __vptr_int32 Pou_xyL3_4567,
   unsigned short pblock[])
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_fft_1024_32x16t_stage2_0_init(Pin_xyL0_0123, Pin_xyL0_4567, Pin_xyL1_0123, Pin_xyL1_4567, Pin_xyL2_0123, Pin_xyL2_4567, Pin_xyL3_0123, Pin_xyL3_4567, Pou_xyL0_0123, Pou_xyL0_4567, Pou_xyL1_0123, Pou_xyL1_4567, Pou_xyL2_0123, Pou_xyL2_4567, Pou_xyL3_0123, Pou_xyL3_4567, pblock);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_fft_1024_32x16t_stage2_0_vloops(pblock);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

#pragma DATA_SECTION(__pblock_vcop_fft_1024_32x16t_stage2_1, ".vcop_parameter_block")
#pragma DATA_ALIGN(__pblock_vcop_fft_1024_32x16t_stage2_1, __ALIGNOF__(int));
unsigned short __pblock_vcop_fft_1024_32x16t_stage2_1[28];

unsigned int vcop_fft_1024_32x16t_stage2_1_param_count(void)
{
   return 28u;
}

unsigned int vcop_fft_1024_32x16t_stage2_1_ctrl_count(void)
{
   return 0u;
}

unsigned int vcop_fft_1024_32x16t_stage2_1_init(
   __vptr_uint16 inp1_l,
   __vptr_int16 inp1_h,
   __vptr_int16 CS,
   __vptr_int32 out,
   unsigned short pblock[])
{
   int __offset = 0;
   /* Loop 1 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), (4)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), (8)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), (3)-1u);
   __vcop_pblock_init32(pblock, __offset+_PREG(6), (uchar *)inp1_l);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)inp1_h+2*(8u/2)*sizeof(*out));
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)inp1_l+2*(8u/2)*sizeof(*out));
   __vcop_pblock_init32(pblock, __offset+_PREG(12), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(14), __vcop_vop_round(1, 15));
   __vcop_pblock_init16(pblock, __offset+_PREG(15), __vcop_vop_round(3, 1));
   __vcop_pblock_init32(pblock, __offset+_PREG(16), (uchar *)out);
   __vcop_pblock_init32(pblock, __offset+_PREG(18), (uchar *)out+2*(8u/2)*sizeof(*out));
   __vcop_pblock_init16(pblock, __offset+_PREG(20), 512);
   __vcop_pblock_init16(pblock, __offset+_PREG(21), -960);
   __vcop_pblock_init16(pblock, __offset+_PREG(22), 576);
   __vcop_pblock_init16(pblock, __offset+_PREG(23), 32);
   __vcop_pblock_init16(pblock, __offset+_PREG(24), -736);
   __vcop_pblock_init32(pblock, __offset+_PREG(26), (uchar *)CS);
   __vcop_pblock_init32(pblock, __offset+_PREG(28), (uchar *)inp1_h);
   __offset += 28;

   return 28u;
}

void vcop_fft_1024_32x16t_stage2_1_vloops(
   unsigned short pblock[])
{
   /* Kernel-wide Vector Registers */

   __vcop_param(&pblock[0]);

   /* VLOOP 1 Start */

   /* VLOOP Local Vector Registers */
   #pragma VCC_VREG("VA", 16);
   #pragma VCC_VREG("VB", 17);
   #pragma VCC_VREG("VC", 18);
   #pragma VCC_VREG("VE", 19);
   #pragma VCC_VREG("VF", 20);
   #pragma VCC_VREG("VG", 21);
   #pragma VCC_VREG("Vacc2", 22);
   #pragma VCC_VREG("Vacc4", 23);
   #pragma VCC_VREG("Vacc6", 24);
   #pragma VCC_VREG("Vacc8", 25);
   #pragma VCC_VREG("Vout0", 26);
   #pragma VCC_VREG("Vout1", 27);
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("Addr_in", "A0");
   #pragma EVE_REG("Addr_iw", "A1");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I2", "I2");
   #pragma EVE_REG("I3", "I3");
   #pragma EVE_REG("I4", "I4");
   

   __vcop_vloop(__vcop_compute(), 20u, 14u, 1u);
   __vcop_vinit(__vcop_sizeW(), __vcop_alws(), _PREG(12), _VREG(26));
   __vcop_vinit(__vcop_sizeW(), __vcop_alws(), _PREG(12), _VREG(27));
   __vcop_vagen(_AGEN(0), _PREG(20), _PREG(21), _PREG(22), _PREG(0));
   __vcop_vagen(_AGEN(1), _PREG(23), _PREG(23), _PREG(24), _PREG(0));
   __vcop_vload(__vcop_sizeH(), __vcop_dintrlv(), _PREG(26), _AGEN(1), _VPAIR(21,18), __vcop_alws());
   __vcop_vload(__vcop_sizeH(), __vcop_ds2(), _PREG(28), _AGEN(0), _VREG(16), __vcop_alws());
   __vcop_vload(__vcop_sizeHU(), __vcop_ds2(), _PREG(6), _AGEN(0), _VREG(17), __vcop_alws());
   __vcop_vload(__vcop_sizeH(), __vcop_ds2(), _PREG(8), _AGEN(0), _VREG(19), __vcop_alws());
   __vcop_vload(__vcop_sizeHU(), __vcop_ds2(), _PREG(10), _AGEN(0), _VREG(20), __vcop_alws());
   __vcop_vmadd(_VREG(17), _VREG(18), _VREG(26), _PREG(14));
   __vcop_vmadd(_VREG(20), _VREG(18), _VREG(27), _PREG(14));
   __vcop_vmadd(_VREG(20), _VREG(21), _VREG(26), _PREG(14));
   __vcop_vmsub(_VREG(17), _VREG(21), _VREG(27), _PREG(14));
   __vcop_vmadd(_VREG(16), _VREG(18), _VREG(26), _PREG(15));
   __vcop_vmsub(_VREG(16), _VREG(21), _VREG(27), _PREG(15));
   __vcop_vmadd(_VREG(19), _VREG(21), _VREG(26), _PREG(15));
   __vcop_vmadd(_VREG(19), _VREG(18), _VREG(27), _PREG(15));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeW(), __vcop_npt(), __vcop_alws(), _VREG(26), _PREG(16), _AGEN(0), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeW(), __vcop_npt(), __vcop_alws(), _VREG(27), _PREG(18), _AGEN(0), _PREG(0));
   __vcop_vloop_end(1u);

}

void vcop_fft_1024_32x16t_stage2_1(
   __vptr_uint16 inp1_l,
   __vptr_int16 inp1_h,
   __vptr_int16 CS,
   __vptr_int32 out)
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_fft_1024_32x16t_stage2_1_init(inp1_l, inp1_h, CS, out, __pblock_vcop_fft_1024_32x16t_stage2_1);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_fft_1024_32x16t_stage2_1_vloops(__pblock_vcop_fft_1024_32x16t_stage2_1);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

void vcop_fft_1024_32x16t_stage2_1_custom(
   __vptr_uint16 inp1_l,
   __vptr_int16 inp1_h,
   __vptr_int16 CS,
   __vptr_int32 out,
   unsigned short pblock[])
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_fft_1024_32x16t_stage2_1_init(inp1_l, inp1_h, CS, out, pblock);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_fft_1024_32x16t_stage2_1_vloops(pblock);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

#pragma DATA_SECTION(__pblock_vcop_fft_1024_32x16t_stage3_0, ".vcop_parameter_block")
#pragma DATA_ALIGN(__pblock_vcop_fft_1024_32x16t_stage3_0, __ALIGNOF__(int));
unsigned short __pblock_vcop_fft_1024_32x16t_stage3_0[42];

unsigned int vcop_fft_1024_32x16t_stage3_0_param_count(void)
{
   return 42u;
}

unsigned int vcop_fft_1024_32x16t_stage3_0_ctrl_count(void)
{
   return 0u;
}

unsigned int vcop_fft_1024_32x16t_stage3_0_init(
   __vptr_int32 Pin_xyL0_0123,
   __vptr_int32 Pin_xyL0_4567,
   __vptr_int32 Pin_xyL1_0123,
   __vptr_int32 Pin_xyL1_4567,
   __vptr_int32 Pin_xyL2_0123,
   __vptr_int32 Pin_xyL2_4567,
   __vptr_int32 Pin_xyL3_0123,
   __vptr_int32 Pin_xyL3_4567,
   __vptr_int32 Pou_xyL0_0123,
   __vptr_int32 Pou_xyL0_4567,
   __vptr_int32 Pou_xyL1_0123,
   __vptr_int32 Pou_xyL1_4567,
   __vptr_int32 Pou_xyL2_0123,
   __vptr_int32 Pou_xyL2_4567,
   __vptr_int32 Pou_xyL3_0123,
   __vptr_int32 Pou_xyL3_4567,
   unsigned short pblock[])
{
   int __offset = 0;
   /* Loop 1 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), (4)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), (2)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), (2)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), (2)-1u);
   __vcop_pblock_init32(pblock, __offset+_PREG(6), (uchar *)Pin_xyL1_0123);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)Pin_xyL1_4567);
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)Pin_xyL2_0123);
   __vcop_pblock_init32(pblock, __offset+_PREG(12), (uchar *)Pin_xyL2_4567);
   __vcop_pblock_init32(pblock, __offset+_PREG(14), (uchar *)Pin_xyL3_0123);
   __vcop_pblock_init32(pblock, __offset+_PREG(16), (uchar *)Pin_xyL3_4567);
   __vcop_pblock_init32(pblock, __offset+_PREG(18), (uchar *)Pou_xyL0_0123);
   __vcop_pblock_init32(pblock, __offset+_PREG(20), (uchar *)Pou_xyL0_4567);
   __vcop_pblock_init32(pblock, __offset+_PREG(22), (uchar *)Pou_xyL1_0123);
   __vcop_pblock_init32(pblock, __offset+_PREG(24), (uchar *)Pou_xyL1_4567);
   __vcop_pblock_init32(pblock, __offset+_PREG(26), (uchar *)Pou_xyL2_0123);
   __vcop_pblock_init32(pblock, __offset+_PREG(28), (uchar *)Pou_xyL2_4567);
   __vcop_pblock_init32(pblock, __offset+_PREG(30), (uchar *)Pou_xyL3_0123);
   __vcop_pblock_init32(pblock, __offset+_PREG(32), (uchar *)Pou_xyL3_4567);
   __vcop_pblock_init16(pblock, __offset+_PREG(34), 64);
   __vcop_pblock_init16(pblock, __offset+_PREG(35), 448);
   __vcop_pblock_init16(pblock, __offset+_PREG(36), 288);
   __vcop_pblock_init16(pblock, __offset+_PREG(37), -272);
   __vcop_pblock_init16(pblock, __offset+_PREG(38), 2000);
   __vcop_pblock_init16(pblock, __offset+_PREG(39), -2604);
   __vcop_pblock_init32(pblock, __offset+_PREG(40), (uchar *)Pin_xyL0_0123);
   __vcop_pblock_init32(pblock, __offset+_PREG(42), (uchar *)Pin_xyL0_4567);
   __offset += 42;

   return 42u;
}

void vcop_fft_1024_32x16t_stage3_0_vloops(
   unsigned short pblock[])
{
   /* Kernel-wide Vector Registers */

   __vcop_param(&pblock[0]);

   /* VLOOP 1 Start */

   /* VLOOP Local Vector Registers */
   #pragma VCC_VREG("VXY_L0_0123", 16);
   #pragma VCC_VREG("VXY_L0_4567", 17);
   #pragma VCC_VREG("VXY_L1_0123", 18);
   #pragma VCC_VREG("VXY_L1_4567", 19);
   #pragma VCC_VREG("VXY_L2_0123", 20);
   #pragma VCC_VREG("VXY_L2_4567", 21);
   #pragma VCC_VREG("VXY_L3_0123", 22);
   #pragma VCC_VREG("VXY_L3_4567", 23);
   #pragma VCC_VREG("VX_L0_01234567", 24);
   #pragma VCC_VREG("VX_L1_01234567", 25);
   #pragma VCC_VREG("VX_L2_01234567", 26);
   #pragma VCC_VREG("VX_L3_01234567", 27);
   #pragma VCC_VREG("VY_L0_01234567", 28);
   #pragma VCC_VREG("VY_L1_01234567", 29);
   #pragma VCC_VREG("VY_L2_01234567", 30);
   #pragma VCC_VREG("VY_L3_01234567", 31);
   #pragma VCC_VREG("V_x0r", 32);
   #pragma VCC_VREG("V_xt1", 33);
   #pragma VCC_VREG("V_xt2", 34);
   #pragma VCC_VREG("V_xt3", 35);
   #pragma VCC_VREG("V_y0i", 36);
   #pragma VCC_VREG("V_yt1", 37);
   #pragma VCC_VREG("V_yt2", 38);
   #pragma VCC_VREG("V_yt3", 39);
   #pragma VCC_VREG("Vxh0", 40);
   #pragma VCC_VREG("Vxh1", 41);
   #pragma VCC_VREG("Vxh20", 42);
   #pragma VCC_VREG("Vxh21", 43);
   #pragma VCC_VREG("Vxl0", 44);
   #pragma VCC_VREG("Vxl1", 45);
   #pragma VCC_VREG("Vxl20", 46);
   #pragma VCC_VREG("Vxl21", 47);
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("Addr_in", "A0");
   #pragma EVE_REG("Addr_ou", "A1");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I1", "I1");
   #pragma EVE_REG("I2", "I2");
   #pragma EVE_REG("I3", "I3");
   #pragma EVE_REG("I4", "I4");
   

   __vcop_vloop(__vcop_compute(), 43u, 21u, 1u);
   __vcop_vagen(_AGEN(0), _PREG(34), _PREG(35), _PREG(35), _PREG(35));
   __vcop_vagen(_AGEN(1), _PREG(36), _PREG(37), _PREG(38), _PREG(39));
   __vcop_vload(__vcop_sizeW(), __vcop_npt(), _PREG(40), _AGEN(0), _VREG(24), __vcop_alws());
   __vcop_vload(__vcop_sizeW(), __vcop_npt(), _PREG(42), _AGEN(0), _VREG(28), __vcop_alws());
   __vcop_vload(__vcop_sizeW(), __vcop_npt(), _PREG(6), _AGEN(0), _VREG(25), __vcop_alws());
   __vcop_vload(__vcop_sizeW(), __vcop_npt(), _PREG(8), _AGEN(0), _VREG(29), __vcop_alws());
   __vcop_vload(__vcop_sizeW(), __vcop_npt(), _PREG(10), _AGEN(0), _VREG(26), __vcop_alws());
   __vcop_vload(__vcop_sizeW(), __vcop_npt(), _PREG(12), _AGEN(0), _VREG(30), __vcop_alws());
   __vcop_vload(__vcop_sizeW(), __vcop_npt(), _PREG(14), _AGEN(0), _VREG(27), __vcop_alws());
   __vcop_vload(__vcop_sizeW(), __vcop_npt(), _PREG(16), _AGEN(0), _VREG(31), __vcop_alws());
   __vcop_vmove(_VREG(24), _VREG(40));
   __vcop_vmove(_VREG(26), _VREG(44));
   __vcop_vaddsub(_VREG(40), _VREG(44));
   __vcop_vmove(_VREG(28), _VREG(41));
   __vcop_vmove(_VREG(30), _VREG(45));
   __vcop_vaddsub(_VREG(41), _VREG(45));
   __vcop_vmove(_VREG(25), _VREG(42));
   __vcop_vmove(_VREG(27), _VREG(46));
   __vcop_vaddsub(_VREG(42), _VREG(46));
   __vcop_vmove(_VREG(29), _VREG(43));
   __vcop_vmove(_VREG(31), _VREG(47));
   __vcop_vaddsub(_VREG(43), _VREG(47));
   __vcop_vmove(_VREG(40), _VREG(32));
   __vcop_vmove(_VREG(42), _VREG(34));
   __vcop_vaddsub(_VREG(32), _VREG(34));
   __vcop_vmove(_VREG(44), _VREG(33));
   __vcop_vmove(_VREG(47), _VREG(35));
   __vcop_vaddsub(_VREG(33), _VREG(35));
   __vcop_vmove(_VREG(41), _VREG(36));
   __vcop_vmove(_VREG(43), _VREG(38));
   __vcop_vaddsub(_VREG(36), _VREG(38));
   __vcop_vmove(_VREG(45), _VREG(39));
   __vcop_vmove(_VREG(46), _VREG(37));
   __vcop_vaddsub(_VREG(39), _VREG(37));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeW(), __vcop_offst_np1(), __vcop_alws(), _VREG(32), _PREG(18), _AGEN(1), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeW(), __vcop_offst_np1(), __vcop_alws(), _VREG(36), _PREG(20), _AGEN(1), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeW(), __vcop_offst_np1(), __vcop_alws(), _VREG(33), _PREG(22), _AGEN(1), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeW(), __vcop_offst_np1(), __vcop_alws(), _VREG(37), _PREG(24), _AGEN(1), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeW(), __vcop_offst_np1(), __vcop_alws(), _VREG(34), _PREG(26), _AGEN(1), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeW(), __vcop_offst_np1(), __vcop_alws(), _VREG(38), _PREG(28), _AGEN(1), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeW(), __vcop_offst_np1(), __vcop_alws(), _VREG(35), _PREG(30), _AGEN(1), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeW(), __vcop_offst_np1(), __vcop_alws(), _VREG(39), _PREG(32), _AGEN(1), _PREG(0));
   __vcop_vloop_end(1u);

}

void vcop_fft_1024_32x16t_stage3_0(
   __vptr_int32 Pin_xyL0_0123,
   __vptr_int32 Pin_xyL0_4567,
   __vptr_int32 Pin_xyL1_0123,
   __vptr_int32 Pin_xyL1_4567,
   __vptr_int32 Pin_xyL2_0123,
   __vptr_int32 Pin_xyL2_4567,
   __vptr_int32 Pin_xyL3_0123,
   __vptr_int32 Pin_xyL3_4567,
   __vptr_int32 Pou_xyL0_0123,
   __vptr_int32 Pou_xyL0_4567,
   __vptr_int32 Pou_xyL1_0123,
   __vptr_int32 Pou_xyL1_4567,
   __vptr_int32 Pou_xyL2_0123,
   __vptr_int32 Pou_xyL2_4567,
   __vptr_int32 Pou_xyL3_0123,
   __vptr_int32 Pou_xyL3_4567)
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_fft_1024_32x16t_stage3_0_init(Pin_xyL0_0123, Pin_xyL0_4567, Pin_xyL1_0123, Pin_xyL1_4567, Pin_xyL2_0123, Pin_xyL2_4567, Pin_xyL3_0123, Pin_xyL3_4567, Pou_xyL0_0123, Pou_xyL0_4567, Pou_xyL1_0123, Pou_xyL1_4567, Pou_xyL2_0123, Pou_xyL2_4567, Pou_xyL3_0123, Pou_xyL3_4567, __pblock_vcop_fft_1024_32x16t_stage3_0);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_fft_1024_32x16t_stage3_0_vloops(__pblock_vcop_fft_1024_32x16t_stage3_0);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

void vcop_fft_1024_32x16t_stage3_0_custom(
   __vptr_int32 Pin_xyL0_0123,
   __vptr_int32 Pin_xyL0_4567,
   __vptr_int32 Pin_xyL1_0123,
   __vptr_int32 Pin_xyL1_4567,
   __vptr_int32 Pin_xyL2_0123,
   __vptr_int32 Pin_xyL2_4567,
   __vptr_int32 Pin_xyL3_0123,
   __vptr_int32 Pin_xyL3_4567,
   __vptr_int32 Pou_xyL0_0123,
   __vptr_int32 Pou_xyL0_4567,
   __vptr_int32 Pou_xyL1_0123,
   __vptr_int32 Pou_xyL1_4567,
   __vptr_int32 Pou_xyL2_0123,
   __vptr_int32 Pou_xyL2_4567,
   __vptr_int32 Pou_xyL3_0123,
   __vptr_int32 Pou_xyL3_4567,
   unsigned short pblock[])
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_fft_1024_32x16t_stage3_0_init(Pin_xyL0_0123, Pin_xyL0_4567, Pin_xyL1_0123, Pin_xyL1_4567, Pin_xyL2_0123, Pin_xyL2_4567, Pin_xyL3_0123, Pin_xyL3_4567, Pou_xyL0_0123, Pou_xyL0_4567, Pou_xyL1_0123, Pou_xyL1_4567, Pou_xyL2_0123, Pou_xyL2_4567, Pou_xyL3_0123, Pou_xyL3_4567, pblock);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_fft_1024_32x16t_stage3_0_vloops(pblock);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

#pragma DATA_SECTION(__pblock_vcop_fft_1024_32x16t_stage3_1, ".vcop_parameter_block")
#pragma DATA_ALIGN(__pblock_vcop_fft_1024_32x16t_stage3_1, __ALIGNOF__(int));
unsigned short __pblock_vcop_fft_1024_32x16t_stage3_1[30];

unsigned int vcop_fft_1024_32x16t_stage3_1_param_count(void)
{
   return 30u;
}

unsigned int vcop_fft_1024_32x16t_stage3_1_ctrl_count(void)
{
   return 0u;
}

unsigned int vcop_fft_1024_32x16t_stage3_1_init(
   __vptr_uint16 inp1_lx,
   __vptr_int16 inp1_hx,
   __vptr_uint16 inp1_ly,
   __vptr_int16 inp1_hy,
   __vptr_int16 C,
   __vptr_int16 S,
   __vptr_int32 out_x,
   __vptr_int32 out_y,
   unsigned short pblock[])
{
   int __offset = 0;
   /* Loop 1 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), (2)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), (2)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), (3)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), (8)-1u);
   __vcop_pblock_init32(pblock, __offset+_PREG(6), (uchar *)inp1_hx);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)inp1_lx);
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)inp1_hy);
   __vcop_pblock_init32(pblock, __offset+_PREG(12), (uchar *)inp1_ly);
   __vcop_pblock_init32(pblock, __offset+_PREG(14), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(16), __vcop_vop_round(1, 15));
   __vcop_pblock_init16(pblock, __offset+_PREG(17), __vcop_vop_round(3, 1));
   __vcop_pblock_init32(pblock, __offset+_PREG(18), (uchar *)out_x);
   __vcop_pblock_init32(pblock, __offset+_PREG(20), (uchar *)out_y);
   __vcop_pblock_init16(pblock, __offset+_PREG(22), 36);
   __vcop_pblock_init16(pblock, __offset+_PREG(23), 324);
   __vcop_pblock_init16(pblock, __offset+_PREG(24), -1116);
   __vcop_pblock_init16(pblock, __offset+_PREG(25), 612);
   __vcop_pblock_init16(pblock, __offset+_PREG(26), 4);
   __vcop_pblock_init16(pblock, __offset+_PREG(27), -188);
   __vcop_pblock_init32(pblock, __offset+_PREG(28), (uchar *)C);
   __vcop_pblock_init32(pblock, __offset+_PREG(30), (uchar *)S);
   __offset += 30;

   return 30u;
}

void vcop_fft_1024_32x16t_stage3_1_vloops(
   unsigned short pblock[])
{
   /* Kernel-wide Vector Registers */
   #pragma VCC_VREG("VA", 16);
   #pragma VCC_VREG("VB", 17);
   #pragma VCC_VREG("VC", 18);
   #pragma VCC_VREG("VE", 19);
   #pragma VCC_VREG("VF", 20);
   #pragma VCC_VREG("VG", 21);
   #pragma VCC_VREG("Vacc2", 22);
   #pragma VCC_VREG("Vacc4", 23);
   #pragma VCC_VREG("Vacc6", 24);
   #pragma VCC_VREG("Vacc8", 25);
   #pragma VCC_VREG("Vout0", 26);
   #pragma VCC_VREG("Vout1", 27);

   __vcop_param(&pblock[0]);

   /* VLOOP 1 Start */

   /* VLOOP Local Vector Registers */
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("Addr_in", "A0");
   #pragma EVE_REG("Addr_ou", "A1");
   #pragma EVE_REG("Addr_tw", "A2");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I1", "I1");
   #pragma EVE_REG("I2", "I2");
   #pragma EVE_REG("I3", "I3");
   #pragma EVE_REG("I4", "I4");
   

   __vcop_vloop(__vcop_compute(), 22u, 15u, 1u);
   __vcop_vinit(__vcop_sizeW(), __vcop_alws(), _PREG(14), _VREG(26));
   __vcop_vinit(__vcop_sizeW(), __vcop_alws(), _PREG(14), _VREG(27));
   __vcop_vagen(_AGEN(0), _PREG(22), _PREG(23), _PREG(24), _PREG(25));
   __vcop_vagen(_AGEN(2), _PREG(26), _PREG(26), _PREG(26), _PREG(27));
   __vcop_vload(__vcop_sizeH(), __vcop_1pt(), _PREG(28), _AGEN(2), _VREG(18), __vcop_alws());
   __vcop_vload(__vcop_sizeH(), __vcop_1pt(), _PREG(30), _AGEN(2), _VREG(21), __vcop_alws());
   __vcop_vload(__vcop_sizeH(), __vcop_ds2(), _PREG(6), _AGEN(0), _VREG(16), __vcop_alws());
   __vcop_vload(__vcop_sizeHU(), __vcop_ds2(), _PREG(8), _AGEN(0), _VREG(17), __vcop_alws());
   __vcop_vload(__vcop_sizeH(), __vcop_ds2(), _PREG(10), _AGEN(0), _VREG(19), __vcop_alws());
   __vcop_vload(__vcop_sizeHU(), __vcop_ds2(), _PREG(12), _AGEN(0), _VREG(20), __vcop_alws());
   __vcop_vmadd(_VREG(17), _VREG(18), _VREG(26), _PREG(16));
   __vcop_vmadd(_VREG(20), _VREG(18), _VREG(27), _PREG(16));
   __vcop_vmadd(_VREG(20), _VREG(21), _VREG(26), _PREG(16));
   __vcop_vmsub(_VREG(17), _VREG(21), _VREG(27), _PREG(16));
   __vcop_vmadd(_VREG(16), _VREG(18), _VREG(26), _PREG(17));
   __vcop_vmsub(_VREG(16), _VREG(21), _VREG(27), _PREG(17));
   __vcop_vmadd(_VREG(19), _VREG(21), _VREG(26), _PREG(17));
   __vcop_vmadd(_VREG(19), _VREG(18), _VREG(27), _PREG(17));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeW(), __vcop_npt(), __vcop_alws(), _VREG(26), _PREG(18), _AGEN(0), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeW(), __vcop_npt(), __vcop_alws(), _VREG(27), _PREG(20), _AGEN(0), _PREG(0));
   __vcop_vloop_end(1u);

}

void vcop_fft_1024_32x16t_stage3_1(
   __vptr_uint16 inp1_lx,
   __vptr_int16 inp1_hx,
   __vptr_uint16 inp1_ly,
   __vptr_int16 inp1_hy,
   __vptr_int16 C,
   __vptr_int16 S,
   __vptr_int32 out_x,
   __vptr_int32 out_y)
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_fft_1024_32x16t_stage3_1_init(inp1_lx, inp1_hx, inp1_ly, inp1_hy, C, S, out_x, out_y, __pblock_vcop_fft_1024_32x16t_stage3_1);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_fft_1024_32x16t_stage3_1_vloops(__pblock_vcop_fft_1024_32x16t_stage3_1);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

void vcop_fft_1024_32x16t_stage3_1_custom(
   __vptr_uint16 inp1_lx,
   __vptr_int16 inp1_hx,
   __vptr_uint16 inp1_ly,
   __vptr_int16 inp1_hy,
   __vptr_int16 C,
   __vptr_int16 S,
   __vptr_int32 out_x,
   __vptr_int32 out_y,
   unsigned short pblock[])
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_fft_1024_32x16t_stage3_1_init(inp1_lx, inp1_hx, inp1_ly, inp1_hy, C, S, out_x, out_y, pblock);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_fft_1024_32x16t_stage3_1_vloops(pblock);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

#pragma DATA_SECTION(__pblock_vcop_fft_1024_32x16t_stage4_0, ".vcop_parameter_block")
#pragma DATA_ALIGN(__pblock_vcop_fft_1024_32x16t_stage4_0, __ALIGNOF__(int));
unsigned short __pblock_vcop_fft_1024_32x16t_stage4_0[38];

unsigned int vcop_fft_1024_32x16t_stage4_0_param_count(void)
{
   return 38u;
}

unsigned int vcop_fft_1024_32x16t_stage4_0_ctrl_count(void)
{
   return 0u;
}

unsigned int vcop_fft_1024_32x16t_stage4_0_init(
   __vptr_int32 Pin_xL0_01234567,
   __vptr_int32 Pin_yL0_01234567,
   __vptr_int32 Pin_xL1_01234567,
   __vptr_int32 Pin_yL1_01234567,
   __vptr_int32 Pin_xL2_01234567,
   __vptr_int32 Pin_yL2_01234567,
   __vptr_int32 Pin_xL3_01234567,
   __vptr_int32 Pin_yL3_01234567,
   __vptr_int32 Pou_xL0_01234567,
   __vptr_int32 Pou_yL0_01234567,
   __vptr_int32 Pou_xL1_01234567,
   __vptr_int32 Pou_yL1_01234567,
   __vptr_int32 Pou_xL2_01234567,
   __vptr_int32 Pou_yL2_01234567,
   __vptr_int32 Pou_xL3_01234567,
   __vptr_int32 Pou_yL3_01234567,
   unsigned short pblock[])
{
   int __offset = 0;
   /* Loop 1 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), (8)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), (4)-1u);
   __vcop_pblock_init32(pblock, __offset+_PREG(6), (uchar *)Pin_xL2_01234567);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)Pin_xL3_01234567);
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)Pin_yL0_01234567);
   __vcop_pblock_init32(pblock, __offset+_PREG(12), (uchar *)Pin_yL1_01234567);
   __vcop_pblock_init32(pblock, __offset+_PREG(14), (uchar *)Pin_yL2_01234567);
   __vcop_pblock_init32(pblock, __offset+_PREG(16), (uchar *)Pin_yL3_01234567);
   __vcop_pblock_init32(pblock, __offset+_PREG(18), (uchar *)Pou_xL0_01234567);
   __vcop_pblock_init32(pblock, __offset+_PREG(20), (uchar *)Pou_yL0_01234567);
   __vcop_pblock_init32(pblock, __offset+_PREG(22), (uchar *)Pou_xL1_01234567);
   __vcop_pblock_init32(pblock, __offset+_PREG(24), (uchar *)Pou_yL1_01234567);
   __vcop_pblock_init32(pblock, __offset+_PREG(26), (uchar *)Pou_xL2_01234567);
   __vcop_pblock_init32(pblock, __offset+_PREG(28), (uchar *)Pou_yL2_01234567);
   __vcop_pblock_init32(pblock, __offset+_PREG(30), (uchar *)Pou_xL3_01234567);
   __vcop_pblock_init32(pblock, __offset+_PREG(32), (uchar *)Pou_yL3_01234567);
   __vcop_pblock_init16(pblock, __offset+_PREG(34), 36);
   __vcop_pblock_init16(pblock, __offset+_PREG(35), 468);
   __vcop_pblock_init32(pblock, __offset+_PREG(36), (uchar *)Pin_xL0_01234567);
   __vcop_pblock_init32(pblock, __offset+_PREG(38), (uchar *)Pin_xL1_01234567);
   __offset += 38;

   return 38u;
}

void vcop_fft_1024_32x16t_stage4_0_vloops(
   unsigned short pblock[])
{
   /* Kernel-wide Vector Registers */

   __vcop_param(&pblock[0]);

   /* VLOOP 1 Start */

   /* VLOOP Local Vector Registers */
   #pragma VCC_VREG("VX_L0_01234567", 16);
   #pragma VCC_VREG("VX_L1_01234567", 17);
   #pragma VCC_VREG("VX_L2_01234567", 18);
   #pragma VCC_VREG("VX_L3_01234567", 19);
   #pragma VCC_VREG("VY_L0_01234567", 20);
   #pragma VCC_VREG("VY_L1_01234567", 21);
   #pragma VCC_VREG("VY_L2_01234567", 22);
   #pragma VCC_VREG("VY_L3_01234567", 23);
   #pragma VCC_VREG("V_x0r", 24);
   #pragma VCC_VREG("V_xt1", 25);
   #pragma VCC_VREG("V_xt2", 26);
   #pragma VCC_VREG("V_xt3", 27);
   #pragma VCC_VREG("V_y0i", 28);
   #pragma VCC_VREG("V_yt1", 29);
   #pragma VCC_VREG("V_yt2", 30);
   #pragma VCC_VREG("V_yt3", 31);
   #pragma VCC_VREG("Vxh0", 32);
   #pragma VCC_VREG("Vxh1", 33);
   #pragma VCC_VREG("Vxh20", 34);
   #pragma VCC_VREG("Vxh21", 35);
   #pragma VCC_VREG("Vxl0", 36);
   #pragma VCC_VREG("Vxl1", 37);
   #pragma VCC_VREG("Vxl20", 38);
   #pragma VCC_VREG("Vxl21", 39);
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("Addr_in", "A0");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I3", "I3");
   #pragma EVE_REG("I4", "I4");
   

   __vcop_vloop(__vcop_compute(), 42u, 19u, 1u);
   __vcop_vagen(_AGEN(0), _PREG(34), _PREG(35), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeW(), __vcop_npt(), _PREG(36), _AGEN(0), _VREG(16), __vcop_alws());
   __vcop_vload(__vcop_sizeW(), __vcop_npt(), _PREG(38), _AGEN(0), _VREG(17), __vcop_alws());
   __vcop_vload(__vcop_sizeW(), __vcop_npt(), _PREG(6), _AGEN(0), _VREG(18), __vcop_alws());
   __vcop_vload(__vcop_sizeW(), __vcop_npt(), _PREG(8), _AGEN(0), _VREG(19), __vcop_alws());
   __vcop_vload(__vcop_sizeW(), __vcop_npt(), _PREG(10), _AGEN(0), _VREG(20), __vcop_alws());
   __vcop_vload(__vcop_sizeW(), __vcop_npt(), _PREG(12), _AGEN(0), _VREG(21), __vcop_alws());
   __vcop_vload(__vcop_sizeW(), __vcop_npt(), _PREG(14), _AGEN(0), _VREG(22), __vcop_alws());
   __vcop_vload(__vcop_sizeW(), __vcop_npt(), _PREG(16), _AGEN(0), _VREG(23), __vcop_alws());
   __vcop_vmove(_VREG(16), _VREG(32));
   __vcop_vmove(_VREG(18), _VREG(36));
   __vcop_vaddsub(_VREG(32), _VREG(36));
   __vcop_vmove(_VREG(20), _VREG(33));
   __vcop_vmove(_VREG(22), _VREG(37));
   __vcop_vaddsub(_VREG(33), _VREG(37));
   __vcop_vmove(_VREG(17), _VREG(34));
   __vcop_vmove(_VREG(19), _VREG(38));
   __vcop_vaddsub(_VREG(34), _VREG(38));
   __vcop_vmove(_VREG(21), _VREG(35));
   __vcop_vmove(_VREG(23), _VREG(39));
   __vcop_vaddsub(_VREG(35), _VREG(39));
   __vcop_vmove(_VREG(32), _VREG(24));
   __vcop_vmove(_VREG(34), _VREG(26));
   __vcop_vaddsub(_VREG(24), _VREG(26));
   __vcop_vmove(_VREG(36), _VREG(25));
   __vcop_vmove(_VREG(39), _VREG(27));
   __vcop_vaddsub(_VREG(25), _VREG(27));
   __vcop_vmove(_VREG(33), _VREG(28));
   __vcop_vmove(_VREG(35), _VREG(30));
   __vcop_vaddsub(_VREG(28), _VREG(30));
   __vcop_vmove(_VREG(37), _VREG(31));
   __vcop_vmove(_VREG(38), _VREG(29));
   __vcop_vaddsub(_VREG(31), _VREG(29));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeW(), __vcop_npt(), __vcop_alws(), _VREG(24), _PREG(18), _AGEN(0), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeW(), __vcop_npt(), __vcop_alws(), _VREG(28), _PREG(20), _AGEN(0), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeW(), __vcop_npt(), __vcop_alws(), _VREG(25), _PREG(22), _AGEN(0), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeW(), __vcop_npt(), __vcop_alws(), _VREG(29), _PREG(24), _AGEN(0), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeW(), __vcop_npt(), __vcop_alws(), _VREG(26), _PREG(26), _AGEN(0), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeW(), __vcop_npt(), __vcop_alws(), _VREG(30), _PREG(28), _AGEN(0), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeW(), __vcop_npt(), __vcop_alws(), _VREG(27), _PREG(30), _AGEN(0), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeW(), __vcop_npt(), __vcop_alws(), _VREG(31), _PREG(32), _AGEN(0), _PREG(0));
   __vcop_vloop_end(1u);

}

void vcop_fft_1024_32x16t_stage4_0(
   __vptr_int32 Pin_xL0_01234567,
   __vptr_int32 Pin_yL0_01234567,
   __vptr_int32 Pin_xL1_01234567,
   __vptr_int32 Pin_yL1_01234567,
   __vptr_int32 Pin_xL2_01234567,
   __vptr_int32 Pin_yL2_01234567,
   __vptr_int32 Pin_xL3_01234567,
   __vptr_int32 Pin_yL3_01234567,
   __vptr_int32 Pou_xL0_01234567,
   __vptr_int32 Pou_yL0_01234567,
   __vptr_int32 Pou_xL1_01234567,
   __vptr_int32 Pou_yL1_01234567,
   __vptr_int32 Pou_xL2_01234567,
   __vptr_int32 Pou_yL2_01234567,
   __vptr_int32 Pou_xL3_01234567,
   __vptr_int32 Pou_yL3_01234567)
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_fft_1024_32x16t_stage4_0_init(Pin_xL0_01234567, Pin_yL0_01234567, Pin_xL1_01234567, Pin_yL1_01234567, Pin_xL2_01234567, Pin_yL2_01234567, Pin_xL3_01234567, Pin_yL3_01234567, Pou_xL0_01234567, Pou_yL0_01234567, Pou_xL1_01234567, Pou_yL1_01234567, Pou_xL2_01234567, Pou_yL2_01234567, Pou_xL3_01234567, Pou_yL3_01234567, __pblock_vcop_fft_1024_32x16t_stage4_0);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_fft_1024_32x16t_stage4_0_vloops(__pblock_vcop_fft_1024_32x16t_stage4_0);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

void vcop_fft_1024_32x16t_stage4_0_custom(
   __vptr_int32 Pin_xL0_01234567,
   __vptr_int32 Pin_yL0_01234567,
   __vptr_int32 Pin_xL1_01234567,
   __vptr_int32 Pin_yL1_01234567,
   __vptr_int32 Pin_xL2_01234567,
   __vptr_int32 Pin_yL2_01234567,
   __vptr_int32 Pin_xL3_01234567,
   __vptr_int32 Pin_yL3_01234567,
   __vptr_int32 Pou_xL0_01234567,
   __vptr_int32 Pou_yL0_01234567,
   __vptr_int32 Pou_xL1_01234567,
   __vptr_int32 Pou_yL1_01234567,
   __vptr_int32 Pou_xL2_01234567,
   __vptr_int32 Pou_yL2_01234567,
   __vptr_int32 Pou_xL3_01234567,
   __vptr_int32 Pou_yL3_01234567,
   unsigned short pblock[])
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_fft_1024_32x16t_stage4_0_init(Pin_xL0_01234567, Pin_yL0_01234567, Pin_xL1_01234567, Pin_yL1_01234567, Pin_xL2_01234567, Pin_yL2_01234567, Pin_xL3_01234567, Pin_yL3_01234567, Pou_xL0_01234567, Pou_yL0_01234567, Pou_xL1_01234567, Pou_yL1_01234567, Pou_xL2_01234567, Pou_yL2_01234567, Pou_xL3_01234567, Pou_yL3_01234567, pblock);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_fft_1024_32x16t_stage4_0_vloops(pblock);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

#pragma DATA_SECTION(__pblock_vcop_fft_1024_32x16t_stage4_1, ".vcop_parameter_block")
#pragma DATA_ALIGN(__pblock_vcop_fft_1024_32x16t_stage4_1, __ALIGNOF__(int));
unsigned short __pblock_vcop_fft_1024_32x16t_stage4_1[28];

unsigned int vcop_fft_1024_32x16t_stage4_1_param_count(void)
{
   return 28u;
}

unsigned int vcop_fft_1024_32x16t_stage4_1_ctrl_count(void)
{
   return 0u;
}

unsigned int vcop_fft_1024_32x16t_stage4_1_init(
   __vptr_uint16 inp1_lx,
   __vptr_int16 inp1_hx,
   __vptr_uint16 inp1_ly,
   __vptr_int16 inp1_hy,
   __vptr_int16 CS,
   __vptr_int32 out_x,
   __vptr_int32 out_y,
   unsigned short pblock[])
{
   int __offset = 0;
   /* Loop 1 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), (8)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), (4)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), (3)-1u);
   __vcop_pblock_init32(pblock, __offset+_PREG(6), (uchar *)inp1_lx);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)inp1_hy);
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)inp1_ly);
   __vcop_pblock_init32(pblock, __offset+_PREG(12), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(14), __vcop_vop_round(1, 15));
   __vcop_pblock_init16(pblock, __offset+_PREG(15), __vcop_vop_round(3, 1));
   __vcop_pblock_init32(pblock, __offset+_PREG(16), (uchar *)out_x);
   __vcop_pblock_init32(pblock, __offset+_PREG(18), (uchar *)out_y);
   __vcop_pblock_init16(pblock, __offset+_PREG(20), 144);
   __vcop_pblock_init16(pblock, __offset+_PREG(21), -252);
   __vcop_pblock_init16(pblock, __offset+_PREG(22), 180);
   __vcop_pblock_init16(pblock, __offset+_PREG(23), 288);
   __vcop_pblock_init16(pblock, __offset+_PREG(24), 32);
   __vcop_pblock_init16(pblock, __offset+_PREG(25), -352);
   __vcop_pblock_init32(pblock, __offset+_PREG(26), (uchar *)CS);
   __vcop_pblock_init32(pblock, __offset+_PREG(28), (uchar *)inp1_hx);
   __offset += 28;

   return 28u;
}

void vcop_fft_1024_32x16t_stage4_1_vloops(
   unsigned short pblock[])
{
   /* Kernel-wide Vector Registers */
   #pragma VCC_VREG("VA", 16);
   #pragma VCC_VREG("VB", 17);
   #pragma VCC_VREG("VC", 18);
   #pragma VCC_VREG("VE", 19);
   #pragma VCC_VREG("VF", 20);
   #pragma VCC_VREG("VG", 21);
   #pragma VCC_VREG("Vacc2", 22);
   #pragma VCC_VREG("Vacc4", 23);
   #pragma VCC_VREG("Vacc6", 24);
   #pragma VCC_VREG("Vacc8", 25);
   #pragma VCC_VREG("Vout0", 26);
   #pragma VCC_VREG("Vout1", 27);

   __vcop_param(&pblock[0]);

   /* VLOOP 1 Start */

   /* VLOOP Local Vector Registers */
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("Addr_in", "A0");
   #pragma EVE_REG("Addr_ou", "A1");
   #pragma EVE_REG("Addr_tw", "A2");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I2", "I2");
   #pragma EVE_REG("I3", "I3");
   #pragma EVE_REG("I4", "I4");
   

   __vcop_vloop(__vcop_compute(), 21u, 14u, 1u);
   __vcop_vinit(__vcop_sizeW(), __vcop_alws(), _PREG(12), _VREG(26));
   __vcop_vinit(__vcop_sizeW(), __vcop_alws(), _PREG(12), _VREG(27));
   __vcop_vagen(_AGEN(0), _PREG(20), _PREG(21), _PREG(22), _PREG(0));
   __vcop_vagen(_AGEN(2), _PREG(24), _PREG(24), _PREG(25), _PREG(0));
   __vcop_vload(__vcop_sizeH(), __vcop_dintrlv(), _PREG(26), _AGEN(2), _VPAIR(21,18), __vcop_alws());
   __vcop_vload(__vcop_sizeH(), __vcop_ds2(), _PREG(28), _AGEN(0), _VREG(16), __vcop_alws());
   __vcop_vload(__vcop_sizeHU(), __vcop_ds2(), _PREG(6), _AGEN(0), _VREG(17), __vcop_alws());
   __vcop_vload(__vcop_sizeH(), __vcop_ds2(), _PREG(8), _AGEN(0), _VREG(19), __vcop_alws());
   __vcop_vload(__vcop_sizeHU(), __vcop_ds2(), _PREG(10), _AGEN(0), _VREG(20), __vcop_alws());
   __vcop_vmadd(_VREG(17), _VREG(18), _VREG(26), _PREG(14));
   __vcop_vmadd(_VREG(20), _VREG(18), _VREG(27), _PREG(14));
   __vcop_vmadd(_VREG(20), _VREG(21), _VREG(26), _PREG(14));
   __vcop_vmsub(_VREG(17), _VREG(21), _VREG(27), _PREG(14));
   __vcop_vmadd(_VREG(16), _VREG(18), _VREG(26), _PREG(15));
   __vcop_vmsub(_VREG(16), _VREG(21), _VREG(27), _PREG(15));
   __vcop_vmadd(_VREG(19), _VREG(21), _VREG(26), _PREG(15));
   __vcop_vmadd(_VREG(19), _VREG(18), _VREG(27), _PREG(15));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeW(), __vcop_npt(), __vcop_alws(), _VREG(26), _PREG(16), _AGEN(0), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeW(), __vcop_npt(), __vcop_alws(), _VREG(27), _PREG(18), _AGEN(0), _PREG(0));
   __vcop_vloop_end(1u);

}

void vcop_fft_1024_32x16t_stage4_1(
   __vptr_uint16 inp1_lx,
   __vptr_int16 inp1_hx,
   __vptr_uint16 inp1_ly,
   __vptr_int16 inp1_hy,
   __vptr_int16 CS,
   __vptr_int32 out_x,
   __vptr_int32 out_y)
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_fft_1024_32x16t_stage4_1_init(inp1_lx, inp1_hx, inp1_ly, inp1_hy, CS, out_x, out_y, __pblock_vcop_fft_1024_32x16t_stage4_1);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_fft_1024_32x16t_stage4_1_vloops(__pblock_vcop_fft_1024_32x16t_stage4_1);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

void vcop_fft_1024_32x16t_stage4_1_custom(
   __vptr_uint16 inp1_lx,
   __vptr_int16 inp1_hx,
   __vptr_uint16 inp1_ly,
   __vptr_int16 inp1_hy,
   __vptr_int16 CS,
   __vptr_int32 out_x,
   __vptr_int32 out_y,
   unsigned short pblock[])
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_fft_1024_32x16t_stage4_1_init(inp1_lx, inp1_hx, inp1_ly, inp1_hy, CS, out_x, out_y, pblock);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_fft_1024_32x16t_stage4_1_vloops(pblock);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

#pragma DATA_SECTION(__pblock_vcop_fft_1024_32x16t_stage5, ".vcop_parameter_block")
#pragma DATA_ALIGN(__pblock_vcop_fft_1024_32x16t_stage5, __ALIGNOF__(int));
unsigned short __pblock_vcop_fft_1024_32x16t_stage5[40];

unsigned int vcop_fft_1024_32x16t_stage5_param_count(void)
{
   return 40u;
}

unsigned int vcop_fft_1024_32x16t_stage5_ctrl_count(void)
{
   return 0u;
}

unsigned int vcop_fft_1024_32x16t_stage5_init(
   __vptr_int32 Pxi0,
   __vptr_int32 Pyi0,
   __vptr_int32 Pxi1,
   __vptr_int32 Pyi1,
   __vptr_int32 Pxi2,
   __vptr_int32 Pyi2,
   __vptr_int32 Pxi3,
   __vptr_int32 Pyi3,
   __vptr_int32 Pox0,
   __vptr_int32 Poy0,
   __vptr_int32 Pox1,
   __vptr_int32 Poy1,
   __vptr_int32 Pox2,
   __vptr_int32 Poy2,
   __vptr_int32 Pox3,
   __vptr_int32 Poy3,
   unsigned short pblock[])
{
   int __offset = 0;
   /* Loop 1 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), (2)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), (4)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), (4)-1u);
   __vcop_pblock_init32(pblock, __offset+_PREG(6), (uchar *)Pxi1);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)Pyi1);
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)Pxi2);
   __vcop_pblock_init32(pblock, __offset+_PREG(12), (uchar *)Pyi2);
   __vcop_pblock_init32(pblock, __offset+_PREG(14), (uchar *)Pxi3);
   __vcop_pblock_init32(pblock, __offset+_PREG(16), (uchar *)Pyi3);
   __vcop_pblock_init32(pblock, __offset+_PREG(18), (uchar *)Pox0);
   __vcop_pblock_init32(pblock, __offset+_PREG(20), (uchar *)Poy0);
   __vcop_pblock_init32(pblock, __offset+_PREG(22), (uchar *)Pox1);
   __vcop_pblock_init32(pblock, __offset+_PREG(24), (uchar *)Poy1);
   __vcop_pblock_init32(pblock, __offset+_PREG(26), (uchar *)Pox2);
   __vcop_pblock_init32(pblock, __offset+_PREG(28), (uchar *)Poy2);
   __vcop_pblock_init32(pblock, __offset+_PREG(30), (uchar *)Pox3);
   __vcop_pblock_init32(pblock, __offset+_PREG(32), (uchar *)Poy3);
   __vcop_pblock_init16(pblock, __offset+_PREG(34), 144);
   __vcop_pblock_init16(pblock, __offset+_PREG(35), 512);
   __vcop_pblock_init16(pblock, __offset+_PREG(36), -1408);
   __vcop_pblock_init16(pblock, __offset+_PREG(37), -1856);
   __vcop_pblock_init32(pblock, __offset+_PREG(38), (uchar *)Pxi0);
   __vcop_pblock_init32(pblock, __offset+_PREG(40), (uchar *)Pyi0);
   __offset += 40;

   return 40u;
}

void vcop_fft_1024_32x16t_stage5_vloops(
   unsigned short pblock[])
{
   /* Kernel-wide Vector Registers */

   __vcop_param(&pblock[0]);

   /* VLOOP 1 Start */

   /* VLOOP Local Vector Registers */
   #pragma VCC_VREG("V_n00", 16);
   #pragma VCC_VREG("V_n01", 17);
   #pragma VCC_VREG("V_n10", 18);
   #pragma VCC_VREG("V_n11", 19);
   #pragma VCC_VREG("V_n20", 20);
   #pragma VCC_VREG("V_n21", 21);
   #pragma VCC_VREG("V_n30", 22);
   #pragma VCC_VREG("V_n31", 23);
   #pragma VCC_VREG("VnX0_76543210", 24);
   #pragma VCC_VREG("VnX1_76543210", 25);
   #pragma VCC_VREG("VnX2_76543210", 26);
   #pragma VCC_VREG("VnX3_76543210", 27);
   #pragma VCC_VREG("VnY0_76543210", 28);
   #pragma VCC_VREG("VnY1_76543210", 29);
   #pragma VCC_VREG("VnY2_76543210", 30);
   #pragma VCC_VREG("VnY3_76543210", 31);
   #pragma VCC_VREG("Vxh0_0", 32);
   #pragma VCC_VREG("Vxh0_1", 33);
   #pragma VCC_VREG("Vxh1_0", 34);
   #pragma VCC_VREG("Vxh1_1", 35);
   #pragma VCC_VREG("Vxl0_0", 36);
   #pragma VCC_VREG("Vxl0_1", 37);
   #pragma VCC_VREG("Vxl1_0", 38);
   #pragma VCC_VREG("Vxl1_1", 39);
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("Addr_in", "A0");
   #pragma EVE_REG("Addr_ou", "A1");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I2", "I2");
   #pragma EVE_REG("I3", "I3");
   #pragma EVE_REG("I4", "I4");
   

   __vcop_vloop(__vcop_compute(), 47u, 20u, 1u);
   __vcop_vagen(_AGEN(0), _PREG(34), _PREG(34), _PREG(34), _PREG(0));
   __vcop_vagen(_AGEN(1), _PREG(35), _PREG(36), _PREG(37), _PREG(0));
   __vcop_vload(__vcop_sizeW(), __vcop_npt(), _PREG(38), _AGEN(0), _VREG(24), __vcop_alws());
   __vcop_vload(__vcop_sizeW(), __vcop_npt(), _PREG(40), _AGEN(0), _VREG(28), __vcop_alws());
   __vcop_vload(__vcop_sizeW(), __vcop_npt(), _PREG(6), _AGEN(0), _VREG(25), __vcop_alws());
   __vcop_vload(__vcop_sizeW(), __vcop_npt(), _PREG(8), _AGEN(0), _VREG(29), __vcop_alws());
   __vcop_vload(__vcop_sizeW(), __vcop_npt(), _PREG(10), _AGEN(0), _VREG(26), __vcop_alws());
   __vcop_vload(__vcop_sizeW(), __vcop_npt(), _PREG(12), _AGEN(0), _VREG(30), __vcop_alws());
   __vcop_vload(__vcop_sizeW(), __vcop_npt(), _PREG(14), _AGEN(0), _VREG(27), __vcop_alws());
   __vcop_vload(__vcop_sizeW(), __vcop_npt(), _PREG(16), _AGEN(0), _VREG(31), __vcop_alws());
   __vcop_vmove(_VREG(24), _VREG(32));
   __vcop_vmove(_VREG(26), _VREG(36));
   __vcop_vaddsub(_VREG(32), _VREG(36));
   __vcop_vmove(_VREG(28), _VREG(34));
   __vcop_vmove(_VREG(30), _VREG(38));
   __vcop_vaddsub(_VREG(34), _VREG(38));
   __vcop_vmove(_VREG(25), _VREG(33));
   __vcop_vmove(_VREG(27), _VREG(37));
   __vcop_vaddsub(_VREG(33), _VREG(37));
   __vcop_vmove(_VREG(29), _VREG(35));
   __vcop_vmove(_VREG(31), _VREG(39));
   __vcop_vaddsub(_VREG(35), _VREG(39));
   __vcop_vmove(_VREG(32), _VREG(16));
   __vcop_vmove(_VREG(33), _VREG(20));
   __vcop_vaddsub(_VREG(16), _VREG(20));
   __vcop_vmove(_VREG(36), _VREG(18));
   __vcop_vmove(_VREG(39), _VREG(22));
   __vcop_vaddsub(_VREG(18), _VREG(22));
   __vcop_vmove(_VREG(34), _VREG(17));
   __vcop_vmove(_VREG(35), _VREG(21));
   __vcop_vaddsub(_VREG(17), _VREG(21));
   __vcop_vmove(_VREG(38), _VREG(23));
   __vcop_vmove(_VREG(37), _VREG(19));
   __vcop_vaddsub(_VREG(23), _VREG(19));
   __vcop_vintrlv(_VREG(16), _VREG(17));
   __vcop_vintrlv(_VREG(18), _VREG(19));
   __vcop_vintrlv(_VREG(20), _VREG(21));
   __vcop_vintrlv(_VREG(22), _VREG(23));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeW(), __vcop_npt(), __vcop_alws(), _VREG(16), _PREG(18), _AGEN(1), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeW(), __vcop_npt(), __vcop_alws(), _VREG(17), _PREG(20), _AGEN(1), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeW(), __vcop_npt(), __vcop_alws(), _VREG(18), _PREG(22), _AGEN(1), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeW(), __vcop_npt(), __vcop_alws(), _VREG(19), _PREG(24), _AGEN(1), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeW(), __vcop_npt(), __vcop_alws(), _VREG(20), _PREG(26), _AGEN(1), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeW(), __vcop_npt(), __vcop_alws(), _VREG(21), _PREG(28), _AGEN(1), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeW(), __vcop_npt(), __vcop_alws(), _VREG(22), _PREG(30), _AGEN(1), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeW(), __vcop_npt(), __vcop_alws(), _VREG(23), _PREG(32), _AGEN(1), _PREG(0));
   __vcop_vloop_end(1u);

}

void vcop_fft_1024_32x16t_stage5(
   __vptr_int32 Pxi0,
   __vptr_int32 Pyi0,
   __vptr_int32 Pxi1,
   __vptr_int32 Pyi1,
   __vptr_int32 Pxi2,
   __vptr_int32 Pyi2,
   __vptr_int32 Pxi3,
   __vptr_int32 Pyi3,
   __vptr_int32 Pox0,
   __vptr_int32 Poy0,
   __vptr_int32 Pox1,
   __vptr_int32 Poy1,
   __vptr_int32 Pox2,
   __vptr_int32 Poy2,
   __vptr_int32 Pox3,
   __vptr_int32 Poy3)
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_fft_1024_32x16t_stage5_init(Pxi0, Pyi0, Pxi1, Pyi1, Pxi2, Pyi2, Pxi3, Pyi3, Pox0, Poy0, Pox1, Poy1, Pox2, Poy2, Pox3, Poy3, __pblock_vcop_fft_1024_32x16t_stage5);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_fft_1024_32x16t_stage5_vloops(__pblock_vcop_fft_1024_32x16t_stage5);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

void vcop_fft_1024_32x16t_stage5_custom(
   __vptr_int32 Pxi0,
   __vptr_int32 Pyi0,
   __vptr_int32 Pxi1,
   __vptr_int32 Pyi1,
   __vptr_int32 Pxi2,
   __vptr_int32 Pyi2,
   __vptr_int32 Pxi3,
   __vptr_int32 Pyi3,
   __vptr_int32 Pox0,
   __vptr_int32 Poy0,
   __vptr_int32 Pox1,
   __vptr_int32 Poy1,
   __vptr_int32 Pox2,
   __vptr_int32 Poy2,
   __vptr_int32 Pox3,
   __vptr_int32 Poy3,
   unsigned short pblock[])
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_fft_1024_32x16t_stage5_init(Pxi0, Pyi0, Pxi1, Pyi1, Pxi2, Pyi2, Pxi3, Pyi3, Pox0, Poy0, Pox1, Poy1, Pox2, Poy2, Pox3, Poy3, pblock);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_fft_1024_32x16t_stage5_vloops(pblock);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

