#include <vcop\vcop.h>

typedef unsigned char uchar;

#pragma DATA_SECTION(__pblock_vcop_hamming_distance, ".vcop_parameter_block")
#pragma DATA_ALIGN(__pblock_vcop_hamming_distance, __ALIGNOF__(int));
unsigned short __pblock_vcop_hamming_distance[62];

unsigned int vcop_hamming_distance_param_count(void)
{
   return 62u;
}

unsigned int vcop_hamming_distance_ctrl_count(void)
{
   return 0u;
}

unsigned int vcop_hamming_distance_init(
   __vptr_uint32 pString1,
   __vptr_uint32 pString2,
   __vptr_uint8 pStringByte1,
   __vptr_uint8 pStringByte2,
   unsigned int xsize,
   unsigned int ysize,
   unsigned int mode,
   unsigned int xpitch,
   __vptr_uint32 pHammingDistance,
   __vptr_uint16 pScratch,
   unsigned short pblock[])
{
   int __offset = 0;
   /* Loop 1 PREGS */
   const int preg_ref1 = _PREG(16);

   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), ((ysize+1)/2)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), ((xsize)/(4 * (8u)))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(6), __vcop_store_round_sat(SM_4PARAM,preg_ref1,RM_NONE,0));
   __vcop_pblock_init16(pblock, __offset+_PREG(7), 32);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)pString2);
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)pString1+xpitch);
   __vcop_pblock_init32(pblock, __offset+_PREG(12), (uchar *)pString2+xpitch*mode);
   __vcop_pblock_init32(pblock, __offset+_PREG(14), (uchar *)pScratch);
   __vcop_pblock_4param_init(pblock, __offset+_PREG(16), 0xFFFF,0xFFFF,0x0,0x0);
   __vcop_pblock_init32(pblock, __offset+_PREG(20), (uchar *)pScratch+sizeof(*pScratch)*8u);
   __vcop_pblock_init16(pblock, __offset+_PREG(22), (2*xpitch) -((4*8u))*(((xsize)/(4 * (8u)))-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(23), (2*xpitch*mode) -((4*8u))*(((xsize)/(4 * (8u)))-1u));
   __vcop_pblock_init32(pblock, __offset+_PREG(24), 0);
   __vcop_pblock_init32(pblock, __offset+_PREG(26), (uchar *)pString1);
   __offset += 26;

   /* Loop 2 PREGS */
   const int preg_ref2 = _PREG(12);

   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), (ysize)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), ((xsize % (4 * (8u))))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(6), __vcop_store_round_sat(SM_4PARAM,preg_ref2,RM_NONE,0));
   __vcop_pblock_init16(pblock, __offset+_PREG(7), 4);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)pStringByte2+xsize/(4*8u)*(4*8u));
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)pHammingDistance);
   __vcop_pblock_4param_init(pblock, __offset+_PREG(12), 0xFFFFFFFF,0xFFFFFFFF,0x0,0x0);
   __vcop_pblock_init16(pblock, __offset+_PREG(16), (xpitch) -(sizeof(*pStringByte1))*(((xsize % (4 * (8u))))-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(17), (xpitch*mode) -(sizeof(*pStringByte1))*(((xsize % (4 * (8u))))-1u));
   __vcop_pblock_init32(pblock, __offset+_PREG(18), 0);
   __vcop_pblock_init32(pblock, __offset+_PREG(20), (uchar *)pStringByte1+xsize/(4*8u)*(4*8u));
   __offset += 20;

   /* Loop 3 PREGS */
   const int preg_ref3 = _PREG(8);

   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), (ysize)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), ((8u))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(6), __vcop_store_round_sat(SM_4PARAM,preg_ref3,RM_NONE,0));
   __vcop_pblock_init16(pblock, __offset+_PREG(7), 4);
   __vcop_pblock_4param_init(pblock, __offset+_PREG(8), 0xFFFFFFFF,0xFFFFFFFF,0x0,0x0);
   __vcop_pblock_init16(pblock, __offset+_PREG(12), 2);
   __vcop_pblock_init32(pblock, __offset+_PREG(14), (uchar *)pHammingDistance);
   __vcop_pblock_init32(pblock, __offset+_PREG(16), (uchar *)pScratch);
   __offset += 16;

   return 62u;
}

