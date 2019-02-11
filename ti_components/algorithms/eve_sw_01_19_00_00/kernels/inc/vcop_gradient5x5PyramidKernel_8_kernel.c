#include <vcop\vcop.h>

typedef unsigned char uchar;

#pragma DATA_SECTION(__pblock_vcop_gradientH5x5PyramidKernel_8, ".vcop_parameter_block")
#pragma DATA_ALIGN(__pblock_vcop_gradientH5x5PyramidKernel_8, __ALIGNOF__(int));
unsigned short __pblock_vcop_gradientH5x5PyramidKernel_8[50];

unsigned int vcop_gradientH5x5PyramidKernel_8_param_count(void)
{
   return 50u;
}

unsigned int vcop_gradientH5x5PyramidKernel_8_ctrl_count(void)
{
   return 0u;
}

unsigned int vcop_gradientH5x5PyramidKernel_8_init(
   __vptr_uint8 pIn,
   __vptr_int16 pB,
   unsigned short width,
   unsigned short pitch,
   unsigned short height,
   __vptr_uint8 pOut,
   unsigned short pblock[])
{
   int __offset = 0;
   /* Loop 1 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), (height)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), ((width)/(2*(8u))+1)-1u);
   __vcop_pblock_init32(pblock, __offset+_PREG(6), (uchar *)pIn+1);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)pIn+3);
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)pIn+4);
   __vcop_pblock_init32(pblock, __offset+_PREG(12), (uchar *)pB);
   __vcop_pblock_init16(pblock, __offset+_PREG(14), 8);
   __vcop_pblock_init16(pblock, __offset+_PREG(15), (pitch*sizeof(*pIn)) -((8u*sizeof(*pIn)))*(((width)/(2*(8u))+1)-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(16), 16);
   __vcop_pblock_init16(pblock, __offset+_PREG(17), (width*sizeof(*pB)) -((8u*sizeof(*pB)))*(((width)/(2*(8u))+1)-1u));
   __vcop_pblock_init32(pblock, __offset+_PREG(18), 1);
   __vcop_pblock_init32(pblock, __offset+_PREG(20), (uchar *)pIn);
   __offset += 20;

   /* Loop 2 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), ((height - 4)/2 + 1)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), (width/(2*(8u))+1)-1u);
   __vcop_pblock_init32(pblock, __offset+_PREG(6), 64);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), 128);
   __vcop_pblock_init32(pblock, __offset+_PREG(10), -7);
   __vcop_pblock_init32(pblock, __offset+_PREG(12), (uchar *)pB+0*width*2);
   __vcop_pblock_init32(pblock, __offset+_PREG(14), (uchar *)pB+1*width*2);
   __vcop_pblock_init32(pblock, __offset+_PREG(16), (uchar *)pB+2*width*2);
   __vcop_pblock_init32(pblock, __offset+_PREG(18), (uchar *)pB+3*width*2);
   __vcop_pblock_init32(pblock, __offset+_PREG(20), (uchar *)pB+4*width*2);
   __vcop_pblock_init32(pblock, __offset+_PREG(22), (uchar *)pOut);
   __vcop_pblock_init16(pblock, __offset+_PREG(24), 16);
   __vcop_pblock_init16(pblock, __offset+_PREG(25), (width*sizeof(*pB)) -((8u*sizeof(*pB)))*((width/(2*(8u))+1)-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(26), 8);
   __vcop_pblock_init16(pblock, __offset+_PREG(27), ((width/2)*sizeof(*pIn)) -((8u*sizeof(*pIn)))*((width/(2*(8u))+1)-1u));
   __vcop_pblock_init32(pblock, __offset+_PREG(28), 2);
   __vcop_pblock_init32(pblock, __offset+_PREG(30), 6);
   __offset += 30;

   return 50u;
}

void vcop_gradientH5x5PyramidKernel_8_vloops(
   unsigned short pblock[])
{
   /* Kernel-wide Vector Registers */
   #pragma VCC_VREG("C_1", 16);
   #pragma VCC_VREG("C_128", 17);
   #pragma VCC_VREG("C_2", 18);
   #pragma VCC_VREG("C_6", 19);
   #pragma VCC_VREG("C_64", 20);
   #pragma VCC_VREG("C_M7", 21);
   #pragma VCC_VREG("R", 22);
   #pragma VCC_VREG("R1", 23);
   #pragma VCC_VREG("R1p", 24);
   #pragma VCC_VREG("R2", 25);
   #pragma VCC_VREG("R2p", 26);
   #pragma VCC_VREG("R3", 27);
   #pragma VCC_VREG("R3p", 28);
   #pragma VCC_VREG("R4", 29);
   #pragma VCC_VREG("R4p", 30);
   #pragma VCC_VREG("R5", 31);
   #pragma VCC_VREG("R5p", 32);
   #pragma VCC_VREG("R6", 33);
   #pragma VCC_VREG("R6p", 34);
   #pragma VCC_VREG("R7", 35);
   #pragma VCC_VREG("Rp", 36);

   __vcop_param(&pblock[0]);

   /* VLOOP 1 Start */

   /* VLOOP Local Vector Registers */
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("Addr1", "A0");
   #pragma EVE_REG("Addr2", "A1");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("i", "I3");
   #pragma EVE_REG("j", "I4");
   

   __vcop_vloop(__vcop_compute(), 17u, 10u, 1u);
   __vcop_vinit(__vcop_sizeW(), __vcop_once(), _PREG(18), _VREG(16));
   __vcop_vagen(_AGEN(0), _PREG(14), _PREG(15), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(1), _PREG(16), _PREG(17), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeBU(), __vcop_dintrlv(), _PREG(20), _AGEN(0), _VPAIR(23,24), __vcop_alws());
   __vcop_vload(__vcop_sizeBU(), __vcop_dintrlv(), _PREG(6), _AGEN(0), _VPAIR(25,26), __vcop_alws());
   __vcop_vload(__vcop_sizeBU(), __vcop_dintrlv(), _PREG(8), _AGEN(0), _VPAIR(27,28), __vcop_alws());
   __vcop_vload(__vcop_sizeBU(), __vcop_dintrlv(), _PREG(10), _AGEN(0), _VPAIR(29,30), __vcop_alws());
   __vcop_vsub(_VREG(25), _VREG(27), _VREG(33));
   __vcop_vsub(_VREG(26), _VREG(28), _VREG(34));
   __vcop_vsub(_VREG(23), _VREG(29), _VREG(31));
   __vcop_vsub(_VREG(24), _VREG(30), _VREG(32));
   __vcop_vshf(_VREG(33), _VREG(16), _VREG(33));
   __vcop_vshf(_VREG(34), _VREG(16), _VREG(34));
   __vcop_vadd(_VREG(33), _VREG(31), _VREG(33));
   __vcop_vadd(_VREG(34), _VREG(32), _VREG(34));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeH(), __vcop_intrlv(), __vcop_alws(), _VPAIR(33,34), _PREG(12), _AGEN(1), _PREG(0));
   __vcop_vloop_end(1u);

   /* VLOOP 2 Start */

   /* VLOOP Local Vector Registers */
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("Addr1", "A0");
   #pragma EVE_REG("Addr2", "A1");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("i", "I3");
   #pragma EVE_REG("j", "I4");
   

   __vcop_vloop(__vcop_compute(), 21u, 15u, 2u);
   __vcop_vinit(__vcop_sizeW(), __vcop_once(), _PREG(28), _VREG(18));
   __vcop_vinit(__vcop_sizeW(), __vcop_once(), _PREG(30), _VREG(19));
   __vcop_vinit(__vcop_sizeW(), __vcop_once(), _PREG(6), _VREG(20));
   __vcop_vinit(__vcop_sizeW(), __vcop_once(), _PREG(8), _VREG(17));
   __vcop_vinit(__vcop_sizeW(), __vcop_once(), _PREG(10), _VREG(21));
   __vcop_vagen(_AGEN(0), _PREG(24), _PREG(25), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(1), _PREG(26), _PREG(27), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeH(), __vcop_ds2(), _PREG(12), _AGEN(0), _VREG(23), __vcop_alws());
   __vcop_vload(__vcop_sizeH(), __vcop_ds2(), _PREG(14), _AGEN(0), _VREG(25), __vcop_alws());
   __vcop_vload(__vcop_sizeH(), __vcop_ds2(), _PREG(16), _AGEN(0), _VREG(27), __vcop_alws());
   __vcop_vload(__vcop_sizeH(), __vcop_ds2(), _PREG(18), _AGEN(0), _VREG(29), __vcop_alws());
   __vcop_vload(__vcop_sizeH(), __vcop_ds2(), _PREG(20), _AGEN(0), _VREG(31), __vcop_alws());
   __vcop_vadd(_VREG(25), _VREG(29), _VREG(35));
   __vcop_vmpy(_VREG(27), _VREG(19), _VREG(33), _PREG(0));
   __vcop_vshf(_VREG(35), _VREG(18), _VREG(35));
   __vcop_vadd3(_VREG(31), _VREG(20), _VREG(23));
   __vcop_vadd3(_VREG(33), _VREG(35), _VREG(23));
   __vcop_vshf(_VREG(23), _VREG(21), _VREG(23));
   __vcop_vadd(_VREG(23), _VREG(17), _VREG(23));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeBU(), __vcop_npt(), __vcop_alws(), _VREG(23), _PREG(22), _AGEN(1), _PREG(0));
   __vcop_vloop_end(2u);

}

