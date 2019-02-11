#include <vcop\vcop.h>

typedef unsigned char uchar;

#pragma DATA_SECTION(__pblock_gamma_correction, ".vcop_parameter_block")
#pragma DATA_ALIGN(__pblock_gamma_correction, __ALIGNOF__(int));
unsigned short __pblock_gamma_correction[70];

unsigned int gamma_correction_param_count(void)
{
   return 70u;
}

unsigned int gamma_correction_ctrl_count(void)
{
   return 0u;
}

unsigned int gamma_correction_init(
   __vptr_uint16 iPtrR_in,
   __vptr_uint16 iPtrG_in,
   __vptr_uint16 iPtrB_in,
   __vptr_uint16 iPtrR_out,
   __vptr_uint16 iPtrG_out,
   __vptr_uint16 iPtrB_out,
   unsigned short blk_w,
   unsigned short blk_h,
   unsigned short input_stride,
   unsigned short output_stride,
   __vptr_uint16 tempPtrR,
   __vptr_uint16 tempPtrG,
   __vptr_uint16 tempPtrB,
   __vptr_uint16 LUT,
   unsigned short pblock[])
{
   int __offset = 0;
   /* Loop 1 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), (blk_h)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), ((blk_w/(8u)))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(6), __vcop_store_round_sat(SM_NONE,0,RM_TRUNC,2));
   __vcop_pblock_init16(pblock, __offset+_PREG(7), 16);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)iPtrB_in);
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)tempPtrR);
   __vcop_pblock_init32(pblock, __offset+_PREG(12), (uchar *)tempPtrG);
   __vcop_pblock_init32(pblock, __offset+_PREG(14), (uchar *)tempPtrB);
   __vcop_pblock_init16(pblock, __offset+_PREG(16), (input_stride*sizeof(*iPtrR_in)) -(8u*sizeof(*iPtrR_in))*(((blk_w/(8u)))-1u));
   __vcop_pblock_init32(pblock, __offset+_PREG(18), (uchar *)iPtrR_in);
   __vcop_pblock_init32(pblock, __offset+_PREG(20), (uchar *)iPtrG_in);
   __offset += 20;

   /* Loop 2 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), (blk_h)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), ((blk_w/4))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(6), 8);
   __vcop_pblock_init16(pblock, __offset+_PREG(7), (input_stride*sizeof(*iPtrR_in)) -(4*sizeof(*iPtrR_in))*(((blk_w/4))-1u));
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)tempPtrR);
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)LUT);
   __offset += 10;

   /* Loop 3 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), (blk_h)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), ((blk_w/4))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(6), 8);
   __vcop_pblock_init16(pblock, __offset+_PREG(7), (input_stride*sizeof(*iPtrR_in)) -(4*sizeof(*iPtrR_in))*(((blk_w/4))-1u));
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)tempPtrG);
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)LUT);
   __offset += 10;

   /* Loop 4 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), (blk_h)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), ((blk_w/4))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(6), 8);
   __vcop_pblock_init16(pblock, __offset+_PREG(7), (input_stride*sizeof(*iPtrR_in)) -(4*sizeof(*iPtrR_in))*(((blk_w/4))-1u));
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)tempPtrB);
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)LUT);
   __offset += 10;

   /* Loop 5 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), (blk_h)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), ((blk_w/(8u)))-1u);
   __vcop_pblock_init32(pblock, __offset+_PREG(6), (uchar *)tempPtrG);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)tempPtrB);
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)iPtrR_out);
   __vcop_pblock_init32(pblock, __offset+_PREG(12), (uchar *)iPtrG_out);
   __vcop_pblock_init32(pblock, __offset+_PREG(14), (uchar *)iPtrB_out);
   __vcop_pblock_init16(pblock, __offset+_PREG(16), 16);
   __vcop_pblock_init16(pblock, __offset+_PREG(17), (output_stride*sizeof(*iPtrR_in)) -(8u*sizeof(*iPtrR_in))*(((blk_w/(8u)))-1u));
   __vcop_pblock_init32(pblock, __offset+_PREG(18), 2);
   __vcop_pblock_init32(pblock, __offset+_PREG(20), (uchar *)tempPtrR);
   __offset += 20;

   return 70u;
}

void gamma_correction_vloops(
   unsigned short pblock[])
{
   /* Kernel-wide Vector Registers */
   #pragma VCC_VREG("Vblue", 16);
   #pragma VCC_VREG("Vgreen", 17);
   #pragma VCC_VREG("Vred", 18);
   #pragma VCC_VREG("Vshift", 19);

   __vcop_param(&pblock[0]);

   /* VLOOP 1 Start */

   /* VLOOP Local Vector Registers */
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("Addr", "A0");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I0", "I3");
   #pragma EVE_REG("I1", "I4");
   

   __vcop_vloop(__vcop_compute(), 8u, 10u, 1u);
   __vcop_vagen(_AGEN(0), _PREG(7), _PREG(16), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeHU(), __vcop_npt(), _PREG(18), _AGEN(0), _VREG(18), __vcop_alws());
   __vcop_vload(__vcop_sizeHU(), __vcop_npt(), _PREG(20), _AGEN(0), _VREG(17), __vcop_alws());
   __vcop_vload(__vcop_sizeHU(), __vcop_npt(), _PREG(8), _AGEN(0), _VREG(16), __vcop_alws());
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeHU(), __vcop_npt(), __vcop_alws(), _VREG(18), _PREG(10), _AGEN(0), _PREG(6));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeHU(), __vcop_npt(), __vcop_alws(), _VREG(17), _PREG(12), _AGEN(0), _PREG(6));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeHU(), __vcop_npt(), __vcop_alws(), _VREG(16), _PREG(14), _AGEN(0), _PREG(6));
   __vcop_vloop_end(1u);

   /* VLOOP 2 Start */

   /* VLOOP Local Vector Registers */
   #pragma VCC_VREG("Vr", 20);
   #pragma VCC_VREG("Vtbl_Rval", 21);
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("AddrR_in", "A0");
   #pragma EVE_REG("AddrR_out", "A2");
   #pragma EVE_REG("tblR_index", "A1");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I2", "I3");
   #pragma EVE_REG("I3", "I4");
   

   __vcop_vloop(__vcop_tablelkup(), 7u, 5u, 2u);
   __vcop_vagen(_AGEN(0), _PREG(6), _PREG(7), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(2), _PREG(6), _PREG(7), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(1), _PREG(0), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeHU(), __vcop_npt(), _PREG(8), _AGEN(0), _VREG(20), __vcop_alws());
   __vcop_vtbload(__vcop_sizeHU(), __vcop_tableinfo(4, 1), _PREG(10), _AGEN(1), _VREG(20), _VREG(21), _PREG(0), __vcop_alws());
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeHU(), __vcop_npt(), __vcop_alws(), _VREG(21), _PREG(8), _AGEN(2), _PREG(0));
   __vcop_vloop_end(2u);

   /* VLOOP 3 Start */

   /* VLOOP Local Vector Registers */
   #pragma VCC_VREG("Vg", 22);
   #pragma VCC_VREG("Vtbl_Gval", 23);
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("AddrG_in", "A0");
   #pragma EVE_REG("AddrG_out", "A2");
   #pragma EVE_REG("tblG_index", "A1");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I2", "I3");
   #pragma EVE_REG("I3", "I4");
   

   __vcop_vloop(__vcop_tablelkup(), 7u, 5u, 3u);
   __vcop_vagen(_AGEN(0), _PREG(6), _PREG(7), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(2), _PREG(6), _PREG(7), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(1), _PREG(0), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeHU(), __vcop_npt(), _PREG(8), _AGEN(0), _VREG(22), __vcop_alws());
   __vcop_vtbload(__vcop_sizeHU(), __vcop_tableinfo(4, 1), _PREG(10), _AGEN(1), _VREG(22), _VREG(23), _PREG(0), __vcop_alws());
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeHU(), __vcop_npt(), __vcop_alws(), _VREG(23), _PREG(8), _AGEN(2), _PREG(0));
   __vcop_vloop_end(3u);

   /* VLOOP 4 Start */

   /* VLOOP Local Vector Registers */
   #pragma VCC_VREG("Vb", 24);
   #pragma VCC_VREG("Vtbl_Bval", 25);
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("AddrB_in", "A0");
   #pragma EVE_REG("AddrB_out", "A2");
   #pragma EVE_REG("tblB_index", "A1");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I2", "I3");
   #pragma EVE_REG("I3", "I4");
   

   __vcop_vloop(__vcop_tablelkup(), 7u, 5u, 4u);
   __vcop_vagen(_AGEN(0), _PREG(6), _PREG(7), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(2), _PREG(6), _PREG(7), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(1), _PREG(0), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeHU(), __vcop_npt(), _PREG(8), _AGEN(0), _VREG(24), __vcop_alws());
   __vcop_vtbload(__vcop_sizeHU(), __vcop_tableinfo(4, 1), _PREG(10), _AGEN(1), _VREG(24), _VREG(25), _PREG(0), __vcop_alws());
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeHU(), __vcop_npt(), __vcop_alws(), _VREG(25), _PREG(8), _AGEN(2), _PREG(0));
   __vcop_vloop_end(4u);

   /* VLOOP 5 Start */

   /* VLOOP Local Vector Registers */
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("Addr", "A0");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I4", "I3");
   #pragma EVE_REG("I5", "I4");
   

   __vcop_vloop(__vcop_compute(), 12u, 10u, 5u);
   __vcop_vinit(__vcop_sizeW(), __vcop_once(), _PREG(18), _VREG(19));
   __vcop_vagen(_AGEN(0), _PREG(16), _PREG(17), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeHU(), __vcop_npt(), _PREG(20), _AGEN(0), _VREG(18), __vcop_alws());
   __vcop_vload(__vcop_sizeHU(), __vcop_npt(), _PREG(6), _AGEN(0), _VREG(17), __vcop_alws());
   __vcop_vload(__vcop_sizeHU(), __vcop_npt(), _PREG(8), _AGEN(0), _VREG(16), __vcop_alws());
   __vcop_vshf(_VREG(18), _VREG(19), _VREG(18));
   __vcop_vshf(_VREG(17), _VREG(19), _VREG(17));
   __vcop_vshf(_VREG(16), _VREG(19), _VREG(16));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeHU(), __vcop_npt(), __vcop_alws(), _VREG(18), _PREG(10), _AGEN(0), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeHU(), __vcop_npt(), __vcop_alws(), _VREG(17), _PREG(12), _AGEN(0), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeHU(), __vcop_npt(), __vcop_alws(), _VREG(16), _PREG(14), _AGEN(0), _PREG(0));
   __vcop_vloop_end(5u);

}

