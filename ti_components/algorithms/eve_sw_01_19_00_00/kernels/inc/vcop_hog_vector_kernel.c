#include <vcop\vcop.h>

typedef unsigned char uchar;

#pragma DATA_SECTION(__pblock_vcop_ti_pd_hog_computation, ".vcop_parameter_block")
#pragma DATA_ALIGN(__pblock_vcop_ti_pd_hog_computation, __ALIGNOF__(int));
unsigned short __pblock_vcop_ti_pd_hog_computation[32];

unsigned int vcop_ti_pd_hog_computation_param_count(void)
{
   return 32u;
}

unsigned int vcop_ti_pd_hog_computation_ctrl_count(void)
{
   return 0u;
}

unsigned int vcop_ti_pd_hog_computation_init(
   __vptr_uint16 pIn,
   unsigned short cb_offset1,
   unsigned short cb_offset2,
   __vptr_uint16 ptemp16,
   __vptr_uint32 ptemp32,
   __vptr_uint32 pOut,
   unsigned short pitch,
   unsigned short width,
   unsigned short height,
   unsigned short pblock[])
{
   int __offset = 0;
   /* Loop 1 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), (height)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), ((width/8))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), ((8u))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), (16/2)-1u);
   __vcop_pblock_init32(pblock, __offset+_PREG(6), (uchar *)ptemp16);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)ptemp16+2);
   __vcop_pblock_init16(pblock, __offset+_PREG(10), (4*pitch*sizeof(*pIn)));
   __vcop_pblock_init16(pblock, __offset+_PREG(11), (sizeof(*pIn)) -(4*pitch*sizeof(*pIn))*((16/2)-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(12), (8u*sizeof(*pIn)) -(sizeof(*pIn))*(((8u))-1u) -(4*pitch*sizeof(*pIn))*((16/2)-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(13), (pitch*sizeof(*pIn)) -(8u*sizeof(*pIn))*(((width/8))-1u) -(sizeof(*pIn))*(((8u))-1u) -(4*pitch*sizeof(*pIn))*((16/2)-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(14), 288);
   __vcop_pblock_init16(pblock, __offset+_PREG(15), -2012);
   __vcop_pblock_init16(pblock, __offset+_PREG(16), 260);
   __vcop_pblock_init16(pblock, __offset+_PREG(17), (((8u+1)*4*8u)*(16/2)*(width/8)) -(((8u+1)*4*8u)*(16/2))*(((width/8))-1u) -(2*sizeof(*pIn))*(((8u))-1u) -(((8u+1)*4*8u))*((16/2)-1u));
   __vcop_pblock_init32(pblock, __offset+_PREG(18), (char *)(((unsigned int)((uchar *)pIn+cb_offset1)) | 0x300000));
   __vcop_pblock_init32(pblock, __offset+_PREG(20), (char *)(((unsigned int)((uchar *)pIn+cb_offset2)) | 0x300000));
   __offset += 20;

   /* Loop 2 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), (height)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), ((width/8))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), (((8u)*16/2))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(6), 36);
   __vcop_pblock_init16(pblock, __offset+_PREG(7), (((8u+1)*4*8u)*(16/2)*(width/8)) -(((8u+1)*4*8u)*(16/2))*(((width/8))-1u) -(((8u+1)*4))*((((8u)*16/2))-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(8), 32);
   __vcop_pblock_init16(pblock, __offset+_PREG(9), ((width/8)*(8u*16/2)*4*8u) -((8u*16/2)*4*8u)*(((width/8))-1u) -(4*8u)*((((8u)*16/2))-1u));
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)ptemp32);
   __vcop_pblock_init32(pblock, __offset+_PREG(12), (uchar *)pOut);
   __offset += 12;

   return 32u;
}

void vcop_ti_pd_hog_computation_vloops(
   unsigned short pblock[])
{
   /* Kernel-wide Vector Registers */
   #pragma VCC_VREG("Vin1", 16);
   #pragma VCC_VREG("Vin2", 17);
   #pragma VCC_VREG("Vout1", 18);
   #pragma VCC_VREG("Vout2", 19);

   __vcop_param(&pblock[0]);

   /* VLOOP 1 Start */

   /* VLOOP Local Vector Registers */
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("Addr1", "A0");
   #pragma EVE_REG("Addr2", "A1");
   #pragma EVE_REG("Addr3", "A2");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I1", "I1");
   #pragma EVE_REG("I2", "I2");
   #pragma EVE_REG("I3", "I3");
   #pragma EVE_REG("I4", "I4");
   

   __vcop_vloop(__vcop_compute(), 11u, 10u, 1u);
   __vcop_vagen(_AGEN(0), _PREG(10), _PREG(11), _PREG(12), _PREG(13));
   __vcop_vagen(_AGEN(1), _PREG(14), _PREG(15), _PREG(16), _PREG(17));
   __vcop_vload(__vcop_sizeHU(), __vcop_ds2(), _PREG(18), _AGEN(0), _VREG(16), __vcop_alws());
   __vcop_vload(__vcop_sizeHU(), __vcop_ds2(), _PREG(20), _AGEN(0), _VREG(17), __vcop_alws());
   __vcop_vmove(_VREG(16), _VREG(18));
   __vcop_vmove(_VREG(17), _VREG(19));
   __vcop_vdintrlv(_VREG(18), _VREG(19));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeHU(), __vcop_offst_np1(), __vcop_alws(), _VREG(18), _PREG(6), _AGEN(1), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeHU(), __vcop_offst_np1(), __vcop_alws(), _VREG(19), _PREG(8), _AGEN(1), _PREG(0));
   __vcop_vloop_end(1u);

   /* VLOOP 2 Start */

   /* VLOOP Local Vector Registers */
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("Addr1", "A0");
   #pragma EVE_REG("Addr2", "A1");
   #pragma EVE_REG("Addr3", "A2");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I1", "I2");
   #pragma EVE_REG("I2", "I3");
   #pragma EVE_REG("I4", "I4");
   

   __vcop_vloop(__vcop_compute(), 6u, 6u, 2u);
   __vcop_vagen(_AGEN(0), _PREG(6), _PREG(6), _PREG(7), _PREG(0));
   __vcop_vagen(_AGEN(1), _PREG(8), _PREG(8), _PREG(9), _PREG(0));
   __vcop_vload(__vcop_sizeWU(), __vcop_npt(), _PREG(10), _AGEN(0), _VREG(16), __vcop_alws());
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeWU(), __vcop_npt(), __vcop_alws(), _VREG(16), _PREG(12), _AGEN(1), _PREG(0));
   __vcop_vloop_end(2u);

}

