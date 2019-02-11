#include <vcop\vcop.h>

typedef unsigned char uchar;

#pragma DATA_SECTION(__pblock_vcop_memcpy, ".vcop_parameter_block")
#pragma DATA_ALIGN(__pblock_vcop_memcpy, __ALIGNOF__(int));
unsigned short __pblock_vcop_memcpy[10];

unsigned int vcop_memcpy_param_count(void)
{
   return 10u;
}

unsigned int vcop_memcpy_ctrl_count(void)
{
   return 0u;
}

unsigned int vcop_memcpy_init(
   __vptr_uint32 src,
   __vptr_uint32 dst,
   unsigned short blockSize,
   unsigned short pblock[])
{
   int __offset = 0;
   /* Loop 1 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), ((((blockSize) + 4U*(8u)-1U) & ~(4U*(8u)-1U))/(4*(8u)))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(6), 32);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)src);
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)dst);
   __offset += 10;

   return 10u;
}

void vcop_memcpy_vloops(
   unsigned short pblock[])
{
   /* Kernel-wide Vector Registers */

   __vcop_param(&pblock[0]);

   /* VLOOP 1 Start */

   /* VLOOP Local Vector Registers */
   #pragma VCC_VREG("Vdst", 16);
   #pragma VCC_VREG("Vsrc", 17);
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("Addr1", "A0");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I1", "I4");
   

   __vcop_vloop(__vcop_compute(), 5u, 5u, 1u);
   __vcop_vagen(_AGEN(0), _PREG(6), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeWU(), __vcop_npt(), _PREG(8), _AGEN(0), _VREG(17), __vcop_alws());
   __vcop_vor(_VREG(17), _VREG(17), _VREG(16));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeWU(), __vcop_npt(), __vcop_alws(), _VREG(16), _PREG(10), _AGEN(0), _PREG(0));
   __vcop_vloop_end(1u);

}

void vcop_memcpy(
   __vptr_uint32 src,
   __vptr_uint32 dst,
   unsigned short blockSize)
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_memcpy_init(src, dst, blockSize, __pblock_vcop_memcpy);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_memcpy_vloops(__pblock_vcop_memcpy);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

void vcop_memcpy_custom(
   __vptr_uint32 src,
   __vptr_uint32 dst,
   unsigned short blockSize,
   unsigned short pblock[])
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_memcpy_init(src, dst, blockSize, pblock);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_memcpy_vloops(pblock);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

#pragma DATA_SECTION(__pblock_vcop_memcpy2d, ".vcop_parameter_block")
#pragma DATA_ALIGN(__pblock_vcop_memcpy2d, __ALIGNOF__(int));
unsigned short __pblock_vcop_memcpy2d[12];

unsigned int vcop_memcpy2d_param_count(void)
{
   return 12u;
}

unsigned int vcop_memcpy2d_ctrl_count(void)
{
   return 0u;
}

unsigned int vcop_memcpy2d_init(
   __vptr_uint16 src,
   __vptr_uint16 dst,
   unsigned short width,
   unsigned short height,
   unsigned short pitch,
   unsigned short pblock[])
{
   int __offset = 0;
   /* Loop 1 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), (height)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), ((((width) + 2U*(8u)-1U) & ~(2U*(8u)-1U))/(2*(8u)))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(6), 16);
   __vcop_pblock_init16(pblock, __offset+_PREG(7), (pitch) -(8u*sizeof(*src))*(((((width) + 2U*(8u)-1U) & ~(2U*(8u)-1U))/(2*(8u)))-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(8), (width) -(8u*sizeof(*dst))*(((((width) + 2U*(8u)-1U) & ~(2U*(8u)-1U))/(2*(8u)))-1u));
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)src);
   __vcop_pblock_init32(pblock, __offset+_PREG(12), (uchar *)dst);
   __offset += 12;

   return 12u;
}

void vcop_memcpy2d_vloops(
   unsigned short pblock[])
{
   /* Kernel-wide Vector Registers */

   __vcop_param(&pblock[0]);

   /* VLOOP 1 Start */

   /* VLOOP Local Vector Registers */
   #pragma VCC_VREG("Vsrc", 16);
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("Addr1", "A0");
   #pragma EVE_REG("Addr2", "A1");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I1", "I3");
   #pragma EVE_REG("I2", "I4");
   

   __vcop_vloop(__vcop_compute(), 5u, 6u, 1u);
   __vcop_vagen(_AGEN(0), _PREG(6), _PREG(7), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(1), _PREG(6), _PREG(8), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeHU(), __vcop_npt(), _PREG(10), _AGEN(0), _VREG(16), __vcop_alws());
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeHU(), __vcop_npt(), __vcop_alws(), _VREG(16), _PREG(12), _AGEN(1), _PREG(0));
   __vcop_vloop_end(1u);

}

void vcop_memcpy2d(
   __vptr_uint16 src,
   __vptr_uint16 dst,
   unsigned short width,
   unsigned short height,
   unsigned short pitch)
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_memcpy2d_init(src, dst, width, height, pitch, __pblock_vcop_memcpy2d);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_memcpy2d_vloops(__pblock_vcop_memcpy2d);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

void vcop_memcpy2d_custom(
   __vptr_uint16 src,
   __vptr_uint16 dst,
   unsigned short width,
   unsigned short height,
   unsigned short pitch,
   unsigned short pblock[])
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_memcpy2d_init(src, dst, width, height, pitch, pblock);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_memcpy2d_vloops(pblock);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

