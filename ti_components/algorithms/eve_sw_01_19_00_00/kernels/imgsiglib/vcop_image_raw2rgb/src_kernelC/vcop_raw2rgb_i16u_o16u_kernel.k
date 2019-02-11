/*==========================================================================*/
/*      Copyright (C) 2017 Texas Instruments Incorporated.                  */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/*-----------------------------------------------------------------*/
/* NAME : vcop_cfaInterp_i16u_o16u                                    */
/*                                                                 */
/*                                                                 */
/* DESCRIPTION:                                                    */
/* The "vcop_cfaInterp_i16u_o16u" code accepts 16-bit data            */
/* in the form of 16-bit Bayer Pattern, and writes out             */
/* the result as separate R, G and B planes. The output is         */
/* interpolated data to match the input width and height.          */
/* Interpolation is carried out by implementing the Adams-Hamilton  */
/* algorithm described in US patent 5,629,734                      */
/*                                                                 */
/*                                                                 */
/* The Bayer pattern is as follows:                                */
/* -------------------------------                                 */
/* B G B G B G B G                                                 */
/* G R G R G R G R                                                 */
/* B G B G B G B G                                                 */
/* G R G R G R G R                                                 */
/* B G B G B G B G                                                 */
/* G R G R G R G R                                                 */
/*                                                                 */
/*                                                                 */
/* PERFORMANCE                                                     */
/*                                                                 */
/* (2/16 * 1/3) + 13/16 = 0.85 cyc/pix                             */
/*                                                                 */
/*=================================================================*/
/* Texas Instruments Incorporated 2017.                            */
/*-----------------------------------------------------------------*/
#if VCOP_HOST_EMULATION
#include <vcop.h>
#endif

#define VCOP_2SIMD_WIDTH   (VCOP_SIMD_WIDTH * 2)

#define ALIGN_SIMD(a)   (((a) + VCOP_SIMD_WIDTH-1) & ~(VCOP_SIMD_WIDTH-1))
#define ALIGN_SIMD2(a)   (((a) + (2*VCOP_SIMD_WIDTH)-1) & ~(2*VCOP_SIMD_WIDTH-1))

#define ELEMSZ_IN     sizeof(*pInBuff)
#define ELEMSZ_OUT    sizeof(*pRbuff)