void vcop_ti_pd_hog_computation(
   __vptr_uint16 pIn,
   unsigned short cb_offset1,
   unsigned short cb_offset2,
   __vptr_uint16 ptemp16,
   __vptr_uint32 ptemp32,
   __vptr_uint32 pOut,
   unsigned short pitch,
   unsigned short width,
   unsigned short height)
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_ti_pd_hog_computation_init(pIn, cb_offset1, cb_offset2, ptemp16, ptemp32, pOut, pitch, width, height, __pblock_vcop_ti_pd_hog_computation);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_ti_pd_hog_computation_vloops(__pblock_vcop_ti_pd_hog_computation);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

void vcop_ti_pd_hog_computation_custom(
   __vptr_uint16 pIn,
   unsigned short cb_offset1,
   unsigned short cb_offset2,
   __vptr_uint16 ptemp16,
   __vptr_uint32 ptemp32,
   __vptr_uint32 pOut,
   unsigned short pitch,
   unsigned short width,
   unsigned short height,
   unsigned short pblock[])
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_ti_pd_hog_computation_init(pIn, cb_offset1, cb_offset2, ptemp16, ptemp32, pOut, pitch, width, height, pblock);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_ti_pd_hog_computation_vloops(pblock);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

#pragma DATA_SECTION(__pblock_vcop_ti_pd_2x2_sum, ".vcop_parameter_block")
#pragma DATA_ALIGN(__pblock_vcop_ti_pd_2x2_sum, __ALIGNOF__(int));
unsigned short __pblock_vcop_ti_pd_2x2_sum[28];

