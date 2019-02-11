#include <vcop\vcop.h>

typedef unsigned char uchar;

#pragma DATA_SECTION(__pblock_vcop_fast9_score_kernel, ".vcop_parameter_block")
#pragma DATA_ALIGN(__pblock_vcop_fast9_score_kernel, __ALIGNOF__(int));
unsigned short __pblock_vcop_fast9_score_kernel[80];

unsigned int vcop_fast9_score_kernel_param_count(void)
{
   return 80u;
}

unsigned int vcop_fast9_score_kernel_ctrl_count(void)
{
   return 0u;
}

unsigned int vcop_fast9_score_kernel_init(
   __vptr_uint32 pIn,
   __vptr_uint32 pTemp_buf,
   __vptr_uint32 pTemp,
   __vptr_uint8 pTemp1,
   unsigned int nFeatures,
   signed char Thr,
   __vptr_uint8 Index,
   __vptr_uint8 Offset_Out,
   __vptr_uint16 BScore,
   __vptr_uint16 DScore,
   __vptr_uint16 Score,
   __vptr_uint32 updateOutPtr,
   unsigned short pblock[])
{
   int __offset = 0;
   /* Loop 1 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), ((nFeatures+(8u)-1)/(8u))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), (8)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), (2)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(6), 32);
   __vcop_pblock_init16(pblock, __offset+_PREG(7), 288);
   __vcop_pblock_init16(pblock, __offset+_PREG(8), -284);
   __vcop_pblock_init16(pblock, __offset+_PREG(9), 260);
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)pIn);
   __vcop_pblock_init32(pblock, __offset+_PREG(12), (uchar *)pTemp_buf);
   __offset += 12;

   /* Loop 2 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), ((nFeatures+(8u)-1)/(8u))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), (16)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(6), 36);
   __vcop_pblock_init16(pblock, __offset+_PREG(7), 32);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)pTemp_buf);
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)pTemp);
   __offset += 10;

   /* Loop 3 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), ((nFeatures+(8u)-1)/(8u))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), (17)-1u);
   __vcop_pblock_init32(pblock, __offset+_PREG(6), (uchar *)Offset_Out);
   __vcop_pblock_init16(pblock, __offset+_PREG(8), 8);
   __vcop_pblock_init16(pblock, __offset+_PREG(9), -128);
   __vcop_pblock_init16(pblock, __offset+_PREG(10), 512);
   __vcop_pblock_init32(pblock, __offset+_PREG(12), (uchar *)Index);
   __vcop_pblock_init32(pblock, __offset+_PREG(14), (uchar *)pTemp1);
   __offset += 14;

   /* Loop 4 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), ((nFeatures+(8u)-1)/(8u))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), (4)-1u);
   __vcop_pblock_init32(pblock, __offset+_PREG(6), 0);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)Offset_Out+8u*16);
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)Offset_Out);
   __vcop_pblock_init32(pblock, __offset+_PREG(12), (uchar *)Offset_Out+8u*sizeof(*pTemp1));
   __vcop_pblock_init32(pblock, __offset+_PREG(14), (uchar *)Offset_Out+2*8u*sizeof(*pTemp1));
   __vcop_pblock_init32(pblock, __offset+_PREG(16), (uchar *)Offset_Out+3*8u*sizeof(*pTemp1));
   __vcop_pblock_init32(pblock, __offset+_PREG(18), (uchar *)BScore);
   __vcop_pblock_init32(pblock, __offset+_PREG(20), (uchar *)DScore);
   __vcop_pblock_init16(pblock, __offset+_PREG(22), 136);
   __vcop_pblock_init16(pblock, __offset+_PREG(23), 16);
   __vcop_pblock_init16(pblock, __offset+_PREG(24), 32);
   __vcop_pblock_init16(pblock, __offset+_PREG(25), 40);
   __vcop_pblock_init32(pblock, __offset+_PREG(26), Thr);
   __vcop_pblock_init32(pblock, __offset+_PREG(28), -Thr);
   __offset += 28;

   /* Loop 5 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), (1)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), ((nFeatures+2*(8u)-1)/(2*(8u)))-1u);
   __vcop_pblock_init32(pblock, __offset+_PREG(6), (uchar *)BScore);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)DScore);
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)Score);
   __vcop_pblock_init16(pblock, __offset+_PREG(12), 32);
   __vcop_pblock_init16(pblock, __offset+_PREG(13),  -(2*8u*sizeof(*BScore))*(((nFeatures+2*(8u)-1)/(2*(8u)))-1u));
   __vcop_pblock_init32(pblock, __offset+_PREG(14), nFeatures*2);
   __vcop_pblock_init32(pblock, __offset+_PREG(16), (uchar *)updateOutPtr+144);
   __offset += 16;

   return 80u;
}

void vcop_fast9_score_kernel_vloops(
   unsigned short pblock[])
{
   /* Kernel-wide Vector Registers */
   #pragma VCC_VREG("Vnt", 16);
   #pragma VCC_VREG("Vt", 17);
   #pragma VCC_VREG("Vzero", 18);

   __vcop_param(&pblock[0]);

   /* VLOOP 1 Start */

   /* VLOOP Local Vector Registers */
   #pragma VCC_VREG("Vin1", 19);
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("Addr1", "A0");
   #pragma EVE_REG("Addr2", "A1");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I1", "I2");
   #pragma EVE_REG("I2", "I3");
   #pragma EVE_REG("I3", "I4");
   

   __vcop_vloop(__vcop_compute(), 5u, 6u, 1u);
   __vcop_vagen(_AGEN(0), _PREG(6), _PREG(6), _PREG(6), _PREG(0));
   __vcop_vagen(_AGEN(1), _PREG(7), _PREG(8), _PREG(9), _PREG(0));
   __vcop_vload(__vcop_sizeWU(), __vcop_npt(), _PREG(10), _AGEN(0), _VREG(19), __vcop_alws());
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeWU(), __vcop_offst_np1(), __vcop_alws(), _VREG(19), _PREG(12), _AGEN(1), _PREG(0));
   __vcop_vloop_end(1u);

   /* VLOOP 2 Start */

   /* VLOOP Local Vector Registers */
   #pragma VCC_VREG("Vin1", 20);
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("Addr1", "A0");
   #pragma EVE_REG("Addr2", "A1");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I2", "I3");
   #pragma EVE_REG("I3", "I4");
   

   __vcop_vloop(__vcop_compute(), 5u, 5u, 2u);
   __vcop_vagen(_AGEN(0), _PREG(6), _PREG(6), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(1), _PREG(7), _PREG(7), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeWU(), __vcop_npt(), _PREG(8), _AGEN(0), _VREG(20), __vcop_alws());
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeWU(), __vcop_npt(), __vcop_alws(), _VREG(20), _PREG(10), _AGEN(1), _PREG(0));
   __vcop_vloop_end(2u);

   /* VLOOP 3 Start */

   /* VLOOP Local Vector Registers */
   #pragma VCC_VREG("Vindex", 21);
   #pragma VCC_VREG("Vtabledata", 22);
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("index_addr", "A0");
   #pragma EVE_REG("out_addr", "A2");
   #pragma EVE_REG("table_addr", "A1");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I3", "I3");
   #pragma EVE_REG("I4", "I4");
   

   __vcop_vloop(__vcop_tablelkup(), 7u, 7u, 3u);
   __vcop_vagen(_AGEN(0), _PREG(8), _PREG(9), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(2), _PREG(8), _PREG(8), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(1), _PREG(0), _PREG(10), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeBU(), __vcop_npt(), _PREG(12), _AGEN(0), _VREG(21), __vcop_alws());
   __vcop_vtbload(__vcop_sizeBU(), __vcop_tableinfo(8, 1), _PREG(14), _AGEN(1), _VREG(21), _VREG(22), _PREG(0), __vcop_alws());
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeBU(), __vcop_npt(), __vcop_alws(), _VREG(22), _PREG(6), _AGEN(2), _PREG(0));
   __vcop_vloop_end(3u);

   /* VLOOP 4 Start */

   /* VLOOP Local Vector Registers */
   #pragma VCC_VREG("Score_b", 23);
   #pragma VCC_VREG("Score_d", 24);
   #pragma VCC_VREG("Vin0", 25);
   #pragma VCC_VREG("Vin1", 26);
   #pragma VCC_VREG("Vin2", 27);
   #pragma VCC_VREG("Vin3", 28);
   #pragma VCC_VREG("Vin4", 29);
   #pragma VCC_VREG("Vnt0", 30);
   #pragma VCC_VREG("Vnt1", 31);
   #pragma VCC_VREG("Vout00", 32);
   #pragma VCC_VREG("Vout01", 33);
   #pragma VCC_VREG("Vout10", 34);
   #pragma VCC_VREG("Vout11", 35);
   #pragma VCC_VREG("Vt0", 36);
   #pragma VCC_VREG("Vt1", 37);
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("addr1", "A0");
   #pragma EVE_REG("addr_out", "A1");
   #pragma EVE_REG("addr2", "A2");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I3", "I3");
   #pragma EVE_REG("I4", "I4");
   

   __vcop_vloop(__vcop_compute(), 40u, 14u, 4u);
   __vcop_vinit(__vcop_sizeW(), __vcop_once(), _PREG(26), _VREG(17));
   __vcop_vinit(__vcop_sizeW(), __vcop_once(), _PREG(28), _VREG(16));
   __vcop_vinit(__vcop_sizeW(), __vcop_once(), _PREG(6), _VREG(18));
   __vcop_vinit(__vcop_sizeW(), __vcop_i4_zero(), _PREG(6), _VREG(23));
   __vcop_vinit(__vcop_sizeW(), __vcop_i4_zero(), _PREG(6), _VREG(24));
   __vcop_vagen(_AGEN(0), _PREG(0), _PREG(22), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(1), _PREG(0), _PREG(23), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(2), _PREG(24), _PREG(25), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeBU(), __vcop_npt(), _PREG(8), _AGEN(0), _VREG(25), __vcop_i4_zero());
   __vcop_vload(__vcop_sizeBU(), __vcop_npt(), _PREG(10), _AGEN(2), _VREG(26), __vcop_alws());
   __vcop_vload(__vcop_sizeBU(), __vcop_npt(), _PREG(12), _AGEN(2), _VREG(27), __vcop_alws());
   __vcop_vload(__vcop_sizeBU(), __vcop_npt(), _PREG(14), _AGEN(2), _VREG(28), __vcop_alws());
   __vcop_vload(__vcop_sizeBU(), __vcop_npt(), _PREG(16), _AGEN(2), _VREG(29), __vcop_alws());
   __vcop_vsub(_VREG(25), _VREG(26), _VREG(36));
   __vcop_vsub(_VREG(25), _VREG(27), _VREG(37));
   __vcop_vsub(_VREG(18), _VREG(36), _VREG(30));
   __vcop_vsub(_VREG(18), _VREG(37), _VREG(31));
   __vcop_vcmpge(_VREG(36), _VREG(17), _VREG(32));
   __vcop_vcmpge(_VREG(16), _VREG(36), _VREG(34));
   __vcop_vcmpge(_VREG(37), _VREG(17), _VREG(33));
   __vcop_vcmpge(_VREG(16), _VREG(37), _VREG(35));
   __vcop_vmadd(_VREG(32), _VREG(36), _VREG(23), _PREG(0));
   __vcop_vmadd(_VREG(34), _VREG(30), _VREG(24), _PREG(0));
   __vcop_vmadd(_VREG(33), _VREG(37), _VREG(23), _PREG(0));
   __vcop_vmadd(_VREG(35), _VREG(31), _VREG(24), _PREG(0));
   __vcop_vsub(_VREG(25), _VREG(28), _VREG(36));
   __vcop_vsub(_VREG(25), _VREG(29), _VREG(37));
   __vcop_vsub(_VREG(18), _VREG(36), _VREG(30));
   __vcop_vsub(_VREG(18), _VREG(37), _VREG(31));
   __vcop_vcmpge(_VREG(36), _VREG(17), _VREG(32));
   __vcop_vcmpge(_VREG(16), _VREG(36), _VREG(34));
   __vcop_vcmpge(_VREG(37), _VREG(17), _VREG(33));
   __vcop_vcmpge(_VREG(16), _VREG(37), _VREG(35));
   __vcop_vmadd(_VREG(32), _VREG(36), _VREG(23), _PREG(0));
   __vcop_vmadd(_VREG(34), _VREG(30), _VREG(24), _PREG(0));
   __vcop_vmadd(_VREG(33), _VREG(37), _VREG(23), _PREG(0));
   __vcop_vmadd(_VREG(35), _VREG(31), _VREG(24), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeHU(), __vcop_npt(), __vcop_last_i4(), _VREG(23), _PREG(18), _AGEN(1), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeHU(), __vcop_npt(), __vcop_last_i4(), _VREG(24), _PREG(20), _AGEN(1), _PREG(0));
   __vcop_vloop_end(4u);

   /* VLOOP 5 Start */

   /* VLOOP Local Vector Registers */
   #pragma VCC_VREG("OutIncr", 38);
   #pragma VCC_VREG("num", 39);
   #pragma VCC_VREG("offset", 40);
   #pragma VCC_VREG("Vin0", 41);
   #pragma VCC_VREG("Vin1", 42);
   #pragma VCC_VREG("Vin2", 43);
   #pragma VCC_VREG("Vin3", 44);
   #pragma VCC_VREG("Vout00", 45);
   #pragma VCC_VREG("Vout01", 46);
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("Addr0", "A0");
   #pragma EVE_REG("addr1", "A1");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I3", "I3");
   #pragma EVE_REG("I4", "I4");
   

   __vcop_vloop(__vcop_compute(), 12u, 8u, 5u);
   __vcop_vinit(__vcop_sizeW(), __vcop_i4_zero(), _PREG(14), _VREG(39));
   __vcop_vagen(_AGEN(0), _PREG(0), _PREG(1), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(1), _PREG(12), _PREG(13), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeWU(), __vcop_1pt(), _PREG(16), _AGEN(0), _VREG(40), __vcop_i4_zero());
   __vcop_vload(__vcop_sizeHU(), __vcop_dintrlv(), _PREG(6), _AGEN(1), _VPAIR(41,43), __vcop_alws());
   __vcop_vload(__vcop_sizeHU(), __vcop_dintrlv(), _PREG(8), _AGEN(1), _VPAIR(42,44), __vcop_alws());
   __vcop_vmax(_VREG(41), _VREG(42), _VREG(45));
   __vcop_vmax(_VREG(43), _VREG(44), _VREG(46));
   __vcop_vadd(_VREG(40), _VREG(39), _VREG(38));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeHU(), __vcop_intrlv(), __vcop_alws(), _VPAIR(45,46), _PREG(10), _AGEN(1), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeWU(), __vcop_1pt(), __vcop_last_i4(), _VREG(38), _PREG(16), _AGEN(0), _PREG(0));
   __vcop_vloop_end(5u);

}