/* * * * * * * * * * * * * * * * * * * * */
void vcop_raw2rgb_CGGC_i16u_o16u
(
        __vptr_uint16 pInBuff,
        __vptr_uint16 pRbuff,
        __vptr_uint16 pGbuff,
        __vptr_uint16 pBbuff,
        __vptr_uint16 pScratch,
        unsigned short blkWidth,
        unsigned short blkHeight,
        unsigned short input_stride,
        unsigned short outputG_stride,
        unsigned short outputRB_stride
)
{
    /*

    Input:

	    |
	R G R G R G
	G B G B G B
	R G R G R G <---
	G B G B G B
	R G R G R G

    https://www.google.com/patents/US5629734
        
     Green plane interpolation 

    Input when bayer pattern is AGGC:

             |
	A00 G01 A02 G03 A04 G05 A06 G07 A08
	G10 C11 G12 C13 G14 C15 G16 C17 G18
	A20 G21 A22 G23 A24 G25 A26 G27 A28<---
	G30 C31 G32 C33 G34 C35 G36 C37 G38
	A40 G41 A42 G43 A44 G45 A46 G47 A48 
	G50 C51 G52 C53 G54 C55 G56 C57 G58
	A60 G61 A62 G63 A64 G65 A66 G67 A68
	G70 C71 G72 C73 G74 C75 G76 C77 G78
	A80 G81 A82 G83 A84 G85 A86 G87 A88

	Output when bayer pattern is AGGC::

	G22 G23 G24 G25 G26 G27
	N/A G33 G34 G35 G36 G37
	G42 G43 G44 G45 G46 G47
	N/A G53 G54 G55 G56 G57
	G62 G63 G64 G65 G66 G67


    Input when bayer pattern is GACG:

             |
    G00 A01 G02 A03 G04 A05 G06 A07 G08
    C10 G11 C12 G13 C14 G15 C16 G17 C18
    G20 A21 G22 A23 G24 A25 G26 A27 G28<--
    C30 G31 C32 G33 C34 G35 C36 G37 C38
    G40 A41 G42 A43 G44 A45 G46 A47 G48
    C50 G51 C52 G53 C54 G55 C56 G57 C58
    G60 A61 G62 A63 G64 A65 G66 A67 G68
    C70 G71 C72 G73 C74 G75 C76 G77 C78
    G80 A81 G82 A83 G84 A85 G86 A87 G88

	Output when bayer pattern is GACG::

	N/A G23 G24 G25 G26 G27
	G32 G33 G34 G35 G36 G37
	N/A G43 G44 G45 G46 G47
	G52 G53 G54 G55 G56 G57
	N/A G63 G64 G65 G66 G67

	    
	Algorithm:

	For AGGC pattern, let's remap the naming convention

	               A02
	               G12
	       A20 G21 A22 G23 A24
	               G32
	               A42

	to:
	               A1
	               G2
	         A3 G4 A5 G6 A7 
	               G8
	               A9

    to match the convention used in the patent https://www.google.com/patents/US5629734

            Output:
            G5 G6
          
     Algorithm:
     
     DH=|-A3+2A5-A7|+|G4-G6|
     DV=|-A1+2A5-A9|+|G2-G8|
     G5H=(G4+G6)/2+(-A3+2A5-A7)/4
     G5V=(G2+G8)/2+(-A1+2A5-A9)/4
     G5A=(G2+G4+G6+G8)/4+(-A1-A3+4A5-A7-A9)/8
     
     IF (DH<DV)
         THEN G5=G5H
         ELSEIF DV < DH
                   THEN G5=G5V
                   ELSE G5=G5A
                   
     1) Compute G4mG6=(G4-G6) & G4pG6=(G4+G6) using (Vsrc1, Vsrc2).addsub(); // 1/16 cyc/pixel
     2) Compute G2mG8=(G2-G8) & G2pG8=(G8+G8) using (Vsrc1, Vsrc2).addsub(); // 1/16 cyc/pixel
     3) Compute abdiffG4mG6=|G4-G6| // 1/16 cyc/pixel
     4) Compute abdiffG2mG8=|G2-G8| // 1/16 cyc/pixel
     5) Compute DHchroma=-A3+2A5-A7= (A5<<1)-A3-A7)= 1/16 + 1/16 + 1/16= 3/16
     6) Compute DVchroma=-A1+2A5-A9= (A5<<1)-A1-A9)= 0 + 1/16 + 1/16= 2/16 // note that (A5<<1) is already computed in previously step
     7) Compute abdiffDHchroma= |-A3+2A5-A7| // 1/16 cyc/pixel
     8) Compute abdiffDVchroma= |-A1+2A5-A9| // 1/16 cyc/pixel 
     9) Compute DH= abdiffDHchroma +  abdiffG4mG6 // 1/16 cyc/pixel
     10) Compute DV= abdiffDVchroma +  abdiffG2mG8 // 1/16 cyc/pixel
     11) Compute G5H= G4pG6>>1 + DHchroma>>2 // 1/16 + 1/16 + 1/16= 3/16
     12) Compute G5V= G2pG8>>1 + DVchroma>>2 // 1/16 + 1/16 + 1/16= 3/16
     13) Compute G5A= (G2pG8+G4pG6)>>2 + (DHchroma + DVchroma)>>3 // 1/16 + 1/16 + 1/16 + 1/16= 4/16
     14) Compute flagH= (DH<DV) // 1/16
     15) Compute flagEq= (DV=DH) // 1/16
     16) Compute G5=G5H using G5= select(flagH, G5H, G5V) // 1/16
     17) Compute G5=G5A using G5= select(flagEq, G5A, G5) // 1/16
	 
	 Performance: 2.25 cyc/pixel
 
    Chroma plane interpolation 
    Input:

    A1 G2 A3
	G4 C5 G6
	A7 G8 A9
          
     Algorithm:
     
     DN=|-G1+2G5-G9|+|A1-A9|
     DP=|-G3+2G5-G7|+|A3-A7|
     A5N=(A1+A9)/2+(-G1+2G5-G9)/2
     A5P=(A3+A7)/2+(-G3+2G5-G7)/2
     A5A=(A1+A3+A7+A9)/4+(-G1-G3+4G5-G7-G9)/4
     
     IF (DN<DP)
         THEN A5=A5N
         ELSEIF DP < DN
                   THEN A5=A5P
                   ELSE A5=A5A
                   
     1) Compute A1mA9=(A1-A9) & A1pA9=(A1+A9) using (Vsrc1, Vsrc2).addsub(); // 1/16 cyc/pixel
     2) Compute A3mA7=(A3-A7) & A3pA7=(A3+A7) using (Vsrc1, Vsrc2).addsub(); // 1/16 cyc/pixel
     3) Compute abdiffA1mA9=|A1-A9| // 1/16 cyc/pixel
     4) Compute abdiffA3mA7=|A3-A7| // 1/16 cyc/pixel
     5) Compute DNluma=-G1+2G5-G9= (G5<<1)-G1-G9)= 1/16 + 1/16 + 1/16= 3/16
     6) Compute DPluma=-G3+2G5-G7= (G5<<1)-G3-G7)= 0 + 1/16 + 1/16= 2/16 // note that (G5<<1) is already computed in previously step
     7) Compute abdiffDNluma= |-G1+2G5-G9| // 1/16 cyc/pixel
     8) Compute abdiffDPluma= |-G3+2G5-G7| // 1/16 cyc/pixel 
     9) Compute DN= abdiffDNluma +  abdiffA1mA9 // 1/16 cyc/pixel
     10) Compute DP= abdiffDPluma +  abdiffA3mA7 // 1/16 cyc/pixel
     11) Compute A5N= A1pA9>>1 + DNluma>>1 // 1/16 + 1/16 + 1/16= 3/16
     12) Compute A5P= A3pA7>>1 + DPluma>>2 // 1/16 + 1/16 + 1/16= 3/16
     13) Compute A5A= (A3pA7+A1pA9)>>2 + (abdiffDNluma + abdiffDPluma)>>2 // 1/16 + 1/16 + 1/16 + 1/16= 4/16
     14) Compute flagN= (DN<DP) A/ 1/16
     15) Compute flagEq= (DN=DP) // 1/16
     16) Compute A5=A5N using A5= select(flagN, A5N, A5P) // 1/16
     17) Compute A5=A5A using G5= select(flagEq, A5A, A5) // 1/16
	 
	 Total: 1 + 1 + 1 + 1 + 3 + 2 + 1 + 1+ 1+ 1 + 3 + 3 + 4 + 1 + 1 + 1 + 1= 27/16 = 1.6875 cyc/pixel
	 */

     __vector Vone, Vtwo, Vthree;
     
     Vone= -1;
     Vtwo= -2;
     Vthree= -3;

     /* Process G even line
		compute: 15/(4*8) cyc/pixel
		LD/ST: (7 + 2)/(4*8) cyc/pixel
     */
     for (int h=0; h < (blkHeight + 2)/2; h++) {
        for (int w=0; w < ALIGN_SIMD((blkWidth + 2)/2)/VCOP_SIMD_WIDTH; w++) {
            __agen inputAddr= h*2*input_stride*ELEMSZ_IN + w*VCOP_2SIMD_WIDTH*ELEMSZ_IN;
            __agen outputAddr= h*2*outputG_stride*ELEMSZ_OUT + w*VCOP_2SIMD_WIDTH*ELEMSZ_OUT;
                            
            __vector A1, A3, A5, A7, A9;
            __vector G2, G4, G6, G8, G6tmp;
            __vector G4pG6, G4mG6, G2pG8, G2mG8;
            __vector DH, DV, G5H, G5V, G5A, G5A_tmp;
            __vector DHchroma, DVchroma, abdiffG4mG6, abdiffG2mG8, abdiffDHchroma, abdiffDVchroma, G4pG6_div2, G2pG8_div2, DHchroma_div4, DVchroma_div4;
            __vector flagH, flagEq;

            A1= (pInBuff + 2*ELEMSZ_IN)[inputAddr].ds2();
            (A3, G4)= (pInBuff + 2*input_stride*ELEMSZ_IN)[inputAddr].deinterleave();
            (A5, G6)= (pInBuff + 2*input_stride*ELEMSZ_IN + 2*ELEMSZ_IN)[inputAddr].deinterleave();
            A7= (pInBuff + 2*input_stride*ELEMSZ_IN + 4*ELEMSZ_IN)[inputAddr].ds2();
            A9= (pInBuff + 4*input_stride*ELEMSZ_IN + 2*ELEMSZ_IN)[inputAddr].ds2();

            G2= (pInBuff + input_stride*ELEMSZ_IN + 2*ELEMSZ_IN)[inputAddr].ds2();
            //G4= pInBuff[(2*h+2)*input_stride + 2*w + 1];
            //G6= pInBuff[(2*h+2)*input_stride + 2*w + 3];
            G8= (pInBuff + 3*input_stride*ELEMSZ_IN + 2*ELEMSZ_IN)[inputAddr].ds2();

            /*
            DH= ABS(-A3+2*A5-A7) + ABS(G4-G6);
            DV= ABS(-A1+2*A5-A9) + ABS(G2-G8);

            G5H=(G4+G6)/2+(-A3+2*A5-A7)/4;
            G5V=(G2+G8)/2+(-A1+2*A5-A9)/4;
            G5A=(G2+G4+G6+G8)/4+(-A1-A3+4*A5-A7-A9)/8;
            */

            /*
            1) Compute G4mG6=(G4-G6) & G4pG6=(G4+G6) using (Vsrc1, Vsrc2).addsub(); // 1/16 cyc/pixel
            2) Compute G2mG8=(G2-G8) & G2pG8=(G2+G8) using (Vsrc1, Vsrc2).addsub(); // 1/16 cyc/pixel
            */
            G6tmp= G6;
            (G4pG6,G4mG6)= (G4, G6).addsub();
            (G2pG8,G2mG8)= (G2, G8).addsub();

            /*
            3) Compute abdiffG4mG6=|G4-G6| // 1/16 cyc/pixel
            4) Compute abdiffG2mG8=|G2-G8| // 1/16 cyc/pixel
            */
            abdiffG4mG6= abs(G4mG6);
            abdiffG2mG8= abs(G2mG8);
            
            /*
            5) Compute DHchroma=-A3+2A5-A7= (A5<<1)-A3-A7)= 1/16 + 1/16 + 1/16= 3/16
            6) Compute DVchroma=-A1+2A5-A9= (A5<<1)-A1-A9)= 0 + 1/16 + 1/16= 2/16 // note that (A5<<1) is already computed in previously step
            */
            DHchroma= A5 - A7;
            DVchroma= A5 - A9;

            DHchroma= A5 - A3 + DHchroma;
            DVchroma= A5 - A1 + DVchroma;

            /*
            7) Compute abdiffDHchroma= |-A3+2A5-A7| // 1/16 cyc/pixel
            8) Compute abdiffDVchroma= |-A1+2A5-A9| // 1/16 cyc/pixel 
            */
            abdiffDHchroma= abs(DHchroma);
            abdiffDVchroma= abs(DVchroma);

            /*
            9) Compute DH= abdiffDHchroma +  abdiffG4mG6 // 1/16 cyc/pixel
            10) Compute DV= abdiffDVchroma +  abdiffG2mG8 // 1/16 cyc/pixel
            */
            DH= abdiffDHchroma + abdiffG4mG6;
            DV= abdiffDVchroma + abdiffG2mG8;
            
            /*
            11) Compute G5H= G4pG6>>1 + DHchroma>>2 // 1/16 + 1/16 + 1/16= 3/16
            12) Compute G5V= G2pG8>>1 + DVchroma>>2 // 1/16 + 1/16 + 1/16= 3/16
            */
            G4pG6_div2= G4pG6<<Vone;
            G2pG8_div2= G2pG8<<Vone;
            
            DHchroma_div4= DHchroma<<Vtwo;
            DVchroma_div4= DVchroma<<Vtwo;

            G5H= G4pG6_div2+ DHchroma_div4;
            G5V= G2pG8_div2 + DVchroma_div4;

            /*
            13) Compute G5A= (G2pG8+G4pG6)>>2 + (DHchroma + DVchroma)>>3 // 1/16 + 1/16 + 1/16 + 1/16= 4/16
            14) Compute flagH= (DH<DV) // 1/16
            */
            G5A= G2pG8 + G4pG6;
            G5A_tmp= DHchroma + DVchroma;

            G5A= G5A << Vtwo;
            G5A_tmp= G5A_tmp << Vthree;

            G5A= G5A + G5A_tmp;
            flagH= (DH < DV);

            /*
            15) Compute flagEq= (DN=DP) // 1/16
            16) Compute G5=G5H using G5= select(flagH, G5H, G5V) // 1/16
            */
            flagEq= (DH==DV);
            G5V= select(flagH, G5H, G5V);
            
            /*
            17) Compute G5=G5A using G5= select(flagEq, G5A, G5) // 1/16
            */
            G5V= select(flagEq, G5A, G5V);

			/* Since outputG_stride is odd, the destination address is not 32-bits aligned and thus interleave() cannot be used. Use skip(), instead */
            //(pGbuff)[outputAddr].interleave()= (G5V, G6tmp); 
            (pGbuff)[outputAddr].skip()= G5V;
            (pGbuff + ELEMSZ_OUT)[outputAddr].skip()= G6tmp; 
        }
    }
#if 1
	/* Copy the lines of the input that start with G to the scratch buffer so subsequent deinterleave() load are 32-bits aligned. The read starts at offset 1 half-word  */
		for (int h=0; h < (blkHeight + 6)/2; h++) {
			        for (int w=0; w < ALIGN_SIMD(blkWidth + 6)/VCOP_SIMD_WIDTH; w++) {
			            __agen inputAddr= h*2*input_stride*ELEMSZ_IN + w*VCOP_SIMD_WIDTH*ELEMSZ_IN;
			            __agen outputAddr= h*input_stride*ELEMSZ_IN + w*VCOP_SIMD_WIDTH*ELEMSZ_IN;

			            __vector A1;

			            A1= (pInBuff + (input_stride + 1)*ELEMSZ_IN)[inputAddr].npt();
			            pScratch[outputAddr].npt()= A1;
			        }
		}

	    /* Process G odd line
		compute: 15/(4*8) cyc/pixel
		LD/ST: (7 + 2)/(4*8) cyc/pixel
	    */
		for (int h=0; h < (blkHeight + 2)/2; h++) {
	        for (int w=0; w < ALIGN_SIMD((blkWidth + 2)/2)/VCOP_SIMD_WIDTH; w++) {
	            __agen inputAddr= h*2*input_stride*ELEMSZ_IN + w*VCOP_2SIMD_WIDTH*ELEMSZ_IN;
	            __agen scratchAddr= h*input_stride*ELEMSZ_IN + w*VCOP_2SIMD_WIDTH*ELEMSZ_IN;
	            __agen outputAddr= h*2*outputG_stride*ELEMSZ_OUT + w*VCOP_2SIMD_WIDTH*ELEMSZ_OUT;
	                            
	            __vector A1, A3, A5, A7, A9;
	            __vector G2, G4, G6, G8, G6tmp;
	            __vector G4pG6, G4mG6, G2pG8, G2mG8;
	            __vector DH, DV, G5H, G5V, G5A, G5A_tmp;
	            __vector DHchroma, DVchroma, abdiffG4mG6, abdiffG2mG8, abdiffDHchroma, abdiffDVchroma, G4pG6_div2, G2pG8_div2, DHchroma_div4, DVchroma_div4;
	            __vector flagH, flagEq;

	            A1= (pInBuff + (input_stride + 1)*ELEMSZ_IN + 2*ELEMSZ_IN)[inputAddr].ds2();
	            (A3, G4)= (pScratch + input_stride*ELEMSZ_IN)[scratchAddr].deinterleave();
	            (A5, G6)= (pScratch + input_stride*ELEMSZ_IN + 2*ELEMSZ_IN)[scratchAddr].deinterleave();
	            A7= (pInBuff + (input_stride + 1)*ELEMSZ_IN + 2*input_stride*ELEMSZ_IN + 4*ELEMSZ_IN)[inputAddr].ds2();
	            A9= (pInBuff + (input_stride + 1)*ELEMSZ_IN + 4*input_stride*ELEMSZ_IN + 2*ELEMSZ_IN)[inputAddr].ds2();

	            G2= (pInBuff + (input_stride + 1)*ELEMSZ_IN + input_stride*ELEMSZ_IN + 2*ELEMSZ_IN)[inputAddr].ds2();
	            //G4= pInBuff[(2*h+2)*input_stride + 2*w + 1];
	            //G6= pInBuff[(2*h+2)*input_stride + 2*w + 3];
	            G8= (pInBuff + (input_stride + 1)*ELEMSZ_IN + 3*input_stride*ELEMSZ_IN + 2*ELEMSZ_IN)[inputAddr].ds2();

	            /*
	            DH= ABS(-A3+2*A5-A7) + ABS(G4-G6);
	            DV= ABS(-A1+2*A5-A9) + ABS(G2-G8);

	            G5H=(G4+G6)/2+(-A3+2*A5-A7)/4;
	            G5V=(G2+G8)/2+(-A1+2*A5-A9)/4;
	            G5A=(G2+G4+G6+G8)/4+(-A1-A3+4*A5-A7-A9)/8;
	            */

	            /*
	            1) Compute G4mG6=(G4-G6) & G4pG6=(G4+G6) using (Vsrc1, Vsrc2).addsub(); // 1/16 cyc/pixel
	            2) Compute G2mG8=(G2-G8) & G2pG8=(G2+G8) using (Vsrc1, Vsrc2).addsub(); // 1/16 cyc/pixel
	            */
	            G6tmp= G6;
	            (G4pG6,G4mG6)= (G4, G6).addsub();
	            (G2pG8,G2mG8)= (G2, G8).addsub();

	            /*
	            3) Compute abdiffG4mG6=|G4-G6| // 1/16 cyc/pixel
	            4) Compute abdiffG2mG8=|G2-G8| // 1/16 cyc/pixel
	            */
	            abdiffG4mG6= abs(G4mG6);
	            abdiffG2mG8= abs(G2mG8);
	            
	            /*
	            5) Compute DHchroma=-A3+2A5-A7= (A5<<1)-A3-A7)= 1/16 + 1/16 + 1/16= 3/16
	            6) Compute DVchroma=-A1+2A5-A9= (A5<<1)-A1-A9)= 0 + 1/16 + 1/16= 2/16 // note that (A5<<1) is already computed in previously step
	            */
	            DHchroma= A5 - A7;
	            DVchroma= A5 - A9;

	            DHchroma= A5 - A3 + DHchroma;
	            DVchroma= A5 - A1 + DVchroma;

	            /*
	            7) Compute abdiffDHchroma= |-A3+2A5-A7| // 1/16 cyc/pixel
	            8) Compute abdiffDVchroma= |-A1+2A5-A9| // 1/16 cyc/pixel 
	            */
	            abdiffDHchroma= abs(DHchroma);
	            abdiffDVchroma= abs(DVchroma);

	            /*
	            9) Compute DH= abdiffDHchroma +  abdiffG4mG6 // 1/16 cyc/pixel
	            10) Compute DV= abdiffDVchroma +  abdiffG2mG8 // 1/16 cyc/pixel
	            */
	            DH= abdiffDHchroma + abdiffG4mG6;
	            DV= abdiffDVchroma + abdiffG2mG8;
	            
	            /*
	            11) Compute G5H= G4pG6>>1 + DHchroma>>2 // 1/16 + 1/16 + 1/16= 3/16
	            12) Compute G5V= G2pG8>>1 + DVchroma>>2 // 1/16 + 1/16 + 1/16= 3/16
	            */
	            G4pG6_div2= G4pG6<<Vone;
	            G2pG8_div2= G2pG8<<Vone;
	            
	            DHchroma_div4= DHchroma<<Vtwo;
	            DVchroma_div4= DVchroma<<Vtwo;

	            G5H= G4pG6_div2+ DHchroma_div4;
	            G5V= G2pG8_div2 + DVchroma_div4;

	            /*
	            13) Compute G5A= (G2pG8+G4pG6)>>2 + (DHchroma + DVchroma)>>3 // 1/16 + 1/16 + 1/16 + 1/16= 4/16
	            14) Compute flagH= (DH<DV) // 1/16
	            */
	            G5A= G2pG8 + G4pG6;
	            G5A_tmp= DHchroma + DVchroma;

	            G5A= G5A << Vtwo;
	            G5A_tmp= G5A_tmp << Vthree;

	            G5A= G5A + G5A_tmp;
	            flagH= (DH < DV);

	            /*
	            15) Compute flagEq= (DH=DV) // 1/16
	            16) Compute G5=G5H using G5= select(flagH, G5H, G5V) // 1/16
	            */
	            flagEq= (DH==DV);
	            G5V= select(flagH, G5H, G5V);
	            
	            /*
	            17) Compute G5=G5A using G5= select(flagEq, G5A, G5) // 1/16
	            */
	            G5V= select(flagEq, G5A, G5V);

				/* Since outputG_stride is odd, interleave() is fine */
	            (pGbuff + (outputG_stride + 1)*ELEMSZ_OUT)[outputAddr].interleave()= (G5V, G6tmp);
	        }
	    }	

#else
    /* Process G odd line*/
	for (int h=0; h < (blkHeight + 2)/2; h++) {
	        for (int w=0; w < ALIGN_SIMD((blkWidth + 2)/2)/VCOP_SIMD_WIDTH; w++) {
	            __agen inputAddr= h*2*input_stride*ELEMSZ_IN + w*VCOP_2SIMD_WIDTH*ELEMSZ_IN;
	            __agen outputAddr= h*2*outputG_stride*ELEMSZ_OUT + w*VCOP_2SIMD_WIDTH*ELEMSZ_OUT;
	                            
	            __vector A1, A3, A5, A7, A9;
	            __vector G2, G4, G6, G8, G6tmp;
	            __vector G4pG6, G4mG6, G2pG8, G2mG8;
	            __vector DH, DV, G5H, G5V, G5A, G5A_tmp;
	            __vector DHchroma, DVchroma, abdiffG4mG6, abdiffG2mG8, abdiffDHchroma, abdiffDVchroma, G4pG6_div2, G2pG8_div2, DHchroma_div4, DVchroma_div4;
	            __vector flagH, flagEq;

	            A1= (pInBuff + (input_stride + 1)*ELEMSZ_IN + 2*ELEMSZ_IN)[inputAddr].ds2();
	            (A3, G4)= (pInBuff + (input_stride + 1)*ELEMSZ_IN + 2*input_stride*ELEMSZ_IN)[inputAddr].deinterleave();
	            (A5, G6)= (pInBuff + (input_stride + 1)*ELEMSZ_IN + 2*input_stride*ELEMSZ_IN + 2*ELEMSZ_IN)[inputAddr].deinterleave();
	            A7= (pInBuff + (input_stride + 1)*ELEMSZ_IN + 2*input_stride*ELEMSZ_IN + 4*ELEMSZ_IN)[inputAddr].ds2();
	            A9= (pInBuff + (*input_stride + 1)*ELEMSZ_IN + 4*input_stride*ELEMSZ_IN + 2*ELEMSZ_IN)[inputAddr].ds2();

	            G2= (pInBuff + (input_stride + 1)*ELEMSZ_IN + input_stride*ELEMSZ_IN + 2*ELEMSZ_IN)[inputAddr].ds2();
	            //G4= pInBuff[(2*h+2)*input_stride + 2*w + 1];
	            //G6= pInBuff[(2*h+2)*input_stride + 2*w + 3];
	            G8= (pInBuff + (input_stride + 1)*ELEMSZ_IN + 3*input_stride*ELEMSZ_IN + 2*ELEMSZ_IN)[inputAddr].ds2();

	            /*
	            DH= ABS(-A3+2*A5-A7) + ABS(G4-G6);
	            DV= ABS(-A1+2*A5-A9) + ABS(G2-G8);

	            G5H=(G4+G6)/2+(-A3+2*A5-A7)/4;
	            G5V=(G2+G8)/2+(-A1+2*A5-A9)/4;
	            G5A=(G2+G4+G6+G8)/4+(-A1-A3+4*A5-A7-A9)/8;
	            */

	            /*
	            1) Compute G4mG6=(G4-G6) & G4pG6=(G4+G6) using (Vsrc1, Vsrc2).addsub(); // 1/16 cyc/pixel
	            2) Compute G2mG8=(G2-G8) & G2pG8=(G2+G8) using (Vsrc1, Vsrc2).addsub(); // 1/16 cyc/pixel
	            */
	            G6tmp= G6;
	            (G4pG6,G4mG6)= (G4, G6).addsub();
	            (G2pG8,G2mG8)= (G2, G8).addsub();

	            /*
	            3) Compute abdiffG4mG6=|G4-G6| // 1/16 cyc/pixel
	            4) Compute abdiffG2mG8=|G2-G8| // 1/16 cyc/pixel
	            */
	            abdiffG4mG6= abs(G4mG6);
	            abdiffG2mG8= abs(G2mG8);
	            
	            /*
	            5) Compute DHchroma=-A3+2A5-A7= (A5<<1)-A3-A7)= 1/16 + 1/16 + 1/16= 3/16
	            6) Compute DVchroma=-A1+2A5-A9= (A5<<1)-A1-A9)= 0 + 1/16 + 1/16= 2/16 // note that (A5<<1) is already computed in previously step
	            */
	            DHchroma= A5 - A7;
	            DVchroma= A5 - A9;

	            DHchroma= A5 - A3 + DHchroma;
	            DVchroma= A5 - A1 + DVchroma;

	            /*
	            7) Compute abdiffDHchroma= |-A3+2A5-A7| // 1/16 cyc/pixel
	            8) Compute abdiffDVchroma= |-A1+2A5-A9| // 1/16 cyc/pixel 
	            */
	            abdiffDHchroma= abs(DHchroma);
	            abdiffDVchroma= abs(DVchroma);

	            /*
	            9) Compute DH= abdiffDHchroma +  abdiffG4mG6 // 1/16 cyc/pixel
	            10) Compute DV= abdiffDVchroma +  abdiffG2mG8 // 1/16 cyc/pixel
	            */
	            DH= abdiffDHchroma + abdiffG4mG6;
	            DV= abdiffDVchroma + abdiffG2mG8;
	            
	            /*
	            11) Compute G5H= G4pG6>>1 + DHchroma>>2 // 1/16 + 1/16 + 1/16= 3/16
	            12) Compute G5V= G2pG8>>1 + DVchroma>>2 // 1/16 + 1/16 + 1/16= 3/16
	            */
	            G4pG6_div2= G4pG6<<Vone;
	            G2pG8_div2= G2pG8<<Vone;
	            
	            DHchroma_div4= DHchroma<<Vtwo;
	            DVchroma_div4= DVchroma<<Vtwo;

	            G5H= G4pG6_div2+ DHchroma_div4;
	            G5V= G2pG8_div2 + DVchroma_div4;

	            /*
	            13) Compute G5A= (G2pG8+G4pG6)>>2 + (DHchroma + DVchroma)>>3 // 1/16 + 1/16 + 1/16 + 1/16= 4/16
	            14) Compute flagH= (DH<DV) // 1/16
	            */
	            G5A= G2pG8 + G4pG6;
	            G5A_tmp= DHchroma + DVchroma;

	            G5A= G5A << Vtwo;
	            G5A_tmp= G5A_tmp << Vthree;

	            G5A= G5A + G5A_tmp;
	            flagH= (DH < DV);

	            /*
	            15) Compute flagEq= (DH=DV) // 1/16
	            16) Compute G5=G5H using G5= select(flagH, G5H, G5V) // 1/16
	            */
	            flagEq= (DH==DV);
	            G5V= select(flagH, G5H, G5V);
	            
	            /*
	            17) Compute G5=G5A using G5= select(flagEq, G5A, G5) // 1/16
	            */
	            G5V= select(flagEq, G5A, G5V);

	            (pGbuff + (outputG_stride + 1)*ELEMSZ_OUT)[outputAddr].interleave()= (G5V, G6tmp);
	        }
	    }
#endif
	  /*
	        
	    Chroma plane interpolation
	    
    Input when bayer pattern is AGGC:

	                 |
		A00 G01 A02 G03 A04 G05 A06 G07 A08
		G10 C11 G12 C13 G14 C15 G16 C17 G18
		A20 G21 A22 G23 A24 G25 A26 G27 A28
		G30 C31 G32 C33 G34 C35 G36 C37 G38<--
		A40 G41 A42 G43 A44 G45 A46 G47 A48 
		G50 C51 G52 C53 G54 C55 G56 C57 G58
		A60 G61 A62 G63 A64 G65 A66 G67 A68
		G70 C71 G72 C73 G74 C75 G76 C77 G78
		A80 G81 A82 G83 A84 G85 A86 G87 A88

	    
	    Output when bayer pattern is AGGC:

	Green:
	 
	    G22 G23 G24 G25 G26 G27
	    N/A G33 G34 G35 G36 G37
	    G42 G43 G44 G45 G46 G47
	    N/A G53 G54 G55 G56 G57
	    G62 G63 G64 G65 G66 G67

	Chroma:
	     Blue
	     A33 A34 A35 A36
	     A43 A44 A45 A46
	     A53 A54 A55 A56

	     Red
	     C33 C34 C35 C36
	     C43 C44 C45 C46
	     C53 C54 C55 C56

    Input when bayer pattern is GACG:

                     |
	    G00 A01 G02 A03 G04 A05 G06 A07 G08
	    C10 G11 C12 G13 C14 G15 C16 G17 C18
	    G20 A21 G22 A23 G24 A25 G26 A27 G28
	    C30 G31 C32 G33 C34 G35 C36 G37 C38<--
	    G40 A41 G42 A43 G44 A45 G46 A47 G48
	    C50 G51 C52 G53 C54 G55 C56 G57 C58
	    G60 A61 G62 A63 G64 A65 G66 A67 G68
	    C70 G71 C72 G73 C74 G75 C76 G77 C78
	    G80 A81 G82 A83 G84 A85 G86 A87 G88

	Output when bayer pattern is GACG::

	Green:
		N/A G23 G24 G25 G26 G27
		G32 G33 G34 G35 G36 G37
		N/A G43 G44 G45 G46 G47
		G52 G53 G54 G55 G56 G57
		N/A G63 G64 G65 G66 G67

	Chroma
	Blue:
	     A33 A34 A35 A36
	     A43 A44 A45 A46
	     A53 A54 A55 A56

	Red:
	     C33 C34 C35 C36
	     C43 C44 C45 C46
	     C53 C54 C55 C56
	
	Note that chroma output's area is smaller than green's output area. It is actually 2 pixels shorter and 2 pixels narrower.


	    Algorithm:

	    For AGGC, to compute Red
	    Let's remap the naming convention
	    
	    C33 G34 C35
	    G43 A44 G45
	    C53 G54 C55

	    to:

	    A1 G2 A3
	    G4 C5 G6
	    A7 G8 A9

	    to match the convention used in the patent https://www.google.com/patents/US5629734
	    which produces:
	    A1 A2
	    A4 A5

	    which maps back to
	    C33 C34
	    C43 C44


	     For AGGC:
	     column nearest neighbour: A4= (A1+A7)/2 + (-G1+2G4-G7)/2
	     row nearest neighbour: A2= (A1+A3)/2 + (-G1+2G2-G3)/2   
	 
	     Diagonal:
	     DN=|-G1+2G5-G9|+|A1-A9|
	     DP=|-G3+2G5-G7|+|A3-A7|
	     A5N=(A1+A9)/2+(-G1+2G5-G9)/2
	     A5P=(A3+A7)/2+(-G3+2G5-G7)/2
	     A5A=(A1+A3+A7+A9)/4+(-G1-G3+4G5-G7-G9)/4
	     
	     IF (DN<DP)
	         THEN A5=A5N
	         ELSEIF DP < DN
	                   THEN A5=A5P
	                   ELSE A5=A5A

	*/
	
	
	/* Process R color A1, A4 and A2 
		compute: 6/(4*8) cyc/pixel
		LD/ST: 7/(4*8) cyc/pixel
	*/

    for (int h=0; h < blkHeight/2; h++) {
        for (int w=0; w < ALIGN_SIMD(blkWidth/2)/VCOP_SIMD_WIDTH; w++) {
            __agen inputAddr= h*2*input_stride*ELEMSZ_IN + w*VCOP_2SIMD_WIDTH*ELEMSZ_IN;
            __agen inputGaddr= h*2*outputG_stride*ELEMSZ_OUT + w*VCOP_2SIMD_WIDTH*ELEMSZ_OUT;
            __agen outputAddr= h*2*outputRB_stride*ELEMSZ_OUT + w*VCOP_2SIMD_WIDTH*ELEMSZ_OUT;
                            
            __vector A1, A3, A7, A2, A4;
            __vector G1, G2, G3, G4, G5, G7;
            __vector A4_tmp, A2_tmp ;

		/*
	        A1= pInBuff[(2*h+3)*input_stride + 2*w + 3];  coincide with C33 notation used during green processing 
	        A3= pInBuff[(2*h+3)*input_stride + 2*w + 5];  coincide with C35 notation used during green processing 
	        A7= pInBuff[(2*h+5)*input_stride + 2*w + 3];  coincide with C53 notation used during green processing 
	        A9= pInBuff[(2*h+5)*input_stride + 2*w + 5];  coincide with C55 notation used during green processing 
	        
	        G1= pGbuff[(2*h+1)*outputG_stride + 2*w + 1];  coincide with G33 notation used during green processing 
	        G2= pGbuff[(2*h+1)*outputG_stride + 2*w + 2];  coincide with G34 notation used during green processing 
	        G3= pGbuff[(2*h+1)*outputG_stride + 2*w + 3];  coincide with G35 notation used during green processing 
	        G4= pGbuff[(2*h+2)*outputG_stride + 2*w + 1];  coincide with G43 notation used during green processing 
	        G5= pGbuff[(2*h+2)*outputG_stride + 2*w + 2];  coincide with G44 notation used during green processing 
	        G7= pGbuff[(2*h+3)*outputG_stride + 2*w + 1];  coincide with G53 notation used during green processing 
	        G9= pGbuff[(2*h+3)*outputG_stride + 2*w + 3];  coincide with G55 notation used during green processing 
        */
            A1= (pInBuff + 3*input_stride*ELEMSZ_IN + 3*ELEMSZ_IN)[inputAddr].ds2();
            A3= (pInBuff + 3*input_stride*ELEMSZ_IN + 5*ELEMSZ_IN)[inputAddr].ds2();
            A7= (pInBuff + 5*input_stride*ELEMSZ_IN + 3*ELEMSZ_IN)[inputAddr].ds2();
            //A9= (pInBuff + 5*input_stride*ELEMSZ_IN + 5*ELEMSZ_IN)[inputAddr].ds2();

            (G1, G2)= (pGbuff + outputG_stride*ELEMSZ_OUT + ELEMSZ_OUT)[inputGaddr].deinterleave();
            G3= (pGbuff + outputG_stride*ELEMSZ_OUT + 3*ELEMSZ_OUT)[inputGaddr].ds2();
            
            //(G4, G5)= (pGbuff + 2*outputG_stride*ELEMSZ_OUT + ELEMSZ_OUT)[inputGaddr].deinterleave();
            G4= (pGbuff + 2*outputG_stride*ELEMSZ_OUT + ELEMSZ_OUT)[inputGaddr].ds2();
            //G5= (pGbuff + 2*outputG_stride*ELEMSZ_OUT + 2*ELEMSZ_OUT)[inputGaddr].ds2();
            G7= (pGbuff + 3*outputG_stride*ELEMSZ_OUT + ELEMSZ_OUT)[inputGaddr].ds2();

            //G9= (pGbuff + 3*outputG_stride*ELEMSZ_OUT + 3*ELEMSZ_OUT)[inputGaddr].ds2();

            /*
		     column nearest neighbour: A4= (A1+A7)/2 + (-G1+2G4-G7)/2
		     row nearest neighbour: A2= (A1+A3)/2 + (-G1+2G2-G3)/2
            */
			A4= A1 + A7;
			A2= A1 + A3;
			
			A4= A4 << Vone;
			A2= A2 << Vone;

			A4_tmp= G4 - G7;
			A2_tmp= G2 - G3;
			
			A4_tmp= G4 - G1 + A4_tmp;
			A2_tmp= G2 - G1 + A2_tmp;

			A4_tmp= A4_tmp << Vone;
			A2_tmp= A2_tmp << Vone;		

			A4= A4 + A4_tmp;
			A2= A2 + A2_tmp;

			/*
			pRbuff[(2*h+1)*outputRB_stride + 2*w]= A4;
        	pRbuff[(2*h+1)*outputRB_stride + 2*w+1]= A5;
        	pRbuff[2*h*outputRB_stride + 2*w + 1]= A2;
        	*/
        	(pRbuff)[outputAddr].skip()= A1;
			(pRbuff + outputRB_stride*ELEMSZ_OUT)[outputAddr].skip()= A4;
			(pRbuff + ELEMSZ_OUT)[outputAddr].skip()= A2;
			(pScratch)[outputAddr].skip()= G1;
			(pScratch + ELEMSZ_OUT)[outputAddr].skip()= G3;
			}
		}

	/* Process R color A5 
		compute: 14/(4*8) cyc/pixel
		LD/ST: (4)/(4*8) cyc/pixel
	*/


    for (int h=0; h < blkHeight/2; h++) {
        for (int w=0; w < ALIGN_SIMD(blkWidth/2)/VCOP_SIMD_WIDTH; w++) {
            __agen inputAddr= h*2*input_stride*ELEMSZ_IN + w*VCOP_2SIMD_WIDTH*ELEMSZ_IN;
            __agen inputGaddr= h*2*outputG_stride*ELEMSZ_OUT + w*VCOP_2SIMD_WIDTH*ELEMSZ_OUT;
            __agen outputAddr= h*2*outputRB_stride*ELEMSZ_OUT + w*VCOP_2SIMD_WIDTH*ELEMSZ_OUT;
                            
            __vector A1, A3, A7, A9;
            __vector G1, G3, G4, G5, G7, G9;
            __vector A1pA9, A1mA9, A3pA7,A3mA7;
            __vector DN, DP, A5N, A5P, A5A, A5A_tmp;
            __vector DNgreen, DPgreen, abdiffA1mA9, abdiffA3mA7, abdiffDNgreen, abdiffDPgreen, A1pA9_div2, A3pA7_div2, DNgreen_div2, DPgreen_div2;
            __vector flagN, flagEq;
            
		/*
	        A1= pInBuff[(2*h+3)*input_stride + 2*w + 3];  coincide with C33 notation used during green processing 
	        A3= pInBuff[(2*h+3)*input_stride + 2*w + 5];  coincide with C35 notation used during green processing 
	        A7= pInBuff[(2*h+5)*input_stride + 2*w + 3];  coincide with C53 notation used during green processing 
	        A9= pInBuff[(2*h+5)*input_stride + 2*w + 5];  coincide with C55 notation used during green processing 
	        
	        G1= pGbuff[(2*h+1)*outputG_stride + 2*w + 1];  coincide with G33 notation used during green processing 
	        G2= pGbuff[(2*h+1)*outputG_stride + 2*w + 2];  coincide with G34 notation used during green processing 
	        G3= pGbuff[(2*h+1)*outputG_stride + 2*w + 3];  coincide with G35 notation used during green processing 
	        G4= pGbuff[(2*h+2)*outputG_stride + 2*w + 1];  coincide with G43 notation used during green processing 
	        G5= pGbuff[(2*h+2)*outputG_stride + 2*w + 2];  coincide with G44 notation used during green processing 
	        G7= pGbuff[(2*h+3)*outputG_stride + 2*w + 1];  coincide with G53 notation used during green processing 
	        G9= pGbuff[(2*h+3)*outputG_stride + 2*w + 3];  coincide with G55 notation used during green processing 
        */
            A1= (pInBuff + 3*input_stride*ELEMSZ_IN + 3*ELEMSZ_IN)[inputAddr].ds2();
            A3= (pInBuff + 3*input_stride*ELEMSZ_IN + 5*ELEMSZ_IN)[inputAddr].ds2();
            A7= (pInBuff + 5*input_stride*ELEMSZ_IN + 3*ELEMSZ_IN)[inputAddr].ds2();
            A9= (pInBuff + 5*input_stride*ELEMSZ_IN + 5*ELEMSZ_IN)[inputAddr].ds2();

            (G1, G3)= (pScratch)[outputAddr].deinterleave();
            
            G5= (pGbuff + 2*outputG_stride*ELEMSZ_OUT + 2*ELEMSZ_OUT)[inputGaddr].ds2();
            G7= (pGbuff + 3*outputG_stride*ELEMSZ_OUT + ELEMSZ_OUT)[inputGaddr].ds2();

            G9= (pGbuff + 3*outputG_stride*ELEMSZ_OUT + 3*ELEMSZ_OUT)[inputGaddr].ds2();

		/*
	     Diagonal:
	     DN=|-G1+2G5-G9|+|A1-A9|
	     DP=|-G3+2G5-G7|+|A3-A7|
	     A5N=(A1+A9)/2+(-G1+2G5-G9)/2
	     A5P=(A3+A7)/2+(-G3+2G5-G7)/2
	     A5A=(A1+A3+A7+A9)/4+(-G1-G3+4G5-G7-G9)/4
	     
	     IF (DN<DP)
	         THEN A5=A5N
	         ELSEIF DP < DN
	                   THEN A5=A5P
	                   ELSE A5=A5A

	     */
            /*
            DN= ABS(-G1+2*G5-G9) + ABS(A1-A9);
            DP= ABS(-G3+2*G5-G7) + ABS(A3-A7);

            A5N=(A1+A9)/2+(-G1+2*G5-G9)/2;
            A5P=(A3+A7)/2+(-G3+2*G5-G7)/2;
            A5A=(A1+A3+A7+A9)/4+(-G1-G3+4G5-G7-G9)/8;
            */

            /*
            1) Compute A1mA9=(A1-A9) & A1pA9=(A1+A9) using (Vsrc1, Vsrc2).addsub(); // 1/16 cyc/pixel
            2) Compute A3mA7=(A3-A7) & A3pA7=(G2+G8) using (Vsrc1, Vsrc2).addsub(); // 1/16 cyc/pixel
            */
            (A1pA9,A1mA9)= (A1, A9).addsub();
            (A3pA7,A3mA7)= (A3, A7).addsub();

            /*
            3) Compute abdiffA1mA9=|A1-A9| // 1/16 cyc/pixel
            4) Compute abdiffA3mA7=|A3-A7| // 1/16 cyc/pixel
            */
            abdiffA1mA9= abs(A1mA9);
            abdiffA3mA7= abs(A3mA7);
            
            /*
            5) Compute DNgreen=-G1+2G5-G9= (G5<<1)-G1-G9)= 1/16 + 1/16 + 1/16= 3/16
            6) Compute DPgreen=-G3+2G5-G7= (G5<<1)-G3-G7)= 0 + 1/16 + 1/16= 2/16 // note that (A5<<1) is already computed in previously step
            */
            DNgreen= G5 - G1;
            DPgreen= G5 - G3;

            DNgreen= G5 - G9 + DNgreen;
            DPgreen= G5 - G7 + DPgreen;

            /*
            7) Compute abdiffDNgreen= |-G1+2*G5-G9| // 1/16 cyc/pixel
            8) Compute abdiffDPgreen= |-G3+2*G5-G7| // 1/16 cyc/pixel 
            */
            abdiffDNgreen= abs(DNgreen);
            abdiffDPgreen= abs(DPgreen);

            /*
            9) Compute DN= abdiffDNgreen +  abdiffA1mA9 // 1/16 cyc/pixel
            10) Compute DP= abdiffDPgreen +  abdiffA3mA7 // 1/16 cyc/pixel
            */
            DN= abdiffDNgreen + abdiffA1mA9;
            DP= abdiffDPgreen + abdiffA3mA7;
            
            /*
            11) Compute A5N= A1pA9>>1 + DNgreen>>2 // 1/16 + 1/16 + 1/16= 3/16
            12) Compute A5P= A3pA7>>1 + DPgreen>>2 // 1/16 + 1/16 + 1/16= 3/16
            */
            A1pA9_div2= A1pA9<<Vone;
            A3pA7_div2= A3pA7<<Vone;
            
            DNgreen_div2= DNgreen<<Vone;
            DPgreen_div2= DPgreen<<Vone;

            A5N= A1pA9_div2+ DNgreen_div2;
            A5P= A3pA7_div2 + DPgreen_div2;

            /*
            13) Compute A5A= (A1+A3+A7+A9)>>2 + (DNgreen + DPgreen)>>2 // 1/16 + 1/16 + 1/16 + 1/16= 4/16
            14) Compute flagH= (DN<DP) // 1/16
            */
            A5A= A1pA9 + A3pA7;
            A5A_tmp= DNgreen + DPgreen;

            A5A= A5A << Vtwo;
            A5A_tmp= A5A_tmp << Vtwo;

            A5A= A5A + A5A_tmp;
            flagN= (DN < DP);

            /*
            15) Compute flagEq= (DN=DP) // 1/16
            16) Compute A5=A5N using A5= select(flagN, A5N, A5P) // 1/16
            */
            flagEq= (DN==DP);
            A5P= select(flagN, A5N, A5P);
            
            /*
            17) Compute A5=A5A using A5= select(flagEq, A5A, A5) // 1/16
            */
            A5P= select(flagEq, A5A, A5P);

            (pRbuff + outputRB_stride*ELEMSZ_OUT + ELEMSZ_OUT)[outputAddr].skip()= A5P;

			}
		}

/* Process B color 

          To compute Blue

    We remap the naming convention

    A22 G23 A24
    G32 C33 G34
    A42 G43 A44

    to:

    A1 G2 A3
    G4 C5 G6
    A7 G8 A9

    to produce:
         A5 A6
         A8 A9

    which maps back to:
         A33 A34
         A43 A44

    column nearest neighbour: A6= (A3+A9)/2 + (-G3+2G6-G9)/2
    row nearest neighbour: A8= (A7+A9)/2 + (-G7+2G8-G9)/2

    Diagonal:
    DN=|-G1+2G5-G9|+|A1-A9|
    DP=|-G3+2G5-G7|+|A3-A7|
    A5N=(A1+A9)/2+(-G1+2G5-G9)/2
    A5P=(A3+A7)/2+(-G3+2G5-G7)/2
    A5A=(A1+A3+A7+A9)/4+(-G1-G3+4G5-G7-G9)/4

    IF (DN<DP)
        THEN A5=A5N
        ELSEIF DP < DN
                  THEN A5=A5P
                  ELSE A5=A5A
*/
              
	/* Process B color A9, A6 and A8 
		compute: 6/(4*8) cyc/pixel
		LD/ST: 7/(4*8) cyc/pixel
	*/

    for (int h=0; h < blkHeight/2; h++) {
        for (int w=0; w < ALIGN_SIMD(blkWidth/2)/VCOP_SIMD_WIDTH; w++) {
            __agen inputAddr= h*2*input_stride*ELEMSZ_IN + w*VCOP_2SIMD_WIDTH*ELEMSZ_IN;
            __agen inputGaddr= h*2*outputG_stride*ELEMSZ_OUT + w*VCOP_2SIMD_WIDTH*ELEMSZ_OUT;
            __agen outputAddr= h*2*outputRB_stride*ELEMSZ_OUT + w*VCOP_2SIMD_WIDTH*ELEMSZ_OUT;
                            
            __vector A9, A3, A7, A6, A8;
            __vector G3, G6, G7, G8, G9;
            __vector A6_tmp, A8_tmp ;

		/*
	        A1= (pInBuff - input_stride - 1)[(2*h+3)*input_stride + 2*w + 3];  coincide with A22 notation used during green processing 
        	A3= (pInBuff - input_stride - 1)[(2*h+3)*input_stride + 2*w + 5];  coincide with A24 notation used during green processing 
        	A7= (pInBuff - input_stride - 1)[(2*h+5)*input_stride + 2*w + 3];  coincide with A42 notation used during green processing
        	A9= (pInBuff - input_stride - 1)[(2*h+5)*input_stride + 2*w + 5];  coincide with A44 notation used during green processing
        
        	G1= (pGbuff - outputG_stride - 1)[(2*h+1)*outputG_stride + 2*w + 1]; coincide with G22 notation used during green processing
        	G3= (pGbuff - outputG_stride - 1)[(2*h+1)*outputG_stride + 2*w + 3]; coincide with G24 notation used during green processing
        	G5= (pGbuff - outputG_stride - 1)[(2*h+2)*outputG_stride + 2*w + 2]; coincide with G33 notation used during green processing
        	G6= (pGbuff - outputG_stride - 1)[(2*h+2)*outputG_stride + 2*w + 3]; coincide with G34 notation used during green processing
        	G7= (pGbuff - outputG_stride - 1)[(2*h+3)*outputG_stride + 2*w + 1]; coincide with G42 notation used during green processing
        	G8= (pGbuff - outputG_stride - 1)[(2*h+3)*outputG_stride + 2*w + 2]; coincide with G43 notation used during green processing
        	G9= (pGbuff - outputG_stride - 1)[(2*h+3)*outputG_stride + 2*w + 3]; coincide with G44 notation used during green processing
        */
            A3= (pInBuff + (-1 + 3)*input_stride*ELEMSZ_IN + (-1 + 5)*ELEMSZ_IN)[inputAddr].ds2();
            A7= (pInBuff + (-1 + 5)*input_stride*ELEMSZ_IN + (-1 + 3)*ELEMSZ_IN)[inputAddr].ds2();
            A9= (pInBuff + (-1 + 5)*input_stride*ELEMSZ_IN + (-1 + 5)*ELEMSZ_IN)[inputAddr].ds2();

            G3= (pGbuff + (-1 + 1)*outputG_stride*ELEMSZ_OUT + (-1 + 3)*ELEMSZ_OUT)[inputGaddr].ds2();            
            G6= (pGbuff + (-1 + 2)*outputG_stride*ELEMSZ_OUT + (-1 + 3)*ELEMSZ_OUT)[inputGaddr].ds2();
            G7= (pGbuff + (-1 + 3)*outputG_stride*ELEMSZ_OUT + (-1 + 1)*ELEMSZ_OUT)[inputGaddr].ds2();
            //(G8, G9)= (pGbuff + (-1 + 3)*outputG_stride*ELEMSZ_OUT + (-1 + 2)*ELEMSZ_OUT)[inputGaddr].deinterleave();
			G8= (pGbuff + (-1 + 3)*outputG_stride*ELEMSZ_OUT + (-1 + 2)*ELEMSZ_OUT)[inputGaddr].ds2();
			G9= (pGbuff + (-1 + 3)*outputG_stride*ELEMSZ_OUT + (-1 + 3)*ELEMSZ_OUT)[inputGaddr].ds2();

            /*
		     column nearest neighbour: A6= (A3+A9)/2 + (-G3+2G6-G9)/2
		     row nearest neighbour: A8= (A7+A9)/2 + (-G7+2G8-G9)/2
            */
			A6= A3 + A9;
			A8= A7 + A9;
			
			A6= A6 << Vone;
			A8= A8 << Vone;

			A6_tmp= G6 - G9;
			A8_tmp= G8 - G9;
			
			A6_tmp= G6 - G3 + A6_tmp;
			A8_tmp= G8 - G7 + A8_tmp;

			A6_tmp= A6_tmp << Vone;
			A8_tmp= A8_tmp << Vone;		

			A6= A6 + A6_tmp;
			A8= A8 + A8_tmp;

			/*
        	pBbuff[(2*h+1)*outputRB_stride + 2*w]= A8;
        	pBbuff[(2*h+1)*outputRB_stride + 2*w+1]= A9;
        	pBbuff[2*h*outputRB_stride + 2*w + 1]= A6;
        	*/

			(pBbuff + outputRB_stride*ELEMSZ_OUT)[outputAddr].skip()= A8;
			(pBbuff + outputRB_stride*ELEMSZ_OUT + ELEMSZ_OUT)[outputAddr].skip()= A9;
			(pBbuff + ELEMSZ_OUT)[outputAddr].skip()= A6;
			(pScratch)[outputAddr].skip()= G7;
			(pScratch + ELEMSZ_OUT)[outputAddr].skip()= G9;
			}
		}

	/* Process B color A5 
		compute: 14/(4*8) cyc/pixel
		LD/ST: (4)/(4*8) cyc/pixel
	*/


    for (int h=0; h < blkHeight/2; h++) {
        for (int w=0; w < ALIGN_SIMD(blkWidth/2)/VCOP_SIMD_WIDTH; w++) {
            __agen inputAddr= h*2*input_stride*ELEMSZ_IN + w*VCOP_2SIMD_WIDTH*ELEMSZ_IN;
            __agen inputGaddr= h*2*outputG_stride*ELEMSZ_OUT + w*VCOP_2SIMD_WIDTH*ELEMSZ_OUT;
            __agen outputAddr= h*2*outputRB_stride*ELEMSZ_OUT + w*VCOP_2SIMD_WIDTH*ELEMSZ_OUT;
                            
            __vector A1, A3, A7, A9;
            __vector G1, G3, G5, G7, G9;
            __vector A1pA9, A1mA9, A3pA7,A3mA7;
            __vector DN, DP, A5N, A5P, A5A, A5A_tmp;
            __vector DNgreen, DPgreen, abdiffA1mA9, abdiffA3mA7, abdiffDNgreen, abdiffDPgreen, A1pA9_div2, A3pA7_div2, DNgreen_div2, DPgreen_div2;
            __vector flagN, flagEq;
            
		/*
	        A1= (pInBuff - input_stride - 1)[(2*h+3)*input_stride + 2*w + 3];  coincide with A22 notation used during green processing 
        	A3= (pInBuff - input_stride - 1)[(2*h+3)*input_stride + 2*w + 5];  coincide with A24 notation used during green processing 
        	A7= (pInBuff - input_stride - 1)[(2*h+5)*input_stride + 2*w + 3];  coincide with A42 notation used during green processing
        	A9= (pInBuff - input_stride - 1)[(2*h+5)*input_stride + 2*w + 5];  coincide with A44 notation used during green processing
        
        	G1= (pGbuff - outputG_stride - 1)[(2*h+1)*outputG_stride + 2*w + 1]; coincide with G22 notation used during green processing
        	G3= (pGbuff - outputG_stride - 1)[(2*h+1)*outputG_stride + 2*w + 3]; coincide with G24 notation used during green processing
        	G5= (pGbuff - outputG_stride - 1)[(2*h+2)*outputG_stride + 2*w + 2]; coincide with G33 notation used during green processing
        	G6= (pGbuff - outputG_stride - 1)[(2*h+2)*outputG_stride + 2*w + 3]; coincide with G34 notation used during green processing
        	G7= (pGbuff - outputG_stride - 1)[(2*h+3)*outputG_stride + 2*w + 1]; coincide with G42 notation used during green processing
        	G8= (pGbuff - outputG_stride - 1)[(2*h+3)*outputG_stride + 2*w + 2]; coincide with G43 notation used during green processing
        	G9= (pGbuff - outputG_stride - 1)[(2*h+3)*outputG_stride + 2*w + 3]; coincide with G44 notation used during green processing
        */
            A1= (pInBuff + (-1 + 3)*input_stride*ELEMSZ_IN + (-1 + 3)*ELEMSZ_IN)[inputAddr].ds2();
            A3= (pInBuff + (-1 + 3)*input_stride*ELEMSZ_IN + (-1 + 5)*ELEMSZ_IN)[inputAddr].ds2();
            A7= (pInBuff + (-1 + 5)*input_stride*ELEMSZ_IN + (-1 + 3)*ELEMSZ_IN)[inputAddr].ds2();
            A9= (pInBuff + (-1 + 5)*input_stride*ELEMSZ_IN + (-1 + 5)*ELEMSZ_IN)[inputAddr].ds2();

            G1= (pGbuff + (-1 + 1)*outputG_stride*ELEMSZ_OUT + (-1 + 1)*ELEMSZ_OUT)[inputGaddr].ds2();
            G3= (pGbuff + (-1 + 1)*outputG_stride*ELEMSZ_OUT + (-1 + 3)*ELEMSZ_OUT)[inputGaddr].ds2();
            G5= (pGbuff + (-1 + 2)*outputG_stride*ELEMSZ_OUT + (-1 + 2)*ELEMSZ_OUT)[inputGaddr].ds2();
            (G7, G9)= (pScratch)[outputAddr].deinterleave();


		/*
	     Diagonal:
	     DN=|-G1+2G5-G9|+|A1-A9|
	     DP=|-G3+2G5-G7|+|A3-A7|
	     A5N=(A1+A9)/2+(-G1+2G5-G9)/2
	     A5P=(A3+A7)/2+(-G3+2G5-G7)/2
	     A5A=(A1+A3+A7+A9)/4+(-G1-G3+4G5-G7-G9)/4
	     
	     IF (DN<DP)
	         THEN A5=A5N
	         ELSEIF DP < DN
	                   THEN A5=A5P
	                   ELSE A5=A5A

	     */
            /*
            DN= ABS(-G1+2*G5-G9) + ABS(A1-A9);
            DP= ABS(-G3+2*G5-G7) + ABS(A3-A7);

            A5N=(A1+A9)/2+(-G1+2*G5-G9)/2;
            A5P=(A3+A7)/2+(-G3+2*G5-G7)/2;
            A5A=(A1+A3+A7+A9)/4+(-G1-G3+4G5-G7-G9)/8;
            */

            /*
            1) Compute A1mA9=(A1-A9) & A1pA9=(A1+A9) using (Vsrc1, Vsrc2).addsub(); // 1/16 cyc/pixel
            2) Compute A3mA7=(A3-A7) & A3pA7=(G2+G8) using (Vsrc1, Vsrc2).addsub(); // 1/16 cyc/pixel
            */
            (A1pA9,A1mA9)= (A1, A9).addsub();
            (A3pA7,A3mA7)= (A3, A7).addsub();

            /*
            3) Compute abdiffA1mA9=|A1-A9| // 1/16 cyc/pixel
            4) Compute abdiffA3mA7=|A3-A7| // 1/16 cyc/pixel
            */
            abdiffA1mA9= abs(A1mA9);
            abdiffA3mA7= abs(A3mA7);
            
            /*
            5) Compute DNgreen=-G1+2G5-G9= (G5<<1)-G1-G9)= 1/16 + 1/16 + 1/16= 3/16
            6) Compute DPgreen=-G3+2G5-G7= (G5<<1)-G3-G7)= 0 + 1/16 + 1/16= 2/16 // note that (A5<<1) is already computed in previously step
            */
            DNgreen= G5 - G1;
            DPgreen= G5 - G3;

            DNgreen= G5 - G9 + DNgreen;
            DPgreen= G5 - G7 + DPgreen;

            /*
            7) Compute abdiffDNgreen= |-G1+2*G5-G9| // 1/16 cyc/pixel
            8) Compute abdiffDPgreen= |-G3+2*G5-G7| // 1/16 cyc/pixel 
            */
            abdiffDNgreen= abs(DNgreen);
            abdiffDPgreen= abs(DPgreen);

            /*
            9) Compute DN= abdiffDNgreen +  abdiffA1mA9 // 1/16 cyc/pixel
            10) Compute DP= abdiffDPgreen +  abdiffA3mA7 // 1/16 cyc/pixel
            */
            DN= abdiffDNgreen + abdiffA1mA9;
            DP= abdiffDPgreen + abdiffA3mA7;
            
            /*
            11) Compute A5N= A1pA9>>1 + DNgreen>>2 // 1/16 + 1/16 + 1/16= 3/16
            12) Compute A5P= A3pA7>>1 + DPgreen>>2 // 1/16 + 1/16 + 1/16= 3/16
            */
            A1pA9_div2= A1pA9<<Vone;
            A3pA7_div2= A3pA7<<Vone;
            
            DNgreen_div2= DNgreen<<Vone;
            DPgreen_div2= DPgreen<<Vone;

            A5N= A1pA9_div2+ DNgreen_div2;
            A5P= A3pA7_div2 + DPgreen_div2;

            /*
            13) Compute A5A= (A1+A3+A7+A9)>>2 + (DNgreen + DPgreen)>>2 // 1/16 + 1/16 + 1/16 + 1/16= 4/16
            14) Compute flagH= (DN<DP) // 1/16
            */
            A5A= A1pA9 + A3pA7;
            A5A_tmp= DNgreen + DPgreen;

            A5A= A5A << Vtwo;
            A5A_tmp= A5A_tmp << Vtwo;

            A5A= A5A + A5A_tmp;
            flagN= (DN < DP);

            /*
            15) Compute flagEq= (DN=DP) // 1/16
            16) Compute A5=A5N using A5= select(flagN, A5N, A5P) // 1/16
            */
            flagEq= (DN==DP);
            A5P= select(flagN, A5N, A5P);
            
            /*
            17) Compute A5=A5A using A5= select(flagEq, A5A, A5) // 1/16
            */
            A5P= select(flagEq, A5A, A5P);

            pBbuff[outputAddr].skip()= A5P;

			}
		}
}


