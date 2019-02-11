#include <vcop\vcop.h>

typedef unsigned char uchar;

#pragma DATA_SECTION(__pblock_vcop_hough_circle_compute_idx, ".vcop_parameter_block")
#pragma DATA_ALIGN(__pblock_vcop_hough_circle_compute_idx, __ALIGNOF__(int));
unsigned short __pblock_vcop_hough_circle_compute_idx[44];

unsigned int vcop_hough_circle_compute_idx_param_count(void)
{
   return 44u;
}

unsigned int vcop_hough_circle_compute_idx_ctrl_count(void)
{
   return 0u;
}

unsigned int vcop_hough_circle_compute_idx_init(
   __vptr_int16 gradUnitVecXY,
   __vptr_uint16 xyList,
   __vptr_int16 scratch,
   __vptr_uint16 houghSpaceIndex,
   unsigned short numEdgePoints,
   char radius,
   unsigned char downShift,
   unsigned short houghSpaceSaturateX,
   unsigned short houghSpaceSaturateY,
   unsigned short houghSpacePitch,
   unsigned short pblock[])
{
   int __offset = 0;
   /* Loop 1 PREGS */
   const int preg_ref1 = _PREG(14);
   const int preg_ref2 = _PREG(20);

   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), ((2*numEdgePoints + (2*(8u)) - 1)/(2*(8u)))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(6), __vcop_store_round_sat(SM_4PARAM,preg_ref1,RM_ROUND,downShift));
   __vcop_pblock_init16(pblock, __offset+_PREG(7), __vcop_store_round_sat(SM_4PARAM,preg_ref2,RM_ROUND,downShift));
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)xyList);
   __vcop_pblock_init16(pblock, __offset+_PREG(10), __vcop_vop_round(1, 8));
   __vcop_pblock_init16(pblock, __offset+_PREG(11), 32);
   __vcop_pblock_init32(pblock, __offset+_PREG(12), (uchar *)scratch);
   __vcop_pblock_4param_init(pblock, __offset+_PREG(14), houghSpaceSaturateY,0,0,0);
   __vcop_pblock_init32(pblock, __offset+_PREG(18), (uchar *)scratch+sizeof(*scratch));
   __vcop_pblock_4param_init(pblock, __offset+_PREG(20), houghSpaceSaturateX,0,0,0);
   __vcop_pblock_init32(pblock, __offset+_PREG(24), radius);
   __vcop_pblock_init32(pblock, __offset+_PREG(26), (uchar *)gradUnitVecXY);
   __offset += 26;

   /* Loop 2 PREGS */
   const int preg_ref3 = _PREG(10);

   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), ((2*numEdgePoints + (2*(8u)) - 1)/(2*(8u)))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(6), __vcop_store_round_sat(SM_4PARAM,preg_ref3,RM_NONE,0));
   __vcop_pblock_init16(pblock, __offset+_PREG(7), 32);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)houghSpaceIndex);
   __vcop_pblock_4param_init(pblock, __offset+_PREG(10), 65535,65535,0,0);
   __vcop_pblock_init16(pblock, __offset+_PREG(14), 16);
   __vcop_pblock_init32(pblock, __offset+_PREG(16), houghSpacePitch);
   __vcop_pblock_init32(pblock, __offset+_PREG(18), (uchar *)scratch);
   __offset += 18;

   return 44u;
}

