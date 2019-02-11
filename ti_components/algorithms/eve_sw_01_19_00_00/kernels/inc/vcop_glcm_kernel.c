#include <vcop\vcop.h>

typedef unsigned char uchar;

#pragma DATA_SECTION(__pblock_vcop_initialize_glcm, ".vcop_parameter_block")
#pragma DATA_ALIGN(__pblock_vcop_initialize_glcm, __ALIGNOF__(int));
unsigned short __pblock_vcop_initialize_glcm[10];

unsigned int vcop_initialize_glcm_param_count(void)
{
   return 10u;
}

unsigned int vcop_initialize_glcm_ctrl_count(void)
{
   return 0u;
}

unsigned int vcop_initialize_glcm_init(
   __vptr_uint16 in_glcm_A,
   unsigned char numLevels,
   unsigned char numCopies,
   unsigned short pblock[])
{
   int __offset = 0;
   /* Loop 1 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), ((numCopies*numLevels*numLevels + (2*(8u)) - 1)/(2*(8u)))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(6), 32);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), 0);
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)in_glcm_A);
   __offset += 10;

   return 10u;
}

void vcop_initialize_glcm_vloops(
   unsigned short pblock[])
{
   /* Kernel-wide Vector Registers */
   #pragma VCC_VREG("VKe_0", 16);
   #pragma VCC_VREG("VKo_0", 17);

   __vcop_param(&pblock[0]);

   /* VLOOP 1 Start */

   /* VLOOP Local Vector Registers */
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("A0", "A0");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I1", "I4");
   

   __vcop_vloop(__vcop_compute(), 5u, 5u, 1u);
   __vcop_vinit(__vcop_sizeW(), __vcop_alws(), _PREG(8), _VREG(17));
   __vcop_vinit(__vcop_sizeW(), __vcop_alws(), _PREG(8), _VREG(16));
   __vcop_vagen(_AGEN(0), _PREG(6), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeHU(), __vcop_intrlv(), __vcop_alws(), _VPAIR(17,16), _PREG(10), _AGEN(0), _PREG(0));
   __vcop_vloop_end(1u);

}

void vcop_initialize_glcm(
   __vptr_uint16 in_glcm_A,
   unsigned char numLevels,
   unsigned char numCopies)
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_initialize_glcm_init(in_glcm_A, numLevels, numCopies, __pblock_vcop_initialize_glcm);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_initialize_glcm_vloops(__pblock_vcop_initialize_glcm);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

void vcop_initialize_glcm_custom(
   __vptr_uint16 in_glcm_A,
   unsigned char numLevels,
   unsigned char numCopies,
   unsigned short pblock[])
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_initialize_glcm_init(in_glcm_A, numLevels, numCopies, pblock);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_initialize_glcm_vloops(pblock);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

#pragma DATA_SECTION(__pblock_vcop_glcm_compute_1c, ".vcop_parameter_block")
#pragma DATA_ALIGN(__pblock_vcop_glcm_compute_1c, __ALIGNOF__(int));
unsigned short __pblock_vcop_glcm_compute_1c[272];

unsigned short __ctrl_vcop_glcm_compute_1c[2];

unsigned int vcop_glcm_compute_1c_param_count(void)
{
   return 272u;
}

unsigned int vcop_glcm_compute_1c_ctrl_count(void)
{
   return 2u;
}