unsigned int vcop_ti_pd_2x2_sum_param_count(void)
{
   return 28u;
}

unsigned int vcop_ti_pd_2x2_sum_ctrl_count(void)
{
   return 0u;
}

unsigned int vcop_ti_pd_2x2_sum_init(
   __vptr_uint16 pIn,
   __vptr_uint16 pOut1,
   __vptr_uint16 pOut2,
   unsigned short width,
   unsigned short height,
   unsigned short pitch,
   unsigned short pblock[])
{
   int __offset = 0;
   /* Loop 1 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), (height)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), ((width/16))-1u);
   __vcop_pblock_init32(pblock, __offset+_PREG(6), (uchar *)pIn+2);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)pIn+pitch*2+2);
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)pIn+16);
   __vcop_pblock_init32(pblock, __offset+_PREG(12), (uchar *)pIn+pitch*2+16);
   __vcop_pblock_init32(pblock, __offset+_PREG(14), (uchar *)pIn+18);
   __vcop_pblock_init32(pblock, __offset+_PREG(16), (uchar *)pIn+pitch*2+18);
   __vcop_pblock_init32(pblock, __offset+_PREG(18), (uchar *)pOut1);
   __vcop_pblock_init32(pblock, __offset+_PREG(20), (uchar *)pOut2);
   __vcop_pblock_init16(pblock, __offset+_PREG(22), 32);
   __vcop_pblock_init16(pblock, __offset+_PREG(23), (pitch*2) -(16*2)*(((width/16))-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(24), 16);
   __vcop_pblock_init16(pblock, __offset+_PREG(25), (width) -(8*2)*(((width/16))-1u));
   __vcop_pblock_init32(pblock, __offset+_PREG(26), (uchar *)pIn);
   __vcop_pblock_init32(pblock, __offset+_PREG(28), (uchar *)pIn+pitch*2);
   __offset += 28;

   return 28u;
}

void vcop_ti_pd_2x2_sum_vloops(
   unsigned short pblock[])
{
   /* Kernel-wide Vector Registers */
   #pragma VCC_VREG("Vin1", 16);
   #pragma VCC_VREG("Vin2", 17);
   #pragma VCC_VREG("Vin3", 18);
   #pragma VCC_VREG("Vin4", 19);
   #pragma VCC_VREG("Vin5", 20);
   #pragma VCC_VREG("Vin6", 21);
   #pragma VCC_VREG("Vin7", 22);
   #pragma VCC_VREG("Vin8", 23);
   #pragma VCC_VREG("Vsum1", 24);
   #pragma VCC_VREG("Vsum2", 25);
   #pragma VCC_VREG("Vsum3", 26);
   #pragma VCC_VREG("Vsum4", 27);

   __vcop_param(&pblock[0]);

   /* VLOOP 1 Start */

   /* VLOOP Local Vector Registers */
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("Addr1", "A0");
   #pragma EVE_REG("Addr2", "A1");
   #pragma EVE_REG("Addr3", "A2");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I1", "I3");
   #pragma EVE_REG("I2", "I4");
   

   __vcop_vloop(__vcop_compute(), 21u, 14u, 1u);
   __vcop_vagen(_AGEN(0), _PREG(22), _PREG(23), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(1), _PREG(24), _PREG(25), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeHU(), __vcop_npt(), _PREG(26), _AGEN(0), _VREG(16), __vcop_alws());
   __vcop_vload(__vcop_sizeHU(), __vcop_npt(), _PREG(28), _AGEN(0), _VREG(17), __vcop_alws());
   __vcop_vload(__vcop_sizeHU(), __vcop_npt(), _PREG(6), _AGEN(0), _VREG(18), __vcop_alws());
   __vcop_vload(__vcop_sizeHU(), __vcop_npt(), _PREG(8), _AGEN(0), _VREG(19), __vcop_alws());
   __vcop_vload(__vcop_sizeHU(), __vcop_npt(), _PREG(10), _AGEN(0), _VREG(20), __vcop_alws());
   __vcop_vload(__vcop_sizeHU(), __vcop_npt(), _PREG(12), _AGEN(0), _VREG(21), __vcop_alws());
   __vcop_vload(__vcop_sizeHU(), __vcop_npt(), _PREG(14), _AGEN(0), _VREG(22), __vcop_alws());
   __vcop_vload(__vcop_sizeHU(), __vcop_npt(), _PREG(16), _AGEN(0), _VREG(23), __vcop_alws());
   __vcop_vadd(_VREG(16), _VREG(17), _VREG(24));
   __vcop_vadd(_VREG(20), _VREG(21), _VREG(25));
   __vcop_vadd3(_VREG(18), _VREG(19), _VREG(24));
   __vcop_vadd3(_VREG(22), _VREG(23), _VREG(25));
   __vcop_vmove(_VREG(24), _VREG(26));
   __vcop_vmove(_VREG(25), _VREG(27));
   __vcop_vdintrlv(_VREG(26), _VREG(27));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeHU(), __vcop_npt(), __vcop_alws(), _VREG(26), _PREG(18), _AGEN(1), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeHU(), __vcop_npt(), __vcop_alws(), _VREG(27), _PREG(20), _AGEN(1), _PREG(0));
   __vcop_vloop_end(1u);

}

