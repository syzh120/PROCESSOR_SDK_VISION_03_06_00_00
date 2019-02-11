#include <vcop\vcop.h>

typedef unsigned char uchar;

#pragma DATA_SECTION(__pblock_vcop_bhattacharyaDistance, ".vcop_parameter_block")
#pragma DATA_ALIGN(__pblock_vcop_bhattacharyaDistance, __ALIGNOF__(int));
unsigned short __pblock_vcop_bhattacharyaDistance[14];

unsigned int vcop_bhattacharyaDistance_param_count(void)
{
   return 14u;
}

unsigned int vcop_bhattacharyaDistance_ctrl_count(void)
{
   return 0u;
}

unsigned int vcop_bhattacharyaDistance_init(
   __vptr_int16 X_ptr,
   __vptr_int16 Y_ptr,
   unsigned short num,
   __vptr_int16 in1_ptr,
   unsigned short pblock[])
{
   int __offset = 0;
   /* Loop 1 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), (num/(8u))-1u);
   __vcop_pblock_init32(pblock, __offset+_PREG(6), (uchar *)Y_ptr);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)in1_ptr);
   __vcop_pblock_init16(pblock, __offset+_PREG(10), 16);
   __vcop_pblock_init32(pblock, __offset+_PREG(12), 65536/15360);
   __vcop_pblock_init32(pblock, __offset+_PREG(14), (uchar *)X_ptr);
   __offset += 14;

   return 14u;
}

void vcop_bhattacharyaDistance_vloops(
   unsigned short pblock[])
{
   /* Kernel-wide Vector Registers */
   #pragma VCC_VREG("R0", 16);
   #pragma VCC_VREG("Vin1", 17);
   #pragma VCC_VREG("Vin2", 18);
   #pragma VCC_VREG("Vin_x", 19);
   #pragma VCC_VREG("Vin_y", 20);
   #pragma VCC_VREG("Vout", 21);

   __vcop_param(&pblock[0]);

   /* VLOOP 1 Start */

   /* VLOOP Local Vector Registers */
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("Addr", "A0");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I1", "I4");
   

   __vcop_vloop(__vcop_compute(), 9u, 7u, 1u);
   __vcop_vinit(__vcop_sizeW(), __vcop_alws(), _PREG(12), _VREG(16));
   __vcop_vagen(_AGEN(0), _PREG(10), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeH(), __vcop_npt(), _PREG(14), _AGEN(0), _VREG(19), __vcop_alws());
   __vcop_vload(__vcop_sizeH(), __vcop_npt(), _PREG(6), _AGEN(0), _VREG(20), __vcop_alws());
   __vcop_vmpy(_VREG(19), _VREG(16), _VREG(17), _PREG(0));
   __vcop_vmpy(_VREG(20), _VREG(16), _VREG(18), _PREG(0));
   __vcop_vmpy(_VREG(17), _VREG(18), _VREG(21), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeH(), __vcop_npt(), __vcop_alws(), _VREG(21), _PREG(8), _AGEN(0), _PREG(0));
   __vcop_vloop_end(1u);

}

void vcop_bhattacharyaDistance(
   __vptr_int16 X_ptr,
   __vptr_int16 Y_ptr,
   unsigned short num,
   __vptr_int16 in1_ptr)
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_bhattacharyaDistance_init(X_ptr, Y_ptr, num, in1_ptr, __pblock_vcop_bhattacharyaDistance);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_bhattacharyaDistance_vloops(__pblock_vcop_bhattacharyaDistance);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

void vcop_bhattacharyaDistance_custom(
   __vptr_int16 X_ptr,
   __vptr_int16 Y_ptr,
   unsigned short num,
   __vptr_int16 in1_ptr,
   unsigned short pblock[])
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_bhattacharyaDistance_init(X_ptr, Y_ptr, num, in1_ptr, pblock);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_bhattacharyaDistance_vloops(pblock);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

#pragma DATA_SECTION(__pblock_eve_array_sqrt_intlv_lut_idx_log4, ".vcop_parameter_block")
#pragma DATA_ALIGN(__pblock_eve_array_sqrt_intlv_lut_idx_log4, __ALIGNOF__(int));
unsigned short __pblock_eve_array_sqrt_intlv_lut_idx_log4[24];

unsigned int eve_array_sqrt_intlv_lut_idx_log4_param_count(void)
{
   return 24u;
}

unsigned int eve_array_sqrt_intlv_lut_idx_log4_ctrl_count(void)
{
   return 0u;
}