unsigned int vcop_glcm_compute_1c_init(
   __vptr_uint8 inp_data_A,
   __vptr_uint16_arr scratch_index_B,
   __vptr_uint16_arr out_glcm_C,
   unsigned char numLevels,
   unsigned char numOffsets,
   unsigned char rowStart[],
   unsigned char colStart[],
   char rowOffsets[],
   char colOffsets[],
   unsigned char numRows,
   unsigned char numCols,
   unsigned short blk_wdth,
   unsigned short blk_hght,
   unsigned short blk_stride,
   unsigned short pblock[])
{
   int I0;
   int __offset = 0;
   /* Loop 1 PREGS */

   __ctrl_vcop_glcm_compute_1c[0] = numOffsets - 1;
   for (I0 = 0; I0 < numOffsets; I0++)
   {
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), (numRows)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), ((numCols + (2*(8u)) - 1)/(2*(8u)))-1u);
   __vcop_pblock_init32(pblock, __offset+_PREG(6), (uchar *)inp_data_A+(rowStart[I0]+rowOffsets[I0])*blk_stride+(colStart[I0]+colOffsets[I0]));
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)scratch_index_B[I0]);
   __vcop_pblock_init16(pblock, __offset+_PREG(10), 16);
   __vcop_pblock_init16(pblock, __offset+_PREG(11), (blk_stride*sizeof(*inp_data_A)) -((2*8u)*sizeof(*inp_data_A))*(((numCols + (2*(8u)) - 1)/(2*(8u)))-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(12), ((2*8u)*sizeof(*scratch_index_B[I0])));
   __vcop_pblock_init16(pblock, __offset+_PREG(13), ((2*((numCols+1)/2)*sizeof(*scratch_index_B[I0]))) -((2*8u)*sizeof(*scratch_index_B[I0]))*(((numCols + (2*(8u)) - 1)/(2*(8u)))-1u));
   __vcop_pblock_init32(pblock, __offset+_PREG(14), numLevels);
   __vcop_pblock_init32(pblock, __offset+_PREG(16), (uchar *)inp_data_A+rowStart[I0]*blk_stride+colStart[I0]);
   __offset += 16;
   }


   /* Loop 2 PREGS */

   __ctrl_vcop_glcm_compute_1c[1] = numOffsets - 1;
   for (I0 = 0; I0 < numOffsets; I0++)
   {
   const int preg_ref1 = _PREG(10);

   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), (numRows)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), (numCols)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(6), __vcop_store_round_sat(SM_4PARAM,preg_ref1,RM_NONE,0));
   __vcop_pblock_init16(pblock, __offset+_PREG(7), (sizeof(*scratch_index_B[I0])));
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)out_glcm_C[I0]);
   __vcop_pblock_4param_init(pblock, __offset+_PREG(10), numLevels*numLevels-1, numLevels*numLevels-1, 0, 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(14), ((2*((numCols+1)/2)*sizeof(*scratch_index_B[I0]))) -(sizeof(*scratch_index_B[I0]))*((numCols)-1u));
   __vcop_pblock_init32(pblock, __offset+_PREG(16), 1);
   __vcop_pblock_init32(pblock, __offset+_PREG(18), (uchar *)scratch_index_B[I0]);
   __offset += 18;
   }


   return 272u;
}

