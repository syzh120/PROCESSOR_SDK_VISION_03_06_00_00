#include <vcop\vcop.h>

typedef unsigned char uchar;

#pragma DATA_SECTION(__pblock_vcop_SAD_char_int, ".vcop_parameter_block")
#pragma DATA_ALIGN(__pblock_vcop_SAD_char_int, __ALIGNOF__(int));
unsigned short __pblock_vcop_SAD_char_int[56];

unsigned int vcop_SAD_char_int_param_count(void)
{
   return 56u;
}

unsigned int vcop_SAD_char_int_ctrl_count(void)
{
   return 0u;
}

unsigned int vcop_SAD_char_int_init(
   __vptr_int8 in,
   __vptr_int8 ref,
   __vptr_int16 vert_sad,
   __vptr_int16 vert_sad_t,
   __vptr_int16 sad_array,
   int blk_w,
   int blk_h,
   int in_w,
   int in_h,
   int ref_w,
   int ref_h,
   int offset_horz,
   int offset_vert,
   int steps_horz,
   int steps_vert,
   unsigned short pblock[])
{
   int __offset = 0;
   /* Loop 1 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), (steps_vert)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), (steps_horz)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), (blk_w/(8u))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), (blk_h)-1u);
   __vcop_pblock_init32(pblock, __offset+_PREG(6), (uchar *)ref);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)vert_sad);
   __vcop_pblock_init16(pblock, __offset+_PREG(10), 16);
   __vcop_pblock_init16(pblock, __offset+_PREG(11), (blk_w*sizeof(*vert_sad)) -(8u*sizeof(*vert_sad))*((blk_w/(8u))-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(12), (blk_w*steps_horz*sizeof(*vert_sad)) -(blk_w*sizeof(*vert_sad))*((steps_horz)-1u) -(8u*sizeof(*vert_sad))*((blk_w/(8u))-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(13), (in_w*sizeof(*in)));
   __vcop_pblock_init16(pblock, __offset+_PREG(14), (8u*sizeof(*in)) -(in_w*sizeof(*in))*((blk_h)-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(15),  -(8u*sizeof(*in))*((blk_w/(8u))-1u) -(in_w*sizeof(*in))*((blk_h)-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(16), (ref_w*sizeof(*ref)));
   __vcop_pblock_init16(pblock, __offset+_PREG(17), (8u*sizeof(*ref)) -(ref_w*sizeof(*ref))*((blk_h)-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(18), (offset_horz*sizeof(*ref)) -(8u*sizeof(*ref))*((blk_w/(8u))-1u) -(ref_w*sizeof(*ref))*((blk_h)-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(19), (offset_vert*ref_w*sizeof(*ref)) -(offset_horz*sizeof(*ref))*((steps_horz)-1u) -(8u*sizeof(*ref))*((blk_w/(8u))-1u) -(ref_w*sizeof(*ref))*((blk_h)-1u));
   __vcop_pblock_init32(pblock, __offset+_PREG(20), 0);
   __vcop_pblock_init32(pblock, __offset+_PREG(22), (uchar *)in);
   __offset += 22;

   /* Loop 2 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), (steps_vert)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), ((steps_horz/(8 * 2)))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), ((8 * 2))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), (blk_w/(8u))-1u);
   __vcop_pblock_init32(pblock, __offset+_PREG(6), (uchar *)vert_sad_t);
   __vcop_pblock_init16(pblock, __offset+_PREG(8), 16);
   __vcop_pblock_init16(pblock, __offset+_PREG(9), (blk_w*sizeof(*vert_sad)) -(8u*sizeof(*vert_sad))*((blk_w/(8u))-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(10), (blk_w*(8*2)*sizeof(*vert_sad)) -(blk_w*sizeof(*vert_sad))*(((8 * 2))-1u) -(8u*sizeof(*vert_sad))*((blk_w/(8u))-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(11), (steps_horz*blk_w*sizeof(*vert_sad)) -(blk_w*(8*2)*sizeof(*vert_sad))*(((steps_horz/(8 * 2)))-1u) -(blk_w*sizeof(*vert_sad))*(((8 * 2))-1u) -(8u*sizeof(*vert_sad))*((blk_w/(8u))-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(12), 288);
   __vcop_pblock_init16(pblock, __offset+_PREG(13), (sizeof(*vert_sad)) -(8*(8*2+2)*sizeof(*vert_sad))*((blk_w/(8u))-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(14), (blk_w*(8*2+2)*sizeof(*vert_sad)) -(sizeof(*vert_sad))*(((8 * 2))-1u) -(8*(8*2+2)*sizeof(*vert_sad))*((blk_w/(8u))-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(15), (steps_horz*(blk_w+blk_w/8)*sizeof(*vert_sad)) -(blk_w*(8*2+2)*sizeof(*vert_sad))*(((steps_horz/(8 * 2)))-1u) -(sizeof(*vert_sad))*(((8 * 2))-1u) -(8*(8*2+2)*sizeof(*vert_sad))*((blk_w/(8u))-1u));
   __vcop_pblock_init32(pblock, __offset+_PREG(16), 0);
   __vcop_pblock_init32(pblock, __offset+_PREG(18), (uchar *)vert_sad);
   __offset += 18;

   /* Loop 3 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), (steps_vert)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), ((steps_horz/(8 * 2)))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), (blk_w)-1u);
   __vcop_pblock_init32(pblock, __offset+_PREG(6), (uchar *)sad_array);
   __vcop_pblock_init16(pblock, __offset+_PREG(8), 32);
   __vcop_pblock_init16(pblock, __offset+_PREG(9), (steps_horz*sizeof(*vert_sad)) -((8*2)*sizeof(*vert_sad))*(((steps_horz/(8 * 2)))-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(10), 36);
   __vcop_pblock_init16(pblock, __offset+_PREG(11), (blk_w*(8*2+2)*sizeof(*vert_sad)) -((8*2+2)*sizeof(*vert_sad))*((blk_w)-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(12), (steps_horz*(blk_w+blk_w/8)*sizeof(*vert_sad)) -(blk_w*(8*2+2)*sizeof(*vert_sad))*(((steps_horz/(8 * 2)))-1u) -((8*2+2)*sizeof(*vert_sad))*((blk_w)-1u));
   __vcop_pblock_init32(pblock, __offset+_PREG(14), 0);
   __vcop_pblock_init32(pblock, __offset+_PREG(16), (uchar *)vert_sad_t);
   __offset += 16;

   return 56u;
}

void vcop_SAD_char_int_vloops(
   unsigned short pblock[])
{
   /* Kernel-wide Vector Registers */
   #pragma VCC_VREG("Vin", 16);
   #pragma VCC_VREG("Vin1", 17);
   #pragma VCC_VREG("Vin2", 18);
   #pragma VCC_VREG("Vout", 19);
   #pragma VCC_VREG("Vref", 20);
   #pragma VCC_VREG("Vsad1", 21);
   #pragma VCC_VREG("Vsad2", 22);
   #pragma VCC_VREG("Vzero", 23);

   __vcop_param(&pblock[0]);

   /* VLOOP 1 Start */

   /* VLOOP Local Vector Registers */
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("interAddr", "A0");
   #pragma EVE_REG("inAddr", "A1");
   #pragma EVE_REG("refAddr", "A2");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I1", "I1");
   #pragma EVE_REG("I2", "I2");
   #pragma EVE_REG("I3", "I3");
   #pragma EVE_REG("I4", "I4");
   

   __vcop_vloop(__vcop_compute(), 9u, 11u, 1u);
   __vcop_vinit(__vcop_sizeW(), __vcop_i4_zero(), _PREG(20), _VREG(21));
   __vcop_vagen(_AGEN(0), _PREG(0), _PREG(10), _PREG(11), _PREG(12));
   __vcop_vagen(_AGEN(1), _PREG(13), _PREG(14), _PREG(15), _PREG(15));
   __vcop_vagen(_AGEN(2), _PREG(16), _PREG(17), _PREG(18), _PREG(19));
   __vcop_vload(__vcop_sizeB(), __vcop_npt(), _PREG(22), _AGEN(1), _VREG(16), __vcop_alws());
   __vcop_vload(__vcop_sizeB(), __vcop_npt(), _PREG(6), _AGEN(2), _VREG(20), __vcop_alws());
   __vcop_vsad(_VREG(16), _VREG(20), _VREG(21));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeH(), __vcop_npt(), __vcop_last_i4(), _VREG(21), _PREG(8), _AGEN(0), _PREG(0));
   __vcop_vloop_end(1u);

   /* VLOOP 2 Start */

   /* VLOOP Local Vector Registers */
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("inAddr", "A0");
   #pragma EVE_REG("outAddr", "A1");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I1", "I1");
   #pragma EVE_REG("I2", "I2");
   #pragma EVE_REG("I3", "I3");
   #pragma EVE_REG("I4", "I4");
   

   __vcop_vloop(__vcop_compute(), 7u, 9u, 2u);
   __vcop_vinit(__vcop_sizeW(), __vcop_once(), _PREG(16), _VREG(23));
   __vcop_vagen(_AGEN(0), _PREG(8), _PREG(9), _PREG(10), _PREG(11));
   __vcop_vagen(_AGEN(1), _PREG(12), _PREG(13), _PREG(14), _PREG(15));
   __vcop_vload(__vcop_sizeH(), __vcop_npt(), _PREG(18), _AGEN(0), _VREG(16), __vcop_alws());
   __vcop_vor(_VREG(16), _VREG(16), _VREG(19));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeH(), __vcop_offst_np1(), __vcop_alws(), _VREG(19), _PREG(6), _AGEN(1), _PREG(0));
   __vcop_vloop_end(2u);

   /* VLOOP 3 Start */

   /* VLOOP Local Vector Registers */
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("outAddr", "A0");
   #pragma EVE_REG("inAddr", "A1");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I1", "I2");
   #pragma EVE_REG("I2", "I3");
   #pragma EVE_REG("I3", "I4");
   

   __vcop_vloop(__vcop_compute(), 9u, 8u, 3u);
   __vcop_vinit(__vcop_sizeW(), __vcop_i4_zero(), _PREG(14), _VREG(21));
   __vcop_vinit(__vcop_sizeW(), __vcop_i4_zero(), _PREG(14), _VREG(22));
   __vcop_vagen(_AGEN(0), _PREG(0), _PREG(8), _PREG(9), _PREG(0));
   __vcop_vagen(_AGEN(1), _PREG(10), _PREG(11), _PREG(12), _PREG(0));
   __vcop_vload(__vcop_sizeH(), __vcop_dintrlv(), _PREG(16), _AGEN(1), _VPAIR(17,18), __vcop_alws());
   __vcop_vadd(_VREG(21), _VREG(17), _VREG(21));
   __vcop_vadd(_VREG(22), _VREG(18), _VREG(22));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeH(), __vcop_intrlv(), __vcop_last_i4(), _VPAIR(21,22), _PREG(6), _AGEN(0), _PREG(0));
   __vcop_vloop_end(3u);

}

