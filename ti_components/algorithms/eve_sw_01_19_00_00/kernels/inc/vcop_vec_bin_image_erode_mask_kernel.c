#include <vcop\vcop.h>

typedef unsigned char uchar;

#pragma DATA_SECTION(__pblock_vcop_vec_bin_image_erode_mask, ".vcop_parameter_block")
#pragma DATA_ALIGN(__pblock_vcop_vec_bin_image_erode_mask, __ALIGNOF__(int));
unsigned short __pblock_vcop_vec_bin_image_erode_mask[32];

unsigned int vcop_vec_bin_image_erode_mask_param_count(void)
{
   return 32u;
}

unsigned int vcop_vec_bin_image_erode_mask_ctrl_count(void)
{
   return 0u;
}

unsigned int vcop_vec_bin_image_erode_mask_init(
   __vptr_uint32 pIn,
   __vptr_uint32 complementMask0,
   __vptr_uint32 complementMask1,
   __vptr_uint32 complementMask2,
   __vptr_uint32 out,
   unsigned short cols,
   unsigned short pitch,
   unsigned short height,
   unsigned short pblock[])
{
   int __offset = 0;
   /* Loop 1 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), (height)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), (((cols + 32*(8u)-1) & ~(32*(8u)-1))/(32*(8u)))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), (3)-1u);
   __vcop_pblock_init32(pblock, __offset+_PREG(6), 31);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), 30);
   __vcop_pblock_init32(pblock, __offset+_PREG(10), 4294967295);
   __vcop_pblock_init32(pblock, __offset+_PREG(12), (uchar *)pIn);
   __vcop_pblock_init32(pblock, __offset+_PREG(14), (uchar *)pIn+1*4);
   __vcop_pblock_init32(pblock, __offset+_PREG(16), (uchar *)complementMask0);
   __vcop_pblock_init32(pblock, __offset+_PREG(18), (uchar *)complementMask1);
   __vcop_pblock_init32(pblock, __offset+_PREG(20), (uchar *)complementMask2);
   __vcop_pblock_init32(pblock, __offset+_PREG(22), (uchar *)out);
   __vcop_pblock_init16(pblock, __offset+_PREG(24), 32);
   __vcop_pblock_init16(pblock, __offset+_PREG(25), ((pitch/8)) -((8u*sizeof(*pIn)))*((((cols + 32*(8u)-1) & ~(32*(8u)-1))/(32*(8u)))-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(26), ((pitch/8)));
   __vcop_pblock_init16(pblock, __offset+_PREG(27), ((8u*sizeof(*pIn))) -((pitch/8))*((3)-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(28), ((pitch/8)) -((8u*sizeof(*pIn)))*((((cols + 32*(8u)-1) & ~(32*(8u)-1))/(32*(8u)))-1u) -((pitch/8))*((3)-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(29), -64);
   __vcop_pblock_init32(pblock, __offset+_PREG(30), -1);
   __vcop_pblock_init32(pblock, __offset+_PREG(32), -2);
   __offset += 32;

   return 32u;
}

void vcop_vec_bin_image_erode_mask_vloops(
   unsigned short pblock[])
{
   /* Kernel-wide Vector Registers */
   #pragma VCC_VREG("R0", 16);
   #pragma VCC_VREG("R1", 17);
   #pragma VCC_VREG("R10", 18);
   #pragma VCC_VREG("R11", 19);
   #pragma VCC_VREG("R12", 20);
   #pragma VCC_VREG("R13", 21);
   #pragma VCC_VREG("R14", 22);
   #pragma VCC_VREG("R15", 23);
   #pragma VCC_VREG("R2", 24);
   #pragma VCC_VREG("R3", 25);
   #pragma VCC_VREG("R4", 26);
   #pragma VCC_VREG("R5", 27);
   #pragma VCC_VREG("R6", 28);
   #pragma VCC_VREG("R7", 29);
   #pragma VCC_VREG("R8", 30);
   #pragma VCC_VREG("R9", 31);

   __vcop_param(&pblock[0]);

   /* VLOOP 1 Start */

   /* VLOOP Local Vector Registers */
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("Addr2", "A0");
   #pragma EVE_REG("Addr1", "A1");
   #pragma EVE_REG("Addr3", "A2");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I1", "I2");
   #pragma EVE_REG("I2", "I3");
   #pragma EVE_REG("I3", "I4");
   

   __vcop_vloop(__vcop_compute(), 24u, 16u, 1u);
   __vcop_vinit(__vcop_sizeW(), __vcop_once(), _PREG(30), _VREG(20));
   __vcop_vinit(__vcop_sizeW(), __vcop_once(), _PREG(32), _VREG(21));
   __vcop_vinit(__vcop_sizeW(), __vcop_once(), _PREG(6), _VREG(22));
   __vcop_vinit(__vcop_sizeW(), __vcop_once(), _PREG(8), _VREG(23));
   __vcop_vinit(__vcop_sizeWU(), __vcop_i4_zero(), _PREG(10), _VREG(30));
   __vcop_vagen(_AGEN(0), _PREG(0), _PREG(24), _PREG(25), _PREG(0));
   __vcop_vagen(_AGEN(1), _PREG(26), _PREG(27), _PREG(28), _PREG(0));
   __vcop_vagen(_AGEN(2), _PREG(24), _PREG(29), _PREG(29), _PREG(0));
   __vcop_vload(__vcop_sizeWU(), __vcop_npt(), _PREG(12), _AGEN(1), _VREG(16), __vcop_alws());
   __vcop_vload(__vcop_sizeWU(), __vcop_npt(), _PREG(14), _AGEN(1), _VREG(17), __vcop_alws());
   __vcop_vload(__vcop_sizeWU(), __vcop_npt(), _PREG(16), _AGEN(2), _VREG(24), __vcop_alws());
   __vcop_vload(__vcop_sizeWU(), __vcop_npt(), _PREG(18), _AGEN(2), _VREG(25), __vcop_alws());
   __vcop_vload(__vcop_sizeWU(), __vcop_npt(), _PREG(20), _AGEN(2), _VREG(26), __vcop_alws());
   __vcop_vshf(_VREG(16), _VREG(20), _VREG(31));
   __vcop_vshf(_VREG(16), _VREG(21), _VREG(18));
   __vcop_vshfor(_VREG(17), _VREG(22), _VREG(31));
   __vcop_vshfor(_VREG(17), _VREG(23), _VREG(18));
   __vcop_vor(_VREG(16), _VREG(24), _VREG(27));
   __vcop_vor(_VREG(31), _VREG(25), _VREG(31));
   __vcop_vor(_VREG(18), _VREG(26), _VREG(18));
   __vcop_vand(_VREG(27), _VREG(31), _VREG(27));
   __vcop_vand3(_VREG(27), _VREG(18), _VREG(30));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeWU(), __vcop_npt(), __vcop_last_i4(), _VREG(30), _PREG(22), _AGEN(0), _PREG(0));
   __vcop_vloop_end(1u);

}

void vcop_vec_bin_image_erode_mask(
   __vptr_uint32 pIn,
   __vptr_uint32 complementMask0,
   __vptr_uint32 complementMask1,
   __vptr_uint32 complementMask2,
   __vptr_uint32 out,
   unsigned short cols,
   unsigned short pitch,
   unsigned short height)
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_vec_bin_image_erode_mask_init(pIn, complementMask0, complementMask1, complementMask2, out, cols, pitch, height, __pblock_vcop_vec_bin_image_erode_mask);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_vec_bin_image_erode_mask_vloops(__pblock_vcop_vec_bin_image_erode_mask);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

void vcop_vec_bin_image_erode_mask_custom(
   __vptr_uint32 pIn,
   __vptr_uint32 complementMask0,
   __vptr_uint32 complementMask1,
   __vptr_uint32 complementMask2,
   __vptr_uint32 out,
   unsigned short cols,
   unsigned short pitch,
   unsigned short height,
   unsigned short pblock[])
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_vec_bin_image_erode_mask_init(pIn, complementMask0, complementMask1, complementMask2, out, cols, pitch, height, pblock);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_vec_bin_image_erode_mask_vloops(pblock);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

