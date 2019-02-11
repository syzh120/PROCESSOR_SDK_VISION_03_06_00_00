#include <vcop\vcop.h>

typedef unsigned char uchar;

#pragma DATA_SECTION(__pblock_vcop_bilinearInterpolateYUV420SPchroma, ".vcop_parameter_block")
#pragma DATA_ALIGN(__pblock_vcop_bilinearInterpolateYUV420SPchroma, __ALIGNOF__(int));
unsigned short __pblock_vcop_bilinearInterpolateYUV420SPchroma[90];

unsigned int vcop_bilinearInterpolateYUV420SPchroma_param_count(void)
{
   return 90u;
}

unsigned int vcop_bilinearInterpolateYUV420SPchroma_ctrl_count(void)
{
   return 0u;
}

unsigned int vcop_bilinearInterpolateYUV420SPchroma_init(
   __vptr_uint8 src,
   __vptr_uint8 dst,
   unsigned short maxNumMappedPixels,
   unsigned short numMappedPixels,
   __vptr_uint16 tluIndexArray,
   __vptr_uint8 xFracArray,
   __vptr_uint8 yFracArray,
   __vptr_uint16 scatterStoreArray,
   __vptr_uint8 scattered_ofst,
   __vptr_uint16 scratch,
   __vptr_uint8 scratchHbuf,
   unsigned char stride,
   unsigned char mnQShift,
   unsigned char oQShift,
   unsigned short qScale,
   unsigned char rightShift,
   unsigned short src_size,
   long sat_high,
   long sat_high_set,
   long sat_low,
   long sat_low_set,
   unsigned short dst_end_offset,
   unsigned short pblock[])
{
   int __offset = 0;
   /* Loop 1 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), ((((numMappedPixels) + 2U*(8u)-1U) & ~(2U*(8u)-1U))/(2*(8u)))-1u);
   __vcop_pblock_init32(pblock, __offset+_PREG(6), (uchar *)scratch);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)scratch+sizeof(*scratch)*(maxNumMappedPixels+2U*8u-1U&~(2U*8u-1U)));
   __vcop_pblock_init16(pblock, __offset+_PREG(10), 32);
   __vcop_pblock_init32(pblock, __offset+_PREG(12), stride);
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
   __vcop_pblock_init32(pblock, __offset+_PREG(12), (uchar *)scratchHbuf);
   __vcop_pblock_init16(pblock, __offset+_PREG(14), 4);
   __vcop_pblock_init32(pblock, __offset+_PREG(16), (uchar *)scratch);
   __vcop_pblock_init32(pblock, __offset+_PREG(18), (uchar *)src);
   __offset += 18;

   /* Loop 3 PREGS */
   const int preg_ref2 = _PREG(8);

   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), (numMappedPixels)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(6), __vcop_store_round_sat(SM_4PARAM,preg_ref2,RM_NONE,0));
   __vcop_pblock_init16(pblock, __offset+_PREG(7), 2);
   __vcop_pblock_4param_init(pblock, __offset+_PREG(8), src_size, src_size, 0, 0);
   __vcop_pblock_init32(pblock, __offset+_PREG(12), (uchar *)scratchHbuf+sizeof(*dst)*4*maxNumMappedPixels);
   __vcop_pblock_init16(pblock, __offset+_PREG(14), 4);
   __vcop_pblock_init32(pblock, __offset+_PREG(16), (uchar *)scratch+sizeof(*scratch)*(maxNumMappedPixels+2U*8u-1U&~(2U*8u-1U)));
   __vcop_pblock_init32(pblock, __offset+_PREG(18), (uchar *)src);
   __offset += 18;

   /* Loop 4 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), (1)-1u);
   __vcop_pblock_init32(pblock, __offset+_PREG(6), dst_end_offset);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)scatterStoreArray+2*numMappedPixels);
   __offset += 8;

   /* Loop 5 PREGS */
   const int preg_ref3 = _PREG(24);

   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), ((((numMappedPixels) + ((8u)/2U)-1U) & ~(((8u)/2U)-1U))/4)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(6), __vcop_store_round_sat(SM_4PARAM,preg_ref3,RM_ROUND,mnQShift+oQShift));
   __vcop_pblock_init16(pblock, __offset+_PREG(7), 4);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)xFracArray);
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)yFracArray);
   __vcop_pblock_init32(pblock, __offset+_PREG(12), (uchar *)scatterStoreArray);
   __vcop_pblock_init32(pblock, __offset+_PREG(14), (uchar *)scratchHbuf);
   __vcop_pblock_init32(pblock, __offset+_PREG(16), (uchar *)scratchHbuf+8u);
   __vcop_pblock_init32(pblock, __offset+_PREG(18), (uchar *)scratchHbuf+sizeof(*dst)*4*maxNumMappedPixels);
   __vcop_pblock_init32(pblock, __offset+_PREG(20), (uchar *)scratchHbuf+sizeof(*dst)*4*maxNumMappedPixels+8u);
   __vcop_pblock_init32(pblock, __offset+_PREG(22), (uchar *)dst);
   __vcop_pblock_4param_init(pblock, __offset+_PREG(24), sat_high,sat_high_set,sat_low,sat_low_set);
   __vcop_pblock_init16(pblock, __offset+_PREG(28), (2*8u*sizeof(*(scratchHbuf+sizeof(*dst)*4*maxNumMappedPixels))));
   __vcop_pblock_init16(pblock, __offset+_PREG(29), 8);
   __vcop_pblock_init32(pblock, __offset+_PREG(30), qScale);
   __vcop_pblock_init32(pblock, __offset+_PREG(32), (uchar *)scattered_ofst);
   __offset += 32;

   return 90u;
}

