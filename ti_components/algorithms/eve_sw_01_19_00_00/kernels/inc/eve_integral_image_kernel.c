#include <vcop\vcop.h>

typedef unsigned char uchar;

#pragma DATA_SECTION(__pblock_eve_integral_image_reset_accv, ".vcop_parameter_block")
#pragma DATA_ALIGN(__pblock_eve_integral_image_reset_accv, __ALIGNOF__(int));
unsigned short __pblock_eve_integral_image_reset_accv[10];

unsigned int eve_integral_image_reset_accv_param_count(void)
{
   return 10u;
}

unsigned int eve_integral_image_reset_accv_ctrl_count(void)
{
   return 0u;
}

unsigned int eve_integral_image_reset_accv_init(
   __vptr_uint32 acc_v_ptr,
   unsigned int blk_h,
   unsigned short pblock[])
{
   int __offset = 0;
   /* Loop 1 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), (blk_h)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(6), 4);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), 0);
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)acc_v_ptr);
   __offset += 10;

   return 10u;
}

void eve_integral_image_reset_accv_vloops(
   unsigned short pblock[])
{
   /* Kernel-wide Vector Registers */

   __vcop_param(&pblock[0]);

   /* VLOOP 1 Start */

   /* VLOOP Local Vector Registers */
   #pragma VCC_VREG("vZero", 16);
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("Addr0", "A0");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("i", "I4");
   

   __vcop_vloop(__vcop_compute(), 4u, 5u, 1u);
   __vcop_vinit(__vcop_sizeW(), __vcop_alws(), _PREG(8), _VREG(16));
   __vcop_vagen(_AGEN(0), _PREG(6), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeWU(), __vcop_1pt(), __vcop_alws(), _VREG(16), _PREG(10), _AGEN(0), _PREG(0));
   __vcop_vloop_end(1u);

}

void eve_integral_image_reset_accv(
   __vptr_uint32 acc_v_ptr,
   unsigned int blk_h)
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   eve_integral_image_reset_accv_init(acc_v_ptr, blk_h, __pblock_eve_integral_image_reset_accv);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   eve_integral_image_reset_accv_vloops(__pblock_eve_integral_image_reset_accv);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

void eve_integral_image_reset_accv_custom(
   __vptr_uint32 acc_v_ptr,
   unsigned int blk_h,
   unsigned short pblock[])
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   eve_integral_image_reset_accv_init(acc_v_ptr, blk_h, pblock);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   eve_integral_image_reset_accv_vloops(pblock);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

#pragma DATA_SECTION(__pblock_eve_integral_image_reset_acch, ".vcop_parameter_block")
#pragma DATA_ALIGN(__pblock_eve_integral_image_reset_acch, __ALIGNOF__(int));
unsigned short __pblock_eve_integral_image_reset_acch[10];

unsigned int eve_integral_image_reset_acch_param_count(void)
{
   return 10u;
}

unsigned int eve_integral_image_reset_acch_ctrl_count(void)
{
   return 0u;
}

unsigned int eve_integral_image_reset_acch_init(
   __vptr_uint32 acc_h_ptr,
   unsigned int blk_w,
   unsigned short pblock[])
{
   int __offset = 0;
   /* Loop 1 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), (blk_w/8)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(6), 32);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), 0);
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)acc_h_ptr);
   __offset += 10;

   return 10u;
}

void eve_integral_image_reset_acch_vloops(
   unsigned short pblock[])
{
   /* Kernel-wide Vector Registers */

   __vcop_param(&pblock[0]);

   /* VLOOP 1 Start */

   /* VLOOP Local Vector Registers */
   #pragma VCC_VREG("vZero", 16);
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("Addr0", "A0");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("i", "I4");
   

   __vcop_vloop(__vcop_compute(), 4u, 5u, 1u);
   __vcop_vinit(__vcop_sizeW(), __vcop_alws(), _PREG(8), _VREG(16));
   __vcop_vagen(_AGEN(0), _PREG(6), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeWU(), __vcop_npt(), __vcop_alws(), _VREG(16), _PREG(10), _AGEN(0), _PREG(0));
   __vcop_vloop_end(1u);

}

