#include <vcop\vcop.h>

typedef unsigned char uchar;

#pragma DATA_SECTION(__pblock_vcop_featureMatching_32, ".vcop_parameter_block")
#pragma DATA_ALIGN(__pblock_vcop_featureMatching_32, __ALIGNOF__(int));
unsigned short __pblock_vcop_featureMatching_32[62];

unsigned int vcop_featureMatching_32_param_count(void)
{
   return 62u;
}

unsigned int vcop_featureMatching_32_ctrl_count(void)
{
   return 0u;
}

unsigned int vcop_featureMatching_32_init(
   __vptr_uint32 pString1,
   __vptr_uint32 pString2,
   __vptr_uint8 pScratch,
   __vptr_uint16 pHammingDistance,
   unsigned int ysize,
   unsigned int mode,
   unsigned int xpitch,
   short startIdx,
   unsigned short pblock[])
{
   int __offset = 0;
   /* Loop 1 PREGS */
   const int preg_ref1 = _PREG(14);

   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), ((ysize+1)/2)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), (((2-mode)*(2-mode)*(2-mode)*(2-mode)))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(6), __vcop_store_round_sat(SM_4PARAM,preg_ref1,RM_NONE,0));
   __vcop_pblock_init16(pblock, __offset+_PREG(7), (2*xpitch));
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)pString2);
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)pString2+xpitch*mode);
   __vcop_pblock_init32(pblock, __offset+_PREG(12), (uchar *)pScratch);
   __vcop_pblock_4param_init(pblock, __offset+_PREG(14), 0xFF,0xFF,0x0,0x0);
   __vcop_pblock_init32(pblock, __offset+_PREG(18), (uchar *)pScratch+sizeof(*pScratch));
   __vcop_pblock_init16(pblock, __offset+_PREG(20), (xpitch));
   __vcop_pblock_init16(pblock, __offset+_PREG(21), (2*xpitch*mode) -(xpitch)*((((2-mode)*(2-mode)*(2-mode)*(2-mode)))-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(22), 2);
   __vcop_pblock_init16(pblock, __offset+_PREG(23), ((4*9)*8u) -(2*sizeof(*pScratch))*((((2-mode)*(2-mode)*(2-mode)*(2-mode)))-1u));
   __vcop_pblock_init32(pblock, __offset+_PREG(24), (uchar *)pString1);
   __vcop_pblock_init32(pblock, __offset+_PREG(26), (uchar *)pString1+xpitch);
   __offset += 26;

   /* Loop 2 PREGS */
   const int preg_ref2 = _PREG(10);

   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), (2)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), ((ysize+1)/2)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), ((8u))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(6), __vcop_store_round_sat(SM_4PARAM,preg_ref2,RM_NONE,0));
   __vcop_pblock_init16(pblock, __offset+_PREG(7), 128);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)pHammingDistance+2);
   __vcop_pblock_4param_init(pblock, __offset+_PREG(10), 0xFFFF,0xFFFF,0x0,0x0);
   __vcop_pblock_init32(pblock, __offset+_PREG(14), (uchar *)pHammingDistance+2*8u*4+2);
   __vcop_pblock_init16(pblock, __offset+_PREG(16), (8u*4) -(2*4*(2*8u))*(((ysize+1)/2)-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(17), 36);
   __vcop_pblock_init16(pblock, __offset+_PREG(18), ((2*8u)*sizeof(*pScratch)) -((4*9)*8u)*(((ysize+1)/2)-1u) -((4*9))*(((8u))-1u));
   __vcop_pblock_init32(pblock, __offset+_PREG(20), 0);
   __vcop_pblock_init32(pblock, __offset+_PREG(22), (uchar *)pScratch);
   __offset += 22;

   /* Loop 3 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), (ysize)-1u);
   __vcop_pblock_init32(pblock, __offset+_PREG(6), (uchar *)pHammingDistance);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)pHammingDistance+4*8u);
   __vcop_pblock_init16(pblock, __offset+_PREG(10), 64);
   __vcop_pblock_init32(pblock, __offset+_PREG(12), startIdx - 1);
   __vcop_pblock_init32(pblock, __offset+_PREG(14), 1);
   __offset += 14;

   return 62u;
}

void vcop_featureMatching_32_vloops(
   unsigned short pblock[])
{
   /* Kernel-wide Vector Registers */
   #pragma VCC_VREG("Vidx1", 16);

   __vcop_param(&pblock[0]);

   /* VLOOP 1 Start */

   /* VLOOP Local Vector Registers */
   #pragma VCC_VREG("Vin11", 17);
   #pragma VCC_VREG("Vin12", 18);
   #pragma VCC_VREG("Vbitcnt1", 19);
   #pragma VCC_VREG("Vbitcnt2", 20);
   #pragma VCC_VREG("Vin21", 21);
   #pragma VCC_VREG("Vin22", 22);
   #pragma VCC_VREG("Vout1", 23);
   #pragma VCC_VREG("Vout2", 24);
   #pragma VCC_VREG("Vxor1", 25);
   #pragma VCC_VREG("Vxor2", 26);
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("Addr1", "A0");
   #pragma EVE_REG("Addr2", "A1");
   #pragma EVE_REG("AddrOut", "A2");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I2", "I3");
   #pragma EVE_REG("I1", "I4");
   

   __vcop_vloop(__vcop_compute(), 14u, 13u, 1u);
   __vcop_vagen(_AGEN(0), _PREG(0), _PREG(7), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(1), _PREG(20), _PREG(21), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(2), _PREG(22), _PREG(23), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeWU(), __vcop_npt(), _PREG(24), _AGEN(0), _VREG(17), __vcop_i4_zero());
   __vcop_vload(__vcop_sizeWU(), __vcop_npt(), _PREG(26), _AGEN(0), _VREG(18), __vcop_i4_zero());
   __vcop_vload(__vcop_sizeWU(), __vcop_npt(), _PREG(8), _AGEN(1), _VREG(21), __vcop_alws());
   __vcop_vload(__vcop_sizeWU(), __vcop_npt(), _PREG(10), _AGEN(1), _VREG(22), __vcop_alws());
   __vcop_vxor(_VREG(17), _VREG(21), _VREG(25));
   __vcop_vxor(_VREG(18), _VREG(22), _VREG(26));
   __vcop_vbitc(_VREG(25), _VREG(23));
   __vcop_vbitc(_VREG(26), _VREG(24));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeBU(), __vcop_offst_np1(), __vcop_alws(), _VREG(23), _PREG(12), _AGEN(2), _PREG(6));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeBU(), __vcop_offst_np1(), __vcop_alws(), _VREG(24), _PREG(18), _AGEN(2), _PREG(6));
   __vcop_vloop_end(1u);

   /* VLOOP 2 Start */

   /* VLOOP Local Vector Registers */
   #pragma VCC_VREG("Vout1", 27);
   #pragma VCC_VREG("Vout2", 28);
   #pragma VCC_VREG("Vin1", 29);
   #pragma VCC_VREG("Vin2", 30);
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("AddrOut", "A0");
   #pragma EVE_REG("AddrIn", "A1");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I1", "I2");
   #pragma EVE_REG("I2", "I3");
   #pragma EVE_REG("I3", "I4");
   

   __vcop_vloop(__vcop_compute(), 10u, 11u, 2u);
   __vcop_vinit(__vcop_sizeW(), __vcop_i4_zero(), _PREG(20), _VREG(27));
   __vcop_vinit(__vcop_sizeW(), __vcop_i4_zero(), _PREG(20), _VREG(28));
   __vcop_vagen(_AGEN(0), _PREG(0), _PREG(7), _PREG(16), _PREG(0));
   __vcop_vagen(_AGEN(1), _PREG(17), _PREG(17), _PREG(18), _PREG(0));
   __vcop_vload(__vcop_sizeBU(), __vcop_dintrlv(), _PREG(22), _AGEN(1), _VPAIR(29,30), __vcop_alws());
   __vcop_vadd(_VREG(27), _VREG(29), _VREG(27));
   __vcop_vadd(_VREG(28), _VREG(30), _VREG(28));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeHU(), __vcop_skip(), __vcop_last_i4(), _VREG(27), _PREG(8), _AGEN(0), _PREG(6));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeHU(), __vcop_skip(), __vcop_last_i4(), _VREG(28), _PREG(14), _AGEN(0), _PREG(6));
   __vcop_vloop_end(2u);

   /* VLOOP 3 Start */

   /* VLOOP Local Vector Registers */
   #pragma VCC_VREG("VK1", 31);
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("AddrOut", "A0");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I1", "I4");
   

   __vcop_vloop(__vcop_compute(), 7u, 7u, 3u);
   __vcop_vinit(__vcop_sizeW(), __vcop_once(), _PREG(12), _VREG(16));
   __vcop_vinit(__vcop_sizeW(), __vcop_alws(), _PREG(14), _VREG(31));
   __vcop_vagen(_AGEN(0), _PREG(10), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vadd(_VREG(16), _VREG(31), _VREG(16));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeHU(), __vcop_skip(), __vcop_alws(), _VREG(16), _PREG(6), _AGEN(0), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeHU(), __vcop_skip(), __vcop_alws(), _VREG(16), _PREG(8), _AGEN(0), _PREG(0));
   __vcop_vloop_end(3u);

}

void vcop_featureMatching_32(
   __vptr_uint32 pString1,
   __vptr_uint32 pString2,
   __vptr_uint8 pScratch,
   __vptr_uint16 pHammingDistance,
   unsigned int ysize,
   unsigned int mode,
   unsigned int xpitch,
   short startIdx)
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_featureMatching_32_init(pString1, pString2, pScratch, pHammingDistance, ysize, mode, xpitch, startIdx, __pblock_vcop_featureMatching_32);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_featureMatching_32_vloops(__pblock_vcop_featureMatching_32);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

void vcop_featureMatching_32_custom(
   __vptr_uint32 pString1,
   __vptr_uint32 pString2,
   __vptr_uint8 pScratch,
   __vptr_uint16 pHammingDistance,
   unsigned int ysize,
   unsigned int mode,
   unsigned int xpitch,
   short startIdx,
   unsigned short pblock[])
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_featureMatching_32_init(pString1, pString2, pScratch, pHammingDistance, ysize, mode, xpitch, startIdx, pblock);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_featureMatching_32_vloops(pblock);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

#pragma DATA_SECTION(__pblock_vcop_featureMatching_lt_32, ".vcop_parameter_block")
#pragma DATA_ALIGN(__pblock_vcop_featureMatching_lt_32, __ALIGNOF__(int));
unsigned short __pblock_vcop_featureMatching_lt_32[58];

unsigned int vcop_featureMatching_lt_32_param_count(void)
{
   return 58u;
}

unsigned int vcop_featureMatching_lt_32_ctrl_count(void)
{
   return 0u;
}

