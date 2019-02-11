#include <vcop\vcop.h>

typedef unsigned char uchar;

#pragma DATA_SECTION(__pblock_vcop_grayscale_dilate_mask, ".vcop_parameter_block")
#pragma DATA_ALIGN(__pblock_vcop_grayscale_dilate_mask, __ALIGNOF__(int));
unsigned short __pblock_vcop_grayscale_dilate_mask[20];

unsigned int vcop_grayscale_dilate_mask_param_count(void)
{
   return 20u;
}

unsigned int vcop_grayscale_dilate_mask_ctrl_count(void)
{
   return 0u;
}

unsigned int vcop_grayscale_dilate_mask_init(
   unsigned short blk_w,
   unsigned short line_ofst,
   unsigned short blk_h,
   __vptr_uint8 data_ptr,
   unsigned short se_w,
   unsigned short se_h,
   __vptr_uint8 se_ptr,
   __vptr_uint8 output_ptr,
   unsigned short pblock[])
{
   int __offset = 0;
   /* Loop 1 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), (blk_h-se_h+1)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), (((blk_w-se_w+(2 * (8u)))/(2 * (8u))))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), (se_h)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), (se_w)-1u);
   __vcop_pblock_init32(pblock, __offset+_PREG(6), (uchar *)se_ptr);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)output_ptr);
   __vcop_pblock_init16(pblock, __offset+_PREG(10), 16);
   __vcop_pblock_init16(pblock, __offset+_PREG(11), ((line_ofst*sizeof(*output_ptr))) -((2*8u*sizeof(*output_ptr)))*((((blk_w-se_w+(2 * (8u)))/(2 * (8u))))-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(12), ((line_ofst*sizeof(*data_ptr))) -(sizeof(*data_ptr))*((se_w)-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(13), ((2*8u*sizeof(*data_ptr))) -((line_ofst*sizeof(*data_ptr)))*((se_h)-1u) -(sizeof(*data_ptr))*((se_w)-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(14), ((line_ofst*sizeof(*data_ptr))) -((2*8u*sizeof(*data_ptr)))*((((blk_w-se_w+(2 * (8u)))/(2 * (8u))))-1u) -((line_ofst*sizeof(*data_ptr)))*((se_h)-1u) -(sizeof(*data_ptr))*((se_w)-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(15), ((se_w*sizeof(*se_ptr))) -(sizeof(*se_ptr))*((se_w)-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(16),  -((se_w*sizeof(*se_ptr)))*((se_h)-1u) -(sizeof(*se_ptr))*((se_w)-1u));
   __vcop_pblock_init32(pblock, __offset+_PREG(18), 0);
   __vcop_pblock_init32(pblock, __offset+_PREG(20), (uchar *)data_ptr);
   __offset += 20;

   return 20u;
}

void vcop_grayscale_dilate_mask_vloops(
   unsigned short pblock[])
{
   /* Kernel-wide Vector Registers */
   #pragma VCC_VREG("Vin1", 16);
   #pragma VCC_VREG("Vin2", 17);
   #pragma VCC_VREG("Vmax1", 18);
   #pragma VCC_VREG("Vmax2", 19);
   #pragma VCC_VREG("Vse", 20);
   #pragma VCC_VREG("Vsmall1", 21);
   #pragma VCC_VREG("Vsmall2", 22);

   __vcop_param(&pblock[0]);

   /* VLOOP 1 Start */

   /* VLOOP Local Vector Registers */
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("A2", "A0");
   #pragma EVE_REG("A0", "A1");
   #pragma EVE_REG("A1", "A2");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I1", "I1");
   #pragma EVE_REG("I2", "I2");
   #pragma EVE_REG("I3", "I3");
   #pragma EVE_REG("I4", "I4");
   

   __vcop_vloop(__vcop_compute(), 15u, 10u, 1u);
   __vcop_vinit(__vcop_sizeW(), __vcop_i34_zero(), _PREG(18), _VREG(18));
   __vcop_vinit(__vcop_sizeW(), __vcop_i34_zero(), _PREG(18), _VREG(19));
   __vcop_vinit(__vcop_sizeW(), __vcop_alws(), _PREG(18), _VREG(21));
   __vcop_vinit(__vcop_sizeW(), __vcop_alws(), _PREG(18), _VREG(22));
   __vcop_vagen(_AGEN(0), _PREG(0), _PREG(0), _PREG(10), _PREG(11));
   __vcop_vagen(_AGEN(1), _PREG(1), _PREG(12), _PREG(13), _PREG(14));
   __vcop_vagen(_AGEN(2), _PREG(1), _PREG(15), _PREG(16), _PREG(16));
   __vcop_vload(__vcop_sizeBU(), __vcop_dintrlv(), _PREG(20), _AGEN(1), _VPAIR(16,17), __vcop_alws());
   __vcop_vload(__vcop_sizeBU(), __vcop_1pt(), _PREG(6), _AGEN(2), _VREG(20), __vcop_alws());
   __vcop_vsel(_VREG(20), _VREG(16), _VREG(21));
   __vcop_vsel(_VREG(20), _VREG(17), _VREG(22));
   __vcop_vmax(_VREG(21), _VREG(18), _VREG(18));
   __vcop_vmax(_VREG(22), _VREG(19), _VREG(19));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeBU(), __vcop_intrlv(), __vcop_last_i34(), _VPAIR(18,19), _PREG(8), _AGEN(0), _PREG(0));
   __vcop_vloop_end(1u);

}

void vcop_grayscale_dilate_mask(
   unsigned short blk_w,
   unsigned short line_ofst,
   unsigned short blk_h,
   __vptr_uint8 data_ptr,
   unsigned short se_w,
   unsigned short se_h,
   __vptr_uint8 se_ptr,
   __vptr_uint8 output_ptr)
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_grayscale_dilate_mask_init(blk_w, line_ofst, blk_h, data_ptr, se_w, se_h, se_ptr, output_ptr, __pblock_vcop_grayscale_dilate_mask);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_grayscale_dilate_mask_vloops(__pblock_vcop_grayscale_dilate_mask);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

void vcop_grayscale_dilate_mask_custom(
   unsigned short blk_w,
   unsigned short line_ofst,
   unsigned short blk_h,
   __vptr_uint8 data_ptr,
   unsigned short se_w,
   unsigned short se_h,
   __vptr_uint8 se_ptr,
   __vptr_uint8 output_ptr,
   unsigned short pblock[])
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_grayscale_dilate_mask_init(blk_w, line_ofst, blk_h, data_ptr, se_w, se_h, se_ptr, output_ptr, pblock);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_grayscale_dilate_mask_vloops(pblock);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