unsigned int eve_array_sqrt_intlv_lut_idx_log4_init(
   __vptr_uint16 in1_ptr,
   __vptr_uint16 TLU_idx_ptr,
   __vptr_uint8 log4_ptr,
   unsigned short num_data,
   int TLU_Qbits_p1,
   int idx_norm2,
   unsigned short pblock[])
{
   int __offset = 0;
   /* Loop 1 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), (num_data/(2*(8u)))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(6), __vcop_store_round_sat(SM_NONE,0,RM_ROUND,1));
   __vcop_pblock_init16(pblock, __offset+_PREG(7), 32);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), TLU_Qbits_p1);
   __vcop_pblock_init32(pblock, __offset+_PREG(10), idx_norm2);
   __vcop_pblock_init32(pblock, __offset+_PREG(12), 2);
   __vcop_pblock_init32(pblock, __offset+_PREG(14), (uchar *)in1_ptr);
   __vcop_pblock_init32(pblock, __offset+_PREG(16), (uchar *)TLU_idx_ptr);
   __vcop_pblock_init32(pblock, __offset+_PREG(18), (uchar *)log4_ptr);
   __vcop_pblock_init16(pblock, __offset+_PREG(20), 16);
   __vcop_pblock_init32(pblock, __offset+_PREG(22), 1);
   __vcop_pblock_init32(pblock, __offset+_PREG(24), -1);
   __offset += 24;

   return 24u;
}

void eve_array_sqrt_intlv_lut_idx_log4_vloops(
   unsigned short pblock[])
{
   /* Kernel-wide Vector Registers */
   #pragma VCC_VREG("VQbits_p1", 16);
   #pragma VCC_VREG("Vidx_norm2", 17);
   #pragma VCC_VREG("Vin1", 18);
   #pragma VCC_VREG("Vin2", 19);
   #pragma VCC_VREG("Vlmbd1", 20);
   #pragma VCC_VREG("Vlmbd2", 21);
   #pragma VCC_VREG("Vlog2_1", 22);
   #pragma VCC_VREG("Vlog2_2", 23);
   #pragma VCC_VREG("Vlog4_1", 24);
   #pragma VCC_VREG("Vlog4_2", 25);
   #pragma VCC_VREG("Vlut_idx1", 26);
   #pragma VCC_VREG("Vlut_idx2", 27);
   #pragma VCC_VREG("Vmant1", 28);
   #pragma VCC_VREG("Vmant2", 29);
   #pragma VCC_VREG("Vneg_one", 30);
   #pragma VCC_VREG("Vone", 31);
   #pragma VCC_VREG("Vshft1", 32);
   #pragma VCC_VREG("Vshft2", 33);
   #pragma VCC_VREG("Vtwo", 34);

   __vcop_param(&pblock[0]);

   /* VLOOP 1 Start */

   /* VLOOP Local Vector Registers */
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("Addr1", "A0");
   #pragma EVE_REG("Addr2", "A1");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I4", "I4");
   

   __vcop_vloop(__vcop_compute(), 23u, 12u, 1u);
   __vcop_vinit(__vcop_sizeW(), __vcop_once(), _PREG(22), _VREG(31));
   __vcop_vinit(__vcop_sizeW(), __vcop_once(), _PREG(24), _VREG(30));
   __vcop_vinit(__vcop_sizeW(), __vcop_once(), _PREG(8), _VREG(16));
   __vcop_vinit(__vcop_sizeW(), __vcop_once(), _PREG(10), _VREG(17));
   __vcop_vinit(__vcop_sizeW(), __vcop_once(), _PREG(12), _VREG(34));
   __vcop_vagen(_AGEN(0), _PREG(7), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(1), _PREG(20), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeHU(), __vcop_dintrlv(), _PREG(14), _AGEN(0), _VPAIR(18,19), __vcop_alws());
   __vcop_vlmbd(_VREG(18), _VREG(31), _VREG(20));
   __vcop_vlmbd(_VREG(19), _VREG(31), _VREG(21));
   __vcop_vshf(_VREG(20), _VREG(30), _VREG(24));
   __vcop_vshf(_VREG(21), _VREG(30), _VREG(25));
   __vcop_vshf(_VREG(24), _VREG(31), _VREG(22));
   __vcop_vshf(_VREG(25), _VREG(31), _VREG(23));
   __vcop_vsub(_VREG(16), _VREG(22), _VREG(32));
   __vcop_vsub(_VREG(16), _VREG(23), _VREG(33));
   __vcop_vshf(_VREG(18), _VREG(32), _VREG(28));
   __vcop_vshf(_VREG(19), _VREG(33), _VREG(29));
   __vcop_vsub(_VREG(28), _VREG(17), _VREG(26));
   __vcop_vsub(_VREG(29), _VREG(17), _VREG(27));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeHU(), __vcop_intrlv(), __vcop_alws(), _VPAIR(26,27), _PREG(16), _AGEN(0), _PREG(6));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeBU(), __vcop_intrlv(), __vcop_alws(), _VPAIR(24,25), _PREG(18), _AGEN(1), _PREG(0));
   __vcop_vloop_end(1u);

}