unsigned int vcop_featureMatching_lt_32_init(
   __vptr_uint32 pString1,
   __vptr_uint32 pString2,
   __vptr_uint32 pDescriptorMask,
   __vptr_uint8 pScratch,
   __vptr_uint16 pHammingDistance,
   unsigned int ysize,
   unsigned int mode,
   unsigned int xpitch,
   short startIdx,
   unsigned short pblock[])
{
   int __offset = 0;
   /* Loop 1 PREGS */
   const int preg_ref3 = _PREG(7);

   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), ((ysize+1)/2)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), (((2-mode)*(2-mode)*(2-mode)*(2-mode)))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(6), __vcop_store_round_sat(SM_SYMM,preg_ref3,RM_NONE,0));
   __vcop_pblock_init16(pblock, __offset+_PREG(7), 65535);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)pString1+xpitch);
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)pString2);
   __vcop_pblock_init32(pblock, __offset+_PREG(12), (uchar *)pString2+xpitch*mode);
   __vcop_pblock_init32(pblock, __offset+_PREG(14), (uchar *)pScratch);
   __vcop_pblock_init32(pblock, __offset+_PREG(16), (uchar *)pScratch+sizeof(*pScratch));
   __vcop_pblock_init16(pblock, __offset+_PREG(18), (2*xpitch));
   __vcop_pblock_init16(pblock, __offset+_PREG(19), (xpitch));
   __vcop_pblock_init16(pblock, __offset+_PREG(20), (2*xpitch*mode) -(xpitch)*((((2-mode)*(2-mode)*(2-mode)*(2-mode)))-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(21), 2);
   __vcop_pblock_init16(pblock, __offset+_PREG(22), ((4*9)*8u) -(2*sizeof(*pScratch))*((((2-mode)*(2-mode)*(2-mode)*(2-mode)))-1u));
   __vcop_pblock_init32(pblock, __offset+_PREG(24), (uchar *)pDescriptorMask);
   __vcop_pblock_init32(pblock, __offset+_PREG(26), (uchar *)pString1);
   __offset += 26;

   /* Loop 2 PREGS */
   const int preg_ref4 = _PREG(7);

   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), (2)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), ((ysize+1)/2)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), ((8u))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(6), __vcop_store_round_sat(SM_SYMM,preg_ref4,RM_NONE,0));
   __vcop_pblock_init16(pblock, __offset+_PREG(7), 65535);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)pHammingDistance+2);
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)pHammingDistance+2*8u*4+2);
   __vcop_pblock_init16(pblock, __offset+_PREG(12), 128);
   __vcop_pblock_init16(pblock, __offset+_PREG(13), (8u*4) -(2*4*(2*8u))*(((ysize+1)/2)-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(14), 36);
   __vcop_pblock_init16(pblock, __offset+_PREG(15), ((2*8u)*sizeof(*pScratch)) -((4*9)*8u)*(((ysize+1)/2)-1u) -((4*9))*(((8u))-1u));
   __vcop_pblock_init32(pblock, __offset+_PREG(16), 0);
   __vcop_pblock_init32(pblock, __offset+_PREG(18), (uchar *)pScratch);
   __offset += 18;

   /* Loop 3 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), (ysize)-1u);
   __vcop_pblock_init32(pblock, __offset+_PREG(6), (uchar *)pHammingDistance);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)pHammingDistance+4*8u);
   __vcop_pblock_init16(pblock, __offset+_PREG(10), 64);
   __vcop_pblock_init32(pblock, __offset+_PREG(12), startIdx - 1);
   __vcop_pblock_init32(pblock, __offset+_PREG(14), 1);
   __offset += 14;

   return 58u;
}

void vcop_featureMatching_lt_32_vloops(
   unsigned short pblock[])
{
   /* Kernel-wide Vector Registers */
   #pragma VCC_VREG("Vidx1", 16);
   #pragma VCC_VREG("Vmask", 17);

   __vcop_param(&pblock[0]);

   /* VLOOP 1 Start */

   /* VLOOP Local Vector Registers */
   #pragma VCC_VREG("Vin11", 18);
   #pragma VCC_VREG("Vin12", 19);
   #pragma VCC_VREG("Vin21", 20);
   #pragma VCC_VREG("Vin22", 21);
   #pragma VCC_VREG("Vout1", 22);
   #pragma VCC_VREG("Vout2", 23);
   #pragma VCC_VREG("Vtemp1", 24);
   #pragma VCC_VREG("Vtemp2", 25);
   #pragma VCC_VREG("Vxor1", 26);
   #pragma VCC_VREG("Vxor2", 27);
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("Addr0", "A0");
   #pragma EVE_REG("Addr1", "A1");
   #pragma EVE_REG("Addr2", "A2");
   #pragma EVE_REG("AddrOut", "A3");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I2", "I3");
   #pragma EVE_REG("I1", "I4");
   

   __vcop_vloop(__vcop_compute(), 18u, 13u, 1u);
   __vcop_vagen(_AGEN(0), _PREG(0), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(1), _PREG(0), _PREG(18), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(2), _PREG(19), _PREG(20), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(3), _PREG(21), _PREG(22), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeWU(), __vcop_npt(), _PREG(24), _AGEN(0), _VREG(17), __vcop_once());
   __vcop_vload(__vcop_sizeWU(), __vcop_npt(), _PREG(26), _AGEN(1), _VREG(18), __vcop_i4_zero());
   __vcop_vload(__vcop_sizeWU(), __vcop_npt(), _PREG(8), _AGEN(1), _VREG(19), __vcop_i4_zero());
   __vcop_vload(__vcop_sizeWU(), __vcop_npt(), _PREG(10), _AGEN(2), _VREG(20), __vcop_alws());
   __vcop_vload(__vcop_sizeWU(), __vcop_npt(), _PREG(12), _AGEN(2), _VREG(21), __vcop_alws());
   __vcop_vxor(_VREG(18), _VREG(20), _VREG(26));
   __vcop_vxor(_VREG(19), _VREG(21), _VREG(27));
   __vcop_vand(_VREG(26), _VREG(17), _VREG(24));
   __vcop_vand(_VREG(27), _VREG(17), _VREG(25));
   __vcop_vbitc(_VREG(24), _VREG(22));
   __vcop_vbitc(_VREG(25), _VREG(23));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeBU(), __vcop_offst_np1(), __vcop_alws(), _VREG(22), _PREG(14), _AGEN(3), _PREG(6));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeBU(), __vcop_offst_np1(), __vcop_alws(), _VREG(23), _PREG(16), _AGEN(3), _PREG(6));
   __vcop_vloop_end(1u);

   /* VLOOP 2 Start */

   /* VLOOP Local Vector Registers */
   #pragma VCC_VREG("Vout1", 28);
   #pragma VCC_VREG("Vout2", 29);
   #pragma VCC_VREG("Vin1", 30);
   #pragma VCC_VREG("Vin2", 31);
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("Addr0", "A0");
   #pragma EVE_REG("AddrOut", "A1");
   #pragma EVE_REG("AddrIn", "A2");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I1", "I2");
   #pragma EVE_REG("I2", "I3");
   #pragma EVE_REG("I3", "I4");
   

   __vcop_vloop(__vcop_compute(), 11u, 9u, 2u);
   __vcop_vinit(__vcop_sizeW(), __vcop_i4_zero(), _PREG(16), _VREG(28));
   __vcop_vinit(__vcop_sizeW(), __vcop_i4_zero(), _PREG(16), _VREG(29));
   __vcop_vagen(_AGEN(1), _PREG(0), _PREG(12), _PREG(13), _PREG(0));
   __vcop_vagen(_AGEN(2), _PREG(14), _PREG(14), _PREG(15), _PREG(0));
   __vcop_vload(__vcop_sizeBU(), __vcop_dintrlv(), _PREG(18), _AGEN(2), _VPAIR(30,31), __vcop_alws());
   __vcop_vadd(_VREG(28), _VREG(30), _VREG(28));
   __vcop_vadd(_VREG(29), _VREG(31), _VREG(29));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeHU(), __vcop_skip(), __vcop_last_i4(), _VREG(28), _PREG(8), _AGEN(1), _PREG(6));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeHU(), __vcop_skip(), __vcop_last_i4(), _VREG(29), _PREG(10), _AGEN(1), _PREG(6));
   __vcop_vloop_end(2u);

   /* VLOOP 3 Start */

   /* VLOOP Local Vector Registers */
   #pragma VCC_VREG("VK1", 32);
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("Addr0", "A0");
   #pragma EVE_REG("AddrOut", "A1");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I1", "I4");
   

   __vcop_vloop(__vcop_compute(), 8u, 7u, 3u);
   __vcop_vinit(__vcop_sizeW(), __vcop_once(), _PREG(12), _VREG(16));
   __vcop_vinit(__vcop_sizeW(), __vcop_alws(), _PREG(14), _VREG(32));
   __vcop_vagen(_AGEN(1), _PREG(10), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vadd(_VREG(16), _VREG(32), _VREG(16));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeHU(), __vcop_skip(), __vcop_alws(), _VREG(16), _PREG(6), _AGEN(1), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeHU(), __vcop_skip(), __vcop_alws(), _VREG(16), _PREG(8), _AGEN(1), _PREG(0));
   __vcop_vloop_end(3u);

}

void vcop_featureMatching_lt_32(
   __vptr_uint32 pString1,
   __vptr_uint32 pString2,
   __vptr_uint32 pDescriptorMask,
   __vptr_uint8 pScratch,
   __vptr_uint16 pHammingDistance,
   unsigned int ysize,
   unsigned int mode,
   unsigned int xpitch,
   short startIdx)
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_featureMatching_lt_32_init(pString1, pString2, pDescriptorMask, pScratch, pHammingDistance, ysize, mode, xpitch, startIdx, __pblock_vcop_featureMatching_lt_32);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_featureMatching_lt_32_vloops(__pblock_vcop_featureMatching_lt_32);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

void vcop_featureMatching_lt_32_custom(
   __vptr_uint32 pString1,
   __vptr_uint32 pString2,
   __vptr_uint32 pDescriptorMask,
   __vptr_uint8 pScratch,
   __vptr_uint16 pHammingDistance,
   unsigned int ysize,
   unsigned int mode,
   unsigned int xpitch,
   short startIdx,
   unsigned short pblock[])
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_featureMatching_lt_32_init(pString1, pString2, pDescriptorMask, pScratch, pHammingDistance, ysize, mode, xpitch, startIdx, pblock);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_featureMatching_lt_32_vloops(pblock);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

#pragma DATA_SECTION(__pblock_vcop_featureMatching_gt_32, ".vcop_parameter_block")
#pragma DATA_ALIGN(__pblock_vcop_featureMatching_gt_32, __ALIGNOF__(int));
unsigned short __pblock_vcop_featureMatching_gt_32[64];

unsigned int vcop_featureMatching_gt_32_param_count(void)
{
   return 64u;
}

unsigned int vcop_featureMatching_gt_32_ctrl_count(void)
{
   return 0u;
}