#pragma DATA_SECTION(__pblock_vcop_grayscale_erode_mask, ".vcop_parameter_block")
#pragma DATA_ALIGN(__pblock_vcop_grayscale_erode_mask, __ALIGNOF__(int));
unsigned short __pblock_vcop_grayscale_erode_mask[20];

unsigned int vcop_grayscale_erode_mask_param_count(void)
{
   return 20u;
}

unsigned int vcop_grayscale_erode_mask_ctrl_count(void)
{
   return 0u;
}

unsigned int vcop_grayscale_erode_mask_init(
   unsigned short blk_w,
   unsigned short line_ofst,
   unsigned short blk_h,
   __vptr_uint8 data_ptr,
   unsigned short se_w,
   unsigned short se_h,
   __vptr_uint8 se_ptr,
   __vptr_uint8 output_ptr,
   unsigned short pblock[])
{
   int __offset = 0;
   /* Loop 1 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), (blk_h-se_h+1)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), (((blk_w-se_w+(2 * (8u)))/(2 * (8u))))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), (se_h)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), (se_w)-1u);
   __vcop_pblock_init32(pblock, __offset+_PREG(6), (uchar *)se_ptr);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)output_ptr);
   __vcop_pblock_init16(pblock, __offset+_PREG(10), 16);
   __vcop_pblock_init16(pblock, __offset+_PREG(11), ((line_ofst*sizeof(*output_ptr))) -((2*8u*sizeof(*output_ptr)))*((((blk_w-se_w+(2 * (8u)))/(2 * (8u))))-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(12), ((line_ofst*sizeof(*data_ptr))) -(sizeof(*data_ptr))*((se_w)-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(13), ((2*8u*sizeof(*data_ptr))) -((line_ofst*sizeof(*data_ptr)))*((se_h)-1u) -(sizeof(*data_ptr))*((se_w)-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(14), ((line_ofst*sizeof(*data_ptr))) -((2*8u*sizeof(*data_ptr)))*((((blk_w-se_w+(2 * (8u)))/(2 * (8u))))-1u) -((line_ofst*sizeof(*data_ptr)))*((se_h)-1u) -(sizeof(*data_ptr))*((se_w)-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(15), ((se_w*sizeof(*se_ptr))) -(sizeof(*se_ptr))*((se_w)-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(16),  -((se_w*sizeof(*se_ptr)))*((se_h)-1u) -(sizeof(*se_ptr))*((se_w)-1u));
   __vcop_pblock_init32(pblock, __offset+_PREG(18), 255);
   __vcop_pblock_init32(pblock, __offset+_PREG(20), (uchar *)data_ptr);
   __offset += 20;

   return 20u;
}

void vcop_grayscale_erode_mask_vloops(
   unsigned short pblock[])
{
   /* Kernel-wide Vector Registers */
   #pragma VCC_VREG("Vin1", 16);
   #pragma VCC_VREG("Vin2", 17);
   #pragma VCC_VREG("Vlarge1", 18);
   #pragma VCC_VREG("Vlarge2", 19);
   #pragma VCC_VREG("Vmin1", 20);
   #pragma VCC_VREG("Vmin2", 21);
   #pragma VCC_VREG("Vse", 22);

   __vcop_param(&pblock[0]);

   /* VLOOP 1 Start */

   /* VLOOP Local Vector Registers */
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("A2", "A0");
   #pragma EVE_REG("A0", "A1");
   #pragma EVE_REG("A1", "A2");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I1", "I1");
   #pragma EVE_REG("I2", "I2");
   #pragma EVE_REG("I3", "I3");
   #pragma EVE_REG("I4", "I4");
   

   __vcop_vloop(__vcop_compute(), 15u, 10u, 1u);
   __vcop_vinit(__vcop_sizeW(), __vcop_i34_zero(), _PREG(18), _VREG(20));
   __vcop_vinit(__vcop_sizeW(), __vcop_i34_zero(), _PREG(18), _VREG(21));
   __vcop_vinit(__vcop_sizeW(), __vcop_alws(), _PREG(18), _VREG(18));
   __vcop_vinit(__vcop_sizeW(), __vcop_alws(), _PREG(18), _VREG(19));
   __vcop_vagen(_AGEN(0), _PREG(0), _PREG(0), _PREG(10), _PREG(11));
   __vcop_vagen(_AGEN(1), _PREG(1), _PREG(12), _PREG(13), _PREG(14));
   __vcop_vagen(_AGEN(2), _PREG(1), _PREG(15), _PREG(16), _PREG(16));
   __vcop_vload(__vcop_sizeBU(), __vcop_dintrlv(), _PREG(20), _AGEN(1), _VPAIR(16,17), __vcop_alws());
   __vcop_vload(__vcop_sizeBU(), __vcop_1pt(), _PREG(6), _AGEN(2), _VREG(22), __vcop_alws());
   __vcop_vsel(_VREG(22), _VREG(16), _VREG(18));
   __vcop_vsel(_VREG(22), _VREG(17), _VREG(19));
   __vcop_vmin(_VREG(18), _VREG(20), _VREG(20));
   __vcop_vmin(_VREG(19), _VREG(21), _VREG(21));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeBU(), __vcop_intrlv(), __vcop_last_i34(), _VPAIR(20,21), _PREG(8), _AGEN(0), _PREG(0));
   __vcop_vloop_end(1u);

}

void vcop_grayscale_erode_mask(
   unsigned short blk_w,
   unsigned short line_ofst,
   unsigned short blk_h,
   __vptr_uint8 data_ptr,
   unsigned short se_w,
   unsigned short se_h,
   __vptr_uint8 se_ptr,
   __vptr_uint8 output_ptr)
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_grayscale_erode_mask_init(blk_w, line_ofst, blk_h, data_ptr, se_w, se_h, se_ptr, output_ptr, __pblock_vcop_grayscale_erode_mask);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_grayscale_erode_mask_vloops(__pblock_vcop_grayscale_erode_mask);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

void vcop_grayscale_erode_mask_custom(
   unsigned short blk_w,
   unsigned short line_ofst,
   unsigned short blk_h,
   __vptr_uint8 data_ptr,
   unsigned short se_w,
   unsigned short se_h,
   __vptr_uint8 se_ptr,
   __vptr_uint8 output_ptr,
   unsigned short pblock[])
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_grayscale_erode_mask_init(blk_w, line_ofst, blk_h, data_ptr, se_w, se_h, se_ptr, output_ptr, pblock);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_grayscale_erode_mask_vloops(pblock);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

