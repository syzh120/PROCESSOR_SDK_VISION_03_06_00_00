#include <vcop\vcop.h>

typedef unsigned char uchar;

#pragma DATA_SECTION(__pblock_vcop_raw2rgb_CGGC_i16u_o16u, ".vcop_parameter_block")
#pragma DATA_ALIGN(__pblock_vcop_raw2rgb_CGGC_i16u_o16u, __ALIGNOF__(int));
unsigned short __pblock_vcop_raw2rgb_CGGC_i16u_o16u[186];

unsigned int vcop_raw2rgb_CGGC_i16u_o16u_param_count(void)
{
   return 186u;
}

unsigned int vcop_raw2rgb_CGGC_i16u_o16u_ctrl_count(void)
{
   return 0u;
}

unsigned int vcop_raw2rgb_CGGC_i16u_o16u_init(
   __vptr_uint16 pInBuff,
   __vptr_uint16 pRbuff,
   __vptr_uint16 pGbuff,
   __vptr_uint16 pBbuff,
   __vptr_uint16 pScratch,
   unsigned short blkWidth,
   unsigned short blkHeight,
   unsigned short input_stride,
   unsigned short outputG_stride,
   unsigned short outputRB_stride,
   unsigned short pblock[])
{
   int __offset = 0;
   /* Loop 1 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), ((blkHeight + 2)/2)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), (((((blkWidth + 2)/2) + (8u)-1) & ~((8u)-1))/(8u))-1u);
   __vcop_pblock_init32(pblock, __offset+_PREG(6), -3);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)pInBuff+2*sizeof(*pInBuff));
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)pInBuff+2*input_stride*sizeof(*pInBuff));
   __vcop_pblock_init32(pblock, __offset+_PREG(12), (uchar *)pInBuff+2*input_stride*sizeof(*pInBuff)+2*sizeof(*pInBuff));
   __vcop_pblock_init32(pblock, __offset+_PREG(14), (uchar *)pInBuff+2*input_stride*sizeof(*pInBuff)+4*sizeof(*pInBuff));
   __vcop_pblock_init32(pblock, __offset+_PREG(16), (uchar *)pInBuff+4*input_stride*sizeof(*pInBuff)+2*sizeof(*pInBuff));
   __vcop_pblock_init32(pblock, __offset+_PREG(18), (uchar *)pInBuff+input_stride*sizeof(*pInBuff)+2*sizeof(*pInBuff));
   __vcop_pblock_init32(pblock, __offset+_PREG(20), (uchar *)pInBuff+3*input_stride*sizeof(*pInBuff)+2*sizeof(*pInBuff));
   __vcop_pblock_init32(pblock, __offset+_PREG(22), (uchar *)pGbuff);
   __vcop_pblock_init32(pblock, __offset+_PREG(24), (uchar *)pGbuff+sizeof(*pRbuff));
   __vcop_pblock_init16(pblock, __offset+_PREG(26), 32);
   __vcop_pblock_init16(pblock, __offset+_PREG(27), (2*input_stride*sizeof(*pInBuff)) -((8u*2)*sizeof(*pInBuff))*((((((blkWidth + 2)/2) + (8u)-1) & ~((8u)-1))/(8u))-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(28), (2*outputG_stride*sizeof(*pRbuff)) -((8u*2)*sizeof(*pRbuff))*((((((blkWidth + 2)/2) + (8u)-1) & ~((8u)-1))/(8u))-1u));
   __vcop_pblock_init32(pblock, __offset+_PREG(30), -1);
   __vcop_pblock_init32(pblock, __offset+_PREG(32), -2);
   __offset += 32;

   /* Loop 2 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), ((blkHeight + 6)/2)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), ((((blkWidth + 6) + (8u)-1) & ~((8u)-1))/(8u))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(6), 16);
   __vcop_pblock_init16(pblock, __offset+_PREG(7), (2*input_stride*sizeof(*pInBuff)) -(8u*sizeof(*pInBuff))*(((((blkWidth + 6) + (8u)-1) & ~((8u)-1))/(8u))-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(8), (input_stride*sizeof(*pInBuff)) -(8u*sizeof(*pInBuff))*(((((blkWidth + 6) + (8u)-1) & ~((8u)-1))/(8u))-1u));
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)pInBuff+(input_stride+1)*sizeof(*pInBuff));
   __vcop_pblock_init32(pblock, __offset+_PREG(12), (uchar *)pScratch);
   __offset += 12;

   /* Loop 3 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), ((blkHeight + 2)/2)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), (((((blkWidth + 2)/2) + (8u)-1) & ~((8u)-1))/(8u))-1u);
   __vcop_pblock_init32(pblock, __offset+_PREG(6), (uchar *)pScratch+input_stride*sizeof(*pInBuff)+2*sizeof(*pInBuff));
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)pInBuff+(input_stride+1)*sizeof(*pInBuff)+2*input_stride*sizeof(*pInBuff)+4*sizeof(*pInBuff));
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)pInBuff+(input_stride+1)*sizeof(*pInBuff)+4*input_stride*sizeof(*pInBuff)+2*sizeof(*pInBuff));
   __vcop_pblock_init32(pblock, __offset+_PREG(12), (uchar *)pInBuff+(input_stride+1)*sizeof(*pInBuff)+input_stride*sizeof(*pInBuff)+2*sizeof(*pInBuff));
   __vcop_pblock_init32(pblock, __offset+_PREG(14), (uchar *)pInBuff+(input_stride+1)*sizeof(*pInBuff)+3*input_stride*sizeof(*pInBuff)+2*sizeof(*pInBuff));
   __vcop_pblock_init32(pblock, __offset+_PREG(16), (uchar *)pGbuff+(outputG_stride+1)*sizeof(*pRbuff));
   __vcop_pblock_init16(pblock, __offset+_PREG(18), 32);
   __vcop_pblock_init16(pblock, __offset+_PREG(19), (2*input_stride*sizeof(*pInBuff)) -((8u*2)*sizeof(*pInBuff))*((((((blkWidth + 2)/2) + (8u)-1) & ~((8u)-1))/(8u))-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(20), (2*outputG_stride*sizeof(*pRbuff)) -((8u*2)*sizeof(*pRbuff))*((((((blkWidth + 2)/2) + (8u)-1) & ~((8u)-1))/(8u))-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(21), (input_stride*sizeof(*pInBuff)) -((8u*2)*sizeof(*pInBuff))*((((((blkWidth + 2)/2) + (8u)-1) & ~((8u)-1))/(8u))-1u));
   __vcop_pblock_init32(pblock, __offset+_PREG(22), (uchar *)pInBuff+(input_stride+1)*sizeof(*pInBuff)+2*sizeof(*pInBuff));
   __vcop_pblock_init32(pblock, __offset+_PREG(24), (uchar *)pScratch+input_stride*sizeof(*pInBuff));
   __offset += 24;

   /* Loop 4 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), (blkHeight/2)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), ((((blkWidth/2) + (8u)-1) & ~((8u)-1))/(8u))-1u);
   __vcop_pblock_init32(pblock, __offset+_PREG(6), (uchar *)pInBuff+5*input_stride*sizeof(*pInBuff)+3*sizeof(*pInBuff));
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)pGbuff+outputG_stride*sizeof(*pRbuff)+sizeof(*pRbuff));
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)pGbuff+outputG_stride*sizeof(*pRbuff)+3*sizeof(*pRbuff));
   __vcop_pblock_init32(pblock, __offset+_PREG(12), (uchar *)pGbuff+2*outputG_stride*sizeof(*pRbuff)+sizeof(*pRbuff));
   __vcop_pblock_init32(pblock, __offset+_PREG(14), (uchar *)pGbuff+3*outputG_stride*sizeof(*pRbuff)+sizeof(*pRbuff));
   __vcop_pblock_init32(pblock, __offset+_PREG(16), (uchar *)pRbuff);
   __vcop_pblock_init32(pblock, __offset+_PREG(18), (uchar *)pRbuff+outputRB_stride*sizeof(*pRbuff));
   __vcop_pblock_init32(pblock, __offset+_PREG(20), (uchar *)pRbuff+sizeof(*pRbuff));
   __vcop_pblock_init32(pblock, __offset+_PREG(22), (uchar *)pScratch);
   __vcop_pblock_init32(pblock, __offset+_PREG(24), (uchar *)pScratch+sizeof(*pRbuff));
   __vcop_pblock_init16(pblock, __offset+_PREG(26), 32);
   __vcop_pblock_init16(pblock, __offset+_PREG(27), (2*input_stride*sizeof(*pInBuff)) -((8u*2)*sizeof(*pInBuff))*(((((blkWidth/2) + (8u)-1) & ~((8u)-1))/(8u))-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(28), (2*outputG_stride*sizeof(*pRbuff)) -((8u*2)*sizeof(*pRbuff))*(((((blkWidth/2) + (8u)-1) & ~((8u)-1))/(8u))-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(29), (2*outputRB_stride*sizeof(*pRbuff)) -((8u*2)*sizeof(*pRbuff))*(((((blkWidth/2) + (8u)-1) & ~((8u)-1))/(8u))-1u));
   __vcop_pblock_init32(pblock, __offset+_PREG(30), (uchar *)pInBuff+3*input_stride*sizeof(*pInBuff)+3*sizeof(*pInBuff));
   __vcop_pblock_init32(pblock, __offset+_PREG(32), (uchar *)pInBuff+3*input_stride*sizeof(*pInBuff)+5*sizeof(*pInBuff));
   __offset += 32;

   /* Loop 5 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), (blkHeight/2)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), ((((blkWidth/2) + (8u)-1) & ~((8u)-1))/(8u))-1u);
   __vcop_pblock_init32(pblock, __offset+_PREG(6), (uchar *)pInBuff+5*input_stride*sizeof(*pInBuff)+3*sizeof(*pInBuff));
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)pInBuff+5*input_stride*sizeof(*pInBuff)+5*sizeof(*pInBuff));
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)pScratch);
   __vcop_pblock_init32(pblock, __offset+_PREG(12), (uchar *)pGbuff+2*outputG_stride*sizeof(*pRbuff)+2*sizeof(*pRbuff));
   __vcop_pblock_init32(pblock, __offset+_PREG(14), (uchar *)pGbuff+3*outputG_stride*sizeof(*pRbuff)+sizeof(*pRbuff));
   __vcop_pblock_init32(pblock, __offset+_PREG(16), (uchar *)pGbuff+3*outputG_stride*sizeof(*pRbuff)+3*sizeof(*pRbuff));
   __vcop_pblock_init32(pblock, __offset+_PREG(18), (uchar *)pRbuff+outputRB_stride*sizeof(*pRbuff)+sizeof(*pRbuff));
   __vcop_pblock_init16(pblock, __offset+_PREG(20), 32);
   __vcop_pblock_init16(pblock, __offset+_PREG(21), (2*input_stride*sizeof(*pInBuff)) -((8u*2)*sizeof(*pInBuff))*(((((blkWidth/2) + (8u)-1) & ~((8u)-1))/(8u))-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(22), (2*outputG_stride*sizeof(*pRbuff)) -((8u*2)*sizeof(*pRbuff))*(((((blkWidth/2) + (8u)-1) & ~((8u)-1))/(8u))-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(23), (2*outputRB_stride*sizeof(*pRbuff)) -((8u*2)*sizeof(*pRbuff))*(((((blkWidth/2) + (8u)-1) & ~((8u)-1))/(8u))-1u));
   __vcop_pblock_init32(pblock, __offset+_PREG(24), (uchar *)pInBuff+3*input_stride*sizeof(*pInBuff)+3*sizeof(*pInBuff));
   __vcop_pblock_init32(pblock, __offset+_PREG(26), (uchar *)pInBuff+3*input_stride*sizeof(*pInBuff)+5*sizeof(*pInBuff));
   __offset += 26;

   /* Loop 6 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), (blkHeight/2)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), ((((blkWidth/2) + (8u)-1) & ~((8u)-1))/(8u))-1u);
   __vcop_pblock_init32(pblock, __offset+_PREG(6), (uchar *)pInBuff+(-1+5)*input_stride*sizeof(*pInBuff)+(-1+5)*sizeof(*pInBuff));
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)pGbuff+(-1+1)*outputG_stride*sizeof(*pRbuff)+(-1+3)*sizeof(*pRbuff));
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)pGbuff+(-1+2)*outputG_stride*sizeof(*pRbuff)+(-1+3)*sizeof(*pRbuff));
   __vcop_pblock_init32(pblock, __offset+_PREG(12), (uchar *)pGbuff+(-1+3)*outputG_stride*sizeof(*pRbuff)+(-1+1)*sizeof(*pRbuff));
   __vcop_pblock_init32(pblock, __offset+_PREG(14), (uchar *)pGbuff+(-1+3)*outputG_stride*sizeof(*pRbuff)+(-1+2)*sizeof(*pRbuff));
   __vcop_pblock_init32(pblock, __offset+_PREG(16), (uchar *)pGbuff+(-1+3)*outputG_stride*sizeof(*pRbuff)+(-1+3)*sizeof(*pRbuff));
   __vcop_pblock_init32(pblock, __offset+_PREG(18), (uchar *)pBbuff+outputRB_stride*sizeof(*pRbuff));
   __vcop_pblock_init32(pblock, __offset+_PREG(20), (uchar *)pBbuff+outputRB_stride*sizeof(*pRbuff)+sizeof(*pRbuff));
   __vcop_pblock_init32(pblock, __offset+_PREG(22), (uchar *)pBbuff+sizeof(*pRbuff));
   __vcop_pblock_init32(pblock, __offset+_PREG(24), (uchar *)pScratch);
   __vcop_pblock_init32(pblock, __offset+_PREG(26), (uchar *)pScratch+sizeof(*pRbuff));
   __vcop_pblock_init16(pblock, __offset+_PREG(28), 32);
   __vcop_pblock_init16(pblock, __offset+_PREG(29), (2*input_stride*sizeof(*pInBuff)) -((8u*2)*sizeof(*pInBuff))*(((((blkWidth/2) + (8u)-1) & ~((8u)-1))/(8u))-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(30), (2*outputG_stride*sizeof(*pRbuff)) -((8u*2)*sizeof(*pRbuff))*(((((blkWidth/2) + (8u)-1) & ~((8u)-1))/(8u))-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(31), (2*outputRB_stride*sizeof(*pRbuff)) -((8u*2)*sizeof(*pRbuff))*(((((blkWidth/2) + (8u)-1) & ~((8u)-1))/(8u))-1u));
   __vcop_pblock_init32(pblock, __offset+_PREG(32), (uchar *)pInBuff+(-1+3)*input_stride*sizeof(*pInBuff)+(-1+5)*sizeof(*pInBuff));
   __vcop_pblock_init32(pblock, __offset+_PREG(34), (uchar *)pInBuff+(-1+5)*input_stride*sizeof(*pInBuff)+(-1+3)*sizeof(*pInBuff));
   __offset += 34;

   /* Loop 7 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), (blkHeight/2)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), ((((blkWidth/2) + (8u)-1) & ~((8u)-1))/(8u))-1u);
   __vcop_pblock_init32(pblock, __offset+_PREG(6), (uchar *)pInBuff+(-1+5)*input_stride*sizeof(*pInBuff)+(-1+3)*sizeof(*pInBuff));
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)pInBuff+(-1+5)*input_stride*sizeof(*pInBuff)+(-1+5)*sizeof(*pInBuff));
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)pGbuff+(-1+1)*outputG_stride*sizeof(*pRbuff)+(-1+1)*sizeof(*pRbuff));
   __vcop_pblock_init32(pblock, __offset+_PREG(12), (uchar *)pGbuff+(-1+1)*outputG_stride*sizeof(*pRbuff)+(-1+3)*sizeof(*pRbuff));
   __vcop_pblock_init32(pblock, __offset+_PREG(14), (uchar *)pGbuff+(-1+2)*outputG_stride*sizeof(*pRbuff)+(-1+2)*sizeof(*pRbuff));
   __vcop_pblock_init32(pblock, __offset+_PREG(16), (uchar *)pScratch);
   __vcop_pblock_init32(pblock, __offset+_PREG(18), (uchar *)pBbuff);
   __vcop_pblock_init16(pblock, __offset+_PREG(20), 32);
   __vcop_pblock_init16(pblock, __offset+_PREG(21), (2*input_stride*sizeof(*pInBuff)) -((8u*2)*sizeof(*pInBuff))*(((((blkWidth/2) + (8u)-1) & ~((8u)-1))/(8u))-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(22), (2*outputG_stride*sizeof(*pRbuff)) -((8u*2)*sizeof(*pRbuff))*(((((blkWidth/2) + (8u)-1) & ~((8u)-1))/(8u))-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(23), (2*outputRB_stride*sizeof(*pRbuff)) -((8u*2)*sizeof(*pRbuff))*(((((blkWidth/2) + (8u)-1) & ~((8u)-1))/(8u))-1u));
   __vcop_pblock_init32(pblock, __offset+_PREG(24), (uchar *)pInBuff+(-1+3)*input_stride*sizeof(*pInBuff)+(-1+3)*sizeof(*pInBuff));
   __vcop_pblock_init32(pblock, __offset+_PREG(26), (uchar *)pInBuff+(-1+3)*input_stride*sizeof(*pInBuff)+(-1+5)*sizeof(*pInBuff));
   __offset += 26;

   return 186u;
}

void vcop_raw2rgb_CGGC_i16u_o16u_vloops(
   unsigned short pblock[])
{
   /* Kernel-wide Vector Registers */
   #pragma VCC_VREG("Vone", 16);
   #pragma VCC_VREG("Vthree", 17);
   #pragma VCC_VREG("Vtwo", 18);

   __vcop_param(&pblock[0]);

   /* VLOOP 1 Start */

   /* VLOOP Local Vector Registers */
   #pragma VCC_VREG("A1", 19);
   #pragma VCC_VREG("A3", 20);
   #pragma VCC_VREG("A5", 21);
   #pragma VCC_VREG("A7", 22);
   #pragma VCC_VREG("A9", 23);
   #pragma VCC_VREG("DH", 24);
   #pragma VCC_VREG("DHchroma", 25);
   #pragma VCC_VREG("DHchroma_div4", 26);
   #pragma VCC_VREG("DV", 27);
   #pragma VCC_VREG("DVchroma", 28);
   #pragma VCC_VREG("DVchroma_div4", 29);
   #pragma VCC_VREG("G2", 30);
   #pragma VCC_VREG("G2mG8", 31);
   #pragma VCC_VREG("G2pG8", 32);
   #pragma VCC_VREG("G2pG8_div2", 33);
   #pragma VCC_VREG("G4", 34);
   #pragma VCC_VREG("G4mG6", 35);
   #pragma VCC_VREG("G4pG6", 36);
   #pragma VCC_VREG("G4pG6_div2", 37);
   #pragma VCC_VREG("G5A", 38);
   #pragma VCC_VREG("G5A_tmp", 39);
   #pragma VCC_VREG("G5H", 40);
   #pragma VCC_VREG("G5V", 41);
   #pragma VCC_VREG("G6", 42);
   #pragma VCC_VREG("G6tmp", 43);
   #pragma VCC_VREG("G8", 44);
   #pragma VCC_VREG("abdiffDHchroma", 45);
   #pragma VCC_VREG("abdiffDVchroma", 46);
   #pragma VCC_VREG("abdiffG2mG8", 47);
   #pragma VCC_VREG("abdiffG4mG6", 48);
   #pragma VCC_VREG("flagEq", 49);
   #pragma VCC_VREG("flagH", 50);
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("inputAddr", "A0");
   #pragma EVE_REG("outputAddr", "A1");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("h", "I3");
   #pragma EVE_REG("w", "I4");
   

   __vcop_vloop(__vcop_compute(), 47u, 16u, 1u);
   __vcop_vinit(__vcop_sizeW(), __vcop_once(), _PREG(30), _VREG(16));
   __vcop_vinit(__vcop_sizeW(), __vcop_once(), _PREG(32), _VREG(18));
   __vcop_vinit(__vcop_sizeW(), __vcop_once(), _PREG(6), _VREG(17));
   __vcop_vagen(_AGEN(0), _PREG(26), _PREG(27), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(1), _PREG(26), _PREG(28), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeHU(), __vcop_ds2(), _PREG(8), _AGEN(0), _VREG(19), __vcop_alws());
   __vcop_vload(__vcop_sizeHU(), __vcop_dintrlv(), _PREG(10), _AGEN(0), _VPAIR(20,34), __vcop_alws());
   __vcop_vload(__vcop_sizeHU(), __vcop_dintrlv(), _PREG(12), _AGEN(0), _VPAIR(21,42), __vcop_alws());
   __vcop_vload(__vcop_sizeHU(), __vcop_ds2(), _PREG(14), _AGEN(0), _VREG(22), __vcop_alws());
   __vcop_vload(__vcop_sizeHU(), __vcop_ds2(), _PREG(16), _AGEN(0), _VREG(23), __vcop_alws());
   __vcop_vload(__vcop_sizeHU(), __vcop_ds2(), _PREG(18), _AGEN(0), _VREG(30), __vcop_alws());
   __vcop_vload(__vcop_sizeHU(), __vcop_ds2(), _PREG(20), _AGEN(0), _VREG(44), __vcop_alws());
   __vcop_vor(_VREG(42), _VREG(42), _VREG(43));
   __vcop_vmove(_VREG(34), _VREG(36));
   __vcop_vmove(_VREG(42), _VREG(35));
   __vcop_vaddsub(_VREG(36), _VREG(35));
   __vcop_vmove(_VREG(30), _VREG(32));
   __vcop_vmove(_VREG(44), _VREG(31));
   __vcop_vaddsub(_VREG(32), _VREG(31));
   __vcop_vabs(_VREG(35), _VREG(48));
   __vcop_vabs(_VREG(31), _VREG(47));
   __vcop_vsub(_VREG(21), _VREG(22), _VREG(25));
   __vcop_vsub(_VREG(21), _VREG(23), _VREG(28));
   __vcop_vadif(_VREG(21), _VREG(20), _VREG(25));
   __vcop_vadif(_VREG(21), _VREG(19), _VREG(28));
   __vcop_vabs(_VREG(25), _VREG(45));
   __vcop_vabs(_VREG(28), _VREG(46));
   __vcop_vadd(_VREG(45), _VREG(48), _VREG(24));
   __vcop_vadd(_VREG(46), _VREG(47), _VREG(27));
   __vcop_vshf(_VREG(36), _VREG(16), _VREG(37));
   __vcop_vshf(_VREG(32), _VREG(16), _VREG(33));
   __vcop_vshf(_VREG(25), _VREG(18), _VREG(26));
   __vcop_vshf(_VREG(28), _VREG(18), _VREG(29));
   __vcop_vadd(_VREG(37), _VREG(26), _VREG(40));
   __vcop_vadd(_VREG(33), _VREG(29), _VREG(41));
   __vcop_vadd(_VREG(32), _VREG(36), _VREG(38));
   __vcop_vadd(_VREG(25), _VREG(28), _VREG(39));
   __vcop_vshf(_VREG(38), _VREG(18), _VREG(38));
   __vcop_vshf(_VREG(39), _VREG(17), _VREG(39));
   __vcop_vadd(_VREG(38), _VREG(39), _VREG(38));
   __vcop_vcmplt(_VREG(24), _VREG(27), _VREG(50));
   __vcop_vcmpeq(_VREG(24), _VREG(27), _VREG(49));
   __vcop_vsel(_VREG(50), _VREG(40), _VREG(41));
   __vcop_vsel(_VREG(49), _VREG(38), _VREG(41));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeHU(), __vcop_skip(), __vcop_alws(), _VREG(41), _PREG(22), _AGEN(1), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeHU(), __vcop_skip(), __vcop_alws(), _VREG(43), _PREG(24), _AGEN(1), _PREG(0));
   __vcop_vloop_end(1u);

   /* VLOOP 2 Start */

   /* VLOOP Local Vector Registers */
   #pragma VCC_VREG("A1", 51);
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("inputAddr", "A0");
   #pragma EVE_REG("outputAddr", "A1");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("h", "I3");
   #pragma EVE_REG("w", "I4");
   

   __vcop_vloop(__vcop_compute(), 5u, 6u, 2u);
   __vcop_vagen(_AGEN(0), _PREG(6), _PREG(7), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(1), _PREG(6), _PREG(8), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeHU(), __vcop_npt(), _PREG(10), _AGEN(0), _VREG(51), __vcop_alws());
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeHU(), __vcop_npt(), __vcop_alws(), _VREG(51), _PREG(12), _AGEN(1), _PREG(0));
   __vcop_vloop_end(2u);

   /* VLOOP 3 Start */

   /* VLOOP Local Vector Registers */
   #pragma VCC_VREG("A1", 52);
   #pragma VCC_VREG("A3", 53);
   #pragma VCC_VREG("A5", 54);
   #pragma VCC_VREG("A7", 55);
   #pragma VCC_VREG("A9", 56);
   #pragma VCC_VREG("DH", 57);
   #pragma VCC_VREG("DHchroma", 58);
   #pragma VCC_VREG("DHchroma_div4", 59);
   #pragma VCC_VREG("DV", 60);
   #pragma VCC_VREG("DVchroma", 61);
   #pragma VCC_VREG("DVchroma_div4", 62);
   #pragma VCC_VREG("G2", 63);
   #pragma VCC_VREG("G2mG8", 64);
   #pragma VCC_VREG("G2pG8", 65);
   #pragma VCC_VREG("G2pG8_div2", 66);
   #pragma VCC_VREG("G4", 67);
   #pragma VCC_VREG("G4mG6", 68);
   #pragma VCC_VREG("G4pG6", 69);
   #pragma VCC_VREG("G4pG6_div2", 70);
   #pragma VCC_VREG("G5A", 71);
   #pragma VCC_VREG("G5A_tmp", 72);
   #pragma VCC_VREG("G5H", 73);
   #pragma VCC_VREG("G5V", 74);
   #pragma VCC_VREG("G6", 75);
   #pragma VCC_VREG("G6tmp", 76);
   #pragma VCC_VREG("G8", 77);
   #pragma VCC_VREG("abdiffDHchroma", 78);
   #pragma VCC_VREG("abdiffDVchroma", 79);
   #pragma VCC_VREG("abdiffG2mG8", 80);
   #pragma VCC_VREG("abdiffG4mG6", 81);
   #pragma VCC_VREG("flagEq", 82);
   #pragma VCC_VREG("flagH", 83);
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("inputAddr", "A0");
   #pragma EVE_REG("outputAddr", "A1");
   #pragma EVE_REG("scratchAddr", "A2");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("h", "I3");
   #pragma EVE_REG("w", "I4");
   

   __vcop_vloop(__vcop_compute(), 44u, 12u, 3u);
   __vcop_vagen(_AGEN(0), _PREG(18), _PREG(19), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(1), _PREG(18), _PREG(20), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(2), _PREG(18), _PREG(21), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeHU(), __vcop_ds2(), _PREG(22), _AGEN(0), _VREG(52), __vcop_alws());
   __vcop_vload(__vcop_sizeHU(), __vcop_dintrlv(), _PREG(24), _AGEN(2), _VPAIR(53,67), __vcop_alws());
   __vcop_vload(__vcop_sizeHU(), __vcop_dintrlv(), _PREG(6), _AGEN(2), _VPAIR(54,75), __vcop_alws());
   __vcop_vload(__vcop_sizeHU(), __vcop_ds2(), _PREG(8), _AGEN(0), _VREG(55), __vcop_alws());
   __vcop_vload(__vcop_sizeHU(), __vcop_ds2(), _PREG(10), _AGEN(0), _VREG(56), __vcop_alws());
   __vcop_vload(__vcop_sizeHU(), __vcop_ds2(), _PREG(12), _AGEN(0), _VREG(63), __vcop_alws());
   __vcop_vload(__vcop_sizeHU(), __vcop_ds2(), _PREG(14), _AGEN(0), _VREG(77), __vcop_alws());
   __vcop_vor(_VREG(75), _VREG(75), _VREG(76));
   __vcop_vmove(_VREG(67), _VREG(69));
   __vcop_vmove(_VREG(75), _VREG(68));
   __vcop_vaddsub(_VREG(69), _VREG(68));
   __vcop_vmove(_VREG(63), _VREG(65));
   __vcop_vmove(_VREG(77), _VREG(64));
   __vcop_vaddsub(_VREG(65), _VREG(64));
   __vcop_vabs(_VREG(68), _VREG(81));
   __vcop_vabs(_VREG(64), _VREG(80));
   __vcop_vsub(_VREG(54), _VREG(55), _VREG(58));
   __vcop_vsub(_VREG(54), _VREG(56), _VREG(61));
   __vcop_vadif(_VREG(54), _VREG(53), _VREG(58));
   __vcop_vadif(_VREG(54), _VREG(52), _VREG(61));
   __vcop_vabs(_VREG(58), _VREG(78));
   __vcop_vabs(_VREG(61), _VREG(79));
   __vcop_vadd(_VREG(78), _VREG(81), _VREG(57));
   __vcop_vadd(_VREG(79), _VREG(80), _VREG(60));
   __vcop_vshf(_VREG(69), _VREG(16), _VREG(70));
   __vcop_vshf(_VREG(65), _VREG(16), _VREG(66));
   __vcop_vshf(_VREG(58), _VREG(18), _VREG(59));
   __vcop_vshf(_VREG(61), _VREG(18), _VREG(62));
   __vcop_vadd(_VREG(70), _VREG(59), _VREG(73));
   __vcop_vadd(_VREG(66), _VREG(62), _VREG(74));
   __vcop_vadd(_VREG(65), _VREG(69), _VREG(71));
   __vcop_vadd(_VREG(58), _VREG(61), _VREG(72));
   __vcop_vshf(_VREG(71), _VREG(18), _VREG(71));
   __vcop_vshf(_VREG(72), _VREG(17), _VREG(72));
   __vcop_vadd(_VREG(71), _VREG(72), _VREG(71));
   __vcop_vcmplt(_VREG(57), _VREG(60), _VREG(83));
   __vcop_vcmpeq(_VREG(57), _VREG(60), _VREG(82));
   __vcop_vsel(_VREG(83), _VREG(73), _VREG(74));
   __vcop_vsel(_VREG(82), _VREG(71), _VREG(74));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeHU(), __vcop_intrlv(), __vcop_alws(), _VPAIR(74,76), _PREG(16), _AGEN(1), _PREG(0));
   __vcop_vloop_end(3u);

   /* VLOOP 4 Start */

   /* VLOOP Local Vector Registers */
   #pragma VCC_VREG("A1", 84);
   #pragma VCC_VREG("A2", 85);
   #pragma VCC_VREG("A2_tmp", 86);
   #pragma VCC_VREG("A3", 87);
   #pragma VCC_VREG("A4", 88);
   #pragma VCC_VREG("A4_tmp", 89);
   #pragma VCC_VREG("A7", 90);
   #pragma VCC_VREG("G1", 91);
   #pragma VCC_VREG("G2", 92);
   #pragma VCC_VREG("G3", 93);
   #pragma VCC_VREG("G4", 94);
   #pragma VCC_VREG("G5", 95);
   #pragma VCC_VREG("G7", 96);
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("inputAddr", "A0");
   #pragma EVE_REG("inputGaddr", "A1");
   #pragma EVE_REG("outputAddr", "A2");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("h", "I3");
   #pragma EVE_REG("w", "I4");
   

   __vcop_vloop(__vcop_compute(), 28u, 16u, 4u);
   __vcop_vagen(_AGEN(0), _PREG(26), _PREG(27), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(1), _PREG(26), _PREG(28), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(2), _PREG(26), _PREG(29), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeHU(), __vcop_ds2(), _PREG(30), _AGEN(0), _VREG(84), __vcop_alws());
   __vcop_vload(__vcop_sizeHU(), __vcop_ds2(), _PREG(32), _AGEN(0), _VREG(87), __vcop_alws());
   __vcop_vload(__vcop_sizeHU(), __vcop_ds2(), _PREG(6), _AGEN(0), _VREG(90), __vcop_alws());
   __vcop_vload(__vcop_sizeHU(), __vcop_dintrlv(), _PREG(8), _AGEN(1), _VPAIR(91,92), __vcop_alws());
   __vcop_vload(__vcop_sizeHU(), __vcop_ds2(), _PREG(10), _AGEN(1), _VREG(93), __vcop_alws());
   __vcop_vload(__vcop_sizeHU(), __vcop_ds2(), _PREG(12), _AGEN(1), _VREG(94), __vcop_alws());
   __vcop_vload(__vcop_sizeHU(), __vcop_ds2(), _PREG(14), _AGEN(1), _VREG(96), __vcop_alws());
   __vcop_vadd(_VREG(84), _VREG(90), _VREG(88));
   __vcop_vadd(_VREG(84), _VREG(87), _VREG(85));
   __vcop_vshf(_VREG(88), _VREG(16), _VREG(88));
   __vcop_vshf(_VREG(85), _VREG(16), _VREG(85));
   __vcop_vsub(_VREG(94), _VREG(96), _VREG(89));
   __vcop_vsub(_VREG(92), _VREG(93), _VREG(86));
   __vcop_vadif(_VREG(94), _VREG(91), _VREG(89));
   __vcop_vadif(_VREG(92), _VREG(91), _VREG(86));
   __vcop_vshf(_VREG(89), _VREG(16), _VREG(89));
   __vcop_vshf(_VREG(86), _VREG(16), _VREG(86));
   __vcop_vadd(_VREG(88), _VREG(89), _VREG(88));
   __vcop_vadd(_VREG(85), _VREG(86), _VREG(85));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeHU(), __vcop_skip(), __vcop_alws(), _VREG(84), _PREG(16), _AGEN(2), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeHU(), __vcop_skip(), __vcop_alws(), _VREG(88), _PREG(18), _AGEN(2), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeHU(), __vcop_skip(), __vcop_alws(), _VREG(85), _PREG(20), _AGEN(2), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeHU(), __vcop_skip(), __vcop_alws(), _VREG(91), _PREG(22), _AGEN(2), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeHU(), __vcop_skip(), __vcop_alws(), _VREG(93), _PREG(24), _AGEN(2), _PREG(0));
   __vcop_vloop_end(4u);

   /* VLOOP 5 Start */

   /* VLOOP Local Vector Registers */
   #pragma VCC_VREG("A1", 97);
   #pragma VCC_VREG("A1mA9", 98);
   #pragma VCC_VREG("A1pA9", 99);
   #pragma VCC_VREG("A1pA9_div2", 100);
   #pragma VCC_VREG("A3", 101);
   #pragma VCC_VREG("A3mA7", 102);
   #pragma VCC_VREG("A3pA7", 103);
   #pragma VCC_VREG("A3pA7_div2", 104);
   #pragma VCC_VREG("A5A", 105);
   #pragma VCC_VREG("A5A_tmp", 106);
   #pragma VCC_VREG("A5N", 107);
   #pragma VCC_VREG("A5P", 108);
   #pragma VCC_VREG("A7", 109);
   #pragma VCC_VREG("A9", 110);
   #pragma VCC_VREG("DN", 111);
   #pragma VCC_VREG("DNgreen", 112);
   #pragma VCC_VREG("DNgreen_div2", 113);
   #pragma VCC_VREG("DP", 114);
   #pragma VCC_VREG("DPgreen", 115);
   #pragma VCC_VREG("DPgreen_div2", 116);
   #pragma VCC_VREG("G1", 117);
   #pragma VCC_VREG("G3", 118);
   #pragma VCC_VREG("G4", 119);
   #pragma VCC_VREG("G5", 120);
   #pragma VCC_VREG("G7", 121);
   #pragma VCC_VREG("G9", 122);
   #pragma VCC_VREG("abdiffA1mA9", 123);
   #pragma VCC_VREG("abdiffA3mA7", 124);
   #pragma VCC_VREG("abdiffDNgreen", 125);
   #pragma VCC_VREG("abdiffDPgreen", 126);
   #pragma VCC_VREG("flagEq", 127);
   #pragma VCC_VREG("flagN", 128);
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("inputAddr", "A0");
   #pragma EVE_REG("inputGaddr", "A1");
   #pragma EVE_REG("outputAddr", "A2");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("h", "I3");
   #pragma EVE_REG("w", "I4");
   

   __vcop_vloop(__vcop_compute(), 44u, 13u, 5u);
   __vcop_vagen(_AGEN(0), _PREG(20), _PREG(21), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(1), _PREG(20), _PREG(22), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(2), _PREG(20), _PREG(23), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeHU(), __vcop_ds2(), _PREG(24), _AGEN(0), _VREG(97), __vcop_alws());
   __vcop_vload(__vcop_sizeHU(), __vcop_ds2(), _PREG(26), _AGEN(0), _VREG(101), __vcop_alws());
   __vcop_vload(__vcop_sizeHU(), __vcop_ds2(), _PREG(6), _AGEN(0), _VREG(109), __vcop_alws());
   __vcop_vload(__vcop_sizeHU(), __vcop_ds2(), _PREG(8), _AGEN(0), _VREG(110), __vcop_alws());
   __vcop_vload(__vcop_sizeHU(), __vcop_dintrlv(), _PREG(10), _AGEN(2), _VPAIR(117,118), __vcop_alws());
   __vcop_vload(__vcop_sizeHU(), __vcop_ds2(), _PREG(12), _AGEN(1), _VREG(120), __vcop_alws());
   __vcop_vload(__vcop_sizeHU(), __vcop_ds2(), _PREG(14), _AGEN(1), _VREG(121), __vcop_alws());
   __vcop_vload(__vcop_sizeHU(), __vcop_ds2(), _PREG(16), _AGEN(1), _VREG(122), __vcop_alws());
   __vcop_vmove(_VREG(97), _VREG(99));
   __vcop_vmove(_VREG(110), _VREG(98));
   __vcop_vaddsub(_VREG(99), _VREG(98));
   __vcop_vmove(_VREG(101), _VREG(103));
   __vcop_vmove(_VREG(109), _VREG(102));
   __vcop_vaddsub(_VREG(103), _VREG(102));
   __vcop_vabs(_VREG(98), _VREG(123));
   __vcop_vabs(_VREG(102), _VREG(124));
   __vcop_vsub(_VREG(120), _VREG(117), _VREG(112));
   __vcop_vsub(_VREG(120), _VREG(118), _VREG(115));
   __vcop_vadif(_VREG(120), _VREG(122), _VREG(112));
   __vcop_vadif(_VREG(120), _VREG(121), _VREG(115));
   __vcop_vabs(_VREG(112), _VREG(125));
   __vcop_vabs(_VREG(115), _VREG(126));
   __vcop_vadd(_VREG(125), _VREG(123), _VREG(111));
   __vcop_vadd(_VREG(126), _VREG(124), _VREG(114));
   __vcop_vshf(_VREG(99), _VREG(16), _VREG(100));
   __vcop_vshf(_VREG(103), _VREG(16), _VREG(104));
   __vcop_vshf(_VREG(112), _VREG(16), _VREG(113));
   __vcop_vshf(_VREG(115), _VREG(16), _VREG(116));
   __vcop_vadd(_VREG(100), _VREG(113), _VREG(107));
   __vcop_vadd(_VREG(104), _VREG(116), _VREG(108));
   __vcop_vadd(_VREG(99), _VREG(103), _VREG(105));
   __vcop_vadd(_VREG(112), _VREG(115), _VREG(106));
   __vcop_vshf(_VREG(105), _VREG(18), _VREG(105));
   __vcop_vshf(_VREG(106), _VREG(18), _VREG(106));
   __vcop_vadd(_VREG(105), _VREG(106), _VREG(105));
   __vcop_vcmplt(_VREG(111), _VREG(114), _VREG(128));
   __vcop_vcmpeq(_VREG(111), _VREG(114), _VREG(127));
   __vcop_vsel(_VREG(128), _VREG(107), _VREG(108));
   __vcop_vsel(_VREG(127), _VREG(105), _VREG(108));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeHU(), __vcop_skip(), __vcop_alws(), _VREG(108), _PREG(18), _AGEN(2), _PREG(0));
   __vcop_vloop_end(5u);

   /* VLOOP 6 Start */

   /* VLOOP Local Vector Registers */
   #pragma VCC_VREG("A3", 129);
   #pragma VCC_VREG("A6", 130);
   #pragma VCC_VREG("A6_tmp", 131);
   #pragma VCC_VREG("A7", 132);
   #pragma VCC_VREG("A8", 133);
   #pragma VCC_VREG("A8_tmp", 134);
   #pragma VCC_VREG("A9", 135);
   #pragma VCC_VREG("G3", 136);
   #pragma VCC_VREG("G6", 137);
   #pragma VCC_VREG("G7", 138);
   #pragma VCC_VREG("G8", 139);
   #pragma VCC_VREG("G9", 140);
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("inputAddr", "A0");
   #pragma EVE_REG("inputGaddr", "A1");
   #pragma EVE_REG("outputAddr", "A2");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("h", "I3");
   #pragma EVE_REG("w", "I4");
   

   __vcop_vloop(__vcop_compute(), 29u, 17u, 6u);
   __vcop_vagen(_AGEN(0), _PREG(28), _PREG(29), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(1), _PREG(28), _PREG(30), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(2), _PREG(28), _PREG(31), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeHU(), __vcop_ds2(), _PREG(32), _AGEN(0), _VREG(129), __vcop_alws());
   __vcop_vload(__vcop_sizeHU(), __vcop_ds2(), _PREG(34), _AGEN(0), _VREG(132), __vcop_alws());
   __vcop_vload(__vcop_sizeHU(), __vcop_ds2(), _PREG(6), _AGEN(0), _VREG(135), __vcop_alws());
   __vcop_vload(__vcop_sizeHU(), __vcop_ds2(), _PREG(8), _AGEN(1), _VREG(136), __vcop_alws());
   __vcop_vload(__vcop_sizeHU(), __vcop_ds2(), _PREG(10), _AGEN(1), _VREG(137), __vcop_alws());
   __vcop_vload(__vcop_sizeHU(), __vcop_ds2(), _PREG(12), _AGEN(1), _VREG(138), __vcop_alws());
   __vcop_vload(__vcop_sizeHU(), __vcop_ds2(), _PREG(14), _AGEN(1), _VREG(139), __vcop_alws());
   __vcop_vload(__vcop_sizeHU(), __vcop_ds2(), _PREG(16), _AGEN(1), _VREG(140), __vcop_alws());
   __vcop_vadd(_VREG(129), _VREG(135), _VREG(130));
   __vcop_vadd(_VREG(132), _VREG(135), _VREG(133));
   __vcop_vshf(_VREG(130), _VREG(16), _VREG(130));
   __vcop_vshf(_VREG(133), _VREG(16), _VREG(133));
   __vcop_vsub(_VREG(137), _VREG(140), _VREG(131));
   __vcop_vsub(_VREG(139), _VREG(140), _VREG(134));
   __vcop_vadif(_VREG(137), _VREG(136), _VREG(131));
   __vcop_vadif(_VREG(139), _VREG(138), _VREG(134));
   __vcop_vshf(_VREG(131), _VREG(16), _VREG(131));
   __vcop_vshf(_VREG(134), _VREG(16), _VREG(134));
   __vcop_vadd(_VREG(130), _VREG(131), _VREG(130));
   __vcop_vadd(_VREG(133), _VREG(134), _VREG(133));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeHU(), __vcop_skip(), __vcop_alws(), _VREG(133), _PREG(18), _AGEN(2), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeHU(), __vcop_skip(), __vcop_alws(), _VREG(135), _PREG(20), _AGEN(2), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeHU(), __vcop_skip(), __vcop_alws(), _VREG(130), _PREG(22), _AGEN(2), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeHU(), __vcop_skip(), __vcop_alws(), _VREG(138), _PREG(24), _AGEN(2), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeHU(), __vcop_skip(), __vcop_alws(), _VREG(140), _PREG(26), _AGEN(2), _PREG(0));
   __vcop_vloop_end(6u);

   /* VLOOP 7 Start */

   /* VLOOP Local Vector Registers */
   #pragma VCC_VREG("A1", 141);
   #pragma VCC_VREG("A1mA9", 142);
   #pragma VCC_VREG("A1pA9", 143);
   #pragma VCC_VREG("A1pA9_div2", 144);
   #pragma VCC_VREG("A3", 145);
   #pragma VCC_VREG("A3mA7", 146);
   #pragma VCC_VREG("A3pA7", 147);
   #pragma VCC_VREG("A3pA7_div2", 148);
   #pragma VCC_VREG("A5A", 149);
   #pragma VCC_VREG("A5A_tmp", 150);
   #pragma VCC_VREG("A5N", 151);
   #pragma VCC_VREG("A5P", 152);
   #pragma VCC_VREG("A7", 153);
   #pragma VCC_VREG("A9", 154);
   #pragma VCC_VREG("DN", 155);
   #pragma VCC_VREG("DNgreen", 156);
   #pragma VCC_VREG("DNgreen_div2", 157);
   #pragma VCC_VREG("DP", 158);
   #pragma VCC_VREG("DPgreen", 159);
   #pragma VCC_VREG("DPgreen_div2", 160);
   #pragma VCC_VREG("G1", 161);
   #pragma VCC_VREG("G3", 162);
   #pragma VCC_VREG("G5", 163);
   #pragma VCC_VREG("G7", 164);
   #pragma VCC_VREG("G9", 165);
   #pragma VCC_VREG("abdiffA1mA9", 166);
   #pragma VCC_VREG("abdiffA3mA7", 167);
   #pragma VCC_VREG("abdiffDNgreen", 168);
   #pragma VCC_VREG("abdiffDPgreen", 169);
   #pragma VCC_VREG("flagEq", 170);
   #pragma VCC_VREG("flagN", 171);
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("inputAddr", "A0");
   #pragma EVE_REG("inputGaddr", "A1");
   #pragma EVE_REG("outputAddr", "A2");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("h", "I3");
   #pragma EVE_REG("w", "I4");
   

   __vcop_vloop(__vcop_compute(), 44u, 13u, 7u);
   __vcop_vagen(_AGEN(0), _PREG(20), _PREG(21), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(1), _PREG(20), _PREG(22), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(2), _PREG(20), _PREG(23), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeHU(), __vcop_ds2(), _PREG(24), _AGEN(0), _VREG(141), __vcop_alws());
   __vcop_vload(__vcop_sizeHU(), __vcop_ds2(), _PREG(26), _AGEN(0), _VREG(145), __vcop_alws());
   __vcop_vload(__vcop_sizeHU(), __vcop_ds2(), _PREG(6), _AGEN(0), _VREG(153), __vcop_alws());
   __vcop_vload(__vcop_sizeHU(), __vcop_ds2(), _PREG(8), _AGEN(0), _VREG(154), __vcop_alws());
   __vcop_vload(__vcop_sizeHU(), __vcop_ds2(), _PREG(10), _AGEN(1), _VREG(161), __vcop_alws());
   __vcop_vload(__vcop_sizeHU(), __vcop_ds2(), _PREG(12), _AGEN(1), _VREG(162), __vcop_alws());
   __vcop_vload(__vcop_sizeHU(), __vcop_ds2(), _PREG(14), _AGEN(1), _VREG(163), __vcop_alws());
   __vcop_vload(__vcop_sizeHU(), __vcop_dintrlv(), _PREG(16), _AGEN(2), _VPAIR(164,165), __vcop_alws());
   __vcop_vmove(_VREG(141), _VREG(143));
   __vcop_vmove(_VREG(154), _VREG(142));
   __vcop_vaddsub(_VREG(143), _VREG(142));
   __vcop_vmove(_VREG(145), _VREG(147));
   __vcop_vmove(_VREG(153), _VREG(146));
   __vcop_vaddsub(_VREG(147), _VREG(146));
   __vcop_vabs(_VREG(142), _VREG(166));
   __vcop_vabs(_VREG(146), _VREG(167));
   __vcop_vsub(_VREG(163), _VREG(161), _VREG(156));
   __vcop_vsub(_VREG(163), _VREG(162), _VREG(159));
   __vcop_vadif(_VREG(163), _VREG(165), _VREG(156));
   __vcop_vadif(_VREG(163), _VREG(164), _VREG(159));
   __vcop_vabs(_VREG(156), _VREG(168));
   __vcop_vabs(_VREG(159), _VREG(169));
   __vcop_vadd(_VREG(168), _VREG(166), _VREG(155));
   __vcop_vadd(_VREG(169), _VREG(167), _VREG(158));
   __vcop_vshf(_VREG(143), _VREG(16), _VREG(144));
   __vcop_vshf(_VREG(147), _VREG(16), _VREG(148));
   __vcop_vshf(_VREG(156), _VREG(16), _VREG(157));
   __vcop_vshf(_VREG(159), _VREG(16), _VREG(160));
   __vcop_vadd(_VREG(144), _VREG(157), _VREG(151));
   __vcop_vadd(_VREG(148), _VREG(160), _VREG(152));
   __vcop_vadd(_VREG(143), _VREG(147), _VREG(149));
   __vcop_vadd(_VREG(156), _VREG(159), _VREG(150));
   __vcop_vshf(_VREG(149), _VREG(18), _VREG(149));
   __vcop_vshf(_VREG(150), _VREG(18), _VREG(150));
   __vcop_vadd(_VREG(149), _VREG(150), _VREG(149));
   __vcop_vcmplt(_VREG(155), _VREG(158), _VREG(171));
   __vcop_vcmpeq(_VREG(155), _VREG(158), _VREG(170));
   __vcop_vsel(_VREG(171), _VREG(151), _VREG(152));
   __vcop_vsel(_VREG(170), _VREG(149), _VREG(152));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeHU(), __vcop_skip(), __vcop_alws(), _VREG(152), _PREG(18), _AGEN(2), _PREG(0));
   __vcop_vloop_end(7u);

}