void vcop_fast9_score_kernel(
   __vptr_uint32 pIn,
   __vptr_uint32 pTemp_buf,
   __vptr_uint32 pTemp,
   __vptr_uint8 pTemp1,
   unsigned int nFeatures,
   signed char Thr,
   __vptr_uint8 Index,
   __vptr_uint8 Offset_Out,
   __vptr_uint16 BScore,
   __vptr_uint16 DScore,
   __vptr_uint16 Score,
   __vptr_uint32 updateOutPtr)
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_fast9_score_kernel_init(pIn, pTemp_buf, pTemp, pTemp1, nFeatures, Thr, Index, Offset_Out, BScore, DScore, Score, updateOutPtr, __pblock_vcop_fast9_score_kernel);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_fast9_score_kernel_vloops(__pblock_vcop_fast9_score_kernel);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

void vcop_fast9_score_kernel_custom(
   __vptr_uint32 pIn,
   __vptr_uint32 pTemp_buf,
   __vptr_uint32 pTemp,
   __vptr_uint8 pTemp1,
   unsigned int nFeatures,
   signed char Thr,
   __vptr_uint8 Index,
   __vptr_uint8 Offset_Out,
   __vptr_uint16 BScore,
   __vptr_uint16 DScore,
   __vptr_uint16 Score,
   __vptr_uint32 updateOutPtr,
   unsigned short pblock[])
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_fast9_score_kernel_init(pIn, pTemp_buf, pTemp, pTemp1, nFeatures, Thr, Index, Offset_Out, BScore, DScore, Score, updateOutPtr, pblock);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_fast9_score_kernel_vloops(pblock);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

