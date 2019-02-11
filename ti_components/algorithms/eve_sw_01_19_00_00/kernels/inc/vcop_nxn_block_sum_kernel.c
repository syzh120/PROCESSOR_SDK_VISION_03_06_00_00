#include <vcop\vcop.h>

typedef unsigned char uchar;

#pragma DATA_SECTION(__pblock_vcop_nxn_sum_interleaved, ".vcop_parameter_block")
#pragma DATA_ALIGN(__pblock_vcop_nxn_sum_interleaved, __ALIGNOF__(int));
unsigned short __pblock_vcop_nxn_sum_interleaved[62];

unsigned int vcop_nxn_sum_interleaved_param_count(void)
{
   return 62u;
}

unsigned int vcop_nxn_sum_interleaved_ctrl_count(void)
{
   return 0u;
}

unsigned int vcop_nxn_sum_interleaved_init(
   __vptr_uint8 inPtr1,
   __vptr_uint16 outPtr1,
   __vptr_uint16 outPtr2,
   __vptr_uint32 tempPtr1,
   __vptr_uint32 tempPtr2,
   unsigned short n,
   unsigned short width,
   unsigned short height,
   unsigned short pitch,
   signed short shiftValue,
   unsigned short pblock[])
{
   int __offset = 0;
   /* Loop 1 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), ((height/(8u))/n)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), ((width)/((8u)))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), ((8u))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), (n)-1u);
   __vcop_pblock_init32(pblock, __offset+_PREG(6), (uchar *)inPtr1);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)tempPtr1);
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)tempPtr2);
   __vcop_pblock_init16(pblock, __offset+_PREG(12), (pitch*1));
   __vcop_pblock_init16(pblock, __offset+_PREG(13), (pitch*1*n) -(pitch*1)*((n)-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(14), (8u*2) -(pitch*1*n)*(((8u))-1u) -(pitch*1)*((n)-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(15), (pitch*1*8u*n) -(8u*2)*(((width)/((8u)))-1u) -(pitch*1*n)*(((8u))-1u) -(pitch*1)*((n)-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(16), 4);
   __vcop_pblock_init16(pblock, __offset+_PREG(17), 260);
   __vcop_pblock_init16(pblock, __offset+_PREG(18), ((width/8u)*((8u+1)*4*8u)) -(((8u+1)*4*8u))*(((width)/((8u)))-1u) -(4)*(((8u))-1u));
   __vcop_pblock_init32(pblock, __offset+_PREG(20), shiftValue);
   __vcop_pblock_init32(pblock, __offset+_PREG(22), 0);
   __offset += 22;

   /* Loop 2 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), ((height/n)/((8u)))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), ((width/(8u))/n)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), ((8u))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), (n)-1u);
   __vcop_pblock_init32(pblock, __offset+_PREG(6), (uchar *)tempPtr2);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)tempPtr1+(width+(8u-1))/8u*8u/8u*((height+(8u*n-1))/(8u*n)*(8u*n)/(8u*n)*((8u+1)*4*8u)));
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)tempPtr2+(width+(8u-1))/8u*8u/8u*((height+(8u*n-1))/(8u*n)*(8u*n)/(8u*n)*((8u+1)*4*8u)));
   __vcop_pblock_init16(pblock, __offset+_PREG(12), 36);
   __vcop_pblock_init16(pblock, __offset+_PREG(13), (((8u+1)*4)*n) -(((8u+1)*4))*((n)-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(14), (((8u+1)*4)*8u*n) -(((8u+1)*4)*n)*(((8u))-1u) -(((8u+1)*4))*((n)-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(15), ((width/8u)*((8u+1)*4*8u)) -(((8u+1)*4)*8u*n)*(((width/(8u))/n)-1u) -(((8u+1)*4)*n)*(((8u))-1u) -(((8u+1)*4))*((n)-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(16), 4);
   __vcop_pblock_init16(pblock, __offset+_PREG(17), 260);
   __vcop_pblock_init16(pblock, __offset+_PREG(18), ((width/8u/n)*((8u+1)*4*8u)) -(((8u+1)*4*8u))*(((width/(8u))/n)-1u) -(4)*(((8u))-1u));
   __vcop_pblock_init32(pblock, __offset+_PREG(20), 0);
   __vcop_pblock_init32(pblock, __offset+_PREG(22), (uchar *)tempPtr1);
   __offset += 22;

   /* Loop 3 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), (((height / (8u)) /n))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), (((width/n)/(8u)))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), ((8u))-1u);
   __vcop_pblock_init32(pblock, __offset+_PREG(6), (uchar *)outPtr1);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)outPtr2);
   __vcop_pblock_init16(pblock, __offset+_PREG(10), (sizeof(*outPtr2)*(width/n)));
   __vcop_pblock_init16(pblock, __offset+_PREG(11), (8u*sizeof(*outPtr2)) -(sizeof(*outPtr2)*(width/n))*(((8u))-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(12), (sizeof(*outPtr2)*(width/n)*8u) -(8u*sizeof(*outPtr2))*((((width/n)/(8u)))-1u) -(sizeof(*outPtr2)*(width/n))*(((8u))-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(13), 36);
   __vcop_pblock_init16(pblock, __offset+_PREG(14), ((width/n/8u)*((8u+1)*4*8u)) -(((8u+1)*4*8u))*((((width/n)/(8u)))-1u) -(((8u+1)*4))*(((8u))-1u));
   __vcop_pblock_init32(pblock, __offset+_PREG(16), (uchar *)tempPtr1+(width+(8u-1))/8u*8u/8u*((height+(8u*n-1))/(8u*n)*(8u*n)/(8u*n)*((8u+1)*4*8u)));
   __vcop_pblock_init32(pblock, __offset+_PREG(18), (uchar *)tempPtr2+(width+(8u-1))/8u*8u/8u*((height+(8u*n-1))/(8u*n)*(8u*n)/(8u*n)*((8u+1)*4*8u)));
   __offset += 18;

   return 62u;
}

void vcop_nxn_sum_interleaved_vloops(
   unsigned short pblock[])
{
   /* Kernel-wide Vector Registers */
   #pragma VCC_VREG("vin1", 16);
   #pragma VCC_VREG("vin2", 17);
   #pragma VCC_VREG("vin3", 18);
   #pragma VCC_VREG("vin4", 19);
   #pragma VCC_VREG("vshift", 20);
   #pragma VCC_VREG("vsum1", 21);
   #pragma VCC_VREG("vsum2", 22);

   __vcop_param(&pblock[0]);

   /* VLOOP 1 Start */

   /* VLOOP Local Vector Registers */
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("Addr1", "A0");
   #pragma EVE_REG("Addr2", "A1");
   #pragma EVE_REG("Addr3", "A2");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I1", "I1");
   #pragma EVE_REG("I2", "I2");
   #pragma EVE_REG("I3", "I3");
   #pragma EVE_REG("I4", "I4");
   

   __vcop_vloop(__vcop_compute(), 12u, 11u, 1u);
   __vcop_vinit(__vcop_sizeW(), __vcop_once(), _PREG(20), _VREG(20));
   __vcop_vinit(__vcop_sizeW(), __vcop_i4_zero(), _PREG(22), _VREG(21));
   __vcop_vinit(__vcop_sizeW(), __vcop_i4_zero(), _PREG(22), _VREG(22));
   __vcop_vagen(_AGEN(0), _PREG(12), _PREG(13), _PREG(14), _PREG(15));
   __vcop_vagen(_AGEN(1), _PREG(0), _PREG(16), _PREG(17), _PREG(18));
   __vcop_vload(__vcop_sizeBU(), __vcop_dintrlv(), _PREG(6), _AGEN(0), _VPAIR(18,19), __vcop_alws());
   __vcop_vadd(_VREG(21), _VREG(18), _VREG(21));
   __vcop_vadd(_VREG(22), _VREG(19), _VREG(22));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeWU(), __vcop_offst_np1(), __vcop_last_i4(), _VREG(21), _PREG(8), _AGEN(1), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeWU(), __vcop_offst_np1(), __vcop_last_i4(), _VREG(22), _PREG(10), _AGEN(1), _PREG(0));
   __vcop_vloop_end(1u);

   /* VLOOP 2 Start */

   /* VLOOP Local Vector Registers */
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("Addr1", "A0");
   #pragma EVE_REG("Addr2", "A1");
   #pragma EVE_REG("Addr3", "A2");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I1", "I1");
   #pragma EVE_REG("I2", "I2");
   #pragma EVE_REG("I3", "I3");
   #pragma EVE_REG("I4", "I4");
   

   __vcop_vloop(__vcop_compute(), 12u, 11u, 2u);
   __vcop_vinit(__vcop_sizeW(), __vcop_i4_zero(), _PREG(20), _VREG(21));
   __vcop_vinit(__vcop_sizeW(), __vcop_i4_zero(), _PREG(20), _VREG(22));
   __vcop_vagen(_AGEN(0), _PREG(12), _PREG(13), _PREG(14), _PREG(15));
   __vcop_vagen(_AGEN(1), _PREG(0), _PREG(16), _PREG(17), _PREG(18));
   __vcop_vload(__vcop_sizeWU(), __vcop_npt(), _PREG(22), _AGEN(0), _VREG(16), __vcop_alws());
   __vcop_vload(__vcop_sizeWU(), __vcop_npt(), _PREG(6), _AGEN(0), _VREG(17), __vcop_alws());
   __vcop_vadd(_VREG(21), _VREG(16), _VREG(21));
   __vcop_vadd(_VREG(22), _VREG(17), _VREG(22));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeWU(), __vcop_offst_np1(), __vcop_last_i4(), _VREG(21), _PREG(8), _AGEN(1), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeWU(), __vcop_offst_np1(), __vcop_last_i4(), _VREG(22), _PREG(10), _AGEN(1), _PREG(0));
   __vcop_vloop_end(2u);

   /* VLOOP 3 Start */

   /* VLOOP Local Vector Registers */
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("Addr1", "A0");
   #pragma EVE_REG("Addr2", "A1");
   #pragma EVE_REG("Addr3", "A2");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I1", "I2");
   #pragma EVE_REG("I2", "I3");
   #pragma EVE_REG("I3", "I4");
   

   __vcop_vloop(__vcop_compute(), 10u, 9u, 3u);
   __vcop_vagen(_AGEN(0), _PREG(10), _PREG(11), _PREG(12), _PREG(0));
   __vcop_vagen(_AGEN(1), _PREG(13), _PREG(13), _PREG(14), _PREG(0));
   __vcop_vload(__vcop_sizeWU(), __vcop_npt(), _PREG(16), _AGEN(1), _VREG(16), __vcop_alws());
   __vcop_vload(__vcop_sizeWU(), __vcop_npt(), _PREG(18), _AGEN(1), _VREG(17), __vcop_alws());
   __vcop_vshf(_VREG(16), _VREG(20), _VREG(16));
   __vcop_vshf(_VREG(17), _VREG(20), _VREG(17));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeHU(), __vcop_npt(), __vcop_alws(), _VREG(16), _PREG(6), _AGEN(0), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeHU(), __vcop_npt(), __vcop_alws(), _VREG(17), _PREG(8), _AGEN(0), _PREG(0));
   __vcop_vloop_end(3u);

}

