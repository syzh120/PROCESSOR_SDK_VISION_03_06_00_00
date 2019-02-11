#include <vcop\vcop.h>

typedef unsigned char uchar;

#pragma DATA_SECTION(__pblock_vcop_deInterleaveYUV422ILE, ".vcop_parameter_block")
#pragma DATA_ALIGN(__pblock_vcop_deInterleaveYUV422ILE, __ALIGNOF__(int));
unsigned short __pblock_vcop_deInterleaveYUV422ILE[16];

unsigned int vcop_deInterleaveYUV422ILE_param_count(void)
{
   return 16u;
}

unsigned int vcop_deInterleaveYUV422ILE_ctrl_count(void)
{
   return 0u;
}

unsigned int vcop_deInterleaveYUV422ILE_init(
   __vptr_uint8 src,
   __vptr_uint8 dst,
   __vptr_uint8 dst_u,
   __vptr_uint8 dst_v,
   unsigned short size,
   unsigned short pblock[])
{
   int __offset = 0;
   /* Loop 1 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), ((((2*size) + 2U*(8u)-1U) & ~(2U*(8u)-1U))/(2*(8u)))-1u);
   __vcop_pblock_init32(pblock, __offset+_PREG(6), (uchar *)dst);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)dst_v);
   __vcop_pblock_init16(pblock, __offset+_PREG(10), 16);
   __vcop_pblock_init16(pblock, __offset+_PREG(11), 4);
   __vcop_pblock_init16(pblock, __offset+_PREG(12), 8);
   __vcop_pblock_init32(pblock, __offset+_PREG(14), (uchar *)src);
   __vcop_pblock_init32(pblock, __offset+_PREG(16), (uchar *)dst_u);
   __offset += 16;

   return 16u;
}

void vcop_deInterleaveYUV422ILE_vloops(
   unsigned short pblock[])
{
   /* Kernel-wide Vector Registers */

   __vcop_param(&pblock[0]);

   /* VLOOP 1 Start */

   /* VLOOP Local Vector Registers */
   #pragma VCC_VREG("uvVec", 16);
   #pragma VCC_VREG("vVec", 17);
   #pragma VCC_VREG("yVec", 18);
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("Addr", "A0");
   #pragma EVE_REG("Addr_uvout", "A1");
   #pragma EVE_REG("Addr_yout", "A2");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I1", "I4");
   

   __vcop_vloop(__vcop_compute(), 9u, 8u, 1u);
   __vcop_vagen(_AGEN(0), _PREG(10), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(1), _PREG(11), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(2), _PREG(12), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeBU(), __vcop_dintrlv(), _PREG(14), _AGEN(0), _VPAIR(16,18), __vcop_alws());
   __vcop_vdintrlv(_VREG(16), _VREG(17));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeBU(), __vcop_npt(), __vcop_alws(), _VREG(16), _PREG(16), _AGEN(1), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeBU(), __vcop_npt(), __vcop_alws(), _VREG(18), _PREG(6), _AGEN(2), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeBU(), __vcop_npt(), __vcop_alws(), _VREG(17), _PREG(8), _AGEN(1), _PREG(0));
   __vcop_vloop_end(1u);

}

void vcop_deInterleaveYUV422ILE(
   __vptr_uint8 src,
   __vptr_uint8 dst,
   __vptr_uint8 dst_u,
   __vptr_uint8 dst_v,
   unsigned short size)
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_deInterleaveYUV422ILE_init(src, dst, dst_u, dst_v, size, __pblock_vcop_deInterleaveYUV422ILE);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_deInterleaveYUV422ILE_vloops(__pblock_vcop_deInterleaveYUV422ILE);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

void vcop_deInterleaveYUV422ILE_custom(
   __vptr_uint8 src,
   __vptr_uint8 dst,
   __vptr_uint8 dst_u,
   __vptr_uint8 dst_v,
   unsigned short size,
   unsigned short pblock[])
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_deInterleaveYUV422ILE_init(src, dst, dst_u, dst_v, size, pblock);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_deInterleaveYUV422ILE_vloops(pblock);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

