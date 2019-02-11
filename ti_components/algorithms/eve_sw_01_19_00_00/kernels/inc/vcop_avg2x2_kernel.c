#include <vcop\vcop.h>

typedef unsigned char uchar;

#pragma DATA_SECTION(__pblock_vcop_avg2x2_uchar, ".vcop_parameter_block")
#pragma DATA_ALIGN(__pblock_vcop_avg2x2_uchar, __ALIGNOF__(int));
unsigned short __pblock_vcop_avg2x2_uchar[18];

unsigned int vcop_avg2x2_uchar_param_count(void)
{
   return 18u;
}

unsigned int vcop_avg2x2_uchar_ctrl_count(void)
{
   return 0u;
}

unsigned int vcop_avg2x2_uchar_init(
   __vptr_uint8 in,
   __vptr_int16 result,
   int w_input,
   int w_out,
   int w_blk,
   int h_blk,
   int shift_val,
   int type_input,
   int type_output,
   unsigned short pblock[])
{
   int __offset = 0;
   /* Loop 1 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), (w_out/(2 * (8u)))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), (h_blk)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(6), __vcop_store_round_sat(SM_NONE,0,RM_TRUNC,shift_val));
   __vcop_pblock_init16(pblock, __offset+_PREG(7), (w_input*sizeof(*in)));
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)in+2*sizeof(*in));
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)result);
   __vcop_pblock_init16(pblock, __offset+_PREG(12), (2*8u*sizeof(*in)) -(w_input*sizeof(*in))*((h_blk)-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(13), (w_out*sizeof(*result)));
   __vcop_pblock_init16(pblock, __offset+_PREG(14), (2*8u*sizeof(*result)) -(w_out*sizeof(*result))*((h_blk)-1u));
   __vcop_pblock_init32(pblock, __offset+_PREG(16), 0);
   __vcop_pblock_init32(pblock, __offset+_PREG(18), (uchar *)in);
   __offset += 18;

   return 18u;
}

void vcop_avg2x2_uchar_vloops(
   unsigned short pblock[])
{
   /* Kernel-wide Vector Registers */
   #pragma VCC_VREG("Vin0", 16);
   #pragma VCC_VREG("Vin1", 17);
   #pragma VCC_VREG("Vin2", 18);
   #pragma VCC_VREG("Vin3", 19);
   #pragma VCC_VREG("Vout0", 20);
   #pragma VCC_VREG("Vout1", 21);
   #pragma VCC_VREG("Vprev0", 22);
   #pragma VCC_VREG("Vprev1", 23);

   __vcop_param(&pblock[0]);

   /* VLOOP 1 Start */

   /* VLOOP Local Vector Registers */
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("inAddr", "A0");
   #pragma EVE_REG("outAddr", "A1");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I1", "I3");
   #pragma EVE_REG("I2", "I4");
   

   __vcop_vloop(__vcop_compute(), 14u, 9u, 1u);
   __vcop_vinit(__vcop_sizeW(), __vcop_i4_zero(), _PREG(16), _VREG(22));
   __vcop_vinit(__vcop_sizeW(), __vcop_i4_zero(), _PREG(16), _VREG(23));
   __vcop_vagen(_AGEN(0), _PREG(7), _PREG(12), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(1), _PREG(13), _PREG(14), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeBU(), __vcop_dintrlv(), _PREG(18), _AGEN(0), _VPAIR(16,17), __vcop_alws());
   __vcop_vload(__vcop_sizeBU(), __vcop_dintrlv(), _PREG(8), _AGEN(0), _VPAIR(18,19), __vcop_alws());
   __vcop_vadd(_VREG(16), _VREG(17), _VREG(20));
   __vcop_vadd(_VREG(17), _VREG(18), _VREG(21));
   __vcop_vadd(_VREG(20), _VREG(22), _VREG(20));
   __vcop_vadd(_VREG(21), _VREG(23), _VREG(21));
   __vcop_vadd(_VREG(16), _VREG(17), _VREG(22));
   __vcop_vadd(_VREG(17), _VREG(18), _VREG(23));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeH(), __vcop_intrlv(), __vcop_alws(), _VPAIR(20,21), _PREG(10), _AGEN(1), _PREG(6));
   __vcop_vloop_end(1u);

}

