#include <vcop\vcop.h>

typedef unsigned char uchar;

#pragma DATA_SECTION(__pblock_vcop_fast9, ".vcop_parameter_block")
#pragma DATA_ALIGN(__pblock_vcop_fast9, __ALIGNOF__(int));
unsigned short __pblock_vcop_fast9[184];

unsigned int vcop_fast9_param_count(void)
{
   return 184u;
}

unsigned int vcop_fast9_ctrl_count(void)
{
   return 0u;
}

unsigned int vcop_fast9_init(
   __vptr_uint8 vec1,
   __vptr_uint8 out_0_ptr,
   __vptr_uint8 out_1_ptr,
   __vptr_uint16 out_4_ptr,
   __vptr_uint8 Out,
   signed char Thr,
   unsigned int pitch,
   unsigned int in_w,
   unsigned int in_h,
   unsigned short pblock[])
{
   int __offset = 0;
   /* Loop 1 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), (((in_h-6)))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), ((((in_w-6))+(8u)-1)/(8u))-1u);
   __vcop_pblock_init32(pblock, __offset+_PREG(6), (uchar *)vec1+3*pitch+3);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)vec1+3);
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)vec1+4);
   __vcop_pblock_init32(pblock, __offset+_PREG(12), (uchar *)vec1+pitch+5);
   __vcop_pblock_init32(pblock, __offset+_PREG(14), (uchar *)vec1+2*pitch+6);
   __vcop_pblock_init32(pblock, __offset+_PREG(16), (uchar *)out_0_ptr);
   __vcop_pblock_init32(pblock, __offset+_PREG(18), (uchar *)out_0_ptr+sizeof(*out_0_ptr));
   __vcop_pblock_init32(pblock, __offset+_PREG(20), (uchar *)out_0_ptr+2*sizeof(*out_0_ptr));
   __vcop_pblock_init32(pblock, __offset+_PREG(22), (uchar *)out_0_ptr+3*sizeof(*out_0_ptr));
   __vcop_pblock_init32(pblock, __offset+_PREG(24), (uchar *)out_1_ptr);
   __vcop_pblock_init32(pblock, __offset+_PREG(26), (uchar *)out_1_ptr+sizeof(*out_0_ptr));
   __vcop_pblock_init32(pblock, __offset+_PREG(28), (uchar *)out_1_ptr+2*sizeof(*out_0_ptr));
   __vcop_pblock_init32(pblock, __offset+_PREG(30), (uchar *)out_1_ptr+3*sizeof(*out_0_ptr));
   __vcop_pblock_init16(pblock, __offset+_PREG(32), 8);
   __vcop_pblock_init16(pblock, __offset+_PREG(33), (pitch*sizeof(*vec1)) -(8u*sizeof(*vec1))*(((((in_w-6))+(8u)-1)/(8u))-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(34), ((in_w-6)*sizeof(*out_0_ptr)) -(8u*sizeof(*out_0_ptr))*(((((in_w-6))+(8u)-1)/(8u))-1u));
   __vcop_pblock_init32(pblock, __offset+_PREG(36), Thr);
   __vcop_pblock_init32(pblock, __offset+_PREG(38), -Thr);
   __offset += 38;

   /* Loop 2 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), (((in_h-6)))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), ((((in_w-6))+(8u)-1)/(8u))-1u);
   __vcop_pblock_init32(pblock, __offset+_PREG(6), (uchar *)vec1+4*pitch+6);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)vec1+5*pitch+5);
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)vec1+6*pitch+4);
   __vcop_pblock_init32(pblock, __offset+_PREG(12), (uchar *)out_0_ptr+8u*sizeof(*out_0_ptr)/2);
   __vcop_pblock_init32(pblock, __offset+_PREG(14), (uchar *)out_0_ptr+8u*sizeof(*out_0_ptr)/2+sizeof(*out_0_ptr));
   __vcop_pblock_init32(pblock, __offset+_PREG(16), (uchar *)out_0_ptr+8u*sizeof(*out_0_ptr)/2+2*sizeof(*out_0_ptr));
   __vcop_pblock_init32(pblock, __offset+_PREG(18), (uchar *)out_0_ptr+8u*sizeof(*out_0_ptr)/2+3*sizeof(*out_0_ptr));
   __vcop_pblock_init32(pblock, __offset+_PREG(20), (uchar *)out_1_ptr+8u*sizeof(*out_0_ptr)/2);
   __vcop_pblock_init32(pblock, __offset+_PREG(22), (uchar *)out_1_ptr+8u*sizeof(*out_0_ptr)/2+sizeof(*out_0_ptr));
   __vcop_pblock_init32(pblock, __offset+_PREG(24), (uchar *)out_1_ptr+8u*sizeof(*out_0_ptr)/2+2*sizeof(*out_0_ptr));
   __vcop_pblock_init32(pblock, __offset+_PREG(26), (uchar *)out_1_ptr+8u*sizeof(*out_0_ptr)/2+3*sizeof(*out_0_ptr));
   __vcop_pblock_init16(pblock, __offset+_PREG(28), 8);
   __vcop_pblock_init16(pblock, __offset+_PREG(29), (pitch*sizeof(*vec1)) -(8u*sizeof(*vec1))*(((((in_w-6))+(8u)-1)/(8u))-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(30), ((in_w-6)*sizeof(*out_0_ptr)) -(8u*sizeof(*out_0_ptr))*(((((in_w-6))+(8u)-1)/(8u))-1u));
   __vcop_pblock_init32(pblock, __offset+_PREG(32), (uchar *)vec1+3*pitch+3);
   __vcop_pblock_init32(pblock, __offset+_PREG(34), (uchar *)vec1+3*pitch+6);
   __offset += 34;

   /* Loop 3 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), (((in_h-6)))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), ((((in_w-6))+(8u)-1)/(8u))-1u);
   __vcop_pblock_init32(pblock, __offset+_PREG(6), (uchar *)vec1+6*pitch+2);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)vec1+5*pitch+1);
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)vec1+4*pitch);
   __vcop_pblock_init32(pblock, __offset+_PREG(12), (uchar *)out_0_ptr+(in_w-6)*(in_h-6)*sizeof(*out_0_ptr));
   __vcop_pblock_init32(pblock, __offset+_PREG(14), (uchar *)out_0_ptr+(in_w-6)*(in_h-6)*sizeof(*out_0_ptr)+sizeof(*out_0_ptr));
   __vcop_pblock_init32(pblock, __offset+_PREG(16), (uchar *)out_0_ptr+(in_w-6)*(in_h-6)*sizeof(*out_0_ptr)+2*sizeof(*out_0_ptr));
   __vcop_pblock_init32(pblock, __offset+_PREG(18), (uchar *)out_0_ptr+(in_w-6)*(in_h-6)*sizeof(*out_0_ptr)+3*sizeof(*out_0_ptr));
   __vcop_pblock_init32(pblock, __offset+_PREG(20), (uchar *)out_1_ptr+(in_w-6)*(in_h-6)*sizeof(*out_1_ptr));
   __vcop_pblock_init32(pblock, __offset+_PREG(22), (uchar *)out_1_ptr+(in_w-6)*(in_h-6)*sizeof(*out_1_ptr)+sizeof(*out_0_ptr));
   __vcop_pblock_init32(pblock, __offset+_PREG(24), (uchar *)out_1_ptr+(in_w-6)*(in_h-6)*sizeof(*out_1_ptr)+2*sizeof(*out_0_ptr));
   __vcop_pblock_init32(pblock, __offset+_PREG(26), (uchar *)out_1_ptr+(in_w-6)*(in_h-6)*sizeof(*out_1_ptr)+3*sizeof(*out_0_ptr));
   __vcop_pblock_init16(pblock, __offset+_PREG(28), 8);
   __vcop_pblock_init16(pblock, __offset+_PREG(29), (pitch*sizeof(*vec1)) -(8u*sizeof(*vec1))*(((((in_w-6))+(8u)-1)/(8u))-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(30), ((in_w-6)*sizeof(*out_0_ptr)) -(8u*sizeof(*out_0_ptr))*(((((in_w-6))+(8u)-1)/(8u))-1u));
   __vcop_pblock_init32(pblock, __offset+_PREG(32), (uchar *)vec1+3*pitch+3);
   __vcop_pblock_init32(pblock, __offset+_PREG(34), (uchar *)vec1+6*pitch+3);
   __offset += 34;

   /* Loop 4 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), (((in_h-6)))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), ((((in_w-6))+(8u)-1)/(8u))-1u);
   __vcop_pblock_init32(pblock, __offset+_PREG(6), (uchar *)vec1+2*pitch);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)vec1+pitch+1);
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)vec1+2);
   __vcop_pblock_init32(pblock, __offset+_PREG(12), (uchar *)out_0_ptr+(in_w-6)*(in_h-6)*sizeof(*out_0_ptr)+8u*sizeof(*out_0_ptr)/2);
   __vcop_pblock_init32(pblock, __offset+_PREG(14), (uchar *)out_0_ptr+(in_w-6)*(in_h-6)*sizeof(*out_0_ptr)+8u*sizeof(*out_0_ptr)/2+sizeof(*out_0_ptr));
   __vcop_pblock_init32(pblock, __offset+_PREG(16), (uchar *)out_0_ptr+(in_w-6)*(in_h-6)*sizeof(*out_0_ptr)+8u*sizeof(*out_0_ptr)/2+2*sizeof(*out_0_ptr));
   __vcop_pblock_init32(pblock, __offset+_PREG(18), (uchar *)out_0_ptr+(in_w-6)*(in_h-6)*sizeof(*out_0_ptr)+8u*sizeof(*out_0_ptr)/2+3*sizeof(*out_0_ptr));
   __vcop_pblock_init32(pblock, __offset+_PREG(20), (uchar *)out_1_ptr+(in_w-6)*(in_h-6)*sizeof(*out_1_ptr)+8u*sizeof(*out_0_ptr)/2);
   __vcop_pblock_init32(pblock, __offset+_PREG(22), (uchar *)out_1_ptr+(in_w-6)*(in_h-6)*sizeof(*out_1_ptr)+8u*sizeof(*out_0_ptr)/2+sizeof(*out_0_ptr));
   __vcop_pblock_init32(pblock, __offset+_PREG(24), (uchar *)out_1_ptr+(in_w-6)*(in_h-6)*sizeof(*out_1_ptr)+8u*sizeof(*out_0_ptr)/2+2*sizeof(*out_0_ptr));
   __vcop_pblock_init32(pblock, __offset+_PREG(26), (uchar *)out_1_ptr+(in_w-6)*(in_h-6)*sizeof(*out_1_ptr)+8u*sizeof(*out_0_ptr)/2+3*sizeof(*out_0_ptr));
   __vcop_pblock_init16(pblock, __offset+_PREG(28), 8);
   __vcop_pblock_init16(pblock, __offset+_PREG(29), (pitch*sizeof(*vec1)) -(8u*sizeof(*vec1))*(((((in_w-6))+(8u)-1)/(8u))-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(30), ((in_w-6)*sizeof(*out_0_ptr)) -(8u*sizeof(*out_0_ptr))*(((((in_w-6))+(8u)-1)/(8u))-1u));
   __vcop_pblock_init32(pblock, __offset+_PREG(32), (uchar *)vec1+3*pitch+3);
   __vcop_pblock_init32(pblock, __offset+_PREG(34), (uchar *)vec1+3*pitch);
   __offset += 34;

   /* Loop 5 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), (((in_h-6)))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), ((((in_w-6))+(8u)-1)/(8u))-1u);
   __vcop_pblock_init32(pblock, __offset+_PREG(6), (uchar *)out_1_ptr);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)out_0_ptr+(in_w-6)*(in_h-6));
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)out_1_ptr+(in_w-6)*(in_h-6));
   __vcop_pblock_init32(pblock, __offset+_PREG(12), (uchar *)out_4_ptr);
   __vcop_pblock_init32(pblock, __offset+_PREG(14), (uchar *)out_4_ptr+(in_w-6)*(in_h-6)*sizeof(*out_4_ptr));
   __vcop_pblock_init16(pblock, __offset+_PREG(16), 8);
   __vcop_pblock_init16(pblock, __offset+_PREG(17), ((in_w-6)*sizeof(*out_0_ptr)) -(8u*sizeof(*out_0_ptr))*(((((in_w-6))+(8u)-1)/(8u))-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(18), 16);
   __vcop_pblock_init16(pblock, __offset+_PREG(19), ((in_w-6)*sizeof(*out_4_ptr)) -(8u*sizeof(*out_4_ptr))*(((((in_w-6))+(8u)-1)/(8u))-1u));
   __vcop_pblock_init32(pblock, __offset+_PREG(20), 8);
   __vcop_pblock_init32(pblock, __offset+_PREG(22), (uchar *)out_0_ptr);
   __offset += 22;

   /* Loop 6 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), (((in_h-6)))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), ((((in_w-6))+(8u)-1)/(8u))-1u);
   __vcop_pblock_init32(pblock, __offset+_PREG(6), 2);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), 1);
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)out_4_ptr);
   __vcop_pblock_init32(pblock, __offset+_PREG(12), (uchar *)out_4_ptr+(in_w-6)*(in_h-6)*sizeof(*out_4_ptr));
   __vcop_pblock_init32(pblock, __offset+_PREG(14), (uchar *)Out);
   __vcop_pblock_init16(pblock, __offset+_PREG(16), 16);
   __vcop_pblock_init16(pblock, __offset+_PREG(17), ((in_w-6)*sizeof(*out_4_ptr)) -(8u*sizeof(*out_4_ptr))*(((((in_w-6))+(8u)-1)/(8u))-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(18), (((in_w-6+8u-1)/8u)*sizeof(*Out)) -(sizeof(*Out))*(((((in_w-6))+(8u)-1)/(8u))-1u));
   __vcop_pblock_init32(pblock, __offset+_PREG(20), 16);
   __vcop_pblock_init32(pblock, __offset+_PREG(22), 4);
   __offset += 22;

   return 184u;
}

void vcop_fast9_vloops(
   unsigned short pblock[])
{
   /* Kernel-wide Vector Registers */
   #pragma VCC_VREG("Vin0", 16);
   #pragma VCC_VREG("Vin1", 17);
   #pragma VCC_VREG("Vin2", 18);
   #pragma VCC_VREG("Vin3", 19);
   #pragma VCC_VREG("Vin4", 20);
   #pragma VCC_VREG("Vminus", 21);
   #pragma VCC_VREG("Vnt", 22);
   #pragma VCC_VREG("Vout00", 23);
   #pragma VCC_VREG("Vout01", 24);
   #pragma VCC_VREG("Vout02", 25);
   #pragma VCC_VREG("Vout03", 26);
   #pragma VCC_VREG("Vout10", 27);
   #pragma VCC_VREG("Vout11", 28);
   #pragma VCC_VREG("Vout12", 29);
   #pragma VCC_VREG("Vout13", 30);
   #pragma VCC_VREG("Vshl", 31);
   #pragma VCC_VREG("Vshr", 32);
   #pragma VCC_VREG("Vt", 33);
   #pragma VCC_VREG("Vt01", 34);
   #pragma VCC_VREG("Vt02", 35);
   #pragma VCC_VREG("Vt03", 36);
   #pragma VCC_VREG("Vt04", 37);

   __vcop_param(&pblock[0]);

   /* VLOOP 1 Start */

   /* VLOOP Local Vector Registers */
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("Addr_in", "A0");
   #pragma EVE_REG("Addr_out", "A1");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I1", "I3");
   #pragma EVE_REG("I2", "I4");
   

   __vcop_vloop(__vcop_compute(), 30u, 19u, 1u);
   __vcop_vinit(__vcop_sizeW(), __vcop_once(), _PREG(36), _VREG(33));
   __vcop_vinit(__vcop_sizeW(), __vcop_once(), _PREG(38), _VREG(22));
   __vcop_vagen(_AGEN(0), _PREG(32), _PREG(33), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(1), _PREG(32), _PREG(34), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeBU(), __vcop_npt(), _PREG(6), _AGEN(0), _VREG(16), __vcop_alws());
   __vcop_vload(__vcop_sizeBU(), __vcop_npt(), _PREG(8), _AGEN(0), _VREG(17), __vcop_alws());
   __vcop_vload(__vcop_sizeBU(), __vcop_npt(), _PREG(10), _AGEN(0), _VREG(18), __vcop_alws());
   __vcop_vload(__vcop_sizeBU(), __vcop_npt(), _PREG(12), _AGEN(0), _VREG(19), __vcop_alws());
   __vcop_vload(__vcop_sizeBU(), __vcop_npt(), _PREG(14), _AGEN(0), _VREG(20), __vcop_alws());
   __vcop_vsub(_VREG(16), _VREG(17), _VREG(34));
   __vcop_vsub(_VREG(16), _VREG(18), _VREG(35));
   __vcop_vsub(_VREG(16), _VREG(19), _VREG(36));
   __vcop_vsub(_VREG(16), _VREG(20), _VREG(37));
   __vcop_vbitpk(_VREG(34), _VREG(33), _VREG(23));
   __vcop_vbitpk(_VREG(35), _VREG(33), _VREG(24));
   __vcop_vbitpk(_VREG(36), _VREG(33), _VREG(25));
   __vcop_vbitpk(_VREG(37), _VREG(33), _VREG(26));
   __vcop_vbitpk(_VREG(22), _VREG(34), _VREG(27));
   __vcop_vbitpk(_VREG(22), _VREG(35), _VREG(28));
   __vcop_vbitpk(_VREG(22), _VREG(36), _VREG(29));
   __vcop_vbitpk(_VREG(22), _VREG(37), _VREG(30));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeBU(), __vcop_1pt(), __vcop_alws(), _VREG(23), _PREG(16), _AGEN(1), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeBU(), __vcop_1pt(), __vcop_alws(), _VREG(24), _PREG(18), _AGEN(1), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeBU(), __vcop_1pt(), __vcop_alws(), _VREG(25), _PREG(20), _AGEN(1), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeBU(), __vcop_1pt(), __vcop_alws(), _VREG(26), _PREG(22), _AGEN(1), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeBU(), __vcop_1pt(), __vcop_alws(), _VREG(27), _PREG(24), _AGEN(1), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeBU(), __vcop_1pt(), __vcop_alws(), _VREG(28), _PREG(26), _AGEN(1), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeBU(), __vcop_1pt(), __vcop_alws(), _VREG(29), _PREG(28), _AGEN(1), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeBU(), __vcop_1pt(), __vcop_alws(), _VREG(30), _PREG(30), _AGEN(1), _PREG(0));
   __vcop_vloop_end(1u);

   /* VLOOP 2 Start */

   /* VLOOP Local Vector Registers */
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("Addr_in", "A0");
   #pragma EVE_REG("Addr_out", "A1");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I1", "I3");
   #pragma EVE_REG("I2", "I4");
   

   __vcop_vloop(__vcop_compute(), 28u, 17u, 2u);
   __vcop_vagen(_AGEN(0), _PREG(28), _PREG(29), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(1), _PREG(28), _PREG(30), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeBU(), __vcop_npt(), _PREG(32), _AGEN(0), _VREG(16), __vcop_alws());
   __vcop_vload(__vcop_sizeBU(), __vcop_npt(), _PREG(34), _AGEN(0), _VREG(17), __vcop_alws());
   __vcop_vload(__vcop_sizeBU(), __vcop_npt(), _PREG(6), _AGEN(0), _VREG(18), __vcop_alws());
   __vcop_vload(__vcop_sizeBU(), __vcop_npt(), _PREG(8), _AGEN(0), _VREG(19), __vcop_alws());
   __vcop_vload(__vcop_sizeBU(), __vcop_npt(), _PREG(10), _AGEN(0), _VREG(20), __vcop_alws());
   __vcop_vsub(_VREG(16), _VREG(17), _VREG(34));
   __vcop_vsub(_VREG(16), _VREG(18), _VREG(35));
   __vcop_vsub(_VREG(16), _VREG(19), _VREG(36));
   __vcop_vsub(_VREG(16), _VREG(20), _VREG(37));
   __vcop_vbitpk(_VREG(34), _VREG(33), _VREG(23));
   __vcop_vbitpk(_VREG(35), _VREG(33), _VREG(24));
   __vcop_vbitpk(_VREG(36), _VREG(33), _VREG(25));
   __vcop_vbitpk(_VREG(37), _VREG(33), _VREG(26));
   __vcop_vbitpk(_VREG(22), _VREG(34), _VREG(27));
   __vcop_vbitpk(_VREG(22), _VREG(35), _VREG(28));
   __vcop_vbitpk(_VREG(22), _VREG(36), _VREG(29));
   __vcop_vbitpk(_VREG(22), _VREG(37), _VREG(30));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeBU(), __vcop_1pt(), __vcop_alws(), _VREG(23), _PREG(12), _AGEN(1), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeBU(), __vcop_1pt(), __vcop_alws(), _VREG(24), _PREG(14), _AGEN(1), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeBU(), __vcop_1pt(), __vcop_alws(), _VREG(25), _PREG(16), _AGEN(1), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeBU(), __vcop_1pt(), __vcop_alws(), _VREG(26), _PREG(18), _AGEN(1), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeBU(), __vcop_1pt(), __vcop_alws(), _VREG(27), _PREG(20), _AGEN(1), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeBU(), __vcop_1pt(), __vcop_alws(), _VREG(28), _PREG(22), _AGEN(1), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeBU(), __vcop_1pt(), __vcop_alws(), _VREG(29), _PREG(24), _AGEN(1), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeBU(), __vcop_1pt(), __vcop_alws(), _VREG(30), _PREG(26), _AGEN(1), _PREG(0));
   __vcop_vloop_end(2u);

   /* VLOOP 3 Start */

   /* VLOOP Local Vector Registers */
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("Addr_in", "A0");
   #pragma EVE_REG("Addr_out", "A1");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I1", "I3");
   #pragma EVE_REG("I2", "I4");
   

   __vcop_vloop(__vcop_compute(), 28u, 17u, 3u);
   __vcop_vagen(_AGEN(0), _PREG(28), _PREG(29), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(1), _PREG(28), _PREG(30), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeBU(), __vcop_npt(), _PREG(32), _AGEN(0), _VREG(16), __vcop_alws());
   __vcop_vload(__vcop_sizeBU(), __vcop_npt(), _PREG(34), _AGEN(0), _VREG(17), __vcop_alws());
   __vcop_vload(__vcop_sizeBU(), __vcop_npt(), _PREG(6), _AGEN(0), _VREG(18), __vcop_alws());
   __vcop_vload(__vcop_sizeBU(), __vcop_npt(), _PREG(8), _AGEN(0), _VREG(19), __vcop_alws());
   __vcop_vload(__vcop_sizeBU(), __vcop_npt(), _PREG(10), _AGEN(0), _VREG(20), __vcop_alws());
   __vcop_vsub(_VREG(16), _VREG(17), _VREG(34));
   __vcop_vsub(_VREG(16), _VREG(18), _VREG(35));
   __vcop_vsub(_VREG(16), _VREG(19), _VREG(36));
   __vcop_vsub(_VREG(16), _VREG(20), _VREG(37));
   __vcop_vbitpk(_VREG(34), _VREG(33), _VREG(23));
   __vcop_vbitpk(_VREG(35), _VREG(33), _VREG(24));
   __vcop_vbitpk(_VREG(36), _VREG(33), _VREG(25));
   __vcop_vbitpk(_VREG(37), _VREG(33), _VREG(26));
   __vcop_vbitpk(_VREG(22), _VREG(34), _VREG(27));
   __vcop_vbitpk(_VREG(22), _VREG(35), _VREG(28));
   __vcop_vbitpk(_VREG(22), _VREG(36), _VREG(29));
   __vcop_vbitpk(_VREG(22), _VREG(37), _VREG(30));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeBU(), __vcop_1pt(), __vcop_alws(), _VREG(23), _PREG(12), _AGEN(1), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeBU(), __vcop_1pt(), __vcop_alws(), _VREG(24), _PREG(14), _AGEN(1), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeBU(), __vcop_1pt(), __vcop_alws(), _VREG(25), _PREG(16), _AGEN(1), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeBU(), __vcop_1pt(), __vcop_alws(), _VREG(26), _PREG(18), _AGEN(1), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeBU(), __vcop_1pt(), __vcop_alws(), _VREG(27), _PREG(20), _AGEN(1), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeBU(), __vcop_1pt(), __vcop_alws(), _VREG(28), _PREG(22), _AGEN(1), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeBU(), __vcop_1pt(), __vcop_alws(), _VREG(29), _PREG(24), _AGEN(1), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeBU(), __vcop_1pt(), __vcop_alws(), _VREG(30), _PREG(26), _AGEN(1), _PREG(0));
   __vcop_vloop_end(3u);

   /* VLOOP 4 Start */

   /* VLOOP Local Vector Registers */
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("Addr_in", "A0");
   #pragma EVE_REG("Addr_out", "A1");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I1", "I3");
   #pragma EVE_REG("I2", "I4");
   

   __vcop_vloop(__vcop_compute(), 28u, 17u, 4u);
   __vcop_vagen(_AGEN(0), _PREG(28), _PREG(29), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(1), _PREG(28), _PREG(30), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeBU(), __vcop_npt(), _PREG(32), _AGEN(0), _VREG(16), __vcop_alws());
   __vcop_vload(__vcop_sizeBU(), __vcop_npt(), _PREG(34), _AGEN(0), _VREG(17), __vcop_alws());
   __vcop_vload(__vcop_sizeBU(), __vcop_npt(), _PREG(6), _AGEN(0), _VREG(18), __vcop_alws());
   __vcop_vload(__vcop_sizeBU(), __vcop_npt(), _PREG(8), _AGEN(0), _VREG(19), __vcop_alws());
   __vcop_vload(__vcop_sizeBU(), __vcop_npt(), _PREG(10), _AGEN(0), _VREG(20), __vcop_alws());
   __vcop_vsub(_VREG(16), _VREG(17), _VREG(34));
   __vcop_vsub(_VREG(16), _VREG(18), _VREG(35));
   __vcop_vsub(_VREG(16), _VREG(19), _VREG(36));
   __vcop_vsub(_VREG(16), _VREG(20), _VREG(37));
   __vcop_vbitpk(_VREG(34), _VREG(33), _VREG(23));
   __vcop_vbitpk(_VREG(35), _VREG(33), _VREG(24));
   __vcop_vbitpk(_VREG(36), _VREG(33), _VREG(25));
   __vcop_vbitpk(_VREG(37), _VREG(33), _VREG(26));
   __vcop_vbitpk(_VREG(22), _VREG(34), _VREG(27));
   __vcop_vbitpk(_VREG(22), _VREG(35), _VREG(28));
   __vcop_vbitpk(_VREG(22), _VREG(36), _VREG(29));
   __vcop_vbitpk(_VREG(22), _VREG(37), _VREG(30));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeBU(), __vcop_1pt(), __vcop_alws(), _VREG(23), _PREG(12), _AGEN(1), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeBU(), __vcop_1pt(), __vcop_alws(), _VREG(24), _PREG(14), _AGEN(1), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeBU(), __vcop_1pt(), __vcop_alws(), _VREG(25), _PREG(16), _AGEN(1), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeBU(), __vcop_1pt(), __vcop_alws(), _VREG(26), _PREG(18), _AGEN(1), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeBU(), __vcop_1pt(), __vcop_alws(), _VREG(27), _PREG(20), _AGEN(1), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeBU(), __vcop_1pt(), __vcop_alws(), _VREG(28), _PREG(22), _AGEN(1), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeBU(), __vcop_1pt(), __vcop_alws(), _VREG(29), _PREG(24), _AGEN(1), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeBU(), __vcop_1pt(), __vcop_alws(), _VREG(30), _PREG(26), _AGEN(1), _PREG(0));
   __vcop_vloop_end(4u);

   /* VLOOP 5 Start */

   /* VLOOP Local Vector Registers */
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("Addr_in", "A0");
   #pragma EVE_REG("Addr_out", "A1");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I1", "I3");
   #pragma EVE_REG("I2", "I4");
   

   __vcop_vloop(__vcop_compute(), 16u, 11u, 5u);
   __vcop_vinit(__vcop_sizeW(), __vcop_once(), _PREG(20), _VREG(31));
   __vcop_vagen(_AGEN(0), _PREG(16), _PREG(17), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(1), _PREG(18), _PREG(19), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeBU(), __vcop_npt(), _PREG(22), _AGEN(0), _VREG(16), __vcop_alws());
   __vcop_vload(__vcop_sizeBU(), __vcop_npt(), _PREG(6), _AGEN(0), _VREG(17), __vcop_alws());
   __vcop_vload(__vcop_sizeBU(), __vcop_npt(), _PREG(8), _AGEN(0), _VREG(18), __vcop_alws());
   __vcop_vload(__vcop_sizeBU(), __vcop_npt(), _PREG(10), _AGEN(0), _VREG(19), __vcop_alws());
   __vcop_vbittr(_VREG(16), _VREG(34));
   __vcop_vbittr(_VREG(17), _VREG(35));
   __vcop_vbittr(_VREG(18), _VREG(36));
   __vcop_vbittr(_VREG(19), _VREG(37));
   __vcop_vshfor(_VREG(36), _VREG(31), _VREG(34));
   __vcop_vshfor(_VREG(37), _VREG(31), _VREG(35));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeHU(), __vcop_npt(), __vcop_alws(), _VREG(34), _PREG(12), _AGEN(1), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeHU(), __vcop_npt(), __vcop_alws(), _VREG(35), _PREG(14), _AGEN(1), _PREG(0));
   __vcop_vloop_end(5u);

   /* VLOOP 6 Start */

   /* VLOOP Local Vector Registers */
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("Addr_in", "A0");
   #pragma EVE_REG("Addr_out", "A1");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I1", "I3");
   #pragma EVE_REG("I2", "I4");
   

   __vcop_vloop(__vcop_compute(), 32u, 11u, 6u);
   __vcop_vinit(__vcop_sizeW(), __vcop_once(), _PREG(20), _VREG(32));
   __vcop_vinit(__vcop_sizeW(), __vcop_once(), _PREG(22), _VREG(24));
   __vcop_vinit(__vcop_sizeW(), __vcop_once(), _PREG(6), _VREG(23));
   __vcop_vinit(__vcop_sizeW(), __vcop_once(), _PREG(8), _VREG(31));
   __vcop_vagen(_AGEN(0), _PREG(16), _PREG(17), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(1), _PREG(1), _PREG(18), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeHU(), __vcop_npt(), _PREG(10), _AGEN(0), _VREG(16), __vcop_alws());
   __vcop_vload(__vcop_sizeHU(), __vcop_npt(), _PREG(12), _AGEN(0), _VREG(17), __vcop_alws());
   __vcop_vshf(_VREG(16), _VREG(32), _VREG(34));
   __vcop_vshf(_VREG(17), _VREG(32), _VREG(35));
   __vcop_vor(_VREG(34), _VREG(16), _VREG(34));
   __vcop_vor(_VREG(35), _VREG(17), _VREG(35));
   __vcop_vshf(_VREG(34), _VREG(31), _VREG(36));
   __vcop_vshf(_VREG(35), _VREG(31), _VREG(37));
   __vcop_vand(_VREG(34), _VREG(36), _VREG(34));
   __vcop_vand(_VREG(35), _VREG(37), _VREG(35));
   __vcop_vshf(_VREG(34), _VREG(23), _VREG(36));
   __vcop_vshf(_VREG(35), _VREG(23), _VREG(37));
   __vcop_vand(_VREG(34), _VREG(36), _VREG(34));
   __vcop_vand(_VREG(35), _VREG(37), _VREG(35));
   __vcop_vshf(_VREG(34), _VREG(24), _VREG(36));
   __vcop_vshf(_VREG(35), _VREG(24), _VREG(37));
   __vcop_vand(_VREG(34), _VREG(36), _VREG(34));
   __vcop_vand(_VREG(35), _VREG(37), _VREG(35));
   __vcop_vshf(_VREG(34), _VREG(31), _VREG(36));
   __vcop_vshf(_VREG(35), _VREG(31), _VREG(37));
   __vcop_vand(_VREG(34), _VREG(36), _VREG(34));
   __vcop_vand(_VREG(35), _VREG(37), _VREG(35));
   __vcop_vor(_VREG(34), _VREG(35), _VREG(34));
   __vcop_vbitpk(_VREG(34), _VREG(31), _VREG(25));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeBU(), __vcop_1pt(), __vcop_alws(), _VREG(25), _PREG(14), _AGEN(1), _PREG(0));
   __vcop_vloop_end(6u);

}

void vcop_fast9(
   __vptr_uint8 vec1,
   __vptr_uint8 out_0_ptr,
   __vptr_uint8 out_1_ptr,
   __vptr_uint16 out_4_ptr,
   __vptr_uint8 Out,
   signed char Thr,
   unsigned int pitch,
   unsigned int in_w,
   unsigned int in_h)
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_fast9_init(vec1, out_0_ptr, out_1_ptr, out_4_ptr, Out, Thr, pitch, in_w, in_h, __pblock_vcop_fast9);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_fast9_vloops(__pblock_vcop_fast9);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

void vcop_fast9_custom(
   __vptr_uint8 vec1,
   __vptr_uint8 out_0_ptr,
   __vptr_uint8 out_1_ptr,
   __vptr_uint16 out_4_ptr,
   __vptr_uint8 Out,
   signed char Thr,
   unsigned int pitch,
   unsigned int in_w,
   unsigned int in_h,
   unsigned short pblock[])
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_fast9_init(vec1, out_0_ptr, out_1_ptr, out_4_ptr, Out, Thr, pitch, in_w, in_h, pblock);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_fast9_vloops(pblock);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