#pragma DATA_SECTION(__pblock_vcop_grayscale_dilate_rect, ".vcop_parameter_block")
#pragma DATA_ALIGN(__pblock_vcop_grayscale_dilate_rect, __ALIGNOF__(int));
unsigned short __pblock_vcop_grayscale_dilate_rect[32];

unsigned int vcop_grayscale_dilate_rect_param_count(void)
{
   return 32u;
}

unsigned int vcop_grayscale_dilate_rect_ctrl_count(void)
{
   return 0u;
}

unsigned int vcop_grayscale_dilate_rect_init(
   unsigned short blk_w,
   unsigned short line_ofst,
   unsigned short blk_h,
   __vptr_uint8 data_ptr,
   unsigned short se_w,
   unsigned short se_h,
   __vptr_uint8 scratch_ptr,
   __vptr_uint8 output_ptr,
   unsigned short pblock[])
{
   int __offset = 0;
   /* Loop 1 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), (blk_h-se_h+1)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), (((blk_w + (2 * (8u)) - 1)/(2 * (8u))))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), ((se_h-1))-1u);
   __vcop_pblock_init32(pblock, __offset+_PREG(6), (uchar *)scratch_ptr);
   __vcop_pblock_init16(pblock, __offset+_PREG(8), 16);
   __vcop_pblock_init16(pblock, __offset+_PREG(9), ((line_ofst*sizeof(*output_ptr))) -((2*8u*sizeof(*output_ptr)))*((((blk_w + (2 * (8u)) - 1)/(2 * (8u))))-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(10), ((line_ofst*sizeof(*data_ptr))) -((2*8u*sizeof(*data_ptr)))*((((blk_w + (2 * (8u)) - 1)/(2 * (8u))))-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(11), ((line_ofst*sizeof(*data_ptr))));
   __vcop_pblock_init16(pblock, __offset+_PREG(12), ((2*8u*sizeof(*data_ptr))) -((line_ofst*sizeof(*data_ptr)))*(((se_h-1))-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(13), ((line_ofst*sizeof(*data_ptr))) -((2*8u*sizeof(*data_ptr)))*((((blk_w + (2 * (8u)) - 1)/(2 * (8u))))-1u) -((line_ofst*sizeof(*data_ptr)))*(((se_h-1))-1u));
   __vcop_pblock_init32(pblock, __offset+_PREG(14), (uchar *)data_ptr);
   __vcop_pblock_init32(pblock, __offset+_PREG(16), (uchar *)data_ptr+line_ofst*sizeof(*data_ptr));
   __offset += 16;

   /* Loop 2 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), (blk_h-se_h+1)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), (((blk_w-se_w+(2 * (8u)))/(2 * (8u))))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), ((se_w-1))-1u);
   __vcop_pblock_init32(pblock, __offset+_PREG(6), (uchar *)output_ptr);
   __vcop_pblock_init16(pblock, __offset+_PREG(8), 16);
   __vcop_pblock_init16(pblock, __offset+_PREG(9), ((line_ofst*sizeof(*output_ptr))) -((2*8u*sizeof(*output_ptr)))*((((blk_w-se_w+(2 * (8u)))/(2 * (8u))))-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(10), ((line_ofst*sizeof(*data_ptr))) -((2*8u*sizeof(*data_ptr)))*((((blk_w-se_w+(2 * (8u)))/(2 * (8u))))-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(11), ((2*8u*sizeof(*data_ptr))) -(sizeof(*data_ptr))*(((se_w-1))-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(12), ((line_ofst*sizeof(*data_ptr))) -((2*8u*sizeof(*data_ptr)))*((((blk_w-se_w+(2 * (8u)))/(2 * (8u))))-1u) -(sizeof(*data_ptr))*(((se_w-1))-1u));
   __vcop_pblock_init32(pblock, __offset+_PREG(14), (uchar *)scratch_ptr);
   __vcop_pblock_init32(pblock, __offset+_PREG(16), (uchar *)scratch_ptr+sizeof(*data_ptr));
   __offset += 16;

   return 32u;
}

void vcop_grayscale_dilate_rect_vloops(
   unsigned short pblock[])
{
   /* Kernel-wide Vector Registers */
   #pragma VCC_VREG("Vin1", 16);
   #pragma VCC_VREG("Vin2", 17);
   #pragma VCC_VREG("Vmax1", 18);
   #pragma VCC_VREG("Vmax2", 19);

   __vcop_param(&pblock[0]);

   /* VLOOP 1 Start */

   /* VLOOP Local Vector Registers */
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("A1", "A0");
   #pragma EVE_REG("A2", "A1");
   #pragma EVE_REG("A0", "A2");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I1", "I2");
   #pragma EVE_REG("I2", "I3");
   #pragma EVE_REG("I3", "I4");
   

   __vcop_vloop(__vcop_compute(), 9u, 8u, 1u);
   __vcop_vagen(_AGEN(0), _PREG(0), _PREG(8), _PREG(9), _PREG(0));
   __vcop_vagen(_AGEN(1), _PREG(0), _PREG(8), _PREG(10), _PREG(0));
   __vcop_vagen(_AGEN(2), _PREG(11), _PREG(12), _PREG(13), _PREG(0));
   __vcop_vload(__vcop_sizeBU(), __vcop_dintrlv(), _PREG(14), _AGEN(1), _VPAIR(18,19), __vcop_i4_zero());
   __vcop_vload(__vcop_sizeBU(), __vcop_dintrlv(), _PREG(16), _AGEN(2), _VPAIR(16,17), __vcop_alws());
   __vcop_vmax(_VREG(16), _VREG(18), _VREG(18));
   __vcop_vmax(_VREG(17), _VREG(19), _VREG(19));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeBU(), __vcop_intrlv(), __vcop_last_i4(), _VPAIR(18,19), _PREG(6), _AGEN(0), _PREG(0));
   __vcop_vloop_end(1u);

   /* VLOOP 2 Start */

   /* VLOOP Local Vector Registers */
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("A1", "A0");
   #pragma EVE_REG("A2", "A1");
   #pragma EVE_REG("A0", "A2");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I1", "I2");
   #pragma EVE_REG("I2", "I3");
   #pragma EVE_REG("I3", "I4");
   

   __vcop_vloop(__vcop_compute(), 9u, 8u, 2u);
   __vcop_vagen(_AGEN(0), _PREG(0), _PREG(8), _PREG(9), _PREG(0));
   __vcop_vagen(_AGEN(1), _PREG(0), _PREG(8), _PREG(10), _PREG(0));
   __vcop_vagen(_AGEN(2), _PREG(1), _PREG(11), _PREG(12), _PREG(0));
   __vcop_vload(__vcop_sizeBU(), __vcop_dintrlv(), _PREG(14), _AGEN(1), _VPAIR(18,19), __vcop_i4_zero());
   __vcop_vload(__vcop_sizeBU(), __vcop_dintrlv(), _PREG(16), _AGEN(2), _VPAIR(16,17), __vcop_alws());
   __vcop_vmax(_VREG(16), _VREG(18), _VREG(18));
   __vcop_vmax(_VREG(17), _VREG(19), _VREG(19));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeBU(), __vcop_intrlv(), __vcop_last_i4(), _VPAIR(18,19), _PREG(6), _AGEN(0), _PREG(0));
   __vcop_vloop_end(2u);

}

