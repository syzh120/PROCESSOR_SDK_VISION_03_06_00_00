#include <vcop\vcop.h>

typedef unsigned char uchar;

#pragma DATA_SECTION(__pblock_vcop_img_bilateralFilter, ".vcop_parameter_block")
#pragma DATA_ALIGN(__pblock_vcop_img_bilateralFilter, __ALIGNOF__(int));
unsigned short __pblock_vcop_img_bilateralFilter[100];

unsigned int vcop_img_bilateralFilter_param_count(void)
{
   return 100u;
}

unsigned int vcop_img_bilateralFilter_ctrl_count(void)
{
   return 0u;
}

unsigned int vcop_img_bilateralFilter_init(
   __vptr_uint8 input_ptr,
   __vptr_uint8 output_ptr,
   __vptr_uint8 diff_ptr,
   __vptr_uint16 G_pq_ptr,
   __vptr_uint32 W_p_ptr,
   __vptr_uint32 BF_p_ptr,
   __vptr_uint16 LUT_RANGE_8TBL,
   __vptr_uint16 LUT_SPACE_TBL,
   int blk_width,
   int blk_height,
   int blk_stride,
   int horz_pad_size,
   int vert_pad_size,
   unsigned int Qpoint_tbl,
   unsigned int Qpoint_div,
   unsigned char pixel_format,
   unsigned short pblock[])
{
   int __offset = 0;
   /* Loop 1 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), (blk_height)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), ((blk_width/(2*(8u))))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), (5)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), (5)-1u);
   __vcop_pblock_init32(pblock, __offset+_PREG(6), (uchar *)input_ptr);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)diff_ptr);
   __vcop_pblock_init16(pblock, __offset+_PREG(10), 16);
   __vcop_pblock_init16(pblock, __offset+_PREG(11), (blk_stride) -((2*8u))*(((blk_width/(2*(8u))))-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(12), (blk_width*blk_height));
   __vcop_pblock_init16(pblock, __offset+_PREG(13), (blk_width*blk_height*5) -(blk_width*blk_height)*((5)-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(14), ((2*8u)) -(blk_width*blk_height*5)*((5)-1u) -(blk_width*blk_height)*((5)-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(15), (blk_width) -((2*8u))*(((blk_width/(2*(8u))))-1u) -(blk_width*blk_height*5)*((5)-1u) -(blk_width*blk_height)*((5)-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(16), (pixel_format));
   __vcop_pblock_init16(pblock, __offset+_PREG(17), (blk_stride) -(pixel_format)*((5)-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(18), ((2*8u)) -(blk_stride)*((5)-1u) -(pixel_format)*((5)-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(19), (blk_stride) -((2*8u))*(((blk_width/(2*(8u))))-1u) -(blk_stride)*((5)-1u) -(pixel_format)*((5)-1u));
   __vcop_pblock_init32(pblock, __offset+_PREG(20), (uchar *)input_ptr+vert_pad_size*blk_stride+horz_pad_size);
   __vcop_pblock_init32(pblock, __offset+_PREG(22), 0);
   __offset += 22;

   /* Loop 2 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), (((5)*(5)))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), (((blk_height*blk_width)/(8u)))-1u);
   __vcop_pblock_init32(pblock, __offset+_PREG(6), (uchar *)G_pq_ptr);
   __vcop_pblock_init16(pblock, __offset+_PREG(8), 16);
   __vcop_pblock_init16(pblock, __offset+_PREG(9), (blk_height*blk_width*2) -(8u*2)*((((blk_height*blk_width)/(8u)))-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(10), 8);
   __vcop_pblock_init16(pblock, __offset+_PREG(11), (blk_height*blk_width) -(8u)*((((blk_height*blk_width)/(8u)))-1u));
   __vcop_pblock_init32(pblock, __offset+_PREG(12), (uchar *)diff_ptr);
   __vcop_pblock_init32(pblock, __offset+_PREG(14), (uchar *)LUT_RANGE_8TBL);
   __offset += 14;

   /* Loop 3 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), (blk_height)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), ((blk_width/(2*(8u))))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), ((5))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), ((5))-1u);
   __vcop_pblock_init32(pblock, __offset+_PREG(6), (uchar *)input_ptr);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)input_ptr+8u);
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)G_pq_ptr);
   __vcop_pblock_init32(pblock, __offset+_PREG(12), (uchar *)G_pq_ptr+8u*2);
   __vcop_pblock_init16(pblock, __offset+_PREG(14), __vcop_vop_round(2, 8));
   __vcop_pblock_init16(pblock, __offset+_PREG(15), 64);
   __vcop_pblock_init32(pblock, __offset+_PREG(16), (uchar *)W_p_ptr);
   __vcop_pblock_init32(pblock, __offset+_PREG(18), (uchar *)W_p_ptr+8u*4);
   __vcop_pblock_init32(pblock, __offset+_PREG(20), (uchar *)BF_p_ptr);
   __vcop_pblock_init32(pblock, __offset+_PREG(22), (uchar *)BF_p_ptr+8u*4);
   __vcop_pblock_init16(pblock, __offset+_PREG(24), (blk_width*4) -(4*(2*8u))*(((blk_width/(2*(8u))))-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(25), 2);
   __vcop_pblock_init16(pblock, __offset+_PREG(26), -48);
   __vcop_pblock_init16(pblock, __offset+_PREG(27), (pixel_format));
   __vcop_pblock_init16(pblock, __offset+_PREG(28), (blk_stride) -(pixel_format)*(((5))-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(29), ((2*8u)) -(blk_stride)*(((5))-1u) -(pixel_format)*(((5))-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(30), (blk_stride) -((2*8u))*(((blk_width/(2*(8u))))-1u) -(blk_stride)*(((5))-1u) -(pixel_format)*(((5))-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(31), (blk_height*blk_width*2));
   __vcop_pblock_init16(pblock, __offset+_PREG(32), (5*blk_height*blk_width*2) -(blk_height*blk_width*2)*(((5))-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(33), ((2*8u)*2) -(5*blk_height*blk_width*2)*(((5))-1u) -(blk_height*blk_width*2)*(((5))-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(34), (blk_width*2) -((2*8u)*2)*(((blk_width/(2*(8u))))-1u) -(5*blk_height*blk_width*2)*(((5))-1u) -(blk_height*blk_width*2)*(((5))-1u));
   __vcop_pblock_init32(pblock, __offset+_PREG(36), 0);
   __vcop_pblock_init32(pblock, __offset+_PREG(38), (uchar *)LUT_SPACE_TBL);
   __offset += 38;

   /* Loop 4 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), (blk_height)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), ((blk_width/(8u)))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(6), __vcop_store_round_sat(SM_NONE,0,RM_ROUND,Qpoint_tbl));
   __vcop_pblock_init16(pblock, __offset+_PREG(7), 32);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), Qpoint_tbl - 28);
   __vcop_pblock_init32(pblock, __offset+_PREG(10), 268435456);
   __vcop_pblock_init32(pblock, __offset+_PREG(12), 0x0FFFFFFF);
   __vcop_pblock_init32(pblock, __offset+_PREG(14), (uchar *)BF_p_ptr);
   __vcop_pblock_init32(pblock, __offset+_PREG(16), (uchar *)W_p_ptr);
   __vcop_pblock_init32(pblock, __offset+_PREG(18), (uchar *)output_ptr);
   __vcop_pblock_init16(pblock, __offset+_PREG(20), (blk_width*4) -(8u*4)*(((blk_width/(8u)))-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(21), 8);
   __vcop_pblock_init16(pblock, __offset+_PREG(22), (blk_width) -(8u)*(((blk_width/(8u)))-1u));
   __vcop_pblock_init32(pblock, __offset+_PREG(24), Qpoint_div - Qpoint_tbl);
   __vcop_pblock_init32(pblock, __offset+_PREG(26), -28);
   __offset += 26;

   return 100u;
}

void vcop_img_bilateralFilter_vloops(
   unsigned short pblock[])
{
   /* Kernel-wide Vector Registers */
   #pragma VCC_VREG("V2_to_28", 16);
   #pragma VCC_VREG("VQm28", 17);
   #pragma VCC_VREG("VbinX", 18);
   #pragma VCC_VREG("VbinY", 19);
   #pragma VCC_VREG("Vdelta", 20);
   #pragma VCC_VREG("Vexp", 21);
   #pragma VCC_VREG("Vexp_adj", 22);
   #pragma VCC_VREG("Vfmask", 23);
   #pragma VCC_VREG("Vfrac", 24);
   #pragma VCC_VREG("Vfrac_p1", 25);
   #pragma VCC_VREG("Vin1", 26);
   #pragma VCC_VREG("Vin2", 27);
   #pragma VCC_VREG("Vm28", 28);
   #pragma VCC_VREG("Vout", 29);
   #pragma VCC_VREG("Vshift", 30);

   __vcop_param(&pblock[0]);

   /* VLOOP 1 Start */

   /* VLOOP Local Vector Registers */
   #pragma VCC_VREG("VI_p_1", 31);
   #pragma VCC_VREG("VI_p_2", 32);
   #pragma VCC_VREG("VI_q_1", 33);
   #pragma VCC_VREG("VI_q_2", 34);
   #pragma VCC_VREG("Vdiff_1", 35);
   #pragma VCC_VREG("Vdiff_2", 36);
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("Addr_ctrl", "A0");
   #pragma EVE_REG("Addr_diff_out", "A1");
   #pragma EVE_REG("Addr_nbr_pixel", "A2");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("i", "I1");
   #pragma EVE_REG("j", "I2");
   #pragma EVE_REG("s", "I3");
   #pragma EVE_REG("t", "I4");
   

   __vcop_vloop(__vcop_compute(), 11u, 11u, 1u);
   __vcop_vinit(__vcop_sizeW(), __vcop_alws(), _PREG(22), _VREG(35));
   __vcop_vinit(__vcop_sizeW(), __vcop_alws(), _PREG(22), _VREG(36));
   __vcop_vagen(_AGEN(0), _PREG(0), _PREG(0), _PREG(10), _PREG(11));
   __vcop_vagen(_AGEN(1), _PREG(12), _PREG(13), _PREG(14), _PREG(15));
   __vcop_vagen(_AGEN(2), _PREG(16), _PREG(17), _PREG(18), _PREG(19));
   __vcop_vload(__vcop_sizeBU(), __vcop_dintrlv(), _PREG(20), _AGEN(0), _VPAIR(31,32), __vcop_i34_zero());
   __vcop_vload(__vcop_sizeBU(), __vcop_dintrlv(), _PREG(6), _AGEN(2), _VPAIR(33,34), __vcop_alws());
   __vcop_vsad(_VREG(31), _VREG(33), _VREG(35));
   __vcop_vsad(_VREG(32), _VREG(34), _VREG(36));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeBU(), __vcop_intrlv(), __vcop_alws(), _VPAIR(35,36), _PREG(8), _AGEN(1), _PREG(0));
   __vcop_vloop_end(1u);

   /* VLOOP 2 Start */

   /* VLOOP Local Vector Registers */
   #pragma VCC_VREG("VG_pq", 37);
   #pragma VCC_VREG("Vdiff_val", 38);
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("Gpq_offset", "A2");
   #pragma EVE_REG("diff_offset", "A0");
   #pragma EVE_REG("table_index", "A1");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("i", "I3");
   #pragma EVE_REG("j", "I4");
   

   __vcop_vloop(__vcop_tablelkup(), 7u, 7u, 2u);
   __vcop_vagen(_AGEN(2), _PREG(8), _PREG(9), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(0), _PREG(10), _PREG(11), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(1), _PREG(0), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeBU(), __vcop_npt(), _PREG(12), _AGEN(0), _VREG(38), __vcop_alws());
   __vcop_vtbload(__vcop_sizeHU(), __vcop_tableinfo(8, 1), _PREG(14), _AGEN(1), _VREG(38), _VREG(37), _PREG(0), __vcop_alws());
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeHU(), __vcop_npt(), __vcop_alws(), _VREG(37), _PREG(6), _AGEN(2), _PREG(0));
   __vcop_vloop_end(2u);

   /* VLOOP 3 Start */

   /* VLOOP Local Vector Registers */
   #pragma VCC_VREG("VBF_p_1", 39);
   #pragma VCC_VREG("VBF_p_2", 40);
   #pragma VCC_VREG("VW_p_1", 41);
   #pragma VCC_VREG("VW_p_2", 42);
   #pragma VCC_VREG("VG_pq_1", 43);
   #pragma VCC_VREG("VG_pq_2", 44);
   #pragma VCC_VREG("VI_q_1", 45);
   #pragma VCC_VREG("VI_q_2", 46);
   #pragma VCC_VREG("Vlut_r_1", 47);
   #pragma VCC_VREG("Vlut_r_2", 48);
   #pragma VCC_VREG("Vlut_s", 49);
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("Addr_output", "A0");
   #pragma EVE_REG("Add_lut_s", "A1");
   #pragma EVE_REG("Addr_nbr_pixel_1", "A2");
   #pragma EVE_REG("Addr_nbr_pixel_2", "A3");
   #pragma EVE_REG("Gpq_offset", "A4");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("m", "I1");
   #pragma EVE_REG("n", "I2");
   #pragma EVE_REG("p", "I3");
   #pragma EVE_REG("q", "I4");
   

   __vcop_vloop(__vcop_compute(), 25u, 19u, 3u);
   __vcop_vinit(__vcop_sizeW(), __vcop_i34_zero(), _PREG(36), _VREG(41));
   __vcop_vinit(__vcop_sizeW(), __vcop_i34_zero(), _PREG(36), _VREG(39));
   __vcop_vinit(__vcop_sizeW(), __vcop_i34_zero(), _PREG(36), _VREG(42));
   __vcop_vinit(__vcop_sizeW(), __vcop_i34_zero(), _PREG(36), _VREG(40));
   __vcop_vagen(_AGEN(0), _PREG(0), _PREG(0), _PREG(15), _PREG(24));
   __vcop_vagen(_AGEN(1), _PREG(25), _PREG(25), _PREG(26), _PREG(26));
   __vcop_vagen(_AGEN(2), _PREG(27), _PREG(28), _PREG(29), _PREG(30));
   __vcop_vagen(_AGEN(3), _PREG(27), _PREG(28), _PREG(29), _PREG(30));
   __vcop_vagen(_AGEN(4), _PREG(31), _PREG(32), _PREG(33), _PREG(34));
   __vcop_vload(__vcop_sizeHU(), __vcop_1pt(), _PREG(38), _AGEN(1), _VREG(49), __vcop_alws());
   __vcop_vload(__vcop_sizeBU(), __vcop_npt(), _PREG(6), _AGEN(2), _VREG(45), __vcop_alws());
   __vcop_vload(__vcop_sizeBU(), __vcop_npt(), _PREG(8), _AGEN(3), _VREG(46), __vcop_alws());
   __vcop_vload(__vcop_sizeHU(), __vcop_npt(), _PREG(10), _AGEN(4), _VREG(47), __vcop_alws());
   __vcop_vload(__vcop_sizeHU(), __vcop_npt(), _PREG(12), _AGEN(4), _VREG(48), __vcop_alws());
   __vcop_vmpy(_VREG(49), _VREG(47), _VREG(43), _PREG(14));
   __vcop_vmpy(_VREG(49), _VREG(48), _VREG(44), _PREG(14));
   __vcop_vadd(_VREG(41), _VREG(43), _VREG(41));
   __vcop_vadd(_VREG(42), _VREG(44), _VREG(42));
   __vcop_vmadd(_VREG(45), _VREG(43), _VREG(39), _PREG(0));
   __vcop_vmadd(_VREG(46), _VREG(44), _VREG(40), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeWU(), __vcop_npt(), __vcop_last_i34(), _VREG(41), _PREG(16), _AGEN(0), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeWU(), __vcop_npt(), __vcop_last_i34(), _VREG(42), _PREG(18), _AGEN(0), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeWU(), __vcop_npt(), __vcop_last_i34(), _VREG(39), _PREG(20), _AGEN(0), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeWU(), __vcop_npt(), __vcop_last_i34(), _VREG(40), _PREG(22), _AGEN(0), _PREG(0));
   __vcop_vloop_end(3u);

   /* VLOOP 4 Start */

   /* VLOOP Local Vector Registers */
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("Addr_input", "A0");
   #pragma EVE_REG("Addr_output", "A1");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("i", "I3");
   #pragma EVE_REG("j", "I4");
   

   __vcop_vloop(__vcop_compute(), 21u, 13u, 4u);
   __vcop_vinit(__vcop_sizeW(), __vcop_once(), _PREG(24), _VREG(30));
   __vcop_vinit(__vcop_sizeW(), __vcop_once(), _PREG(26), _VREG(28));
   __vcop_vinit(__vcop_sizeW(), __vcop_once(), _PREG(8), _VREG(17));
   __vcop_vinit(__vcop_sizeW(), __vcop_once(), _PREG(10), _VREG(16));
   __vcop_vinit(__vcop_sizeW(), __vcop_once(), _PREG(12), _VREG(23));
   __vcop_vagen(_AGEN(0), _PREG(7), _PREG(20), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(1), _PREG(21), _PREG(22), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeWU(), __vcop_npt(), _PREG(14), _AGEN(0), _VREG(26), __vcop_alws());
   __vcop_vload(__vcop_sizeWU(), __vcop_npt(), _PREG(16), _AGEN(0), _VREG(27), __vcop_alws());
   __vcop_vshf(_VREG(26), _VREG(30), _VREG(26));
   __vcop_vshf(_VREG(27), _VREG(30), _VREG(27));
   __vcop_vbinlog(_VREG(26), _VREG(18));
   __vcop_vbinlog(_VREG(27), _VREG(19));
   __vcop_vsub(_VREG(18), _VREG(19), _VREG(20));
   __vcop_vand(_VREG(20), _VREG(23), _VREG(24));
   __vcop_vshf(_VREG(20), _VREG(28), _VREG(21));
   __vcop_vor(_VREG(24), _VREG(16), _VREG(25));
   __vcop_vadd(_VREG(21), _VREG(17), _VREG(22));
   __vcop_vshf(_VREG(25), _VREG(22), _VREG(29));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeBU(), __vcop_npt(), __vcop_alws(), _VREG(29), _PREG(18), _AGEN(1), _PREG(6));
   __vcop_vloop_end(4u);

}