void eve_array_sqrt_intlv_lut_idx_log4(
   __vptr_uint16 in1_ptr,
   __vptr_uint16 TLU_idx_ptr,
   __vptr_uint8 log4_ptr,
   unsigned short num_data,
   int TLU_Qbits_p1,
   int idx_norm2)
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   eve_array_sqrt_intlv_lut_idx_log4_init(in1_ptr, TLU_idx_ptr, log4_ptr, num_data, TLU_Qbits_p1, idx_norm2, __pblock_eve_array_sqrt_intlv_lut_idx_log4);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   eve_array_sqrt_intlv_lut_idx_log4_vloops(__pblock_eve_array_sqrt_intlv_lut_idx_log4);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

void eve_array_sqrt_intlv_lut_idx_log4_custom(
   __vptr_uint16 in1_ptr,
   __vptr_uint16 TLU_idx_ptr,
   __vptr_uint8 log4_ptr,
   unsigned short num_data,
   int TLU_Qbits_p1,
   int idx_norm2,
   unsigned short pblock[])
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   eve_array_sqrt_intlv_lut_idx_log4_init(in1_ptr, TLU_idx_ptr, log4_ptr, num_data, TLU_Qbits_p1, idx_norm2, pblock);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   eve_array_sqrt_intlv_lut_idx_log4_vloops(pblock);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

#pragma DATA_SECTION(__pblock_eve_tlu_1c_hword, ".vcop_parameter_block")
#pragma DATA_ALIGN(__pblock_eve_tlu_1c_hword, __ALIGNOF__(int));
unsigned short __pblock_eve_tlu_1c_hword[12];

unsigned int eve_tlu_1c_hword_param_count(void)
{
   return 12u;
}

unsigned int eve_tlu_1c_hword_ctrl_count(void)
{
   return 0u;
}

unsigned int eve_tlu_1c_hword_init(
   __vptr_uint16 Table,
   __vptr_uint16 inp_data,
   unsigned int blk_hght,
   unsigned int blk_wdth,
   __vptr_uint16 Out,
   unsigned short pblock[])
{
   int __offset = 0;
   /* Loop 1 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), (blk_hght)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), (blk_wdth)-1u);
   __vcop_pblock_init32(pblock, __offset+_PREG(6), (uchar *)Out);
   __vcop_pblock_init16(pblock, __offset+_PREG(8), 2);
   __vcop_pblock_init16(pblock, __offset+_PREG(9), ((blk_wdth*sizeof(*inp_data))) -(sizeof(*inp_data))*((blk_wdth)-1u));
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)inp_data);
   __vcop_pblock_init32(pblock, __offset+_PREG(12), (uchar *)Table);
   __offset += 12;

   return 12u;
}

void eve_tlu_1c_hword_vloops(
   unsigned short pblock[])
{
   /* Kernel-wide Vector Registers */
   #pragma VCC_VREG("Vdata", 16);
   #pragma VCC_VREG("Vindex", 17);
   #pragma VCC_VREG("Vout", 18);

   __vcop_param(&pblock[0]);

   /* VLOOP 1 Start */

   /* VLOOP Local Vector Registers */
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("TLU_agen", "A1");
   #pragma EVE_REG("ind_agen", "A0");
   #pragma EVE_REG("out_agen", "A2");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("i3", "I3");
   #pragma EVE_REG("i4", "I4");
   

   __vcop_vloop(__vcop_tablelkup(), 7u, 6u, 1u);
   __vcop_vagen(_AGEN(1), _PREG(0), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(0), _PREG(8), _PREG(9), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(2), _PREG(8), _PREG(9), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeHU(), __vcop_npt(), _PREG(10), _AGEN(0), _VREG(17), __vcop_alws());
   __vcop_vtbload(__vcop_sizeHU(), __vcop_tableinfo(1, 1), _PREG(12), _AGEN(1), _VREG(17), _VREG(16), _PREG(0), __vcop_alws());
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeHU(), __vcop_npt(), __vcop_alws(), _VREG(16), _PREG(6), _AGEN(2), _PREG(0));
   __vcop_vloop_end(1u);

}