void vcop_glcm_compute_1c_vloops(
   unsigned short pblock[])
{
   /* Kernel-wide Vector Registers */

   __vcop_param(&pblock[0]);

   /* VLOOP 1 Start */

   /* VLOOP Local Vector Registers */
   #pragma VCC_VREG("VKnumLevels", 16);
   #pragma VCC_VREG("Vcurrent_e", 17);
   #pragma VCC_VREG("Vcurrent_o", 18);
   #pragma VCC_VREG("Vidx_e", 19);
   #pragma VCC_VREG("Vidx_o", 20);
   #pragma VCC_VREG("Vneighbor_e", 21);
   #pragma VCC_VREG("Vneighbor_o", 22);
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("A0", "A0");
   #pragma EVE_REG("A1", "A1");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I0", "I0");
   #pragma EVE_REG("I1", "I3");
   #pragma EVE_REG("I2", "I4");
   

   __vcop_rpt(__ctrl_vcop_glcm_compute_1c[0]);
   __vcop_vloop(__vcop_compute(), 11u, 8u, 1u);
   __vcop_vinit(__vcop_sizeW(), __vcop_once(), _PREG(14), _VREG(16));
   __vcop_vagen(_AGEN(0), _PREG(10), _PREG(11), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(1), _PREG(12), _PREG(13), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeBU(), __vcop_dintrlv(), _PREG(16), _AGEN(0), _VPAIR(17,18), __vcop_alws());
   __vcop_vload(__vcop_sizeBU(), __vcop_dintrlv(), _PREG(6), _AGEN(0), _VPAIR(21,22), __vcop_alws());
   __vcop_vmpy(_VREG(18), _VREG(16), _VREG(20), _PREG(0));
   __vcop_vmpy(_VREG(17), _VREG(16), _VREG(19), _PREG(0));
   __vcop_vadd(_VREG(20), _VREG(22), _VREG(20));
   __vcop_vadd(_VREG(19), _VREG(21), _VREG(19));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeHU(), __vcop_intrlv(), __vcop_alws(), _VPAIR(19,20), _PREG(8), _AGEN(1), _PREG(0));
   __vcop_vloop_end(1u);

   /* VLOOP 2 Start */

   /* VLOOP Local Vector Registers */
   #pragma VCC_VREG("Vweight", 23);
   #pragma VCC_VREG("Vdata", 24);
   #pragma VCC_VREG("Vindex", 25);
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("hist_agen", "A1");
   #pragma EVE_REG("ind_agen", "A0");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I0", "I0");
   #pragma EVE_REG("I1", "I3");
   #pragma EVE_REG("I2", "I4");
   

   __vcop_rpt(__ctrl_vcop_glcm_compute_1c[1]);
   __vcop_vloop(__vcop_histogram(), 8u, 9u, 2u);
   __vcop_vinit(__vcop_sizeW(), __vcop_once(), _PREG(16), _VREG(23));
   __vcop_vagen(_AGEN(1), _PREG(0), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(0), _PREG(7), _PREG(14), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeHU(), __vcop_npt(), _PREG(18), _AGEN(0), _VREG(25), __vcop_alws());
   __vcop_vhistload(__vcop_sizeHU(), 1, _PREG(8), _AGEN(1), _VREG(25), _VREG(24), _PREG(6), __vcop_alws());
   __vcop_hist_vadd(_VREG(24), _VREG(23), _VREG(24));
   __vcop_vhiststore(__vcop_sizeHU(), 1, __vcop_alws(), _VREG(24), _PREG(8), _AGEN(1), _VREG(25));
   __vcop_vloop_end(2u);

}

void vcop_glcm_compute_1c(
   __vptr_uint8 inp_data_A,
   __vptr_uint16_arr scratch_index_B,
   __vptr_uint16_arr out_glcm_C,
   unsigned char numLevels,
   unsigned char numOffsets,
   unsigned char rowStart[],
   unsigned char colStart[],
   char rowOffsets[],
   char colOffsets[],
   unsigned char numRows,
   unsigned char numCols,
   unsigned short blk_wdth,
   unsigned short blk_hght,
   unsigned short blk_stride)
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_glcm_compute_1c_init(inp_data_A, scratch_index_B, out_glcm_C, numLevels, numOffsets, rowStart, colStart, rowOffsets, colOffsets, numRows, numCols, blk_wdth, blk_hght, blk_stride, __pblock_vcop_glcm_compute_1c);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_glcm_compute_1c_vloops(__pblock_vcop_glcm_compute_1c);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

void vcop_glcm_compute_1c_custom(
   __vptr_uint8 inp_data_A,
   __vptr_uint16_arr scratch_index_B,
   __vptr_uint16_arr out_glcm_C,
   unsigned char numLevels,
   unsigned char numOffsets,
   unsigned char rowStart[],
   unsigned char colStart[],
   char rowOffsets[],
   char colOffsets[],
   unsigned char numRows,
   unsigned char numCols,
   unsigned short blk_wdth,
   unsigned short blk_hght,
   unsigned short blk_stride,
   unsigned short pblock[])
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_glcm_compute_1c_init(inp_data_A, scratch_index_B, out_glcm_C, numLevels, numOffsets, rowStart, colStart, rowOffsets, colOffsets, numRows, numCols, blk_wdth, blk_hght, blk_stride, pblock);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_glcm_compute_1c_vloops(pblock);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