void eve_integral_image_reset_acch(
   __vptr_uint32 acc_h_ptr,
   unsigned int blk_w)
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   eve_integral_image_reset_acch_init(acc_h_ptr, blk_w, __pblock_eve_integral_image_reset_acch);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   eve_integral_image_reset_acch_vloops(__pblock_eve_integral_image_reset_acch);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

void eve_integral_image_reset_acch_custom(
   __vptr_uint32 acc_h_ptr,
   unsigned int blk_w,
   unsigned short pblock[])
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   eve_integral_image_reset_acch_init(acc_h_ptr, blk_w, pblock);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   eve_integral_image_reset_acch_vloops(pblock);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

#pragma DATA_SECTION(__pblock_eve_integral_image_u8_int_int, ".vcop_parameter_block")
#pragma DATA_ALIGN(__pblock_eve_integral_image_u8_int_int, __ALIGNOF__(int));
unsigned short __pblock_eve_integral_image_u8_int_int[64];

unsigned int eve_integral_image_u8_int_int_param_count(void)
{
   return 64u;
}

unsigned int eve_integral_image_u8_int_int_ctrl_count(void)
{
   return 0u;
}

unsigned int eve_integral_image_u8_int_int_init(
   unsigned int blk_w,
   unsigned int blk_h,
   unsigned int in_width,
   __vptr_uint32 acc_h_ptr,
   __vptr_uint32 acc_v_ptr,
   __vptr_uint8 in_ptr,
   __vptr_uint32 B0_ptr,
   __vptr_uint32 B1_ptr,
   __vptr_uint32 C0_ptr,
   __vptr_uint32 C1_ptr,
   __vptr_uint32 out_ptr,
   __vptr_uint32 out_acc_h_ptr,
   unsigned short pblock[])
{
   int __offset = 0;
   /* Loop 1 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), (blk_w/(2 * 8))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), (blk_h/8)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), (8)-1u);
   __vcop_pblock_init32(pblock, __offset+_PREG(6), (uchar *)in_ptr);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)B0_ptr);
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)B1_ptr);
   __vcop_pblock_init32(pblock, __offset+_PREG(12), (uchar *)out_acc_h_ptr);
   __vcop_pblock_init32(pblock, __offset+_PREG(14), (uchar *)out_acc_h_ptr+32);
   __vcop_pblock_init16(pblock, __offset+_PREG(16), 64);
   __vcop_pblock_init16(pblock, __offset+_PREG(17), (in_width*sizeof(*in_ptr)));
   __vcop_pblock_init16(pblock, __offset+_PREG(18), (in_width*8*sizeof(*in_ptr)) -(in_width*sizeof(*in_ptr))*((8)-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(19), ((8*sizeof(*in_ptr))*2) -(in_width*8*sizeof(*in_ptr))*((blk_h/8)-1u) -(in_width*sizeof(*in_ptr))*((8)-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(20), 4);
   __vcop_pblock_init16(pblock, __offset+_PREG(21), 260);
   __vcop_pblock_init16(pblock, __offset+_PREG(22), (8*(8+1)*(blk_h/8)*sizeof(*B0_ptr)) -((8+1)*8*sizeof(*B0_ptr))*((blk_h/8)-1u) -(sizeof(*B0_ptr))*((8)-1u));
   __vcop_pblock_init32(pblock, __offset+_PREG(24), (uchar *)acc_h_ptr);
   __vcop_pblock_init32(pblock, __offset+_PREG(26), (uchar *)acc_h_ptr+32);
   __offset += 26;

   /* Loop 2 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), (blk_w/( 2 * 8))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), (blk_h/8)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), (8)-1u);
   __vcop_pblock_init32(pblock, __offset+_PREG(6), (uchar *)B1_ptr);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)C0_ptr);
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)C1_ptr);
   __vcop_pblock_init16(pblock, __offset+_PREG(12), 32);
   __vcop_pblock_init16(pblock, __offset+_PREG(13),  -(8*sizeof(*B0_ptr))*((blk_h/8)-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(14), 36);
   __vcop_pblock_init16(pblock, __offset+_PREG(15), (8*(8+1)*(blk_h/8)*sizeof(*B0_ptr)) -((8+1)*8*sizeof(*B0_ptr))*((blk_h/8)-1u) -((8+1)*sizeof(*B0_ptr))*((8)-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(16), 4);
   __vcop_pblock_init16(pblock, __offset+_PREG(17), 260);
   __vcop_pblock_init16(pblock, __offset+_PREG(18), (8*(8+1)*(blk_h/8)*sizeof(*out_ptr)) -((8+1)*8*sizeof(*out_ptr))*((blk_h/8)-1u) -(sizeof(*out_ptr))*((8)-1u));
   __vcop_pblock_init32(pblock, __offset+_PREG(20), (uchar *)acc_v_ptr);
   __vcop_pblock_init32(pblock, __offset+_PREG(22), (uchar *)B0_ptr);
   __offset += 22;

   /* Loop 3 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), (blk_w/(2 * 8))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), (blk_h)-1u);
   __vcop_pblock_init32(pblock, __offset+_PREG(6), (uchar *)out_ptr);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)out_ptr+8*4);
   __vcop_pblock_init16(pblock, __offset+_PREG(10), 36);
   __vcop_pblock_init16(pblock, __offset+_PREG(11), (blk_h*(8+1)*sizeof(*out_ptr)) -((8+1)*sizeof(*out_ptr))*((blk_h)-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(12), (in_width*sizeof(*out_ptr)));
   __vcop_pblock_init16(pblock, __offset+_PREG(13), (2*(8*sizeof(*out_ptr))) -(in_width*sizeof(*out_ptr))*((blk_h)-1u));
   __vcop_pblock_init32(pblock, __offset+_PREG(14), (uchar *)C0_ptr);
   __vcop_pblock_init32(pblock, __offset+_PREG(16), (uchar *)C1_ptr);
   __offset += 16;

   return 64u;
}

void eve_integral_image_u8_int_int_vloops(
   unsigned short pblock[])
{
   /* Kernel-wide Vector Registers */
   #pragma VCC_VREG("V_C0", 16);
   #pragma VCC_VREG("Vacc_h_even", 17);
   #pragma VCC_VREG("Vacc_h_odd", 18);
   #pragma VCC_VREG("Vacc_v", 19);
   #pragma VCC_VREG("Vin_B0", 20);
   #pragma VCC_VREG("Vin_B1", 21);
   #pragma VCC_VREG("Vin_a", 22);
   #pragma VCC_VREG("Vin_b", 23);
   #pragma VCC_VREG("Vin_even", 24);
   #pragma VCC_VREG("Vin_odd", 25);

   __vcop_param(&pblock[0]);

   /* VLOOP 1 Start */

   /* VLOOP Local Vector Registers */
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("accAddr", "A0");
   #pragma EVE_REG("dataAddr", "A1");
   #pragma EVE_REG("outAddr", "A2");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I1", "I2");
   #pragma EVE_REG("I2", "I3");
   #pragma EVE_REG("I3", "I4");
   

   __vcop_vloop(__vcop_compute(), 13u, 13u, 1u);
   __vcop_vagen(_AGEN(0), _PREG(0), _PREG(0), _PREG(16), _PREG(0));
   __vcop_vagen(_AGEN(1), _PREG(17), _PREG(18), _PREG(19), _PREG(0));
   __vcop_vagen(_AGEN(2), _PREG(20), _PREG(21), _PREG(22), _PREG(0));
   __vcop_vload(__vcop_sizeWU(), __vcop_npt(), _PREG(24), _AGEN(0), _VREG(17), __vcop_i34_zero());
   __vcop_vload(__vcop_sizeWU(), __vcop_npt(), _PREG(26), _AGEN(0), _VREG(18), __vcop_i34_zero());
   __vcop_vload(__vcop_sizeBU(), __vcop_dintrlv(), _PREG(6), _AGEN(1), _VPAIR(24,25), __vcop_alws());
   __vcop_vadd(_VREG(17), _VREG(24), _VREG(17));
   __vcop_vadd(_VREG(18), _VREG(25), _VREG(18));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeWU(), __vcop_offst_np1(), __vcop_alws(), _VREG(17), _PREG(8), _AGEN(2), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeWU(), __vcop_offst_np1(), __vcop_alws(), _VREG(18), _PREG(10), _AGEN(2), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeWU(), __vcop_npt(), __vcop_last_i34(), _VREG(17), _PREG(12), _AGEN(0), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeWU(), __vcop_npt(), __vcop_last_i34(), _VREG(18), _PREG(14), _AGEN(0), _PREG(0));
   __vcop_vloop_end(1u);

   /* VLOOP 2 Start */

   /* VLOOP Local Vector Registers */
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("accAddr", "A0");
   #pragma EVE_REG("dataAddr", "A1");
   #pragma EVE_REG("outAddr", "A2");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I1", "I2");
   #pragma EVE_REG("I2", "I3");
   #pragma EVE_REG("I3", "I4");
   

   __vcop_vloop(__vcop_compute(), 12u, 11u, 2u);
   __vcop_vagen(_AGEN(0), _PREG(0), _PREG(12), _PREG(13), _PREG(0));
   __vcop_vagen(_AGEN(1), _PREG(14), _PREG(14), _PREG(15), _PREG(0));
   __vcop_vagen(_AGEN(2), _PREG(16), _PREG(17), _PREG(18), _PREG(0));
   __vcop_vload(__vcop_sizeWU(), __vcop_npt(), _PREG(20), _AGEN(0), _VREG(19), __vcop_i4_zero());
   __vcop_vload(__vcop_sizeWU(), __vcop_npt(), _PREG(22), _AGEN(1), _VREG(20), __vcop_alws());
   __vcop_vload(__vcop_sizeWU(), __vcop_npt(), _PREG(6), _AGEN(1), _VREG(21), __vcop_alws());
   __vcop_vadd(_VREG(19), _VREG(20), _VREG(16));
   __vcop_vadd3(_VREG(20), _VREG(21), _VREG(19));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeWU(), __vcop_offst_np1(), __vcop_alws(), _VREG(16), _PREG(8), _AGEN(2), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeWU(), __vcop_offst_np1(), __vcop_alws(), _VREG(19), _PREG(10), _AGEN(2), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeWU(), __vcop_npt(), __vcop_last_i4(), _VREG(19), _PREG(20), _AGEN(0), _PREG(0));
   __vcop_vloop_end(2u);

   /* VLOOP 3 Start */

   /* VLOOP Local Vector Registers */
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("dataAddr", "A0");
   #pragma EVE_REG("outAddr", "A1");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I1", "I3");
   #pragma EVE_REG("I2", "I4");
   

   __vcop_vloop(__vcop_compute(), 8u, 8u, 3u);
   __vcop_vagen(_AGEN(0), _PREG(10), _PREG(11), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(1), _PREG(12), _PREG(13), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeWU(), __vcop_npt(), _PREG(14), _AGEN(0), _VREG(22), __vcop_alws());
   __vcop_vload(__vcop_sizeWU(), __vcop_npt(), _PREG(16), _AGEN(0), _VREG(23), __vcop_alws());
   __vcop_vintrlv(_VREG(22), _VREG(23));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeWU(), __vcop_npt(), __vcop_alws(), _VREG(22), _PREG(6), _AGEN(1), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeWU(), __vcop_npt(), __vcop_alws(), _VREG(23), _PREG(8), _AGEN(1), _PREG(0));
   __vcop_vloop_end(3u);

}