void vcop_nxn_sum_interleaved(
   __vptr_uint8 inPtr1,
   __vptr_uint16 outPtr1,
   __vptr_uint16 outPtr2,
   __vptr_uint32 tempPtr1,
   __vptr_uint32 tempPtr2,
   unsigned short n,
   unsigned short width,
   unsigned short height,
   unsigned short pitch,
   signed short shiftValue)
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_nxn_sum_interleaved_init(inPtr1, outPtr1, outPtr2, tempPtr1, tempPtr2, n, width, height, pitch, shiftValue, __pblock_vcop_nxn_sum_interleaved);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_nxn_sum_interleaved_vloops(__pblock_vcop_nxn_sum_interleaved);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

void vcop_nxn_sum_interleaved_custom(
   __vptr_uint8 inPtr1,
   __vptr_uint16 outPtr1,
   __vptr_uint16 outPtr2,
   __vptr_uint32 tempPtr1,
   __vptr_uint32 tempPtr2,
   unsigned short n,
   unsigned short width,
   unsigned short height,
   unsigned short pitch,
   signed short shiftValue,
   unsigned short pblock[])
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_nxn_sum_interleaved_init(inPtr1, outPtr1, outPtr2, tempPtr1, tempPtr2, n, width, height, pitch, shiftValue, pblock);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_nxn_sum_interleaved_vloops(pblock);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

#pragma DATA_SECTION(__pblock_vcop_nxn_sum_u8, ".vcop_parameter_block")
#pragma DATA_ALIGN(__pblock_vcop_nxn_sum_u8, __ALIGNOF__(int));
unsigned short __pblock_vcop_nxn_sum_u8[66];

unsigned int vcop_nxn_sum_u8_param_count(void)
{
   return 66u;
}

unsigned int vcop_nxn_sum_u8_ctrl_count(void)
{
   return 0u;
}

