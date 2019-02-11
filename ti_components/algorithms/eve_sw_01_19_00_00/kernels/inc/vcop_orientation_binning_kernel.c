#include <vcop\vcop.h>

typedef unsigned char uchar;

#pragma DATA_SECTION(__pblock_vcop_orientation_binning, ".vcop_parameter_block")
#pragma DATA_ALIGN(__pblock_vcop_orientation_binning, __ALIGNOF__(int));
unsigned short __pblock_vcop_orientation_binning[54];

unsigned int vcop_orientation_binning_param_count(void)
{
   return 54u;
}

unsigned int vcop_orientation_binning_ctrl_count(void)
{
   return 0u;
}

unsigned int vcop_orientation_binning_init(
   __vptr_int16 gradX,
   __vptr_int16 gradY,
   __vptr_uint8 outBin,
   __vptr_int16 wSinTab,
   __vptr_int16 wCosTab,
   unsigned short numBins,
   unsigned short width,
   unsigned short height,
   unsigned short pitch,
   unsigned short pblock[])
{
   int __offset = 0;
   /* Loop 1 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), ((height+1)/2)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), (((width + ((8u)-1)) & (~((8u)-1)))/((8u)))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), (numBins)-1u);
   __vcop_pblock_init32(pblock, __offset+_PREG(6), (uchar *)gradX+pitch*2);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)gradY+pitch*2);
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (0x7FFFFFFF));
   __vcop_pblock_init32(pblock, __offset+_PREG(12), (0));
   __vcop_pblock_init32(pblock, __offset+_PREG(14), (uchar *)wSinTab);
   __vcop_pblock_init32(pblock, __offset+_PREG(16), (uchar *)wCosTab);
   __vcop_pblock_init32(pblock, __offset+_PREG(18), (uchar *)outBin);
   __vcop_pblock_init32(pblock, __offset+_PREG(20), (uchar *)outBin+pitch);
   __vcop_pblock_init16(pblock, __offset+_PREG(22), 8);
   __vcop_pblock_init16(pblock, __offset+_PREG(23), (pitch*2) -(8u)*((((width + ((8u)-1)) & (~((8u)-1)))/((8u)))-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(24), 16);
   __vcop_pblock_init16(pblock, __offset+_PREG(25), (pitch*4) -(8u*2)*((((width + ((8u)-1)) & (~((8u)-1)))/((8u)))-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(26), 2);
   __vcop_pblock_init16(pblock, __offset+_PREG(27),  -(sizeof(*wSinTab))*((numBins)-1u));
   __vcop_pblock_init32(pblock, __offset+_PREG(28), (uchar *)gradX);
   __vcop_pblock_init32(pblock, __offset+_PREG(30), (uchar *)gradY);
   __offset += 30;

   /* Loop 2 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), (height)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), (((width + ((8u)*2-1)) & (~((8u)*2-1)))/((8u)*2))-1u);
   __vcop_pblock_init32(pblock, __offset+_PREG(6), (uchar *)gradX);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)gradX+8u*2);
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)gradY);
   __vcop_pblock_init32(pblock, __offset+_PREG(12), (uchar *)gradY+8u*2);
   __vcop_pblock_init32(pblock, __offset+_PREG(14), (uchar *)outBin);
   __vcop_pblock_init32(pblock, __offset+_PREG(16), (uchar *)outBin+8u);
   __vcop_pblock_init16(pblock, __offset+_PREG(18), 32);
   __vcop_pblock_init16(pblock, __offset+_PREG(19), (pitch*2) -(8u*2*2)*((((width + ((8u)*2-1)) & (~((8u)*2-1)))/((8u)*2))-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(20), 16);
   __vcop_pblock_init16(pblock, __offset+_PREG(21), (pitch) -(8u*2)*((((width + ((8u)*2-1)) & (~((8u)*2-1)))/((8u)*2))-1u));
   __vcop_pblock_init32(pblock, __offset+_PREG(22), numBins-1);
   __vcop_pblock_init32(pblock, __offset+_PREG(24), 0);
   __offset += 24;

   return 54u;
}

void vcop_orientation_binning_vloops(
   unsigned short pblock[])
{
   /* Kernel-wide Vector Registers */
   #pragma VCC_VREG("vBinsMinus1", 16);
   #pragma VCC_VREG("vcos", 17);
   #pragma VCC_VREG("vcurIndex", 18);
   #pragma VCC_VREG("vgx1", 19);
   #pragma VCC_VREG("vgx2", 20);
   #pragma VCC_VREG("vgy1", 21);
   #pragma VCC_VREG("vgy2", 22);
   #pragma VCC_VREG("vmin1", 23);
   #pragma VCC_VREG("vmin2", 24);
   #pragma VCC_VREG("vminIndex1", 25);
   #pragma VCC_VREG("vminIndex2", 26);
   #pragma VCC_VREG("vminflags1", 27);
   #pragma VCC_VREG("vminflags2", 28);
   #pragma VCC_VREG("vsin", 29);
   #pragma VCC_VREG("vsum1", 30);
   #pragma VCC_VREG("vsum1A", 31);
   #pragma VCC_VREG("vsum2", 32);
   #pragma VCC_VREG("vsum2A", 33);
   #pragma VCC_VREG("vx1", 34);
   #pragma VCC_VREG("vx2", 35);
   #pragma VCC_VREG("vxflags1", 36);
   #pragma VCC_VREG("vxflags2", 37);
   #pragma VCC_VREG("vy1", 38);
   #pragma VCC_VREG("vy2", 39);
   #pragma VCC_VREG("vyflags1", 40);
   #pragma VCC_VREG("vyflags2", 41);
   #pragma VCC_VREG("vzero", 42);

   __vcop_param(&pblock[0]);

   /* VLOOP 1 Start */

   /* VLOOP Local Vector Registers */
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("Addr1", "A0");
   #pragma EVE_REG("Addr2", "A1");
   #pragma EVE_REG("Addr3", "A2");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I1", "I2");
   #pragma EVE_REG("I2", "I3");
   #pragma EVE_REG("I3", "I4");
   

   __vcop_vloop(__vcop_compute(), 27u, 15u, 1u);
   __vcop_vinit(__vcop_sizeW(), __vcop_i4_zero(), _PREG(10), _VREG(23));
   __vcop_vinit(__vcop_sizeW(), __vcop_i4_zero(), _PREG(12), _VREG(25));
   __vcop_vinit(__vcop_sizeW(), __vcop_i4_zero(), _PREG(10), _VREG(24));
   __vcop_vinit(__vcop_sizeW(), __vcop_i4_zero(), _PREG(12), _VREG(26));
   __vcop_vinit(__vcop_sizeHU(), __vcop_alws(), _PREG(68), _VREG(18));
   __vcop_vagen(_AGEN(0), _PREG(0), _PREG(22), _PREG(23), _PREG(0));
   __vcop_vagen(_AGEN(1), _PREG(0), _PREG(24), _PREG(25), _PREG(0));
   __vcop_vagen(_AGEN(2), _PREG(26), _PREG(27), _PREG(27), _PREG(0));
   __vcop_vload(__vcop_sizeH(), __vcop_npt(), _PREG(28), _AGEN(1), _VREG(34), __vcop_i4_zero());
   __vcop_vload(__vcop_sizeH(), __vcop_npt(), _PREG(30), _AGEN(1), _VREG(38), __vcop_i4_zero());
   __vcop_vload(__vcop_sizeH(), __vcop_npt(), _PREG(6), _AGEN(1), _VREG(35), __vcop_i4_zero());
   __vcop_vload(__vcop_sizeH(), __vcop_npt(), _PREG(8), _AGEN(1), _VREG(39), __vcop_i4_zero());
   __vcop_vload(__vcop_sizeH(), __vcop_1pt(), _PREG(14), _AGEN(2), _VREG(29), __vcop_alws());
   __vcop_vload(__vcop_sizeH(), __vcop_1pt(), _PREG(16), _AGEN(2), _VREG(17), __vcop_alws());
   __vcop_vmpy(_VREG(38), _VREG(17), _VREG(30), _PREG(0));
   __vcop_vmpy(_VREG(35), _VREG(29), _VREG(32), _PREG(0));
   __vcop_vmpy(_VREG(34), _VREG(29), _VREG(31), _PREG(0));
   __vcop_vmpy(_VREG(39), _VREG(17), _VREG(33), _PREG(0));
   __vcop_vabsdif(_VREG(30), _VREG(31), _VREG(30));
   __vcop_vabsdif(_VREG(32), _VREG(33), _VREG(32));
   __vcop_vminsetf(_VREG(30), _VREG(23), _VREG(27));
   __vcop_vminsetf(_VREG(32), _VREG(24), _VREG(28));
   __vcop_vsel(_VREG(27), _VREG(18), _VREG(25));
   __vcop_vsel(_VREG(28), _VREG(18), _VREG(26));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeBU(), __vcop_npt(), __vcop_last_i4(), _VREG(25), _PREG(18), _AGEN(0), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeBU(), __vcop_npt(), __vcop_last_i4(), _VREG(26), _PREG(20), _AGEN(0), _PREG(0));
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
   

   __vcop_vloop(__vcop_compute(), 18u, 12u, 2u);
   __vcop_vinit(__vcop_sizeW(), __vcop_once(), _PREG(22), _VREG(16));
   __vcop_vinit(__vcop_sizeW(), __vcop_once(), _PREG(24), _VREG(42));
   __vcop_vagen(_AGEN(0), _PREG(18), _PREG(19), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(1), _PREG(20), _PREG(21), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeH(), __vcop_npt(), _PREG(6), _AGEN(0), _VREG(19), __vcop_alws());
   __vcop_vload(__vcop_sizeH(), __vcop_npt(), _PREG(8), _AGEN(0), _VREG(20), __vcop_alws());
   __vcop_vload(__vcop_sizeH(), __vcop_npt(), _PREG(10), _AGEN(0), _VREG(21), __vcop_alws());
   __vcop_vload(__vcop_sizeH(), __vcop_npt(), _PREG(12), _AGEN(0), _VREG(22), __vcop_alws());
   __vcop_vcmpeq(_VREG(21), _VREG(42), _VREG(40));
   __vcop_vcmpeq(_VREG(22), _VREG(42), _VREG(41));
   __vcop_vcmplt(_VREG(19), _VREG(42), _VREG(36));
   __vcop_vcmplt(_VREG(20), _VREG(42), _VREG(37));
   __vcop_vand(_VREG(40), _VREG(36), _VREG(40));
   __vcop_vand(_VREG(41), _VREG(37), _VREG(41));
   __vcop_vstore(__vcop_predicate(_VREG(40)), __vcop_sizeBU(), __vcop_npt(), __vcop_alws(), _VREG(16), _PREG(14), _AGEN(1), _PREG(0));
   __vcop_vstore(__vcop_predicate(_VREG(41)), __vcop_sizeBU(), __vcop_npt(), __vcop_alws(), _VREG(16), _PREG(16), _AGEN(1), _PREG(0));
   __vcop_vloop_end(2u);

}