void vcop_raw2rgb_CGGC_i16u_o16u(
   __vptr_uint16 pInBuff,
   __vptr_uint16 pRbuff,
   __vptr_uint16 pGbuff,
   __vptr_uint16 pBbuff,
   __vptr_uint16 pScratch,
   unsigned short blkWidth,
   unsigned short blkHeight,
   unsigned short input_stride,
   unsigned short outputG_stride,
   unsigned short outputRB_stride)
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_raw2rgb_CGGC_i16u_o16u_init(pInBuff, pRbuff, pGbuff, pBbuff, pScratch, blkWidth, blkHeight, input_stride, outputG_stride, outputRB_stride, __pblock_vcop_raw2rgb_CGGC_i16u_o16u);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_raw2rgb_CGGC_i16u_o16u_vloops(__pblock_vcop_raw2rgb_CGGC_i16u_o16u);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

void vcop_raw2rgb_CGGC_i16u_o16u_custom(
   __vptr_uint16 pInBuff,
   __vptr_uint16 pRbuff,
   __vptr_uint16 pGbuff,
   __vptr_uint16 pBbuff,
   __vptr_uint16 pScratch,
   unsigned short blkWidth,
   unsigned short blkHeight,
   unsigned short input_stride,
   unsigned short outputG_stride,
   unsigned short outputRB_stride,
   unsigned short pblock[])
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_raw2rgb_CGGC_i16u_o16u_init(pInBuff, pRbuff, pGbuff, pBbuff, pScratch, blkWidth, blkHeight, input_stride, outputG_stride, outputRB_stride, pblock);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_raw2rgb_CGGC_i16u_o16u_vloops(pblock);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

