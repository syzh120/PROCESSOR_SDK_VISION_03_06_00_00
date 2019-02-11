#include <vcop\vcop.h>

typedef unsigned char uchar;

#pragma DATA_SECTION(__pblock_vcop_gauss5x5PyramidKernel_8_horiz, ".vcop_parameter_block")
#pragma DATA_ALIGN(__pblock_vcop_gauss5x5PyramidKernel_8_horiz, __ALIGNOF__(int));
unsigned short __pblock_vcop_gauss5x5PyramidKernel_8_horiz[22];

unsigned int vcop_gauss5x5PyramidKernel_8_horiz_param_count(void)
{
   return 22u;
}

unsigned int vcop_gauss5x5PyramidKernel_8_horiz_ctrl_count(void)
{
   return 0u;
}

unsigned int vcop_gauss5x5PyramidKernel_8_horiz_init(
   __vptr_uint8 pIn,
   __vptr_uint8 pOut,
   unsigned short width,
   unsigned short height,
   unsigned short inPitch,
   unsigned short outPitch,
   unsigned short pblock[])
{
   int __offset = 0;
   /* Loop 1 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), (height)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), ((((width) + (2*(8u))-1) & ~(2*(8u)-1))/(2*(8u)))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(6), __vcop_store_round_sat(SM_NONE,0,RM_TRUNC,4));
   __vcop_pblock_init16(pblock, __offset+_PREG(7), 16);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)pIn);
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)pIn+2*sizeof(*pIn));
   __vcop_pblock_init32(pblock, __offset+_PREG(12), (uchar *)pIn+4*sizeof(*pIn));
   __vcop_pblock_init32(pblock, __offset+_PREG(14), (uchar *)pOut);
   __vcop_pblock_init16(pblock, __offset+_PREG(16), (inPitch*sizeof(*pIn)) -(2*(8u*sizeof(*pIn)))*(((((width) + (2*(8u))-1) & ~(2*(8u)-1))/(2*(8u)))-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(17), 8);
   __vcop_pblock_init16(pblock, __offset+_PREG(18), (outPitch*sizeof(*pIn)) -((8u*sizeof(*pIn)))*(((((width) + (2*(8u))-1) & ~(2*(8u)-1))/(2*(8u)))-1u));
   __vcop_pblock_init32(pblock, __offset+_PREG(20), 4);
   __vcop_pblock_init32(pblock, __offset+_PREG(22), 6);
   __offset += 22;

   return 22u;
}

void vcop_gauss5x5PyramidKernel_8_horiz_vloops(
   unsigned short pblock[])
{
   /* Kernel-wide Vector Registers */
   #pragma VCC_VREG("C_4", 16);
   #pragma VCC_VREG("C_6", 17);
   #pragma VCC_VREG("vIn024_14", 18);
   #pragma VCC_VREG("vIn135_15", 19);
   #pragma VCC_VREG("vIn246_16", 20);
   #pragma VCC_VREG("vIn357_17", 21);
   #pragma VCC_VREG("vIn468_18", 22);
   #pragma VCC_VREG("vIn579_19", 23);
   #pragma VCC_VREG("vTemp", 24);
   #pragma VCC_VREG("vTemp1", 25);
   #pragma VCC_VREG("vTemp2", 26);

   __vcop_param(&pblock[0]);

   /* VLOOP 1 Start */

   /* VLOOP Local Vector Registers */
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("Addr1", "A0");
   #pragma EVE_REG("Addr2", "A1");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("i", "I3");
   #pragma EVE_REG("j", "I4");
   

   __vcop_vloop(__vcop_compute(), 14u, 11u, 1u);
   __vcop_vinit(__vcop_sizeW(), __vcop_once(), _PREG(20), _VREG(16));
   __vcop_vinit(__vcop_sizeW(), __vcop_once(), _PREG(22), _VREG(17));
   __vcop_vagen(_AGEN(0), _PREG(7), _PREG(16), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(1), _PREG(17), _PREG(18), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeBU(), __vcop_dintrlv(), _PREG(8), _AGEN(0), _VPAIR(18,19), __vcop_alws());
   __vcop_vload(__vcop_sizeBU(), __vcop_dintrlv(), _PREG(10), _AGEN(0), _VPAIR(20,21), __vcop_alws());
   __vcop_vload(__vcop_sizeBU(), __vcop_dintrlv(), _PREG(12), _AGEN(0), _VPAIR(22,23), __vcop_alws());
   __vcop_vadd(_VREG(19), _VREG(21), _VREG(25));
   __vcop_vadd(_VREG(22), _VREG(18), _VREG(26));
   __vcop_vmpy(_VREG(20), _VREG(17), _VREG(24), _PREG(0));
   __vcop_vmpy(_VREG(25), _VREG(16), _VREG(25), _PREG(0));
   __vcop_vadd3(_VREG(25), _VREG(24), _VREG(26));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeBU(), __vcop_npt(), __vcop_alws(), _VREG(26), _PREG(14), _AGEN(1), _PREG(6));
   __vcop_vloop_end(1u);

}