void vcop_grayscale_dilate_rect(
   unsigned short blk_w,
   unsigned short line_ofst,
   unsigned short blk_h,
   __vptr_uint8 data_ptr,
   unsigned short se_w,
   unsigned short se_h,
   __vptr_uint8 scratch_ptr,
   __vptr_uint8 output_ptr)
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_grayscale_dilate_rect_init(blk_w, line_ofst, blk_h, data_ptr, se_w, se_h, scratch_ptr, output_ptr, __pblock_vcop_grayscale_dilate_rect);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_grayscale_dilate_rect_vloops(__pblock_vcop_grayscale_dilate_rect);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

void vcop_grayscale_dilate_rect_custom(
   unsigned short blk_w,
   unsigned short line_ofst,
   unsigned short blk_h,
   __vptr_uint8 data_ptr,
   unsigned short se_w,
   unsigned short se_h,
   __vptr_uint8 scratch_ptr,
   __vptr_uint8 output_ptr,
   unsigned short pblock[])
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_grayscale_dilate_rect_init(blk_w, line_ofst, blk_h, data_ptr, se_w, se_h, scratch_ptr, output_ptr, pblock);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_grayscale_dilate_rect_vloops(pblock);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

#pragma DATA_SECTION(__pblock_vcop_grayscale_erode_rect, ".vcop_parameter_block")
#pragma DATA_ALIGN(__pblock_vcop_grayscale_erode_rect, __ALIGNOF__(int));
unsigned short __pblock_vcop_grayscale_erode_rect[32];

unsigned int vcop_grayscale_erode_rect_param_count(void)
{
   return 32u;
}

unsigned int vcop_grayscale_erode_rect_ctrl_count(void)
{
   return 0u;
}

unsigned int vcop_grayscale_erode_rect_init(
   unsigned short blk_w,
   unsigned short line_ofst,
   unsigned short blk_h,
   __vptr_uint8 data_ptr,
   unsigned short se_w,
   unsigned short se_h,
   __vptr_uint8 scratch_ptr,
   __vptr_uint8 output_ptr,
   unsigned short pblock[])
{
   int __offset = 0;
   /* Loop 1 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), (blk_h-se_h+1)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), (((blk_w+(2 * (8u))-1)/(2 * (8u))))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), ((se_h-1))-1u);
   __vcop_pblock_init32(pblock, __offset+_PREG(6), (uchar *)scratch_ptr);
   __vcop_pblock_init16(pblock, __offset+_PREG(8), 16);
   __vcop_pblock_init16(pblock, __offset+_PREG(9), ((line_ofst*sizeof(*output_ptr))) -((2*8u*sizeof(*output_ptr)))*((((blk_w+(2 * (8u))-1)/(2 * (8u))))-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(10), ((line_ofst*sizeof(*data_ptr))) -((2*8u*sizeof(*data_ptr)))*((((blk_w+(2 * (8u))-1)/(2 * (8u))))-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(11), ((line_ofst*sizeof(*data_ptr))));
   __vcop_pblock_init16(pblock, __offset+_PREG(12), ((2*8u*sizeof(*data_ptr))) -((line_ofst*sizeof(*data_ptr)))*(((se_h-1))-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(13), ((line_ofst*sizeof(*data_ptr))) -((2*8u*sizeof(*data_ptr)))*((((blk_w+(2 * (8u))-1)/(2 * (8u))))-1u) -((line_ofst*sizeof(*data_ptr)))*(((se_h-1))-1u));
   __vcop_pblock_init32(pblock, __offset+_PREG(14), (uchar *)data_ptr);
   __vcop_pblock_init32(pblock, __offset+_PREG(16), (uchar *)data_ptr+line_ofst*sizeof(*data_ptr));
   __offset += 16;

   /* Loop 2 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), (blk_h-se_h+1)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), (((blk_w-se_w+(2 * (8u)))/(2 * (8u))))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), ((se_w-1))-1u);
   __vcop_pblock_init32(pblock, __offset+_PREG(6), (uchar *)output_ptr);
   __vcop_pblock_init16(pblock, __offset+_PREG(8), 16);
   __vcop_pblock_init16(pblock, __offset+_PREG(9), ((line_ofst*sizeof(*output_ptr))) -((2*8u*sizeof(*output_ptr)))*((((blk_w-se_w+(2 * (8u)))/(2 * (8u))))-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(10), ((line_ofst*sizeof(*data_ptr))) -((2*8u*sizeof(*data_ptr)))*((((blk_w-se_w+(2 * (8u)))/(2 * (8u))))-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(11), ((2*8u*sizeof(*data_ptr))) -(sizeof(*data_ptr))*(((se_w-1))-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(12), ((line_ofst*sizeof(*data_ptr))) -((2*8u*sizeof(*data_ptr)))*((((blk_w-se_w+(2 * (8u)))/(2 * (8u))))-1u) -(sizeof(*data_ptr))*(((se_w-1))-1u));
   __vcop_pblock_init32(pblock, __offset+_PREG(14), (uchar *)scratch_ptr);
   __vcop_pblock_init32(pblock, __offset+_PREG(16), (uchar *)scratch_ptr+sizeof(*data_ptr));
   __offset += 16;

   return 32u;
}

void vcop_grayscale_erode_rect_vloops(
   unsigned short pblock[])
{
   /* Kernel-wide Vector Registers */
   #pragma VCC_VREG("Vin1", 16);
   #pragma VCC_VREG("Vin2", 17);
   #pragma VCC_VREG("Vmin1", 18);
   #pragma VCC_VREG("Vmin2", 19);

   __vcop_param(&pblock[0]);

   /* VLOOP 1 Start */

   /* VLOOP Local Vector Registers */
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("A1", "A0");
   #pragma EVE_REG("A2", "A1");
   #pragma EVE_REG("A0", "A2");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I1", "I2");
   #pragma EVE_REG("I2", "I3");
   #pragma EVE_REG("I3", "I4");
   

   __vcop_vloop(__vcop_compute(), 9u, 8u, 1u);
   __vcop_vagen(_AGEN(0), _PREG(0), _PREG(8), _PREG(9), _PREG(0));
   __vcop_vagen(_AGEN(1), _PREG(0), _PREG(8), _PREG(10), _PREG(0));
   __vcop_vagen(_AGEN(2), _PREG(11), _PREG(12), _PREG(13), _PREG(0));
   __vcop_vload(__vcop_sizeBU(), __vcop_dintrlv(), _PREG(14), _AGEN(1), _VPAIR(18,19), __vcop_i4_zero());
   __vcop_vload(__vcop_sizeBU(), __vcop_dintrlv(), _PREG(16), _AGEN(2), _VPAIR(16,17), __vcop_alws());
   __vcop_vmin(_VREG(16), _VREG(18), _VREG(18));
   __vcop_vmin(_VREG(17), _VREG(19), _VREG(19));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeBU(), __vcop_intrlv(), __vcop_last_i4(), _VPAIR(18,19), _PREG(6), _AGEN(0), _PREG(0));
   __vcop_vloop_end(1u);

   /* VLOOP 2 Start */

   /* VLOOP Local Vector Registers */
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("A1", "A0");
   #pragma EVE_REG("A2", "A1");
   #pragma EVE_REG("A0", "A2");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I1", "I2");
   #pragma EVE_REG("I2", "I3");
   #pragma EVE_REG("I3", "I4");
   

   __vcop_vloop(__vcop_compute(), 9u, 8u, 2u);
   __vcop_vagen(_AGEN(0), _PREG(0), _PREG(8), _PREG(9), _PREG(0));
   __vcop_vagen(_AGEN(1), _PREG(0), _PREG(8), _PREG(10), _PREG(0));
   __vcop_vagen(_AGEN(2), _PREG(1), _PREG(11), _PREG(12), _PREG(0));
   __vcop_vload(__vcop_sizeBU(), __vcop_dintrlv(), _PREG(14), _AGEN(1), _VPAIR(18,19), __vcop_i4_zero());
   __vcop_vload(__vcop_sizeBU(), __vcop_dintrlv(), _PREG(16), _AGEN(2), _VPAIR(16,17), __vcop_alws());
   __vcop_vmin(_VREG(16), _VREG(18), _VREG(18));
   __vcop_vmin(_VREG(17), _VREG(19), _VREG(19));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeBU(), __vcop_intrlv(), __vcop_last_i4(), _VPAIR(18,19), _PREG(6), _AGEN(0), _PREG(0));
   __vcop_vloop_end(2u);

}

