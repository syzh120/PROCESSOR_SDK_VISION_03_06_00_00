#include <vcop\vcop.h>

typedef unsigned char uchar;

#pragma DATA_SECTION(__pblock_vcop_census_16bits, ".vcop_parameter_block")
#pragma DATA_ALIGN(__pblock_vcop_census_16bits, __ALIGNOF__(int));
unsigned short __pblock_vcop_census_16bits[86];

unsigned int vcop_census_16bits_param_count(void)
{
   return 86u;
}

unsigned int vcop_census_16bits_ctrl_count(void)
{
   return 0u;
}

unsigned int vcop_census_16bits_init(
   __vptr_uint16 pIn16,
   __vptr_uint8 pOut,
   __vptr_uint8 pScratchBitmask,
   __vptr_uint16 pScratch16,
   __vptr_uint8 pScratch8,
   __vptr_uint16 pOffset,
   __vptr_uint8 pCodeWordMask,
   __vptr_uint8 pRowMask,
   unsigned char winWidth,
   unsigned char winHeight,
   unsigned char winHorzStep,
   unsigned char winVertStep,
   unsigned short computeWidth,
   unsigned short computeHeight,
   unsigned short inStride,
   unsigned short outStride,
   unsigned short scratchStride,
   unsigned short pblock[])
{
   int __offset = 0;
   /* Loop 1 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), ((((inStride*(computeHeight + winHeight - 1)) + (2*(8u))-1) & ~(2*(8u)-1))/(2*(8u)))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(6), 32);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)pIn16);
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)pScratch16);
   __offset += 10;

   /* Loop 2 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), (((winHeight + winVertStep - 1)/winVertStep))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), (((winWidth + winHorzStep - 1)/winHorzStep))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), (computeHeight/2)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), (((((computeWidth) + (2*(8u))-1) & ~(2*(8u)-1))/(2*(8u))))-1u);
   __vcop_pblock_init32(pblock, __offset+_PREG(6), (uchar *)pScratch16);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)pScratch16+sizeof(*pIn16)*8u);
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)pIn16+sizeof(*pIn16)*(winWidth/2+(winHeight/2+1)*inStride));
   __vcop_pblock_init32(pblock, __offset+_PREG(12), (uchar *)pIn16+sizeof(*pIn16)*(winWidth/2+(winHeight/2+1)*inStride+8u));
   __vcop_pblock_init32(pblock, __offset+_PREG(14), (uchar *)pScratch16+sizeof(*pIn16)*inStride);
   __vcop_pblock_init32(pblock, __offset+_PREG(16), (uchar *)pScratch16+sizeof(*pIn16)*(inStride+8u));
   __vcop_pblock_init32(pblock, __offset+_PREG(18), (uchar *)pScratchBitmask);
   __vcop_pblock_init32(pblock, __offset+_PREG(20), (uchar *)pScratchBitmask+(computeWidth+2*8u-1&~(2*8u-1))/(2*8u)*(2*((winWidth+winHorzStep-1)/winHorzStep)*((winHeight+winVertStep-1)/winVertStep)+2*8u));
   __vcop_pblock_init16(pblock, __offset+_PREG(22), ((2*((winWidth+winHorzStep-1)/winHorzStep)*((winHeight+winVertStep-1)/winVertStep)+2*8u)));
   __vcop_pblock_init16(pblock, __offset+_PREG(23), (2*((computeWidth+2*8u-1&~(2*8u-1))/(2*8u))*(2*((winWidth+winHorzStep-1)/winHorzStep)*((winHeight+winVertStep-1)/winVertStep)+2*8u)) -((2*((winWidth+winHorzStep-1)/winHorzStep)*((winHeight+winVertStep-1)/winVertStep)+2*8u))*((((((computeWidth) + (2*(8u))-1) & ~(2*(8u)-1))/(2*(8u))))-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(24), (2) -(2*((computeWidth+2*8u-1&~(2*8u-1))/(2*8u))*(2*((winWidth+winHorzStep-1)/winHorzStep)*((winHeight+winVertStep-1)/winVertStep)+2*8u))*((computeHeight/2)-1u) -((2*((winWidth+winHorzStep-1)/winHorzStep)*((winHeight+winVertStep-1)/winVertStep)+2*8u))*((((((computeWidth) + (2*(8u))-1) & ~(2*(8u)-1))/(2*(8u))))-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(25), (2*((winWidth+winHorzStep-1)/winHorzStep)) -(2)*((((winWidth + winHorzStep - 1)/winHorzStep))-1u) -(2*((computeWidth+2*8u-1&~(2*8u-1))/(2*8u))*(2*((winWidth+winHorzStep-1)/winHorzStep)*((winHeight+winVertStep-1)/winVertStep)+2*8u))*((computeHeight/2)-1u) -((2*((winWidth+winHorzStep-1)/winHorzStep)*((winHeight+winVertStep-1)/winVertStep)+2*8u))*((((((computeWidth) + (2*(8u))-1) & ~(2*(8u)-1))/(2*(8u))))-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(26), 32);
   __vcop_pblock_init16(pblock, __offset+_PREG(27), (2*sizeof(*pIn16)*inStride) -(sizeof(*pIn16)*(2*8u))*((((((computeWidth) + (2*(8u))-1) & ~(2*(8u)-1))/(2*(8u))))-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(28),  -(2*sizeof(*pIn16)*inStride)*((computeHeight/2)-1u) -(sizeof(*pIn16)*(2*8u))*((((((computeWidth) + (2*(8u))-1) & ~(2*(8u)-1))/(2*(8u))))-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(29), (winHorzStep*sizeof(*pIn16)) -(2*sizeof(*pIn16)*inStride)*((computeHeight/2)-1u) -(sizeof(*pIn16)*(2*8u))*((((((computeWidth) + (2*(8u))-1) & ~(2*(8u)-1))/(2*(8u))))-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(30), (winVertStep*sizeof(*pIn16)*inStride) -(winHorzStep*sizeof(*pIn16))*((((winWidth + winHorzStep - 1)/winHorzStep))-1u) -(2*sizeof(*pIn16)*inStride)*((computeHeight/2)-1u) -(sizeof(*pIn16)*(2*8u))*((((((computeWidth) + (2*(8u))-1) & ~(2*(8u)-1))/(2*(8u))))-1u));
   __vcop_pblock_init32(pblock, __offset+_PREG(32), (uchar *)pIn16+sizeof(*pIn16)*(winWidth/2+winHeight/2*inStride));
   __vcop_pblock_init32(pblock, __offset+_PREG(34), (uchar *)pIn16+sizeof(*pIn16)*(winWidth/2+winHeight/2*inStride+8u));
   __offset += 34;

   /* Loop 3 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), (computeHeight)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), (((((computeWidth) + (2*(8u))-1) & ~(2*(8u)-1))/(2*(8u))))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), (((((((winHeight + winVertStep - 1)/winVertStep)*((winWidth + winHorzStep - 1)/winHorzStep)) + 7) & ~(7))/8))-1u);
   __vcop_pblock_init32(pblock, __offset+_PREG(6), (uchar *)pScratch8);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)pScratch8+8u*scratchStride);
   __vcop_pblock_init16(pblock, __offset+_PREG(10), 16);
   __vcop_pblock_init16(pblock, __offset+_PREG(11), ((2*((winWidth+winHorzStep-1)/winHorzStep)*((winHeight+winVertStep-1)/winVertStep)+2*8u)) -((2*8u))*((((((((winHeight + winVertStep - 1)/winVertStep)*((winWidth + winHorzStep - 1)/winHorzStep)) + 7) & ~(7))/8))-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(12), (((computeWidth+2*8u-1&~(2*8u-1))/(2*8u))*(2*((winWidth+winHorzStep-1)/winHorzStep)*((winHeight+winVertStep-1)/winVertStep)+2*8u)) -((2*((winWidth+winHorzStep-1)/winHorzStep)*((winHeight+winVertStep-1)/winVertStep)+2*8u))*((((((computeWidth) + (2*(8u))-1) & ~(2*(8u)-1))/(2*(8u))))-1u) -((2*8u))*((((((((winHeight + winVertStep - 1)/winVertStep)*((winWidth + winHorzStep - 1)/winHorzStep)) + 7) & ~(7))/8))-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(13), (computeWidth*scratchStride));
   __vcop_pblock_init16(pblock, __offset+_PREG(14), (2*scratchStride*8u) -(computeWidth*scratchStride)*((((((((winHeight + winVertStep - 1)/winVertStep)*((winWidth + winHorzStep - 1)/winHorzStep)) + 7) & ~(7))/8))-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(15), (1) -(2*scratchStride*8u)*((((((computeWidth) + (2*(8u))-1) & ~(2*(8u)-1))/(2*(8u))))-1u) -(computeWidth*scratchStride)*((((((((winHeight + winVertStep - 1)/winVertStep)*((winWidth + winHorzStep - 1)/winHorzStep)) + 7) & ~(7))/8))-1u));
   __vcop_pblock_init32(pblock, __offset+_PREG(16), (uchar *)pOffset);
   __vcop_pblock_init32(pblock, __offset+_PREG(18), (uchar *)pScratchBitmask);
   __offset += 18;

   /* Loop 4 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), ((((computeHeight) + (8u)-1) & ~((8u)-1))/(8u))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), ((((computeWidth) + 1) & ~(1))/2)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), (((((((winHeight + winVertStep - 1)/winVertStep)*((winWidth + winHorzStep - 1)/winHorzStep)) + 7) & ~(7))/8))-1u);
   __vcop_pblock_init32(pblock, __offset+_PREG(6), (uchar *)pScratch8);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)pScratch8+scratchStride);
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)pCodeWordMask);
   __vcop_pblock_init32(pblock, __offset+_PREG(12), (uchar *)pOut);
   __vcop_pblock_init32(pblock, __offset+_PREG(14), (uchar *)pOut+((winHeight+winVertStep-1)/winVertStep*((winWidth+winHorzStep-1)/winHorzStep)+7&~7)/8);
   __vcop_pblock_init16(pblock, __offset+_PREG(16), (computeWidth*scratchStride));
   __vcop_pblock_init16(pblock, __offset+_PREG(17), (2*scratchStride) -(computeWidth*scratchStride)*((((((((winHeight + winVertStep - 1)/winVertStep)*((winWidth + winHorzStep - 1)/winHorzStep)) + 7) & ~(7))/8))-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(18), (8u) -(2*scratchStride)*(((((computeWidth) + 1) & ~(1))/2)-1u) -(computeWidth*scratchStride)*((((((((winHeight + winVertStep - 1)/winVertStep)*((winWidth + winHorzStep - 1)/winHorzStep)) + 7) & ~(7))/8))-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(19),  -(1)*((((((((winHeight + winVertStep - 1)/winVertStep)*((winWidth + winHorzStep - 1)/winHorzStep)) + 7) & ~(7))/8))-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(20), (2*(((winHeight+winVertStep-1)/winVertStep*((winWidth+winHorzStep-1)/winHorzStep)+7&~7)/8)) -(1)*((((((((winHeight + winVertStep - 1)/winVertStep)*((winWidth + winHorzStep - 1)/winHorzStep)) + 7) & ~(7))/8))-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(21), (8u*outStride*sizeof(*pOut)) -(2*(((winHeight+winVertStep-1)/winVertStep*((winWidth+winHorzStep-1)/winHorzStep)+7&~7)/8))*(((((computeWidth) + 1) & ~(1))/2)-1u) -(1)*((((((((winHeight + winVertStep - 1)/winVertStep)*((winWidth + winHorzStep - 1)/winHorzStep)) + 7) & ~(7))/8))-1u));
   __vcop_pblock_init32(pblock, __offset+_PREG(22), (uchar *)pOffset+16);
   __vcop_pblock_init32(pblock, __offset+_PREG(24), (uchar *)pRowMask);
   __offset += 24;

   return 86u;
}

void vcop_census_16bits_vloops(
   unsigned short pblock[])
{
   /* Kernel-wide Vector Registers */
   #pragma VCC_VREG("vOfst", 16);

   __vcop_param(&pblock[0]);

   /* VLOOP 1 Start */

   /* VLOOP Local Vector Registers */
   #pragma VCC_VREG("vIn1", 17);
   #pragma VCC_VREG("vIn2", 18);
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("Addr", "A0");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("i", "I4");
   

   __vcop_vloop(__vcop_compute(), 4u, 5u, 1u);
   __vcop_vagen(_AGEN(0), _PREG(6), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeHU(), __vcop_dintrlv(), _PREG(8), _AGEN(0), _VPAIR(17,18), __vcop_alws());
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeHU(), __vcop_intrlv(), __vcop_alws(), _VPAIR(17,18), _PREG(10), _AGEN(0), _PREG(0));
   __vcop_vloop_end(1u);

   /* VLOOP 2 Start */

   /* VLOOP Local Vector Registers */
   #pragma VCC_VREG("vBitMask1", 19);
   #pragma VCC_VREG("vBitMask2", 20);
   #pragma VCC_VREG("vBitMask3", 21);
   #pragma VCC_VREG("vBitMask4", 22);
   #pragma VCC_VREG("vCenter1", 23);
   #pragma VCC_VREG("vCenter2", 24);
   #pragma VCC_VREG("vCenter3", 25);
   #pragma VCC_VREG("vCenter4", 26);
   #pragma VCC_VREG("vNeighbour1", 27);
   #pragma VCC_VREG("vNeighbour2", 28);
   #pragma VCC_VREG("vNeighbour3", 29);
   #pragma VCC_VREG("vNeighbour4", 30);
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("AddrBitmask", "A0");
   #pragma EVE_REG("AddrCenter", "A1");
   #pragma EVE_REG("AddrNeighbour", "A2");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("wh", "I1");
   #pragma EVE_REG("ww", "I2");
   #pragma EVE_REG("h", "I3");
   #pragma EVE_REG("w", "I4");
   

   __vcop_vloop(__vcop_compute(), 18u, 17u, 2u);
   __vcop_vagen(_AGEN(0), _PREG(22), _PREG(23), _PREG(24), _PREG(25));
   __vcop_vagen(_AGEN(1), _PREG(26), _PREG(27), _PREG(28), _PREG(28));
   __vcop_vagen(_AGEN(2), _PREG(26), _PREG(27), _PREG(29), _PREG(30));
   __vcop_vload(__vcop_sizeHU(), __vcop_npt(), _PREG(32), _AGEN(1), _VREG(23), __vcop_alws());
   __vcop_vload(__vcop_sizeHU(), __vcop_npt(), _PREG(34), _AGEN(1), _VREG(24), __vcop_alws());
   __vcop_vload(__vcop_sizeHU(), __vcop_npt(), _PREG(6), _AGEN(2), _VREG(27), __vcop_alws());
   __vcop_vload(__vcop_sizeHU(), __vcop_npt(), _PREG(8), _AGEN(2), _VREG(28), __vcop_alws());
   __vcop_vload(__vcop_sizeHU(), __vcop_npt(), _PREG(10), _AGEN(1), _VREG(25), __vcop_alws());
   __vcop_vload(__vcop_sizeHU(), __vcop_npt(), _PREG(12), _AGEN(1), _VREG(26), __vcop_alws());
   __vcop_vload(__vcop_sizeHU(), __vcop_npt(), _PREG(14), _AGEN(2), _VREG(29), __vcop_alws());
   __vcop_vload(__vcop_sizeHU(), __vcop_npt(), _PREG(16), _AGEN(2), _VREG(30), __vcop_alws());
   __vcop_vbitpk(_VREG(23), _VREG(27), _VREG(19));
   __vcop_vbitpk(_VREG(24), _VREG(28), _VREG(20));
   __vcop_vbitpk(_VREG(25), _VREG(29), _VREG(21));
   __vcop_vbitpk(_VREG(26), _VREG(30), _VREG(22));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeBU(), __vcop_intrlv(), __vcop_alws(), _VPAIR(19,20), _PREG(18), _AGEN(0), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeBU(), __vcop_intrlv(), __vcop_alws(), _VPAIR(21,22), _PREG(20), _AGEN(0), _PREG(0));
   __vcop_vloop_end(2u);

   /* VLOOP 3 Start */

   /* VLOOP Local Vector Registers */
   #pragma VCC_VREG("v_0_7_A_H", 31);
   #pragma VCC_VREG("v_8_15_A_H", 32);
   #pragma VCC_VREG("v_A_H_0_7", 33);
   #pragma VCC_VREG("v_A_H_8_15", 34);
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("AddrOffset", "A0");
   #pragma EVE_REG("AddrBitMask", "A1");
   #pragma EVE_REG("AddrOut", "A2");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("h", "I2");
   #pragma EVE_REG("w", "I3");
   #pragma EVE_REG("ww", "I4");
   

   __vcop_vloop(__vcop_compute(), 10u, 9u, 3u);
   __vcop_vagen(_AGEN(0), _PREG(0), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(1), _PREG(10), _PREG(11), _PREG(12), _PREG(0));
   __vcop_vagen(_AGEN(2), _PREG(13), _PREG(14), _PREG(15), _PREG(0));
   __vcop_vload(__vcop_sizeHU(), __vcop_npt(), _PREG(16), _AGEN(0), _VREG(16), __vcop_once());
   __vcop_vload(__vcop_sizeBU(), __vcop_dintrlv(), _PREG(18), _AGEN(1), _VPAIR(33,34), __vcop_alws());
   __vcop_vbittr(_VREG(33), _VREG(31));
   __vcop_vbittr(_VREG(34), _VREG(32));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeBU(), __vcop_pdda(_VREG(16)), __vcop_alws(), _VREG(31), _PREG(6), _AGEN(2), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeBU(), __vcop_pdda(_VREG(16)), __vcop_alws(), _VREG(32), _PREG(8), _AGEN(2), _PREG(0));
   __vcop_vloop_end(3u);

   /* VLOOP 4 Start */

   /* VLOOP Local Vector Registers */
   #pragma VCC_VREG("vRowMask", 35);
   #pragma VCC_VREG("vMask_0_7_A_H", 36);
   #pragma VCC_VREG("v_0_0_7_A_H", 37);
   #pragma VCC_VREG("v_1_0_7_A_H", 38);
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("AddrOffset", "A0");
   #pragma EVE_REG("AddrRowMask", "A1");
   #pragma EVE_REG("AddrIn", "A2");
   #pragma EVE_REG("AddrMask", "A3");
   #pragma EVE_REG("AddrOut", "A4");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("h", "I2");
   #pragma EVE_REG("w", "I3");
   #pragma EVE_REG("ww", "I4");
   

   __vcop_vloop(__vcop_compute(), 15u, 12u, 4u);
   __vcop_vagen(_AGEN(0), _PREG(0), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(1), _PREG(0), _PREG(0), _PREG(1), _PREG(0));
   __vcop_vagen(_AGEN(2), _PREG(16), _PREG(17), _PREG(18), _PREG(0));
   __vcop_vagen(_AGEN(3), _PREG(1), _PREG(19), _PREG(19), _PREG(0));
   __vcop_vagen(_AGEN(4), _PREG(1), _PREG(20), _PREG(21), _PREG(0));
   __vcop_vload(__vcop_sizeHU(), __vcop_npt(), _PREG(22), _AGEN(0), _VREG(16), __vcop_once());
   __vcop_vload(__vcop_sizeBU(), __vcop_nbits(), _PREG(24), _AGEN(1), _VREG(35), __vcop_i34_zero());
   __vcop_vload(__vcop_sizeBU(), __vcop_npt(), _PREG(6), _AGEN(2), _VREG(37), __vcop_alws());
   __vcop_vload(__vcop_sizeBU(), __vcop_npt(), _PREG(8), _AGEN(2), _VREG(38), __vcop_alws());
   __vcop_vload(__vcop_sizeBU(), __vcop_1pt(), _PREG(10), _AGEN(3), _VREG(36), __vcop_alws());
   __vcop_vand(_VREG(37), _VREG(36), _VREG(37));
   __vcop_vand(_VREG(38), _VREG(36), _VREG(38));
   __vcop_vstore(__vcop_predicate(_VREG(35)), __vcop_sizeBU(), __vcop_pdda(_VREG(16)), __vcop_alws(), _VREG(37), _PREG(12), _AGEN(4), _PREG(0));
   __vcop_vstore(__vcop_predicate(_VREG(35)), __vcop_sizeBU(), __vcop_pdda(_VREG(16)), __vcop_alws(), _VREG(38), _PREG(14), _AGEN(4), _PREG(0));
   __vcop_vloop_end(4u);

}