void gamma_correction(
   __vptr_uint16 iPtrR_in,
   __vptr_uint16 iPtrG_in,
   __vptr_uint16 iPtrB_in,
   __vptr_uint16 iPtrR_out,
   __vptr_uint16 iPtrG_out,
   __vptr_uint16 iPtrB_out,
   unsigned short blk_w,
   unsigned short blk_h,
   unsigned short input_stride,
   unsigned short output_stride,
   __vptr_uint16 tempPtrR,
   __vptr_uint16 tempPtrG,
   __vptr_uint16 tempPtrB,
   __vptr_uint16 LUT)
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   gamma_correction_init(iPtrR_in, iPtrG_in, iPtrB_in, iPtrR_out, iPtrG_out, iPtrB_out, blk_w, blk_h, input_stride, output_stride, tempPtrR, tempPtrG, tempPtrB, LUT, __pblock_gamma_correction);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   gamma_correction_vloops(__pblock_gamma_correction);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

void gamma_correction_custom(
   __vptr_uint16 iPtrR_in,
   __vptr_uint16 iPtrG_in,
   __vptr_uint16 iPtrB_in,
   __vptr_uint16 iPtrR_out,
   __vptr_uint16 iPtrG_out,
   __vptr_uint16 iPtrB_out,
   unsigned short blk_w,
   unsigned short blk_h,
   unsigned short input_stride,
   unsigned short output_stride,
   __vptr_uint16 tempPtrR,
   __vptr_uint16 tempPtrG,
   __vptr_uint16 tempPtrB,
   __vptr_uint16 LUT,
   unsigned short pblock[])
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   gamma_correction_init(iPtrR_in, iPtrG_in, iPtrB_in, iPtrR_out, iPtrG_out, iPtrB_out, blk_w, blk_h, input_stride, output_stride, tempPtrR, tempPtrG, tempPtrB, LUT, pblock);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   gamma_correction_vloops(pblock);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