void eve_tlu_1c_hword(
   __vptr_uint16 Table,
   __vptr_uint16 inp_data,
   unsigned int blk_hght,
   unsigned int blk_wdth,
   __vptr_uint16 Out)
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   eve_tlu_1c_hword_init(Table, inp_data, blk_hght, blk_wdth, Out, __pblock_eve_tlu_1c_hword);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   eve_tlu_1c_hword_vloops(__pblock_eve_tlu_1c_hword);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

void eve_tlu_1c_hword_custom(
   __vptr_uint16 Table,
   __vptr_uint16 inp_data,
   unsigned int blk_hght,
   unsigned int blk_wdth,
   __vptr_uint16 Out,
   unsigned short pblock[])
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   eve_tlu_1c_hword_init(Table, inp_data, blk_hght, blk_wdth, Out, pblock);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   eve_tlu_1c_hword_vloops(pblock);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

#pragma DATA_SECTION(__pblock_eve_array_sqrt_intlv_align, ".vcop_parameter_block")
#pragma DATA_ALIGN(__pblock_eve_array_sqrt_intlv_align, __ALIGNOF__(int));
unsigned short __pblock_eve_array_sqrt_intlv_align[14];

unsigned int eve_array_sqrt_intlv_align_param_count(void)
{
   return 14u;
}

unsigned int eve_array_sqrt_intlv_align_ctrl_count(void)
{
   return 0u;
}

unsigned int eve_array_sqrt_intlv_align_init(
   __vptr_uint16 in1_ptr,
   __vptr_uint8 log4_ptr,
   unsigned short num_data,
   __vptr_uint32 out_ptr,
   unsigned short pblock[])
{
   int __offset = 0;
   /* Loop 1 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), (num_data/(8u))-1u);
   __vcop_pblock_init32(pblock, __offset+_PREG(6), (uchar *)out_ptr);
   __vcop_pblock_init16(pblock, __offset+_PREG(8), 16);
   __vcop_pblock_init16(pblock, __offset+_PREG(9), 8);
   __vcop_pblock_init16(pblock, __offset+_PREG(10), 32);
   __vcop_pblock_init32(pblock, __offset+_PREG(12), (uchar *)in1_ptr);
   __vcop_pblock_init32(pblock, __offset+_PREG(14), (uchar *)log4_ptr);
   __offset += 14;

   return 14u;
}

void eve_array_sqrt_intlv_align_vloops(
   unsigned short pblock[])
{
   /* Kernel-wide Vector Registers */
   #pragma VCC_VREG("Vin", 16);
   #pragma VCC_VREG("Vlog4", 17);
   #pragma VCC_VREG("Vout", 18);
   #pragma VCC_VREG("Vout1", 19);

   __vcop_param(&pblock[0]);

   /* VLOOP 1 Start */

   /* VLOOP Local Vector Registers */
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("Addr1", "A0");
   #pragma EVE_REG("Addr2", "A1");
   #pragma EVE_REG("Addr3", "A2");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I4", "I4");
   

   __vcop_vloop(__vcop_compute(), 8u, 7u, 1u);
   __vcop_vagen(_AGEN(0), _PREG(8), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(1), _PREG(9), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(2), _PREG(10), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeHU(), __vcop_npt(), _PREG(12), _AGEN(0), _VREG(16), __vcop_alws());
   __vcop_vload(__vcop_sizeBU(), __vcop_npt(), _PREG(14), _AGEN(1), _VREG(17), __vcop_alws());
   __vcop_vshf(_VREG(16), _VREG(17), _VREG(18));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeWU(), __vcop_npt(), __vcop_alws(), _VREG(18), _PREG(6), _AGEN(2), _PREG(0));
   __vcop_vloop_end(1u);

}

void eve_array_sqrt_intlv_align(
   __vptr_uint16 in1_ptr,
   __vptr_uint8 log4_ptr,
   unsigned short num_data,
   __vptr_uint32 out_ptr)
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   eve_array_sqrt_intlv_align_init(in1_ptr, log4_ptr, num_data, out_ptr, __pblock_eve_array_sqrt_intlv_align);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   eve_array_sqrt_intlv_align_vloops(__pblock_eve_array_sqrt_intlv_align);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

void eve_array_sqrt_intlv_align_custom(
   __vptr_uint16 in1_ptr,
   __vptr_uint8 log4_ptr,
   unsigned short num_data,
   __vptr_uint32 out_ptr,
   unsigned short pblock[])
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   eve_array_sqrt_intlv_align_init(in1_ptr, log4_ptr, num_data, out_ptr, pblock);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   eve_array_sqrt_intlv_align_vloops(pblock);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