void vcop_avg2x2_uchar(
   __vptr_uint8 in,
   __vptr_int16 result,
   int w_input,
   int w_out,
   int w_blk,
   int h_blk,
   int shift_val,
   int type_input,
   int type_output)
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_avg2x2_uchar_init(in, result, w_input, w_out, w_blk, h_blk, shift_val, type_input, type_output, __pblock_vcop_avg2x2_uchar);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_avg2x2_uchar_vloops(__pblock_vcop_avg2x2_uchar);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

void vcop_avg2x2_uchar_custom(
   __vptr_uint8 in,
   __vptr_int16 result,
   int w_input,
   int w_out,
   int w_blk,
   int h_blk,
   int shift_val,
   int type_input,
   int type_output,
   unsigned short pblock[])
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_avg2x2_uchar_init(in, result, w_input, w_out, w_blk, h_blk, shift_val, type_input, type_output, pblock);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_avg2x2_uchar_vloops(pblock);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

#pragma DATA_SECTION(__pblock_vcop_avg2x2_char, ".vcop_parameter_block")
#pragma DATA_ALIGN(__pblock_vcop_avg2x2_char, __ALIGNOF__(int));
unsigned short __pblock_vcop_avg2x2_char[18];

unsigned int vcop_avg2x2_char_param_count(void)
{
   return 18u;
}

unsigned int vcop_avg2x2_char_ctrl_count(void)
{
   return 0u;
}

unsigned int vcop_avg2x2_char_init(
   __vptr_int8 in,
   __vptr_int16 result,
   int w_input,
   int w_out,
   int w_blk,
   int h_blk,
   int shift_val,
   int type_input,
   int type_output,
   unsigned short pblock[])
{
   int __offset = 0;
   /* Loop 1 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), (w_out/(2 * (8u)))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), (h_blk)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(6), __vcop_store_round_sat(SM_NONE,0,RM_TRUNC,shift_val));
   __vcop_pblock_init16(pblock, __offset+_PREG(7), (w_input*sizeof(*in)));
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)in+2*sizeof(*in));
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)result);
   __vcop_pblock_init16(pblock, __offset+_PREG(12), (2*8u*sizeof(*in)) -(w_input*sizeof(*in))*((h_blk)-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(13), (w_out*sizeof(*result)));
   __vcop_pblock_init16(pblock, __offset+_PREG(14), (2*8u*sizeof(*result)) -(w_out*sizeof(*result))*((h_blk)-1u));
   __vcop_pblock_init32(pblock, __offset+_PREG(16), 0);
   __vcop_pblock_init32(pblock, __offset+_PREG(18), (uchar *)in);
   __offset += 18;

   return 18u;
}

void vcop_avg2x2_char_vloops(
   unsigned short pblock[])
{
   /* Kernel-wide Vector Registers */
   #pragma VCC_VREG("Vin0", 16);
   #pragma VCC_VREG("Vin1", 17);
   #pragma VCC_VREG("Vin2", 18);
   #pragma VCC_VREG("Vin3", 19);
   #pragma VCC_VREG("Vout0", 20);
   #pragma VCC_VREG("Vout1", 21);
   #pragma VCC_VREG("Vprev0", 22);
   #pragma VCC_VREG("Vprev1", 23);

   __vcop_param(&pblock[0]);

   /* VLOOP 1 Start */

   /* VLOOP Local Vector Registers */
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("inAddr", "A0");
   #pragma EVE_REG("outAddr", "A1");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I1", "I3");
   #pragma EVE_REG("I2", "I4");
   

   __vcop_vloop(__vcop_compute(), 14u, 9u, 1u);
   __vcop_vinit(__vcop_sizeW(), __vcop_i4_zero(), _PREG(16), _VREG(22));
   __vcop_vinit(__vcop_sizeW(), __vcop_i4_zero(), _PREG(16), _VREG(23));
   __vcop_vagen(_AGEN(0), _PREG(7), _PREG(12), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(1), _PREG(13), _PREG(14), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeB(), __vcop_dintrlv(), _PREG(18), _AGEN(0), _VPAIR(16,17), __vcop_alws());
   __vcop_vload(__vcop_sizeB(), __vcop_dintrlv(), _PREG(8), _AGEN(0), _VPAIR(18,19), __vcop_alws());
   __vcop_vadd(_VREG(16), _VREG(17), _VREG(20));
   __vcop_vadd(_VREG(17), _VREG(18), _VREG(21));
   __vcop_vadd(_VREG(20), _VREG(22), _VREG(20));
   __vcop_vadd(_VREG(21), _VREG(23), _VREG(21));
   __vcop_vadd(_VREG(16), _VREG(17), _VREG(22));
   __vcop_vadd(_VREG(17), _VREG(18), _VREG(23));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeH(), __vcop_intrlv(), __vcop_alws(), _VPAIR(20,21), _PREG(10), _AGEN(1), _PREG(6));
   __vcop_vloop_end(1u);

}

