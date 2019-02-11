#include <vcop\vcop.h>

typedef unsigned char uchar;

#pragma DATA_SECTION(__pblock_vcop_vec_bin_image_erode_cross, ".vcop_parameter_block")
#pragma DATA_ALIGN(__pblock_vcop_vec_bin_image_erode_cross, __ALIGNOF__(int));
unsigned short __pblock_vcop_vec_bin_image_erode_cross[28];

unsigned int vcop_vec_bin_image_erode_cross_param_count(void)
{
   return 28u;
}

unsigned int vcop_vec_bin_image_erode_cross_ctrl_count(void)
{
   return 0u;
}

unsigned int vcop_vec_bin_image_erode_cross_init(
   __vptr_uint32 pIn,
   __vptr_uint32 out,
   unsigned short cols,
   unsigned short pitch,
   unsigned short height,
   unsigned short pblock[])
{
   int __offset = 0;
   /* Loop 1 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), (height)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), (((cols + 32*(8u)-1) & ~(32*(8u)-1))/(32*(8u)))-1u);
   __vcop_pblock_init32(pblock, __offset+_PREG(6), -2);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), -1);
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)pIn);
   __vcop_pblock_init32(pblock, __offset+_PREG(12), (uchar *)pIn+1*4);
   __vcop_pblock_init32(pblock, __offset+_PREG(14), (uchar *)pIn+pitch/8);
   __vcop_pblock_init32(pblock, __offset+_PREG(16), (uchar *)pIn+pitch/8+1*4);
   __vcop_pblock_init32(pblock, __offset+_PREG(18), (uchar *)pIn+pitch*2/8);
   __vcop_pblock_init32(pblock, __offset+_PREG(20), (uchar *)pIn+pitch*2/8+1*4);
   __vcop_pblock_init32(pblock, __offset+_PREG(22), (uchar *)out);
   __vcop_pblock_init16(pblock, __offset+_PREG(24), 32);
   __vcop_pblock_init16(pblock, __offset+_PREG(25), ((pitch/8)) -((8u*sizeof(*pIn)))*((((cols + 32*(8u)-1) & ~(32*(8u)-1))/(32*(8u)))-1u));
   __vcop_pblock_init32(pblock, __offset+_PREG(26), 31);
   __vcop_pblock_init32(pblock, __offset+_PREG(28), 30);
   __offset += 28;

   return 28u;
}

void vcop_vec_bin_image_erode_cross_vloops(
   unsigned short pblock[])
{
   /* Kernel-wide Vector Registers */
   #pragma VCC_VREG("R10", 16);
   #pragma VCC_VREG("R11", 17);
   #pragma VCC_VREG("R12", 18);
   #pragma VCC_VREG("R13", 19);
   #pragma VCC_VREG("R6", 20);
   #pragma VCC_VREG("R7", 21);
   #pragma VCC_VREG("R8", 22);
   #pragma VCC_VREG("R9", 23);
   #pragma VCC_VREG("in00", 24);
   #pragma VCC_VREG("in01", 25);
   #pragma VCC_VREG("in10", 26);
   #pragma VCC_VREG("in11", 27);
   #pragma VCC_VREG("in20", 28);
   #pragma VCC_VREG("in21", 29);
   #pragma VCC_VREG("t1", 30);
   #pragma VCC_VREG("t2", 31);
   #pragma VCC_VREG("t3", 32);
   #pragma VCC_VREG("t4", 33);

   __vcop_param(&pblock[0]);

   /* VLOOP 1 Start */

   /* VLOOP Local Vector Registers */
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("Addr1", "A0");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I1", "I3");
   #pragma EVE_REG("I2", "I4");
   

   __vcop_vloop(__vcop_compute(), 23u, 14u, 1u);
   __vcop_vinit(__vcop_sizeW(), __vcop_once(), _PREG(26), _VREG(16));
   __vcop_vinit(__vcop_sizeW(), __vcop_once(), _PREG(28), _VREG(17));
   __vcop_vinit(__vcop_sizeW(), __vcop_once(), _PREG(6), _VREG(18));
   __vcop_vinit(__vcop_sizeW(), __vcop_once(), _PREG(8), _VREG(19));
   __vcop_vagen(_AGEN(0), _PREG(24), _PREG(25), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeWU(), __vcop_npt(), _PREG(10), _AGEN(0), _VREG(24), __vcop_alws());
   __vcop_vload(__vcop_sizeWU(), __vcop_npt(), _PREG(12), _AGEN(0), _VREG(25), __vcop_alws());
   __vcop_vload(__vcop_sizeWU(), __vcop_npt(), _PREG(14), _AGEN(0), _VREG(26), __vcop_alws());
   __vcop_vload(__vcop_sizeWU(), __vcop_npt(), _PREG(16), _AGEN(0), _VREG(27), __vcop_alws());
   __vcop_vload(__vcop_sizeWU(), __vcop_npt(), _PREG(18), _AGEN(0), _VREG(28), __vcop_alws());
   __vcop_vload(__vcop_sizeWU(), __vcop_npt(), _PREG(20), _AGEN(0), _VREG(29), __vcop_alws());
   __vcop_vshf(_VREG(24), _VREG(19), _VREG(20));
   __vcop_vshf(_VREG(26), _VREG(19), _VREG(21));
   __vcop_vshfor(_VREG(25), _VREG(16), _VREG(20));
   __vcop_vshfor(_VREG(27), _VREG(16), _VREG(21));
   __vcop_vshf(_VREG(26), _VREG(18), _VREG(22));
   __vcop_vshf(_VREG(28), _VREG(19), _VREG(23));
   __vcop_vand3(_VREG(20), _VREG(21), _VREG(26));
   __vcop_vshfor(_VREG(27), _VREG(17), _VREG(22));
   __vcop_vshfor(_VREG(29), _VREG(16), _VREG(23));
   __vcop_vand3(_VREG(26), _VREG(23), _VREG(22));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeWU(), __vcop_npt(), __vcop_alws(), _VREG(22), _PREG(22), _AGEN(0), _PREG(0));
   __vcop_vloop_end(1u);

}

void vcop_vec_bin_image_erode_cross(
   __vptr_uint32 pIn,
   __vptr_uint32 out,
   unsigned short cols,
   unsigned short pitch,
   unsigned short height)
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_vec_bin_image_erode_cross_init(pIn, out, cols, pitch, height, __pblock_vcop_vec_bin_image_erode_cross);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_vec_bin_image_erode_cross_vloops(__pblock_vcop_vec_bin_image_erode_cross);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

void vcop_vec_bin_image_erode_cross_custom(
   __vptr_uint32 pIn,
   __vptr_uint32 out,
   unsigned short cols,
   unsigned short pitch,
   unsigned short height,
   unsigned short pblock[])
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_vec_bin_image_erode_cross_init(pIn, out, cols, pitch, height, pblock);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_vec_bin_image_erode_cross_vloops(pblock);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

