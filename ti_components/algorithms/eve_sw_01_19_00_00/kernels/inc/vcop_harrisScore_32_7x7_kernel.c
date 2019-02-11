#include <vcop\vcop.h>

typedef unsigned char uchar;

#pragma DATA_SECTION(__pblock_vcop_harrisScore_32_7x7_1, ".vcop_parameter_block")
#pragma DATA_ALIGN(__pblock_vcop_harrisScore_32_7x7_1, __ALIGNOF__(int));
unsigned short __pblock_vcop_harrisScore_32_7x7_1[74];

unsigned int vcop_harrisScore_32_7x7_1_param_count(void)
{
   return 74u;
}

unsigned int vcop_harrisScore_32_7x7_1_ctrl_count(void)
{
   return 0u;
}

unsigned int vcop_harrisScore_32_7x7_1_init(
   __vptr_int16 gradX,
   __vptr_int16 gradY,
   unsigned int width,
   unsigned int height,
   unsigned int srcPitch,
   unsigned int dstPitch,
   unsigned char windowSize,
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
   __vcop_pblock_init32(pblock, __offset+_PREG(6), (uchar *)XY+1*((width+(8u-1))/8u*8u)*4+(windowSize-1)*((width+(8u-1))/8u*8u)*4);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)XX);
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)YY);
   __vcop_pblock_init32(pblock, __offset+_PREG(12), (uchar *)XY);
   __vcop_pblock_init16(pblock, __offset+_PREG(14), 32);
   __vcop_pblock_init32(pblock, __offset+_PREG(16), (uchar *)XX+1*((width+(8u-1))/8u*8u)*4+(windowSize-1)*((width+(8u-1))/8u*8u)*4);
   __vcop_pblock_init32(pblock, __offset+_PREG(18), (uchar *)YY+1*((width+(8u-1))/8u*8u)*4+(windowSize-1)*((width+(8u-1))/8u*8u)*4);
   __offset += 18;

   /* Loop 3 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), ((( width + ((8u)-1))/(8u)))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), ((height - (windowSize-1) -1))-1u);
   __vcop_pblock_init32(pblock, __offset+_PREG(6), (uchar *)XY+1*((width+(8u-1))/8u*8u)*4);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)XX+1*((width+(8u-1))/8u*8u)*4+windowSize*((width+(8u-1))/8u*8u)*4);
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)YY+1*((width+(8u-1))/8u*8u)*4+windowSize*((width+(8u-1))/8u*8u)*4);
   __vcop_pblock_init32(pblock, __offset+_PREG(12), (uchar *)XY+1*((width+(8u-1))/8u*8u)*4+windowSize*((width+(8u-1))/8u*8u)*4);
   __vcop_pblock_init16(pblock, __offset+_PREG(14), (((width+(8u-1))/8u*8u)*4));
   __vcop_pblock_init16(pblock, __offset+_PREG(15), (4*8u) -(((width+(8u-1))/8u*8u)*4)*(((height - (windowSize-1) -1))-1u));
   __vcop_pblock_init32(pblock, __offset+_PREG(16), (uchar *)XX+1*((width+(8u-1))/8u*8u)*4);
   __vcop_pblock_init32(pblock, __offset+_PREG(18), (uchar *)YY+1*((width+(8u-1))/8u*8u)*4);
   __offset += 18;

   /* Loop 4 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), ((height - (windowSize - 1)))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), (( width- (windowSize - 1) + ((8u)-1))/(8u))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), (windowSize)-1u);
   __vcop_pblock_init32(pblock, __offset+_PREG(6), (uchar *)XY);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)YY);
   __vcop_pblock_init16(pblock, __offset+_PREG(10), 32);
   __vcop_pblock_init16(pblock, __offset+_PREG(11), (dstPitch*4) -(4*8u)*((( width- (windowSize - 1) + ((8u)-1))/(8u))-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(12), 4);
   __vcop_pblock_init16(pblock, __offset+_PREG(13), (4*8u) -(4)*((windowSize)-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(14), (((width+(8u-1))/8u*8u)*4) -(4*8u)*((( width- (windowSize - 1) + ((8u)-1))/(8u))-1u) -(4)*((windowSize)-1u));
   __vcop_pblock_init32(pblock, __offset+_PREG(16), 0);
   __vcop_pblock_init32(pblock, __offset+_PREG(18), (uchar *)XX);
   __offset += 18;

   return 74u;
}

void vcop_harrisScore_32_7x7_1_vloops(
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
   #pragma EVE_REG("Addr2", "A1");
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
   #pragma EVE_REG("Addr2", "A1");
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

void vcop_harrisScore_32_7x7_1(
   __vptr_int16 gradX,
   __vptr_int16 gradY,
   unsigned int width,
   unsigned int height,
   unsigned int srcPitch,
   unsigned int dstPitch,
   unsigned char windowSize,
   __vptr_int32 XX,
   __vptr_int32 YY,
   __vptr_int32 XY)
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_harrisScore_32_7x7_1_init(gradX, gradY, width, height, srcPitch, dstPitch, windowSize, XX, YY, XY, __pblock_vcop_harrisScore_32_7x7_1);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_harrisScore_32_7x7_1_vloops(__pblock_vcop_harrisScore_32_7x7_1);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

void vcop_harrisScore_32_7x7_1_custom(
   __vptr_int16 gradX,
   __vptr_int16 gradY,
   unsigned int width,
   unsigned int height,
   unsigned int srcPitch,
   unsigned int dstPitch,
   unsigned char windowSize,
   __vptr_int32 XX,
   __vptr_int32 YY,
   __vptr_int32 XY,
   unsigned short pblock[])
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_harrisScore_32_7x7_1_init(gradX, gradY, width, height, srcPitch, dstPitch, windowSize, XX, YY, XY, pblock);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_harrisScore_32_7x7_1_vloops(pblock);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

#pragma DATA_SECTION(__pblock_vcop_harrisScore_32_7x7_2, ".vcop_parameter_block")
#pragma DATA_ALIGN(__pblock_vcop_harrisScore_32_7x7_2, __ALIGNOF__(int));
unsigned short __pblock_vcop_harrisScore_32_7x7_2[84];

unsigned int vcop_harrisScore_32_7x7_2_param_count(void)
{
   return 84u;
}

unsigned int vcop_harrisScore_32_7x7_2_ctrl_count(void)
{
   return 0u;
}

unsigned int vcop_harrisScore_32_7x7_2_init(
   int width,
   int height,
   unsigned int srcPitch,
   unsigned int dstPitch,
   __vptr_int32 outm,
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
   __vcop_pblock_init32(pblock, __offset+_PREG(6), 8);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (26));
   __vcop_pblock_init32(pblock, __offset+_PREG(10), ( (1 << (26)) - 1 ));
   __vcop_pblock_init32(pblock, __offset+_PREG(12), 4278190080);
   __vcop_pblock_init32(pblock, __offset+_PREG(14), 4294967295);
   __vcop_pblock_init32(pblock, __offset+_PREG(16), 31);
   __vcop_pblock_init32(pblock, __offset+_PREG(18), (uchar *)detL);
   __vcop_pblock_init32(pblock, __offset+_PREG(20), (uchar *)detH);
   __vcop_pblock_init32(pblock, __offset+_PREG(22), (uchar *)outm);
   __vcop_pblock_init16(pblock, __offset+_PREG(24), 32);
   __vcop_pblock_init16(pblock, __offset+_PREG(25), (dstPitch*4) -(4*8u)*((((width + ((8u)-1))/ (8u)))-1u));
   __vcop_pblock_init32(pblock, __offset+_PREG(26), 0);
   __vcop_pblock_init32(pblock, __offset+_PREG(28), 1);
   __offset += 28;

   return 84u;
}

void vcop_harrisScore_32_7x7_2_vloops(
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
   #pragma VCC_VREG("VK16", 23);
   #pragma VCC_VREG("VK27", 24);
   #pragma VCC_VREG("VK32", 25);
   #pragma VCC_VREG("VM15", 26);
   #pragma VCC_VREG("VM16", 27);
   #pragma VCC_VREG("Vmask", 28);
   #pragma VCC_VREG("Vmask_s", 29);
   #pragma VCC_VREG("Vt1", 30);
   #pragma VCC_VREG("Vt2", 31);
   #pragma VCC_VREG("Vt2H", 32);
   #pragma VCC_VREG("Vt2L", 33);
   #pragma VCC_VREG("Vt3", 34);
   #pragma VCC_VREG("Vt3H", 35);
   #pragma VCC_VREG("Vt3L", 36);
   #pragma VCC_VREG("Vt4", 37);
   #pragma VCC_VREG("Vzero", 38);
   #pragma VCC_VREG("Z", 39);
   #pragma VCC_VREG("d", 40);
   #pragma VCC_VREG("d1", 41);
   #pragma VCC_VREG("d1_h", 42);
   #pragma VCC_VREG("d1_l", 43);
   #pragma VCC_VREG("d2", 44);
   #pragma VCC_VREG("d2_h", 45);
   #pragma VCC_VREG("d2_l", 46);
   #pragma VCC_VREG("d_h", 47);
   #pragma VCC_VREG("d_l", 48);
   #pragma VCC_VREG("dx", 49);
   #pragma VCC_VREG("dy", 50);
   #pragma VCC_VREG("exp", 51);
   #pragma VCC_VREG("frac", 52);
   #pragma VCC_VREG("lmb", 53);
   #pragma VCC_VREG("lmb_h", 54);
   #pragma VCC_VREG("lmb_l", 55);
   #pragma VCC_VREG("out", 56);
   #pragma VCC_VREG("s1", 57);
   #pragma VCC_VREG("s2", 58);
   #pragma VCC_VREG("t1", 59);
   #pragma VCC_VREG("t2", 60);
   #pragma VCC_VREG("t3", 61);
   #pragma VCC_VREG("t4", 62);
   #pragma VCC_VREG("trace", 63);
   #pragma VCC_VREG("trace2", 64);
   #pragma VCC_VREG("ts1", 65);
   #pragma VCC_VREG("ts2", 66);
   #pragma VCC_VREG("x", 67);
   #pragma VCC_VREG("y", 68);
   #pragma VCC_VREG("zxx", 69);
   #pragma VCC_VREG("zxxH", 70);
   #pragma VCC_VREG("zxxL", 71);
   #pragma VCC_VREG("zxy", 72);
   #pragma VCC_VREG("zxyH", 73);
   #pragma VCC_VREG("zxyL", 74);
   #pragma VCC_VREG("zyy", 75);
   #pragma VCC_VREG("zyyH", 76);
   #pragma VCC_VREG("zyyL", 77);

   __vcop_param(&pblock[0]);

   /* VLOOP 1 Start */

   /* VLOOP Local Vector Registers */
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("Addr1", "A0");
   #pragma EVE_REG("Addr2", "A1");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I1", "I3");
   #pragma EVE_REG("I2", "I4");
   

   __vcop_vloop(__vcop_compute(), 33u, 13u, 1u);
   __vcop_vinit(__vcop_sizeWU(), __vcop_alws(), _PREG(14), _VREG(28));
   __vcop_vagen(_AGEN(0), _PREG(20), _PREG(21), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(1), _PREG(20), _PREG(22), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeHU(), __vcop_ds2(), _PREG(24), _AGEN(0), _VREG(71), __vcop_alws());
   __vcop_vload(__vcop_sizeH(), __vcop_ds2(), _PREG(26), _AGEN(0), _VREG(70), __vcop_alws());
   __vcop_vload(__vcop_sizeHU(), __vcop_ds2(), _PREG(6), _AGEN(0), _VREG(77), __vcop_alws());
   __vcop_vload(__vcop_sizeH(), __vcop_ds2(), _PREG(8), _AGEN(0), _VREG(76), __vcop_alws());
   __vcop_vload(__vcop_sizeHU(), __vcop_ds2(), _PREG(10), _AGEN(0), _VREG(74), __vcop_alws());
   __vcop_vload(__vcop_sizeH(), __vcop_ds2(), _PREG(12), _AGEN(0), _VREG(73), __vcop_alws());
   __vcop_vmpy(_VREG(71), _VREG(76), _VREG(31), _PREG(0));
   __vcop_vmpy(_VREG(70), _VREG(77), _VREG(34), _PREG(0));
   __vcop_vmpy(_VREG(70), _VREG(76), _VREG(42), _PREG(0));
   __vcop_vmpy(_VREG(71), _VREG(77), _VREG(43), _PREG(0));
   __vcop_vshf16(_VREG(31), _VREG(33), _VREG(32));
   __vcop_vshf16(_VREG(34), _VREG(36), _VREG(35));
   __vcop_vadd3(_VREG(33), _VREG(36), _VREG(43));
   __vcop_vadd3(_VREG(32), _VREG(35), _VREG(42));
   __vcop_vaddh(_VREG(42), _VREG(43), _VREG(42));
   __vcop_vmpy(_VREG(74), _VREG(73), _VREG(31), _PREG(0));
   __vcop_vmpy(_VREG(73), _VREG(73), _VREG(45), _PREG(0));
   __vcop_vmpy(_VREG(74), _VREG(74), _VREG(46), _PREG(0));
   __vcop_vshf16(_VREG(31), _VREG(33), _VREG(32));
   __vcop_vadd3(_VREG(33), _VREG(33), _VREG(46));
   __vcop_vadd3(_VREG(32), _VREG(32), _VREG(45));
   __vcop_vaddh(_VREG(45), _VREG(46), _VREG(45));
   __vcop_vand(_VREG(43), _VREG(28), _VREG(43));
   __vcop_vand(_VREG(46), _VREG(28), _VREG(46));
   __vcop_vsub(_VREG(43), _VREG(46), _VREG(48));
   __vcop_vsub(_VREG(42), _VREG(45), _VREG(47));
   __vcop_vaddh(_VREG(47), _VREG(48), _VREG(47));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeWU(), __vcop_npt(), __vcop_alws(), _VREG(48), _PREG(16), _AGEN(1), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeW(), __vcop_npt(), __vcop_alws(), _VREG(47), _PREG(18), _AGEN(1), _PREG(0));
   __vcop_vloop_end(1u);

   /* VLOOP 2 Start */

   /* VLOOP Local Vector Registers */
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("Addr1", "A0");
   #pragma EVE_REG("Addr2", "A1");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I1", "I3");
   #pragma EVE_REG("I2", "I4");
   

   __vcop_vloop(__vcop_compute(), 49u, 15u, 2u);
   __vcop_vinit(__vcop_sizeWU(), __vcop_alws(), _PREG(10), _VREG(28));
   __vcop_vinit(__vcop_sizeHU(), __vcop_alws(), _PREG(12), _VREG(29));
   __vcop_vinit(__vcop_sizeW(), __vcop_alws(), _PREG(14), _VREG(16));
   __vcop_vinit(__vcop_sizeW(), __vcop_alws(), _PREG(16), _VREG(23));
   __vcop_vinit(__vcop_sizeW(), __vcop_alws(), _PREG(18), _VREG(27));
   __vcop_vinit(__vcop_sizeW(), __vcop_alws(), _PREG(20), _VREG(26));
   __vcop_vinit(__vcop_sizeW(), __vcop_alws(), _PREG(22), _VREG(25));
   __vcop_vinit(__vcop_sizeW(), __vcop_alws(), _PREG(24), _VREG(39));
   __vcop_vagen(_AGEN(0), _PREG(13), _PREG(26), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(1), _PREG(13), _PREG(27), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeW(), __vcop_npt(), _PREG(28), _AGEN(0), _VREG(69), __vcop_alws());
   __vcop_vload(__vcop_sizeW(), __vcop_npt(), _PREG(30), _AGEN(0), _VREG(75), __vcop_alws());
   __vcop_vload(__vcop_sizeWU(), __vcop_npt(), _PREG(6), _AGEN(1), _VREG(48), __vcop_alws());
   __vcop_vload(__vcop_sizeW(), __vcop_npt(), _PREG(8), _AGEN(1), _VREG(47), __vcop_alws());
   __vcop_vadd(_VREG(69), _VREG(75), _VREG(63));
   __vcop_vshf(_VREG(63), _VREG(27), _VREG(19));
   __vcop_vand(_VREG(63), _VREG(29), _VREG(20));
   __vcop_vmpy(_VREG(19), _VREG(16), _VREG(34), _PREG(0));
   __vcop_vmpy(_VREG(20), _VREG(16), _VREG(37), _PREG(0));
   __vcop_vshf(_VREG(34), _VREG(23), _VREG(36));
   __vcop_vshf(_VREG(34), _VREG(27), _VREG(42));
   __vcop_vand(_VREG(36), _VREG(28), _VREG(36));
   __vcop_vadd(_VREG(37), _VREG(36), _VREG(37));
   __vcop_vaddh(_VREG(42), _VREG(37), _VREG(42));
   __vcop_vand(_VREG(37), _VREG(28), _VREG(43));
   __vcop_vshf(_VREG(43), _VREG(26), _VREG(30));
   __vcop_vadd(_VREG(25), _VREG(26), _VREG(21));
   __vcop_vshf(_VREG(42), _VREG(21), _VREG(31));
   __vcop_vor(_VREG(30), _VREG(31), _VREG(46));
   __vcop_vand(_VREG(46), _VREG(28), _VREG(46));
   __vcop_vshf(_VREG(46), _VREG(27), _VREG(21));
   __vcop_vand(_VREG(46), _VREG(29), _VREG(22));
   __vcop_vmpy(_VREG(20), _VREG(21), _VREG(31), _PREG(0));
   __vcop_vmpy(_VREG(19), _VREG(22), _VREG(34), _PREG(0));
   __vcop_vshf16(_VREG(31), _VREG(33), _VREG(32));
   __vcop_vshf16(_VREG(34), _VREG(36), _VREG(35));
   __vcop_vmpy(_VREG(19), _VREG(21), _VREG(42), _PREG(0));
   __vcop_vmpy(_VREG(20), _VREG(22), _VREG(37), _PREG(0));
   __vcop_vadd3(_VREG(33), _VREG(36), _VREG(37));
   __vcop_vadd3(_VREG(32), _VREG(35), _VREG(42));
   __vcop_vaddh(_VREG(42), _VREG(37), _VREG(42));
   __vcop_vand(_VREG(37), _VREG(28), _VREG(43));
   __vcop_vsub(_VREG(48), _VREG(43), _VREG(30));
   __vcop_vsub(_VREG(47), _VREG(42), _VREG(47));
   __vcop_vaddh(_VREG(47), _VREG(30), _VREG(47));
   __vcop_vand(_VREG(30), _VREG(28), _VREG(48));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeWU(), __vcop_npt(), __vcop_alws(), _VREG(48), _PREG(6), _AGEN(1), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeW(), __vcop_npt(), __vcop_alws(), _VREG(47), _PREG(8), _AGEN(1), _PREG(0));
   __vcop_vloop_end(2u);

   /* VLOOP 3 Start */

   /* VLOOP Local Vector Registers */
   #pragma VCC_VREG("VK31", 78);
   #pragma VCC_VREG("VK8", 79);
   #pragma VCC_VREG("V_MantisaMask", 80);
   #pragma VCC_VREG("V_negExp", 81);
   #pragma VCC_VREG("V_negMask", 82);
   #pragma VCC_VREG("V_signExtendedL", 83);
   #pragma VCC_VREG("V_tempH", 84);
   #pragma VCC_VREG("V_tempL", 85);
   #pragma VCC_VREG("VmantisaBit", 86);
   #pragma VCC_VREG("Vtemp", 87);
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("Addr1", "A0");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I1", "I3");
   #pragma EVE_REG("I2", "I4");
   

   __vcop_vloop(__vcop_compute(), 43u, 14u, 3u);
   __vcop_vinit(__vcop_sizeW(), __vcop_alws(), _PREG(26), _VREG(39));
   __vcop_vinit(__vcop_sizeW(), __vcop_alws(), _PREG(28), _VREG(18));
   __vcop_vinit(__vcop_sizeW(), __vcop_alws(), _PREG(6), _VREG(79));
   __vcop_vinit(__vcop_sizeW(), __vcop_alws(), _PREG(8), _VREG(86));
   __vcop_vinit(__vcop_sizeW(), __vcop_alws(), _PREG(10), _VREG(80));
   __vcop_vinit(__vcop_sizeWU(), __vcop_alws(), _PREG(12), _VREG(83));
   __vcop_vinit(__vcop_sizeWU(), __vcop_alws(), _PREG(14), _VREG(28));
   __vcop_vinit(__vcop_sizeW(), __vcop_alws(), _PREG(16), _VREG(78));
   __vcop_vagen(_AGEN(0), _PREG(24), _PREG(25), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeWU(), __vcop_npt(), _PREG(18), _AGEN(0), _VREG(48), __vcop_alws());
   __vcop_vload(__vcop_sizeW(), __vcop_npt(), _PREG(20), _AGEN(0), _VREG(47), __vcop_alws());
   __vcop_vshf(_VREG(83), _VREG(79), _VREG(83));
   __vcop_vabs(_VREG(47), _VREG(87));
   __vcop_vxor(_VREG(47), _VREG(87), _VREG(82));
   __vcop_vlmbd(_VREG(48), _VREG(18), _VREG(21));
   __vcop_vlmbd(_VREG(47), _VREG(18), _VREG(22));
   __vcop_vor(_VREG(83), _VREG(48), _VREG(83));
   __vcop_vlmbd(_VREG(83), _VREG(39), _VREG(85));
   __vcop_vlmbd(_VREG(47), _VREG(39), _VREG(84));
   __vcop_vsel(_VREG(82), _VREG(85), _VREG(21));
   __vcop_vsel(_VREG(82), _VREG(84), _VREG(22));
   __vcop_vadd(_VREG(21), _VREG(18), _VREG(21));
   __vcop_vadd(_VREG(22), _VREG(18), _VREG(22));
   __vcop_vcmpeq(_VREG(22), _VREG(39), _VREG(19));
   __vcop_vadd(_VREG(22), _VREG(25), _VREG(53));
   __vcop_vsel(_VREG(19), _VREG(21), _VREG(53));
   __vcop_vcmple(_VREG(53), _VREG(86), _VREG(19));
   __vcop_vsub(_VREG(53), _VREG(86), _VREG(51));
   __vcop_vsel(_VREG(19), _VREG(39), _VREG(51));
   __vcop_vsub(_VREG(39), _VREG(51), _VREG(17));
   __vcop_vshf(_VREG(47), _VREG(17), _VREG(42));
   __vcop_vshf(_VREG(48), _VREG(17), _VREG(43));
   __vcop_vsub(_VREG(25), _VREG(51), _VREG(20));
   __vcop_vcmpeq(_VREG(20), _VREG(25), _VREG(19));
   __vcop_vsel(_VREG(19), _VREG(78), _VREG(20));
   __vcop_vshfor(_VREG(47), _VREG(20), _VREG(43));
   __vcop_vadd(_VREG(51), _VREG(18), _VREG(17));
   __vcop_vsub(_VREG(39), _VREG(17), _VREG(81));
   __vcop_vsel(_VREG(82), _VREG(81), _VREG(51));
   __vcop_vand(_VREG(43), _VREG(80), _VREG(43));
   __vcop_vshfor(_VREG(51), _VREG(86), _VREG(43));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeW(), __vcop_npt(), __vcop_alws(), _VREG(43), _PREG(22), _AGEN(0), _PREG(0));
   __vcop_vloop_end(3u);

}