unsigned int vcop_nxn_sum_u8_init(
   __vptr_uint8 inPtr1,
   __vptr_uint8 inPtr2,
   __vptr_uint16 outPtr1,
   __vptr_uint16 outPtr2,
   __vptr_uint32 tempPtr1,
   __vptr_uint32 tempPtr2,
   unsigned short n,
   unsigned short width,
   unsigned short height,
   unsigned short pitch1,
   unsigned short pitch2,
   unsigned short pblock[])
{
   int __offset = 0;
   /* Loop 1 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), ((((height + (((8u)*n)-1)) / ((8u)*n)) * ((8u)*n))/((8u)*n))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), ((((width + ((8u)-1)) / (8u)) * (8u))/(8u))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), ((8u))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), (n)-1u);
   __vcop_pblock_init32(pblock, __offset+_PREG(6), (uchar *)inPtr2);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)tempPtr1);
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)tempPtr2);
   __vcop_pblock_init16(pblock, __offset+_PREG(12), (pitch1*1));
   __vcop_pblock_init16(pblock, __offset+_PREG(13), (pitch1*1*n) -(pitch1*1)*((n)-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(14), (8u) -(pitch1*1*n)*(((8u))-1u) -(pitch1*1)*((n)-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(15), (pitch1*1*8u*n) -(8u)*(((((width + ((8u)-1)) / (8u)) * (8u))/(8u))-1u) -(pitch1*1*n)*(((8u))-1u) -(pitch1*1)*((n)-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(16), 4);
   __vcop_pblock_init16(pblock, __offset+_PREG(17), 260);
   __vcop_pblock_init16(pblock, __offset+_PREG(18), ((width/8u)*((8u+1)*4*8u)) -(((8u+1)*4*8u))*(((((width + ((8u)-1)) / (8u)) * (8u))/(8u))-1u) -(4)*(((8u))-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(19), (pitch2*1));
   __vcop_pblock_init16(pblock, __offset+_PREG(20), (pitch2*1*n) -(pitch2*1)*((n)-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(21), (8u) -(pitch2*1*n)*(((8u))-1u) -(pitch2*1)*((n)-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(22), (pitch2*1*8u*n) -(8u)*(((((width + ((8u)-1)) / (8u)) * (8u))/(8u))-1u) -(pitch2*1*n)*(((8u))-1u) -(pitch2*1)*((n)-1u));
   __vcop_pblock_init32(pblock, __offset+_PREG(24), 0);
   __vcop_pblock_init32(pblock, __offset+_PREG(26), (uchar *)inPtr1);
   __offset += 26;

   /* Loop 2 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), ((((height + (((8u)*n)-1)) / ((8u)*n)) * ((8u)*n))/((8u)*n))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), ((((width + (((8u)*n)-1)) / ((8u)*n)) * ((8u)*n))/((8u)*n))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), ((8u))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), (n)-1u);
   __vcop_pblock_init32(pblock, __offset+_PREG(6), (uchar *)tempPtr2);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)tempPtr1+(width+(8u-1))/8u*8u/8u*((height+(8u*n-1))/(8u*n)*(8u*n)/(8u*n)*((8u+1)*4*8u)));
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)tempPtr2+(width+(8u-1))/8u*8u/8u*((height+(8u*n-1))/(8u*n)*(8u*n)/(8u*n)*((8u+1)*4*8u)));
   __vcop_pblock_init16(pblock, __offset+_PREG(12), 36);
   __vcop_pblock_init16(pblock, __offset+_PREG(13), (((8u+1)*4)*n) -(((8u+1)*4))*((n)-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(14), (((8u+1)*4)*8u*n) -(((8u+1)*4)*n)*(((8u))-1u) -(((8u+1)*4))*((n)-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(15), ((width/8u)*((8u+1)*4*8u)) -(((8u+1)*4)*8u*n)*(((((width + (((8u)*n)-1)) / ((8u)*n)) * ((8u)*n))/((8u)*n))-1u) -(((8u+1)*4)*n)*(((8u))-1u) -(((8u+1)*4))*((n)-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(16), 4);
   __vcop_pblock_init16(pblock, __offset+_PREG(17), 260);
   __vcop_pblock_init16(pblock, __offset+_PREG(18), ((width/8u/n)*((8u+1)*4*8u)) -(((8u+1)*4*8u))*(((((width + (((8u)*n)-1)) / ((8u)*n)) * ((8u)*n))/((8u)*n))-1u) -(4)*(((8u))-1u));
   __vcop_pblock_init32(pblock, __offset+_PREG(20), 0);
   __vcop_pblock_init32(pblock, __offset+_PREG(22), (uchar *)tempPtr1);
   __offset += 22;

   /* Loop 3 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), ((((height + (((8u)*n)-1)) / ((8u)*n)) * ((8u)*n))/((8u)*n))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), ((((width + (((8u)*n)-1)) / ((8u)*n)) * ((8u)*n))/((8u)*n))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), ((8u))-1u);
   __vcop_pblock_init32(pblock, __offset+_PREG(6), (uchar *)outPtr1);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)outPtr2);
   __vcop_pblock_init16(pblock, __offset+_PREG(10), (sizeof(*outPtr2)*(width/n)));
   __vcop_pblock_init16(pblock, __offset+_PREG(11), (8u*sizeof(*outPtr2)) -(sizeof(*outPtr2)*(width/n))*(((8u))-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(12), (sizeof(*outPtr2)*(width/n)*8u) -(8u*sizeof(*outPtr2))*(((((width + (((8u)*n)-1)) / ((8u)*n)) * ((8u)*n))/((8u)*n))-1u) -(sizeof(*outPtr2)*(width/n))*(((8u))-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(13), 36);
   __vcop_pblock_init16(pblock, __offset+_PREG(14), ((width/n/8u)*((8u+1)*4*8u)) -(((8u+1)*4*8u))*(((((width + (((8u)*n)-1)) / ((8u)*n)) * ((8u)*n))/((8u)*n))-1u) -(((8u+1)*4))*(((8u))-1u));
   __vcop_pblock_init32(pblock, __offset+_PREG(16), (uchar *)tempPtr1+(width+(8u-1))/8u*8u/8u*((height+(8u*n-1))/(8u*n)*(8u*n)/(8u*n)*((8u+1)*4*8u)));
   __vcop_pblock_init32(pblock, __offset+_PREG(18), (uchar *)tempPtr2+(width+(8u-1))/8u*8u/8u*((height+(8u*n-1))/(8u*n)*(8u*n)/(8u*n)*((8u+1)*4*8u)));
   __offset += 18;

   return 66u;
}

void vcop_nxn_sum_u8_vloops(
   unsigned short pblock[])
{
   /* Kernel-wide Vector Registers */
   #pragma VCC_VREG("vin1", 16);
   #pragma VCC_VREG("vin2", 17);
   #pragma VCC_VREG("vsum1", 18);
   #pragma VCC_VREG("vsum2", 19);

   __vcop_param(&pblock[0]);

   /* VLOOP 1 Start */

   /* VLOOP Local Vector Registers */
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("Addr1", "A0");
   #pragma EVE_REG("Addr2", "A1");
   #pragma EVE_REG("Addr3", "A2");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I1", "I1");
   #pragma EVE_REG("I2", "I2");
   #pragma EVE_REG("I3", "I3");
   #pragma EVE_REG("I4", "I4");
   

   __vcop_vloop(__vcop_compute(), 12u, 13u, 1u);
   __vcop_vinit(__vcop_sizeW(), __vcop_i4_zero(), _PREG(24), _VREG(18));
   __vcop_vinit(__vcop_sizeW(), __vcop_i4_zero(), _PREG(24), _VREG(19));
   __vcop_vagen(_AGEN(0), _PREG(12), _PREG(13), _PREG(14), _PREG(15));
   __vcop_vagen(_AGEN(1), _PREG(0), _PREG(16), _PREG(17), _PREG(18));
   __vcop_vagen(_AGEN(2), _PREG(19), _PREG(20), _PREG(21), _PREG(22));
   __vcop_vload(__vcop_sizeBU(), __vcop_npt(), _PREG(26), _AGEN(0), _VREG(16), __vcop_alws());
   __vcop_vload(__vcop_sizeBU(), __vcop_npt(), _PREG(6), _AGEN(2), _VREG(17), __vcop_alws());
   __vcop_vadd(_VREG(18), _VREG(16), _VREG(18));
   __vcop_vadd(_VREG(19), _VREG(17), _VREG(19));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeWU(), __vcop_offst_np1(), __vcop_last_i4(), _VREG(18), _PREG(8), _AGEN(1), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeWU(), __vcop_offst_np1(), __vcop_last_i4(), _VREG(19), _PREG(10), _AGEN(1), _PREG(0));
   __vcop_vloop_end(1u);

   /* VLOOP 2 Start */

   /* VLOOP Local Vector Registers */
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("Addr1", "A0");
   #pragma EVE_REG("Addr2", "A1");
   #pragma EVE_REG("Addr3", "A2");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I1", "I1");
   #pragma EVE_REG("I2", "I2");
   #pragma EVE_REG("I3", "I3");
   #pragma EVE_REG("I4", "I4");
   

   __vcop_vloop(__vcop_compute(), 12u, 11u, 2u);
   __vcop_vinit(__vcop_sizeW(), __vcop_i4_zero(), _PREG(20), _VREG(18));
   __vcop_vinit(__vcop_sizeW(), __vcop_i4_zero(), _PREG(20), _VREG(19));
   __vcop_vagen(_AGEN(0), _PREG(12), _PREG(13), _PREG(14), _PREG(15));
   __vcop_vagen(_AGEN(1), _PREG(0), _PREG(16), _PREG(17), _PREG(18));
   __vcop_vload(__vcop_sizeWU(), __vcop_npt(), _PREG(22), _AGEN(0), _VREG(16), __vcop_alws());
   __vcop_vload(__vcop_sizeWU(), __vcop_npt(), _PREG(6), _AGEN(0), _VREG(17), __vcop_alws());
   __vcop_vadd(_VREG(18), _VREG(16), _VREG(18));
   __vcop_vadd(_VREG(19), _VREG(17), _VREG(19));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeWU(), __vcop_offst_np1(), __vcop_last_i4(), _VREG(18), _PREG(8), _AGEN(1), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeWU(), __vcop_offst_np1(), __vcop_last_i4(), _VREG(19), _PREG(10), _AGEN(1), _PREG(0));
   __vcop_vloop_end(2u);

   /* VLOOP 3 Start */

   /* VLOOP Local Vector Registers */
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("Addr1", "A0");
   #pragma EVE_REG("Addr2", "A1");
   #pragma EVE_REG("Addr3", "A2");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I1", "I2");
   #pragma EVE_REG("I2", "I3");
   #pragma EVE_REG("I3", "I4");
   

   __vcop_vloop(__vcop_compute(), 8u, 9u, 3u);
   __vcop_vagen(_AGEN(0), _PREG(10), _PREG(11), _PREG(12), _PREG(0));
   __vcop_vagen(_AGEN(1), _PREG(13), _PREG(13), _PREG(14), _PREG(0));
   __vcop_vload(__vcop_sizeWU(), __vcop_npt(), _PREG(16), _AGEN(1), _VREG(16), __vcop_alws());
   __vcop_vload(__vcop_sizeWU(), __vcop_npt(), _PREG(18), _AGEN(1), _VREG(17), __vcop_alws());
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeHU(), __vcop_npt(), __vcop_alws(), _VREG(16), _PREG(6), _AGEN(0), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeHU(), __vcop_npt(), __vcop_alws(), _VREG(17), _PREG(8), _AGEN(0), _PREG(0));
   __vcop_vloop_end(3u);

}