void vcop_hamming_distance_vloops(
   unsigned short pblock[])
{
   /* Kernel-wide Vector Registers */

   __vcop_param(&pblock[0]);

   /* VLOOP 1 Start */

   /* VLOOP Local Vector Registers */
   #pragma VCC_VREG("Vout1", 16);
   #pragma VCC_VREG("Vout2", 17);
   #pragma VCC_VREG("Vbitcnt1", 18);
   #pragma VCC_VREG("Vbitcnt2", 19);
   #pragma VCC_VREG("Vin11", 20);
   #pragma VCC_VREG("Vin12", 21);
   #pragma VCC_VREG("Vin21", 22);
   #pragma VCC_VREG("Vin22", 23);
   #pragma VCC_VREG("Vxor1", 24);
   #pragma VCC_VREG("Vxor2", 25);
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("AddrOut", "A0");
   #pragma EVE_REG("Addr1", "A1");
   #pragma EVE_REG("Addr2", "A2");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I1", "I3");
   #pragma EVE_REG("I2", "I4");
   

   __vcop_vloop(__vcop_compute(), 18u, 13u, 1u);
   __vcop_vinit(__vcop_sizeW(), __vcop_i4_zero(), _PREG(24), _VREG(16));
   __vcop_vinit(__vcop_sizeW(), __vcop_i4_zero(), _PREG(24), _VREG(17));
   __vcop_vagen(_AGEN(0), _PREG(0), _PREG(7), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(1), _PREG(7), _PREG(22), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(2), _PREG(7), _PREG(23), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeWU(), __vcop_npt(), _PREG(26), _AGEN(1), _VREG(20), __vcop_alws());
   __vcop_vload(__vcop_sizeWU(), __vcop_npt(), _PREG(8), _AGEN(2), _VREG(22), __vcop_alws());
   __vcop_vload(__vcop_sizeWU(), __vcop_npt(), _PREG(10), _AGEN(1), _VREG(21), __vcop_alws());
   __vcop_vload(__vcop_sizeWU(), __vcop_npt(), _PREG(12), _AGEN(2), _VREG(23), __vcop_alws());
   __vcop_vxor(_VREG(20), _VREG(22), _VREG(24));
   __vcop_vxor(_VREG(21), _VREG(23), _VREG(25));
   __vcop_vbitc(_VREG(24), _VREG(18));
   __vcop_vbitc(_VREG(25), _VREG(19));
   __vcop_vadd(_VREG(16), _VREG(18), _VREG(16));
   __vcop_vadd(_VREG(17), _VREG(19), _VREG(17));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeHU(), __vcop_npt(), __vcop_last_i4(), _VREG(16), _PREG(14), _AGEN(0), _PREG(6));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeHU(), __vcop_npt(), __vcop_last_i4(), _VREG(17), _PREG(20), _AGEN(0), _PREG(6));
   __vcop_vloop_end(1u);

   /* VLOOP 2 Start */

   /* VLOOP Local Vector Registers */
   #pragma VCC_VREG("Vout1", 26);
   #pragma VCC_VREG("Vout2", 27);
   #pragma VCC_VREG("Vbitcnt1", 28);
   #pragma VCC_VREG("Vbitcnt2", 29);
   #pragma VCC_VREG("Vin11", 30);
   #pragma VCC_VREG("Vin12", 31);
   #pragma VCC_VREG("Vin21", 32);
   #pragma VCC_VREG("Vin22", 33);
   #pragma VCC_VREG("Vxor1", 34);
   #pragma VCC_VREG("Vxor2", 35);
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("AddrOut", "A0");
   #pragma EVE_REG("Addr1", "A1");
   #pragma EVE_REG("Addr2", "A2");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I1", "I3");
   #pragma EVE_REG("I2", "I4");
   

   __vcop_vloop(__vcop_compute(), 11u, 10u, 2u);
   __vcop_vinit(__vcop_sizeW(), __vcop_i4_zero(), _PREG(18), _VREG(26));
   __vcop_vagen(_AGEN(0), _PREG(0), _PREG(7), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(1), _PREG(1), _PREG(16), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(2), _PREG(1), _PREG(17), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeBU(), __vcop_1pt(), _PREG(20), _AGEN(1), _VREG(30), __vcop_alws());
   __vcop_vload(__vcop_sizeBU(), __vcop_1pt(), _PREG(8), _AGEN(2), _VREG(32), __vcop_alws());
   __vcop_vxor(_VREG(30), _VREG(32), _VREG(34));
   __vcop_vbitc(_VREG(34), _VREG(28));
   __vcop_vadd(_VREG(26), _VREG(28), _VREG(26));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeWU(), __vcop_1pt(), __vcop_last_i4(), _VREG(26), _PREG(10), _AGEN(0), _PREG(6));
   __vcop_vloop_end(2u);

   /* VLOOP 3 Start */

   /* VLOOP Local Vector Registers */
   #pragma VCC_VREG("Vout1", 36);
   #pragma VCC_VREG("Vout2", 37);
   #pragma VCC_VREG("Vin", 38);
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("AddrOut", "A0");
   #pragma EVE_REG("Addr1", "A1");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I1", "I3");
   #pragma EVE_REG("I2", "I4");
   

   __vcop_vloop(__vcop_compute(), 7u, 8u, 3u);
   __vcop_vagen(_AGEN(0), _PREG(0), _PREG(7), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(1), _PREG(12), _PREG(12), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeWU(), __vcop_1pt(), _PREG(14), _AGEN(0), _VREG(36), __vcop_i4_zero());
   __vcop_vload(__vcop_sizeHU(), __vcop_1pt(), _PREG(16), _AGEN(1), _VREG(38), __vcop_alws());
   __vcop_vadd(_VREG(36), _VREG(38), _VREG(36));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeWU(), __vcop_1pt(), __vcop_last_i4(), _VREG(36), _PREG(14), _AGEN(0), _PREG(6));
   __vcop_vloop_end(3u);

}