void vcop_grayscale_erode_rect(
   unsigned short blk_w,
   unsigned short line_ofst,
   unsigned short blk_h,
   __vptr_uint8 data_ptr,
   unsigned short se_w,
   unsigned short se_h,
   __vptr_uint8 scratch_ptr,
   __vptr_uint8 output_ptr)
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_grayscale_erode_rect_init(blk_w, line_ofst, blk_h, data_ptr, se_w, se_h, scratch_ptr, output_ptr, __pblock_vcop_grayscale_erode_rect);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_grayscale_erode_rect_vloops(__pblock_vcop_grayscale_erode_rect);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

void vcop_grayscale_erode_rect_custom(
   unsigned short blk_w,
   unsigned short line_ofst,
   unsigned short blk_h,
   __vptr_uint8 data_ptr,
   unsigned short se_w,
   unsigned short se_h,
   __vptr_uint8 scratch_ptr,
   __vptr_uint8 output_ptr,
   unsigned short pblock[])
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_grayscale_erode_rect_init(blk_w, line_ofst, blk_h, data_ptr, se_w, se_h, scratch_ptr, output_ptr, pblock);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_grayscale_erode_rect_vloops(pblock);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

#pragma DATA_SECTION(__pblock_vcop_grayscale_dilate_cross, ".vcop_parameter_block")
#pragma DATA_ALIGN(__pblock_vcop_grayscale_dilate_cross, __ALIGNOF__(int));
unsigned short __pblock_vcop_grayscale_dilate_cross[32];

unsigned int vcop_grayscale_dilate_cross_param_count(void)
{
   return 32u;
}

unsigned int vcop_grayscale_dilate_cross_ctrl_count(void)
{
   return 0u;
}