void vcop_nxn_sum_u8(
   __vptr_uint8 inPtr1,
   __vptr_uint8 inPtr2,
   __vptr_uint16 outPtr1,
   __vptr_uint16 outPtr2,
   __vptr_uint32 tempPtr1,
   __vptr_uint32 tempPtr2,
   unsigned short n,
   unsigned short width,
   unsigned short height,
   unsigned short pitch1,
   unsigned short pitch2)
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_nxn_sum_u8_init(inPtr1, inPtr2, outPtr1, outPtr2, tempPtr1, tempPtr2, n, width, height, pitch1, pitch2, __pblock_vcop_nxn_sum_u8);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_nxn_sum_u8_vloops(__pblock_vcop_nxn_sum_u8);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

void vcop_nxn_sum_u8_custom(
   __vptr_uint8 inPtr1,
   __vptr_uint8 inPtr2,
   __vptr_uint16 outPtr1,
   __vptr_uint16 outPtr2,
   __vptr_uint32 tempPtr1,
   __vptr_uint32 tempPtr2,
   unsigned short n,
   unsigned short width,
   unsigned short height,
   unsigned short pitch1,
   unsigned short pitch2,
   unsigned short pblock[])
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_nxn_sum_u8_init(inPtr1, inPtr2, outPtr1, outPtr2, tempPtr1, tempPtr2, n, width, height, pitch1, pitch2, pblock);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_nxn_sum_u8_vloops(pblock);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

#pragma DATA_SECTION(__pblock_vcop_nxn_sum_u16, ".vcop_parameter_block")
#pragma DATA_ALIGN(__pblock_vcop_nxn_sum_u16, __ALIGNOF__(int));
unsigned short __pblock_vcop_nxn_sum_u16[66];

unsigned int vcop_nxn_sum_u16_param_count(void)
{
   return 66u;
}

unsigned int vcop_nxn_sum_u16_ctrl_count(void)
{
   return 0u;
}

