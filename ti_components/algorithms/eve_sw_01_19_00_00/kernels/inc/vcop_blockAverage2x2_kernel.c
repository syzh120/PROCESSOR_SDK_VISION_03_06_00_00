#include <vcop\vcop.h>

typedef unsigned char uchar;

#pragma DATA_SECTION(__pblock_vcop_blockAverage2x2_uchar, ".vcop_parameter_block")
#pragma DATA_ALIGN(__pblock_vcop_blockAverage2x2_uchar, __ALIGNOF__(int));
unsigned short __pblock_vcop_blockAverage2x2_uchar[16];

unsigned int vcop_blockAverage2x2_uchar_param_count(void)
{
   return 16u;
}

unsigned int vcop_blockAverage2x2_uchar_ctrl_count(void)
{
   return 0u;
}

unsigned int vcop_blockAverage2x2_uchar_init(
   __vptr_uint8 in,
   __vptr_uint8 result,
   int w_in,
   int w_out,
   int w_compute,
   int h_compute,
   unsigned short pblock[])
{
   int __offset = 0;
   /* Loop 1 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), (h_compute / 2)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), ((w_compute +(2*(8u)-1)) / (2*(8u)))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(6), __vcop_store_round_sat(SM_NONE,0,RM_ROUND,2));
   __vcop_pblock_init16(pblock, __offset+_PREG(7), 16);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)result);
   __vcop_pblock_init16(pblock, __offset+_PREG(10), (sizeof(*in)*w_in*2) -(2*(8u*sizeof(*in)))*(((w_compute +(2*(8u)-1)) / (2*(8u)))-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(11), 8);
   __vcop_pblock_init16(pblock, __offset+_PREG(12), (sizeof(*result)*w_out) -((8u*sizeof(*result)))*(((w_compute +(2*(8u)-1)) / (2*(8u)))-1u));
   __vcop_pblock_init32(pblock, __offset+_PREG(14), (uchar *)in);
   __vcop_pblock_init32(pblock, __offset+_PREG(16), (uchar *)in+sizeof(*in)*w_in);
   __offset += 16;

   return 16u;
}

void vcop_blockAverage2x2_uchar_vloops(
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
   #pragma VCC_VREG("vAver0", 24);
   #pragma VCC_VREG("vAver1", 25);
   #pragma VCC_VREG("vIn0a", 26);
   #pragma VCC_VREG("vIn0b", 27);
   #pragma VCC_VREG("vIn1a", 28);
   #pragma VCC_VREG("vIn1b", 29);
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("AddrIn", "A0");
   #pragma EVE_REG("AddrOut", "A1");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("i", "I3");
   #pragma EVE_REG("j", "I4");
   

   __vcop_vloop(__vcop_compute(), 9u, 8u, 1u);
   __vcop_vagen(_AGEN(0), _PREG(7), _PREG(10), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(1), _PREG(11), _PREG(12), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeBU(), __vcop_dintrlv(), _PREG(14), _AGEN(0), _VPAIR(26,27), __vcop_alws());
   __vcop_vload(__vcop_sizeBU(), __vcop_dintrlv(), _PREG(16), _AGEN(0), _VPAIR(28,29), __vcop_alws());
   __vcop_vadd(_VREG(26), _VREG(27), _VREG(24));
   __vcop_vadd(_VREG(28), _VREG(29), _VREG(25));
   __vcop_vadd(_VREG(24), _VREG(25), _VREG(24));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeBU(), __vcop_npt(), __vcop_alws(), _VREG(24), _PREG(8), _AGEN(1), _PREG(6));
   __vcop_vloop_end(1u);

}

void vcop_blockAverage2x2_uchar(
   __vptr_uint8 in,
   __vptr_uint8 result,
   int w_in,
   int w_out,
   int w_compute,
   int h_compute)
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_blockAverage2x2_uchar_init(in, result, w_in, w_out, w_compute, h_compute, __pblock_vcop_blockAverage2x2_uchar);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_blockAverage2x2_uchar_vloops(__pblock_vcop_blockAverage2x2_uchar);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

void vcop_blockAverage2x2_uchar_custom(
   __vptr_uint8 in,
   __vptr_uint8 result,
   int w_in,
   int w_out,
   int w_compute,
   int h_compute,
   unsigned short pblock[])
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_blockAverage2x2_uchar_init(in, result, w_in, w_out, w_compute, h_compute, pblock);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_blockAverage2x2_uchar_vloops(pblock);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

#pragma DATA_SECTION(__pblock_vcop_blockAverage2x2_char, ".vcop_parameter_block")
#pragma DATA_ALIGN(__pblock_vcop_blockAverage2x2_char, __ALIGNOF__(int));
unsigned short __pblock_vcop_blockAverage2x2_char[16];

unsigned int vcop_blockAverage2x2_char_param_count(void)
{
   return 16u;
}

unsigned int vcop_blockAverage2x2_char_ctrl_count(void)
{
   return 0u;
}

unsigned int vcop_blockAverage2x2_char_init(
   __vptr_int8 in,
   __vptr_int8 result,
   int w_in,
   int w_out,
   int w_compute,
   int h_compute,
   unsigned short pblock[])
{
   int __offset = 0;
   /* Loop 1 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), (h_compute / 2)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), ((w_compute +(2*(8u)-1))  / (2*(8u)))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(6), __vcop_store_round_sat(SM_NONE,0,RM_ROUND,2));
   __vcop_pblock_init16(pblock, __offset+_PREG(7), 16);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)result);
   __vcop_pblock_init16(pblock, __offset+_PREG(10), (sizeof(*in)*w_in*2) -(2*(8u*sizeof(*in)))*(((w_compute +(2*(8u)-1))  / (2*(8u)))-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(11), 8);
   __vcop_pblock_init16(pblock, __offset+_PREG(12), (sizeof(*result)*w_out) -((8u*sizeof(*result)))*(((w_compute +(2*(8u)-1))  / (2*(8u)))-1u));
   __vcop_pblock_init32(pblock, __offset+_PREG(14), (uchar *)in);
   __vcop_pblock_init32(pblock, __offset+_PREG(16), (uchar *)in+sizeof(*in)*w_in);
   __offset += 16;

   return 16u;
}

void vcop_blockAverage2x2_char_vloops(
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
   #pragma VCC_VREG("vAver0", 24);
   #pragma VCC_VREG("vAver1", 25);
   #pragma VCC_VREG("vIn0a", 26);
   #pragma VCC_VREG("vIn0b", 27);
   #pragma VCC_VREG("vIn1a", 28);
   #pragma VCC_VREG("vIn1b", 29);
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("AddrIn", "A0");
   #pragma EVE_REG("AddrOut", "A1");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("i", "I3");
   #pragma EVE_REG("j", "I4");
   

   __vcop_vloop(__vcop_compute(), 9u, 8u, 1u);
   __vcop_vagen(_AGEN(0), _PREG(7), _PREG(10), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(1), _PREG(11), _PREG(12), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeB(), __vcop_dintrlv(), _PREG(14), _AGEN(0), _VPAIR(26,27), __vcop_alws());
   __vcop_vload(__vcop_sizeB(), __vcop_dintrlv(), _PREG(16), _AGEN(0), _VPAIR(28,29), __vcop_alws());
   __vcop_vadd(_VREG(26), _VREG(27), _VREG(24));
   __vcop_vadd(_VREG(28), _VREG(29), _VREG(25));
   __vcop_vadd(_VREG(24), _VREG(25), _VREG(24));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeB(), __vcop_npt(), __vcop_alws(), _VREG(24), _PREG(8), _AGEN(1), _PREG(6));
   __vcop_vloop_end(1u);

}

void vcop_blockAverage2x2_char(
   __vptr_int8 in,
   __vptr_int8 result,
   int w_in,
   int w_out,
   int w_compute,
   int h_compute)
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_blockAverage2x2_char_init(in, result, w_in, w_out, w_compute, h_compute, __pblock_vcop_blockAverage2x2_char);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_blockAverage2x2_char_vloops(__pblock_vcop_blockAverage2x2_char);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

void vcop_blockAverage2x2_char_custom(
   __vptr_int8 in,
   __vptr_int8 result,
   int w_in,
   int w_out,
   int w_compute,
   int h_compute,
   unsigned short pblock[])
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_blockAverage2x2_char_init(in, result, w_in, w_out, w_compute, h_compute, pblock);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_blockAverage2x2_char_vloops(pblock);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

#pragma DATA_SECTION(__pblock_vcop_blockAverage2x2_ushort, ".vcop_parameter_block")
#pragma DATA_ALIGN(__pblock_vcop_blockAverage2x2_ushort, __ALIGNOF__(int));
unsigned short __pblock_vcop_blockAverage2x2_ushort[16];

unsigned int vcop_blockAverage2x2_ushort_param_count(void)
{
   return 16u;
}

unsigned int vcop_blockAverage2x2_ushort_ctrl_count(void)
{
   return 0u;
}

unsigned int vcop_blockAverage2x2_ushort_init(
   __vptr_uint16 in,
   __vptr_uint16 result,
   int w_in,
   int w_out,
   int w_compute,
   int h_compute,
   unsigned short pblock[])
{
   int __offset = 0;
   /* Loop 1 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), (h_compute / 2)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), ((w_compute +(2*(8u)-1))  / (2*(8u)))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(6), __vcop_store_round_sat(SM_NONE,0,RM_ROUND,2));
   __vcop_pblock_init16(pblock, __offset+_PREG(7), 32);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)result);
   __vcop_pblock_init16(pblock, __offset+_PREG(10), (sizeof(*in)*w_in*2) -(2*(8u*sizeof(*in)))*(((w_compute +(2*(8u)-1))  / (2*(8u)))-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(11), 16);
   __vcop_pblock_init16(pblock, __offset+_PREG(12), (sizeof(*result)*w_out) -((8u*sizeof(*result)))*(((w_compute +(2*(8u)-1))  / (2*(8u)))-1u));
   __vcop_pblock_init32(pblock, __offset+_PREG(14), (uchar *)in);
   __vcop_pblock_init32(pblock, __offset+_PREG(16), (uchar *)in+sizeof(*in)*w_in);
   __offset += 16;

   return 16u;
}

void vcop_blockAverage2x2_ushort_vloops(
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
   #pragma VCC_VREG("vAver0", 24);
   #pragma VCC_VREG("vAver1", 25);
   #pragma VCC_VREG("vIn0a", 26);
   #pragma VCC_VREG("vIn0b", 27);
   #pragma VCC_VREG("vIn1a", 28);
   #pragma VCC_VREG("vIn1b", 29);
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("AddrIn", "A0");
   #pragma EVE_REG("AddrOut", "A1");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("i", "I3");
   #pragma EVE_REG("j", "I4");
   

   __vcop_vloop(__vcop_compute(), 9u, 8u, 1u);
   __vcop_vagen(_AGEN(0), _PREG(7), _PREG(10), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(1), _PREG(11), _PREG(12), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeHU(), __vcop_dintrlv(), _PREG(14), _AGEN(0), _VPAIR(26,27), __vcop_alws());
   __vcop_vload(__vcop_sizeHU(), __vcop_dintrlv(), _PREG(16), _AGEN(0), _VPAIR(28,29), __vcop_alws());
   __vcop_vadd(_VREG(26), _VREG(27), _VREG(24));
   __vcop_vadd(_VREG(28), _VREG(29), _VREG(25));
   __vcop_vadd(_VREG(24), _VREG(25), _VREG(24));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeHU(), __vcop_npt(), __vcop_alws(), _VREG(24), _PREG(8), _AGEN(1), _PREG(6));
   __vcop_vloop_end(1u);

}

void vcop_blockAverage2x2_ushort(
   __vptr_uint16 in,
   __vptr_uint16 result,
   int w_in,
   int w_out,
   int w_compute,
   int h_compute)
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_blockAverage2x2_ushort_init(in, result, w_in, w_out, w_compute, h_compute, __pblock_vcop_blockAverage2x2_ushort);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_blockAverage2x2_ushort_vloops(__pblock_vcop_blockAverage2x2_ushort);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

void vcop_blockAverage2x2_ushort_custom(
   __vptr_uint16 in,
   __vptr_uint16 result,
   int w_in,
   int w_out,
   int w_compute,
   int h_compute,
   unsigned short pblock[])
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_blockAverage2x2_ushort_init(in, result, w_in, w_out, w_compute, h_compute, pblock);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_blockAverage2x2_ushort_vloops(pblock);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

#pragma DATA_SECTION(__pblock_vcop_blockAverage2x2_short, ".vcop_parameter_block")
#pragma DATA_ALIGN(__pblock_vcop_blockAverage2x2_short, __ALIGNOF__(int));
unsigned short __pblock_vcop_blockAverage2x2_short[16];

unsigned int vcop_blockAverage2x2_short_param_count(void)
{
   return 16u;
}

unsigned int vcop_blockAverage2x2_short_ctrl_count(void)
{
   return 0u;
}

unsigned int vcop_blockAverage2x2_short_init(
   __vptr_int16 in,
   __vptr_int16 result,
   int w_in,
   int w_out,
   int w_compute,
   int h_compute,
   unsigned short pblock[])
{
   int __offset = 0;
   /* Loop 1 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), (h_compute / 2)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), ((w_compute + (2*(8u)-1))  / (2*(8u)))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(6), __vcop_store_round_sat(SM_NONE,0,RM_ROUND,2));
   __vcop_pblock_init16(pblock, __offset+_PREG(7), 32);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)result);
   __vcop_pblock_init16(pblock, __offset+_PREG(10), (sizeof(*in)*w_in*2) -(2*(8u*sizeof(*in)))*(((w_compute + (2*(8u)-1))  / (2*(8u)))-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(11), 16);
   __vcop_pblock_init16(pblock, __offset+_PREG(12), (sizeof(*result)*w_out) -((8u*sizeof(*result)))*(((w_compute + (2*(8u)-1))  / (2*(8u)))-1u));
   __vcop_pblock_init32(pblock, __offset+_PREG(14), (uchar *)in);
   __vcop_pblock_init32(pblock, __offset+_PREG(16), (uchar *)in+sizeof(*in)*w_in);
   __offset += 16;

   return 16u;
}

void vcop_blockAverage2x2_short_vloops(
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
   #pragma VCC_VREG("vAver0", 24);
   #pragma VCC_VREG("vAver1", 25);
   #pragma VCC_VREG("vIn0a", 26);
   #pragma VCC_VREG("vIn0b", 27);
   #pragma VCC_VREG("vIn1a", 28);
   #pragma VCC_VREG("vIn1b", 29);
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("AddrIn", "A0");
   #pragma EVE_REG("AddrOut", "A1");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("i", "I3");
   #pragma EVE_REG("j", "I4");
   

   __vcop_vloop(__vcop_compute(), 9u, 8u, 1u);
   __vcop_vagen(_AGEN(0), _PREG(7), _PREG(10), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(1), _PREG(11), _PREG(12), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeH(), __vcop_dintrlv(), _PREG(14), _AGEN(0), _VPAIR(26,27), __vcop_alws());
   __vcop_vload(__vcop_sizeH(), __vcop_dintrlv(), _PREG(16), _AGEN(0), _VPAIR(28,29), __vcop_alws());
   __vcop_vadd(_VREG(26), _VREG(27), _VREG(24));
   __vcop_vadd(_VREG(28), _VREG(29), _VREG(25));
   __vcop_vadd(_VREG(24), _VREG(25), _VREG(24));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeH(), __vcop_npt(), __vcop_alws(), _VREG(24), _PREG(8), _AGEN(1), _PREG(6));
   __vcop_vloop_end(1u);

}

void vcop_blockAverage2x2_short(
   __vptr_int16 in,
   __vptr_int16 result,
   int w_in,
   int w_out,
   int w_compute,
   int h_compute)
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_blockAverage2x2_short_init(in, result, w_in, w_out, w_compute, h_compute, __pblock_vcop_blockAverage2x2_short);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_blockAverage2x2_short_vloops(__pblock_vcop_blockAverage2x2_short);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

void vcop_blockAverage2x2_short_custom(
   __vptr_int16 in,
   __vptr_int16 result,
   int w_in,
   int w_out,
   int w_compute,
   int h_compute,
   unsigned short pblock[])
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_blockAverage2x2_short_init(in, result, w_in, w_out, w_compute, h_compute, pblock);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_blockAverage2x2_short_vloops(pblock);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