void vcop_hough_circle_compute_idx_vloops(
   unsigned short pblock[])
{
   /* Kernel-wide Vector Registers */

   __vcop_param(&pblock[0]);

   /* VLOOP 1 Start */

   /* VLOOP Local Vector Registers */
   #pragma VCC_VREG("Vcx", 16);
   #pragma VCC_VREG("Vcy", 17);
   #pragma VCC_VREG("Vrad", 18);
   #pragma VCC_VREG("Vux", 19);
   #pragma VCC_VREG("Vuy", 20);
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("Addr1", "A0");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I1", "I4");
   

   __vcop_vloop(__vcop_compute(), 9u, 13u, 1u);
   __vcop_vinit(__vcop_sizeW(), __vcop_alws(), _PREG(24), _VREG(18));
   __vcop_vagen(_AGEN(0), _PREG(11), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeH(), __vcop_dintrlv(), _PREG(26), _AGEN(0), _VPAIR(20,19), __vcop_alws());
   __vcop_vload(__vcop_sizeHU(), __vcop_dintrlv(), _PREG(8), _AGEN(0), _VPAIR(17,16), __vcop_alws());
   __vcop_vmadd(_VREG(18), _VREG(19), _VREG(16), _PREG(10));
   __vcop_vmadd(_VREG(18), _VREG(20), _VREG(17), _PREG(10));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeH(), __vcop_skip(), __vcop_alws(), _VREG(17), _PREG(12), _AGEN(0), _PREG(6));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeH(), __vcop_skip(), __vcop_alws(), _VREG(16), _PREG(18), _AGEN(0), _PREG(7));
   __vcop_vloop_end(1u);

   /* VLOOP 2 Start */

   /* VLOOP Local Vector Registers */
   #pragma VCC_VREG("Vcx", 21);
   #pragma VCC_VREG("Vcy", 22);
   #pragma VCC_VREG("Vwidth", 23);
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("AddrIn", "A0");
   #pragma EVE_REG("AddrOut", "A1");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I1", "I4");
   

   __vcop_vloop(__vcop_compute(), 7u, 9u, 2u);
   __vcop_vinit(__vcop_sizeW(), __vcop_alws(), _PREG(16), _VREG(23));
   __vcop_vagen(_AGEN(0), _PREG(7), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(1), _PREG(14), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeH(), __vcop_dintrlv(), _PREG(18), _AGEN(0), _VPAIR(22,21), __vcop_alws());
   __vcop_vmadd(_VREG(22), _VREG(23), _VREG(21), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeHU(), __vcop_npt(), __vcop_alws(), _VREG(21), _PREG(8), _AGEN(1), _PREG(6));
   __vcop_vloop_end(2u);

}

void vcop_hough_circle_compute_idx(
   __vptr_int16 gradUnitVecXY,
   __vptr_uint16 xyList,
   __vptr_int16 scratch,
   __vptr_uint16 houghSpaceIndex,
   unsigned short numEdgePoints,
   char radius,
   unsigned char downShift,
   unsigned short houghSpaceSaturateX,
   unsigned short houghSpaceSaturateY,
   unsigned short houghSpacePitch)
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_hough_circle_compute_idx_init(gradUnitVecXY, xyList, scratch, houghSpaceIndex, numEdgePoints, radius, downShift, houghSpaceSaturateX, houghSpaceSaturateY, houghSpacePitch, __pblock_vcop_hough_circle_compute_idx);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_hough_circle_compute_idx_vloops(__pblock_vcop_hough_circle_compute_idx);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

void vcop_hough_circle_compute_idx_custom(
   __vptr_int16 gradUnitVecXY,
   __vptr_uint16 xyList,
   __vptr_int16 scratch,
   __vptr_uint16 houghSpaceIndex,
   unsigned short numEdgePoints,
   char radius,
   unsigned char downShift,
   unsigned short houghSpaceSaturateX,
   unsigned short houghSpaceSaturateY,
   unsigned short houghSpacePitch,
   unsigned short pblock[])
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_hough_circle_compute_idx_init(gradUnitVecXY, xyList, scratch, houghSpaceIndex, numEdgePoints, radius, downShift, houghSpaceSaturateX, houghSpaceSaturateY, houghSpacePitch, pblock);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_hough_circle_compute_idx_vloops(pblock);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

#pragma DATA_SECTION(__pblock_vcop_hough_circle_compute_idx_param_block_update, ".vcop_parameter_block")
#pragma DATA_ALIGN(__pblock_vcop_hough_circle_compute_idx_param_block_update, __ALIGNOF__(int));
unsigned short __pblock_vcop_hough_circle_compute_idx_param_block_update[24];