void vcop_bilinearInterpolateYUV420SPchroma_vloops(
   unsigned short pblock[])
{
   /* Kernel-wide Vector Registers */
   #pragma VCC_VREG("Vstride", 16);
   #pragma VCC_VREG("v_UVoffset", 17);
   #pragma VCC_VREG("v_qScale", 18);

   __vcop_param(&pblock[0]);

   /* VLOOP 1 Start */

   /* VLOOP Local Vector Registers */
   #pragma VCC_VREG("index00_1", 19);
   #pragma VCC_VREG("index00_2", 20);
   #pragma VCC_VREG("index01_1", 21);
   #pragma VCC_VREG("index01_2", 22);
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("Addr0", "A0");
   #pragma EVE_REG("Addr2", "A1");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I1", "I4");
   

   __vcop_vloop(__vcop_compute(), 9u, 7u, 1u);
   __vcop_vinit(__vcop_sizeW(), __vcop_once(), _PREG(12), _VREG(16));
   __vcop_vagen(_AGEN(1), _PREG(10), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeHU(), __vcop_dintrlv(), _PREG(14), _AGEN(1), _VPAIR(19,20), __vcop_alws());
   __vcop_vadd(_VREG(19), _VREG(16), _VREG(21));
   __vcop_vadd(_VREG(20), _VREG(16), _VREG(22));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeHU(), __vcop_intrlv(), __vcop_alws(), _VPAIR(19,20), _PREG(6), _AGEN(1), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeHU(), __vcop_intrlv(), __vcop_alws(), _VPAIR(21,22), _PREG(8), _AGEN(1), _PREG(0));
   __vcop_vloop_end(1u);

   /* VLOOP 2 Start */

   /* VLOOP Local Vector Registers */
   #pragma VCC_VREG("Vdata", 23);
   #pragma VCC_VREG("Vindex", 24);
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("TLU_agen", "A1");
   #pragma EVE_REG("ind_agen", "A0");
   #pragma EVE_REG("out_agen", "A2");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I1", "I4");
   

   __vcop_vloop(__vcop_tablelkup(), 7u, 9u, 2u);
   __vcop_vagen(_AGEN(1), _PREG(0), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(0), _PREG(7), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(2), _PREG(14), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeHU(), __vcop_npt(), _PREG(16), _AGEN(0), _VREG(24), __vcop_alws());
   __vcop_vtbload(__vcop_sizeBU(), __vcop_tableinfo(1, 4), _PREG(18), _AGEN(1), _VREG(24), _VREG(23), _PREG(6), __vcop_alws());
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeBU(), __vcop_npt(), __vcop_alws(), _VREG(23), _PREG(12), _AGEN(2), _PREG(0));
   __vcop_vloop_end(2u);

   /* VLOOP 3 Start */

   /* VLOOP Local Vector Registers */
   #pragma VCC_VREG("Vdata", 25);
   #pragma VCC_VREG("Vindex", 26);
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("TLU_agen", "A1");
   #pragma EVE_REG("ind_agen", "A0");
   #pragma EVE_REG("out_agen", "A2");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I1", "I4");
   

   __vcop_vloop(__vcop_tablelkup(), 7u, 9u, 3u);
   __vcop_vagen(_AGEN(1), _PREG(0), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(0), _PREG(7), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(2), _PREG(14), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeHU(), __vcop_npt(), _PREG(16), _AGEN(0), _VREG(26), __vcop_alws());
   __vcop_vtbload(__vcop_sizeBU(), __vcop_tableinfo(1, 4), _PREG(18), _AGEN(1), _VREG(26), _VREG(25), _PREG(6), __vcop_alws());
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeBU(), __vcop_npt(), __vcop_alws(), _VREG(25), _PREG(12), _AGEN(2), _PREG(0));
   __vcop_vloop_end(3u);

   /* VLOOP 4 Start */

   /* VLOOP Local Vector Registers */
   #pragma VCC_VREG("Voffset", 27);
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("Addr0", "A0");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I1", "I4");
   

   __vcop_vloop(__vcop_compute(), 4u, 4u, 4u);
   __vcop_vinit(__vcop_sizeW(), __vcop_alws(), _PREG(6), _VREG(27));
   __vcop_vagen(_AGEN(0), _PREG(0), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeHU(), __vcop_npt(), __vcop_alws(), _VREG(27), _PREG(8), _AGEN(0), _PREG(0));
   __vcop_vloop_end(4u);

   /* VLOOP 5 Start */

   /* VLOOP Local Vector Registers */
   #pragma VCC_VREG("pix00UV", 28);
   #pragma VCC_VREG("pix00UV_1", 29);
   #pragma VCC_VREG("pix00UV_2", 30);
   #pragma VCC_VREG("pix01UV", 31);
   #pragma VCC_VREG("pix01UV_1", 32);
   #pragma VCC_VREG("pix01UV_2", 33);
   #pragma VCC_VREG("pix10UV", 34);
   #pragma VCC_VREG("pix11UV", 35);
   #pragma VCC_VREG("qScale_xFrac", 36);
   #pragma VCC_VREG("qScale_yFrac", 37);
   #pragma VCC_VREG("scatterStore", 38);
   #pragma VCC_VREG("temp1", 39);
   #pragma VCC_VREG("temp2", 40);
   #pragma VCC_VREG("xFrac", 41);
   #pragma VCC_VREG("yFrac", 42);
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("Addr0", "A0");
   #pragma EVE_REG("Addr1", "A1");
   #pragma EVE_REG("Addr2", "A2");
   #pragma EVE_REG("Addr3", "A3");
   #pragma EVE_REG("Addr_out", "A4");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I1", "I4");
   

   __vcop_vloop(__vcop_compute(), 32u, 16u, 5u);
   __vcop_vinit(__vcop_sizeW(), __vcop_once(), _PREG(30), _VREG(18));
   __vcop_vagen(_AGEN(0), _PREG(0), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(1), _PREG(7), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(2), _PREG(28), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(3), _PREG(29), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(4), _PREG(0), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeBU(), __vcop_npt(), _PREG(32), _AGEN(0), _VREG(17), __vcop_once());
   __vcop_vload(__vcop_sizeBU(), __vcop_us2(), _PREG(8), _AGEN(1), _VREG(41), __vcop_alws());
   __vcop_vload(__vcop_sizeBU(), __vcop_us2(), _PREG(10), _AGEN(1), _VREG(42), __vcop_alws());
   __vcop_vload(__vcop_sizeHU(), __vcop_us2(), _PREG(12), _AGEN(3), _VREG(38), __vcop_alws());
   __vcop_vload(__vcop_sizeBU(), __vcop_npt(), _PREG(14), _AGEN(2), _VREG(29), __vcop_alws());
   __vcop_vload(__vcop_sizeBU(), __vcop_npt(), _PREG(16), _AGEN(2), _VREG(30), __vcop_alws());
   __vcop_vload(__vcop_sizeBU(), __vcop_npt(), _PREG(18), _AGEN(2), _VREG(32), __vcop_alws());
   __vcop_vload(__vcop_sizeBU(), __vcop_npt(), _PREG(20), _AGEN(2), _VREG(33), __vcop_alws());
   __vcop_vmove(_VREG(29), _VREG(28));
   __vcop_vmove(_VREG(30), _VREG(34));
   __vcop_vdintrlv2(_VREG(28), _VREG(34));
   __vcop_vmove(_VREG(32), _VREG(31));
   __vcop_vmove(_VREG(33), _VREG(35));
   __vcop_vdintrlv2(_VREG(31), _VREG(35));
   __vcop_vmpy(_VREG(41), _VREG(34), _VREG(39), _PREG(0));
   __vcop_vmpy(_VREG(41), _VREG(35), _VREG(40), _PREG(0));
   __vcop_vsub(_VREG(18), _VREG(41), _VREG(36));
   __vcop_vsub(_VREG(18), _VREG(42), _VREG(37));
   __vcop_vmadd(_VREG(36), _VREG(28), _VREG(39), _PREG(0));
   __vcop_vmadd(_VREG(36), _VREG(31), _VREG(40), _PREG(0));
   __vcop_vmpy(_VREG(37), _VREG(39), _VREG(39), _PREG(0));
   __vcop_vmpy(_VREG(42), _VREG(40), _VREG(40), _PREG(0));
   __vcop_vadd(_VREG(39), _VREG(40), _VREG(39));
   __vcop_vadd(_VREG(38), _VREG(17), _VREG(38));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeBU(), __vcop_sdda(_VREG(38)), __vcop_alws(), _VREG(39), _PREG(22), _AGEN(4), _PREG(6));
   __vcop_vloop_end(5u);

}