unsigned int vcop_featureMatching_gt_32_init(
   __vptr_uint32 pString1,
   __vptr_uint32 pString2,
   __vptr_uint32 pDescriptorMask,
   __vptr_uint16 pScratch,
   __vptr_uint16 pScatterOffsets,
   __vptr_uint16 pHammingDistance,
   unsigned int xsize,
   unsigned int ysize,
   unsigned int mode,
   unsigned int xpitch,
   short startIdx,
   unsigned short pblock[])
{
   int __offset = 0;
   /* Loop 1 PREGS */
   const int preg_ref5 = _PREG(7);

   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), ((ysize+1)/2)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), (((2-mode)*(2-mode)*(2-mode)*(2-mode)))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), ((xsize + (4 * (8u)) - 1)/(4 * (8u)))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(6), __vcop_store_round_sat(SM_SYMM,preg_ref5,RM_NONE,0));
   __vcop_pblock_init16(pblock, __offset+_PREG(7), 65535);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)pString1);
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)pString2);
   __vcop_pblock_init32(pblock, __offset+_PREG(12), (uchar *)pString1+xpitch);
   __vcop_pblock_init32(pblock, __offset+_PREG(14), (uchar *)pString2+xpitch*mode);
   __vcop_pblock_init32(pblock, __offset+_PREG(16), (uchar *)pDescriptorMask);
   __vcop_pblock_init32(pblock, __offset+_PREG(18), (uchar *)pScratch);
   __vcop_pblock_init32(pblock, __offset+_PREG(20), (uchar *)pScratch+sizeof(*pScratch));
   __vcop_pblock_init16(pblock, __offset+_PREG(22), 4);
   __vcop_pblock_init16(pblock, __offset+_PREG(23), ((4*17)*8u) -(2*sizeof(*pScratch))*((((2-mode)*(2-mode)*(2-mode)*(2-mode)))-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(24), 32);
   __vcop_pblock_init16(pblock, __offset+_PREG(25),  -((4*8u))*(((xsize + (4 * (8u)) - 1)/(4 * (8u)))-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(26), (2*xpitch) -((4*8u))*(((xsize + (4 * (8u)) - 1)/(4 * (8u)))-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(27), (xpitch) -((4*8u))*(((xsize + (4 * (8u)) - 1)/(4 * (8u)))-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(28), (2*xpitch*mode) -(xpitch)*((((2-mode)*(2-mode)*(2-mode)*(2-mode)))-1u) -((4*8u))*(((xsize + (4 * (8u)) - 1)/(4 * (8u)))-1u));
   __vcop_pblock_init32(pblock, __offset+_PREG(30), (uchar *)pScatterOffsets);
   __vcop_pblock_init32(pblock, __offset+_PREG(32), 0);
   __offset += 32;

   /* Loop 2 PREGS */
   const int preg_ref6 = _PREG(7);

   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), (2)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), ((ysize+1)/2)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), ((8u))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(6), __vcop_store_round_sat(SM_SYMM,preg_ref6,RM_NONE,0));
   __vcop_pblock_init16(pblock, __offset+_PREG(7), 65535);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)pHammingDistance+2);
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)pHammingDistance+2*8u*4+2);
   __vcop_pblock_init16(pblock, __offset+_PREG(12), 128);
   __vcop_pblock_init16(pblock, __offset+_PREG(13), (8u*4) -(2*4*(2*8u))*(((ysize+1)/2)-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(14), 68);
   __vcop_pblock_init16(pblock, __offset+_PREG(15), ((2*8u)*sizeof(*pScratch)) -((4*17)*8u)*(((ysize+1)/2)-1u) -((4*17))*(((8u))-1u));
   __vcop_pblock_init32(pblock, __offset+_PREG(16), 0);
   __vcop_pblock_init32(pblock, __offset+_PREG(18), (uchar *)pScratch);
   __offset += 18;

   /* Loop 3 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), (ysize)-1u);
   __vcop_pblock_init32(pblock, __offset+_PREG(6), (uchar *)pHammingDistance);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)pHammingDistance+4*8u);
   __vcop_pblock_init16(pblock, __offset+_PREG(10), 64);
   __vcop_pblock_init32(pblock, __offset+_PREG(12), startIdx - 1);
   __vcop_pblock_init32(pblock, __offset+_PREG(14), 1);
   __offset += 14;

   return 64u;
}

void vcop_featureMatching_gt_32_vloops(
   unsigned short pblock[])
{
   /* Kernel-wide Vector Registers */
   #pragma VCC_VREG("Vidx1", 16);
   #pragma VCC_VREG("Voffs", 17);

   __vcop_param(&pblock[0]);

   /* VLOOP 1 Start */

   /* VLOOP Local Vector Registers */
   #pragma VCC_VREG("Vout1", 18);
   #pragma VCC_VREG("Vout2", 19);
   #pragma VCC_VREG("Vbitcnt1", 20);
   #pragma VCC_VREG("Vbitcnt2", 21);
   #pragma VCC_VREG("Vin11", 22);
   #pragma VCC_VREG("Vin12", 23);
   #pragma VCC_VREG("Vin21", 24);
   #pragma VCC_VREG("Vin22", 25);
   #pragma VCC_VREG("Vmask", 26);
   #pragma VCC_VREG("Vtemp1", 27);
   #pragma VCC_VREG("Vtemp2", 28);
   #pragma VCC_VREG("Vxor1", 29);
   #pragma VCC_VREG("Vxor2", 30);
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("Addr0", "A0");
   #pragma EVE_REG("AddrOut", "A1");
   #pragma EVE_REG("Addr1", "A2");
   #pragma EVE_REG("Addr2", "A3");
   #pragma EVE_REG("AddrMask", "A4");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I2", "I2");
   #pragma EVE_REG("I1", "I3");
   #pragma EVE_REG("I3", "I4");
   

   __vcop_vloop(__vcop_compute(), 24u, 16u, 1u);
   __vcop_vinit(__vcop_sizeW(), __vcop_i4_zero(), _PREG(32), _VREG(18));
   __vcop_vinit(__vcop_sizeW(), __vcop_i4_zero(), _PREG(32), _VREG(19));
   __vcop_vagen(_AGEN(0), _PREG(0), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(1), _PREG(0), _PREG(22), _PREG(23), _PREG(0));
   __vcop_vagen(_AGEN(2), _PREG(24), _PREG(25), _PREG(26), _PREG(0));
   __vcop_vagen(_AGEN(3), _PREG(24), _PREG(27), _PREG(28), _PREG(0));
   __vcop_vagen(_AGEN(4), _PREG(24), _PREG(25), _PREG(25), _PREG(0));
   __vcop_vload(__vcop_sizeHU(), __vcop_npt(), _PREG(30), _AGEN(0), _VREG(17), __vcop_once());
   __vcop_vload(__vcop_sizeWU(), __vcop_npt(), _PREG(8), _AGEN(2), _VREG(22), __vcop_alws());
   __vcop_vload(__vcop_sizeWU(), __vcop_npt(), _PREG(10), _AGEN(3), _VREG(24), __vcop_alws());
   __vcop_vload(__vcop_sizeWU(), __vcop_npt(), _PREG(12), _AGEN(2), _VREG(23), __vcop_alws());
   __vcop_vload(__vcop_sizeWU(), __vcop_npt(), _PREG(14), _AGEN(3), _VREG(25), __vcop_alws());
   __vcop_vload(__vcop_sizeWU(), __vcop_npt(), _PREG(16), _AGEN(4), _VREG(26), __vcop_alws());
   __vcop_vxor(_VREG(22), _VREG(24), _VREG(29));
   __vcop_vxor(_VREG(23), _VREG(25), _VREG(30));
   __vcop_vand(_VREG(29), _VREG(26), _VREG(27));
   __vcop_vand(_VREG(30), _VREG(26), _VREG(28));
   __vcop_vbitc(_VREG(27), _VREG(20));
   __vcop_vbitc(_VREG(28), _VREG(21));
   __vcop_vadd(_VREG(18), _VREG(20), _VREG(18));
   __vcop_vadd(_VREG(19), _VREG(21), _VREG(19));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeHU(), __vcop_pdda(_VREG(17)), __vcop_last_i4(), _VREG(18), _PREG(18), _AGEN(1), _PREG(6));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeHU(), __vcop_pdda(_VREG(17)), __vcop_last_i4(), _VREG(19), _PREG(20), _AGEN(1), _PREG(6));
   __vcop_vloop_end(1u);

   /* VLOOP 2 Start */

   /* VLOOP Local Vector Registers */
   #pragma VCC_VREG("Vout1", 31);
   #pragma VCC_VREG("Vout2", 32);
   #pragma VCC_VREG("Vin1", 33);
   #pragma VCC_VREG("Vin2", 34);
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("Addr0", "A0");
   #pragma EVE_REG("AddrOut", "A1");
   #pragma EVE_REG("AddrIn", "A2");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I1", "I2");
   #pragma EVE_REG("I2", "I3");
   #pragma EVE_REG("I3", "I4");
   

   __vcop_vloop(__vcop_compute(), 11u, 9u, 2u);
   __vcop_vinit(__vcop_sizeW(), __vcop_i4_zero(), _PREG(16), _VREG(31));
   __vcop_vinit(__vcop_sizeW(), __vcop_i4_zero(), _PREG(16), _VREG(32));
   __vcop_vagen(_AGEN(1), _PREG(0), _PREG(12), _PREG(13), _PREG(0));
   __vcop_vagen(_AGEN(2), _PREG(14), _PREG(14), _PREG(15), _PREG(0));
   __vcop_vload(__vcop_sizeHU(), __vcop_dintrlv(), _PREG(18), _AGEN(2), _VPAIR(33,34), __vcop_alws());
   __vcop_vadd(_VREG(31), _VREG(33), _VREG(31));
   __vcop_vadd(_VREG(32), _VREG(34), _VREG(32));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeHU(), __vcop_skip(), __vcop_last_i4(), _VREG(31), _PREG(8), _AGEN(1), _PREG(6));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeHU(), __vcop_skip(), __vcop_last_i4(), _VREG(32), _PREG(10), _AGEN(1), _PREG(6));
   __vcop_vloop_end(2u);

   /* VLOOP 3 Start */

   /* VLOOP Local Vector Registers */
   #pragma VCC_VREG("VK1", 35);
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("Addr0", "A0");
   #pragma EVE_REG("AddrOut", "A1");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I1", "I4");
   

   __vcop_vloop(__vcop_compute(), 8u, 7u, 3u);
   __vcop_vinit(__vcop_sizeW(), __vcop_once(), _PREG(12), _VREG(16));
   __vcop_vinit(__vcop_sizeW(), __vcop_alws(), _PREG(14), _VREG(35));
   __vcop_vagen(_AGEN(1), _PREG(10), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vadd(_VREG(16), _VREG(35), _VREG(16));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeHU(), __vcop_skip(), __vcop_alws(), _VREG(16), _PREG(6), _AGEN(1), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeHU(), __vcop_skip(), __vcop_alws(), _VREG(16), _PREG(8), _AGEN(1), _PREG(0));
   __vcop_vloop_end(3u);

}