void eve_integral_image_u8_int_int(
   unsigned int blk_w,
   unsigned int blk_h,
   unsigned int in_width,
   __vptr_uint32 acc_h_ptr,
   __vptr_uint32 acc_v_ptr,
   __vptr_uint8 in_ptr,
   __vptr_uint32 B0_ptr,
   __vptr_uint32 B1_ptr,
   __vptr_uint32 C0_ptr,
   __vptr_uint32 C1_ptr,
   __vptr_uint32 out_ptr,
   __vptr_uint32 out_acc_h_ptr)
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   eve_integral_image_u8_int_int_init(blk_w, blk_h, in_width, acc_h_ptr, acc_v_ptr, in_ptr, B0_ptr, B1_ptr, C0_ptr, C1_ptr, out_ptr, out_acc_h_ptr, __pblock_eve_integral_image_u8_int_int);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   eve_integral_image_u8_int_int_vloops(__pblock_eve_integral_image_u8_int_int);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

void eve_integral_image_u8_int_int_custom(
   unsigned int blk_w,
   unsigned int blk_h,
   unsigned int in_width,
   __vptr_uint32 acc_h_ptr,
   __vptr_uint32 acc_v_ptr,
   __vptr_uint8 in_ptr,
   __vptr_uint32 B0_ptr,
   __vptr_uint32 B1_ptr,
   __vptr_uint32 C0_ptr,
   __vptr_uint32 C1_ptr,
   __vptr_uint32 out_ptr,
   __vptr_uint32 out_acc_h_ptr,
   unsigned short pblock[])
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   eve_integral_image_u8_int_int_init(blk_w, blk_h, in_width, acc_h_ptr, acc_v_ptr, in_ptr, B0_ptr, B1_ptr, C0_ptr, C1_ptr, out_ptr, out_acc_h_ptr, pblock);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   eve_integral_image_u8_int_int_vloops(pblock);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