unsigned int vcop_hough_circle_compute_idx_param_block_update_param_count(void)
{
   return 24u;
}

unsigned int vcop_hough_circle_compute_idx_param_block_update_ctrl_count(void)
{
   return 0u;
}

unsigned int vcop_hough_circle_compute_idx_param_block_update_init(
   __vptr_uint16 pBlock,
   __vptr_int32 pBlockSigned,
   __vptr_uint16 pListSizePtr,
   __vptr_int8 pCurrRadiusPtr,
   unsigned short pblock[])
{
   int __offset = 0;
   /* Loop 1 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), (1)-1u);
   __vcop_pblock_init32(pblock, __offset+_PREG(6), 1);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), -4);
   __vcop_pblock_init32(pblock, __offset+_PREG(10), -1);
   __vcop_pblock_init32(pblock, __offset+_PREG(12), (uchar *)pListSizePtr);
   __vcop_pblock_init32(pblock, __offset+_PREG(14), (uchar *)pCurrRadiusPtr);
   __vcop_pblock_init32(pblock, __offset+_PREG(16), (uchar *)pBlock+6);
   __vcop_pblock_init32(pblock, __offset+_PREG(18), (uchar *)pBlockSigned+44);
   __vcop_pblock_init32(pblock, __offset+_PREG(20), (uchar *)pBlock+58);
   __vcop_pblock_init32(pblock, __offset+_PREG(22), 15);
   __vcop_pblock_init32(pblock, __offset+_PREG(24), 0);
   __offset += 24;

   return 24u;
}

void vcop_hough_circle_compute_idx_param_block_update_vloops(
   unsigned short pblock[])
{
   /* Kernel-wide Vector Registers */
   #pragma VCC_VREG("VMask", 16);
   #pragma VCC_VREG("Vk0", 17);
   #pragma VCC_VREG("Vk1", 18);
   #pragma VCC_VREG("Vk15", 19);
   #pragma VCC_VREG("Vk2", 20);
   #pragma VCC_VREG("VkMinus1", 21);
   #pragma VCC_VREG("VkMinus4", 22);
   #pragma VCC_VREG("VlistSizeAlign2SIMD", 23);
   #pragma VCC_VREG("Vradius", 24);

   __vcop_param(&pblock[0]);

   /* VLOOP 1 Start */

   /* VLOOP Local Vector Registers */
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("addr0", "A0");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("i", "I4");
   

   __vcop_vloop(__vcop_compute(), 18u, 12u, 1u);
   __vcop_vinit(__vcop_sizeW(), __vcop_once(), _PREG(22), _VREG(19));
   __vcop_vinit(__vcop_sizeW(), __vcop_once(), _PREG(24), _VREG(17));
   __vcop_vinit(__vcop_sizeW(), __vcop_once(), _PREG(6), _VREG(18));
   __vcop_vinit(__vcop_sizeW(), __vcop_once(), _PREG(8), _VREG(22));
   __vcop_vinit(__vcop_sizeW(), __vcop_once(), _PREG(10), _VREG(21));
   __vcop_vagen(_AGEN(0), _PREG(0), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeHU(), __vcop_1pt(), _PREG(12), _AGEN(0), _VREG(23), __vcop_once());
   __vcop_vload(__vcop_sizeB(), __vcop_1pt(), _PREG(14), _AGEN(0), _VREG(24), __vcop_once());
   __vcop_vcmpeq(_VREG(23), _VREG(17), _VREG(16));
   __vcop_vsel(_VREG(16), _VREG(18), _VREG(23));
   __vcop_vshf(_VREG(23), _VREG(18), _VREG(23));
   __vcop_vadd(_VREG(23), _VREG(19), _VREG(23));
   __vcop_vshf(_VREG(23), _VREG(22), _VREG(23));
   __vcop_vadd(_VREG(23), _VREG(21), _VREG(23));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeHU(), __vcop_1pt(), __vcop_alws(), _VREG(23), _PREG(16), _AGEN(0), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeW(), __vcop_1pt(), __vcop_alws(), _VREG(24), _PREG(18), _AGEN(0), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeHU(), __vcop_1pt(), __vcop_alws(), _VREG(23), _PREG(20), _AGEN(0), _PREG(0));
   __vcop_vloop_end(1u);

}

