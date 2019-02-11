#include <vcop\vcop.h>

typedef unsigned char uchar;

#pragma DATA_SECTION(__pblock_clahe_make_8way_look_up_kernel, ".vcop_parameter_block")
#pragma DATA_ALIGN(__pblock_clahe_make_8way_look_up_kernel, __ALIGNOF__(int));
unsigned short __pblock_clahe_make_8way_look_up_kernel[10];

unsigned int clahe_make_8way_look_up_kernel_param_count(void)
{
   return 10u;
}

unsigned int clahe_make_8way_look_up_kernel_ctrl_count(void)
{
   return 0u;
}

unsigned int clahe_make_8way_look_up_kernel_init(
   __vptr_uint32 inLuts,
   __vptr_uint32 outLuts,
   unsigned short histSize,
   unsigned short pblock[])
{
   int __offset = 0;
   /* Loop 1 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), (histSize)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(6), 4);
   __vcop_pblock_init16(pblock, __offset+_PREG(7), 32);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)inLuts);
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)outLuts);
   __offset += 10;

   return 10u;
}

void clahe_make_8way_look_up_kernel_vloops(
   unsigned short pblock[])
{
   /* Kernel-wide Vector Registers */
   #pragma VCC_VREG("Vlut", 16);

   __vcop_param(&pblock[0]);

   /* VLOOP 1 Start */

   /* VLOOP Local Vector Registers */
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("Addr_in", "A0");
   #pragma EVE_REG("Addr_out", "A1");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("i", "I4");
   

   __vcop_vloop(__vcop_compute(), 5u, 5u, 1u);
   __vcop_vagen(_AGEN(0), _PREG(6), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(1), _PREG(7), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeWU(), __vcop_1pt(), _PREG(8), _AGEN(0), _VREG(16), __vcop_alws());
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeWU(), __vcop_npt(), __vcop_alws(), _VREG(16), _PREG(10), _AGEN(1), _PREG(0));
   __vcop_vloop_end(1u);

}

void clahe_make_8way_look_up_kernel(
   __vptr_uint32 inLuts,
   __vptr_uint32 outLuts,
   unsigned short histSize)
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   clahe_make_8way_look_up_kernel_init(inLuts, outLuts, histSize, __pblock_clahe_make_8way_look_up_kernel);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   clahe_make_8way_look_up_kernel_vloops(__pblock_clahe_make_8way_look_up_kernel);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

void clahe_make_8way_look_up_kernel_custom(
   __vptr_uint32 inLuts,
   __vptr_uint32 outLuts,
   unsigned short histSize,
   unsigned short pblock[])
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   clahe_make_8way_look_up_kernel_init(inLuts, outLuts, histSize, pblock);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   clahe_make_8way_look_up_kernel_vloops(pblock);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

#pragma DATA_SECTION(__pblock_clahe_look_up_and_interpolate_kernel, ".vcop_parameter_block")
#pragma DATA_ALIGN(__pblock_clahe_look_up_and_interpolate_kernel, __ALIGNOF__(int));
unsigned short __pblock_clahe_look_up_and_interpolate_kernel[48];

unsigned int clahe_look_up_and_interpolate_kernel_param_count(void)
{
   return 48u;
}

unsigned int clahe_look_up_and_interpolate_kernel_ctrl_count(void)
{
   return 0u;
}

