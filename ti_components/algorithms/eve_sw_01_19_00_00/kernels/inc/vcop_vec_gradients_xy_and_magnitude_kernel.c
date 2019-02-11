#include <vcop\vcop.h>

typedef unsigned char uchar;

#pragma DATA_SECTION(__pblock_vcop_vec_gradients_xy_magnitudeu8, ".vcop_parameter_block")
#pragma DATA_ALIGN(__pblock_vcop_vec_gradients_xy_magnitudeu8, __ALIGNOF__(int));
unsigned short __pblock_vcop_vec_gradients_xy_magnitudeu8[28];

unsigned int vcop_vec_gradients_xy_magnitudeu8_param_count(void)
{
   return 28u;
}

unsigned int vcop_vec_gradients_xy_magnitudeu8_ctrl_count(void)
{
   return 0u;
}

unsigned int vcop_vec_gradients_xy_magnitudeu8_init(
   __vptr_uint8 pIn,
   __vptr_int16 pGradX,
   __vptr_int16 pGradY,
   __vptr_uint8 pMag,
   unsigned short pitch,
   unsigned short width,
   unsigned short height,
   unsigned short pblock[])
{
   int __offset = 0;
   /* Loop 1 PREGS */
   const int preg_ref1 = _PREG(7);

   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), (height)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), (((width + ((2*(8u))-1)) & (~((2*(8u))-1)))/(2*(8u)))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(6), __vcop_store_round_sat(SM_SYMM,preg_ref1,RM_NONE,0));
   __vcop_pblock_init16(pblock, __offset+_PREG(7), 255);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)pIn+pitch);
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)pIn+pitch+2);
   __vcop_pblock_init32(pblock, __offset+_PREG(12), (uchar *)pIn+2*pitch+1);
   __vcop_pblock_init32(pblock, __offset+_PREG(14), (uchar *)pGradX);
   __vcop_pblock_init32(pblock, __offset+_PREG(16), (uchar *)pGradY);
   __vcop_pblock_init32(pblock, __offset+_PREG(18), (uchar *)pMag);
   __vcop_pblock_init16(pblock, __offset+_PREG(20), 16);
   __vcop_pblock_init16(pblock, __offset+_PREG(21), (pitch*sizeof(*pIn)) -((8u*sizeof(*pIn))*2)*((((width + ((2*(8u))-1)) & (~((2*(8u))-1)))/(2*(8u)))-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(22), 32);
   __vcop_pblock_init16(pblock, __offset+_PREG(23), (width*sizeof(*pIn)*2) -((8u*sizeof(*pIn))*2*2)*((((width + ((2*(8u))-1)) & (~((2*(8u))-1)))/(2*(8u)))-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(24), (width*sizeof(*pIn)) -((8u*sizeof(*pIn))*2)*((((width + ((2*(8u))-1)) & (~((2*(8u))-1)))/(2*(8u)))-1u));
   __vcop_pblock_init32(pblock, __offset+_PREG(26), 0);
   __vcop_pblock_init32(pblock, __offset+_PREG(28), (uchar *)pIn+1);
   __offset += 28;

   return 28u;
}

void vcop_vec_gradients_xy_magnitudeu8_vloops(
   unsigned short pblock[])
{
   /* Kernel-wide Vector Registers */
   #pragma VCC_VREG("Vabs_gX_1", 16);
   #pragma VCC_VREG("Vabs_gX_2", 17);
   #pragma VCC_VREG("Vabs_gY_1", 18);
   #pragma VCC_VREG("Vabs_gY_2", 19);
   #pragma VCC_VREG("VgX_1", 20);
   #pragma VCC_VREG("VgX_2", 21);
   #pragma VCC_VREG("VgY_1", 22);
   #pragma VCC_VREG("VgY_2", 23);
   #pragma VCC_VREG("VinB1", 24);
   #pragma VCC_VREG("VinB2", 25);
   #pragma VCC_VREG("VinL1", 26);
   #pragma VCC_VREG("VinL2", 27);
   #pragma VCC_VREG("VinR1", 28);
   #pragma VCC_VREG("VinR2", 29);
   #pragma VCC_VREG("VinT1", 30);
   #pragma VCC_VREG("VinT2", 31);
   #pragma VCC_VREG("Vmag1", 32);
   #pragma VCC_VREG("Vmag2", 33);
   #pragma VCC_VREG("Z", 34);

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
   

   __vcop_vloop(__vcop_compute(), 20u, 14u, 1u);
   __vcop_vinit(__vcop_sizeW(), __vcop_once(), _PREG(26), _VREG(34));
   __vcop_vagen(_AGEN(0), _PREG(20), _PREG(21), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(1), _PREG(22), _PREG(23), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(2), _PREG(20), _PREG(24), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeBU(), __vcop_dintrlv(), _PREG(28), _AGEN(0), _VPAIR(30,31), __vcop_alws());
   __vcop_vload(__vcop_sizeBU(), __vcop_dintrlv(), _PREG(8), _AGEN(0), _VPAIR(26,27), __vcop_alws());
   __vcop_vload(__vcop_sizeBU(), __vcop_dintrlv(), _PREG(10), _AGEN(0), _VPAIR(28,29), __vcop_alws());
   __vcop_vload(__vcop_sizeBU(), __vcop_dintrlv(), _PREG(12), _AGEN(0), _VPAIR(24,25), __vcop_alws());
   __vcop_vsub(_VREG(28), _VREG(26), _VREG(20));
   __vcop_vsub(_VREG(24), _VREG(30), _VREG(22));
   __vcop_vsub(_VREG(29), _VREG(27), _VREG(21));
   __vcop_vsub(_VREG(25), _VREG(31), _VREG(23));
   __vcop_vabs(_VREG(20), _VREG(32));
   __vcop_vabs(_VREG(21), _VREG(33));
   __vcop_vsad(_VREG(22), _VREG(34), _VREG(32));
   __vcop_vsad(_VREG(23), _VREG(34), _VREG(33));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeH(), __vcop_intrlv(), __vcop_alws(), _VPAIR(20,21), _PREG(14), _AGEN(1), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeH(), __vcop_intrlv(), __vcop_alws(), _VPAIR(22,23), _PREG(16), _AGEN(1), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeBU(), __vcop_intrlv(), __vcop_alws(), _VPAIR(32,33), _PREG(18), _AGEN(2), _PREG(6));
   __vcop_vloop_end(1u);

}

