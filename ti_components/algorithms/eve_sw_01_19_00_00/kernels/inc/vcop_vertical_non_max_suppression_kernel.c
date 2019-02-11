#include <vcop\vcop.h>

typedef unsigned char uchar;

#pragma DATA_SECTION(__pblock_vcop_vertical_non_max_suppression_kernel, ".vcop_parameter_block")
#pragma DATA_ALIGN(__pblock_vcop_vertical_non_max_suppression_kernel, __ALIGNOF__(int));
unsigned short __pblock_vcop_vertical_non_max_suppression_kernel[114];

unsigned int vcop_vertical_non_max_suppression_kernel_param_count(void)
{
   return 114u;
}

unsigned int vcop_vertical_non_max_suppression_kernel_ctrl_count(void)
{
   return 0u;
}

unsigned int vcop_vertical_non_max_suppression_kernel_init(
   __vptr_uint32 pack_XY,
   unsigned short num_corners,
   unsigned short max_corners,
   __vptr_uint16 nms_X_Score,
   __vptr_uint16 nms_id,
   __vptr_uint16 nms_Y_Score,
   __vptr_uint16 nms_Y_XY,
   __vptr_uint32 nms_Y1_XY,
   __vptr_uint32 nms_Score,
   __vptr_uint8 Id_list,
   unsigned short pblock[])
{
   int __offset = 0;
   /* Loop 1 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), ((num_corners+(8u)-1)/(8u))-1u);
   __vcop_pblock_init32(pblock, __offset+_PREG(6), 0x003FF000);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), 0x00000FFF);
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)pack_XY);
   __vcop_pblock_init32(pblock, __offset+_PREG(12), (uchar *)nms_Y_XY);
   __vcop_pblock_init32(pblock, __offset+_PREG(14), (uchar *)nms_id);
   __vcop_pblock_init16(pblock, __offset+_PREG(16), 32);
   __vcop_pblock_init16(pblock, __offset+_PREG(17), 16);
   __vcop_pblock_init32(pblock, __offset+_PREG(18), -22);
   __vcop_pblock_init32(pblock, __offset+_PREG(20), -12);
   __offset += 20;

   /* Loop 2 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), (num_corners)-1u);
   __vcop_pblock_init32(pblock, __offset+_PREG(6), (uchar *)nms_Y_Score);
   __vcop_pblock_init16(pblock, __offset+_PREG(8), 2);
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)nms_id);
   __vcop_pblock_init32(pblock, __offset+_PREG(12), (uchar *)nms_X_Score);
   __offset += 12;

   /* Loop 3 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), (1)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), ((num_corners+(8u)-1)/(8u))-1u);
   __vcop_pblock_init32(pblock, __offset+_PREG(6), 8);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), 16);
   __vcop_pblock_init32(pblock, __offset+_PREG(10), 0);
   __vcop_pblock_init32(pblock, __offset+_PREG(12), (uchar *)nms_Y1_XY);
   __vcop_pblock_init32(pblock, __offset+_PREG(14), (uchar *)nms_Y1_XY+sizeof(*pack_XY));
   __vcop_pblock_init32(pblock, __offset+_PREG(16), (uchar *)nms_Y1_XY+2*sizeof(*pack_XY));
   __vcop_pblock_init32(pblock, __offset+_PREG(18), (uchar *)nms_Y_Score);
   __vcop_pblock_init32(pblock, __offset+_PREG(20), (uchar *)nms_Y_Score+sizeof(*nms_id));
   __vcop_pblock_init32(pblock, __offset+_PREG(22), (uchar *)nms_Y_Score+2*sizeof(*nms_id));
   __vcop_pblock_init32(pblock, __offset+_PREG(24), (uchar *)nms_Score+sizeof(*pack_XY));
   __vcop_pblock_init16(pblock, __offset+_PREG(26), 32);
   __vcop_pblock_init16(pblock, __offset+_PREG(27),  -(8u*sizeof(*pack_XY))*(((num_corners+(8u)-1)/(8u))-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(28), 16);
   __vcop_pblock_init16(pblock, __offset+_PREG(29),  -(8u*sizeof(*nms_id))*(((num_corners+(8u)-1)/(8u))-1u));
   __vcop_pblock_init32(pblock, __offset+_PREG(30), (uchar *)Id_list);
   __vcop_pblock_init32(pblock, __offset+_PREG(32), 1);
   __offset += 32;

   /* Loop 4 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), (1)-1u);
   __vcop_pblock_init32(pblock, __offset+_PREG(6), 1);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)nms_Y_Score);
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)nms_Y_Score+sizeof(*nms_id));
   __vcop_pblock_init32(pblock, __offset+_PREG(12), (uchar *)nms_Y1_XY);
   __vcop_pblock_init32(pblock, __offset+_PREG(14), (uchar *)nms_Y1_XY+sizeof(*pack_XY));
   __vcop_pblock_init32(pblock, __offset+_PREG(16), (uchar *)nms_Score);
   __vcop_pblock_init32(pblock, __offset+_PREG(18), 0);
   __vcop_pblock_init32(pblock, __offset+_PREG(20), 16);
   __offset += 20;

   /* Loop 5 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), (1)-1u);
   __vcop_pblock_init32(pblock, __offset+_PREG(6), 1);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)nms_Y_Score+(num_corners-1)*sizeof(*nms_id));
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)nms_Y_Score+(num_corners-2)*sizeof(*nms_id));
   __vcop_pblock_init32(pblock, __offset+_PREG(12), (uchar *)nms_Y1_XY+(num_corners-2)*sizeof(*pack_XY));
   __vcop_pblock_init32(pblock, __offset+_PREG(14), (uchar *)nms_Y1_XY+(num_corners-1)*sizeof(*pack_XY));
   __vcop_pblock_init32(pblock, __offset+_PREG(16), (uchar *)nms_Score+(num_corners-1)*sizeof(*pack_XY));
   __vcop_pblock_init32(pblock, __offset+_PREG(18), num_corners-1);
   __vcop_pblock_init32(pblock, __offset+_PREG(20), 16);
   __offset += 20;

   /* Loop 6 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), ((max_corners-num_corners+(8u)-1)/(8u))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(6), 32);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), 0);
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)nms_Score+num_corners*sizeof(*pack_XY));
   __offset += 10;

   return 114u;
}

void vcop_vertical_non_max_suppression_kernel_vloops(
   unsigned short pblock[])
{
   /* Kernel-wide Vector Registers */

   __vcop_param(&pblock[0]);

   /* VLOOP 1 Start */

   /* VLOOP Local Vector Registers */
   #pragma VCC_VREG("Vconst12", 16);
   #pragma VCC_VREG("Vconst22", 17);
   #pragma VCC_VREG("Vin", 18);
   #pragma VCC_VREG("Vmask1", 19);
   #pragma VCC_VREG("Vmask2", 20);
   #pragma VCC_VREG("Vx", 21);
   #pragma VCC_VREG("Vy", 22);
   #pragma VCC_VREG("id", 23);
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("Addr1", "A0");
   #pragma EVE_REG("Addr2", "A1");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I3", "I4");
   

   __vcop_vloop(__vcop_compute(), 14u, 10u, 1u);
   __vcop_vinit(__vcop_sizeW(), __vcop_alws(), _PREG(18), _VREG(17));
   __vcop_vinit(__vcop_sizeW(), __vcop_alws(), _PREG(20), _VREG(16));
   __vcop_vinit(__vcop_sizeW(), __vcop_alws(), _PREG(6), _VREG(19));
   __vcop_vinit(__vcop_sizeW(), __vcop_alws(), _PREG(8), _VREG(20));
   __vcop_vagen(_AGEN(0), _PREG(16), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(1), _PREG(17), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeWU(), __vcop_npt(), _PREG(10), _AGEN(0), _VREG(18), __vcop_alws());
   __vcop_vshf(_VREG(18), _VREG(17), _VREG(21));
   __vcop_vand(_VREG(18), _VREG(19), _VREG(22));
   __vcop_vshf(_VREG(22), _VREG(16), _VREG(22));
   __vcop_vand(_VREG(18), _VREG(20), _VREG(23));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeHU(), __vcop_intrlv(), __vcop_alws(), _VPAIR(22,21), _PREG(12), _AGEN(0), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeHU(), __vcop_npt(), __vcop_alws(), _VREG(23), _PREG(14), _AGEN(1), _PREG(0));
   __vcop_vloop_end(1u);

   /* VLOOP 2 Start */

   /* VLOOP Local Vector Registers */
   #pragma VCC_VREG("Vindex", 24);
   #pragma VCC_VREG("Vtabledata", 25);
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("index_addr", "A0");
   #pragma EVE_REG("out_addr", "A2");
   #pragma EVE_REG("table_addr", "A1");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I3", "I4");
   

   __vcop_vloop(__vcop_tablelkup(), 7u, 6u, 2u);
   __vcop_vagen(_AGEN(0), _PREG(8), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(2), _PREG(8), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(1), _PREG(0), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeHU(), __vcop_npt(), _PREG(10), _AGEN(0), _VREG(24), __vcop_alws());
   __vcop_vtbload(__vcop_sizeHU(), __vcop_tableinfo(1, 1), _PREG(12), _AGEN(1), _VREG(24), _VREG(25), _PREG(0), __vcop_alws());
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeHU(), __vcop_npt(), __vcop_alws(), _VREG(25), _PREG(6), _AGEN(2), _PREG(0));
   __vcop_vloop_end(2u);

   /* VLOOP 3 Start */

   /* VLOOP Local Vector Registers */
   #pragma VCC_VREG("id", 26);
   #pragma VCC_VREG("Vconst16", 27);
   #pragma VCC_VREG("Vconst8", 28);
   #pragma VCC_VREG("Vf", 29);
   #pragma VCC_VREG("Vf1", 30);
   #pragma VCC_VREG("Vf2", 31);
   #pragma VCC_VREG("Vin1", 32);
   #pragma VCC_VREG("Vin2", 33);
   #pragma VCC_VREG("Vin3", 34);
   #pragma VCC_VREG("Vnf1", 35);
   #pragma VCC_VREG("Vnf2", 36);
   #pragma VCC_VREG("Vone", 37);
   #pragma VCC_VREG("Vscore1", 38);
   #pragma VCC_VREG("Vscore2", 39);
   #pragma VCC_VREG("Vscore3", 40);
   #pragma VCC_VREG("Vsf1", 41);
   #pragma VCC_VREG("Vsf2", 42);
   #pragma VCC_VREG("Vzero", 43);
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("Addr0", "A0");
   #pragma EVE_REG("Addr1", "A1");
   #pragma EVE_REG("Addr2", "A2");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I2", "I3");
   #pragma EVE_REG("I3", "I4");
   

   __vcop_vloop(__vcop_compute(), 30u, 16u, 3u);
   __vcop_vinit(__vcop_sizeW(), __vcop_alws(), _PREG(32), _VREG(37));
   __vcop_vinit(__vcop_sizeW(), __vcop_alws(), _PREG(6), _VREG(28));
   __vcop_vinit(__vcop_sizeW(), __vcop_alws(), _PREG(8), _VREG(27));
   __vcop_vinit(__vcop_sizeW(), __vcop_alws(), _PREG(10), _VREG(43));
   __vcop_vagen(_AGEN(0), _PREG(0), _PREG(1), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(1), _PREG(26), _PREG(27), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(2), _PREG(28), _PREG(29), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeBU(), __vcop_npt(), _PREG(30), _AGEN(0), _VREG(26), __vcop_i4_zero());
   __vcop_vload(__vcop_sizeWU(), __vcop_npt(), _PREG(12), _AGEN(1), _VREG(32), __vcop_alws());
   __vcop_vload(__vcop_sizeWU(), __vcop_npt(), _PREG(14), _AGEN(1), _VREG(33), __vcop_alws());
   __vcop_vload(__vcop_sizeWU(), __vcop_npt(), _PREG(16), _AGEN(1), _VREG(34), __vcop_alws());
   __vcop_vload(__vcop_sizeHU(), __vcop_npt(), _PREG(18), _AGEN(2), _VREG(38), __vcop_alws());
   __vcop_vload(__vcop_sizeHU(), __vcop_npt(), _PREG(20), _AGEN(2), _VREG(39), __vcop_alws());
   __vcop_vload(__vcop_sizeHU(), __vcop_npt(), _PREG(22), _AGEN(2), _VREG(40), __vcop_alws());
   __vcop_vadd(_VREG(32), _VREG(37), _VREG(32));
   __vcop_vsub(_VREG(34), _VREG(37), _VREG(34));
   __vcop_vcmpeq(_VREG(33), _VREG(32), _VREG(35));
   __vcop_vcmpeq(_VREG(33), _VREG(34), _VREG(36));
   __vcop_vcmple(_VREG(39), _VREG(38), _VREG(41));
   __vcop_vcmple(_VREG(39), _VREG(40), _VREG(42));
   __vcop_vand(_VREG(35), _VREG(41), _VREG(30));
   __vcop_vand(_VREG(36), _VREG(42), _VREG(31));
   __vcop_vor(_VREG(30), _VREG(31), _VREG(30));
   __vcop_vshf(_VREG(39), _VREG(27), _VREG(32));
   __vcop_vsub(_VREG(37), _VREG(30), _VREG(29));
   __vcop_vor(_VREG(32), _VREG(26), _VREG(32));
   __vcop_vadd(_VREG(26), _VREG(28), _VREG(26));
   __vcop_vstore(__vcop_predicate(_VREG(30)), __vcop_sizeWU(), __vcop_npt(), __vcop_alws(), _VREG(43), _PREG(24), _AGEN(1), _PREG(0));
   __vcop_vstore(__vcop_predicate(_VREG(29)), __vcop_sizeWU(), __vcop_npt(), __vcop_alws(), _VREG(32), _PREG(24), _AGEN(1), _PREG(0));
   __vcop_vloop_end(3u);

   /* VLOOP 4 Start */

   /* VLOOP Local Vector Registers */
   #pragma VCC_VREG("Score0", 44);
   #pragma VCC_VREG("Score1", 45);
   #pragma VCC_VREG("Vconst16", 46);
   #pragma VCC_VREG("Vf1", 47);
   #pragma VCC_VREG("Vin1", 48);
   #pragma VCC_VREG("Vnf1", 49);
   #pragma VCC_VREG("Vone", 50);
   #pragma VCC_VREG("Vsf1", 51);
   #pragma VCC_VREG("Vzero", 52);
   #pragma VCC_VREG("xy0", 53);
   #pragma VCC_VREG("xy1", 54);
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("Addr0", "A0");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I3", "I4");
   

   __vcop_vloop(__vcop_compute(), 18u, 10u, 4u);
   __vcop_vinit(__vcop_sizeW(), __vcop_alws(), _PREG(18), _VREG(52));
   __vcop_vinit(__vcop_sizeW(), __vcop_alws(), _PREG(20), _VREG(46));
   __vcop_vinit(__vcop_sizeW(), __vcop_alws(), _PREG(6), _VREG(50));
   __vcop_vagen(_AGEN(0), _PREG(1), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeHU(), __vcop_1pt(), _PREG(8), _AGEN(0), _VREG(44), __vcop_alws());
   __vcop_vload(__vcop_sizeHU(), __vcop_1pt(), _PREG(10), _AGEN(0), _VREG(45), __vcop_alws());
   __vcop_vload(__vcop_sizeWU(), __vcop_1pt(), _PREG(12), _AGEN(0), _VREG(53), __vcop_alws());
   __vcop_vload(__vcop_sizeWU(), __vcop_1pt(), _PREG(14), _AGEN(0), _VREG(54), __vcop_alws());
   __vcop_vadd(_VREG(53), _VREG(50), _VREG(53));
   __vcop_vcmple(_VREG(44), _VREG(45), _VREG(51));
   __vcop_vcmpeq(_VREG(53), _VREG(54), _VREG(49));
   __vcop_vshf(_VREG(44), _VREG(46), _VREG(48));
   __vcop_vand(_VREG(49), _VREG(51), _VREG(47));
   __vcop_vor(_VREG(48), _VREG(52), _VREG(48));
   __vcop_vsub(_VREG(50), _VREG(47), _VREG(49));
   __vcop_vstore(__vcop_predicate(_VREG(47)), __vcop_sizeWU(), __vcop_1pt(), __vcop_alws(), _VREG(52), _PREG(16), _AGEN(0), _PREG(0));
   __vcop_vstore(__vcop_predicate(_VREG(49)), __vcop_sizeWU(), __vcop_1pt(), __vcop_alws(), _VREG(48), _PREG(16), _AGEN(0), _PREG(0));
   __vcop_vloop_end(4u);

   /* VLOOP 5 Start */

   /* VLOOP Local Vector Registers */
   #pragma VCC_VREG("Score_last", 55);
   #pragma VCC_VREG("Score_last_1", 56);
   #pragma VCC_VREG("Vconst16", 57);
   #pragma VCC_VREG("Vf1", 58);
   #pragma VCC_VREG("Vid", 59);
   #pragma VCC_VREG("Vin1", 60);
   #pragma VCC_VREG("Vlast", 61);
   #pragma VCC_VREG("Vnf1", 62);
   #pragma VCC_VREG("Vone", 63);
   #pragma VCC_VREG("Vsf1", 64);
   #pragma VCC_VREG("xy0", 65);
   #pragma VCC_VREG("xy1", 66);
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("Addr0", "A0");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I3", "I4");
   

   __vcop_vloop(__vcop_compute(), 19u, 10u, 5u);
   __vcop_vinit(__vcop_sizeW(), __vcop_alws(), _PREG(18), _VREG(59));
   __vcop_vinit(__vcop_sizeW(), __vcop_alws(), _PREG(18), _VREG(61));
   __vcop_vinit(__vcop_sizeW(), __vcop_alws(), _PREG(20), _VREG(57));
   __vcop_vinit(__vcop_sizeW(), __vcop_alws(), _PREG(6), _VREG(63));
   __vcop_vagen(_AGEN(0), _PREG(1), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeHU(), __vcop_1pt(), _PREG(8), _AGEN(0), _VREG(55), __vcop_alws());
   __vcop_vload(__vcop_sizeHU(), __vcop_1pt(), _PREG(10), _AGEN(0), _VREG(56), __vcop_alws());
   __vcop_vload(__vcop_sizeWU(), __vcop_1pt(), _PREG(12), _AGEN(0), _VREG(65), __vcop_alws());
   __vcop_vload(__vcop_sizeWU(), __vcop_1pt(), _PREG(14), _AGEN(0), _VREG(66), __vcop_alws());
   __vcop_vadd(_VREG(65), _VREG(63), _VREG(65));
   __vcop_vcmple(_VREG(55), _VREG(56), _VREG(64));
   __vcop_vcmpeq(_VREG(65), _VREG(66), _VREG(62));
   __vcop_vshf(_VREG(55), _VREG(57), _VREG(60));
   __vcop_vand(_VREG(62), _VREG(64), _VREG(58));
   __vcop_vor(_VREG(60), _VREG(61), _VREG(60));
   __vcop_vsub(_VREG(63), _VREG(58), _VREG(62));
   __vcop_vstore(__vcop_predicate(_VREG(58)), __vcop_sizeWU(), __vcop_1pt(), __vcop_alws(), _VREG(59), _PREG(16), _AGEN(0), _PREG(0));
   __vcop_vstore(__vcop_predicate(_VREG(62)), __vcop_sizeWU(), __vcop_1pt(), __vcop_alws(), _VREG(60), _PREG(16), _AGEN(0), _PREG(0));
   __vcop_vloop_end(5u);

   /* VLOOP 6 Start */

   /* VLOOP Local Vector Registers */
   #pragma VCC_VREG("Vzero", 67);
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("Addr0", "A0");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I3", "I4");
   

   __vcop_vloop(__vcop_compute(), 4u, 5u, 6u);
   __vcop_vinit(__vcop_sizeW(), __vcop_alws(), _PREG(8), _VREG(67));
   __vcop_vagen(_AGEN(0), _PREG(6), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeWU(), __vcop_npt(), __vcop_alws(), _VREG(67), _PREG(10), _AGEN(0), _PREG(0));
   __vcop_vloop_end(6u);

}