#pragma DATA_SECTION(__pblock_vcop_glcm_compute_8c, ".vcop_parameter_block")
#pragma DATA_ALIGN(__pblock_vcop_glcm_compute_8c, __ALIGNOF__(int));
unsigned short __pblock_vcop_glcm_compute_8c[400];

unsigned short __ctrl_vcop_glcm_compute_8c[3];

unsigned int vcop_glcm_compute_8c_param_count(void)
{
   return 400u;
}

unsigned int vcop_glcm_compute_8c_ctrl_count(void)
{
   return 3u;
}

unsigned int vcop_glcm_compute_8c_init(
   __vptr_uint8 inp_data_A,
   __vptr_uint16_arr scratch_index_B,
   __vptr_uint16_arr out_glcm_C,
   __vptr_uint8 wgt_delta_A,
   unsigned char numLevels,
   unsigned char numOffsets,
   unsigned char rowStart[],
   unsigned char colStart[],
   char rowOffsets[],
   char colOffsets[],
   unsigned char numRows,
   unsigned char numCols,
   unsigned short blk_wdth,
   unsigned short blk_hght,
   unsigned short blk_stride,
   unsigned short pblock[])
{
   int I0;
   int __offset = 0;
   /* Loop 1 PREGS */

   __ctrl_vcop_glcm_compute_8c[0] = numOffsets - 1;
   for (I0 = 0; I0 < numOffsets; I0++)
   {
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), (numRows)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), ((numCols + (2*(8u)) -1)/(2*(8u)))-1u);
   __vcop_pblock_init32(pblock, __offset+_PREG(6), (uchar *)inp_data_A+(rowStart[I0]+rowOffsets[I0])*blk_stride+(colStart[I0]+colOffsets[I0]));
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)scratch_index_B[I0]);
   __vcop_pblock_init16(pblock, __offset+_PREG(10), 16);
   __vcop_pblock_init16(pblock, __offset+_PREG(11), (blk_stride*sizeof(*inp_data_A)) -((2*8u)*sizeof(*inp_data_A))*(((numCols + (2*(8u)) -1)/(2*(8u)))-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(12), ((2*8u)*sizeof(*scratch_index_B[I0])));
   __vcop_pblock_init16(pblock, __offset+_PREG(13), ((2*((numCols+1)/2)*sizeof(*scratch_index_B[I0]))) -((2*8u)*sizeof(*scratch_index_B[I0]))*(((numCols + (2*(8u)) -1)/(2*(8u)))-1u));
   __vcop_pblock_init32(pblock, __offset+_PREG(14), numLevels);
   __vcop_pblock_init32(pblock, __offset+_PREG(16), (uchar *)inp_data_A+rowStart[I0]*blk_stride+colStart[I0]);
   __offset += 16;
   }


   /* Loop 2 PREGS */

   __ctrl_vcop_glcm_compute_8c[1] = numOffsets - 1;
   for (I0 = 0; I0 < numOffsets; I0++)
   {
   const int preg_ref2 = _PREG(10);

   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), (numRows)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), (((8)*((numCols-1)/(8)))/(8))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(6), __vcop_store_round_sat(SM_4PARAM,preg_ref2,RM_NONE,0));
   __vcop_pblock_init16(pblock, __offset+_PREG(7), ((8*sizeof(*scratch_index_B[I0]))));
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)out_glcm_C[I0]);
   __vcop_pblock_4param_init(pblock, __offset+_PREG(10), numLevels*numLevels-1, numLevels*numLevels-1, 0, 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(14), ((2*((numCols+1)/2)*sizeof(*scratch_index_B[I0]))) -((8*sizeof(*scratch_index_B[I0])))*((((8)*((numCols-1)/(8)))/(8))-1u));
   __vcop_pblock_init32(pblock, __offset+_PREG(16), 1);
   __vcop_pblock_init32(pblock, __offset+_PREG(18), (uchar *)scratch_index_B[I0]);
   __offset += 18;
   }


   /* Loop 3 PREGS */

   __ctrl_vcop_glcm_compute_8c[2] = numOffsets - 1;
   for (I0 = 0; I0 < numOffsets; I0++)
   {
   const int preg_ref3 = _PREG(10);

   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), (numRows)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(6), __vcop_store_round_sat(SM_4PARAM,preg_ref3,RM_NONE,0));
   __vcop_pblock_init16(pblock, __offset+_PREG(7), ((2*((numCols+1)/2)*sizeof(*scratch_index_B[I0]))));
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)out_glcm_C[I0]);
   __vcop_pblock_4param_init(pblock, __offset+_PREG(10), numLevels*numLevels-1, numLevels*numLevels-1, 0, 0);
   __vcop_pblock_init32(pblock, __offset+_PREG(14), (uchar *)scratch_index_B[I0]+8*((numCols-1)/8)*sizeof(*scratch_index_B[I0]));
   __vcop_pblock_init32(pblock, __offset+_PREG(16), (uchar *)wgt_delta_A);
   __offset += 16;
   }


   return 400u;
}