void vcop_vec_gradients_xy_magnitudeu8(
   __vptr_uint8 pIn,
   __vptr_int16 pGradX,
   __vptr_int16 pGradY,
   __vptr_uint8 pMag,
   unsigned short pitch,
   unsigned short width,
   unsigned short height)
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_vec_gradients_xy_magnitudeu8_init(pIn, pGradX, pGradY, pMag, pitch, width, height, __pblock_vcop_vec_gradients_xy_magnitudeu8);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_vec_gradients_xy_magnitudeu8_vloops(__pblock_vcop_vec_gradients_xy_magnitudeu8);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

void vcop_vec_gradients_xy_magnitudeu8_custom(
   __vptr_uint8 pIn,
   __vptr_int16 pGradX,
   __vptr_int16 pGradY,
   __vptr_uint8 pMag,
   unsigned short pitch,
   unsigned short width,
   unsigned short height,
   unsigned short pblock[])
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_vec_gradients_xy_magnitudeu8_init(pIn, pGradX, pGradY, pMag, pitch, width, height, pblock);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_vec_gradients_xy_magnitudeu8_vloops(pblock);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

#pragma DATA_SECTION(__pblock_vcop_vec_gradients_xy_and_magnitude, ".vcop_parameter_block")
#pragma DATA_ALIGN(__pblock_vcop_vec_gradients_xy_and_magnitude, __ALIGNOF__(int));
unsigned short __pblock_vcop_vec_gradients_xy_and_magnitude[24];

unsigned int vcop_vec_gradients_xy_and_magnitude_param_count(void)
{
   return 24u;
}

unsigned int vcop_vec_gradients_xy_and_magnitude_ctrl_count(void)
{
   return 0u;
}

unsigned int vcop_vec_gradients_xy_and_magnitude_init(
   __vptr_uint8 pIn,
   __vptr_int16 pGradX,
   __vptr_int16 pGradY,
   __vptr_int16 pMag,
   unsigned short pitch,
   unsigned short width,
   unsigned short height,
   unsigned short pblock[])
{
   int __offset = 0;
   /* Loop 1 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), (height)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), (((width + ((2*(8u))-1)) & (~((2*(8u))-1)))/(2*(8u)))-1u);
   __vcop_pblock_init32(pblock, __offset+_PREG(6), (uchar *)pIn+pitch);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)pIn+pitch+2);
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)pIn+2*pitch+1);
   __vcop_pblock_init32(pblock, __offset+_PREG(12), (uchar *)pGradX);
   __vcop_pblock_init32(pblock, __offset+_PREG(14), (uchar *)pGradY);
   __vcop_pblock_init32(pblock, __offset+_PREG(16), (uchar *)pMag);
   __vcop_pblock_init16(pblock, __offset+_PREG(18), 16);
   __vcop_pblock_init16(pblock, __offset+_PREG(19), (pitch*sizeof(*pIn)) -((8u*sizeof(*pIn))*2)*((((width + ((2*(8u))-1)) & (~((2*(8u))-1)))/(2*(8u)))-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(20), 32);
   __vcop_pblock_init16(pblock, __offset+_PREG(21), (width*sizeof(*pIn)*2) -((8u*sizeof(*pIn))*2*2)*((((width + ((2*(8u))-1)) & (~((2*(8u))-1)))/(2*(8u)))-1u));
   __vcop_pblock_init32(pblock, __offset+_PREG(22), 0);
   __vcop_pblock_init32(pblock, __offset+_PREG(24), (uchar *)pIn+1);
   __offset += 24;

   return 24u;
}

void vcop_vec_gradients_xy_and_magnitude_vloops(
   unsigned short pblock[])
{
   /* Kernel-wide Vector Registers */
   #pragma VCC_VREG("Vabs_gX_1", 16);
   #pragma VCC_VREG("Vabs_gX_2", 17);
   #pragma VCC_VREG("Vabs_gY_1", 18);
   #pragma VCC_VREG("Vabs_gY_2", 19);
   #pragma VCC_VREG("VgX_1", 20);
   #pragma VCC_VREG("VgX_2", 21);
   #pragma VCC_VREG("VgY_1", 22);
   #pragma VCC_VREG("VgY_2", 23);
   #pragma VCC_VREG("VinB1", 24);
   #pragma VCC_VREG("VinB2", 25);
   #pragma VCC_VREG("VinL1", 26);
   #pragma VCC_VREG("VinL2", 27);
   #pragma VCC_VREG("VinR1", 28);
   #pragma VCC_VREG("VinR2", 29);
   #pragma VCC_VREG("VinT1", 30);
   #pragma VCC_VREG("VinT2", 31);
   #pragma VCC_VREG("Vmag1", 32);
   #pragma VCC_VREG("Vmag2", 33);
   #pragma VCC_VREG("Z", 34);

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
   

   __vcop_vloop(__vcop_compute(), 20u, 12u, 1u);
   __vcop_vinit(__vcop_sizeW(), __vcop_once(), _PREG(22), _VREG(34));
   __vcop_vagen(_AGEN(0), _PREG(18), _PREG(19), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(1), _PREG(20), _PREG(21), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(2), _PREG(20), _PREG(21), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeBU(), __vcop_dintrlv(), _PREG(24), _AGEN(0), _VPAIR(30,31), __vcop_alws());
   __vcop_vload(__vcop_sizeBU(), __vcop_dintrlv(), _PREG(6), _AGEN(0), _VPAIR(26,27), __vcop_alws());
   __vcop_vload(__vcop_sizeBU(), __vcop_dintrlv(), _PREG(8), _AGEN(0), _VPAIR(28,29), __vcop_alws());
   __vcop_vload(__vcop_sizeBU(), __vcop_dintrlv(), _PREG(10), _AGEN(0), _VPAIR(24,25), __vcop_alws());
   __vcop_vsub(_VREG(28), _VREG(26), _VREG(20));
   __vcop_vsub(_VREG(24), _VREG(30), _VREG(22));
   __vcop_vsub(_VREG(29), _VREG(27), _VREG(21));
   __vcop_vsub(_VREG(25), _VREG(31), _VREG(23));
   __vcop_vabs(_VREG(20), _VREG(32));
   __vcop_vabs(_VREG(21), _VREG(33));
   __vcop_vsad(_VREG(22), _VREG(34), _VREG(32));
   __vcop_vsad(_VREG(23), _VREG(34), _VREG(33));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeH(), __vcop_intrlv(), __vcop_alws(), _VPAIR(20,21), _PREG(12), _AGEN(1), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeH(), __vcop_intrlv(), __vcop_alws(), _VPAIR(22,23), _PREG(14), _AGEN(1), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeH(), __vcop_intrlv(), __vcop_alws(), _VPAIR(32,33), _PREG(16), _AGEN(2), _PREG(0));
   __vcop_vloop_end(1u);

}