void vcop_gradientH5x5PyramidKernel_8(
   __vptr_uint8 pIn,
   __vptr_int16 pB,
   unsigned short width,
   unsigned short pitch,
   unsigned short height,
   __vptr_uint8 pOut)
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_gradientH5x5PyramidKernel_8_init(pIn, pB, width, pitch, height, pOut, __pblock_vcop_gradientH5x5PyramidKernel_8);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_gradientH5x5PyramidKernel_8_vloops(__pblock_vcop_gradientH5x5PyramidKernel_8);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

void vcop_gradientH5x5PyramidKernel_8_custom(
   __vptr_uint8 pIn,
   __vptr_int16 pB,
   unsigned short width,
   unsigned short pitch,
   unsigned short height,
   __vptr_uint8 pOut,
   unsigned short pblock[])
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_gradientH5x5PyramidKernel_8_init(pIn, pB, width, pitch, height, pOut, pblock);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_gradientH5x5PyramidKernel_8_vloops(pblock);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

#pragma DATA_SECTION(__pblock_vcop_gradientV5x5PyramidKernel_8, ".vcop_parameter_block")
#pragma DATA_ALIGN(__pblock_vcop_gradientV5x5PyramidKernel_8, __ALIGNOF__(int));
unsigned short __pblock_vcop_gradientV5x5PyramidKernel_8[50];