unsigned int vcop_nxn_sum_u16_init(
   __vptr_uint16 inPtr1,
   __vptr_uint16 inPtr2,
   __vptr_uint16 outPtr1,
   __vptr_uint16 outPtr2,
   __vptr_uint32 tempPtr1,
   __vptr_uint32 tempPtr2,
   unsigned short n,
   unsigned short width,
   unsigned short height,
   unsigned short pitch1,
   unsigned short pitch2,
   unsigned short pblock[])
{
   int __offset = 0;
   /* Loop 1 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), ((((height + (((8u)*n)-1)) / ((8u)*n)) * ((8u)*n))/((8u)*n))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), ((((width + ((8u)-1)) / (8u)) * (8u))/((8u)))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), ((8u))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), (n)-1u);
   __vcop_pblock_init32(pblock, __offset+_PREG(6), (uchar *)inPtr2);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)tempPtr1);
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)tempPtr2);
   __vcop_pblock_init16(pblock, __offset+_PREG(12), (pitch1*2));
   __vcop_pblock_init16(pblock, __offset+_PREG(13), (pitch1*2*n) -(pitch1*2)*((n)-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(14), (2*8u) -(pitch1*2*n)*(((8u))-1u) -(pitch1*2)*((n)-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(15), (pitch1*2*8u*n) -(2*8u)*(((((width + ((8u)-1)) / (8u)) * (8u))/((8u)))-1u) -(pitch1*2*n)*(((8u))-1u) -(pitch1*2)*((n)-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(16), 4);
   __vcop_pblock_init16(pblock, __offset+_PREG(17), 260);
   __vcop_pblock_init16(pblock, __offset+_PREG(18), ((width/8u)*((8u+1)*4*8u)) -(((8u+1)*4*8u))*(((((width + ((8u)-1)) / (8u)) * (8u))/((8u)))-1u) -(4)*(((8u))-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(19), (pitch2*2));
   __vcop_pblock_init16(pblock, __offset+_PREG(20), (pitch2*2*n) -(pitch2*2)*((n)-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(21), (2*8u) -(pitch2*2*n)*(((8u))-1u) -(pitch2*2)*((n)-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(22), (pitch2*2*8u*n) -(2*8u)*(((((width + ((8u)-1)) / (8u)) * (8u))/((8u)))-1u) -(pitch2*2*n)*(((8u))-1u) -(pitch2*2)*((n)-1u));
   __vcop_pblock_init32(pblock, __offset+_PREG(24), 0);
   __vcop_pblock_init32(pblock, __offset+_PREG(26), (uchar *)inPtr1);
   __offset += 26;

   /* Loop 2 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), ((((height + (((8u)*n)-1)) / ((8u)*n)) * ((8u)*n))/((8u)*n))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), ((((width + (((8u)*n)-1)) / ((8u)*n)) * ((8u)*n))/((8u)*n))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), ((8u))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), (n)-1u);
   __vcop_pblock_init32(pblock, __offset+_PREG(6), (uchar *)tempPtr2);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)tempPtr1+(width+(8u-1))/8u*8u/8u*((height+(8u*n-1))/(8u*n)*(8u*n)/(8u*n)*((8u+1)*4*8u)));
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)tempPtr2+(width+(8u-1))/8u*8u/8u*((height+(8u*n-1))/(8u*n)*(8u*n)/(8u*n)*((8u+1)*4*8u)));
   __vcop_pblock_init16(pblock, __offset+_PREG(12), 36);
   __vcop_pblock_init16(pblock, __offset+_PREG(13), (((8u+1)*4)*n) -(((8u+1)*4))*((n)-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(14), (((8u+1)*4)*8u*n) -(((8u+1)*4)*n)*(((8u))-1u) -(((8u+1)*4))*((n)-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(15), ((width/8u)*((8u+1)*4*8u)) -(((8u+1)*4)*8u*n)*(((((width + (((8u)*n)-1)) / ((8u)*n)) * ((8u)*n))/((8u)*n))-1u) -(((8u+1)*4)*n)*(((8u))-1u) -(((8u+1)*4))*((n)-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(16), 4);
   __vcop_pblock_init16(pblock, __offset+_PREG(17), 260);
   __vcop_pblock_init16(pblock, __offset+_PREG(18), ((width/8u/n)*((8u+1)*4*8u)) -(((8u+1)*4*8u))*(((((width + (((8u)*n)-1)) / ((8u)*n)) * ((8u)*n))/((8u)*n))-1u) -(4)*(((8u))-1u));
   __vcop_pblock_init32(pblock, __offset+_PREG(20), 0);
   __vcop_pblock_init32(pblock, __offset+_PREG(22), (uchar *)tempPtr1);
   __offset += 22;

   /* Loop 3 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), ((((height + (((8u)*n)-1)) / ((8u)*n)) * ((8u)*n))/((8u)*n))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), ((((width + (((8u)*n)-1)) / ((8u)*n)) * ((8u)*n))/((8u)*n))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), ((8u))-1u);
   __vcop_pblock_init32(pblock, __offset+_PREG(6), (uchar *)outPtr1);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)outPtr2);
   __vcop_pblock_init16(pblock, __offset+_PREG(10), (sizeof(*outPtr2)*(width/n)));
   __vcop_pblock_init16(pblock, __offset+_PREG(11), (8u*sizeof(*outPtr2)) -(sizeof(*outPtr2)*(width/n))*(((8u))-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(12), (sizeof(*outPtr2)*(width/n)*8u) -(8u*sizeof(*outPtr2))*(((((width + (((8u)*n)-1)) / ((8u)*n)) * ((8u)*n))/((8u)*n))-1u) -(sizeof(*outPtr2)*(width/n))*(((8u))-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(13), 36);
   __vcop_pblock_init16(pblock, __offset+_PREG(14), ((width/n/8u)*((8u+1)*4*8u)) -(((8u+1)*4*8u))*(((((width + (((8u)*n)-1)) / ((8u)*n)) * ((8u)*n))/((8u)*n))-1u) -(((8u+1)*4))*(((8u))-1u));
   __vcop_pblock_init32(pblock, __offset+_PREG(16), (uchar *)tempPtr1+(width+(8u-1))/8u*8u/8u*((height+(8u*n-1))/(8u*n)*(8u*n)/(8u*n)*((8u+1)*4*8u)));
   __vcop_pblock_init32(pblock, __offset+_PREG(18), (uchar *)tempPtr2+(width+(8u-1))/8u*8u/8u*((height+(8u*n-1))/(8u*n)*(8u*n)/(8u*n)*((8u+1)*4*8u)));
   __offset += 18;

   return 66u;
}

void vcop_nxn_sum_u16_vloops(
   unsigned short pblock[])
{
   /* Kernel-wide Vector Registers */
   #pragma VCC_VREG("vin1", 16);
   #pragma VCC_VREG("vin2", 17);
   #pragma VCC_VREG("vsum1", 18);
   #pragma VCC_VREG("vsum2", 19);

   __vcop_param(&pblock[0]);

   /* VLOOP 1 Start */

   /* VLOOP Local Vector Registers */
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("Addr1", "A0");
   #pragma EVE_REG("Addr2", "A1");
   #pragma EVE_REG("Addr3", "A2");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I1", "I1");
   #pragma EVE_REG("I2", "I2");
   #pragma EVE_REG("I3", "I3");
   #pragma EVE_REG("I4", "I4");
   

   __vcop_vloop(__vcop_compute(), 12u, 13u, 1u);
   __vcop_vinit(__vcop_sizeW(), __vcop_i4_zero(), _PREG(24), _VREG(18));
   __vcop_vinit(__vcop_sizeW(), __vcop_i4_zero(), _PREG(24), _VREG(19));
   __vcop_vagen(_AGEN(0), _PREG(12), _PREG(13), _PREG(14), _PREG(15));
   __vcop_vagen(_AGEN(1), _PREG(0), _PREG(16), _PREG(17), _PREG(18));
   __vcop_vagen(_AGEN(2), _PREG(19), _PREG(20), _PREG(21), _PREG(22));
   __vcop_vload(__vcop_sizeHU(), __vcop_npt(), _PREG(26), _AGEN(0), _VREG(16), __vcop_alws());
   __vcop_vload(__vcop_sizeHU(), __vcop_npt(), _PREG(6), _AGEN(2), _VREG(17), __vcop_alws());
   __vcop_vadd(_VREG(18), _VREG(16), _VREG(18));
   __vcop_vadd(_VREG(19), _VREG(17), _VREG(19));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeWU(), __vcop_offst_np1(), __vcop_last_i4(), _VREG(18), _PREG(8), _AGEN(1), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeWU(), __vcop_offst_np1(), __vcop_last_i4(), _VREG(19), _PREG(10), _AGEN(1), _PREG(0));
   __vcop_vloop_end(1u);

   /* VLOOP 2 Start */

   /* VLOOP Local Vector Registers */
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("Addr1", "A0");
   #pragma EVE_REG("Addr2", "A1");
   #pragma EVE_REG("Addr3", "A2");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I1", "I1");
   #pragma EVE_REG("I2", "I2");
   #pragma EVE_REG("I3", "I3");
   #pragma EVE_REG("I4", "I4");
   

   __vcop_vloop(__vcop_compute(), 12u, 11u, 2u);
   __vcop_vinit(__vcop_sizeW(), __vcop_i4_zero(), _PREG(20), _VREG(18));
   __vcop_vinit(__vcop_sizeW(), __vcop_i4_zero(), _PREG(20), _VREG(19));
   __vcop_vagen(_AGEN(0), _PREG(12), _PREG(13), _PREG(14), _PREG(15));
   __vcop_vagen(_AGEN(1), _PREG(0), _PREG(16), _PREG(17), _PREG(18));
   __vcop_vload(__vcop_sizeWU(), __vcop_npt(), _PREG(22), _AGEN(0), _VREG(16), __vcop_alws());
   __vcop_vload(__vcop_sizeWU(), __vcop_npt(), _PREG(6), _AGEN(0), _VREG(17), __vcop_alws());
   __vcop_vadd(_VREG(18), _VREG(16), _VREG(18));
   __vcop_vadd(_VREG(19), _VREG(17), _VREG(19));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeWU(), __vcop_offst_np1(), __vcop_last_i4(), _VREG(18), _PREG(8), _AGEN(1), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeWU(), __vcop_offst_np1(), __vcop_last_i4(), _VREG(19), _PREG(10), _AGEN(1), _PREG(0));
   __vcop_vloop_end(2u);

   /* VLOOP 3 Start */

   /* VLOOP Local Vector Registers */
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("Addr1", "A0");
   #pragma EVE_REG("Addr2", "A1");
   #pragma EVE_REG("Addr3", "A2");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I1", "I2");
   #pragma EVE_REG("I2", "I3");
   #pragma EVE_REG("I3", "I4");
   

   __vcop_vloop(__vcop_compute(), 8u, 9u, 3u);
   __vcop_vagen(_AGEN(0), _PREG(10), _PREG(11), _PREG(12), _PREG(0));
   __vcop_vagen(_AGEN(1), _PREG(13), _PREG(13), _PREG(14), _PREG(0));
   __vcop_vload(__vcop_sizeWU(), __vcop_npt(), _PREG(16), _AGEN(1), _VREG(16), __vcop_alws());
   __vcop_vload(__vcop_sizeWU(), __vcop_npt(), _PREG(18), _AGEN(1), _VREG(17), __vcop_alws());
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeHU(), __vcop_npt(), __vcop_alws(), _VREG(16), _PREG(6), _AGEN(0), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeHU(), __vcop_npt(), __vcop_alws(), _VREG(17), _PREG(8), _AGEN(0), _PREG(0));
   __vcop_vloop_end(3u);

}

