#include <vcop\vcop.h>

typedef unsigned char uchar;

#pragma DATA_SECTION(__pblock_vcop_multipoint_harrisScore_7x7_u16, ".vcop_parameter_block")
#pragma DATA_ALIGN(__pblock_vcop_multipoint_harrisScore_7x7_u16, __ALIGNOF__(int));
unsigned short __pblock_vcop_multipoint_harrisScore_7x7_u16[160];

unsigned int vcop_multipoint_harrisScore_7x7_u16_param_count(void)
{
   return 160u;
}

unsigned int vcop_multipoint_harrisScore_7x7_u16_ctrl_count(void)
{
   return 0u;
}

unsigned int vcop_multipoint_harrisScore_7x7_u16_init(
   __vptr_uint8 pImgBlocks_A,
   __vptr_uint16 harrisScore_C,
   unsigned short numPoints,
   unsigned short inputStride,
   unsigned short interBlockOffset,
   unsigned short sensitivityParam,
   short start_idx,
   __vptr_uint16 seq_array_C,
   __vptr_int32 vertSumX2_C,
   __vptr_int32 vertSumY2_B,
   __vptr_int32 vertSumXY_C,
   __vptr_int32 Ixx_A,
   __vptr_int32 Iyy_C,
   __vptr_int32 Ixy_A,
   __vptr_uint16 Ixx_l,
   __vptr_uint16 Iyy_l,
   __vptr_uint16 Ixy_l,
   __vptr_int16 Ixx_h,
   __vptr_int16 Iyy_h,
   __vptr_int16 Ixy_h,
   __vptr_uint32 detL_C,
   __vptr_int32 detH_C,
   __vptr_int32 pBlock,
   unsigned short pblock[])
{
   int __offset = 0;
   /* Loop 1 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), ((numPoints + ((8u)-1))/(8u))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), ((8u)/2)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), ((7))-1u);
   __vcop_pblock_init32(pblock, __offset+_PREG(6), (uchar *)pImgBlocks_A+inputStride);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)pImgBlocks_A+inputStride+2);
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)pImgBlocks_A+2*inputStride+1);
   __vcop_pblock_init32(pblock, __offset+_PREG(12), (uchar *)pImgBlocks_A+interBlockOffset*sizeof(*pImgBlocks_A)+1);
   __vcop_pblock_init32(pblock, __offset+_PREG(14), (uchar *)pImgBlocks_A+interBlockOffset*sizeof(*pImgBlocks_A)+inputStride);
   __vcop_pblock_init32(pblock, __offset+_PREG(16), (uchar *)pImgBlocks_A+interBlockOffset*sizeof(*pImgBlocks_A)+inputStride+2);
   __vcop_pblock_init32(pblock, __offset+_PREG(18), (uchar *)pImgBlocks_A+interBlockOffset*sizeof(*pImgBlocks_A)+2*inputStride+1);
   __vcop_pblock_init32(pblock, __offset+_PREG(20), (uchar *)vertSumX2_C);
   __vcop_pblock_init32(pblock, __offset+_PREG(22), (uchar *)vertSumY2_B);
   __vcop_pblock_init32(pblock, __offset+_PREG(24), (uchar *)vertSumXY_C);
   __vcop_pblock_init32(pblock, __offset+_PREG(26), (uchar *)vertSumX2_C+4);
   __vcop_pblock_init32(pblock, __offset+_PREG(28), (uchar *)vertSumY2_B+4);
   __vcop_pblock_init32(pblock, __offset+_PREG(30), (uchar *)vertSumXY_C+4);
   __vcop_pblock_init16(pblock, __offset+_PREG(32), 8);
   __vcop_pblock_init16(pblock, __offset+_PREG(33), 228);
   __vcop_pblock_init16(pblock, __offset+_PREG(34), (inputStride*sizeof(*pImgBlocks_A)));
   __vcop_pblock_init16(pblock, __offset+_PREG(35), (2*interBlockOffset*sizeof(*pImgBlocks_A)) -(inputStride*sizeof(*pImgBlocks_A))*(((7))-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(36), (8*interBlockOffset*sizeof(*pImgBlocks_A)) -(2*interBlockOffset*sizeof(*pImgBlocks_A))*(((8u)/2)-1u) -(inputStride*sizeof(*pImgBlocks_A))*(((7))-1u));
   __vcop_pblock_init32(pblock, __offset+_PREG(38), 0);
   __vcop_pblock_init32(pblock, __offset+_PREG(40), (uchar *)pImgBlocks_A+1);
   __offset += 40;

   /* Loop 2 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), ((numPoints + ((2*(8u))-1))/(2*(8u)))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), ((7))-1u);
   __vcop_pblock_init32(pblock, __offset+_PREG(6), (uchar *)vertSumY2_B);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)vertSumXY_C);
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)vertSumX2_C+36*7);
   __vcop_pblock_init32(pblock, __offset+_PREG(12), (uchar *)vertSumY2_B+36*7);
   __vcop_pblock_init32(pblock, __offset+_PREG(14), (uchar *)vertSumXY_C+36*7);
   __vcop_pblock_init32(pblock, __offset+_PREG(16), (uchar *)Ixx_A);
   __vcop_pblock_init32(pblock, __offset+_PREG(18), (uchar *)Iyy_C);
   __vcop_pblock_init32(pblock, __offset+_PREG(20), (uchar *)Ixy_A);
   __vcop_pblock_init32(pblock, __offset+_PREG(22), (uchar *)Ixx_A+4*8u);
   __vcop_pblock_init32(pblock, __offset+_PREG(24), (uchar *)Iyy_C+4*8u);
   __vcop_pblock_init32(pblock, __offset+_PREG(26), (uchar *)Ixy_A+4*8u);
   __vcop_pblock_init16(pblock, __offset+_PREG(28), 64);
   __vcop_pblock_init16(pblock, __offset+_PREG(29), 36);
   __vcop_pblock_init16(pblock, __offset+_PREG(30), 288);
   __vcop_pblock_init32(pblock, __offset+_PREG(32), 0);
   __vcop_pblock_init32(pblock, __offset+_PREG(34), (uchar *)vertSumX2_C);
   __offset += 34;

   /* Loop 3 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), (((numPoints + ((8u)-1))/ (8u)))-1u);
   __vcop_pblock_init32(pblock, __offset+_PREG(6), (uchar *)Iyy_l);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)Iyy_h);
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)Ixy_l);
   __vcop_pblock_init32(pblock, __offset+_PREG(12), (uchar *)Ixy_h);
   __vcop_pblock_init32(pblock, __offset+_PREG(14), 4294967295);
   __vcop_pblock_init32(pblock, __offset+_PREG(16), (uchar *)detL_C);
   __vcop_pblock_init32(pblock, __offset+_PREG(18), (uchar *)detH_C);
   __vcop_pblock_init16(pblock, __offset+_PREG(20), 32);
   __vcop_pblock_init32(pblock, __offset+_PREG(22), (uchar *)Ixx_l);
   __vcop_pblock_init32(pblock, __offset+_PREG(24), (uchar *)Ixx_h);
   __offset += 24;

   /* Loop 4 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), (((numPoints + ((8u)-1))/ (8u)))-1u);
   __vcop_pblock_init32(pblock, __offset+_PREG(6), (uchar *)detL_C);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)detH_C);
   __vcop_pblock_init32(pblock, __offset+_PREG(10), 4294967295);
   __vcop_pblock_init16(pblock, __offset+_PREG(12), 65535);
   __vcop_pblock_init16(pblock, __offset+_PREG(13), 32);
   __vcop_pblock_init32(pblock, __offset+_PREG(14), sensitivityParam);
   __vcop_pblock_init32(pblock, __offset+_PREG(16), 16);
   __vcop_pblock_init32(pblock, __offset+_PREG(18), -16);
   __vcop_pblock_init32(pblock, __offset+_PREG(20), -15);
   __vcop_pblock_init32(pblock, __offset+_PREG(22), 32);
   __vcop_pblock_init32(pblock, __offset+_PREG(24), 0);
   __vcop_pblock_init32(pblock, __offset+_PREG(26), (uchar *)Ixx_A);
   __vcop_pblock_init32(pblock, __offset+_PREG(28), (uchar *)Iyy_C);
   __offset += 28;

   /* Loop 5 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), (1)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), (((numPoints + ((8u)-1))/ (8u)))-1u);
   __vcop_pblock_init32(pblock, __offset+_PREG(6), 4*numPoints);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)seq_array_C);
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)pBlock+2*152);
   __vcop_pblock_init32(pblock, __offset+_PREG(12), (uchar *)pBlock+2*156);
   __vcop_pblock_init32(pblock, __offset+_PREG(14), 0);
   __vcop_pblock_init32(pblock, __offset+_PREG(16), 1);
   __vcop_pblock_init32(pblock, __offset+_PREG(18), 8);
   __vcop_pblock_init32(pblock, __offset+_PREG(20), 10);
   __vcop_pblock_init32(pblock, __offset+_PREG(22), 32);
   __vcop_pblock_init32(pblock, __offset+_PREG(24), (uchar *)detL_C);
   __vcop_pblock_init32(pblock, __offset+_PREG(26), (uchar *)detH_C);
   __vcop_pblock_init32(pblock, __offset+_PREG(28), (uchar *)harrisScore_C);
   __vcop_pblock_init16(pblock, __offset+_PREG(30), 32);
   __vcop_pblock_init16(pblock, __offset+_PREG(31),  -(4*8u)*((((numPoints + ((8u)-1))/ (8u)))-1u));
   __vcop_pblock_init32(pblock, __offset+_PREG(32), start_idx);
   __vcop_pblock_init32(pblock, __offset+_PREG(34), numPoints);
   __offset += 34;

   return 160u;
}

void vcop_multipoint_harrisScore_7x7_u16_vloops(
   unsigned short pblock[])
{
   /* Kernel-wide Vector Registers */

   __vcop_param(&pblock[0]);

   /* VLOOP 1 Start */

   /* VLOOP Local Vector Registers */
   #pragma VCC_VREG("VgXX1", 16);
   #pragma VCC_VREG("VgXX2", 17);
   #pragma VCC_VREG("VgXY1", 18);
   #pragma VCC_VREG("VgXY2", 19);
   #pragma VCC_VREG("VgYY1", 20);
   #pragma VCC_VREG("VgYY2", 21);
   #pragma VCC_VREG("VgX1", 22);
   #pragma VCC_VREG("VgX2", 23);
   #pragma VCC_VREG("VgY1", 24);
   #pragma VCC_VREG("VgY2", 25);
   #pragma VCC_VREG("VinB1", 26);
   #pragma VCC_VREG("VinB2", 27);
   #pragma VCC_VREG("VinL1", 28);
   #pragma VCC_VREG("VinL2", 29);
   #pragma VCC_VREG("VinR1", 30);
   #pragma VCC_VREG("VinR2", 31);
   #pragma VCC_VREG("VinT1", 32);
   #pragma VCC_VREG("VinT2", 33);
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("outAddr", "A0");
   #pragma EVE_REG("Addr_in", "A1");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I1", "I2");
   #pragma EVE_REG("I2", "I3");
   #pragma EVE_REG("I3", "I4");
   

   __vcop_vloop(__vcop_compute(), 33u, 20u, 1u);
   __vcop_vinit(__vcop_sizeW(), __vcop_i4_zero(), _PREG(38), _VREG(16));
   __vcop_vinit(__vcop_sizeW(), __vcop_i4_zero(), _PREG(38), _VREG(20));
   __vcop_vinit(__vcop_sizeW(), __vcop_i4_zero(), _PREG(38), _VREG(18));
   __vcop_vinit(__vcop_sizeW(), __vcop_i4_zero(), _PREG(38), _VREG(17));
   __vcop_vinit(__vcop_sizeW(), __vcop_i4_zero(), _PREG(38), _VREG(21));
   __vcop_vinit(__vcop_sizeW(), __vcop_i4_zero(), _PREG(38), _VREG(19));
   __vcop_vagen(_AGEN(0), _PREG(0), _PREG(32), _PREG(33), _PREG(0));
   __vcop_vagen(_AGEN(1), _PREG(34), _PREG(35), _PREG(36), _PREG(0));
   __vcop_vload(__vcop_sizeBU(), __vcop_npt(), _PREG(40), _AGEN(1), _VREG(32), __vcop_alws());
   __vcop_vload(__vcop_sizeBU(), __vcop_npt(), _PREG(6), _AGEN(1), _VREG(28), __vcop_alws());
   __vcop_vload(__vcop_sizeBU(), __vcop_npt(), _PREG(8), _AGEN(1), _VREG(30), __vcop_alws());
   __vcop_vload(__vcop_sizeBU(), __vcop_npt(), _PREG(10), _AGEN(1), _VREG(26), __vcop_alws());
   __vcop_vload(__vcop_sizeBU(), __vcop_npt(), _PREG(12), _AGEN(1), _VREG(33), __vcop_alws());
   __vcop_vload(__vcop_sizeBU(), __vcop_npt(), _PREG(14), _AGEN(1), _VREG(29), __vcop_alws());
   __vcop_vload(__vcop_sizeBU(), __vcop_npt(), _PREG(16), _AGEN(1), _VREG(31), __vcop_alws());
   __vcop_vload(__vcop_sizeBU(), __vcop_npt(), _PREG(18), _AGEN(1), _VREG(27), __vcop_alws());
   __vcop_vsub(_VREG(30), _VREG(28), _VREG(22));
   __vcop_vsub(_VREG(26), _VREG(32), _VREG(24));
   __vcop_vsub(_VREG(31), _VREG(29), _VREG(23));
   __vcop_vsub(_VREG(27), _VREG(33), _VREG(25));
   __vcop_vmadd(_VREG(22), _VREG(22), _VREG(16), _PREG(0));
   __vcop_vmadd(_VREG(23), _VREG(23), _VREG(17), _PREG(0));
   __vcop_vmadd(_VREG(24), _VREG(24), _VREG(20), _PREG(0));
   __vcop_vmadd(_VREG(25), _VREG(25), _VREG(21), _PREG(0));
   __vcop_vmadd(_VREG(22), _VREG(24), _VREG(18), _PREG(0));
   __vcop_vmadd(_VREG(23), _VREG(25), _VREG(19), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeW(), __vcop_offst_np1(), __vcop_last_i4(), _VREG(16), _PREG(20), _AGEN(0), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeW(), __vcop_offst_np1(), __vcop_last_i4(), _VREG(20), _PREG(22), _AGEN(0), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeW(), __vcop_offst_np1(), __vcop_last_i4(), _VREG(18), _PREG(24), _AGEN(0), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeW(), __vcop_offst_np1(), __vcop_last_i4(), _VREG(17), _PREG(26), _AGEN(0), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeW(), __vcop_offst_np1(), __vcop_last_i4(), _VREG(21), _PREG(28), _AGEN(0), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeW(), __vcop_offst_np1(), __vcop_last_i4(), _VREG(19), _PREG(30), _AGEN(0), _PREG(0));
   __vcop_vloop_end(1u);

   /* VLOOP 2 Start */

   /* VLOOP Local Vector Registers */
   #pragma VCC_VREG("VgXX1", 34);
   #pragma VCC_VREG("VgXX2", 35);
   #pragma VCC_VREG("VgXY1", 36);
   #pragma VCC_VREG("VgXY2", 37);
   #pragma VCC_VREG("VgYY1", 38);
   #pragma VCC_VREG("VgYY2", 39);
   #pragma VCC_VREG("VIxx1", 40);
   #pragma VCC_VREG("VIxx2", 41);
   #pragma VCC_VREG("VIxy1", 42);
   #pragma VCC_VREG("VIxy2", 43);
   #pragma VCC_VREG("VIyy1", 44);
   #pragma VCC_VREG("VIyy2", 45);
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("outAddr", "A0");
   #pragma EVE_REG("inAddr", "A1");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I1", "I3");
   #pragma EVE_REG("I2", "I4");
   

   __vcop_vloop(__vcop_compute(), 27u, 17u, 2u);
   __vcop_vinit(__vcop_sizeW(), __vcop_i4_zero(), _PREG(32), _VREG(34));
   __vcop_vinit(__vcop_sizeW(), __vcop_i4_zero(), _PREG(32), _VREG(38));
   __vcop_vinit(__vcop_sizeW(), __vcop_i4_zero(), _PREG(32), _VREG(36));
   __vcop_vinit(__vcop_sizeW(), __vcop_i4_zero(), _PREG(32), _VREG(35));
   __vcop_vinit(__vcop_sizeW(), __vcop_i4_zero(), _PREG(32), _VREG(39));
   __vcop_vinit(__vcop_sizeW(), __vcop_i4_zero(), _PREG(32), _VREG(37));
   __vcop_vagen(_AGEN(0), _PREG(0), _PREG(28), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(1), _PREG(29), _PREG(30), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeW(), __vcop_npt(), _PREG(34), _AGEN(1), _VREG(40), __vcop_alws());
   __vcop_vload(__vcop_sizeW(), __vcop_npt(), _PREG(6), _AGEN(1), _VREG(44), __vcop_alws());
   __vcop_vload(__vcop_sizeW(), __vcop_npt(), _PREG(8), _AGEN(1), _VREG(42), __vcop_alws());
   __vcop_vload(__vcop_sizeW(), __vcop_npt(), _PREG(10), _AGEN(1), _VREG(41), __vcop_alws());
   __vcop_vload(__vcop_sizeW(), __vcop_npt(), _PREG(12), _AGEN(1), _VREG(45), __vcop_alws());
   __vcop_vload(__vcop_sizeW(), __vcop_npt(), _PREG(14), _AGEN(1), _VREG(43), __vcop_alws());
   __vcop_vadd(_VREG(34), _VREG(40), _VREG(34));
   __vcop_vadd(_VREG(35), _VREG(41), _VREG(35));
   __vcop_vadd(_VREG(38), _VREG(44), _VREG(38));
   __vcop_vadd(_VREG(39), _VREG(45), _VREG(39));
   __vcop_vadd(_VREG(36), _VREG(42), _VREG(36));
   __vcop_vadd(_VREG(37), _VREG(43), _VREG(37));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeW(), __vcop_npt(), __vcop_last_i4(), _VREG(34), _PREG(16), _AGEN(0), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeW(), __vcop_npt(), __vcop_last_i4(), _VREG(38), _PREG(18), _AGEN(0), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeW(), __vcop_npt(), __vcop_last_i4(), _VREG(36), _PREG(20), _AGEN(0), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeW(), __vcop_npt(), __vcop_last_i4(), _VREG(35), _PREG(22), _AGEN(0), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeW(), __vcop_npt(), __vcop_last_i4(), _VREG(39), _PREG(24), _AGEN(0), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeW(), __vcop_npt(), __vcop_last_i4(), _VREG(37), _PREG(26), _AGEN(0), _PREG(0));
   __vcop_vloop_end(2u);

   /* VLOOP 3 Start */

   /* VLOOP Local Vector Registers */
   #pragma VCC_VREG("Vmask", 46);
   #pragma VCC_VREG("Vt2", 47);
   #pragma VCC_VREG("Vt2H", 48);
   #pragma VCC_VREG("Vt2L", 49);
   #pragma VCC_VREG("Vt3", 50);
   #pragma VCC_VREG("Vt3H", 51);
   #pragma VCC_VREG("Vt3L", 52);
   #pragma VCC_VREG("d1_h", 53);
   #pragma VCC_VREG("d1_l", 54);
   #pragma VCC_VREG("d2_h", 55);
   #pragma VCC_VREG("d2_l", 56);
   #pragma VCC_VREG("d_h", 57);
   #pragma VCC_VREG("d_l", 58);
   #pragma VCC_VREG("zxxH", 59);
   #pragma VCC_VREG("zxxL", 60);
   #pragma VCC_VREG("zxyH", 61);
   #pragma VCC_VREG("zxyL", 62);
   #pragma VCC_VREG("zyyH", 63);
   #pragma VCC_VREG("zyyL", 64);
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("Addr1", "A0");
   #pragma EVE_REG("Addr2", "A1");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I1", "I4");
   

   __vcop_vloop(__vcop_compute(), 33u, 12u, 3u);
   __vcop_vinit(__vcop_sizeWU(), __vcop_alws(), _PREG(14), _VREG(46));
   __vcop_vagen(_AGEN(0), _PREG(20), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(1), _PREG(20), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeHU(), __vcop_ds2(), _PREG(22), _AGEN(0), _VREG(60), __vcop_alws());
   __vcop_vload(__vcop_sizeH(), __vcop_ds2(), _PREG(24), _AGEN(0), _VREG(59), __vcop_alws());
   __vcop_vload(__vcop_sizeHU(), __vcop_ds2(), _PREG(6), _AGEN(0), _VREG(64), __vcop_alws());
   __vcop_vload(__vcop_sizeH(), __vcop_ds2(), _PREG(8), _AGEN(0), _VREG(63), __vcop_alws());
   __vcop_vload(__vcop_sizeHU(), __vcop_ds2(), _PREG(10), _AGEN(0), _VREG(62), __vcop_alws());
   __vcop_vload(__vcop_sizeH(), __vcop_ds2(), _PREG(12), _AGEN(0), _VREG(61), __vcop_alws());
   __vcop_vmpy(_VREG(60), _VREG(63), _VREG(47), _PREG(0));
   __vcop_vmpy(_VREG(59), _VREG(64), _VREG(50), _PREG(0));
   __vcop_vmpy(_VREG(59), _VREG(63), _VREG(53), _PREG(0));
   __vcop_vmpy(_VREG(60), _VREG(64), _VREG(54), _PREG(0));
   __vcop_vshf16(_VREG(47), _VREG(49), _VREG(48));
   __vcop_vshf16(_VREG(50), _VREG(52), _VREG(51));
   __vcop_vadd3(_VREG(49), _VREG(52), _VREG(54));
   __vcop_vadd3(_VREG(48), _VREG(51), _VREG(53));
   __vcop_vaddh(_VREG(53), _VREG(54), _VREG(53));
   __vcop_vmpy(_VREG(62), _VREG(61), _VREG(47), _PREG(0));
   __vcop_vmpy(_VREG(61), _VREG(61), _VREG(55), _PREG(0));
   __vcop_vmpy(_VREG(62), _VREG(62), _VREG(56), _PREG(0));
   __vcop_vshf16(_VREG(47), _VREG(49), _VREG(48));
   __vcop_vadd3(_VREG(49), _VREG(49), _VREG(56));
   __vcop_vadd3(_VREG(48), _VREG(48), _VREG(55));
   __vcop_vaddh(_VREG(55), _VREG(56), _VREG(55));
   __vcop_vand(_VREG(54), _VREG(46), _VREG(54));
   __vcop_vand(_VREG(56), _VREG(46), _VREG(56));
   __vcop_vsub(_VREG(54), _VREG(56), _VREG(58));
   __vcop_vsub(_VREG(53), _VREG(55), _VREG(57));
   __vcop_vaddh(_VREG(57), _VREG(58), _VREG(57));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeWU(), __vcop_npt(), __vcop_alws(), _VREG(58), _PREG(16), _AGEN(1), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeW(), __vcop_npt(), __vcop_alws(), _VREG(57), _PREG(18), _AGEN(1), _PREG(0));
   __vcop_vloop_end(3u);

   /* VLOOP 4 Start */

   /* VLOOP Local Vector Registers */
   #pragma VCC_VREG("K", 65);
   #pragma VCC_VREG("VA", 66);
   #pragma VCC_VREG("VB", 67);
   #pragma VCC_VREG("VC", 68);
   #pragma VCC_VREG("VD", 69);
   #pragma VCC_VREG("VK16", 70);
   #pragma VCC_VREG("VK32", 71);
   #pragma VCC_VREG("VM15", 72);
   #pragma VCC_VREG("VM16", 73);
   #pragma VCC_VREG("Vmask", 74);
   #pragma VCC_VREG("Vmask_s", 75);
   #pragma VCC_VREG("Vt1", 76);
   #pragma VCC_VREG("Vt2", 77);
   #pragma VCC_VREG("Vt2H", 78);
   #pragma VCC_VREG("Vt2L", 79);
   #pragma VCC_VREG("Vt3", 80);
   #pragma VCC_VREG("Vt3H", 81);
   #pragma VCC_VREG("Vt3L", 82);
   #pragma VCC_VREG("Vt4", 83);
   #pragma VCC_VREG("Z", 84);
   #pragma VCC_VREG("d1_h", 85);
   #pragma VCC_VREG("d1_l", 86);
   #pragma VCC_VREG("d2_l", 87);
   #pragma VCC_VREG("d_h", 88);
   #pragma VCC_VREG("d_l", 89);
   #pragma VCC_VREG("t1", 90);
   #pragma VCC_VREG("t2", 91);
   #pragma VCC_VREG("t3", 92);
   #pragma VCC_VREG("trace", 93);
   #pragma VCC_VREG("zxx", 94);
   #pragma VCC_VREG("zyy", 95);
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("Addr1", "A0");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I1", "I4");
   

   __vcop_vloop(__vcop_compute(), 55u, 14u, 4u);
   __vcop_vinit(__vcop_sizeWU(), __vcop_alws(), _PREG(10), _VREG(74));
   __vcop_vinit(__vcop_sizeHU(), __vcop_alws(), _PREG(12), _VREG(75));
   __vcop_vinit(__vcop_sizeW(), __vcop_alws(), _PREG(14), _VREG(65));
   __vcop_vinit(__vcop_sizeW(), __vcop_alws(), _PREG(16), _VREG(70));
   __vcop_vinit(__vcop_sizeW(), __vcop_alws(), _PREG(18), _VREG(73));
   __vcop_vinit(__vcop_sizeW(), __vcop_alws(), _PREG(20), _VREG(72));
   __vcop_vinit(__vcop_sizeW(), __vcop_alws(), _PREG(22), _VREG(71));
   __vcop_vinit(__vcop_sizeW(), __vcop_alws(), _PREG(24), _VREG(84));
   __vcop_vagen(_AGEN(0), _PREG(13), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeW(), __vcop_npt(), _PREG(26), _AGEN(0), _VREG(94), __vcop_alws());
   __vcop_vload(__vcop_sizeW(), __vcop_npt(), _PREG(28), _AGEN(0), _VREG(95), __vcop_alws());
   __vcop_vload(__vcop_sizeWU(), __vcop_npt(), _PREG(6), _AGEN(0), _VREG(89), __vcop_alws());
   __vcop_vload(__vcop_sizeW(), __vcop_npt(), _PREG(8), _AGEN(0), _VREG(88), __vcop_alws());
   __vcop_vadd(_VREG(94), _VREG(95), _VREG(93));
   __vcop_vshf(_VREG(93), _VREG(73), _VREG(66));
   __vcop_vand(_VREG(93), _VREG(75), _VREG(67));
   __vcop_vmpy(_VREG(66), _VREG(65), _VREG(80), _PREG(0));
   __vcop_vmpy(_VREG(67), _VREG(65), _VREG(83), _PREG(0));
   __vcop_vshf(_VREG(80), _VREG(70), _VREG(82));
   __vcop_vshf(_VREG(80), _VREG(73), _VREG(85));
   __vcop_vand(_VREG(82), _VREG(74), _VREG(82));
   __vcop_vadd(_VREG(83), _VREG(82), _VREG(83));
   __vcop_vaddh(_VREG(85), _VREG(83), _VREG(85));
   __vcop_vand(_VREG(83), _VREG(74), _VREG(86));
   __vcop_vshf(_VREG(86), _VREG(72), _VREG(76));
   __vcop_vadd(_VREG(71), _VREG(72), _VREG(68));
   __vcop_vshf(_VREG(85), _VREG(68), _VREG(77));
   __vcop_vor(_VREG(76), _VREG(77), _VREG(87));
   __vcop_vand(_VREG(87), _VREG(74), _VREG(87));
   __vcop_vshf(_VREG(87), _VREG(73), _VREG(68));
   __vcop_vand(_VREG(87), _VREG(75), _VREG(69));
   __vcop_vmpy(_VREG(67), _VREG(68), _VREG(77), _PREG(0));
   __vcop_vmpy(_VREG(66), _VREG(69), _VREG(80), _PREG(0));
   __vcop_vshf16(_VREG(77), _VREG(79), _VREG(78));
   __vcop_vshf16(_VREG(80), _VREG(82), _VREG(81));
   __vcop_vmpy(_VREG(66), _VREG(68), _VREG(85), _PREG(0));
   __vcop_vmpy(_VREG(67), _VREG(69), _VREG(83), _PREG(0));
   __vcop_vadd3(_VREG(79), _VREG(82), _VREG(83));
   __vcop_vadd3(_VREG(78), _VREG(81), _VREG(85));
   __vcop_vaddh(_VREG(85), _VREG(83), _VREG(85));
   __vcop_vand(_VREG(83), _VREG(74), _VREG(86));
   __vcop_vcmpeq(_VREG(88), _VREG(85), _VREG(91));
   __vcop_vcmplt(_VREG(89), _VREG(86), _VREG(92));
   __vcop_vand(_VREG(91), _VREG(92), _VREG(90));
   __vcop_vcmplt(_VREG(88), _VREG(85), _VREG(92));
   __vcop_vor(_VREG(90), _VREG(92), _VREG(90));
   __vcop_vsub(_VREG(89), _VREG(86), _VREG(76));
   __vcop_vsub(_VREG(88), _VREG(85), _VREG(88));
   __vcop_vaddh(_VREG(88), _VREG(76), _VREG(88));
   __vcop_vand(_VREG(76), _VREG(74), _VREG(89));
   __vcop_vsel(_VREG(90), _VREG(84), _VREG(88));
   __vcop_vsel(_VREG(90), _VREG(84), _VREG(89));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeWU(), __vcop_npt(), __vcop_alws(), _VREG(89), _PREG(6), _AGEN(0), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeW(), __vcop_npt(), __vcop_alws(), _VREG(88), _PREG(8), _AGEN(0), _PREG(0));
   __vcop_vloop_end(4u);

   /* VLOOP 5 Start */

   /* VLOOP Local Vector Registers */
   #pragma VCC_VREG("V4np", 96);
   #pragma VCC_VREG("Vnp", 97);
   #pragma VCC_VREG("Vscore_preg", 98);
   #pragma VCC_VREG("Vscore_preg_new", 99);
   #pragma VCC_VREG("Vseq", 100);
   #pragma VCC_VREG("Vstart", 101);
   #pragma VCC_VREG("VstartIdx_preg", 102);
   #pragma VCC_VREG("VstartIdx_preg_new", 103);
   #pragma VCC_VREG("Nexp", 104);
   #pragma VCC_VREG("ONE", 105);
   #pragma VCC_VREG("VA", 106);
   #pragma VCC_VREG("VB", 107);
   #pragma VCC_VREG("VC", 108);
   #pragma VCC_VREG("VD", 109);
   #pragma VCC_VREG("VK10", 110);
   #pragma VCC_VREG("VK32", 111);
   #pragma VCC_VREG("VK8", 112);
   #pragma VCC_VREG("Vidx", 113);
   #pragma VCC_VREG("Z", 114);
   #pragma VCC_VREG("d1_h", 115);
   #pragma VCC_VREG("d1_l", 116);
   #pragma VCC_VREG("d_h", 117);
   #pragma VCC_VREG("d_l", 118);
   #pragma VCC_VREG("exp", 119);
   #pragma VCC_VREG("lmb", 120);
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("seqAddr", "A0");
   #pragma EVE_REG("Addr1", "A1");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I2", "I3");
   #pragma EVE_REG("I1", "I4");
   

   __vcop_vloop(__vcop_compute(), 40u, 17u, 5u);
   __vcop_vinit(__vcop_sizeW(), __vcop_i4_zero(), _PREG(32), _VREG(101));
   __vcop_vinit(__vcop_sizeW(), __vcop_i4_zero(), _PREG(34), _VREG(97));
   __vcop_vinit(__vcop_sizeW(), __vcop_i4_zero(), _PREG(6), _VREG(96));
   __vcop_vinit(__vcop_sizeW(), __vcop_alws(), _PREG(14), _VREG(114));
   __vcop_vinit(__vcop_sizeW(), __vcop_alws(), _PREG(16), _VREG(105));
   __vcop_vinit(__vcop_sizeW(), __vcop_alws(), _PREG(18), _VREG(112));
   __vcop_vinit(__vcop_sizeW(), __vcop_alws(), _PREG(20), _VREG(110));
   __vcop_vinit(__vcop_sizeW(), __vcop_alws(), _PREG(22), _VREG(111));
   __vcop_vagen(_AGEN(0), _PREG(0), _PREG(1), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(1), _PREG(30), _PREG(31), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeHU(), __vcop_npt(), _PREG(8), _AGEN(0), _VREG(100), __vcop_i4_zero());
   __vcop_vload(__vcop_sizeW(), __vcop_1pt(), _PREG(10), _AGEN(0), _VREG(98), __vcop_i4_zero());
   __vcop_vload(__vcop_sizeW(), __vcop_1pt(), _PREG(12), _AGEN(0), _VREG(102), __vcop_i4_zero());
   __vcop_vload(__vcop_sizeWU(), __vcop_npt(), _PREG(24), _AGEN(1), _VREG(118), __vcop_alws());
   __vcop_vload(__vcop_sizeW(), __vcop_npt(), _PREG(26), _AGEN(1), _VREG(117), __vcop_alws());
   __vcop_vlmbd(_VREG(118), _VREG(105), _VREG(108));
   __vcop_vlmbd(_VREG(117), _VREG(105), _VREG(109));
   __vcop_vadd(_VREG(108), _VREG(105), _VREG(108));
   __vcop_vadd(_VREG(109), _VREG(105), _VREG(109));
   __vcop_vcmpeq(_VREG(109), _VREG(114), _VREG(106));
   __vcop_vadd(_VREG(109), _VREG(111), _VREG(120));
   __vcop_vsel(_VREG(106), _VREG(108), _VREG(120));
   __vcop_vcmple(_VREG(120), _VREG(110), _VREG(106));
   __vcop_vsub(_VREG(120), _VREG(110), _VREG(119));
   __vcop_vsel(_VREG(106), _VREG(114), _VREG(119));
   __vcop_vsub(_VREG(114), _VREG(119), _VREG(104));
   __vcop_vshf(_VREG(117), _VREG(104), _VREG(115));
   __vcop_vshf(_VREG(118), _VREG(104), _VREG(116));
   __vcop_vsub(_VREG(111), _VREG(119), _VREG(107));
   __vcop_vshfor(_VREG(117), _VREG(107), _VREG(116));
   __vcop_vor(_VREG(116), _VREG(115), _VREG(116));
   __vcop_vshfor(_VREG(119), _VREG(110), _VREG(116));
   __vcop_vadd(_VREG(101), _VREG(112), _VREG(101));
   __vcop_vadd(_VREG(100), _VREG(101), _VREG(113));
   __vcop_vadd(_VREG(102), _VREG(97), _VREG(103));
   __vcop_vadd(_VREG(98), _VREG(96), _VREG(99));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeHU(), __vcop_intrlv(), __vcop_alws(), _VPAIR(113,116), _PREG(28), _AGEN(1), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeW(), __vcop_1pt(), __vcop_last_i4(), _VREG(99), _PREG(10), _AGEN(0), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeW(), __vcop_1pt(), __vcop_last_i4(), _VREG(103), _PREG(12), _AGEN(0), _PREG(0));
   __vcop_vloop_end(5u);

}