void vcop_featureMatching_gt_32(
   __vptr_uint32 pString1,
   __vptr_uint32 pString2,
   __vptr_uint32 pDescriptorMask,
   __vptr_uint16 pScratch,
   __vptr_uint16 pScatterOffsets,
   __vptr_uint16 pHammingDistance,
   unsigned int xsize,
   unsigned int ysize,
   unsigned int mode,
   unsigned int xpitch,
   short startIdx)
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_featureMatching_gt_32_init(pString1, pString2, pDescriptorMask, pScratch, pScatterOffsets, pHammingDistance, xsize, ysize, mode, xpitch, startIdx, __pblock_vcop_featureMatching_gt_32);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_featureMatching_gt_32_vloops(__pblock_vcop_featureMatching_gt_32);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

void vcop_featureMatching_gt_32_custom(
   __vptr_uint32 pString1,
   __vptr_uint32 pString2,
   __vptr_uint32 pDescriptorMask,
   __vptr_uint16 pScratch,
   __vptr_uint16 pScatterOffsets,
   __vptr_uint16 pHammingDistance,
   unsigned int xsize,
   unsigned int ysize,
   unsigned int mode,
   unsigned int xpitch,
   short startIdx,
   unsigned short pblock[])
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_featureMatching_gt_32_init(pString1, pString2, pDescriptorMask, pScratch, pScatterOffsets, pHammingDistance, xsize, ysize, mode, xpitch, startIdx, pblock);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_featureMatching_gt_32_vloops(pblock);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

#pragma DATA_SECTION(__pblock_vcop_featureMatch_initialize, ".vcop_parameter_block")
#pragma DATA_ALIGN(__pblock_vcop_featureMatch_initialize, __ALIGNOF__(int));
unsigned short __pblock_vcop_featureMatch_initialize[12];

unsigned int vcop_featureMatch_initialize_param_count(void)
{
   return 12u;
}

unsigned int vcop_featureMatch_initialize_ctrl_count(void)
{
   return 0u;
}

unsigned int vcop_featureMatch_initialize_init(
   __vptr_uint32 pMinDist0,
   __vptr_uint32 pMinDist1,
   unsigned int m,
   unsigned short pblock[])
{
   int __offset = 0;
   /* Loop 1 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), ((m + (8u) - 1)/(8u))-1u);
   __vcop_pblock_init32(pblock, __offset+_PREG(6), (uchar *)pMinDist1);
   __vcop_pblock_init16(pblock, __offset+_PREG(8), 32);
   __vcop_pblock_init32(pblock, __offset+_PREG(10), 4294967295);
   __vcop_pblock_init32(pblock, __offset+_PREG(12), (uchar *)pMinDist0);
   __offset += 12;

   return 12u;
}

void vcop_featureMatch_initialize_vloops(
   unsigned short pblock[])
{
   /* Kernel-wide Vector Registers */

   __vcop_param(&pblock[0]);

   /* VLOOP 1 Start */

   /* VLOOP Local Vector Registers */
   #pragma VCC_VREG("VK", 16);
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("AddrOut", "A0");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I1", "I4");
   

   __vcop_vloop(__vcop_compute(), 5u, 6u, 1u);
   __vcop_vinit(__vcop_sizeWU(), __vcop_alws(), _PREG(10), _VREG(16));
   __vcop_vagen(_AGEN(0), _PREG(8), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeWU(), __vcop_npt(), __vcop_alws(), _VREG(16), _PREG(12), _AGEN(0), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeWU(), __vcop_npt(), __vcop_alws(), _VREG(16), _PREG(6), _AGEN(0), _PREG(0));
   __vcop_vloop_end(1u);

}

void vcop_featureMatch_initialize(
   __vptr_uint32 pMinDist0,
   __vptr_uint32 pMinDist1,
   unsigned int m)
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_featureMatch_initialize_init(pMinDist0, pMinDist1, m, __pblock_vcop_featureMatch_initialize);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_featureMatch_initialize_vloops(__pblock_vcop_featureMatch_initialize);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

void vcop_featureMatch_initialize_custom(
   __vptr_uint32 pMinDist0,
   __vptr_uint32 pMinDist1,
   unsigned int m,
   unsigned short pblock[])
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_featureMatch_initialize_init(pMinDist0, pMinDist1, m, pblock);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_featureMatch_initialize_vloops(pblock);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

#pragma DATA_SECTION(__pblock_vcop_findTwoBestMatches, ".vcop_parameter_block")
#pragma DATA_ALIGN(__pblock_vcop_findTwoBestMatches, __ALIGNOF__(int));
unsigned short __pblock_vcop_findTwoBestMatches[18];

unsigned int vcop_findTwoBestMatches_param_count(void)
{
   return 18u;
}

unsigned int vcop_findTwoBestMatches_ctrl_count(void)
{
   return 0u;
}

unsigned int vcop_findTwoBestMatches_init(
   __vptr_uint32 pHammingDistance,
   __vptr_uint32 pMinDist0,
   __vptr_uint32 pMinDist1,
   unsigned char stride,
   unsigned int n,
   unsigned short pblock[])
{
   int __offset = 0;
   /* Loop 1 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), (1)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), (n)-1u);
   __vcop_pblock_init32(pblock, __offset+_PREG(6), (uchar *)pMinDist1);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)pMinDist1+8u*4);
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)pHammingDistance);
   __vcop_pblock_init32(pblock, __offset+_PREG(12), (uchar *)pHammingDistance+8u*4);
   __vcop_pblock_init16(pblock, __offset+_PREG(14), (4*stride));
   __vcop_pblock_init16(pblock, __offset+_PREG(15),  -(4*stride)*((n)-1u));
   __vcop_pblock_init32(pblock, __offset+_PREG(16), (uchar *)pMinDist0);
   __vcop_pblock_init32(pblock, __offset+_PREG(18), (uchar *)pMinDist0+8u*4);
   __offset += 18;

   return 18u;
}

void vcop_findTwoBestMatches_vloops(
   unsigned short pblock[])
{
   /* Kernel-wide Vector Registers */

   __vcop_param(&pblock[0]);

   /* VLOOP 1 Start */

   /* VLOOP Local Vector Registers */
   #pragma VCC_VREG("Vmin00", 16);
   #pragma VCC_VREG("Vmin01", 17);
   #pragma VCC_VREG("Vmin10", 18);
   #pragma VCC_VREG("Vmin11", 19);
   #pragma VCC_VREG("Vin0", 20);
   #pragma VCC_VREG("Vin1", 21);
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("Addr0", "A0");
   #pragma EVE_REG("AddrIn", "A1");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I0", "I3");
   #pragma EVE_REG("I1", "I4");
   

   __vcop_vloop(__vcop_compute(), 17u, 9u, 1u);
   __vcop_vagen(_AGEN(0), _PREG(0), _PREG(1), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(1), _PREG(14), _PREG(15), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeWU(), __vcop_npt(), _PREG(16), _AGEN(0), _VREG(16), __vcop_i4_zero());
   __vcop_vload(__vcop_sizeWU(), __vcop_npt(), _PREG(18), _AGEN(0), _VREG(17), __vcop_i4_zero());
   __vcop_vload(__vcop_sizeWU(), __vcop_npt(), _PREG(6), _AGEN(0), _VREG(18), __vcop_i4_zero());
   __vcop_vload(__vcop_sizeWU(), __vcop_npt(), _PREG(8), _AGEN(0), _VREG(19), __vcop_i4_zero());
   __vcop_vload(__vcop_sizeWU(), __vcop_npt(), _PREG(10), _AGEN(1), _VREG(20), __vcop_alws());
   __vcop_vload(__vcop_sizeWU(), __vcop_npt(), _PREG(12), _AGEN(1), _VREG(21), __vcop_alws());
   __vcop_vsort2(_VREG(16), _VREG(20));
   __vcop_vsort2(_VREG(17), _VREG(21));
   __vcop_vsort2(_VREG(18), _VREG(20));
   __vcop_vsort2(_VREG(19), _VREG(21));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeWU(), __vcop_npt(), __vcop_last_i4(), _VREG(16), _PREG(16), _AGEN(0), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeWU(), __vcop_npt(), __vcop_last_i4(), _VREG(17), _PREG(18), _AGEN(0), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeWU(), __vcop_npt(), __vcop_last_i4(), _VREG(18), _PREG(6), _AGEN(0), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeWU(), __vcop_npt(), __vcop_last_i4(), _VREG(19), _PREG(8), _AGEN(0), _PREG(0));
   __vcop_vloop_end(1u);

}

void vcop_findTwoBestMatches(
   __vptr_uint32 pHammingDistance,
   __vptr_uint32 pMinDist0,
   __vptr_uint32 pMinDist1,
   unsigned char stride,
   unsigned int n)
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_findTwoBestMatches_init(pHammingDistance, pMinDist0, pMinDist1, stride, n, __pblock_vcop_findTwoBestMatches);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_findTwoBestMatches_vloops(__pblock_vcop_findTwoBestMatches);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

void vcop_findTwoBestMatches_custom(
   __vptr_uint32 pHammingDistance,
   __vptr_uint32 pMinDist0,
   __vptr_uint32 pMinDist1,
   unsigned char stride,
   unsigned int n,
   unsigned short pblock[])
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_findTwoBestMatches_init(pHammingDistance, pMinDist0, pMinDist1, stride, n, pblock);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_findTwoBestMatches_vloops(pblock);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

#pragma DATA_SECTION(__pblock_vcop_pickConfidentMatches, ".vcop_parameter_block")
#pragma DATA_ALIGN(__pblock_vcop_pickConfidentMatches, __ALIGNOF__(int));
unsigned short __pblock_vcop_pickConfidentMatches[20];

unsigned int vcop_pickConfidentMatches_param_count(void)
{
   return 20u;
}

unsigned int vcop_pickConfidentMatches_ctrl_count(void)
{
   return 0u;
}

