#include <vcop\vcop.h>

typedef unsigned char uchar;

#pragma DATA_SECTION(__pblock_vcop_compute_rBrief, ".vcop_parameter_block")
#pragma DATA_ALIGN(__pblock_vcop_compute_rBrief, __ALIGNOF__(int));
unsigned short __pblock_vcop_compute_rBrief[220];

unsigned int vcop_compute_rBrief_param_count(void)
{
   return 220u;
}

unsigned int vcop_compute_rBrief_ctrl_count(void)
{
   return 0u;
}

unsigned int vcop_compute_rBrief_init(
   __vptr_int8 moments_col_mask,
   __vptr_int16 moments_col_sum,
   __vptr_int8 moments_row_mask,
   __vptr_int16 moments_row_sum,
   __vptr_int16 moments_m10,
   __vptr_int16 moments_m01,
   __vptr_uint16 arctan_xthr,
   __vptr_uint8 arctan_pack_decision,
   __vptr_int16 cos_array_ptr,
   __vptr_int16 sin_array_ptr,
   __vptr_uint16 offset_ptr,
   __vptr_int16 cos_ptr,
   __vptr_int16 sin_ptr,
   __vptr_uint8 input_image_ptr,
   __vptr_int16 col_sum_ptr,
   __vptr_int16 row_col_sum_ct_ptr,
   __vptr_int8 in_src_dst_x_ptr,
   __vptr_int8 in_src_dst_y_ptr,
   __vptr_int8 rot_src_dst_ptr_x,
   __vptr_int8 rot_src_dst_ptr_y,
   __vptr_uint16 rot_src_lin_ptr,
   __vptr_uint16 rot_dst_lin_ptr,
   __vptr_int16 tlu_src_ptr,
   __vptr_int16 tlu_dst_ptr,
   __vptr_uint8 true_descriptor_optr,
   unsigned short pblock[])
{
   int __offset = 0;
   /* Loop 1 PREGS */
   const int preg_ref1 = _PREG(7);

   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), (1)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), ((32)/(2*(8u)))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), ((32))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(6), __vcop_store_round_sat(SM_ASYMM,preg_ref1,RM_NONE,0));
   __vcop_pblock_init16(pblock, __offset+_PREG(7), 32767);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)moments_col_mask);
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)moments_row_mask);
   __vcop_pblock_init32(pblock, __offset+_PREG(12), (uchar *)moments_col_sum);
   __vcop_pblock_init32(pblock, __offset+_PREG(14), (uchar *)moments_row_sum);
   __vcop_pblock_init16(pblock, __offset+_PREG(16), 48);
   __vcop_pblock_init16(pblock, __offset+_PREG(17), -1472);
   __vcop_pblock_init16(pblock, __offset+_PREG(18), -1504);
   __vcop_pblock_init16(pblock, __offset+_PREG(19), 32);
   __vcop_pblock_init16(pblock, __offset+_PREG(20), -976);
   __vcop_pblock_init16(pblock, __offset+_PREG(21), -1008);
   __vcop_pblock_init32(pblock, __offset+_PREG(22), 0);
   __vcop_pblock_init32(pblock, __offset+_PREG(24), (uchar *)input_image_ptr+(5*48+8*48+8)*sizeof(*input_image_ptr));
   __offset += 24;

   /* Loop 2 PREGS */
   const int preg_ref2 = _PREG(7);

   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), (1)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), ((32)/2)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(6), __vcop_store_round_sat(SM_ASYMM,preg_ref2,RM_NONE,0));
   __vcop_pblock_init16(pblock, __offset+_PREG(7), 32767);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)moments_row_sum);
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)moments_m10);
   __vcop_pblock_init32(pblock, __offset+_PREG(12), (uchar *)moments_m01);
   __vcop_pblock_init16(pblock, __offset+_PREG(14), 2);
   __vcop_pblock_init16(pblock, __offset+_PREG(15), -30);
   __vcop_pblock_init32(pblock, __offset+_PREG(16), 0);
   __vcop_pblock_init32(pblock, __offset+_PREG(18), (uchar *)moments_col_sum);
   __offset += 18;

   /* Loop 3 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), (1)-1u);
   __vcop_pblock_init32(pblock, __offset+_PREG(6), (uchar *)moments_m10);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)moments_m01);
   __vcop_pblock_init16(pblock, __offset+_PREG(10), __vcop_vop_round(1, 8));
   __vcop_pblock_init16(pblock, __offset+_PREG(11), 2);
   __vcop_pblock_init32(pblock, __offset+_PREG(12), 0);
   __vcop_pblock_init32(pblock, __offset+_PREG(14), (uchar *)arctan_xthr);
   __offset += 14;

   /* Loop 4 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), (1)-1u);
   __vcop_pblock_init32(pblock, __offset+_PREG(6), 8);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), 16);
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)moments_m10);
   __vcop_pblock_init32(pblock, __offset+_PREG(12), (uchar *)moments_m01);
   __vcop_pblock_init32(pblock, __offset+_PREG(14), (uchar *)arctan_pack_decision);
   __vcop_pblock_init16(pblock, __offset+_PREG(16), 2);
   __vcop_pblock_init32(pblock, __offset+_PREG(18), 0);
   __vcop_pblock_init32(pblock, __offset+_PREG(20), 24);
   __offset += 20;

   /* Loop 5 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), ((48)/(2*(8u)))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), ((48))-1u);
   __vcop_pblock_init32(pblock, __offset+_PREG(6), (uchar *)input_image_ptr);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)input_image_ptr+5*48*sizeof(*input_image_ptr));
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)col_sum_ptr+5*(48+2)*sizeof(*col_sum_ptr));
   __vcop_pblock_init32(pblock, __offset+_PREG(12), (uchar *)col_sum_ptr+5*(48+2)*sizeof(*col_sum_ptr)+(48+2)*8*sizeof(*col_sum_ptr));
   __vcop_pblock_init16(pblock, __offset+_PREG(14), 2);
   __vcop_pblock_init16(pblock, __offset+_PREG(15), 1506);
   __vcop_pblock_init16(pblock, __offset+_PREG(16), 48);
   __vcop_pblock_init16(pblock, __offset+_PREG(17), -2240);
   __vcop_pblock_init32(pblock, __offset+_PREG(18), (uchar *)offset_ptr);
   __vcop_pblock_init32(pblock, __offset+_PREG(20), 0);
   __offset += 20;

   /* Loop 6 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), ((48)/(2*(8u)))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), ((48))-1u);
   __vcop_pblock_init32(pblock, __offset+_PREG(6), (uchar *)col_sum_ptr+5*(48+2)*sizeof(*col_sum_ptr));
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)row_col_sum_ct_ptr);
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)row_col_sum_ct_ptr+2*(8u*sizeof(*col_sum_ptr)));
   __vcop_pblock_init32(pblock, __offset+_PREG(12), (uchar *)row_col_sum_ct_ptr+8*sizeof(*row_col_sum_ct_ptr));
   __vcop_pblock_init32(pblock, __offset+_PREG(14), (uchar *)row_col_sum_ct_ptr+8*sizeof(*row_col_sum_ct_ptr)+2*(8u*sizeof(*col_sum_ptr)));
   __vcop_pblock_init16(pblock, __offset+_PREG(16), 192);
   __vcop_pblock_init16(pblock, __offset+_PREG(17), -8960);
   __vcop_pblock_init16(pblock, __offset+_PREG(18), 100);
   __vcop_pblock_init16(pblock, __offset+_PREG(19), -4668);
   __vcop_pblock_init32(pblock, __offset+_PREG(20), 0);
   __vcop_pblock_init32(pblock, __offset+_PREG(22), (uchar *)col_sum_ptr);
   __offset += 22;

   /* Loop 7 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), (1)-1u);
   __vcop_pblock_init32(pblock, __offset+_PREG(6), (uchar *)sin_ptr);
   __vcop_pblock_init16(pblock, __offset+_PREG(8), 2);
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)arctan_pack_decision);
   __vcop_pblock_init32(pblock, __offset+_PREG(12), (uchar *)sin_array_ptr);
   __offset += 12;

   /* Loop 8 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), (1)-1u);
   __vcop_pblock_init32(pblock, __offset+_PREG(6), (uchar *)cos_ptr);
   __vcop_pblock_init16(pblock, __offset+_PREG(8), 2);
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)arctan_pack_decision);
   __vcop_pblock_init32(pblock, __offset+_PREG(12), (uchar *)cos_array_ptr);
   __offset += 12;

   /* Loop 9 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), (512/(2*(8u)))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(6), __vcop_store_round_sat(SM_NONE,0,RM_ROUND,14));
   __vcop_pblock_init16(pblock, __offset+_PREG(7), 16);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)in_src_dst_x_ptr);
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)in_src_dst_y_ptr);
   __vcop_pblock_init32(pblock, __offset+_PREG(12), (uchar *)rot_src_dst_ptr_x);
   __vcop_pblock_init32(pblock, __offset+_PREG(14), (uchar *)rot_src_dst_ptr_y);
   __vcop_pblock_init32(pblock, __offset+_PREG(16), (uchar *)cos_ptr);
   __vcop_pblock_init32(pblock, __offset+_PREG(18), (uchar *)sin_ptr);
   __offset += 18;

   /* Loop 10 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), (256/(2*(8u)))-1u);
   __vcop_pblock_init32(pblock, __offset+_PREG(6), (uchar *)rot_src_dst_ptr_x);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)rot_src_dst_ptr_y);
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)rot_src_dst_ptr_x+256*sizeof(*rot_src_dst_ptr_x));
   __vcop_pblock_init32(pblock, __offset+_PREG(12), (uchar *)rot_src_dst_ptr_y+256*sizeof(*rot_src_dst_ptr_y));
   __vcop_pblock_init32(pblock, __offset+_PREG(14), (uchar *)rot_src_lin_ptr);
   __vcop_pblock_init32(pblock, __offset+_PREG(16), (uchar *)rot_dst_lin_ptr);
   __vcop_pblock_init16(pblock, __offset+_PREG(18), 16);
   __vcop_pblock_init16(pblock, __offset+_PREG(19), 32);
   __vcop_pblock_init32(pblock, __offset+_PREG(20), 1225);
   __vcop_pblock_init32(pblock, __offset+_PREG(22), (48));
   __offset += 22;

   /* Loop 11 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), (256/2)-1u);
   __vcop_pblock_init32(pblock, __offset+_PREG(6), (uchar *)tlu_src_ptr);
   __vcop_pblock_init16(pblock, __offset+_PREG(8), 4);
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)rot_src_lin_ptr);
   __vcop_pblock_init32(pblock, __offset+_PREG(12), (uchar *)row_col_sum_ct_ptr);
   __offset += 12;

   /* Loop 12 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), (256/2)-1u);
   __vcop_pblock_init32(pblock, __offset+_PREG(6), (uchar *)tlu_dst_ptr);
   __vcop_pblock_init16(pblock, __offset+_PREG(8), 4);
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)rot_dst_lin_ptr);
   __vcop_pblock_init32(pblock, __offset+_PREG(12), (uchar *)row_col_sum_ct_ptr);
   __offset += 12;

   /* Loop 13 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), (256/(2*(8u)))-1u);
   __vcop_pblock_init32(pblock, __offset+_PREG(6), (uchar *)true_descriptor_optr);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)true_descriptor_optr+sizeof(*input_image_ptr));
   __vcop_pblock_init16(pblock, __offset+_PREG(10), 32);
   __vcop_pblock_init16(pblock, __offset+_PREG(11), 2);
   __vcop_pblock_init32(pblock, __offset+_PREG(12), (uchar *)tlu_src_ptr);
   __vcop_pblock_init32(pblock, __offset+_PREG(14), (uchar *)tlu_dst_ptr);
   __offset += 14;

   return 220u;
}

void vcop_compute_rBrief_vloops(
   unsigned short pblock[])
{
   /* Kernel-wide Vector Registers */
   #pragma VCC_VREG("V_offset", 16);
   #pragma VCC_VREG("Voff", 17);

   __vcop_param(&pblock[0]);

   /* VLOOP 1 Start */

   /* VLOOP Local Vector Registers */
   #pragma VCC_VREG("VSum1", 18);
   #pragma VCC_VREG("VSum2", 19);
   #pragma VCC_VREG("VSum3", 20);
   #pragma VCC_VREG("VSum4", 21);
   #pragma VCC_VREG("Vin1", 22);
   #pragma VCC_VREG("Vin2", 23);
   #pragma VCC_VREG("Vin3", 24);
   #pragma VCC_VREG("Vin4", 25);
   #pragma VCC_VREG("Vin5", 26);
   #pragma VCC_VREG("Vin6", 27);
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("Addr_off", "A0");
   #pragma EVE_REG("Addr_in1", "A1");
   #pragma EVE_REG("Addr_mask1", "A2");
   #pragma EVE_REG("Addr_out", "A3");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I3", "I2");
   #pragma EVE_REG("I1", "I3");
   #pragma EVE_REG("I2", "I4");
   

   __vcop_vloop(__vcop_compute(), 18u, 12u, 1u);
   __vcop_vinit(__vcop_sizeW(), __vcop_i34_zero(), _PREG(22), _VREG(18));
   __vcop_vinit(__vcop_sizeW(), __vcop_i34_zero(), _PREG(22), _VREG(19));
   __vcop_vinit(__vcop_sizeW(), __vcop_i34_zero(), _PREG(22), _VREG(20));
   __vcop_vinit(__vcop_sizeW(), __vcop_i34_zero(), _PREG(22), _VREG(21));
   __vcop_vagen(_AGEN(1), _PREG(16), _PREG(17), _PREG(18), _PREG(0));
   __vcop_vagen(_AGEN(2), _PREG(19), _PREG(20), _PREG(21), _PREG(0));
   __vcop_vagen(_AGEN(3), _PREG(0), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeBU(), __vcop_dintrlv(), _PREG(24), _AGEN(1), _VPAIR(22,24), __vcop_alws());
   __vcop_vload(__vcop_sizeB(), __vcop_dintrlv(), _PREG(8), _AGEN(2), _VPAIR(23,25), __vcop_alws());
   __vcop_vload(__vcop_sizeB(), __vcop_dintrlv(), _PREG(10), _AGEN(2), _VPAIR(26,27), __vcop_alws());
   __vcop_vmadd(_VREG(22), _VREG(23), _VREG(18), _PREG(0));
   __vcop_vmadd(_VREG(24), _VREG(25), _VREG(19), _PREG(0));
   __vcop_vmadd(_VREG(22), _VREG(26), _VREG(20), _PREG(0));
   __vcop_vmadd(_VREG(24), _VREG(27), _VREG(21), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeH(), __vcop_intrlv(), __vcop_last_i34(), _VPAIR(18,19), _PREG(12), _AGEN(3), _PREG(6));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeH(), __vcop_intrlv(), __vcop_last_i34(), _VPAIR(20,21), _PREG(14), _AGEN(3), _PREG(6));
   __vcop_vloop_end(1u);

   /* VLOOP 2 Start */

   /* VLOOP Local Vector Registers */
   #pragma VCC_VREG("VSum1", 28);
   #pragma VCC_VREG("VSum2", 29);
   #pragma VCC_VREG("Vin1", 30);
   #pragma VCC_VREG("Vin2", 31);
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("Addr_off", "A0");
   #pragma EVE_REG("Addr_in1", "A1");
   #pragma EVE_REG("Addr_out", "A2");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I1", "I3");
   #pragma EVE_REG("I2", "I4");
   

   __vcop_vloop(__vcop_compute(), 12u, 9u, 2u);
   __vcop_vinit(__vcop_sizeW(), __vcop_i4_zero(), _PREG(16), _VREG(28));
   __vcop_vinit(__vcop_sizeW(), __vcop_i4_zero(), _PREG(16), _VREG(29));
   __vcop_vagen(_AGEN(1), _PREG(14), _PREG(15), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(2), _PREG(0), _PREG(14), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeH(), __vcop_1pt(), _PREG(18), _AGEN(1), _VREG(30), __vcop_alws());
   __vcop_vload(__vcop_sizeH(), __vcop_1pt(), _PREG(8), _AGEN(1), _VREG(31), __vcop_alws());
   __vcop_vadd(_VREG(28), _VREG(30), _VREG(28));
   __vcop_vadd(_VREG(29), _VREG(31), _VREG(29));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeH(), __vcop_1pt(), __vcop_last_i4(), _VREG(28), _PREG(10), _AGEN(2), _PREG(6));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeH(), __vcop_1pt(), __vcop_last_i4(), _VREG(29), _PREG(12), _AGEN(2), _PREG(6));
   __vcop_vloop_end(2u);

   /* VLOOP 3 Start */

   /* VLOOP Local Vector Registers */
   #pragma VCC_VREG("V_decision", 32);
   #pragma VCC_VREG("Vx", 33);
   #pragma VCC_VREG("Vx_abs", 34);
   #pragma VCC_VREG("Vx_multhr", 35);
   #pragma VCC_VREG("Vxthr", 36);
   #pragma VCC_VREG("Vy", 37);
   #pragma VCC_VREG("Vy_abs", 38);
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("Addr_off", "A0");
   #pragma EVE_REG("Addr_in1", "A1");
   #pragma EVE_REG("Addr_out", "A2");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I1", "I4");
   

   __vcop_vloop(__vcop_compute(), 13u, 7u, 3u);
   __vcop_vinit(__vcop_sizeW(), __vcop_once(), _PREG(12), _VREG(16));
   __vcop_vagen(_AGEN(1), _PREG(11), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeHU(), __vcop_npt(), _PREG(14), _AGEN(1), _VREG(36), __vcop_alws());
   __vcop_vload(__vcop_sizeH(), __vcop_1pt(), _PREG(6), _AGEN(1), _VREG(33), __vcop_alws());
   __vcop_vload(__vcop_sizeH(), __vcop_1pt(), _PREG(8), _AGEN(1), _VREG(37), __vcop_alws());
   __vcop_vabs(_VREG(33), _VREG(34));
   __vcop_vabs(_VREG(37), _VREG(38));
   __vcop_vmpy(_VREG(34), _VREG(36), _VREG(35), _PREG(10));
   __vcop_vbitpk(_VREG(38), _VREG(35), _VREG(32));
   __vcop_vbitc(_VREG(32), _VREG(16));
   __vcop_vloop_end(3u);

   /* VLOOP 4 Start */

   /* VLOOP Local Vector Registers */
   #pragma VCC_VREG("Vk_0", 39);
   #pragma VCC_VREG("Vk_16", 40);
   #pragma VCC_VREG("Vk_24", 41);
   #pragma VCC_VREG("Vk_8", 42);
   #pragma VCC_VREG("Vquad_offset", 43);
   #pragma VCC_VREG("Vx", 44);
   #pragma VCC_VREG("Vx_0", 45);
   #pragma VCC_VREG("Vx_1", 46);
   #pragma VCC_VREG("Vx_sign", 47);
   #pragma VCC_VREG("Vxy_xor", 48);
   #pragma VCC_VREG("Vy", 49);
   #pragma VCC_VREG("Vy_sign", 50);
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("Addr_off", "A0");
   #pragma EVE_REG("Addr_in1", "A1");
   #pragma EVE_REG("Addr_out", "A2");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I1", "I4");
   

   __vcop_vloop(__vcop_compute(), 20u, 10u, 4u);
   __vcop_vinit(__vcop_sizeW(), __vcop_alws(), _PREG(18), _VREG(45));
   __vcop_vinit(__vcop_sizeW(), __vcop_alws(), _PREG(20), _VREG(46));
   __vcop_vinit(__vcop_sizeW(), __vcop_alws(), _PREG(18), _VREG(39));
   __vcop_vinit(__vcop_sizeW(), __vcop_alws(), _PREG(6), _VREG(42));
   __vcop_vinit(__vcop_sizeW(), __vcop_alws(), _PREG(8), _VREG(40));
   __vcop_vagen(_AGEN(1), _PREG(16), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(2), _PREG(1), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeH(), __vcop_1pt(), _PREG(10), _AGEN(1), _VREG(44), __vcop_alws());
   __vcop_vload(__vcop_sizeH(), __vcop_1pt(), _PREG(12), _AGEN(1), _VREG(49), __vcop_alws());
   __vcop_vcmpgt(_VREG(39), _VREG(44), _VREG(47));
   __vcop_vcmpgt(_VREG(39), _VREG(49), _VREG(50));
   __vcop_vxor(_VREG(47), _VREG(50), _VREG(48));
   __vcop_vsel(_VREG(47), _VREG(40), _VREG(45));
   __vcop_vsel(_VREG(47), _VREG(42), _VREG(46));
   __vcop_vor(_VREG(45), _VREG(45), _VREG(43));
   __vcop_vsel(_VREG(48), _VREG(46), _VREG(43));
   __vcop_vadd(_VREG(43), _VREG(16), _VREG(43));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeBU(), __vcop_npt(), __vcop_alws(), _VREG(43), _PREG(14), _AGEN(2), _PREG(0));
   __vcop_vloop_end(4u);

   /* VLOOP 5 Start */

   /* VLOOP Local Vector Registers */
   #pragma VCC_VREG("VSum1", 51);
   #pragma VCC_VREG("VSum2", 52);
   #pragma VCC_VREG("Vin1", 53);
   #pragma VCC_VREG("Vin2", 54);
   #pragma VCC_VREG("Vin3", 55);
   #pragma VCC_VREG("Vin4", 56);
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("Addr_off", "A0");
   #pragma EVE_REG("Addr_out", "A1");
   #pragma EVE_REG("Addr_sub", "A2");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I1", "I3");
   #pragma EVE_REG("I2", "I4");
   

   __vcop_vloop(__vcop_compute(), 17u, 10u, 5u);
   __vcop_vinit(__vcop_sizeW(), __vcop_i4_zero(), _PREG(20), _VREG(51));
   __vcop_vinit(__vcop_sizeW(), __vcop_i4_zero(), _PREG(20), _VREG(52));
   __vcop_vagen(_AGEN(0), _PREG(0), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(1), _PREG(14), _PREG(15), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(2), _PREG(16), _PREG(17), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeHU(), __vcop_npt(), _PREG(18), _AGEN(0), _VREG(17), __vcop_once());
   __vcop_vload(__vcop_sizeBU(), __vcop_dintrlv(), _PREG(6), _AGEN(2), _VPAIR(53,55), __vcop_alws());
   __vcop_vload(__vcop_sizeBU(), __vcop_dintrlv(), _PREG(8), _AGEN(2), _VPAIR(54,56), __vcop_alws());
   __vcop_vintrlv(_VREG(53), _VREG(55));
   __vcop_vintrlv(_VREG(54), _VREG(56));
   __vcop_vadd(_VREG(51), _VREG(54), _VREG(51));
   __vcop_vadd(_VREG(52), _VREG(56), _VREG(52));
   __vcop_vsub(_VREG(51), _VREG(53), _VREG(51));
   __vcop_vsub(_VREG(52), _VREG(55), _VREG(52));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeH(), __vcop_pdda(_VREG(17)), __vcop_alws(), _VREG(51), _PREG(10), _AGEN(1), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeH(), __vcop_pdda(_VREG(17)), __vcop_alws(), _VREG(52), _PREG(12), _AGEN(1), _PREG(0));
   __vcop_vloop_end(5u);

   /* VLOOP 6 Start */

   /* VLOOP Local Vector Registers */
   #pragma VCC_VREG("VSum1", 57);
   #pragma VCC_VREG("VSum2", 58);
   #pragma VCC_VREG("Vin1", 59);
   #pragma VCC_VREG("Vin2", 60);
   #pragma VCC_VREG("Vin3", 61);
   #pragma VCC_VREG("Vin4", 62);
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("Addr_off", "A0");
   #pragma EVE_REG("Addr_out", "A1");
   #pragma EVE_REG("Addr_sub", "A2");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I1", "I3");
   #pragma EVE_REG("I2", "I4");
   

   __vcop_vloop(__vcop_compute(), 18u, 11u, 6u);
   __vcop_vinit(__vcop_sizeW(), __vcop_i4_zero(), _PREG(20), _VREG(57));
   __vcop_vinit(__vcop_sizeW(), __vcop_i4_zero(), _PREG(20), _VREG(58));
   __vcop_vagen(_AGEN(1), _PREG(16), _PREG(17), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(2), _PREG(18), _PREG(19), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeH(), __vcop_dintrlv(), _PREG(22), _AGEN(2), _VPAIR(59,61), __vcop_alws());
   __vcop_vload(__vcop_sizeH(), __vcop_dintrlv(), _PREG(6), _AGEN(2), _VPAIR(60,62), __vcop_alws());
   __vcop_vintrlv(_VREG(59), _VREG(61));
   __vcop_vintrlv(_VREG(60), _VREG(62));
   __vcop_vadd(_VREG(57), _VREG(60), _VREG(57));
   __vcop_vadd(_VREG(58), _VREG(62), _VREG(58));
   __vcop_vsub(_VREG(57), _VREG(59), _VREG(57));
   __vcop_vsub(_VREG(58), _VREG(61), _VREG(58));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeH(), __vcop_npt(), __vcop_alws(), _VREG(57), _PREG(8), _AGEN(1), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeH(), __vcop_npt(), __vcop_alws(), _VREG(58), _PREG(10), _AGEN(1), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeH(), __vcop_npt(), __vcop_alws(), _VREG(57), _PREG(12), _AGEN(1), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeH(), __vcop_npt(), __vcop_alws(), _VREG(58), _PREG(14), _AGEN(1), _PREG(0));
   __vcop_vloop_end(6u);

   /* VLOOP 7 Start */

   /* VLOOP Local Vector Registers */
   #pragma VCC_VREG("Vindex", 63);
   #pragma VCC_VREG("Vtabledata", 64);
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("index_addr", "A0");
   #pragma EVE_REG("out_addr", "A2");
   #pragma EVE_REG("table_addr", "A1");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I2", "I4");
   

   __vcop_vloop(__vcop_tablelkup(), 7u, 6u, 7u);
   __vcop_vagen(_AGEN(0), _PREG(1), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(2), _PREG(8), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(1), _PREG(0), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeBU(), __vcop_npt(), _PREG(10), _AGEN(0), _VREG(63), __vcop_alws());
   __vcop_vtbload(__vcop_sizeH(), __vcop_tableinfo(1, 1), _PREG(12), _AGEN(1), _VREG(63), _VREG(64), _PREG(0), __vcop_alws());
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeH(), __vcop_npt(), __vcop_alws(), _VREG(64), _PREG(6), _AGEN(2), _PREG(0));
   __vcop_vloop_end(7u);

   /* VLOOP 8 Start */

   /* VLOOP Local Vector Registers */
   #pragma VCC_VREG("Vindex", 65);
   #pragma VCC_VREG("Vtabledata", 66);
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("index_addr", "A0");
   #pragma EVE_REG("out_addr", "A2");
   #pragma EVE_REG("table_addr", "A1");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I2", "I4");
   

   __vcop_vloop(__vcop_tablelkup(), 7u, 6u, 8u);
   __vcop_vagen(_AGEN(0), _PREG(1), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(2), _PREG(8), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(1), _PREG(0), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeBU(), __vcop_npt(), _PREG(10), _AGEN(0), _VREG(65), __vcop_alws());
   __vcop_vtbload(__vcop_sizeH(), __vcop_tableinfo(1, 1), _PREG(12), _AGEN(1), _VREG(65), _VREG(66), _PREG(0), __vcop_alws());
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeH(), __vcop_npt(), __vcop_alws(), _VREG(66), _PREG(6), _AGEN(2), _PREG(0));
   __vcop_vloop_end(8u);

   /* VLOOP 9 Start */

   /* VLOOP Local Vector Registers */
   #pragma VCC_VREG("Vin_x_1", 67);
   #pragma VCC_VREG("Vin_x_2", 68);
   #pragma VCC_VREG("Vin_y_1", 69);
   #pragma VCC_VREG("Vin_y_2", 70);
   #pragma VCC_VREG("Vout_x_1", 71);
   #pragma VCC_VREG("Vout_x_2", 72);
   #pragma VCC_VREG("Vout_y_1", 73);
   #pragma VCC_VREG("Vout_y_2", 74);
   #pragma VCC_VREG("cos_phi", 75);
   #pragma VCC_VREG("sin_phi", 76);
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("Addr_off", "A0");
   #pragma EVE_REG("Addr_1", "A1");
   #pragma EVE_REG("Addr_2", "A2");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I1", "I4");
   

   __vcop_vloop(__vcop_compute(), 18u, 9u, 9u);
   __vcop_vagen(_AGEN(1), _PREG(0), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(2), _PREG(7), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeH(), __vcop_1pt(), _PREG(16), _AGEN(1), _VREG(75), __vcop_alws_condload());
   __vcop_vload(__vcop_sizeH(), __vcop_1pt(), _PREG(18), _AGEN(1), _VREG(76), __vcop_alws_condload());
   __vcop_vload(__vcop_sizeB(), __vcop_dintrlv(), _PREG(8), _AGEN(2), _VPAIR(67,68), __vcop_alws());
   __vcop_vload(__vcop_sizeB(), __vcop_dintrlv(), _PREG(10), _AGEN(2), _VPAIR(69,70), __vcop_alws());
   __vcop_vmpy(_VREG(67), _VREG(75), _VREG(71), _PREG(0));
   __vcop_vmpy(_VREG(68), _VREG(75), _VREG(72), _PREG(0));
   __vcop_vmsub(_VREG(69), _VREG(76), _VREG(71), _PREG(0));
   __vcop_vmsub(_VREG(70), _VREG(76), _VREG(72), _PREG(0));
   __vcop_vmpy(_VREG(69), _VREG(75), _VREG(73), _PREG(0));
   __vcop_vmadd(_VREG(67), _VREG(76), _VREG(73), _PREG(0));
   __vcop_vmpy(_VREG(70), _VREG(75), _VREG(74), _PREG(0));
   __vcop_vmadd(_VREG(68), _VREG(76), _VREG(74), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeB(), __vcop_intrlv(), __vcop_alws(), _VPAIR(71,72), _PREG(12), _AGEN(2), _PREG(6));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeB(), __vcop_intrlv(), __vcop_alws(), _VPAIR(73,74), _PREG(14), _AGEN(2), _PREG(6));
   __vcop_vloop_end(9u);

   /* VLOOP 10 Start */

   /* VLOOP Local Vector Registers */
   #pragma VCC_VREG("V_width", 77);
   #pragma VCC_VREG("Vconst", 78);
   #pragma VCC_VREG("Vin_x_1", 79);
   #pragma VCC_VREG("Vin_x_2", 80);
   #pragma VCC_VREG("Vin_x_3", 81);
   #pragma VCC_VREG("Vin_x_4", 82);
   #pragma VCC_VREG("Vin_y_1", 83);
   #pragma VCC_VREG("Vin_y_2", 84);
   #pragma VCC_VREG("Vin_y_3", 85);
   #pragma VCC_VREG("Vin_y_4", 86);
   #pragma VCC_VREG("Vout_y_1", 87);
   #pragma VCC_VREG("Vout_y_2", 88);
   #pragma VCC_VREG("Vout_y_3", 89);
   #pragma VCC_VREG("Vout_y_4", 90);
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("Addr_off", "A0");
   #pragma EVE_REG("Addr_2", "A1");
   #pragma EVE_REG("Addr_3", "A2");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I1", "I4");
   

   __vcop_vloop(__vcop_compute(), 20u, 11u, 10u);
   __vcop_vinit(__vcop_sizeW(), __vcop_alws(), _PREG(20), _VREG(78));
   __vcop_vinit(__vcop_sizeW(), __vcop_alws(), _PREG(22), _VREG(77));
   __vcop_vagen(_AGEN(1), _PREG(18), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(2), _PREG(19), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeB(), __vcop_dintrlv(), _PREG(6), _AGEN(1), _VPAIR(79,80), __vcop_alws());
   __vcop_vload(__vcop_sizeB(), __vcop_dintrlv(), _PREG(8), _AGEN(1), _VPAIR(83,84), __vcop_alws());
   __vcop_vload(__vcop_sizeB(), __vcop_dintrlv(), _PREG(10), _AGEN(1), _VPAIR(81,82), __vcop_alws());
   __vcop_vload(__vcop_sizeB(), __vcop_dintrlv(), _PREG(12), _AGEN(1), _VPAIR(85,86), __vcop_alws());
   __vcop_vadd(_VREG(78), _VREG(83), _VREG(87));
   __vcop_vmadd(_VREG(79), _VREG(77), _VREG(87), _PREG(0));
   __vcop_vadd(_VREG(85), _VREG(78), _VREG(89));
   __vcop_vmadd(_VREG(81), _VREG(77), _VREG(89), _PREG(0));
   __vcop_vadd(_VREG(78), _VREG(84), _VREG(88));
   __vcop_vmadd(_VREG(80), _VREG(77), _VREG(88), _PREG(0));
   __vcop_vadd(_VREG(86), _VREG(78), _VREG(90));
   __vcop_vmadd(_VREG(82), _VREG(77), _VREG(90), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeHU(), __vcop_intrlv(), __vcop_alws(), _VPAIR(87,88), _PREG(14), _AGEN(2), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeHU(), __vcop_intrlv(), __vcop_alws(), _VPAIR(89,90), _PREG(16), _AGEN(2), _PREG(0));
   __vcop_vloop_end(10u);

   /* VLOOP 11 Start */

   /* VLOOP Local Vector Registers */
   #pragma VCC_VREG("Vindex", 91);
   #pragma VCC_VREG("Vtabledata", 92);
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("index_addr", "A0");
   #pragma EVE_REG("out_addr", "A2");
   #pragma EVE_REG("table_addr", "A1");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I2", "I4");
   

   __vcop_vloop(__vcop_tablelkup(), 7u, 6u, 11u);
   __vcop_vagen(_AGEN(0), _PREG(8), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(2), _PREG(8), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(1), _PREG(0), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeHU(), __vcop_npt(), _PREG(10), _AGEN(0), _VREG(91), __vcop_alws());
   __vcop_vtbload(__vcop_sizeH(), __vcop_tableinfo(2, 1), _PREG(12), _AGEN(1), _VREG(91), _VREG(92), _PREG(0), __vcop_alws());
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeH(), __vcop_npt(), __vcop_alws(), _VREG(92), _PREG(6), _AGEN(2), _PREG(0));
   __vcop_vloop_end(11u);

   /* VLOOP 12 Start */

   /* VLOOP Local Vector Registers */
   #pragma VCC_VREG("Vindex", 93);
   #pragma VCC_VREG("Vtabledata", 94);
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("index_addr", "A0");
   #pragma EVE_REG("out_addr", "A2");
   #pragma EVE_REG("table_addr", "A1");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I2", "I4");
   

   __vcop_vloop(__vcop_tablelkup(), 7u, 6u, 12u);
   __vcop_vagen(_AGEN(0), _PREG(8), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(2), _PREG(8), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(1), _PREG(0), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeHU(), __vcop_npt(), _PREG(10), _AGEN(0), _VREG(93), __vcop_alws());
   __vcop_vtbload(__vcop_sizeH(), __vcop_tableinfo(2, 1), _PREG(12), _AGEN(1), _VREG(93), _VREG(94), _PREG(0), __vcop_alws());
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeH(), __vcop_npt(), __vcop_alws(), _VREG(94), _PREG(6), _AGEN(2), _PREG(0));
   __vcop_vloop_end(12u);

   /* VLOOP 13 Start */

   /* VLOOP Local Vector Registers */
   #pragma VCC_VREG("VSum1", 95);
   #pragma VCC_VREG("VSum2", 96);
   #pragma VCC_VREG("Vin_x_1", 97);
   #pragma VCC_VREG("Vin_x_2", 98);
   #pragma VCC_VREG("Vin_y_1", 99);
   #pragma VCC_VREG("Vin_y_2", 100);
   #pragma VCC_VREG("Vout_1", 101);
   #pragma VCC_VREG("Vout_2", 102);
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("Addr_off", "A0");
   #pragma EVE_REG("Addr_1", "A1");
   #pragma EVE_REG("Addr_2", "A2");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I2", "I4");
   

   __vcop_vloop(__vcop_compute(), 14u, 7u, 13u);
   __vcop_vagen(_AGEN(1), _PREG(10), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(2), _PREG(11), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeH(), __vcop_dintrlv(), _PREG(12), _AGEN(1), _VPAIR(97,98), __vcop_alws());
   __vcop_vload(__vcop_sizeH(), __vcop_dintrlv(), _PREG(14), _AGEN(1), _VPAIR(99,100), __vcop_alws());
   __vcop_vintrlv(_VREG(97), _VREG(98));
   __vcop_vintrlv(_VREG(99), _VREG(100));
   __vcop_vbitpk(_VREG(97), _VREG(99), _VREG(101));
   __vcop_vbitpk(_VREG(98), _VREG(100), _VREG(102));
   __vcop_vnot(_VREG(101), _VREG(95));
   __vcop_vnot(_VREG(102), _VREG(96));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeBU(), __vcop_1pt(), __vcop_alws(), _VREG(95), _PREG(6), _AGEN(2), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeBU(), __vcop_1pt(), __vcop_alws(), _VREG(96), _PREG(8), _AGEN(2), _PREG(0));
   __vcop_vloop_end(13u);

}