void vcop_gauss5x5PyramidKernel_8_horiz(
   __vptr_uint8 pIn,
   __vptr_uint8 pOut,
   unsigned short width,
   unsigned short height,
   unsigned short inPitch,
   unsigned short outPitch)
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_gauss5x5PyramidKernel_8_horiz_init(pIn, pOut, width, height, inPitch, outPitch, __pblock_vcop_gauss5x5PyramidKernel_8_horiz);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_gauss5x5PyramidKernel_8_horiz_vloops(__pblock_vcop_gauss5x5PyramidKernel_8_horiz);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

void vcop_gauss5x5PyramidKernel_8_horiz_custom(
   __vptr_uint8 pIn,
   __vptr_uint8 pOut,
   unsigned short width,
   unsigned short height,
   unsigned short inPitch,
   unsigned short outPitch,
   unsigned short pblock[])
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_gauss5x5PyramidKernel_8_horiz_init(pIn, pOut, width, height, inPitch, outPitch, pblock);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_gauss5x5PyramidKernel_8_horiz_vloops(pblock);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

#pragma DATA_SECTION(__pblock_vcop_gauss5x5PyramidKernel_8_vert, ".vcop_parameter_block")
#pragma DATA_ALIGN(__pblock_vcop_gauss5x5PyramidKernel_8_vert, __ALIGNOF__(int));
unsigned short __pblock_vcop_gauss5x5PyramidKernel_8_vert[24];

unsigned int vcop_gauss5x5PyramidKernel_8_vert_param_count(void)
{
   return 24u;
}

unsigned int vcop_gauss5x5PyramidKernel_8_vert_ctrl_count(void)
{
   return 0u;
}