void vcop_hough_circle_compute_idx_param_block_update(
   __vptr_uint16 pBlock,
   __vptr_int32 pBlockSigned,
   __vptr_uint16 pListSizePtr,
   __vptr_int8 pCurrRadiusPtr)
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_hough_circle_compute_idx_param_block_update_init(pBlock, pBlockSigned, pListSizePtr, pCurrRadiusPtr, __pblock_vcop_hough_circle_compute_idx_param_block_update);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_hough_circle_compute_idx_param_block_update_vloops(__pblock_vcop_hough_circle_compute_idx_param_block_update);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

void vcop_hough_circle_compute_idx_param_block_update_custom(
   __vptr_uint16 pBlock,
   __vptr_int32 pBlockSigned,
   __vptr_uint16 pListSizePtr,
   __vptr_int8 pCurrRadiusPtr,
   unsigned short pblock[])
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_hough_circle_compute_idx_param_block_update_init(pBlock, pBlockSigned, pListSizePtr, pCurrRadiusPtr, pblock);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_hough_circle_compute_idx_param_block_update_vloops(pblock);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

#pragma DATA_SECTION(__pblock_vcop_hough_circle_init_hough_space, ".vcop_parameter_block")
#pragma DATA_ALIGN(__pblock_vcop_hough_circle_init_hough_space, __ALIGNOF__(int));
unsigned short __pblock_vcop_hough_circle_init_hough_space[10];

unsigned int vcop_hough_circle_init_hough_space_param_count(void)
{
   return 10u;
}

unsigned int vcop_hough_circle_init_hough_space_ctrl_count(void)
{
   return 0u;
}

unsigned int vcop_hough_circle_init_hough_space_init(
   __vptr_uint32 houghSpacePtr,
   unsigned short houghSpacePitch,
   unsigned short houghSpaceHeight,
   unsigned short pblock[])
{
   int __offset = 0;
   /* Loop 1 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), (((houghSpacePitch*houghSpaceHeight + 3)/4 + (8u) - 1)/(8u))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(6), 32);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), 0);
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)houghSpacePtr);
   __offset += 10;

   return 10u;
}

void vcop_hough_circle_init_hough_space_vloops(
   unsigned short pblock[])
{
   /* Kernel-wide Vector Registers */

   __vcop_param(&pblock[0]);

   /* VLOOP 1 Start */

   /* VLOOP Local Vector Registers */
   #pragma VCC_VREG("VK0", 16);
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("AddrOut", "A0");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I1", "I4");
   

   __vcop_vloop(__vcop_compute(), 4u, 5u, 1u);
   __vcop_vinit(__vcop_sizeW(), __vcop_alws(), _PREG(8), _VREG(16));
   __vcop_vagen(_AGEN(0), _PREG(6), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeWU(), __vcop_npt(), __vcop_alws(), _VREG(16), _PREG(10), _AGEN(0), _PREG(0));
   __vcop_vloop_end(1u);

}

void vcop_hough_circle_init_hough_space(
   __vptr_uint32 houghSpacePtr,
   unsigned short houghSpacePitch,
   unsigned short houghSpaceHeight)
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_hough_circle_init_hough_space_init(houghSpacePtr, houghSpacePitch, houghSpaceHeight, __pblock_vcop_hough_circle_init_hough_space);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_hough_circle_init_hough_space_vloops(__pblock_vcop_hough_circle_init_hough_space);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

void vcop_hough_circle_init_hough_space_custom(
   __vptr_uint32 houghSpacePtr,
   unsigned short houghSpacePitch,
   unsigned short houghSpaceHeight,
   unsigned short pblock[])
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_hough_circle_init_hough_space_init(houghSpacePtr, houghSpacePitch, houghSpaceHeight, pblock);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_hough_circle_init_hough_space_vloops(pblock);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

