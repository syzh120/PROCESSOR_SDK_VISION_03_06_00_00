#include <vcop\vcop.h>

typedef unsigned char uchar;

#pragma DATA_SECTION(__pblock_vcop_sort8_simd8_64, ".vcop_parameter_block")
#pragma DATA_ALIGN(__pblock_vcop_sort8_simd8_64, __ALIGNOF__(int));
unsigned short __pblock_vcop_sort8_simd8_64[36];

unsigned int vcop_sort8_simd8_64_param_count(void)
{
   return 36u;
}

unsigned int vcop_sort8_simd8_64_ctrl_count(void)
{
   return 0u;
}

unsigned int vcop_sort8_simd8_64_init(
   int niter,
   int out_tr,
   __vptr_uint32 in,
   __vptr_uint32 out,
   unsigned short pblock[])
{
   int __offset = 0;
   /* Loop 1 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), (1)-1u);
   __vcop_pblock_init32(pblock, __offset+_PREG(6), (uchar *)in+2*(8u*sizeof(*in)));
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)in+3*(8u*sizeof(*in)));
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)in+4*(8u*sizeof(*in)));
   __vcop_pblock_init32(pblock, __offset+_PREG(12), (uchar *)in+5*(8u*sizeof(*in)));
   __vcop_pblock_init32(pblock, __offset+_PREG(14), (uchar *)in+6*(8u*sizeof(*in)));
   __vcop_pblock_init32(pblock, __offset+_PREG(16), (uchar *)in+7*(8u*sizeof(*in)));
   __vcop_pblock_init32(pblock, __offset+_PREG(18), (uchar *)out+0);
   __vcop_pblock_init32(pblock, __offset+_PREG(20), (uchar *)out+4);
   __vcop_pblock_init32(pblock, __offset+_PREG(22), (uchar *)out+8);
   __vcop_pblock_init32(pblock, __offset+_PREG(24), (uchar *)out+12);
   __vcop_pblock_init32(pblock, __offset+_PREG(26), (uchar *)out+16);
   __vcop_pblock_init32(pblock, __offset+_PREG(28), (uchar *)out+20);
   __vcop_pblock_init32(pblock, __offset+_PREG(30), (uchar *)out+24);
   __vcop_pblock_init32(pblock, __offset+_PREG(32), (uchar *)out+28);
   __vcop_pblock_init32(pblock, __offset+_PREG(34), (uchar *)in+0*(8u*sizeof(*in)));
   __vcop_pblock_init32(pblock, __offset+_PREG(36), (uchar *)in+1*(8u*sizeof(*in)));
   __offset += 36;

   return 36u;
}

void vcop_sort8_simd8_64_vloops(
   unsigned short pblock[])
{
   /* Kernel-wide Vector Registers */
   #pragma VCC_VREG("Vin0", 16);
   #pragma VCC_VREG("Vin1", 17);
   #pragma VCC_VREG("Vin2", 18);
   #pragma VCC_VREG("Vin3", 19);
   #pragma VCC_VREG("Vin4", 20);
   #pragma VCC_VREG("Vin5", 21);
   #pragma VCC_VREG("Vin6", 22);
   #pragma VCC_VREG("Vin7", 23);

   __vcop_param(&pblock[0]);

   /* VLOOP 1 Start */

   /* VLOOP Local Vector Registers */
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("Addr", "A0");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I1", "I4");
   

   __vcop_vloop(__vcop_compute(), 37u, 18u, 1u);
   __vcop_vagen(_AGEN(0), _PREG(0), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeWU(), __vcop_npt(), _PREG(34), _AGEN(0), _VREG(16), __vcop_alws_condload());
   __vcop_vload(__vcop_sizeWU(), __vcop_npt(), _PREG(36), _AGEN(0), _VREG(17), __vcop_alws_condload());
   __vcop_vload(__vcop_sizeWU(), __vcop_npt(), _PREG(6), _AGEN(0), _VREG(18), __vcop_alws_condload());
   __vcop_vload(__vcop_sizeWU(), __vcop_npt(), _PREG(8), _AGEN(0), _VREG(19), __vcop_alws_condload());
   __vcop_vload(__vcop_sizeWU(), __vcop_npt(), _PREG(10), _AGEN(0), _VREG(20), __vcop_alws_condload());
   __vcop_vload(__vcop_sizeWU(), __vcop_npt(), _PREG(12), _AGEN(0), _VREG(21), __vcop_alws_condload());
   __vcop_vload(__vcop_sizeWU(), __vcop_npt(), _PREG(14), _AGEN(0), _VREG(22), __vcop_alws_condload());
   __vcop_vload(__vcop_sizeWU(), __vcop_npt(), _PREG(16), _AGEN(0), _VREG(23), __vcop_alws_condload());
   __vcop_vsort2(_VREG(16), _VREG(17));
   __vcop_vsort2(_VREG(18), _VREG(19));
   __vcop_vsort2(_VREG(16), _VREG(18));
   __vcop_vsort2(_VREG(17), _VREG(19));
   __vcop_vsort2(_VREG(17), _VREG(18));
   __vcop_vsort2(_VREG(20), _VREG(21));
   __vcop_vsort2(_VREG(22), _VREG(23));
   __vcop_vsort2(_VREG(20), _VREG(22));
   __vcop_vsort2(_VREG(21), _VREG(23));
   __vcop_vsort2(_VREG(21), _VREG(22));
   __vcop_vsort2(_VREG(16), _VREG(20));
   __vcop_vsort2(_VREG(18), _VREG(22));
   __vcop_vsort2(_VREG(18), _VREG(20));
   __vcop_vsort2(_VREG(17), _VREG(21));
   __vcop_vsort2(_VREG(19), _VREG(23));
   __vcop_vsort2(_VREG(19), _VREG(21));
   __vcop_vsort2(_VREG(17), _VREG(18));
   __vcop_vsort2(_VREG(19), _VREG(20));
   __vcop_vsort2(_VREG(21), _VREG(22));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeWU(), __vcop_offst_np1(), __vcop_alws(), _VREG(16), _PREG(18), _AGEN(0), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeWU(), __vcop_offst_np1(), __vcop_alws(), _VREG(17), _PREG(20), _AGEN(0), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeWU(), __vcop_offst_np1(), __vcop_alws(), _VREG(18), _PREG(22), _AGEN(0), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeWU(), __vcop_offst_np1(), __vcop_alws(), _VREG(19), _PREG(24), _AGEN(0), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeWU(), __vcop_offst_np1(), __vcop_alws(), _VREG(20), _PREG(26), _AGEN(0), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeWU(), __vcop_offst_np1(), __vcop_alws(), _VREG(21), _PREG(28), _AGEN(0), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeWU(), __vcop_offst_np1(), __vcop_alws(), _VREG(22), _PREG(30), _AGEN(0), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeWU(), __vcop_offst_np1(), __vcop_alws(), _VREG(23), _PREG(32), _AGEN(0), _PREG(0));
   __vcop_vloop_end(1u);

}

void vcop_sort8_simd8_64(
   int niter,
   int out_tr,
   __vptr_uint32 in,
   __vptr_uint32 out)
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_sort8_simd8_64_init(niter, out_tr, in, out, __pblock_vcop_sort8_simd8_64);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_sort8_simd8_64_vloops(__pblock_vcop_sort8_simd8_64);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

void vcop_sort8_simd8_64_custom(
   int niter,
   int out_tr,
   __vptr_uint32 in,
   __vptr_uint32 out,
   unsigned short pblock[])
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_sort8_simd8_64_init(niter, out_tr, in, out, pblock);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_sort8_simd8_64_vloops(pblock);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

#pragma DATA_SECTION(__pblock_vcop_sort8_simd8_XX, ".vcop_parameter_block")
#pragma DATA_ALIGN(__pblock_vcop_sort8_simd8_XX, __ALIGNOF__(int));
unsigned short __pblock_vcop_sort8_simd8_XX[38];

unsigned int vcop_sort8_simd8_XX_param_count(void)
{
   return 38u;
}

unsigned int vcop_sort8_simd8_XX_ctrl_count(void)
{
   return 0u;
}

