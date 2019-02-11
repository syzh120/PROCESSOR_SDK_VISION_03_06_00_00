#include <vcop\vcop.h>

typedef unsigned char uchar;

#pragma DATA_SECTION(__pblock_vcop_multiblock_gradient_xy, ".vcop_parameter_block")
#pragma DATA_ALIGN(__pblock_vcop_multiblock_gradient_xy, __ALIGNOF__(int));
unsigned short __pblock_vcop_multiblock_gradient_xy[20];

unsigned int vcop_multiblock_gradient_xy_param_count(void)
{
   return 20u;
}

unsigned int vcop_multiblock_gradient_xy_ctrl_count(void)
{
   return 0u;
}

unsigned int vcop_multiblock_gradient_xy_init(
   __vptr_uint8 pIn_A,
   __vptr_int16 pIntlvGradXY_B,
   unsigned short inputStride,
   unsigned short blkWidth,
   unsigned short blkHeight,
   unsigned short blkOffset,
   unsigned short numBlocks,
   unsigned short pblock[])
{
   int __offset = 0;
   /* Loop 1 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), (blkHeight)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), (numBlocks)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), ((blkWidth+(8u)-1)/(8u))-1u);
   __vcop_pblock_init32(pblock, __offset+_PREG(6), (uchar *)pIn_A+inputStride+2);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)pIn_A+2*inputStride+1);
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)pIntlvGradXY_B);
   __vcop_pblock_init16(pblock, __offset+_PREG(12), 8);
   __vcop_pblock_init16(pblock, __offset+_PREG(13), (blkOffset*sizeof(*pIn_A)) -((8u*sizeof(*pIn_A)))*(((blkWidth+(8u)-1)/(8u))-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(14), (inputStride*sizeof(*pIn_A)) -(blkOffset*sizeof(*pIn_A))*((numBlocks)-1u) -((8u*sizeof(*pIn_A)))*(((blkWidth+(8u)-1)/(8u))-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(15), 32);
   __vcop_pblock_init16(pblock, __offset+_PREG(16), ((blkHeight*blkWidth+(blkWidth+7)/8*8-blkWidth)*4) -((8u*sizeof(*pIn_A))*4)*(((blkWidth+(8u)-1)/(8u))-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(17), (blkWidth*4) -((blkHeight*blkWidth+(blkWidth+7)/8*8-blkWidth)*4)*((numBlocks)-1u) -((8u*sizeof(*pIn_A))*4)*(((blkWidth+(8u)-1)/(8u))-1u));
   __vcop_pblock_init32(pblock, __offset+_PREG(18), (uchar *)pIn_A+1);
   __vcop_pblock_init32(pblock, __offset+_PREG(20), (uchar *)pIn_A+inputStride);
   __offset += 20;

   return 20u;
}

void vcop_multiblock_gradient_xy_vloops(
   unsigned short pblock[])
{
   /* Kernel-wide Vector Registers */
   #pragma VCC_VREG("VgX", 16);
   #pragma VCC_VREG("VgY", 17);
   #pragma VCC_VREG("VinB", 18);
   #pragma VCC_VREG("VinL", 19);
   #pragma VCC_VREG("VinR", 20);
   #pragma VCC_VREG("VinT", 21);

   __vcop_param(&pblock[0]);

   /* VLOOP 1 Start */

   /* VLOOP Local Vector Registers */
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("Addr1", "A0");
   #pragma EVE_REG("Addr2", "A1");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I1", "I2");
   #pragma EVE_REG("I2", "I3");
   #pragma EVE_REG("I3", "I4");
   

   __vcop_vloop(__vcop_compute(), 10u, 10u, 1u);
   __vcop_vagen(_AGEN(0), _PREG(12), _PREG(13), _PREG(14), _PREG(0));
   __vcop_vagen(_AGEN(1), _PREG(15), _PREG(16), _PREG(17), _PREG(0));
   __vcop_vload(__vcop_sizeBU(), __vcop_npt(), _PREG(18), _AGEN(0), _VREG(21), __vcop_alws());
   __vcop_vload(__vcop_sizeBU(), __vcop_npt(), _PREG(20), _AGEN(0), _VREG(19), __vcop_alws());
   __vcop_vload(__vcop_sizeBU(), __vcop_npt(), _PREG(6), _AGEN(0), _VREG(20), __vcop_alws());
   __vcop_vload(__vcop_sizeBU(), __vcop_npt(), _PREG(8), _AGEN(0), _VREG(18), __vcop_alws());
   __vcop_vsub(_VREG(20), _VREG(19), _VREG(16));
   __vcop_vsub(_VREG(18), _VREG(21), _VREG(17));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeH(), __vcop_intrlv(), __vcop_alws(), _VPAIR(16,17), _PREG(10), _AGEN(1), _PREG(0));
   __vcop_vloop_end(1u);

}

void vcop_multiblock_gradient_xy(
   __vptr_uint8 pIn_A,
   __vptr_int16 pIntlvGradXY_B,
   unsigned short inputStride,
   unsigned short blkWidth,
   unsigned short blkHeight,
   unsigned short blkOffset,
   unsigned short numBlocks)
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_multiblock_gradient_xy_init(pIn_A, pIntlvGradXY_B, inputStride, blkWidth, blkHeight, blkOffset, numBlocks, __pblock_vcop_multiblock_gradient_xy);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_multiblock_gradient_xy_vloops(__pblock_vcop_multiblock_gradient_xy);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

void vcop_multiblock_gradient_xy_custom(
   __vptr_uint8 pIn_A,
   __vptr_int16 pIntlvGradXY_B,
   unsigned short inputStride,
   unsigned short blkWidth,
   unsigned short blkHeight,
   unsigned short blkOffset,
   unsigned short numBlocks,
   unsigned short pblock[])
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_multiblock_gradient_xy_init(pIn_A, pIntlvGradXY_B, inputStride, blkWidth, blkHeight, blkOffset, numBlocks, pblock);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_multiblock_gradient_xy_vloops(pblock);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