void vcop_vec_gradients_xy_and_magnitude(
   __vptr_uint8 pIn,
   __vptr_int16 pGradX,
   __vptr_int16 pGradY,
   __vptr_int16 pMag,
   unsigned short pitch,
   unsigned short width,
   unsigned short height)
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_vec_gradients_xy_and_magnitude_init(pIn, pGradX, pGradY, pMag, pitch, width, height, __pblock_vcop_vec_gradients_xy_and_magnitude);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_vec_gradients_xy_and_magnitude_vloops(__pblock_vcop_vec_gradients_xy_and_magnitude);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

void vcop_vec_gradients_xy_and_magnitude_custom(
   __vptr_uint8 pIn,
   __vptr_int16 pGradX,
   __vptr_int16 pGradY,
   __vptr_int16 pMag,
   unsigned short pitch,
   unsigned short width,
   unsigned short height,
   unsigned short pblock[])
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_vec_gradients_xy_and_magnitude_init(pIn, pGradX, pGradY, pMag, pitch, width, height, pblock);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_vec_gradients_xy_and_magnitude_vloops(pblock);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

#pragma DATA_SECTION(__pblock_vcop_gradients_xy_list, ".vcop_parameter_block")
#pragma DATA_ALIGN(__pblock_vcop_gradients_xy_list, __ALIGNOF__(int));
unsigned short __pblock_vcop_gradients_xy_list[46];

unsigned int vcop_gradients_xy_list_param_count(void)
{
   return 46u;
}

unsigned int vcop_gradients_xy_list_ctrl_count(void)
{
   return 0u;
}

unsigned int vcop_gradients_xy_list_init(
   __vptr_uint8 pIn,
   __vptr_uint32 pUpperLeftXY,
   __vptr_uint8 pEdgeMap,
   __vptr_uint32 xSequence_C,
   __vptr_int32 pGradXY,
   __vptr_uint32 pEdgeListXY,
   __vptr_uint16 pListSize,
   unsigned short width,
   unsigned short height,
   unsigned short pitchInData,
   unsigned short pitchEdgeMap,
   unsigned short pblock[])
{
   int __offset = 0;
   /* Loop 1 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), (1)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), (height)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), ((((width) + (8u)-1) & ~((8u)-1))/ (8u))-1u);
   __vcop_pblock_init32(pblock, __offset+_PREG(6), (uchar *)pUpperLeftXY);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)pIn+1);
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)pIn+pitchInData);
   __vcop_pblock_init32(pblock, __offset+_PREG(12), (uchar *)pIn+pitchInData+2);
   __vcop_pblock_init32(pblock, __offset+_PREG(14), (uchar *)pIn+2*pitchInData+1);
   __vcop_pblock_init32(pblock, __offset+_PREG(16), (uchar *)pEdgeMap);
   __vcop_pblock_init32(pblock, __offset+_PREG(18), (uchar *)xSequence_C);
   __vcop_pblock_init32(pblock, __offset+_PREG(20), (uchar *)pGradXY);
   __vcop_pblock_init32(pblock, __offset+_PREG(22), (uchar *)pEdgeListXY);
   __vcop_pblock_init32(pblock, __offset+_PREG(24), (uchar *)pListSize);
   __vcop_pblock_init16(pblock, __offset+_PREG(26), 8);
   __vcop_pblock_init16(pblock, __offset+_PREG(27), (pitchInData*sizeof(*pIn)) -(8u*sizeof(*pIn))*(((((width) + (8u)-1) & ~((8u)-1))/ (8u))-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(28),  -(pitchInData*sizeof(*pIn))*((height)-1u) -(8u*sizeof(*pIn))*(((((width) + (8u)-1) & ~((8u)-1))/ (8u))-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(29), (pitchEdgeMap*sizeof(*pEdgeMap)) -(8u*sizeof(*pEdgeMap))*(((((width) + (8u)-1) & ~((8u)-1))/ (8u))-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(30),  -(pitchEdgeMap*sizeof(*pEdgeMap))*((height)-1u) -(8u*sizeof(*pEdgeMap))*(((((width) + (8u)-1) & ~((8u)-1))/ (8u))-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(31), 32);
   __vcop_pblock_init16(pblock, __offset+_PREG(32),  -(8u*sizeof(*xSequence_C))*(((((width) + (8u)-1) & ~((8u)-1))/ (8u))-1u));
   __vcop_pblock_init32(pblock, __offset+_PREG(34), 0);
   __vcop_pblock_init32(pblock, __offset+_PREG(36), 16);
   __offset += 36;

   /* Loop 2 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), (1)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), (7)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(6), 2);
   __vcop_pblock_init16(pblock, __offset+_PREG(7), -12);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)pListSize+sizeof(*pListSize));
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)pListSize);
   __offset += 10;

   return 46u;
}

void vcop_gradients_xy_list_vloops(
   unsigned short pblock[])
{
   /* Kernel-wide Vector Registers */
   #pragma VCC_VREG("K16", 16);
   #pragma VCC_VREG("Vedge", 17);
   #pragma VCC_VREG("VedgeXY", 18);
   #pragma VCC_VREG("VgX", 19);
   #pragma VCC_VREG("VgXY", 20);
   #pragma VCC_VREG("VgY", 21);
   #pragma VCC_VREG("VinB", 22);
   #pragma VCC_VREG("VinL", 23);
   #pragma VCC_VREG("VinR", 24);
   #pragma VCC_VREG("VinT", 25);
   #pragma VCC_VREG("VnumEntries", 26);
   #pragma VCC_VREG("VxSeq", 27);
   #pragma VCC_VREG("upperLeftXY", 28);

   __vcop_param(&pblock[0]);

   /* VLOOP 1 Start */

   /* VLOOP Local Vector Registers */
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("Addr0", "A0");
   #pragma EVE_REG("Addr1", "A1");
   #pragma EVE_REG("Addr2", "A2");
   #pragma EVE_REG("Addr3", "A3");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I0", "I2");
   #pragma EVE_REG("I1", "I3");
   #pragma EVE_REG("I2", "I4");
   

   __vcop_vloop(__vcop_compute(), 24u, 18u, 1u);
   __vcop_vinit(__vcop_sizeW(), __vcop_once(), _PREG(34), _VREG(26));
   __vcop_vinit(__vcop_sizeW(), __vcop_once(), _PREG(36), _VREG(16));
   __vcop_vinit(__vcop_sizeHU(), __vcop_alws(), _PREG(67), _VREG(18));
   __vcop_vagen(_AGEN(0), _PREG(0), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(1), _PREG(26), _PREG(27), _PREG(28), _PREG(0));
   __vcop_vagen(_AGEN(2), _PREG(26), _PREG(29), _PREG(30), _PREG(0));
   __vcop_vagen(_AGEN(3), _PREG(31), _PREG(32), _PREG(32), _PREG(0));
   __vcop_vload(__vcop_sizeWU(), __vcop_1pt(), _PREG(6), _AGEN(0), _VREG(28), __vcop_once());
   __vcop_vload(__vcop_sizeBU(), __vcop_npt(), _PREG(8), _AGEN(1), _VREG(25), __vcop_alws());
   __vcop_vload(__vcop_sizeBU(), __vcop_npt(), _PREG(10), _AGEN(1), _VREG(23), __vcop_alws());
   __vcop_vload(__vcop_sizeBU(), __vcop_npt(), _PREG(12), _AGEN(1), _VREG(24), __vcop_alws());
   __vcop_vload(__vcop_sizeBU(), __vcop_npt(), _PREG(14), _AGEN(1), _VREG(22), __vcop_alws());
   __vcop_vload(__vcop_sizeBU(), __vcop_npt(), _PREG(16), _AGEN(2), _VREG(17), __vcop_alws());
   __vcop_vload(__vcop_sizeWU(), __vcop_npt(), _PREG(18), _AGEN(3), _VREG(27), __vcop_alws());
   __vcop_vsub(_VREG(24), _VREG(23), _VREG(19));
   __vcop_vsub(_VREG(22), _VREG(25), _VREG(21));
   __vcop_vadd(_VREG(26), _VREG(17), _VREG(26));
   __vcop_vshf(_VREG(19), _VREG(16), _VREG(20));
   __vcop_vadd3(_VREG(27), _VREG(28), _VREG(18));
   __vcop_vadd(_VREG(20), _VREG(21), _VREG(20));
   __vcop_vstore(__vcop_predicate(_VREG(17)), __vcop_sizeW(), __vcop_collat(), __vcop_alws(), _VREG(20), _PREG(20), _AGEN(0), _PREG(0));
   __vcop_vstore(__vcop_predicate(_VREG(17)), __vcop_sizeWU(), __vcop_collat(), __vcop_alws(), _VREG(18), _PREG(22), _AGEN(0), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeHU(), __vcop_npt(), __vcop_last_i34(), _VREG(26), _PREG(24), _AGEN(0), _PREG(0));
   __vcop_vloop_end(1u);

   /* VLOOP 2 Start */

   /* VLOOP Local Vector Registers */
   #pragma VCC_VREG("sz", 29);
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("Addr0", "A0");
   #pragma EVE_REG("Addr1", "A1");
   #pragma EVE_REG("Addr2", "A2");
   #pragma EVE_REG("Addr3", "A3");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("i", "I3");
   #pragma EVE_REG("j", "I4");
   

   __vcop_vloop(__vcop_compute(), 8u, 5u, 2u);
   __vcop_vagen(_AGEN(0), _PREG(0), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(1), _PREG(6), _PREG(7), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeHU(), __vcop_1pt(), _PREG(8), _AGEN(1), _VREG(29), __vcop_alws());
   __vcop_vadd(_VREG(26), _VREG(29), _VREG(26));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeHU(), __vcop_1pt(), __vcop_last_i4(), _VREG(26), _PREG(10), _AGEN(0), _PREG(0));
   __vcop_vloop_end(2u);

}