void vcop_glcm_compute_8c_vloops(
   unsigned short pblock[])
{
   /* Kernel-wide Vector Registers */

   __vcop_param(&pblock[0]);

   /* VLOOP 1 Start */

   /* VLOOP Local Vector Registers */
   #pragma VCC_VREG("VKnumLevels", 16);
   #pragma VCC_VREG("Vcurrent_e", 17);
   #pragma VCC_VREG("Vcurrent_o", 18);
   #pragma VCC_VREG("Vidx_e", 19);
   #pragma VCC_VREG("Vidx_o", 20);
   #pragma VCC_VREG("Vneighbor_e", 21);
   #pragma VCC_VREG("Vneighbor_o", 22);
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("A0", "A0");
   #pragma EVE_REG("A1", "A1");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I0", "I0");
   #pragma EVE_REG("I1", "I3");
   #pragma EVE_REG("I2", "I4");
   

   __vcop_rpt(__ctrl_vcop_glcm_compute_8c[0]);
   __vcop_vloop(__vcop_compute(), 11u, 8u, 1u);
   __vcop_vinit(__vcop_sizeW(), __vcop_once(), _PREG(14), _VREG(16));
   __vcop_vagen(_AGEN(0), _PREG(10), _PREG(11), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(1), _PREG(12), _PREG(13), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeBU(), __vcop_dintrlv(), _PREG(16), _AGEN(0), _VPAIR(17,18), __vcop_alws());
   __vcop_vload(__vcop_sizeBU(), __vcop_dintrlv(), _PREG(6), _AGEN(0), _VPAIR(21,22), __vcop_alws());
   __vcop_vmpy(_VREG(18), _VREG(16), _VREG(20), _PREG(0));
   __vcop_vmpy(_VREG(17), _VREG(16), _VREG(19), _PREG(0));
   __vcop_vadd(_VREG(20), _VREG(22), _VREG(20));
   __vcop_vadd(_VREG(19), _VREG(21), _VREG(19));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeHU(), __vcop_intrlv(), __vcop_alws(), _VPAIR(19,20), _PREG(8), _AGEN(1), _PREG(0));
   __vcop_vloop_end(1u);

   /* VLOOP 2 Start */

   /* VLOOP Local Vector Registers */
   #pragma VCC_VREG("Vweight", 23);
   #pragma VCC_VREG("Vdata", 24);
   #pragma VCC_VREG("Vindex", 25);
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("hist_agen", "A1");
   #pragma EVE_REG("ind_agen", "A0");
   #pragma EVE_REG("wgt_agen", "A3");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I0", "I0");
   #pragma EVE_REG("I1", "I3");
   #pragma EVE_REG("I2", "I4");
   

   __vcop_rpt(__ctrl_vcop_glcm_compute_8c[1]);
   __vcop_vloop(__vcop_histogram(), 9u, 9u, 2u);
   __vcop_vinit(__vcop_sizeW(), __vcop_once(), _PREG(16), _VREG(23));
   __vcop_vagen(_AGEN(1), _PREG(0), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(0), _PREG(7), _PREG(14), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeHU(), __vcop_npt(), _PREG(18), _AGEN(0), _VREG(25), __vcop_alws());
   __vcop_vhistload(__vcop_sizeHU(), 8, _PREG(8), _AGEN(1), _VREG(25), _VREG(24), _PREG(6), __vcop_alws());
   __vcop_hist_vadd(_VREG(24), _VREG(23), _VREG(24));
   __vcop_vhiststore(__vcop_sizeHU(), 8, __vcop_alws(), _VREG(24), _PREG(8), _AGEN(1), _VREG(25));
   __vcop_vloop_end(2u);

   /* VLOOP 3 Start */

   /* VLOOP Local Vector Registers */
   #pragma VCC_VREG("Vweight", 26);
   #pragma VCC_VREG("Vdata", 27);
   #pragma VCC_VREG("Vindex", 28);
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("hist_agen", "A1");
   #pragma EVE_REG("ind_agen", "A0");
   #pragma EVE_REG("wgt_agen", "A2");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I0", "I0");
   #pragma EVE_REG("I1", "I4");
   

   __vcop_rpt(__ctrl_vcop_glcm_compute_8c[2]);
   __vcop_vloop(__vcop_histogram(), 9u, 8u, 3u);
   __vcop_vagen(_AGEN(1), _PREG(0), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(0), _PREG(7), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(2), _PREG(0), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeHU(), __vcop_npt(), _PREG(14), _AGEN(0), _VREG(28), __vcop_alws());
   __vcop_vload(__vcop_sizeBU(), __vcop_npt(), _PREG(16), _AGEN(2), _VREG(26), __vcop_alws());
   __vcop_vhistload(__vcop_sizeHU(), 8, _PREG(8), _AGEN(1), _VREG(28), _VREG(27), _PREG(6), __vcop_alws());
   __vcop_hist_vadd(_VREG(27), _VREG(26), _VREG(27));
   __vcop_vhiststore(__vcop_sizeHU(), 8, __vcop_alws(), _VREG(27), _PREG(8), _AGEN(1), _VREG(28));
   __vcop_vloop_end(3u);

}