#pragma DATA_SECTION(__pblock_vcop_fast9_thresh_score, ".vcop_parameter_block")
#pragma DATA_ALIGN(__pblock_vcop_fast9_thresh_score, __ALIGNOF__(int));
unsigned short __pblock_vcop_fast9_thresh_score[104];

unsigned int vcop_fast9_thresh_score_param_count(void)
{
   return 104u;
}

unsigned int vcop_fast9_thresh_score_ctrl_count(void)
{
   return 0u;
}

unsigned int vcop_fast9_thresh_score_init(
   __vptr_uint32 pIn,
   __vptr_uint32 pTemp_buf,
   __vptr_uint32 pTemp,
   __vptr_uint8 pTemp1,
   unsigned int nFeatures,
   signed char Thr,
   __vptr_uint8 Index,
   __vptr_uint8 Offset_Out,
   __vptr_uint8 BScore,
   __vptr_uint8 DScore,
   __vptr_uint16 Score_B,
   __vptr_uint16 Score_D,
   __vptr_uint16 Score,
   __vptr_uint32 updateOutPtr,
   unsigned short pblock[])
{
   int __offset = 0;
   /* Loop 1 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), ((nFeatures+(8u)-1)/(8u))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), (8)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), (2)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(6), 32);
   __vcop_pblock_init16(pblock, __offset+_PREG(7), 288);
   __vcop_pblock_init16(pblock, __offset+_PREG(8), -284);
   __vcop_pblock_init16(pblock, __offset+_PREG(9), 260);
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)pIn);
   __vcop_pblock_init32(pblock, __offset+_PREG(12), (uchar *)pTemp_buf);
   __offset += 12;

   /* Loop 2 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), ((nFeatures+(8u)-1)/(8u))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), (16)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(6), 36);
   __vcop_pblock_init16(pblock, __offset+_PREG(7), 32);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)pTemp_buf);
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)pTemp);
   __offset += 10;

   /* Loop 3 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), ((nFeatures+(8u)-1)/(8u))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), (25)-1u);
   __vcop_pblock_init32(pblock, __offset+_PREG(6), (uchar *)Offset_Out);
   __vcop_pblock_init16(pblock, __offset+_PREG(8), 8);
   __vcop_pblock_init16(pblock, __offset+_PREG(9), -192);
   __vcop_pblock_init16(pblock, __offset+_PREG(10), 512);
   __vcop_pblock_init32(pblock, __offset+_PREG(12), (uchar *)Index);
   __vcop_pblock_init32(pblock, __offset+_PREG(14), (uchar *)pTemp1);
   __offset += 14;

   /* Loop 4 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), ((nFeatures+(8u)-1)/(8u))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), (16)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), (8)-1u);
   __vcop_pblock_init32(pblock, __offset+_PREG(6), (uchar *)BScore);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)DScore);
   __vcop_pblock_init16(pblock, __offset+_PREG(10), 8);
   __vcop_pblock_init16(pblock, __offset+_PREG(11), 80);
   __vcop_pblock_init16(pblock, __offset+_PREG(12), -48);
   __vcop_pblock_init16(pblock, __offset+_PREG(13), 24);
   __vcop_pblock_init32(pblock, __offset+_PREG(14), (uchar *)Offset_Out);
   __vcop_pblock_init32(pblock, __offset+_PREG(16), (uchar *)Offset_Out+8u*sizeof(*Offset_Out));
   __offset += 16;

   /* Loop 5 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), ((nFeatures+(8u)-1)/(8u))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), (15)-1u);
   __vcop_pblock_init32(pblock, __offset+_PREG(6), (uchar *)BScore+8u*sizeof(*BScore));
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)DScore+8u*sizeof(*DScore));
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)Score_B);
   __vcop_pblock_init32(pblock, __offset+_PREG(12), (uchar *)Score_D);
   __vcop_pblock_init16(pblock, __offset+_PREG(14), 128);
   __vcop_pblock_init16(pblock, __offset+_PREG(15), 8);
   __vcop_pblock_init16(pblock, __offset+_PREG(16), 16);
   __vcop_pblock_init32(pblock, __offset+_PREG(18), (uchar *)BScore);
   __vcop_pblock_init32(pblock, __offset+_PREG(20), (uchar *)DScore);
   __offset += 20;

   /* Loop 6 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), (1)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), ((nFeatures+2*(8u)-1)/(2*(8u)))-1u);
   __vcop_pblock_init32(pblock, __offset+_PREG(6), (uchar *)updateOutPtr+184);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)updateOutPtr+188);
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)Score_B);
   __vcop_pblock_init32(pblock, __offset+_PREG(12), (uchar *)Score_B+8u*sizeof(*Score_B));
   __vcop_pblock_init32(pblock, __offset+_PREG(14), (uchar *)Score_D);
   __vcop_pblock_init32(pblock, __offset+_PREG(16), (uchar *)Score_D+8u*sizeof(*Score_D));
   __vcop_pblock_init32(pblock, __offset+_PREG(18), (uchar *)Offset_Out+8u*24*sizeof(*Offset_Out));
   __vcop_pblock_init32(pblock, __offset+_PREG(20), (uchar *)Offset_Out+8u*49*sizeof(*Offset_Out));
   __vcop_pblock_init32(pblock, __offset+_PREG(22), (uchar *)Score);
   __vcop_pblock_init32(pblock, __offset+_PREG(24), (uchar *)Score+8u*sizeof(*Score));
   __vcop_pblock_init16(pblock, __offset+_PREG(26), 400);
   __vcop_pblock_init16(pblock, __offset+_PREG(27),  -(2*8u*25*sizeof(*Offset_Out))*(((nFeatures+2*(8u)-1)/(2*(8u)))-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(28), 32);
   __vcop_pblock_init16(pblock, __offset+_PREG(29),  -(2*8u*sizeof(*Score_B))*(((nFeatures+2*(8u)-1)/(2*(8u)))-1u));
   __vcop_pblock_init32(pblock, __offset+_PREG(30), 1);
   __vcop_pblock_init32(pblock, __offset+_PREG(32), nFeatures*2);
   __offset += 32;

   return 104u;
}

void vcop_fast9_thresh_score_vloops(
   unsigned short pblock[])
{
   /* Kernel-wide Vector Registers */
   #pragma VCC_VREG("Vone", 16);

   __vcop_param(&pblock[0]);

   /* VLOOP 1 Start */

   /* VLOOP Local Vector Registers */
   #pragma VCC_VREG("Vin1", 17);
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("Addr1", "A0");
   #pragma EVE_REG("Addr2", "A1");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I1", "I2");
   #pragma EVE_REG("I2", "I3");
   #pragma EVE_REG("I3", "I4");
   

   __vcop_vloop(__vcop_compute(), 5u, 6u, 1u);
   __vcop_vagen(_AGEN(0), _PREG(6), _PREG(6), _PREG(6), _PREG(0));
   __vcop_vagen(_AGEN(1), _PREG(7), _PREG(8), _PREG(9), _PREG(0));
   __vcop_vload(__vcop_sizeWU(), __vcop_npt(), _PREG(10), _AGEN(0), _VREG(17), __vcop_alws());
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeWU(), __vcop_offst_np1(), __vcop_alws(), _VREG(17), _PREG(12), _AGEN(1), _PREG(0));
   __vcop_vloop_end(1u);

   /* VLOOP 2 Start */

   /* VLOOP Local Vector Registers */
   #pragma VCC_VREG("Vin1", 18);
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("Addr1", "A0");
   #pragma EVE_REG("Addr2", "A1");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I2", "I3");
   #pragma EVE_REG("I3", "I4");
   

   __vcop_vloop(__vcop_compute(), 5u, 5u, 2u);
   __vcop_vagen(_AGEN(0), _PREG(6), _PREG(6), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(1), _PREG(7), _PREG(7), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeWU(), __vcop_npt(), _PREG(8), _AGEN(0), _VREG(18), __vcop_alws());
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeWU(), __vcop_npt(), __vcop_alws(), _VREG(18), _PREG(10), _AGEN(1), _PREG(0));
   __vcop_vloop_end(2u);

   /* VLOOP 3 Start */

   /* VLOOP Local Vector Registers */
   #pragma VCC_VREG("Vindex", 19);
   #pragma VCC_VREG("Vtabledata", 20);
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("index_addr", "A0");
   #pragma EVE_REG("out_addr", "A2");
   #pragma EVE_REG("table_addr", "A1");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I3", "I3");
   #pragma EVE_REG("I4", "I4");
   

   __vcop_vloop(__vcop_tablelkup(), 7u, 7u, 3u);
   __vcop_vagen(_AGEN(0), _PREG(8), _PREG(9), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(2), _PREG(8), _PREG(8), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(1), _PREG(0), _PREG(10), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeBU(), __vcop_npt(), _PREG(12), _AGEN(0), _VREG(19), __vcop_alws());
   __vcop_vtbload(__vcop_sizeBU(), __vcop_tableinfo(8, 1), _PREG(14), _AGEN(1), _VREG(19), _VREG(20), _PREG(0), __vcop_alws());
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeBU(), __vcop_npt(), __vcop_alws(), _VREG(20), _PREG(6), _AGEN(2), _PREG(0));
   __vcop_vloop_end(3u);

   /* VLOOP 4 Start */

   /* VLOOP Local Vector Registers */
   #pragma VCC_VREG("Vin1", 21);
   #pragma VCC_VREG("Vmax", 22);
   #pragma VCC_VREG("Vmin", 23);
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("Addr0", "A0");
   #pragma EVE_REG("Addr1", "A1");
   #pragma EVE_REG("Addr_out", "A2");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I2", "I2");
   #pragma EVE_REG("I3", "I3");
   #pragma EVE_REG("I4", "I4");
   

   __vcop_vloop(__vcop_compute(), 11u, 8u, 4u);
   __vcop_vagen(_AGEN(0), _PREG(0), _PREG(10), _PREG(11), _PREG(0));
   __vcop_vagen(_AGEN(1), _PREG(10), _PREG(12), _PREG(13), _PREG(0));
   __vcop_vagen(_AGEN(2), _PREG(0), _PREG(10), _PREG(10), _PREG(0));
   __vcop_vload(__vcop_sizeBU(), __vcop_npt(), _PREG(14), _AGEN(0), _VREG(23), __vcop_i4_zero());
   __vcop_vload(__vcop_sizeBU(), __vcop_npt(), _PREG(14), _AGEN(0), _VREG(22), __vcop_i4_zero());
   __vcop_vload(__vcop_sizeBU(), __vcop_npt(), _PREG(16), _AGEN(1), _VREG(21), __vcop_alws());
   __vcop_vmax(_VREG(22), _VREG(21), _VREG(22));
   __vcop_vmin(_VREG(23), _VREG(21), _VREG(23));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeBU(), __vcop_npt(), __vcop_last_i4(), _VREG(22), _PREG(6), _AGEN(2), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeBU(), __vcop_npt(), __vcop_last_i4(), _VREG(23), _PREG(8), _AGEN(2), _PREG(0));
   __vcop_vloop_end(4u);

   /* VLOOP 5 Start */

   /* VLOOP Local Vector Registers */
   #pragma VCC_VREG("Vin_b", 24);
   #pragma VCC_VREG("Vin_d", 25);
   #pragma VCC_VREG("Vmax", 26);
   #pragma VCC_VREG("Vmin", 27);
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("Addr0", "A0");
   #pragma EVE_REG("Addr1", "A1");
   #pragma EVE_REG("Addr_out", "A2");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I3", "I3");
   #pragma EVE_REG("I4", "I4");
   

   __vcop_vloop(__vcop_compute(), 12u, 10u, 5u);
   __vcop_vagen(_AGEN(0), _PREG(0), _PREG(14), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(1), _PREG(15), _PREG(16), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(2), _PREG(0), _PREG(16), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeBU(), __vcop_npt(), _PREG(18), _AGEN(0), _VREG(27), __vcop_i4_zero());
   __vcop_vload(__vcop_sizeBU(), __vcop_npt(), _PREG(20), _AGEN(0), _VREG(26), __vcop_i4_zero());
   __vcop_vload(__vcop_sizeBU(), __vcop_npt(), _PREG(6), _AGEN(1), _VREG(24), __vcop_alws());
   __vcop_vload(__vcop_sizeBU(), __vcop_npt(), _PREG(8), _AGEN(1), _VREG(25), __vcop_alws());
   __vcop_vmin(_VREG(27), _VREG(24), _VREG(27));
   __vcop_vmax(_VREG(26), _VREG(25), _VREG(26));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeHU(), __vcop_npt(), __vcop_last_i4(), _VREG(27), _PREG(10), _AGEN(2), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeHU(), __vcop_npt(), __vcop_last_i4(), _VREG(26), _PREG(12), _AGEN(2), _PREG(0));
   __vcop_vloop_end(5u);

   /* VLOOP 6 Start */

   /* VLOOP Local Vector Registers */
   #pragma VCC_VREG("OutIncr1", 28);
   #pragma VCC_VREG("OutIncr2", 29);
   #pragma VCC_VREG("num", 30);
   #pragma VCC_VREG("offset1", 31);
   #pragma VCC_VREG("offset2", 32);
   #pragma VCC_VREG("Vin0", 33);
   #pragma VCC_VREG("Vin1", 34);
   #pragma VCC_VREG("Vin_b1", 35);
   #pragma VCC_VREG("Vin_b2", 36);
   #pragma VCC_VREG("Vin_d1", 37);
   #pragma VCC_VREG("Vin_d2", 38);
   #pragma VCC_VREG("Vmask1", 39);
   #pragma VCC_VREG("Vmask2", 40);
   #pragma VCC_VREG("Vout1", 41);
   #pragma VCC_VREG("Vout2", 42);
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("Addr2", "A0");
   #pragma EVE_REG("Addr0", "A1");
   #pragma EVE_REG("Addr1", "A2");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I3", "I3");
   #pragma EVE_REG("I4", "I4");
   

   __vcop_vloop(__vcop_compute(), 30u, 16u, 6u);
   __vcop_vinit(__vcop_sizeW(), __vcop_once(), _PREG(30), _VREG(16));
   __vcop_vinit(__vcop_sizeW(), __vcop_i4_zero(), _PREG(32), _VREG(30));
   __vcop_vagen(_AGEN(0), _PREG(0), _PREG(1), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(1), _PREG(26), _PREG(27), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(2), _PREG(28), _PREG(29), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeWU(), __vcop_1pt(), _PREG(6), _AGEN(0), _VREG(31), __vcop_i4_zero());
   __vcop_vload(__vcop_sizeWU(), __vcop_1pt(), _PREG(8), _AGEN(0), _VREG(32), __vcop_i4_zero());
   __vcop_vload(__vcop_sizeHU(), __vcop_npt(), _PREG(10), _AGEN(2), _VREG(35), __vcop_alws());
   __vcop_vload(__vcop_sizeHU(), __vcop_npt(), _PREG(12), _AGEN(2), _VREG(36), __vcop_alws());
   __vcop_vload(__vcop_sizeHU(), __vcop_npt(), _PREG(14), _AGEN(2), _VREG(37), __vcop_alws());
   __vcop_vload(__vcop_sizeHU(), __vcop_npt(), _PREG(16), _AGEN(2), _VREG(38), __vcop_alws());
   __vcop_vload(__vcop_sizeBU(), __vcop_npt(), _PREG(18), _AGEN(1), _VREG(33), __vcop_alws());
   __vcop_vload(__vcop_sizeBU(), __vcop_npt(), _PREG(20), _AGEN(1), _VREG(34), __vcop_alws());
   __vcop_vcmpgt(_VREG(35), _VREG(33), _VREG(39));
   __vcop_vcmpgt(_VREG(36), _VREG(34), _VREG(40));
   __vcop_vsort2(_VREG(35), _VREG(37));
   __vcop_vsort2(_VREG(36), _VREG(38));
   __vcop_vsel(_VREG(39), _VREG(35), _VREG(37));
   __vcop_vsel(_VREG(40), _VREG(36), _VREG(38));
   __vcop_vabsdif(_VREG(33), _VREG(37), _VREG(41));
   __vcop_vabsdif(_VREG(34), _VREG(38), _VREG(42));
   __vcop_vsub(_VREG(41), _VREG(16), _VREG(41));
   __vcop_vsub(_VREG(42), _VREG(16), _VREG(42));
   __vcop_vadd(_VREG(31), _VREG(30), _VREG(28));
   __vcop_vadd(_VREG(32), _VREG(30), _VREG(29));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeHU(), __vcop_npt(), __vcop_alws(), _VREG(41), _PREG(22), _AGEN(2), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeHU(), __vcop_npt(), __vcop_alws(), _VREG(42), _PREG(24), _AGEN(2), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeWU(), __vcop_1pt(), __vcop_last_i4(), _VREG(28), _PREG(6), _AGEN(0), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeWU(), __vcop_1pt(), __vcop_last_i4(), _VREG(29), _PREG(8), _AGEN(0), _PREG(0));
   __vcop_vloop_end(6u);

}