unsigned int vcop_grayscale_dilate_cross_init(
   unsigned short blk_w,
   unsigned short line_ofst,
   unsigned short blk_h,
   __vptr_uint8 data_ptr,
   unsigned short se_w,
   unsigned short se_h,
   unsigned short cross_se_row,
   unsigned short cross_se_col,
   __vptr_uint8 scratch_ptr,
   __vptr_uint8 output_ptr,
   unsigned short pblock[])
{
   int __offset = 0;
   /* Loop 1 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), (blk_h-se_h+1)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), (((blk_w-se_w+(2 * (8u)))/(2 * (8u))))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), ((se_w-1))-1u);
   __vcop_pblock_init32(pblock, __offset+_PREG(6), (uchar *)scratch_ptr);
   __vcop_pblock_init16(pblock, __offset+_PREG(8), 16);
   __vcop_pblock_init16(pblock, __offset+_PREG(9), ((line_ofst*sizeof(*data_ptr))) -((2*8u*sizeof(*data_ptr)))*((((blk_w-se_w+(2 * (8u)))/(2 * (8u))))-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(10), ((line_ofst*sizeof(*output_ptr))) -((2*8u*sizeof(*output_ptr)))*((((blk_w-se_w+(2 * (8u)))/(2 * (8u))))-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(11), ((2*8u*sizeof(*data_ptr))) -(sizeof(*data_ptr))*(((se_w-1))-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(12), ((line_ofst*sizeof(*data_ptr))) -((2*8u*sizeof(*data_ptr)))*((((blk_w-se_w+(2 * (8u)))/(2 * (8u))))-1u) -(sizeof(*data_ptr))*(((se_w-1))-1u));
   __vcop_pblock_init32(pblock, __offset+_PREG(14), (uchar *)data_ptr+cross_se_row*(line_ofst*sizeof(*data_ptr)));
   __vcop_pblock_init32(pblock, __offset+_PREG(16), (uchar *)data_ptr+cross_se_row*(line_ofst*sizeof(*data_ptr))+sizeof(*data_ptr));
   __offset += 16;

   /* Loop 2 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), (blk_h-se_h+1)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), (((blk_w-se_w+(2 * (8u)))/(2 * (8u))))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), (se_h)-1u);
   __vcop_pblock_init32(pblock, __offset+_PREG(6), (uchar *)output_ptr);
   __vcop_pblock_init16(pblock, __offset+_PREG(8), 16);
   __vcop_pblock_init16(pblock, __offset+_PREG(9), ((line_ofst*sizeof(*output_ptr))) -((2*8u*sizeof(*output_ptr)))*((((blk_w-se_w+(2 * (8u)))/(2 * (8u))))-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(10), ((line_ofst*sizeof(*data_ptr))));
   __vcop_pblock_init16(pblock, __offset+_PREG(11), ((2*8u*sizeof(*data_ptr))) -((line_ofst*sizeof(*data_ptr)))*((se_h)-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(12), ((line_ofst*sizeof(*data_ptr))) -((2*8u*sizeof(*data_ptr)))*((((blk_w-se_w+(2 * (8u)))/(2 * (8u))))-1u) -((line_ofst*sizeof(*data_ptr)))*((se_h)-1u));
   __vcop_pblock_init32(pblock, __offset+_PREG(14), (uchar *)scratch_ptr);
   __vcop_pblock_init32(pblock, __offset+_PREG(16), (uchar *)data_ptr+cross_se_col*sizeof(*data_ptr));
   __offset += 16;

   return 32u;
}

void vcop_grayscale_dilate_cross_vloops(
   unsigned short pblock[])
{
   /* Kernel-wide Vector Registers */
   #pragma VCC_VREG("Vin1", 16);
   #pragma VCC_VREG("Vin2", 17);
   #pragma VCC_VREG("Vmax1", 18);
   #pragma VCC_VREG("Vmax2", 19);

   __vcop_param(&pblock[0]);

   /* VLOOP 1 Start */

   /* VLOOP Local Vector Registers */
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("A1", "A0");
   #pragma EVE_REG("A2", "A1");
   #pragma EVE_REG("A0", "A2");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I1", "I2");
   #pragma EVE_REG("I2", "I3");
   #pragma EVE_REG("I3", "I4");
   

   __vcop_vloop(__vcop_compute(), 9u, 8u, 1u);
   __vcop_vagen(_AGEN(0), _PREG(0), _PREG(8), _PREG(9), _PREG(0));
   __vcop_vagen(_AGEN(1), _PREG(0), _PREG(8), _PREG(10), _PREG(0));
   __vcop_vagen(_AGEN(2), _PREG(1), _PREG(11), _PREG(12), _PREG(0));
   __vcop_vload(__vcop_sizeBU(), __vcop_dintrlv(), _PREG(14), _AGEN(0), _VPAIR(18,19), __vcop_i4_zero());
   __vcop_vload(__vcop_sizeBU(), __vcop_dintrlv(), _PREG(16), _AGEN(2), _VPAIR(16,17), __vcop_alws());
   __vcop_vmax(_VREG(16), _VREG(18), _VREG(18));
   __vcop_vmax(_VREG(17), _VREG(19), _VREG(19));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeBU(), __vcop_intrlv(), __vcop_last_i4(), _VPAIR(18,19), _PREG(6), _AGEN(1), _PREG(0));
   __vcop_vloop_end(1u);

   /* VLOOP 2 Start */

   /* VLOOP Local Vector Registers */
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("A1", "A0");
   #pragma EVE_REG("A0", "A1");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I1", "I2");
   #pragma EVE_REG("I2", "I3");
   #pragma EVE_REG("I3", "I4");
   

   __vcop_vloop(__vcop_compute(), 8u, 8u, 2u);
   __vcop_vagen(_AGEN(0), _PREG(0), _PREG(8), _PREG(9), _PREG(0));
   __vcop_vagen(_AGEN(1), _PREG(10), _PREG(11), _PREG(12), _PREG(0));
   __vcop_vload(__vcop_sizeBU(), __vcop_dintrlv(), _PREG(14), _AGEN(0), _VPAIR(18,19), __vcop_i4_zero());
   __vcop_vload(__vcop_sizeBU(), __vcop_dintrlv(), _PREG(16), _AGEN(1), _VPAIR(16,17), __vcop_alws());
   __vcop_vmax(_VREG(16), _VREG(18), _VREG(18));
   __vcop_vmax(_VREG(17), _VREG(19), _VREG(19));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeBU(), __vcop_intrlv(), __vcop_last_i4(), _VPAIR(18,19), _PREG(6), _AGEN(0), _PREG(0));
   __vcop_vloop_end(2u);

}

void vcop_grayscale_dilate_cross(
   unsigned short blk_w,
   unsigned short line_ofst,
   unsigned short blk_h,
   __vptr_uint8 data_ptr,
   unsigned short se_w,
   unsigned short se_h,
   unsigned short cross_se_row,
   unsigned short cross_se_col,
   __vptr_uint8 scratch_ptr,
   __vptr_uint8 output_ptr)
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_grayscale_dilate_cross_init(blk_w, line_ofst, blk_h, data_ptr, se_w, se_h, cross_se_row, cross_se_col, scratch_ptr, output_ptr, __pblock_vcop_grayscale_dilate_cross);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_grayscale_dilate_cross_vloops(__pblock_vcop_grayscale_dilate_cross);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

void vcop_grayscale_dilate_cross_custom(
   unsigned short blk_w,
   unsigned short line_ofst,
   unsigned short blk_h,
   __vptr_uint8 data_ptr,
   unsigned short se_w,
   unsigned short se_h,
   unsigned short cross_se_row,
   unsigned short cross_se_col,
   __vptr_uint8 scratch_ptr,
   __vptr_uint8 output_ptr,
   unsigned short pblock[])
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_grayscale_dilate_cross_init(blk_w, line_ofst, blk_h, data_ptr, se_w, se_h, cross_se_row, cross_se_col, scratch_ptr, output_ptr, pblock);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_grayscale_dilate_cross_vloops(pblock);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

