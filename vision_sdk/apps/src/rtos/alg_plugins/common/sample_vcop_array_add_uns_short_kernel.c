#include <vcop/vcop.h>

typedef unsigned char uchar;

#pragma DATA_SECTION(__pblock_sample_eve_array_add_uns_short, ".vcop_parameter_block")
#pragma DATA_ALIGN(__pblock_sample_eve_array_add_uns_short, __ALIGNOF__(int));
unsigned short __pblock_sample_eve_array_add_uns_short[12];

unsigned int sample_eve_array_add_uns_short_param_count(void)
{
   return 12u;
}

unsigned int sample_eve_array_add_uns_short_ctrl_count(void)
{
   return 0u;
}

unsigned int sample_eve_array_add_uns_short_init(
   __vptr_uint16 in1_ptr,
   __vptr_uint16 in2_ptr,
   __vptr_uint16 optr,
   unsigned short width,
   unsigned short height,
   unsigned short pblock[])
{
   int __offset = 0;
   /* Loop 1 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), (height)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), (width/(8u))-1u);
   __vcop_pblock_init32(pblock, __offset+_PREG(6), (uchar *)optr);
   __vcop_pblock_init16(pblock, __offset+_PREG(8), 16);
   __vcop_pblock_init16(pblock, __offset+_PREG(9), (width*sizeof(*in1_ptr)) -((8u*sizeof(*in1_ptr)))*((width/(8u))-1u));
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)in1_ptr);
   __vcop_pblock_init32(pblock, __offset+_PREG(12), (uchar *)in2_ptr);
   __offset += 12;

   return 12u;
}

void sample_eve_array_add_uns_short_vloops(
   unsigned short pblock[])
{
   /* Kernel-wide Vector Registers */
   #pragma VCC_VREG("Vin1", 16);
   #pragma VCC_VREG("Vin2", 17);
   #pragma VCC_VREG("Vout", 18);

   __vcop_param(&pblock[0]);

   /* VLOOP 1 Start */

   /* VLOOP Local Vector Registers */
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("Addr", "A0");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I1", "I3");
   #pragma EVE_REG("I2", "I4");
   

   #line 54 "common/sample_vcop_array_add_uns_short_kernel.k"
   __vcop_vloop(__vcop_compute(), 6u, 6u, 1u);
   #line 58 "common/sample_vcop_array_add_uns_short_kernel.k"
   __vcop_vagen(_AGEN(0), _PREG(8), _PREG(9), _PREG(0), _PREG(0));
   #line 62 "common/sample_vcop_array_add_uns_short_kernel.k"
   __vcop_vload(__vcop_sizeHU(), __vcop_npt(), _PREG(10), _AGEN(0), _VREG(16), __vcop_alws_condload());
   #line 63 "common/sample_vcop_array_add_uns_short_kernel.k"
   __vcop_vload(__vcop_sizeHU(), __vcop_npt(), _PREG(12), _AGEN(0), _VREG(17), __vcop_alws_condload());
   #line 64 "common/sample_vcop_array_add_uns_short_kernel.k"
   __vcop_vadd(_VREG(16), _VREG(17), _VREG(18));
   #line 65 "common/sample_vcop_array_add_uns_short_kernel.k"
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeHU(), __vcop_npt(), __vcop_alws(), _VREG(18), _PREG(6), _AGEN(0), _PREG(0));
   #line 78 "common/sample_vcop_array_add_uns_short_kernel.c"
   __vcop_vloop_end(1u);

}

void sample_eve_array_add_uns_short(
   __vptr_uint16 in1_ptr,
   __vptr_uint16 in2_ptr,
   __vptr_uint16 optr,
   unsigned short width,
   unsigned short height)
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   sample_eve_array_add_uns_short_init(in1_ptr, in2_ptr, optr, width, height, __pblock_sample_eve_array_add_uns_short);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   sample_eve_array_add_uns_short_vloops(__pblock_sample_eve_array_add_uns_short);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

void sample_eve_array_add_uns_short_custom(
   __vptr_uint16 in1_ptr,
   __vptr_uint16 in2_ptr,
   __vptr_uint16 optr,
   unsigned short width,
   unsigned short height,
   unsigned short pblock[])
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   sample_eve_array_add_uns_short_init(in1_ptr, in2_ptr, optr, width, height, pblock);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   sample_eve_array_add_uns_short_vloops(pblock);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

