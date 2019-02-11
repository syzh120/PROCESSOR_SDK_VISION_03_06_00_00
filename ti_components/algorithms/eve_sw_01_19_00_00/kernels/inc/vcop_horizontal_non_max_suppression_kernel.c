#include <vcop\vcop.h>

typedef unsigned char uchar;

#pragma DATA_SECTION(__pblock_vcop_horizontal_non_max_suppression, ".vcop_parameter_block")
#pragma DATA_ALIGN(__pblock_vcop_horizontal_non_max_suppression, __ALIGNOF__(int));
unsigned short __pblock_vcop_horizontal_non_max_suppression[116];

unsigned int vcop_horizontal_non_max_suppression_param_count(void)
{
   return 116u;
}

unsigned int vcop_horizontal_non_max_suppression_ctrl_count(void)
{
   return 0u;
}

unsigned int vcop_horizontal_non_max_suppression_init(
   __vptr_uint32 pInXY,
   unsigned short num_corners,
   unsigned short max_corners,
   __vptr_uint16 Score,
   __vptr_uint32 pack_XY,
   __vptr_uint16 nms_X_Score,
   __vptr_uint8 Id_list,
   unsigned short pblock[])
{
   int __offset = 0;
   /* Loop 1 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), (1)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), ((num_corners+(8u)-1)/(8u))-1u);
   __vcop_pblock_init32(pblock, __offset+_PREG(6), 12);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), 8);
   __vcop_pblock_init32(pblock, __offset+_PREG(10), 0x10000);
   __vcop_pblock_init32(pblock, __offset+_PREG(12), 0);
   __vcop_pblock_init32(pblock, __offset+_PREG(14), 4294901760);
   __vcop_pblock_init32(pblock, __offset+_PREG(16), 0x0000FFFF);
   __vcop_pblock_init32(pblock, __offset+_PREG(18), 1);
   __vcop_pblock_init32(pblock, __offset+_PREG(20), (uchar *)pInXY);
   __vcop_pblock_init32(pblock, __offset+_PREG(22), (uchar *)pInXY+sizeof(*pInXY));
   __vcop_pblock_init32(pblock, __offset+_PREG(24), (uchar *)pInXY+2*sizeof(*pInXY));
   __vcop_pblock_init32(pblock, __offset+_PREG(26), (uchar *)Score);
   __vcop_pblock_init32(pblock, __offset+_PREG(28), (uchar *)Score+sizeof(*Score));
   __vcop_pblock_init32(pblock, __offset+_PREG(30), (uchar *)Score+2*sizeof(*Score));
   __vcop_pblock_init32(pblock, __offset+_PREG(32), (uchar *)nms_X_Score+sizeof(*Score));
   __vcop_pblock_init32(pblock, __offset+_PREG(34), (uchar *)pack_XY+sizeof(*pack_XY));
   __vcop_pblock_init16(pblock, __offset+_PREG(36), 32);
   __vcop_pblock_init16(pblock, __offset+_PREG(37),  -((8u*sizeof(*pInXY)))*(((num_corners+(8u)-1)/(8u))-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(38), 16);
   __vcop_pblock_init16(pblock, __offset+_PREG(39),  -((8u*sizeof(*Score)))*(((num_corners+(8u)-1)/(8u))-1u));
   __vcop_pblock_init32(pblock, __offset+_PREG(40), (uchar *)Id_list);
   __vcop_pblock_init32(pblock, __offset+_PREG(42), 6);
   __offset += 42;

   /* Loop 2 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), (1)-1u);
   __vcop_pblock_init32(pblock, __offset+_PREG(6), 0);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), 0x10000);
   __vcop_pblock_init32(pblock, __offset+_PREG(10), 4294901760);
   __vcop_pblock_init32(pblock, __offset+_PREG(12), 0x0000FFFF);
   __vcop_pblock_init32(pblock, __offset+_PREG(14), 1);
   __vcop_pblock_init32(pblock, __offset+_PREG(16), (uchar *)pInXY);
   __vcop_pblock_init32(pblock, __offset+_PREG(18), (uchar *)pInXY+sizeof(*pInXY));
   __vcop_pblock_init32(pblock, __offset+_PREG(20), (uchar *)Score);
   __vcop_pblock_init32(pblock, __offset+_PREG(22), (uchar *)Score+sizeof(*Score));
   __vcop_pblock_init32(pblock, __offset+_PREG(24), (uchar *)pack_XY);
   __vcop_pblock_init32(pblock, __offset+_PREG(26), (uchar *)nms_X_Score);
   __vcop_pblock_init32(pblock, __offset+_PREG(28), 6);
   __vcop_pblock_init32(pblock, __offset+_PREG(30), 12);
   __offset += 30;

   /* Loop 3 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), (1)-1u);
   __vcop_pblock_init32(pblock, __offset+_PREG(6), 0);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), num_corners - 1);
   __vcop_pblock_init32(pblock, __offset+_PREG(10), 0x10000);
   __vcop_pblock_init32(pblock, __offset+_PREG(12), 4294901760);
   __vcop_pblock_init32(pblock, __offset+_PREG(14), 0x0000FFFF);
   __vcop_pblock_init32(pblock, __offset+_PREG(16), 1);
   __vcop_pblock_init32(pblock, __offset+_PREG(18), (uchar *)pInXY+(num_corners-2)*sizeof(*pInXY));
   __vcop_pblock_init32(pblock, __offset+_PREG(20), (uchar *)pInXY+(num_corners-1)*sizeof(*pInXY));
   __vcop_pblock_init32(pblock, __offset+_PREG(22), (uchar *)Score+(num_corners-2)*sizeof(*Score));
   __vcop_pblock_init32(pblock, __offset+_PREG(24), (uchar *)Score+(num_corners-1)*sizeof(*Score));
   __vcop_pblock_init32(pblock, __offset+_PREG(26), (uchar *)pack_XY+(num_corners-1)*sizeof(*pack_XY));
   __vcop_pblock_init32(pblock, __offset+_PREG(28), (uchar *)nms_X_Score+(num_corners-1)*sizeof(*Score));
   __vcop_pblock_init32(pblock, __offset+_PREG(30), 6);
   __vcop_pblock_init32(pblock, __offset+_PREG(32), 12);
   __offset += 32;

   /* Loop 4 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), ((max_corners-num_corners+(8u)-1)/(8u))-1u);
   __vcop_pblock_init32(pblock, __offset+_PREG(6), (uchar *)pack_XY+num_corners*sizeof(*pInXY));
   __vcop_pblock_init16(pblock, __offset+_PREG(8), 32);
   __vcop_pblock_init16(pblock, __offset+_PREG(9), 16);
   __vcop_pblock_init32(pblock, __offset+_PREG(10), 0);
   __vcop_pblock_init32(pblock, __offset+_PREG(12), (uchar *)nms_X_Score+num_corners*sizeof(*Score));
   __offset += 12;

   return 116u;
}

void vcop_horizontal_non_max_suppression_vloops(
   unsigned short pblock[])
{
   /* Kernel-wide Vector Registers */

   __vcop_param(&pblock[0]);

   /* VLOOP 1 Start */

   /* VLOOP Local Vector Registers */
   #pragma VCC_VREG("id", 16);
   #pragma VCC_VREG("Vconst", 17);
   #pragma VCC_VREG("Vconst12", 18);
   #pragma VCC_VREG("Vconst6", 19);
   #pragma VCC_VREG("Vconst8", 20);
   #pragma VCC_VREG("Vf1", 21);
   #pragma VCC_VREG("Vf2", 22);
   #pragma VCC_VREG("Vin1", 23);
   #pragma VCC_VREG("Vin2", 24);
   #pragma VCC_VREG("Vin3", 25);
   #pragma VCC_VREG("Vmask1", 26);
   #pragma VCC_VREG("Vmask2", 27);
   #pragma VCC_VREG("Vnf1", 28);
   #pragma VCC_VREG("Vnf2", 29);
   #pragma VCC_VREG("Vone", 30);
   #pragma VCC_VREG("Vscore1", 31);
   #pragma VCC_VREG("Vscore2", 32);
   #pragma VCC_VREG("Vscore3", 33);
   #pragma VCC_VREG("Vsf1", 34);
   #pragma VCC_VREG("Vsf2", 35);
   #pragma VCC_VREG("Vzero", 36);
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("Addr0", "A0");
   #pragma EVE_REG("Addr1", "A1");
   #pragma EVE_REG("Addr2", "A2");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I2", "I3");
   #pragma EVE_REG("I3", "I4");
   

   __vcop_vloop(__vcop_compute(), 38u, 21u, 1u);
   __vcop_vinit(__vcop_sizeW(), __vcop_alws(), _PREG(42), _VREG(19));
   __vcop_vinit(__vcop_sizeW(), __vcop_alws(), _PREG(6), _VREG(18));
   __vcop_vinit(__vcop_sizeW(), __vcop_alws(), _PREG(8), _VREG(20));
   __vcop_vinit(__vcop_sizeW(), __vcop_alws(), _PREG(10), _VREG(17));
   __vcop_vinit(__vcop_sizeW(), __vcop_alws(), _PREG(12), _VREG(36));
   __vcop_vinit(__vcop_sizeWU(), __vcop_alws(), _PREG(14), _VREG(26));
   __vcop_vinit(__vcop_sizeW(), __vcop_alws(), _PREG(16), _VREG(27));
   __vcop_vinit(__vcop_sizeW(), __vcop_alws(), _PREG(18), _VREG(30));
   __vcop_vagen(_AGEN(0), _PREG(0), _PREG(1), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(1), _PREG(36), _PREG(37), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(2), _PREG(38), _PREG(39), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeBU(), __vcop_npt(), _PREG(40), _AGEN(0), _VREG(16), __vcop_i4_zero());
   __vcop_vload(__vcop_sizeWU(), __vcop_npt(), _PREG(20), _AGEN(1), _VREG(23), __vcop_alws());
   __vcop_vload(__vcop_sizeWU(), __vcop_npt(), _PREG(22), _AGEN(1), _VREG(24), __vcop_alws());
   __vcop_vload(__vcop_sizeWU(), __vcop_npt(), _PREG(24), _AGEN(1), _VREG(25), __vcop_alws());
   __vcop_vload(__vcop_sizeHU(), __vcop_npt(), _PREG(26), _AGEN(2), _VREG(31), __vcop_alws());
   __vcop_vload(__vcop_sizeHU(), __vcop_npt(), _PREG(28), _AGEN(2), _VREG(32), __vcop_alws());
   __vcop_vload(__vcop_sizeHU(), __vcop_npt(), _PREG(30), _AGEN(2), _VREG(33), __vcop_alws());
   __vcop_vadd(_VREG(23), _VREG(17), _VREG(23));
   __vcop_vsub(_VREG(25), _VREG(17), _VREG(25));
   __vcop_vcmpeq(_VREG(23), _VREG(24), _VREG(28));
   __vcop_vcmpeq(_VREG(25), _VREG(24), _VREG(29));
   __vcop_vcmple(_VREG(32), _VREG(31), _VREG(34));
   __vcop_vcmple(_VREG(32), _VREG(33), _VREG(35));
   __vcop_vand(_VREG(28), _VREG(34), _VREG(21));
   __vcop_vand(_VREG(29), _VREG(35), _VREG(22));
   __vcop_vor(_VREG(21), _VREG(22), _VREG(21));
   __vcop_vsub(_VREG(30), _VREG(21), _VREG(22));
   __vcop_vand(_VREG(24), _VREG(26), _VREG(28));
   __vcop_vand(_VREG(24), _VREG(27), _VREG(29));
   __vcop_vshf(_VREG(28), _VREG(19), _VREG(34));
   __vcop_vshf(_VREG(29), _VREG(18), _VREG(35));
   __vcop_vor3(_VREG(34), _VREG(16), _VREG(35));
   __vcop_vadd(_VREG(16), _VREG(20), _VREG(16));
   __vcop_vstore(__vcop_predicate(_VREG(21)), __vcop_sizeHU(), __vcop_npt(), __vcop_alws(), _VREG(36), _PREG(32), _AGEN(2), _PREG(0));
   __vcop_vstore(__vcop_predicate(_VREG(22)), __vcop_sizeHU(), __vcop_npt(), __vcop_alws(), _VREG(32), _PREG(32), _AGEN(2), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeWU(), __vcop_npt(), __vcop_alws(), _VREG(35), _PREG(34), _AGEN(1), _PREG(0));
   __vcop_vloop_end(1u);

   /* VLOOP 2 Start */

   /* VLOOP Local Vector Registers */
   #pragma VCC_VREG("Score1", 37);
   #pragma VCC_VREG("Score_zero", 38);
   #pragma VCC_VREG("Vconst", 39);
   #pragma VCC_VREG("Vconst12", 40);
   #pragma VCC_VREG("Vconst6", 41);
   #pragma VCC_VREG("Vf1", 42);
   #pragma VCC_VREG("Vin1", 43);
   #pragma VCC_VREG("Vin2", 44);
   #pragma VCC_VREG("Vmask1", 45);
   #pragma VCC_VREG("Vmask2", 46);
   #pragma VCC_VREG("Vnf1", 47);
   #pragma VCC_VREG("Vone", 48);
   #pragma VCC_VREG("Vout1", 49);
   #pragma VCC_VREG("Vsf1", 50);
   #pragma VCC_VREG("Vx1", 51);
   #pragma VCC_VREG("Vy1", 52);
   #pragma VCC_VREG("Vzero", 53);
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("Addr0", "A0");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I3", "I4");
   

   __vcop_vloop(__vcop_compute(), 26u, 15u, 2u);
   __vcop_vinit(__vcop_sizeW(), __vcop_alws(), _PREG(28), _VREG(41));
   __vcop_vinit(__vcop_sizeW(), __vcop_alws(), _PREG(30), _VREG(40));
   __vcop_vinit(__vcop_sizeW(), __vcop_alws(), _PREG(6), _VREG(53));
   __vcop_vinit(__vcop_sizeW(), __vcop_alws(), _PREG(8), _VREG(39));
   __vcop_vinit(__vcop_sizeWU(), __vcop_alws(), _PREG(10), _VREG(45));
   __vcop_vinit(__vcop_sizeW(), __vcop_alws(), _PREG(12), _VREG(46));
   __vcop_vinit(__vcop_sizeW(), __vcop_alws(), _PREG(14), _VREG(48));
   __vcop_vagen(_AGEN(0), _PREG(1), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeWU(), __vcop_1pt(), _PREG(16), _AGEN(0), _VREG(43), __vcop_alws());
   __vcop_vload(__vcop_sizeWU(), __vcop_1pt(), _PREG(18), _AGEN(0), _VREG(44), __vcop_alws());
   __vcop_vload(__vcop_sizeHU(), __vcop_1pt(), _PREG(20), _AGEN(0), _VREG(38), __vcop_alws());
   __vcop_vload(__vcop_sizeHU(), __vcop_1pt(), _PREG(22), _AGEN(0), _VREG(37), __vcop_alws());
   __vcop_vsub(_VREG(44), _VREG(39), _VREG(44));
   __vcop_vand(_VREG(43), _VREG(46), _VREG(52));
   __vcop_vcmple(_VREG(38), _VREG(37), _VREG(50));
   __vcop_vcmpeq(_VREG(43), _VREG(44), _VREG(47));
   __vcop_vand(_VREG(47), _VREG(50), _VREG(42));
   __vcop_vand(_VREG(43), _VREG(45), _VREG(51));
   __vcop_vsub(_VREG(48), _VREG(42), _VREG(47));
   __vcop_vshf(_VREG(51), _VREG(41), _VREG(49));
   __vcop_vshfor(_VREG(52), _VREG(40), _VREG(49));
   __vcop_vor(_VREG(49), _VREG(53), _VREG(49));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeWU(), __vcop_1pt(), __vcop_alws(), _VREG(49), _PREG(24), _AGEN(0), _PREG(0));
   __vcop_vstore(__vcop_predicate(_VREG(42)), __vcop_sizeHU(), __vcop_1pt(), __vcop_alws(), _VREG(53), _PREG(26), _AGEN(0), _PREG(0));
   __vcop_vstore(__vcop_predicate(_VREG(47)), __vcop_sizeHU(), __vcop_1pt(), __vcop_alws(), _VREG(38), _PREG(26), _AGEN(0), _PREG(0));
   __vcop_vloop_end(2u);

   /* VLOOP 3 Start */

   /* VLOOP Local Vector Registers */
   #pragma VCC_VREG("Score_last", 54);
   #pragma VCC_VREG("Score_last_1", 55);
   #pragma VCC_VREG("Vconst", 56);
   #pragma VCC_VREG("Vconst12", 57);
   #pragma VCC_VREG("Vconst6", 58);
   #pragma VCC_VREG("Vf1", 59);
   #pragma VCC_VREG("Vin1", 60);
   #pragma VCC_VREG("Vin2", 61);
   #pragma VCC_VREG("Vlast", 62);
   #pragma VCC_VREG("Vmask1", 63);
   #pragma VCC_VREG("Vmask2", 64);
   #pragma VCC_VREG("Vnf1", 65);
   #pragma VCC_VREG("Vone", 66);
   #pragma VCC_VREG("Vout1", 67);
   #pragma VCC_VREG("Vsf1", 68);
   #pragma VCC_VREG("Vx1", 69);
   #pragma VCC_VREG("Vy1", 70);
   #pragma VCC_VREG("Vzero", 71);
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("Addr0", "A0");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I3", "I4");
   

   __vcop_vloop(__vcop_compute(), 27u, 16u, 3u);
   __vcop_vinit(__vcop_sizeW(), __vcop_alws(), _PREG(30), _VREG(58));
   __vcop_vinit(__vcop_sizeW(), __vcop_alws(), _PREG(32), _VREG(57));
   __vcop_vinit(__vcop_sizeW(), __vcop_alws(), _PREG(6), _VREG(71));
   __vcop_vinit(__vcop_sizeW(), __vcop_alws(), _PREG(8), _VREG(62));
   __vcop_vinit(__vcop_sizeW(), __vcop_alws(), _PREG(10), _VREG(56));
   __vcop_vinit(__vcop_sizeWU(), __vcop_alws(), _PREG(12), _VREG(63));
   __vcop_vinit(__vcop_sizeW(), __vcop_alws(), _PREG(14), _VREG(64));
   __vcop_vinit(__vcop_sizeW(), __vcop_alws(), _PREG(16), _VREG(66));
   __vcop_vagen(_AGEN(0), _PREG(1), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeWU(), __vcop_1pt(), _PREG(18), _AGEN(0), _VREG(60), __vcop_alws());
   __vcop_vload(__vcop_sizeWU(), __vcop_1pt(), _PREG(20), _AGEN(0), _VREG(61), __vcop_alws());
   __vcop_vload(__vcop_sizeHU(), __vcop_1pt(), _PREG(22), _AGEN(0), _VREG(55), __vcop_alws());
   __vcop_vload(__vcop_sizeHU(), __vcop_1pt(), _PREG(24), _AGEN(0), _VREG(54), __vcop_alws());
   __vcop_vadd(_VREG(60), _VREG(56), _VREG(60));
   __vcop_vand(_VREG(61), _VREG(64), _VREG(70));
   __vcop_vcmple(_VREG(54), _VREG(55), _VREG(68));
   __vcop_vcmpeq(_VREG(60), _VREG(61), _VREG(65));
   __vcop_vand(_VREG(61), _VREG(63), _VREG(69));
   __vcop_vand(_VREG(65), _VREG(68), _VREG(59));
   __vcop_vsub(_VREG(66), _VREG(59), _VREG(65));
   __vcop_vshf(_VREG(69), _VREG(58), _VREG(67));
   __vcop_vshfor(_VREG(70), _VREG(57), _VREG(67));
   __vcop_vor(_VREG(67), _VREG(62), _VREG(67));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeWU(), __vcop_1pt(), __vcop_alws(), _VREG(67), _PREG(26), _AGEN(0), _PREG(0));
   __vcop_vstore(__vcop_predicate(_VREG(59)), __vcop_sizeHU(), __vcop_1pt(), __vcop_alws(), _VREG(71), _PREG(28), _AGEN(0), _PREG(0));
   __vcop_vstore(__vcop_predicate(_VREG(65)), __vcop_sizeHU(), __vcop_1pt(), __vcop_alws(), _VREG(54), _PREG(28), _AGEN(0), _PREG(0));
   __vcop_vloop_end(3u);

   /* VLOOP 4 Start */

   /* VLOOP Local Vector Registers */
   #pragma VCC_VREG("Vzero", 72);
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("Addr0", "A0");
   #pragma EVE_REG("Addr1", "A1");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I3", "I4");
   

   __vcop_vloop(__vcop_compute(), 6u, 6u, 4u);
   __vcop_vinit(__vcop_sizeW(), __vcop_alws(), _PREG(10), _VREG(72));
   __vcop_vagen(_AGEN(0), _PREG(8), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(1), _PREG(9), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeHU(), __vcop_npt(), __vcop_alws(), _VREG(72), _PREG(12), _AGEN(1), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeWU(), __vcop_npt(), __vcop_alws(), _VREG(72), _PREG(6), _AGEN(0), _PREG(0));
   __vcop_vloop_end(4u);

}

void vcop_horizontal_non_max_suppression(
   __vptr_uint32 pInXY,
   unsigned short num_corners,
   unsigned short max_corners,
   __vptr_uint16 Score,
   __vptr_uint32 pack_XY,
   __vptr_uint16 nms_X_Score,
   __vptr_uint8 Id_list)
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_horizontal_non_max_suppression_init(pInXY, num_corners, max_corners, Score, pack_XY, nms_X_Score, Id_list, __pblock_vcop_horizontal_non_max_suppression);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_horizontal_non_max_suppression_vloops(__pblock_vcop_horizontal_non_max_suppression);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

void vcop_horizontal_non_max_suppression_custom(
   __vptr_uint32 pInXY,
   unsigned short num_corners,
   unsigned short max_corners,
   __vptr_uint16 Score,
   __vptr_uint32 pack_XY,
   __vptr_uint16 nms_X_Score,
   __vptr_uint8 Id_list,
   unsigned short pblock[])
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_horizontal_non_max_suppression_init(pInXY, num_corners, max_corners, Score, pack_XY, nms_X_Score, Id_list, pblock);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_horizontal_non_max_suppression_vloops(pblock);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

