#include <vcop\vcop.h>

typedef unsigned char uchar;

#pragma DATA_SECTION(__pblock_vcop_harrisScore_7x7_1, ".vcop_parameter_block")
#pragma DATA_ALIGN(__pblock_vcop_harrisScore_7x7_1, __ALIGNOF__(int));
unsigned short __pblock_vcop_harrisScore_7x7_1[74];

unsigned int vcop_harrisScore_7x7_1_param_count(void)
{
   return 74u;
}

unsigned int vcop_harrisScore_7x7_1_ctrl_count(void)
{
   return 0u;
}

unsigned int vcop_harrisScore_7x7_1_init(
   __vptr_int16 gradX,
   __vptr_int16 gradY,
   unsigned int width,
   unsigned int height,
   unsigned int srcPitch,
   unsigned int dstPitch,
   __vptr_int32 XX,
   __vptr_int32 YY,
   __vptr_int32 XY,
   unsigned short pblock[])
{
   int __offset = 0;
   /* Loop 1 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), ((( width + ((8u)-1))/(8u)))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), ((height))-1u);
   __vcop_pblock_init32(pblock, __offset+_PREG(6), (uchar *)gradY);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)XX+1*((width+(8u-1))/8u*8u)*4);
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)YY+1*((width+(8u-1))/8u*8u)*4);
   __vcop_pblock_init32(pblock, __offset+_PREG(12), (uchar *)XY+1*((width+(8u-1))/8u*8u)*4);
   __vcop_pblock_init16(pblock, __offset+_PREG(14), (((width+(8u-1))/8u*8u)*4));
   __vcop_pblock_init16(pblock, __offset+_PREG(15), (4*8u) -(((width+(8u-1))/8u*8u)*4)*(((height))-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(16), (srcPitch*2));
   __vcop_pblock_init16(pblock, __offset+_PREG(17), (2*8u) -(srcPitch*2)*(((height))-1u));
   __vcop_pblock_init32(pblock, __offset+_PREG(18), 0);
   __vcop_pblock_init32(pblock, __offset+_PREG(20), (uchar *)gradX);
   __offset += 20;

   /* Loop 2 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), ((( width + ((8u)-1))/(8u)))-1u);
   __vcop_pblock_init32(pblock, __offset+_PREG(6), (uchar *)XY+1*((width+(8u-1))/8u*8u)*4+(7-1)*((width+(8u-1))/8u*8u)*4);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)XX);
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)YY);
   __vcop_pblock_init32(pblock, __offset+_PREG(12), (uchar *)XY);
   __vcop_pblock_init16(pblock, __offset+_PREG(14), 32);
   __vcop_pblock_init32(pblock, __offset+_PREG(16), (uchar *)XX+1*((width+(8u-1))/8u*8u)*4+(7-1)*((width+(8u-1))/8u*8u)*4);
   __vcop_pblock_init32(pblock, __offset+_PREG(18), (uchar *)YY+1*((width+(8u-1))/8u*8u)*4+(7-1)*((width+(8u-1))/8u*8u)*4);
   __offset += 18;

   /* Loop 3 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), ((( width + ((8u)-1))/(8u)))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), ((height - (7-1) -1))-1u);
   __vcop_pblock_init32(pblock, __offset+_PREG(6), (uchar *)XY+1*((width+(8u-1))/8u*8u)*4);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)XX+1*((width+(8u-1))/8u*8u)*4+7*((width+(8u-1))/8u*8u)*4);
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)YY+1*((width+(8u-1))/8u*8u)*4+7*((width+(8u-1))/8u*8u)*4);
   __vcop_pblock_init32(pblock, __offset+_PREG(12), (uchar *)XY+1*((width+(8u-1))/8u*8u)*4+7*((width+(8u-1))/8u*8u)*4);
   __vcop_pblock_init16(pblock, __offset+_PREG(14), (((width+(8u-1))/8u*8u)*4));
   __vcop_pblock_init16(pblock, __offset+_PREG(15), (4*8u) -(((width+(8u-1))/8u*8u)*4)*(((height - (7-1) -1))-1u));
   __vcop_pblock_init32(pblock, __offset+_PREG(16), (uchar *)XX+1*((width+(8u-1))/8u*8u)*4);
   __vcop_pblock_init32(pblock, __offset+_PREG(18), (uchar *)YY+1*((width+(8u-1))/8u*8u)*4);
   __offset += 18;

   /* Loop 4 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), ((height - (7 - 1)))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), (( width- (7 - 1) + ((8u)-1))/(8u))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), (7)-1u);
   __vcop_pblock_init32(pblock, __offset+_PREG(6), (uchar *)XY);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)YY);
   __vcop_pblock_init16(pblock, __offset+_PREG(10), 32);
   __vcop_pblock_init16(pblock, __offset+_PREG(11), (dstPitch*4) -(4*8u)*((( width- (7 - 1) + ((8u)-1))/(8u))-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(12), 4);
   __vcop_pblock_init16(pblock, __offset+_PREG(13), 8);
   __vcop_pblock_init16(pblock, __offset+_PREG(14), (((width+(8u-1))/8u*8u)*4) -(4*8u)*((( width- (7 - 1) + ((8u)-1))/(8u))-1u) -(4)*((7)-1u));
   __vcop_pblock_init32(pblock, __offset+_PREG(16), 0);
   __vcop_pblock_init32(pblock, __offset+_PREG(18), (uchar *)XX);
   __offset += 18;

   return 74u;
}

void vcop_harrisScore_7x7_1_vloops(
   unsigned short pblock[])
{
   /* Kernel-wide Vector Registers */
   #pragma VCC_VREG("dx", 16);
   #pragma VCC_VREG("dx_old", 17);
   #pragma VCC_VREG("dy", 18);
   #pragma VCC_VREG("dy_old", 19);
   #pragma VCC_VREG("zxx", 20);
   #pragma VCC_VREG("zxxi", 21);
   #pragma VCC_VREG("zxy", 22);
   #pragma VCC_VREG("zxyi", 23);
   #pragma VCC_VREG("zyy", 24);
   #pragma VCC_VREG("zyyi", 25);

   __vcop_param(&pblock[0]);

   /* VLOOP 1 Start */

   /* VLOOP Local Vector Registers */
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("Addr1", "A0");
   #pragma EVE_REG("Addr3", "A1");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I1", "I3");
   #pragma EVE_REG("I2", "I4");
   

   __vcop_vloop(__vcop_compute(), 14u, 10u, 1u);
   __vcop_vinit(__vcop_sizeW(), __vcop_i4_zero(), _PREG(18), _VREG(20));
   __vcop_vinit(__vcop_sizeW(), __vcop_i4_zero(), _PREG(18), _VREG(24));
   __vcop_vinit(__vcop_sizeW(), __vcop_i4_zero(), _PREG(18), _VREG(22));
   __vcop_vagen(_AGEN(0), _PREG(14), _PREG(15), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(1), _PREG(16), _PREG(17), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeH(), __vcop_npt(), _PREG(20), _AGEN(1), _VREG(16), __vcop_alws());
   __vcop_vload(__vcop_sizeH(), __vcop_npt(), _PREG(6), _AGEN(1), _VREG(18), __vcop_alws());
   __vcop_vmadd(_VREG(16), _VREG(16), _VREG(20), _PREG(0));
   __vcop_vmadd(_VREG(16), _VREG(18), _VREG(22), _PREG(0));
   __vcop_vmadd(_VREG(18), _VREG(18), _VREG(24), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeW(), __vcop_npt(), __vcop_alws(), _VREG(20), _PREG(8), _AGEN(0), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeW(), __vcop_npt(), __vcop_alws(), _VREG(24), _PREG(10), _AGEN(0), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeW(), __vcop_npt(), __vcop_alws(), _VREG(22), _PREG(12), _AGEN(0), _PREG(0));
   __vcop_vloop_end(1u);

   /* VLOOP 2 Start */

   /* VLOOP Local Vector Registers */
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("Addr1", "A0");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I1", "I4");
   

   __vcop_vloop(__vcop_compute(), 8u, 9u, 2u);
   __vcop_vagen(_AGEN(0), _PREG(14), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeW(), __vcop_npt(), _PREG(16), _AGEN(0), _VREG(20), __vcop_alws());
   __vcop_vload(__vcop_sizeW(), __vcop_npt(), _PREG(18), _AGEN(0), _VREG(24), __vcop_alws());
   __vcop_vload(__vcop_sizeW(), __vcop_npt(), _PREG(6), _AGEN(0), _VREG(22), __vcop_alws());
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeW(), __vcop_npt(), __vcop_alws(), _VREG(20), _PREG(8), _AGEN(0), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeW(), __vcop_npt(), __vcop_alws(), _VREG(24), _PREG(10), _AGEN(0), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeW(), __vcop_npt(), __vcop_alws(), _VREG(22), _PREG(12), _AGEN(0), _PREG(0));
   __vcop_vloop_end(2u);

   /* VLOOP 3 Start */

   /* VLOOP Local Vector Registers */
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("Addr1", "A0");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I1", "I3");
   #pragma EVE_REG("I2", "I4");
   

   __vcop_vloop(__vcop_compute(), 14u, 9u, 3u);
   __vcop_vagen(_AGEN(0), _PREG(14), _PREG(15), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeW(), __vcop_npt(), _PREG(16), _AGEN(0), _VREG(20), __vcop_alws());
   __vcop_vload(__vcop_sizeW(), __vcop_npt(), _PREG(18), _AGEN(0), _VREG(24), __vcop_alws());
   __vcop_vload(__vcop_sizeW(), __vcop_npt(), _PREG(6), _AGEN(0), _VREG(22), __vcop_alws());
   __vcop_vload(__vcop_sizeW(), __vcop_npt(), _PREG(8), _AGEN(0), _VREG(21), __vcop_alws());
   __vcop_vload(__vcop_sizeW(), __vcop_npt(), _PREG(10), _AGEN(0), _VREG(25), __vcop_alws());
   __vcop_vload(__vcop_sizeW(), __vcop_npt(), _PREG(12), _AGEN(0), _VREG(23), __vcop_alws());
   __vcop_vsub(_VREG(21), _VREG(20), _VREG(21));
   __vcop_vsub(_VREG(25), _VREG(24), _VREG(25));
   __vcop_vsub(_VREG(23), _VREG(22), _VREG(23));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeW(), __vcop_npt(), __vcop_alws(), _VREG(21), _PREG(16), _AGEN(0), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeW(), __vcop_npt(), __vcop_alws(), _VREG(25), _PREG(18), _AGEN(0), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeW(), __vcop_npt(), __vcop_alws(), _VREG(23), _PREG(6), _AGEN(0), _PREG(0));
   __vcop_vloop_end(3u);

   /* VLOOP 4 Start */

   /* VLOOP Local Vector Registers */
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("Addr1", "A0");
   #pragma EVE_REG("Addr3", "A1");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I1", "I2");
   #pragma EVE_REG("I2", "I3");
   #pragma EVE_REG("I4", "I4");
   

   __vcop_vloop(__vcop_compute(), 15u, 9u, 4u);
   __vcop_vinit(__vcop_sizeW(), __vcop_i4_zero(), _PREG(16), _VREG(20));
   __vcop_vinit(__vcop_sizeW(), __vcop_i4_zero(), _PREG(16), _VREG(22));
   __vcop_vinit(__vcop_sizeW(), __vcop_i4_zero(), _PREG(16), _VREG(24));
   __vcop_vagen(_AGEN(0), _PREG(0), _PREG(10), _PREG(11), _PREG(0));
   __vcop_vagen(_AGEN(1), _PREG(12), _PREG(13), _PREG(14), _PREG(0));
   __vcop_vload(__vcop_sizeW(), __vcop_npt(), _PREG(18), _AGEN(1), _VREG(21), __vcop_alws());
   __vcop_vload(__vcop_sizeW(), __vcop_npt(), _PREG(6), _AGEN(1), _VREG(23), __vcop_alws());
   __vcop_vload(__vcop_sizeW(), __vcop_npt(), _PREG(8), _AGEN(1), _VREG(25), __vcop_alws());
   __vcop_vadd(_VREG(20), _VREG(21), _VREG(20));
   __vcop_vadd(_VREG(22), _VREG(23), _VREG(22));
   __vcop_vadd(_VREG(24), _VREG(25), _VREG(24));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeW(), __vcop_npt(), __vcop_last_i4(), _VREG(20), _PREG(18), _AGEN(0), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeW(), __vcop_npt(), __vcop_last_i4(), _VREG(24), _PREG(8), _AGEN(0), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeW(), __vcop_npt(), __vcop_last_i4(), _VREG(22), _PREG(6), _AGEN(0), _PREG(0));
   __vcop_vloop_end(4u);

}