void vcop_glcm_compute_8c(
   __vptr_uint8 inp_data_A,
   __vptr_uint16_arr scratch_index_B,
   __vptr_uint16_arr out_glcm_C,
   __vptr_uint8 wgt_delta_A,
   unsigned char numLevels,
   unsigned char numOffsets,
   unsigned char rowStart[],
   unsigned char colStart[],
   char rowOffsets[],
   char colOffsets[],
   unsigned char numRows,
   unsigned char numCols,
   unsigned short blk_wdth,
   unsigned short blk_hght,
   unsigned short blk_stride)
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_glcm_compute_8c_init(inp_data_A, scratch_index_B, out_glcm_C, wgt_delta_A, numLevels, numOffsets, rowStart, colStart, rowOffsets, colOffsets, numRows, numCols, blk_wdth, blk_hght, blk_stride, __pblock_vcop_glcm_compute_8c);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_glcm_compute_8c_vloops(__pblock_vcop_glcm_compute_8c);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

void vcop_glcm_compute_8c_custom(
   __vptr_uint8 inp_data_A,
   __vptr_uint16_arr scratch_index_B,
   __vptr_uint16_arr out_glcm_C,
   __vptr_uint8 wgt_delta_A,
   unsigned char numLevels,
   unsigned char numOffsets,
   unsigned char rowStart[],
   unsigned char colStart[],
   char rowOffsets[],
   char colOffsets[],
   unsigned char numRows,
   unsigned char numCols,
   unsigned short blk_wdth,
   unsigned short blk_hght,
   unsigned short blk_stride,
   unsigned short pblock[])
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_glcm_compute_8c_init(inp_data_A, scratch_index_B, out_glcm_C, wgt_delta_A, numLevels, numOffsets, rowStart, colStart, rowOffsets, colOffsets, numRows, numCols, blk_wdth, blk_hght, blk_stride, pblock);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_glcm_compute_8c_vloops(pblock);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