unsigned int vcop_gauss5x5PyramidKernel_8_vert_init(
   __vptr_uint8 pIn,
   __vptr_uint8 pOut,
   unsigned short width,
   unsigned short height,
   unsigned short inPitch,
   unsigned short outPitch,
   unsigned short pblock[])
{
   int __offset = 0;
   /* Loop 1 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), ((height/2))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), ((((width) + (2*(8u))-1) & ~(2*(8u)-1))/(2*(8u)))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(6), __vcop_store_round_sat(SM_NONE,0,RM_TRUNC,4));
   __vcop_pblock_init16(pblock, __offset+_PREG(7), 16);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)pIn);
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)pIn+inPitch*sizeof(*pIn));
   __vcop_pblock_init32(pblock, __offset+_PREG(12), (uchar *)pIn+2*inPitch*sizeof(*pIn));
   __vcop_pblock_init32(pblock, __offset+_PREG(14), (uchar *)pIn+3*inPitch*sizeof(*pIn));
   __vcop_pblock_init32(pblock, __offset+_PREG(16), (uchar *)pIn+4*inPitch*sizeof(*pIn));
   __vcop_pblock_init32(pblock, __offset+_PREG(18), (uchar *)pOut);
   __vcop_pblock_init16(pblock, __offset+_PREG(20), (2*inPitch*sizeof(*pIn)) -(2*(8u*sizeof(*pIn)))*(((((width) + (2*(8u))-1) & ~(2*(8u)-1))/(2*(8u)))-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(21), (outPitch*sizeof(*pIn)) -(2*(8u*sizeof(*pIn)))*(((((width) + (2*(8u))-1) & ~(2*(8u)-1))/(2*(8u)))-1u));
   __vcop_pblock_init32(pblock, __offset+_PREG(22), 4);
   __vcop_pblock_init32(pblock, __offset+_PREG(24), 6);
   __offset += 24;

   return 24u;
}

void vcop_gauss5x5PyramidKernel_8_vert_vloops(
   unsigned short pblock[])
{
   /* Kernel-wide Vector Registers */
   #pragma VCC_VREG("C_4", 16);
   #pragma VCC_VREG("C_6", 17);
   #pragma VCC_VREG("vTemp1", 18);
   #pragma VCC_VREG("vTemp2", 19);
   #pragma VCC_VREG("vTemp_e", 20);
   #pragma VCC_VREG("vTemp_o", 21);
   #pragma VCC_VREG("vec1_e", 22);
   #pragma VCC_VREG("vec1_o", 23);
   #pragma VCC_VREG("vec2_e", 24);
   #pragma VCC_VREG("vec2_o", 25);
   #pragma VCC_VREG("vec3_e", 26);
   #pragma VCC_VREG("vec3_o", 27);
   #pragma VCC_VREG("vec4_e", 28);
   #pragma VCC_VREG("vec4_o", 29);
   #pragma VCC_VREG("vec5_e", 30);
   #pragma VCC_VREG("vec5_o", 31);

   __vcop_param(&pblock[0]);

   /* VLOOP 1 Start */

   /* VLOOP Local Vector Registers */
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("Addr1", "A0");
   #pragma EVE_REG("Addr2", "A1");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("i", "I3");
   #pragma EVE_REG("j", "I4");
   

   __vcop_vloop(__vcop_compute(), 21u, 12u, 1u);
   __vcop_vinit(__vcop_sizeW(), __vcop_once(), _PREG(22), _VREG(16));
   __vcop_vinit(__vcop_sizeW(), __vcop_once(), _PREG(24), _VREG(17));
   __vcop_vagen(_AGEN(0), _PREG(7), _PREG(20), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(1), _PREG(7), _PREG(21), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeBU(), __vcop_dintrlv(), _PREG(8), _AGEN(0), _VPAIR(22,23), __vcop_alws());
   __vcop_vload(__vcop_sizeBU(), __vcop_dintrlv(), _PREG(10), _AGEN(0), _VPAIR(24,25), __vcop_alws());
   __vcop_vload(__vcop_sizeBU(), __vcop_dintrlv(), _PREG(12), _AGEN(0), _VPAIR(26,27), __vcop_alws());
   __vcop_vload(__vcop_sizeBU(), __vcop_dintrlv(), _PREG(14), _AGEN(0), _VPAIR(28,29), __vcop_alws());
   __vcop_vload(__vcop_sizeBU(), __vcop_dintrlv(), _PREG(16), _AGEN(0), _VPAIR(30,31), __vcop_alws());
   __vcop_vadd(_VREG(24), _VREG(28), _VREG(18));
   __vcop_vadd(_VREG(22), _VREG(30), _VREG(22));
   __vcop_vmpy(_VREG(26), _VREG(17), _VREG(20), _PREG(0));
   __vcop_vmpy(_VREG(18), _VREG(16), _VREG(18), _PREG(0));
   __vcop_vadd3(_VREG(20), _VREG(18), _VREG(22));
   __vcop_vadd(_VREG(25), _VREG(29), _VREG(19));
   __vcop_vadd(_VREG(23), _VREG(31), _VREG(23));
   __vcop_vmpy(_VREG(27), _VREG(17), _VREG(21), _PREG(0));
   __vcop_vmpy(_VREG(19), _VREG(16), _VREG(19), _PREG(0));
   __vcop_vadd3(_VREG(21), _VREG(19), _VREG(23));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeBU(), __vcop_intrlv(), __vcop_alws(), _VPAIR(22,23), _PREG(18), _AGEN(1), _PREG(6));
   __vcop_vloop_end(1u);

}

void vcop_gauss5x5PyramidKernel_8_vert(
   __vptr_uint8 pIn,
   __vptr_uint8 pOut,
   unsigned short width,
   unsigned short height,
   unsigned short inPitch,
   unsigned short outPitch)
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_gauss5x5PyramidKernel_8_vert_init(pIn, pOut, width, height, inPitch, outPitch, __pblock_vcop_gauss5x5PyramidKernel_8_vert);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_gauss5x5PyramidKernel_8_vert_vloops(__pblock_vcop_gauss5x5PyramidKernel_8_vert);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

void vcop_gauss5x5PyramidKernel_8_vert_custom(
   __vptr_uint8 pIn,
   __vptr_uint8 pOut,
   unsigned short width,
   unsigned short height,
   unsigned short inPitch,
   unsigned short outPitch,
   unsigned short pblock[])
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_gauss5x5PyramidKernel_8_vert_init(pIn, pOut, width, height, inPitch, outPitch, pblock);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_gauss5x5PyramidKernel_8_vert_vloops(pblock);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