void vcop_orientation_binning(
   __vptr_int16 gradX,
   __vptr_int16 gradY,
   __vptr_uint8 outBin,
   __vptr_int16 wSinTab,
   __vptr_int16 wCosTab,
   unsigned short numBins,
   unsigned short width,
   unsigned short height,
   unsigned short pitch)
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_orientation_binning_init(gradX, gradY, outBin, wSinTab, wCosTab, numBins, width, height, pitch, __pblock_vcop_orientation_binning);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_orientation_binning_vloops(__pblock_vcop_orientation_binning);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

void vcop_orientation_binning_custom(
   __vptr_int16 gradX,
   __vptr_int16 gradY,
   __vptr_uint8 outBin,
   __vptr_int16 wSinTab,
   __vptr_int16 wCosTab,
   unsigned short numBins,
   unsigned short width,
   unsigned short height,
   unsigned short pitch,
   unsigned short pblock[])
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_orientation_binning_init(gradX, gradY, outBin, wSinTab, wCosTab, numBins, width, height, pitch, pblock);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_orientation_binning_vloops(pblock);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

#pragma DATA_SECTION(__pblock_vcop_orientation_binning_even, ".vcop_parameter_block")
#pragma DATA_ALIGN(__pblock_vcop_orientation_binning_even, __ALIGNOF__(int));
unsigned short __pblock_vcop_orientation_binning_even[64];