void vcop_multipoint_harrisScore_7x7_u16(
   __vptr_uint8 pImgBlocks_A,
   __vptr_uint16 harrisScore_C,
   unsigned short numPoints,
   unsigned short inputStride,
   unsigned short interBlockOffset,
   unsigned short sensitivityParam,
   short start_idx,
   __vptr_uint16 seq_array_C,
   __vptr_int32 vertSumX2_C,
   __vptr_int32 vertSumY2_B,
   __vptr_int32 vertSumXY_C,
   __vptr_int32 Ixx_A,
   __vptr_int32 Iyy_C,
   __vptr_int32 Ixy_A,
   __vptr_uint16 Ixx_l,
   __vptr_uint16 Iyy_l,
   __vptr_uint16 Ixy_l,
   __vptr_int16 Ixx_h,
   __vptr_int16 Iyy_h,
   __vptr_int16 Ixy_h,
   __vptr_uint32 detL_C,
   __vptr_int32 detH_C,
   __vptr_int32 pBlock)
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_multipoint_harrisScore_7x7_u16_init(pImgBlocks_A, harrisScore_C, numPoints, inputStride, interBlockOffset, sensitivityParam, start_idx, seq_array_C, vertSumX2_C, vertSumY2_B, vertSumXY_C, Ixx_A, Iyy_C, Ixy_A, Ixx_l, Iyy_l, Ixy_l, Ixx_h, Iyy_h, Ixy_h, detL_C, detH_C, pBlock, __pblock_vcop_multipoint_harrisScore_7x7_u16);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_multipoint_harrisScore_7x7_u16_vloops(__pblock_vcop_multipoint_harrisScore_7x7_u16);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