#pragma DATA_SECTION(__pblock_vcop_grayscale_erode_cross, ".vcop_parameter_block")
#pragma DATA_ALIGN(__pblock_vcop_grayscale_erode_cross, __ALIGNOF__(int));
unsigned short __pblock_vcop_grayscale_erode_cross[32];

unsigned int vcop_grayscale_erode_cross_param_count(void)
{
   return 32u;
}

unsigned int vcop_grayscale_erode_cross_ctrl_count(void)
{
   return 0u;
}

unsigned int vcop_grayscale_erode_cross_init(
   unsigned short blk_w,
   unsigned short line_ofst,
   unsigned short blk_h,
   __vptr_uint8 data_ptr,
   unsigned short se_w,
   unsigned short se_h,
   unsigned short cross_se_row,
   unsigned short cross_se_col,
   __vptr_uint8 scratch_ptr,
   __vptr_uint8 output_ptr,
   unsigned short pblock[])
{
   int __offset = 0;
   /* Loop 1 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), (blk_h-se_h+1)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), (((blk_w-se_w+(2 * (8u)))/(2 * (8u))))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), ((se_w-1))-1u);
   __vcop_pblock_init32(pblock, __offset+_PREG(6), (uchar *)scratch_ptr);
   __vcop_pblock_init16(pblock, __offset+_PREG(8), 16);
   __vcop_pblock_init16(pblock, __offset+_PREG(9), ((line_ofst*sizeof(*data_ptr))) -((2*8u*sizeof(*data_ptr)))*((((blk_w-se_w+(2 * (8u)))/(2 * (8u))))-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(10), ((line_ofst*sizeof(*output_ptr))) -((2*8u*sizeof(*output_ptr)))*((((blk_w-se_w+(2 * (8u)))/(2 * (8u))))-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(11), ((2*8u*sizeof(*data_ptr))) -(sizeof(*data_ptr))*(((se_w-1))-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(12), ((line_ofst*sizeof(*data_ptr))) -((2*8u*sizeof(*data_ptr)))*((((blk_w-se_w+(2 * (8u)))/(2 * (8u))))-1u) -(sizeof(*data_ptr))*(((se_w-1))-1u));
   __vcop_pblock_init32(pblock, __offset+_PREG(14), (uchar *)data_ptr+cross_se_row*(line_ofst*sizeof(*data_ptr)));
   __vcop_pblock_init32(pblock, __offset+_PREG(16), (uchar *)data_ptr+cross_se_row*(line_ofst*sizeof(*data_ptr))+sizeof(*data_ptr));
   __offset += 16;

   /* Loop 2 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), (blk_h-se_h+1)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), (((blk_w-se_w+(2 * (8u)))/(2 * (8u))))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), (se_h)-1u);
   __vcop_pblock_init32(pblock, __offset+_PREG(6), (uchar *)output_ptr);
   __vcop_pblock_init16(pblock, __offset+_PREG(8), 16);
   __vcop_pblock_init16(pblock, __offset+_PREG(9), ((line_ofst*sizeof(*output_ptr))) -((2*8u*sizeof(*output_ptr)))*((((blk_w-se_w+(2 * (8u)))/(2 * (8u))))-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(10), ((line_ofst*sizeof(*data_ptr))));
   __vcop_pblock_init16(pblock, __offset+_PREG(11), ((2*8u*sizeof(*data_ptr))) -((line_ofst*sizeof(*data_ptr)))*((se_h)-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(12), ((line_ofst*sizeof(*data_ptr))) -((2*8u*sizeof(*data_ptr)))*((((blk_w-se_w+(2 * (8u)))/(2 * (8u))))-1u) -((line_ofst*sizeof(*data_ptr)))*((se_h)-1u));
   __vcop_pblock_init32(pblock, __offset+_PREG(14), (uchar *)scratch_ptr);
   __vcop_pblock_init32(pblock, __offset+_PREG(16), (uchar *)data_ptr+cross_se_col*sizeof(*data_ptr));
   __offset += 16;

   return 32u;
}

void vcop_grayscale_erode_cross_vloops(
   unsigned short pblock[])
{
   /* Kernel-wide Vector Registers */
   #pragma VCC_VREG("Vin1", 16);
   #pragma VCC_VREG("Vin2", 17);
   #pragma VCC_VREG("Vmin1", 18);
   #pragma VCC_VREG("Vmin2", 19);

   __vcop_param(&pblock[0]);

   /* VLOOP 1 Start */

   /* VLOOP Local Vector Registers */
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("A1", "A0");
   #pragma EVE_REG("A2", "A1");
   #pragma EVE_REG("A0", "A2");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I1", "I2");
   #pragma EVE_REG("I2", "I3");
   #pragma EVE_REG("I3", "I4");
   

   __vcop_vloop(__vcop_compute(), 9u, 8u, 1u);
   __vcop_vagen(_AGEN(0), _PREG(0), _PREG(8), _PREG(9), _PREG(0));
   __vcop_vagen(_AGEN(1), _PREG(0), _PREG(8), _PREG(10), _PREG(0));
   __vcop_vagen(_AGEN(2), _PREG(1), _PREG(11), _PREG(12), _PREG(0));
   __vcop_vload(__vcop_sizeBU(), __vcop_dintrlv(), _PREG(14), _AGEN(0), _VPAIR(18,19), __vcop_i4_zero());
   __vcop_vload(__vcop_sizeBU(), __vcop_dintrlv(), _PREG(16), _AGEN(2), _VPAIR(16,17), __vcop_alws());
   __vcop_vmin(_VREG(16), _VREG(18), _VREG(18));
   __vcop_vmin(_VREG(17), _VREG(19), _VREG(19));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeBU(), __vcop_intrlv(), __vcop_last_i4(), _VPAIR(18,19), _PREG(6), _AGEN(1), _PREG(0));
   __vcop_vloop_end(1u);

   /* VLOOP 2 Start */

   /* VLOOP Local Vector Registers */
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("A1", "A0");
   #pragma EVE_REG("A0", "A1");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I1", "I2");
   #pragma EVE_REG("I2", "I3");
   #pragma EVE_REG("I3", "I4");
   

   __vcop_vloop(__vcop_compute(), 8u, 8u, 2u);
   __vcop_vagen(_AGEN(0), _PREG(0), _PREG(8), _PREG(9), _PREG(0));
   __vcop_vagen(_AGEN(1), _PREG(10), _PREG(11), _PREG(12), _PREG(0));
   __vcop_vload(__vcop_sizeBU(), __vcop_dintrlv(), _PREG(14), _AGEN(0), _VPAIR(18,19), __vcop_i4_zero());
   __vcop_vload(__vcop_sizeBU(), __vcop_dintrlv(), _PREG(16), _AGEN(1), _VPAIR(16,17), __vcop_alws());
   __vcop_vmin(_VREG(16), _VREG(18), _VREG(18));
   __vcop_vmin(_VREG(17), _VREG(19), _VREG(19));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeBU(), __vcop_intrlv(), __vcop_last_i4(), _VPAIR(18,19), _PREG(6), _AGEN(0), _PREG(0));
   __vcop_vloop_end(2u);

}