void vcop_gradients_xy_list(
   __vptr_uint8 pIn,
   __vptr_uint32 pUpperLeftXY,
   __vptr_uint8 pEdgeMap,
   __vptr_uint32 xSequence_C,
   __vptr_int32 pGradXY,
   __vptr_uint32 pEdgeListXY,
   __vptr_uint16 pListSize,
   unsigned short width,
   unsigned short height,
   unsigned short pitchInData,
   unsigned short pitchEdgeMap)
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_gradients_xy_list_init(pIn, pUpperLeftXY, pEdgeMap, xSequence_C, pGradXY, pEdgeListXY, pListSize, width, height, pitchInData, pitchEdgeMap, __pblock_vcop_gradients_xy_list);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_gradients_xy_list_vloops(__pblock_vcop_gradients_xy_list);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

void vcop_gradients_xy_list_custom(
   __vptr_uint8 pIn,
   __vptr_uint32 pUpperLeftXY,
   __vptr_uint8 pEdgeMap,
   __vptr_uint32 xSequence_C,
   __vptr_int32 pGradXY,
   __vptr_uint32 pEdgeListXY,
   __vptr_uint16 pListSize,
   unsigned short width,
   unsigned short height,
   unsigned short pitchInData,
   unsigned short pitchEdgeMap,
   unsigned short pblock[])
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_gradients_xy_list_init(pIn, pUpperLeftXY, pEdgeMap, xSequence_C, pGradXY, pEdgeListXY, pListSize, width, height, pitchInData, pitchEdgeMap, pblock);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_gradients_xy_list_vloops(pblock);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

#pragma DATA_SECTION(__pblock_vcop_gradients_xy_mag_lut_index_calulcation, ".vcop_parameter_block")
#pragma DATA_ALIGN(__pblock_vcop_gradients_xy_mag_lut_index_calulcation, __ALIGNOF__(int));
unsigned short __pblock_vcop_gradients_xy_mag_lut_index_calulcation[36];

unsigned int vcop_gradients_xy_mag_lut_index_calulcation_param_count(void)
{
   return 36u;
}

unsigned int vcop_gradients_xy_mag_lut_index_calulcation_ctrl_count(void)
{
   return 0u;
}