void vcop_hamming_distance(
   __vptr_uint32 pString1,
   __vptr_uint32 pString2,
   __vptr_uint8 pStringByte1,
   __vptr_uint8 pStringByte2,
   unsigned int xsize,
   unsigned int ysize,
   unsigned int mode,
   unsigned int xpitch,
   __vptr_uint32 pHammingDistance,
   __vptr_uint16 pScratch)
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_hamming_distance_init(pString1, pString2, pStringByte1, pStringByte2, xsize, ysize, mode, xpitch, pHammingDistance, pScratch, __pblock_vcop_hamming_distance);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_hamming_distance_vloops(__pblock_vcop_hamming_distance);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

void vcop_hamming_distance_custom(
   __vptr_uint32 pString1,
   __vptr_uint32 pString2,
   __vptr_uint8 pStringByte1,
   __vptr_uint8 pStringByte2,
   unsigned int xsize,
   unsigned int ysize,
   unsigned int mode,
   unsigned int xpitch,
   __vptr_uint32 pHammingDistance,
   __vptr_uint16 pScratch,
   unsigned short pblock[])
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_hamming_distance_init(pString1, pString2, pStringByte1, pStringByte2, xsize, ysize, mode, xpitch, pHammingDistance, pScratch, pblock);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_hamming_distance_vloops(pblock);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

#pragma DATA_SECTION(__pblock_vcop_hamming_distance_multiple_32, ".vcop_parameter_block")
#pragma DATA_ALIGN(__pblock_vcop_hamming_distance_multiple_32, __ALIGNOF__(int));
unsigned short __pblock_vcop_hamming_distance_multiple_32[48];

unsigned int vcop_hamming_distance_multiple_32_param_count(void)
{
   return 48u;
}

unsigned int vcop_hamming_distance_multiple_32_ctrl_count(void)
{
   return 0u;
}