#pragma DATA_SECTION(__pblock_vcop_accumulate_8c_glcm, ".vcop_parameter_block")
#pragma DATA_ALIGN(__pblock_vcop_accumulate_8c_glcm, __ALIGNOF__(int));
unsigned short __pblock_vcop_accumulate_8c_glcm[272];

unsigned short __ctrl_vcop_accumulate_8c_glcm[2];

unsigned int vcop_accumulate_8c_glcm_param_count(void)
{
   return 272u;
}

unsigned int vcop_accumulate_8c_glcm_ctrl_count(void)
{
   return 2u;
}

unsigned int vcop_accumulate_8c_glcm_init(
   __vptr_uint16_arr in_glcm_C,
   __vptr_uint16_arr out_glcm_C,
   __vptr_uint16_arr scratch_A,
   __vptr_uint16 scatter_offsets_B,
   unsigned char numLevels,
   unsigned char numOffsets,
   unsigned short scatter_offset,
   unsigned short pblock[])
{
   int I0;
   int __offset = 0;
   /* Loop 1 PREGS */

   __ctrl_vcop_accumulate_8c_glcm[0] = numOffsets - 1;
   for (I0 = 0; I0 < numOffsets; I0++)
   {
   const int preg_ref4 = _PREG(7);

   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), ((numLevels*numLevels + 1)/2)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), (2)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(6), __vcop_store_round_sat(SM_SYMM,preg_ref4,RM_NONE,0));
   __vcop_pblock_init16(pblock, __offset+_PREG(7), 65535);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)in_glcm_C[I0]);
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)scratch_A[I0]);
   __vcop_pblock_init16(pblock, __offset+_PREG(12), 2);
   __vcop_pblock_init16(pblock, __offset+_PREG(13), 16);
   __vcop_pblock_init32(pblock, __offset+_PREG(14), (uchar *)scatter_offsets_B);
   __vcop_pblock_init32(pblock, __offset+_PREG(16), 0);
   __offset += 16;
   }


   /* Loop 2 PREGS */

   __ctrl_vcop_accumulate_8c_glcm[1] = numOffsets - 1;
   for (I0 = 0; I0 < numOffsets; I0++)
   {
   const int preg_ref5 = _PREG(7);

   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), (((numLevels*numLevels + 1)/2 + (8u) - 1)/(8u))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), (4)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(6), __vcop_store_round_sat(SM_SYMM,preg_ref5,RM_NONE,0));
   __vcop_pblock_init16(pblock, __offset+_PREG(7), 65535);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)scratch_A[I0]+scatter_offset);
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)out_glcm_C[I0]);
   __vcop_pblock_init16(pblock, __offset+_PREG(12), 32);
   __vcop_pblock_init16(pblock, __offset+_PREG(13), (2*scatter_offset));
   __vcop_pblock_init16(pblock, __offset+_PREG(14), (2*8u) -(2*scatter_offset)*((4)-1u));
   __vcop_pblock_init32(pblock, __offset+_PREG(16), 0);
   __vcop_pblock_init32(pblock, __offset+_PREG(18), (uchar *)scratch_A[I0]);
   __offset += 18;
   }


   return 272u;
}