void vcop_SAD_char_int(
   __vptr_int8 in,
   __vptr_int8 ref,
   __vptr_int16 vert_sad,
   __vptr_int16 vert_sad_t,
   __vptr_int16 sad_array,
   int blk_w,
   int blk_h,
   int in_w,
   int in_h,
   int ref_w,
   int ref_h,
   int offset_horz,
   int offset_vert,
   int steps_horz,
   int steps_vert)
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_SAD_char_int_init(in, ref, vert_sad, vert_sad_t, sad_array, blk_w, blk_h, in_w, in_h, ref_w, ref_h, offset_horz, offset_vert, steps_horz, steps_vert, __pblock_vcop_SAD_char_int);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_SAD_char_int_vloops(__pblock_vcop_SAD_char_int);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

void vcop_SAD_char_int_custom(
   __vptr_int8 in,
   __vptr_int8 ref,
   __vptr_int16 vert_sad,
   __vptr_int16 vert_sad_t,
   __vptr_int16 sad_array,
   int blk_w,
   int blk_h,
   int in_w,
   int in_h,
   int ref_w,
   int ref_h,
   int offset_horz,
   int offset_vert,
   int steps_horz,
   int steps_vert,
   unsigned short pblock[])
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_SAD_char_int_init(in, ref, vert_sad, vert_sad_t, sad_array, blk_w, blk_h, in_w, in_h, ref_w, ref_h, offset_horz, offset_vert, steps_horz, steps_vert, pblock);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_SAD_char_int_vloops(pblock);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

