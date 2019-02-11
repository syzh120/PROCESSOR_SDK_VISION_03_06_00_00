#include <vcop\vcop.h>

typedef unsigned char uchar;

#pragma DATA_SECTION(__pblock_vcop_yuv420_fir2d_separable_y, ".vcop_parameter_block")
#pragma DATA_ALIGN(__pblock_vcop_yuv420_fir2d_separable_y, __ALIGNOF__(int));
unsigned short __pblock_vcop_yuv420_fir2d_separable_y[38];

unsigned int vcop_yuv420_fir2d_separable_y_param_count(void)
{
   return 38u;
}

unsigned int vcop_yuv420_fir2d_separable_y_ctrl_count(void)
{
   return 0u;
}

unsigned int vcop_yuv420_fir2d_separable_y_init(
   __vptr_uint8 data_ptr,
   __vptr_int16 inter_ptr,
   __vptr_int8 coefh_ptr,
   __vptr_int8 coefv_ptr,
   unsigned short blkw,
   unsigned short lofst,
   unsigned short blkh,
   unsigned short num_coef,
   __vptr_uint8 output_ptr,
   unsigned short rnd_bits,
   unsigned short pblock[])
{
   int __offset = 0;
   /* Loop 1 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), (blkh + num_coef - 1)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), (blkw/(2 * (8u)))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), (num_coef)-1u);
   __vcop_pblock_init32(pblock, __offset+_PREG(6), (uchar *)coefh_ptr);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)inter_ptr);
   __vcop_pblock_init16(pblock, __offset+_PREG(10), 32);
   __vcop_pblock_init16(pblock, __offset+_PREG(11), (blkw*sizeof(*inter_ptr)) -((2*8u)*sizeof(*inter_ptr))*((blkw/(2 * (8u)))-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(12), ((2*8u)*sizeof(*data_ptr)) -(sizeof(*data_ptr))*((num_coef)-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(13), (lofst*sizeof(*data_ptr)) -((2*8u)*sizeof(*data_ptr))*((blkw/(2 * (8u)))-1u) -(sizeof(*data_ptr))*((num_coef)-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(14),  -(sizeof(*coefh_ptr))*((num_coef)-1u));
   __vcop_pblock_init32(pblock, __offset+_PREG(16), 0);
   __vcop_pblock_init32(pblock, __offset+_PREG(18), (uchar *)data_ptr);
   __offset += 18;

   /* Loop 2 PREGS */
   const int preg_ref1 = _PREG(7);

   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), (blkh)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), (blkw/(2 * (8u)))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), (num_coef)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(6), __vcop_store_round_sat(SM_SYMM,preg_ref1,RM_ROUND,rnd_bits));
   __vcop_pblock_init16(pblock, __offset+_PREG(7), 255);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)coefv_ptr);
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)output_ptr);
   __vcop_pblock_init16(pblock, __offset+_PREG(12), 16);
   __vcop_pblock_init16(pblock, __offset+_PREG(13), (blkw*sizeof(*output_ptr)) -((2*8u)*sizeof(*output_ptr))*((blkw/(2 * (8u)))-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(14), (blkw*sizeof(*inter_ptr)));
   __vcop_pblock_init16(pblock, __offset+_PREG(15), ((2*8u)*sizeof(*inter_ptr)) -(blkw*sizeof(*inter_ptr))*((num_coef)-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(16), (blkw*sizeof(*inter_ptr)) -((2*8u)*sizeof(*inter_ptr))*((blkw/(2 * (8u)))-1u) -(blkw*sizeof(*inter_ptr))*((num_coef)-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(17),  -(sizeof(*coefh_ptr))*((num_coef)-1u));
   __vcop_pblock_init32(pblock, __offset+_PREG(18), 0);
   __vcop_pblock_init32(pblock, __offset+_PREG(20), (uchar *)inter_ptr);
   __offset += 20;

   return 38u;
}

void vcop_yuv420_fir2d_separable_y_vloops(
   unsigned short pblock[])
{
   /* Kernel-wide Vector Registers */

   __vcop_param(&pblock[0]);

   /* VLOOP 1 Start */

   /* VLOOP Local Vector Registers */
   #pragma VCC_VREG("Vout1", 16);
   #pragma VCC_VREG("Vout2", 17);
   #pragma VCC_VREG("Vin1", 18);
   #pragma VCC_VREG("Vin2", 19);
   #pragma VCC_VREG("Vcoef", 20);
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("A2", "A0");
   #pragma EVE_REG("A0", "A1");
   #pragma EVE_REG("A1", "A2");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I1", "I2");
   #pragma EVE_REG("I2", "I3");
   #pragma EVE_REG("I3", "I4");
   

   __vcop_vloop(__vcop_compute(), 11u, 9u, 1u);
   __vcop_vinit(__vcop_sizeW(), __vcop_i4_zero(), _PREG(16), _VREG(16));
   __vcop_vinit(__vcop_sizeW(), __vcop_i4_zero(), _PREG(16), _VREG(17));
   __vcop_vagen(_AGEN(0), _PREG(0), _PREG(10), _PREG(11), _PREG(0));
   __vcop_vagen(_AGEN(1), _PREG(1), _PREG(12), _PREG(13), _PREG(0));
   __vcop_vagen(_AGEN(2), _PREG(1), _PREG(14), _PREG(14), _PREG(0));
   __vcop_vload(__vcop_sizeBU(), __vcop_dintrlv(), _PREG(18), _AGEN(1), _VPAIR(18,19), __vcop_alws());
   __vcop_vload(__vcop_sizeB(), __vcop_1pt(), _PREG(6), _AGEN(2), _VREG(20), __vcop_alws());
   __vcop_vmadd(_VREG(18), _VREG(20), _VREG(16), _PREG(0));
   __vcop_vmadd(_VREG(19), _VREG(20), _VREG(17), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeH(), __vcop_intrlv(), __vcop_last_i4(), _VPAIR(16,17), _PREG(8), _AGEN(0), _PREG(0));
   __vcop_vloop_end(1u);

   /* VLOOP 2 Start */

   /* VLOOP Local Vector Registers */
   #pragma VCC_VREG("Vcoef", 21);
   #pragma VCC_VREG("Vout1", 22);
   #pragma VCC_VREG("Vout2", 23);
   #pragma VCC_VREG("Vin1", 24);
   #pragma VCC_VREG("Vin2", 25);
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("A2", "A0");
   #pragma EVE_REG("A0", "A1");
   #pragma EVE_REG("A1", "A2");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I1", "I2");
   #pragma EVE_REG("I2", "I3");
   #pragma EVE_REG("I3", "I4");
   

   __vcop_vloop(__vcop_compute(), 11u, 10u, 2u);
   __vcop_vinit(__vcop_sizeW(), __vcop_i4_zero(), _PREG(18), _VREG(22));
   __vcop_vinit(__vcop_sizeW(), __vcop_i4_zero(), _PREG(18), _VREG(23));
   __vcop_vagen(_AGEN(0), _PREG(0), _PREG(12), _PREG(13), _PREG(0));
   __vcop_vagen(_AGEN(1), _PREG(14), _PREG(15), _PREG(16), _PREG(0));
   __vcop_vagen(_AGEN(2), _PREG(1), _PREG(17), _PREG(17), _PREG(0));
   __vcop_vload(__vcop_sizeH(), __vcop_dintrlv(), _PREG(20), _AGEN(1), _VPAIR(24,25), __vcop_alws());
   __vcop_vload(__vcop_sizeB(), __vcop_1pt(), _PREG(8), _AGEN(2), _VREG(21), __vcop_alws());
   __vcop_vmadd(_VREG(24), _VREG(21), _VREG(22), _PREG(0));
   __vcop_vmadd(_VREG(25), _VREG(21), _VREG(23), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeBU(), __vcop_intrlv(), __vcop_last_i4(), _VPAIR(22,23), _PREG(10), _AGEN(0), _PREG(6));
   __vcop_vloop_end(2u);

}

void vcop_yuv420_fir2d_separable_y(
   __vptr_uint8 data_ptr,
   __vptr_int16 inter_ptr,
   __vptr_int8 coefh_ptr,
   __vptr_int8 coefv_ptr,
   unsigned short blkw,
   unsigned short lofst,
   unsigned short blkh,
   unsigned short num_coef,
   __vptr_uint8 output_ptr,
   unsigned short rnd_bits)
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_yuv420_fir2d_separable_y_init(data_ptr, inter_ptr, coefh_ptr, coefv_ptr, blkw, lofst, blkh, num_coef, output_ptr, rnd_bits, __pblock_vcop_yuv420_fir2d_separable_y);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_yuv420_fir2d_separable_y_vloops(__pblock_vcop_yuv420_fir2d_separable_y);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

void vcop_yuv420_fir2d_separable_y_custom(
   __vptr_uint8 data_ptr,
   __vptr_int16 inter_ptr,
   __vptr_int8 coefh_ptr,
   __vptr_int8 coefv_ptr,
   unsigned short blkw,
   unsigned short lofst,
   unsigned short blkh,
   unsigned short num_coef,
   __vptr_uint8 output_ptr,
   unsigned short rnd_bits,
   unsigned short pblock[])
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_yuv420_fir2d_separable_y_init(data_ptr, inter_ptr, coefh_ptr, coefv_ptr, blkw, lofst, blkh, num_coef, output_ptr, rnd_bits, pblock);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_yuv420_fir2d_separable_y_vloops(pblock);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

#pragma DATA_SECTION(__pblock_vcop_yuv420_fir2d_separable_uv, ".vcop_parameter_block")
#pragma DATA_ALIGN(__pblock_vcop_yuv420_fir2d_separable_uv, __ALIGNOF__(int));
unsigned short __pblock_vcop_yuv420_fir2d_separable_uv[38];

unsigned int vcop_yuv420_fir2d_separable_uv_param_count(void)
{
   return 38u;
}

unsigned int vcop_yuv420_fir2d_separable_uv_ctrl_count(void)
{
   return 0u;
}

unsigned int vcop_yuv420_fir2d_separable_uv_init(
   __vptr_uint8 UVdata_ptr,
   __vptr_int16 inter_ptr,
   __vptr_int8 coefh_ptr,
   __vptr_int8 coefv_ptr,
   unsigned short blkw,
   unsigned short lofst,
   unsigned short blkh,
   unsigned short num_coef,
   __vptr_uint8 UVout_ptr,
   unsigned short rnd_bits,
   unsigned short pblock[])
{
   int __offset = 0;
   /* Loop 1 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), (blkh + num_coef - 1)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), (blkw/(2 * (8u)))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), (num_coef)-1u);
   __vcop_pblock_init32(pblock, __offset+_PREG(6), (uchar *)coefh_ptr);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)inter_ptr);
   __vcop_pblock_init16(pblock, __offset+_PREG(10), 32);
   __vcop_pblock_init16(pblock, __offset+_PREG(11), (blkw*sizeof(*inter_ptr)) -((2*8u)*sizeof(*inter_ptr))*((blkw/(2 * (8u)))-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(12), 2);
   __vcop_pblock_init16(pblock, __offset+_PREG(13), ((2*8u)*sizeof(*UVdata_ptr)) -(2*sizeof(*UVdata_ptr))*((num_coef)-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(14), (lofst*sizeof(*UVdata_ptr)) -((2*8u)*sizeof(*UVdata_ptr))*((blkw/(2 * (8u)))-1u) -(2*sizeof(*UVdata_ptr))*((num_coef)-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(15),  -(sizeof(*coefh_ptr))*((num_coef)-1u));
   __vcop_pblock_init32(pblock, __offset+_PREG(16), 0);
   __vcop_pblock_init32(pblock, __offset+_PREG(18), (uchar *)UVdata_ptr);
   __offset += 18;

   /* Loop 2 PREGS */
   const int preg_ref2 = _PREG(7);

   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), (blkh)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), (blkw/(2 * (8u)))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), (num_coef)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(6), __vcop_store_round_sat(SM_SYMM,preg_ref2,RM_ROUND,rnd_bits));
   __vcop_pblock_init16(pblock, __offset+_PREG(7), 255);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)coefv_ptr);
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)UVout_ptr);
   __vcop_pblock_init16(pblock, __offset+_PREG(12), 16);
   __vcop_pblock_init16(pblock, __offset+_PREG(13), (blkw*sizeof(*UVout_ptr)) -((2*8u)*sizeof(*UVout_ptr))*((blkw/(2 * (8u)))-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(14), (blkw*sizeof(*inter_ptr)));
   __vcop_pblock_init16(pblock, __offset+_PREG(15), ((2*8u)*sizeof(*inter_ptr)) -(blkw*sizeof(*inter_ptr))*((num_coef)-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(16), (blkw*sizeof(*inter_ptr)) -((2*8u)*sizeof(*inter_ptr))*((blkw/(2 * (8u)))-1u) -(blkw*sizeof(*inter_ptr))*((num_coef)-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(17),  -(sizeof(*coefh_ptr))*((num_coef)-1u));
   __vcop_pblock_init32(pblock, __offset+_PREG(18), 0);
   __vcop_pblock_init32(pblock, __offset+_PREG(20), (uchar *)inter_ptr);
   __offset += 20;

   return 38u;
}

void vcop_yuv420_fir2d_separable_uv_vloops(
   unsigned short pblock[])
{
   /* Kernel-wide Vector Registers */

   __vcop_param(&pblock[0]);

   /* VLOOP 1 Start */

   /* VLOOP Local Vector Registers */
   #pragma VCC_VREG("Vout1", 16);
   #pragma VCC_VREG("Vout2", 17);
   #pragma VCC_VREG("Vin1", 18);
   #pragma VCC_VREG("Vin2", 19);
   #pragma VCC_VREG("Vcoef", 20);
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("A2", "A0");
   #pragma EVE_REG("A0", "A1");
   #pragma EVE_REG("A1", "A2");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I1", "I2");
   #pragma EVE_REG("I2", "I3");
   #pragma EVE_REG("I3", "I4");
   

   __vcop_vloop(__vcop_compute(), 11u, 9u, 1u);
   __vcop_vinit(__vcop_sizeW(), __vcop_i4_zero(), _PREG(16), _VREG(16));
   __vcop_vinit(__vcop_sizeW(), __vcop_i4_zero(), _PREG(16), _VREG(17));
   __vcop_vagen(_AGEN(0), _PREG(0), _PREG(10), _PREG(11), _PREG(0));
   __vcop_vagen(_AGEN(1), _PREG(12), _PREG(13), _PREG(14), _PREG(0));
   __vcop_vagen(_AGEN(2), _PREG(1), _PREG(15), _PREG(15), _PREG(0));
   __vcop_vload(__vcop_sizeBU(), __vcop_dintrlv(), _PREG(18), _AGEN(1), _VPAIR(18,19), __vcop_alws());
   __vcop_vload(__vcop_sizeB(), __vcop_1pt(), _PREG(6), _AGEN(2), _VREG(20), __vcop_alws());
   __vcop_vmadd(_VREG(18), _VREG(20), _VREG(16), _PREG(0));
   __vcop_vmadd(_VREG(19), _VREG(20), _VREG(17), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeH(), __vcop_intrlv(), __vcop_last_i4(), _VPAIR(16,17), _PREG(8), _AGEN(0), _PREG(0));
   __vcop_vloop_end(1u);

   /* VLOOP 2 Start */

   /* VLOOP Local Vector Registers */
   #pragma VCC_VREG("Vcoef", 21);
   #pragma VCC_VREG("Vout1", 22);
   #pragma VCC_VREG("Vout2", 23);
   #pragma VCC_VREG("Vin1", 24);
   #pragma VCC_VREG("Vin2", 25);
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("A2", "A0");
   #pragma EVE_REG("A0", "A1");
   #pragma EVE_REG("A1", "A2");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I1", "I2");
   #pragma EVE_REG("I2", "I3");
   #pragma EVE_REG("I3", "I4");
   

   __vcop_vloop(__vcop_compute(), 11u, 10u, 2u);
   __vcop_vinit(__vcop_sizeW(), __vcop_i4_zero(), _PREG(18), _VREG(22));
   __vcop_vinit(__vcop_sizeW(), __vcop_i4_zero(), _PREG(18), _VREG(23));
   __vcop_vagen(_AGEN(0), _PREG(0), _PREG(12), _PREG(13), _PREG(0));
   __vcop_vagen(_AGEN(1), _PREG(14), _PREG(15), _PREG(16), _PREG(0));
   __vcop_vagen(_AGEN(2), _PREG(1), _PREG(17), _PREG(17), _PREG(0));
   __vcop_vload(__vcop_sizeH(), __vcop_dintrlv(), _PREG(20), _AGEN(1), _VPAIR(24,25), __vcop_alws());
   __vcop_vload(__vcop_sizeB(), __vcop_1pt(), _PREG(8), _AGEN(2), _VREG(21), __vcop_alws());
   __vcop_vmadd(_VREG(24), _VREG(21), _VREG(22), _PREG(0));
   __vcop_vmadd(_VREG(25), _VREG(21), _VREG(23), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeBU(), __vcop_intrlv(), __vcop_last_i4(), _VPAIR(22,23), _PREG(10), _AGEN(0), _PREG(6));
   __vcop_vloop_end(2u);

}

void vcop_yuv420_fir2d_separable_uv(
   __vptr_uint8 UVdata_ptr,
   __vptr_int16 inter_ptr,
   __vptr_int8 coefh_ptr,
   __vptr_int8 coefv_ptr,
   unsigned short blkw,
   unsigned short lofst,
   unsigned short blkh,
   unsigned short num_coef,
   __vptr_uint8 UVout_ptr,
   unsigned short rnd_bits)
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_yuv420_fir2d_separable_uv_init(UVdata_ptr, inter_ptr, coefh_ptr, coefv_ptr, blkw, lofst, blkh, num_coef, UVout_ptr, rnd_bits, __pblock_vcop_yuv420_fir2d_separable_uv);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_yuv420_fir2d_separable_uv_vloops(__pblock_vcop_yuv420_fir2d_separable_uv);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

void vcop_yuv420_fir2d_separable_uv_custom(
   __vptr_uint8 UVdata_ptr,
   __vptr_int16 inter_ptr,
   __vptr_int8 coefh_ptr,
   __vptr_int8 coefv_ptr,
   unsigned short blkw,
   unsigned short lofst,
   unsigned short blkh,
   unsigned short num_coef,
   __vptr_uint8 UVout_ptr,
   unsigned short rnd_bits,
   unsigned short pblock[])
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_yuv420_fir2d_separable_uv_init(UVdata_ptr, inter_ptr, coefh_ptr, coefv_ptr, blkw, lofst, blkh, num_coef, UVout_ptr, rnd_bits, pblock);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_yuv420_fir2d_separable_uv_vloops(pblock);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