unsigned int vcop_hamming_distance_multiple_32_init(
   __vptr_uint32 pString1,
   __vptr_uint32 pString2,
   unsigned int xsize,
   unsigned int ysize,
   unsigned int mode,
   unsigned int xpitch,
   __vptr_uint32 pHammingDistance,
   __vptr_uint16 pScratch,
   unsigned short pblock[])
{
   int __offset = 0;
   /* Loop 1 PREGS */
   const int preg_ref4 = _PREG(16);

   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), ((ysize+1)/2)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), ((xsize)/(4 * (8u)))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(6), __vcop_store_round_sat(SM_4PARAM,preg_ref4,RM_NONE,0));
   __vcop_pblock_init16(pblock, __offset+_PREG(7), 32);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)pString2);
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)pString1+xpitch);
   __vcop_pblock_init32(pblock, __offset+_PREG(12), (uchar *)pString2+xpitch*mode);
   __vcop_pblock_init32(pblock, __offset+_PREG(14), (uchar *)pScratch);
   __vcop_pblock_4param_init(pblock, __offset+_PREG(16), 0xFFFF,0xFFFF,0x0,0x0);
   __vcop_pblock_init32(pblock, __offset+_PREG(20), (uchar *)pScratch+sizeof(*pScratch)*8u);
   __vcop_pblock_init16(pblock, __offset+_PREG(22), (2*xpitch) -((4*8u))*(((xsize)/(4 * (8u)))-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(23), (2*xpitch*mode) -((4*8u))*(((xsize)/(4 * (8u)))-1u));
   __vcop_pblock_init32(pblock, __offset+_PREG(24), 0);
   __vcop_pblock_init32(pblock, __offset+_PREG(26), (uchar *)pString1);
   __offset += 26;

   /* Loop 2 PREGS */
   const int preg_ref5 = _PREG(12);

   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), ((ysize+1)/2)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), ((8u))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(6), __vcop_store_round_sat(SM_4PARAM,preg_ref5,RM_NONE,0));
   __vcop_pblock_init16(pblock, __offset+_PREG(7), 8);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)pScratch+sizeof(*pScratch)*8u);
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)pHammingDistance);
   __vcop_pblock_4param_init(pblock, __offset+_PREG(12), 0xFFFFFFFF,0xFFFFFFFF,0x0,0x0);
   __vcop_pblock_init32(pblock, __offset+_PREG(16), (uchar *)pHammingDistance+sizeof(*pHammingDistance));
   __vcop_pblock_init16(pblock, __offset+_PREG(18), 2);
   __vcop_pblock_init16(pblock, __offset+_PREG(19), 18);
   __vcop_pblock_init32(pblock, __offset+_PREG(20), 0);
   __vcop_pblock_init32(pblock, __offset+_PREG(22), (uchar *)pScratch);
   __offset += 22;

   return 48u;
}

void vcop_hamming_distance_multiple_32_vloops(
   unsigned short pblock[])
{
   /* Kernel-wide Vector Registers */

   __vcop_param(&pblock[0]);

   /* VLOOP 1 Start */

   /* VLOOP Local Vector Registers */
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("AddrOut", "A0");
   #pragma EVE_REG("Addr1", "A1");
   #pragma EVE_REG("Addr2", "A2");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I2", "I3");
   #pragma EVE_REG("I3", "I4");
   

   __vcop_vloop(__vcop_compute(), 18u, 13u, 1u);
   __vcop_vinit(__vcop_sizeW(), __vcop_i4_zero(), _PREG(24), _VREG(8));
   __vcop_vinit(__vcop_sizeW(), __vcop_i4_zero(), _PREG(24), _VREG(10));
   __vcop_vagen(_AGEN(0), _PREG(0), _PREG(7), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(1), _PREG(7), _PREG(22), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(2), _PREG(7), _PREG(23), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeWU(), __vcop_npt(), _PREG(26), _AGEN(1), _VREG(0), __vcop_alws());
   __vcop_vload(__vcop_sizeWU(), __vcop_npt(), _PREG(8), _AGEN(2), _VREG(4), __vcop_alws());
   __vcop_vload(__vcop_sizeWU(), __vcop_npt(), _PREG(10), _AGEN(1), _VREG(2), __vcop_alws());
   __vcop_vload(__vcop_sizeWU(), __vcop_npt(), _PREG(12), _AGEN(2), _VREG(6), __vcop_alws());
   __vcop_vxor(_VREG(0), _VREG(4), _VREG(1));
   __vcop_vxor(_VREG(2), _VREG(6), _VREG(3));
   __vcop_vbitc(_VREG(1), _VREG(5));
   __vcop_vbitc(_VREG(3), _VREG(7));
   __vcop_vadd(_VREG(8), _VREG(5), _VREG(8));
   __vcop_vadd(_VREG(10), _VREG(7), _VREG(10));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeHU(), __vcop_npt(), __vcop_last_i4(), _VREG(8), _PREG(14), _AGEN(0), _PREG(6));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeHU(), __vcop_npt(), __vcop_last_i4(), _VREG(10), _PREG(20), _AGEN(0), _PREG(6));
   __vcop_vloop_end(1u);

   /* VLOOP 2 Start */

   /* VLOOP Local Vector Registers */
   #pragma VCC_VREG("Vin1", 16);
   #pragma VCC_VREG("Vin2", 17);
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("AddrOut", "A0");
   #pragma EVE_REG("Addr1", "A1");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I2", "I3");
   #pragma EVE_REG("I3", "I4");
   

   __vcop_vloop(__vcop_compute(), 11u, 11u, 2u);
   __vcop_vinit(__vcop_sizeW(), __vcop_i4_zero(), _PREG(20), _VREG(8));
   __vcop_vinit(__vcop_sizeW(), __vcop_i4_zero(), _PREG(20), _VREG(10));
   __vcop_vagen(_AGEN(0), _PREG(0), _PREG(7), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(1), _PREG(18), _PREG(19), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeHU(), __vcop_1pt(), _PREG(22), _AGEN(1), _VREG(16), __vcop_alws());
   __vcop_vload(__vcop_sizeHU(), __vcop_1pt(), _PREG(8), _AGEN(1), _VREG(17), __vcop_alws());
   __vcop_vadd(_VREG(8), _VREG(16), _VREG(8));
   __vcop_vadd(_VREG(10), _VREG(17), _VREG(10));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeWU(), __vcop_1pt(), __vcop_last_i4(), _VREG(8), _PREG(10), _AGEN(0), _PREG(6));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeWU(), __vcop_1pt(), __vcop_last_i4(), _VREG(10), _PREG(16), _AGEN(0), _PREG(6));
   __vcop_vloop_end(2u);

}