unsigned int vcop_pickConfidentMatches_init(
   __vptr_uint16 pMinDist0,
   __vptr_uint16 pMinDist1,
   __vptr_uint16 pMatchIndex,
   unsigned int m,
   unsigned short minDistanceThres,
   unsigned short matchConfidence,
   unsigned short pblock[])
{
   int __offset = 0;
   /* Loop 1 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), ((m + (8u) - 1)/(8u))-1u);
   __vcop_pblock_init32(pblock, __offset+_PREG(6), minDistanceThres);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), 32768 - matchConfidence);
   __vcop_pblock_init32(pblock, __offset+_PREG(10), 0xFFFF);
   __vcop_pblock_init16(pblock, __offset+_PREG(12), __vcop_vop_round(2, 15));
   __vcop_pblock_init16(pblock, __offset+_PREG(13), 32);
   __vcop_pblock_init32(pblock, __offset+_PREG(14), (uchar *)pMatchIndex);
   __vcop_pblock_init16(pblock, __offset+_PREG(16), 16);
   __vcop_pblock_init32(pblock, __offset+_PREG(18), (uchar *)pMinDist0);
   __vcop_pblock_init32(pblock, __offset+_PREG(20), (uchar *)pMinDist1+2);
   __offset += 20;

   return 20u;
}

void vcop_pickConfidentMatches_vloops(
   unsigned short pblock[])
{
   /* Kernel-wide Vector Registers */

   __vcop_param(&pblock[0]);

   /* VLOOP 1 Start */

   /* VLOOP Local Vector Registers */
   #pragma VCC_VREG("Vflag", 16);
   #pragma VCC_VREG("Vflag1", 17);
   #pragma VCC_VREG("Vflag2", 18);
   #pragma VCC_VREG("Vidx", 19);
   #pragma VCC_VREG("Vlim", 20);
   #pragma VCC_VREG("Vmc", 21);
   #pragma VCC_VREG("VminDist0", 22);
   #pragma VCC_VREG("VminDist1", 23);
   #pragma VCC_VREG("Vout", 24);
   #pragma VCC_VREG("Vthresh", 25);
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("AddrIn", "A0");
   #pragma EVE_REG("AddrOut", "A1");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I1", "I4");
   

   __vcop_vloop(__vcop_compute(), 14u, 10u, 1u);
   __vcop_vinit(__vcop_sizeW(), __vcop_alws(), _PREG(6), _VREG(25));
   __vcop_vinit(__vcop_sizeW(), __vcop_alws(), _PREG(8), _VREG(21));
   __vcop_vinit(__vcop_sizeW(), __vcop_alws(), _PREG(10), _VREG(24));
   __vcop_vagen(_AGEN(0), _PREG(13), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(1), _PREG(16), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeHU(), __vcop_dintrlv(), _PREG(18), _AGEN(0), _VPAIR(19,22), __vcop_alws());
   __vcop_vload(__vcop_sizeHU(), __vcop_ds2(), _PREG(20), _AGEN(0), _VREG(23), __vcop_alws());
   __vcop_vcmpge(_VREG(25), _VREG(22), _VREG(17));
   __vcop_vmpy(_VREG(21), _VREG(23), _VREG(20), _PREG(12));
   __vcop_vcmpge(_VREG(20), _VREG(22), _VREG(18));
   __vcop_vand(_VREG(17), _VREG(18), _VREG(16));
   __vcop_vsel(_VREG(16), _VREG(19), _VREG(24));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeHU(), __vcop_npt(), __vcop_alws(), _VREG(24), _PREG(14), _AGEN(1), _PREG(0));
   __vcop_vloop_end(1u);

}

void vcop_pickConfidentMatches(
   __vptr_uint16 pMinDist0,
   __vptr_uint16 pMinDist1,
   __vptr_uint16 pMatchIndex,
   unsigned int m,
   unsigned short minDistanceThres,
   unsigned short matchConfidence)
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_pickConfidentMatches_init(pMinDist0, pMinDist1, pMatchIndex, m, minDistanceThres, matchConfidence, __pblock_vcop_pickConfidentMatches);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_pickConfidentMatches_vloops(__pblock_vcop_pickConfidentMatches);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

void vcop_pickConfidentMatches_custom(
   __vptr_uint16 pMinDist0,
   __vptr_uint16 pMinDist1,
   __vptr_uint16 pMatchIndex,
   unsigned int m,
   unsigned short minDistanceThres,
   unsigned short matchConfidence,
   unsigned short pblock[])
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_pickConfidentMatches_init(pMinDist0, pMinDist1, pMatchIndex, m, minDistanceThres, matchConfidence, pblock);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_pickConfidentMatches_vloops(pblock);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

#pragma DATA_SECTION(__pblock_vcop_featureMatch_32_pblk_update, ".vcop_parameter_block")
#pragma DATA_ALIGN(__pblock_vcop_featureMatch_32_pblk_update, __ALIGNOF__(int));
unsigned short __pblock_vcop_featureMatch_32_pblk_update[22];

unsigned int vcop_featureMatch_32_pblk_update_param_count(void)
{
   return 22u;
}

unsigned int vcop_featureMatch_32_pblk_update_ctrl_count(void)
{
   return 0u;
}

unsigned int vcop_featureMatch_32_pblk_update_init(
   __vptr_uint32 pFeatureMatchParamBlk,
   __vptr_uint32 pBestMatchesParamBlk,
   unsigned short str2ByteIncr,
   unsigned short minDistIncr,
   unsigned short pblock[])
{
   int __offset = 0;
   /* Loop 1 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), (1)-1u);
   __vcop_pblock_init32(pblock, __offset+_PREG(6), 32);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)pFeatureMatchParamBlk+12);
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)pBestMatchesParamBlk+28);
   __vcop_pblock_init32(pblock, __offset+_PREG(12), (uchar *)pBestMatchesParamBlk+8);
   __vcop_pblock_init32(pblock, __offset+_PREG(14), (uchar *)pFeatureMatchParamBlk+16);
   __vcop_pblock_init32(pblock, __offset+_PREG(16), (uchar *)pBestMatchesParamBlk+32);
   __vcop_pblock_init32(pblock, __offset+_PREG(18), (uchar *)pBestMatchesParamBlk+12);
   __vcop_pblock_init32(pblock, __offset+_PREG(20), str2ByteIncr);
   __vcop_pblock_init32(pblock, __offset+_PREG(22), minDistIncr);
   __offset += 22;

   return 22u;
}

void vcop_featureMatch_32_pblk_update_vloops(
   unsigned short pblock[])
{
   /* Kernel-wide Vector Registers */

   __vcop_param(&pblock[0]);

   /* VLOOP 1 Start */

   /* VLOOP Local Vector Registers */
   #pragma VCC_VREG("VK32", 16);
   #pragma VCC_VREG("Vincr", 17);
   #pragma VCC_VREG("VminDist0", 18);
   #pragma VCC_VREG("VminDist0_", 19);
   #pragma VCC_VREG("VminDist1", 20);
   #pragma VCC_VREG("VminDist1_", 21);
   #pragma VCC_VREG("VminDistIncr", 22);
   #pragma VCC_VREG("Vstr2", 23);
   #pragma VCC_VREG("Vstr2_new", 24);
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("Addr0", "A0");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I1", "I4");
   

   __vcop_vloop(__vcop_compute(), 19u, 11u, 1u);
   __vcop_vinit(__vcop_sizeW(), __vcop_alws(), _PREG(20), _VREG(17));
   __vcop_vinit(__vcop_sizeW(), __vcop_alws(), _PREG(22), _VREG(22));
   __vcop_vinit(__vcop_sizeW(), __vcop_alws(), _PREG(6), _VREG(16));
   __vcop_vagen(_AGEN(0), _PREG(1), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeWU(), __vcop_1pt(), _PREG(8), _AGEN(0), _VREG(23), __vcop_alws());
   __vcop_vload(__vcop_sizeWU(), __vcop_1pt(), _PREG(10), _AGEN(0), _VREG(18), __vcop_alws());
   __vcop_vload(__vcop_sizeWU(), __vcop_1pt(), _PREG(12), _AGEN(0), _VREG(20), __vcop_alws());
   __vcop_vadd(_VREG(23), _VREG(17), _VREG(24));
   __vcop_vadd(_VREG(18), _VREG(22), _VREG(18));
   __vcop_vadd(_VREG(20), _VREG(22), _VREG(20));
   __vcop_vadd(_VREG(18), _VREG(16), _VREG(19));
   __vcop_vadd(_VREG(20), _VREG(16), _VREG(21));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeWU(), __vcop_1pt(), __vcop_alws(), _VREG(24), _PREG(8), _AGEN(0), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeWU(), __vcop_1pt(), __vcop_alws(), _VREG(24), _PREG(14), _AGEN(0), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeWU(), __vcop_1pt(), __vcop_alws(), _VREG(18), _PREG(10), _AGEN(0), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeWU(), __vcop_1pt(), __vcop_alws(), _VREG(19), _PREG(16), _AGEN(0), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeWU(), __vcop_1pt(), __vcop_alws(), _VREG(20), _PREG(12), _AGEN(0), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeWU(), __vcop_1pt(), __vcop_alws(), _VREG(21), _PREG(18), _AGEN(0), _PREG(0));
   __vcop_vloop_end(1u);

}

void vcop_featureMatch_32_pblk_update(
   __vptr_uint32 pFeatureMatchParamBlk,
   __vptr_uint32 pBestMatchesParamBlk,
   unsigned short str2ByteIncr,
   unsigned short minDistIncr)
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_featureMatch_32_pblk_update_init(pFeatureMatchParamBlk, pBestMatchesParamBlk, str2ByteIncr, minDistIncr, __pblock_vcop_featureMatch_32_pblk_update);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_featureMatch_32_pblk_update_vloops(__pblock_vcop_featureMatch_32_pblk_update);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

void vcop_featureMatch_32_pblk_update_custom(
   __vptr_uint32 pFeatureMatchParamBlk,
   __vptr_uint32 pBestMatchesParamBlk,
   unsigned short str2ByteIncr,
   unsigned short minDistIncr,
   unsigned short pblock[])
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_featureMatch_32_pblk_update_init(pFeatureMatchParamBlk, pBestMatchesParamBlk, str2ByteIncr, minDistIncr, pblock);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_featureMatch_32_pblk_update_vloops(pblock);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

#pragma DATA_SECTION(__pblock_vcop_featureMatch_32_pblk_reset, ".vcop_parameter_block")
#pragma DATA_ALIGN(__pblock_vcop_featureMatch_32_pblk_reset, __ALIGNOF__(int));
unsigned short __pblock_vcop_featureMatch_32_pblk_reset[34];

unsigned int vcop_featureMatch_32_pblk_reset_param_count(void)
{
   return 34u;
}

unsigned int vcop_featureMatch_32_pblk_reset_ctrl_count(void)
{
   return 0u;
}

unsigned int vcop_featureMatch_32_pblk_reset_init(
   __vptr_int32 pFeatureMatchParamBlk,
   __vptr_uint32 pBestMatchesParamBlk,
   unsigned short startIdxIncr,
   unsigned int maxStartIdx,
   unsigned int str2Addr,
   unsigned int minDist0Addr,
   unsigned int minDist1Addr,
   unsigned short pblock[])
{
   int __offset = 0;
   /* Loop 1 PREGS */
   const int preg_ref7 = _PREG(20);

   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), (1)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(6), __vcop_store_round_sat(SM_4PARAM,preg_ref7,RM_NONE,0));
   __vcop_pblock_init32(pblock, __offset+_PREG(8), minDist0Addr);
   __vcop_pblock_init32(pblock, __offset+_PREG(10), minDist1Addr);
   __vcop_pblock_init32(pblock, __offset+_PREG(12), 32);
   __vcop_pblock_init32(pblock, __offset+_PREG(14), (uchar *)pFeatureMatchParamBlk+116);
   __vcop_pblock_init32(pblock, __offset+_PREG(16), (uchar *)pFeatureMatchParamBlk+12);
   __vcop_pblock_init32(pblock, __offset+_PREG(18), (uchar *)pFeatureMatchParamBlk+16);
   __vcop_pblock_4param_init(pblock, __offset+_PREG(20), maxStartIdx,-1,0,0);
   __vcop_pblock_init32(pblock, __offset+_PREG(24), (uchar *)pBestMatchesParamBlk+28);
   __vcop_pblock_init32(pblock, __offset+_PREG(26), (uchar *)pBestMatchesParamBlk+32);
   __vcop_pblock_init32(pblock, __offset+_PREG(28), (uchar *)pBestMatchesParamBlk+8);
   __vcop_pblock_init32(pblock, __offset+_PREG(30), (uchar *)pBestMatchesParamBlk+12);
   __vcop_pblock_init32(pblock, __offset+_PREG(32), startIdxIncr);
   __vcop_pblock_init32(pblock, __offset+_PREG(34), str2Addr);
   __offset += 34;

   return 34u;
}