#pragma DATA_SECTION(__pblock_vcop_raw2rgb_GCCG_i16u_o16u, ".vcop_parameter_block")
#pragma DATA_ALIGN(__pblock_vcop_raw2rgb_GCCG_i16u_o16u, __ALIGNOF__(int));
unsigned short __pblock_vcop_raw2rgb_GCCG_i16u_o16u[190];

unsigned int vcop_raw2rgb_GCCG_i16u_o16u_param_count(void)
{
   return 190u;
}

unsigned int vcop_raw2rgb_GCCG_i16u_o16u_ctrl_count(void)
{
   return 0u;
}

unsigned int vcop_raw2rgb_GCCG_i16u_o16u_init(
   __vptr_uint16 pInBuff,
   __vptr_uint16 pRbuff,
   __vptr_uint16 pGbuff,
   __vptr_uint16 pBbuff,
   __vptr_uint16 pScratch,
   unsigned short blkWidth,
   unsigned short blkHeight,
   unsigned short input_stride,
   unsigned short outputG_stride,
   unsigned short outputRB_stride,
   unsigned short pblock[])
{
   int __offset = 0;
   /* Loop 1 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), ((blkHeight + 2)/2)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), (((((blkWidth + 2)/2) + (8u)-1) & ~((8u)-1))/(8u))-1u);
   __vcop_pblock_init32(pblock, __offset+_PREG(6), -3);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)pInBuff+input_stride*sizeof(*pInBuff)+2*sizeof(*pInBuff));
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)pInBuff+input_stride*sizeof(*pInBuff)+2*input_stride*sizeof(*pInBuff));
   __vcop_pblock_init32(pblock, __offset+_PREG(12), (uchar *)pInBuff+input_stride*sizeof(*pInBuff)+2*input_stride*sizeof(*pInBuff)+2*sizeof(*pInBuff));
   __vcop_pblock_init32(pblock, __offset+_PREG(14), (uchar *)pInBuff+input_stride*sizeof(*pInBuff)+2*input_stride*sizeof(*pInBuff)+4*sizeof(*pInBuff));
   __vcop_pblock_init32(pblock, __offset+_PREG(16), (uchar *)pInBuff+input_stride*sizeof(*pInBuff)+4*input_stride*sizeof(*pInBuff)+2*sizeof(*pInBuff));
   __vcop_pblock_init32(pblock, __offset+_PREG(18), (uchar *)pInBuff+input_stride*sizeof(*pInBuff)+input_stride*sizeof(*pInBuff)+2*sizeof(*pInBuff));
   __vcop_pblock_init32(pblock, __offset+_PREG(20), (uchar *)pInBuff+input_stride*sizeof(*pInBuff)+3*input_stride*sizeof(*pInBuff)+2*sizeof(*pInBuff));
   __vcop_pblock_init32(pblock, __offset+_PREG(22), (uchar *)pGbuff+outputG_stride*sizeof(*pRbuff));
   __vcop_pblock_init32(pblock, __offset+_PREG(24), (uchar *)pGbuff+outputG_stride*sizeof(*pRbuff)+sizeof(*pRbuff));
   __vcop_pblock_init16(pblock, __offset+_PREG(26), 32);
   __vcop_pblock_init16(pblock, __offset+_PREG(27), (2*input_stride*sizeof(*pInBuff)) -((8u*2)*sizeof(*pInBuff))*((((((blkWidth + 2)/2) + (8u)-1) & ~((8u)-1))/(8u))-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(28), (2*outputG_stride*sizeof(*pRbuff)) -((8u*2)*sizeof(*pRbuff))*((((((blkWidth + 2)/2) + (8u)-1) & ~((8u)-1))/(8u))-1u));
   __vcop_pblock_init32(pblock, __offset+_PREG(30), -1);
   __vcop_pblock_init32(pblock, __offset+_PREG(32), -2);
   __offset += 32;

   /* Loop 2 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), ((blkHeight + 6)/2)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), ((((blkWidth + 6) + (8u)-1) & ~((8u)-1))/(8u))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(6), 16);
   __vcop_pblock_init16(pblock, __offset+_PREG(7), (2*input_stride*sizeof(*pInBuff)) -(8u*sizeof(*pInBuff))*(((((blkWidth + 6) + (8u)-1) & ~((8u)-1))/(8u))-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(8), (input_stride*sizeof(*pInBuff)) -(8u*sizeof(*pInBuff))*(((((blkWidth + 6) + (8u)-1) & ~((8u)-1))/(8u))-1u));
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)pInBuff+sizeof(*pInBuff));
   __vcop_pblock_init32(pblock, __offset+_PREG(12), (uchar *)pScratch);
   __offset += 12;

   /* Loop 3 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), ((blkHeight + 2)/2)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), (((((blkWidth + 2)/2) + (8u)-1) & ~((8u)-1))/(8u))-1u);
   __vcop_pblock_init32(pblock, __offset+_PREG(6), (uchar *)pScratch+input_stride*sizeof(*pInBuff)+2*sizeof(*pInBuff));
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)pInBuff+sizeof(*pInBuff)+2*input_stride*sizeof(*pInBuff)+4*sizeof(*pInBuff));
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)pInBuff+sizeof(*pInBuff)+4*input_stride*sizeof(*pInBuff)+2*sizeof(*pInBuff));
   __vcop_pblock_init32(pblock, __offset+_PREG(12), (uchar *)pInBuff+sizeof(*pInBuff)+input_stride*sizeof(*pInBuff)+2*sizeof(*pInBuff));
   __vcop_pblock_init32(pblock, __offset+_PREG(14), (uchar *)pInBuff+sizeof(*pInBuff)+3*input_stride*sizeof(*pInBuff)+2*sizeof(*pInBuff));
   __vcop_pblock_init32(pblock, __offset+_PREG(16), (uchar *)pGbuff+sizeof(*pRbuff));
   __vcop_pblock_init32(pblock, __offset+_PREG(18), (uchar *)pGbuff+2*sizeof(*pRbuff));
   __vcop_pblock_init16(pblock, __offset+_PREG(20), 32);
   __vcop_pblock_init16(pblock, __offset+_PREG(21), (2*input_stride*sizeof(*pInBuff)) -((8u*2)*sizeof(*pInBuff))*((((((blkWidth + 2)/2) + (8u)-1) & ~((8u)-1))/(8u))-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(22), (2*outputG_stride*sizeof(*pRbuff)) -((8u*2)*sizeof(*pRbuff))*((((((blkWidth + 2)/2) + (8u)-1) & ~((8u)-1))/(8u))-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(23), (input_stride*sizeof(*pInBuff)) -((8u*2)*sizeof(*pInBuff))*((((((blkWidth + 2)/2) + (8u)-1) & ~((8u)-1))/(8u))-1u));
   __vcop_pblock_init32(pblock, __offset+_PREG(24), (uchar *)pInBuff+sizeof(*pInBuff)+2*sizeof(*pInBuff));
   __vcop_pblock_init32(pblock, __offset+_PREG(26), (uchar *)pScratch+input_stride*sizeof(*pInBuff));
   __offset += 26;

   /* Loop 4 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), (blkHeight/2)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), ((((blkWidth/2) + (8u)-1) & ~((8u)-1))/(8u))-1u);
   __vcop_pblock_init32(pblock, __offset+_PREG(6), (uchar *)pInBuff+(5-1)*input_stride*sizeof(*pInBuff)+5*sizeof(*pInBuff));
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)pGbuff+sizeof(*pRbuff));
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)pGbuff+2*sizeof(*pRbuff));
   __vcop_pblock_init32(pblock, __offset+_PREG(12), (uchar *)pGbuff+(2-1)*outputG_stride*sizeof(*pRbuff)+sizeof(*pRbuff));
   __vcop_pblock_init32(pblock, __offset+_PREG(14), (uchar *)pGbuff+(3-1)*outputG_stride*sizeof(*pRbuff)+sizeof(*pRbuff));
   __vcop_pblock_init32(pblock, __offset+_PREG(16), (uchar *)pGbuff+(3-1)*outputG_stride*sizeof(*pRbuff)+2*sizeof(*pRbuff));
   __vcop_pblock_init32(pblock, __offset+_PREG(18), (uchar *)pBbuff);
   __vcop_pblock_init32(pblock, __offset+_PREG(20), (uchar *)pBbuff+outputRB_stride*sizeof(*pRbuff));
   __vcop_pblock_init32(pblock, __offset+_PREG(22), (uchar *)pBbuff+outputRB_stride*sizeof(*pRbuff)+sizeof(*pRbuff));
   __vcop_pblock_init32(pblock, __offset+_PREG(24), (uchar *)pScratch);
   __vcop_pblock_init32(pblock, __offset+_PREG(26), (uchar *)pScratch+sizeof(*pRbuff));
   __vcop_pblock_init16(pblock, __offset+_PREG(28), 32);
   __vcop_pblock_init16(pblock, __offset+_PREG(29), (2*input_stride*sizeof(*pInBuff)) -((8u*2)*sizeof(*pInBuff))*(((((blkWidth/2) + (8u)-1) & ~((8u)-1))/(8u))-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(30), (2*outputG_stride*sizeof(*pRbuff)) -((8u*2)*sizeof(*pRbuff))*(((((blkWidth/2) + (8u)-1) & ~((8u)-1))/(8u))-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(31), (2*outputRB_stride*sizeof(*pRbuff)) -((8u*2)*sizeof(*pRbuff))*(((((blkWidth/2) + (8u)-1) & ~((8u)-1))/(8u))-1u));
   __vcop_pblock_init32(pblock, __offset+_PREG(32), (uchar *)pInBuff+(3-1)*input_stride*sizeof(*pInBuff)+3*sizeof(*pInBuff));
   __vcop_pblock_init32(pblock, __offset+_PREG(34), (uchar *)pInBuff+(5-1)*input_stride*sizeof(*pInBuff)+3*sizeof(*pInBuff));
   __offset += 34;

   /* Loop 5 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), (blkHeight/2)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), ((((blkWidth/2) + (8u)-1) & ~((8u)-1))/(8u))-1u);
   __vcop_pblock_init32(pblock, __offset+_PREG(6), (uchar *)pInBuff+(5-1)*input_stride*sizeof(*pInBuff)+3*sizeof(*pInBuff));
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)pInBuff+(5-1)*input_stride*sizeof(*pInBuff)+5*sizeof(*pInBuff));
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)pScratch);
   __vcop_pblock_init32(pblock, __offset+_PREG(12), (uchar *)pGbuff+(2-1)*outputG_stride*sizeof(*pRbuff)+2*sizeof(*pRbuff));
   __vcop_pblock_init32(pblock, __offset+_PREG(14), (uchar *)pGbuff+(1-1)*outputG_stride*sizeof(*pRbuff)+sizeof(*pRbuff));
   __vcop_pblock_init32(pblock, __offset+_PREG(16), (uchar *)pGbuff+(1-1)*outputG_stride*sizeof(*pRbuff)+3*sizeof(*pRbuff));
   __vcop_pblock_init32(pblock, __offset+_PREG(18), (uchar *)pBbuff+sizeof(*pRbuff));
   __vcop_pblock_init16(pblock, __offset+_PREG(20), 32);
   __vcop_pblock_init16(pblock, __offset+_PREG(21), (2*input_stride*sizeof(*pInBuff)) -((8u*2)*sizeof(*pInBuff))*(((((blkWidth/2) + (8u)-1) & ~((8u)-1))/(8u))-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(22), (2*outputG_stride*sizeof(*pRbuff)) -((8u*2)*sizeof(*pRbuff))*(((((blkWidth/2) + (8u)-1) & ~((8u)-1))/(8u))-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(23), (2*outputRB_stride*sizeof(*pRbuff)) -((8u*2)*sizeof(*pRbuff))*(((((blkWidth/2) + (8u)-1) & ~((8u)-1))/(8u))-1u));
   __vcop_pblock_init32(pblock, __offset+_PREG(24), (uchar *)pInBuff+(3-1)*input_stride*sizeof(*pInBuff)+3*sizeof(*pInBuff));
   __vcop_pblock_init32(pblock, __offset+_PREG(26), (uchar *)pInBuff+(3-1)*input_stride*sizeof(*pInBuff)+5*sizeof(*pInBuff));
   __offset += 26;

   /* Loop 6 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), (blkHeight/2)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), ((((blkWidth/2) + (8u)-1) & ~((8u)-1))/(8u))-1u);
   __vcop_pblock_init32(pblock, __offset+_PREG(6), (uchar *)pInBuff+5*input_stride*sizeof(*pInBuff)+(-1+5)*sizeof(*pInBuff));
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)pGbuff+1*outputG_stride*sizeof(*pRbuff)+(-1+3)*sizeof(*pRbuff));
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)pGbuff+2*outputG_stride*sizeof(*pRbuff)+(-1+3)*sizeof(*pRbuff));
   __vcop_pblock_init32(pblock, __offset+_PREG(12), (uchar *)pGbuff+1*outputG_stride*sizeof(*pRbuff)+(-1+1)*sizeof(*pRbuff));
   __vcop_pblock_init32(pblock, __offset+_PREG(14), (uchar *)pGbuff+1*outputG_stride*sizeof(*pRbuff)+(-1+1+1)*sizeof(*pRbuff));
   __vcop_pblock_init32(pblock, __offset+_PREG(16), (uchar *)pGbuff+3*outputG_stride*sizeof(*pRbuff)+(-1+3)*sizeof(*pRbuff));
   __vcop_pblock_init32(pblock, __offset+_PREG(18), (uchar *)pRbuff+sizeof(*pRbuff));
   __vcop_pblock_init32(pblock, __offset+_PREG(20), (uchar *)pRbuff+outputRB_stride*sizeof(*pRbuff)+sizeof(*pRbuff));
   __vcop_pblock_init32(pblock, __offset+_PREG(22), (uchar *)pRbuff);
   __vcop_pblock_init32(pblock, __offset+_PREG(24), (uchar *)pScratch);
   __vcop_pblock_init32(pblock, __offset+_PREG(26), (uchar *)pScratch+sizeof(*pRbuff));
   __vcop_pblock_init16(pblock, __offset+_PREG(28), 32);
   __vcop_pblock_init16(pblock, __offset+_PREG(29), (2*input_stride*sizeof(*pInBuff)) -((8u*2)*sizeof(*pInBuff))*(((((blkWidth/2) + (8u)-1) & ~((8u)-1))/(8u))-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(30), (2*outputG_stride*sizeof(*pRbuff)) -((8u*2)*sizeof(*pRbuff))*(((((blkWidth/2) + (8u)-1) & ~((8u)-1))/(8u))-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(31), (2*outputRB_stride*sizeof(*pRbuff)) -((8u*2)*sizeof(*pRbuff))*(((((blkWidth/2) + (8u)-1) & ~((8u)-1))/(8u))-1u));
   __vcop_pblock_init32(pblock, __offset+_PREG(32), (uchar *)pInBuff+3*input_stride*sizeof(*pInBuff)+(-1+5)*sizeof(*pInBuff));
   __vcop_pblock_init32(pblock, __offset+_PREG(34), (uchar *)pInBuff+3*input_stride*sizeof(*pInBuff)+(-1+3)*sizeof(*pInBuff));
   __offset += 34;

   /* Loop 7 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), (blkHeight/2)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), ((((blkWidth/2) + (8u)-1) & ~((8u)-1))/(8u))-1u);
   __vcop_pblock_init32(pblock, __offset+_PREG(6), (uchar *)pInBuff+5*input_stride*sizeof(*pInBuff)+(-1+3)*sizeof(*pInBuff));
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)pInBuff+5*input_stride*sizeof(*pInBuff)+(-1+5)*sizeof(*pInBuff));
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)pGbuff+3*outputG_stride*sizeof(*pRbuff)+(-1+1)*sizeof(*pRbuff));
   __vcop_pblock_init32(pblock, __offset+_PREG(12), (uchar *)pGbuff+3*outputG_stride*sizeof(*pRbuff)+(-1+3)*sizeof(*pRbuff));
   __vcop_pblock_init32(pblock, __offset+_PREG(14), (uchar *)pGbuff+2*outputG_stride*sizeof(*pRbuff)+(-1+2)*sizeof(*pRbuff));
   __vcop_pblock_init32(pblock, __offset+_PREG(16), (uchar *)pScratch);
   __vcop_pblock_init32(pblock, __offset+_PREG(18), (uchar *)pRbuff+outputRB_stride*sizeof(*pRbuff));
   __vcop_pblock_init16(pblock, __offset+_PREG(20), 32);
   __vcop_pblock_init16(pblock, __offset+_PREG(21), (2*input_stride*sizeof(*pInBuff)) -((8u*2)*sizeof(*pInBuff))*(((((blkWidth/2) + (8u)-1) & ~((8u)-1))/(8u))-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(22), (2*outputG_stride*sizeof(*pRbuff)) -((8u*2)*sizeof(*pRbuff))*(((((blkWidth/2) + (8u)-1) & ~((8u)-1))/(8u))-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(23), (2*outputRB_stride*sizeof(*pRbuff)) -((8u*2)*sizeof(*pRbuff))*(((((blkWidth/2) + (8u)-1) & ~((8u)-1))/(8u))-1u));
   __vcop_pblock_init32(pblock, __offset+_PREG(24), (uchar *)pInBuff+3*input_stride*sizeof(*pInBuff)+(-1+3)*sizeof(*pInBuff));
   __vcop_pblock_init32(pblock, __offset+_PREG(26), (uchar *)pInBuff+3*input_stride*sizeof(*pInBuff)+(-1+5)*sizeof(*pInBuff));
   __offset += 26;

   return 190u;
}

void vcop_raw2rgb_GCCG_i16u_o16u_vloops(
   unsigned short pblock[])
{
   /* Kernel-wide Vector Registers */
   #pragma VCC_VREG("Vone", 16);
   #pragma VCC_VREG("Vthree", 17);
   #pragma VCC_VREG("Vtwo", 18);

   __vcop_param(&pblock[0]);

   /* VLOOP 1 Start */

   /* VLOOP Local Vector Registers */
   #pragma VCC_VREG("A1", 19);
   #pragma VCC_VREG("A3", 20);
   #pragma VCC_VREG("A5", 21);
   #pragma VCC_VREG("A7", 22);
   #pragma VCC_VREG("A9", 23);
   #pragma VCC_VREG("DH", 24);
   #pragma VCC_VREG("DHchroma", 25);
   #pragma VCC_VREG("DHchroma_div4", 26);
   #pragma VCC_VREG("DV", 27);
   #pragma VCC_VREG("DVchroma", 28);
   #pragma VCC_VREG("DVchroma_div4", 29);
   #pragma VCC_VREG("G2", 30);
   #pragma VCC_VREG("G2mG8", 31);
   #pragma VCC_VREG("G2pG8", 32);
   #pragma VCC_VREG("G2pG8_div2", 33);
   #pragma VCC_VREG("G4", 34);
   #pragma VCC_VREG("G4mG6", 35);
   #pragma VCC_VREG("G4pG6", 36);
   #pragma VCC_VREG("G4pG6_div2", 37);
   #pragma VCC_VREG("G5A", 38);
   #pragma VCC_VREG("G5A_tmp", 39);
   #pragma VCC_VREG("G5H", 40);
   #pragma VCC_VREG("G5V", 41);
   #pragma VCC_VREG("G6", 42);
   #pragma VCC_VREG("G6tmp", 43);
   #pragma VCC_VREG("G8", 44);
   #pragma VCC_VREG("abdiffDHchroma", 45);
   #pragma VCC_VREG("abdiffDVchroma", 46);
   #pragma VCC_VREG("abdiffG2mG8", 47);
   #pragma VCC_VREG("abdiffG4mG6", 48);
   #pragma VCC_VREG("flagEq", 49);
   #pragma VCC_VREG("flagH", 50);
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("inputAddr", "A0");
   #pragma EVE_REG("outputAddr", "A1");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("h", "I3");
   #pragma EVE_REG("w", "I4");
   

   __vcop_vloop(__vcop_compute(), 47u, 16u, 1u);
   __vcop_vinit(__vcop_sizeW(), __vcop_once(), _PREG(30), _VREG(16));
   __vcop_vinit(__vcop_sizeW(), __vcop_once(), _PREG(32), _VREG(18));
   __vcop_vinit(__vcop_sizeW(), __vcop_once(), _PREG(6), _VREG(17));
   __vcop_vagen(_AGEN(0), _PREG(26), _PREG(27), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(1), _PREG(26), _PREG(28), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeHU(), __vcop_ds2(), _PREG(8), _AGEN(0), _VREG(19), __vcop_alws());
   __vcop_vload(__vcop_sizeHU(), __vcop_dintrlv(), _PREG(10), _AGEN(0), _VPAIR(20,34), __vcop_alws());
   __vcop_vload(__vcop_sizeHU(), __vcop_dintrlv(), _PREG(12), _AGEN(0), _VPAIR(21,42), __vcop_alws());
   __vcop_vload(__vcop_sizeHU(), __vcop_ds2(), _PREG(14), _AGEN(0), _VREG(22), __vcop_alws());
   __vcop_vload(__vcop_sizeHU(), __vcop_ds2(), _PREG(16), _AGEN(0), _VREG(23), __vcop_alws());
   __vcop_vload(__vcop_sizeHU(), __vcop_ds2(), _PREG(18), _AGEN(0), _VREG(30), __vcop_alws());
   __vcop_vload(__vcop_sizeHU(), __vcop_ds2(), _PREG(20), _AGEN(0), _VREG(44), __vcop_alws());
   __vcop_vor(_VREG(42), _VREG(42), _VREG(43));
   __vcop_vmove(_VREG(34), _VREG(36));
   __vcop_vmove(_VREG(42), _VREG(35));
   __vcop_vaddsub(_VREG(36), _VREG(35));
   __vcop_vmove(_VREG(30), _VREG(32));
   __vcop_vmove(_VREG(44), _VREG(31));
   __vcop_vaddsub(_VREG(32), _VREG(31));
   __vcop_vabs(_VREG(35), _VREG(48));
   __vcop_vabs(_VREG(31), _VREG(47));
   __vcop_vsub(_VREG(21), _VREG(22), _VREG(25));
   __vcop_vsub(_VREG(21), _VREG(23), _VREG(28));
   __vcop_vadif(_VREG(21), _VREG(20), _VREG(25));
   __vcop_vadif(_VREG(21), _VREG(19), _VREG(28));
   __vcop_vabs(_VREG(25), _VREG(45));
   __vcop_vabs(_VREG(28), _VREG(46));
   __vcop_vadd(_VREG(45), _VREG(48), _VREG(24));
   __vcop_vadd(_VREG(46), _VREG(47), _VREG(27));
   __vcop_vshf(_VREG(36), _VREG(16), _VREG(37));
   __vcop_vshf(_VREG(32), _VREG(16), _VREG(33));
   __vcop_vshf(_VREG(25), _VREG(18), _VREG(26));
   __vcop_vshf(_VREG(28), _VREG(18), _VREG(29));
   __vcop_vadd(_VREG(37), _VREG(26), _VREG(40));
   __vcop_vadd(_VREG(33), _VREG(29), _VREG(41));
   __vcop_vadd(_VREG(32), _VREG(36), _VREG(38));
   __vcop_vadd(_VREG(25), _VREG(28), _VREG(39));
   __vcop_vshf(_VREG(38), _VREG(18), _VREG(38));
   __vcop_vshf(_VREG(39), _VREG(17), _VREG(39));
   __vcop_vadd(_VREG(38), _VREG(39), _VREG(38));
   __vcop_vcmplt(_VREG(24), _VREG(27), _VREG(50));
   __vcop_vcmpeq(_VREG(24), _VREG(27), _VREG(49));
   __vcop_vsel(_VREG(50), _VREG(40), _VREG(41));
   __vcop_vsel(_VREG(49), _VREG(38), _VREG(41));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeHU(), __vcop_skip(), __vcop_alws(), _VREG(41), _PREG(22), _AGEN(1), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeHU(), __vcop_skip(), __vcop_alws(), _VREG(43), _PREG(24), _AGEN(1), _PREG(0));
   __vcop_vloop_end(1u);

   /* VLOOP 2 Start */

   /* VLOOP Local Vector Registers */
   #pragma VCC_VREG("A1", 51);
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("inputAddr", "A0");
   #pragma EVE_REG("outputAddr", "A1");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("h", "I3");
   #pragma EVE_REG("w", "I4");
   

   __vcop_vloop(__vcop_compute(), 5u, 6u, 2u);
   __vcop_vagen(_AGEN(0), _PREG(6), _PREG(7), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(1), _PREG(6), _PREG(8), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeHU(), __vcop_npt(), _PREG(10), _AGEN(0), _VREG(51), __vcop_alws());
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeHU(), __vcop_npt(), __vcop_alws(), _VREG(51), _PREG(12), _AGEN(1), _PREG(0));
   __vcop_vloop_end(2u);

   /* VLOOP 3 Start */

   /* VLOOP Local Vector Registers */
   #pragma VCC_VREG("A1", 52);
   #pragma VCC_VREG("A3", 53);
   #pragma VCC_VREG("A5", 54);
   #pragma VCC_VREG("A7", 55);
   #pragma VCC_VREG("A9", 56);
   #pragma VCC_VREG("DH", 57);
   #pragma VCC_VREG("DHchroma", 58);
   #pragma VCC_VREG("DHchroma_div4", 59);
   #pragma VCC_VREG("DV", 60);
   #pragma VCC_VREG("DVchroma", 61);
   #pragma VCC_VREG("DVchroma_div4", 62);
   #pragma VCC_VREG("G2", 63);
   #pragma VCC_VREG("G2mG8", 64);
   #pragma VCC_VREG("G2pG8", 65);
   #pragma VCC_VREG("G2pG8_div2", 66);
   #pragma VCC_VREG("G4", 67);
   #pragma VCC_VREG("G4mG6", 68);
   #pragma VCC_VREG("G4pG6", 69);
   #pragma VCC_VREG("G4pG6_div2", 70);
   #pragma VCC_VREG("G5A", 71);
   #pragma VCC_VREG("G5A_tmp", 72);
   #pragma VCC_VREG("G5H", 73);
   #pragma VCC_VREG("G5V", 74);
   #pragma VCC_VREG("G6", 75);
   #pragma VCC_VREG("G6tmp", 76);
   #pragma VCC_VREG("G8", 77);
   #pragma VCC_VREG("abdiffDHchroma", 78);
   #pragma VCC_VREG("abdiffDVchroma", 79);
   #pragma VCC_VREG("abdiffG2mG8", 80);
   #pragma VCC_VREG("abdiffG4mG6", 81);
   #pragma VCC_VREG("flagEq", 82);
   #pragma VCC_VREG("flagH", 83);
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("inputAddr", "A0");
   #pragma EVE_REG("outputAddr", "A1");
   #pragma EVE_REG("scratchAddr", "A2");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("h", "I3");
   #pragma EVE_REG("w", "I4");
   

   __vcop_vloop(__vcop_compute(), 45u, 13u, 3u);
   __vcop_vagen(_AGEN(0), _PREG(20), _PREG(21), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(1), _PREG(20), _PREG(22), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(2), _PREG(20), _PREG(23), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeHU(), __vcop_ds2(), _PREG(24), _AGEN(0), _VREG(52), __vcop_alws());
   __vcop_vload(__vcop_sizeHU(), __vcop_dintrlv(), _PREG(26), _AGEN(2), _VPAIR(53,67), __vcop_alws());
   __vcop_vload(__vcop_sizeHU(), __vcop_dintrlv(), _PREG(6), _AGEN(2), _VPAIR(54,75), __vcop_alws());
   __vcop_vload(__vcop_sizeHU(), __vcop_ds2(), _PREG(8), _AGEN(0), _VREG(55), __vcop_alws());
   __vcop_vload(__vcop_sizeHU(), __vcop_ds2(), _PREG(10), _AGEN(0), _VREG(56), __vcop_alws());
   __vcop_vload(__vcop_sizeHU(), __vcop_ds2(), _PREG(12), _AGEN(0), _VREG(63), __vcop_alws());
   __vcop_vload(__vcop_sizeHU(), __vcop_ds2(), _PREG(14), _AGEN(0), _VREG(77), __vcop_alws());
   __vcop_vor(_VREG(75), _VREG(75), _VREG(76));
   __vcop_vmove(_VREG(67), _VREG(69));
   __vcop_vmove(_VREG(75), _VREG(68));
   __vcop_vaddsub(_VREG(69), _VREG(68));
   __vcop_vmove(_VREG(63), _VREG(65));
   __vcop_vmove(_VREG(77), _VREG(64));
   __vcop_vaddsub(_VREG(65), _VREG(64));
   __vcop_vabs(_VREG(68), _VREG(81));
   __vcop_vabs(_VREG(64), _VREG(80));
   __vcop_vsub(_VREG(54), _VREG(55), _VREG(58));
   __vcop_vsub(_VREG(54), _VREG(56), _VREG(61));
   __vcop_vadif(_VREG(54), _VREG(53), _VREG(58));
   __vcop_vadif(_VREG(54), _VREG(52), _VREG(61));
   __vcop_vabs(_VREG(58), _VREG(78));
   __vcop_vabs(_VREG(61), _VREG(79));
   __vcop_vadd(_VREG(78), _VREG(81), _VREG(57));
   __vcop_vadd(_VREG(79), _VREG(80), _VREG(60));
   __vcop_vshf(_VREG(69), _VREG(16), _VREG(70));
   __vcop_vshf(_VREG(65), _VREG(16), _VREG(66));
   __vcop_vshf(_VREG(58), _VREG(18), _VREG(59));
   __vcop_vshf(_VREG(61), _VREG(18), _VREG(62));
   __vcop_vadd(_VREG(70), _VREG(59), _VREG(73));
   __vcop_vadd(_VREG(66), _VREG(62), _VREG(74));
   __vcop_vadd(_VREG(65), _VREG(69), _VREG(71));
   __vcop_vadd(_VREG(58), _VREG(61), _VREG(72));
   __vcop_vshf(_VREG(71), _VREG(18), _VREG(71));
   __vcop_vshf(_VREG(72), _VREG(17), _VREG(72));
   __vcop_vadd(_VREG(71), _VREG(72), _VREG(71));
   __vcop_vcmplt(_VREG(57), _VREG(60), _VREG(83));
   __vcop_vcmpeq(_VREG(57), _VREG(60), _VREG(82));
   __vcop_vsel(_VREG(83), _VREG(73), _VREG(74));
   __vcop_vsel(_VREG(82), _VREG(71), _VREG(74));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeHU(), __vcop_skip(), __vcop_alws(), _VREG(74), _PREG(16), _AGEN(1), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeHU(), __vcop_skip(), __vcop_alws(), _VREG(76), _PREG(18), _AGEN(1), _PREG(0));
   __vcop_vloop_end(3u);

   /* VLOOP 4 Start */

   /* VLOOP Local Vector Registers */
   #pragma VCC_VREG("A1", 84);
   #pragma VCC_VREG("A4", 85);
   #pragma VCC_VREG("A4_tmp", 86);
   #pragma VCC_VREG("A7", 87);
   #pragma VCC_VREG("A8", 88);
   #pragma VCC_VREG("A8_tmp", 89);
   #pragma VCC_VREG("A9", 90);
   #pragma VCC_VREG("G1", 91);
   #pragma VCC_VREG("G2", 92);
   #pragma VCC_VREG("G4", 93);
   #pragma VCC_VREG("G7", 94);
   #pragma VCC_VREG("G8", 95);
   #pragma VCC_VREG("G9", 96);
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("inputAddr", "A0");
   #pragma EVE_REG("inputGaddr", "A1");
   #pragma EVE_REG("outputAddr", "A2");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("h", "I3");
   #pragma EVE_REG("w", "I4");
   

   __vcop_vloop(__vcop_compute(), 29u, 17u, 4u);
   __vcop_vagen(_AGEN(0), _PREG(28), _PREG(29), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(1), _PREG(28), _PREG(30), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(2), _PREG(28), _PREG(31), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeHU(), __vcop_ds2(), _PREG(32), _AGEN(0), _VREG(84), __vcop_alws());
   __vcop_vload(__vcop_sizeHU(), __vcop_ds2(), _PREG(34), _AGEN(0), _VREG(87), __vcop_alws());
   __vcop_vload(__vcop_sizeHU(), __vcop_ds2(), _PREG(6), _AGEN(0), _VREG(90), __vcop_alws());
   __vcop_vload(__vcop_sizeHU(), __vcop_ds2(), _PREG(8), _AGEN(1), _VREG(91), __vcop_alws());
   __vcop_vload(__vcop_sizeHU(), __vcop_ds2(), _PREG(10), _AGEN(1), _VREG(92), __vcop_alws());
   __vcop_vload(__vcop_sizeHU(), __vcop_ds2(), _PREG(12), _AGEN(1), _VREG(93), __vcop_alws());
   __vcop_vload(__vcop_sizeHU(), __vcop_ds2(), _PREG(14), _AGEN(1), _VREG(94), __vcop_alws());
   __vcop_vload(__vcop_sizeHU(), __vcop_dintrlv(), _PREG(16), _AGEN(1), _VPAIR(95,96), __vcop_alws());
   __vcop_vadd(_VREG(84), _VREG(87), _VREG(85));
   __vcop_vadd(_VREG(90), _VREG(87), _VREG(88));
   __vcop_vshf(_VREG(85), _VREG(16), _VREG(85));
   __vcop_vshf(_VREG(88), _VREG(16), _VREG(88));
   __vcop_vsub(_VREG(93), _VREG(94), _VREG(86));
   __vcop_vsub(_VREG(95), _VREG(94), _VREG(89));
   __vcop_vadif(_VREG(93), _VREG(91), _VREG(86));
   __vcop_vadif(_VREG(95), _VREG(96), _VREG(89));
   __vcop_vshf(_VREG(86), _VREG(16), _VREG(86));
   __vcop_vshf(_VREG(89), _VREG(16), _VREG(89));
   __vcop_vadd(_VREG(85), _VREG(86), _VREG(85));
   __vcop_vadd(_VREG(88), _VREG(89), _VREG(88));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeHU(), __vcop_skip(), __vcop_alws(), _VREG(85), _PREG(18), _AGEN(2), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeHU(), __vcop_skip(), __vcop_alws(), _VREG(87), _PREG(20), _AGEN(2), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeHU(), __vcop_skip(), __vcop_alws(), _VREG(88), _PREG(22), _AGEN(2), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeHU(), __vcop_skip(), __vcop_alws(), _VREG(94), _PREG(24), _AGEN(2), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeHU(), __vcop_skip(), __vcop_alws(), _VREG(96), _PREG(26), _AGEN(2), _PREG(0));
   __vcop_vloop_end(4u);

   /* VLOOP 5 Start */

   /* VLOOP Local Vector Registers */
   #pragma VCC_VREG("A1", 97);
   #pragma VCC_VREG("A1mA9", 98);
   #pragma VCC_VREG("A1pA9", 99);
   #pragma VCC_VREG("A1pA9_div2", 100);
   #pragma VCC_VREG("A3", 101);
   #pragma VCC_VREG("A3mA7", 102);
   #pragma VCC_VREG("A3pA7", 103);
   #pragma VCC_VREG("A3pA7_div2", 104);
   #pragma VCC_VREG("A5A", 105);
   #pragma VCC_VREG("A5A_tmp", 106);
   #pragma VCC_VREG("A5N", 107);
   #pragma VCC_VREG("A5P", 108);
   #pragma VCC_VREG("A7", 109);
   #pragma VCC_VREG("A9", 110);
   #pragma VCC_VREG("DN", 111);
   #pragma VCC_VREG("DNgreen", 112);
   #pragma VCC_VREG("DNgreen_div2", 113);
   #pragma VCC_VREG("DP", 114);
   #pragma VCC_VREG("DPgreen", 115);
   #pragma VCC_VREG("DPgreen_div2", 116);
   #pragma VCC_VREG("G1", 117);
   #pragma VCC_VREG("G3", 118);
   #pragma VCC_VREG("G4", 119);
   #pragma VCC_VREG("G5", 120);
   #pragma VCC_VREG("G7", 121);
   #pragma VCC_VREG("G9", 122);
   #pragma VCC_VREG("abdiffA1mA9", 123);
   #pragma VCC_VREG("abdiffA3mA7", 124);
   #pragma VCC_VREG("abdiffDNgreen", 125);
   #pragma VCC_VREG("abdiffDPgreen", 126);
   #pragma VCC_VREG("flagEq", 127);
   #pragma VCC_VREG("flagN", 128);
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("inputAddr", "A0");
   #pragma EVE_REG("inputGaddr", "A1");
   #pragma EVE_REG("outputAddr", "A2");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("h", "I3");
   #pragma EVE_REG("w", "I4");
   

   __vcop_vloop(__vcop_compute(), 44u, 13u, 5u);
   __vcop_vagen(_AGEN(0), _PREG(20), _PREG(21), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(1), _PREG(20), _PREG(22), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(2), _PREG(20), _PREG(23), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeHU(), __vcop_ds2(), _PREG(24), _AGEN(0), _VREG(97), __vcop_alws());
   __vcop_vload(__vcop_sizeHU(), __vcop_ds2(), _PREG(26), _AGEN(0), _VREG(101), __vcop_alws());
   __vcop_vload(__vcop_sizeHU(), __vcop_ds2(), _PREG(6), _AGEN(0), _VREG(109), __vcop_alws());
   __vcop_vload(__vcop_sizeHU(), __vcop_ds2(), _PREG(8), _AGEN(0), _VREG(110), __vcop_alws());
   __vcop_vload(__vcop_sizeHU(), __vcop_dintrlv(), _PREG(10), _AGEN(2), _VPAIR(121,122), __vcop_alws());
   __vcop_vload(__vcop_sizeHU(), __vcop_ds2(), _PREG(12), _AGEN(1), _VREG(120), __vcop_alws());
   __vcop_vload(__vcop_sizeHU(), __vcop_ds2(), _PREG(14), _AGEN(1), _VREG(117), __vcop_alws());
   __vcop_vload(__vcop_sizeHU(), __vcop_ds2(), _PREG(16), _AGEN(1), _VREG(118), __vcop_alws());
   __vcop_vmove(_VREG(97), _VREG(99));
   __vcop_vmove(_VREG(110), _VREG(98));
   __vcop_vaddsub(_VREG(99), _VREG(98));
   __vcop_vmove(_VREG(101), _VREG(103));
   __vcop_vmove(_VREG(109), _VREG(102));
   __vcop_vaddsub(_VREG(103), _VREG(102));
   __vcop_vabs(_VREG(98), _VREG(123));
   __vcop_vabs(_VREG(102), _VREG(124));
   __vcop_vsub(_VREG(120), _VREG(117), _VREG(112));
   __vcop_vsub(_VREG(120), _VREG(118), _VREG(115));
   __vcop_vadif(_VREG(120), _VREG(122), _VREG(112));
   __vcop_vadif(_VREG(120), _VREG(121), _VREG(115));
   __vcop_vabs(_VREG(112), _VREG(125));
   __vcop_vabs(_VREG(115), _VREG(126));
   __vcop_vadd(_VREG(125), _VREG(123), _VREG(111));
   __vcop_vadd(_VREG(126), _VREG(124), _VREG(114));
   __vcop_vshf(_VREG(99), _VREG(16), _VREG(100));
   __vcop_vshf(_VREG(103), _VREG(16), _VREG(104));
   __vcop_vshf(_VREG(112), _VREG(16), _VREG(113));
   __vcop_vshf(_VREG(115), _VREG(16), _VREG(116));
   __vcop_vadd(_VREG(100), _VREG(113), _VREG(107));
   __vcop_vadd(_VREG(104), _VREG(116), _VREG(108));
   __vcop_vadd(_VREG(99), _VREG(103), _VREG(105));
   __vcop_vadd(_VREG(112), _VREG(115), _VREG(106));
   __vcop_vshf(_VREG(105), _VREG(18), _VREG(105));
   __vcop_vshf(_VREG(106), _VREG(18), _VREG(106));
   __vcop_vadd(_VREG(105), _VREG(106), _VREG(105));
   __vcop_vcmplt(_VREG(111), _VREG(114), _VREG(128));
   __vcop_vcmpeq(_VREG(111), _VREG(114), _VREG(127));
   __vcop_vsel(_VREG(128), _VREG(107), _VREG(108));
   __vcop_vsel(_VREG(127), _VREG(105), _VREG(108));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeHU(), __vcop_skip(), __vcop_alws(), _VREG(108), _PREG(18), _AGEN(2), _PREG(0));
   __vcop_vloop_end(5u);

   /* VLOOP 6 Start */

   /* VLOOP Local Vector Registers */
   #pragma VCC_VREG("A1", 129);
   #pragma VCC_VREG("A2", 130);
   #pragma VCC_VREG("A2_tmp", 131);
   #pragma VCC_VREG("A3", 132);
   #pragma VCC_VREG("A6", 133);
   #pragma VCC_VREG("A6_tmp", 134);
   #pragma VCC_VREG("A7", 135);
   #pragma VCC_VREG("A9", 136);
   #pragma VCC_VREG("G1", 137);
   #pragma VCC_VREG("G2", 138);
   #pragma VCC_VREG("G3", 139);
   #pragma VCC_VREG("G6", 140);
   #pragma VCC_VREG("G9", 141);
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("inputAddr", "A0");
   #pragma EVE_REG("inputGaddr", "A1");
   #pragma EVE_REG("outputAddr", "A2");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("h", "I3");
   #pragma EVE_REG("w", "I4");
   

   __vcop_vloop(__vcop_compute(), 29u, 17u, 6u);
   __vcop_vagen(_AGEN(0), _PREG(28), _PREG(29), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(1), _PREG(28), _PREG(30), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(2), _PREG(28), _PREG(31), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeHU(), __vcop_ds2(), _PREG(32), _AGEN(0), _VREG(132), __vcop_alws());
   __vcop_vload(__vcop_sizeHU(), __vcop_ds2(), _PREG(34), _AGEN(0), _VREG(129), __vcop_alws());
   __vcop_vload(__vcop_sizeHU(), __vcop_ds2(), _PREG(6), _AGEN(0), _VREG(136), __vcop_alws());
   __vcop_vload(__vcop_sizeHU(), __vcop_ds2(), _PREG(8), _AGEN(1), _VREG(139), __vcop_alws());
   __vcop_vload(__vcop_sizeHU(), __vcop_ds2(), _PREG(10), _AGEN(1), _VREG(140), __vcop_alws());
   __vcop_vload(__vcop_sizeHU(), __vcop_ds2(), _PREG(12), _AGEN(1), _VREG(137), __vcop_alws());
   __vcop_vload(__vcop_sizeHU(), __vcop_ds2(), _PREG(14), _AGEN(1), _VREG(138), __vcop_alws());
   __vcop_vload(__vcop_sizeHU(), __vcop_ds2(), _PREG(16), _AGEN(1), _VREG(141), __vcop_alws());
   __vcop_vadd(_VREG(132), _VREG(136), _VREG(133));
   __vcop_vadd(_VREG(132), _VREG(129), _VREG(130));
   __vcop_vshf(_VREG(133), _VREG(16), _VREG(133));
   __vcop_vshf(_VREG(130), _VREG(16), _VREG(130));
   __vcop_vsub(_VREG(140), _VREG(141), _VREG(134));
   __vcop_vsub(_VREG(138), _VREG(137), _VREG(131));
   __vcop_vadif(_VREG(140), _VREG(139), _VREG(134));
   __vcop_vadif(_VREG(138), _VREG(139), _VREG(131));
   __vcop_vshf(_VREG(134), _VREG(16), _VREG(134));
   __vcop_vshf(_VREG(131), _VREG(16), _VREG(131));
   __vcop_vadd(_VREG(133), _VREG(134), _VREG(133));
   __vcop_vadd(_VREG(130), _VREG(131), _VREG(130));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeHU(), __vcop_skip(), __vcop_alws(), _VREG(132), _PREG(18), _AGEN(2), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeHU(), __vcop_skip(), __vcop_alws(), _VREG(133), _PREG(20), _AGEN(2), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeHU(), __vcop_skip(), __vcop_alws(), _VREG(130), _PREG(22), _AGEN(2), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeHU(), __vcop_skip(), __vcop_alws(), _VREG(137), _PREG(24), _AGEN(2), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeHU(), __vcop_skip(), __vcop_alws(), _VREG(139), _PREG(26), _AGEN(2), _PREG(0));
   __vcop_vloop_end(6u);

   /* VLOOP 7 Start */

   /* VLOOP Local Vector Registers */
   #pragma VCC_VREG("A1", 142);
   #pragma VCC_VREG("A1mA9", 143);
   #pragma VCC_VREG("A1pA9", 144);
   #pragma VCC_VREG("A1pA9_div2", 145);
   #pragma VCC_VREG("A3", 146);
   #pragma VCC_VREG("A3mA7", 147);
   #pragma VCC_VREG("A3pA7", 148);
   #pragma VCC_VREG("A3pA7_div2", 149);
   #pragma VCC_VREG("A5A", 150);
   #pragma VCC_VREG("A5A_tmp", 151);
   #pragma VCC_VREG("A5N", 152);
   #pragma VCC_VREG("A5P", 153);
   #pragma VCC_VREG("A7", 154);
   #pragma VCC_VREG("A9", 155);
   #pragma VCC_VREG("DN", 156);
   #pragma VCC_VREG("DNgreen", 157);
   #pragma VCC_VREG("DNgreen_div2", 158);
   #pragma VCC_VREG("DP", 159);
   #pragma VCC_VREG("DPgreen", 160);
   #pragma VCC_VREG("DPgreen_div2", 161);
   #pragma VCC_VREG("G1", 162);
   #pragma VCC_VREG("G3", 163);
   #pragma VCC_VREG("G5", 164);
   #pragma VCC_VREG("G7", 165);
   #pragma VCC_VREG("G9", 166);
   #pragma VCC_VREG("abdiffA1mA9", 167);
   #pragma VCC_VREG("abdiffA3mA7", 168);
   #pragma VCC_VREG("abdiffDNgreen", 169);
   #pragma VCC_VREG("abdiffDPgreen", 170);
   #pragma VCC_VREG("flagEq", 171);
   #pragma VCC_VREG("flagN", 172);
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("inputAddr", "A0");
   #pragma EVE_REG("inputGaddr", "A1");
   #pragma EVE_REG("outputAddr", "A2");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("h", "I3");
   #pragma EVE_REG("w", "I4");
   

   __vcop_vloop(__vcop_compute(), 44u, 13u, 7u);
   __vcop_vagen(_AGEN(0), _PREG(20), _PREG(21), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(1), _PREG(20), _PREG(22), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(2), _PREG(20), _PREG(23), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeHU(), __vcop_ds2(), _PREG(24), _AGEN(0), _VREG(142), __vcop_alws());
   __vcop_vload(__vcop_sizeHU(), __vcop_ds2(), _PREG(26), _AGEN(0), _VREG(146), __vcop_alws());
   __vcop_vload(__vcop_sizeHU(), __vcop_ds2(), _PREG(6), _AGEN(0), _VREG(154), __vcop_alws());
   __vcop_vload(__vcop_sizeHU(), __vcop_ds2(), _PREG(8), _AGEN(0), _VREG(155), __vcop_alws());
   __vcop_vload(__vcop_sizeHU(), __vcop_ds2(), _PREG(10), _AGEN(1), _VREG(165), __vcop_alws());
   __vcop_vload(__vcop_sizeHU(), __vcop_ds2(), _PREG(12), _AGEN(1), _VREG(166), __vcop_alws());
   __vcop_vload(__vcop_sizeHU(), __vcop_ds2(), _PREG(14), _AGEN(1), _VREG(164), __vcop_alws());
   __vcop_vload(__vcop_sizeHU(), __vcop_dintrlv(), _PREG(16), _AGEN(2), _VPAIR(162,163), __vcop_alws());
   __vcop_vmove(_VREG(142), _VREG(144));
   __vcop_vmove(_VREG(155), _VREG(143));
   __vcop_vaddsub(_VREG(144), _VREG(143));
   __vcop_vmove(_VREG(146), _VREG(148));
   __vcop_vmove(_VREG(154), _VREG(147));
   __vcop_vaddsub(_VREG(148), _VREG(147));
   __vcop_vabs(_VREG(143), _VREG(167));
   __vcop_vabs(_VREG(147), _VREG(168));
   __vcop_vsub(_VREG(164), _VREG(162), _VREG(157));
   __vcop_vsub(_VREG(164), _VREG(163), _VREG(160));
   __vcop_vadif(_VREG(164), _VREG(166), _VREG(157));
   __vcop_vadif(_VREG(164), _VREG(165), _VREG(160));
   __vcop_vabs(_VREG(157), _VREG(169));
   __vcop_vabs(_VREG(160), _VREG(170));
   __vcop_vadd(_VREG(169), _VREG(167), _VREG(156));
   __vcop_vadd(_VREG(170), _VREG(168), _VREG(159));
   __vcop_vshf(_VREG(144), _VREG(16), _VREG(145));
   __vcop_vshf(_VREG(148), _VREG(16), _VREG(149));
   __vcop_vshf(_VREG(157), _VREG(16), _VREG(158));
   __vcop_vshf(_VREG(160), _VREG(16), _VREG(161));
   __vcop_vadd(_VREG(145), _VREG(158), _VREG(152));
   __vcop_vadd(_VREG(149), _VREG(161), _VREG(153));
   __vcop_vadd(_VREG(144), _VREG(148), _VREG(150));
   __vcop_vadd(_VREG(157), _VREG(160), _VREG(151));
   __vcop_vshf(_VREG(150), _VREG(18), _VREG(150));
   __vcop_vshf(_VREG(151), _VREG(18), _VREG(151));
   __vcop_vadd(_VREG(150), _VREG(151), _VREG(150));
   __vcop_vcmplt(_VREG(156), _VREG(159), _VREG(172));
   __vcop_vcmpeq(_VREG(156), _VREG(159), _VREG(171));
   __vcop_vsel(_VREG(172), _VREG(152), _VREG(153));
   __vcop_vsel(_VREG(171), _VREG(150), _VREG(153));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeHU(), __vcop_skip(), __vcop_alws(), _VREG(153), _PREG(18), _AGEN(2), _PREG(0));
   __vcop_vloop_end(7u);

}