void vcop_nxn_sum_u16(
   __vptr_uint16 inPtr1,
   __vptr_uint16 inPtr2,
   __vptr_uint16 outPtr1,
   __vptr_uint16 outPtr2,
   __vptr_uint32 tempPtr1,
   __vptr_uint32 tempPtr2,
   unsigned short n,
   unsigned short width,
   unsigned short height,
   unsigned short pitch1,
   unsigned short pitch2)
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_nxn_sum_u16_init(inPtr1, inPtr2, outPtr1, outPtr2, tempPtr1, tempPtr2, n, width, height, pitch1, pitch2, __pblock_vcop_nxn_sum_u16);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_nxn_sum_u16_vloops(__pblock_vcop_nxn_sum_u16);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

void vcop_nxn_sum_u16_custom(
   __vptr_uint16 inPtr1,
   __vptr_uint16 inPtr2,
   __vptr_uint16 outPtr1,
   __vptr_uint16 outPtr2,
   __vptr_uint32 tempPtr1,
   __vptr_uint32 tempPtr2,
   unsigned short n,
   unsigned short width,
   unsigned short height,
   unsigned short pitch1,
   unsigned short pitch2,
   unsigned short pblock[])
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_nxn_sum_u16_init(inPtr1, inPtr2, outPtr1, outPtr2, tempPtr1, tempPtr2, n, width, height, pitch1, pitch2, pblock);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_nxn_sum_u16_vloops(pblock);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

#pragma DATA_SECTION(__pblock_vcop_nxn_sum_u8_u16, ".vcop_parameter_block")
#pragma DATA_ALIGN(__pblock_vcop_nxn_sum_u8_u16, __ALIGNOF__(int));
unsigned short __pblock_vcop_nxn_sum_u8_u16[66];