#pragma DATA_SECTION(__pblock_eve_integral_image_u16_int_int, ".vcop_parameter_block")
#pragma DATA_ALIGN(__pblock_eve_integral_image_u16_int_int, __ALIGNOF__(int));
unsigned short __pblock_eve_integral_image_u16_int_int[60];

unsigned int eve_integral_image_u16_int_int_param_count(void)
{
   return 60u;
}

unsigned int eve_integral_image_u16_int_int_ctrl_count(void)
{
   return 0u;
}

unsigned int eve_integral_image_u16_int_int_init(
   unsigned int blk_w,
   unsigned int blk_h,
   unsigned int in_width,
   __vptr_uint32 acc_h_ptr,
   __vptr_uint32 acc_v_ptr,
   __vptr_uint16 in_ptr,
   __vptr_uint32 B0_ptr,
   __vptr_uint32 B1_ptr,
   __vptr_uint32 C0_ptr,
   __vptr_uint32 C1_ptr,
   __vptr_uint32 out_ptr,
   unsigned short pblock[])
{
   int __offset = 0;
   /* Loop 1 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), (blk_w/(2 * 8))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), (blk_h/8)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), (8)-1u);
   __vcop_pblock_init32(pblock, __offset+_PREG(6), (uchar *)in_ptr);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)B0_ptr);
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)B1_ptr);
   __vcop_pblock_init16(pblock, __offset+_PREG(12), 64);
   __vcop_pblock_init16(pblock, __offset+_PREG(13), (in_width*sizeof(*in_ptr)));
   __vcop_pblock_init16(pblock, __offset+_PREG(14), (in_width*8*sizeof(*in_ptr)) -(in_width*sizeof(*in_ptr))*((8)-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(15), ((8*sizeof(*in_ptr))*2) -(in_width*8*sizeof(*in_ptr))*((blk_h/8)-1u) -(in_width*sizeof(*in_ptr))*((8)-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(16), 4);
   __vcop_pblock_init16(pblock, __offset+_PREG(17), 260);
   __vcop_pblock_init16(pblock, __offset+_PREG(18), (8*(8+1)*(blk_h/8)*sizeof(*B0_ptr)) -((8+1)*8*sizeof(*B0_ptr))*((blk_h/8)-1u) -(sizeof(*B0_ptr))*((8)-1u));
   __vcop_pblock_init32(pblock, __offset+_PREG(20), (uchar *)acc_h_ptr);
   __vcop_pblock_init32(pblock, __offset+_PREG(22), (uchar *)acc_h_ptr+32);
   __offset += 22;

   /* Loop 2 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), (blk_w/( 2 * 8))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), (blk_h/8)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), (8)-1u);
   __vcop_pblock_init32(pblock, __offset+_PREG(6), (uchar *)B1_ptr);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)C0_ptr);
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)C1_ptr);
   __vcop_pblock_init16(pblock, __offset+_PREG(12), 32);
   __vcop_pblock_init16(pblock, __offset+_PREG(13),  -(8*sizeof(*B0_ptr))*((blk_h/8)-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(14), 36);
   __vcop_pblock_init16(pblock, __offset+_PREG(15), (8*(8+1)*(blk_h/8)*sizeof(*B0_ptr)) -((8+1)*8*sizeof(*B0_ptr))*((blk_h/8)-1u) -((8+1)*sizeof(*B0_ptr))*((8)-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(16), 4);
   __vcop_pblock_init16(pblock, __offset+_PREG(17), 260);
   __vcop_pblock_init16(pblock, __offset+_PREG(18), (8*(8+1)*(blk_h/8)*sizeof(*out_ptr)) -((8+1)*8*sizeof(*out_ptr))*((blk_h/8)-1u) -(sizeof(*out_ptr))*((8)-1u));
   __vcop_pblock_init32(pblock, __offset+_PREG(20), (uchar *)acc_v_ptr);
   __vcop_pblock_init32(pblock, __offset+_PREG(22), (uchar *)B0_ptr);
   __offset += 22;

   /* Loop 3 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), (blk_w/(2 * 8))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), (blk_h)-1u);
   __vcop_pblock_init32(pblock, __offset+_PREG(6), (uchar *)out_ptr);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)out_ptr+8*4);
   __vcop_pblock_init16(pblock, __offset+_PREG(10), 36);
   __vcop_pblock_init16(pblock, __offset+_PREG(11), (blk_h*(8+1)*sizeof(*out_ptr)) -((8+1)*sizeof(*out_ptr))*((blk_h)-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(12), (in_width*sizeof(*out_ptr)));
   __vcop_pblock_init16(pblock, __offset+_PREG(13), (2*(8*sizeof(*out_ptr))) -(in_width*sizeof(*out_ptr))*((blk_h)-1u));
   __vcop_pblock_init32(pblock, __offset+_PREG(14), (uchar *)C0_ptr);
   __vcop_pblock_init32(pblock, __offset+_PREG(16), (uchar *)C1_ptr);
   __offset += 16;

   return 60u;
}

void eve_integral_image_u16_int_int_vloops(
   unsigned short pblock[])
{
   /* Kernel-wide Vector Registers */
   #pragma VCC_VREG("V_C0", 16);
   #pragma VCC_VREG("Vacc_h_even", 17);
   #pragma VCC_VREG("Vacc_h_odd", 18);
   #pragma VCC_VREG("Vacc_v", 19);
   #pragma VCC_VREG("Vin_B0", 20);
   #pragma VCC_VREG("Vin_B1", 21);
   #pragma VCC_VREG("Vin_a", 22);
   #pragma VCC_VREG("Vin_b", 23);
   #pragma VCC_VREG("Vin_even", 24);
   #pragma VCC_VREG("Vin_odd", 25);

   __vcop_param(&pblock[0]);

   /* VLOOP 1 Start */

   /* VLOOP Local Vector Registers */
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("accAddr", "A0");
   #pragma EVE_REG("dataAddr", "A1");
   #pragma EVE_REG("outAddr", "A2");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I1", "I2");
   #pragma EVE_REG("I2", "I3");
   #pragma EVE_REG("I3", "I4");
   

   __vcop_vloop(__vcop_compute(), 13u, 11u, 1u);
   __vcop_vagen(_AGEN(0), _PREG(0), _PREG(0), _PREG(12), _PREG(0));
   __vcop_vagen(_AGEN(1), _PREG(13), _PREG(14), _PREG(15), _PREG(0));
   __vcop_vagen(_AGEN(2), _PREG(16), _PREG(17), _PREG(18), _PREG(0));
   __vcop_vload(__vcop_sizeWU(), __vcop_npt(), _PREG(20), _AGEN(0), _VREG(17), __vcop_i34_zero());
   __vcop_vload(__vcop_sizeWU(), __vcop_npt(), _PREG(22), _AGEN(0), _VREG(18), __vcop_i34_zero());
   __vcop_vload(__vcop_sizeHU(), __vcop_dintrlv(), _PREG(6), _AGEN(1), _VPAIR(24,25), __vcop_alws());
   __vcop_vadd(_VREG(17), _VREG(24), _VREG(17));
   __vcop_vadd(_VREG(18), _VREG(25), _VREG(18));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeWU(), __vcop_offst_np1(), __vcop_alws(), _VREG(17), _PREG(8), _AGEN(2), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeWU(), __vcop_offst_np1(), __vcop_alws(), _VREG(18), _PREG(10), _AGEN(2), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeWU(), __vcop_npt(), __vcop_last_i34(), _VREG(17), _PREG(20), _AGEN(0), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeWU(), __vcop_npt(), __vcop_last_i34(), _VREG(18), _PREG(22), _AGEN(0), _PREG(0));
   __vcop_vloop_end(1u);

   /* VLOOP 2 Start */

   /* VLOOP Local Vector Registers */
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("accAddr", "A0");
   #pragma EVE_REG("dataAddr", "A1");
   #pragma EVE_REG("outAddr", "A2");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I1", "I2");
   #pragma EVE_REG("I2", "I3");
   #pragma EVE_REG("I3", "I4");
   

   __vcop_vloop(__vcop_compute(), 12u, 11u, 2u);
   __vcop_vagen(_AGEN(0), _PREG(0), _PREG(12), _PREG(13), _PREG(0));
   __vcop_vagen(_AGEN(1), _PREG(14), _PREG(14), _PREG(15), _PREG(0));
   __vcop_vagen(_AGEN(2), _PREG(16), _PREG(17), _PREG(18), _PREG(0));
   __vcop_vload(__vcop_sizeWU(), __vcop_npt(), _PREG(20), _AGEN(0), _VREG(19), __vcop_i4_zero());
   __vcop_vload(__vcop_sizeWU(), __vcop_npt(), _PREG(22), _AGEN(1), _VREG(20), __vcop_alws());
   __vcop_vload(__vcop_sizeWU(), __vcop_npt(), _PREG(6), _AGEN(1), _VREG(21), __vcop_alws());
   __vcop_vadd(_VREG(19), _VREG(20), _VREG(16));
   __vcop_vadd3(_VREG(20), _VREG(21), _VREG(19));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeWU(), __vcop_offst_np1(), __vcop_alws(), _VREG(16), _PREG(8), _AGEN(2), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeWU(), __vcop_offst_np1(), __vcop_alws(), _VREG(19), _PREG(10), _AGEN(2), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeWU(), __vcop_npt(), __vcop_last_i4(), _VREG(19), _PREG(20), _AGEN(0), _PREG(0));
   __vcop_vloop_end(2u);

   /* VLOOP 3 Start */

   /* VLOOP Local Vector Registers */
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("dataAddr", "A0");
   #pragma EVE_REG("outAddr", "A1");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I1", "I3");
   #pragma EVE_REG("I2", "I4");
   

   __vcop_vloop(__vcop_compute(), 8u, 8u, 3u);
   __vcop_vagen(_AGEN(0), _PREG(10), _PREG(11), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(1), _PREG(12), _PREG(13), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeWU(), __vcop_npt(), _PREG(14), _AGEN(0), _VREG(22), __vcop_alws());
   __vcop_vload(__vcop_sizeWU(), __vcop_npt(), _PREG(16), _AGEN(0), _VREG(23), __vcop_alws());
   __vcop_vintrlv(_VREG(22), _VREG(23));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeWU(), __vcop_npt(), __vcop_alws(), _VREG(22), _PREG(6), _AGEN(1), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeWU(), __vcop_npt(), __vcop_alws(), _VREG(23), _PREG(8), _AGEN(1), _PREG(0));
   __vcop_vloop_end(3u);

}