unsigned int vcop_sort8_simd8_XX_init(
   int niter,
   int out_tr,
   __vptr_uint32 in,
   __vptr_uint32 out,
   unsigned short pblock[])
{
   int __offset = 0;
   /* Loop 1 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), (niter)-1u);
   __vcop_pblock_init32(pblock, __offset+_PREG(6), (uchar *)in+2*(8u*sizeof(*in)));
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)in+3*(8u*sizeof(*in)));
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)in+4*(8u*sizeof(*in)));
   __vcop_pblock_init32(pblock, __offset+_PREG(12), (uchar *)in+5*(8u*sizeof(*in)));
   __vcop_pblock_init32(pblock, __offset+_PREG(14), (uchar *)in+6*(8u*sizeof(*in)));
   __vcop_pblock_init32(pblock, __offset+_PREG(16), (uchar *)in+7*(8u*sizeof(*in)));
   __vcop_pblock_init32(pblock, __offset+_PREG(18), (uchar *)out+0*(8u*sizeof(*in)));
   __vcop_pblock_init32(pblock, __offset+_PREG(20), (uchar *)out+1*(8u*sizeof(*in)));
   __vcop_pblock_init32(pblock, __offset+_PREG(22), (uchar *)out+2*(8u*sizeof(*in)));
   __vcop_pblock_init32(pblock, __offset+_PREG(24), (uchar *)out+3*(8u*sizeof(*in)));
   __vcop_pblock_init32(pblock, __offset+_PREG(26), (uchar *)out+4*(8u*sizeof(*in)));
   __vcop_pblock_init32(pblock, __offset+_PREG(28), (uchar *)out+5*(8u*sizeof(*in)));
   __vcop_pblock_init32(pblock, __offset+_PREG(30), (uchar *)out+6*(8u*sizeof(*in)));
   __vcop_pblock_init32(pblock, __offset+_PREG(32), (uchar *)out+7*(8u*sizeof(*in)));
   __vcop_pblock_init16(pblock, __offset+_PREG(34), 256);
   __vcop_pblock_init32(pblock, __offset+_PREG(36), (uchar *)in+0*(8u*sizeof(*in)));
   __vcop_pblock_init32(pblock, __offset+_PREG(38), (uchar *)in+1*(8u*sizeof(*in)));
   __offset += 38;

   return 38u;
}

void vcop_sort8_simd8_XX_vloops(
   unsigned short pblock[])
{
   /* Kernel-wide Vector Registers */
   #pragma VCC_VREG("Vin0", 16);
   #pragma VCC_VREG("Vin1", 17);
   #pragma VCC_VREG("Vin2", 18);
   #pragma VCC_VREG("Vin3", 19);
   #pragma VCC_VREG("Vin4", 20);
   #pragma VCC_VREG("Vin5", 21);
   #pragma VCC_VREG("Vin6", 22);
   #pragma VCC_VREG("Vin7", 23);

   __vcop_param(&pblock[0]);

   /* VLOOP 1 Start */

   /* VLOOP Local Vector Registers */
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("Addr", "A0");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I1", "I4");
   

   __vcop_vloop(__vcop_compute(), 37u, 19u, 1u);
   __vcop_vagen(_AGEN(0), _PREG(34), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeWU(), __vcop_npt(), _PREG(36), _AGEN(0), _VREG(16), __vcop_alws());
   __vcop_vload(__vcop_sizeWU(), __vcop_npt(), _PREG(38), _AGEN(0), _VREG(17), __vcop_alws());
   __vcop_vload(__vcop_sizeWU(), __vcop_npt(), _PREG(6), _AGEN(0), _VREG(18), __vcop_alws());
   __vcop_vload(__vcop_sizeWU(), __vcop_npt(), _PREG(8), _AGEN(0), _VREG(19), __vcop_alws());
   __vcop_vload(__vcop_sizeWU(), __vcop_npt(), _PREG(10), _AGEN(0), _VREG(20), __vcop_alws());
   __vcop_vload(__vcop_sizeWU(), __vcop_npt(), _PREG(12), _AGEN(0), _VREG(21), __vcop_alws());
   __vcop_vload(__vcop_sizeWU(), __vcop_npt(), _PREG(14), _AGEN(0), _VREG(22), __vcop_alws());
   __vcop_vload(__vcop_sizeWU(), __vcop_npt(), _PREG(16), _AGEN(0), _VREG(23), __vcop_alws());
   __vcop_vsort2(_VREG(16), _VREG(17));
   __vcop_vsort2(_VREG(18), _VREG(19));
   __vcop_vsort2(_VREG(16), _VREG(18));
   __vcop_vsort2(_VREG(17), _VREG(19));
   __vcop_vsort2(_VREG(17), _VREG(18));
   __vcop_vsort2(_VREG(20), _VREG(21));
   __vcop_vsort2(_VREG(22), _VREG(23));
   __vcop_vsort2(_VREG(20), _VREG(22));
   __vcop_vsort2(_VREG(21), _VREG(23));
   __vcop_vsort2(_VREG(21), _VREG(22));
   __vcop_vsort2(_VREG(16), _VREG(20));
   __vcop_vsort2(_VREG(18), _VREG(22));
   __vcop_vsort2(_VREG(18), _VREG(20));
   __vcop_vsort2(_VREG(17), _VREG(21));
   __vcop_vsort2(_VREG(19), _VREG(23));
   __vcop_vsort2(_VREG(19), _VREG(21));
   __vcop_vsort2(_VREG(17), _VREG(18));
   __vcop_vsort2(_VREG(19), _VREG(20));
   __vcop_vsort2(_VREG(21), _VREG(22));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeWU(), __vcop_npt(), __vcop_alws(), _VREG(16), _PREG(18), _AGEN(0), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeWU(), __vcop_npt(), __vcop_alws(), _VREG(17), _PREG(20), _AGEN(0), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeWU(), __vcop_npt(), __vcop_alws(), _VREG(18), _PREG(22), _AGEN(0), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeWU(), __vcop_npt(), __vcop_alws(), _VREG(19), _PREG(24), _AGEN(0), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeWU(), __vcop_npt(), __vcop_alws(), _VREG(20), _PREG(26), _AGEN(0), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeWU(), __vcop_npt(), __vcop_alws(), _VREG(21), _PREG(28), _AGEN(0), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeWU(), __vcop_npt(), __vcop_alws(), _VREG(22), _PREG(30), _AGEN(0), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeWU(), __vcop_npt(), __vcop_alws(), _VREG(23), _PREG(32), _AGEN(0), _PREG(0));
   __vcop_vloop_end(1u);

}

void vcop_sort8_simd8_XX(
   int niter,
   int out_tr,
   __vptr_uint32 in,
   __vptr_uint32 out)
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_sort8_simd8_XX_init(niter, out_tr, in, out, __pblock_vcop_sort8_simd8_XX);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_sort8_simd8_XX_vloops(__pblock_vcop_sort8_simd8_XX);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

void vcop_sort8_simd8_XX_custom(
   int niter,
   int out_tr,
   __vptr_uint32 in,
   __vptr_uint32 out,
   unsigned short pblock[])
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_sort8_simd8_XX_init(niter, out_tr, in, out, pblock);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_sort8_simd8_XX_vloops(pblock);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

#pragma DATA_SECTION(__pblock_vcop_psort2_1step_reverse_kernel, ".vcop_parameter_block")
#pragma DATA_ALIGN(__pblock_vcop_psort2_1step_reverse_kernel, __ALIGNOF__(int));
unsigned short __pblock_vcop_psort2_1step_reverse_kernel[28];

unsigned int vcop_psort2_1step_reverse_kernel_param_count(void)
{
   return 28u;
}

unsigned int vcop_psort2_1step_reverse_kernel_ctrl_count(void)
{
   return 0u;
}