void vcop_ti_pd_2x2_sum(
   __vptr_uint16 pIn,
   __vptr_uint16 pOut1,
   __vptr_uint16 pOut2,
   unsigned short width,
   unsigned short height,
   unsigned short pitch)
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_ti_pd_2x2_sum_init(pIn, pOut1, pOut2, width, height, pitch, __pblock_vcop_ti_pd_2x2_sum);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_ti_pd_2x2_sum_vloops(__pblock_vcop_ti_pd_2x2_sum);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

void vcop_ti_pd_2x2_sum_custom(
   __vptr_uint16 pIn,
   __vptr_uint16 pOut1,
   __vptr_uint16 pOut2,
   unsigned short width,
   unsigned short height,
   unsigned short pitch,
   unsigned short pblock[])
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_ti_pd_2x2_sum_init(pIn, pOut1, pOut2, width, height, pitch, pblock);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_ti_pd_2x2_sum_vloops(pblock);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

#pragma DATA_SECTION(__pblock_vcop_ti_pd_2x2_sum_planar, ".vcop_parameter_block")
#pragma DATA_ALIGN(__pblock_vcop_ti_pd_2x2_sum_planar, __ALIGNOF__(int));
unsigned short __pblock_vcop_ti_pd_2x2_sum_planar[28];

unsigned int vcop_ti_pd_2x2_sum_planar_param_count(void)
{
   return 28u;
}

unsigned int vcop_ti_pd_2x2_sum_planar_ctrl_count(void)
{
   return 0u;
}