void vcop_vertical_non_max_suppression_kernel(
   __vptr_uint32 pack_XY,
   unsigned short num_corners,
   unsigned short max_corners,
   __vptr_uint16 nms_X_Score,
   __vptr_uint16 nms_id,
   __vptr_uint16 nms_Y_Score,
   __vptr_uint16 nms_Y_XY,
   __vptr_uint32 nms_Y1_XY,
   __vptr_uint32 nms_Score,
   __vptr_uint8 Id_list)
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_vertical_non_max_suppression_kernel_init(pack_XY, num_corners, max_corners, nms_X_Score, nms_id, nms_Y_Score, nms_Y_XY, nms_Y1_XY, nms_Score, Id_list, __pblock_vcop_vertical_non_max_suppression_kernel);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_vertical_non_max_suppression_kernel_vloops(__pblock_vcop_vertical_non_max_suppression_kernel);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

void vcop_vertical_non_max_suppression_kernel_custom(
   __vptr_uint32 pack_XY,
   unsigned short num_corners,
   unsigned short max_corners,
   __vptr_uint16 nms_X_Score,
   __vptr_uint16 nms_id,
   __vptr_uint16 nms_Y_Score,
   __vptr_uint16 nms_Y_XY,
   __vptr_uint32 nms_Y1_XY,
   __vptr_uint32 nms_Score,
   __vptr_uint8 Id_list,
   unsigned short pblock[])
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_vertical_non_max_suppression_kernel_init(pack_XY, num_corners, max_corners, nms_X_Score, nms_id, nms_Y_Score, nms_Y_XY, nms_Y1_XY, nms_Score, Id_list, pblock);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_vertical_non_max_suppression_kernel_vloops(pblock);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

