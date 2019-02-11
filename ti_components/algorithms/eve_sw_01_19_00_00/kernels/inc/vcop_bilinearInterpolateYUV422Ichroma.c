#include <vcop\vcop.h>

typedef unsigned char uchar;

#pragma DATA_SECTION(__pblock_vcop_bilinearInterpolateYUV422Ichroma, ".vcop_parameter_block")
#pragma DATA_ALIGN(__pblock_vcop_bilinearInterpolateYUV422Ichroma, __ALIGNOF__(int));
unsigned short __pblock_vcop_bilinearInterpolateYUV422Ichroma[74];

unsigned int vcop_bilinearInterpolateYUV422Ichroma_param_count(void)
{
   return 74u;
}

unsigned int vcop_bilinearInterpolateYUV422Ichroma_ctrl_count(void)
{
   return 0u;
}

unsigned int vcop_bilinearInterpolateYUV422Ichroma_init(
   __vptr_uint8 src,
   __vptr_uint8 dst,
   unsigned short maxNumMappedPixels,
   unsigned short numMappedPixels,
   __vptr_uint16 tluIndexArray,
   __vptr_uint8 xFracArray,
   __vptr_uint8 yFracArray,
   __vptr_uint16 scatterStoreArray,
   __vptr_uint16 scratchLUT,
   __vptr_uint8 scratchPixel,
   __vptr_uint16 stride_ptr,
   unsigned char mnQShift,
   unsigned char oQShift,
   unsigned short qScale,
   unsigned char rightShift,
   unsigned short src_size,
   long sat_high,
   long sat_high_set,
   long sat_low,
   long sat_low_set,
   unsigned short pblock[])
{
   int __offset = 0;
   /* Loop 1 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), ((((numMappedPixels) + 2U*(8u)-1U) & ~(2U*(8u)-1U))/(2*(8u)))-1u);
   __vcop_pblock_init32(pblock, __offset+_PREG(6), (uchar *)scratchLUT);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)scratchLUT+sizeof(*scratchLUT)*(maxNumMappedPixels+2U*8u-1U&~(2U*8u-1U)));
   __vcop_pblock_init16(pblock, __offset+_PREG(10), 32);
   __vcop_pblock_init32(pblock, __offset+_PREG(12), (uchar *)stride_ptr);
   __vcop_pblock_init32(pblock, __offset+_PREG(14), (uchar *)tluIndexArray);
   __offset += 14;

   /* Loop 2 PREGS */
   const int preg_ref1 = _PREG(8);

   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), (numMappedPixels)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(6), __vcop_store_round_sat(SM_4PARAM,preg_ref1,RM_NONE,0));
   __vcop_pblock_init16(pblock, __offset+_PREG(7), 2);
   __vcop_pblock_4param_init(pblock, __offset+_PREG(8), src_size, src_size, 0, 0);
   __vcop_pblock_init32(pblock, __offset+_PREG(12), (uchar *)scratchPixel);
   __vcop_pblock_init32(pblock, __offset+_PREG(14), (uchar *)scratchLUT);
   __vcop_pblock_init32(pblock, __offset+_PREG(16), (uchar *)src);
   __offset += 16;

   /* Loop 3 PREGS */
   const int preg_ref2 = _PREG(8);

   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), (numMappedPixels)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(6), __vcop_store_round_sat(SM_4PARAM,preg_ref2,RM_NONE,0));
   __vcop_pblock_init16(pblock, __offset+_PREG(7), 2);
   __vcop_pblock_4param_init(pblock, __offset+_PREG(8), src_size, src_size, 0, 0);
   __vcop_pblock_init32(pblock, __offset+_PREG(12), (uchar *)scratchPixel+sizeof(*dst)*2*maxNumMappedPixels);
   __vcop_pblock_init32(pblock, __offset+_PREG(14), (uchar *)scratchLUT+sizeof(*scratchLUT)*(maxNumMappedPixels+2U*8u-1U&~(2U*8u-1U)));
   __vcop_pblock_init32(pblock, __offset+_PREG(16), (uchar *)src);
   __offset += 16;

   /* Loop 4 PREGS */
   const int preg_ref3 = _PREG(20);

   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), ((((numMappedPixels) + (8u)-1U) & ~((8u)-1U))/(8u))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(6), __vcop_store_round_sat(SM_4PARAM,preg_ref3,RM_ROUND,mnQShift+oQShift));
   __vcop_pblock_init16(pblock, __offset+_PREG(7), 8);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)xFracArray);
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)yFracArray);
   __vcop_pblock_init32(pblock, __offset+_PREG(12), (uchar *)scatterStoreArray);
   __vcop_pblock_init32(pblock, __offset+_PREG(14), (uchar *)scratchPixel);
   __vcop_pblock_init32(pblock, __offset+_PREG(16), (uchar *)scratchPixel+sizeof(*dst)*2*maxNumMappedPixels);
   __vcop_pblock_init32(pblock, __offset+_PREG(18), (uchar *)dst);
   __vcop_pblock_4param_init(pblock, __offset+_PREG(20), sat_high,sat_high_set,sat_low,sat_low_set);
   __vcop_pblock_init16(pblock, __offset+_PREG(24), (2*8u*sizeof(*(scratchPixel+sizeof(*dst)*2*maxNumMappedPixels))));
   __vcop_pblock_init16(pblock, __offset+_PREG(25), 16);
   __vcop_pblock_init32(pblock, __offset+_PREG(26), qScale);
   __vcop_pblock_init32(pblock, __offset+_PREG(28), 0x0000000001);
   __offset += 28;

   return 74u;
}