void vcop_accumulate_8c_glcm_vloops(
   unsigned short pblock[])
{
   /* Kernel-wide Vector Registers */

   __vcop_param(&pblock[0]);

   /* VLOOP 1 Start */

   /* VLOOP Local Vector Registers */
   #pragma VCC_VREG("Voffs", 16);
   #pragma VCC_VREG("Vacc", 17);
   #pragma VCC_VREG("Vin", 18);
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("A0", "A0");
   #pragma EVE_REG("A1", "A1");
   #pragma EVE_REG("A2", "A2");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I0", "I0");
   #pragma EVE_REG("I1", "I3");
   #pragma EVE_REG("I2", "I4");
   

   __vcop_rpt(__ctrl_vcop_accumulate_8c_glcm[0]);
   __vcop_vloop(__vcop_compute(), 9u, 8u, 1u);
   __vcop_vinit(__vcop_sizeW(), __vcop_i4_zero(), _PREG(16), _VREG(17));
   __vcop_vagen(_AGEN(0), _PREG(0), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(1), _PREG(0), _PREG(12), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(2), _PREG(13), _PREG(13), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeHU(), __vcop_npt(), _PREG(14), _AGEN(0), _VREG(16), __vcop_once());
   __vcop_vload(__vcop_sizeHU(), __vcop_npt(), _PREG(8), _AGEN(2), _VREG(18), __vcop_alws());
   __vcop_vadd(_VREG(17), _VREG(18), _VREG(17));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeHU(), __vcop_pdda(_VREG(16)), __vcop_last_i4(), _VREG(17), _PREG(10), _AGEN(1), _PREG(6));
   __vcop_vloop_end(1u);

   /* VLOOP 2 Start */

   /* VLOOP Local Vector Registers */
   #pragma VCC_VREG("Vacc1", 19);
   #pragma VCC_VREG("Vacc2", 20);
   #pragma VCC_VREG("Vin1", 21);
   #pragma VCC_VREG("Vin2", 22);
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("A1", "A0");
   #pragma EVE_REG("A2", "A1");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I0", "I0");
   #pragma EVE_REG("I1", "I3");
   #pragma EVE_REG("I2", "I4");
   

   __vcop_rpt(__ctrl_vcop_accumulate_8c_glcm[1]);
   __vcop_vloop(__vcop_compute(), 10u, 9u, 2u);
   __vcop_vinit(__vcop_sizeW(), __vcop_i4_zero(), _PREG(16), _VREG(19));
   __vcop_vinit(__vcop_sizeW(), __vcop_i4_zero(), _PREG(16), _VREG(20));
   __vcop_vagen(_AGEN(0), _PREG(0), _PREG(12), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(1), _PREG(13), _PREG(14), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeHU(), __vcop_npt(), _PREG(18), _AGEN(1), _VREG(21), __vcop_alws());
   __vcop_vload(__vcop_sizeHU(), __vcop_npt(), _PREG(8), _AGEN(1), _VREG(22), __vcop_alws());
   __vcop_vadd(_VREG(19), _VREG(21), _VREG(19));
   __vcop_vadd(_VREG(20), _VREG(22), _VREG(20));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeHU(), __vcop_intrlv(), __vcop_last_i4(), _VPAIR(19,20), _PREG(10), _AGEN(0), _PREG(6));
   __vcop_vloop_end(2u);

}

void vcop_accumulate_8c_glcm(
   __vptr_uint16_arr in_glcm_C,
   __vptr_uint16_arr out_glcm_C,
   __vptr_uint16_arr scratch_A,
   __vptr_uint16 scatter_offsets_B,
   unsigned char numLevels,
   unsigned char numOffsets,
   unsigned short scatter_offset)
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_accumulate_8c_glcm_init(in_glcm_C, out_glcm_C, scratch_A, scatter_offsets_B, numLevels, numOffsets, scatter_offset, __pblock_vcop_accumulate_8c_glcm);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_accumulate_8c_glcm_vloops(__pblock_vcop_accumulate_8c_glcm);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

void vcop_accumulate_8c_glcm_custom(
   __vptr_uint16_arr in_glcm_C,
   __vptr_uint16_arr out_glcm_C,
   __vptr_uint16_arr scratch_A,
   __vptr_uint16 scatter_offsets_B,
   unsigned char numLevels,
   unsigned char numOffsets,
   unsigned short scatter_offset,
   unsigned short pblock[])
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_accumulate_8c_glcm_init(in_glcm_C, out_glcm_C, scratch_A, scatter_offsets_B, numLevels, numOffsets, scatter_offset, pblock);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_accumulate_8c_glcm_vloops(pblock);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

