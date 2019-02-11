#include <vcop\vcop.h>

typedef unsigned char uchar;

#pragma DATA_SECTION(__pblock_vcop_vec_array_l1_distance, ".vcop_parameter_block")
#pragma DATA_ALIGN(__pblock_vcop_vec_array_l1_distance, __ALIGNOF__(int));
unsigned short __pblock_vcop_vec_array_l1_distance[16];

unsigned int vcop_vec_array_l1_distance_param_count(void)
{
   return 16u;
}

unsigned int vcop_vec_array_l1_distance_ctrl_count(void)
{
   return 0u;
}

unsigned int vcop_vec_array_l1_distance_init(
   __vptr_int16 a,
   __vptr_int16 b,
   __vptr_uint32 c,
   int array_len,
   unsigned short pblock[])
{
   int __offset = 0;
   /* Loop 1 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), (1)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), (array_len/(2*(8u)))-1u);
   __vcop_pblock_init32(pblock, __offset+_PREG(6), (uchar *)b);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)c);
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)c+8*4);
   __vcop_pblock_init16(pblock, __offset+_PREG(12), 32);
   __vcop_pblock_init16(pblock, __offset+_PREG(13),  -((8u*sizeof(*a))*2)*((array_len/(2*(8u)))-1u));
   __vcop_pblock_init32(pblock, __offset+_PREG(14), 0);
   __vcop_pblock_init32(pblock, __offset+_PREG(16), (uchar *)a);
   __offset += 16;

   return 16u;
}

void vcop_vec_array_l1_distance_vloops(
   unsigned short pblock[])
{
   /* Kernel-wide Vector Registers */
   #pragma VCC_VREG("Va_1", 16);
   #pragma VCC_VREG("Va_2", 17);
   #pragma VCC_VREG("Vacc1", 18);
   #pragma VCC_VREG("Vacc2", 19);
   #pragma VCC_VREG("Vb_1", 20);
   #pragma VCC_VREG("Vb_2", 21);

   __vcop_param(&pblock[0]);

   /* VLOOP 1 Start */

   /* VLOOP Local Vector Registers */
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("Addr2", "A0");
   #pragma EVE_REG("Addr1", "A1");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I2", "I3");
   #pragma EVE_REG("I1", "I4");
   

   __vcop_vloop(__vcop_compute(), 11u, 8u, 1u);
   __vcop_vinit(__vcop_sizeW(), __vcop_once(), _PREG(14), _VREG(18));
   __vcop_vinit(__vcop_sizeW(), __vcop_once(), _PREG(14), _VREG(19));
   __vcop_vagen(_AGEN(0), _PREG(0), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(1), _PREG(12), _PREG(13), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeH(), __vcop_dintrlv(), _PREG(16), _AGEN(1), _VPAIR(16,17), __vcop_alws());
   __vcop_vload(__vcop_sizeH(), __vcop_dintrlv(), _PREG(6), _AGEN(1), _VPAIR(20,21), __vcop_alws());
   __vcop_vsad(_VREG(20), _VREG(16), _VREG(18));
   __vcop_vsad(_VREG(21), _VREG(17), _VREG(19));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeWU(), __vcop_npt(), __vcop_last_i4(), _VREG(18), _PREG(8), _AGEN(0), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeWU(), __vcop_npt(), __vcop_last_i4(), _VREG(19), _PREG(10), _AGEN(0), _PREG(0));
   __vcop_vloop_end(1u);

}

void vcop_vec_array_l1_distance(
   __vptr_int16 a,
   __vptr_int16 b,
   __vptr_uint32 c,
   int array_len)
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_vec_array_l1_distance_init(a, b, c, array_len, __pblock_vcop_vec_array_l1_distance);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_vec_array_l1_distance_vloops(__pblock_vcop_vec_array_l1_distance);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

void vcop_vec_array_l1_distance_custom(
   __vptr_int16 a,
   __vptr_int16 b,
   __vptr_uint32 c,
   int array_len,
   unsigned short pblock[])
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_vec_array_l1_distance_init(a, b, c, array_len, pblock);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_vec_array_l1_distance_vloops(pblock);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