unsigned int vcop_nxn_sum_u8_u16_param_count(void)
{
   return 66u;
}

unsigned int vcop_nxn_sum_u8_u16_ctrl_count(void)
{
   return 0u;
}

unsigned int vcop_nxn_sum_u8_u16_init(
   __vptr_uint8 inPtr1,
   __vptr_uint16 inPtr2,
   __vptr_uint16 outPtr1,
   __vptr_uint16 outPtr2,
   __vptr_uint32 tempPtr1,
   __vptr_uint32 tempPtr2,
   unsigned short n,
   unsigned short width,
   unsigned short height,
   unsigned short pitch1,
   unsigned short pitch2,
   unsigned short pblock[])
{
   int __offset = 0;
   /* Loop 1 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), ((((height + (((8u)*n)-1)) / ((8u)*n)) * ((8u)*n))/((8u)*n))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), ((((width + ((8u)-1)) / (8u)) * (8u))/((8u)))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), ((8u))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), (n)-1u);
   __vcop_pblock_init32(pblock, __offset+_PREG(6), (uchar *)inPtr2);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)tempPtr1);
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)tempPtr2);
   __vcop_pblock_init16(pblock, __offset+_PREG(12), (pitch1*1));
   __vcop_pblock_init16(pblock, __offset+_PREG(13), (pitch1*1*n) -(pitch1*1)*((n)-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(14), (8u) -(pitch1*1*n)*(((8u))-1u) -(pitch1*1)*((n)-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(15), (pitch1*1*8u*n) -(8u)*(((((width + ((8u)-1)) / (8u)) * (8u))/((8u)))-1u) -(pitch1*1*n)*(((8u))-1u) -(pitch1*1)*((n)-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(16), 4);
   __vcop_pblock_init16(pblock, __offset+_PREG(17), 260);
   __vcop_pblock_init16(pblock, __offset+_PREG(18), ((width/8u)*((8u+1)*4*8u)) -(((8u+1)*4*8u))*(((((width + ((8u)-1)) / (8u)) * (8u))/((8u)))-1u) -(4)*(((8u))-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(19), (pitch2*2));
   __vcop_pblock_init16(pblock, __offset+_PREG(20), (pitch2*2*n) -(pitch2*2)*((n)-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(21), (2*8u) -(pitch2*2*n)*(((8u))-1u) -(pitch2*2)*((n)-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(22), (pitch2*2*8u*n) -(2*8u)*(((((width + ((8u)-1)) / (8u)) * (8u))/((8u)))-1u) -(pitch2*2*n)*(((8u))-1u) -(pitch2*2)*((n)-1u));
   __vcop_pblock_init32(pblock, __offset+_PREG(24), 0);
   __vcop_pblock_init32(pblock, __offset+_PREG(26), (uchar *)inPtr1);
   __offset += 26;

   /* Loop 2 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), ((((height + (((8u)*n)-1)) / ((8u)*n)) * ((8u)*n))/((8u)*n))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), ((((width + (((8u)*n)-1)) / ((8u)*n)) * ((8u)*n))/((8u)*n))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), ((8u))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), (n)-1u);
   __vcop_pblock_init32(pblock, __offset+_PREG(6), (uchar *)tempPtr2);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)tempPtr1+(width+(8u-1))/8u*8u/8u*((height+(8u*n-1))/(8u*n)*(8u*n)/(8u*n)*((8u+1)*4*8u)));
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)tempPtr2+(width+(8u-1))/8u*8u/8u*((height+(8u*n-1))/(8u*n)*(8u*n)/(8u*n)*((8u+1)*4*8u)));
   __vcop_pblock_init16(pblock, __offset+_PREG(12), 36);
   __vcop_pblock_init16(pblock, __offset+_PREG(13), (((8u+1)*4)*n) -(((8u+1)*4))*((n)-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(14), (((8u+1)*4)*8u*n) -(((8u+1)*4)*n)*(((8u))-1u) -(((8u+1)*4))*((n)-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(15), ((width/8u)*((8u+1)*4*8u)) -(((8u+1)*4)*8u*n)*(((((width + (((8u)*n)-1)) / ((8u)*n)) * ((8u)*n))/((8u)*n))-1u) -(((8u+1)*4)*n)*(((8u))-1u) -(((8u+1)*4))*((n)-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(16), 4);
   __vcop_pblock_init16(pblock, __offset+_PREG(17), 260);
   __vcop_pblock_init16(pblock, __offset+_PREG(18), ((width/8u/n)*((8u+1)*4*8u)) -(((8u+1)*4*8u))*(((((width + (((8u)*n)-1)) / ((8u)*n)) * ((8u)*n))/((8u)*n))-1u) -(4)*(((8u))-1u));
   __vcop_pblock_init32(pblock, __offset+_PREG(20), 0);
   __vcop_pblock_init32(pblock, __offset+_PREG(22), (uchar *)tempPtr1);
   __offset += 22;

   /* Loop 3 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), ((((height + (((8u)*n)-1)) / ((8u)*n)) * ((8u)*n))/((8u)*n))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), ((((width + (((8u)*n)-1)) / ((8u)*n)) * ((8u)*n))/((8u)*n))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), ((8u))-1u);
   __vcop_pblock_init32(pblock, __offset+_PREG(6), (uchar *)outPtr1);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)outPtr2);
   __vcop_pblock_init16(pblock, __offset+_PREG(10), (sizeof(*outPtr2)*(width/n)));
   __vcop_pblock_init16(pblock, __offset+_PREG(11), (8u*sizeof(*outPtr2)) -(sizeof(*outPtr2)*(width/n))*(((8u))-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(12), (sizeof(*outPtr2)*(width/n)*8u) -(8u*sizeof(*outPtr2))*(((((width + (((8u)*n)-1)) / ((8u)*n)) * ((8u)*n))/((8u)*n))-1u) -(sizeof(*outPtr2)*(width/n))*(((8u))-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(13), 36);
   __vcop_pblock_init16(pblock, __offset+_PREG(14), ((width/n/8u)*((8u+1)*4*8u)) -(((8u+1)*4*8u))*(((((width + (((8u)*n)-1)) / ((8u)*n)) * ((8u)*n))/((8u)*n))-1u) -(((8u+1)*4))*(((8u))-1u));
   __vcop_pblock_init32(pblock, __offset+_PREG(16), (uchar *)tempPtr1+(width+(8u-1))/8u*8u/8u*((height+(8u*n-1))/(8u*n)*(8u*n)/(8u*n)*((8u+1)*4*8u)));
   __vcop_pblock_init32(pblock, __offset+_PREG(18), (uchar *)tempPtr2+(width+(8u-1))/8u*8u/8u*((height+(8u*n-1))/(8u*n)*(8u*n)/(8u*n)*((8u+1)*4*8u)));
   __offset += 18;

   return 66u;
}

void vcop_nxn_sum_u8_u16_vloops(
   unsigned short pblock[])
{
   /* Kernel-wide Vector Registers */
   #pragma VCC_VREG("vin1", 16);
   #pragma VCC_VREG("vin2", 17);
   #pragma VCC_VREG("vsum1", 18);
   #pragma VCC_VREG("vsum2", 19);

   __vcop_param(&pblock[0]);

   /* VLOOP 1 Start */

   /* VLOOP Local Vector Registers */
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("Addr1", "A0");
   #pragma EVE_REG("Addr2", "A1");
   #pragma EVE_REG("Addr3", "A2");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I1", "I1");
   #pragma EVE_REG("I2", "I2");
   #pragma EVE_REG("I3", "I3");
   #pragma EVE_REG("I4", "I4");
   

   __vcop_vloop(__vcop_compute(), 12u, 13u, 1u);
   __vcop_vinit(__vcop_sizeW(), __vcop_i4_zero(), _PREG(24), _VREG(18));
   __vcop_vinit(__vcop_sizeW(), __vcop_i4_zero(), _PREG(24), _VREG(19));
   __vcop_vagen(_AGEN(0), _PREG(12), _PREG(13), _PREG(14), _PREG(15));
   __vcop_vagen(_AGEN(1), _PREG(0), _PREG(16), _PREG(17), _PREG(18));
   __vcop_vagen(_AGEN(2), _PREG(19), _PREG(20), _PREG(21), _PREG(22));
   __vcop_vload(__vcop_sizeBU(), __vcop_npt(), _PREG(26), _AGEN(0), _VREG(16), __vcop_alws());
   __vcop_vload(__vcop_sizeHU(), __vcop_npt(), _PREG(6), _AGEN(2), _VREG(17), __vcop_alws());
   __vcop_vadd(_VREG(18), _VREG(16), _VREG(18));
   __vcop_vadd(_VREG(19), _VREG(17), _VREG(19));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeWU(), __vcop_offst_np1(), __vcop_last_i4(), _VREG(18), _PREG(8), _AGEN(1), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeWU(), __vcop_offst_np1(), __vcop_last_i4(), _VREG(19), _PREG(10), _AGEN(1), _PREG(0));
   __vcop_vloop_end(1u);

   /* VLOOP 2 Start */

   /* VLOOP Local Vector Registers */
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("Addr1", "A0");
   #pragma EVE_REG("Addr2", "A1");
   #pragma EVE_REG("Addr3", "A2");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I1", "I1");
   #pragma EVE_REG("I2", "I2");
   #pragma EVE_REG("I3", "I3");
   #pragma EVE_REG("I4", "I4");
   

   __vcop_vloop(__vcop_compute(), 12u, 11u, 2u);
   __vcop_vinit(__vcop_sizeW(), __vcop_i4_zero(), _PREG(20), _VREG(18));
   __vcop_vinit(__vcop_sizeW(), __vcop_i4_zero(), _PREG(20), _VREG(19));
   __vcop_vagen(_AGEN(0), _PREG(12), _PREG(13), _PREG(14), _PREG(15));
   __vcop_vagen(_AGEN(1), _PREG(0), _PREG(16), _PREG(17), _PREG(18));
   __vcop_vload(__vcop_sizeWU(), __vcop_npt(), _PREG(22), _AGEN(0), _VREG(16), __vcop_alws());
   __vcop_vload(__vcop_sizeWU(), __vcop_npt(), _PREG(6), _AGEN(0), _VREG(17), __vcop_alws());
   __vcop_vadd(_VREG(18), _VREG(16), _VREG(18));
   __vcop_vadd(_VREG(19), _VREG(17), _VREG(19));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeWU(), __vcop_offst_np1(), __vcop_last_i4(), _VREG(18), _PREG(8), _AGEN(1), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeWU(), __vcop_offst_np1(), __vcop_last_i4(), _VREG(19), _PREG(10), _AGEN(1), _PREG(0));
   __vcop_vloop_end(2u);

   /* VLOOP 3 Start */

   /* VLOOP Local Vector Registers */
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("Addr1", "A0");
   #pragma EVE_REG("Addr2", "A1");
   #pragma EVE_REG("Addr3", "A2");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I1", "I2");
   #pragma EVE_REG("I2", "I3");
   #pragma EVE_REG("I3", "I4");
   

   __vcop_vloop(__vcop_compute(), 8u, 9u, 3u);
   __vcop_vagen(_AGEN(0), _PREG(10), _PREG(11), _PREG(12), _PREG(0));
   __vcop_vagen(_AGEN(1), _PREG(13), _PREG(13), _PREG(14), _PREG(0));
   __vcop_vload(__vcop_sizeWU(), __vcop_npt(), _PREG(16), _AGEN(1), _VREG(16), __vcop_alws());
   __vcop_vload(__vcop_sizeWU(), __vcop_npt(), _PREG(18), _AGEN(1), _VREG(17), __vcop_alws());
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeHU(), __vcop_npt(), __vcop_alws(), _VREG(16), _PREG(6), _AGEN(0), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeHU(), __vcop_npt(), __vcop_alws(), _VREG(17), _PREG(8), _AGEN(0), _PREG(0));
   __vcop_vloop_end(3u);

}