#pragma DATA_SECTION(__pblock_vcop_hough_circle_vote_to_hough_space, ".vcop_parameter_block")
#pragma DATA_ALIGN(__pblock_vcop_hough_circle_vote_to_hough_space, __ALIGNOF__(int));
unsigned short __pblock_vcop_hough_circle_vote_to_hough_space[12];

unsigned int vcop_hough_circle_vote_to_hough_space_param_count(void)
{
   return 12u;
}

unsigned int vcop_hough_circle_vote_to_hough_space_ctrl_count(void)
{
   return 0u;
}

unsigned int vcop_hough_circle_vote_to_hough_space_init(
   __vptr_uint16 houghSpaceIndex,
   __vptr_uint8 houghSpacePtr,
   unsigned short numEdgePoints,
   unsigned short pblock[])
{
   int __offset = 0;
   /* Loop 1 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), (numEdgePoints/(1))-1u);
   __vcop_pblock_init32(pblock, __offset+_PREG(6), (uchar *)houghSpacePtr);
   __vcop_pblock_init16(pblock, __offset+_PREG(8), 2);
   __vcop_pblock_init32(pblock, __offset+_PREG(10), 1);
   __vcop_pblock_init32(pblock, __offset+_PREG(12), (uchar *)houghSpaceIndex);
   __offset += 12;

   return 12u;
}

void vcop_hough_circle_vote_to_hough_space_vloops(
   unsigned short pblock[])
{
   /* Kernel-wide Vector Registers */
   #pragma VCC_VREG("Vdata", 16);
   #pragma VCC_VREG("Vindex", 17);
   #pragma VCC_VREG("Vweight", 18);

   __vcop_param(&pblock[0]);

   /* VLOOP 1 Start */

   /* VLOOP Local Vector Registers */
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("hist_agen", "A1");
   #pragma EVE_REG("ind_agen", "A0");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I1", "I4");
   

   __vcop_vloop(__vcop_histogram(), 8u, 6u, 1u);
   __vcop_vinit(__vcop_sizeW(), __vcop_once(), _PREG(10), _VREG(18));
   __vcop_vagen(_AGEN(1), _PREG(0), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(0), _PREG(8), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeHU(), __vcop_npt(), _PREG(12), _AGEN(0), _VREG(17), __vcop_alws());
   __vcop_vhistload(__vcop_sizeBU(), 1, _PREG(6), _AGEN(1), _VREG(17), _VREG(16), _PREG(0), __vcop_alws());
   __vcop_hist_vadd(_VREG(16), _VREG(18), _VREG(16));
   __vcop_vhiststore(__vcop_sizeBU(), 1, __vcop_alws(), _VREG(16), _PREG(6), _AGEN(1), _VREG(17));
   __vcop_vloop_end(1u);

}

void vcop_hough_circle_vote_to_hough_space(
   __vptr_uint16 houghSpaceIndex,
   __vptr_uint8 houghSpacePtr,
   unsigned short numEdgePoints)
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_hough_circle_vote_to_hough_space_init(houghSpaceIndex, houghSpacePtr, numEdgePoints, __pblock_vcop_hough_circle_vote_to_hough_space);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_hough_circle_vote_to_hough_space_vloops(__pblock_vcop_hough_circle_vote_to_hough_space);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

void vcop_hough_circle_vote_to_hough_space_custom(
   __vptr_uint16 houghSpaceIndex,
   __vptr_uint8 houghSpacePtr,
   unsigned short numEdgePoints,
   unsigned short pblock[])
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_hough_circle_vote_to_hough_space_init(houghSpaceIndex, houghSpacePtr, numEdgePoints, pblock);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_hough_circle_vote_to_hough_space_vloops(pblock);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

#pragma DATA_SECTION(__pblock_vcop_hough_circle_vote_to_hough_space_param_block_update, ".vcop_parameter_block")
#pragma DATA_ALIGN(__pblock_vcop_hough_circle_vote_to_hough_space_param_block_update, __ALIGNOF__(int));
unsigned short __pblock_vcop_hough_circle_vote_to_hough_space_param_block_update[10];