void vcop_avg2x2_char(
   __vptr_int8 in,
   __vptr_int16 result,
   int w_input,
   int w_out,
   int w_blk,
   int h_blk,
   int shift_val,
   int type_input,
   int type_output)
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_avg2x2_char_init(in, result, w_input, w_out, w_blk, h_blk, shift_val, type_input, type_output, __pblock_vcop_avg2x2_char);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_avg2x2_char_vloops(__pblock_vcop_avg2x2_char);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

void vcop_avg2x2_char_custom(
   __vptr_int8 in,
   __vptr_int16 result,
   int w_input,
   int w_out,
   int w_blk,
   int h_blk,
   int shift_val,
   int type_input,
   int type_output,
   unsigned short pblock[])
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_avg2x2_char_init(in, result, w_input, w_out, w_blk, h_blk, shift_val, type_input, type_output, pblock);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_avg2x2_char_vloops(pblock);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

#pragma DATA_SECTION(__pblock_vcop_avg2x2_ushort, ".vcop_parameter_block")
#pragma DATA_ALIGN(__pblock_vcop_avg2x2_ushort, __ALIGNOF__(int));
unsigned short __pblock_vcop_avg2x2_ushort[18];

unsigned int vcop_avg2x2_ushort_param_count(void)
{
   return 18u;
}

unsigned int vcop_avg2x2_ushort_ctrl_count(void)
{
   return 0u;
}