void vcop_harrisScore_7x7_1(
   __vptr_int16 gradX,
   __vptr_int16 gradY,
   unsigned int width,
   unsigned int height,
   unsigned int srcPitch,
   unsigned int dstPitch,
   __vptr_int32 XX,
   __vptr_int32 YY,
   __vptr_int32 XY)
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_harrisScore_7x7_1_init(gradX, gradY, width, height, srcPitch, dstPitch, XX, YY, XY, __pblock_vcop_harrisScore_7x7_1);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_harrisScore_7x7_1_vloops(__pblock_vcop_harrisScore_7x7_1);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

void vcop_harrisScore_7x7_1_custom(
   __vptr_int16 gradX,
   __vptr_int16 gradY,
   unsigned int width,
   unsigned int height,
   unsigned int srcPitch,
   unsigned int dstPitch,
   __vptr_int32 XX,
   __vptr_int32 YY,
   __vptr_int32 XY,
   unsigned short pblock[])
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_harrisScore_7x7_1_init(gradX, gradY, width, height, srcPitch, dstPitch, XX, YY, XY, pblock);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_harrisScore_7x7_1_vloops(pblock);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

#pragma DATA_SECTION(__pblock_vcop_harrisScore_7x7_2, ".vcop_parameter_block")
#pragma DATA_ALIGN(__pblock_vcop_harrisScore_7x7_2, __ALIGNOF__(int));
unsigned short __pblock_vcop_harrisScore_7x7_2[78];