unsigned int vcop_gradients_xy_mag_lut_index_calulcation_init(
   __vptr_int16 gradXY,
   __vptr_uint16 lutIdxPtr,
   __vptr_int8 log4aPtr,
   unsigned short width,
   unsigned short height,
   unsigned short pitch,
   unsigned short pblock[])
{
   int __offset = 0;
   /* Loop 1 PREGS */
   const int preg_ref2 = _PREG(7);

   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), (height)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), ((((width) + 2*(8u)-1) & ~(2*(8u)-1))/ (2 * (8u)))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(6), __vcop_store_round_sat(SM_SYMM,preg_ref2,RM_NONE,0));
   __vcop_pblock_init16(pblock, __offset+_PREG(7), 767);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), 8);
   __vcop_pblock_init32(pblock, __offset+_PREG(10), 256);
   __vcop_pblock_init32(pblock, __offset+_PREG(12), 2);
   __vcop_pblock_init32(pblock, __offset+_PREG(14), 0);
   __vcop_pblock_init32(pblock, __offset+_PREG(16), (uchar *)gradXY);
   __vcop_pblock_init32(pblock, __offset+_PREG(18), (uchar *)gradXY+2*8u*sizeof(*gradXY));
   __vcop_pblock_init32(pblock, __offset+_PREG(20), (uchar *)lutIdxPtr);
   __vcop_pblock_init32(pblock, __offset+_PREG(22), (uchar *)lutIdxPtr+8u*sizeof(*lutIdxPtr));
   __vcop_pblock_init32(pblock, __offset+_PREG(24), (uchar *)log4aPtr);
   __vcop_pblock_init32(pblock, __offset+_PREG(26), (uchar *)log4aPtr+8u*sizeof(*log4aPtr));
   __vcop_pblock_init16(pblock, __offset+_PREG(28), 16);
   __vcop_pblock_init16(pblock, __offset+_PREG(29), (pitch*sizeof(*log4aPtr)) -((2*8u)*sizeof(*log4aPtr))*(((((width) + 2*(8u)-1) & ~(2*(8u)-1))/ (2 * (8u)))-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(30), 64);
   __vcop_pblock_init16(pblock, __offset+_PREG(31), (pitch*sizeof(*gradXY)*2) -((2*8u)*sizeof(*gradXY)*2)*(((((width) + 2*(8u)-1) & ~(2*(8u)-1))/ (2 * (8u)))-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(32), 32);
   __vcop_pblock_init16(pblock, __offset+_PREG(33), (pitch*sizeof(*lutIdxPtr)) -((2*8u)*sizeof(*lutIdxPtr))*(((((width) + 2*(8u)-1) & ~(2*(8u)-1))/ (2 * (8u)))-1u));
   __vcop_pblock_init32(pblock, __offset+_PREG(34), 1);
   __vcop_pblock_init32(pblock, __offset+_PREG(36), -1);
   __offset += 36;

   return 36u;
}

void vcop_gradients_xy_mag_lut_index_calulcation_vloops(
   unsigned short pblock[])
{
   /* Kernel-wide Vector Registers */
   #pragma VCC_VREG("VMthr", 16);
   #pragma VCC_VREG("VgM0", 17);
   #pragma VCC_VREG("VgM1", 18);
   #pragma VCC_VREG("VgX0", 19);
   #pragma VCC_VREG("VgX1", 20);
   #pragma VCC_VREG("VgY0", 21);
   #pragma VCC_VREG("VgY1", 22);
   #pragma VCC_VREG("Vk0", 23);
   #pragma VCC_VREG("Vk1", 24);
   #pragma VCC_VREG("Vk2", 25);
   #pragma VCC_VREG("Vk256", 26);
   #pragma VCC_VREG("Vkn1", 27);
   #pragma VCC_VREG("Vlut_idx_0", 28);
   #pragma VCC_VREG("Vlut_idx_1", 29);
   #pragma VCC_VREG("Vlut_shift_0", 30);
   #pragma VCC_VREG("Vlut_shift_1", 31);
   #pragma VCC_VREG("Vrnd_val_0", 32);
   #pragma VCC_VREG("Vrnd_val_1", 33);
   #pragma VCC_VREG("Vw0", 34);
   #pragma VCC_VREG("Vw1", 35);
   #pragma VCC_VREG("Vz0", 36);
   #pragma VCC_VREG("Vz1", 37);
   #pragma VCC_VREG("Vzlog4_0", 38);
   #pragma VCC_VREG("Vzlog4_1", 39);

   __vcop_param(&pblock[0]);

   /* VLOOP 1 Start */

   /* VLOOP Local Vector Registers */
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("Addr_CHAR", "A0");
   #pragma EVE_REG("Addr_SHORT_IN", "A1");
   #pragma EVE_REG("Addr_SHORT_OUT", "A2");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I1", "I3");
   #pragma EVE_REG("I2", "I4");
   

   __vcop_vloop(__vcop_compute(), 44u, 18u, 1u);
   __vcop_vinit(__vcop_sizeW(), __vcop_once(), _PREG(34), _VREG(24));
   __vcop_vinit(__vcop_sizeW(), __vcop_once(), _PREG(36), _VREG(27));
   __vcop_vinit(__vcop_sizeW(), __vcop_alws(), _PREG(8), _VREG(30));
   __vcop_vinit(__vcop_sizeW(), __vcop_alws(), _PREG(10), _VREG(26));
   __vcop_vinit(__vcop_sizeW(), __vcop_alws(), _PREG(12), _VREG(25));
   __vcop_vinit(__vcop_sizeW(), __vcop_alws(), _PREG(14), _VREG(23));
   __vcop_vagen(_AGEN(0), _PREG(28), _PREG(29), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(1), _PREG(30), _PREG(31), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(2), _PREG(32), _PREG(33), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeH(), __vcop_dintrlv(), _PREG(16), _AGEN(1), _VPAIR(19,21), __vcop_alws());
   __vcop_vload(__vcop_sizeH(), __vcop_dintrlv(), _PREG(18), _AGEN(1), _VPAIR(20,22), __vcop_alws());
   __vcop_vadd(_VREG(30), _VREG(23), _VREG(31));
   __vcop_vmpy(_VREG(19), _VREG(19), _VREG(36), _PREG(0));
   __vcop_vmpy(_VREG(20), _VREG(20), _VREG(37), _PREG(0));
   __vcop_vmadd(_VREG(21), _VREG(21), _VREG(36), _PREG(0));
   __vcop_vmadd(_VREG(22), _VREG(22), _VREG(37), _PREG(0));
   __vcop_vlmbd(_VREG(36), _VREG(24), _VREG(38));
   __vcop_vlmbd(_VREG(37), _VREG(24), _VREG(39));
   __vcop_vshf(_VREG(38), _VREG(27), _VREG(38));
   __vcop_vshf(_VREG(39), _VREG(27), _VREG(39));
   __vcop_vmsub(_VREG(25), _VREG(38), _VREG(30), _PREG(0));
   __vcop_vmsub(_VREG(25), _VREG(39), _VREG(31), _PREG(0));
   __vcop_vsub(_VREG(23), _VREG(30), _VREG(32));
   __vcop_vsub(_VREG(23), _VREG(31), _VREG(33));
   __vcop_vsub(_VREG(32), _VREG(24), _VREG(32));
   __vcop_vsub(_VREG(33), _VREG(24), _VREG(33));
   __vcop_vshf(_VREG(24), _VREG(32), _VREG(32));
   __vcop_vshf(_VREG(24), _VREG(33), _VREG(33));
   __vcop_vadd(_VREG(36), _VREG(32), _VREG(32));
   __vcop_vadd(_VREG(37), _VREG(33), _VREG(33));
   __vcop_vshf(_VREG(32), _VREG(30), _VREG(28));
   __vcop_vshf(_VREG(33), _VREG(31), _VREG(29));
   __vcop_vsub(_VREG(28), _VREG(26), _VREG(28));
   __vcop_vsub(_VREG(29), _VREG(26), _VREG(29));
   __vcop_vsub(_VREG(26), _VREG(24), _VREG(26));
   __vcop_vcmpeq(_VREG(36), _VREG(23), _VREG(36));
   __vcop_vcmpeq(_VREG(37), _VREG(23), _VREG(37));
   __vcop_vsel(_VREG(36), _VREG(26), _VREG(28));
   __vcop_vsel(_VREG(37), _VREG(26), _VREG(29));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeHU(), __vcop_npt(), __vcop_alws(), _VREG(28), _PREG(20), _AGEN(2), _PREG(6));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeHU(), __vcop_npt(), __vcop_alws(), _VREG(29), _PREG(22), _AGEN(2), _PREG(6));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeB(), __vcop_npt(), __vcop_alws(), _VREG(38), _PREG(24), _AGEN(0), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeB(), __vcop_npt(), __vcop_alws(), _VREG(39), _PREG(26), _AGEN(0), _PREG(0));
   __vcop_vloop_end(1u);

}