unsigned int vcop_orientation_binning_even_param_count(void)
{
   return 64u;
}

unsigned int vcop_orientation_binning_even_ctrl_count(void)
{
   return 0u;
}

unsigned int vcop_orientation_binning_even_init(
   __vptr_int16 gradX,
   __vptr_int16 gradY,
   __vptr_uint8 absGradX,
   __vptr_uint8 absGradY,
   __vptr_uint8 outBin,
   __vptr_int16 wSinTab,
   __vptr_int16 wCosTab,
   unsigned short numBins,
   unsigned short width,
   unsigned short height,
   unsigned short pitch,
   unsigned short pblock[])
{
   int __offset = 0;
   /* Loop 1 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), (height)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), ((width)/((8u)*2))-1u);
   __vcop_pblock_init32(pblock, __offset+_PREG(6), (uchar *)absGradX);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)absGradY);
   __vcop_pblock_init16(pblock, __offset+_PREG(10), 32);
   __vcop_pblock_init16(pblock, __offset+_PREG(11), (pitch*2) -(8u*2*2)*(((width)/((8u)*2))-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(12), 16);
   __vcop_pblock_init16(pblock, __offset+_PREG(13), (width) -(8u*2)*(((width)/((8u)*2))-1u));
   __vcop_pblock_init32(pblock, __offset+_PREG(14), (uchar *)gradX);
   __vcop_pblock_init32(pblock, __offset+_PREG(16), (uchar *)gradY);
   __offset += 16;

   /* Loop 2 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), ((height+1)/2)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), ((width)/((8u)))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), ((numBins/2))-1u);
   __vcop_pblock_init32(pblock, __offset+_PREG(6), (uchar *)absGradX+width);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)absGradY+width);
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (0x7FFFFFFF));
   __vcop_pblock_init32(pblock, __offset+_PREG(12), (0));
   __vcop_pblock_init32(pblock, __offset+_PREG(14), (uchar *)wSinTab);
   __vcop_pblock_init32(pblock, __offset+_PREG(16), (uchar *)wCosTab);
   __vcop_pblock_init32(pblock, __offset+_PREG(18), (uchar *)outBin);
   __vcop_pblock_init32(pblock, __offset+_PREG(20), (uchar *)outBin+width);
   __vcop_pblock_init16(pblock, __offset+_PREG(22), 8);
   __vcop_pblock_init16(pblock, __offset+_PREG(23), (width*2) -(8u)*(((width)/((8u)))-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(24), 2);
   __vcop_pblock_init16(pblock, __offset+_PREG(25),  -(sizeof(*wSinTab))*(((numBins/2))-1u));
   __vcop_pblock_init32(pblock, __offset+_PREG(26), (uchar *)absGradX);
   __vcop_pblock_init32(pblock, __offset+_PREG(28), (uchar *)absGradY);
   __offset += 28;

   /* Loop 3 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), (height)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), ((width)/((8u)*2))-1u);
   __vcop_pblock_init32(pblock, __offset+_PREG(6), (uchar *)gradX);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)gradY);
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)outBin);
   __vcop_pblock_init32(pblock, __offset+_PREG(12), (uchar *)absGradX);
   __vcop_pblock_init16(pblock, __offset+_PREG(14), 16);
   __vcop_pblock_init16(pblock, __offset+_PREG(15), (width) -(8u*2)*(((width)/((8u)*2))-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(16), 32);
   __vcop_pblock_init16(pblock, __offset+_PREG(17), (pitch*2) -(8u*2*2)*(((width)/((8u)*2))-1u));
   __vcop_pblock_init32(pblock, __offset+_PREG(18), numBins-1);
   __vcop_pblock_init32(pblock, __offset+_PREG(20), 0);
   __offset += 20;

   return 64u;
}

void vcop_orientation_binning_even_vloops(
   unsigned short pblock[])
{
   /* Kernel-wide Vector Registers */
   #pragma VCC_VREG("Vec0", 16);
   #pragma VCC_VREG("Vec1", 17);
   #pragma VCC_VREG("Vec10", 18);
   #pragma VCC_VREG("Vec11", 19);
   #pragma VCC_VREG("Vec12", 20);
   #pragma VCC_VREG("Vec13", 21);
   #pragma VCC_VREG("Vec14", 22);
   #pragma VCC_VREG("Vec15", 23);
   #pragma VCC_VREG("Vec2", 24);
   #pragma VCC_VREG("Vec3", 25);
   #pragma VCC_VREG("Vec4", 26);
   #pragma VCC_VREG("Vec5", 27);
   #pragma VCC_VREG("Vec6", 28);
   #pragma VCC_VREG("Vec7", 29);
   #pragma VCC_VREG("Vec8", 30);
   #pragma VCC_VREG("Vec9", 31);

   __vcop_param(&pblock[0]);

   /* VLOOP 1 Start */

   /* VLOOP Local Vector Registers */
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("Addr1", "A0");
   #pragma EVE_REG("Addr2", "A1");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I1", "I3");
   #pragma EVE_REG("I2", "I4");
   

   __vcop_vloop(__vcop_compute(), 11u, 8u, 1u);
   __vcop_vagen(_AGEN(0), _PREG(10), _PREG(11), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(1), _PREG(12), _PREG(13), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeH(), __vcop_dintrlv(), _PREG(14), _AGEN(0), _VPAIR(16,17), __vcop_alws());
   __vcop_vload(__vcop_sizeH(), __vcop_dintrlv(), _PREG(16), _AGEN(0), _VPAIR(24,25), __vcop_alws());
   __vcop_vabs(_VREG(16), _VREG(16));
   __vcop_vabs(_VREG(17), _VREG(17));
   __vcop_vabs(_VREG(24), _VREG(24));
   __vcop_vabs(_VREG(25), _VREG(25));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeBU(), __vcop_intrlv(), __vcop_alws(), _VPAIR(16,17), _PREG(6), _AGEN(1), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeBU(), __vcop_intrlv(), __vcop_alws(), _VPAIR(24,25), _PREG(8), _AGEN(1), _PREG(0));
   __vcop_vloop_end(1u);

   /* VLOOP 2 Start */

   /* VLOOP Local Vector Registers */
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("Addr1", "A0");
   #pragma EVE_REG("Addr2", "A1");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I1", "I2");
   #pragma EVE_REG("I2", "I3");
   #pragma EVE_REG("I3", "I4");
   

   __vcop_vloop(__vcop_compute(), 26u, 14u, 2u);
   __vcop_vinit(__vcop_sizeW(), __vcop_i4_zero(), _PREG(10), _VREG(17));
   __vcop_vinit(__vcop_sizeW(), __vcop_i4_zero(), _PREG(12), _VREG(29));
   __vcop_vinit(__vcop_sizeW(), __vcop_i4_zero(), _PREG(10), _VREG(25));
   __vcop_vinit(__vcop_sizeW(), __vcop_i4_zero(), _PREG(12), _VREG(27));
   __vcop_vinit(__vcop_sizeHU(), __vcop_alws(), _PREG(68), _VREG(22));
   __vcop_vagen(_AGEN(0), _PREG(0), _PREG(22), _PREG(23), _PREG(0));
   __vcop_vagen(_AGEN(1), _PREG(24), _PREG(25), _PREG(25), _PREG(0));
   __vcop_vload(__vcop_sizeBU(), __vcop_npt(), _PREG(26), _AGEN(0), _VREG(16), __vcop_i4_zero());
   __vcop_vload(__vcop_sizeBU(), __vcop_npt(), _PREG(28), _AGEN(0), _VREG(26), __vcop_i4_zero());
   __vcop_vload(__vcop_sizeBU(), __vcop_npt(), _PREG(6), _AGEN(0), _VREG(24), __vcop_i4_zero());
   __vcop_vload(__vcop_sizeBU(), __vcop_npt(), _PREG(8), _AGEN(0), _VREG(28), __vcop_i4_zero());
   __vcop_vload(__vcop_sizeH(), __vcop_1pt(), _PREG(14), _AGEN(1), _VREG(30), __vcop_alws());
   __vcop_vload(__vcop_sizeH(), __vcop_1pt(), _PREG(16), _AGEN(1), _VREG(18), __vcop_alws());
   __vcop_vmpy(_VREG(26), _VREG(18), _VREG(31), _PREG(0));
   __vcop_vmpy(_VREG(24), _VREG(30), _VREG(19), _PREG(0));
   __vcop_vmpy(_VREG(16), _VREG(30), _VREG(20), _PREG(0));
   __vcop_vmpy(_VREG(28), _VREG(18), _VREG(21), _PREG(0));
   __vcop_vabsdif(_VREG(31), _VREG(20), _VREG(31));
   __vcop_vabsdif(_VREG(19), _VREG(21), _VREG(19));
   __vcop_vminsetf(_VREG(31), _VREG(17), _VREG(30));
   __vcop_vminsetf(_VREG(19), _VREG(25), _VREG(18));
   __vcop_vsel(_VREG(30), _VREG(22), _VREG(29));
   __vcop_vsel(_VREG(18), _VREG(22), _VREG(27));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeBU(), __vcop_npt(), __vcop_last_i4(), _VREG(29), _PREG(18), _AGEN(0), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeBU(), __vcop_npt(), __vcop_last_i4(), _VREG(27), _PREG(20), _AGEN(0), _PREG(0));
   __vcop_vloop_end(2u);

   /* VLOOP 3 Start */

   /* VLOOP Local Vector Registers */
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("Addr1", "A0");
   #pragma EVE_REG("Addr2", "A1");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I1", "I3");
   #pragma EVE_REG("I2", "I4");
   

   __vcop_vloop(__vcop_compute(), 26u, 10u, 3u);
   __vcop_vinit(__vcop_sizeW(), __vcop_once(), _PREG(18), _VREG(18));
   __vcop_vinit(__vcop_sizeW(), __vcop_once(), _PREG(20), _VREG(19));
   __vcop_vagen(_AGEN(0), _PREG(14), _PREG(15), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(1), _PREG(16), _PREG(17), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeH(), __vcop_dintrlv(), _PREG(6), _AGEN(1), _VPAIR(16,17), __vcop_alws());
   __vcop_vload(__vcop_sizeH(), __vcop_dintrlv(), _PREG(8), _AGEN(1), _VPAIR(24,25), __vcop_alws());
   __vcop_vload(__vcop_sizeBU(), __vcop_dintrlv(), _PREG(10), _AGEN(0), _VPAIR(26,27), __vcop_alws());
   __vcop_vload(__vcop_sizeBU(), __vcop_dintrlv(), _PREG(12), _AGEN(0), _VPAIR(20,21), __vcop_alws());
   __vcop_vabsdif(_VREG(26), _VREG(18), _VREG(30));
   __vcop_vabsdif(_VREG(27), _VREG(18), _VREG(31));
   __vcop_vcmplt(_VREG(16), _VREG(19), _VREG(28));
   __vcop_vcmplt(_VREG(17), _VREG(19), _VREG(29));
   __vcop_vsel(_VREG(28), _VREG(30), _VREG(26));
   __vcop_vsel(_VREG(29), _VREG(31), _VREG(27));
   __vcop_vabsdif(_VREG(26), _VREG(18), _VREG(30));
   __vcop_vabsdif(_VREG(27), _VREG(18), _VREG(31));
   __vcop_vcmplt(_VREG(24), _VREG(19), _VREG(28));
   __vcop_vcmplt(_VREG(25), _VREG(19), _VREG(29));
   __vcop_vcmplt(_VREG(19), _VREG(20), _VREG(20));
   __vcop_vcmplt(_VREG(19), _VREG(21), _VREG(21));
   __vcop_vand(_VREG(28), _VREG(20), _VREG(28));
   __vcop_vand(_VREG(29), _VREG(21), _VREG(29));
   __vcop_vsel(_VREG(28), _VREG(30), _VREG(26));
   __vcop_vsel(_VREG(29), _VREG(31), _VREG(27));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeBU(), __vcop_intrlv(), __vcop_alws(), _VPAIR(26,27), _PREG(10), _AGEN(0), _PREG(0));
   __vcop_vloop_end(3u);

}