void vcop_bilinearInterpolateYUV420SPchroma(
   __vptr_uint8 src,
   __vptr_uint8 dst,
   unsigned short maxNumMappedPixels,
   unsigned short numMappedPixels,
   __vptr_uint16 tluIndexArray,
   __vptr_uint8 xFracArray,
   __vptr_uint8 yFracArray,
   __vptr_uint16 scatterStoreArray,
   __vptr_uint8 scattered_ofst,
   __vptr_uint16 scratch,
   __vptr_uint8 scratchHbuf,
   unsigned char stride,
   unsigned char mnQShift,
   unsigned char oQShift,
   unsigned short qScale,
   unsigned char rightShift,
   unsigned short src_size,
   long sat_high,
   long sat_high_set,
   long sat_low,
   long sat_low_set,
   unsigned short dst_end_offset)
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_bilinearInterpolateYUV420SPchroma_init(src, dst, maxNumMappedPixels, numMappedPixels, tluIndexArray, xFracArray, yFracArray, scatterStoreArray, scattered_ofst, scratch, scratchHbuf, stride, mnQShift, oQShift, qScale, rightShift, src_size, sat_high, sat_high_set, sat_low, sat_low_set, dst_end_offset, __pblock_vcop_bilinearInterpolateYUV420SPchroma);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_bilinearInterpolateYUV420SPchroma_vloops(__pblock_vcop_bilinearInterpolateYUV420SPchroma);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