void vcop_census_16bits(
   __vptr_uint16 pIn16,
   __vptr_uint8 pOut,
   __vptr_uint8 pScratchBitmask,
   __vptr_uint16 pScratch16,
   __vptr_uint8 pScratch8,
   __vptr_uint16 pOffset,
   __vptr_uint8 pCodeWordMask,
   __vptr_uint8 pRowMask,
   unsigned char winWidth,
   unsigned char winHeight,
   unsigned char winHorzStep,
   unsigned char winVertStep,
   unsigned short computeWidth,
   unsigned short computeHeight,
   unsigned short inStride,
   unsigned short outStride,
   unsigned short scratchStride)
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_census_16bits_init(pIn16, pOut, pScratchBitmask, pScratch16, pScratch8, pOffset, pCodeWordMask, pRowMask, winWidth, winHeight, winHorzStep, winVertStep, computeWidth, computeHeight, inStride, outStride, scratchStride, __pblock_vcop_census_16bits);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_census_16bits_vloops(__pblock_vcop_census_16bits);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

void vcop_census_16bits_custom(
   __vptr_uint16 pIn16,
   __vptr_uint8 pOut,
   __vptr_uint8 pScratchBitmask,
   __vptr_uint16 pScratch16,
   __vptr_uint8 pScratch8,
   __vptr_uint16 pOffset,
   __vptr_uint8 pCodeWordMask,
   __vptr_uint8 pRowMask,
   unsigned char winWidth,
   unsigned char winHeight,
   unsigned char winHorzStep,
   unsigned char winVertStep,
   unsigned short computeWidth,
   unsigned short computeHeight,
   unsigned short inStride,
   unsigned short outStride,
   unsigned short scratchStride,
   unsigned short pblock[])
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_census_16bits_init(pIn16, pOut, pScratchBitmask, pScratch16, pScratch8, pOffset, pCodeWordMask, pRowMask, winWidth, winHeight, winHorzStep, winVertStep, computeWidth, computeHeight, inStride, outStride, scratchStride, pblock);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_census_16bits_vloops(pblock);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