unsigned int vcop_harrisScore_7x7_2_param_count(void)
{
   return 78u;
}

unsigned int vcop_harrisScore_7x7_2_ctrl_count(void)
{
   return 0u;
}

unsigned int vcop_harrisScore_7x7_2_init(
   int width,
   int height,
   unsigned int srcPitch,
   unsigned int dstPitch,
   __vptr_int16 outm,
   unsigned short k,
   __vptr_int32 XX,
   __vptr_int32 YY,
   __vptr_int32 XY,
   __vptr_uint16 XXl,
   __vptr_uint16 YYl,
   __vptr_uint16 XYl,
   __vptr_int16 XXh,
   __vptr_int16 YYh,
   __vptr_int16 XYh,
   __vptr_uint32 detL,
   __vptr_int32 detH,
   unsigned short pblock[])
{
   int __offset = 0;
   /* Loop 1 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), (height)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), (((width + ((8u)-1))/ (8u)))-1u);
   __vcop_pblock_init32(pblock, __offset+_PREG(6), (uchar *)YYl);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)YYh);
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)XYl);
   __vcop_pblock_init32(pblock, __offset+_PREG(12), (uchar *)XYh);
   __vcop_pblock_init32(pblock, __offset+_PREG(14), 4294967295);
   __vcop_pblock_init32(pblock, __offset+_PREG(16), (uchar *)detL);
   __vcop_pblock_init32(pblock, __offset+_PREG(18), (uchar *)detH);
   __vcop_pblock_init16(pblock, __offset+_PREG(20), 32);
   __vcop_pblock_init16(pblock, __offset+_PREG(21), (srcPitch*4) -(4*8u)*((((width + ((8u)-1))/ (8u)))-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(22), (dstPitch*4) -(4*8u)*((((width + ((8u)-1))/ (8u)))-1u));
   __vcop_pblock_init32(pblock, __offset+_PREG(24), (uchar *)XXl);
   __vcop_pblock_init32(pblock, __offset+_PREG(26), (uchar *)XXh);
   __offset += 26;

   /* Loop 2 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), (height)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), (((width + ((8u)-1))/ (8u)))-1u);
   __vcop_pblock_init32(pblock, __offset+_PREG(6), (uchar *)detL);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)detH);
   __vcop_pblock_init32(pblock, __offset+_PREG(10), 4294967295);
   __vcop_pblock_init16(pblock, __offset+_PREG(12), 65535);
   __vcop_pblock_init16(pblock, __offset+_PREG(13), 32);
   __vcop_pblock_init32(pblock, __offset+_PREG(14), k);
   __vcop_pblock_init32(pblock, __offset+_PREG(16), 16);
   __vcop_pblock_init32(pblock, __offset+_PREG(18), -16);
   __vcop_pblock_init32(pblock, __offset+_PREG(20), -15);
   __vcop_pblock_init32(pblock, __offset+_PREG(22), 32);
   __vcop_pblock_init32(pblock, __offset+_PREG(24), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(26), (srcPitch*4) -(4*8u)*((((width + ((8u)-1))/ (8u)))-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(27), (dstPitch*4) -(4*8u)*((((width + ((8u)-1))/ (8u)))-1u));
   __vcop_pblock_init32(pblock, __offset+_PREG(28), (uchar *)XX);
   __vcop_pblock_init32(pblock, __offset+_PREG(30), (uchar *)YY);
   __offset += 30;

   /* Loop 3 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), (height)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), (((width + ((8u)-1))/ (8u)))-1u);
   __vcop_pblock_init32(pblock, __offset+_PREG(6), 10);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), 15);
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)detL);
   __vcop_pblock_init32(pblock, __offset+_PREG(12), (uchar *)detH);
   __vcop_pblock_init32(pblock, __offset+_PREG(14), (uchar *)outm);
   __vcop_pblock_init16(pblock, __offset+_PREG(16), 32);
   __vcop_pblock_init16(pblock, __offset+_PREG(17), (dstPitch*4) -(4*8u)*((((width + ((8u)-1))/ (8u)))-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(18), 16);
   __vcop_pblock_init16(pblock, __offset+_PREG(19), (dstPitch*2) -(2*8u)*((((width + ((8u)-1))/ (8u)))-1u));
   __vcop_pblock_init32(pblock, __offset+_PREG(20), 0);
   __vcop_pblock_init32(pblock, __offset+_PREG(22), 1);
   __offset += 22;

   return 78u;
}

void vcop_harrisScore_7x7_2_vloops(
   unsigned short pblock[])
{
   /* Kernel-wide Vector Registers */
   #pragma VCC_VREG("K", 16);
   #pragma VCC_VREG("Nexp", 17);
   #pragma VCC_VREG("ONE", 18);
   #pragma VCC_VREG("VA", 19);
   #pragma VCC_VREG("VB", 20);
   #pragma VCC_VREG("VC", 21);
   #pragma VCC_VREG("VD", 22);
   #pragma VCC_VREG("VK10", 23);
   #pragma VCC_VREG("VK15", 24);
   #pragma VCC_VREG("VK16", 25);
   #pragma VCC_VREG("VK32", 26);
   #pragma VCC_VREG("VM15", 27);
   #pragma VCC_VREG("VM16", 28);
   #pragma VCC_VREG("Vmask", 29);
   #pragma VCC_VREG("Vmask_s", 30);
   #pragma VCC_VREG("Vt1", 31);
   #pragma VCC_VREG("Vt2", 32);
   #pragma VCC_VREG("Vt2H", 33);
   #pragma VCC_VREG("Vt2L", 34);
   #pragma VCC_VREG("Vt3", 35);
   #pragma VCC_VREG("Vt3H", 36);
   #pragma VCC_VREG("Vt3L", 37);
   #pragma VCC_VREG("Vt4", 38);
   #pragma VCC_VREG("Vzero", 39);
   #pragma VCC_VREG("Z", 40);
   #pragma VCC_VREG("d", 41);
   #pragma VCC_VREG("d1", 42);
   #pragma VCC_VREG("d1_h", 43);
   #pragma VCC_VREG("d1_l", 44);
   #pragma VCC_VREG("d2", 45);
   #pragma VCC_VREG("d2_h", 46);
   #pragma VCC_VREG("d2_l", 47);
   #pragma VCC_VREG("d_h", 48);
   #pragma VCC_VREG("d_l", 49);
   #pragma VCC_VREG("dx", 50);
   #pragma VCC_VREG("dy", 51);
   #pragma VCC_VREG("exp", 52);
   #pragma VCC_VREG("frac", 53);
   #pragma VCC_VREG("lmb", 54);
   #pragma VCC_VREG("lmb_h", 55);
   #pragma VCC_VREG("lmb_l", 56);
   #pragma VCC_VREG("out", 57);
   #pragma VCC_VREG("s1", 58);
   #pragma VCC_VREG("s2", 59);
   #pragma VCC_VREG("t1", 60);
   #pragma VCC_VREG("t2", 61);
   #pragma VCC_VREG("t3", 62);
   #pragma VCC_VREG("t4", 63);
   #pragma VCC_VREG("trace", 64);
   #pragma VCC_VREG("trace2", 65);
   #pragma VCC_VREG("ts1", 66);
   #pragma VCC_VREG("ts2", 67);
   #pragma VCC_VREG("x", 68);
   #pragma VCC_VREG("y", 69);
   #pragma VCC_VREG("zxx", 70);
   #pragma VCC_VREG("zxxH", 71);
   #pragma VCC_VREG("zxxL", 72);
   #pragma VCC_VREG("zxy", 73);
   #pragma VCC_VREG("zxyH", 74);
   #pragma VCC_VREG("zxyL", 75);
   #pragma VCC_VREG("zyy", 76);
   #pragma VCC_VREG("zyyH", 77);
   #pragma VCC_VREG("zyyL", 78);

   __vcop_param(&pblock[0]);

   /* VLOOP 1 Start */

   /* VLOOP Local Vector Registers */
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("Addr1", "A0");
   #pragma EVE_REG("Addr2", "A1");
   #pragma EVE_REG("Addr3", "A2");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I1", "I3");
   #pragma EVE_REG("I2", "I4");
   

   __vcop_vloop(__vcop_compute(), 34u, 13u, 1u);
   __vcop_vinit(__vcop_sizeWU(), __vcop_alws(), _PREG(14), _VREG(29));
   __vcop_vagen(_AGEN(0), _PREG(20), _PREG(21), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(1), _PREG(20), _PREG(22), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeHU(), __vcop_ds2(), _PREG(24), _AGEN(0), _VREG(72), __vcop_alws());
   __vcop_vload(__vcop_sizeH(), __vcop_ds2(), _PREG(26), _AGEN(0), _VREG(71), __vcop_alws());
   __vcop_vload(__vcop_sizeHU(), __vcop_ds2(), _PREG(6), _AGEN(0), _VREG(78), __vcop_alws());
   __vcop_vload(__vcop_sizeH(), __vcop_ds2(), _PREG(8), _AGEN(0), _VREG(77), __vcop_alws());
   __vcop_vload(__vcop_sizeHU(), __vcop_ds2(), _PREG(10), _AGEN(0), _VREG(75), __vcop_alws());
   __vcop_vload(__vcop_sizeH(), __vcop_ds2(), _PREG(12), _AGEN(0), _VREG(74), __vcop_alws());
   __vcop_vmpy(_VREG(72), _VREG(77), _VREG(32), _PREG(0));
   __vcop_vmpy(_VREG(71), _VREG(78), _VREG(35), _PREG(0));
   __vcop_vmpy(_VREG(71), _VREG(77), _VREG(43), _PREG(0));
   __vcop_vmpy(_VREG(72), _VREG(78), _VREG(44), _PREG(0));
   __vcop_vshf16(_VREG(32), _VREG(34), _VREG(33));
   __vcop_vshf16(_VREG(35), _VREG(37), _VREG(36));
   __vcop_vadd3(_VREG(34), _VREG(37), _VREG(44));
   __vcop_vadd3(_VREG(33), _VREG(36), _VREG(43));
   __vcop_vaddh(_VREG(43), _VREG(44), _VREG(43));
   __vcop_vmpy(_VREG(75), _VREG(74), _VREG(32), _PREG(0));
   __vcop_vmpy(_VREG(74), _VREG(74), _VREG(46), _PREG(0));
   __vcop_vmpy(_VREG(75), _VREG(75), _VREG(47), _PREG(0));
   __vcop_vshf16(_VREG(32), _VREG(34), _VREG(33));
   __vcop_vadd3(_VREG(34), _VREG(34), _VREG(47));
   __vcop_vadd3(_VREG(33), _VREG(33), _VREG(46));
   __vcop_vaddh(_VREG(46), _VREG(47), _VREG(46));
   __vcop_vand(_VREG(44), _VREG(29), _VREG(44));
   __vcop_vand(_VREG(47), _VREG(29), _VREG(47));
   __vcop_vsub(_VREG(44), _VREG(47), _VREG(49));
   __vcop_vsub(_VREG(43), _VREG(46), _VREG(48));
   __vcop_vaddh(_VREG(48), _VREG(49), _VREG(48));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeWU(), __vcop_npt(), __vcop_alws(), _VREG(49), _PREG(16), _AGEN(1), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeW(), __vcop_npt(), __vcop_alws(), _VREG(48), _PREG(18), _AGEN(1), _PREG(0));
   __vcop_vloop_end(1u);

   /* VLOOP 2 Start */

   /* VLOOP Local Vector Registers */
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("Addr1", "A0");
   #pragma EVE_REG("Addr2", "A1");
   #pragma EVE_REG("Addr3", "A2");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I1", "I3");
   #pragma EVE_REG("I2", "I4");
   

   __vcop_vloop(__vcop_compute(), 57u, 15u, 2u);
   __vcop_vinit(__vcop_sizeWU(), __vcop_alws(), _PREG(10), _VREG(29));
   __vcop_vinit(__vcop_sizeHU(), __vcop_alws(), _PREG(12), _VREG(30));
   __vcop_vinit(__vcop_sizeW(), __vcop_alws(), _PREG(14), _VREG(16));
   __vcop_vinit(__vcop_sizeW(), __vcop_alws(), _PREG(16), _VREG(25));
   __vcop_vinit(__vcop_sizeW(), __vcop_alws(), _PREG(18), _VREG(28));
   __vcop_vinit(__vcop_sizeW(), __vcop_alws(), _PREG(20), _VREG(27));
   __vcop_vinit(__vcop_sizeW(), __vcop_alws(), _PREG(22), _VREG(26));
   __vcop_vinit(__vcop_sizeW(), __vcop_alws(), _PREG(24), _VREG(40));
   __vcop_vagen(_AGEN(0), _PREG(13), _PREG(26), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(1), _PREG(13), _PREG(27), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeW(), __vcop_npt(), _PREG(28), _AGEN(0), _VREG(70), __vcop_alws());
   __vcop_vload(__vcop_sizeW(), __vcop_npt(), _PREG(30), _AGEN(0), _VREG(76), __vcop_alws());
   __vcop_vload(__vcop_sizeWU(), __vcop_npt(), _PREG(6), _AGEN(1), _VREG(49), __vcop_alws());
   __vcop_vload(__vcop_sizeW(), __vcop_npt(), _PREG(8), _AGEN(1), _VREG(48), __vcop_alws());
   __vcop_vadd(_VREG(70), _VREG(76), _VREG(64));
   __vcop_vshf(_VREG(64), _VREG(28), _VREG(19));
   __vcop_vand(_VREG(64), _VREG(30), _VREG(20));
   __vcop_vmpy(_VREG(19), _VREG(16), _VREG(35), _PREG(0));
   __vcop_vmpy(_VREG(20), _VREG(16), _VREG(38), _PREG(0));
   __vcop_vshf(_VREG(35), _VREG(25), _VREG(37));
   __vcop_vshf(_VREG(35), _VREG(28), _VREG(43));
   __vcop_vand(_VREG(37), _VREG(29), _VREG(37));
   __vcop_vadd(_VREG(38), _VREG(37), _VREG(38));
   __vcop_vaddh(_VREG(43), _VREG(38), _VREG(43));
   __vcop_vand(_VREG(38), _VREG(29), _VREG(44));
   __vcop_vshf(_VREG(44), _VREG(27), _VREG(31));
   __vcop_vadd(_VREG(26), _VREG(27), _VREG(21));
   __vcop_vshf(_VREG(43), _VREG(21), _VREG(32));
   __vcop_vor(_VREG(31), _VREG(32), _VREG(47));
   __vcop_vand(_VREG(47), _VREG(29), _VREG(47));
   __vcop_vshf(_VREG(47), _VREG(28), _VREG(21));
   __vcop_vand(_VREG(47), _VREG(30), _VREG(22));
   __vcop_vmpy(_VREG(20), _VREG(21), _VREG(32), _PREG(0));
   __vcop_vmpy(_VREG(19), _VREG(22), _VREG(35), _PREG(0));
   __vcop_vshf16(_VREG(32), _VREG(34), _VREG(33));
   __vcop_vshf16(_VREG(35), _VREG(37), _VREG(36));
   __vcop_vmpy(_VREG(19), _VREG(21), _VREG(43), _PREG(0));
   __vcop_vmpy(_VREG(20), _VREG(22), _VREG(38), _PREG(0));
   __vcop_vadd3(_VREG(34), _VREG(37), _VREG(38));
   __vcop_vadd3(_VREG(33), _VREG(36), _VREG(43));
   __vcop_vaddh(_VREG(43), _VREG(38), _VREG(43));
   __vcop_vand(_VREG(38), _VREG(29), _VREG(44));
   __vcop_vcmpeq(_VREG(48), _VREG(43), _VREG(61));
   __vcop_vcmplt(_VREG(49), _VREG(44), _VREG(62));
   __vcop_vand(_VREG(61), _VREG(62), _VREG(60));
   __vcop_vcmplt(_VREG(48), _VREG(43), _VREG(62));
   __vcop_vor(_VREG(60), _VREG(62), _VREG(60));
   __vcop_vsub(_VREG(49), _VREG(44), _VREG(31));
   __vcop_vsub(_VREG(48), _VREG(43), _VREG(48));
   __vcop_vaddh(_VREG(48), _VREG(31), _VREG(48));
   __vcop_vand(_VREG(31), _VREG(29), _VREG(49));
   __vcop_vsel(_VREG(60), _VREG(40), _VREG(48));
   __vcop_vsel(_VREG(60), _VREG(40), _VREG(49));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeWU(), __vcop_npt(), __vcop_alws(), _VREG(49), _PREG(6), _AGEN(1), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeW(), __vcop_npt(), __vcop_alws(), _VREG(48), _PREG(8), _AGEN(1), _PREG(0));
   __vcop_vloop_end(2u);

   /* VLOOP 3 Start */

   /* VLOOP Local Vector Registers */
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("Addr1", "A0");
   #pragma EVE_REG("Addr2", "A1");
   #pragma EVE_REG("Addr3", "A2");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I1", "I3");
   #pragma EVE_REG("I2", "I4");
   

   __vcop_vloop(__vcop_compute(), 28u, 11u, 3u);
   __vcop_vinit(__vcop_sizeW(), __vcop_alws(), _PREG(20), _VREG(40));
   __vcop_vinit(__vcop_sizeW(), __vcop_alws(), _PREG(22), _VREG(18));
   __vcop_vinit(__vcop_sizeW(), __vcop_alws(), _PREG(6), _VREG(23));
   __vcop_vinit(__vcop_sizeW(), __vcop_alws(), _PREG(8), _VREG(24));
   __vcop_vagen(_AGEN(0), _PREG(16), _PREG(17), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(1), _PREG(18), _PREG(19), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeWU(), __vcop_npt(), _PREG(10), _AGEN(0), _VREG(49), __vcop_alws());
   __vcop_vload(__vcop_sizeW(), __vcop_npt(), _PREG(12), _AGEN(0), _VREG(48), __vcop_alws());
   __vcop_vlmbd(_VREG(49), _VREG(18), _VREG(21));
   __vcop_vlmbd(_VREG(48), _VREG(18), _VREG(22));
   __vcop_vadd(_VREG(21), _VREG(18), _VREG(21));
   __vcop_vadd(_VREG(22), _VREG(18), _VREG(22));
   __vcop_vcmpeq(_VREG(22), _VREG(40), _VREG(19));
   __vcop_vadd(_VREG(22), _VREG(26), _VREG(54));
   __vcop_vsel(_VREG(19), _VREG(21), _VREG(54));
   __vcop_vcmple(_VREG(54), _VREG(23), _VREG(19));
   __vcop_vsub(_VREG(54), _VREG(23), _VREG(52));
   __vcop_vsel(_VREG(19), _VREG(40), _VREG(52));
   __vcop_vsub(_VREG(40), _VREG(52), _VREG(17));
   __vcop_vshf(_VREG(48), _VREG(17), _VREG(43));
   __vcop_vshf(_VREG(49), _VREG(17), _VREG(44));
   __vcop_vsub(_VREG(26), _VREG(52), _VREG(20));
   __vcop_vshfor(_VREG(48), _VREG(20), _VREG(44));
   __vcop_vor(_VREG(44), _VREG(43), _VREG(44));
   __vcop_vshfor(_VREG(52), _VREG(23), _VREG(44));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeH(), __vcop_npt(), __vcop_alws(), _VREG(44), _PREG(14), _AGEN(1), _PREG(0));
   __vcop_vloop_end(3u);

}