void vcop_bilinearInterpolateYUV420SPchroma_custom(
   __vptr_uint8 src,
   __vptr_uint8 dst,
   unsigned short maxNumMappedPixels,
   unsigned short numMappedPixels,
   __vptr_uint16 tluIndexArray,
   __vptr_uint8 xFracArray,
   __vptr_uint8 yFracArray,
   __vptr_uint16 scatterStoreArray,
   __vptr_uint8 scattered_ofst,
   __vptr_uint16 scratch,
   __vptr_uint8 scratchHbuf,
   unsigned char stride,
   unsigned char mnQShift,
   unsigned char oQShift,
   unsigned short qScale,
   unsigned char rightShift,
   unsigned short src_size,
   long sat_high,
   long sat_high_set,
   long sat_low,
   long sat_low_set,
   unsigned short dst_end_offset,
   unsigned short pblock[])
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_bilinearInterpolateYUV420SPchroma_init(src, dst, maxNumMappedPixels, numMappedPixels, tluIndexArray, xFracArray, yFracArray, scatterStoreArray, scattered_ofst, scratch, scratchHbuf, stride, mnQShift, oQShift, qScale, rightShift, src_size, sat_high, sat_high_set, sat_low, sat_low_set, dst_end_offset, pblock);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_bilinearInterpolateYUV420SPchroma_vloops(pblock);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