unsigned int vcop_hough_circle_vote_to_hough_space_param_block_update_param_count(void)
{
   return 10u;
}

unsigned int vcop_hough_circle_vote_to_hough_space_param_block_update_ctrl_count(void)
{
   return 0u;
}

unsigned int vcop_hough_circle_vote_to_hough_space_param_block_update_init(
   __vptr_uint16 pBlock,
   unsigned short numElemsInLastBlk,
   unsigned short pblock[])
{
   int __offset = 0;
   /* Loop 1 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), (1)-1u);
   __vcop_pblock_init32(pblock, __offset+_PREG(6), (uchar *)pBlock+6);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), -1);
   __vcop_pblock_init32(pblock, __offset+_PREG(10), numElemsInLastBlk);
   __offset += 10;

   return 10u;
}

void vcop_hough_circle_vote_to_hough_space_param_block_update_vloops(
   unsigned short pblock[])
{
   /* Kernel-wide Vector Registers */
   #pragma VCC_VREG("Vkminus1", 16);
   #pragma VCC_VREG("VnumElemsInLastBlk", 17);

   __vcop_param(&pblock[0]);

   /* VLOOP 1 Start */

   /* VLOOP Local Vector Registers */
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("addr0", "A0");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("i", "I4");
   

   __vcop_vloop(__vcop_compute(), 6u, 5u, 1u);
   __vcop_vinit(__vcop_sizeW(), __vcop_once(), _PREG(8), _VREG(16));
   __vcop_vinit(__vcop_sizeW(), __vcop_once(), _PREG(10), _VREG(17));
   __vcop_vagen(_AGEN(0), _PREG(0), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vadd(_VREG(17), _VREG(16), _VREG(17));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeHU(), __vcop_1pt(), __vcop_alws(), _VREG(17), _PREG(6), _AGEN(0), _PREG(0));
   __vcop_vloop_end(1u);

}

void vcop_hough_circle_vote_to_hough_space_param_block_update(
   __vptr_uint16 pBlock,
   unsigned short numElemsInLastBlk)
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_hough_circle_vote_to_hough_space_param_block_update_init(pBlock, numElemsInLastBlk, __pblock_vcop_hough_circle_vote_to_hough_space_param_block_update);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_hough_circle_vote_to_hough_space_param_block_update_vloops(__pblock_vcop_hough_circle_vote_to_hough_space_param_block_update);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

void vcop_hough_circle_vote_to_hough_space_param_block_update_custom(
   __vptr_uint16 pBlock,
   unsigned short numElemsInLastBlk,
   unsigned short pblock[])
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_hough_circle_vote_to_hough_space_param_block_update_init(pBlock, numElemsInLastBlk, pblock);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_hough_circle_vote_to_hough_space_param_block_update_vloops(pblock);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

#pragma DATA_SECTION(__pblock_vcop_hough_for_circle_detect, ".vcop_parameter_block")
#pragma DATA_ALIGN(__pblock_vcop_hough_for_circle_detect, __ALIGNOF__(int));
unsigned short __pblock_vcop_hough_for_circle_detect[38];

unsigned int vcop_hough_for_circle_detect_param_count(void)
{
   return 38u;
}

unsigned int vcop_hough_for_circle_detect_ctrl_count(void)
{
   return 0u;
}