unsigned int vcop_gradientV5x5PyramidKernel_8_param_count(void)
{
   return 50u;
}

unsigned int vcop_gradientV5x5PyramidKernel_8_ctrl_count(void)
{
   return 0u;
}

unsigned int vcop_gradientV5x5PyramidKernel_8_init(
   __vptr_uint8 pIn,
   __vptr_int16 pB,
   unsigned short width,
   unsigned short pitch,
   unsigned short height,
   __vptr_uint8 pOut,
   unsigned short pblock[])
{
   int __offset = 0;
   /* Loop 1 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), (height)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), (width/(2*(8u))+1)-1u);
   __vcop_pblock_init32(pblock, __offset+_PREG(6), (uchar *)pIn+0);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)pIn+1);
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)pIn+2);
   __vcop_pblock_init32(pblock, __offset+_PREG(12), (uchar *)pIn+3);
   __vcop_pblock_init32(pblock, __offset+_PREG(14), (uchar *)pIn+4);
   __vcop_pblock_init32(pblock, __offset+_PREG(16), (uchar *)pB);
   __vcop_pblock_init16(pblock, __offset+_PREG(18), 8);
   __vcop_pblock_init16(pblock, __offset+_PREG(19), (pitch*sizeof(*pIn)) -((8u*sizeof(*pIn)))*((width/(2*(8u))+1)-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(20), 16);
   __vcop_pblock_init16(pblock, __offset+_PREG(21), (width*sizeof(*pB)) -((8u*sizeof(*pB)))*((width/(2*(8u))+1)-1u));
   __vcop_pblock_init32(pblock, __offset+_PREG(22), 2);
   __vcop_pblock_init32(pblock, __offset+_PREG(24), 6);
   __offset += 24;

   /* Loop 2 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), ((height - 3)/2)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), (width/(2*(8u)) +1)-1u);
   __vcop_pblock_init32(pblock, __offset+_PREG(6), 128);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), -7);
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)pB+0*width*2);
   __vcop_pblock_init32(pblock, __offset+_PREG(12), (uchar *)pB+1*width*2);
   __vcop_pblock_init32(pblock, __offset+_PREG(14), (uchar *)pB+3*width*2);
   __vcop_pblock_init32(pblock, __offset+_PREG(16), (uchar *)pB+4*width*2);
   __vcop_pblock_init32(pblock, __offset+_PREG(18), (uchar *)pOut);
   __vcop_pblock_init16(pblock, __offset+_PREG(20), 16);
   __vcop_pblock_init16(pblock, __offset+_PREG(21), (width*sizeof(*pB)) -((8u*sizeof(*pB)))*((width/(2*(8u)) +1)-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(22), 8);
   __vcop_pblock_init16(pblock, __offset+_PREG(23), ((width/2)*sizeof(*pIn)) -((8u*sizeof(*pIn)))*((width/(2*(8u)) +1)-1u));
   __vcop_pblock_init32(pblock, __offset+_PREG(24), 1);
   __vcop_pblock_init32(pblock, __offset+_PREG(26), 64);
   __offset += 26;

   return 50u;
}

void vcop_gradientV5x5PyramidKernel_8_vloops(
   unsigned short pblock[])
{
   /* Kernel-wide Vector Registers */
   #pragma VCC_VREG("C_1", 16);
   #pragma VCC_VREG("C_128", 17);
   #pragma VCC_VREG("C_2", 18);
   #pragma VCC_VREG("C_6", 19);
   #pragma VCC_VREG("C_64", 20);
   #pragma VCC_VREG("C_M7", 21);
   #pragma VCC_VREG("R", 22);
   #pragma VCC_VREG("R1", 23);
   #pragma VCC_VREG("R1p", 24);
   #pragma VCC_VREG("R2", 25);
   #pragma VCC_VREG("R2p", 26);
   #pragma VCC_VREG("R3", 27);
   #pragma VCC_VREG("R3p", 28);
   #pragma VCC_VREG("R4", 29);
   #pragma VCC_VREG("R4p", 30);
   #pragma VCC_VREG("R5", 31);
   #pragma VCC_VREG("R5p", 32);
   #pragma VCC_VREG("R6", 33);
   #pragma VCC_VREG("R6p", 34);
   #pragma VCC_VREG("R7", 35);
   #pragma VCC_VREG("R7p", 36);
   #pragma VCC_VREG("Rp", 37);

   __vcop_param(&pblock[0]);

   /* VLOOP 1 Start */

   /* VLOOP Local Vector Registers */
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("Addr1", "A0");
   #pragma EVE_REG("Addr2", "A1");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("i", "I3");
   #pragma EVE_REG("j", "I4");
   

   __vcop_vloop(__vcop_compute(), 19u, 12u, 1u);
   __vcop_vinit(__vcop_sizeW(), __vcop_once(), _PREG(22), _VREG(18));
   __vcop_vinit(__vcop_sizeW(), __vcop_once(), _PREG(24), _VREG(19));
   __vcop_vagen(_AGEN(0), _PREG(18), _PREG(19), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(1), _PREG(20), _PREG(21), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeBU(), __vcop_dintrlv(), _PREG(6), _AGEN(0), _VPAIR(23,24), __vcop_alws());
   __vcop_vload(__vcop_sizeBU(), __vcop_dintrlv(), _PREG(8), _AGEN(0), _VPAIR(25,26), __vcop_alws());
   __vcop_vload(__vcop_sizeBU(), __vcop_dintrlv(), _PREG(10), _AGEN(0), _VPAIR(27,28), __vcop_alws());
   __vcop_vload(__vcop_sizeBU(), __vcop_dintrlv(), _PREG(12), _AGEN(0), _VPAIR(29,30), __vcop_alws());
   __vcop_vload(__vcop_sizeBU(), __vcop_dintrlv(), _PREG(14), _AGEN(0), _VPAIR(31,32), __vcop_alws());
   __vcop_vmadd(_VREG(27), _VREG(19), _VREG(31), _PREG(0));
   __vcop_vmadd(_VREG(28), _VREG(19), _VREG(32), _PREG(0));
   __vcop_vadd(_VREG(25), _VREG(29), _VREG(35));
   __vcop_vadd(_VREG(26), _VREG(30), _VREG(36));
   __vcop_vshf(_VREG(35), _VREG(18), _VREG(35));
   __vcop_vshf(_VREG(36), _VREG(18), _VREG(36));
   __vcop_vadd3(_VREG(31), _VREG(35), _VREG(23));
   __vcop_vadd3(_VREG(32), _VREG(36), _VREG(24));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeH(), __vcop_intrlv(), __vcop_alws(), _VPAIR(23,24), _PREG(16), _AGEN(1), _PREG(0));
   __vcop_vloop_end(1u);

   /* VLOOP 2 Start */

   /* VLOOP Local Vector Registers */
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("Addr1", "A0");
   #pragma EVE_REG("Addr2", "A1");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("i", "I3");
   #pragma EVE_REG("j", "I4");
   

   __vcop_vloop(__vcop_compute(), 18u, 13u, 2u);
   __vcop_vinit(__vcop_sizeW(), __vcop_once(), _PREG(24), _VREG(16));
   __vcop_vinit(__vcop_sizeW(), __vcop_once(), _PREG(26), _VREG(20));
   __vcop_vinit(__vcop_sizeW(), __vcop_once(), _PREG(6), _VREG(17));
   __vcop_vinit(__vcop_sizeW(), __vcop_once(), _PREG(8), _VREG(21));
   __vcop_vagen(_AGEN(0), _PREG(20), _PREG(21), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(1), _PREG(22), _PREG(23), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeH(), __vcop_ds2(), _PREG(10), _AGEN(0), _VREG(23), __vcop_alws());
   __vcop_vload(__vcop_sizeH(), __vcop_ds2(), _PREG(12), _AGEN(0), _VREG(25), __vcop_alws());
   __vcop_vload(__vcop_sizeH(), __vcop_ds2(), _PREG(14), _AGEN(0), _VREG(27), __vcop_alws());
   __vcop_vload(__vcop_sizeH(), __vcop_ds2(), _PREG(16), _AGEN(0), _VREG(29), __vcop_alws());
   __vcop_vadif(_VREG(20), _VREG(29), _VREG(23));
   __vcop_vsub(_VREG(25), _VREG(27), _VREG(33));
   __vcop_vshf(_VREG(33), _VREG(16), _VREG(33));
   __vcop_vadd(_VREG(23), _VREG(33), _VREG(23));
   __vcop_vshf(_VREG(23), _VREG(21), _VREG(22));
   __vcop_vadd(_VREG(22), _VREG(17), _VREG(22));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeBU(), __vcop_npt(), __vcop_alws(), _VREG(22), _PREG(18), _AGEN(1), _PREG(0));
   __vcop_vloop_end(2u);

}

void vcop_gradientV5x5PyramidKernel_8(
   __vptr_uint8 pIn,
   __vptr_int16 pB,
   unsigned short width,
   unsigned short pitch,
   unsigned short height,
   __vptr_uint8 pOut)
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_gradientV5x5PyramidKernel_8_init(pIn, pB, width, pitch, height, pOut, __pblock_vcop_gradientV5x5PyramidKernel_8);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_gradientV5x5PyramidKernel_8_vloops(__pblock_vcop_gradientV5x5PyramidKernel_8);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

void vcop_gradientV5x5PyramidKernel_8_custom(
   __vptr_uint8 pIn,
   __vptr_int16 pB,
   unsigned short width,
   unsigned short pitch,
   unsigned short height,
   __vptr_uint8 pOut,
   unsigned short pblock[])
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_gradientV5x5PyramidKernel_8_init(pIn, pB, width, pitch, height, pOut, pblock);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_gradientV5x5PyramidKernel_8_vloops(pblock);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