unsigned int clahe_look_up_and_interpolate_kernel_init(
   __vptr_uint8 inBuf,
   __vptr_uint8 inLut,
   __vptr_uint16 xWgtBuf,
   __vptr_uint16 yWgtBuf,
   __vptr_uint8 tempBuf,
   __vptr_uint8 outBuf,
   unsigned short inWidth,
   unsigned short inHeight,
   unsigned short inPitch,
   unsigned short tablePitch,
   unsigned short numTab,
   unsigned short pblock[])
{
   int __offset = 0;
   /* Loop 1 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), (numTab)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), (inHeight)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), (((inWidth+(8u)-1) /(8u)))-1u);
   __vcop_pblock_init32(pblock, __offset+_PREG(6), (uchar *)tempBuf);
   __vcop_pblock_init16(pblock, __offset+_PREG(8), 8);
   __vcop_pblock_init16(pblock, __offset+_PREG(9), (inPitch) -(sizeof(*inBuf)*8u)*((((inWidth+(8u)-1) /(8u)))-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(10), (0) -(inPitch)*((inHeight)-1u) -(sizeof(*inBuf)*8u)*((((inWidth+(8u)-1) /(8u)))-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(11), (inWidth) -(sizeof(*inBuf)*8u)*((((inWidth+(8u)-1) /(8u)))-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(12), (inWidth*inHeight) -(inWidth)*((inHeight)-1u) -(sizeof(*inBuf)*8u)*((((inWidth+(8u)-1) /(8u)))-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(13), (0) -(0)*((((inWidth+(8u)-1) /(8u)))-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(14), (tablePitch) -(0)*((inHeight)-1u) -(0)*((((inWidth+(8u)-1) /(8u)))-1u));
   __vcop_pblock_init32(pblock, __offset+_PREG(16), (uchar *)inBuf);
   __vcop_pblock_init32(pblock, __offset+_PREG(18), (uchar *)inLut);
   __offset += 18;

   /* Loop 2 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), (inHeight)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), (((inWidth+(8u)-1) /(8u)))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(6), __vcop_store_round_sat(SM_NONE,0,RM_ROUND,23));
   __vcop_pblock_init16(pblock, __offset+_PREG(7), 8);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)yWgtBuf+2);
   __vcop_pblock_init32(pblock, __offset+_PREG(10), 0xFF);
   __vcop_pblock_init32(pblock, __offset+_PREG(12), (uchar *)xWgtBuf);
   __vcop_pblock_init32(pblock, __offset+_PREG(14), (uchar *)tempBuf+0*inWidth*inHeight);
   __vcop_pblock_init32(pblock, __offset+_PREG(16), (uchar *)tempBuf+1*inWidth*inHeight);
   __vcop_pblock_init32(pblock, __offset+_PREG(18), (uchar *)tempBuf+2*inWidth*inHeight);
   __vcop_pblock_init32(pblock, __offset+_PREG(20), (uchar *)tempBuf+3*inWidth*inHeight);
   __vcop_pblock_init32(pblock, __offset+_PREG(22), (uchar *)outBuf);
   __vcop_pblock_init16(pblock, __offset+_PREG(24), (inWidth) -(sizeof(*inBuf)*8u)*((((inWidth+(8u)-1) /(8u)))-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(25), 32);
   __vcop_pblock_init16(pblock, __offset+_PREG(26),  -(sizeof(*xWgtBuf)*8u*2)*((((inWidth+(8u)-1) /(8u)))-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(27), 4);
   __vcop_pblock_init32(pblock, __offset+_PREG(28), -9);
   __vcop_pblock_init32(pblock, __offset+_PREG(30), (uchar *)yWgtBuf);
   __offset += 30;

   return 48u;
}

void clahe_look_up_and_interpolate_kernel_vloops(
   unsigned short pblock[])
{
   /* Kernel-wide Vector Registers */
   #pragma VCC_VREG("Vdata0", 16);
   #pragma VCC_VREG("Vdata1", 17);
   #pragma VCC_VREG("Vdata2", 18);
   #pragma VCC_VREG("Vdata3", 19);
   #pragma VCC_VREG("Vindex", 20);
   #pragma VCC_VREG("Vout", 21);
   #pragma VCC_VREG("Vout0", 22);
   #pragma VCC_VREG("Vout1", 23);
   #pragma VCC_VREG("VxWgt0", 24);
   #pragma VCC_VREG("VxWgt1", 25);
   #pragma VCC_VREG("VyWgt0", 26);
   #pragma VCC_VREG("VyWgt1", 27);
   #pragma VCC_VREG("vShift", 28);

   __vcop_param(&pblock[0]);

   /* VLOOP 1 Start */

   /* VLOOP Local Vector Registers */
   #pragma VCC_VREG("Vdata", 29);
   #pragma VCC_VREG("Vindex", 30);
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("Addr_index", "A0");
   #pragma EVE_REG("Addr_out", "A2");
   #pragma EVE_REG("Addr_table", "A1");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("k", "I2");
   #pragma EVE_REG("i", "I3");
   #pragma EVE_REG("j", "I4");
   

   __vcop_vloop(__vcop_tablelkup(), 7u, 9u, 1u);
   __vcop_vagen(_AGEN(0), _PREG(8), _PREG(9), _PREG(10), _PREG(0));
   __vcop_vagen(_AGEN(2), _PREG(8), _PREG(11), _PREG(12), _PREG(0));
   __vcop_vagen(_AGEN(1), _PREG(0), _PREG(13), _PREG(14), _PREG(0));
   __vcop_vload(__vcop_sizeBU(), __vcop_npt(), _PREG(16), _AGEN(0), _VREG(30), __vcop_alws());
   __vcop_vtbload(__vcop_sizeBU(), __vcop_tableinfo(8, 1), _PREG(18), _AGEN(1), _VREG(30), _VREG(29), _PREG(0), __vcop_alws());
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeBU(), __vcop_npt(), __vcop_alws(), _VREG(29), _PREG(6), _AGEN(2), _PREG(0));
   __vcop_vloop_end(1u);

   /* VLOOP 2 Start */

   /* VLOOP Local Vector Registers */
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("Addr_0", "A0");
   #pragma EVE_REG("Addr_out", "A1");
   #pragma EVE_REG("Addr_xWgt", "A2");
   #pragma EVE_REG("Addr_yWgt", "A3");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("i", "I3");
   #pragma EVE_REG("j", "I4");
   

   __vcop_vloop(__vcop_compute(), 24u, 15u, 2u);
   __vcop_vinit(__vcop_sizeW(), __vcop_once(), _PREG(28), _VREG(28));
   __vcop_vinit(__vcop_sizeW(), __vcop_alws(), _PREG(10), _VREG(22));
   __vcop_vinit(__vcop_sizeW(), __vcop_alws(), _PREG(10), _VREG(23));
   __vcop_vagen(_AGEN(0), _PREG(7), _PREG(24), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(1), _PREG(7), _PREG(24), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(2), _PREG(25), _PREG(26), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(3), _PREG(0), _PREG(27), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeHU(), __vcop_1pt(), _PREG(30), _AGEN(3), _VREG(26), __vcop_i4_zero());
   __vcop_vload(__vcop_sizeHU(), __vcop_1pt(), _PREG(8), _AGEN(3), _VREG(27), __vcop_i4_zero());
   __vcop_vload(__vcop_sizeHU(), __vcop_dintrlv(), _PREG(12), _AGEN(2), _VPAIR(24,25), __vcop_alws());
   __vcop_vload(__vcop_sizeBU(), __vcop_npt(), _PREG(14), _AGEN(0), _VREG(16), __vcop_alws());
   __vcop_vload(__vcop_sizeBU(), __vcop_npt(), _PREG(16), _AGEN(0), _VREG(17), __vcop_alws());
   __vcop_vload(__vcop_sizeBU(), __vcop_npt(), _PREG(18), _AGEN(0), _VREG(18), __vcop_alws());
   __vcop_vload(__vcop_sizeBU(), __vcop_npt(), _PREG(20), _AGEN(0), _VREG(19), __vcop_alws());
   __vcop_vmadd(_VREG(16), _VREG(24), _VREG(22), _PREG(0));
   __vcop_vmadd(_VREG(17), _VREG(25), _VREG(22), _PREG(0));
   __vcop_vmadd(_VREG(18), _VREG(24), _VREG(23), _PREG(0));
   __vcop_vmadd(_VREG(19), _VREG(25), _VREG(23), _PREG(0));
   __vcop_vshf(_VREG(22), _VREG(28), _VREG(22));
   __vcop_vshf(_VREG(23), _VREG(28), _VREG(23));
   __vcop_vmpy(_VREG(22), _VREG(26), _VREG(21), _PREG(0));
   __vcop_vmadd(_VREG(23), _VREG(27), _VREG(21), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeBU(), __vcop_npt(), __vcop_alws(), _VREG(21), _PREG(22), _AGEN(1), _PREG(6));
   __vcop_vloop_end(2u);

}