void vcop_gradients_xy_mag_lut_index_calulcation(
   __vptr_int16 gradXY,
   __vptr_uint16 lutIdxPtr,
   __vptr_int8 log4aPtr,
   unsigned short width,
   unsigned short height,
   unsigned short pitch)
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_gradients_xy_mag_lut_index_calulcation_init(gradXY, lutIdxPtr, log4aPtr, width, height, pitch, __pblock_vcop_gradients_xy_mag_lut_index_calulcation);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_gradients_xy_mag_lut_index_calulcation_vloops(__pblock_vcop_gradients_xy_mag_lut_index_calulcation);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

void vcop_gradients_xy_mag_lut_index_calulcation_custom(
   __vptr_int16 gradXY,
   __vptr_uint16 lutIdxPtr,
   __vptr_int8 log4aPtr,
   unsigned short width,
   unsigned short height,
   unsigned short pitch,
   unsigned short pblock[])
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_gradients_xy_mag_lut_index_calulcation_init(gradXY, lutIdxPtr, log4aPtr, width, height, pitch, pblock);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_gradients_xy_mag_lut_index_calulcation_vloops(pblock);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

#pragma DATA_SECTION(__pblock_vcop_reciprocal_sqrt_lookup, ".vcop_parameter_block")
#pragma DATA_ALIGN(__pblock_vcop_reciprocal_sqrt_lookup, __ALIGNOF__(int));
unsigned short __pblock_vcop_reciprocal_sqrt_lookup[12];

unsigned int vcop_reciprocal_sqrt_lookup_param_count(void)
{
   return 12u;
}

unsigned int vcop_reciprocal_sqrt_lookup_ctrl_count(void)
{
   return 0u;
}

unsigned int vcop_reciprocal_sqrt_lookup_init(
   __vptr_uint16 lutIdxPtr,
   __vptr_uint8 reciSqrtLut,
   __vptr_uint8 reciSqrtLutOutput,
   unsigned short listSize,
   unsigned short pblock[])
{
   int __offset = 0;
   /* Loop 1 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), ((((listSize) + (8u)-1) & ~((8u)-1))/ (8))-1u);
   __vcop_pblock_init32(pblock, __offset+_PREG(6), (uchar *)reciSqrtLutOutput);
   __vcop_pblock_init16(pblock, __offset+_PREG(8), 8);
   __vcop_pblock_init16(pblock, __offset+_PREG(9), 16);
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)lutIdxPtr);
   __vcop_pblock_init32(pblock, __offset+_PREG(12), (uchar *)reciSqrtLut);
   __offset += 12;

   return 12u;
}

void vcop_reciprocal_sqrt_lookup_vloops(
   unsigned short pblock[])
{
   /* Kernel-wide Vector Registers */

   __vcop_param(&pblock[0]);

   /* VLOOP 1 Start */

   /* VLOOP Local Vector Registers */
   #pragma VCC_VREG("Vindex", 16);
   #pragma VCC_VREG("Vtabledata", 17);
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("Addr_CHAR", "A2");
   #pragma EVE_REG("Addr_SHORT", "A0");
   #pragma EVE_REG("Addr_TABLE", "A1");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("i4", "I4");
   

   __vcop_vloop(__vcop_tablelkup(), 7u, 6u, 1u);
   __vcop_vagen(_AGEN(2), _PREG(8), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(0), _PREG(9), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(1), _PREG(0), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeHU(), __vcop_npt(), _PREG(10), _AGEN(0), _VREG(16), __vcop_alws());
   __vcop_vtbload(__vcop_sizeBU(), __vcop_tableinfo(8, 1), _PREG(12), _AGEN(1), _VREG(16), _VREG(17), _PREG(0), __vcop_alws());
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeBU(), __vcop_npt(), __vcop_alws(), _VREG(17), _PREG(6), _AGEN(2), _PREG(0));
   __vcop_vloop_end(1u);

}

void vcop_reciprocal_sqrt_lookup(
   __vptr_uint16 lutIdxPtr,
   __vptr_uint8 reciSqrtLut,
   __vptr_uint8 reciSqrtLutOutput,
   unsigned short listSize)
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_reciprocal_sqrt_lookup_init(lutIdxPtr, reciSqrtLut, reciSqrtLutOutput, listSize, __pblock_vcop_reciprocal_sqrt_lookup);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_reciprocal_sqrt_lookup_vloops(__pblock_vcop_reciprocal_sqrt_lookup);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

void vcop_reciprocal_sqrt_lookup_custom(
   __vptr_uint16 lutIdxPtr,
   __vptr_uint8 reciSqrtLut,
   __vptr_uint8 reciSqrtLutOutput,
   unsigned short listSize,
   unsigned short pblock[])
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_reciprocal_sqrt_lookup_init(lutIdxPtr, reciSqrtLut, reciSqrtLutOutput, listSize, pblock);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_reciprocal_sqrt_lookup_vloops(pblock);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

#pragma DATA_SECTION(__pblock_vcop_gradients_xy_unit_vecs, ".vcop_parameter_block")
#pragma DATA_ALIGN(__pblock_vcop_gradients_xy_unit_vecs, __ALIGNOF__(int));
unsigned short __pblock_vcop_gradients_xy_unit_vecs[24];

unsigned int vcop_gradients_xy_unit_vecs_param_count(void)
{
   return 24u;
}

unsigned int vcop_gradients_xy_unit_vecs_ctrl_count(void)
{
   return 0u;
}