void vcop_fast9_thresh_score(
   __vptr_uint32 pIn,
   __vptr_uint32 pTemp_buf,
   __vptr_uint32 pTemp,
   __vptr_uint8 pTemp1,
   unsigned int nFeatures,
   signed char Thr,
   __vptr_uint8 Index,
   __vptr_uint8 Offset_Out,
   __vptr_uint8 BScore,
   __vptr_uint8 DScore,
   __vptr_uint16 Score_B,
   __vptr_uint16 Score_D,
   __vptr_uint16 Score,
   __vptr_uint32 updateOutPtr)
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_fast9_thresh_score_init(pIn, pTemp_buf, pTemp, pTemp1, nFeatures, Thr, Index, Offset_Out, BScore, DScore, Score_B, Score_D, Score, updateOutPtr, __pblock_vcop_fast9_thresh_score);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_fast9_thresh_score_vloops(__pblock_vcop_fast9_thresh_score);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

void vcop_fast9_thresh_score_custom(
   __vptr_uint32 pIn,
   __vptr_uint32 pTemp_buf,
   __vptr_uint32 pTemp,
   __vptr_uint8 pTemp1,
   unsigned int nFeatures,
   signed char Thr,
   __vptr_uint8 Index,
   __vptr_uint8 Offset_Out,
   __vptr_uint8 BScore,
   __vptr_uint8 DScore,
   __vptr_uint16 Score_B,
   __vptr_uint16 Score_D,
   __vptr_uint16 Score,
   __vptr_uint32 updateOutPtr,
   unsigned short pblock[])
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_fast9_thresh_score_init(pIn, pTemp_buf, pTemp, pTemp1, nFeatures, Thr, Index, Offset_Out, BScore, DScore, Score_B, Score_D, Score, updateOutPtr, pblock);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_fast9_thresh_score_vloops(pblock);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