void vcop_raw2rgb_GCCG_i16u_o16u
(
        __vptr_uint16 pInBuff,
        __vptr_uint16 pRbuff,
        __vptr_uint16 pGbuff,
        __vptr_uint16 pBbuff,
        __vptr_uint16 pScratch,
        unsigned short blkWidth,
        unsigned short blkHeight,
        unsigned short input_stride,
        unsigned short outputG_stride,
        unsigned short outputRB_stride
)
{
    /*

    Input:

	    |
	G R G R G R
	B G B G B G
	G R G R G R <---
	B G B G B G
	G R G R G R

    https://www.google.com/patents/US5629734
        
     Green plane interpolation 


    Input when bayer pattern is GACG:

             |
    G00 A01 G02 A03 G04 A05 G06 A07 G08
    C10 G11 C12 G13 C14 G15 C16 G17 C18
    G20 A21 G22 A23 G24 A25 G26 A27 G28<--
    C30 G31 C32 G33 C34 G35 C36 G37 C38
    G40 A41 G42 A43 G44 A45 G46 A47 G48
    C50 G51 C52 G53 C54 G55 C56 G57 C58
    G60 A61 G62 A63 G64 A65 G66 A67 G68
    C70 G71 C72 G73 C74 G75 C76 G77 C78
    G80 A81 G82 A83 G84 A85 G86 A87 G88

	Output when bayer pattern is GACG::

	N/A G23 G24 G25 G26 G27
	G32 G33 G34 G35 G36 G37
	N/A G43 G44 G45 G46 G47
	G52 G53 G54 G55 G56 G57
	N/A G63 G64 G65 G66 G67

	    
	Algorithm:

	For AGGC pattern, let's remap the naming convention

	               A02
	               G12
	       A20 G21 A22 G23 A24
	               G32
	               A42

	to:
	               A1
	               G2
	         A3 G4 A5 G6 A7 
	               G8
	               A9

    to match the convention used in the patent https://www.google.com/patents/US5629734

            Output:
            G5 G6
          
     Algorithm:
     
     DH=|-A3+2A5-A7|+|G4-G6|
     DV=|-A1+2A5-A9|+|G2-G8|
     G5H=(G4+G6)/2+(-A3+2A5-A7)/4
     G5V=(G2+G8)/2+(-A1+2A5-A9)/4
     G5A=(G2+G4+G6+G8)/4+(-A1-A3+4A5-A7-A9)/8
     
     IF (DH<DV)
         THEN G5=G5H
         ELSEIF DV < DH
                   THEN G5=G5V
                   ELSE G5=G5A
                   
     1) Compute G4mG6=(G4-G6) & G4pG6=(G4+G6) using (Vsrc1, Vsrc2).addsub(); // 1/16 cyc/pixel
     2) Compute G2mG8=(G2-G8) & G2pG8=(G8+G8) using (Vsrc1, Vsrc2).addsub(); // 1/16 cyc/pixel
     3) Compute abdiffG4mG6=|G4-G6| // 1/16 cyc/pixel
     4) Compute abdiffG2mG8=|G2-G8| // 1/16 cyc/pixel
     5) Compute DHchroma=-A3+2A5-A7= (A5<<1)-A3-A7)= 1/16 + 1/16 + 1/16= 3/16
     6) Compute DVchroma=-A1+2A5-A9= (A5<<1)-A1-A9)= 0 + 1/16 + 1/16= 2/16 // note that (A5<<1) is already computed in previously step
     7) Compute abdiffDHchroma= |-A3+2A5-A7| // 1/16 cyc/pixel
     8) Compute abdiffDVchroma= |-A1+2A5-A9| // 1/16 cyc/pixel 
     9) Compute DH= abdiffDHchroma +  abdiffG4mG6 // 1/16 cyc/pixel
     10) Compute DV= abdiffDVchroma +  abdiffG2mG8 // 1/16 cyc/pixel
     11) Compute G5H= G4pG6>>1 + DHchroma>>2 // 1/16 + 1/16 + 1/16= 3/16
     12) Compute G5V= G2pG8>>1 + DVchroma>>2 // 1/16 + 1/16 + 1/16= 3/16
     13) Compute G5A= (G2pG8+G4pG6)>>2 + (DHchroma + DVchroma)>>3 // 1/16 + 1/16 + 1/16 + 1/16= 4/16
     14) Compute flagH= (DH<DV) // 1/16
     15) Compute flagEq= (DV=DH) // 1/16
     16) Compute G5=G5H using G5= select(flagH, G5H, G5V) // 1/16
     17) Compute G5=G5A using G5= select(flagEq, G5A, G5) // 1/16
	 
	 Total: 1 + 1 + 1 + 1 + 3 + 2 + 1 + 1+ 1+ 1 + 3 + 3 + 4 + 1 + 1 + 1 + 1= 27/16 = 1.6875 cyc/pixel
 
    Chroma plane interpolation 
    Input:

    A1 G2 A3
	G4 C5 G6
	A7 G8 A9
          
     Algorithm:
     
     DN=|-G1+2G5-G9|+|A1-A9|
     DP=|-G3+2G5-G7|+|A3-A7|
     A5N=(A1+A9)/2+(-G1+2G5-G9)/2
     A5P=(A3+A7)/2+(-G3+2G5-G7)/2
     A5A=(A1+A3+A7+A9)/4+(-G1-G3+4G5-G7-G9)/4
     
     IF (DN<DP)
         THEN A5=A5N
         ELSEIF DP < DN
                   THEN A5=A5P
                   ELSE A5=A5A
                   
     1) Compute A1mA9=(A1-A9) & A1pA9=(A1+A9) using (Vsrc1, Vsrc2).addsub(); // 1/16 cyc/pixel
     2) Compute A3mA7=(A3-A7) & A3pA7=(A3+A7) using (Vsrc1, Vsrc2).addsub(); // 1/16 cyc/pixel
     3) Compute abdiffA1mA9=|A1-A9| // 1/16 cyc/pixel
     4) Compute abdiffA3mA7=|A3-A7| // 1/16 cyc/pixel
     5) Compute DNluma=-G1+2G5-G9= (G5<<1)-G1-G9)= 1/16 + 1/16 + 1/16= 3/16
     6) Compute DPluma=-G3+2G5-G7= (G5<<1)-G3-G7)= 0 + 1/16 + 1/16= 2/16 // note that (G5<<1) is already computed in previously step
     7) Compute abdiffDNluma= |-G1+2G5-G9| // 1/16 cyc/pixel
     8) Compute abdiffDPluma= |-G3+2G5-G7| // 1/16 cyc/pixel 
     9) Compute DN= abdiffDNluma +  abdiffA1mA9 // 1/16 cyc/pixel
     10) Compute DP= abdiffDPluma +  abdiffA3mA7 // 1/16 cyc/pixel
     11) Compute A5N= A1pA9>>1 + DNluma>>1 // 1/16 + 1/16 + 1/16= 3/16
     12) Compute A5P= A3pA7>>1 + DPluma>>2 // 1/16 + 1/16 + 1/16= 3/16
     13) Compute A5A= (A3pA7+A1pA9)>>2 + (abdiffDNluma + abdiffDPluma)>>2 // 1/16 + 1/16 + 1/16 + 1/16= 4/16
     14) Compute flagN= (DN<DP) A/ 1/16
     15) Compute flagEq= (DN=DP) // 1/16
     16) Compute A5=A5N using A5= select(flagN, A5N, A5P) // 1/16
     17) Compute A5=A5A using G5= select(flagEq, A5A, A5) // 1/16
	 
	 Total: 1 + 1 + 1 + 1 + 3 + 2 + 1 + 1+ 1+ 1 + 3 + 3 + 4 + 1 + 1 + 1 + 1= 27/16 = 1.6875 cyc/pixel
	 */

     __vector Vone, Vtwo, Vthree;
     
     Vone= -1;
     Vtwo= -2;
     Vthree= -3;

     /* Process G even line*/
     for (int h=0; h < (blkHeight + 2)/2; h++) {
        for (int w=0; w < ALIGN_SIMD((blkWidth + 2)/2)/VCOP_SIMD_WIDTH; w++) {
            __agen inputAddr= h*2*input_stride*ELEMSZ_IN + w*VCOP_2SIMD_WIDTH*ELEMSZ_IN;
            __agen outputAddr= h*2*outputG_stride*ELEMSZ_OUT + w*VCOP_2SIMD_WIDTH*ELEMSZ_OUT;
                            
            __vector A1, A3, A5, A7, A9;
            __vector G2, G4, G6, G8, G6tmp;
            __vector G4pG6, G4mG6, G2pG8, G2mG8;
            __vector DH, DV, G5H, G5V, G5A, G5A_tmp;
            __vector DHchroma, DVchroma, abdiffG4mG6, abdiffG2mG8, abdiffDHchroma, abdiffDVchroma, G4pG6_div2, G2pG8_div2, DHchroma_div4, DVchroma_div4;
            __vector flagH, flagEq;

            A1= (pInBuff + input_stride*ELEMSZ_IN + 2*ELEMSZ_IN)[inputAddr].ds2();
            (A3, G4)= (pInBuff + input_stride*ELEMSZ_IN + 2*input_stride*ELEMSZ_IN)[inputAddr].deinterleave();
            (A5, G6)= (pInBuff + input_stride*ELEMSZ_IN + 2*input_stride*ELEMSZ_IN + 2*ELEMSZ_IN)[inputAddr].deinterleave();
            A7= (pInBuff + input_stride*ELEMSZ_IN + 2*input_stride*ELEMSZ_IN + 4*ELEMSZ_IN)[inputAddr].ds2();
            A9= (pInBuff + input_stride*ELEMSZ_IN + 4*input_stride*ELEMSZ_IN + 2*ELEMSZ_IN)[inputAddr].ds2();

            G2= (pInBuff + input_stride*ELEMSZ_IN + input_stride*ELEMSZ_IN + 2*ELEMSZ_IN)[inputAddr].ds2();
            //G4= pInBuff[(2*h+2)*input_stride + 2*w + 1];
            //G6= pInBuff[(2*h+2)*input_stride + 2*w + 3];
            G8= (pInBuff + input_stride*ELEMSZ_IN + 3*input_stride*ELEMSZ_IN + 2*ELEMSZ_IN)[inputAddr].ds2();

            /*
            DH= ABS(-A3+2*A5-A7) + ABS(G4-G6);
            DV= ABS(-A1+2*A5-A9) + ABS(G2-G8);

            G5H=(G4+G6)/2+(-A3+2*A5-A7)/4;
            G5V=(G2+G8)/2+(-A1+2*A5-A9)/4;
            G5A=(G2+G4+G6+G8)/4+(-A1-A3+4*A5-A7-A9)/8;
            */

            /*
            1) Compute G4mG6=(G4-G6) & G4pG6=(G4+G6) using (Vsrc1, Vsrc2).addsub(); // 1/16 cyc/pixel
            2) Compute G2mG8=(G2-G8) & G2pG8=(G2+G8) using (Vsrc1, Vsrc2).addsub(); // 1/16 cyc/pixel
            */
            G6tmp= G6;
            (G4pG6,G4mG6)= (G4, G6).addsub();
            (G2pG8,G2mG8)= (G2, G8).addsub();

            /*
            3) Compute abdiffG4mG6=|G4-G6| // 1/16 cyc/pixel
            4) Compute abdiffG2mG8=|G2-G8| // 1/16 cyc/pixel
            */
            abdiffG4mG6= abs(G4mG6);
            abdiffG2mG8= abs(G2mG8);
            
            /*
            5) Compute DHchroma=-A3+2A5-A7= (A5<<1)-A3-A7)= 1/16 + 1/16 + 1/16= 3/16
            6) Compute DVchroma=-A1+2A5-A9= (A5<<1)-A1-A9)= 0 + 1/16 + 1/16= 2/16 // note that (A5<<1) is already computed in previously step
            */
            DHchroma= A5 - A7;
            DVchroma= A5 - A9;

            DHchroma= A5 - A3 + DHchroma;
            DVchroma= A5 - A1 + DVchroma;

            /*
            7) Compute abdiffDHchroma= |-A3+2A5-A7| // 1/16 cyc/pixel
            8) Compute abdiffDVchroma= |-A1+2A5-A9| // 1/16 cyc/pixel 
            */
            abdiffDHchroma= abs(DHchroma);
            abdiffDVchroma= abs(DVchroma);

            /*
            9) Compute DH= abdiffDHchroma +  abdiffG4mG6 // 1/16 cyc/pixel
            10) Compute DV= abdiffDVchroma +  abdiffG2mG8 // 1/16 cyc/pixel
            */
            DH= abdiffDHchroma + abdiffG4mG6;
            DV= abdiffDVchroma + abdiffG2mG8;
            
            /*
            11) Compute G5H= G4pG6>>1 + DHchroma>>2 // 1/16 + 1/16 + 1/16= 3/16
            12) Compute G5V= G2pG8>>1 + DVchroma>>2 // 1/16 + 1/16 + 1/16= 3/16
            */
            G4pG6_div2= G4pG6<<Vone;
            G2pG8_div2= G2pG8<<Vone;
            
            DHchroma_div4= DHchroma<<Vtwo;
            DVchroma_div4= DVchroma<<Vtwo;

            G5H= G4pG6_div2+ DHchroma_div4;
            G5V= G2pG8_div2 + DVchroma_div4;

            /*
            13) Compute G5A= (G2pG8+G4pG6)>>2 + (DHchroma + DVchroma)>>3 // 1/16 + 1/16 + 1/16 + 1/16= 4/16
            14) Compute flagH= (DH<DV) // 1/16
            */
            G5A= G2pG8 + G4pG6;
            G5A_tmp= DHchroma + DVchroma;

            G5A= G5A << Vtwo;
            G5A_tmp= G5A_tmp << Vthree;

            G5A= G5A + G5A_tmp;
            flagH= (DH < DV);

            /*
            15) Compute flagEq= (DN=DP) // 1/16
            16) Compute G5=G5H using G5= select(flagH, G5H, G5V) // 1/16
            */
            flagEq= (DH==DV);
            G5V= select(flagH, G5H, G5V);
            
            /*
            17) Compute G5=G5A using G5= select(flagEq, G5A, G5) // 1/16
            */
            G5V= select(flagEq, G5A, G5V);

			/* Since outputG_stride is odd, the destination address is not 32-bits aligned and thus interleave() cannot be used. Use skip(), instead */
            //(pGbuff + outputG_stride*ELEMSZ_OUT)[outputAddr].interleave()= (G5V, G6tmp); 
            (pGbuff + outputG_stride*ELEMSZ_OUT)[outputAddr].skip()= G5V;
            (pGbuff + outputG_stride*ELEMSZ_OUT + ELEMSZ_OUT)[outputAddr].skip()= G6tmp; 
        }
    }
#if 1
	/* Copy the lines of the input that start with G to the scratch buffer so subsequent deinterleave() load are 32-bits aligned. The read starts at offset 1 half-word  */
		for (int h=0; h < (blkHeight + 6)/2; h++) {
			        for (int w=0; w < ALIGN_SIMD(blkWidth + 6)/VCOP_SIMD_WIDTH; w++) {
			            __agen inputAddr= h*2*input_stride*ELEMSZ_IN + w*VCOP_SIMD_WIDTH*ELEMSZ_IN;
			            __agen outputAddr= h*input_stride*ELEMSZ_IN + w*VCOP_SIMD_WIDTH*ELEMSZ_IN;

			            __vector A1;

			            A1= (pInBuff + ELEMSZ_IN)[inputAddr].npt();
			            pScratch[outputAddr].npt()= A1;
			        }
		}

	    /* Process G odd line*/
		for (int h=0; h < (blkHeight + 2)/2; h++) {
	        for (int w=0; w < ALIGN_SIMD((blkWidth + 2)/2)/VCOP_SIMD_WIDTH; w++) {
	            __agen inputAddr= h*2*input_stride*ELEMSZ_IN + w*VCOP_2SIMD_WIDTH*ELEMSZ_IN;
	            __agen scratchAddr= h*input_stride*ELEMSZ_IN + w*VCOP_2SIMD_WIDTH*ELEMSZ_IN;
	            __agen outputAddr= h*2*outputG_stride*ELEMSZ_OUT + w*VCOP_2SIMD_WIDTH*ELEMSZ_OUT;
	                            
	            __vector A1, A3, A5, A7, A9;
	            __vector G2, G4, G6, G8, G6tmp;
	            __vector G4pG6, G4mG6, G2pG8, G2mG8;
	            __vector DH, DV, G5H, G5V, G5A, G5A_tmp;
	            __vector DHchroma, DVchroma, abdiffG4mG6, abdiffG2mG8, abdiffDHchroma, abdiffDVchroma, G4pG6_div2, G2pG8_div2, DHchroma_div4, DVchroma_div4;
	            __vector flagH, flagEq;

	            A1= (pInBuff + ELEMSZ_IN + 2*ELEMSZ_IN)[inputAddr].ds2();
	            (A3, G4)= (pScratch + input_stride*ELEMSZ_IN)[scratchAddr].deinterleave();
	            (A5, G6)= (pScratch + input_stride*ELEMSZ_IN + 2*ELEMSZ_IN)[scratchAddr].deinterleave();
	            A7= (pInBuff + ELEMSZ_IN + 2*input_stride*ELEMSZ_IN + 4*ELEMSZ_IN)[inputAddr].ds2();
	            A9= (pInBuff + ELEMSZ_IN + 4*input_stride*ELEMSZ_IN + 2*ELEMSZ_IN)[inputAddr].ds2();

	            G2= (pInBuff + ELEMSZ_IN + input_stride*ELEMSZ_IN + 2*ELEMSZ_IN)[inputAddr].ds2();
	            //G4= pInBuff[(2*h+2)*input_stride + 2*w + 1];
	            //G6= pInBuff[(2*h+2)*input_stride + 2*w + 3];
	            G8= (pInBuff + ELEMSZ_IN + 3*input_stride*ELEMSZ_IN + 2*ELEMSZ_IN)[inputAddr].ds2();

	            /*
	            DH= ABS(-A3+2*A5-A7) + ABS(G4-G6);
	            DV= ABS(-A1+2*A5-A9) + ABS(G2-G8);

	            G5H=(G4+G6)/2+(-A3+2*A5-A7)/4;
	            G5V=(G2+G8)/2+(-A1+2*A5-A9)/4;
	            G5A=(G2+G4+G6+G8)/4+(-A1-A3+4*A5-A7-A9)/8;
	            */

	            /*
	            1) Compute G4mG6=(G4-G6) & G4pG6=(G4+G6) using (Vsrc1, Vsrc2).addsub(); // 1/16 cyc/pixel
	            2) Compute G2mG8=(G2-G8) & G2pG8=(G2+G8) using (Vsrc1, Vsrc2).addsub(); // 1/16 cyc/pixel
	            */
	            G6tmp= G6;
	            (G4pG6,G4mG6)= (G4, G6).addsub();
	            (G2pG8,G2mG8)= (G2, G8).addsub();

	            /*
	            3) Compute abdiffG4mG6=|G4-G6| // 1/16 cyc/pixel
	            4) Compute abdiffG2mG8=|G2-G8| // 1/16 cyc/pixel
	            */
	            abdiffG4mG6= abs(G4mG6);
	            abdiffG2mG8= abs(G2mG8);
	            
	            /*
	            5) Compute DHchroma=-A3+2A5-A7= (A5<<1)-A3-A7)= 1/16 + 1/16 + 1/16= 3/16
	            6) Compute DVchroma=-A1+2A5-A9= (A5<<1)-A1-A9)= 0 + 1/16 + 1/16= 2/16 // note that (A5<<1) is already computed in previously step
	            */
	            DHchroma= A5 - A7;
	            DVchroma= A5 - A9;

	            DHchroma= A5 - A3 + DHchroma;
	            DVchroma= A5 - A1 + DVchroma;

	            /*
	            7) Compute abdiffDHchroma= |-A3+2A5-A7| // 1/16 cyc/pixel
	            8) Compute abdiffDVchroma= |-A1+2A5-A9| // 1/16 cyc/pixel 
	            */
	            abdiffDHchroma= abs(DHchroma);
	            abdiffDVchroma= abs(DVchroma);

	            /*
	            9) Compute DH= abdiffDHchroma +  abdiffG4mG6 // 1/16 cyc/pixel
	            10) Compute DV= abdiffDVchroma +  abdiffG2mG8 // 1/16 cyc/pixel
	            */
	            DH= abdiffDHchroma + abdiffG4mG6;
	            DV= abdiffDVchroma + abdiffG2mG8;
	            
	            /*
	            11) Compute G5H= G4pG6>>1 + DHchroma>>2 // 1/16 + 1/16 + 1/16= 3/16
	            12) Compute G5V= G2pG8>>1 + DVchroma>>2 // 1/16 + 1/16 + 1/16= 3/16
	            */
	            G4pG6_div2= G4pG6<<Vone;
	            G2pG8_div2= G2pG8<<Vone;
	            
	            DHchroma_div4= DHchroma<<Vtwo;
	            DVchroma_div4= DVchroma<<Vtwo;

	            G5H= G4pG6_div2+ DHchroma_div4;
	            G5V= G2pG8_div2 + DVchroma_div4;

	            /*
	            13) Compute G5A= (G2pG8+G4pG6)>>2 + (DHchroma + DVchroma)>>3 // 1/16 + 1/16 + 1/16 + 1/16= 4/16
	            14) Compute flagH= (DH<DV) // 1/16
	            */
	            G5A= G2pG8 + G4pG6;
	            G5A_tmp= DHchroma + DVchroma;

	            G5A= G5A << Vtwo;
	            G5A_tmp= G5A_tmp << Vthree;

	            G5A= G5A + G5A_tmp;
	            flagH= (DH < DV);

	            /*
	            15) Compute flagEq= (DH=DV) // 1/16
	            16) Compute G5=G5H using G5= select(flagH, G5H, G5V) // 1/16
	            */
	            flagEq= (DH==DV);
	            G5V= select(flagH, G5H, G5V);
	            
	            /*
	            17) Compute G5=G5A using G5= select(flagEq, G5A, G5) // 1/16
	            */
	            G5V= select(flagEq, G5A, G5V);

	            (pGbuff + ELEMSZ_OUT)[outputAddr].skip()= G5V;
	            (pGbuff + 2*ELEMSZ_OUT)[outputAddr].skip()= G6tmp;
	        }
	    }	

#else
    /* Process G odd line*/
	for (int h=0; h < (blkHeight + 2)/2; h++) {
	        for (int w=0; w < ALIGN_SIMD((blkWidth + 2)/2)/VCOP_SIMD_WIDTH; w++) {
	            __agen inputAddr= h*2*input_stride*ELEMSZ_IN + w*VCOP_2SIMD_WIDTH*ELEMSZ_IN;
	            __agen outputAddr= h*2*outputG_stride*ELEMSZ_OUT + w*VCOP_2SIMD_WIDTH*ELEMSZ_OUT;
	                            
	            __vector A1, A3, A5, A7, A9;
	            __vector G2, G4, G6, G8, G6tmp;
	            __vector G4pG6, G4mG6, G2pG8, G2mG8;
	            __vector DH, DV, G5H, G5V, G5A, G5A_tmp;
	            __vector DHchroma, DVchroma, abdiffG4mG6, abdiffG2mG8, abdiffDHchroma, abdiffDVchroma, G4pG6_div2, G2pG8_div2, DHchroma_div4, DVchroma_div4;
	            __vector flagH, flagEq;

	            A1= (pInBuff + (ELEMSZ_IN + 2*ELEMSZ_IN)[inputAddr].ds2();
	            (A3, G4)= (pInBuff + ELEMSZ_IN + 2*input_stride*ELEMSZ_IN)[inputAddr].deinterleave();
	            (A5, G6)= (pInBuff + ELEMSZ_IN + 2*input_stride*ELEMSZ_IN + 2*ELEMSZ_IN)[inputAddr].deinterleave();
	            A7= (pInBuff + ELEMSZ_IN + 2*input_stride*ELEMSZ_IN + 4*ELEMSZ_IN)[inputAddr].ds2();
	            A9= (pInBuff + ELEMSZ_IN + 4*input_stride*ELEMSZ_IN + 2*ELEMSZ_IN)[inputAddr].ds2();

	            G2= (pInBuff + ELEMSZ_IN + input_stride*ELEMSZ_IN + 2*ELEMSZ_IN)[inputAddr].ds2();
	            //G4= pInBuff[(2*h+2)*input_stride + 2*w + 1];
	            //G6= pInBuff[(2*h+2)*input_stride + 2*w + 3];
	            G8= (pInBuff + (ELEMSZ_IN + 3*input_stride*ELEMSZ_IN + 2*ELEMSZ_IN)[inputAddr].ds2();

	            /*
	            DH= ABS(-A3+2*A5-A7) + ABS(G4-G6);
	            DV= ABS(-A1+2*A5-A9) + ABS(G2-G8);

	            G5H=(G4+G6)/2+(-A3+2*A5-A7)/4;
	            G5V=(G2+G8)/2+(-A1+2*A5-A9)/4;
	            G5A=(G2+G4+G6+G8)/4+(-A1-A3+4*A5-A7-A9)/8;
	            */

	            /*
	            1) Compute G4mG6=(G4-G6) & G4pG6=(G4+G6) using (Vsrc1, Vsrc2).addsub(); // 1/16 cyc/pixel
	            2) Compute G2mG8=(G2-G8) & G2pG8=(G2+G8) using (Vsrc1, Vsrc2).addsub(); // 1/16 cyc/pixel
	            */
	            G6tmp= G6;
	            (G4pG6,G4mG6)= (G4, G6).addsub();
	            (G2pG8,G2mG8)= (G2, G8).addsub();

	            /*
	            3) Compute abdiffG4mG6=|G4-G6| // 1/16 cyc/pixel
	            4) Compute abdiffG2mG8=|G2-G8| // 1/16 cyc/pixel
	            */
	            abdiffG4mG6= abs(G4mG6);
	            abdiffG2mG8= abs(G2mG8);
	            
	            /*
	            5) Compute DHchroma=-A3+2A5-A7= (A5<<1)-A3-A7)= 1/16 + 1/16 + 1/16= 3/16
	            6) Compute DVchroma=-A1+2A5-A9= (A5<<1)-A1-A9)= 0 + 1/16 + 1/16= 2/16 // note that (A5<<1) is already computed in previously step
	            */
	            DHchroma= A5 - A7;
	            DVchroma= A5 - A9;

	            DHchroma= A5 - A3 + DHchroma;
	            DVchroma= A5 - A1 + DVchroma;

	            /*
	            7) Compute abdiffDHchroma= |-A3+2A5-A7| // 1/16 cyc/pixel
	            8) Compute abdiffDVchroma= |-A1+2A5-A9| // 1/16 cyc/pixel 
	            */
	            abdiffDHchroma= abs(DHchroma);
	            abdiffDVchroma= abs(DVchroma);

	            /*
	            9) Compute DH= abdiffDHchroma +  abdiffG4mG6 // 1/16 cyc/pixel
	            10) Compute DV= abdiffDVchroma +  abdiffG2mG8 // 1/16 cyc/pixel
	            */
	            DH= abdiffDHchroma + abdiffG4mG6;
	            DV= abdiffDVchroma + abdiffG2mG8;
	            
	            /*
	            11) Compute G5H= G4pG6>>1 + DHchroma>>2 // 1/16 + 1/16 + 1/16= 3/16
	            12) Compute G5V= G2pG8>>1 + DVchroma>>2 // 1/16 + 1/16 + 1/16= 3/16
	            */
	            G4pG6_div2= G4pG6<<Vone;
	            G2pG8_div2= G2pG8<<Vone;
	            
	            DHchroma_div4= DHchroma<<Vtwo;
	            DVchroma_div4= DVchroma<<Vtwo;

	            G5H= G4pG6_div2+ DHchroma_div4;
	            G5V= G2pG8_div2 + DVchroma_div4;

	            /*
	            13) Compute G5A= (G2pG8+G4pG6)>>2 + (DHchroma + DVchroma)>>3 // 1/16 + 1/16 + 1/16 + 1/16= 4/16
	            14) Compute flagH= (DH<DV) // 1/16
	            */
	            G5A= G2pG8 + G4pG6;
	            G5A_tmp= DHchroma + DVchroma;

	            G5A= G5A << Vtwo;
	            G5A_tmp= G5A_tmp << Vthree;

	            G5A= G5A + G5A_tmp;
	            flagH= (DH < DV);

	            /*
	            15) Compute flagEq= (DH=DV) // 1/16
	            16) Compute G5=G5H using G5= select(flagH, G5H, G5V) // 1/16
	            */
	            flagEq= (DH==DV);
	            G5V= select(flagH, G5H, G5V);
	            
	            /*
	            17) Compute G5=G5A using G5= select(flagEq, G5A, G5) // 1/16
	            */
	            G5V= select(flagEq, G5A, G5V);

	            (pGbuff + ELEMSZ_OUT)[outputAddr].interleave()= (G5V, G6tmp);
	        }
	    }
#endif
	  /*
	        
	    Chroma plane interpolation
	    
    Input when bayer pattern is GACG:

                     |
	    G00 A01 G02 A03 G04 A05 G06 A07 G08
	    C10 G11 C12 G13 C14 G15 C16 G17 C18
	    G20 A21 G22 A23 G24 A25 G26 A27 G28
	    C30 G31 C32 G33 C34 G35 C36 G37 C38<--
	    G40 A41 G42 A43 G44 A45 G46 A47 G48
	    C50 G51 C52 G53 C54 G55 C56 G57 C58
	    G60 A61 G62 A63 G64 A65 G66 A67 G68
	    C70 G71 C72 G73 C74 G75 C76 G77 C78
	    G80 A81 G82 A83 G84 A85 G86 A87 G88

	Output when bayer pattern is GACG::

	Green:
		N/A G23 G24 G25 G26 G27
		G32 G33 G34 G35 G36 G37
		N/A G43 G44 G45 G46 G47
		G52 G53 G54 G55 G56 G57
		N/A G63 G64 G65 G66 G67

	Chroma
	Blue:
	     A33 A34 A35 A36
	     A43 A44 A45 A46
	     A53 A54 A55 A56

	Red:
	     C33 C34 C35 C36
	     C43 C44 C45 C46
	     C53 C54 C55 C56
	
	Note that chroma output's area is smaller than green's output area. It is actually 2 pixels shorter and 2 pixels narrower.


	    Algorithm:

	    For GACG, to compute Blue
	    Let's remap the naming convention
	    
	    C23 G24 C25
	    G33 C34 G35
	    C43 G44 C45

	    to:

	    A1 G2 A3
	    G4 C5 G6
	    A7 G8 A9

	    to match the convention used in the patent https://www.google.com/patents/US5629734
	    which produces:
	    A4 A5
	    A7 A8

	    which maps back to
	    A33 A34
	    A43 A44

	     For AGGC:
	     column nearest neighbour: A4= (A1+A7)/2 + (-G1+2G4-G7)/2
	     row nearest neighbour: A2= (A1+A3)/2 + (-G1+2G2-G3)/2

	     For GACG:
	     column nearest neighbour: A4= (A1+A7)/2 + (-G1+2G4-G7)/2
	     row nearest neighbour: A8= (A7+A9)/2 + (-G7+2G8-G9)/2	     
	 
	     Diagonal:
	     DN=|-G1+2G5-G9|+|A1-A9|
	     DP=|-G3+2G5-G7|+|A3-A7|
	     A5N=(A1+A9)/2+(-G1+2G5-G9)/2
	     A5P=(A3+A7)/2+(-G3+2G5-G7)/2
	     A5A=(A1+A3+A7+A9)/4+(-G1-G3+4G5-G7-G9)/4
	     
	     IF (DN<DP)
	         THEN A5=A5N
	         ELSEIF DP < DN
	                   THEN A5=A5P
	                   ELSE A5=A5A

	*/
	
	
	/* Process B color A7, A4 and A8 */

    for (int h=0; h < blkHeight/2; h++) {
        for (int w=0; w < ALIGN_SIMD(blkWidth/2)/VCOP_SIMD_WIDTH; w++) {
            __agen inputAddr= h*2*input_stride*ELEMSZ_IN + w*VCOP_2SIMD_WIDTH*ELEMSZ_IN;
            __agen inputGaddr= h*2*outputG_stride*ELEMSZ_OUT + w*VCOP_2SIMD_WIDTH*ELEMSZ_OUT;
            __agen outputAddr= h*2*outputRB_stride*ELEMSZ_OUT + w*VCOP_2SIMD_WIDTH*ELEMSZ_OUT;
                            
            __vector A1, A9, A7, A8, A4;
            __vector G1, G2, G4, G7, G8, G9;
            __vector A4_tmp, A8_tmp;

		/*
	        A1= pInBuff[(2*h+3-1)*input_stride + 2*w + 3];  coincide with A23 notation used during green processing 
	        A3= pInBuff[(2*h+3-1)*input_stride + 2*w + 5];  coincide with A25 notation used during green processing 
	        A7= pInBuff[(2*h+5-1)*input_stride + 2*w + 3];  coincide with A43 notation used during green processing 
	        A9= pInBuff[(2*h+5-1)*input_stride + 2*w + 5];  coincide with A45 notation used during green processing 
	        
	        G1= pGbuff[(2*h+1-1)*outputG_stride + 2*w + 1];  coincide with G23 notation used during green processing 
	        G2= pGbuff[(2*h+1-1)*outputG_stride + 2*w + 2];  coincide with G24 notation used during green processing 
	        G3= pGbuff[(2*h+1-1)*outputG_stride + 2*w + 3];  coincide with G25 notation used during green processing 
	        G4= pGbuff[(2*h+2-1)*outputG_stride + 2*w + 1];  coincide with G33 notation used during green processing 
	        G5= pGbuff[(2*h+2-1)*outputG_stride + 2*w + 2];  coincide with G34 notation used during green processing 
	        G7= pGbuff[(2*h+3-1)*outputG_stride + 2*w + 1];  coincide with G43 notation used during green processing 
	        G9= pGbuff[(2*h+3-1)*outputG_stride + 2*w + 3];  coincide with G45 notation used during green processing 
        */
            A1= (pInBuff + (3-1)*input_stride*ELEMSZ_IN + 3*ELEMSZ_IN)[inputAddr].ds2();
            //A3= (pInBuff + (3-1)*input_stride*ELEMSZ_IN + 5*ELEMSZ_IN)[inputAddr].ds2();
            A7= (pInBuff + (5-1)*input_stride*ELEMSZ_IN + 3*ELEMSZ_IN)[inputAddr].ds2();
            A9= (pInBuff + (5-1)*input_stride*ELEMSZ_IN + 5*ELEMSZ_IN)[inputAddr].ds2();

            G1= (pGbuff + ELEMSZ_OUT)[inputGaddr].ds2();  
            G2= (pGbuff + 2*ELEMSZ_OUT)[inputGaddr].ds2();  
            //(G4, G5)= (pGbuff + 2*outputG_stride*ELEMSZ_OUT + ELEMSZ_OUT)[inputGaddr].deinterleave();
            G4= (pGbuff + (2-1)*outputG_stride*ELEMSZ_OUT + ELEMSZ_OUT)[inputGaddr].ds2();
            //G5= (pGbuff + (2-1)*outputG_stride*ELEMSZ_OUT + 2*ELEMSZ_OUT)[inputGaddr].ds2();
            G7= (pGbuff + (3-1)*outputG_stride*ELEMSZ_OUT + ELEMSZ_OUT)[inputGaddr].ds2();
            (G8, G9)= (pGbuff + (3-1)*outputG_stride*ELEMSZ_OUT + 2*ELEMSZ_OUT)[inputGaddr].deinterleave();
            //G8= (pGbuff + (3-1)*outputG_stride*ELEMSZ_OUT + 2*ELEMSZ_OUT)[inputGaddr].ds2();
            //G9= (pGbuff + (3-1)*outputG_stride*ELEMSZ_OUT + 3*ELEMSZ_OUT)[inputGaddr].ds2();

            /*
		     column nearest neighbour: A4= (A1+A7)/2 + (-G1+2G4-G7)/2
		     row nearest neighbour: A2= (A1+A3)/2 + (-G1+2G2-G3)/2
            */
			A4= A1 + A7;
			A8= A9 + A7;
			
			A4= A4 << Vone;
			A8= A8 << Vone;

			A4_tmp= G4 - G7;
			A8_tmp= G8 - G7;
			
			A4_tmp= G4 - G1 + A4_tmp;
			A8_tmp= G8 - G9 + A8_tmp;

			A4_tmp= A4_tmp << Vone;
			A8_tmp= A8_tmp << Vone;		

			A4= A4 + A4_tmp;
			A8= A8 + A8_tmp;

			/*
			pBbuff[(2*h+1)*outputRB_stride + 2*w]= A7;
        	pBbuff[(2*h+1)*outputRB_stride + 2*w+1]= A8;
        	pBbuff[2*h*outputRB_stride + 2*w]= A4;
        	*/
        	(pBbuff)[outputAddr].skip()= A4;
			(pBbuff + outputRB_stride*ELEMSZ_OUT)[outputAddr].skip()= A7;
			(pBbuff + outputRB_stride*ELEMSZ_OUT + ELEMSZ_OUT)[outputAddr].skip()= A8;
			(pScratch)[outputAddr].skip()= G7;
			(pScratch + ELEMSZ_OUT)[outputAddr].skip()= G9;
			}
		}

	/* Process B color A5 */


    for (int h=0; h < blkHeight/2; h++) {
        for (int w=0; w < ALIGN_SIMD(blkWidth/2)/VCOP_SIMD_WIDTH; w++) {
            __agen inputAddr= h*2*input_stride*ELEMSZ_IN + w*VCOP_2SIMD_WIDTH*ELEMSZ_IN;
            __agen inputGaddr= h*2*outputG_stride*ELEMSZ_OUT + w*VCOP_2SIMD_WIDTH*ELEMSZ_OUT;
            __agen outputAddr= h*2*outputRB_stride*ELEMSZ_OUT + w*VCOP_2SIMD_WIDTH*ELEMSZ_OUT;
                            
            __vector A1, A3, A7, A9;
            __vector G1, G3, G4, G5, G7, G9;
            __vector A1pA9, A1mA9, A3pA7,A3mA7;
            __vector DN, DP, A5N, A5P, A5A, A5A_tmp;
            __vector DNgreen, DPgreen, abdiffA1mA9, abdiffA3mA7, abdiffDNgreen, abdiffDPgreen, A1pA9_div2, A3pA7_div2, DNgreen_div2, DPgreen_div2;
            __vector flagN, flagEq;
            
		/*
	        A1= pInBuff[(2*h+3-1)*input_stride + 2*w + 3];  coincide with A23 notation used during green processing 
	        A3= pInBuff[(2*h+3-1)*input_stride + 2*w + 5];  coincide with A25 notation used during green processing 
	        A7= pInBuff[(2*h+5-1)*input_stride + 2*w + 3];  coincide with A43 notation used during green processing 
	        A9= pInBuff[(2*h+5-1)*input_stride + 2*w + 5];  coincide with A45 notation used during green processing 
	        
	        G1= pGbuff[(2*h+1-1)*outputG_stride + 2*w + 1];  coincide with G23 notation used during green processing 
	        G2= pGbuff[(2*h+1-1)*outputG_stride + 2*w + 2];  coincide with G24 notation used during green processing 
	        G3= pGbuff[(2*h+1-1)*outputG_stride + 2*w + 3];  coincide with G25 notation used during green processing 
	        G4= pGbuff[(2*h+2-1)*outputG_stride + 2*w + 1];  coincide with G33 notation used during green processing 
	        G5= pGbuff[(2*h+2-1)*outputG_stride + 2*w + 2];  coincide with G34 notation used during green processing 
	        G7= pGbuff[(2*h+3-1)*outputG_stride + 2*w + 1];  coincide with G43 notation used during green processing 
	        G9= pGbuff[(2*h+3-1)*outputG_stride + 2*w + 3];  coincide with G45 notation used during green processing 
        */
            A1= (pInBuff + (3-1)*input_stride*ELEMSZ_IN + 3*ELEMSZ_IN)[inputAddr].ds2();
            A3= (pInBuff + (3-1)*input_stride*ELEMSZ_IN + 5*ELEMSZ_IN)[inputAddr].ds2();
            A7= (pInBuff + (5-1)*input_stride*ELEMSZ_IN + 3*ELEMSZ_IN)[inputAddr].ds2();
            A9= (pInBuff + (5-1)*input_stride*ELEMSZ_IN + 5*ELEMSZ_IN)[inputAddr].ds2();

            (G7, G9)= (pScratch)[outputAddr].deinterleave();
            
            G5= (pGbuff + (2-1)*outputG_stride*ELEMSZ_OUT + 2*ELEMSZ_OUT)[inputGaddr].ds2();
            G1= (pGbuff + (1-1)*outputG_stride*ELEMSZ_OUT + ELEMSZ_OUT)[inputGaddr].ds2();

            G3= (pGbuff + (1-1)*outputG_stride*ELEMSZ_OUT + 3*ELEMSZ_OUT)[inputGaddr].ds2();

		/*
	     Diagonal:
	     DN=|-G1+2G5-G9|+|A1-A9|
	     DP=|-G3+2G5-G7|+|A3-A7|
	     A5N=(A1+A9)/2+(-G1+2G5-G9)/2
	     A5P=(A3+A7)/2+(-G3+2G5-G7)/2
	     A5A=(A1+A3+A7+A9)/4+(-G1-G3+4G5-G7-G9)/4
	     
	     IF (DN<DP)
	         THEN A5=A5N
	         ELSEIF DP < DN
	                   THEN A5=A5P
	                   ELSE A5=A5A

	     */
            /*
            DN= ABS(-G1+2*G5-G9) + ABS(A1-A9);
            DP= ABS(-G3+2*G5-G7) + ABS(A3-A7);

            A5N=(A1+A9)/2+(-G1+2*G5-G9)/2;
            A5P=(A3+A7)/2+(-G3+2*G5-G7)/2;
            A5A=(A1+A3+A7+A9)/4+(-G1-G3+4G5-G7-G9)/8;
            */

            /*
            1) Compute A1mA9=(A1-A9) & A1pA9=(A1+A9) using (Vsrc1, Vsrc2).addsub(); // 1/16 cyc/pixel
            2) Compute A3mA7=(A3-A7) & A3pA7=(G2+G8) using (Vsrc1, Vsrc2).addsub(); // 1/16 cyc/pixel
            */
            (A1pA9,A1mA9)= (A1, A9).addsub();
            (A3pA7,A3mA7)= (A3, A7).addsub();

            /*
            3) Compute abdiffA1mA9=|A1-A9| // 1/16 cyc/pixel
            4) Compute abdiffA3mA7=|A3-A7| // 1/16 cyc/pixel
            */
            abdiffA1mA9= abs(A1mA9);
            abdiffA3mA7= abs(A3mA7);
            
            /*
            5) Compute DNgreen=-G1+2G5-G9= (G5<<1)-G1-G9)= 1/16 + 1/16 + 1/16= 3/16
            6) Compute DPgreen=-G3+2G5-G7= (G5<<1)-G3-G7)= 0 + 1/16 + 1/16= 2/16 // note that (A5<<1) is already computed in previously step
            */
            DNgreen= G5 - G1;
            DPgreen= G5 - G3;

            DNgreen= G5 - G9 + DNgreen;
            DPgreen= G5 - G7 + DPgreen;

            /*
            7) Compute abdiffDNgreen= |-G1+2*G5-G9| // 1/16 cyc/pixel
            8) Compute abdiffDPgreen= |-G3+2*G5-G7| // 1/16 cyc/pixel 
            */
            abdiffDNgreen= abs(DNgreen);
            abdiffDPgreen= abs(DPgreen);

            /*
            9) Compute DN= abdiffDNgreen +  abdiffA1mA9 // 1/16 cyc/pixel
            10) Compute DP= abdiffDPgreen +  abdiffA3mA7 // 1/16 cyc/pixel
            */
            DN= abdiffDNgreen + abdiffA1mA9;
            DP= abdiffDPgreen + abdiffA3mA7;
            
            /*
            11) Compute A5N= A1pA9>>1 + DNgreen>>2 // 1/16 + 1/16 + 1/16= 3/16
            12) Compute A5P= A3pA7>>1 + DPgreen>>2 // 1/16 + 1/16 + 1/16= 3/16
            */
            A1pA9_div2= A1pA9<<Vone;
            A3pA7_div2= A3pA7<<Vone;
            
            DNgreen_div2= DNgreen<<Vone;
            DPgreen_div2= DPgreen<<Vone;

            A5N= A1pA9_div2+ DNgreen_div2;
            A5P= A3pA7_div2 + DPgreen_div2;

            /*
            13) Compute A5A= (A1+A3+A7+A9)>>2 + (DNgreen + DPgreen)>>2 // 1/16 + 1/16 + 1/16 + 1/16= 4/16
            14) Compute flagH= (DN<DP) // 1/16
            */
            A5A= A1pA9 + A3pA7;
            A5A_tmp= DNgreen + DPgreen;

            A5A= A5A << Vtwo;
            A5A_tmp= A5A_tmp << Vtwo;

            A5A= A5A + A5A_tmp;
            flagN= (DN < DP);

            /*
            15) Compute flagEq= (DN=DP) // 1/16
            16) Compute A5=A5N using A5= select(flagN, A5N, A5P) // 1/16
            */
            flagEq= (DN==DP);
            A5P= select(flagN, A5N, A5P);
            
            /*
            17) Compute A5=A5A using A5= select(flagEq, A5A, A5) // 1/16
            */
            A5P= select(flagEq, A5A, A5P);

            (pBbuff + ELEMSZ_OUT)[outputAddr].skip()= A5P;

			}
		}

/* Process R color 

    To compute Red

    We remap the naming convention

    C32 G33 C34
    G42 C43 G44
    C52 G53 C54

    to:

    A1 G2 A3
    G4 C5 G6
    A7 G8 A9

    to produce:
         A2 A3
         A5 A6

    which maps back to:
         C33 C34
         C43 C44

    column nearest neighbour: A6= (A3+A9)/2 + (-G3+2G6-G9)/2
    row nearest neighbour: A2= (A1+A3)/2 + (-G1+2G2-G3)/2

    Diagonal:
    DN=|-G1+2G5-G9|+|A1-A9|
    DP=|-G3+2G5-G7|+|A3-A7|
    A5N=(A1+A9)/2+(-G1+2G5-G9)/2
    A5P=(A3+A7)/2+(-G3+2G5-G7)/2
    A5A=(A1+A3+A7+A9)/4+(-G1-G3+4G5-G7-G9)/4

    IF (DN<DP)
        THEN A5=A5N
        ELSEIF DP < DN
                  THEN A5=A5P
                  ELSE A5=A5A
*/
              
	/* Process R color A2, A3 and A6 */

    for (int h=0; h < blkHeight/2; h++) {
        for (int w=0; w < ALIGN_SIMD(blkWidth/2)/VCOP_SIMD_WIDTH; w++) {
            __agen inputAddr= h*2*input_stride*ELEMSZ_IN + w*VCOP_2SIMD_WIDTH*ELEMSZ_IN;
            __agen inputGaddr= h*2*outputG_stride*ELEMSZ_OUT + w*VCOP_2SIMD_WIDTH*ELEMSZ_OUT;
            __agen outputAddr= h*2*outputRB_stride*ELEMSZ_OUT + w*VCOP_2SIMD_WIDTH*ELEMSZ_OUT;
                            
            __vector A1, A9, A3, A7, A6, A2;
            __vector G1, G2, G3, G6, G9;
            __vector A6_tmp, A2_tmp;

		/*
	        A1= (pInBuff - 1)[(2*h+3)*input_stride + 2*w + 3];  coincide with C32 notation used during green processing 
        	A3= (pInBuff - 1)[(2*h+3)*input_stride + 2*w + 5];  coincide with C34 notation used during green processing 
        	A7= (pInBuff - 1)[(2*h+5)*input_stride + 2*w + 3];  coincide with C52 notation used during green processing
        	A9= (pInBuff - 1)[(2*h+5)*input_stride + 2*w + 5];  coincide with C54 notation used during green processing
        
        	G1= (pGbuff - 1)[(2*h+1)*outputG_stride + 2*w + 1]; coincide with G32 notation used during green processing
        	G3= (pGbuff - 1)[(2*h+1)*outputG_stride + 2*w + 3]; coincide with G34 notation used during green processing
        	G5= (pGbuff - 1)[(2*h+2)*outputG_stride + 2*w + 2]; coincide with G43 notation used during green processing
        	G6= (pGbuff - 1)[(2*h+2)*outputG_stride + 2*w + 3]; coincide with G44 notation used during green processing
        	G7= (pGbuff - 1)[(2*h+3)*outputG_stride + 2*w + 1]; coincide with G52 notation used during green processing
        	G8= (pGbuff - 1)[(2*h+3)*outputG_stride + 2*w + 2]; coincide with G53 notation used during green processing
        	G9= (pGbuff - 1)[(2*h+3)*outputG_stride + 2*w + 3]; coincide with G54 notation used during green processing
        */
            A3= (pInBuff + (3)*input_stride*ELEMSZ_IN + (-1 + 5)*ELEMSZ_IN)[inputAddr].ds2();
            A1= (pInBuff + (3)*input_stride*ELEMSZ_IN + (-1 + 3)*ELEMSZ_IN)[inputAddr].ds2();
            A9= (pInBuff + (5)*input_stride*ELEMSZ_IN + (-1 + 5)*ELEMSZ_IN)[inputAddr].ds2();

            G3= (pGbuff + (1)*outputG_stride*ELEMSZ_OUT + (-1 + 3)*ELEMSZ_OUT)[inputGaddr].ds2();            
            G6= (pGbuff + (2)*outputG_stride*ELEMSZ_OUT + (-1 + 3)*ELEMSZ_OUT)[inputGaddr].ds2();
            G1= (pGbuff + (1)*outputG_stride*ELEMSZ_OUT + (-1 + 1)*ELEMSZ_OUT)[inputGaddr].ds2();
            G2= (pGbuff + (1)*outputG_stride*ELEMSZ_OUT + (-1 + 1 + 1)*ELEMSZ_OUT)[inputGaddr].ds2();
			G9= (pGbuff + (3)*outputG_stride*ELEMSZ_OUT + (-1 + 3)*ELEMSZ_OUT)[inputGaddr].ds2();

            /*
		     column nearest neighbour: A6= (A3+A9)/2 + (-G3+2G6-G9)/2
		     row nearest neighbour: A8= (A7+A9)/2 + (-G7+2G8-G9)/2
            */
			A6= A3 + A9;
			A2= A3 + A1;
			
			A6= A6 << Vone;
			A2= A2 << Vone;

			A6_tmp= G6 - G9;
			A2_tmp= G2 - G1;
			
			A6_tmp= G6 - G3 + A6_tmp;
			A2_tmp= G2 - G3 + A2_tmp;

			A6_tmp= A6_tmp << Vone;
			A2_tmp= A2_tmp << Vone;		

			A6= A6 + A6_tmp;
			A2= A2 + A2_tmp;

			/*
        	pRbuff[2*h*outputRB_stride + 2*w + 1]= A3;
        	pRbuff[(2*h+1)*outputRB_stride + 2*w+1]= A6;
        	pRbuff[2*h*outputRB_stride + 2*w]= A2;
        	*/

			(pRbuff + ELEMSZ_OUT)[outputAddr].skip()= A3;
			(pRbuff + outputRB_stride*ELEMSZ_OUT + ELEMSZ_OUT)[outputAddr].skip()= A6;
			(pRbuff)[outputAddr].skip()= A2;
			(pScratch)[outputAddr].skip()= G1;
			(pScratch + ELEMSZ_OUT)[outputAddr].skip()= G3;
			}
		}

	/* Process R color A5 */


    for (int h=0; h < blkHeight/2; h++) {
        for (int w=0; w < ALIGN_SIMD(blkWidth/2)/VCOP_SIMD_WIDTH; w++) {
            __agen inputAddr= h*2*input_stride*ELEMSZ_IN + w*VCOP_2SIMD_WIDTH*ELEMSZ_IN;
            __agen inputGaddr= h*2*outputG_stride*ELEMSZ_OUT + w*VCOP_2SIMD_WIDTH*ELEMSZ_OUT;
            __agen outputAddr= h*2*outputRB_stride*ELEMSZ_OUT + w*VCOP_2SIMD_WIDTH*ELEMSZ_OUT;
                            
            __vector A1, A3, A7, A9;
            __vector G1, G3, G5, G7, G9;
            __vector A1pA9, A1mA9, A3pA7,A3mA7;
            __vector DN, DP, A5N, A5P, A5A, A5A_tmp;
            __vector DNgreen, DPgreen, abdiffA1mA9, abdiffA3mA7, abdiffDNgreen, abdiffDPgreen, A1pA9_div2, A3pA7_div2, DNgreen_div2, DPgreen_div2;
            __vector flagN, flagEq;
            
		/*
	        A1= (pInBuff - 1)[(2*h+3)*input_stride + 2*w + 3];  coincide with C32 notation used during green processing 
        	A3= (pInBuff - 1)[(2*h+3)*input_stride + 2*w + 5];  coincide with C34 notation used during green processing 
        	A7= (pInBuff - 1)[(2*h+5)*input_stride + 2*w + 3];  coincide with C52 notation used during green processing
        	A9= (pInBuff - 1)[(2*h+5)*input_stride + 2*w + 5];  coincide with C54 notation used during green processing
        
        	G1= (pGbuff - 1)[(2*h+1)*outputG_stride + 2*w + 1]; coincide with G32 notation used during green processing
        	G3= (pGbuff - 1)[(2*h+1)*outputG_stride + 2*w + 3]; coincide with G34 notation used during green processing
        	G5= (pGbuff - 1)[(2*h+2)*outputG_stride + 2*w + 2]; coincide with G43 notation used during green processing
        	G6= (pGbuff - 1)[(2*h+2)*outputG_stride + 2*w + 3]; coincide with G44 notation used during green processing
        	G7= (pGbuff - 1)[(2*h+3)*outputG_stride + 2*w + 1]; coincide with G52 notation used during green processing
        	G8= (pGbuff - 1)[(2*h+3)*outputG_stride + 2*w + 2]; coincide with G53 notation used during green processing
        	G9= (pGbuff - 1)[(2*h+3)*outputG_stride + 2*w + 3]; coincide with G54 notation used during green processing
        */
            A1= (pInBuff + (3)*input_stride*ELEMSZ_IN + (-1 + 3)*ELEMSZ_IN)[inputAddr].ds2();
            A3= (pInBuff + (3)*input_stride*ELEMSZ_IN + (-1 + 5)*ELEMSZ_IN)[inputAddr].ds2();
            A7= (pInBuff + (5)*input_stride*ELEMSZ_IN + (-1 + 3)*ELEMSZ_IN)[inputAddr].ds2();
            A9= (pInBuff + (5)*input_stride*ELEMSZ_IN + (-1 + 5)*ELEMSZ_IN)[inputAddr].ds2();

            G7= (pGbuff + (3)*outputG_stride*ELEMSZ_OUT + (-1 + 1)*ELEMSZ_OUT)[inputGaddr].ds2();
            G9= (pGbuff + (3)*outputG_stride*ELEMSZ_OUT + (-1 + 3)*ELEMSZ_OUT)[inputGaddr].ds2();
            G5= (pGbuff + (2)*outputG_stride*ELEMSZ_OUT + (-1 + 2)*ELEMSZ_OUT)[inputGaddr].ds2();
            (G1, G3)= (pScratch)[outputAddr].deinterleave();


		/*
	     Diagonal:
	     DN=|-G1+2G5-G9|+|A1-A9|
	     DP=|-G3+2G5-G7|+|A3-A7|
	     A5N=(A1+A9)/2+(-G1+2G5-G9)/2
	     A5P=(A3+A7)/2+(-G3+2G5-G7)/2
	     A5A=(A1+A3+A7+A9)/4+(-G1-G3+4G5-G7-G9)/4
	     
	     IF (DN<DP)
	         THEN A5=A5N
	         ELSEIF DP < DN
	                   THEN A5=A5P
	                   ELSE A5=A5A

	     */
            /*
            DN= ABS(-G1+2*G5-G9) + ABS(A1-A9);
            DP= ABS(-G3+2*G5-G7) + ABS(A3-A7);

            A5N=(A1+A9)/2+(-G1+2*G5-G9)/2;
            A5P=(A3+A7)/2+(-G3+2*G5-G7)/2;
            A5A=(A1+A3+A7+A9)/4+(-G1-G3+4G5-G7-G9)/8;
            */

            /*
            1) Compute A1mA9=(A1-A9) & A1pA9=(A1+A9) using (Vsrc1, Vsrc2).addsub(); // 1/16 cyc/pixel
            2) Compute A3mA7=(A3-A7) & A3pA7=(G2+G8) using (Vsrc1, Vsrc2).addsub(); // 1/16 cyc/pixel
            */
            (A1pA9,A1mA9)= (A1, A9).addsub();
            (A3pA7,A3mA7)= (A3, A7).addsub();

            /*
            3) Compute abdiffA1mA9=|A1-A9| // 1/16 cyc/pixel
            4) Compute abdiffA3mA7=|A3-A7| // 1/16 cyc/pixel
            */
            abdiffA1mA9= abs(A1mA9);
            abdiffA3mA7= abs(A3mA7);
            
            /*
            5) Compute DNgreen=-G1+2G5-G9= (G5<<1)-G1-G9)= 1/16 + 1/16 + 1/16= 3/16
            6) Compute DPgreen=-G3+2G5-G7= (G5<<1)-G3-G7)= 0 + 1/16 + 1/16= 2/16 // note that (A5<<1) is already computed in previously step
            */
            DNgreen= G5 - G1;
            DPgreen= G5 - G3;

            DNgreen= G5 - G9 + DNgreen;
            DPgreen= G5 - G7 + DPgreen;

            /*
            7) Compute abdiffDNgreen= |-G1+2*G5-G9| // 1/16 cyc/pixel
            8) Compute abdiffDPgreen= |-G3+2*G5-G7| // 1/16 cyc/pixel 
            */
            abdiffDNgreen= abs(DNgreen);
            abdiffDPgreen= abs(DPgreen);

            /*
            9) Compute DN= abdiffDNgreen +  abdiffA1mA9 // 1/16 cyc/pixel
            10) Compute DP= abdiffDPgreen +  abdiffA3mA7 // 1/16 cyc/pixel
            */
            DN= abdiffDNgreen + abdiffA1mA9;
            DP= abdiffDPgreen + abdiffA3mA7;
            
            /*
            11) Compute A5N= A1pA9>>1 + DNgreen>>2 // 1/16 + 1/16 + 1/16= 3/16
            12) Compute A5P= A3pA7>>1 + DPgreen>>2 // 1/16 + 1/16 + 1/16= 3/16
            */
            A1pA9_div2= A1pA9<<Vone;
            A3pA7_div2= A3pA7<<Vone;
            
            DNgreen_div2= DNgreen<<Vone;
            DPgreen_div2= DPgreen<<Vone;

            A5N= A1pA9_div2+ DNgreen_div2;
            A5P= A3pA7_div2 + DPgreen_div2;

            /*
            13) Compute A5A= (A1+A3+A7+A9)>>2 + (DNgreen + DPgreen)>>2 // 1/16 + 1/16 + 1/16 + 1/16= 4/16
            14) Compute flagH= (DN<DP) // 1/16
            */
            A5A= A1pA9 + A3pA7;
            A5A_tmp= DNgreen + DPgreen;

            A5A= A5A << Vtwo;
            A5A_tmp= A5A_tmp << Vtwo;

            A5A= A5A + A5A_tmp;
            flagN= (DN < DP);

            /*
            15) Compute flagEq= (DN=DP) // 1/16
            16) Compute A5=A5N using A5= select(flagN, A5N, A5P) // 1/16
            */
            flagEq= (DN==DP);
            A5P= select(flagN, A5N, A5P);
            
            /*
            17) Compute A5=A5A using A5= select(flagEq, A5A, A5) // 1/16
            */
            A5P= select(flagEq, A5A, A5P);

            (pRbuff + outputRB_stride*ELEMSZ_OUT)[outputAddr].skip()= A5P;

			}
		}
}