void eve_integral_image_u16_int_int(
   unsigned int blk_w,
   unsigned int blk_h,
   unsigned int in_width,
   __vptr_uint32 acc_h_ptr,
   __vptr_uint32 acc_v_ptr,
   __vptr_uint16 in_ptr,
   __vptr_uint32 B0_ptr,
   __vptr_uint32 B1_ptr,
   __vptr_uint32 C0_ptr,
   __vptr_uint32 C1_ptr,
   __vptr_uint32 out_ptr)
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   eve_integral_image_u16_int_int_init(blk_w, blk_h, in_width, acc_h_ptr, acc_v_ptr, in_ptr, B0_ptr, B1_ptr, C0_ptr, C1_ptr, out_ptr, __pblock_eve_integral_image_u16_int_int);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   eve_integral_image_u16_int_int_vloops(__pblock_eve_integral_image_u16_int_int);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

void eve_integral_image_u16_int_int_custom(
   unsigned int blk_w,
   unsigned int blk_h,
   unsigned int in_width,
   __vptr_uint32 acc_h_ptr,
   __vptr_uint32 acc_v_ptr,
   __vptr_uint16 in_ptr,
   __vptr_uint32 B0_ptr,
   __vptr_uint32 B1_ptr,
   __vptr_uint32 C0_ptr,
   __vptr_uint32 C1_ptr,
   __vptr_uint32 out_ptr,
   unsigned short pblock[])
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   eve_integral_image_u16_int_int_init(blk_w, blk_h, in_width, acc_h_ptr, acc_v_ptr, in_ptr, B0_ptr, B1_ptr, C0_ptr, C1_ptr, out_ptr, pblock);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   eve_integral_image_u16_int_int_vloops(pblock);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