unsigned int vcop_hough_for_circle_detect_init(
   __vptr_uint8 houghSpacePtr,
   __vptr_uint32 pUpperLeftXY,
   __vptr_uint32 xSequence,
   __vptr_uint16 pNumCircles,
   __vptr_uint32 pCenterListXY,
   __vptr_uint8 pHoughScoreList,
   unsigned char houghScoreThreshold,
   unsigned short houghSpaceWidth,
   unsigned short houghSpaceHeight,
   unsigned short houghSpacePitch,
   unsigned char houghSpaceShift,
   unsigned short pblock[])
{
   int __offset = 0;
   /* Loop 1 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), (houghSpaceHeight)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), ((houghSpaceWidth + (8u) - 1)/(8u))-1u);
   __vcop_pblock_init32(pblock, __offset+_PREG(6), (2048 / (8u)));
   __vcop_pblock_init32(pblock, __offset+_PREG(8), houghSpaceShift);
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)houghSpacePtr);
   __vcop_pblock_init32(pblock, __offset+_PREG(12), (uchar *)xSequence);
   __vcop_pblock_init32(pblock, __offset+_PREG(14), houghScoreThreshold);
   __vcop_pblock_init32(pblock, __offset+_PREG(16), (uchar *)pCenterListXY);
   __vcop_pblock_init32(pblock, __offset+_PREG(18), (uchar *)pHoughScoreList);
   __vcop_pblock_init32(pblock, __offset+_PREG(20), (uchar *)pNumCircles);
   __vcop_pblock_init16(pblock, __offset+_PREG(22), 8);
   __vcop_pblock_init16(pblock, __offset+_PREG(23), (houghSpacePitch) -(8u)*(((houghSpaceWidth + (8u) - 1)/(8u))-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(24), 32);
   __vcop_pblock_init16(pblock, __offset+_PREG(25),  -(8u*sizeof(*xSequence))*(((houghSpaceWidth + (8u) - 1)/(8u))-1u));
   __vcop_pblock_init32(pblock, __offset+_PREG(26), 0);
   __vcop_pblock_init32(pblock, __offset+_PREG(28), (uchar *)pUpperLeftXY);
   __offset += 28;

   /* Loop 2 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), (1)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), (7)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(6), 2);
   __vcop_pblock_init16(pblock, __offset+_PREG(7), -12);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)pNumCircles+sizeof(*pNumCircles));
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)pNumCircles);
   __offset += 10;

   return 38u;
}

void vcop_hough_for_circle_detect_vloops(
   unsigned short pblock[])
{
   /* Kernel-wide Vector Registers */
   #pragma VCC_VREG("VExitCondition", 16);
   #pragma VCC_VREG("VhoughSpaceShift", 17);
   #pragma VCC_VREG("VmaxNumCircles", 18);
   #pragma VCC_VREG("VnumEntries", 19);
   #pragma VCC_VREG("VupperLeftXY", 20);

   __vcop_param(&pblock[0]);

   /* VLOOP 1 Start */

   /* VLOOP Local Vector Registers */
   #pragma VCC_VREG("VcenterXY", 21);
   #pragma VCC_VREG("Vflag", 22);
   #pragma VCC_VREG("Vin", 23);
   #pragma VCC_VREG("Vthrs", 24);
   #pragma VCC_VREG("VxSeq", 25);
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("Addr0", "A0");
   #pragma EVE_REG("AddrIn", "A1");
   #pragma EVE_REG("AddrOut", "A2");
   #pragma EVE_REG("AddrSeq", "A3");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I1", "I3");
   #pragma EVE_REG("I2", "I4");
   

   __vcop_vloop(__vcop_compute(), 23u, 14u, 1u);
   __vcop_vinit(__vcop_sizeW(), __vcop_once(), _PREG(26), _VREG(19));
   __vcop_vinit(__vcop_sizeW(), __vcop_once(), _PREG(26), _VREG(16));
   __vcop_vinit(__vcop_sizeW(), __vcop_once(), _PREG(6), _VREG(18));
   __vcop_vinit(__vcop_sizeW(), __vcop_once(), _PREG(8), _VREG(17));
   __vcop_vinit(__vcop_sizeHU(), __vcop_alws(), _PREG(67), _VREG(21));
   __vcop_vinit(__vcop_sizeW(), __vcop_alws(), _PREG(14), _VREG(24));
   __vcop_vagen(_AGEN(0), _PREG(0), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(1), _PREG(22), _PREG(23), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(3), _PREG(24), _PREG(25), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeWU(), __vcop_1pt(), _PREG(28), _AGEN(0), _VREG(20), __vcop_once());
   __vcop_vload(__vcop_sizeBU(), __vcop_npt(), _PREG(10), _AGEN(1), _VREG(23), __vcop_alws());
   __vcop_vload(__vcop_sizeWU(), __vcop_npt(), _PREG(12), _AGEN(3), _VREG(25), __vcop_alws());
   __vcop_vshf(_VREG(21), _VREG(17), _VREG(21));
   __vcop_vcmpge(_VREG(23), _VREG(24), _VREG(22));
   __vcop_vadd3(_VREG(25), _VREG(20), _VREG(21));
   __vcop_vadd(_VREG(19), _VREG(22), _VREG(19));
   __vcop_vbitpk(_VREG(19), _VREG(18), _VREG(16));
   __vcop_vexitnz(__vcop_level_vloop(), _VREG(16));
   __vcop_vstore(__vcop_predicate(_VREG(22)), __vcop_sizeWU(), __vcop_collat(), __vcop_alws(), _VREG(21), _PREG(16), _AGEN(0), _PREG(0));
   __vcop_vstore(__vcop_predicate(_VREG(22)), __vcop_sizeBU(), __vcop_collat(), __vcop_alws(), _VREG(23), _PREG(18), _AGEN(0), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeHU(), __vcop_npt(), __vcop_alws(), _VREG(19), _PREG(20), _AGEN(0), _PREG(0));
   __vcop_vloop_end(1u);

   /* VLOOP 2 Start */

   /* VLOOP Local Vector Registers */
   #pragma VCC_VREG("Vsz", 26);
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("Addr0", "A0");
   #pragma EVE_REG("Addr1", "A1");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("i", "I3");
   #pragma EVE_REG("j", "I4");
   

   __vcop_vloop(__vcop_compute(), 6u, 5u, 2u);
   __vcop_vagen(_AGEN(0), _PREG(0), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(1), _PREG(6), _PREG(7), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeHU(), __vcop_1pt(), _PREG(8), _AGEN(1), _VREG(26), __vcop_alws());
   __vcop_vadd(_VREG(19), _VREG(26), _VREG(19));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeHU(), __vcop_1pt(), __vcop_last_i4(), _VREG(19), _PREG(10), _AGEN(0), _PREG(0));
   __vcop_vloop_end(2u);

}