void vcop_img_bilateralFilter(
   __vptr_uint8 input_ptr,
   __vptr_uint8 output_ptr,
   __vptr_uint8 diff_ptr,
   __vptr_uint16 G_pq_ptr,
   __vptr_uint32 W_p_ptr,
   __vptr_uint32 BF_p_ptr,
   __vptr_uint16 LUT_RANGE_8TBL,
   __vptr_uint16 LUT_SPACE_TBL,
   int blk_width,
   int blk_height,
   int blk_stride,
   int horz_pad_size,
   int vert_pad_size,
   unsigned int Qpoint_tbl,
   unsigned int Qpoint_div,
   unsigned char pixel_format)
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_img_bilateralFilter_init(input_ptr, output_ptr, diff_ptr, G_pq_ptr, W_p_ptr, BF_p_ptr, LUT_RANGE_8TBL, LUT_SPACE_TBL, blk_width, blk_height, blk_stride, horz_pad_size, vert_pad_size, Qpoint_tbl, Qpoint_div, pixel_format, __pblock_vcop_img_bilateralFilter);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_img_bilateralFilter_vloops(__pblock_vcop_img_bilateralFilter);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

void vcop_img_bilateralFilter_custom(
   __vptr_uint8 input_ptr,
   __vptr_uint8 output_ptr,
   __vptr_uint8 diff_ptr,
   __vptr_uint16 G_pq_ptr,
   __vptr_uint32 W_p_ptr,
   __vptr_uint32 BF_p_ptr,
   __vptr_uint16 LUT_RANGE_8TBL,
   __vptr_uint16 LUT_SPACE_TBL,
   int blk_width,
   int blk_height,
   int blk_stride,
   int horz_pad_size,
   int vert_pad_size,
   unsigned int Qpoint_tbl,
   unsigned int Qpoint_div,
   unsigned char pixel_format,
   unsigned short pblock[])
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_img_bilateralFilter_init(input_ptr, output_ptr, diff_ptr, G_pq_ptr, W_p_ptr, BF_p_ptr, LUT_RANGE_8TBL, LUT_SPACE_TBL, blk_width, blk_height, blk_stride, horz_pad_size, vert_pad_size, Qpoint_tbl, Qpoint_div, pixel_format, pblock);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_img_bilateralFilter_vloops(pblock);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