#pragma DATA_SECTION(__pblock_vcop_bilinearInterpolateYUV420SPchromaBB, ".vcop_parameter_block")
#pragma DATA_ALIGN(__pblock_vcop_bilinearInterpolateYUV420SPchromaBB, __ALIGNOF__(int));
unsigned short __pblock_vcop_bilinearInterpolateYUV420SPchromaBB[66];

unsigned int vcop_bilinearInterpolateYUV420SPchromaBB_param_count(void)
{
   return 66u;
}

unsigned int vcop_bilinearInterpolateYUV420SPchromaBB_ctrl_count(void)
{
   return 0u;
}

unsigned int vcop_bilinearInterpolateYUV420SPchromaBB_init(
   __vptr_uint8 src,
   __vptr_uint8 dst,
   unsigned short outputBlockSize,
   __vptr_uint8 xFracArray,
   __vptr_uint8 yFracArray,
   __vptr_uint16 tluIndexArray,
   __vptr_uint16 scratch,
   __vptr_uint8 scratchHbuf,
   __vptr_uint16 stride_ptr,
   unsigned char mnQShift,
   unsigned char oQShift,
   unsigned short qScale,
   unsigned char rightShift,
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
   __vcop_pblock_init16(pblock, __offset+_PREG(5), ((((outputBlockSize) + 2U*(8u)-1U) & ~(2U*(8u)-1U))/(2*(8u)))-1u);
   __vcop_pblock_init32(pblock, __offset+_PREG(6), (uchar *)scratch);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)scratch+sizeof(*scratch)*(outputBlockSize+2U*8u-1U&~(2U*8u-1U)));
   __vcop_pblock_init16(pblock, __offset+_PREG(10), 32);
   __vcop_pblock_init32(pblock, __offset+_PREG(12), (uchar *)stride_ptr);
   __vcop_pblock_init32(pblock, __offset+_PREG(14), (uchar *)tluIndexArray);
   __offset += 14;

   /* Loop 2 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), (outputBlockSize)-1u);
   __vcop_pblock_init32(pblock, __offset+_PREG(6), (uchar *)scratchHbuf);
   __vcop_pblock_init16(pblock, __offset+_PREG(8), 2);
   __vcop_pblock_init16(pblock, __offset+_PREG(9), 4);
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)scratch);
   __vcop_pblock_init32(pblock, __offset+_PREG(12), (uchar *)src);
   __offset += 12;

   /* Loop 3 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), (outputBlockSize)-1u);
   __vcop_pblock_init32(pblock, __offset+_PREG(6), (uchar *)scratchHbuf+sizeof(*dst)*4*outputBlockSize);
   __vcop_pblock_init16(pblock, __offset+_PREG(8), 2);
   __vcop_pblock_init16(pblock, __offset+_PREG(9), 4);
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)scratch+sizeof(*scratch)*(outputBlockSize+2U*8u-1U&~(2U*8u-1U)));
   __vcop_pblock_init32(pblock, __offset+_PREG(12), (uchar *)src);
   __offset += 12;

   /* Loop 4 PREGS */
   const int preg_ref4 = _PREG(20);

   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), ((((outputBlockSize) + (8u)-1U) & ~((8u)-1U))/4)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(6), __vcop_store_round_sat(SM_4PARAM,preg_ref4,RM_ROUND,mnQShift+oQShift));
   __vcop_pblock_init16(pblock, __offset+_PREG(7), 4);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)yFracArray);
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)scratchHbuf);
   __vcop_pblock_init32(pblock, __offset+_PREG(12), (uchar *)scratchHbuf+8u);
   __vcop_pblock_init32(pblock, __offset+_PREG(14), (uchar *)scratchHbuf+sizeof(*dst)*4*outputBlockSize);
   __vcop_pblock_init32(pblock, __offset+_PREG(16), (uchar *)scratchHbuf+sizeof(*dst)*4*outputBlockSize+8u);
   __vcop_pblock_init32(pblock, __offset+_PREG(18), (uchar *)dst);
   __vcop_pblock_4param_init(pblock, __offset+_PREG(20), sat_high,sat_high_set,sat_low,sat_low_set);
   __vcop_pblock_init16(pblock, __offset+_PREG(24), (2*8u*sizeof(*(scratchHbuf+sizeof(*dst)*4*outputBlockSize))));
   __vcop_pblock_init16(pblock, __offset+_PREG(25), 8);
   __vcop_pblock_init32(pblock, __offset+_PREG(26), qScale);
   __vcop_pblock_init32(pblock, __offset+_PREG(28), (uchar *)xFracArray);
   __offset += 28;

   return 66u;
}