unsigned int vcop_gradients_xy_unit_vecs_init(
   __vptr_int16 gradXY,
   __vptr_int8 log4aPtr,
   __vptr_uint8 reciprocalLutOutput,
   __vptr_int16 unitXYptr,
   unsigned short listSize,
   unsigned short pblock[])
{
   int __offset = 0;
   /* Loop 1 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), ((((listSize) + 2*(8u)-1) & ~(2*(8u)-1))/ (2 * (8u)))-1u);
   __vcop_pblock_init32(pblock, __offset+_PREG(6), (uchar *)gradXY+2*8u*sizeof(*gradXY));
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)log4aPtr);
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)log4aPtr+8u*sizeof(*log4aPtr));
   __vcop_pblock_init32(pblock, __offset+_PREG(12), (uchar *)reciprocalLutOutput);
   __vcop_pblock_init32(pblock, __offset+_PREG(14), (uchar *)reciprocalLutOutput+8u*sizeof(*reciprocalLutOutput));
   __vcop_pblock_init32(pblock, __offset+_PREG(16), (uchar *)unitXYptr);
   __vcop_pblock_init32(pblock, __offset+_PREG(18), (uchar *)unitXYptr+2*8u*sizeof(*unitXYptr));
   __vcop_pblock_init16(pblock, __offset+_PREG(20), 16);
   __vcop_pblock_init16(pblock, __offset+_PREG(21), 64);
   __vcop_pblock_init32(pblock, __offset+_PREG(22), 0);
   __vcop_pblock_init32(pblock, __offset+_PREG(24), (uchar *)gradXY);
   __offset += 24;

   return 24u;
}

void vcop_gradients_xy_unit_vecs_vloops(
   unsigned short pblock[])
{
   /* Kernel-wide Vector Registers */
   #pragma VCC_VREG("V_UnitX0", 16);
   #pragma VCC_VREG("V_UnitX1", 17);
   #pragma VCC_VREG("V_UnitY0", 18);
   #pragma VCC_VREG("V_UnitY1", 19);
   #pragma VCC_VREG("VgX0", 20);
   #pragma VCC_VREG("VgX1", 21);
   #pragma VCC_VREG("VgY0", 22);
   #pragma VCC_VREG("VgY1", 23);
   #pragma VCC_VREG("Vk0", 24);
   #pragma VCC_VREG("Vrec_zqm0", 25);
   #pragma VCC_VREG("Vrec_zqm1", 26);
   #pragma VCC_VREG("Vtrig_shf0", 27);
   #pragma VCC_VREG("Vtrig_shf1", 28);
   #pragma VCC_VREG("Vzlog4_0", 29);
   #pragma VCC_VREG("Vzlog4_1", 30);

   __vcop_param(&pblock[0]);

   /* VLOOP 1 Start */

   /* VLOOP Local Vector Registers */
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("Addr_CHAR", "A0");
   #pragma EVE_REG("Addr_SHORT", "A1");
   #pragma EVE_REG("Addr_out", "A2");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I2", "I4");
   

   __vcop_vloop(__vcop_compute(), 23u, 12u, 1u);
   __vcop_vinit(__vcop_sizeW(), __vcop_once(), _PREG(22), _VREG(24));
   __vcop_vagen(_AGEN(0), _PREG(20), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(1), _PREG(21), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(2), _PREG(21), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeH(), __vcop_dintrlv(), _PREG(24), _AGEN(1), _VPAIR(20,22), __vcop_alws());
   __vcop_vload(__vcop_sizeH(), __vcop_dintrlv(), _PREG(6), _AGEN(1), _VPAIR(21,23), __vcop_alws());
   __vcop_vload(__vcop_sizeB(), __vcop_npt(), _PREG(8), _AGEN(0), _VREG(29), __vcop_alws());
   __vcop_vload(__vcop_sizeB(), __vcop_npt(), _PREG(10), _AGEN(0), _VREG(30), __vcop_alws());
   __vcop_vload(__vcop_sizeBU(), __vcop_npt(), _PREG(12), _AGEN(0), _VREG(25), __vcop_alws());
   __vcop_vload(__vcop_sizeBU(), __vcop_npt(), _PREG(14), _AGEN(0), _VREG(26), __vcop_alws());
   __vcop_vsub(_VREG(24), _VREG(29), _VREG(27));
   __vcop_vsub(_VREG(24), _VREG(30), _VREG(28));
   __vcop_vmpy(_VREG(20), _VREG(25), _VREG(16), _PREG(0));
   __vcop_vmpy(_VREG(21), _VREG(26), _VREG(17), _PREG(0));
   __vcop_vmpy(_VREG(22), _VREG(25), _VREG(18), _PREG(0));
   __vcop_vmpy(_VREG(23), _VREG(26), _VREG(19), _PREG(0));
   __vcop_vshf(_VREG(16), _VREG(27), _VREG(16));
   __vcop_vshf(_VREG(17), _VREG(28), _VREG(17));
   __vcop_vshf(_VREG(18), _VREG(27), _VREG(18));
   __vcop_vshf(_VREG(19), _VREG(28), _VREG(19));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeH(), __vcop_intrlv(), __vcop_alws(), _VPAIR(16,18), _PREG(16), _AGEN(2), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeH(), __vcop_intrlv(), __vcop_alws(), _VPAIR(17,19), _PREG(18), _AGEN(2), _PREG(0));
   __vcop_vloop_end(1u);

}

void vcop_gradients_xy_unit_vecs(
   __vptr_int16 gradXY,
   __vptr_int8 log4aPtr,
   __vptr_uint8 reciprocalLutOutput,
   __vptr_int16 unitXYptr,
   unsigned short listSize)
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_gradients_xy_unit_vecs_init(gradXY, log4aPtr, reciprocalLutOutput, unitXYptr, listSize, __pblock_vcop_gradients_xy_unit_vecs);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_gradients_xy_unit_vecs_vloops(__pblock_vcop_gradients_xy_unit_vecs);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

void vcop_gradients_xy_unit_vecs_custom(
   __vptr_int16 gradXY,
   __vptr_int8 log4aPtr,
   __vptr_uint8 reciprocalLutOutput,
   __vptr_int16 unitXYptr,
   unsigned short listSize,
   unsigned short pblock[])
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_gradients_xy_unit_vecs_init(gradXY, log4aPtr, reciprocalLutOutput, unitXYptr, listSize, pblock);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_gradients_xy_unit_vecs_vloops(pblock);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

#pragma DATA_SECTION(__pblock_vcop_gradients_xy_update_param_block, ".vcop_parameter_block")
#pragma DATA_ALIGN(__pblock_vcop_gradients_xy_update_param_block, __ALIGNOF__(int));
unsigned short __pblock_vcop_gradients_xy_update_param_block[28];