unsigned int vcop_avg2x2_ushort_init(
   __vptr_uint16 in,
   __vptr_int16 result,
   int w_input,
   int w_out,
   int w_blk,
   int h_blk,
   int shift_val,
   int type_input,
   int type_output,
   unsigned short pblock[])
{
   int __offset = 0;
   /* Loop 1 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), (w_out/(2 * (8u)))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), (h_blk)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(6), __vcop_store_round_sat(SM_NONE,0,RM_TRUNC,shift_val));
   __vcop_pblock_init16(pblock, __offset+_PREG(7), (w_input*sizeof(*in)));
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)in+2*sizeof(*in));
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)result);
   __vcop_pblock_init16(pblock, __offset+_PREG(12), (2*8u*sizeof(*in)) -(w_input*sizeof(*in))*((h_blk)-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(13), (w_out*sizeof(*result)));
   __vcop_pblock_init16(pblock, __offset+_PREG(14), (2*8u*sizeof(*result)) -(w_out*sizeof(*result))*((h_blk)-1u));
   __vcop_pblock_init32(pblock, __offset+_PREG(16), 0);
   __vcop_pblock_init32(pblock, __offset+_PREG(18), (uchar *)in);
   __offset += 18;

   return 18u;
}

void vcop_avg2x2_ushort_vloops(
   unsigned short pblock[])
{
   /* Kernel-wide Vector Registers */
   #pragma VCC_VREG("Vin0", 16);
   #pragma VCC_VREG("Vin1", 17);
   #pragma VCC_VREG("Vin2", 18);
   #pragma VCC_VREG("Vin3", 19);
   #pragma VCC_VREG("Vout0", 20);
   #pragma VCC_VREG("Vout1", 21);
   #pragma VCC_VREG("Vprev0", 22);
   #pragma VCC_VREG("Vprev1", 23);

   __vcop_param(&pblock[0]);

   /* VLOOP 1 Start */

   /* VLOOP Local Vector Registers */
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("inAddr", "A0");
   #pragma EVE_REG("outAddr", "A1");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I1", "I3");
   #pragma EVE_REG("I2", "I4");
   

   __vcop_vloop(__vcop_compute(), 14u, 9u, 1u);
   __vcop_vinit(__vcop_sizeW(), __vcop_i4_zero(), _PREG(16), _VREG(22));
   __vcop_vinit(__vcop_sizeW(), __vcop_i4_zero(), _PREG(16), _VREG(23));
   __vcop_vagen(_AGEN(0), _PREG(7), _PREG(12), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(1), _PREG(13), _PREG(14), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeHU(), __vcop_dintrlv(), _PREG(18), _AGEN(0), _VPAIR(16,17), __vcop_alws());
   __vcop_vload(__vcop_sizeHU(), __vcop_dintrlv(), _PREG(8), _AGEN(0), _VPAIR(18,19), __vcop_alws());
   __vcop_vadd(_VREG(16), _VREG(17), _VREG(20));
   __vcop_vadd(_VREG(17), _VREG(18), _VREG(21));
   __vcop_vadd(_VREG(20), _VREG(22), _VREG(20));
   __vcop_vadd(_VREG(21), _VREG(23), _VREG(21));
   __vcop_vadd(_VREG(16), _VREG(17), _VREG(22));
   __vcop_vadd(_VREG(17), _VREG(18), _VREG(23));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeH(), __vcop_intrlv(), __vcop_alws(), _VPAIR(20,21), _PREG(10), _AGEN(1), _PREG(6));
   __vcop_vloop_end(1u);

}

void vcop_avg2x2_ushort(
   __vptr_uint16 in,
   __vptr_int16 result,
   int w_input,
   int w_out,
   int w_blk,
   int h_blk,
   int shift_val,
   int type_input,
   int type_output)
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_avg2x2_ushort_init(in, result, w_input, w_out, w_blk, h_blk, shift_val, type_input, type_output, __pblock_vcop_avg2x2_ushort);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_avg2x2_ushort_vloops(__pblock_vcop_avg2x2_ushort);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

void vcop_avg2x2_ushort_custom(
   __vptr_uint16 in,
   __vptr_int16 result,
   int w_input,
   int w_out,
   int w_blk,
   int h_blk,
   int shift_val,
   int type_input,
   int type_output,
   unsigned short pblock[])
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_avg2x2_ushort_init(in, result, w_input, w_out, w_blk, h_blk, shift_val, type_input, type_output, pblock);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_avg2x2_ushort_vloops(pblock);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

#pragma DATA_SECTION(__pblock_vcop_avg2x2_short, ".vcop_parameter_block")
#pragma DATA_ALIGN(__pblock_vcop_avg2x2_short, __ALIGNOF__(int));
unsigned short __pblock_vcop_avg2x2_short[18];

unsigned int vcop_avg2x2_short_param_count(void)
{
   return 18u;
}

unsigned int vcop_avg2x2_short_ctrl_count(void)
{
   return 0u;
}