void vcop_compute_rBrief(
   __vptr_int8 moments_col_mask,
   __vptr_int16 moments_col_sum,
   __vptr_int8 moments_row_mask,
   __vptr_int16 moments_row_sum,
   __vptr_int16 moments_m10,
   __vptr_int16 moments_m01,
   __vptr_uint16 arctan_xthr,
   __vptr_uint8 arctan_pack_decision,
   __vptr_int16 cos_array_ptr,
   __vptr_int16 sin_array_ptr,
   __vptr_uint16 offset_ptr,
   __vptr_int16 cos_ptr,
   __vptr_int16 sin_ptr,
   __vptr_uint8 input_image_ptr,
   __vptr_int16 col_sum_ptr,
   __vptr_int16 row_col_sum_ct_ptr,
   __vptr_int8 in_src_dst_x_ptr,
   __vptr_int8 in_src_dst_y_ptr,
   __vptr_int8 rot_src_dst_ptr_x,
   __vptr_int8 rot_src_dst_ptr_y,
   __vptr_uint16 rot_src_lin_ptr,
   __vptr_uint16 rot_dst_lin_ptr,
   __vptr_int16 tlu_src_ptr,
   __vptr_int16 tlu_dst_ptr,
   __vptr_uint8 true_descriptor_optr)
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_compute_rBrief_init(moments_col_mask, moments_col_sum, moments_row_mask, moments_row_sum, moments_m10, moments_m01, arctan_xthr, arctan_pack_decision, cos_array_ptr, sin_array_ptr, offset_ptr, cos_ptr, sin_ptr, input_image_ptr, col_sum_ptr, row_col_sum_ct_ptr, in_src_dst_x_ptr, in_src_dst_y_ptr, rot_src_dst_ptr_x, rot_src_dst_ptr_y, rot_src_lin_ptr, rot_dst_lin_ptr, tlu_src_ptr, tlu_dst_ptr, true_descriptor_optr, __pblock_vcop_compute_rBrief);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_compute_rBrief_vloops(__pblock_vcop_compute_rBrief);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

