#include <vcop\vcop.h>

typedef unsigned char uchar;

#pragma DATA_SECTION(__pblock_vcop_block_statistics, ".vcop_parameter_block")
#pragma DATA_ALIGN(__pblock_vcop_block_statistics, __ALIGNOF__(int));
unsigned short __pblock_vcop_block_statistics[70];

unsigned int vcop_block_statistics_param_count(void)
{
   return 70u;
}

unsigned int vcop_block_statistics_ctrl_count(void)
{
   return 0u;
}

unsigned int vcop_block_statistics_init(
   __vptr_uint8 im_A,
   unsigned short blockStride,
   unsigned short blockWidth,
   unsigned short blockHeight,
   unsigned short statBlockWidth,
   unsigned short statBlockHeight,
   __vptr_uint8 scratch_C,
   __vptr_uint16 scratchSum_A,
   __vptr_uint32 scratchSumSq_B,
   __vptr_uint32 scratchSumSq_C,
   __vptr_uint16 scratchSumSq_C_lo,
   __vptr_uint16 scratchSumSq_C_hi,
   __vptr_uint8 min_B,
   __vptr_uint8 max_B,
   __vptr_uint16 mean_B,
   __vptr_uint32 variance_A,
   unsigned short pblock[])
{
   int __offset = 0;
   /* Loop 1 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), ((blockHeight/statBlockHeight))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), (((blockWidth + (8u) - 1)/(8u)))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), (statBlockHeight)-1u);
   __vcop_pblock_init32(pblock, __offset+_PREG(6), (uchar *)im_A);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)scratch_C);
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)scratch_C+8);
   __vcop_pblock_init32(pblock, __offset+_PREG(12), (uchar *)scratchSum_A);
   __vcop_pblock_init32(pblock, __offset+_PREG(14), (uchar *)scratchSumSq_B);
   __vcop_pblock_init16(pblock, __offset+_PREG(16), 288);
   __vcop_pblock_init16(pblock, __offset+_PREG(17), (sizeof(*im_A)) -(36*8u)*((((blockWidth + (8u) - 1)/(8u)))-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(18), (2*sizeof(*im_A)) -(36*8u)*((((blockWidth + (8u) - 1)/(8u)))-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(19), (4*sizeof(*im_A)) -(36*8u)*((((blockWidth + (8u) - 1)/(8u)))-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(20), (blockStride));
   __vcop_pblock_init16(pblock, __offset+_PREG(21), ((8u*sizeof(*im_A))) -(blockStride)*((statBlockHeight)-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(22), (statBlockHeight*blockStride) -((8u*sizeof(*im_A)))*((((blockWidth + (8u) - 1)/(8u)))-1u) -(blockStride)*((statBlockHeight)-1u));
   __vcop_pblock_init32(pblock, __offset+_PREG(24), 255);
   __vcop_pblock_init32(pblock, __offset+_PREG(26), 0);
   __offset += 26;

   /* Loop 2 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), ((blockWidth/statBlockWidth))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), (statBlockWidth)-1u);
   __vcop_pblock_init32(pblock, __offset+_PREG(6), (uchar *)scratch_C);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)scratchSum_A);
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)scratch_C+8);
   __vcop_pblock_init32(pblock, __offset+_PREG(12), (uchar *)scratchSumSq_B);
   __vcop_pblock_init32(pblock, __offset+_PREG(14), (uchar *)min_B);
   __vcop_pblock_init32(pblock, __offset+_PREG(16), (uchar *)max_B);
   __vcop_pblock_init32(pblock, __offset+_PREG(18), (uchar *)mean_B);
   __vcop_pblock_init32(pblock, __offset+_PREG(20), (uchar *)scratchSumSq_C);
   __vcop_pblock_init16(pblock, __offset+_PREG(22), 2);
   __vcop_pblock_init16(pblock, __offset+_PREG(23), 4);
   __vcop_pblock_init16(pblock, __offset+_PREG(24), 36);
   __vcop_pblock_init16(pblock, __offset+_PREG(25), (statBlockWidth*36) -(36)*((statBlockWidth)-1u));
   __vcop_pblock_init32(pblock, __offset+_PREG(26), 255);
   __vcop_pblock_init32(pblock, __offset+_PREG(28), 0);
   __offset += 28;

   /* Loop 3 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), ((blockHeight/statBlockHeight))-1u);
   __vcop_pblock_init32(pblock, __offset+_PREG(6), (uchar *)mean_B);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), statBlockWidth*statBlockHeight);
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)variance_A);
   __vcop_pblock_init16(pblock, __offset+_PREG(12), 36);
   __vcop_pblock_init16(pblock, __offset+_PREG(13), ((blockWidth/statBlockWidth)*4));
   __vcop_pblock_init32(pblock, __offset+_PREG(14), (uchar *)scratchSumSq_C_lo);
   __vcop_pblock_init32(pblock, __offset+_PREG(16), (uchar *)scratchSumSq_C_hi);
   __offset += 16;

   return 70u;
}

void vcop_block_statistics_vloops(
   unsigned short pblock[])
{
   /* Kernel-wide Vector Registers */

   __vcop_param(&pblock[0]);

   /* VLOOP 1 Start */

   /* VLOOP Local Vector Registers */
   #pragma VCC_VREG("Vmax", 16);
   #pragma VCC_VREG("Vmin", 17);
   #pragma VCC_VREG("Vsum", 18);
   #pragma VCC_VREG("VsumSq", 19);
   #pragma VCC_VREG("Vin", 20);
   #pragma VCC_VREG("VinSq", 21);
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("AddrOut", "A0");
   #pragma EVE_REG("AddrOutSum", "A1");
   #pragma EVE_REG("AddrOutSumSq", "A2");
   #pragma EVE_REG("AddrIn", "A3");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I1", "I2");
   #pragma EVE_REG("I2", "I3");
   #pragma EVE_REG("I3", "I4");
   

   __vcop_vloop(__vcop_compute(), 18u, 13u, 1u);
   __vcop_vinit(__vcop_sizeW(), __vcop_i4_zero(), _PREG(24), _VREG(17));
   __vcop_vinit(__vcop_sizeW(), __vcop_i4_zero(), _PREG(26), _VREG(16));
   __vcop_vinit(__vcop_sizeW(), __vcop_i4_zero(), _PREG(26), _VREG(18));
   __vcop_vinit(__vcop_sizeW(), __vcop_i4_zero(), _PREG(26), _VREG(19));
   __vcop_vagen(_AGEN(0), _PREG(0), _PREG(16), _PREG(17), _PREG(0));
   __vcop_vagen(_AGEN(1), _PREG(0), _PREG(16), _PREG(18), _PREG(0));
   __vcop_vagen(_AGEN(2), _PREG(0), _PREG(16), _PREG(19), _PREG(0));
   __vcop_vagen(_AGEN(3), _PREG(20), _PREG(21), _PREG(22), _PREG(0));
   __vcop_vload(__vcop_sizeBU(), __vcop_npt(), _PREG(6), _AGEN(3), _VREG(20), __vcop_alws());
   __vcop_vadd(_VREG(18), _VREG(20), _VREG(18));
   __vcop_vmadd(_VREG(20), _VREG(20), _VREG(19), _PREG(0));
   __vcop_vmin(_VREG(20), _VREG(17), _VREG(17));
   __vcop_vmax(_VREG(20), _VREG(16), _VREG(16));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeBU(), __vcop_offst_np1(), __vcop_last_i4(), _VREG(17), _PREG(8), _AGEN(0), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeBU(), __vcop_offst_np1(), __vcop_last_i4(), _VREG(16), _PREG(10), _AGEN(0), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeHU(), __vcop_offst_np1(), __vcop_last_i4(), _VREG(18), _PREG(12), _AGEN(1), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeWU(), __vcop_offst_np1(), __vcop_last_i4(), _VREG(19), _PREG(14), _AGEN(2), _PREG(0));
   __vcop_vloop_end(1u);

   /* VLOOP 2 Start */

   /* VLOOP Local Vector Registers */
   #pragma VCC_VREG("Vmax", 22);
   #pragma VCC_VREG("Vmin", 23);
   #pragma VCC_VREG("Vsum", 24);
   #pragma VCC_VREG("VsumSq", 25);
   #pragma VCC_VREG("VrowMax", 26);
   #pragma VCC_VREG("VrowMin", 27);
   #pragma VCC_VREG("VrowSum", 28);
   #pragma VCC_VREG("VrowSumSq", 29);
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("AddrOut", "A0");
   #pragma EVE_REG("AddrOutSum", "A1");
   #pragma EVE_REG("AddrOutSumSq", "A2");
   #pragma EVE_REG("AddrIn", "A3");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I1", "I3");
   #pragma EVE_REG("I2", "I4");
   

   __vcop_vloop(__vcop_compute(), 21u, 14u, 2u);
   __vcop_vinit(__vcop_sizeW(), __vcop_i4_zero(), _PREG(26), _VREG(23));
   __vcop_vinit(__vcop_sizeW(), __vcop_i4_zero(), _PREG(28), _VREG(22));
   __vcop_vinit(__vcop_sizeW(), __vcop_i4_zero(), _PREG(28), _VREG(24));
   __vcop_vinit(__vcop_sizeW(), __vcop_i4_zero(), _PREG(28), _VREG(25));
   __vcop_vagen(_AGEN(0), _PREG(0), _PREG(1), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(1), _PREG(0), _PREG(22), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(2), _PREG(0), _PREG(23), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(3), _PREG(24), _PREG(25), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeBU(), __vcop_npt(), _PREG(6), _AGEN(3), _VREG(27), __vcop_alws());
   __vcop_vload(__vcop_sizeHU(), __vcop_npt(), _PREG(8), _AGEN(3), _VREG(28), __vcop_alws());
   __vcop_vload(__vcop_sizeBU(), __vcop_npt(), _PREG(10), _AGEN(3), _VREG(26), __vcop_alws());
   __vcop_vload(__vcop_sizeWU(), __vcop_npt(), _PREG(12), _AGEN(3), _VREG(29), __vcop_alws());
   __vcop_vadd(_VREG(24), _VREG(28), _VREG(24));
   __vcop_vadd(_VREG(25), _VREG(29), _VREG(25));
   __vcop_vmin(_VREG(27), _VREG(23), _VREG(23));
   __vcop_vmax(_VREG(26), _VREG(22), _VREG(22));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeBU(), __vcop_offst_np1(), __vcop_last_i4(), _VREG(23), _PREG(14), _AGEN(0), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeBU(), __vcop_offst_np1(), __vcop_last_i4(), _VREG(22), _PREG(16), _AGEN(0), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeHU(), __vcop_offst_np1(), __vcop_last_i4(), _VREG(24), _PREG(18), _AGEN(1), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeWU(), __vcop_offst_np1(), __vcop_last_i4(), _VREG(25), _PREG(20), _AGEN(2), _PREG(0));
   __vcop_vloop_end(2u);

   /* VLOOP 3 Start */

   /* VLOOP Local Vector Registers */
   #pragma VCC_VREG("Vhi", 30);
   #pragma VCC_VREG("Vlo", 31);
   #pragma VCC_VREG("Vmean", 32);
   #pragma VCC_VREG("Vmean2", 33);
   #pragma VCC_VREG("Vn", 34);
   #pragma VCC_VREG("Vt1", 35);
   #pragma VCC_VREG("Vt1H", 36);
   #pragma VCC_VREG("Vt1L", 37);
   #pragma VCC_VREG("Vt2", 38);
   #pragma VCC_VREG("Vvar", 39);
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("AddrIn", "A0");
   #pragma EVE_REG("Addrout", "A1");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I1", "I4");
   

   __vcop_vloop(__vcop_compute(), 14u, 8u, 3u);
   __vcop_vinit(__vcop_sizeW(), __vcop_alws(), _PREG(8), _VREG(34));
   __vcop_vagen(_AGEN(0), _PREG(12), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(1), _PREG(13), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeHU(), __vcop_ds2(), _PREG(14), _AGEN(0), _VREG(31), __vcop_alws());
   __vcop_vload(__vcop_sizeHU(), __vcop_ds2(), _PREG(16), _AGEN(0), _VREG(30), __vcop_alws());
   __vcop_vload(__vcop_sizeHU(), __vcop_npt(), _PREG(6), _AGEN(0), _VREG(32), __vcop_alws());
   __vcop_vmpy(_VREG(32), _VREG(32), _VREG(33), _PREG(0));
   __vcop_vmpy(_VREG(30), _VREG(34), _VREG(35), _PREG(0));
   __vcop_vmpy(_VREG(31), _VREG(34), _VREG(38), _PREG(0));
   __vcop_vshf16(_VREG(35), _VREG(37), _VREG(36));
   __vcop_vadd(_VREG(38), _VREG(37), _VREG(38));
   __vcop_vsub(_VREG(38), _VREG(33), _VREG(39));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeWU(), __vcop_npt(), __vcop_alws(), _VREG(39), _PREG(10), _AGEN(1), _PREG(0));
   __vcop_vloop_end(3u);

}

