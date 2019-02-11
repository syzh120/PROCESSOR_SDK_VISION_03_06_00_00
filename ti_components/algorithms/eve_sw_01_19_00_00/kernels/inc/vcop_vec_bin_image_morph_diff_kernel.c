#include <vcop\vcop.h>

typedef unsigned char uchar;

#pragma DATA_SECTION(__pblock_vcop_vec_bin_image_morph_diff, ".vcop_parameter_block")
#pragma DATA_ALIGN(__pblock_vcop_vec_bin_image_morph_diff, __ALIGNOF__(int));
unsigned short __pblock_vcop_vec_bin_image_morph_diff[24];

unsigned int vcop_vec_bin_image_morph_diff_param_count(void)
{
   return 24u;
}

unsigned int vcop_vec_bin_image_morph_diff_ctrl_count(void)
{
   return 0u;
}

unsigned int vcop_vec_bin_image_morph_diff_init(
   unsigned short blk_w,
   unsigned short line_ofst,
   unsigned short blk_h,
   __vptr_uint32 data1_ptr,
   unsigned short data1_bit_shift,
   __vptr_uint32 data2_ptr,
   unsigned short data2_bit_shift,
   __vptr_uint32 output_ptr,
   unsigned short pblock[])
{
   int __offset = 0;
   /* Loop 1 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), (blk_h)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), (((blk_w + 32*(8u)-1) & ~(32*(8u)-1))/(32*(8u)))-1u);
   __vcop_pblock_init32(pblock, __offset+_PREG(6), -data2_bit_shift);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), 32 - data2_bit_shift);
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)data1_ptr);
   __vcop_pblock_init32(pblock, __offset+_PREG(12), (uchar *)data1_ptr+1*4);
   __vcop_pblock_init32(pblock, __offset+_PREG(14), (uchar *)data2_ptr);
   __vcop_pblock_init32(pblock, __offset+_PREG(16), (uchar *)data2_ptr+1*4);
   __vcop_pblock_init32(pblock, __offset+_PREG(18), (uchar *)output_ptr);
   __vcop_pblock_init16(pblock, __offset+_PREG(20), 32);
   __vcop_pblock_init16(pblock, __offset+_PREG(21), ((line_ofst/8)) -((8u*sizeof(*data1_ptr)))*((((blk_w + 32*(8u)-1) & ~(32*(8u)-1))/(32*(8u)))-1u));
   __vcop_pblock_init32(pblock, __offset+_PREG(22), -data1_bit_shift);
   __vcop_pblock_init32(pblock, __offset+_PREG(24), 32 - data1_bit_shift);
   __offset += 24;

   return 24u;
}

void vcop_vec_bin_image_morph_diff_vloops(
   unsigned short pblock[])
{
   /* Kernel-wide Vector Registers */
   #pragma VCC_VREG("Vdata1", 16);
   #pragma VCC_VREG("Vdata1shift", 17);
   #pragma VCC_VREG("Vdata1shift_opp", 18);
   #pragma VCC_VREG("Vdata2", 19);
   #pragma VCC_VREG("Vdata2shift", 20);
   #pragma VCC_VREG("Vdata2shift_opp", 21);
   #pragma VCC_VREG("Vdiff", 22);
   #pragma VCC_VREG("Vin1", 23);
   #pragma VCC_VREG("Vin1_1", 24);
   #pragma VCC_VREG("Vin2", 25);
   #pragma VCC_VREG("Vin2_1", 26);

   __vcop_param(&pblock[0]);

   /* VLOOP 1 Start */

   /* VLOOP Local Vector Registers */
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("A0", "A0");
   #pragma EVE_REG("A1", "A1");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I1", "I3");
   #pragma EVE_REG("I2", "I4");
   

   __vcop_vloop(__vcop_compute(), 17u, 12u, 1u);
   __vcop_vinit(__vcop_sizeW(), __vcop_once(), _PREG(22), _VREG(17));
   __vcop_vinit(__vcop_sizeW(), __vcop_once(), _PREG(24), _VREG(18));
   __vcop_vinit(__vcop_sizeW(), __vcop_once(), _PREG(6), _VREG(20));
   __vcop_vinit(__vcop_sizeW(), __vcop_once(), _PREG(8), _VREG(21));
   __vcop_vagen(_AGEN(0), _PREG(20), _PREG(21), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeWU(), __vcop_npt(), _PREG(10), _AGEN(0), _VREG(23), __vcop_alws());
   __vcop_vload(__vcop_sizeWU(), __vcop_npt(), _PREG(12), _AGEN(0), _VREG(24), __vcop_alws());
   __vcop_vload(__vcop_sizeWU(), __vcop_npt(), _PREG(14), _AGEN(0), _VREG(25), __vcop_alws());
   __vcop_vload(__vcop_sizeWU(), __vcop_npt(), _PREG(16), _AGEN(0), _VREG(26), __vcop_alws());
   __vcop_vshf(_VREG(23), _VREG(17), _VREG(16));
   __vcop_vshfor(_VREG(24), _VREG(18), _VREG(16));
   __vcop_vshf(_VREG(25), _VREG(20), _VREG(19));
   __vcop_vshfor(_VREG(26), _VREG(21), _VREG(19));
   __vcop_vxor(_VREG(16), _VREG(19), _VREG(22));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeWU(), __vcop_npt(), __vcop_alws(), _VREG(22), _PREG(18), _AGEN(0), _PREG(0));
   __vcop_vloop_end(1u);

}

void vcop_vec_bin_image_morph_diff(
   unsigned short blk_w,
   unsigned short line_ofst,
   unsigned short blk_h,
   __vptr_uint32 data1_ptr,
   unsigned short data1_bit_shift,
   __vptr_uint32 data2_ptr,
   unsigned short data2_bit_shift,
   __vptr_uint32 output_ptr)
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_vec_bin_image_morph_diff_init(blk_w, line_ofst, blk_h, data1_ptr, data1_bit_shift, data2_ptr, data2_bit_shift, output_ptr, __pblock_vcop_vec_bin_image_morph_diff);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_vec_bin_image_morph_diff_vloops(__pblock_vcop_vec_bin_image_morph_diff);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

void vcop_vec_bin_image_morph_diff_custom(
   unsigned short blk_w,
   unsigned short line_ofst,
   unsigned short blk_h,
   __vptr_uint32 data1_ptr,
   unsigned short data1_bit_shift,
   __vptr_uint32 data2_ptr,
   unsigned short data2_bit_shift,
   __vptr_uint32 output_ptr,
   unsigned short pblock[])
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_vec_bin_image_morph_diff_init(blk_w, line_ofst, blk_h, data1_ptr, data1_bit_shift, data2_ptr, data2_bit_shift, output_ptr, pblock);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_vec_bin_image_morph_diff_vloops(pblock);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