void vcop_featureMatch_32_pblk_reset_vloops(
   unsigned short pblock[])
{
   /* Kernel-wide Vector Registers */

   __vcop_param(&pblock[0]);

   /* VLOOP 1 Start */

   /* VLOOP Local Vector Registers */
   #pragma VCC_VREG("VK32", 16);
   #pragma VCC_VREG("Vidx", 17);
   #pragma VCC_VREG("Vidx_new", 18);
   #pragma VCC_VREG("Vincr", 19);
   #pragma VCC_VREG("VminDist0", 20);
   #pragma VCC_VREG("VminDist0_", 21);
   #pragma VCC_VREG("VminDist1", 22);
   #pragma VCC_VREG("VminDist1_", 23);
   #pragma VCC_VREG("Vstr2", 24);
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("Addr0", "A0");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I1", "I4");
   

   __vcop_vloop(__vcop_compute(), 18u, 17u, 1u);
   __vcop_vinit(__vcop_sizeW(), __vcop_alws(), _PREG(32), _VREG(19));
   __vcop_vinit(__vcop_sizeW(), __vcop_alws(), _PREG(34), _VREG(24));
   __vcop_vinit(__vcop_sizeW(), __vcop_alws(), _PREG(8), _VREG(20));
   __vcop_vinit(__vcop_sizeW(), __vcop_alws(), _PREG(10), _VREG(22));
   __vcop_vinit(__vcop_sizeW(), __vcop_alws(), _PREG(12), _VREG(16));
   __vcop_vagen(_AGEN(0), _PREG(1), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeW(), __vcop_1pt(), _PREG(14), _AGEN(0), _VREG(17), __vcop_alws());
   __vcop_vadd(_VREG(17), _VREG(19), _VREG(18));
   __vcop_vadd(_VREG(20), _VREG(16), _VREG(21));
   __vcop_vadd(_VREG(22), _VREG(16), _VREG(23));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeW(), __vcop_1pt(), __vcop_alws(), _VREG(24), _PREG(16), _AGEN(0), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeW(), __vcop_1pt(), __vcop_alws(), _VREG(24), _PREG(18), _AGEN(0), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeW(), __vcop_1pt(), __vcop_alws(), _VREG(18), _PREG(14), _AGEN(0), _PREG(6));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeWU(), __vcop_1pt(), __vcop_alws(), _VREG(20), _PREG(24), _AGEN(0), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeWU(), __vcop_1pt(), __vcop_alws(), _VREG(21), _PREG(26), _AGEN(0), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeWU(), __vcop_1pt(), __vcop_alws(), _VREG(22), _PREG(28), _AGEN(0), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeWU(), __vcop_1pt(), __vcop_alws(), _VREG(23), _PREG(30), _AGEN(0), _PREG(0));
   __vcop_vloop_end(1u);

}

void vcop_featureMatch_32_pblk_reset(
   __vptr_int32 pFeatureMatchParamBlk,
   __vptr_uint32 pBestMatchesParamBlk,
   unsigned short startIdxIncr,
   unsigned int maxStartIdx,
   unsigned int str2Addr,
   unsigned int minDist0Addr,
   unsigned int minDist1Addr)
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_featureMatch_32_pblk_reset_init(pFeatureMatchParamBlk, pBestMatchesParamBlk, startIdxIncr, maxStartIdx, str2Addr, minDist0Addr, minDist1Addr, __pblock_vcop_featureMatch_32_pblk_reset);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_featureMatch_32_pblk_reset_vloops(__pblock_vcop_featureMatch_32_pblk_reset);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

void vcop_featureMatch_32_pblk_reset_custom(
   __vptr_int32 pFeatureMatchParamBlk,
   __vptr_uint32 pBestMatchesParamBlk,
   unsigned short startIdxIncr,
   unsigned int maxStartIdx,
   unsigned int str2Addr,
   unsigned int minDist0Addr,
   unsigned int minDist1Addr,
   unsigned short pblock[])
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_featureMatch_32_pblk_reset_init(pFeatureMatchParamBlk, pBestMatchesParamBlk, startIdxIncr, maxStartIdx, str2Addr, minDist0Addr, minDist1Addr, pblock);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_featureMatch_32_pblk_reset_vloops(pblock);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

#pragma DATA_SECTION(__pblock_vcop_featureMatch_lt_32_pblk_update, ".vcop_parameter_block")
#pragma DATA_ALIGN(__pblock_vcop_featureMatch_lt_32_pblk_update, __ALIGNOF__(int));
unsigned short __pblock_vcop_featureMatch_lt_32_pblk_update[22];

unsigned int vcop_featureMatch_lt_32_pblk_update_param_count(void)
{
   return 22u;
}

unsigned int vcop_featureMatch_lt_32_pblk_update_ctrl_count(void)
{
   return 0u;
}

unsigned int vcop_featureMatch_lt_32_pblk_update_init(
   __vptr_uint32 pFeatureMatchParamBlk,
   __vptr_uint32 pBestMatchesParamBlk,
   unsigned short str2ByteIncr,
   unsigned short minDistIncr,
   unsigned short pblock[])
{
   int __offset = 0;
   /* Loop 1 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), (1)-1u);
   __vcop_pblock_init32(pblock, __offset+_PREG(6), 32);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)pFeatureMatchParamBlk+16);
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)pBestMatchesParamBlk+28);
   __vcop_pblock_init32(pblock, __offset+_PREG(12), (uchar *)pBestMatchesParamBlk+8);
   __vcop_pblock_init32(pblock, __offset+_PREG(14), (uchar *)pFeatureMatchParamBlk+20);
   __vcop_pblock_init32(pblock, __offset+_PREG(16), (uchar *)pBestMatchesParamBlk+32);
   __vcop_pblock_init32(pblock, __offset+_PREG(18), (uchar *)pBestMatchesParamBlk+12);
   __vcop_pblock_init32(pblock, __offset+_PREG(20), str2ByteIncr);
   __vcop_pblock_init32(pblock, __offset+_PREG(22), minDistIncr);
   __offset += 22;

   return 22u;
}

void vcop_featureMatch_lt_32_pblk_update_vloops(
   unsigned short pblock[])
{
   /* Kernel-wide Vector Registers */

   __vcop_param(&pblock[0]);

   /* VLOOP 1 Start */

   /* VLOOP Local Vector Registers */
   #pragma VCC_VREG("VK32", 16);
   #pragma VCC_VREG("Vincr", 17);
   #pragma VCC_VREG("VminDist0", 18);
   #pragma VCC_VREG("VminDist0_", 19);
   #pragma VCC_VREG("VminDist1", 20);
   #pragma VCC_VREG("VminDist1_", 21);
   #pragma VCC_VREG("VminDistIncr", 22);
   #pragma VCC_VREG("Vstr2", 23);
   #pragma VCC_VREG("Vstr2_new", 24);
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("Addr0", "A0");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I1", "I4");
   

   __vcop_vloop(__vcop_compute(), 19u, 11u, 1u);
   __vcop_vinit(__vcop_sizeW(), __vcop_alws(), _PREG(20), _VREG(17));
   __vcop_vinit(__vcop_sizeW(), __vcop_alws(), _PREG(22), _VREG(22));
   __vcop_vinit(__vcop_sizeW(), __vcop_alws(), _PREG(6), _VREG(16));
   __vcop_vagen(_AGEN(0), _PREG(1), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeWU(), __vcop_1pt(), _PREG(8), _AGEN(0), _VREG(23), __vcop_alws());
   __vcop_vload(__vcop_sizeWU(), __vcop_1pt(), _PREG(10), _AGEN(0), _VREG(18), __vcop_alws());
   __vcop_vload(__vcop_sizeWU(), __vcop_1pt(), _PREG(12), _AGEN(0), _VREG(20), __vcop_alws());
   __vcop_vadd(_VREG(23), _VREG(17), _VREG(24));
   __vcop_vadd(_VREG(18), _VREG(22), _VREG(18));
   __vcop_vadd(_VREG(20), _VREG(22), _VREG(20));
   __vcop_vadd(_VREG(18), _VREG(16), _VREG(19));
   __vcop_vadd(_VREG(20), _VREG(16), _VREG(21));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeWU(), __vcop_1pt(), __vcop_alws(), _VREG(24), _PREG(8), _AGEN(0), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeWU(), __vcop_1pt(), __vcop_alws(), _VREG(24), _PREG(14), _AGEN(0), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeWU(), __vcop_1pt(), __vcop_alws(), _VREG(18), _PREG(10), _AGEN(0), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeWU(), __vcop_1pt(), __vcop_alws(), _VREG(19), _PREG(16), _AGEN(0), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeWU(), __vcop_1pt(), __vcop_alws(), _VREG(20), _PREG(12), _AGEN(0), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeWU(), __vcop_1pt(), __vcop_alws(), _VREG(21), _PREG(18), _AGEN(0), _PREG(0));
   __vcop_vloop_end(1u);

}

void vcop_featureMatch_lt_32_pblk_update(
   __vptr_uint32 pFeatureMatchParamBlk,
   __vptr_uint32 pBestMatchesParamBlk,
   unsigned short str2ByteIncr,
   unsigned short minDistIncr)
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_featureMatch_lt_32_pblk_update_init(pFeatureMatchParamBlk, pBestMatchesParamBlk, str2ByteIncr, minDistIncr, __pblock_vcop_featureMatch_lt_32_pblk_update);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_featureMatch_lt_32_pblk_update_vloops(__pblock_vcop_featureMatch_lt_32_pblk_update);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

void vcop_featureMatch_lt_32_pblk_update_custom(
   __vptr_uint32 pFeatureMatchParamBlk,
   __vptr_uint32 pBestMatchesParamBlk,
   unsigned short str2ByteIncr,
   unsigned short minDistIncr,
   unsigned short pblock[])
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_featureMatch_lt_32_pblk_update_init(pFeatureMatchParamBlk, pBestMatchesParamBlk, str2ByteIncr, minDistIncr, pblock);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_featureMatch_lt_32_pblk_update_vloops(pblock);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