void vcop_block_statistics(
   __vptr_uint8 im_A,
   unsigned short blockStride,
   unsigned short blockWidth,
   unsigned short blockHeight,
   unsigned short statBlockWidth,
   unsigned short statBlockHeight,
   __vptr_uint8 scratch_C,
   __vptr_uint16 scratchSum_A,
   __vptr_uint32 scratchSumSq_B,
   __vptr_uint32 scratchSumSq_C,
   __vptr_uint16 scratchSumSq_C_lo,
   __vptr_uint16 scratchSumSq_C_hi,
   __vptr_uint8 min_B,
   __vptr_uint8 max_B,
   __vptr_uint16 mean_B,
   __vptr_uint32 variance_A)
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_block_statistics_init(im_A, blockStride, blockWidth, blockHeight, statBlockWidth, statBlockHeight, scratch_C, scratchSum_A, scratchSumSq_B, scratchSumSq_C, scratchSumSq_C_lo, scratchSumSq_C_hi, min_B, max_B, mean_B, variance_A, __pblock_vcop_block_statistics);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_block_statistics_vloops(__pblock_vcop_block_statistics);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

void vcop_block_statistics_custom(
   __vptr_uint8 im_A,
   unsigned short blockStride,
   unsigned short blockWidth,
   unsigned short blockHeight,
   unsigned short statBlockWidth,
   unsigned short statBlockHeight,
   __vptr_uint8 scratch_C,
   __vptr_uint16 scratchSum_A,
   __vptr_uint32 scratchSumSq_B,
   __vptr_uint32 scratchSumSq_C,
   __vptr_uint16 scratchSumSq_C_lo,
   __vptr_uint16 scratchSumSq_C_hi,
   __vptr_uint8 min_B,
   __vptr_uint8 max_B,
   __vptr_uint16 mean_B,
   __vptr_uint32 variance_A,
   unsigned short pblock[])
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_block_statistics_init(im_A, blockStride, blockWidth, blockHeight, statBlockWidth, statBlockHeight, scratch_C, scratchSum_A, scratchSumSq_B, scratchSumSq_C, scratchSumSq_C_lo, scratchSumSq_C_hi, min_B, max_B, mean_B, variance_A, pblock);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_block_statistics_vloops(pblock);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