void vcop_multipoint_harrisScore_7x7_u16_custom(
   __vptr_uint8 pImgBlocks_A,
   __vptr_uint16 harrisScore_C,
   unsigned short numPoints,
   unsigned short inputStride,
   unsigned short interBlockOffset,
   unsigned short sensitivityParam,
   short start_idx,
   __vptr_uint16 seq_array_C,
   __vptr_int32 vertSumX2_C,
   __vptr_int32 vertSumY2_B,
   __vptr_int32 vertSumXY_C,
   __vptr_int32 Ixx_A,
   __vptr_int32 Iyy_C,
   __vptr_int32 Ixy_A,
   __vptr_uint16 Ixx_l,
   __vptr_uint16 Iyy_l,
   __vptr_uint16 Ixy_l,
   __vptr_int16 Ixx_h,
   __vptr_int16 Iyy_h,
   __vptr_int16 Ixy_h,
   __vptr_uint32 detL_C,
   __vptr_int32 detH_C,
   __vptr_int32 pBlock,
   unsigned short pblock[])
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_multipoint_harrisScore_7x7_u16_init(pImgBlocks_A, harrisScore_C, numPoints, inputStride, interBlockOffset, sensitivityParam, start_idx, seq_array_C, vertSumX2_C, vertSumY2_B, vertSumXY_C, Ixx_A, Iyy_C, Ixy_A, Ixx_l, Iyy_l, Ixy_l, Ixx_h, Iyy_h, Ixy_h, detL_C, detH_C, pBlock, pblock);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_multipoint_harrisScore_7x7_u16_vloops(pblock);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