void vcop_grayscale_erode_cross(
   unsigned short blk_w,
   unsigned short line_ofst,
   unsigned short blk_h,
   __vptr_uint8 data_ptr,
   unsigned short se_w,
   unsigned short se_h,
   unsigned short cross_se_row,
   unsigned short cross_se_col,
   __vptr_uint8 scratch_ptr,
   __vptr_uint8 output_ptr)
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_grayscale_erode_cross_init(blk_w, line_ofst, blk_h, data_ptr, se_w, se_h, cross_se_row, cross_se_col, scratch_ptr, output_ptr, __pblock_vcop_grayscale_erode_cross);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_grayscale_erode_cross_vloops(__pblock_vcop_grayscale_erode_cross);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

void vcop_grayscale_erode_cross_custom(
   unsigned short blk_w,
   unsigned short line_ofst,
   unsigned short blk_h,
   __vptr_uint8 data_ptr,
   unsigned short se_w,
   unsigned short se_h,
   unsigned short cross_se_row,
   unsigned short cross_se_col,
   __vptr_uint8 scratch_ptr,
   __vptr_uint8 output_ptr,
   unsigned short pblock[])
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_grayscale_erode_cross_init(blk_w, line_ofst, blk_h, data_ptr, se_w, se_h, cross_se_row, cross_se_col, scratch_ptr, output_ptr, pblock);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_grayscale_erode_cross_vloops(pblock);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

#pragma DATA_SECTION(__pblock_vcop_grayscale_morp_diff, ".vcop_parameter_block")
#pragma DATA_ALIGN(__pblock_vcop_grayscale_morp_diff, __ALIGNOF__(int));
unsigned short __pblock_vcop_grayscale_morp_diff[14];

unsigned int vcop_grayscale_morp_diff_param_count(void)
{
   return 14u;
}

unsigned int vcop_grayscale_morp_diff_ctrl_count(void)
{
   return 0u;
}

unsigned int vcop_grayscale_morp_diff_init(
   unsigned short blk_w,
   unsigned short line_ofst,
   unsigned short blk_h,
   __vptr_uint8 data_ptr,
   __vptr_uint8 data2_ptr,
   __vptr_uint8 output_ptr,
   unsigned short pblock[])
{
   int __offset = 0;
   /* Loop 1 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), (blk_h)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), (((blk_w+(2 * (8u))-1)/(2 * (8u))))-1u);
   __vcop_pblock_init32(pblock, __offset+_PREG(6), (uchar *)output_ptr);
   __vcop_pblock_init16(pblock, __offset+_PREG(8), 16);
   __vcop_pblock_init16(pblock, __offset+_PREG(9), ((line_ofst*sizeof(*data_ptr))) -((2*8u*sizeof(*data_ptr)))*((((blk_w+(2 * (8u))-1)/(2 * (8u))))-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(10), ((line_ofst*sizeof(*output_ptr))) -((2*8u*sizeof(*output_ptr)))*((((blk_w+(2 * (8u))-1)/(2 * (8u))))-1u));
   __vcop_pblock_init32(pblock, __offset+_PREG(12), (uchar *)data_ptr);
   __vcop_pblock_init32(pblock, __offset+_PREG(14), (uchar *)data2_ptr);
   __offset += 14;

   return 14u;
}

void vcop_grayscale_morp_diff_vloops(
   unsigned short pblock[])
{
   /* Kernel-wide Vector Registers */
   #pragma VCC_VREG("Vdiff1", 16);
   #pragma VCC_VREG("Vdiff2", 17);
   #pragma VCC_VREG("Vin1", 18);
   #pragma VCC_VREG("Vin2", 19);
   #pragma VCC_VREG("Vin3", 20);
   #pragma VCC_VREG("Vin4", 21);

   __vcop_param(&pblock[0]);

   /* VLOOP 1 Start */

   /* VLOOP Local Vector Registers */
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("A0", "A0");
   #pragma EVE_REG("A1", "A1");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I1", "I3");
   #pragma EVE_REG("I2", "I4");
   

   __vcop_vloop(__vcop_compute(), 8u, 7u, 1u);
   __vcop_vagen(_AGEN(0), _PREG(8), _PREG(9), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(1), _PREG(8), _PREG(10), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeBU(), __vcop_dintrlv(), _PREG(12), _AGEN(0), _VPAIR(18,19), __vcop_alws());
   __vcop_vload(__vcop_sizeBU(), __vcop_dintrlv(), _PREG(14), _AGEN(0), _VPAIR(20,21), __vcop_alws());
   __vcop_vsub(_VREG(18), _VREG(20), _VREG(16));
   __vcop_vsub(_VREG(19), _VREG(21), _VREG(17));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeBU(), __vcop_intrlv(), __vcop_alws(), _VPAIR(16,17), _PREG(6), _AGEN(1), _PREG(0));
   __vcop_vloop_end(1u);

}

void vcop_grayscale_morp_diff(
   unsigned short blk_w,
   unsigned short line_ofst,
   unsigned short blk_h,
   __vptr_uint8 data_ptr,
   __vptr_uint8 data2_ptr,
   __vptr_uint8 output_ptr)
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_grayscale_morp_diff_init(blk_w, line_ofst, blk_h, data_ptr, data2_ptr, output_ptr, __pblock_vcop_grayscale_morp_diff);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_grayscale_morp_diff_vloops(__pblock_vcop_grayscale_morp_diff);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

void vcop_grayscale_morp_diff_custom(
   unsigned short blk_w,
   unsigned short line_ofst,
   unsigned short blk_h,
   __vptr_uint8 data_ptr,
   __vptr_uint8 data2_ptr,
   __vptr_uint8 output_ptr,
   unsigned short pblock[])
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_grayscale_morp_diff_init(blk_w, line_ofst, blk_h, data_ptr, data2_ptr, output_ptr, pblock);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_grayscale_morp_diff_vloops(pblock);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