unsigned int vcop_avg2x2_short_init(
   __vptr_int16 in,
   __vptr_int16 result,
   int w_input,
   int w_out,
   int w_blk,
   int h_blk,
   int shift_val,
   int type_input,
   int type_output,
   unsigned short pblock[])
{
   int __offset = 0;
   /* Loop 1 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), (w_out/(2 * (8u)))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), (h_blk)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(6), __vcop_store_round_sat(SM_NONE,0,RM_TRUNC,shift_val));
   __vcop_pblock_init16(pblock, __offset+_PREG(7), (w_input*sizeof(*in)));
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)in+2*sizeof(*in));
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)result);
   __vcop_pblock_init16(pblock, __offset+_PREG(12), (2*8u*sizeof(*in)) -(w_input*sizeof(*in))*((h_blk)-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(13), (w_out*sizeof(*result)));
   __vcop_pblock_init16(pblock, __offset+_PREG(14), (2*8u*sizeof(*result)) -(w_out*sizeof(*result))*((h_blk)-1u));
   __vcop_pblock_init32(pblock, __offset+_PREG(16), 0);
   __vcop_pblock_init32(pblock, __offset+_PREG(18), (uchar *)in);
   __offset += 18;

   return 18u;
}

void vcop_avg2x2_short_vloops(
   unsigned short pblock[])
{
   /* Kernel-wide Vector Registers */
   #pragma VCC_VREG("Vin0", 16);
   #pragma VCC_VREG("Vin1", 17);
   #pragma VCC_VREG("Vin2", 18);
   #pragma VCC_VREG("Vin3", 19);
   #pragma VCC_VREG("Vout0", 20);
   #pragma VCC_VREG("Vout1", 21);
   #pragma VCC_VREG("Vprev0", 22);
   #pragma VCC_VREG("Vprev1", 23);

   __vcop_param(&pblock[0]);

   /* VLOOP 1 Start */

   /* VLOOP Local Vector Registers */
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("inAddr", "A0");
   #pragma EVE_REG("outAddr", "A1");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I1", "I3");
   #pragma EVE_REG("I2", "I4");
   

   __vcop_vloop(__vcop_compute(), 14u, 9u, 1u);
   __vcop_vinit(__vcop_sizeW(), __vcop_i4_zero(), _PREG(16), _VREG(22));
   __vcop_vinit(__vcop_sizeW(), __vcop_i4_zero(), _PREG(16), _VREG(23));
   __vcop_vagen(_AGEN(0), _PREG(7), _PREG(12), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(1), _PREG(13), _PREG(14), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeH(), __vcop_dintrlv(), _PREG(18), _AGEN(0), _VPAIR(16,17), __vcop_alws());
   __vcop_vload(__vcop_sizeH(), __vcop_dintrlv(), _PREG(8), _AGEN(0), _VPAIR(18,19), __vcop_alws());
   __vcop_vadd(_VREG(16), _VREG(17), _VREG(20));
   __vcop_vadd(_VREG(17), _VREG(18), _VREG(21));
   __vcop_vadd(_VREG(20), _VREG(22), _VREG(20));
   __vcop_vadd(_VREG(21), _VREG(23), _VREG(21));
   __vcop_vadd(_VREG(16), _VREG(17), _VREG(22));
   __vcop_vadd(_VREG(17), _VREG(18), _VREG(23));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeH(), __vcop_intrlv(), __vcop_alws(), _VPAIR(20,21), _PREG(10), _AGEN(1), _PREG(6));
   __vcop_vloop_end(1u);

}

void vcop_avg2x2_short(
   __vptr_int16 in,
   __vptr_int16 result,
   int w_input,
   int w_out,
   int w_blk,
   int h_blk,
   int shift_val,
   int type_input,
   int type_output)
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_avg2x2_short_init(in, result, w_input, w_out, w_blk, h_blk, shift_val, type_input, type_output, __pblock_vcop_avg2x2_short);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_avg2x2_short_vloops(__pblock_vcop_avg2x2_short);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

void vcop_avg2x2_short_custom(
   __vptr_int16 in,
   __vptr_int16 result,
   int w_input,
   int w_out,
   int w_blk,
   int h_blk,
   int shift_val,
   int type_input,
   int type_output,
   unsigned short pblock[])
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_avg2x2_short_init(in, result, w_input, w_out, w_blk, h_blk, shift_val, type_input, type_output, pblock);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_avg2x2_short_vloops(pblock);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