void vcop_bilinearInterpolateYUV420SPchromaBB_vloops(
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
   

   __vcop_vloop(__vcop_tablelkup(), 7u, 6u, 2u);
   __vcop_vagen(_AGEN(1), _PREG(0), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(0), _PREG(8), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(2), _PREG(9), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeHU(), __vcop_npt(), _PREG(10), _AGEN(0), _VREG(23), __vcop_alws());
   __vcop_vtbload(__vcop_sizeBU(), __vcop_tableinfo(1, 4), _PREG(12), _AGEN(1), _VREG(23), _VREG(22), _PREG(0), __vcop_alws());
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeBU(), __vcop_npt(), __vcop_alws(), _VREG(22), _PREG(6), _AGEN(2), _PREG(0));
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
   

   __vcop_vloop(__vcop_tablelkup(), 7u, 6u, 3u);
   __vcop_vagen(_AGEN(1), _PREG(0), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(0), _PREG(8), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(2), _PREG(9), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeHU(), __vcop_npt(), _PREG(10), _AGEN(0), _VREG(25), __vcop_alws());
   __vcop_vtbload(__vcop_sizeBU(), __vcop_tableinfo(1, 4), _PREG(12), _AGEN(1), _VREG(25), _VREG(24), _PREG(0), __vcop_alws());
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeBU(), __vcop_npt(), __vcop_alws(), _VREG(24), _PREG(6), _AGEN(2), _PREG(0));
   __vcop_vloop_end(3u);

   /* VLOOP 4 Start */

   /* VLOOP Local Vector Registers */
   #pragma VCC_VREG("pix00UV", 26);
   #pragma VCC_VREG("pix00UV_1", 27);
   #pragma VCC_VREG("pix00UV_2", 28);
   #pragma VCC_VREG("pix01UV", 29);
   #pragma VCC_VREG("pix01UV_1", 30);
   #pragma VCC_VREG("pix01UV_2", 31);
   #pragma VCC_VREG("pix10UV", 32);
   #pragma VCC_VREG("pix11UV", 33);
   #pragma VCC_VREG("qScale_xFrac", 34);
   #pragma VCC_VREG("qScale_yFrac", 35);
   #pragma VCC_VREG("temp1", 36);
   #pragma VCC_VREG("temp2", 37);
   #pragma VCC_VREG("xFrac", 38);
   #pragma VCC_VREG("yFrac", 39);
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("Addr0", "A0");
   #pragma EVE_REG("Addr1", "A1");
   #pragma EVE_REG("Addr2", "A2");
   #pragma EVE_REG("Addr_out", "A3");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I1", "I4");
   

   __vcop_vloop(__vcop_compute(), 28u, 14u, 4u);
   __vcop_vinit(__vcop_sizeW(), __vcop_once(), _PREG(26), _VREG(17));
   __vcop_vagen(_AGEN(1), _PREG(7), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(2), _PREG(24), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(3), _PREG(25), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeBU(), __vcop_us2(), _PREG(28), _AGEN(1), _VREG(38), __vcop_alws());
   __vcop_vload(__vcop_sizeBU(), __vcop_us2(), _PREG(8), _AGEN(1), _VREG(39), __vcop_alws());
   __vcop_vload(__vcop_sizeBU(), __vcop_npt(), _PREG(10), _AGEN(2), _VREG(27), __vcop_alws());
   __vcop_vload(__vcop_sizeBU(), __vcop_npt(), _PREG(12), _AGEN(2), _VREG(28), __vcop_alws());
   __vcop_vload(__vcop_sizeBU(), __vcop_npt(), _PREG(14), _AGEN(2), _VREG(30), __vcop_alws());
   __vcop_vload(__vcop_sizeBU(), __vcop_npt(), _PREG(16), _AGEN(2), _VREG(31), __vcop_alws());
   __vcop_vmove(_VREG(27), _VREG(26));
   __vcop_vmove(_VREG(28), _VREG(32));
   __vcop_vdintrlv2(_VREG(26), _VREG(32));
   __vcop_vmove(_VREG(30), _VREG(29));
   __vcop_vmove(_VREG(31), _VREG(33));
   __vcop_vdintrlv2(_VREG(29), _VREG(33));
   __vcop_vmpy(_VREG(38), _VREG(32), _VREG(36), _PREG(0));
   __vcop_vmpy(_VREG(38), _VREG(33), _VREG(37), _PREG(0));
   __vcop_vsub(_VREG(17), _VREG(38), _VREG(34));
   __vcop_vsub(_VREG(17), _VREG(39), _VREG(35));
   __vcop_vmadd(_VREG(34), _VREG(26), _VREG(36), _PREG(0));
   __vcop_vmadd(_VREG(34), _VREG(29), _VREG(37), _PREG(0));
   __vcop_vmpy(_VREG(35), _VREG(36), _VREG(36), _PREG(0));
   __vcop_vmpy(_VREG(39), _VREG(37), _VREG(37), _PREG(0));
   __vcop_vadd(_VREG(36), _VREG(37), _VREG(36));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeBU(), __vcop_npt(), __vcop_alws(), _VREG(36), _PREG(18), _AGEN(3), _PREG(6));
   __vcop_vloop_end(4u);

}