void vcop_hamming_distance_multiple_32(
   __vptr_uint32 pString1,
   __vptr_uint32 pString2,
   unsigned int xsize,
   unsigned int ysize,
   unsigned int mode,
   unsigned int xpitch,
   __vptr_uint32 pHammingDistance,
   __vptr_uint16 pScratch)
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_hamming_distance_multiple_32_init(pString1, pString2, xsize, ysize, mode, xpitch, pHammingDistance, pScratch, __pblock_vcop_hamming_distance_multiple_32);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_hamming_distance_multiple_32_vloops(__pblock_vcop_hamming_distance_multiple_32);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

void vcop_hamming_distance_multiple_32_custom(
   __vptr_uint32 pString1,
   __vptr_uint32 pString2,
   unsigned int xsize,
   unsigned int ysize,
   unsigned int mode,
   unsigned int xpitch,
   __vptr_uint32 pHammingDistance,
   __vptr_uint16 pScratch,
   unsigned short pblock[])
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_hamming_distance_multiple_32_init(pString1, pString2, xsize, ysize, mode, xpitch, pHammingDistance, pScratch, pblock);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_hamming_distance_multiple_32_vloops(pblock);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

#pragma DATA_SECTION(__pblock_vcop_hamming_distance_size_lt_32, ".vcop_parameter_block")
#pragma DATA_ALIGN(__pblock_vcop_hamming_distance_size_lt_32, __ALIGNOF__(int));
unsigned short __pblock_vcop_hamming_distance_size_lt_32[26];

unsigned int vcop_hamming_distance_size_lt_32_param_count(void)
{
   return 26u;
}

unsigned int vcop_hamming_distance_size_lt_32_ctrl_count(void)
{
   return 0u;
}

unsigned int vcop_hamming_distance_size_lt_32_init(
   __vptr_uint8 pStringByte1,
   __vptr_uint8 pStringByte2,
   unsigned int xsize,
   unsigned int ysize,
   unsigned int mode,
   unsigned int xpitch,
   __vptr_uint32 pHammingDistance,
   unsigned short pblock[])
{
   int __offset = 0;
   /* Loop 1 PREGS */
   const int preg_ref6 = _PREG(16);

   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), ((ysize+1)/2)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), (xsize)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(6), __vcop_store_round_sat(SM_4PARAM,preg_ref6,RM_NONE,0));
   __vcop_pblock_init16(pblock, __offset+_PREG(7), 8);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)pStringByte2);
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)pStringByte1+xpitch);
   __vcop_pblock_init32(pblock, __offset+_PREG(12), (uchar *)pStringByte2+xpitch*mode);
   __vcop_pblock_init32(pblock, __offset+_PREG(14), (uchar *)pHammingDistance);
   __vcop_pblock_4param_init(pblock, __offset+_PREG(16), 0xFFFFFFFF,0xFFFFFFFF,0x0,0x0);
   __vcop_pblock_init32(pblock, __offset+_PREG(20), (uchar *)pHammingDistance+sizeof(*pHammingDistance));
   __vcop_pblock_init16(pblock, __offset+_PREG(22), (2*xpitch) -(sizeof(*pStringByte1))*((xsize)-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(23), (2*xpitch*mode) -(sizeof(*pStringByte1))*((xsize)-1u));
   __vcop_pblock_init32(pblock, __offset+_PREG(24), 0);
   __vcop_pblock_init32(pblock, __offset+_PREG(26), (uchar *)pStringByte1);
   __offset += 26;

   return 26u;
}