void vcop_nxn_sum_u8_u16(
   __vptr_uint8 inPtr1,
   __vptr_uint16 inPtr2,
   __vptr_uint16 outPtr1,
   __vptr_uint16 outPtr2,
   __vptr_uint32 tempPtr1,
   __vptr_uint32 tempPtr2,
   unsigned short n,
   unsigned short width,
   unsigned short height,
   unsigned short pitch1,
   unsigned short pitch2)
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_nxn_sum_u8_u16_init(inPtr1, inPtr2, outPtr1, outPtr2, tempPtr1, tempPtr2, n, width, height, pitch1, pitch2, __pblock_vcop_nxn_sum_u8_u16);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_nxn_sum_u8_u16_vloops(__pblock_vcop_nxn_sum_u8_u16);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

void vcop_nxn_sum_u8_u16_custom(
   __vptr_uint8 inPtr1,
   __vptr_uint16 inPtr2,
   __vptr_uint16 outPtr1,
   __vptr_uint16 outPtr2,
   __vptr_uint32 tempPtr1,
   __vptr_uint32 tempPtr2,
   unsigned short n,
   unsigned short width,
   unsigned short height,
   unsigned short pitch1,
   unsigned short pitch2,
   unsigned short pblock[])
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_nxn_sum_u8_u16_init(inPtr1, inPtr2, outPtr1, outPtr2, tempPtr1, tempPtr2, n, width, height, pitch1, pitch2, pblock);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_nxn_sum_u8_u16_vloops(pblock);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