unsigned int vcop_gradients_xy_update_param_block_param_count(void)
{
   return 28u;
}

unsigned int vcop_gradients_xy_update_param_block_ctrl_count(void)
{
   return 0u;
}

unsigned int vcop_gradients_xy_update_param_block_init(
   __vptr_uint16 pBlockGradientsXyMagLutIndexCalulcation,
   __vptr_uint16 pBlockReciprocalSqrtLookup,
   __vptr_uint16 pBlockGradientsXyUnitVecs,
   __vptr_uint16 pListSize,
   __vptr_uint16 pListSizeWbuf,
   unsigned short pblock[])
{
   int __offset = 0;
   /* Loop 1 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), (1)-1u);
   __vcop_pblock_init32(pblock, __offset+_PREG(6), 0);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), 1);
   __vcop_pblock_init32(pblock, __offset+_PREG(10), -4);
   __vcop_pblock_init32(pblock, __offset+_PREG(12), -3);
   __vcop_pblock_init32(pblock, __offset+_PREG(14), -1);
   __vcop_pblock_init32(pblock, __offset+_PREG(16), (uchar *)pListSize);
   __vcop_pblock_init32(pblock, __offset+_PREG(18), (uchar *)pBlockGradientsXyMagLutIndexCalulcation+6);
   __vcop_pblock_init32(pblock, __offset+_PREG(20), (uchar *)pBlockReciprocalSqrtLookup+6);
   __vcop_pblock_init32(pblock, __offset+_PREG(22), (uchar *)pBlockGradientsXyUnitVecs+6);
   __vcop_pblock_init32(pblock, __offset+_PREG(24), (uchar *)pListSizeWbuf);
   __vcop_pblock_init32(pblock, __offset+_PREG(26), 15);
   __vcop_pblock_init32(pblock, __offset+_PREG(28), 7);
   __offset += 28;

   return 28u;
}

void vcop_gradients_xy_update_param_block_vloops(
   unsigned short pblock[])
{
   /* Kernel-wide Vector Registers */
   #pragma VCC_VREG("VMask", 16);
   #pragma VCC_VREG("Vk0", 17);
   #pragma VCC_VREG("Vk1", 18);
   #pragma VCC_VREG("Vk15", 19);
   #pragma VCC_VREG("Vk7", 20);
   #pragma VCC_VREG("VkMinus1", 21);
   #pragma VCC_VREG("VkMinus3", 22);
   #pragma VCC_VREG("VkMinus4", 23);
   #pragma VCC_VREG("VlistSize", 24);
   #pragma VCC_VREG("VlistSizeAlign2SIMD", 25);
   #pragma VCC_VREG("VlistSizeAlignSIMD", 26);

   __vcop_param(&pblock[0]);

   /* VLOOP 1 Start */

   /* VLOOP Local Vector Registers */
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("addr0", "A0");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("i", "I4");
   

   __vcop_vloop(__vcop_compute(), 24u, 14u, 1u);
   __vcop_vinit(__vcop_sizeW(), __vcop_once(), _PREG(26), _VREG(19));
   __vcop_vinit(__vcop_sizeW(), __vcop_once(), _PREG(28), _VREG(20));
   __vcop_vinit(__vcop_sizeW(), __vcop_once(), _PREG(6), _VREG(17));
   __vcop_vinit(__vcop_sizeW(), __vcop_once(), _PREG(8), _VREG(18));
   __vcop_vinit(__vcop_sizeW(), __vcop_once(), _PREG(10), _VREG(23));
   __vcop_vinit(__vcop_sizeW(), __vcop_once(), _PREG(12), _VREG(22));
   __vcop_vinit(__vcop_sizeW(), __vcop_once(), _PREG(14), _VREG(21));
   __vcop_vagen(_AGEN(0), _PREG(0), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeHU(), __vcop_1pt(), _PREG(16), _AGEN(0), _VREG(24), __vcop_once());
   __vcop_vadd(_VREG(24), _VREG(17), _VREG(26));
   __vcop_vcmpeq(_VREG(26), _VREG(17), _VREG(16));
   __vcop_vsel(_VREG(16), _VREG(18), _VREG(26));
   __vcop_vadd(_VREG(26), _VREG(17), _VREG(25));
   __vcop_vadd(_VREG(25), _VREG(19), _VREG(25));
   __vcop_vshf(_VREG(25), _VREG(23), _VREG(25));
   __vcop_vadd(_VREG(25), _VREG(21), _VREG(25));
   __vcop_vadd(_VREG(26), _VREG(20), _VREG(26));
   __vcop_vshf(_VREG(26), _VREG(22), _VREG(26));
   __vcop_vadd(_VREG(26), _VREG(21), _VREG(26));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeHU(), __vcop_1pt(), __vcop_alws(), _VREG(25), _PREG(18), _AGEN(0), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeHU(), __vcop_1pt(), __vcop_alws(), _VREG(26), _PREG(20), _AGEN(0), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeHU(), __vcop_1pt(), __vcop_alws(), _VREG(25), _PREG(22), _AGEN(0), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeHU(), __vcop_1pt(), __vcop_alws(), _VREG(24), _PREG(24), _AGEN(0), _PREG(0));
   __vcop_vloop_end(1u);

}

void vcop_gradients_xy_update_param_block(
   __vptr_uint16 pBlockGradientsXyMagLutIndexCalulcation,
   __vptr_uint16 pBlockReciprocalSqrtLookup,
   __vptr_uint16 pBlockGradientsXyUnitVecs,
   __vptr_uint16 pListSize,
   __vptr_uint16 pListSizeWbuf)
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_gradients_xy_update_param_block_init(pBlockGradientsXyMagLutIndexCalulcation, pBlockReciprocalSqrtLookup, pBlockGradientsXyUnitVecs, pListSize, pListSizeWbuf, __pblock_vcop_gradients_xy_update_param_block);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_gradients_xy_update_param_block_vloops(__pblock_vcop_gradients_xy_update_param_block);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

void vcop_gradients_xy_update_param_block_custom(
   __vptr_uint16 pBlockGradientsXyMagLutIndexCalulcation,
   __vptr_uint16 pBlockReciprocalSqrtLookup,
   __vptr_uint16 pBlockGradientsXyUnitVecs,
   __vptr_uint16 pListSize,
   __vptr_uint16 pListSizeWbuf,
   unsigned short pblock[])
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_gradients_xy_update_param_block_init(pBlockGradientsXyMagLutIndexCalulcation, pBlockReciprocalSqrtLookup, pBlockGradientsXyUnitVecs, pListSize, pListSizeWbuf, pblock);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_gradients_xy_update_param_block_vloops(pblock);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

