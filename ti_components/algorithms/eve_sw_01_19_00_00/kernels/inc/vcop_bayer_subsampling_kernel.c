#include <vcop\vcop.h>

typedef unsigned char uchar;

#pragma DATA_SECTION(__pblock_bayer_subSampling, ".vcop_parameter_block")
#pragma DATA_ALIGN(__pblock_bayer_subSampling, __ALIGNOF__(int));
unsigned short __pblock_bayer_subSampling[16];

unsigned int bayer_subSampling_param_count(void)
{
   return 16u;
}

unsigned int bayer_subSampling_ctrl_count(void)
{
   return 0u;
}

unsigned int bayer_subSampling_init(
   __vptr_uint16 CFA_short,
   __vptr_uint16 subSample_out,
   unsigned int blk_w,
   unsigned int blk_h,
   unsigned int input_stride,
   unsigned int output_stride,
   unsigned int subSample_X,
   unsigned int subSample_Y,
   unsigned int NumOfSample,
   unsigned short pblock[])
{
   int __offset = 0;
   /* Loop 1 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), ((blk_h/subSample_Y))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), ((blk_w/subSample_X))-1u);
   __vcop_pblock_init32(pblock, __offset+_PREG(6), (uchar *)subSample_out);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)subSample_out+output_stride*sizeof(*CFA_short));
   __vcop_pblock_init16(pblock, __offset+_PREG(10), (subSample_X*sizeof(*CFA_short)));
   __vcop_pblock_init16(pblock, __offset+_PREG(11), (input_stride*subSample_Y*sizeof(*CFA_short)) -(subSample_X*sizeof(*CFA_short))*(((blk_w/subSample_X))-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(12), (NumOfSample*2*sizeof(*CFA_short)));
   __vcop_pblock_init16(pblock, __offset+_PREG(13), (output_stride*sizeof(*CFA_short)*2) -(NumOfSample*2*sizeof(*CFA_short))*(((blk_w/subSample_X))-1u));
   __vcop_pblock_init32(pblock, __offset+_PREG(14), (uchar *)CFA_short);
   __vcop_pblock_init32(pblock, __offset+_PREG(16), (uchar *)CFA_short+input_stride*sizeof(*CFA_short));
   __offset += 16;

   return 16u;
}

void bayer_subSampling_vloops(
   unsigned short pblock[])
{
   /* Kernel-wide Vector Registers */
   #pragma VCC_VREG("pixel1", 16);
   #pragma VCC_VREG("pixel2", 17);

   __vcop_param(&pblock[0]);

   /* VLOOP 1 Start */

   /* VLOOP Local Vector Registers */
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("Addr_in", "A0");
   #pragma EVE_REG("Addr_out", "A1");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I0", "I3");
   #pragma EVE_REG("I1", "I4");
   

   __vcop_vloop(__vcop_compute(), 7u, 8u, 1u);
   __vcop_vagen(_AGEN(0), _PREG(10), _PREG(11), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(1), _PREG(12), _PREG(13), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeHU(), __vcop_npt(), _PREG(14), _AGEN(0), _VREG(16), __vcop_alws());
   __vcop_vload(__vcop_sizeHU(), __vcop_npt(), _PREG(16), _AGEN(0), _VREG(17), __vcop_alws());
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeHU(), __vcop_npt(), __vcop_alws(), _VREG(16), _PREG(6), _AGEN(1), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeHU(), __vcop_npt(), __vcop_alws(), _VREG(17), _PREG(8), _AGEN(1), _PREG(0));
   __vcop_vloop_end(1u);

}

void bayer_subSampling(
   __vptr_uint16 CFA_short,
   __vptr_uint16 subSample_out,
   unsigned int blk_w,
   unsigned int blk_h,
   unsigned int input_stride,
   unsigned int output_stride,
   unsigned int subSample_X,
   unsigned int subSample_Y,
   unsigned int NumOfSample)
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   bayer_subSampling_init(CFA_short, subSample_out, blk_w, blk_h, input_stride, output_stride, subSample_X, subSample_Y, NumOfSample, __pblock_bayer_subSampling);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   bayer_subSampling_vloops(__pblock_bayer_subSampling);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

void bayer_subSampling_custom(
   __vptr_uint16 CFA_short,
   __vptr_uint16 subSample_out,
   unsigned int blk_w,
   unsigned int blk_h,
   unsigned int input_stride,
   unsigned int output_stride,
   unsigned int subSample_X,
   unsigned int subSample_Y,
   unsigned int NumOfSample,
   unsigned short pblock[])
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   bayer_subSampling_init(CFA_short, subSample_out, blk_w, blk_h, input_stride, output_stride, subSample_X, subSample_Y, NumOfSample, pblock);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   bayer_subSampling_vloops(pblock);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