void vcop_hamming_distance_size_lt_32_vloops(
   unsigned short pblock[])
{
   /* Kernel-wide Vector Registers */

   __vcop_param(&pblock[0]);

   /* VLOOP 1 Start */

   /* VLOOP Local Vector Registers */
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("AddrOut", "A0");
   #pragma EVE_REG("Addr1", "A1");
   #pragma EVE_REG("Addr2", "A2");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I1", "I3");
   #pragma EVE_REG("I2", "I4");
   

   __vcop_vloop(__vcop_compute(), 18u, 13u, 1u);
   __vcop_vinit(__vcop_sizeW(), __vcop_i4_zero(), _PREG(24), _VREG(8));
   __vcop_vinit(__vcop_sizeW(), __vcop_i4_zero(), _PREG(24), _VREG(10));
   __vcop_vagen(_AGEN(0), _PREG(0), _PREG(7), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(1), _PREG(1), _PREG(22), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(2), _PREG(1), _PREG(23), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeBU(), __vcop_1pt(), _PREG(26), _AGEN(1), _VREG(0), __vcop_alws());
   __vcop_vload(__vcop_sizeBU(), __vcop_1pt(), _PREG(8), _AGEN(2), _VREG(4), __vcop_alws());
   __vcop_vload(__vcop_sizeBU(), __vcop_1pt(), _PREG(10), _AGEN(1), _VREG(2), __vcop_alws());
   __vcop_vload(__vcop_sizeBU(), __vcop_1pt(), _PREG(12), _AGEN(2), _VREG(6), __vcop_alws());
   __vcop_vxor(_VREG(0), _VREG(4), _VREG(1));
   __vcop_vxor(_VREG(2), _VREG(6), _VREG(3));
   __vcop_vbitc(_VREG(1), _VREG(5));
   __vcop_vbitc(_VREG(3), _VREG(7));
   __vcop_vadd(_VREG(8), _VREG(5), _VREG(8));
   __vcop_vadd(_VREG(10), _VREG(7), _VREG(10));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeWU(), __vcop_1pt(), __vcop_last_i4(), _VREG(8), _PREG(14), _AGEN(0), _PREG(6));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeWU(), __vcop_1pt(), __vcop_last_i4(), _VREG(10), _PREG(20), _AGEN(0), _PREG(6));
   __vcop_vloop_end(1u);

}

void vcop_hamming_distance_size_lt_32(
   __vptr_uint8 pStringByte1,
   __vptr_uint8 pStringByte2,
   unsigned int xsize,
   unsigned int ysize,
   unsigned int mode,
   unsigned int xpitch,
   __vptr_uint32 pHammingDistance)
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_hamming_distance_size_lt_32_init(pStringByte1, pStringByte2, xsize, ysize, mode, xpitch, pHammingDistance, __pblock_vcop_hamming_distance_size_lt_32);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_hamming_distance_size_lt_32_vloops(__pblock_vcop_hamming_distance_size_lt_32);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

void vcop_hamming_distance_size_lt_32_custom(
   __vptr_uint8 pStringByte1,
   __vptr_uint8 pStringByte2,
   unsigned int xsize,
   unsigned int ysize,
   unsigned int mode,
   unsigned int xpitch,
   __vptr_uint32 pHammingDistance,
   unsigned short pblock[])
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_hamming_distance_size_lt_32_init(pStringByte1, pStringByte2, xsize, ysize, mode, xpitch, pHammingDistance, pblock);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_hamming_distance_size_lt_32_vloops(pblock);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