void vcop_orientation_binning_even(
   __vptr_int16 gradX,
   __vptr_int16 gradY,
   __vptr_uint8 absGradX,
   __vptr_uint8 absGradY,
   __vptr_uint8 outBin,
   __vptr_int16 wSinTab,
   __vptr_int16 wCosTab,
   unsigned short numBins,
   unsigned short width,
   unsigned short height,
   unsigned short pitch)
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_orientation_binning_even_init(gradX, gradY, absGradX, absGradY, outBin, wSinTab, wCosTab, numBins, width, height, pitch, __pblock_vcop_orientation_binning_even);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_orientation_binning_even_vloops(__pblock_vcop_orientation_binning_even);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

void vcop_orientation_binning_even_custom(
   __vptr_int16 gradX,
   __vptr_int16 gradY,
   __vptr_uint8 absGradX,
   __vptr_uint8 absGradY,
   __vptr_uint8 outBin,
   __vptr_int16 wSinTab,
   __vptr_int16 wCosTab,
   unsigned short numBins,
   unsigned short width,
   unsigned short height,
   unsigned short pitch,
   unsigned short pblock[])
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_orientation_binning_even_init(gradX, gradY, absGradX, absGradY, outBin, wSinTab, wCosTab, numBins, width, height, pitch, pblock);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_orientation_binning_even_vloops(pblock);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