void vcop_bilinearInterpolateYUV420SPchromaBB(
   __vptr_uint8 src,
   __vptr_uint8 dst,
   unsigned short outputBlockSize,
   __vptr_uint8 xFracArray,
   __vptr_uint8 yFracArray,
   __vptr_uint16 tluIndexArray,
   __vptr_uint16 scratch,
   __vptr_uint8 scratchHbuf,
   __vptr_uint16 stride_ptr,
   unsigned char mnQShift,
   unsigned char oQShift,
   unsigned short qScale,
   unsigned char rightShift,
   long sat_high,
   long sat_high_set,
   long sat_low,
   long sat_low_set)
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_bilinearInterpolateYUV420SPchromaBB_init(src, dst, outputBlockSize, xFracArray, yFracArray, tluIndexArray, scratch, scratchHbuf, stride_ptr, mnQShift, oQShift, qScale, rightShift, sat_high, sat_high_set, sat_low, sat_low_set, __pblock_vcop_bilinearInterpolateYUV420SPchromaBB);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_bilinearInterpolateYUV420SPchromaBB_vloops(__pblock_vcop_bilinearInterpolateYUV420SPchromaBB);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

void vcop_bilinearInterpolateYUV420SPchromaBB_custom(
   __vptr_uint8 src,
   __vptr_uint8 dst,
   unsigned short outputBlockSize,
   __vptr_uint8 xFracArray,
   __vptr_uint8 yFracArray,
   __vptr_uint16 tluIndexArray,
   __vptr_uint16 scratch,
   __vptr_uint8 scratchHbuf,
   __vptr_uint16 stride_ptr,
   unsigned char mnQShift,
   unsigned char oQShift,
   unsigned short qScale,
   unsigned char rightShift,
   long sat_high,
   long sat_high_set,
   long sat_low,
   long sat_low_set,
   unsigned short pblock[])
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_bilinearInterpolateYUV420SPchromaBB_init(src, dst, outputBlockSize, xFracArray, yFracArray, tluIndexArray, scratch, scratchHbuf, stride_ptr, mnQShift, oQShift, qScale, rightShift, sat_high, sat_high_set, sat_low, sat_low_set, pblock);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_bilinearInterpolateYUV420SPchromaBB_vloops(pblock);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