#pragma DATA_SECTION(__pblock_vcop_featureMatch_lt_32_pblk_reset, ".vcop_parameter_block")
#pragma DATA_ALIGN(__pblock_vcop_featureMatch_lt_32_pblk_reset, __ALIGNOF__(int));
unsigned short __pblock_vcop_featureMatch_lt_32_pblk_reset[34];

unsigned int vcop_featureMatch_lt_32_pblk_reset_param_count(void)
{
   return 34u;
}

unsigned int vcop_featureMatch_lt_32_pblk_reset_ctrl_count(void)
{
   return 0u;
}

unsigned int vcop_featureMatch_lt_32_pblk_reset_init(
   __vptr_int32 pFeatureMatchParamBlk,
   __vptr_uint32 pBestMatchesParamBlk,
   unsigned short startIdxIncr,
   unsigned int maxStartIdx,
   unsigned int str2Addr,
   unsigned int minDist0Addr,
   unsigned int minDist1Addr,
   unsigned short pblock[])
{
   int __offset = 0;
   /* Loop 1 PREGS */
   const int preg_ref8 = _PREG(20);

   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), (1)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(6), __vcop_store_round_sat(SM_4PARAM,preg_ref8,RM_NONE,0));
   __vcop_pblock_init32(pblock, __offset+_PREG(8), minDist0Addr);
   __vcop_pblock_init32(pblock, __offset+_PREG(10), minDist1Addr);
   __vcop_pblock_init32(pblock, __offset+_PREG(12), 32);
   __vcop_pblock_init32(pblock, __offset+_PREG(14), (uchar *)pFeatureMatchParamBlk+108);
   __vcop_pblock_init32(pblock, __offset+_PREG(16), (uchar *)pFeatureMatchParamBlk+16);
   __vcop_pblock_init32(pblock, __offset+_PREG(18), (uchar *)pFeatureMatchParamBlk+20);
   __vcop_pblock_4param_init(pblock, __offset+_PREG(20), maxStartIdx,-1,0,0);
   __vcop_pblock_init32(pblock, __offset+_PREG(24), (uchar *)pBestMatchesParamBlk+28);
   __vcop_pblock_init32(pblock, __offset+_PREG(26), (uchar *)pBestMatchesParamBlk+32);
   __vcop_pblock_init32(pblock, __offset+_PREG(28), (uchar *)pBestMatchesParamBlk+8);
   __vcop_pblock_init32(pblock, __offset+_PREG(30), (uchar *)pBestMatchesParamBlk+12);
   __vcop_pblock_init32(pblock, __offset+_PREG(32), startIdxIncr);
   __vcop_pblock_init32(pblock, __offset+_PREG(34), str2Addr);
   __offset += 34;

   return 34u;
}

void vcop_featureMatch_lt_32_pblk_reset_vloops(
   unsigned short pblock[])
{
   /* Kernel-wide Vector Registers */

   __vcop_param(&pblock[0]);

   /* VLOOP 1 Start */

   /* VLOOP Local Vector Registers */
   #pragma VCC_VREG("VK32", 16);
   #pragma VCC_VREG("Vidx", 17);
   #pragma VCC_VREG("Vidx_new", 18);
   #pragma VCC_VREG("Vincr", 19);
   #pragma VCC_VREG("VminDist0", 20);
   #pragma VCC_VREG("VminDist0_", 21);
   #pragma VCC_VREG("VminDist1", 22);
   #pragma VCC_VREG("VminDist1_", 23);
   #pragma VCC_VREG("Vstr2", 24);
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("Addr0", "A0");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I1", "I4");
   

   __vcop_vloop(__vcop_compute(), 18u, 17u, 1u);
   __vcop_vinit(__vcop_sizeW(), __vcop_alws(), _PREG(32), _VREG(19));
   __vcop_vinit(__vcop_sizeW(), __vcop_alws(), _PREG(34), _VREG(24));
   __vcop_vinit(__vcop_sizeW(), __vcop_alws(), _PREG(8), _VREG(20));
   __vcop_vinit(__vcop_sizeW(), __vcop_alws(), _PREG(10), _VREG(22));
   __vcop_vinit(__vcop_sizeW(), __vcop_alws(), _PREG(12), _VREG(16));
   __vcop_vagen(_AGEN(0), _PREG(1), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeW(), __vcop_1pt(), _PREG(14), _AGEN(0), _VREG(17), __vcop_alws());
   __vcop_vadd(_VREG(17), _VREG(19), _VREG(18));
   __vcop_vadd(_VREG(20), _VREG(16), _VREG(21));
   __vcop_vadd(_VREG(22), _VREG(16), _VREG(23));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeW(), __vcop_1pt(), __vcop_alws(), _VREG(24), _PREG(16), _AGEN(0), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeW(), __vcop_1pt(), __vcop_alws(), _VREG(24), _PREG(18), _AGEN(0), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeW(), __vcop_1pt(), __vcop_alws(), _VREG(18), _PREG(14), _AGEN(0), _PREG(6));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeWU(), __vcop_1pt(), __vcop_alws(), _VREG(20), _PREG(24), _AGEN(0), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeWU(), __vcop_1pt(), __vcop_alws(), _VREG(21), _PREG(26), _AGEN(0), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeWU(), __vcop_1pt(), __vcop_alws(), _VREG(22), _PREG(28), _AGEN(0), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeWU(), __vcop_1pt(), __vcop_alws(), _VREG(23), _PREG(30), _AGEN(0), _PREG(0));
   __vcop_vloop_end(1u);

}

void vcop_featureMatch_lt_32_pblk_reset(
   __vptr_int32 pFeatureMatchParamBlk,
   __vptr_uint32 pBestMatchesParamBlk,
   unsigned short startIdxIncr,
   unsigned int maxStartIdx,
   unsigned int str2Addr,
   unsigned int minDist0Addr,
   unsigned int minDist1Addr)
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_featureMatch_lt_32_pblk_reset_init(pFeatureMatchParamBlk, pBestMatchesParamBlk, startIdxIncr, maxStartIdx, str2Addr, minDist0Addr, minDist1Addr, __pblock_vcop_featureMatch_lt_32_pblk_reset);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_featureMatch_lt_32_pblk_reset_vloops(__pblock_vcop_featureMatch_lt_32_pblk_reset);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

void vcop_featureMatch_lt_32_pblk_reset_custom(
   __vptr_int32 pFeatureMatchParamBlk,
   __vptr_uint32 pBestMatchesParamBlk,
   unsigned short startIdxIncr,
   unsigned int maxStartIdx,
   unsigned int str2Addr,
   unsigned int minDist0Addr,
   unsigned int minDist1Addr,
   unsigned short pblock[])
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_featureMatch_lt_32_pblk_reset_init(pFeatureMatchParamBlk, pBestMatchesParamBlk, startIdxIncr, maxStartIdx, str2Addr, minDist0Addr, minDist1Addr, pblock);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_featureMatch_lt_32_pblk_reset_vloops(pblock);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

#pragma DATA_SECTION(__pblock_vcop_featureMatch_gt_32_pblk_update, ".vcop_parameter_block")
#pragma DATA_ALIGN(__pblock_vcop_featureMatch_gt_32_pblk_update, __ALIGNOF__(int));
unsigned short __pblock_vcop_featureMatch_gt_32_pblk_update[22];

unsigned int vcop_featureMatch_gt_32_pblk_update_param_count(void)
{
   return 22u;
}

unsigned int vcop_featureMatch_gt_32_pblk_update_ctrl_count(void)
{
   return 0u;
}

unsigned int vcop_featureMatch_gt_32_pblk_update_init(
   __vptr_uint32 pFeatureMatchParamBlk,
   __vptr_uint32 pBestMatchesParamBlk,
   unsigned short str2ByteIncr,
   unsigned short minDistIncr,
   unsigned short pblock[])
{
   int __offset = 0;
   /* Loop 1 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), (1)-1u);
   __vcop_pblock_init32(pblock, __offset+_PREG(6), 32);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)pFeatureMatchParamBlk+16);
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)pBestMatchesParamBlk+28);
   __vcop_pblock_init32(pblock, __offset+_PREG(12), (uchar *)pBestMatchesParamBlk+8);
   __vcop_pblock_init32(pblock, __offset+_PREG(14), (uchar *)pFeatureMatchParamBlk+24);
   __vcop_pblock_init32(pblock, __offset+_PREG(16), (uchar *)pBestMatchesParamBlk+32);
   __vcop_pblock_init32(pblock, __offset+_PREG(18), (uchar *)pBestMatchesParamBlk+12);
   __vcop_pblock_init32(pblock, __offset+_PREG(20), str2ByteIncr);
   __vcop_pblock_init32(pblock, __offset+_PREG(22), minDistIncr);
   __offset += 22;

   return 22u;
}

void vcop_featureMatch_gt_32_pblk_update_vloops(
   unsigned short pblock[])
{
   /* Kernel-wide Vector Registers */

   __vcop_param(&pblock[0]);

   /* VLOOP 1 Start */

   /* VLOOP Local Vector Registers */
   #pragma VCC_VREG("VK32", 16);
   #pragma VCC_VREG("Vincr", 17);
   #pragma VCC_VREG("VminDist0", 18);
   #pragma VCC_VREG("VminDist0_", 19);
   #pragma VCC_VREG("VminDist1", 20);
   #pragma VCC_VREG("VminDist1_", 21);
   #pragma VCC_VREG("VminDistIncr", 22);
   #pragma VCC_VREG("Vstr2", 23);
   #pragma VCC_VREG("Vstr2_new", 24);
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("Addr0", "A0");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I1", "I4");
   

   __vcop_vloop(__vcop_compute(), 19u, 11u, 1u);
   __vcop_vinit(__vcop_sizeW(), __vcop_alws(), _PREG(20), _VREG(17));
   __vcop_vinit(__vcop_sizeW(), __vcop_alws(), _PREG(22), _VREG(22));
   __vcop_vinit(__vcop_sizeW(), __vcop_alws(), _PREG(6), _VREG(16));
   __vcop_vagen(_AGEN(0), _PREG(1), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeWU(), __vcop_1pt(), _PREG(8), _AGEN(0), _VREG(23), __vcop_alws());
   __vcop_vload(__vcop_sizeWU(), __vcop_1pt(), _PREG(10), _AGEN(0), _VREG(18), __vcop_alws());
   __vcop_vload(__vcop_sizeWU(), __vcop_1pt(), _PREG(12), _AGEN(0), _VREG(20), __vcop_alws());
   __vcop_vadd(_VREG(23), _VREG(17), _VREG(24));
   __vcop_vadd(_VREG(18), _VREG(22), _VREG(18));
   __vcop_vadd(_VREG(20), _VREG(22), _VREG(20));
   __vcop_vadd(_VREG(18), _VREG(16), _VREG(19));
   __vcop_vadd(_VREG(20), _VREG(16), _VREG(21));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeWU(), __vcop_1pt(), __vcop_alws(), _VREG(24), _PREG(8), _AGEN(0), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeWU(), __vcop_1pt(), __vcop_alws(), _VREG(24), _PREG(14), _AGEN(0), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeWU(), __vcop_1pt(), __vcop_alws(), _VREG(18), _PREG(10), _AGEN(0), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeWU(), __vcop_1pt(), __vcop_alws(), _VREG(19), _PREG(16), _AGEN(0), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeWU(), __vcop_1pt(), __vcop_alws(), _VREG(20), _PREG(12), _AGEN(0), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeWU(), __vcop_1pt(), __vcop_alws(), _VREG(21), _PREG(18), _AGEN(0), _PREG(0));
   __vcop_vloop_end(1u);

}

