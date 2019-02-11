#include <vcop\vcop.h>

typedef unsigned char uchar;

#pragma DATA_SECTION(__pblock_yuv_scalar_pixels_look_up_kernel, ".vcop_parameter_block")
#pragma DATA_ALIGN(__pblock_yuv_scalar_pixels_look_up_kernel, __ALIGNOF__(int));
unsigned short __pblock_yuv_scalar_pixels_look_up_kernel[14];

unsigned int yuv_scalar_pixels_look_up_kernel_param_count(void)
{
   return 14u;
}

unsigned int yuv_scalar_pixels_look_up_kernel_ctrl_count(void)
{
   return 0u;
}

unsigned int yuv_scalar_pixels_look_up_kernel_init(
   __vptr_uint32 src,
   __vptr_uint16 index,
   __vptr_uint32 outBuf,
   short int numTaps,
   short int src_w,
   short int dst_h,
   unsigned short pblock[])
{
   int __offset = 0;
   /* Loop 1 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), (numTaps*dst_h)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), ((src_w+((32)-1))/(32))-1u);
   __vcop_pblock_init32(pblock, __offset+_PREG(6), (uchar *)outBuf);
   __vcop_pblock_init16(pblock, __offset+_PREG(8), 2);
   __vcop_pblock_init16(pblock, __offset+_PREG(9), 32);
   __vcop_pblock_init16(pblock, __offset+_PREG(10), (src_w) -(32)*(((src_w+((32)-1))/(32))-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(11), (0) -(32)*(((src_w+((32)-1))/(32))-1u));
   __vcop_pblock_init32(pblock, __offset+_PREG(12), (uchar *)index);
   __vcop_pblock_init32(pblock, __offset+_PREG(14), (uchar *)src);
   __offset += 14;

   return 14u;
}

void yuv_scalar_pixels_look_up_kernel_vloops(
   unsigned short pblock[])
{
   /* Kernel-wide Vector Registers */

   __vcop_param(&pblock[0]);

   /* VLOOP 1 Start */

   /* VLOOP Local Vector Registers */
   #pragma VCC_VREG("Vdata", 16);
   #pragma VCC_VREG("Vindex", 17);
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("Addr_index", "A0");
   #pragma EVE_REG("Addr_out", "A2");
   #pragma EVE_REG("Addr_table", "A1");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("i", "I3");
   #pragma EVE_REG("j", "I4");
   

   __vcop_vloop(__vcop_tablelkup(), 7u, 7u, 1u);
   __vcop_vagen(_AGEN(0), _PREG(0), _PREG(8), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(2), _PREG(9), _PREG(10), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(1), _PREG(9), _PREG(11), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeHU(), __vcop_1pt(), _PREG(12), _AGEN(0), _VREG(17), __vcop_alws());
   __vcop_vtbload(__vcop_sizeWU(), __vcop_tableinfo(1, 8), _PREG(14), _AGEN(1), _VREG(17), _VREG(16), _PREG(0), __vcop_alws());
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeWU(), __vcop_npt(), __vcop_alws(), _VREG(16), _PREG(6), _AGEN(2), _PREG(0));
   __vcop_vloop_end(1u);

}

void yuv_scalar_pixels_look_up_kernel(
   __vptr_uint32 src,
   __vptr_uint16 index,
   __vptr_uint32 outBuf,
   short int numTaps,
   short int src_w,
   short int dst_h)
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   yuv_scalar_pixels_look_up_kernel_init(src, index, outBuf, numTaps, src_w, dst_h, __pblock_yuv_scalar_pixels_look_up_kernel);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   yuv_scalar_pixels_look_up_kernel_vloops(__pblock_yuv_scalar_pixels_look_up_kernel);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

void yuv_scalar_pixels_look_up_kernel_custom(
   __vptr_uint32 src,
   __vptr_uint16 index,
   __vptr_uint32 outBuf,
   short int numTaps,
   short int src_w,
   short int dst_h,
   unsigned short pblock[])
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   yuv_scalar_pixels_look_up_kernel_init(src, index, outBuf, numTaps, src_w, dst_h, pblock);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   yuv_scalar_pixels_look_up_kernel_vloops(pblock);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