void clahe_look_up_and_interpolate_kernel(
   __vptr_uint8 inBuf,
   __vptr_uint8 inLut,
   __vptr_uint16 xWgtBuf,
   __vptr_uint16 yWgtBuf,
   __vptr_uint8 tempBuf,
   __vptr_uint8 outBuf,
   unsigned short inWidth,
   unsigned short inHeight,
   unsigned short inPitch,
   unsigned short tablePitch,
   unsigned short numTab)
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   clahe_look_up_and_interpolate_kernel_init(inBuf, inLut, xWgtBuf, yWgtBuf, tempBuf, outBuf, inWidth, inHeight, inPitch, tablePitch, numTab, __pblock_clahe_look_up_and_interpolate_kernel);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   clahe_look_up_and_interpolate_kernel_vloops(__pblock_clahe_look_up_and_interpolate_kernel);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

void clahe_look_up_and_interpolate_kernel_custom(
   __vptr_uint8 inBuf,
   __vptr_uint8 inLut,
   __vptr_uint16 xWgtBuf,
   __vptr_uint16 yWgtBuf,
   __vptr_uint8 tempBuf,
   __vptr_uint8 outBuf,
   unsigned short inWidth,
   unsigned short inHeight,
   unsigned short inPitch,
   unsigned short tablePitch,
   unsigned short numTab,
   unsigned short pblock[])
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   clahe_look_up_and_interpolate_kernel_init(inBuf, inLut, xWgtBuf, yWgtBuf, tempBuf, outBuf, inWidth, inHeight, inPitch, tablePitch, numTab, pblock);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   clahe_look_up_and_interpolate_kernel_vloops(pblock);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