void vcop_bilinearInterpolateYUV422Ichroma_vloops(
   unsigned short pblock[])
{
   /* Kernel-wide Vector Registers */
   #pragma VCC_VREG("Vstride", 16);
   #pragma VCC_VREG("v_qScale", 17);

   __vcop_param(&pblock[0]);

   /* VLOOP 1 Start */

   /* VLOOP Local Vector Registers */
   #pragma VCC_VREG("index00_1", 18);
   #pragma VCC_VREG("index00_2", 19);
   #pragma VCC_VREG("index01_1", 20);
   #pragma VCC_VREG("index01_2", 21);
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("Addr0", "A0");
   #pragma EVE_REG("Addr2", "A1");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I1", "I4");
   

   __vcop_vloop(__vcop_compute(), 9u, 7u, 1u);
   __vcop_vagen(_AGEN(0), _PREG(0), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(1), _PREG(10), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeHU(), __vcop_1pt(), _PREG(12), _AGEN(0), _VREG(16), __vcop_once());
   __vcop_vload(__vcop_sizeHU(), __vcop_dintrlv(), _PREG(14), _AGEN(1), _VPAIR(18,19), __vcop_alws());
   __vcop_vadd(_VREG(18), _VREG(16), _VREG(20));
   __vcop_vadd(_VREG(19), _VREG(16), _VREG(21));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeHU(), __vcop_intrlv(), __vcop_alws(), _VPAIR(18,19), _PREG(6), _AGEN(1), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeHU(), __vcop_intrlv(), __vcop_alws(), _VPAIR(20,21), _PREG(8), _AGEN(1), _PREG(0));
   __vcop_vloop_end(1u);

   /* VLOOP 2 Start */

   /* VLOOP Local Vector Registers */
   #pragma VCC_VREG("Vdata", 22);
   #pragma VCC_VREG("Vindex", 23);
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("TLU_agen", "A1");
   #pragma EVE_REG("ind_agen", "A0");
   #pragma EVE_REG("out_agen", "A2");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I1", "I4");
   

   __vcop_vloop(__vcop_tablelkup(), 7u, 8u, 2u);
   __vcop_vagen(_AGEN(1), _PREG(0), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(0), _PREG(7), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(2), _PREG(7), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeHU(), __vcop_npt(), _PREG(14), _AGEN(0), _VREG(23), __vcop_alws());
   __vcop_vtbload(__vcop_sizeBU(), __vcop_tableinfo(1, 2), _PREG(16), _AGEN(1), _VREG(23), _VREG(22), _PREG(6), __vcop_alws());
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeBU(), __vcop_npt(), __vcop_alws(), _VREG(22), _PREG(12), _AGEN(2), _PREG(0));
   __vcop_vloop_end(2u);

   /* VLOOP 3 Start */

   /* VLOOP Local Vector Registers */
   #pragma VCC_VREG("Vdata", 24);
   #pragma VCC_VREG("Vindex", 25);
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("TLU_agen", "A1");
   #pragma EVE_REG("ind_agen", "A0");
   #pragma EVE_REG("out_agen", "A2");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I1", "I4");
   

   __vcop_vloop(__vcop_tablelkup(), 7u, 8u, 3u);
   __vcop_vagen(_AGEN(1), _PREG(0), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(0), _PREG(7), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(2), _PREG(7), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeHU(), __vcop_npt(), _PREG(14), _AGEN(0), _VREG(25), __vcop_alws());
   __vcop_vtbload(__vcop_sizeBU(), __vcop_tableinfo(1, 2), _PREG(16), _AGEN(1), _VREG(25), _VREG(24), _PREG(6), __vcop_alws());
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeBU(), __vcop_npt(), __vcop_alws(), _VREG(24), _PREG(12), _AGEN(2), _PREG(0));
   __vcop_vloop_end(3u);

   /* VLOOP 4 Start */

   /* VLOOP Local Vector Registers */
   #pragma VCC_VREG("Vone", 26);
   #pragma VCC_VREG("pix00", 27);
   #pragma VCC_VREG("pix01", 28);
   #pragma VCC_VREG("pix10", 29);
   #pragma VCC_VREG("pix11", 30);
   #pragma VCC_VREG("qScale_xFrac", 31);
   #pragma VCC_VREG("qScale_yFrac", 32);
   #pragma VCC_VREG("scatterStore", 33);
   #pragma VCC_VREG("temp1", 34);
   #pragma VCC_VREG("temp2", 35);
   #pragma VCC_VREG("xFrac", 36);
   #pragma VCC_VREG("yFrac", 37);
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("Addr0", "A0");
   #pragma EVE_REG("Addr1", "A1");
   #pragma EVE_REG("Addr2", "A2");
   #pragma EVE_REG("Addr3", "A3");
   #pragma EVE_REG("Addr_out", "A4");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I1", "I4");
   

   __vcop_vloop(__vcop_compute(), 24u, 14u, 4u);
   __vcop_vinit(__vcop_sizeW(), __vcop_once(), _PREG(26), _VREG(17));
   __vcop_vinit(__vcop_sizeW(), __vcop_alws(), _PREG(28), _VREG(26));
   __vcop_vagen(_AGEN(1), _PREG(7), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(2), _PREG(24), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(3), _PREG(25), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(4), _PREG(0), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeBU(), __vcop_npt(), _PREG(8), _AGEN(1), _VREG(36), __vcop_alws());
   __vcop_vload(__vcop_sizeBU(), __vcop_npt(), _PREG(10), _AGEN(1), _VREG(37), __vcop_alws());
   __vcop_vload(__vcop_sizeHU(), __vcop_npt(), _PREG(12), _AGEN(3), _VREG(33), __vcop_alws());
   __vcop_vload(__vcop_sizeBU(), __vcop_dintrlv(), _PREG(14), _AGEN(2), _VPAIR(27,29), __vcop_alws());
   __vcop_vload(__vcop_sizeBU(), __vcop_dintrlv(), _PREG(16), _AGEN(2), _VPAIR(28,30), __vcop_alws());
   __vcop_vmpy(_VREG(36), _VREG(29), _VREG(34), _PREG(0));
   __vcop_vmpy(_VREG(36), _VREG(30), _VREG(35), _PREG(0));
   __vcop_vsub(_VREG(17), _VREG(36), _VREG(31));
   __vcop_vsub(_VREG(17), _VREG(37), _VREG(32));
   __vcop_vmadd(_VREG(31), _VREG(27), _VREG(34), _PREG(0));
   __vcop_vmadd(_VREG(31), _VREG(28), _VREG(35), _PREG(0));
   __vcop_vmpy(_VREG(32), _VREG(34), _VREG(34), _PREG(0));
   __vcop_vmpy(_VREG(37), _VREG(35), _VREG(35), _PREG(0));
   __vcop_vadd(_VREG(34), _VREG(35), _VREG(34));
   __vcop_vshf(_VREG(33), _VREG(26), _VREG(33));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeBU(), __vcop_sdda(_VREG(33)), __vcop_alws(), _VREG(34), _PREG(18), _AGEN(4), _PREG(6));
   __vcop_vloop_end(4u);

}