#pragma DATA_SECTION(__pblock_yuv_scalar_interpolation_kernel, ".vcop_parameter_block")
#pragma DATA_ALIGN(__pblock_yuv_scalar_interpolation_kernel, __ALIGNOF__(int));
unsigned short __pblock_yuv_scalar_interpolation_kernel[26];

unsigned int yuv_scalar_interpolation_kernel_param_count(void)
{
   return 26u;
}

unsigned int yuv_scalar_interpolation_kernel_ctrl_count(void)
{
   return 0u;
}

unsigned int yuv_scalar_interpolation_kernel_init(
   __vptr_uint8 inPtr,
   __vptr_uint8 fracPtr,
   __vptr_uint8 temp1Ptr,
   __vptr_uint8 temp2Ptr,
   __vptr_uint16 offsetPtr,
   short int tempBufPitch,
   short int fracBits,
   short int numTaps,
   short int src_w,
   short int src_pitch,
   short int dst_h,
   unsigned short pblock[])
{
   int __offset = 0;
   /* Loop 1 PREGS */
   const int preg_ref1 = _PREG(7);

   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), (dst_h)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), (((src_w + (((8u) * 2)-1))/((8u) * 2)))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), (numTaps)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(6), __vcop_store_round_sat(SM_SYMM,preg_ref1,RM_ROUND,fracBits));
   __vcop_pblock_init16(pblock, __offset+_PREG(7), 255);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)inPtr);
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)fracPtr);
   __vcop_pblock_init32(pblock, __offset+_PREG(12), (uchar *)temp1Ptr);
   __vcop_pblock_init32(pblock, __offset+_PREG(14), (uchar *)temp2Ptr);
   __vcop_pblock_init16(pblock, __offset+_PREG(16), (tempBufPitch*8u*sizeof(*inPtr)));
   __vcop_pblock_init16(pblock, __offset+_PREG(17), (sizeof(*inPtr)) -(tempBufPitch*8u*sizeof(*inPtr))*((((src_w + (((8u) * 2)-1))/((8u) * 2)))-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(18), (sizeof(*fracPtr)*dst_h));
   __vcop_pblock_init16(pblock, __offset+_PREG(19),  -(sizeof(*fracPtr)*dst_h)*((numTaps)-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(20), (sizeof(*fracPtr)) -(sizeof(*fracPtr)*dst_h)*((numTaps)-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(21), (sizeof(*inPtr)*src_pitch*dst_h));
   __vcop_pblock_init16(pblock, __offset+_PREG(22), (sizeof(*inPtr)*(8u*2)) -(sizeof(*inPtr)*src_pitch*dst_h)*((numTaps)-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(23), (sizeof(*inPtr)*src_pitch) -(sizeof(*inPtr)*(8u*2))*((((src_w + (((8u) * 2)-1))/((8u) * 2)))-1u) -(sizeof(*inPtr)*src_pitch*dst_h)*((numTaps)-1u));
   __vcop_pblock_init32(pblock, __offset+_PREG(24), (uchar *)offsetPtr);
   __vcop_pblock_init32(pblock, __offset+_PREG(26), 0);
   __offset += 26;

   return 26u;
}

void yuv_scalar_interpolation_kernel_vloops(
   unsigned short pblock[])
{
   /* Kernel-wide Vector Registers */
   #pragma VCC_VREG("Vin1", 16);
   #pragma VCC_VREG("Vin2", 17);
   #pragma VCC_VREG("Vin3", 18);
   #pragma VCC_VREG("Vin4", 19);
   #pragma VCC_VREG("Vinf", 20);
   #pragma VCC_VREG("Voffset", 21);
   #pragma VCC_VREG("Vsum1", 22);
   #pragma VCC_VREG("Vsum2", 23);

   __vcop_param(&pblock[0]);

   /* VLOOP 1 Start */

   /* VLOOP Local Vector Registers */
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("Addr_dstOut", "A0");
   #pragma EVE_REG("Addr_f", "A1");
   #pragma EVE_REG("Addr_offset", "A2");
   #pragma EVE_REG("Addr_p", "A3");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I1", "I2");
   #pragma EVE_REG("I2", "I3");
   #pragma EVE_REG("I3", "I4");
   

   __vcop_vloop(__vcop_compute(), 14u, 13u, 1u);
   __vcop_vinit(__vcop_sizeW(), __vcop_i4_zero(), _PREG(26), _VREG(22));
   __vcop_vinit(__vcop_sizeW(), __vcop_i4_zero(), _PREG(26), _VREG(23));
   __vcop_vagen(_AGEN(0), _PREG(0), _PREG(16), _PREG(17), _PREG(0));
   __vcop_vagen(_AGEN(1), _PREG(18), _PREG(19), _PREG(20), _PREG(0));
   __vcop_vagen(_AGEN(2), _PREG(0), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(3), _PREG(21), _PREG(22), _PREG(23), _PREG(0));
   __vcop_vload(__vcop_sizeHU(), __vcop_npt(), _PREG(24), _AGEN(2), _VREG(21), __vcop_once());
   __vcop_vload(__vcop_sizeBU(), __vcop_dintrlv(), _PREG(8), _AGEN(3), _VPAIR(16,17), __vcop_alws());
   __vcop_vload(__vcop_sizeBU(), __vcop_1pt(), _PREG(10), _AGEN(1), _VREG(20), __vcop_alws());
   __vcop_vmadd(_VREG(20), _VREG(16), _VREG(22), _PREG(0));
   __vcop_vmadd(_VREG(20), _VREG(17), _VREG(23), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeBU(), __vcop_pdda(_VREG(21)), __vcop_last_i4(), _VREG(22), _PREG(12), _AGEN(0), _PREG(6));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeBU(), __vcop_pdda(_VREG(21)), __vcop_last_i4(), _VREG(23), _PREG(14), _AGEN(0), _PREG(6));
   __vcop_vloop_end(1u);

}

void yuv_scalar_interpolation_kernel(
   __vptr_uint8 inPtr,
   __vptr_uint8 fracPtr,
   __vptr_uint8 temp1Ptr,
   __vptr_uint8 temp2Ptr,
   __vptr_uint16 offsetPtr,
   short int tempBufPitch,
   short int fracBits,
   short int numTaps,
   short int src_w,
   short int src_pitch,
   short int dst_h)
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   yuv_scalar_interpolation_kernel_init(inPtr, fracPtr, temp1Ptr, temp2Ptr, offsetPtr, tempBufPitch, fracBits, numTaps, src_w, src_pitch, dst_h, __pblock_yuv_scalar_interpolation_kernel);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   yuv_scalar_interpolation_kernel_vloops(__pblock_yuv_scalar_interpolation_kernel);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

void yuv_scalar_interpolation_kernel_custom(
   __vptr_uint8 inPtr,
   __vptr_uint8 fracPtr,
   __vptr_uint8 temp1Ptr,
   __vptr_uint8 temp2Ptr,
   __vptr_uint16 offsetPtr,
   short int tempBufPitch,
   short int fracBits,
   short int numTaps,
   short int src_w,
   short int src_pitch,
   short int dst_h,
   unsigned short pblock[])
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   yuv_scalar_interpolation_kernel_init(inPtr, fracPtr, temp1Ptr, temp2Ptr, offsetPtr, tempBufPitch, fracBits, numTaps, src_w, src_pitch, dst_h, pblock);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   yuv_scalar_interpolation_kernel_vloops(pblock);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

#pragma DATA_SECTION(__pblock_yuv_scalar_luma_copy_kernel, ".vcop_parameter_block")
#pragma DATA_ALIGN(__pblock_yuv_scalar_luma_copy_kernel, __ALIGNOF__(int));
unsigned short __pblock_yuv_scalar_luma_copy_kernel[16];

unsigned int yuv_scalar_luma_copy_kernel_param_count(void)
{
   return 16u;
}

unsigned int yuv_scalar_luma_copy_kernel_ctrl_count(void)
{
   return 0u;
}

unsigned int yuv_scalar_luma_copy_kernel_init(
   __vptr_uint32 outPtr,
   __vptr_uint32 temp1Ptr,
   __vptr_uint32 temp2Ptr,
   short int tempBufPitch,
   short int src_w,
   short int dst_h,
   unsigned short pblock[])
{
   int __offset = 0;
   /* Loop 1 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), ((src_w+1)/2)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), (((dst_h + (32-1))/32))-1u);
   __vcop_pblock_init32(pblock, __offset+_PREG(6), (uchar *)outPtr);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)outPtr+dst_h);
   __vcop_pblock_init16(pblock, __offset+_PREG(10), 32);
   __vcop_pblock_init16(pblock, __offset+_PREG(11), (tempBufPitch) -(32)*((((dst_h + (32-1))/32))-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(12), (dst_h*2) -(32)*((((dst_h + (32-1))/32))-1u));
   __vcop_pblock_init32(pblock, __offset+_PREG(14), (uchar *)temp1Ptr);
   __vcop_pblock_init32(pblock, __offset+_PREG(16), (uchar *)temp2Ptr);
   __offset += 16;

   return 16u;
}

void yuv_scalar_luma_copy_kernel_vloops(
   unsigned short pblock[])
{
   /* Kernel-wide Vector Registers */
   #pragma VCC_VREG("Vin1", 16);
   #pragma VCC_VREG("Vin2", 17);

   __vcop_param(&pblock[0]);

   /* VLOOP 1 Start */

   /* VLOOP Local Vector Registers */
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("Addr1", "A0");
   #pragma EVE_REG("Addr2", "A1");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I1", "I3");
   #pragma EVE_REG("I2", "I4");
   

   __vcop_vloop(__vcop_compute(), 7u, 8u, 1u);
   __vcop_vagen(_AGEN(0), _PREG(10), _PREG(11), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(1), _PREG(10), _PREG(12), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeWU(), __vcop_npt(), _PREG(14), _AGEN(0), _VREG(16), __vcop_alws());
   __vcop_vload(__vcop_sizeWU(), __vcop_npt(), _PREG(16), _AGEN(0), _VREG(17), __vcop_alws());
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeWU(), __vcop_npt(), __vcop_alws(), _VREG(16), _PREG(6), _AGEN(1), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeWU(), __vcop_npt(), __vcop_alws(), _VREG(17), _PREG(8), _AGEN(1), _PREG(0));
   __vcop_vloop_end(1u);

}

void yuv_scalar_luma_copy_kernel(
   __vptr_uint32 outPtr,
   __vptr_uint32 temp1Ptr,
   __vptr_uint32 temp2Ptr,
   short int tempBufPitch,
   short int src_w,
   short int dst_h)
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   yuv_scalar_luma_copy_kernel_init(outPtr, temp1Ptr, temp2Ptr, tempBufPitch, src_w, dst_h, __pblock_yuv_scalar_luma_copy_kernel);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   yuv_scalar_luma_copy_kernel_vloops(__pblock_yuv_scalar_luma_copy_kernel);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

void yuv_scalar_luma_copy_kernel_custom(
   __vptr_uint32 outPtr,
   __vptr_uint32 temp1Ptr,
   __vptr_uint32 temp2Ptr,
   short int tempBufPitch,
   short int src_w,
   short int dst_h,
   unsigned short pblock[])
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   yuv_scalar_luma_copy_kernel_init(outPtr, temp1Ptr, temp2Ptr, tempBufPitch, src_w, dst_h, pblock);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   yuv_scalar_luma_copy_kernel_vloops(pblock);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

#pragma DATA_SECTION(__pblock_yuv_scalar_chroma_copy_kernel, ".vcop_parameter_block")
#pragma DATA_ALIGN(__pblock_yuv_scalar_chroma_copy_kernel, __ALIGNOF__(int));
unsigned short __pblock_yuv_scalar_chroma_copy_kernel[16];

unsigned int yuv_scalar_chroma_copy_kernel_param_count(void)
{
   return 16u;
}

unsigned int yuv_scalar_chroma_copy_kernel_ctrl_count(void)
{
   return 0u;
}

unsigned int yuv_scalar_chroma_copy_kernel_init(
   __vptr_uint8 outPtr,
   __vptr_uint8 temp1Ptr,
   __vptr_uint8 temp2Ptr,
   short int tempBufPitch,
   short int src_w,
   short int dst_h,
   unsigned short pblock[])
{
   int __offset = 0;
   /* Loop 1 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), ((src_w+1)/2)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), ((dst_h + ((8u)-1))/(8u))-1u);
   __vcop_pblock_init32(pblock, __offset+_PREG(6), (uchar *)temp2Ptr);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)outPtr);
   __vcop_pblock_init16(pblock, __offset+_PREG(10), 8);
   __vcop_pblock_init16(pblock, __offset+_PREG(11), (tempBufPitch) -(8u)*(((dst_h + ((8u)-1))/(8u))-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(12), 16);
   __vcop_pblock_init16(pblock, __offset+_PREG(13), (dst_h*2) -(8u*2)*(((dst_h + ((8u)-1))/(8u))-1u));
   __vcop_pblock_init32(pblock, __offset+_PREG(14), 0);
   __vcop_pblock_init32(pblock, __offset+_PREG(16), (uchar *)temp1Ptr);
   __offset += 16;

   return 16u;
}

void yuv_scalar_chroma_copy_kernel_vloops(
   unsigned short pblock[])
{
   /* Kernel-wide Vector Registers */
   #pragma VCC_VREG("Vin1", 16);
   #pragma VCC_VREG("Vin2", 17);
   #pragma VCC_VREG("Vin3", 18);
   #pragma VCC_VREG("Vin4", 19);
   #pragma VCC_VREG("Vzero", 20);

   __vcop_param(&pblock[0]);

   /* VLOOP 1 Start */

   /* VLOOP Local Vector Registers */
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("Addr1", "A0");
   #pragma EVE_REG("Addr2", "A1");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I1", "I3");
   #pragma EVE_REG("I2", "I4");
   

   __vcop_vloop(__vcop_compute(), 9u, 8u, 1u);
   __vcop_vinit(__vcop_sizeW(), __vcop_once(), _PREG(14), _VREG(20));
   __vcop_vagen(_AGEN(0), _PREG(10), _PREG(11), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(1), _PREG(12), _PREG(13), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeBU(), __vcop_npt(), _PREG(16), _AGEN(0), _VREG(16), __vcop_alws());
   __vcop_vload(__vcop_sizeBU(), __vcop_npt(), _PREG(6), _AGEN(0), _VREG(17), __vcop_alws());
   __vcop_vadd(_VREG(16), _VREG(20), _VREG(18));
   __vcop_vadd(_VREG(17), _VREG(20), _VREG(19));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeBU(), __vcop_intrlv(), __vcop_alws(), _VPAIR(18,19), _PREG(8), _AGEN(1), _PREG(0));
   __vcop_vloop_end(1u);

}

void yuv_scalar_chroma_copy_kernel(
   __vptr_uint8 outPtr,
   __vptr_uint8 temp1Ptr,
   __vptr_uint8 temp2Ptr,
   short int tempBufPitch,
   short int src_w,
   short int dst_h)
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   yuv_scalar_chroma_copy_kernel_init(outPtr, temp1Ptr, temp2Ptr, tempBufPitch, src_w, dst_h, __pblock_yuv_scalar_chroma_copy_kernel);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   yuv_scalar_chroma_copy_kernel_vloops(__pblock_yuv_scalar_chroma_copy_kernel);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

void yuv_scalar_chroma_copy_kernel_custom(
   __vptr_uint8 outPtr,
   __vptr_uint8 temp1Ptr,
   __vptr_uint8 temp2Ptr,
   short int tempBufPitch,
   short int src_w,
   short int dst_h,
   unsigned short pblock[])
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   yuv_scalar_chroma_copy_kernel_init(outPtr, temp1Ptr, temp2Ptr, tempBufPitch, src_w, dst_h, pblock);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   yuv_scalar_chroma_copy_kernel_vloops(pblock);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