unsigned int vcop_ti_pd_2x2_sum_planar_init(
   __vptr_uint16 pIn,
   __vptr_uint16 pOut1,
   unsigned short width,
   unsigned short height,
   unsigned short pitch,
   unsigned short pblock[])
{
   int __offset = 0;
   /* Loop 1 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), (height)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), ((width/16))-1u);
   __vcop_pblock_init32(pblock, __offset+_PREG(6), (uchar *)pIn+2);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)pIn+pitch*2+2);
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)pIn+16);
   __vcop_pblock_init32(pblock, __offset+_PREG(12), (uchar *)pIn+pitch*2+16);
   __vcop_pblock_init32(pblock, __offset+_PREG(14), (uchar *)pIn+18);
   __vcop_pblock_init32(pblock, __offset+_PREG(16), (uchar *)pIn+pitch*2+18);
   __vcop_pblock_init32(pblock, __offset+_PREG(18), (uchar *)pOut1);
   __vcop_pblock_init32(pblock, __offset+_PREG(20), (uchar *)pOut1+8*2);
   __vcop_pblock_init16(pblock, __offset+_PREG(22), 32);
   __vcop_pblock_init16(pblock, __offset+_PREG(23), (pitch*2) -(16*2)*(((width/16))-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(24), (width*2) -(16*2)*(((width/16))-1u));
   __vcop_pblock_init32(pblock, __offset+_PREG(26), (uchar *)pIn);
   __vcop_pblock_init32(pblock, __offset+_PREG(28), (uchar *)pIn+pitch*2);
   __offset += 28;

   return 28u;
}

void vcop_ti_pd_2x2_sum_planar_vloops(
   unsigned short pblock[])
{
   /* Kernel-wide Vector Registers */
   #pragma VCC_VREG("Vin1", 16);
   #pragma VCC_VREG("Vin2", 17);
   #pragma VCC_VREG("Vin3", 18);
   #pragma VCC_VREG("Vin4", 19);
   #pragma VCC_VREG("Vin5", 20);
   #pragma VCC_VREG("Vin6", 21);
   #pragma VCC_VREG("Vin7", 22);
   #pragma VCC_VREG("Vin8", 23);
   #pragma VCC_VREG("Vsum1", 24);
   #pragma VCC_VREG("Vsum2", 25);
   #pragma VCC_VREG("Vsum3", 26);
   #pragma VCC_VREG("Vsum4", 27);

   __vcop_param(&pblock[0]);

   /* VLOOP 1 Start */

   /* VLOOP Local Vector Registers */
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("Addr1", "A0");
   #pragma EVE_REG("Addr2", "A1");
   #pragma EVE_REG("Addr3", "A2");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I1", "I3");
   #pragma EVE_REG("I2", "I4");
   

   __vcop_vloop(__vcop_compute(), 18u, 14u, 1u);
   __vcop_vagen(_AGEN(0), _PREG(22), _PREG(23), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(1), _PREG(22), _PREG(24), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeHU(), __vcop_npt(), _PREG(26), _AGEN(0), _VREG(16), __vcop_alws());
   __vcop_vload(__vcop_sizeHU(), __vcop_npt(), _PREG(28), _AGEN(0), _VREG(17), __vcop_alws());
   __vcop_vload(__vcop_sizeHU(), __vcop_npt(), _PREG(6), _AGEN(0), _VREG(18), __vcop_alws());
   __vcop_vload(__vcop_sizeHU(), __vcop_npt(), _PREG(8), _AGEN(0), _VREG(19), __vcop_alws());
   __vcop_vload(__vcop_sizeHU(), __vcop_npt(), _PREG(10), _AGEN(0), _VREG(20), __vcop_alws());
   __vcop_vload(__vcop_sizeHU(), __vcop_npt(), _PREG(12), _AGEN(0), _VREG(21), __vcop_alws());
   __vcop_vload(__vcop_sizeHU(), __vcop_npt(), _PREG(14), _AGEN(0), _VREG(22), __vcop_alws());
   __vcop_vload(__vcop_sizeHU(), __vcop_npt(), _PREG(16), _AGEN(0), _VREG(23), __vcop_alws());
   __vcop_vadd(_VREG(16), _VREG(17), _VREG(24));
   __vcop_vadd(_VREG(20), _VREG(21), _VREG(25));
   __vcop_vadd3(_VREG(18), _VREG(19), _VREG(24));
   __vcop_vadd3(_VREG(22), _VREG(23), _VREG(25));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeHU(), __vcop_npt(), __vcop_alws(), _VREG(24), _PREG(18), _AGEN(1), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeHU(), __vcop_npt(), __vcop_alws(), _VREG(25), _PREG(20), _AGEN(1), _PREG(0));
   __vcop_vloop_end(1u);

}

void vcop_ti_pd_2x2_sum_planar(
   __vptr_uint16 pIn,
   __vptr_uint16 pOut1,
   unsigned short width,
   unsigned short height,
   unsigned short pitch)
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_ti_pd_2x2_sum_planar_init(pIn, pOut1, width, height, pitch, __pblock_vcop_ti_pd_2x2_sum_planar);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_ti_pd_2x2_sum_planar_vloops(__pblock_vcop_ti_pd_2x2_sum_planar);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

void vcop_ti_pd_2x2_sum_planar_custom(
   __vptr_uint16 pIn,
   __vptr_uint16 pOut1,
   unsigned short width,
   unsigned short height,
   unsigned short pitch,
   unsigned short pblock[])
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_ti_pd_2x2_sum_planar_init(pIn, pOut1, width, height, pitch, pblock);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_ti_pd_2x2_sum_planar_vloops(pblock);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