void vcop_bilinearInterpolateYUV422Ichroma(
   __vptr_uint8 src,
   __vptr_uint8 dst,
   unsigned short maxNumMappedPixels,
   unsigned short numMappedPixels,
   __vptr_uint16 tluIndexArray,
   __vptr_uint8 xFracArray,
   __vptr_uint8 yFracArray,
   __vptr_uint16 scatterStoreArray,
   __vptr_uint16 scratchLUT,
   __vptr_uint8 scratchPixel,
   __vptr_uint16 stride_ptr,
   unsigned char mnQShift,
   unsigned char oQShift,
   unsigned short qScale,
   unsigned char rightShift,
   unsigned short src_size,
   long sat_high,
   long sat_high_set,
   long sat_low,
   long sat_low_set)
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_bilinearInterpolateYUV422Ichroma_init(src, dst, maxNumMappedPixels, numMappedPixels, tluIndexArray, xFracArray, yFracArray, scatterStoreArray, scratchLUT, scratchPixel, stride_ptr, mnQShift, oQShift, qScale, rightShift, src_size, sat_high, sat_high_set, sat_low, sat_low_set, __pblock_vcop_bilinearInterpolateYUV422Ichroma);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_bilinearInterpolateYUV422Ichroma_vloops(__pblock_vcop_bilinearInterpolateYUV422Ichroma);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

void vcop_bilinearInterpolateYUV422Ichroma_custom(
   __vptr_uint8 src,
   __vptr_uint8 dst,
   unsigned short maxNumMappedPixels,
   unsigned short numMappedPixels,
   __vptr_uint16 tluIndexArray,
   __vptr_uint8 xFracArray,
   __vptr_uint8 yFracArray,
   __vptr_uint16 scatterStoreArray,
   __vptr_uint16 scratchLUT,
   __vptr_uint8 scratchPixel,
   __vptr_uint16 stride_ptr,
   unsigned char mnQShift,
   unsigned char oQShift,
   unsigned short qScale,
   unsigned char rightShift,
   unsigned short src_size,
   long sat_high,
   long sat_high_set,
   long sat_low,
   long sat_low_set,
   unsigned short pblock[])
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_bilinearInterpolateYUV422Ichroma_init(src, dst, maxNumMappedPixels, numMappedPixels, tluIndexArray, xFracArray, yFracArray, scatterStoreArray, scratchLUT, scratchPixel, stride_ptr, mnQShift, oQShift, qScale, rightShift, src_size, sat_high, sat_high_set, sat_low, sat_low_set, pblock);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_bilinearInterpolateYUV422Ichroma_vloops(pblock);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