void vcop_harrisScore_32_7x7_2(
   int width,
   int height,
   unsigned int srcPitch,
   unsigned int dstPitch,
   __vptr_int32 outm,
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
   vcop_harrisScore_32_7x7_2_init(width, height, srcPitch, dstPitch, outm, k, XX, YY, XY, XXl, YYl, XYl, XXh, YYh, XYh, detL, detH, __pblock_vcop_harrisScore_32_7x7_2);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_harrisScore_32_7x7_2_vloops(__pblock_vcop_harrisScore_32_7x7_2);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

void vcop_harrisScore_32_7x7_2_custom(
   int width,
   int height,
   unsigned int srcPitch,
   unsigned int dstPitch,
   __vptr_int32 outm,
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
   vcop_harrisScore_32_7x7_2_init(width, height, srcPitch, dstPitch, outm, k, XX, YY, XY, XXl, YYl, XYl, XXh, YYh, XYh, detL, detH, pblock);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_harrisScore_32_7x7_2_vloops(pblock);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

#pragma DATA_SECTION(__pblock_vcop_harrisScore_32_methodB, ".vcop_parameter_block")
#pragma DATA_ALIGN(__pblock_vcop_harrisScore_32_methodB, __ALIGNOF__(int));
unsigned short __pblock_vcop_harrisScore_32_methodB[64];

unsigned int vcop_harrisScore_32_methodB_param_count(void)
{
   return 64u;
}

unsigned int vcop_harrisScore_32_methodB_ctrl_count(void)
{
   return 0u;
}

unsigned int vcop_harrisScore_32_methodB_init(
   __vptr_int16 gradX,
   __vptr_int16 gradY,
   __vptr_uint32 scratchXX,
   __vptr_uint32 scratchYY,
   unsigned short inBlockWidth,
   unsigned short inBlockHeight,
   unsigned short srcPitch,
   unsigned short dstPitch,
   unsigned char windowSize,
   __vptr_uint32 outm,
   unsigned short pblock[])
{
   int __offset = 0;
   /* Loop 1 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), ((((inBlockWidth) + (8u)-1) & ~((8u)-1))/ (8u))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), (inBlockHeight)-1u);
   __vcop_pblock_init32(pblock, __offset+_PREG(6), (uchar *)gradY);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)scratchXX+1*(inBlockWidth+8u-1&~(8u-1))*sizeof(*scratchXX));
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)scratchYY+1*(inBlockWidth+8u-1&~(8u-1))*sizeof(*scratchXX));
   __vcop_pblock_init16(pblock, __offset+_PREG(12), (srcPitch*sizeof(*gradX)));
   __vcop_pblock_init16(pblock, __offset+_PREG(13), (8u*sizeof(*gradX)) -(srcPitch*sizeof(*gradX))*((inBlockHeight)-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(14), ((inBlockWidth+8u-1&~(8u-1))*sizeof(*scratchXX)));
   __vcop_pblock_init16(pblock, __offset+_PREG(15), (sizeof(*scratchXX)*8u) -((inBlockWidth+8u-1&~(8u-1))*sizeof(*scratchXX))*((inBlockHeight)-1u));
   __vcop_pblock_init32(pblock, __offset+_PREG(16), 0);
   __vcop_pblock_init32(pblock, __offset+_PREG(18), (uchar *)gradX);
   __offset += 18;

   /* Loop 2 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), ((((inBlockWidth) + (8u)-1) & ~((8u)-1))/ (8u))-1u);
   __vcop_pblock_init32(pblock, __offset+_PREG(6), (uchar *)scratchXX);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)scratchYY);
   __vcop_pblock_init16(pblock, __offset+_PREG(10), 32);
   __vcop_pblock_init32(pblock, __offset+_PREG(12), (uchar *)scratchXX+(windowSize-1+1)*(inBlockWidth+8u-1&~(8u-1))*sizeof(*scratchXX));
   __vcop_pblock_init32(pblock, __offset+_PREG(14), (uchar *)scratchYY+(windowSize-1+1)*(inBlockWidth+8u-1&~(8u-1))*sizeof(*scratchXX));
   __offset += 14;

   /* Loop 3 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), ((((inBlockWidth) + (8u)-1) & ~((8u)-1))/ (8u))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), ((inBlockHeight - (windowSize-1) - 1))-1u);
   __vcop_pblock_init32(pblock, __offset+_PREG(6), (uchar *)scratchXX+1*(inBlockWidth+8u-1&~(8u-1))*sizeof(*scratchXX)+windowSize*(inBlockWidth+8u-1&~(8u-1))*sizeof(*scratchXX));
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)scratchYY+1*(inBlockWidth+8u-1&~(8u-1))*sizeof(*scratchXX)+windowSize*(inBlockWidth+8u-1&~(8u-1))*sizeof(*scratchXX));
   __vcop_pblock_init16(pblock, __offset+_PREG(10), ((inBlockWidth+8u-1&~(8u-1))*sizeof(*scratchXX)));
   __vcop_pblock_init16(pblock, __offset+_PREG(11), (8u*sizeof(*scratchXX)) -((inBlockWidth+8u-1&~(8u-1))*sizeof(*scratchXX))*(((inBlockHeight - (windowSize-1) - 1))-1u));
   __vcop_pblock_init32(pblock, __offset+_PREG(12), (uchar *)scratchXX+1*(inBlockWidth+8u-1&~(8u-1))*sizeof(*scratchXX));
   __vcop_pblock_init32(pblock, __offset+_PREG(14), (uchar *)scratchYY+1*(inBlockWidth+8u-1&~(8u-1))*sizeof(*scratchXX));
   __offset += 14;

   /* Loop 4 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), ((inBlockHeight - (windowSize - 1)))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), ((((inBlockWidth - (windowSize - 1)) + (8u)-1) & ~((8u)-1))/(8u))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), (windowSize)-1u);
   __vcop_pblock_init32(pblock, __offset+_PREG(6), (uchar *)scratchYY);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)outm);
   __vcop_pblock_init16(pblock, __offset+_PREG(10), 32);
   __vcop_pblock_init16(pblock, __offset+_PREG(11), (dstPitch*sizeof(*outm)) -(sizeof(*outm)*8u)*(((((inBlockWidth - (windowSize - 1)) + (8u)-1) & ~((8u)-1))/(8u))-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(12), 4);
   __vcop_pblock_init16(pblock, __offset+_PREG(13), (8u*sizeof(*scratchXX)) -(sizeof(*scratchXX))*((windowSize)-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(14), ((inBlockWidth+8u-1&~(8u-1))*sizeof(*scratchXX)) -(8u*sizeof(*scratchXX))*(((((inBlockWidth - (windowSize - 1)) + (8u)-1) & ~((8u)-1))/(8u))-1u) -(sizeof(*scratchXX))*((windowSize)-1u));
   __vcop_pblock_init32(pblock, __offset+_PREG(16), 0);
   __vcop_pblock_init32(pblock, __offset+_PREG(18), (uchar *)scratchXX);
   __offset += 18;

   return 64u;
}

void vcop_harrisScore_32_methodB_vloops(
   unsigned short pblock[])
{
   /* Kernel-wide Vector Registers */
   #pragma VCC_VREG("dx", 16);
   #pragma VCC_VREG("dy", 17);
   #pragma VCC_VREG("trace", 18);
   #pragma VCC_VREG("zxx", 19);
   #pragma VCC_VREG("zxxi", 20);
   #pragma VCC_VREG("zyy", 21);
   #pragma VCC_VREG("zyyi", 22);

   __vcop_param(&pblock[0]);

   /* VLOOP 1 Start */

   /* VLOOP Local Vector Registers */
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("addrIn", "A0");
   #pragma EVE_REG("addrOut", "A1");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I1", "I3");
   #pragma EVE_REG("I2", "I4");
   

   __vcop_vloop(__vcop_compute(), 11u, 9u, 1u);
   __vcop_vinit(__vcop_sizeW(), __vcop_i4_zero(), _PREG(16), _VREG(19));
   __vcop_vinit(__vcop_sizeW(), __vcop_i4_zero(), _PREG(16), _VREG(21));
   __vcop_vagen(_AGEN(0), _PREG(12), _PREG(13), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(1), _PREG(14), _PREG(15), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeH(), __vcop_npt(), _PREG(18), _AGEN(0), _VREG(16), __vcop_alws());
   __vcop_vload(__vcop_sizeH(), __vcop_npt(), _PREG(6), _AGEN(0), _VREG(17), __vcop_alws());
   __vcop_vmadd(_VREG(16), _VREG(16), _VREG(19), _PREG(0));
   __vcop_vmadd(_VREG(17), _VREG(17), _VREG(21), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeWU(), __vcop_npt(), __vcop_alws(), _VREG(19), _PREG(8), _AGEN(1), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeWU(), __vcop_npt(), __vcop_alws(), _VREG(21), _PREG(10), _AGEN(1), _PREG(0));
   __vcop_vloop_end(1u);

   /* VLOOP 2 Start */

   /* VLOOP Local Vector Registers */
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("AddrInOut", "A0");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I1", "I4");
   

   __vcop_vloop(__vcop_compute(), 6u, 7u, 2u);
   __vcop_vagen(_AGEN(0), _PREG(10), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeWU(), __vcop_npt(), _PREG(12), _AGEN(0), _VREG(19), __vcop_alws());
   __vcop_vload(__vcop_sizeWU(), __vcop_npt(), _PREG(14), _AGEN(0), _VREG(21), __vcop_alws());
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeWU(), __vcop_npt(), __vcop_alws(), _VREG(19), _PREG(6), _AGEN(0), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeWU(), __vcop_npt(), __vcop_alws(), _VREG(21), _PREG(8), _AGEN(0), _PREG(0));
   __vcop_vloop_end(2u);

   /* VLOOP 3 Start */

   /* VLOOP Local Vector Registers */
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("AddrInOut", "A0");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I1", "I3");
   #pragma EVE_REG("I2", "I4");
   

   __vcop_vloop(__vcop_compute(), 10u, 7u, 3u);
   __vcop_vagen(_AGEN(0), _PREG(10), _PREG(11), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeWU(), __vcop_npt(), _PREG(12), _AGEN(0), _VREG(19), __vcop_alws());
   __vcop_vload(__vcop_sizeWU(), __vcop_npt(), _PREG(14), _AGEN(0), _VREG(21), __vcop_alws());
   __vcop_vload(__vcop_sizeWU(), __vcop_npt(), _PREG(6), _AGEN(0), _VREG(20), __vcop_alws());
   __vcop_vload(__vcop_sizeWU(), __vcop_npt(), _PREG(8), _AGEN(0), _VREG(22), __vcop_alws());
   __vcop_vsub(_VREG(20), _VREG(19), _VREG(20));
   __vcop_vsub(_VREG(22), _VREG(21), _VREG(22));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeWU(), __vcop_npt(), __vcop_alws(), _VREG(20), _PREG(12), _AGEN(0), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeWU(), __vcop_npt(), __vcop_alws(), _VREG(22), _PREG(14), _AGEN(0), _PREG(0));
   __vcop_vloop_end(3u);

   /* VLOOP 4 Start */

   /* VLOOP Local Vector Registers */
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("addrOut", "A0");
   #pragma EVE_REG("addrIn", "A1");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I1", "I2");
   #pragma EVE_REG("I2", "I3");
   #pragma EVE_REG("I4", "I4");
   

   __vcop_vloop(__vcop_compute(), 9u, 9u, 4u);
   __vcop_vinit(__vcop_sizeW(), __vcop_i4_zero(), _PREG(16), _VREG(18));
   __vcop_vagen(_AGEN(0), _PREG(0), _PREG(10), _PREG(11), _PREG(0));
   __vcop_vagen(_AGEN(1), _PREG(12), _PREG(13), _PREG(14), _PREG(0));
   __vcop_vload(__vcop_sizeWU(), __vcop_npt(), _PREG(18), _AGEN(1), _VREG(20), __vcop_alws());
   __vcop_vload(__vcop_sizeWU(), __vcop_npt(), _PREG(6), _AGEN(1), _VREG(22), __vcop_alws());
   __vcop_vadd(_VREG(18), _VREG(20), _VREG(18));
   __vcop_vadd(_VREG(18), _VREG(22), _VREG(18));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeWU(), __vcop_npt(), __vcop_last_i4(), _VREG(18), _PREG(8), _AGEN(0), _PREG(0));
   __vcop_vloop_end(4u);

}