void vcop_compute_rBrief_custom(
   __vptr_int8 moments_col_mask,
   __vptr_int16 moments_col_sum,
   __vptr_int8 moments_row_mask,
   __vptr_int16 moments_row_sum,
   __vptr_int16 moments_m10,
   __vptr_int16 moments_m01,
   __vptr_uint16 arctan_xthr,
   __vptr_uint8 arctan_pack_decision,
   __vptr_int16 cos_array_ptr,
   __vptr_int16 sin_array_ptr,
   __vptr_uint16 offset_ptr,
   __vptr_int16 cos_ptr,
   __vptr_int16 sin_ptr,
   __vptr_uint8 input_image_ptr,
   __vptr_int16 col_sum_ptr,
   __vptr_int16 row_col_sum_ct_ptr,
   __vptr_int8 in_src_dst_x_ptr,
   __vptr_int8 in_src_dst_y_ptr,
   __vptr_int8 rot_src_dst_ptr_x,
   __vptr_int8 rot_src_dst_ptr_y,
   __vptr_uint16 rot_src_lin_ptr,
   __vptr_uint16 rot_dst_lin_ptr,
   __vptr_int16 tlu_src_ptr,
   __vptr_int16 tlu_dst_ptr,
   __vptr_uint8 true_descriptor_optr,
   unsigned short pblock[])
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_compute_rBrief_init(moments_col_mask, moments_col_sum, moments_row_mask, moments_row_sum, moments_m10, moments_m01, arctan_xthr, arctan_pack_decision, cos_array_ptr, sin_array_ptr, offset_ptr, cos_ptr, sin_ptr, input_image_ptr, col_sum_ptr, row_col_sum_ct_ptr, in_src_dst_x_ptr, in_src_dst_y_ptr, rot_src_dst_ptr_x, rot_src_dst_ptr_y, rot_src_lin_ptr, rot_dst_lin_ptr, tlu_src_ptr, tlu_dst_ptr, true_descriptor_optr, pblock);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_compute_rBrief_vloops(pblock);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