unsigned int vcop_psort2_1step_reverse_kernel_init(
   int niter1,
   int niter2,
   int niter3,
   int ibase_0,
   int ibase_1,
   int in1ptr_w1,
   int in1ptr_w2,
   int in1ptr_w3,
   int in2ptr_w1,
   int in2ptr_w2,
   int in2ptr_w3,
   int obase_0,
   int obase_1,
   int outptr_w1,
   int outptr_w2,
   int outptr_w3,
   __vptr_uint32 input,
   __vptr_uint32 output,
   __vptr_int32 out_ofst,
   unsigned short pblock[])
{
   int __offset = 0;
   /* Loop 1 PREGS */
   unsigned char cust_arr1[8] = {7, 6, 5, 4, 3, 2, 1, 0};

   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), (niter1)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), (niter2)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), (niter3)-1u);
   __vcop_pblock_init32(pblock, __offset+_PREG(6), (uchar *)input+ibase_1);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), _CUSTOM(cust_arr1));
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)output+obase_0);
   __vcop_pblock_init32(pblock, __offset+_PREG(12), (uchar *)output+obase_1);
   __vcop_pblock_init16(pblock, __offset+_PREG(14), (0) -(0)*((niter3)-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(15), (0) -(0)*((niter2)-1u) -(0)*((niter3)-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(16), (in1ptr_w3));
   __vcop_pblock_init16(pblock, __offset+_PREG(17), (in1ptr_w2) -(in1ptr_w3)*((niter3)-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(18), (in1ptr_w1) -(in1ptr_w2)*((niter2)-1u) -(in1ptr_w3)*((niter3)-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(19), (in2ptr_w3));
   __vcop_pblock_init16(pblock, __offset+_PREG(20), (in2ptr_w2) -(in2ptr_w3)*((niter3)-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(21), (in2ptr_w1) -(in2ptr_w2)*((niter2)-1u) -(in2ptr_w3)*((niter3)-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(22), (outptr_w3));
   __vcop_pblock_init16(pblock, __offset+_PREG(23), (outptr_w2) -(outptr_w3)*((niter3)-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(24), (outptr_w1) -(outptr_w2)*((niter2)-1u) -(outptr_w3)*((niter3)-1u));
   __vcop_pblock_init32(pblock, __offset+_PREG(26), (uchar *)out_ofst);
   __vcop_pblock_init32(pblock, __offset+_PREG(28), (uchar *)input+ibase_0);
   __offset += 28;

   return 28u;
}

void vcop_psort2_1step_reverse_kernel_vloops(
   unsigned short pblock[])
{
   /* Kernel-wide Vector Registers */
   #pragma VCC_VREG("Vin0", 16);
   #pragma VCC_VREG("Vin0_c", 17);
   #pragma VCC_VREG("Vin0_d", 18);
   #pragma VCC_VREG("Vin1", 19);
   #pragma VCC_VREG("Vin2", 20);
   #pragma VCC_VREG("Vin3", 21);
   #pragma VCC_VREG("Vin4", 22);
   #pragma VCC_VREG("Vin5", 23);
   #pragma VCC_VREG("Vin6", 24);
   #pragma VCC_VREG("Vin7", 25);
   #pragma VCC_VREG("Vindex1", 26);
   #pragma VCC_VREG("Vindex2", 27);

   __vcop_param(&pblock[0]);

   /* VLOOP 1 Start */

   /* VLOOP Local Vector Registers */
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("Addr_in", "A0");
   #pragma EVE_REG("Addr_in1", "A1");
   #pragma EVE_REG("Addr_in2", "A2");
   #pragma EVE_REG("Addr_ou1", "A3");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I1", "I2");
   #pragma EVE_REG("I2", "I3");
   #pragma EVE_REG("I3", "I4");
   

   __vcop_vloop(__vcop_compute(), 12u, 14u, 1u);
   __vcop_vagen(_AGEN(0), _PREG(0), _PREG(14), _PREG(15), _PREG(0));
   __vcop_vagen(_AGEN(1), _PREG(16), _PREG(17), _PREG(18), _PREG(0));
   __vcop_vagen(_AGEN(2), _PREG(19), _PREG(20), _PREG(21), _PREG(0));
   __vcop_vagen(_AGEN(3), _PREG(22), _PREG(23), _PREG(24), _PREG(0));
   __vcop_vload(__vcop_sizeW(), __vcop_npt(), _PREG(26), _AGEN(0), _VREG(27), __vcop_alws_condload());
   __vcop_vload(__vcop_sizeWU(), __vcop_npt(), _PREG(28), _AGEN(1), _VREG(17), __vcop_alws());
   __vcop_vload(__vcop_sizeWU(), __vcop_cust_p8(), _PREG(6), _AGEN(2), _VREG(19), __vcop_alws());
   __vcop_vsort2(_VREG(17), _VREG(19));
   __vcop_vor(_VREG(27), _VREG(27), _VREG(16));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeWU(), __vcop_pdda(_VREG(16)), __vcop_alws(), _VREG(17), _PREG(10), _AGEN(3), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeWU(), __vcop_pdda(_VREG(16)), __vcop_alws(), _VREG(19), _PREG(12), _AGEN(3), _PREG(0));
   __vcop_vloop_end(1u);

}

void vcop_psort2_1step_reverse_kernel(
   int niter1,
   int niter2,
   int niter3,
   int ibase_0,
   int ibase_1,
   int in1ptr_w1,
   int in1ptr_w2,
   int in1ptr_w3,
   int in2ptr_w1,
   int in2ptr_w2,
   int in2ptr_w3,
   int obase_0,
   int obase_1,
   int outptr_w1,
   int outptr_w2,
   int outptr_w3,
   __vptr_uint32 input,
   __vptr_uint32 output,
   __vptr_int32 out_ofst)
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_psort2_1step_reverse_kernel_init(niter1, niter2, niter3, ibase_0, ibase_1, in1ptr_w1, in1ptr_w2, in1ptr_w3, in2ptr_w1, in2ptr_w2, in2ptr_w3, obase_0, obase_1, outptr_w1, outptr_w2, outptr_w3, input, output, out_ofst, __pblock_vcop_psort2_1step_reverse_kernel);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_psort2_1step_reverse_kernel_vloops(__pblock_vcop_psort2_1step_reverse_kernel);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

void vcop_psort2_1step_reverse_kernel_custom(
   int niter1,
   int niter2,
   int niter3,
   int ibase_0,
   int ibase_1,
   int in1ptr_w1,
   int in1ptr_w2,
   int in1ptr_w3,
   int in2ptr_w1,
   int in2ptr_w2,
   int in2ptr_w3,
   int obase_0,
   int obase_1,
   int outptr_w1,
   int outptr_w2,
   int outptr_w3,
   __vptr_uint32 input,
   __vptr_uint32 output,
   __vptr_int32 out_ofst,
   unsigned short pblock[])
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_psort2_1step_reverse_kernel_init(niter1, niter2, niter3, ibase_0, ibase_1, in1ptr_w1, in1ptr_w2, in1ptr_w3, in2ptr_w1, in2ptr_w2, in2ptr_w3, obase_0, obase_1, outptr_w1, outptr_w2, outptr_w3, input, output, out_ofst, pblock);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_psort2_1step_reverse_kernel_vloops(pblock);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

#pragma DATA_SECTION(__pblock_vcop_psort2_1step_kernel, ".vcop_parameter_block")
#pragma DATA_ALIGN(__pblock_vcop_psort2_1step_kernel, __ALIGNOF__(int));
unsigned short __pblock_vcop_psort2_1step_kernel[26];

unsigned int vcop_psort2_1step_kernel_param_count(void)
{
   return 26u;
}

unsigned int vcop_psort2_1step_kernel_ctrl_count(void)
{
   return 0u;
}

unsigned int vcop_psort2_1step_kernel_init(
   int niter1,
   int niter2,
   int niter3,
   int ibase_0,
   int ibase_1,
   int in1ptr_w1,
   int in1ptr_w2,
   int in1ptr_w3,
   int in2ptr_w1,
   int in2ptr_w2,
   int in2ptr_w3,
   int obase_0,
   int obase_1,
   int outptr_w1,
   int outptr_w2,
   int outptr_w3,
   __vptr_uint32 input,
   __vptr_uint32 output,
   __vptr_int32 out_ofst,
   unsigned short pblock[])
{
   int __offset = 0;
   /* Loop 1 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), (niter1)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), (niter2)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), (niter3)-1u);
   __vcop_pblock_init32(pblock, __offset+_PREG(6), (uchar *)input+ibase_1);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)output+obase_0);
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)output+obase_1);
   __vcop_pblock_init16(pblock, __offset+_PREG(12), (0) -(0)*((niter3)-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(13), (0) -(0)*((niter2)-1u) -(0)*((niter3)-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(14), (in1ptr_w3));
   __vcop_pblock_init16(pblock, __offset+_PREG(15), (in1ptr_w2) -(in1ptr_w3)*((niter3)-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(16), (in1ptr_w1) -(in1ptr_w2)*((niter2)-1u) -(in1ptr_w3)*((niter3)-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(17), (in2ptr_w3));
   __vcop_pblock_init16(pblock, __offset+_PREG(18), (in2ptr_w2) -(in2ptr_w3)*((niter3)-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(19), (in2ptr_w1) -(in2ptr_w2)*((niter2)-1u) -(in2ptr_w3)*((niter3)-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(20), (outptr_w3));
   __vcop_pblock_init16(pblock, __offset+_PREG(21), (outptr_w2) -(outptr_w3)*((niter3)-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(22), (outptr_w1) -(outptr_w2)*((niter2)-1u) -(outptr_w3)*((niter3)-1u));
   __vcop_pblock_init32(pblock, __offset+_PREG(24), (uchar *)out_ofst);
   __vcop_pblock_init32(pblock, __offset+_PREG(26), (uchar *)input+ibase_0);
   __offset += 26;

   return 26u;
}

void vcop_psort2_1step_kernel_vloops(
   unsigned short pblock[])
{
   /* Kernel-wide Vector Registers */
   #pragma VCC_VREG("Vin0", 16);
   #pragma VCC_VREG("Vin0_c", 17);
   #pragma VCC_VREG("Vin0_d", 18);
   #pragma VCC_VREG("Vin1", 19);
   #pragma VCC_VREG("Vin2", 20);
   #pragma VCC_VREG("Vin3", 21);
   #pragma VCC_VREG("Vin4", 22);
   #pragma VCC_VREG("Vin5", 23);
   #pragma VCC_VREG("Vin6", 24);
   #pragma VCC_VREG("Vin7", 25);
   #pragma VCC_VREG("Vindex1", 26);
   #pragma VCC_VREG("Vindex2", 27);

   __vcop_param(&pblock[0]);

   /* VLOOP 1 Start */

   /* VLOOP Local Vector Registers */
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("Addr_in", "A0");
   #pragma EVE_REG("Addr_in1", "A1");
   #pragma EVE_REG("Addr_in2", "A2");
   #pragma EVE_REG("Addr_ou1", "A3");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I1", "I2");
   #pragma EVE_REG("I2", "I3");
   #pragma EVE_REG("I3", "I4");
   

   __vcop_vloop(__vcop_compute(), 12u, 13u, 1u);
   __vcop_vagen(_AGEN(0), _PREG(0), _PREG(12), _PREG(13), _PREG(0));
   __vcop_vagen(_AGEN(1), _PREG(14), _PREG(15), _PREG(16), _PREG(0));
   __vcop_vagen(_AGEN(2), _PREG(17), _PREG(18), _PREG(19), _PREG(0));
   __vcop_vagen(_AGEN(3), _PREG(20), _PREG(21), _PREG(22), _PREG(0));
   __vcop_vload(__vcop_sizeW(), __vcop_npt(), _PREG(24), _AGEN(0), _VREG(27), __vcop_alws_condload());
   __vcop_vload(__vcop_sizeWU(), __vcop_npt(), _PREG(26), _AGEN(1), _VREG(17), __vcop_alws());
   __vcop_vload(__vcop_sizeWU(), __vcop_npt(), _PREG(6), _AGEN(2), _VREG(19), __vcop_alws());
   __vcop_vsort2(_VREG(17), _VREG(19));
   __vcop_vor(_VREG(27), _VREG(27), _VREG(16));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeWU(), __vcop_pdda(_VREG(16)), __vcop_alws(), _VREG(17), _PREG(8), _AGEN(3), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeWU(), __vcop_pdda(_VREG(16)), __vcop_alws(), _VREG(19), _PREG(10), _AGEN(3), _PREG(0));
   __vcop_vloop_end(1u);

}

void vcop_psort2_1step_kernel(
   int niter1,
   int niter2,
   int niter3,
   int ibase_0,
   int ibase_1,
   int in1ptr_w1,
   int in1ptr_w2,
   int in1ptr_w3,
   int in2ptr_w1,
   int in2ptr_w2,
   int in2ptr_w3,
   int obase_0,
   int obase_1,
   int outptr_w1,
   int outptr_w2,
   int outptr_w3,
   __vptr_uint32 input,
   __vptr_uint32 output,
   __vptr_int32 out_ofst)
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_psort2_1step_kernel_init(niter1, niter2, niter3, ibase_0, ibase_1, in1ptr_w1, in1ptr_w2, in1ptr_w3, in2ptr_w1, in2ptr_w2, in2ptr_w3, obase_0, obase_1, outptr_w1, outptr_w2, outptr_w3, input, output, out_ofst, __pblock_vcop_psort2_1step_kernel);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_psort2_1step_kernel_vloops(__pblock_vcop_psort2_1step_kernel);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

void vcop_psort2_1step_kernel_custom(
   int niter1,
   int niter2,
   int niter3,
   int ibase_0,
   int ibase_1,
   int in1ptr_w1,
   int in1ptr_w2,
   int in1ptr_w3,
   int in2ptr_w1,
   int in2ptr_w2,
   int in2ptr_w3,
   int obase_0,
   int obase_1,
   int outptr_w1,
   int outptr_w2,
   int outptr_w3,
   __vptr_uint32 input,
   __vptr_uint32 output,
   __vptr_int32 out_ofst,
   unsigned short pblock[])
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_psort2_1step_kernel_init(niter1, niter2, niter3, ibase_0, ibase_1, in1ptr_w1, in1ptr_w2, in1ptr_w3, in2ptr_w1, in2ptr_w2, in2ptr_w3, obase_0, obase_1, outptr_w1, outptr_w2, outptr_w3, input, output, out_ofst, pblock);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_psort2_1step_kernel_vloops(pblock);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

#pragma DATA_SECTION(__pblock_vcop_psort2_2steps_reverse_kernel, ".vcop_parameter_block")
#pragma DATA_ALIGN(__pblock_vcop_psort2_2steps_reverse_kernel, __ALIGNOF__(int));
unsigned short __pblock_vcop_psort2_2steps_reverse_kernel[36];

unsigned int vcop_psort2_2steps_reverse_kernel_param_count(void)
{
   return 36u;
}

unsigned int vcop_psort2_2steps_reverse_kernel_ctrl_count(void)
{
   return 0u;
}

unsigned int vcop_psort2_2steps_reverse_kernel_init(
   int niter1,
   int niter2,
   int niter3,
   int ibase_0,
   int ibase_1,
   int ibase_2,
   int ibase_3,
   int in1ptr_w1,
   int in1ptr_w2,
   int in1ptr_w3,
   int in2ptr_w1,
   int in2ptr_w2,
   int in2ptr_w3,
   int obase_0,
   int obase_1,
   int obase_2,
   int obase_3,
   int outptr_w1,
   int outptr_w2,
   int outptr_w3,
   __vptr_uint32 input,
   __vptr_uint32 output,
   __vptr_int32 out_ofst,
   unsigned short pblock[])
{
   int __offset = 0;
   /* Loop 1 PREGS */
   unsigned char cust_arr2[8] = {7, 6, 5, 4, 3, 2, 1, 0};

   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), (niter1)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), (niter2)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), (niter3)-1u);
   __vcop_pblock_init32(pblock, __offset+_PREG(6), (uchar *)input+ibase_2);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), _CUSTOM(cust_arr2));
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)input+ibase_3);
   __vcop_pblock_init32(pblock, __offset+_PREG(12), (uchar *)out_ofst);
   __vcop_pblock_init32(pblock, __offset+_PREG(14), (uchar *)output+obase_0);
   __vcop_pblock_init32(pblock, __offset+_PREG(16), (uchar *)output+obase_1);
   __vcop_pblock_init32(pblock, __offset+_PREG(18), (uchar *)output+obase_2);
   __vcop_pblock_init32(pblock, __offset+_PREG(20), (uchar *)output+obase_3);
   __vcop_pblock_init16(pblock, __offset+_PREG(22), (0) -(0)*((niter3)-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(23), (0) -(0)*((niter2)-1u) -(0)*((niter3)-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(24), (in1ptr_w3));
   __vcop_pblock_init16(pblock, __offset+_PREG(25), (in1ptr_w2) -(in1ptr_w3)*((niter3)-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(26), (in1ptr_w1) -(in1ptr_w2)*((niter2)-1u) -(in1ptr_w3)*((niter3)-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(27), (in2ptr_w3));
   __vcop_pblock_init16(pblock, __offset+_PREG(28), (in2ptr_w2) -(in2ptr_w3)*((niter3)-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(29), (in2ptr_w1) -(in2ptr_w2)*((niter2)-1u) -(in2ptr_w3)*((niter3)-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(30), (outptr_w3));
   __vcop_pblock_init16(pblock, __offset+_PREG(31), (outptr_w2) -(outptr_w3)*((niter3)-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(32), (outptr_w1) -(outptr_w2)*((niter2)-1u) -(outptr_w3)*((niter3)-1u));
   __vcop_pblock_init32(pblock, __offset+_PREG(34), (uchar *)input+ibase_0);
   __vcop_pblock_init32(pblock, __offset+_PREG(36), (uchar *)input+ibase_1);
   __offset += 36;

   return 36u;
}

void vcop_psort2_2steps_reverse_kernel_vloops(
   unsigned short pblock[])
{
   /* Kernel-wide Vector Registers */
   #pragma VCC_VREG("Vin0", 16);
   #pragma VCC_VREG("Vin0_c", 17);
   #pragma VCC_VREG("Vin0_d", 18);
   #pragma VCC_VREG("Vin1", 19);
   #pragma VCC_VREG("Vin2", 20);
   #pragma VCC_VREG("Vin3", 21);
   #pragma VCC_VREG("Vin4", 22);
   #pragma VCC_VREG("Vin5", 23);
   #pragma VCC_VREG("Vin6", 24);
   #pragma VCC_VREG("Vin7", 25);
   #pragma VCC_VREG("Vindex1", 26);
   #pragma VCC_VREG("Vindex2", 27);

   __vcop_param(&pblock[0]);

   /* VLOOP 1 Start */

   /* VLOOP Local Vector Registers */
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("Addr_in", "A0");
   #pragma EVE_REG("Addr_in1", "A1");
   #pragma EVE_REG("Addr_in2", "A2");
   #pragma EVE_REG("Addr_ou1", "A3");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I1", "I2");
   #pragma EVE_REG("I2", "I3");
   #pragma EVE_REG("I3", "I4");
   

   __vcop_vloop(__vcop_compute(), 20u, 18u, 1u);
   __vcop_vagen(_AGEN(0), _PREG(0), _PREG(22), _PREG(23), _PREG(0));
   __vcop_vagen(_AGEN(1), _PREG(24), _PREG(25), _PREG(26), _PREG(0));
   __vcop_vagen(_AGEN(3), _PREG(30), _PREG(31), _PREG(32), _PREG(0));
   __vcop_vload(__vcop_sizeWU(), __vcop_npt(), _PREG(34), _AGEN(1), _VREG(16), __vcop_alws());
   __vcop_vload(__vcop_sizeWU(), __vcop_npt(), _PREG(36), _AGEN(1), _VREG(19), __vcop_alws());
   __vcop_vload(__vcop_sizeWU(), __vcop_cust_p8(), _PREG(6), _AGEN(1), _VREG(20), __vcop_alws());
   __vcop_vload(__vcop_sizeWU(), __vcop_cust_p8(), _PREG(10), _AGEN(1), _VREG(21), __vcop_alws());
   __vcop_vload(__vcop_sizeW(), __vcop_npt(), _PREG(12), _AGEN(0), _VREG(27), __vcop_alws_condload());
   __vcop_vsort2(_VREG(16), _VREG(20));
   __vcop_vsort2(_VREG(19), _VREG(21));
   __vcop_vsort2(_VREG(16), _VREG(19));
   __vcop_vsort2(_VREG(20), _VREG(21));
   __vcop_vor(_VREG(16), _VREG(16), _VREG(18));
   __vcop_vor(_VREG(27), _VREG(27), _VREG(16));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeWU(), __vcop_pdda(_VREG(16)), __vcop_alws(), _VREG(18), _PREG(14), _AGEN(3), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeWU(), __vcop_pdda(_VREG(16)), __vcop_alws(), _VREG(19), _PREG(16), _AGEN(3), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeWU(), __vcop_pdda(_VREG(16)), __vcop_alws(), _VREG(20), _PREG(18), _AGEN(3), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeWU(), __vcop_pdda(_VREG(16)), __vcop_alws(), _VREG(21), _PREG(20), _AGEN(3), _PREG(0));
   __vcop_vloop_end(1u);

}

void vcop_psort2_2steps_reverse_kernel(
   int niter1,
   int niter2,
   int niter3,
   int ibase_0,
   int ibase_1,
   int ibase_2,
   int ibase_3,
   int in1ptr_w1,
   int in1ptr_w2,
   int in1ptr_w3,
   int in2ptr_w1,
   int in2ptr_w2,
   int in2ptr_w3,
   int obase_0,
   int obase_1,
   int obase_2,
   int obase_3,
   int outptr_w1,
   int outptr_w2,
   int outptr_w3,
   __vptr_uint32 input,
   __vptr_uint32 output,
   __vptr_int32 out_ofst)
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_psort2_2steps_reverse_kernel_init(niter1, niter2, niter3, ibase_0, ibase_1, ibase_2, ibase_3, in1ptr_w1, in1ptr_w2, in1ptr_w3, in2ptr_w1, in2ptr_w2, in2ptr_w3, obase_0, obase_1, obase_2, obase_3, outptr_w1, outptr_w2, outptr_w3, input, output, out_ofst, __pblock_vcop_psort2_2steps_reverse_kernel);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_psort2_2steps_reverse_kernel_vloops(__pblock_vcop_psort2_2steps_reverse_kernel);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

void vcop_psort2_2steps_reverse_kernel_custom(
   int niter1,
   int niter2,
   int niter3,
   int ibase_0,
   int ibase_1,
   int ibase_2,
   int ibase_3,
   int in1ptr_w1,
   int in1ptr_w2,
   int in1ptr_w3,
   int in2ptr_w1,
   int in2ptr_w2,
   int in2ptr_w3,
   int obase_0,
   int obase_1,
   int obase_2,
   int obase_3,
   int outptr_w1,
   int outptr_w2,
   int outptr_w3,
   __vptr_uint32 input,
   __vptr_uint32 output,
   __vptr_int32 out_ofst,
   unsigned short pblock[])
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_psort2_2steps_reverse_kernel_init(niter1, niter2, niter3, ibase_0, ibase_1, ibase_2, ibase_3, in1ptr_w1, in1ptr_w2, in1ptr_w3, in2ptr_w1, in2ptr_w2, in2ptr_w3, obase_0, obase_1, obase_2, obase_3, outptr_w1, outptr_w2, outptr_w3, input, output, out_ofst, pblock);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_psort2_2steps_reverse_kernel_vloops(pblock);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

#pragma DATA_SECTION(__pblock_vcop_psort2_2steps_kernel, ".vcop_parameter_block")
#pragma DATA_ALIGN(__pblock_vcop_psort2_2steps_kernel, __ALIGNOF__(int));
unsigned short __pblock_vcop_psort2_2steps_kernel[34];

unsigned int vcop_psort2_2steps_kernel_param_count(void)
{
   return 34u;
}

unsigned int vcop_psort2_2steps_kernel_ctrl_count(void)
{
   return 0u;
}

unsigned int vcop_psort2_2steps_kernel_init(
   int niter1,
   int niter2,
   int niter3,
   int ibase_0,
   int ibase_1,
   int ibase_2,
   int ibase_3,
   int in1ptr_w1,
   int in1ptr_w2,
   int in1ptr_w3,
   int in2ptr_w1,
   int in2ptr_w2,
   int in2ptr_w3,
   int obase_0,
   int obase_1,
   int obase_2,
   int obase_3,
   int outptr_w1,
   int outptr_w2,
   int outptr_w3,
   __vptr_uint32 input,
   __vptr_uint32 output,
   __vptr_int32 out_ofst,
   unsigned short pblock[])
{
   int __offset = 0;
   /* Loop 1 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), (niter1)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), (niter2)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), (niter3)-1u);
   __vcop_pblock_init32(pblock, __offset+_PREG(6), (uchar *)input+ibase_2);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)input+ibase_3);
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)out_ofst);
   __vcop_pblock_init32(pblock, __offset+_PREG(12), (uchar *)output+obase_0);
   __vcop_pblock_init32(pblock, __offset+_PREG(14), (uchar *)output+obase_1);
   __vcop_pblock_init32(pblock, __offset+_PREG(16), (uchar *)output+obase_2);
   __vcop_pblock_init32(pblock, __offset+_PREG(18), (uchar *)output+obase_3);
   __vcop_pblock_init16(pblock, __offset+_PREG(20), (0) -(0)*((niter3)-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(21), (0) -(0)*((niter2)-1u) -(0)*((niter3)-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(22), (in1ptr_w3));
   __vcop_pblock_init16(pblock, __offset+_PREG(23), (in1ptr_w2) -(in1ptr_w3)*((niter3)-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(24), (in1ptr_w1) -(in1ptr_w2)*((niter2)-1u) -(in1ptr_w3)*((niter3)-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(25), (in2ptr_w3));
   __vcop_pblock_init16(pblock, __offset+_PREG(26), (in2ptr_w2) -(in2ptr_w3)*((niter3)-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(27), (in2ptr_w1) -(in2ptr_w2)*((niter2)-1u) -(in2ptr_w3)*((niter3)-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(28), (outptr_w3));
   __vcop_pblock_init16(pblock, __offset+_PREG(29), (outptr_w2) -(outptr_w3)*((niter3)-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(30), (outptr_w1) -(outptr_w2)*((niter2)-1u) -(outptr_w3)*((niter3)-1u));
   __vcop_pblock_init32(pblock, __offset+_PREG(32), (uchar *)input+ibase_0);
   __vcop_pblock_init32(pblock, __offset+_PREG(34), (uchar *)input+ibase_1);
   __offset += 34;

   return 34u;
}

void vcop_psort2_2steps_kernel_vloops(
   unsigned short pblock[])
{
   /* Kernel-wide Vector Registers */
   #pragma VCC_VREG("Vin0", 16);
   #pragma VCC_VREG("Vin0_c", 17);
   #pragma VCC_VREG("Vin0_d", 18);
   #pragma VCC_VREG("Vin1", 19);
   #pragma VCC_VREG("Vin2", 20);
   #pragma VCC_VREG("Vin3", 21);
   #pragma VCC_VREG("Vin4", 22);
   #pragma VCC_VREG("Vin5", 23);
   #pragma VCC_VREG("Vin6", 24);
   #pragma VCC_VREG("Vin7", 25);
   #pragma VCC_VREG("Vindex1", 26);
   #pragma VCC_VREG("Vindex2", 27);

   __vcop_param(&pblock[0]);

   /* VLOOP 1 Start */

   /* VLOOP Local Vector Registers */
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("Addr_in", "A0");
   #pragma EVE_REG("Addr_in1", "A1");
   #pragma EVE_REG("Addr_in2", "A2");
   #pragma EVE_REG("Addr_ou1", "A3");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I1", "I2");
   #pragma EVE_REG("I2", "I3");
   #pragma EVE_REG("I3", "I4");
   

   __vcop_vloop(__vcop_compute(), 20u, 17u, 1u);
   __vcop_vagen(_AGEN(0), _PREG(0), _PREG(20), _PREG(21), _PREG(0));
   __vcop_vagen(_AGEN(1), _PREG(22), _PREG(23), _PREG(24), _PREG(0));
   __vcop_vagen(_AGEN(3), _PREG(28), _PREG(29), _PREG(30), _PREG(0));
   __vcop_vload(__vcop_sizeWU(), __vcop_npt(), _PREG(32), _AGEN(1), _VREG(16), __vcop_alws());
   __vcop_vload(__vcop_sizeWU(), __vcop_npt(), _PREG(34), _AGEN(1), _VREG(19), __vcop_alws());
   __vcop_vload(__vcop_sizeWU(), __vcop_npt(), _PREG(6), _AGEN(1), _VREG(20), __vcop_alws());
   __vcop_vload(__vcop_sizeWU(), __vcop_npt(), _PREG(8), _AGEN(1), _VREG(21), __vcop_alws());
   __vcop_vload(__vcop_sizeW(), __vcop_npt(), _PREG(10), _AGEN(0), _VREG(27), __vcop_alws_condload());
   __vcop_vsort2(_VREG(16), _VREG(20));
   __vcop_vsort2(_VREG(19), _VREG(21));
   __vcop_vsort2(_VREG(16), _VREG(19));
   __vcop_vsort2(_VREG(20), _VREG(21));
   __vcop_vor(_VREG(16), _VREG(16), _VREG(18));
   __vcop_vor(_VREG(27), _VREG(27), _VREG(16));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeWU(), __vcop_pdda(_VREG(16)), __vcop_alws(), _VREG(18), _PREG(12), _AGEN(3), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeWU(), __vcop_pdda(_VREG(16)), __vcop_alws(), _VREG(19), _PREG(14), _AGEN(3), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeWU(), __vcop_pdda(_VREG(16)), __vcop_alws(), _VREG(20), _PREG(16), _AGEN(3), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeWU(), __vcop_pdda(_VREG(16)), __vcop_alws(), _VREG(21), _PREG(18), _AGEN(3), _PREG(0));
   __vcop_vloop_end(1u);

}

void vcop_psort2_2steps_kernel(
   int niter1,
   int niter2,
   int niter3,
   int ibase_0,
   int ibase_1,
   int ibase_2,
   int ibase_3,
   int in1ptr_w1,
   int in1ptr_w2,
   int in1ptr_w3,
   int in2ptr_w1,
   int in2ptr_w2,
   int in2ptr_w3,
   int obase_0,
   int obase_1,
   int obase_2,
   int obase_3,
   int outptr_w1,
   int outptr_w2,
   int outptr_w3,
   __vptr_uint32 input,
   __vptr_uint32 output,
   __vptr_int32 out_ofst)
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_psort2_2steps_kernel_init(niter1, niter2, niter3, ibase_0, ibase_1, ibase_2, ibase_3, in1ptr_w1, in1ptr_w2, in1ptr_w3, in2ptr_w1, in2ptr_w2, in2ptr_w3, obase_0, obase_1, obase_2, obase_3, outptr_w1, outptr_w2, outptr_w3, input, output, out_ofst, __pblock_vcop_psort2_2steps_kernel);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_psort2_2steps_kernel_vloops(__pblock_vcop_psort2_2steps_kernel);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

void vcop_psort2_2steps_kernel_custom(
   int niter1,
   int niter2,
   int niter3,
   int ibase_0,
   int ibase_1,
   int ibase_2,
   int ibase_3,
   int in1ptr_w1,
   int in1ptr_w2,
   int in1ptr_w3,
   int in2ptr_w1,
   int in2ptr_w2,
   int in2ptr_w3,
   int obase_0,
   int obase_1,
   int obase_2,
   int obase_3,
   int outptr_w1,
   int outptr_w2,
   int outptr_w3,
   __vptr_uint32 input,
   __vptr_uint32 output,
   __vptr_int32 out_ofst,
   unsigned short pblock[])
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_psort2_2steps_kernel_init(niter1, niter2, niter3, ibase_0, ibase_1, ibase_2, ibase_3, in1ptr_w1, in1ptr_w2, in1ptr_w3, in2ptr_w1, in2ptr_w2, in2ptr_w3, obase_0, obase_1, obase_2, obase_3, outptr_w1, outptr_w2, outptr_w3, input, output, out_ofst, pblock);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_psort2_2steps_kernel_vloops(pblock);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

#pragma DATA_SECTION(__pblock_vcop_psort2_3steps_reverse_kernel, ".vcop_parameter_block")
#pragma DATA_ALIGN(__pblock_vcop_psort2_3steps_reverse_kernel, __ALIGNOF__(int));
unsigned short __pblock_vcop_psort2_3steps_reverse_kernel[54];

unsigned int vcop_psort2_3steps_reverse_kernel_param_count(void)
{
   return 54u;
}

unsigned int vcop_psort2_3steps_reverse_kernel_ctrl_count(void)
{
   return 0u;
}

unsigned int vcop_psort2_3steps_reverse_kernel_init(
   int niter1,
   int niter2,
   int niter3,
   int ibase_0,
   int ibase_1,
   int ibase_2,
   int ibase_3,
   int ibase_4,
   int ibase_5,
   int ibase_6,
   int ibase_7,
   int in1ptr_w1,
   int in1ptr_w2,
   int in1ptr_w3,
   int in2ptr_w1,
   int in2ptr_w2,
   int in2ptr_w3,
   int obase_0,
   int obase_1,
   int obase_2,
   int obase_3,
   int obase_4,
   int obase_5,
   int obase_6,
   int obase_7,
   int outptr_w1,
   int outptr_w2,
   int outptr_w3,
   __vptr_uint32 input,
   __vptr_uint32 output,
   __vptr_int32 out_ofst,
   unsigned short pblock[])
{
   int __offset = 0;
   /* Loop 1 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), (1)-1u);
   __vcop_pblock_init32(pblock, __offset+_PREG(6), (uchar *)out_ofst);
   __offset += 6;

   /* Loop 2 PREGS */
   unsigned char cust_arr3[8] = {7, 6, 5, 4, 3, 2, 1, 0};

   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), (niter1)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), (niter2)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), (niter3)-1u);
   __vcop_pblock_init32(pblock, __offset+_PREG(6), (uchar *)input+ibase_2);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), _CUSTOM(cust_arr3));
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)input+ibase_3);
   __vcop_pblock_init32(pblock, __offset+_PREG(12), (uchar *)input+ibase_4);
   __vcop_pblock_init32(pblock, __offset+_PREG(14), (uchar *)input+ibase_5);
   __vcop_pblock_init32(pblock, __offset+_PREG(16), (uchar *)input+ibase_6);
   __vcop_pblock_init32(pblock, __offset+_PREG(18), (uchar *)input+ibase_7);
   __vcop_pblock_init32(pblock, __offset+_PREG(20), (uchar *)output+obase_0);
   __vcop_pblock_init32(pblock, __offset+_PREG(22), (uchar *)output+obase_1);
   __vcop_pblock_init32(pblock, __offset+_PREG(24), (uchar *)output+obase_2);
   __vcop_pblock_init32(pblock, __offset+_PREG(26), (uchar *)output+obase_3);
   __vcop_pblock_init32(pblock, __offset+_PREG(28), (uchar *)output+obase_4);
   __vcop_pblock_init32(pblock, __offset+_PREG(30), (uchar *)output+obase_5);
   __vcop_pblock_init32(pblock, __offset+_PREG(32), (uchar *)output+obase_6);
   __vcop_pblock_init32(pblock, __offset+_PREG(34), (uchar *)output+obase_7);
   __vcop_pblock_init16(pblock, __offset+_PREG(36), (in1ptr_w3));
   __vcop_pblock_init16(pblock, __offset+_PREG(37), (in1ptr_w2) -(in1ptr_w3)*((niter3)-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(38), (in1ptr_w1) -(in1ptr_w2)*((niter2)-1u) -(in1ptr_w3)*((niter3)-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(39), (in2ptr_w3));
   __vcop_pblock_init16(pblock, __offset+_PREG(40), (in2ptr_w2) -(in2ptr_w3)*((niter3)-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(41), (in2ptr_w1) -(in2ptr_w2)*((niter2)-1u) -(in2ptr_w3)*((niter3)-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(42), (outptr_w3));
   __vcop_pblock_init16(pblock, __offset+_PREG(43), (outptr_w2) -(outptr_w3)*((niter3)-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(44), (outptr_w1) -(outptr_w2)*((niter2)-1u) -(outptr_w3)*((niter3)-1u));
   __vcop_pblock_init32(pblock, __offset+_PREG(46), (uchar *)input+ibase_0);
   __vcop_pblock_init32(pblock, __offset+_PREG(48), (uchar *)input+ibase_1);
   __offset += 48;

   return 54u;
}

void vcop_psort2_3steps_reverse_kernel_vloops(
   unsigned short pblock[])
{
   /* Kernel-wide Vector Registers */
   #pragma VCC_VREG("Vin0", 16);
   #pragma VCC_VREG("Vin0_c", 17);
   #pragma VCC_VREG("Vin0_d", 18);
   #pragma VCC_VREG("Vin1", 19);
   #pragma VCC_VREG("Vin2", 20);
   #pragma VCC_VREG("Vin3", 21);
   #pragma VCC_VREG("Vin4", 22);
   #pragma VCC_VREG("Vin5", 23);
   #pragma VCC_VREG("Vin6", 24);
   #pragma VCC_VREG("Vin7", 25);
   #pragma VCC_VREG("Vindex1", 26);
   #pragma VCC_VREG("Vindex2", 27);

   __vcop_param(&pblock[0]);

   /* VLOOP 1 Start */

   /* VLOOP Local Vector Registers */
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("Addr_in", "A0");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I1", "I4");
   

   __vcop_vloop(__vcop_compute(), 4u, 3u, 1u);
   __vcop_vagen(_AGEN(0), _PREG(0), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeW(), __vcop_npt(), _PREG(6), _AGEN(0), _VREG(26), __vcop_alws_condload());
   __vcop_vor(_VREG(26), _VREG(26), _VREG(27));
   __vcop_vloop_end(1u);

   /* VLOOP 2 Start */

   /* VLOOP Local Vector Registers */
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("Addr_in1", "A0");
   #pragma EVE_REG("Addr_in2", "A1");
   #pragma EVE_REG("Addr_ou1", "A2");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I1", "I2");
   #pragma EVE_REG("I2", "I3");
   #pragma EVE_REG("I3", "I4");
   

   __vcop_vloop(__vcop_compute(), 34u, 24u, 2u);
   __vcop_vagen(_AGEN(0), _PREG(36), _PREG(37), _PREG(38), _PREG(0));
   __vcop_vagen(_AGEN(1), _PREG(39), _PREG(40), _PREG(41), _PREG(0));
   __vcop_vagen(_AGEN(2), _PREG(42), _PREG(43), _PREG(44), _PREG(0));
   __vcop_vload(__vcop_sizeWU(), __vcop_npt(), _PREG(46), _AGEN(0), _VREG(16), __vcop_alws());
   __vcop_vload(__vcop_sizeWU(), __vcop_npt(), _PREG(48), _AGEN(0), _VREG(19), __vcop_alws());
   __vcop_vload(__vcop_sizeWU(), __vcop_npt(), _PREG(6), _AGEN(0), _VREG(20), __vcop_alws());
   __vcop_vload(__vcop_sizeWU(), __vcop_npt(), _PREG(10), _AGEN(0), _VREG(21), __vcop_alws());
   __vcop_vload(__vcop_sizeWU(), __vcop_cust_p8(), _PREG(12), _AGEN(1), _VREG(22), __vcop_alws());
   __vcop_vload(__vcop_sizeWU(), __vcop_cust_p8(), _PREG(14), _AGEN(1), _VREG(23), __vcop_alws());
   __vcop_vload(__vcop_sizeWU(), __vcop_cust_p8(), _PREG(16), _AGEN(1), _VREG(24), __vcop_alws());
   __vcop_vload(__vcop_sizeWU(), __vcop_cust_p8(), _PREG(18), _AGEN(1), _VREG(25), __vcop_alws());
   __vcop_vsort2(_VREG(16), _VREG(22));
   __vcop_vsort2(_VREG(19), _VREG(23));
   __vcop_vsort2(_VREG(20), _VREG(24));
   __vcop_vsort2(_VREG(21), _VREG(25));
   __vcop_vsort2(_VREG(16), _VREG(20));
   __vcop_vsort2(_VREG(19), _VREG(21));
   __vcop_vsort2(_VREG(22), _VREG(24));
   __vcop_vsort2(_VREG(23), _VREG(25));
   __vcop_vsort2(_VREG(16), _VREG(19));
   __vcop_vsort2(_VREG(20), _VREG(21));
   __vcop_vsort2(_VREG(22), _VREG(23));
   __vcop_vsort2(_VREG(24), _VREG(25));
   __vcop_vor(_VREG(16), _VREG(16), _VREG(18));
   __vcop_vor(_VREG(27), _VREG(27), _VREG(16));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeWU(), __vcop_pdda(_VREG(16)), __vcop_alws(), _VREG(18), _PREG(20), _AGEN(2), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeWU(), __vcop_pdda(_VREG(16)), __vcop_alws(), _VREG(19), _PREG(22), _AGEN(2), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeWU(), __vcop_pdda(_VREG(16)), __vcop_alws(), _VREG(20), _PREG(24), _AGEN(2), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeWU(), __vcop_pdda(_VREG(16)), __vcop_alws(), _VREG(21), _PREG(26), _AGEN(2), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeWU(), __vcop_pdda(_VREG(16)), __vcop_alws(), _VREG(22), _PREG(28), _AGEN(2), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeWU(), __vcop_pdda(_VREG(16)), __vcop_alws(), _VREG(23), _PREG(30), _AGEN(2), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeWU(), __vcop_pdda(_VREG(16)), __vcop_alws(), _VREG(24), _PREG(32), _AGEN(2), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeWU(), __vcop_pdda(_VREG(16)), __vcop_alws(), _VREG(25), _PREG(34), _AGEN(2), _PREG(0));
   __vcop_vloop_end(2u);

}

void vcop_psort2_3steps_reverse_kernel(
   int niter1,
   int niter2,
   int niter3,
   int ibase_0,
   int ibase_1,
   int ibase_2,
   int ibase_3,
   int ibase_4,
   int ibase_5,
   int ibase_6,
   int ibase_7,
   int in1ptr_w1,
   int in1ptr_w2,
   int in1ptr_w3,
   int in2ptr_w1,
   int in2ptr_w2,
   int in2ptr_w3,
   int obase_0,
   int obase_1,
   int obase_2,
   int obase_3,
   int obase_4,
   int obase_5,
   int obase_6,
   int obase_7,
   int outptr_w1,
   int outptr_w2,
   int outptr_w3,
   __vptr_uint32 input,
   __vptr_uint32 output,
   __vptr_int32 out_ofst)
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_psort2_3steps_reverse_kernel_init(niter1, niter2, niter3, ibase_0, ibase_1, ibase_2, ibase_3, ibase_4, ibase_5, ibase_6, ibase_7, in1ptr_w1, in1ptr_w2, in1ptr_w3, in2ptr_w1, in2ptr_w2, in2ptr_w3, obase_0, obase_1, obase_2, obase_3, obase_4, obase_5, obase_6, obase_7, outptr_w1, outptr_w2, outptr_w3, input, output, out_ofst, __pblock_vcop_psort2_3steps_reverse_kernel);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_psort2_3steps_reverse_kernel_vloops(__pblock_vcop_psort2_3steps_reverse_kernel);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

void vcop_psort2_3steps_reverse_kernel_custom(
   int niter1,
   int niter2,
   int niter3,
   int ibase_0,
   int ibase_1,
   int ibase_2,
   int ibase_3,
   int ibase_4,
   int ibase_5,
   int ibase_6,
   int ibase_7,
   int in1ptr_w1,
   int in1ptr_w2,
   int in1ptr_w3,
   int in2ptr_w1,
   int in2ptr_w2,
   int in2ptr_w3,
   int obase_0,
   int obase_1,
   int obase_2,
   int obase_3,
   int obase_4,
   int obase_5,
   int obase_6,
   int obase_7,
   int outptr_w1,
   int outptr_w2,
   int outptr_w3,
   __vptr_uint32 input,
   __vptr_uint32 output,
   __vptr_int32 out_ofst,
   unsigned short pblock[])
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_psort2_3steps_reverse_kernel_init(niter1, niter2, niter3, ibase_0, ibase_1, ibase_2, ibase_3, ibase_4, ibase_5, ibase_6, ibase_7, in1ptr_w1, in1ptr_w2, in1ptr_w3, in2ptr_w1, in2ptr_w2, in2ptr_w3, obase_0, obase_1, obase_2, obase_3, obase_4, obase_5, obase_6, obase_7, outptr_w1, outptr_w2, outptr_w3, input, output, out_ofst, pblock);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_psort2_3steps_reverse_kernel_vloops(pblock);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

#pragma DATA_SECTION(__pblock_vcop_psort2_3steps_kernel, ".vcop_parameter_block")
#pragma DATA_ALIGN(__pblock_vcop_psort2_3steps_kernel, __ALIGNOF__(int));
unsigned short __pblock_vcop_psort2_3steps_kernel[52];

unsigned int vcop_psort2_3steps_kernel_param_count(void)
{
   return 52u;
}

unsigned int vcop_psort2_3steps_kernel_ctrl_count(void)
{
   return 0u;
}

unsigned int vcop_psort2_3steps_kernel_init(
   int niter1,
   int niter2,
   int niter3,
   int ibase_0,
   int ibase_1,
   int ibase_2,
   int ibase_3,
   int ibase_4,
   int ibase_5,
   int ibase_6,
   int ibase_7,
   int in1ptr_w1,
   int in1ptr_w2,
   int in1ptr_w3,
   int in2ptr_w1,
   int in2ptr_w2,
   int in2ptr_w3,
   int obase_0,
   int obase_1,
   int obase_2,
   int obase_3,
   int obase_4,
   int obase_5,
   int obase_6,
   int obase_7,
   int outptr_w1,
   int outptr_w2,
   int outptr_w3,
   __vptr_uint32 input,
   __vptr_uint32 output,
   __vptr_int32 out_ofst,
   unsigned short pblock[])
{
   int __offset = 0;
   /* Loop 1 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), (1)-1u);
   __vcop_pblock_init32(pblock, __offset+_PREG(6), (uchar *)out_ofst);
   __offset += 6;

   /* Loop 2 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), (niter1)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), (niter2)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), (niter3)-1u);
   __vcop_pblock_init32(pblock, __offset+_PREG(6), (uchar *)input+ibase_2);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)input+ibase_3);
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)input+ibase_4);
   __vcop_pblock_init32(pblock, __offset+_PREG(12), (uchar *)input+ibase_5);
   __vcop_pblock_init32(pblock, __offset+_PREG(14), (uchar *)input+ibase_6);
   __vcop_pblock_init32(pblock, __offset+_PREG(16), (uchar *)input+ibase_7);
   __vcop_pblock_init32(pblock, __offset+_PREG(18), (uchar *)output+obase_0);
   __vcop_pblock_init32(pblock, __offset+_PREG(20), (uchar *)output+obase_1);
   __vcop_pblock_init32(pblock, __offset+_PREG(22), (uchar *)output+obase_2);
   __vcop_pblock_init32(pblock, __offset+_PREG(24), (uchar *)output+obase_3);
   __vcop_pblock_init32(pblock, __offset+_PREG(26), (uchar *)output+obase_4);
   __vcop_pblock_init32(pblock, __offset+_PREG(28), (uchar *)output+obase_5);
   __vcop_pblock_init32(pblock, __offset+_PREG(30), (uchar *)output+obase_6);
   __vcop_pblock_init32(pblock, __offset+_PREG(32), (uchar *)output+obase_7);
   __vcop_pblock_init16(pblock, __offset+_PREG(34), (in1ptr_w3));
   __vcop_pblock_init16(pblock, __offset+_PREG(35), (in1ptr_w2) -(in1ptr_w3)*((niter3)-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(36), (in1ptr_w1) -(in1ptr_w2)*((niter2)-1u) -(in1ptr_w3)*((niter3)-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(37), (in2ptr_w3));
   __vcop_pblock_init16(pblock, __offset+_PREG(38), (in2ptr_w2) -(in2ptr_w3)*((niter3)-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(39), (in2ptr_w1) -(in2ptr_w2)*((niter2)-1u) -(in2ptr_w3)*((niter3)-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(40), (outptr_w3));
   __vcop_pblock_init16(pblock, __offset+_PREG(41), (outptr_w2) -(outptr_w3)*((niter3)-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(42), (outptr_w1) -(outptr_w2)*((niter2)-1u) -(outptr_w3)*((niter3)-1u));
   __vcop_pblock_init32(pblock, __offset+_PREG(44), (uchar *)input+ibase_0);
   __vcop_pblock_init32(pblock, __offset+_PREG(46), (uchar *)input+ibase_1);
   __offset += 46;

   return 52u;
}

void vcop_psort2_3steps_kernel_vloops(
   unsigned short pblock[])
{
   /* Kernel-wide Vector Registers */
   #pragma VCC_VREG("Vin0", 16);
   #pragma VCC_VREG("Vin0_c", 17);
   #pragma VCC_VREG("Vin0_d", 18);
   #pragma VCC_VREG("Vin1", 19);
   #pragma VCC_VREG("Vin2", 20);
   #pragma VCC_VREG("Vin3", 21);
   #pragma VCC_VREG("Vin4", 22);
   #pragma VCC_VREG("Vin5", 23);
   #pragma VCC_VREG("Vin6", 24);
   #pragma VCC_VREG("Vin7", 25);
   #pragma VCC_VREG("Vindex1", 26);
   #pragma VCC_VREG("Vindex2", 27);

   __vcop_param(&pblock[0]);

   /* VLOOP 1 Start */

   /* VLOOP Local Vector Registers */
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("Addr_in", "A0");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I1", "I4");
   

   __vcop_vloop(__vcop_compute(), 4u, 3u, 1u);
   __vcop_vagen(_AGEN(0), _PREG(0), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeW(), __vcop_npt(), _PREG(6), _AGEN(0), _VREG(26), __vcop_alws_condload());
   __vcop_vor(_VREG(26), _VREG(26), _VREG(27));
   __vcop_vloop_end(1u);

   /* VLOOP 2 Start */

   /* VLOOP Local Vector Registers */
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("Addr_in1", "A0");
   #pragma EVE_REG("Addr_in2", "A1");
   #pragma EVE_REG("Addr_ou1", "A2");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I1", "I2");
   #pragma EVE_REG("I2", "I3");
   #pragma EVE_REG("I3", "I4");
   

   __vcop_vloop(__vcop_compute(), 34u, 23u, 2u);
   __vcop_vagen(_AGEN(0), _PREG(34), _PREG(35), _PREG(36), _PREG(0));
   __vcop_vagen(_AGEN(1), _PREG(37), _PREG(38), _PREG(39), _PREG(0));
   __vcop_vagen(_AGEN(2), _PREG(40), _PREG(41), _PREG(42), _PREG(0));
   __vcop_vload(__vcop_sizeWU(), __vcop_npt(), _PREG(44), _AGEN(0), _VREG(16), __vcop_alws());
   __vcop_vload(__vcop_sizeWU(), __vcop_npt(), _PREG(46), _AGEN(0), _VREG(19), __vcop_alws());
   __vcop_vload(__vcop_sizeWU(), __vcop_npt(), _PREG(6), _AGEN(0), _VREG(20), __vcop_alws());
   __vcop_vload(__vcop_sizeWU(), __vcop_npt(), _PREG(8), _AGEN(0), _VREG(21), __vcop_alws());
   __vcop_vload(__vcop_sizeWU(), __vcop_npt(), _PREG(10), _AGEN(1), _VREG(22), __vcop_alws());
   __vcop_vload(__vcop_sizeWU(), __vcop_npt(), _PREG(12), _AGEN(1), _VREG(23), __vcop_alws());
   __vcop_vload(__vcop_sizeWU(), __vcop_npt(), _PREG(14), _AGEN(1), _VREG(24), __vcop_alws());
   __vcop_vload(__vcop_sizeWU(), __vcop_npt(), _PREG(16), _AGEN(1), _VREG(25), __vcop_alws());
   __vcop_vsort2(_VREG(16), _VREG(22));
   __vcop_vsort2(_VREG(19), _VREG(23));
   __vcop_vsort2(_VREG(20), _VREG(24));
   __vcop_vsort2(_VREG(21), _VREG(25));
   __vcop_vsort2(_VREG(16), _VREG(20));
   __vcop_vsort2(_VREG(19), _VREG(21));
   __vcop_vsort2(_VREG(22), _VREG(24));
   __vcop_vsort2(_VREG(23), _VREG(25));
   __vcop_vsort2(_VREG(16), _VREG(19));
   __vcop_vsort2(_VREG(20), _VREG(21));
   __vcop_vsort2(_VREG(22), _VREG(23));
   __vcop_vsort2(_VREG(24), _VREG(25));
   __vcop_vor(_VREG(16), _VREG(16), _VREG(18));
   __vcop_vor(_VREG(27), _VREG(27), _VREG(16));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeWU(), __vcop_pdda(_VREG(16)), __vcop_alws(), _VREG(18), _PREG(18), _AGEN(2), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeWU(), __vcop_pdda(_VREG(16)), __vcop_alws(), _VREG(19), _PREG(20), _AGEN(2), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeWU(), __vcop_pdda(_VREG(16)), __vcop_alws(), _VREG(20), _PREG(22), _AGEN(2), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeWU(), __vcop_pdda(_VREG(16)), __vcop_alws(), _VREG(21), _PREG(24), _AGEN(2), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeWU(), __vcop_pdda(_VREG(16)), __vcop_alws(), _VREG(22), _PREG(26), _AGEN(2), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeWU(), __vcop_pdda(_VREG(16)), __vcop_alws(), _VREG(23), _PREG(28), _AGEN(2), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeWU(), __vcop_pdda(_VREG(16)), __vcop_alws(), _VREG(24), _PREG(30), _AGEN(2), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeWU(), __vcop_pdda(_VREG(16)), __vcop_alws(), _VREG(25), _PREG(32), _AGEN(2), _PREG(0));
   __vcop_vloop_end(2u);

}

void vcop_psort2_3steps_kernel(
   int niter1,
   int niter2,
   int niter3,
   int ibase_0,
   int ibase_1,
   int ibase_2,
   int ibase_3,
   int ibase_4,
   int ibase_5,
   int ibase_6,
   int ibase_7,
   int in1ptr_w1,
   int in1ptr_w2,
   int in1ptr_w3,
   int in2ptr_w1,
   int in2ptr_w2,
   int in2ptr_w3,
   int obase_0,
   int obase_1,
   int obase_2,
   int obase_3,
   int obase_4,
   int obase_5,
   int obase_6,
   int obase_7,
   int outptr_w1,
   int outptr_w2,
   int outptr_w3,
   __vptr_uint32 input,
   __vptr_uint32 output,
   __vptr_int32 out_ofst)
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_psort2_3steps_kernel_init(niter1, niter2, niter3, ibase_0, ibase_1, ibase_2, ibase_3, ibase_4, ibase_5, ibase_6, ibase_7, in1ptr_w1, in1ptr_w2, in1ptr_w3, in2ptr_w1, in2ptr_w2, in2ptr_w3, obase_0, obase_1, obase_2, obase_3, obase_4, obase_5, obase_6, obase_7, outptr_w1, outptr_w2, outptr_w3, input, output, out_ofst, __pblock_vcop_psort2_3steps_kernel);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_psort2_3steps_kernel_vloops(__pblock_vcop_psort2_3steps_kernel);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

void vcop_psort2_3steps_kernel_custom(
   int niter1,
   int niter2,
   int niter3,
   int ibase_0,
   int ibase_1,
   int ibase_2,
   int ibase_3,
   int ibase_4,
   int ibase_5,
   int ibase_6,
   int ibase_7,
   int in1ptr_w1,
   int in1ptr_w2,
   int in1ptr_w3,
   int in2ptr_w1,
   int in2ptr_w2,
   int in2ptr_w3,
   int obase_0,
   int obase_1,
   int obase_2,
   int obase_3,
   int obase_4,
   int obase_5,
   int obase_6,
   int obase_7,
   int outptr_w1,
   int outptr_w2,
   int outptr_w3,
   __vptr_uint32 input,
   __vptr_uint32 output,
   __vptr_int32 out_ofst,
   unsigned short pblock[])
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_psort2_3steps_kernel_init(niter1, niter2, niter3, ibase_0, ibase_1, ibase_2, ibase_3, ibase_4, ibase_5, ibase_6, ibase_7, in1ptr_w1, in1ptr_w2, in1ptr_w3, in2ptr_w1, in2ptr_w2, in2ptr_w3, obase_0, obase_1, obase_2, obase_3, obase_4, obase_5, obase_6, obase_7, outptr_w1, outptr_w2, outptr_w3, input, output, out_ofst, pblock);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_psort2_3steps_kernel_vloops(pblock);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

#pragma DATA_SECTION(__pblock_vcop_remove_ex_col, ".vcop_parameter_block")
#pragma DATA_ALIGN(__pblock_vcop_remove_ex_col, __ALIGNOF__(int));
unsigned short __pblock_vcop_remove_ex_col[12];

unsigned int vcop_remove_ex_col_param_count(void)
{
   return 12u;
}

unsigned int vcop_remove_ex_col_ctrl_count(void)
{
   return 0u;
}

unsigned int vcop_remove_ex_col_init(
   __vptr_uint32 input,
   __vptr_uint32 output,
   int nitems,
   unsigned short pblock[])
{
   int __offset = 0;
   /* Loop 1 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), (8)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), (nitems/64)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(6), 32);
   __vcop_pblock_init16(pblock, __offset+_PREG(7), ((nitems/8+1)*sizeof(*input)) -((8u*sizeof(*input)))*((nitems/64)-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(8), ((nitems/8)*sizeof(*output)) -((8u*sizeof(*input)))*((nitems/64)-1u));
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)input);
   __vcop_pblock_init32(pblock, __offset+_PREG(12), (uchar *)output);
   __offset += 12;

   return 12u;
}

void vcop_remove_ex_col_vloops(
   unsigned short pblock[])
{
   /* Kernel-wide Vector Registers */
   #pragma VCC_VREG("Vinp_data", 16);

   __vcop_param(&pblock[0]);

   /* VLOOP 1 Start */

   /* VLOOP Local Vector Registers */
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("Addr_i", "A0");
   #pragma EVE_REG("Addr_o", "A1");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I3", "I3");
   #pragma EVE_REG("I4", "I4");
   

   __vcop_vloop(__vcop_compute(), 5u, 6u, 1u);
   __vcop_vagen(_AGEN(0), _PREG(6), _PREG(7), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(1), _PREG(6), _PREG(8), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeWU(), __vcop_npt(), _PREG(10), _AGEN(0), _VREG(16), __vcop_alws());
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeWU(), __vcop_npt(), __vcop_alws(), _VREG(16), _PREG(12), _AGEN(1), _PREG(0));
   __vcop_vloop_end(1u);

}

void vcop_remove_ex_col(
   __vptr_uint32 input,
   __vptr_uint32 output,
   int nitems)
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_remove_ex_col_init(input, output, nitems, __pblock_vcop_remove_ex_col);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_remove_ex_col_vloops(__pblock_vcop_remove_ex_col);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

void vcop_remove_ex_col_custom(
   __vptr_uint32 input,
   __vptr_uint32 output,
   int nitems,
   unsigned short pblock[])
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_remove_ex_col_init(input, output, nitems, pblock);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_remove_ex_col_vloops(pblock);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