void vcop_hough_for_circle_detect(
   __vptr_uint8 houghSpacePtr,
   __vptr_uint32 pUpperLeftXY,
   __vptr_uint32 xSequence,
   __vptr_uint16 pNumCircles,
   __vptr_uint32 pCenterListXY,
   __vptr_uint8 pHoughScoreList,
   unsigned char houghScoreThreshold,
   unsigned short houghSpaceWidth,
   unsigned short houghSpaceHeight,
   unsigned short houghSpacePitch,
   unsigned char houghSpaceShift)
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_hough_for_circle_detect_init(houghSpacePtr, pUpperLeftXY, xSequence, pNumCircles, pCenterListXY, pHoughScoreList, houghScoreThreshold, houghSpaceWidth, houghSpaceHeight, houghSpacePitch, houghSpaceShift, __pblock_vcop_hough_for_circle_detect);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_hough_for_circle_detect_vloops(__pblock_vcop_hough_for_circle_detect);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

void vcop_hough_for_circle_detect_custom(
   __vptr_uint8 houghSpacePtr,
   __vptr_uint32 pUpperLeftXY,
   __vptr_uint32 xSequence,
   __vptr_uint16 pNumCircles,
   __vptr_uint32 pCenterListXY,
   __vptr_uint8 pHoughScoreList,
   unsigned char houghScoreThreshold,
   unsigned short houghSpaceWidth,
   unsigned short houghSpaceHeight,
   unsigned short houghSpacePitch,
   unsigned char houghSpaceShift,
   unsigned short pblock[])
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_hough_for_circle_detect_init(houghSpacePtr, pUpperLeftXY, xSequence, pNumCircles, pCenterListXY, pHoughScoreList, houghScoreThreshold, houghSpaceWidth, houghSpaceHeight, houghSpacePitch, houghSpaceShift, pblock);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_hough_for_circle_detect_vloops(pblock);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