void vcop_featureMatch_gt_32_pblk_update(
   __vptr_uint32 pFeatureMatchParamBlk,
   __vptr_uint32 pBestMatchesParamBlk,
   unsigned short str2ByteIncr,
   unsigned short minDistIncr)
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_featureMatch_gt_32_pblk_update_init(pFeatureMatchParamBlk, pBestMatchesParamBlk, str2ByteIncr, minDistIncr, __pblock_vcop_featureMatch_gt_32_pblk_update);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_featureMatch_gt_32_pblk_update_vloops(__pblock_vcop_featureMatch_gt_32_pblk_update);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

void vcop_featureMatch_gt_32_pblk_update_custom(
   __vptr_uint32 pFeatureMatchParamBlk,
   __vptr_uint32 pBestMatchesParamBlk,
   unsigned short str2ByteIncr,
   unsigned short minDistIncr,
   unsigned short pblock[])
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_featureMatch_gt_32_pblk_update_init(pFeatureMatchParamBlk, pBestMatchesParamBlk, str2ByteIncr, minDistIncr, pblock);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_featureMatch_gt_32_pblk_update_vloops(pblock);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

#pragma DATA_SECTION(__pblock_vcop_featureMatch_gt_32_pblk_reset, ".vcop_parameter_block")
#pragma DATA_ALIGN(__pblock_vcop_featureMatch_gt_32_pblk_reset, __ALIGNOF__(int));
unsigned short __pblock_vcop_featureMatch_gt_32_pblk_reset[34];

unsigned int vcop_featureMatch_gt_32_pblk_reset_param_count(void)
{
   return 34u;
}

unsigned int vcop_featureMatch_gt_32_pblk_reset_ctrl_count(void)
{
   return 0u;
}

unsigned int vcop_featureMatch_gt_32_pblk_reset_init(
   __vptr_int32 pFeatureMatchParamBlk,
   __vptr_uint32 pBestMatchesParamBlk,
   unsigned short startIdxIncr,
   unsigned int maxStartIdx,
   unsigned int str2Addr,
   unsigned int minDist0Addr,
   unsigned int minDist1Addr,
   unsigned short pblock[])
{
   int __offset = 0;
   /* Loop 1 PREGS */
   const int preg_ref9 = _PREG(20);

   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), (1)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(6), __vcop_store_round_sat(SM_4PARAM,preg_ref9,RM_NONE,0));
   __vcop_pblock_init32(pblock, __offset+_PREG(8), minDist0Addr);
   __vcop_pblock_init32(pblock, __offset+_PREG(10), minDist1Addr);
   __vcop_pblock_init32(pblock, __offset+_PREG(12), 32);
   __vcop_pblock_init32(pblock, __offset+_PREG(14), (uchar *)pFeatureMatchParamBlk+120);
   __vcop_pblock_init32(pblock, __offset+_PREG(16), (uchar *)pFeatureMatchParamBlk+16);
   __vcop_pblock_init32(pblock, __offset+_PREG(18), (uchar *)pFeatureMatchParamBlk+24);
   __vcop_pblock_4param_init(pblock, __offset+_PREG(20), maxStartIdx,-1,0,0);
   __vcop_pblock_init32(pblock, __offset+_PREG(24), (uchar *)pBestMatchesParamBlk+28);
   __vcop_pblock_init32(pblock, __offset+_PREG(26), (uchar *)pBestMatchesParamBlk+32);
   __vcop_pblock_init32(pblock, __offset+_PREG(28), (uchar *)pBestMatchesParamBlk+8);
   __vcop_pblock_init32(pblock, __offset+_PREG(30), (uchar *)pBestMatchesParamBlk+12);
   __vcop_pblock_init32(pblock, __offset+_PREG(32), startIdxIncr);
   __vcop_pblock_init32(pblock, __offset+_PREG(34), str2Addr);
   __offset += 34;

   return 34u;
}

void vcop_featureMatch_gt_32_pblk_reset_vloops(
   unsigned short pblock[])
{
   /* Kernel-wide Vector Registers */

   __vcop_param(&pblock[0]);

   /* VLOOP 1 Start */

   /* VLOOP Local Vector Registers */
   #pragma VCC_VREG("VK32", 16);
   #pragma VCC_VREG("Vidx", 17);
   #pragma VCC_VREG("Vidx_new", 18);
   #pragma VCC_VREG("Vincr", 19);
   #pragma VCC_VREG("VminDist0", 20);
   #pragma VCC_VREG("VminDist0_", 21);
   #pragma VCC_VREG("VminDist1", 22);
   #pragma VCC_VREG("VminDist1_", 23);
   #pragma VCC_VREG("Vstr2", 24);
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("Addr0", "A0");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I1", "I4");
   

   __vcop_vloop(__vcop_compute(), 18u, 17u, 1u);
   __vcop_vinit(__vcop_sizeW(), __vcop_alws(), _PREG(32), _VREG(19));
   __vcop_vinit(__vcop_sizeW(), __vcop_alws(), _PREG(34), _VREG(24));
   __vcop_vinit(__vcop_sizeW(), __vcop_alws(), _PREG(8), _VREG(20));
   __vcop_vinit(__vcop_sizeW(), __vcop_alws(), _PREG(10), _VREG(22));
   __vcop_vinit(__vcop_sizeW(), __vcop_alws(), _PREG(12), _VREG(16));
   __vcop_vagen(_AGEN(0), _PREG(1), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeW(), __vcop_1pt(), _PREG(14), _AGEN(0), _VREG(17), __vcop_alws());
   __vcop_vadd(_VREG(17), _VREG(19), _VREG(18));
   __vcop_vadd(_VREG(20), _VREG(16), _VREG(21));
   __vcop_vadd(_VREG(22), _VREG(16), _VREG(23));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeW(), __vcop_1pt(), __vcop_alws(), _VREG(24), _PREG(16), _AGEN(0), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeW(), __vcop_1pt(), __vcop_alws(), _VREG(24), _PREG(18), _AGEN(0), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeW(), __vcop_1pt(), __vcop_alws(), _VREG(18), _PREG(14), _AGEN(0), _PREG(6));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeWU(), __vcop_1pt(), __vcop_alws(), _VREG(20), _PREG(24), _AGEN(0), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeWU(), __vcop_1pt(), __vcop_alws(), _VREG(21), _PREG(26), _AGEN(0), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeWU(), __vcop_1pt(), __vcop_alws(), _VREG(22), _PREG(28), _AGEN(0), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeWU(), __vcop_1pt(), __vcop_alws(), _VREG(23), _PREG(30), _AGEN(0), _PREG(0));
   __vcop_vloop_end(1u);

}

void vcop_featureMatch_gt_32_pblk_reset(
   __vptr_int32 pFeatureMatchParamBlk,
   __vptr_uint32 pBestMatchesParamBlk,
   unsigned short startIdxIncr,
   unsigned int maxStartIdx,
   unsigned int str2Addr,
   unsigned int minDist0Addr,
   unsigned int minDist1Addr)
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_featureMatch_gt_32_pblk_reset_init(pFeatureMatchParamBlk, pBestMatchesParamBlk, startIdxIncr, maxStartIdx, str2Addr, minDist0Addr, minDist1Addr, __pblock_vcop_featureMatch_gt_32_pblk_reset);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_featureMatch_gt_32_pblk_reset_vloops(__pblock_vcop_featureMatch_gt_32_pblk_reset);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

void vcop_featureMatch_gt_32_pblk_reset_custom(
   __vptr_int32 pFeatureMatchParamBlk,
   __vptr_uint32 pBestMatchesParamBlk,
   unsigned short startIdxIncr,
   unsigned int maxStartIdx,
   unsigned int str2Addr,
   unsigned int minDist0Addr,
   unsigned int minDist1Addr,
   unsigned short pblock[])
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_featureMatch_gt_32_pblk_reset_init(pFeatureMatchParamBlk, pBestMatchesParamBlk, startIdxIncr, maxStartIdx, str2Addr, minDist0Addr, minDist1Addr, pblock);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_featureMatch_gt_32_pblk_reset_vloops(pblock);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

#pragma DATA_SECTION(__pblock_vcop_twoBestMatches_update_n, ".vcop_parameter_block")
#pragma DATA_ALIGN(__pblock_vcop_twoBestMatches_update_n, __ALIGNOF__(int));
unsigned short __pblock_vcop_twoBestMatches_update_n[8];

unsigned int vcop_twoBestMatches_update_n_param_count(void)
{
   return 8u;
}

unsigned int vcop_twoBestMatches_update_n_ctrl_count(void)
{
   return 0u;
}

unsigned int vcop_twoBestMatches_update_n_init(
   __vptr_int16 pBestMatchesParamBlk,
   unsigned short n_new,
   unsigned short pblock[])
{
   int __offset = 0;
   /* Loop 1 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), (1)-1u);
   __vcop_pblock_init32(pblock, __offset+_PREG(6), n_new);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)pBestMatchesParamBlk+6);
   __offset += 8;

   return 8u;
}

void vcop_twoBestMatches_update_n_vloops(
   unsigned short pblock[])
{
   /* Kernel-wide Vector Registers */

   __vcop_param(&pblock[0]);

   /* VLOOP 1 Start */

   /* VLOOP Local Vector Registers */
   #pragma VCC_VREG("Vn", 16);
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("Addr0", "A0");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I1", "I4");
   

   __vcop_vloop(__vcop_compute(), 4u, 4u, 1u);
   __vcop_vinit(__vcop_sizeW(), __vcop_alws(), _PREG(6), _VREG(16));
   __vcop_vagen(_AGEN(0), _PREG(1), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeH(), __vcop_1pt(), __vcop_alws(), _VREG(16), _PREG(8), _AGEN(0), _PREG(0));
   __vcop_vloop_end(1u);

}

void vcop_twoBestMatches_update_n(
   __vptr_int16 pBestMatchesParamBlk,
   unsigned short n_new)
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_twoBestMatches_update_n_init(pBestMatchesParamBlk, n_new, __pblock_vcop_twoBestMatches_update_n);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_twoBestMatches_update_n_vloops(__pblock_vcop_twoBestMatches_update_n);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

void vcop_twoBestMatches_update_n_custom(
   __vptr_int16 pBestMatchesParamBlk,
   unsigned short n_new,
   unsigned short pblock[])
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_twoBestMatches_update_n_init(pBestMatchesParamBlk, n_new, pblock);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_twoBestMatches_update_n_vloops(pblock);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