void vcop_raw2rgb_GCCG_i16u_o16u(
   __vptr_uint16 pInBuff,
   __vptr_uint16 pRbuff,
   __vptr_uint16 pGbuff,
   __vptr_uint16 pBbuff,
   __vptr_uint16 pScratch,
   unsigned short blkWidth,
   unsigned short blkHeight,
   unsigned short input_stride,
   unsigned short outputG_stride,
   unsigned short outputRB_stride)
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_raw2rgb_GCCG_i16u_o16u_init(pInBuff, pRbuff, pGbuff, pBbuff, pScratch, blkWidth, blkHeight, input_stride, outputG_stride, outputRB_stride, __pblock_vcop_raw2rgb_GCCG_i16u_o16u);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_raw2rgb_GCCG_i16u_o16u_vloops(__pblock_vcop_raw2rgb_GCCG_i16u_o16u);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

void vcop_raw2rgb_GCCG_i16u_o16u_custom(
   __vptr_uint16 pInBuff,
   __vptr_uint16 pRbuff,
   __vptr_uint16 pGbuff,
   __vptr_uint16 pBbuff,
   __vptr_uint16 pScratch,
   unsigned short blkWidth,
   unsigned short blkHeight,
   unsigned short input_stride,
   unsigned short outputG_stride,
   unsigned short outputRB_stride,
   unsigned short pblock[])
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_raw2rgb_GCCG_i16u_o16u_init(pInBuff, pRbuff, pGbuff, pBbuff, pScratch, blkWidth, blkHeight, input_stride, outputG_stride, outputRB_stride, pblock);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_raw2rgb_GCCG_i16u_o16u_vloops(pblock);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