void vcop_harrisScore_7x7_2(
   int width,
   int height,
   unsigned int srcPitch,
   unsigned int dstPitch,
   __vptr_int16 outm,
   unsigned short k,
   __vptr_int32 XX,
   __vptr_int32 YY,
   __vptr_int32 XY,
   __vptr_uint16 XXl,
   __vptr_uint16 YYl,
   __vptr_uint16 XYl,
   __vptr_int16 XXh,
   __vptr_int16 YYh,
   __vptr_int16 XYh,
   __vptr_uint32 detL,
   __vptr_int32 detH)
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_harrisScore_7x7_2_init(width, height, srcPitch, dstPitch, outm, k, XX, YY, XY, XXl, YYl, XYl, XXh, YYh, XYh, detL, detH, __pblock_vcop_harrisScore_7x7_2);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_harrisScore_7x7_2_vloops(__pblock_vcop_harrisScore_7x7_2);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

void vcop_harrisScore_7x7_2_custom(
   int width,
   int height,
   unsigned int srcPitch,
   unsigned int dstPitch,
   __vptr_int16 outm,
   unsigned short k,
   __vptr_int32 XX,
   __vptr_int32 YY,
   __vptr_int32 XY,
   __vptr_uint16 XXl,
   __vptr_uint16 YYl,
   __vptr_uint16 XYl,
   __vptr_int16 XXh,
   __vptr_int16 YYh,
   __vptr_int16 XYh,
   __vptr_uint32 detL,
   __vptr_int32 detH,
   unsigned short pblock[])
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_harrisScore_7x7_2_init(width, height, srcPitch, dstPitch, outm, k, XX, YY, XY, XXl, YYl, XYl, XXh, YYh, XYh, detL, detH, pblock);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_harrisScore_7x7_2_vloops(pblock);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