void vcop_harrisScore_32_methodB(
   __vptr_int16 gradX,
   __vptr_int16 gradY,
   __vptr_uint32 scratchXX,
   __vptr_uint32 scratchYY,
   unsigned short inBlockWidth,
   unsigned short inBlockHeight,
   unsigned short srcPitch,
   unsigned short dstPitch,
   unsigned char windowSize,
   __vptr_uint32 outm)
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_harrisScore_32_methodB_init(gradX, gradY, scratchXX, scratchYY, inBlockWidth, inBlockHeight, srcPitch, dstPitch, windowSize, outm, __pblock_vcop_harrisScore_32_methodB);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_harrisScore_32_methodB_vloops(__pblock_vcop_harrisScore_32_methodB);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

void vcop_harrisScore_32_methodB_custom(
   __vptr_int16 gradX,
   __vptr_int16 gradY,
   __vptr_uint32 scratchXX,
   __vptr_uint32 scratchYY,
   unsigned short inBlockWidth,
   unsigned short inBlockHeight,
   unsigned short srcPitch,
   unsigned short dstPitch,
   unsigned char windowSize,
   __vptr_uint32 outm,
   unsigned short pblock[])
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_harrisScore_32_methodB_init(gradX, gradY, scratchXX, scratchYY, inBlockWidth, inBlockHeight, srcPitch, dstPitch, windowSize, outm, pblock);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_harrisScore_32_methodB_vloops(pblock);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

