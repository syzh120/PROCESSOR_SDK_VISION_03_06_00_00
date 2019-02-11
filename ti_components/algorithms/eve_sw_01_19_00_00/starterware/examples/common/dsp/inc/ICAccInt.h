/*
*
* Copyright (c) 2005-2017 Texas Instruments Incorporated
*
* All rights reserved not granted herein.
*
* Limited License.
*
* Texas Instruments Incorporated grants a world-wide, royalty-free, non-exclusive
* license under copyrights and patents it now or hereafter owns or controls to make,
* have made, use, import, offer to sell and sell ("Utilize") this software subject to the
* terms herein.  With respect to the foregoing patent license, such license is granted
* solely to the extent that any such patent is necessary to Utilize the software alone.
* The patent license shall not apply to any combinations which include this software,
* other than combinations with devices manufactured by or for TI ("TI Devices").
* No hardware patent is licensed hereunder.
*
* Redistributions must preserve existing copyright notices and reproduce this license
* (including the above copyright notice and the disclaimer and (if applicable) source
* code license limitations below) in the documentation and/or other materials provided
* with the distribution
*
* Redistribution and use in binary form, without modification, are permitted provided
* that the following conditions are met:
*
* *       No reverse engineering, decompilation, or disassembly of this software is
* permitted with respect to any software provided in binary form.
*
* *       any redistribution and use are licensed by TI for use only with TI Devices.
*
* *       Nothing shall obligate TI to provide you with source code for the software
* licensed and provided to you in object code.
*
* If software source code is provided to you, modification and redistribution of the
* source code are permitted provided that the following conditions are met:
*
* *       any redistribution and use of the source code, including any resulting derivative
* works, are licensed by TI for use only with TI Devices.
*
* *       any redistribution and use of any object code compiled from the source code
* and any resulting derivative works, are licensed by TI for use only with TI Devices.
*
* Neither the name of Texas Instruments Incorporated nor the names of its suppliers
*
* may be used to endorse or promote products derived from this software without
* specific prior written permission.
*
* DISCLAIMER.
*
* THIS SOFTWARE IS PROVIDED BY TI AND TI'S LICENSORS "AS IS" AND ANY EXPRESS
* OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
* OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
* IN NO EVENT SHALL TI AND TI'S LICENSORS BE LIABLE FOR ANY DIRECT, INDIRECT,
* INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
* BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
* DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY
* OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
* OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
* OF THE POSSIBILITY OF SUCH DAMAGE.
*
*/


#ifndef _IC_ACC_INT_H
#define _IC_ACC_INT_H

#if defined(__cplusplus)
extern "C" {
#endif  /* defined(__cplusplus) */


/*****************************************************************************
* EXPORTED DEFINITIONS
******************************************************************************
*/



/* Register set InterruptController address offset, bank address increment and number of banks */

#define IC_InterruptController_OFFSET                                           (UWORD32)(0x0u)                                                                 
#define IC_InterruptController_STEP                                             (UWORD32)(0x200u)                                                               
#define IC_InterruptController_BANKS                                            (UWORD32)(1)                                                                    

/* Register offset address definitions relative to register set InterruptController */

#define IC_EVTFLAG0_OFFSET                                                      (UWORD32)(0x0u)                                                                 
#define IC_EVTFLAG1_OFFSET                                                      (UWORD32)(0x4u)                                                                 
#define IC_EVTFLAG2_OFFSET                                                      (UWORD32)(0x8u)                                                                 
#define IC_EVTFLAG3_OFFSET                                                      (UWORD32)(0xcu)                                                                 
#define IC_EVTSET0_OFFSET                                                       (UWORD32)(0x20u)                                                                
#define IC_EVTSET1_OFFSET                                                       (UWORD32)(0x24u)                                                                
#define IC_EVTSET2_OFFSET                                                       (UWORD32)(0x28u)                                                                
#define IC_EVTSET3_OFFSET                                                       (UWORD32)(0x2cu)                                                                
#define IC_EVTCLR0_OFFSET                                                       (UWORD32)(0x40u)                                                                
#define IC_EVTCLR1_OFFSET                                                       (UWORD32)(0x44u)                                                                
#define IC_EVTCLR2_OFFSET                                                       (UWORD32)(0x48u)                                                                
#define IC_EVTCLR3_OFFSET                                                       (UWORD32)(0x4cu)                                                                
#define IC_EVTMASK0_OFFSET                                                      (UWORD32)(0x80u)                                                                
#define IC_EVTMASK1_OFFSET                                                      (UWORD32)(0x84u)                                                                
#define IC_EVTMASK2_OFFSET                                                      (UWORD32)(0x88u)                                                                
#define IC_EVTMASK3_OFFSET                                                      (UWORD32)(0x8cu)                                                                
#define IC_MEVTFLAG0_OFFSET                                                     (UWORD32)(0xa0u)                                                                
#define IC_MEVTFLAG1_OFFSET                                                     (UWORD32)(0xa4u)                                                                
#define IC_MEVTFLAG2_OFFSET                                                     (UWORD32)(0xa8u)                                                                
#define IC_MEVTFLAG3_OFFSET                                                     (UWORD32)(0xacu)                                                                
#define IC_EXPMASK0_OFFSET                                                      (UWORD32)(0xc0u)                                                                
#define IC_EXPMASK1_OFFSET                                                      (UWORD32)(0xc4u)                                                                
#define IC_EXPMASK2_OFFSET                                                      (UWORD32)(0xc8u)                                                                
#define IC_EXPMASK3_OFFSET                                                      (UWORD32)(0xccu)                                                                
#define IC_MEXPFLAG0_OFFSET                                                     (UWORD32)(0xe0u)                                                                
#define IC_MEXPFLAG1_OFFSET                                                     (UWORD32)(0xe4u)                                                                
#define IC_MEXPFLAG2_OFFSET                                                     (UWORD32)(0xe8u)                                                                
#define IC_MEXPFLAG3_OFFSET                                                     (UWORD32)(0xecu)                                                                
#define IC_INTMUX1_OFFSET                                                       (UWORD32)(0x104u)                                                               
#define IC_INTMUX2_OFFSET                                                       (UWORD32)(0x108u)                                                               
#define IC_INTMUX3_OFFSET                                                       (UWORD32)(0x10cu)                                                               
#define IC_AEGMUX0_OFFSET                                                       (UWORD32)(0x140u)                                                               
#define IC_AEGMUX1_OFFSET                                                       (UWORD32)(0x144u)                                                               
#define IC_INTXSTAT_OFFSET                                                      (UWORD32)(0x180u)                                                               
#define IC_INTXCLR_OFFSET                                                       (UWORD32)(0x184u)                                                               
#define IC_INTDMASK_OFFSET                                                      (UWORD32)(0x188u)                                                               
#define IC_EVTASRT_OFFSET                                                       (UWORD32)(0x1c0u)                                                               


/* Bitfield mask and offset declarations */

#define IC_EVTFLAG0_EF0_MASK                                                    (UWORD32)(0x1u)                                                                 
#define IC_EVTFLAG0_EF0_OFFSET                                                  (UWORD8)(0)                                                                     

#define IC_EVTFLAG0_EF1_MASK                                                    (UWORD32)(0x2u)                                                                 
#define IC_EVTFLAG0_EF1_OFFSET                                                  (UWORD8)(1)                                                                     

#define IC_EVTFLAG0_EF2_MASK                                                    (UWORD32)(0x4u)                                                                 
#define IC_EVTFLAG0_EF2_OFFSET                                                  (UWORD8)(2)                                                                     

#define IC_EVTFLAG0_EF3_MASK                                                    (UWORD32)(0x8u)                                                                 
#define IC_EVTFLAG0_EF3_OFFSET                                                  (UWORD8)(3)                                                                     

#define IC_EVTFLAG0_EF4_MASK                                                    (UWORD32)(0x10u)                                                                
#define IC_EVTFLAG0_EF4_OFFSET                                                  (UWORD8)(4)                                                                     

#define IC_EVTFLAG0_EF5_MASK                                                    (UWORD32)(0x20u)                                                                
#define IC_EVTFLAG0_EF5_OFFSET                                                  (UWORD8)(5)                                                                     

#define IC_EVTFLAG0_EF6_MASK                                                    (UWORD32)(0x40u)                                                                
#define IC_EVTFLAG0_EF6_OFFSET                                                  (UWORD8)(6)                                                                     

#define IC_EVTFLAG0_EF7_MASK                                                    (UWORD32)(0x80u)                                                                
#define IC_EVTFLAG0_EF7_OFFSET                                                  (UWORD8)(7)                                                                     

#define IC_EVTFLAG0_EF8_MASK                                                    (UWORD32)(0x100u)                                                               
#define IC_EVTFLAG0_EF8_OFFSET                                                  (UWORD8)(8)                                                                     

#define IC_EVTFLAG0_EF9_MASK                                                    (UWORD32)(0x200u)                                                               
#define IC_EVTFLAG0_EF9_OFFSET                                                  (UWORD8)(9)                                                                     

#define IC_EVTFLAG0_EF10_MASK                                                   (UWORD32)(0x400u)                                                               
#define IC_EVTFLAG0_EF10_OFFSET                                                 (UWORD8)(10)                                                                    

#define IC_EVTFLAG0_EF11_MASK                                                   (UWORD32)(0x800u)                                                               
#define IC_EVTFLAG0_EF11_OFFSET                                                 (UWORD8)(11)                                                                    

#define IC_EVTFLAG0_EF12_MASK                                                   (UWORD32)(0x1000u)                                                              
#define IC_EVTFLAG0_EF12_OFFSET                                                 (UWORD8)(12)                                                                    

#define IC_EVTFLAG0_EF13_MASK                                                   (UWORD32)(0x2000u)                                                              
#define IC_EVTFLAG0_EF13_OFFSET                                                 (UWORD8)(13)                                                                    

#define IC_EVTFLAG0_EF14_MASK                                                   (UWORD32)(0x4000u)                                                              
#define IC_EVTFLAG0_EF14_OFFSET                                                 (UWORD8)(14)                                                                    

#define IC_EVTFLAG0_EF15_MASK                                                   (UWORD32)(0x8000u)                                                              
#define IC_EVTFLAG0_EF15_OFFSET                                                 (UWORD8)(15)                                                                    

#define IC_EVTFLAG0_EF16_MASK                                                   (UWORD32)(0x10000u)                                                             
#define IC_EVTFLAG0_EF16_OFFSET                                                 (UWORD8)(16)                                                                    

#define IC_EVTFLAG0_EF17_MASK                                                   (UWORD32)(0x20000u)                                                             
#define IC_EVTFLAG0_EF17_OFFSET                                                 (UWORD8)(17)                                                                    

#define IC_EVTFLAG0_EF18_MASK                                                   (UWORD32)(0x40000u)                                                             
#define IC_EVTFLAG0_EF18_OFFSET                                                 (UWORD8)(18)                                                                    

#define IC_EVTFLAG0_EF19_MASK                                                   (UWORD32)(0x80000u)                                                             
#define IC_EVTFLAG0_EF19_OFFSET                                                 (UWORD8)(19)                                                                    

#define IC_EVTFLAG0_EF20_MASK                                                   (UWORD32)(0x100000u)                                                            
#define IC_EVTFLAG0_EF20_OFFSET                                                 (UWORD8)(20)                                                                    

#define IC_EVTFLAG0_EF21_MASK                                                   (UWORD32)(0x200000u)                                                            
#define IC_EVTFLAG0_EF21_OFFSET                                                 (UWORD8)(21)                                                                    

#define IC_EVTFLAG0_EF22_MASK                                                   (UWORD32)(0x400000u)                                                            
#define IC_EVTFLAG0_EF22_OFFSET                                                 (UWORD8)(22)                                                                    

#define IC_EVTFLAG0_EF23_MASK                                                   (UWORD32)(0x800000u)                                                            
#define IC_EVTFLAG0_EF23_OFFSET                                                 (UWORD8)(23)                                                                    

#define IC_EVTFLAG0_EF24_MASK                                                   (UWORD32)(0x1000000u)                                                           
#define IC_EVTFLAG0_EF24_OFFSET                                                 (UWORD8)(24)                                                                    

#define IC_EVTFLAG0_EF25_MASK                                                   (UWORD32)(0x2000000u)                                                           
#define IC_EVTFLAG0_EF25_OFFSET                                                 (UWORD8)(25)                                                                    

#define IC_EVTFLAG0_EF26_MASK                                                   (UWORD32)(0x4000000u)                                                           
#define IC_EVTFLAG0_EF26_OFFSET                                                 (UWORD8)(26)                                                                    

#define IC_EVTFLAG0_EF27_MASK                                                   (UWORD32)(0x8000000u)                                                           
#define IC_EVTFLAG0_EF27_OFFSET                                                 (UWORD8)(27)                                                                    

#define IC_EVTFLAG0_EF28_MASK                                                   (UWORD32)(0x10000000u)                                                          
#define IC_EVTFLAG0_EF28_OFFSET                                                 (UWORD8)(28)                                                                    

#define IC_EVTFLAG0_EF29_MASK                                                   (UWORD32)(0x20000000u)                                                          
#define IC_EVTFLAG0_EF29_OFFSET                                                 (UWORD8)(29)                                                                    

#define IC_EVTFLAG0_EF30_MASK                                                   (UWORD32)(0x40000000u)                                                          
#define IC_EVTFLAG0_EF30_OFFSET                                                 (UWORD8)(30)                                                                    

#define IC_EVTFLAG0_EF31_MASK                                                   (UWORD32)(0x80000000u)                                                          
#define IC_EVTFLAG0_EF31_OFFSET                                                 (UWORD8)(31)                                                                    

#define IC_EVTFLAG1_EF0_MASK                                                    (UWORD32)(0x1u)                                                                 
#define IC_EVTFLAG1_EF0_OFFSET                                                  (UWORD8)(0)                                                                     

#define IC_EVTFLAG1_EF1_MASK                                                    (UWORD32)(0x2u)                                                                 
#define IC_EVTFLAG1_EF1_OFFSET                                                  (UWORD8)(1)                                                                     

#define IC_EVTFLAG1_EF2_MASK                                                    (UWORD32)(0x4u)                                                                 
#define IC_EVTFLAG1_EF2_OFFSET                                                  (UWORD8)(2)                                                                     

#define IC_EVTFLAG1_EF3_MASK                                                    (UWORD32)(0x8u)                                                                 
#define IC_EVTFLAG1_EF3_OFFSET                                                  (UWORD8)(3)                                                                     

#define IC_EVTFLAG1_EF4_MASK                                                    (UWORD32)(0x10u)                                                                
#define IC_EVTFLAG1_EF4_OFFSET                                                  (UWORD8)(4)                                                                     

#define IC_EVTFLAG1_EF5_MASK                                                    (UWORD32)(0x20u)                                                                
#define IC_EVTFLAG1_EF5_OFFSET                                                  (UWORD8)(5)                                                                     

#define IC_EVTFLAG1_EF6_MASK                                                    (UWORD32)(0x40u)                                                                
#define IC_EVTFLAG1_EF6_OFFSET                                                  (UWORD8)(6)                                                                     

#define IC_EVTFLAG1_EF7_MASK                                                    (UWORD32)(0x80u)                                                                
#define IC_EVTFLAG1_EF7_OFFSET                                                  (UWORD8)(7)                                                                     

#define IC_EVTFLAG1_EF8_MASK                                                    (UWORD32)(0x100u)                                                               
#define IC_EVTFLAG1_EF8_OFFSET                                                  (UWORD8)(8)                                                                     

#define IC_EVTFLAG1_EF9_MASK                                                    (UWORD32)(0x200u)                                                               
#define IC_EVTFLAG1_EF9_OFFSET                                                  (UWORD8)(9)                                                                     

#define IC_EVTFLAG1_EF10_MASK                                                   (UWORD32)(0x400u)                                                               
#define IC_EVTFLAG1_EF10_OFFSET                                                 (UWORD8)(10)                                                                    

#define IC_EVTFLAG1_EF11_MASK                                                   (UWORD32)(0x800u)                                                               
#define IC_EVTFLAG1_EF11_OFFSET                                                 (UWORD8)(11)                                                                    

#define IC_EVTFLAG1_EF12_MASK                                                   (UWORD32)(0x1000u)                                                              
#define IC_EVTFLAG1_EF12_OFFSET                                                 (UWORD8)(12)                                                                    

#define IC_EVTFLAG1_EF13_MASK                                                   (UWORD32)(0x2000u)                                                              
#define IC_EVTFLAG1_EF13_OFFSET                                                 (UWORD8)(13)                                                                    

#define IC_EVTFLAG1_EF14_MASK                                                   (UWORD32)(0x4000u)                                                              
#define IC_EVTFLAG1_EF14_OFFSET                                                 (UWORD8)(14)                                                                    

#define IC_EVTFLAG1_EF15_MASK                                                   (UWORD32)(0x8000u)                                                              
#define IC_EVTFLAG1_EF15_OFFSET                                                 (UWORD8)(15)                                                                    

#define IC_EVTFLAG1_EF16_MASK                                                   (UWORD32)(0x10000u)                                                             
#define IC_EVTFLAG1_EF16_OFFSET                                                 (UWORD8)(16)                                                                    

#define IC_EVTFLAG1_EF17_MASK                                                   (UWORD32)(0x20000u)                                                             
#define IC_EVTFLAG1_EF17_OFFSET                                                 (UWORD8)(17)                                                                    

#define IC_EVTFLAG1_EF18_MASK                                                   (UWORD32)(0x40000u)                                                             
#define IC_EVTFLAG1_EF18_OFFSET                                                 (UWORD8)(18)                                                                    

#define IC_EVTFLAG1_EF19_MASK                                                   (UWORD32)(0x80000u)                                                             
#define IC_EVTFLAG1_EF19_OFFSET                                                 (UWORD8)(19)                                                                    

#define IC_EVTFLAG1_EF20_MASK                                                   (UWORD32)(0x100000u)                                                            
#define IC_EVTFLAG1_EF20_OFFSET                                                 (UWORD8)(20)                                                                    

#define IC_EVTFLAG1_EF21_MASK                                                   (UWORD32)(0x200000u)                                                            
#define IC_EVTFLAG1_EF21_OFFSET                                                 (UWORD8)(21)                                                                    

#define IC_EVTFLAG1_EF22_MASK                                                   (UWORD32)(0x400000u)                                                            
#define IC_EVTFLAG1_EF22_OFFSET                                                 (UWORD8)(22)                                                                    

#define IC_EVTFLAG1_EF23_MASK                                                   (UWORD32)(0x800000u)                                                            
#define IC_EVTFLAG1_EF23_OFFSET                                                 (UWORD8)(23)                                                                    

#define IC_EVTFLAG1_EF24_MASK                                                   (UWORD32)(0x1000000u)                                                           
#define IC_EVTFLAG1_EF24_OFFSET                                                 (UWORD8)(24)                                                                    

#define IC_EVTFLAG1_EF25_MASK                                                   (UWORD32)(0x2000000u)                                                           
#define IC_EVTFLAG1_EF25_OFFSET                                                 (UWORD8)(25)                                                                    

#define IC_EVTFLAG1_EF26_MASK                                                   (UWORD32)(0x4000000u)                                                           
#define IC_EVTFLAG1_EF26_OFFSET                                                 (UWORD8)(26)                                                                    

#define IC_EVTFLAG1_EF27_MASK                                                   (UWORD32)(0x8000000u)                                                           
#define IC_EVTFLAG1_EF27_OFFSET                                                 (UWORD8)(27)                                                                    

#define IC_EVTFLAG1_EF28_MASK                                                   (UWORD32)(0x10000000u)                                                          
#define IC_EVTFLAG1_EF28_OFFSET                                                 (UWORD8)(28)                                                                    

#define IC_EVTFLAG1_EF29_MASK                                                   (UWORD32)(0x20000000u)                                                          
#define IC_EVTFLAG1_EF29_OFFSET                                                 (UWORD8)(29)                                                                    

#define IC_EVTFLAG1_EF30_MASK                                                   (UWORD32)(0x40000000u)                                                          
#define IC_EVTFLAG1_EF30_OFFSET                                                 (UWORD8)(30)                                                                    

#define IC_EVTFLAG1_EF31_MASK                                                   (UWORD32)(0x80000000u)                                                          
#define IC_EVTFLAG1_EF31_OFFSET                                                 (UWORD8)(31)                                                                    

#define IC_EVTFLAG2_EF0_MASK                                                    (UWORD32)(0x1u)                                                                 
#define IC_EVTFLAG2_EF0_OFFSET                                                  (UWORD8)(0)                                                                     

#define IC_EVTFLAG2_EF1_MASK                                                    (UWORD32)(0x2u)                                                                 
#define IC_EVTFLAG2_EF1_OFFSET                                                  (UWORD8)(1)                                                                     

#define IC_EVTFLAG2_EF2_MASK                                                    (UWORD32)(0x4u)                                                                 
#define IC_EVTFLAG2_EF2_OFFSET                                                  (UWORD8)(2)                                                                     

#define IC_EVTFLAG2_EF3_MASK                                                    (UWORD32)(0x8u)                                                                 
#define IC_EVTFLAG2_EF3_OFFSET                                                  (UWORD8)(3)                                                                     

#define IC_EVTFLAG2_EF4_MASK                                                    (UWORD32)(0x10u)                                                                
#define IC_EVTFLAG2_EF4_OFFSET                                                  (UWORD8)(4)                                                                     

#define IC_EVTFLAG2_EF5_MASK                                                    (UWORD32)(0x20u)                                                                
#define IC_EVTFLAG2_EF5_OFFSET                                                  (UWORD8)(5)                                                                     

#define IC_EVTFLAG2_EF6_MASK                                                    (UWORD32)(0x40u)                                                                
#define IC_EVTFLAG2_EF6_OFFSET                                                  (UWORD8)(6)                                                                     

#define IC_EVTFLAG2_EF7_MASK                                                    (UWORD32)(0x80u)                                                                
#define IC_EVTFLAG2_EF7_OFFSET                                                  (UWORD8)(7)                                                                     

#define IC_EVTFLAG2_EF8_MASK                                                    (UWORD32)(0x100u)                                                               
#define IC_EVTFLAG2_EF8_OFFSET                                                  (UWORD8)(8)                                                                     

#define IC_EVTFLAG2_EF9_MASK                                                    (UWORD32)(0x200u)                                                               
#define IC_EVTFLAG2_EF9_OFFSET                                                  (UWORD8)(9)                                                                     

#define IC_EVTFLAG2_EF10_MASK                                                   (UWORD32)(0x400u)                                                               
#define IC_EVTFLAG2_EF10_OFFSET                                                 (UWORD8)(10)                                                                    

#define IC_EVTFLAG2_EF11_MASK                                                   (UWORD32)(0x800u)                                                               
#define IC_EVTFLAG2_EF11_OFFSET                                                 (UWORD8)(11)                                                                    

#define IC_EVTFLAG2_EF12_MASK                                                   (UWORD32)(0x1000u)                                                              
#define IC_EVTFLAG2_EF12_OFFSET                                                 (UWORD8)(12)                                                                    

#define IC_EVTFLAG2_EF13_MASK                                                   (UWORD32)(0x2000u)                                                              
#define IC_EVTFLAG2_EF13_OFFSET                                                 (UWORD8)(13)                                                                    

#define IC_EVTFLAG2_EF14_MASK                                                   (UWORD32)(0x4000u)                                                              
#define IC_EVTFLAG2_EF14_OFFSET                                                 (UWORD8)(14)                                                                    

#define IC_EVTFLAG2_EF15_MASK                                                   (UWORD32)(0x8000u)                                                              
#define IC_EVTFLAG2_EF15_OFFSET                                                 (UWORD8)(15)                                                                    

#define IC_EVTFLAG2_EF16_MASK                                                   (UWORD32)(0x10000u)                                                             
#define IC_EVTFLAG2_EF16_OFFSET                                                 (UWORD8)(16)                                                                    

#define IC_EVTFLAG2_EF17_MASK                                                   (UWORD32)(0x20000u)                                                             
#define IC_EVTFLAG2_EF17_OFFSET                                                 (UWORD8)(17)                                                                    

#define IC_EVTFLAG2_EF18_MASK                                                   (UWORD32)(0x40000u)                                                             
#define IC_EVTFLAG2_EF18_OFFSET                                                 (UWORD8)(18)                                                                    

#define IC_EVTFLAG2_EF19_MASK                                                   (UWORD32)(0x80000u)                                                             
#define IC_EVTFLAG2_EF19_OFFSET                                                 (UWORD8)(19)                                                                    

#define IC_EVTFLAG2_EF20_MASK                                                   (UWORD32)(0x100000u)                                                            
#define IC_EVTFLAG2_EF20_OFFSET                                                 (UWORD8)(20)                                                                    

#define IC_EVTFLAG2_EF21_MASK                                                   (UWORD32)(0x200000u)                                                            
#define IC_EVTFLAG2_EF21_OFFSET                                                 (UWORD8)(21)                                                                    

#define IC_EVTFLAG2_EF22_MASK                                                   (UWORD32)(0x400000u)                                                            
#define IC_EVTFLAG2_EF22_OFFSET                                                 (UWORD8)(22)                                                                    

#define IC_EVTFLAG2_EF23_MASK                                                   (UWORD32)(0x800000u)                                                            
#define IC_EVTFLAG2_EF23_OFFSET                                                 (UWORD8)(23)                                                                    

#define IC_EVTFLAG2_EF24_MASK                                                   (UWORD32)(0x1000000u)                                                           
#define IC_EVTFLAG2_EF24_OFFSET                                                 (UWORD8)(24)                                                                    

#define IC_EVTFLAG2_EF25_MASK                                                   (UWORD32)(0x2000000u)                                                           
#define IC_EVTFLAG2_EF25_OFFSET                                                 (UWORD8)(25)                                                                    

#define IC_EVTFLAG2_EF26_MASK                                                   (UWORD32)(0x4000000u)                                                           
#define IC_EVTFLAG2_EF26_OFFSET                                                 (UWORD8)(26)                                                                    

#define IC_EVTFLAG2_EF27_MASK                                                   (UWORD32)(0x8000000u)                                                           
#define IC_EVTFLAG2_EF27_OFFSET                                                 (UWORD8)(27)                                                                    

#define IC_EVTFLAG2_EF28_MASK                                                   (UWORD32)(0x10000000u)                                                          
#define IC_EVTFLAG2_EF28_OFFSET                                                 (UWORD8)(28)                                                                    

#define IC_EVTFLAG2_EF29_MASK                                                   (UWORD32)(0x20000000u)                                                          
#define IC_EVTFLAG2_EF29_OFFSET                                                 (UWORD8)(29)                                                                    

#define IC_EVTFLAG2_EF30_MASK                                                   (UWORD32)(0x40000000u)                                                          
#define IC_EVTFLAG2_EF30_OFFSET                                                 (UWORD8)(30)                                                                    

#define IC_EVTFLAG2_EF31_MASK                                                   (UWORD32)(0x80000000u)                                                          
#define IC_EVTFLAG2_EF31_OFFSET                                                 (UWORD8)(31)                                                                    

#define IC_EVTFLAG3_EF0_MASK                                                    (UWORD32)(0x1u)                                                                 
#define IC_EVTFLAG3_EF0_OFFSET                                                  (UWORD8)(0)                                                                     

#define IC_EVTFLAG3_EF1_MASK                                                    (UWORD32)(0x2u)                                                                 
#define IC_EVTFLAG3_EF1_OFFSET                                                  (UWORD8)(1)                                                                     

#define IC_EVTFLAG3_EF2_MASK                                                    (UWORD32)(0x4u)                                                                 
#define IC_EVTFLAG3_EF2_OFFSET                                                  (UWORD8)(2)                                                                     

#define IC_EVTFLAG3_EF3_MASK                                                    (UWORD32)(0x8u)                                                                 
#define IC_EVTFLAG3_EF3_OFFSET                                                  (UWORD8)(3)                                                                     

#define IC_EVTFLAG3_EF4_MASK                                                    (UWORD32)(0x10u)                                                                
#define IC_EVTFLAG3_EF4_OFFSET                                                  (UWORD8)(4)                                                                     

#define IC_EVTFLAG3_EF5_MASK                                                    (UWORD32)(0x20u)                                                                
#define IC_EVTFLAG3_EF5_OFFSET                                                  (UWORD8)(5)                                                                     

#define IC_EVTFLAG3_EF6_MASK                                                    (UWORD32)(0x40u)                                                                
#define IC_EVTFLAG3_EF6_OFFSET                                                  (UWORD8)(6)                                                                     

#define IC_EVTFLAG3_EF7_MASK                                                    (UWORD32)(0x80u)                                                                
#define IC_EVTFLAG3_EF7_OFFSET                                                  (UWORD8)(7)                                                                     

#define IC_EVTFLAG3_EF8_MASK                                                    (UWORD32)(0x100u)                                                               
#define IC_EVTFLAG3_EF8_OFFSET                                                  (UWORD8)(8)                                                                     

#define IC_EVTFLAG3_EF9_MASK                                                    (UWORD32)(0x200u)                                                               
#define IC_EVTFLAG3_EF9_OFFSET                                                  (UWORD8)(9)                                                                     

#define IC_EVTFLAG3_EF10_MASK                                                   (UWORD32)(0x400u)                                                               
#define IC_EVTFLAG3_EF10_OFFSET                                                 (UWORD8)(10)                                                                    

#define IC_EVTFLAG3_EF11_MASK                                                   (UWORD32)(0x800u)                                                               
#define IC_EVTFLAG3_EF11_OFFSET                                                 (UWORD8)(11)                                                                    

#define IC_EVTFLAG3_EF12_MASK                                                   (UWORD32)(0x1000u)                                                              
#define IC_EVTFLAG3_EF12_OFFSET                                                 (UWORD8)(12)                                                                    

#define IC_EVTFLAG3_EF13_MASK                                                   (UWORD32)(0x2000u)                                                              
#define IC_EVTFLAG3_EF13_OFFSET                                                 (UWORD8)(13)                                                                    

#define IC_EVTFLAG3_EF14_MASK                                                   (UWORD32)(0x4000u)                                                              
#define IC_EVTFLAG3_EF14_OFFSET                                                 (UWORD8)(14)                                                                    

#define IC_EVTFLAG3_EF15_MASK                                                   (UWORD32)(0x8000u)                                                              
#define IC_EVTFLAG3_EF15_OFFSET                                                 (UWORD8)(15)                                                                    

#define IC_EVTFLAG3_EF16_MASK                                                   (UWORD32)(0x10000u)                                                             
#define IC_EVTFLAG3_EF16_OFFSET                                                 (UWORD8)(16)                                                                    

#define IC_EVTFLAG3_EF17_MASK                                                   (UWORD32)(0x20000u)                                                             
#define IC_EVTFLAG3_EF17_OFFSET                                                 (UWORD8)(17)                                                                    

#define IC_EVTFLAG3_EF18_MASK                                                   (UWORD32)(0x40000u)                                                             
#define IC_EVTFLAG3_EF18_OFFSET                                                 (UWORD8)(18)                                                                    

#define IC_EVTFLAG3_EF19_MASK                                                   (UWORD32)(0x80000u)                                                             
#define IC_EVTFLAG3_EF19_OFFSET                                                 (UWORD8)(19)                                                                    

#define IC_EVTFLAG3_EF20_MASK                                                   (UWORD32)(0x100000u)                                                            
#define IC_EVTFLAG3_EF20_OFFSET                                                 (UWORD8)(20)                                                                    

#define IC_EVTFLAG3_EF21_MASK                                                   (UWORD32)(0x200000u)                                                            
#define IC_EVTFLAG3_EF21_OFFSET                                                 (UWORD8)(21)                                                                    

#define IC_EVTFLAG3_EF22_MASK                                                   (UWORD32)(0x400000u)                                                            
#define IC_EVTFLAG3_EF22_OFFSET                                                 (UWORD8)(22)                                                                    

#define IC_EVTFLAG3_EF23_MASK                                                   (UWORD32)(0x800000u)                                                            
#define IC_EVTFLAG3_EF23_OFFSET                                                 (UWORD8)(23)                                                                    

#define IC_EVTFLAG3_EF24_MASK                                                   (UWORD32)(0x1000000u)                                                           
#define IC_EVTFLAG3_EF24_OFFSET                                                 (UWORD8)(24)                                                                    

#define IC_EVTFLAG3_EF25_MASK                                                   (UWORD32)(0x2000000u)                                                           
#define IC_EVTFLAG3_EF25_OFFSET                                                 (UWORD8)(25)                                                                    

#define IC_EVTFLAG3_EF26_MASK                                                   (UWORD32)(0x4000000u)                                                           
#define IC_EVTFLAG3_EF26_OFFSET                                                 (UWORD8)(26)                                                                    

#define IC_EVTFLAG3_EF27_MASK                                                   (UWORD32)(0x8000000u)                                                           
#define IC_EVTFLAG3_EF27_OFFSET                                                 (UWORD8)(27)                                                                    

#define IC_EVTFLAG3_EF28_MASK                                                   (UWORD32)(0x10000000u)                                                          
#define IC_EVTFLAG3_EF28_OFFSET                                                 (UWORD8)(28)                                                                    

#define IC_EVTFLAG3_EF29_MASK                                                   (UWORD32)(0x20000000u)                                                          
#define IC_EVTFLAG3_EF29_OFFSET                                                 (UWORD8)(29)                                                                    

#define IC_EVTFLAG3_EF30_MASK                                                   (UWORD32)(0x40000000u)                                                          
#define IC_EVTFLAG3_EF30_OFFSET                                                 (UWORD8)(30)                                                                    

#define IC_EVTFLAG3_EF31_MASK                                                   (UWORD32)(0x80000000u)                                                          
#define IC_EVTFLAG3_EF31_OFFSET                                                 (UWORD8)(31)                                                                    

#define IC_EVTSET0_ES0_MASK                                                     (UWORD32)(0x1u)                                                                 
#define IC_EVTSET0_ES0_OFFSET                                                   (UWORD8)(0)                                                                     

#define IC_EVTSET0_ES1_MASK                                                     (UWORD32)(0x2u)                                                                 
#define IC_EVTSET0_ES1_OFFSET                                                   (UWORD8)(1)                                                                     

#define IC_EVTSET0_ES2_MASK                                                     (UWORD32)(0x4u)                                                                 
#define IC_EVTSET0_ES2_OFFSET                                                   (UWORD8)(2)                                                                     

#define IC_EVTSET0_ES3_MASK                                                     (UWORD32)(0x8u)                                                                 
#define IC_EVTSET0_ES3_OFFSET                                                   (UWORD8)(3)                                                                     

#define IC_EVTSET0_ES4_MASK                                                     (UWORD32)(0x10u)                                                                
#define IC_EVTSET0_ES4_OFFSET                                                   (UWORD8)(4)                                                                     

#define IC_EVTSET0_ES5_MASK                                                     (UWORD32)(0x20u)                                                                
#define IC_EVTSET0_ES5_OFFSET                                                   (UWORD8)(5)                                                                     

#define IC_EVTSET0_ES6_MASK                                                     (UWORD32)(0x40u)                                                                
#define IC_EVTSET0_ES6_OFFSET                                                   (UWORD8)(6)                                                                     

#define IC_EVTSET0_ES7_MASK                                                     (UWORD32)(0x80u)                                                                
#define IC_EVTSET0_ES7_OFFSET                                                   (UWORD8)(7)                                                                     

#define IC_EVTSET0_ES8_MASK                                                     (UWORD32)(0x100u)                                                               
#define IC_EVTSET0_ES8_OFFSET                                                   (UWORD8)(8)                                                                     

#define IC_EVTSET0_ES9_MASK                                                     (UWORD32)(0x200u)                                                               
#define IC_EVTSET0_ES9_OFFSET                                                   (UWORD8)(9)                                                                     

#define IC_EVTSET0_ES10_MASK                                                    (UWORD32)(0x400u)                                                               
#define IC_EVTSET0_ES10_OFFSET                                                  (UWORD8)(10)                                                                    

#define IC_EVTSET0_ES11_MASK                                                    (UWORD32)(0x800u)                                                               
#define IC_EVTSET0_ES11_OFFSET                                                  (UWORD8)(11)                                                                    

#define IC_EVTSET0_ES12_MASK                                                    (UWORD32)(0x1000u)                                                              
#define IC_EVTSET0_ES12_OFFSET                                                  (UWORD8)(12)                                                                    

#define IC_EVTSET0_ES13_MASK                                                    (UWORD32)(0x2000u)                                                              
#define IC_EVTSET0_ES13_OFFSET                                                  (UWORD8)(13)                                                                    

#define IC_EVTSET0_ES14_MASK                                                    (UWORD32)(0x4000u)                                                              
#define IC_EVTSET0_ES14_OFFSET                                                  (UWORD8)(14)                                                                    

#define IC_EVTSET0_ES15_MASK                                                    (UWORD32)(0x8000u)                                                              
#define IC_EVTSET0_ES15_OFFSET                                                  (UWORD8)(15)                                                                    

#define IC_EVTSET0_ES16_MASK                                                    (UWORD32)(0x10000u)                                                             
#define IC_EVTSET0_ES16_OFFSET                                                  (UWORD8)(16)                                                                    

#define IC_EVTSET0_ES17_MASK                                                    (UWORD32)(0x20000u)                                                             
#define IC_EVTSET0_ES17_OFFSET                                                  (UWORD8)(17)                                                                    

#define IC_EVTSET0_ES18_MASK                                                    (UWORD32)(0x40000u)                                                             
#define IC_EVTSET0_ES18_OFFSET                                                  (UWORD8)(18)                                                                    

#define IC_EVTSET0_ES19_MASK                                                    (UWORD32)(0x80000u)                                                             
#define IC_EVTSET0_ES19_OFFSET                                                  (UWORD8)(19)                                                                    

#define IC_EVTSET0_ES20_MASK                                                    (UWORD32)(0x100000u)                                                            
#define IC_EVTSET0_ES20_OFFSET                                                  (UWORD8)(20)                                                                    

#define IC_EVTSET0_ES21_MASK                                                    (UWORD32)(0x200000u)                                                            
#define IC_EVTSET0_ES21_OFFSET                                                  (UWORD8)(21)                                                                    

#define IC_EVTSET0_ES22_MASK                                                    (UWORD32)(0x400000u)                                                            
#define IC_EVTSET0_ES22_OFFSET                                                  (UWORD8)(22)                                                                    

#define IC_EVTSET0_ES23_MASK                                                    (UWORD32)(0x800000u)                                                            
#define IC_EVTSET0_ES23_OFFSET                                                  (UWORD8)(23)                                                                    

#define IC_EVTSET0_ES24_MASK                                                    (UWORD32)(0x1000000u)                                                           
#define IC_EVTSET0_ES24_OFFSET                                                  (UWORD8)(24)                                                                    

#define IC_EVTSET0_ES25_MASK                                                    (UWORD32)(0x2000000u)                                                           
#define IC_EVTSET0_ES25_OFFSET                                                  (UWORD8)(25)                                                                    

#define IC_EVTSET0_ES26_MASK                                                    (UWORD32)(0x4000000u)                                                           
#define IC_EVTSET0_ES26_OFFSET                                                  (UWORD8)(26)                                                                    

#define IC_EVTSET0_ES27_MASK                                                    (UWORD32)(0x8000000u)                                                           
#define IC_EVTSET0_ES27_OFFSET                                                  (UWORD8)(27)                                                                    

#define IC_EVTSET0_ES28_MASK                                                    (UWORD32)(0x10000000u)                                                          
#define IC_EVTSET0_ES28_OFFSET                                                  (UWORD8)(28)                                                                    

#define IC_EVTSET0_ES29_MASK                                                    (UWORD32)(0x20000000u)                                                          
#define IC_EVTSET0_ES29_OFFSET                                                  (UWORD8)(29)                                                                    

#define IC_EVTSET0_ES30_MASK                                                    (UWORD32)(0x40000000u)                                                          
#define IC_EVTSET0_ES30_OFFSET                                                  (UWORD8)(30)                                                                    

#define IC_EVTSET0_ES31_MASK                                                    (UWORD32)(0x80000000u)                                                          
#define IC_EVTSET0_ES31_OFFSET                                                  (UWORD8)(31)                                                                    

#define IC_EVTSET1_ES32_MASK                                                    (UWORD32)(0x1u)                                                                 
#define IC_EVTSET1_ES32_OFFSET                                                  (UWORD8)(0)                                                                     

#define IC_EVTSET1_ES33_MASK                                                    (UWORD32)(0x2u)                                                                 
#define IC_EVTSET1_ES33_OFFSET                                                  (UWORD8)(1)                                                                     

#define IC_EVTSET1_ES34_MASK                                                    (UWORD32)(0x4u)                                                                 
#define IC_EVTSET1_ES34_OFFSET                                                  (UWORD8)(2)                                                                     

#define IC_EVTSET1_ES35_MASK                                                    (UWORD32)(0x8u)                                                                 
#define IC_EVTSET1_ES35_OFFSET                                                  (UWORD8)(3)                                                                     

#define IC_EVTSET1_ES36_MASK                                                    (UWORD32)(0x10u)                                                                
#define IC_EVTSET1_ES36_OFFSET                                                  (UWORD8)(4)                                                                     

#define IC_EVTSET1_ES37_MASK                                                    (UWORD32)(0x20u)                                                                
#define IC_EVTSET1_ES37_OFFSET                                                  (UWORD8)(5)                                                                     

#define IC_EVTSET1_ES38_MASK                                                    (UWORD32)(0x40u)                                                                
#define IC_EVTSET1_ES38_OFFSET                                                  (UWORD8)(6)                                                                     

#define IC_EVTSET1_ES39_MASK                                                    (UWORD32)(0x80u)                                                                
#define IC_EVTSET1_ES39_OFFSET                                                  (UWORD8)(7)                                                                     

#define IC_EVTSET1_ES40_MASK                                                    (UWORD32)(0x100u)                                                               
#define IC_EVTSET1_ES40_OFFSET                                                  (UWORD8)(8)                                                                     

#define IC_EVTSET1_ES41_MASK                                                    (UWORD32)(0x200u)                                                               
#define IC_EVTSET1_ES41_OFFSET                                                  (UWORD8)(9)                                                                     

#define IC_EVTSET1_ES42_MASK                                                    (UWORD32)(0x400u)                                                               
#define IC_EVTSET1_ES42_OFFSET                                                  (UWORD8)(10)                                                                    

#define IC_EVTSET1_ES43_MASK                                                    (UWORD32)(0x800u)                                                               
#define IC_EVTSET1_ES43_OFFSET                                                  (UWORD8)(11)                                                                    

#define IC_EVTSET1_ES44_MASK                                                    (UWORD32)(0x1000u)                                                              
#define IC_EVTSET1_ES44_OFFSET                                                  (UWORD8)(12)                                                                    

#define IC_EVTSET1_ES45_MASK                                                    (UWORD32)(0x2000u)                                                              
#define IC_EVTSET1_ES45_OFFSET                                                  (UWORD8)(13)                                                                    

#define IC_EVTSET1_ES46_MASK                                                    (UWORD32)(0x4000u)                                                              
#define IC_EVTSET1_ES46_OFFSET                                                  (UWORD8)(14)                                                                    

#define IC_EVTSET1_ES47_MASK                                                    (UWORD32)(0x8000u)                                                              
#define IC_EVTSET1_ES47_OFFSET                                                  (UWORD8)(15)                                                                    

#define IC_EVTSET1_ES48_MASK                                                    (UWORD32)(0x10000u)                                                             
#define IC_EVTSET1_ES48_OFFSET                                                  (UWORD8)(16)                                                                    

#define IC_EVTSET1_ES49_MASK                                                    (UWORD32)(0x20000u)                                                             
#define IC_EVTSET1_ES49_OFFSET                                                  (UWORD8)(17)                                                                    

#define IC_EVTSET1_ES50_MASK                                                    (UWORD32)(0x40000u)                                                             
#define IC_EVTSET1_ES50_OFFSET                                                  (UWORD8)(18)                                                                    

#define IC_EVTSET1_ES51_MASK                                                    (UWORD32)(0x80000u)                                                             
#define IC_EVTSET1_ES51_OFFSET                                                  (UWORD8)(19)                                                                    

#define IC_EVTSET1_ES52_MASK                                                    (UWORD32)(0x100000u)                                                            
#define IC_EVTSET1_ES52_OFFSET                                                  (UWORD8)(20)                                                                    

#define IC_EVTSET1_ES53_MASK                                                    (UWORD32)(0x200000u)                                                            
#define IC_EVTSET1_ES53_OFFSET                                                  (UWORD8)(21)                                                                    

#define IC_EVTSET1_ES54_MASK                                                    (UWORD32)(0x400000u)                                                            
#define IC_EVTSET1_ES54_OFFSET                                                  (UWORD8)(22)                                                                    

#define IC_EVTSET1_ES55_MASK                                                    (UWORD32)(0x800000u)                                                            
#define IC_EVTSET1_ES55_OFFSET                                                  (UWORD8)(23)                                                                    

#define IC_EVTSET1_ES56_MASK                                                    (UWORD32)(0x1000000u)                                                           
#define IC_EVTSET1_ES56_OFFSET                                                  (UWORD8)(24)                                                                    

#define IC_EVTSET1_ES57_MASK                                                    (UWORD32)(0x2000000u)                                                           
#define IC_EVTSET1_ES57_OFFSET                                                  (UWORD8)(25)                                                                    

#define IC_EVTSET1_ES58_MASK                                                    (UWORD32)(0x4000000u)                                                           
#define IC_EVTSET1_ES58_OFFSET                                                  (UWORD8)(26)                                                                    

#define IC_EVTSET1_ES59_MASK                                                    (UWORD32)(0x8000000u)                                                           
#define IC_EVTSET1_ES59_OFFSET                                                  (UWORD8)(27)                                                                    

#define IC_EVTSET1_ES60_MASK                                                    (UWORD32)(0x10000000u)                                                          
#define IC_EVTSET1_ES60_OFFSET                                                  (UWORD8)(28)                                                                    

#define IC_EVTSET1_ES61_MASK                                                    (UWORD32)(0x20000000u)                                                          
#define IC_EVTSET1_ES61_OFFSET                                                  (UWORD8)(29)                                                                    

#define IC_EVTSET1_ES62_MASK                                                    (UWORD32)(0x40000000u)                                                          
#define IC_EVTSET1_ES62_OFFSET                                                  (UWORD8)(30)                                                                    

#define IC_EVTSET1_ES63_MASK                                                    (UWORD32)(0x80000000u)                                                          
#define IC_EVTSET1_ES63_OFFSET                                                  (UWORD8)(31)                                                                    

#define IC_EVTSET2_ES0_MASK                                                     (UWORD32)(0x1u)                                                                 
#define IC_EVTSET2_ES0_OFFSET                                                   (UWORD8)(0)                                                                     

#define IC_EVTSET2_ES1_MASK                                                     (UWORD32)(0x2u)                                                                 
#define IC_EVTSET2_ES1_OFFSET                                                   (UWORD8)(1)                                                                     

#define IC_EVTSET2_ES2_MASK                                                     (UWORD32)(0x4u)                                                                 
#define IC_EVTSET2_ES2_OFFSET                                                   (UWORD8)(2)                                                                     

#define IC_EVTSET2_ES3_MASK                                                     (UWORD32)(0x8u)                                                                 
#define IC_EVTSET2_ES3_OFFSET                                                   (UWORD8)(3)                                                                     

#define IC_EVTSET2_ES4_MASK                                                     (UWORD32)(0x10u)                                                                
#define IC_EVTSET2_ES4_OFFSET                                                   (UWORD8)(4)                                                                     

#define IC_EVTSET2_ES5_MASK                                                     (UWORD32)(0x20u)                                                                
#define IC_EVTSET2_ES5_OFFSET                                                   (UWORD8)(5)                                                                     

#define IC_EVTSET2_ES6_MASK                                                     (UWORD32)(0x40u)                                                                
#define IC_EVTSET2_ES6_OFFSET                                                   (UWORD8)(6)                                                                     

#define IC_EVTSET2_ES7_MASK                                                     (UWORD32)(0x80u)                                                                
#define IC_EVTSET2_ES7_OFFSET                                                   (UWORD8)(7)                                                                     

#define IC_EVTSET2_ES8_MASK                                                     (UWORD32)(0x100u)                                                               
#define IC_EVTSET2_ES8_OFFSET                                                   (UWORD8)(8)                                                                     

#define IC_EVTSET2_ES9_MASK                                                     (UWORD32)(0x200u)                                                               
#define IC_EVTSET2_ES9_OFFSET                                                   (UWORD8)(9)                                                                     

#define IC_EVTSET2_ES10_MASK                                                    (UWORD32)(0x400u)                                                               
#define IC_EVTSET2_ES10_OFFSET                                                  (UWORD8)(10)                                                                    

#define IC_EVTSET2_ES11_MASK                                                    (UWORD32)(0x800u)                                                               
#define IC_EVTSET2_ES11_OFFSET                                                  (UWORD8)(11)                                                                    

#define IC_EVTSET2_ES12_MASK                                                    (UWORD32)(0x1000u)                                                              
#define IC_EVTSET2_ES12_OFFSET                                                  (UWORD8)(12)                                                                    

#define IC_EVTSET2_ES13_MASK                                                    (UWORD32)(0x2000u)                                                              
#define IC_EVTSET2_ES13_OFFSET                                                  (UWORD8)(13)                                                                    

#define IC_EVTSET2_ES14_MASK                                                    (UWORD32)(0x4000u)                                                              
#define IC_EVTSET2_ES14_OFFSET                                                  (UWORD8)(14)                                                                    

#define IC_EVTSET2_ES15_MASK                                                    (UWORD32)(0x8000u)                                                              
#define IC_EVTSET2_ES15_OFFSET                                                  (UWORD8)(15)                                                                    

#define IC_EVTSET2_ES16_MASK                                                    (UWORD32)(0x10000u)                                                             
#define IC_EVTSET2_ES16_OFFSET                                                  (UWORD8)(16)                                                                    

#define IC_EVTSET2_ES17_MASK                                                    (UWORD32)(0x20000u)                                                             
#define IC_EVTSET2_ES17_OFFSET                                                  (UWORD8)(17)                                                                    

#define IC_EVTSET2_ES18_MASK                                                    (UWORD32)(0x40000u)                                                             
#define IC_EVTSET2_ES18_OFFSET                                                  (UWORD8)(18)                                                                    

#define IC_EVTSET2_ES19_MASK                                                    (UWORD32)(0x80000u)                                                             
#define IC_EVTSET2_ES19_OFFSET                                                  (UWORD8)(19)                                                                    

#define IC_EVTSET2_ES20_MASK                                                    (UWORD32)(0x100000u)                                                            
#define IC_EVTSET2_ES20_OFFSET                                                  (UWORD8)(20)                                                                    

#define IC_EVTSET2_ES21_MASK                                                    (UWORD32)(0x200000u)                                                            
#define IC_EVTSET2_ES21_OFFSET                                                  (UWORD8)(21)                                                                    

#define IC_EVTSET2_ES22_MASK                                                    (UWORD32)(0x400000u)                                                            
#define IC_EVTSET2_ES22_OFFSET                                                  (UWORD8)(22)                                                                    

#define IC_EVTSET2_ES23_MASK                                                    (UWORD32)(0x800000u)                                                            
#define IC_EVTSET2_ES23_OFFSET                                                  (UWORD8)(23)                                                                    

#define IC_EVTSET2_ES24_MASK                                                    (UWORD32)(0x1000000u)                                                           
#define IC_EVTSET2_ES24_OFFSET                                                  (UWORD8)(24)                                                                    

#define IC_EVTSET2_ES25_MASK                                                    (UWORD32)(0x2000000u)                                                           
#define IC_EVTSET2_ES25_OFFSET                                                  (UWORD8)(25)                                                                    

#define IC_EVTSET2_ES26_MASK                                                    (UWORD32)(0x4000000u)                                                           
#define IC_EVTSET2_ES26_OFFSET                                                  (UWORD8)(26)                                                                    

#define IC_EVTSET2_ES27_MASK                                                    (UWORD32)(0x8000000u)                                                           
#define IC_EVTSET2_ES27_OFFSET                                                  (UWORD8)(27)                                                                    

#define IC_EVTSET2_ES28_MASK                                                    (UWORD32)(0x10000000u)                                                          
#define IC_EVTSET2_ES28_OFFSET                                                  (UWORD8)(28)                                                                    

#define IC_EVTSET2_ES29_MASK                                                    (UWORD32)(0x20000000u)                                                          
#define IC_EVTSET2_ES29_OFFSET                                                  (UWORD8)(29)                                                                    

#define IC_EVTSET2_ES30_MASK                                                    (UWORD32)(0x40000000u)                                                          
#define IC_EVTSET2_ES30_OFFSET                                                  (UWORD8)(30)                                                                    

#define IC_EVTSET2_ES31_MASK                                                    (UWORD32)(0x80000000u)                                                          
#define IC_EVTSET2_ES31_OFFSET                                                  (UWORD8)(31)                                                                    

#define IC_EVTSET3_ES0_MASK                                                     (UWORD32)(0x1u)                                                                 
#define IC_EVTSET3_ES0_OFFSET                                                   (UWORD8)(0)                                                                     

#define IC_EVTSET3_ES1_MASK                                                     (UWORD32)(0x2u)                                                                 
#define IC_EVTSET3_ES1_OFFSET                                                   (UWORD8)(1)                                                                     

#define IC_EVTSET3_ES2_MASK                                                     (UWORD32)(0x4u)                                                                 
#define IC_EVTSET3_ES2_OFFSET                                                   (UWORD8)(2)                                                                     

#define IC_EVTSET3_ES3_MASK                                                     (UWORD32)(0x8u)                                                                 
#define IC_EVTSET3_ES3_OFFSET                                                   (UWORD8)(3)                                                                     

#define IC_EVTSET3_ES4_MASK                                                     (UWORD32)(0x10u)                                                                
#define IC_EVTSET3_ES4_OFFSET                                                   (UWORD8)(4)                                                                     

#define IC_EVTSET3_ES5_MASK                                                     (UWORD32)(0x20u)                                                                
#define IC_EVTSET3_ES5_OFFSET                                                   (UWORD8)(5)                                                                     

#define IC_EVTSET3_ES6_MASK                                                     (UWORD32)(0x40u)                                                                
#define IC_EVTSET3_ES6_OFFSET                                                   (UWORD8)(6)                                                                     

#define IC_EVTSET3_ES7_MASK                                                     (UWORD32)(0x80u)                                                                
#define IC_EVTSET3_ES7_OFFSET                                                   (UWORD8)(7)                                                                     

#define IC_EVTSET3_ES8_MASK                                                     (UWORD32)(0x100u)                                                               
#define IC_EVTSET3_ES8_OFFSET                                                   (UWORD8)(8)                                                                     

#define IC_EVTSET3_ES9_MASK                                                     (UWORD32)(0x200u)                                                               
#define IC_EVTSET3_ES9_OFFSET                                                   (UWORD8)(9)                                                                     

#define IC_EVTSET3_ES10_MASK                                                    (UWORD32)(0x400u)                                                               
#define IC_EVTSET3_ES10_OFFSET                                                  (UWORD8)(10)                                                                    

#define IC_EVTSET3_ES11_MASK                                                    (UWORD32)(0x800u)                                                               
#define IC_EVTSET3_ES11_OFFSET                                                  (UWORD8)(11)                                                                    

#define IC_EVTSET3_ES12_MASK                                                    (UWORD32)(0x1000u)                                                              
#define IC_EVTSET3_ES12_OFFSET                                                  (UWORD8)(12)                                                                    

#define IC_EVTSET3_ES13_MASK                                                    (UWORD32)(0x2000u)                                                              
#define IC_EVTSET3_ES13_OFFSET                                                  (UWORD8)(13)                                                                    

#define IC_EVTSET3_ES14_MASK                                                    (UWORD32)(0x4000u)                                                              
#define IC_EVTSET3_ES14_OFFSET                                                  (UWORD8)(14)                                                                    

#define IC_EVTSET3_ES15_MASK                                                    (UWORD32)(0x8000u)                                                              
#define IC_EVTSET3_ES15_OFFSET                                                  (UWORD8)(15)                                                                    

#define IC_EVTSET3_ES16_MASK                                                    (UWORD32)(0x10000u)                                                             
#define IC_EVTSET3_ES16_OFFSET                                                  (UWORD8)(16)                                                                    

#define IC_EVTSET3_ES17_MASK                                                    (UWORD32)(0x20000u)                                                             
#define IC_EVTSET3_ES17_OFFSET                                                  (UWORD8)(17)                                                                    

#define IC_EVTSET3_ES18_MASK                                                    (UWORD32)(0x40000u)                                                             
#define IC_EVTSET3_ES18_OFFSET                                                  (UWORD8)(18)                                                                    

#define IC_EVTSET3_ES19_MASK                                                    (UWORD32)(0x80000u)                                                             
#define IC_EVTSET3_ES19_OFFSET                                                  (UWORD8)(19)                                                                    

#define IC_EVTSET3_ES20_MASK                                                    (UWORD32)(0x100000u)                                                            
#define IC_EVTSET3_ES20_OFFSET                                                  (UWORD8)(20)                                                                    

#define IC_EVTSET3_ES21_MASK                                                    (UWORD32)(0x200000u)                                                            
#define IC_EVTSET3_ES21_OFFSET                                                  (UWORD8)(21)                                                                    

#define IC_EVTSET3_ES22_MASK                                                    (UWORD32)(0x400000u)                                                            
#define IC_EVTSET3_ES22_OFFSET                                                  (UWORD8)(22)                                                                    

#define IC_EVTSET3_ES23_MASK                                                    (UWORD32)(0x800000u)                                                            
#define IC_EVTSET3_ES23_OFFSET                                                  (UWORD8)(23)                                                                    

#define IC_EVTSET3_ES24_MASK                                                    (UWORD32)(0x1000000u)                                                           
#define IC_EVTSET3_ES24_OFFSET                                                  (UWORD8)(24)                                                                    

#define IC_EVTSET3_ES25_MASK                                                    (UWORD32)(0x2000000u)                                                           
#define IC_EVTSET3_ES25_OFFSET                                                  (UWORD8)(25)                                                                    

#define IC_EVTSET3_ES26_MASK                                                    (UWORD32)(0x4000000u)                                                           
#define IC_EVTSET3_ES26_OFFSET                                                  (UWORD8)(26)                                                                    

#define IC_EVTSET3_ES27_MASK                                                    (UWORD32)(0x8000000u)                                                           
#define IC_EVTSET3_ES27_OFFSET                                                  (UWORD8)(27)                                                                    

#define IC_EVTSET3_ES28_MASK                                                    (UWORD32)(0x10000000u)                                                          
#define IC_EVTSET3_ES28_OFFSET                                                  (UWORD8)(28)                                                                    

#define IC_EVTSET3_ES29_MASK                                                    (UWORD32)(0x20000000u)                                                          
#define IC_EVTSET3_ES29_OFFSET                                                  (UWORD8)(29)                                                                    

#define IC_EVTSET3_ES30_MASK                                                    (UWORD32)(0x40000000u)                                                          
#define IC_EVTSET3_ES30_OFFSET                                                  (UWORD8)(30)                                                                    

#define IC_EVTSET3_ES31_MASK                                                    (UWORD32)(0x80000000u)                                                          
#define IC_EVTSET3_ES31_OFFSET                                                  (UWORD8)(31)                                                                    

#define IC_EVTCLR0_EC0_MASK                                                     (UWORD32)(0x1u)                                                                 
#define IC_EVTCLR0_EC0_OFFSET                                                   (UWORD8)(0)                                                                     

#define IC_EVTCLR0_EC1_MASK                                                     (UWORD32)(0x2u)                                                                 
#define IC_EVTCLR0_EC1_OFFSET                                                   (UWORD8)(1)                                                                     

#define IC_EVTCLR0_EC2_MASK                                                     (UWORD32)(0x4u)                                                                 
#define IC_EVTCLR0_EC2_OFFSET                                                   (UWORD8)(2)                                                                     

#define IC_EVTCLR0_EC3_MASK                                                     (UWORD32)(0x8u)                                                                 
#define IC_EVTCLR0_EC3_OFFSET                                                   (UWORD8)(3)                                                                     

#define IC_EVTCLR0_EC4_MASK                                                     (UWORD32)(0x10u)                                                                
#define IC_EVTCLR0_EC4_OFFSET                                                   (UWORD8)(4)                                                                     

#define IC_EVTCLR0_EC5_MASK                                                     (UWORD32)(0x20u)                                                                
#define IC_EVTCLR0_EC5_OFFSET                                                   (UWORD8)(5)                                                                     

#define IC_EVTCLR0_EC6_MASK                                                     (UWORD32)(0x40u)                                                                
#define IC_EVTCLR0_EC6_OFFSET                                                   (UWORD8)(6)                                                                     

#define IC_EVTCLR0_EC7_MASK                                                     (UWORD32)(0x80u)                                                                
#define IC_EVTCLR0_EC7_OFFSET                                                   (UWORD8)(7)                                                                     

#define IC_EVTCLR0_EC8_MASK                                                     (UWORD32)(0x100u)                                                               
#define IC_EVTCLR0_EC8_OFFSET                                                   (UWORD8)(8)                                                                     

#define IC_EVTCLR0_EC9_MASK                                                     (UWORD32)(0x200u)                                                               
#define IC_EVTCLR0_EC9_OFFSET                                                   (UWORD8)(9)                                                                     

#define IC_EVTCLR0_EC10_MASK                                                    (UWORD32)(0x400u)                                                               
#define IC_EVTCLR0_EC10_OFFSET                                                  (UWORD8)(10)                                                                    

#define IC_EVTCLR0_EC11_MASK                                                    (UWORD32)(0x800u)                                                               
#define IC_EVTCLR0_EC11_OFFSET                                                  (UWORD8)(11)                                                                    

#define IC_EVTCLR0_EC12_MASK                                                    (UWORD32)(0x1000u)                                                              
#define IC_EVTCLR0_EC12_OFFSET                                                  (UWORD8)(12)                                                                    

#define IC_EVTCLR0_EC13_MASK                                                    (UWORD32)(0x2000u)                                                              
#define IC_EVTCLR0_EC13_OFFSET                                                  (UWORD8)(13)                                                                    

#define IC_EVTCLR0_EC14_MASK                                                    (UWORD32)(0x4000u)                                                              
#define IC_EVTCLR0_EC14_OFFSET                                                  (UWORD8)(14)                                                                    

#define IC_EVTCLR0_EC15_MASK                                                    (UWORD32)(0x8000u)                                                              
#define IC_EVTCLR0_EC15_OFFSET                                                  (UWORD8)(15)                                                                    

#define IC_EVTCLR0_EC16_MASK                                                    (UWORD32)(0x10000u)                                                             
#define IC_EVTCLR0_EC16_OFFSET                                                  (UWORD8)(16)                                                                    

#define IC_EVTCLR0_EC17_MASK                                                    (UWORD32)(0x20000u)                                                             
#define IC_EVTCLR0_EC17_OFFSET                                                  (UWORD8)(17)                                                                    

#define IC_EVTCLR0_EC18_MASK                                                    (UWORD32)(0x40000u)                                                             
#define IC_EVTCLR0_EC18_OFFSET                                                  (UWORD8)(18)                                                                    

#define IC_EVTCLR0_EC19_MASK                                                    (UWORD32)(0x80000u)                                                             
#define IC_EVTCLR0_EC19_OFFSET                                                  (UWORD8)(19)                                                                    

#define IC_EVTCLR0_EC20_MASK                                                    (UWORD32)(0x100000u)                                                            
#define IC_EVTCLR0_EC20_OFFSET                                                  (UWORD8)(20)                                                                    

#define IC_EVTCLR0_EC21_MASK                                                    (UWORD32)(0x200000u)                                                            
#define IC_EVTCLR0_EC21_OFFSET                                                  (UWORD8)(21)                                                                    

#define IC_EVTCLR0_EC22_MASK                                                    (UWORD32)(0x400000u)                                                            
#define IC_EVTCLR0_EC22_OFFSET                                                  (UWORD8)(22)                                                                    

#define IC_EVTCLR0_EC23_MASK                                                    (UWORD32)(0x800000u)                                                            
#define IC_EVTCLR0_EC23_OFFSET                                                  (UWORD8)(23)                                                                    

#define IC_EVTCLR0_EC24_MASK                                                    (UWORD32)(0x1000000u)                                                           
#define IC_EVTCLR0_EC24_OFFSET                                                  (UWORD8)(24)                                                                    

#define IC_EVTCLR0_EC25_MASK                                                    (UWORD32)(0x2000000u)                                                           
#define IC_EVTCLR0_EC25_OFFSET                                                  (UWORD8)(25)                                                                    

#define IC_EVTCLR0_EC26_MASK                                                    (UWORD32)(0x4000000u)                                                           
#define IC_EVTCLR0_EC26_OFFSET                                                  (UWORD8)(26)                                                                    

#define IC_EVTCLR0_EC27_MASK                                                    (UWORD32)(0x8000000u)                                                           
#define IC_EVTCLR0_EC27_OFFSET                                                  (UWORD8)(27)                                                                    

#define IC_EVTCLR0_EC28_MASK                                                    (UWORD32)(0x10000000u)                                                          
#define IC_EVTCLR0_EC28_OFFSET                                                  (UWORD8)(28)                                                                    

#define IC_EVTCLR0_EC29_MASK                                                    (UWORD32)(0x20000000u)                                                          
#define IC_EVTCLR0_EC29_OFFSET                                                  (UWORD8)(29)                                                                    

#define IC_EVTCLR0_EC30_MASK                                                    (UWORD32)(0x40000000u)                                                          
#define IC_EVTCLR0_EC30_OFFSET                                                  (UWORD8)(30)                                                                    

#define IC_EVTCLR0_EC31_MASK                                                    (UWORD32)(0x80000000u)                                                          
#define IC_EVTCLR0_EC31_OFFSET                                                  (UWORD8)(31)                                                                    

#define IC_EVTCLR1_EC32_MASK                                                    (UWORD32)(0x1u)                                                                 
#define IC_EVTCLR1_EC32_OFFSET                                                  (UWORD8)(0)                                                                     

#define IC_EVTCLR1_EC33_MASK                                                    (UWORD32)(0x2u)                                                                 
#define IC_EVTCLR1_EC33_OFFSET                                                  (UWORD8)(1)                                                                     

#define IC_EVTCLR1_EC34_MASK                                                    (UWORD32)(0x4u)                                                                 
#define IC_EVTCLR1_EC34_OFFSET                                                  (UWORD8)(2)                                                                     

#define IC_EVTCLR1_EC35_MASK                                                    (UWORD32)(0x8u)                                                                 
#define IC_EVTCLR1_EC35_OFFSET                                                  (UWORD8)(3)                                                                     

#define IC_EVTCLR1_EC36_MASK                                                    (UWORD32)(0x10u)                                                                
#define IC_EVTCLR1_EC36_OFFSET                                                  (UWORD8)(4)                                                                     

#define IC_EVTCLR1_EC37_MASK                                                    (UWORD32)(0x20u)                                                                
#define IC_EVTCLR1_EC37_OFFSET                                                  (UWORD8)(5)                                                                     

#define IC_EVTCLR1_EC38_MASK                                                    (UWORD32)(0x40u)                                                                
#define IC_EVTCLR1_EC38_OFFSET                                                  (UWORD8)(6)                                                                     

#define IC_EVTCLR1_EC39_MASK                                                    (UWORD32)(0x80u)                                                                
#define IC_EVTCLR1_EC39_OFFSET                                                  (UWORD8)(7)                                                                     

#define IC_EVTCLR1_EC40_MASK                                                    (UWORD32)(0x100u)                                                               
#define IC_EVTCLR1_EC40_OFFSET                                                  (UWORD8)(8)                                                                     

#define IC_EVTCLR1_EC41_MASK                                                    (UWORD32)(0x200u)                                                               
#define IC_EVTCLR1_EC41_OFFSET                                                  (UWORD8)(9)                                                                     

#define IC_EVTCLR1_EC42_MASK                                                    (UWORD32)(0x400u)                                                               
#define IC_EVTCLR1_EC42_OFFSET                                                  (UWORD8)(10)                                                                    

#define IC_EVTCLR1_EC43_MASK                                                    (UWORD32)(0x800u)                                                               
#define IC_EVTCLR1_EC43_OFFSET                                                  (UWORD8)(11)                                                                    

#define IC_EVTCLR1_EC44_MASK                                                    (UWORD32)(0x1000u)                                                              
#define IC_EVTCLR1_EC44_OFFSET                                                  (UWORD8)(12)                                                                    

#define IC_EVTCLR1_EC45_MASK                                                    (UWORD32)(0x2000u)                                                              
#define IC_EVTCLR1_EC45_OFFSET                                                  (UWORD8)(13)                                                                    

#define IC_EVTCLR1_EC46_MASK                                                    (UWORD32)(0x4000u)                                                              
#define IC_EVTCLR1_EC46_OFFSET                                                  (UWORD8)(14)                                                                    

#define IC_EVTCLR1_EC47_MASK                                                    (UWORD32)(0x8000u)                                                              
#define IC_EVTCLR1_EC47_OFFSET                                                  (UWORD8)(15)                                                                    

#define IC_EVTCLR1_EC48_MASK                                                    (UWORD32)(0x10000u)                                                             
#define IC_EVTCLR1_EC48_OFFSET                                                  (UWORD8)(16)                                                                    

#define IC_EVTCLR1_EC49_MASK                                                    (UWORD32)(0x20000u)                                                             
#define IC_EVTCLR1_EC49_OFFSET                                                  (UWORD8)(17)                                                                    

#define IC_EVTCLR1_EC50_MASK                                                    (UWORD32)(0x40000u)                                                             
#define IC_EVTCLR1_EC50_OFFSET                                                  (UWORD8)(18)                                                                    

#define IC_EVTCLR1_EC51_MASK                                                    (UWORD32)(0x80000u)                                                             
#define IC_EVTCLR1_EC51_OFFSET                                                  (UWORD8)(19)                                                                    

#define IC_EVTCLR1_EC52_MASK                                                    (UWORD32)(0x100000u)                                                            
#define IC_EVTCLR1_EC52_OFFSET                                                  (UWORD8)(20)                                                                    

#define IC_EVTCLR1_EC53_MASK                                                    (UWORD32)(0x200000u)                                                            
#define IC_EVTCLR1_EC53_OFFSET                                                  (UWORD8)(21)                                                                    

#define IC_EVTCLR1_EC54_MASK                                                    (UWORD32)(0x400000u)                                                            
#define IC_EVTCLR1_EC54_OFFSET                                                  (UWORD8)(22)                                                                    

#define IC_EVTCLR1_EC55_MASK                                                    (UWORD32)(0x800000u)                                                            
#define IC_EVTCLR1_EC55_OFFSET                                                  (UWORD8)(23)                                                                    

#define IC_EVTCLR1_EC56_MASK                                                    (UWORD32)(0x1000000u)                                                           
#define IC_EVTCLR1_EC56_OFFSET                                                  (UWORD8)(24)                                                                    

#define IC_EVTCLR1_EC57_MASK                                                    (UWORD32)(0x2000000u)                                                           
#define IC_EVTCLR1_EC57_OFFSET                                                  (UWORD8)(25)                                                                    

#define IC_EVTCLR1_EC58_MASK                                                    (UWORD32)(0x4000000u)                                                           
#define IC_EVTCLR1_EC58_OFFSET                                                  (UWORD8)(26)                                                                    

#define IC_EVTCLR1_EC59_MASK                                                    (UWORD32)(0x8000000u)                                                           
#define IC_EVTCLR1_EC59_OFFSET                                                  (UWORD8)(27)                                                                    

#define IC_EVTCLR1_EC60_MASK                                                    (UWORD32)(0x10000000u)                                                          
#define IC_EVTCLR1_EC60_OFFSET                                                  (UWORD8)(28)                                                                    

#define IC_EVTCLR1_EC61_MASK                                                    (UWORD32)(0x20000000u)                                                          
#define IC_EVTCLR1_EC61_OFFSET                                                  (UWORD8)(29)                                                                    

#define IC_EVTCLR1_EC62_MASK                                                    (UWORD32)(0x40000000u)                                                          
#define IC_EVTCLR1_EC62_OFFSET                                                  (UWORD8)(30)                                                                    

#define IC_EVTCLR1_EC63_MASK                                                    (UWORD32)(0x80000000u)                                                          
#define IC_EVTCLR1_EC63_OFFSET                                                  (UWORD8)(31)                                                                    

#define IC_EVTCLR2_EC64_MASK                                                    (UWORD32)(0x1u)                                                                 
#define IC_EVTCLR2_EC64_OFFSET                                                  (UWORD8)(0)                                                                     

#define IC_EVTCLR2_EC65_MASK                                                    (UWORD32)(0x2u)                                                                 
#define IC_EVTCLR2_EC65_OFFSET                                                  (UWORD8)(1)                                                                     

#define IC_EVTCLR2_EC66_MASK                                                    (UWORD32)(0x4u)                                                                 
#define IC_EVTCLR2_EC66_OFFSET                                                  (UWORD8)(2)                                                                     

#define IC_EVTCLR2_EC67_MASK                                                    (UWORD32)(0x8u)                                                                 
#define IC_EVTCLR2_EC67_OFFSET                                                  (UWORD8)(3)                                                                     

#define IC_EVTCLR2_EC68_MASK                                                    (UWORD32)(0x10u)                                                                
#define IC_EVTCLR2_EC68_OFFSET                                                  (UWORD8)(4)                                                                     

#define IC_EVTCLR2_EC69_MASK                                                    (UWORD32)(0x20u)                                                                
#define IC_EVTCLR2_EC69_OFFSET                                                  (UWORD8)(5)                                                                     

#define IC_EVTCLR2_EC70_MASK                                                    (UWORD32)(0x40u)                                                                
#define IC_EVTCLR2_EC70_OFFSET                                                  (UWORD8)(6)                                                                     

#define IC_EVTCLR2_EC71_MASK                                                    (UWORD32)(0x80u)                                                                
#define IC_EVTCLR2_EC71_OFFSET                                                  (UWORD8)(7)                                                                     

#define IC_EVTCLR2_EC72_MASK                                                    (UWORD32)(0x100u)                                                               
#define IC_EVTCLR2_EC72_OFFSET                                                  (UWORD8)(8)                                                                     

#define IC_EVTCLR2_EC73_MASK                                                    (UWORD32)(0x200u)                                                               
#define IC_EVTCLR2_EC73_OFFSET                                                  (UWORD8)(9)                                                                     

#define IC_EVTCLR2_EC74_MASK                                                    (UWORD32)(0x400u)                                                               
#define IC_EVTCLR2_EC74_OFFSET                                                  (UWORD8)(10)                                                                    

#define IC_EVTCLR2_EC75_MASK                                                    (UWORD32)(0x800u)                                                               
#define IC_EVTCLR2_EC75_OFFSET                                                  (UWORD8)(11)                                                                    

#define IC_EVTCLR2_EC76_MASK                                                    (UWORD32)(0x1000u)                                                              
#define IC_EVTCLR2_EC76_OFFSET                                                  (UWORD8)(12)                                                                    

#define IC_EVTCLR2_EC77_MASK                                                    (UWORD32)(0x2000u)                                                              
#define IC_EVTCLR2_EC77_OFFSET                                                  (UWORD8)(13)                                                                    

#define IC_EVTCLR2_EC78_MASK                                                    (UWORD32)(0x4000u)                                                              
#define IC_EVTCLR2_EC78_OFFSET                                                  (UWORD8)(14)                                                                    

#define IC_EVTCLR2_EC79_MASK                                                    (UWORD32)(0x8000u)                                                              
#define IC_EVTCLR2_EC79_OFFSET                                                  (UWORD8)(15)                                                                    

#define IC_EVTCLR2_EC80_MASK                                                    (UWORD32)(0x10000u)                                                             
#define IC_EVTCLR2_EC80_OFFSET                                                  (UWORD8)(16)                                                                    

#define IC_EVTCLR2_EC81_MASK                                                    (UWORD32)(0x20000u)                                                             
#define IC_EVTCLR2_EC81_OFFSET                                                  (UWORD8)(17)                                                                    

#define IC_EVTCLR2_EC82_MASK                                                    (UWORD32)(0x40000u)                                                             
#define IC_EVTCLR2_EC82_OFFSET                                                  (UWORD8)(18)                                                                    

#define IC_EVTCLR2_EC83_MASK                                                    (UWORD32)(0x80000u)                                                             
#define IC_EVTCLR2_EC83_OFFSET                                                  (UWORD8)(19)                                                                    

#define IC_EVTCLR2_EC84_MASK                                                    (UWORD32)(0x100000u)                                                            
#define IC_EVTCLR2_EC84_OFFSET                                                  (UWORD8)(20)                                                                    

#define IC_EVTCLR2_EC85_MASK                                                    (UWORD32)(0x200000u)                                                            
#define IC_EVTCLR2_EC85_OFFSET                                                  (UWORD8)(21)                                                                    

#define IC_EVTCLR2_EC86_MASK                                                    (UWORD32)(0x400000u)                                                            
#define IC_EVTCLR2_EC86_OFFSET                                                  (UWORD8)(22)                                                                    

#define IC_EVTCLR2_EC87_MASK                                                    (UWORD32)(0x800000u)                                                            
#define IC_EVTCLR2_EC87_OFFSET                                                  (UWORD8)(23)                                                                    

#define IC_EVTCLR2_EC88_MASK                                                    (UWORD32)(0x1000000u)                                                           
#define IC_EVTCLR2_EC88_OFFSET                                                  (UWORD8)(24)                                                                    

#define IC_EVTCLR2_EC89_MASK                                                    (UWORD32)(0x2000000u)                                                           
#define IC_EVTCLR2_EC89_OFFSET                                                  (UWORD8)(25)                                                                    

#define IC_EVTCLR2_EC90_MASK                                                    (UWORD32)(0x4000000u)                                                           
#define IC_EVTCLR2_EC90_OFFSET                                                  (UWORD8)(26)                                                                    

#define IC_EVTCLR2_EC91_MASK                                                    (UWORD32)(0x8000000u)                                                           
#define IC_EVTCLR2_EC91_OFFSET                                                  (UWORD8)(27)                                                                    

#define IC_EVTCLR2_EC92_MASK                                                    (UWORD32)(0x10000000u)                                                          
#define IC_EVTCLR2_EC92_OFFSET                                                  (UWORD8)(28)                                                                    

#define IC_EVTCLR2_EC93_MASK                                                    (UWORD32)(0x20000000u)                                                          
#define IC_EVTCLR2_EC93_OFFSET                                                  (UWORD8)(29)                                                                    

#define IC_EVTCLR2_EC94_MASK                                                    (UWORD32)(0x40000000u)                                                          
#define IC_EVTCLR2_EC94_OFFSET                                                  (UWORD8)(30)                                                                    

#define IC_EVTCLR2_EC95_MASK                                                    (UWORD32)(0x80000000u)                                                          
#define IC_EVTCLR2_EC95_OFFSET                                                  (UWORD8)(31)                                                                    

#define IC_EVTCLR3_EC96_MASK                                                    (UWORD32)(0x1u)                                                                 
#define IC_EVTCLR3_EC96_OFFSET                                                  (UWORD8)(0)                                                                     

#define IC_EVTCLR3_EC97_MASK                                                    (UWORD32)(0x2u)                                                                 
#define IC_EVTCLR3_EC97_OFFSET                                                  (UWORD8)(1)                                                                     

#define IC_EVTCLR3_EC98_MASK                                                    (UWORD32)(0x4u)                                                                 
#define IC_EVTCLR3_EC98_OFFSET                                                  (UWORD8)(2)                                                                     

#define IC_EVTCLR3_EC99_MASK                                                    (UWORD32)(0x8u)                                                                 
#define IC_EVTCLR3_EC99_OFFSET                                                  (UWORD8)(3)                                                                     

#define IC_EVTCLR3_EC100_MASK                                                   (UWORD32)(0x10u)                                                                
#define IC_EVTCLR3_EC100_OFFSET                                                 (UWORD8)(4)                                                                     

#define IC_EVTCLR3_EC101_MASK                                                   (UWORD32)(0x20u)                                                                
#define IC_EVTCLR3_EC101_OFFSET                                                 (UWORD8)(5)                                                                     

#define IC_EVTCLR3_EC102_MASK                                                   (UWORD32)(0x40u)                                                                
#define IC_EVTCLR3_EC102_OFFSET                                                 (UWORD8)(6)                                                                     

#define IC_EVTCLR3_EC103_MASK                                                   (UWORD32)(0x80u)                                                                
#define IC_EVTCLR3_EC103_OFFSET                                                 (UWORD8)(7)                                                                     

#define IC_EVTCLR3_EC104_MASK                                                   (UWORD32)(0x100u)                                                               
#define IC_EVTCLR3_EC104_OFFSET                                                 (UWORD8)(8)                                                                     

#define IC_EVTCLR3_EC105_MASK                                                   (UWORD32)(0x200u)                                                               
#define IC_EVTCLR3_EC105_OFFSET                                                 (UWORD8)(9)                                                                     

#define IC_EVTCLR3_EC106_MASK                                                   (UWORD32)(0x400u)                                                               
#define IC_EVTCLR3_EC106_OFFSET                                                 (UWORD8)(10)                                                                    

#define IC_EVTCLR3_EC107_MASK                                                   (UWORD32)(0x800u)                                                               
#define IC_EVTCLR3_EC107_OFFSET                                                 (UWORD8)(11)                                                                    

#define IC_EVTCLR3_EC108_MASK                                                   (UWORD32)(0x1000u)                                                              
#define IC_EVTCLR3_EC108_OFFSET                                                 (UWORD8)(12)                                                                    

#define IC_EVTCLR3_EC109_MASK                                                   (UWORD32)(0x2000u)                                                              
#define IC_EVTCLR3_EC109_OFFSET                                                 (UWORD8)(13)                                                                    

#define IC_EVTCLR3_EC110_MASK                                                   (UWORD32)(0x4000u)                                                              
#define IC_EVTCLR3_EC110_OFFSET                                                 (UWORD8)(14)                                                                    

#define IC_EVTCLR3_EC111_MASK                                                   (UWORD32)(0x8000u)                                                              
#define IC_EVTCLR3_EC111_OFFSET                                                 (UWORD8)(15)                                                                    

#define IC_EVTCLR3_EC112_MASK                                                   (UWORD32)(0x10000u)                                                             
#define IC_EVTCLR3_EC112_OFFSET                                                 (UWORD8)(16)                                                                    

#define IC_EVTCLR3_EC113_MASK                                                   (UWORD32)(0x20000u)                                                             
#define IC_EVTCLR3_EC113_OFFSET                                                 (UWORD8)(17)                                                                    

#define IC_EVTCLR3_EC114_MASK                                                   (UWORD32)(0x40000u)                                                             
#define IC_EVTCLR3_EC114_OFFSET                                                 (UWORD8)(18)                                                                    

#define IC_EVTCLR3_EC115_MASK                                                   (UWORD32)(0x80000u)                                                             
#define IC_EVTCLR3_EC115_OFFSET                                                 (UWORD8)(19)                                                                    

#define IC_EVTCLR3_EC116_MASK                                                   (UWORD32)(0x100000u)                                                            
#define IC_EVTCLR3_EC116_OFFSET                                                 (UWORD8)(20)                                                                    

#define IC_EVTCLR3_EC117_MASK                                                   (UWORD32)(0x200000u)                                                            
#define IC_EVTCLR3_EC117_OFFSET                                                 (UWORD8)(21)                                                                    

#define IC_EVTCLR3_EC118_MASK                                                   (UWORD32)(0x400000u)                                                            
#define IC_EVTCLR3_EC118_OFFSET                                                 (UWORD8)(22)                                                                    

#define IC_EVTCLR3_EC119_MASK                                                   (UWORD32)(0x800000u)                                                            
#define IC_EVTCLR3_EC119_OFFSET                                                 (UWORD8)(23)                                                                    

#define IC_EVTCLR3_EC120_MASK                                                   (UWORD32)(0x1000000u)                                                           
#define IC_EVTCLR3_EC120_OFFSET                                                 (UWORD8)(24)                                                                    

#define IC_EVTCLR3_EC121_MASK                                                   (UWORD32)(0x2000000u)                                                           
#define IC_EVTCLR3_EC121_OFFSET                                                 (UWORD8)(25)                                                                    

#define IC_EVTCLR3_EC122_MASK                                                   (UWORD32)(0x4000000u)                                                           
#define IC_EVTCLR3_EC122_OFFSET                                                 (UWORD8)(26)                                                                    

#define IC_EVTCLR3_EC123_MASK                                                   (UWORD32)(0x8000000u)                                                           
#define IC_EVTCLR3_EC123_OFFSET                                                 (UWORD8)(27)                                                                    

#define IC_EVTCLR3_EC124_MASK                                                   (UWORD32)(0x10000000u)                                                          
#define IC_EVTCLR3_EC124_OFFSET                                                 (UWORD8)(28)                                                                    

#define IC_EVTCLR3_EC125_MASK                                                   (UWORD32)(0x20000000u)                                                          
#define IC_EVTCLR3_EC125_OFFSET                                                 (UWORD8)(29)                                                                    

#define IC_EVTCLR3_EC126_MASK                                                   (UWORD32)(0x40000000u)                                                          
#define IC_EVTCLR3_EC126_OFFSET                                                 (UWORD8)(30)                                                                    

#define IC_EVTCLR3_EC127_MASK                                                   (UWORD32)(0x80000000u)                                                          
#define IC_EVTCLR3_EC127_OFFSET                                                 (UWORD8)(31)                                                                    

#define IC_EVTMASK0_EM0_MASK                                                    (UWORD32)(0x1u)                                                                 
#define IC_EVTMASK0_EM0_OFFSET                                                  (UWORD8)(0)                                                                     

#define IC_EVTMASK0_EM1_MASK                                                    (UWORD32)(0x2u)                                                                 
#define IC_EVTMASK0_EM1_OFFSET                                                  (UWORD8)(1)                                                                     

#define IC_EVTMASK0_EM2_MASK                                                    (UWORD32)(0x4u)                                                                 
#define IC_EVTMASK0_EM2_OFFSET                                                  (UWORD8)(2)                                                                     

#define IC_EVTMASK0_EM3_MASK                                                    (UWORD32)(0x8u)                                                                 
#define IC_EVTMASK0_EM3_OFFSET                                                  (UWORD8)(3)                                                                     

#define IC_EVTMASK0_EM4_MASK                                                    (UWORD32)(0x10u)                                                                
#define IC_EVTMASK0_EM4_OFFSET                                                  (UWORD8)(4)                                                                     

#define IC_EVTMASK0_EM5_MASK                                                    (UWORD32)(0x20u)                                                                
#define IC_EVTMASK0_EM5_OFFSET                                                  (UWORD8)(5)                                                                     

#define IC_EVTMASK0_EM6_MASK                                                    (UWORD32)(0x40u)                                                                
#define IC_EVTMASK0_EM6_OFFSET                                                  (UWORD8)(6)                                                                     

#define IC_EVTMASK0_EM7_MASK                                                    (UWORD32)(0x80u)                                                                
#define IC_EVTMASK0_EM7_OFFSET                                                  (UWORD8)(7)                                                                     

#define IC_EVTMASK0_EM8_MASK                                                    (UWORD32)(0x100u)                                                               
#define IC_EVTMASK0_EM8_OFFSET                                                  (UWORD8)(8)                                                                     

#define IC_EVTMASK0_EM9_MASK                                                    (UWORD32)(0x200u)                                                               
#define IC_EVTMASK0_EM9_OFFSET                                                  (UWORD8)(9)                                                                     

#define IC_EVTMASK0_EM10_MASK                                                   (UWORD32)(0x400u)                                                               
#define IC_EVTMASK0_EM10_OFFSET                                                 (UWORD8)(10)                                                                    

#define IC_EVTMASK0_EM11_MASK                                                   (UWORD32)(0x800u)                                                               
#define IC_EVTMASK0_EM11_OFFSET                                                 (UWORD8)(11)                                                                    

#define IC_EVTMASK0_EM12_MASK                                                   (UWORD32)(0x1000u)                                                              
#define IC_EVTMASK0_EM12_OFFSET                                                 (UWORD8)(12)                                                                    

#define IC_EVTMASK0_EM13_MASK                                                   (UWORD32)(0x2000u)                                                              
#define IC_EVTMASK0_EM13_OFFSET                                                 (UWORD8)(13)                                                                    

#define IC_EVTMASK0_EM14_MASK                                                   (UWORD32)(0x4000u)                                                              
#define IC_EVTMASK0_EM14_OFFSET                                                 (UWORD8)(14)                                                                    

#define IC_EVTMASK0_EM15_MASK                                                   (UWORD32)(0x8000u)                                                              
#define IC_EVTMASK0_EM15_OFFSET                                                 (UWORD8)(15)                                                                    

#define IC_EVTMASK0_EM16_MASK                                                   (UWORD32)(0x10000u)                                                             
#define IC_EVTMASK0_EM16_OFFSET                                                 (UWORD8)(16)                                                                    

#define IC_EVTMASK0_EM17_MASK                                                   (UWORD32)(0x20000u)                                                             
#define IC_EVTMASK0_EM17_OFFSET                                                 (UWORD8)(17)                                                                    

#define IC_EVTMASK0_EM18_MASK                                                   (UWORD32)(0x40000u)                                                             
#define IC_EVTMASK0_EM18_OFFSET                                                 (UWORD8)(18)                                                                    

#define IC_EVTMASK0_EM19_MASK                                                   (UWORD32)(0x80000u)                                                             
#define IC_EVTMASK0_EM19_OFFSET                                                 (UWORD8)(19)                                                                    

#define IC_EVTMASK0_EM20_MASK                                                   (UWORD32)(0x100000u)                                                            
#define IC_EVTMASK0_EM20_OFFSET                                                 (UWORD8)(20)                                                                    

#define IC_EVTMASK0_EM21_MASK                                                   (UWORD32)(0x200000u)                                                            
#define IC_EVTMASK0_EM21_OFFSET                                                 (UWORD8)(21)                                                                    

#define IC_EVTMASK0_EM22_MASK                                                   (UWORD32)(0x400000u)                                                            
#define IC_EVTMASK0_EM22_OFFSET                                                 (UWORD8)(22)                                                                    

#define IC_EVTMASK0_EM23_MASK                                                   (UWORD32)(0x800000u)                                                            
#define IC_EVTMASK0_EM23_OFFSET                                                 (UWORD8)(23)                                                                    

#define IC_EVTMASK0_EM24_MASK                                                   (UWORD32)(0x1000000u)                                                           
#define IC_EVTMASK0_EM24_OFFSET                                                 (UWORD8)(24)                                                                    

#define IC_EVTMASK0_EM25_MASK                                                   (UWORD32)(0x2000000u)                                                           
#define IC_EVTMASK0_EM25_OFFSET                                                 (UWORD8)(25)                                                                    

#define IC_EVTMASK0_EM26_MASK                                                   (UWORD32)(0x4000000u)                                                           
#define IC_EVTMASK0_EM26_OFFSET                                                 (UWORD8)(26)                                                                    

#define IC_EVTMASK0_EM27_MASK                                                   (UWORD32)(0x8000000u)                                                           
#define IC_EVTMASK0_EM27_OFFSET                                                 (UWORD8)(27)                                                                    

#define IC_EVTMASK0_EM28_MASK                                                   (UWORD32)(0x10000000u)                                                          
#define IC_EVTMASK0_EM28_OFFSET                                                 (UWORD8)(28)                                                                    

#define IC_EVTMASK0_EM29_MASK                                                   (UWORD32)(0x20000000u)                                                          
#define IC_EVTMASK0_EM29_OFFSET                                                 (UWORD8)(29)                                                                    

#define IC_EVTMASK0_EM30_MASK                                                   (UWORD32)(0x40000000u)                                                          
#define IC_EVTMASK0_EM30_OFFSET                                                 (UWORD8)(30)                                                                    

#define IC_EVTMASK0_EM31_MASK                                                   (UWORD32)(0x80000000u)                                                          
#define IC_EVTMASK0_EM31_OFFSET                                                 (UWORD8)(31)                                                                    

#define IC_EVTMASK1_EM0_MASK                                                    (UWORD32)(0x1u)                                                                 
#define IC_EVTMASK1_EM0_OFFSET                                                  (UWORD8)(0)                                                                     

#define IC_EVTMASK1_EM1_MASK                                                    (UWORD32)(0x2u)                                                                 
#define IC_EVTMASK1_EM1_OFFSET                                                  (UWORD8)(1)                                                                     

#define IC_EVTMASK1_EM2_MASK                                                    (UWORD32)(0x4u)                                                                 
#define IC_EVTMASK1_EM2_OFFSET                                                  (UWORD8)(2)                                                                     

#define IC_EVTMASK1_EM3_MASK                                                    (UWORD32)(0x8u)                                                                 
#define IC_EVTMASK1_EM3_OFFSET                                                  (UWORD8)(3)                                                                     

#define IC_EVTMASK1_EM4_MASK                                                    (UWORD32)(0x10u)                                                                
#define IC_EVTMASK1_EM4_OFFSET                                                  (UWORD8)(4)                                                                     

#define IC_EVTMASK1_EM5_MASK                                                    (UWORD32)(0x20u)                                                                
#define IC_EVTMASK1_EM5_OFFSET                                                  (UWORD8)(5)                                                                     

#define IC_EVTMASK1_EM6_MASK                                                    (UWORD32)(0x40u)                                                                
#define IC_EVTMASK1_EM6_OFFSET                                                  (UWORD8)(6)                                                                     

#define IC_EVTMASK1_EM7_MASK                                                    (UWORD32)(0x80u)                                                                
#define IC_EVTMASK1_EM7_OFFSET                                                  (UWORD8)(7)                                                                     

#define IC_EVTMASK1_EM8_MASK                                                    (UWORD32)(0x100u)                                                               
#define IC_EVTMASK1_EM8_OFFSET                                                  (UWORD8)(8)                                                                     

#define IC_EVTMASK1_EM9_MASK                                                    (UWORD32)(0x200u)                                                               
#define IC_EVTMASK1_EM9_OFFSET                                                  (UWORD8)(9)                                                                     

#define IC_EVTMASK1_EM10_MASK                                                   (UWORD32)(0x400u)                                                               
#define IC_EVTMASK1_EM10_OFFSET                                                 (UWORD8)(10)                                                                    

#define IC_EVTMASK1_EM11_MASK                                                   (UWORD32)(0x800u)                                                               
#define IC_EVTMASK1_EM11_OFFSET                                                 (UWORD8)(11)                                                                    

#define IC_EVTMASK1_EM12_MASK                                                   (UWORD32)(0x1000u)                                                              
#define IC_EVTMASK1_EM12_OFFSET                                                 (UWORD8)(12)                                                                    

#define IC_EVTMASK1_EM13_MASK                                                   (UWORD32)(0x2000u)                                                              
#define IC_EVTMASK1_EM13_OFFSET                                                 (UWORD8)(13)                                                                    

#define IC_EVTMASK1_EM14_MASK                                                   (UWORD32)(0x4000u)                                                              
#define IC_EVTMASK1_EM14_OFFSET                                                 (UWORD8)(14)                                                                    

#define IC_EVTMASK1_EM15_MASK                                                   (UWORD32)(0x8000u)                                                              
#define IC_EVTMASK1_EM15_OFFSET                                                 (UWORD8)(15)                                                                    

#define IC_EVTMASK1_EM16_MASK                                                   (UWORD32)(0x10000u)                                                             
#define IC_EVTMASK1_EM16_OFFSET                                                 (UWORD8)(16)                                                                    

#define IC_EVTMASK1_EM17_MASK                                                   (UWORD32)(0x20000u)                                                             
#define IC_EVTMASK1_EM17_OFFSET                                                 (UWORD8)(17)                                                                    

#define IC_EVTMASK1_EM18_MASK                                                   (UWORD32)(0x40000u)                                                             
#define IC_EVTMASK1_EM18_OFFSET                                                 (UWORD8)(18)                                                                    

#define IC_EVTMASK1_EM19_MASK                                                   (UWORD32)(0x80000u)                                                             
#define IC_EVTMASK1_EM19_OFFSET                                                 (UWORD8)(19)                                                                    

#define IC_EVTMASK1_EM20_MASK                                                   (UWORD32)(0x100000u)                                                            
#define IC_EVTMASK1_EM20_OFFSET                                                 (UWORD8)(20)                                                                    

#define IC_EVTMASK1_EM21_MASK                                                   (UWORD32)(0x200000u)                                                            
#define IC_EVTMASK1_EM21_OFFSET                                                 (UWORD8)(21)                                                                    

#define IC_EVTMASK1_EM22_MASK                                                   (UWORD32)(0x400000u)                                                            
#define IC_EVTMASK1_EM22_OFFSET                                                 (UWORD8)(22)                                                                    

#define IC_EVTMASK1_EM23_MASK                                                   (UWORD32)(0x800000u)                                                            
#define IC_EVTMASK1_EM23_OFFSET                                                 (UWORD8)(23)                                                                    

#define IC_EVTMASK1_EM24_MASK                                                   (UWORD32)(0x1000000u)                                                           
#define IC_EVTMASK1_EM24_OFFSET                                                 (UWORD8)(24)                                                                    

#define IC_EVTMASK1_EM25_MASK                                                   (UWORD32)(0x2000000u)                                                           
#define IC_EVTMASK1_EM25_OFFSET                                                 (UWORD8)(25)                                                                    

#define IC_EVTMASK1_EM26_MASK                                                   (UWORD32)(0x4000000u)                                                           
#define IC_EVTMASK1_EM26_OFFSET                                                 (UWORD8)(26)                                                                    

#define IC_EVTMASK1_EM27_MASK                                                   (UWORD32)(0x8000000u)                                                           
#define IC_EVTMASK1_EM27_OFFSET                                                 (UWORD8)(27)                                                                    

#define IC_EVTMASK1_EM28_MASK                                                   (UWORD32)(0x10000000u)                                                          
#define IC_EVTMASK1_EM28_OFFSET                                                 (UWORD8)(28)                                                                    

#define IC_EVTMASK1_EM29_MASK                                                   (UWORD32)(0x20000000u)                                                          
#define IC_EVTMASK1_EM29_OFFSET                                                 (UWORD8)(29)                                                                    

#define IC_EVTMASK1_EM30_MASK                                                   (UWORD32)(0x40000000u)                                                          
#define IC_EVTMASK1_EM30_OFFSET                                                 (UWORD8)(30)                                                                    

#define IC_EVTMASK1_EM31_MASK                                                   (UWORD32)(0x80000000u)                                                          
#define IC_EVTMASK1_EM31_OFFSET                                                 (UWORD8)(31)                                                                    

#define IC_EVTMASK2_EM0_MASK                                                    (UWORD32)(0x1u)                                                                 
#define IC_EVTMASK2_EM0_OFFSET                                                  (UWORD8)(0)                                                                     

#define IC_EVTMASK2_EM1_MASK                                                    (UWORD32)(0x2u)                                                                 
#define IC_EVTMASK2_EM1_OFFSET                                                  (UWORD8)(1)                                                                     

#define IC_EVTMASK2_EM2_MASK                                                    (UWORD32)(0x4u)                                                                 
#define IC_EVTMASK2_EM2_OFFSET                                                  (UWORD8)(2)                                                                     

#define IC_EVTMASK2_EM3_MASK                                                    (UWORD32)(0x8u)                                                                 
#define IC_EVTMASK2_EM3_OFFSET                                                  (UWORD8)(3)                                                                     

#define IC_EVTMASK2_EM4_MASK                                                    (UWORD32)(0x10u)                                                                
#define IC_EVTMASK2_EM4_OFFSET                                                  (UWORD8)(4)                                                                     

#define IC_EVTMASK2_EM5_MASK                                                    (UWORD32)(0x20u)                                                                
#define IC_EVTMASK2_EM5_OFFSET                                                  (UWORD8)(5)                                                                     

#define IC_EVTMASK2_EM6_MASK                                                    (UWORD32)(0x40u)                                                                
#define IC_EVTMASK2_EM6_OFFSET                                                  (UWORD8)(6)                                                                     

#define IC_EVTMASK2_EM7_MASK                                                    (UWORD32)(0x80u)                                                                
#define IC_EVTMASK2_EM7_OFFSET                                                  (UWORD8)(7)                                                                     

#define IC_EVTMASK2_EM8_MASK                                                    (UWORD32)(0x100u)                                                               
#define IC_EVTMASK2_EM8_OFFSET                                                  (UWORD8)(8)                                                                     

#define IC_EVTMASK2_EM9_MASK                                                    (UWORD32)(0x200u)                                                               
#define IC_EVTMASK2_EM9_OFFSET                                                  (UWORD8)(9)                                                                     

#define IC_EVTMASK2_EM10_MASK                                                   (UWORD32)(0x400u)                                                               
#define IC_EVTMASK2_EM10_OFFSET                                                 (UWORD8)(10)                                                                    

#define IC_EVTMASK2_EM11_MASK                                                   (UWORD32)(0x800u)                                                               
#define IC_EVTMASK2_EM11_OFFSET                                                 (UWORD8)(11)                                                                    

#define IC_EVTMASK2_EM12_MASK                                                   (UWORD32)(0x1000u)                                                              
#define IC_EVTMASK2_EM12_OFFSET                                                 (UWORD8)(12)                                                                    

#define IC_EVTMASK2_EM13_MASK                                                   (UWORD32)(0x2000u)                                                              
#define IC_EVTMASK2_EM13_OFFSET                                                 (UWORD8)(13)                                                                    

#define IC_EVTMASK2_EM14_MASK                                                   (UWORD32)(0x4000u)                                                              
#define IC_EVTMASK2_EM14_OFFSET                                                 (UWORD8)(14)                                                                    

#define IC_EVTMASK2_EM15_MASK                                                   (UWORD32)(0x8000u)                                                              
#define IC_EVTMASK2_EM15_OFFSET                                                 (UWORD8)(15)                                                                    

#define IC_EVTMASK2_EM16_MASK                                                   (UWORD32)(0x10000u)                                                             
#define IC_EVTMASK2_EM16_OFFSET                                                 (UWORD8)(16)                                                                    

#define IC_EVTMASK2_EM17_MASK                                                   (UWORD32)(0x20000u)                                                             
#define IC_EVTMASK2_EM17_OFFSET                                                 (UWORD8)(17)                                                                    

#define IC_EVTMASK2_EM18_MASK                                                   (UWORD32)(0x40000u)                                                             
#define IC_EVTMASK2_EM18_OFFSET                                                 (UWORD8)(18)                                                                    

#define IC_EVTMASK2_EM19_MASK                                                   (UWORD32)(0x80000u)                                                             
#define IC_EVTMASK2_EM19_OFFSET                                                 (UWORD8)(19)                                                                    

#define IC_EVTMASK2_EM20_MASK                                                   (UWORD32)(0x100000u)                                                            
#define IC_EVTMASK2_EM20_OFFSET                                                 (UWORD8)(20)                                                                    

#define IC_EVTMASK2_EM21_MASK                                                   (UWORD32)(0x200000u)                                                            
#define IC_EVTMASK2_EM21_OFFSET                                                 (UWORD8)(21)                                                                    

#define IC_EVTMASK2_EM22_MASK                                                   (UWORD32)(0x400000u)                                                            
#define IC_EVTMASK2_EM22_OFFSET                                                 (UWORD8)(22)                                                                    

#define IC_EVTMASK2_EM23_MASK                                                   (UWORD32)(0x800000u)                                                            
#define IC_EVTMASK2_EM23_OFFSET                                                 (UWORD8)(23)                                                                    

#define IC_EVTMASK2_EM24_MASK                                                   (UWORD32)(0x1000000u)                                                           
#define IC_EVTMASK2_EM24_OFFSET                                                 (UWORD8)(24)                                                                    

#define IC_EVTMASK2_EM25_MASK                                                   (UWORD32)(0x2000000u)                                                           
#define IC_EVTMASK2_EM25_OFFSET                                                 (UWORD8)(25)                                                                    

#define IC_EVTMASK2_EM26_MASK                                                   (UWORD32)(0x4000000u)                                                           
#define IC_EVTMASK2_EM26_OFFSET                                                 (UWORD8)(26)                                                                    

#define IC_EVTMASK2_EM27_MASK                                                   (UWORD32)(0x8000000u)                                                           
#define IC_EVTMASK2_EM27_OFFSET                                                 (UWORD8)(27)                                                                    

#define IC_EVTMASK2_EM28_MASK                                                   (UWORD32)(0x10000000u)                                                          
#define IC_EVTMASK2_EM28_OFFSET                                                 (UWORD8)(28)                                                                    

#define IC_EVTMASK2_EM29_MASK                                                   (UWORD32)(0x20000000u)                                                          
#define IC_EVTMASK2_EM29_OFFSET                                                 (UWORD8)(29)                                                                    

#define IC_EVTMASK2_EM30_MASK                                                   (UWORD32)(0x40000000u)                                                          
#define IC_EVTMASK2_EM30_OFFSET                                                 (UWORD8)(30)                                                                    

#define IC_EVTMASK2_EM31_MASK                                                   (UWORD32)(0x80000000u)                                                          
#define IC_EVTMASK2_EM31_OFFSET                                                 (UWORD8)(31)                                                                    

#define IC_EVTMASK3_EM0_MASK                                                    (UWORD32)(0x1u)                                                                 
#define IC_EVTMASK3_EM0_OFFSET                                                  (UWORD8)(0)                                                                     

#define IC_EVTMASK3_EM1_MASK                                                    (UWORD32)(0x2u)                                                                 
#define IC_EVTMASK3_EM1_OFFSET                                                  (UWORD8)(1)                                                                     

#define IC_EVTMASK3_EM2_MASK                                                    (UWORD32)(0x4u)                                                                 
#define IC_EVTMASK3_EM2_OFFSET                                                  (UWORD8)(2)                                                                     

#define IC_EVTMASK3_EM3_MASK                                                    (UWORD32)(0x8u)                                                                 
#define IC_EVTMASK3_EM3_OFFSET                                                  (UWORD8)(3)                                                                     

#define IC_EVTMASK3_EM4_MASK                                                    (UWORD32)(0x10u)                                                                
#define IC_EVTMASK3_EM4_OFFSET                                                  (UWORD8)(4)                                                                     

#define IC_EVTMASK3_EM5_MASK                                                    (UWORD32)(0x20u)                                                                
#define IC_EVTMASK3_EM5_OFFSET                                                  (UWORD8)(5)                                                                     

#define IC_EVTMASK3_EM6_MASK                                                    (UWORD32)(0x40u)                                                                
#define IC_EVTMASK3_EM6_OFFSET                                                  (UWORD8)(6)                                                                     

#define IC_EVTMASK3_EM7_MASK                                                    (UWORD32)(0x80u)                                                                
#define IC_EVTMASK3_EM7_OFFSET                                                  (UWORD8)(7)                                                                     

#define IC_EVTMASK3_EM8_MASK                                                    (UWORD32)(0x100u)                                                               
#define IC_EVTMASK3_EM8_OFFSET                                                  (UWORD8)(8)                                                                     

#define IC_EVTMASK3_EM9_MASK                                                    (UWORD32)(0x200u)                                                               
#define IC_EVTMASK3_EM9_OFFSET                                                  (UWORD8)(9)                                                                     

#define IC_EVTMASK3_EM10_MASK                                                   (UWORD32)(0x400u)                                                               
#define IC_EVTMASK3_EM10_OFFSET                                                 (UWORD8)(10)                                                                    

#define IC_EVTMASK3_EM11_MASK                                                   (UWORD32)(0x800u)                                                               
#define IC_EVTMASK3_EM11_OFFSET                                                 (UWORD8)(11)                                                                    

#define IC_EVTMASK3_EM12_MASK                                                   (UWORD32)(0x1000u)                                                              
#define IC_EVTMASK3_EM12_OFFSET                                                 (UWORD8)(12)                                                                    

#define IC_EVTMASK3_EM13_MASK                                                   (UWORD32)(0x2000u)                                                              
#define IC_EVTMASK3_EM13_OFFSET                                                 (UWORD8)(13)                                                                    

#define IC_EVTMASK3_EM14_MASK                                                   (UWORD32)(0x4000u)                                                              
#define IC_EVTMASK3_EM14_OFFSET                                                 (UWORD8)(14)                                                                    

#define IC_EVTMASK3_EM15_MASK                                                   (UWORD32)(0x8000u)                                                              
#define IC_EVTMASK3_EM15_OFFSET                                                 (UWORD8)(15)                                                                    

#define IC_EVTMASK3_EM16_MASK                                                   (UWORD32)(0x10000u)                                                             
#define IC_EVTMASK3_EM16_OFFSET                                                 (UWORD8)(16)                                                                    

#define IC_EVTMASK3_EM17_MASK                                                   (UWORD32)(0x20000u)                                                             
#define IC_EVTMASK3_EM17_OFFSET                                                 (UWORD8)(17)                                                                    

#define IC_EVTMASK3_EM18_MASK                                                   (UWORD32)(0x40000u)                                                             
#define IC_EVTMASK3_EM18_OFFSET                                                 (UWORD8)(18)                                                                    

#define IC_EVTMASK3_EM19_MASK                                                   (UWORD32)(0x80000u)                                                             
#define IC_EVTMASK3_EM19_OFFSET                                                 (UWORD8)(19)                                                                    

#define IC_EVTMASK3_EM20_MASK                                                   (UWORD32)(0x100000u)                                                            
#define IC_EVTMASK3_EM20_OFFSET                                                 (UWORD8)(20)                                                                    

#define IC_EVTMASK3_EM21_MASK                                                   (UWORD32)(0x200000u)                                                            
#define IC_EVTMASK3_EM21_OFFSET                                                 (UWORD8)(21)                                                                    

#define IC_EVTMASK3_EM22_MASK                                                   (UWORD32)(0x400000u)                                                            
#define IC_EVTMASK3_EM22_OFFSET                                                 (UWORD8)(22)                                                                    

#define IC_EVTMASK3_EM23_MASK                                                   (UWORD32)(0x800000u)                                                            
#define IC_EVTMASK3_EM23_OFFSET                                                 (UWORD8)(23)                                                                    

#define IC_EVTMASK3_EM24_MASK                                                   (UWORD32)(0x1000000u)                                                           
#define IC_EVTMASK3_EM24_OFFSET                                                 (UWORD8)(24)                                                                    

#define IC_EVTMASK3_EM25_MASK                                                   (UWORD32)(0x2000000u)                                                           
#define IC_EVTMASK3_EM25_OFFSET                                                 (UWORD8)(25)                                                                    

#define IC_EVTMASK3_EM26_MASK                                                   (UWORD32)(0x4000000u)                                                           
#define IC_EVTMASK3_EM26_OFFSET                                                 (UWORD8)(26)                                                                    

#define IC_EVTMASK3_EM27_MASK                                                   (UWORD32)(0x8000000u)                                                           
#define IC_EVTMASK3_EM27_OFFSET                                                 (UWORD8)(27)                                                                    

#define IC_EVTMASK3_EM28_MASK                                                   (UWORD32)(0x10000000u)                                                          
#define IC_EVTMASK3_EM28_OFFSET                                                 (UWORD8)(28)                                                                    

#define IC_EVTMASK3_EM29_MASK                                                   (UWORD32)(0x20000000u)                                                          
#define IC_EVTMASK3_EM29_OFFSET                                                 (UWORD8)(29)                                                                    

#define IC_EVTMASK3_EM30_MASK                                                   (UWORD32)(0x40000000u)                                                          
#define IC_EVTMASK3_EM30_OFFSET                                                 (UWORD8)(30)                                                                    

#define IC_EVTMASK3_EM31_MASK                                                   (UWORD32)(0x80000000u)                                                          
#define IC_EVTMASK3_EM31_OFFSET                                                 (UWORD8)(31)                                                                    

#define IC_MEVTFLAG0_MEF0_MASK                                                  (UWORD32)(0x1u)                                                                 
#define IC_MEVTFLAG0_MEF0_OFFSET                                                (UWORD8)(0)                                                                     

#define IC_MEVTFLAG0_MEF1_MASK                                                  (UWORD32)(0x2u)                                                                 
#define IC_MEVTFLAG0_MEF1_OFFSET                                                (UWORD8)(1)                                                                     

#define IC_MEVTFLAG0_MEF2_MASK                                                  (UWORD32)(0x4u)                                                                 
#define IC_MEVTFLAG0_MEF2_OFFSET                                                (UWORD8)(2)                                                                     

#define IC_MEVTFLAG0_MEF3_MASK                                                  (UWORD32)(0x8u)                                                                 
#define IC_MEVTFLAG0_MEF3_OFFSET                                                (UWORD8)(3)                                                                     

#define IC_MEVTFLAG0_MEF4_MASK                                                  (UWORD32)(0x10u)                                                                
#define IC_MEVTFLAG0_MEF4_OFFSET                                                (UWORD8)(4)                                                                     

#define IC_MEVTFLAG0_MEF5_MASK                                                  (UWORD32)(0x20u)                                                                
#define IC_MEVTFLAG0_MEF5_OFFSET                                                (UWORD8)(5)                                                                     

#define IC_MEVTFLAG0_MEF6_MASK                                                  (UWORD32)(0x40u)                                                                
#define IC_MEVTFLAG0_MEF6_OFFSET                                                (UWORD8)(6)                                                                     

#define IC_MEVTFLAG0_MEF7_MASK                                                  (UWORD32)(0x80u)                                                                
#define IC_MEVTFLAG0_MEF7_OFFSET                                                (UWORD8)(7)                                                                     

#define IC_MEVTFLAG0_MEF8_MASK                                                  (UWORD32)(0x100u)                                                               
#define IC_MEVTFLAG0_MEF8_OFFSET                                                (UWORD8)(8)                                                                     

#define IC_MEVTFLAG0_MEF9_MASK                                                  (UWORD32)(0x200u)                                                               
#define IC_MEVTFLAG0_MEF9_OFFSET                                                (UWORD8)(9)                                                                     

#define IC_MEVTFLAG0_MEF10_MASK                                                 (UWORD32)(0x400u)                                                               
#define IC_MEVTFLAG0_MEF10_OFFSET                                               (UWORD8)(10)                                                                    

#define IC_MEVTFLAG0_MEF11_MASK                                                 (UWORD32)(0x800u)                                                               
#define IC_MEVTFLAG0_MEF11_OFFSET                                               (UWORD8)(11)                                                                    

#define IC_MEVTFLAG0_MEF12_MASK                                                 (UWORD32)(0x1000u)                                                              
#define IC_MEVTFLAG0_MEF12_OFFSET                                               (UWORD8)(12)                                                                    

#define IC_MEVTFLAG0_MEF13_MASK                                                 (UWORD32)(0x2000u)                                                              
#define IC_MEVTFLAG0_MEF13_OFFSET                                               (UWORD8)(13)                                                                    

#define IC_MEVTFLAG0_MEF14_MASK                                                 (UWORD32)(0x4000u)                                                              
#define IC_MEVTFLAG0_MEF14_OFFSET                                               (UWORD8)(14)                                                                    

#define IC_MEVTFLAG0_MEF15_MASK                                                 (UWORD32)(0x8000u)                                                              
#define IC_MEVTFLAG0_MEF15_OFFSET                                               (UWORD8)(15)                                                                    

#define IC_MEVTFLAG0_MEF16_MASK                                                 (UWORD32)(0x10000u)                                                             
#define IC_MEVTFLAG0_MEF16_OFFSET                                               (UWORD8)(16)                                                                    

#define IC_MEVTFLAG0_MEF17_MASK                                                 (UWORD32)(0x20000u)                                                             
#define IC_MEVTFLAG0_MEF17_OFFSET                                               (UWORD8)(17)                                                                    

#define IC_MEVTFLAG0_MEF18_MASK                                                 (UWORD32)(0x40000u)                                                             
#define IC_MEVTFLAG0_MEF18_OFFSET                                               (UWORD8)(18)                                                                    

#define IC_MEVTFLAG0_MEF19_MASK                                                 (UWORD32)(0x80000u)                                                             
#define IC_MEVTFLAG0_MEF19_OFFSET                                               (UWORD8)(19)                                                                    

#define IC_MEVTFLAG0_MEF20_MASK                                                 (UWORD32)(0x100000u)                                                            
#define IC_MEVTFLAG0_MEF20_OFFSET                                               (UWORD8)(20)                                                                    

#define IC_MEVTFLAG0_MEF21_MASK                                                 (UWORD32)(0x200000u)                                                            
#define IC_MEVTFLAG0_MEF21_OFFSET                                               (UWORD8)(21)                                                                    

#define IC_MEVTFLAG0_MEF22_MASK                                                 (UWORD32)(0x400000u)                                                            
#define IC_MEVTFLAG0_MEF22_OFFSET                                               (UWORD8)(22)                                                                    

#define IC_MEVTFLAG0_MEF23_MASK                                                 (UWORD32)(0x800000u)                                                            
#define IC_MEVTFLAG0_MEF23_OFFSET                                               (UWORD8)(23)                                                                    

#define IC_MEVTFLAG0_MEF24_MASK                                                 (UWORD32)(0x1000000u)                                                           
#define IC_MEVTFLAG0_MEF24_OFFSET                                               (UWORD8)(24)                                                                    

#define IC_MEVTFLAG0_MEF25_MASK                                                 (UWORD32)(0x2000000u)                                                           
#define IC_MEVTFLAG0_MEF25_OFFSET                                               (UWORD8)(25)                                                                    

#define IC_MEVTFLAG0_MEF26_MASK                                                 (UWORD32)(0x4000000u)                                                           
#define IC_MEVTFLAG0_MEF26_OFFSET                                               (UWORD8)(26)                                                                    

#define IC_MEVTFLAG0_MEF27_MASK                                                 (UWORD32)(0x8000000u)                                                           
#define IC_MEVTFLAG0_MEF27_OFFSET                                               (UWORD8)(27)                                                                    

#define IC_MEVTFLAG0_MEF28_MASK                                                 (UWORD32)(0x10000000u)                                                          
#define IC_MEVTFLAG0_MEF28_OFFSET                                               (UWORD8)(28)                                                                    

#define IC_MEVTFLAG0_MEF29_MASK                                                 (UWORD32)(0x20000000u)                                                          
#define IC_MEVTFLAG0_MEF29_OFFSET                                               (UWORD8)(29)                                                                    

#define IC_MEVTFLAG0_MEF30_MASK                                                 (UWORD32)(0x40000000u)                                                          
#define IC_MEVTFLAG0_MEF30_OFFSET                                               (UWORD8)(30)                                                                    

#define IC_MEVTFLAG0_MEF31_MASK                                                 (UWORD32)(0x80000000u)                                                          
#define IC_MEVTFLAG0_MEF31_OFFSET                                               (UWORD8)(31)                                                                    

#define IC_MEVTFLAG1_MEF0_MASK                                                  (UWORD32)(0x1u)                                                                 
#define IC_MEVTFLAG1_MEF0_OFFSET                                                (UWORD8)(0)                                                                     

#define IC_MEVTFLAG1_MEF1_MASK                                                  (UWORD32)(0x2u)                                                                 
#define IC_MEVTFLAG1_MEF1_OFFSET                                                (UWORD8)(1)                                                                     

#define IC_MEVTFLAG1_MEF2_MASK                                                  (UWORD32)(0x4u)                                                                 
#define IC_MEVTFLAG1_MEF2_OFFSET                                                (UWORD8)(2)                                                                     

#define IC_MEVTFLAG1_MEF3_MASK                                                  (UWORD32)(0x8u)                                                                 
#define IC_MEVTFLAG1_MEF3_OFFSET                                                (UWORD8)(3)                                                                     

#define IC_MEVTFLAG1_MEF4_MASK                                                  (UWORD32)(0x10u)                                                                
#define IC_MEVTFLAG1_MEF4_OFFSET                                                (UWORD8)(4)                                                                     

#define IC_MEVTFLAG1_MEF5_MASK                                                  (UWORD32)(0x20u)                                                                
#define IC_MEVTFLAG1_MEF5_OFFSET                                                (UWORD8)(5)                                                                     

#define IC_MEVTFLAG1_MEF6_MASK                                                  (UWORD32)(0x40u)                                                                
#define IC_MEVTFLAG1_MEF6_OFFSET                                                (UWORD8)(6)                                                                     

#define IC_MEVTFLAG1_MEF7_MASK                                                  (UWORD32)(0x80u)                                                                
#define IC_MEVTFLAG1_MEF7_OFFSET                                                (UWORD8)(7)                                                                     

#define IC_MEVTFLAG1_MEF8_MASK                                                  (UWORD32)(0x100u)                                                               
#define IC_MEVTFLAG1_MEF8_OFFSET                                                (UWORD8)(8)                                                                     

#define IC_MEVTFLAG1_MEF9_MASK                                                  (UWORD32)(0x200u)                                                               
#define IC_MEVTFLAG1_MEF9_OFFSET                                                (UWORD8)(9)                                                                     

#define IC_MEVTFLAG1_MEF10_MASK                                                 (UWORD32)(0x400u)                                                               
#define IC_MEVTFLAG1_MEF10_OFFSET                                               (UWORD8)(10)                                                                    

#define IC_MEVTFLAG1_MEF11_MASK                                                 (UWORD32)(0x800u)                                                               
#define IC_MEVTFLAG1_MEF11_OFFSET                                               (UWORD8)(11)                                                                    

#define IC_MEVTFLAG1_MEF12_MASK                                                 (UWORD32)(0x1000u)                                                              
#define IC_MEVTFLAG1_MEF12_OFFSET                                               (UWORD8)(12)                                                                    

#define IC_MEVTFLAG1_MEF13_MASK                                                 (UWORD32)(0x2000u)                                                              
#define IC_MEVTFLAG1_MEF13_OFFSET                                               (UWORD8)(13)                                                                    

#define IC_MEVTFLAG1_MEF14_MASK                                                 (UWORD32)(0x4000u)                                                              
#define IC_MEVTFLAG1_MEF14_OFFSET                                               (UWORD8)(14)                                                                    

#define IC_MEVTFLAG1_MEF15_MASK                                                 (UWORD32)(0x8000u)                                                              
#define IC_MEVTFLAG1_MEF15_OFFSET                                               (UWORD8)(15)                                                                    

#define IC_MEVTFLAG1_MEF16_MASK                                                 (UWORD32)(0x10000u)                                                             
#define IC_MEVTFLAG1_MEF16_OFFSET                                               (UWORD8)(16)                                                                    

#define IC_MEVTFLAG1_MEF17_MASK                                                 (UWORD32)(0x20000u)                                                             
#define IC_MEVTFLAG1_MEF17_OFFSET                                               (UWORD8)(17)                                                                    

#define IC_MEVTFLAG1_MEF18_MASK                                                 (UWORD32)(0x40000u)                                                             
#define IC_MEVTFLAG1_MEF18_OFFSET                                               (UWORD8)(18)                                                                    

#define IC_MEVTFLAG1_MEF19_MASK                                                 (UWORD32)(0x80000u)                                                             
#define IC_MEVTFLAG1_MEF19_OFFSET                                               (UWORD8)(19)                                                                    

#define IC_MEVTFLAG1_MEF20_MASK                                                 (UWORD32)(0x100000u)                                                            
#define IC_MEVTFLAG1_MEF20_OFFSET                                               (UWORD8)(20)                                                                    

#define IC_MEVTFLAG1_MEF21_MASK                                                 (UWORD32)(0x200000u)                                                            
#define IC_MEVTFLAG1_MEF21_OFFSET                                               (UWORD8)(21)                                                                    

#define IC_MEVTFLAG1_MEF22_MASK                                                 (UWORD32)(0x400000u)                                                            
#define IC_MEVTFLAG1_MEF22_OFFSET                                               (UWORD8)(22)                                                                    

#define IC_MEVTFLAG1_MEF23_MASK                                                 (UWORD32)(0x800000u)                                                            
#define IC_MEVTFLAG1_MEF23_OFFSET                                               (UWORD8)(23)                                                                    

#define IC_MEVTFLAG1_MEF24_MASK                                                 (UWORD32)(0x1000000u)                                                           
#define IC_MEVTFLAG1_MEF24_OFFSET                                               (UWORD8)(24)                                                                    

#define IC_MEVTFLAG1_MEF25_MASK                                                 (UWORD32)(0x2000000u)                                                           
#define IC_MEVTFLAG1_MEF25_OFFSET                                               (UWORD8)(25)                                                                    

#define IC_MEVTFLAG1_MEF26_MASK                                                 (UWORD32)(0x4000000u)                                                           
#define IC_MEVTFLAG1_MEF26_OFFSET                                               (UWORD8)(26)                                                                    

#define IC_MEVTFLAG1_MEF27_MASK                                                 (UWORD32)(0x8000000u)                                                           
#define IC_MEVTFLAG1_MEF27_OFFSET                                               (UWORD8)(27)                                                                    

#define IC_MEVTFLAG1_MEF28_MASK                                                 (UWORD32)(0x10000000u)                                                          
#define IC_MEVTFLAG1_MEF28_OFFSET                                               (UWORD8)(28)                                                                    

#define IC_MEVTFLAG1_MEF29_MASK                                                 (UWORD32)(0x20000000u)                                                          
#define IC_MEVTFLAG1_MEF29_OFFSET                                               (UWORD8)(29)                                                                    

#define IC_MEVTFLAG1_MEF30_MASK                                                 (UWORD32)(0x40000000u)                                                          
#define IC_MEVTFLAG1_MEF30_OFFSET                                               (UWORD8)(30)                                                                    

#define IC_MEVTFLAG1_MEF31_MASK                                                 (UWORD32)(0x80000000u)                                                          
#define IC_MEVTFLAG1_MEF31_OFFSET                                               (UWORD8)(31)                                                                    

#define IC_MEVTFLAG2_MEF0_MASK                                                  (UWORD32)(0x1u)                                                                 
#define IC_MEVTFLAG2_MEF0_OFFSET                                                (UWORD8)(0)                                                                     

#define IC_MEVTFLAG2_MEF1_MASK                                                  (UWORD32)(0x2u)                                                                 
#define IC_MEVTFLAG2_MEF1_OFFSET                                                (UWORD8)(1)                                                                     

#define IC_MEVTFLAG2_MEF2_MASK                                                  (UWORD32)(0x4u)                                                                 
#define IC_MEVTFLAG2_MEF2_OFFSET                                                (UWORD8)(2)                                                                     

#define IC_MEVTFLAG2_MEF3_MASK                                                  (UWORD32)(0x8u)                                                                 
#define IC_MEVTFLAG2_MEF3_OFFSET                                                (UWORD8)(3)                                                                     

#define IC_MEVTFLAG2_MEF4_MASK                                                  (UWORD32)(0x10u)                                                                
#define IC_MEVTFLAG2_MEF4_OFFSET                                                (UWORD8)(4)                                                                     

#define IC_MEVTFLAG2_MEF5_MASK                                                  (UWORD32)(0x20u)                                                                
#define IC_MEVTFLAG2_MEF5_OFFSET                                                (UWORD8)(5)                                                                     

#define IC_MEVTFLAG2_MEF6_MASK                                                  (UWORD32)(0x40u)                                                                
#define IC_MEVTFLAG2_MEF6_OFFSET                                                (UWORD8)(6)                                                                     

#define IC_MEVTFLAG2_MEF7_MASK                                                  (UWORD32)(0x80u)                                                                
#define IC_MEVTFLAG2_MEF7_OFFSET                                                (UWORD8)(7)                                                                     

#define IC_MEVTFLAG2_MEF8_MASK                                                  (UWORD32)(0x100u)                                                               
#define IC_MEVTFLAG2_MEF8_OFFSET                                                (UWORD8)(8)                                                                     

#define IC_MEVTFLAG2_MEF9_MASK                                                  (UWORD32)(0x200u)                                                               
#define IC_MEVTFLAG2_MEF9_OFFSET                                                (UWORD8)(9)                                                                     

#define IC_MEVTFLAG2_MEF10_MASK                                                 (UWORD32)(0x400u)                                                               
#define IC_MEVTFLAG2_MEF10_OFFSET                                               (UWORD8)(10)                                                                    

#define IC_MEVTFLAG2_MEF11_MASK                                                 (UWORD32)(0x800u)                                                               
#define IC_MEVTFLAG2_MEF11_OFFSET                                               (UWORD8)(11)                                                                    

#define IC_MEVTFLAG2_MEF12_MASK                                                 (UWORD32)(0x1000u)                                                              
#define IC_MEVTFLAG2_MEF12_OFFSET                                               (UWORD8)(12)                                                                    

#define IC_MEVTFLAG2_MEF13_MASK                                                 (UWORD32)(0x2000u)                                                              
#define IC_MEVTFLAG2_MEF13_OFFSET                                               (UWORD8)(13)                                                                    

#define IC_MEVTFLAG2_MEF14_MASK                                                 (UWORD32)(0x4000u)                                                              
#define IC_MEVTFLAG2_MEF14_OFFSET                                               (UWORD8)(14)                                                                    

#define IC_MEVTFLAG2_MEF15_MASK                                                 (UWORD32)(0x8000u)                                                              
#define IC_MEVTFLAG2_MEF15_OFFSET                                               (UWORD8)(15)                                                                    

#define IC_MEVTFLAG2_MEF16_MASK                                                 (UWORD32)(0x10000u)                                                             
#define IC_MEVTFLAG2_MEF16_OFFSET                                               (UWORD8)(16)                                                                    

#define IC_MEVTFLAG2_MEF17_MASK                                                 (UWORD32)(0x20000u)                                                             
#define IC_MEVTFLAG2_MEF17_OFFSET                                               (UWORD8)(17)                                                                    

#define IC_MEVTFLAG2_MEF18_MASK                                                 (UWORD32)(0x40000u)                                                             
#define IC_MEVTFLAG2_MEF18_OFFSET                                               (UWORD8)(18)                                                                    

#define IC_MEVTFLAG2_MEF19_MASK                                                 (UWORD32)(0x80000u)                                                             
#define IC_MEVTFLAG2_MEF19_OFFSET                                               (UWORD8)(19)                                                                    

#define IC_MEVTFLAG2_MEF20_MASK                                                 (UWORD32)(0x100000u)                                                            
#define IC_MEVTFLAG2_MEF20_OFFSET                                               (UWORD8)(20)                                                                    

#define IC_MEVTFLAG2_MEF21_MASK                                                 (UWORD32)(0x200000u)                                                            
#define IC_MEVTFLAG2_MEF21_OFFSET                                               (UWORD8)(21)                                                                    

#define IC_MEVTFLAG2_MEF22_MASK                                                 (UWORD32)(0x400000u)                                                            
#define IC_MEVTFLAG2_MEF22_OFFSET                                               (UWORD8)(22)                                                                    

#define IC_MEVTFLAG2_MEF23_MASK                                                 (UWORD32)(0x800000u)                                                            
#define IC_MEVTFLAG2_MEF23_OFFSET                                               (UWORD8)(23)                                                                    

#define IC_MEVTFLAG2_MEF24_MASK                                                 (UWORD32)(0x1000000u)                                                           
#define IC_MEVTFLAG2_MEF24_OFFSET                                               (UWORD8)(24)                                                                    

#define IC_MEVTFLAG2_MEF25_MASK                                                 (UWORD32)(0x2000000u)                                                           
#define IC_MEVTFLAG2_MEF25_OFFSET                                               (UWORD8)(25)                                                                    

#define IC_MEVTFLAG2_MEF26_MASK                                                 (UWORD32)(0x4000000u)                                                           
#define IC_MEVTFLAG2_MEF26_OFFSET                                               (UWORD8)(26)                                                                    

#define IC_MEVTFLAG2_MEF27_MASK                                                 (UWORD32)(0x8000000u)                                                           
#define IC_MEVTFLAG2_MEF27_OFFSET                                               (UWORD8)(27)                                                                    

#define IC_MEVTFLAG2_MEF28_MASK                                                 (UWORD32)(0x10000000u)                                                          
#define IC_MEVTFLAG2_MEF28_OFFSET                                               (UWORD8)(28)                                                                    

#define IC_MEVTFLAG2_MEF29_MASK                                                 (UWORD32)(0x20000000u)                                                          
#define IC_MEVTFLAG2_MEF29_OFFSET                                               (UWORD8)(29)                                                                    

#define IC_MEVTFLAG2_MEF30_MASK                                                 (UWORD32)(0x40000000u)                                                          
#define IC_MEVTFLAG2_MEF30_OFFSET                                               (UWORD8)(30)                                                                    

#define IC_MEVTFLAG2_MEF31_MASK                                                 (UWORD32)(0x80000000u)                                                          
#define IC_MEVTFLAG2_MEF31_OFFSET                                               (UWORD8)(31)                                                                    

#define IC_MEVTFLAG3_MEF0_MASK                                                  (UWORD32)(0x1u)                                                                 
#define IC_MEVTFLAG3_MEF0_OFFSET                                                (UWORD8)(0)                                                                     

#define IC_MEVTFLAG3_MEF1_MASK                                                  (UWORD32)(0x2u)                                                                 
#define IC_MEVTFLAG3_MEF1_OFFSET                                                (UWORD8)(1)                                                                     

#define IC_MEVTFLAG3_MEF2_MASK                                                  (UWORD32)(0x4u)                                                                 
#define IC_MEVTFLAG3_MEF2_OFFSET                                                (UWORD8)(2)                                                                     

#define IC_MEVTFLAG3_MEF3_MASK                                                  (UWORD32)(0x8u)                                                                 
#define IC_MEVTFLAG3_MEF3_OFFSET                                                (UWORD8)(3)                                                                     

#define IC_MEVTFLAG3_MEF4_MASK                                                  (UWORD32)(0x10u)                                                                
#define IC_MEVTFLAG3_MEF4_OFFSET                                                (UWORD8)(4)                                                                     

#define IC_MEVTFLAG3_MEF5_MASK                                                  (UWORD32)(0x20u)                                                                
#define IC_MEVTFLAG3_MEF5_OFFSET                                                (UWORD8)(5)                                                                     

#define IC_MEVTFLAG3_MEF6_MASK                                                  (UWORD32)(0x40u)                                                                
#define IC_MEVTFLAG3_MEF6_OFFSET                                                (UWORD8)(6)                                                                     

#define IC_MEVTFLAG3_MEF7_MASK                                                  (UWORD32)(0x80u)                                                                
#define IC_MEVTFLAG3_MEF7_OFFSET                                                (UWORD8)(7)                                                                     

#define IC_MEVTFLAG3_MEF8_MASK                                                  (UWORD32)(0x100u)                                                               
#define IC_MEVTFLAG3_MEF8_OFFSET                                                (UWORD8)(8)                                                                     

#define IC_MEVTFLAG3_MEF9_MASK                                                  (UWORD32)(0x200u)                                                               
#define IC_MEVTFLAG3_MEF9_OFFSET                                                (UWORD8)(9)                                                                     

#define IC_MEVTFLAG3_MEF10_MASK                                                 (UWORD32)(0x400u)                                                               
#define IC_MEVTFLAG3_MEF10_OFFSET                                               (UWORD8)(10)                                                                    

#define IC_MEVTFLAG3_MEF11_MASK                                                 (UWORD32)(0x800u)                                                               
#define IC_MEVTFLAG3_MEF11_OFFSET                                               (UWORD8)(11)                                                                    

#define IC_MEVTFLAG3_MEF12_MASK                                                 (UWORD32)(0x1000u)                                                              
#define IC_MEVTFLAG3_MEF12_OFFSET                                               (UWORD8)(12)                                                                    

#define IC_MEVTFLAG3_MEF13_MASK                                                 (UWORD32)(0x2000u)                                                              
#define IC_MEVTFLAG3_MEF13_OFFSET                                               (UWORD8)(13)                                                                    

#define IC_MEVTFLAG3_MEF14_MASK                                                 (UWORD32)(0x4000u)                                                              
#define IC_MEVTFLAG3_MEF14_OFFSET                                               (UWORD8)(14)                                                                    

#define IC_MEVTFLAG3_MEF15_MASK                                                 (UWORD32)(0x8000u)                                                              
#define IC_MEVTFLAG3_MEF15_OFFSET                                               (UWORD8)(15)                                                                    

#define IC_MEVTFLAG3_MEF16_MASK                                                 (UWORD32)(0x10000u)                                                             
#define IC_MEVTFLAG3_MEF16_OFFSET                                               (UWORD8)(16)                                                                    

#define IC_MEVTFLAG3_MEF17_MASK                                                 (UWORD32)(0x20000u)                                                             
#define IC_MEVTFLAG3_MEF17_OFFSET                                               (UWORD8)(17)                                                                    

#define IC_MEVTFLAG3_MEF18_MASK                                                 (UWORD32)(0x40000u)                                                             
#define IC_MEVTFLAG3_MEF18_OFFSET                                               (UWORD8)(18)                                                                    

#define IC_MEVTFLAG3_MEF19_MASK                                                 (UWORD32)(0x80000u)                                                             
#define IC_MEVTFLAG3_MEF19_OFFSET                                               (UWORD8)(19)                                                                    

#define IC_MEVTFLAG3_MEF20_MASK                                                 (UWORD32)(0x100000u)                                                            
#define IC_MEVTFLAG3_MEF20_OFFSET                                               (UWORD8)(20)                                                                    

#define IC_MEVTFLAG3_MEF21_MASK                                                 (UWORD32)(0x200000u)                                                            
#define IC_MEVTFLAG3_MEF21_OFFSET                                               (UWORD8)(21)                                                                    

#define IC_MEVTFLAG3_MEF22_MASK                                                 (UWORD32)(0x400000u)                                                            
#define IC_MEVTFLAG3_MEF22_OFFSET                                               (UWORD8)(22)                                                                    

#define IC_MEVTFLAG3_MEF23_MASK                                                 (UWORD32)(0x800000u)                                                            
#define IC_MEVTFLAG3_MEF23_OFFSET                                               (UWORD8)(23)                                                                    

#define IC_MEVTFLAG3_MEF24_MASK                                                 (UWORD32)(0x1000000u)                                                           
#define IC_MEVTFLAG3_MEF24_OFFSET                                               (UWORD8)(24)                                                                    

#define IC_MEVTFLAG3_MEF25_MASK                                                 (UWORD32)(0x2000000u)                                                           
#define IC_MEVTFLAG3_MEF25_OFFSET                                               (UWORD8)(25)                                                                    

#define IC_MEVTFLAG3_MEF26_MASK                                                 (UWORD32)(0x4000000u)                                                           
#define IC_MEVTFLAG3_MEF26_OFFSET                                               (UWORD8)(26)                                                                    

#define IC_MEVTFLAG3_MEF27_MASK                                                 (UWORD32)(0x8000000u)                                                           
#define IC_MEVTFLAG3_MEF27_OFFSET                                               (UWORD8)(27)                                                                    

#define IC_MEVTFLAG3_MEF28_MASK                                                 (UWORD32)(0x10000000u)                                                          
#define IC_MEVTFLAG3_MEF28_OFFSET                                               (UWORD8)(28)                                                                    

#define IC_MEVTFLAG3_MEF29_MASK                                                 (UWORD32)(0x20000000u)                                                          
#define IC_MEVTFLAG3_MEF29_OFFSET                                               (UWORD8)(29)                                                                    

#define IC_MEVTFLAG3_MEF30_MASK                                                 (UWORD32)(0x40000000u)                                                          
#define IC_MEVTFLAG3_MEF30_OFFSET                                               (UWORD8)(30)                                                                    

#define IC_MEVTFLAG3_MEF31_MASK                                                 (UWORD32)(0x80000000u)                                                          
#define IC_MEVTFLAG3_MEF31_OFFSET                                               (UWORD8)(31)                                                                    

#define IC_EXPMASK0_XM0_MASK                                                    (UWORD32)(0x1u)                                                                 
#define IC_EXPMASK0_XM0_OFFSET                                                  (UWORD8)(0)                                                                     

#define IC_EXPMASK0_XM1_MASK                                                    (UWORD32)(0x2u)                                                                 
#define IC_EXPMASK0_XM1_OFFSET                                                  (UWORD8)(1)                                                                     

#define IC_EXPMASK0_XM2_MASK                                                    (UWORD32)(0x4u)                                                                 
#define IC_EXPMASK0_XM2_OFFSET                                                  (UWORD8)(2)                                                                     

#define IC_EXPMASK0_XM3_MASK                                                    (UWORD32)(0x8u)                                                                 
#define IC_EXPMASK0_XM3_OFFSET                                                  (UWORD8)(3)                                                                     

#define IC_EXPMASK0_XM4_MASK                                                    (UWORD32)(0x10u)                                                                
#define IC_EXPMASK0_XM4_OFFSET                                                  (UWORD8)(4)                                                                     

#define IC_EXPMASK0_XM5_MASK                                                    (UWORD32)(0x20u)                                                                
#define IC_EXPMASK0_XM5_OFFSET                                                  (UWORD8)(5)                                                                     

#define IC_EXPMASK0_XM6_MASK                                                    (UWORD32)(0x40u)                                                                
#define IC_EXPMASK0_XM6_OFFSET                                                  (UWORD8)(6)                                                                     

#define IC_EXPMASK0_XM7_MASK                                                    (UWORD32)(0x80u)                                                                
#define IC_EXPMASK0_XM7_OFFSET                                                  (UWORD8)(7)                                                                     

#define IC_EXPMASK0_XM8_MASK                                                    (UWORD32)(0x100u)                                                               
#define IC_EXPMASK0_XM8_OFFSET                                                  (UWORD8)(8)                                                                     

#define IC_EXPMASK0_XM9_MASK                                                    (UWORD32)(0x200u)                                                               
#define IC_EXPMASK0_XM9_OFFSET                                                  (UWORD8)(9)                                                                     

#define IC_EXPMASK0_XM10_MASK                                                   (UWORD32)(0x400u)                                                               
#define IC_EXPMASK0_XM10_OFFSET                                                 (UWORD8)(10)                                                                    

#define IC_EXPMASK0_XM11_MASK                                                   (UWORD32)(0x800u)                                                               
#define IC_EXPMASK0_XM11_OFFSET                                                 (UWORD8)(11)                                                                    

#define IC_EXPMASK0_XM12_MASK                                                   (UWORD32)(0x1000u)                                                              
#define IC_EXPMASK0_XM12_OFFSET                                                 (UWORD8)(12)                                                                    

#define IC_EXPMASK0_XM13_MASK                                                   (UWORD32)(0x2000u)                                                              
#define IC_EXPMASK0_XM13_OFFSET                                                 (UWORD8)(13)                                                                    

#define IC_EXPMASK0_XM14_MASK                                                   (UWORD32)(0x4000u)                                                              
#define IC_EXPMASK0_XM14_OFFSET                                                 (UWORD8)(14)                                                                    

#define IC_EXPMASK0_XM15_MASK                                                   (UWORD32)(0x8000u)                                                              
#define IC_EXPMASK0_XM15_OFFSET                                                 (UWORD8)(15)                                                                    

#define IC_EXPMASK0_XM16_MASK                                                   (UWORD32)(0x10000u)                                                             
#define IC_EXPMASK0_XM16_OFFSET                                                 (UWORD8)(16)                                                                    

#define IC_EXPMASK0_XM17_MASK                                                   (UWORD32)(0x20000u)                                                             
#define IC_EXPMASK0_XM17_OFFSET                                                 (UWORD8)(17)                                                                    

#define IC_EXPMASK0_XM18_MASK                                                   (UWORD32)(0x40000u)                                                             
#define IC_EXPMASK0_XM18_OFFSET                                                 (UWORD8)(18)                                                                    

#define IC_EXPMASK0_XM19_MASK                                                   (UWORD32)(0x80000u)                                                             
#define IC_EXPMASK0_XM19_OFFSET                                                 (UWORD8)(19)                                                                    

#define IC_EXPMASK0_XM20_MASK                                                   (UWORD32)(0x100000u)                                                            
#define IC_EXPMASK0_XM20_OFFSET                                                 (UWORD8)(20)                                                                    

#define IC_EXPMASK0_XM21_MASK                                                   (UWORD32)(0x200000u)                                                            
#define IC_EXPMASK0_XM21_OFFSET                                                 (UWORD8)(21)                                                                    

#define IC_EXPMASK0_XM22_MASK                                                   (UWORD32)(0x400000u)                                                            
#define IC_EXPMASK0_XM22_OFFSET                                                 (UWORD8)(22)                                                                    

#define IC_EXPMASK0_XM23_MASK                                                   (UWORD32)(0x800000u)                                                            
#define IC_EXPMASK0_XM23_OFFSET                                                 (UWORD8)(23)                                                                    

#define IC_EXPMASK0_XM24_MASK                                                   (UWORD32)(0x1000000u)                                                           
#define IC_EXPMASK0_XM24_OFFSET                                                 (UWORD8)(24)                                                                    

#define IC_EXPMASK0_XM25_MASK                                                   (UWORD32)(0x2000000u)                                                           
#define IC_EXPMASK0_XM25_OFFSET                                                 (UWORD8)(25)                                                                    

#define IC_EXPMASK0_XM26_MASK                                                   (UWORD32)(0x4000000u)                                                           
#define IC_EXPMASK0_XM26_OFFSET                                                 (UWORD8)(26)                                                                    

#define IC_EXPMASK0_XM27_MASK                                                   (UWORD32)(0x8000000u)                                                           
#define IC_EXPMASK0_XM27_OFFSET                                                 (UWORD8)(27)                                                                    

#define IC_EXPMASK0_XM28_MASK                                                   (UWORD32)(0x10000000u)                                                          
#define IC_EXPMASK0_XM28_OFFSET                                                 (UWORD8)(28)                                                                    

#define IC_EXPMASK0_XM29_MASK                                                   (UWORD32)(0x20000000u)                                                          
#define IC_EXPMASK0_XM29_OFFSET                                                 (UWORD8)(29)                                                                    

#define IC_EXPMASK0_XM30_MASK                                                   (UWORD32)(0x40000000u)                                                          
#define IC_EXPMASK0_XM30_OFFSET                                                 (UWORD8)(30)                                                                    

#define IC_EXPMASK0_XM31_MASK                                                   (UWORD32)(0x80000000u)                                                          
#define IC_EXPMASK0_XM31_OFFSET                                                 (UWORD8)(31)                                                                    

#define IC_EXPMASK1_XM0_MASK                                                    (UWORD32)(0x1u)                                                                 
#define IC_EXPMASK1_XM0_OFFSET                                                  (UWORD8)(0)                                                                     

#define IC_EXPMASK1_XM1_MASK                                                    (UWORD32)(0x2u)                                                                 
#define IC_EXPMASK1_XM1_OFFSET                                                  (UWORD8)(1)                                                                     

#define IC_EXPMASK1_XM2_MASK                                                    (UWORD32)(0x4u)                                                                 
#define IC_EXPMASK1_XM2_OFFSET                                                  (UWORD8)(2)                                                                     

#define IC_EXPMASK1_XM3_MASK                                                    (UWORD32)(0x8u)                                                                 
#define IC_EXPMASK1_XM3_OFFSET                                                  (UWORD8)(3)                                                                     

#define IC_EXPMASK1_XM4_MASK                                                    (UWORD32)(0x10u)                                                                
#define IC_EXPMASK1_XM4_OFFSET                                                  (UWORD8)(4)                                                                     

#define IC_EXPMASK1_XM5_MASK                                                    (UWORD32)(0x20u)                                                                
#define IC_EXPMASK1_XM5_OFFSET                                                  (UWORD8)(5)                                                                     

#define IC_EXPMASK1_XM6_MASK                                                    (UWORD32)(0x40u)                                                                
#define IC_EXPMASK1_XM6_OFFSET                                                  (UWORD8)(6)                                                                     

#define IC_EXPMASK1_XM7_MASK                                                    (UWORD32)(0x80u)                                                                
#define IC_EXPMASK1_XM7_OFFSET                                                  (UWORD8)(7)                                                                     

#define IC_EXPMASK1_XM8_MASK                                                    (UWORD32)(0x100u)                                                               
#define IC_EXPMASK1_XM8_OFFSET                                                  (UWORD8)(8)                                                                     

#define IC_EXPMASK1_XM9_MASK                                                    (UWORD32)(0x200u)                                                               
#define IC_EXPMASK1_XM9_OFFSET                                                  (UWORD8)(9)                                                                     

#define IC_EXPMASK1_XM10_MASK                                                   (UWORD32)(0x400u)                                                               
#define IC_EXPMASK1_XM10_OFFSET                                                 (UWORD8)(10)                                                                    

#define IC_EXPMASK1_XM11_MASK                                                   (UWORD32)(0x800u)                                                               
#define IC_EXPMASK1_XM11_OFFSET                                                 (UWORD8)(11)                                                                    

#define IC_EXPMASK1_XM12_MASK                                                   (UWORD32)(0x1000u)                                                              
#define IC_EXPMASK1_XM12_OFFSET                                                 (UWORD8)(12)                                                                    

#define IC_EXPMASK1_XM13_MASK                                                   (UWORD32)(0x2000u)                                                              
#define IC_EXPMASK1_XM13_OFFSET                                                 (UWORD8)(13)                                                                    

#define IC_EXPMASK1_XM14_MASK                                                   (UWORD32)(0x4000u)                                                              
#define IC_EXPMASK1_XM14_OFFSET                                                 (UWORD8)(14)                                                                    

#define IC_EXPMASK1_XM15_MASK                                                   (UWORD32)(0x8000u)                                                              
#define IC_EXPMASK1_XM15_OFFSET                                                 (UWORD8)(15)                                                                    

#define IC_EXPMASK1_XM16_MASK                                                   (UWORD32)(0x10000u)                                                             
#define IC_EXPMASK1_XM16_OFFSET                                                 (UWORD8)(16)                                                                    

#define IC_EXPMASK1_XM17_MASK                                                   (UWORD32)(0x20000u)                                                             
#define IC_EXPMASK1_XM17_OFFSET                                                 (UWORD8)(17)                                                                    

#define IC_EXPMASK1_XM18_MASK                                                   (UWORD32)(0x40000u)                                                             
#define IC_EXPMASK1_XM18_OFFSET                                                 (UWORD8)(18)                                                                    

#define IC_EXPMASK1_XM19_MASK                                                   (UWORD32)(0x80000u)                                                             
#define IC_EXPMASK1_XM19_OFFSET                                                 (UWORD8)(19)                                                                    

#define IC_EXPMASK1_XM20_MASK                                                   (UWORD32)(0x100000u)                                                            
#define IC_EXPMASK1_XM20_OFFSET                                                 (UWORD8)(20)                                                                    

#define IC_EXPMASK1_XM21_MASK                                                   (UWORD32)(0x200000u)                                                            
#define IC_EXPMASK1_XM21_OFFSET                                                 (UWORD8)(21)                                                                    

#define IC_EXPMASK1_XM22_MASK                                                   (UWORD32)(0x400000u)                                                            
#define IC_EXPMASK1_XM22_OFFSET                                                 (UWORD8)(22)                                                                    

#define IC_EXPMASK1_XM23_MASK                                                   (UWORD32)(0x800000u)                                                            
#define IC_EXPMASK1_XM23_OFFSET                                                 (UWORD8)(23)                                                                    

#define IC_EXPMASK1_XM24_MASK                                                   (UWORD32)(0x1000000u)                                                           
#define IC_EXPMASK1_XM24_OFFSET                                                 (UWORD8)(24)                                                                    

#define IC_EXPMASK1_XM25_MASK                                                   (UWORD32)(0x2000000u)                                                           
#define IC_EXPMASK1_XM25_OFFSET                                                 (UWORD8)(25)                                                                    

#define IC_EXPMASK1_XM26_MASK                                                   (UWORD32)(0x4000000u)                                                           
#define IC_EXPMASK1_XM26_OFFSET                                                 (UWORD8)(26)                                                                    

#define IC_EXPMASK1_XM27_MASK                                                   (UWORD32)(0x8000000u)                                                           
#define IC_EXPMASK1_XM27_OFFSET                                                 (UWORD8)(27)                                                                    

#define IC_EXPMASK1_XM28_MASK                                                   (UWORD32)(0x10000000u)                                                          
#define IC_EXPMASK1_XM28_OFFSET                                                 (UWORD8)(28)                                                                    

#define IC_EXPMASK1_XM29_MASK                                                   (UWORD32)(0x20000000u)                                                          
#define IC_EXPMASK1_XM29_OFFSET                                                 (UWORD8)(29)                                                                    

#define IC_EXPMASK1_XM30_MASK                                                   (UWORD32)(0x40000000u)                                                          
#define IC_EXPMASK1_XM30_OFFSET                                                 (UWORD8)(30)                                                                    

#define IC_EXPMASK1_XM31_MASK                                                   (UWORD32)(0x80000000u)                                                          
#define IC_EXPMASK1_XM31_OFFSET                                                 (UWORD8)(31)                                                                    

#define IC_EXPMASK2_XM0_MASK                                                    (UWORD32)(0x1u)                                                                 
#define IC_EXPMASK2_XM0_OFFSET                                                  (UWORD8)(0)                                                                     

#define IC_EXPMASK2_XM1_MASK                                                    (UWORD32)(0x2u)                                                                 
#define IC_EXPMASK2_XM1_OFFSET                                                  (UWORD8)(1)                                                                     

#define IC_EXPMASK2_XM2_MASK                                                    (UWORD32)(0x4u)                                                                 
#define IC_EXPMASK2_XM2_OFFSET                                                  (UWORD8)(2)                                                                     

#define IC_EXPMASK2_XM3_MASK                                                    (UWORD32)(0x8u)                                                                 
#define IC_EXPMASK2_XM3_OFFSET                                                  (UWORD8)(3)                                                                     

#define IC_EXPMASK2_XM4_MASK                                                    (UWORD32)(0x10u)                                                                
#define IC_EXPMASK2_XM4_OFFSET                                                  (UWORD8)(4)                                                                     

#define IC_EXPMASK2_XM5_MASK                                                    (UWORD32)(0x20u)                                                                
#define IC_EXPMASK2_XM5_OFFSET                                                  (UWORD8)(5)                                                                     

#define IC_EXPMASK2_XM6_MASK                                                    (UWORD32)(0x40u)                                                                
#define IC_EXPMASK2_XM6_OFFSET                                                  (UWORD8)(6)                                                                     

#define IC_EXPMASK2_XM7_MASK                                                    (UWORD32)(0x80u)                                                                
#define IC_EXPMASK2_XM7_OFFSET                                                  (UWORD8)(7)                                                                     

#define IC_EXPMASK2_XM8_MASK                                                    (UWORD32)(0x100u)                                                               
#define IC_EXPMASK2_XM8_OFFSET                                                  (UWORD8)(8)                                                                     

#define IC_EXPMASK2_XM9_MASK                                                    (UWORD32)(0x200u)                                                               
#define IC_EXPMASK2_XM9_OFFSET                                                  (UWORD8)(9)                                                                     

#define IC_EXPMASK2_XM10_MASK                                                   (UWORD32)(0x400u)                                                               
#define IC_EXPMASK2_XM10_OFFSET                                                 (UWORD8)(10)                                                                    

#define IC_EXPMASK2_XM11_MASK                                                   (UWORD32)(0x800u)                                                               
#define IC_EXPMASK2_XM11_OFFSET                                                 (UWORD8)(11)                                                                    

#define IC_EXPMASK2_XM12_MASK                                                   (UWORD32)(0x1000u)                                                              
#define IC_EXPMASK2_XM12_OFFSET                                                 (UWORD8)(12)                                                                    

#define IC_EXPMASK2_XM13_MASK                                                   (UWORD32)(0x2000u)                                                              
#define IC_EXPMASK2_XM13_OFFSET                                                 (UWORD8)(13)                                                                    

#define IC_EXPMASK2_XM14_MASK                                                   (UWORD32)(0x4000u)                                                              
#define IC_EXPMASK2_XM14_OFFSET                                                 (UWORD8)(14)                                                                    

#define IC_EXPMASK2_XM15_MASK                                                   (UWORD32)(0x8000u)                                                              
#define IC_EXPMASK2_XM15_OFFSET                                                 (UWORD8)(15)                                                                    

#define IC_EXPMASK2_XM16_MASK                                                   (UWORD32)(0x10000u)                                                             
#define IC_EXPMASK2_XM16_OFFSET                                                 (UWORD8)(16)                                                                    

#define IC_EXPMASK2_XM17_MASK                                                   (UWORD32)(0x20000u)                                                             
#define IC_EXPMASK2_XM17_OFFSET                                                 (UWORD8)(17)                                                                    

#define IC_EXPMASK2_XM18_MASK                                                   (UWORD32)(0x40000u)                                                             
#define IC_EXPMASK2_XM18_OFFSET                                                 (UWORD8)(18)                                                                    

#define IC_EXPMASK2_XM19_MASK                                                   (UWORD32)(0x80000u)                                                             
#define IC_EXPMASK2_XM19_OFFSET                                                 (UWORD8)(19)                                                                    

#define IC_EXPMASK2_XM20_MASK                                                   (UWORD32)(0x100000u)                                                            
#define IC_EXPMASK2_XM20_OFFSET                                                 (UWORD8)(20)                                                                    

#define IC_EXPMASK2_XM21_MASK                                                   (UWORD32)(0x200000u)                                                            
#define IC_EXPMASK2_XM21_OFFSET                                                 (UWORD8)(21)                                                                    

#define IC_EXPMASK2_XM22_MASK                                                   (UWORD32)(0x400000u)                                                            
#define IC_EXPMASK2_XM22_OFFSET                                                 (UWORD8)(22)                                                                    

#define IC_EXPMASK2_XM23_MASK                                                   (UWORD32)(0x800000u)                                                            
#define IC_EXPMASK2_XM23_OFFSET                                                 (UWORD8)(23)                                                                    

#define IC_EXPMASK2_XM24_MASK                                                   (UWORD32)(0x1000000u)                                                           
#define IC_EXPMASK2_XM24_OFFSET                                                 (UWORD8)(24)                                                                    

#define IC_EXPMASK2_XM25_MASK                                                   (UWORD32)(0x2000000u)                                                           
#define IC_EXPMASK2_XM25_OFFSET                                                 (UWORD8)(25)                                                                    

#define IC_EXPMASK2_XM26_MASK                                                   (UWORD32)(0x4000000u)                                                           
#define IC_EXPMASK2_XM26_OFFSET                                                 (UWORD8)(26)                                                                    

#define IC_EXPMASK2_XM27_MASK                                                   (UWORD32)(0x8000000u)                                                           
#define IC_EXPMASK2_XM27_OFFSET                                                 (UWORD8)(27)                                                                    

#define IC_EXPMASK2_XM28_MASK                                                   (UWORD32)(0x10000000u)                                                          
#define IC_EXPMASK2_XM28_OFFSET                                                 (UWORD8)(28)                                                                    

#define IC_EXPMASK2_XM29_MASK                                                   (UWORD32)(0x20000000u)                                                          
#define IC_EXPMASK2_XM29_OFFSET                                                 (UWORD8)(29)                                                                    

#define IC_EXPMASK2_XM30_MASK                                                   (UWORD32)(0x40000000u)                                                          
#define IC_EXPMASK2_XM30_OFFSET                                                 (UWORD8)(30)                                                                    

#define IC_EXPMASK2_XM31_MASK                                                   (UWORD32)(0x80000000u)                                                          
#define IC_EXPMASK2_XM31_OFFSET                                                 (UWORD8)(31)                                                                    

#define IC_EXPMASK3_XM0_MASK                                                    (UWORD32)(0x1u)                                                                 
#define IC_EXPMASK3_XM0_OFFSET                                                  (UWORD8)(0)                                                                     

#define IC_EXPMASK3_XM1_MASK                                                    (UWORD32)(0x2u)                                                                 
#define IC_EXPMASK3_XM1_OFFSET                                                  (UWORD8)(1)                                                                     

#define IC_EXPMASK3_XM2_MASK                                                    (UWORD32)(0x4u)                                                                 
#define IC_EXPMASK3_XM2_OFFSET                                                  (UWORD8)(2)                                                                     

#define IC_EXPMASK3_XM3_MASK                                                    (UWORD32)(0x8u)                                                                 
#define IC_EXPMASK3_XM3_OFFSET                                                  (UWORD8)(3)                                                                     

#define IC_EXPMASK3_XM4_MASK                                                    (UWORD32)(0x10u)                                                                
#define IC_EXPMASK3_XM4_OFFSET                                                  (UWORD8)(4)                                                                     

#define IC_EXPMASK3_XM5_MASK                                                    (UWORD32)(0x20u)                                                                
#define IC_EXPMASK3_XM5_OFFSET                                                  (UWORD8)(5)                                                                     

#define IC_EXPMASK3_XM6_MASK                                                    (UWORD32)(0x40u)                                                                
#define IC_EXPMASK3_XM6_OFFSET                                                  (UWORD8)(6)                                                                     

#define IC_EXPMASK3_XM7_MASK                                                    (UWORD32)(0x80u)                                                                
#define IC_EXPMASK3_XM7_OFFSET                                                  (UWORD8)(7)                                                                     

#define IC_EXPMASK3_XM8_MASK                                                    (UWORD32)(0x100u)                                                               
#define IC_EXPMASK3_XM8_OFFSET                                                  (UWORD8)(8)                                                                     

#define IC_EXPMASK3_XM9_MASK                                                    (UWORD32)(0x200u)                                                               
#define IC_EXPMASK3_XM9_OFFSET                                                  (UWORD8)(9)                                                                     

#define IC_EXPMASK3_XM10_MASK                                                   (UWORD32)(0x400u)                                                               
#define IC_EXPMASK3_XM10_OFFSET                                                 (UWORD8)(10)                                                                    

#define IC_EXPMASK3_XM11_MASK                                                   (UWORD32)(0x800u)                                                               
#define IC_EXPMASK3_XM11_OFFSET                                                 (UWORD8)(11)                                                                    

#define IC_EXPMASK3_XM12_MASK                                                   (UWORD32)(0x1000u)                                                              
#define IC_EXPMASK3_XM12_OFFSET                                                 (UWORD8)(12)                                                                    

#define IC_EXPMASK3_XM13_MASK                                                   (UWORD32)(0x2000u)                                                              
#define IC_EXPMASK3_XM13_OFFSET                                                 (UWORD8)(13)                                                                    

#define IC_EXPMASK3_XM14_MASK                                                   (UWORD32)(0x4000u)                                                              
#define IC_EXPMASK3_XM14_OFFSET                                                 (UWORD8)(14)                                                                    

#define IC_EXPMASK3_XM15_MASK                                                   (UWORD32)(0x8000u)                                                              
#define IC_EXPMASK3_XM15_OFFSET                                                 (UWORD8)(15)                                                                    

#define IC_EXPMASK3_XM16_MASK                                                   (UWORD32)(0x10000u)                                                             
#define IC_EXPMASK3_XM16_OFFSET                                                 (UWORD8)(16)                                                                    

#define IC_EXPMASK3_XM17_MASK                                                   (UWORD32)(0x20000u)                                                             
#define IC_EXPMASK3_XM17_OFFSET                                                 (UWORD8)(17)                                                                    

#define IC_EXPMASK3_XM18_MASK                                                   (UWORD32)(0x40000u)                                                             
#define IC_EXPMASK3_XM18_OFFSET                                                 (UWORD8)(18)                                                                    

#define IC_EXPMASK3_XM19_MASK                                                   (UWORD32)(0x80000u)                                                             
#define IC_EXPMASK3_XM19_OFFSET                                                 (UWORD8)(19)                                                                    

#define IC_EXPMASK3_XM20_MASK                                                   (UWORD32)(0x100000u)                                                            
#define IC_EXPMASK3_XM20_OFFSET                                                 (UWORD8)(20)                                                                    

#define IC_EXPMASK3_XM21_MASK                                                   (UWORD32)(0x200000u)                                                            
#define IC_EXPMASK3_XM21_OFFSET                                                 (UWORD8)(21)                                                                    

#define IC_EXPMASK3_XM22_MASK                                                   (UWORD32)(0x400000u)                                                            
#define IC_EXPMASK3_XM22_OFFSET                                                 (UWORD8)(22)                                                                    

#define IC_EXPMASK3_XM23_MASK                                                   (UWORD32)(0x800000u)                                                            
#define IC_EXPMASK3_XM23_OFFSET                                                 (UWORD8)(23)                                                                    

#define IC_EXPMASK3_XM24_MASK                                                   (UWORD32)(0x1000000u)                                                           
#define IC_EXPMASK3_XM24_OFFSET                                                 (UWORD8)(24)                                                                    

#define IC_EXPMASK3_XM25_MASK                                                   (UWORD32)(0x2000000u)                                                           
#define IC_EXPMASK3_XM25_OFFSET                                                 (UWORD8)(25)                                                                    

#define IC_EXPMASK3_XM26_MASK                                                   (UWORD32)(0x4000000u)                                                           
#define IC_EXPMASK3_XM26_OFFSET                                                 (UWORD8)(26)                                                                    

#define IC_EXPMASK3_XM27_MASK                                                   (UWORD32)(0x8000000u)                                                           
#define IC_EXPMASK3_XM27_OFFSET                                                 (UWORD8)(27)                                                                    

#define IC_EXPMASK3_XM28_MASK                                                   (UWORD32)(0x10000000u)                                                          
#define IC_EXPMASK3_XM28_OFFSET                                                 (UWORD8)(28)                                                                    

#define IC_EXPMASK3_XM29_MASK                                                   (UWORD32)(0x20000000u)                                                          
#define IC_EXPMASK3_XM29_OFFSET                                                 (UWORD8)(29)                                                                    

#define IC_EXPMASK3_XM30_MASK                                                   (UWORD32)(0x40000000u)                                                          
#define IC_EXPMASK3_XM30_OFFSET                                                 (UWORD8)(30)                                                                    

#define IC_EXPMASK3_XM31_MASK                                                   (UWORD32)(0x80000000u)                                                          
#define IC_EXPMASK3_XM31_OFFSET                                                 (UWORD8)(31)                                                                    

#define IC_MEXPFLAG0_MXF0_MASK                                                  (UWORD32)(0x1u)                                                                 
#define IC_MEXPFLAG0_MXF0_OFFSET                                                (UWORD8)(0)                                                                     

#define IC_MEXPFLAG0_MXF1_MASK                                                  (UWORD32)(0x2u)                                                                 
#define IC_MEXPFLAG0_MXF1_OFFSET                                                (UWORD8)(1)                                                                     

#define IC_MEXPFLAG0_MXF2_MASK                                                  (UWORD32)(0x4u)                                                                 
#define IC_MEXPFLAG0_MXF2_OFFSET                                                (UWORD8)(2)                                                                     

#define IC_MEXPFLAG0_MXF3_MASK                                                  (UWORD32)(0x8u)                                                                 
#define IC_MEXPFLAG0_MXF3_OFFSET                                                (UWORD8)(3)                                                                     

#define IC_MEXPFLAG0_MXF4_MASK                                                  (UWORD32)(0x10u)                                                                
#define IC_MEXPFLAG0_MXF4_OFFSET                                                (UWORD8)(4)                                                                     

#define IC_MEXPFLAG0_MXF5_MASK                                                  (UWORD32)(0x20u)                                                                
#define IC_MEXPFLAG0_MXF5_OFFSET                                                (UWORD8)(5)                                                                     

#define IC_MEXPFLAG0_MXF6_MASK                                                  (UWORD32)(0x40u)                                                                
#define IC_MEXPFLAG0_MXF6_OFFSET                                                (UWORD8)(6)                                                                     

#define IC_MEXPFLAG0_MXF7_MASK                                                  (UWORD32)(0x80u)                                                                
#define IC_MEXPFLAG0_MXF7_OFFSET                                                (UWORD8)(7)                                                                     

#define IC_MEXPFLAG0_MXF8_MASK                                                  (UWORD32)(0x100u)                                                               
#define IC_MEXPFLAG0_MXF8_OFFSET                                                (UWORD8)(8)                                                                     

#define IC_MEXPFLAG0_MXF9_MASK                                                  (UWORD32)(0x200u)                                                               
#define IC_MEXPFLAG0_MXF9_OFFSET                                                (UWORD8)(9)                                                                     

#define IC_MEXPFLAG0_MXF10_MASK                                                 (UWORD32)(0x400u)                                                               
#define IC_MEXPFLAG0_MXF10_OFFSET                                               (UWORD8)(10)                                                                    

#define IC_MEXPFLAG0_MXF11_MASK                                                 (UWORD32)(0x800u)                                                               
#define IC_MEXPFLAG0_MXF11_OFFSET                                               (UWORD8)(11)                                                                    

#define IC_MEXPFLAG0_MXF12_MASK                                                 (UWORD32)(0x1000u)                                                              
#define IC_MEXPFLAG0_MXF12_OFFSET                                               (UWORD8)(12)                                                                    

#define IC_MEXPFLAG0_MXF13_MASK                                                 (UWORD32)(0x2000u)                                                              
#define IC_MEXPFLAG0_MXF13_OFFSET                                               (UWORD8)(13)                                                                    

#define IC_MEXPFLAG0_MXF14_MASK                                                 (UWORD32)(0x4000u)                                                              
#define IC_MEXPFLAG0_MXF14_OFFSET                                               (UWORD8)(14)                                                                    

#define IC_MEXPFLAG0_MXF15_MASK                                                 (UWORD32)(0x8000u)                                                              
#define IC_MEXPFLAG0_MXF15_OFFSET                                               (UWORD8)(15)                                                                    

#define IC_MEXPFLAG0_MXF16_MASK                                                 (UWORD32)(0x10000u)                                                             
#define IC_MEXPFLAG0_MXF16_OFFSET                                               (UWORD8)(16)                                                                    

#define IC_MEXPFLAG0_MXF17_MASK                                                 (UWORD32)(0x20000u)                                                             
#define IC_MEXPFLAG0_MXF17_OFFSET                                               (UWORD8)(17)                                                                    

#define IC_MEXPFLAG0_MXF18_MASK                                                 (UWORD32)(0x40000u)                                                             
#define IC_MEXPFLAG0_MXF18_OFFSET                                               (UWORD8)(18)                                                                    

#define IC_MEXPFLAG0_MXF19_MASK                                                 (UWORD32)(0x80000u)                                                             
#define IC_MEXPFLAG0_MXF19_OFFSET                                               (UWORD8)(19)                                                                    

#define IC_MEXPFLAG0_MXF20_MASK                                                 (UWORD32)(0x100000u)                                                            
#define IC_MEXPFLAG0_MXF20_OFFSET                                               (UWORD8)(20)                                                                    

#define IC_MEXPFLAG0_MXF21_MASK                                                 (UWORD32)(0x200000u)                                                            
#define IC_MEXPFLAG0_MXF21_OFFSET                                               (UWORD8)(21)                                                                    

#define IC_MEXPFLAG0_MXF22_MASK                                                 (UWORD32)(0x400000u)                                                            
#define IC_MEXPFLAG0_MXF22_OFFSET                                               (UWORD8)(22)                                                                    

#define IC_MEXPFLAG0_MXF23_MASK                                                 (UWORD32)(0x800000u)                                                            
#define IC_MEXPFLAG0_MXF23_OFFSET                                               (UWORD8)(23)                                                                    

#define IC_MEXPFLAG0_MXF24_MASK                                                 (UWORD32)(0x1000000u)                                                           
#define IC_MEXPFLAG0_MXF24_OFFSET                                               (UWORD8)(24)                                                                    

#define IC_MEXPFLAG0_MXF25_MASK                                                 (UWORD32)(0x2000000u)                                                           
#define IC_MEXPFLAG0_MXF25_OFFSET                                               (UWORD8)(25)                                                                    

#define IC_MEXPFLAG0_MXF26_MASK                                                 (UWORD32)(0x4000000u)                                                           
#define IC_MEXPFLAG0_MXF26_OFFSET                                               (UWORD8)(26)                                                                    

#define IC_MEXPFLAG0_MXF27_MASK                                                 (UWORD32)(0x8000000u)                                                           
#define IC_MEXPFLAG0_MXF27_OFFSET                                               (UWORD8)(27)                                                                    

#define IC_MEXPFLAG0_MXF28_MASK                                                 (UWORD32)(0x10000000u)                                                          
#define IC_MEXPFLAG0_MXF28_OFFSET                                               (UWORD8)(28)                                                                    

#define IC_MEXPFLAG0_MXF29_MASK                                                 (UWORD32)(0x20000000u)                                                          
#define IC_MEXPFLAG0_MXF29_OFFSET                                               (UWORD8)(29)                                                                    

#define IC_MEXPFLAG0_MXF30_MASK                                                 (UWORD32)(0x40000000u)                                                          
#define IC_MEXPFLAG0_MXF30_OFFSET                                               (UWORD8)(30)                                                                    

#define IC_MEXPFLAG0_MXF31_MASK                                                 (UWORD32)(0x80000000u)                                                          
#define IC_MEXPFLAG0_MXF31_OFFSET                                               (UWORD8)(31)                                                                    

#define IC_MEXPFLAG1_MXF0_MASK                                                  (UWORD32)(0x1u)                                                                 
#define IC_MEXPFLAG1_MXF0_OFFSET                                                (UWORD8)(0)                                                                     

#define IC_MEXPFLAG1_MXF1_MASK                                                  (UWORD32)(0x2u)                                                                 
#define IC_MEXPFLAG1_MXF1_OFFSET                                                (UWORD8)(1)                                                                     

#define IC_MEXPFLAG1_MXF2_MASK                                                  (UWORD32)(0x4u)                                                                 
#define IC_MEXPFLAG1_MXF2_OFFSET                                                (UWORD8)(2)                                                                     

#define IC_MEXPFLAG1_MXF3_MASK                                                  (UWORD32)(0x8u)                                                                 
#define IC_MEXPFLAG1_MXF3_OFFSET                                                (UWORD8)(3)                                                                     

#define IC_MEXPFLAG1_MXF4_MASK                                                  (UWORD32)(0x10u)                                                                
#define IC_MEXPFLAG1_MXF4_OFFSET                                                (UWORD8)(4)                                                                     

#define IC_MEXPFLAG1_MXF5_MASK                                                  (UWORD32)(0x20u)                                                                
#define IC_MEXPFLAG1_MXF5_OFFSET                                                (UWORD8)(5)                                                                     

#define IC_MEXPFLAG1_MXF6_MASK                                                  (UWORD32)(0x40u)                                                                
#define IC_MEXPFLAG1_MXF6_OFFSET                                                (UWORD8)(6)                                                                     

#define IC_MEXPFLAG1_MXF7_MASK                                                  (UWORD32)(0x80u)                                                                
#define IC_MEXPFLAG1_MXF7_OFFSET                                                (UWORD8)(7)                                                                     

#define IC_MEXPFLAG1_MXF8_MASK                                                  (UWORD32)(0x100u)                                                               
#define IC_MEXPFLAG1_MXF8_OFFSET                                                (UWORD8)(8)                                                                     

#define IC_MEXPFLAG1_MXF9_MASK                                                  (UWORD32)(0x200u)                                                               
#define IC_MEXPFLAG1_MXF9_OFFSET                                                (UWORD8)(9)                                                                     

#define IC_MEXPFLAG1_MXF10_MASK                                                 (UWORD32)(0x400u)                                                               
#define IC_MEXPFLAG1_MXF10_OFFSET                                               (UWORD8)(10)                                                                    

#define IC_MEXPFLAG1_MXF11_MASK                                                 (UWORD32)(0x800u)                                                               
#define IC_MEXPFLAG1_MXF11_OFFSET                                               (UWORD8)(11)                                                                    

#define IC_MEXPFLAG1_MXF12_MASK                                                 (UWORD32)(0x1000u)                                                              
#define IC_MEXPFLAG1_MXF12_OFFSET                                               (UWORD8)(12)                                                                    

#define IC_MEXPFLAG1_MXF13_MASK                                                 (UWORD32)(0x2000u)                                                              
#define IC_MEXPFLAG1_MXF13_OFFSET                                               (UWORD8)(13)                                                                    

#define IC_MEXPFLAG1_MXF14_MASK                                                 (UWORD32)(0x4000u)                                                              
#define IC_MEXPFLAG1_MXF14_OFFSET                                               (UWORD8)(14)                                                                    

#define IC_MEXPFLAG1_MXF15_MASK                                                 (UWORD32)(0x8000u)                                                              
#define IC_MEXPFLAG1_MXF15_OFFSET                                               (UWORD8)(15)                                                                    

#define IC_MEXPFLAG1_MXF16_MASK                                                 (UWORD32)(0x10000u)                                                             
#define IC_MEXPFLAG1_MXF16_OFFSET                                               (UWORD8)(16)                                                                    

#define IC_MEXPFLAG1_MXF17_MASK                                                 (UWORD32)(0x20000u)                                                             
#define IC_MEXPFLAG1_MXF17_OFFSET                                               (UWORD8)(17)                                                                    

#define IC_MEXPFLAG1_MXF18_MASK                                                 (UWORD32)(0x40000u)                                                             
#define IC_MEXPFLAG1_MXF18_OFFSET                                               (UWORD8)(18)                                                                    

#define IC_MEXPFLAG1_MXF19_MASK                                                 (UWORD32)(0x80000u)                                                             
#define IC_MEXPFLAG1_MXF19_OFFSET                                               (UWORD8)(19)                                                                    

#define IC_MEXPFLAG1_MXF20_MASK                                                 (UWORD32)(0x100000u)                                                            
#define IC_MEXPFLAG1_MXF20_OFFSET                                               (UWORD8)(20)                                                                    

#define IC_MEXPFLAG1_MXF21_MASK                                                 (UWORD32)(0x200000u)                                                            
#define IC_MEXPFLAG1_MXF21_OFFSET                                               (UWORD8)(21)                                                                    

#define IC_MEXPFLAG1_MXF22_MASK                                                 (UWORD32)(0x400000u)                                                            
#define IC_MEXPFLAG1_MXF22_OFFSET                                               (UWORD8)(22)                                                                    

#define IC_MEXPFLAG1_MXF23_MASK                                                 (UWORD32)(0x800000u)                                                            
#define IC_MEXPFLAG1_MXF23_OFFSET                                               (UWORD8)(23)                                                                    

#define IC_MEXPFLAG1_MXF24_MASK                                                 (UWORD32)(0x1000000u)                                                           
#define IC_MEXPFLAG1_MXF24_OFFSET                                               (UWORD8)(24)                                                                    

#define IC_MEXPFLAG1_MXF25_MASK                                                 (UWORD32)(0x2000000u)                                                           
#define IC_MEXPFLAG1_MXF25_OFFSET                                               (UWORD8)(25)                                                                    

#define IC_MEXPFLAG1_MXF26_MASK                                                 (UWORD32)(0x4000000u)                                                           
#define IC_MEXPFLAG1_MXF26_OFFSET                                               (UWORD8)(26)                                                                    

#define IC_MEXPFLAG1_MXF27_MASK                                                 (UWORD32)(0x8000000u)                                                           
#define IC_MEXPFLAG1_MXF27_OFFSET                                               (UWORD8)(27)                                                                    

#define IC_MEXPFLAG1_MXF28_MASK                                                 (UWORD32)(0x10000000u)                                                          
#define IC_MEXPFLAG1_MXF28_OFFSET                                               (UWORD8)(28)                                                                    

#define IC_MEXPFLAG1_MXF29_MASK                                                 (UWORD32)(0x20000000u)                                                          
#define IC_MEXPFLAG1_MXF29_OFFSET                                               (UWORD8)(29)                                                                    

#define IC_MEXPFLAG1_MXF30_MASK                                                 (UWORD32)(0x40000000u)                                                          
#define IC_MEXPFLAG1_MXF30_OFFSET                                               (UWORD8)(30)                                                                    

#define IC_MEXPFLAG1_MXF31_MASK                                                 (UWORD32)(0x80000000u)                                                          
#define IC_MEXPFLAG1_MXF31_OFFSET                                               (UWORD8)(31)                                                                    

#define IC_MEXPFLAG2_MXF0_MASK                                                  (UWORD32)(0x1u)                                                                 
#define IC_MEXPFLAG2_MXF0_OFFSET                                                (UWORD8)(0)                                                                     

#define IC_MEXPFLAG2_MXF1_MASK                                                  (UWORD32)(0x2u)                                                                 
#define IC_MEXPFLAG2_MXF1_OFFSET                                                (UWORD8)(1)                                                                     

#define IC_MEXPFLAG2_MXF2_MASK                                                  (UWORD32)(0x4u)                                                                 
#define IC_MEXPFLAG2_MXF2_OFFSET                                                (UWORD8)(2)                                                                     

#define IC_MEXPFLAG2_MXF3_MASK                                                  (UWORD32)(0x8u)                                                                 
#define IC_MEXPFLAG2_MXF3_OFFSET                                                (UWORD8)(3)                                                                     

#define IC_MEXPFLAG2_MXF4_MASK                                                  (UWORD32)(0x10u)                                                                
#define IC_MEXPFLAG2_MXF4_OFFSET                                                (UWORD8)(4)                                                                     

#define IC_MEXPFLAG2_MXF5_MASK                                                  (UWORD32)(0x20u)                                                                
#define IC_MEXPFLAG2_MXF5_OFFSET                                                (UWORD8)(5)                                                                     

#define IC_MEXPFLAG2_MXF6_MASK                                                  (UWORD32)(0x40u)                                                                
#define IC_MEXPFLAG2_MXF6_OFFSET                                                (UWORD8)(6)                                                                     

#define IC_MEXPFLAG2_MXF7_MASK                                                  (UWORD32)(0x80u)                                                                
#define IC_MEXPFLAG2_MXF7_OFFSET                                                (UWORD8)(7)                                                                     

#define IC_MEXPFLAG2_MXF8_MASK                                                  (UWORD32)(0x100u)                                                               
#define IC_MEXPFLAG2_MXF8_OFFSET                                                (UWORD8)(8)                                                                     

#define IC_MEXPFLAG2_MXF9_MASK                                                  (UWORD32)(0x200u)                                                               
#define IC_MEXPFLAG2_MXF9_OFFSET                                                (UWORD8)(9)                                                                     

#define IC_MEXPFLAG2_MXF10_MASK                                                 (UWORD32)(0x400u)                                                               
#define IC_MEXPFLAG2_MXF10_OFFSET                                               (UWORD8)(10)                                                                    

#define IC_MEXPFLAG2_MXF11_MASK                                                 (UWORD32)(0x800u)                                                               
#define IC_MEXPFLAG2_MXF11_OFFSET                                               (UWORD8)(11)                                                                    

#define IC_MEXPFLAG2_MXF12_MASK                                                 (UWORD32)(0x1000u)                                                              
#define IC_MEXPFLAG2_MXF12_OFFSET                                               (UWORD8)(12)                                                                    

#define IC_MEXPFLAG2_MXF13_MASK                                                 (UWORD32)(0x2000u)                                                              
#define IC_MEXPFLAG2_MXF13_OFFSET                                               (UWORD8)(13)                                                                    

#define IC_MEXPFLAG2_MXF14_MASK                                                 (UWORD32)(0x4000u)                                                              
#define IC_MEXPFLAG2_MXF14_OFFSET                                               (UWORD8)(14)                                                                    

#define IC_MEXPFLAG2_MXF15_MASK                                                 (UWORD32)(0x8000u)                                                              
#define IC_MEXPFLAG2_MXF15_OFFSET                                               (UWORD8)(15)                                                                    

#define IC_MEXPFLAG2_MXF16_MASK                                                 (UWORD32)(0x10000u)                                                             
#define IC_MEXPFLAG2_MXF16_OFFSET                                               (UWORD8)(16)                                                                    

#define IC_MEXPFLAG2_MXF17_MASK                                                 (UWORD32)(0x20000u)                                                             
#define IC_MEXPFLAG2_MXF17_OFFSET                                               (UWORD8)(17)                                                                    

#define IC_MEXPFLAG2_MXF18_MASK                                                 (UWORD32)(0x40000u)                                                             
#define IC_MEXPFLAG2_MXF18_OFFSET                                               (UWORD8)(18)                                                                    

#define IC_MEXPFLAG2_MXF19_MASK                                                 (UWORD32)(0x80000u)                                                             
#define IC_MEXPFLAG2_MXF19_OFFSET                                               (UWORD8)(19)                                                                    

#define IC_MEXPFLAG2_MXF20_MASK                                                 (UWORD32)(0x100000u)                                                            
#define IC_MEXPFLAG2_MXF20_OFFSET                                               (UWORD8)(20)                                                                    

#define IC_MEXPFLAG2_MXF21_MASK                                                 (UWORD32)(0x200000u)                                                            
#define IC_MEXPFLAG2_MXF21_OFFSET                                               (UWORD8)(21)                                                                    

#define IC_MEXPFLAG2_MXF22_MASK                                                 (UWORD32)(0x400000u)                                                            
#define IC_MEXPFLAG2_MXF22_OFFSET                                               (UWORD8)(22)                                                                    

#define IC_MEXPFLAG2_MXF23_MASK                                                 (UWORD32)(0x800000u)                                                            
#define IC_MEXPFLAG2_MXF23_OFFSET                                               (UWORD8)(23)                                                                    

#define IC_MEXPFLAG2_MXF24_MASK                                                 (UWORD32)(0x1000000u)                                                           
#define IC_MEXPFLAG2_MXF24_OFFSET                                               (UWORD8)(24)                                                                    

#define IC_MEXPFLAG2_MXF25_MASK                                                 (UWORD32)(0x2000000u)                                                           
#define IC_MEXPFLAG2_MXF25_OFFSET                                               (UWORD8)(25)                                                                    

#define IC_MEXPFLAG2_MXF26_MASK                                                 (UWORD32)(0x4000000u)                                                           
#define IC_MEXPFLAG2_MXF26_OFFSET                                               (UWORD8)(26)                                                                    

#define IC_MEXPFLAG2_MXF27_MASK                                                 (UWORD32)(0x8000000u)                                                           
#define IC_MEXPFLAG2_MXF27_OFFSET                                               (UWORD8)(27)                                                                    

#define IC_MEXPFLAG2_MXF28_MASK                                                 (UWORD32)(0x10000000u)                                                          
#define IC_MEXPFLAG2_MXF28_OFFSET                                               (UWORD8)(28)                                                                    

#define IC_MEXPFLAG2_MXF29_MASK                                                 (UWORD32)(0x20000000u)                                                          
#define IC_MEXPFLAG2_MXF29_OFFSET                                               (UWORD8)(29)                                                                    

#define IC_MEXPFLAG2_MXF30_MASK                                                 (UWORD32)(0x40000000u)                                                          
#define IC_MEXPFLAG2_MXF30_OFFSET                                               (UWORD8)(30)                                                                    

#define IC_MEXPFLAG2_MXF31_MASK                                                 (UWORD32)(0x80000000u)                                                          
#define IC_MEXPFLAG2_MXF31_OFFSET                                               (UWORD8)(31)                                                                    

#define IC_MEXPFLAG3_MXF0_MASK                                                  (UWORD32)(0x1u)                                                                 
#define IC_MEXPFLAG3_MXF0_OFFSET                                                (UWORD8)(0)                                                                     

#define IC_MEXPFLAG3_MXF1_MASK                                                  (UWORD32)(0x2u)                                                                 
#define IC_MEXPFLAG3_MXF1_OFFSET                                                (UWORD8)(1)                                                                     

#define IC_MEXPFLAG3_MXF2_MASK                                                  (UWORD32)(0x4u)                                                                 
#define IC_MEXPFLAG3_MXF2_OFFSET                                                (UWORD8)(2)                                                                     

#define IC_MEXPFLAG3_MXF3_MASK                                                  (UWORD32)(0x8u)                                                                 
#define IC_MEXPFLAG3_MXF3_OFFSET                                                (UWORD8)(3)                                                                     

#define IC_MEXPFLAG3_MXF4_MASK                                                  (UWORD32)(0x10u)                                                                
#define IC_MEXPFLAG3_MXF4_OFFSET                                                (UWORD8)(4)                                                                     

#define IC_MEXPFLAG3_MXF5_MASK                                                  (UWORD32)(0x20u)                                                                
#define IC_MEXPFLAG3_MXF5_OFFSET                                                (UWORD8)(5)                                                                     

#define IC_MEXPFLAG3_MXF6_MASK                                                  (UWORD32)(0x40u)                                                                
#define IC_MEXPFLAG3_MXF6_OFFSET                                                (UWORD8)(6)                                                                     

#define IC_MEXPFLAG3_MXF7_MASK                                                  (UWORD32)(0x80u)                                                                
#define IC_MEXPFLAG3_MXF7_OFFSET                                                (UWORD8)(7)                                                                     

#define IC_MEXPFLAG3_MXF8_MASK                                                  (UWORD32)(0x100u)                                                               
#define IC_MEXPFLAG3_MXF8_OFFSET                                                (UWORD8)(8)                                                                     

#define IC_MEXPFLAG3_MXF9_MASK                                                  (UWORD32)(0x200u)                                                               
#define IC_MEXPFLAG3_MXF9_OFFSET                                                (UWORD8)(9)                                                                     

#define IC_MEXPFLAG3_MXF10_MASK                                                 (UWORD32)(0x400u)                                                               
#define IC_MEXPFLAG3_MXF10_OFFSET                                               (UWORD8)(10)                                                                    

#define IC_MEXPFLAG3_MXF11_MASK                                                 (UWORD32)(0x800u)                                                               
#define IC_MEXPFLAG3_MXF11_OFFSET                                               (UWORD8)(11)                                                                    

#define IC_MEXPFLAG3_MXF12_MASK                                                 (UWORD32)(0x1000u)                                                              
#define IC_MEXPFLAG3_MXF12_OFFSET                                               (UWORD8)(12)                                                                    

#define IC_MEXPFLAG3_MXF13_MASK                                                 (UWORD32)(0x2000u)                                                              
#define IC_MEXPFLAG3_MXF13_OFFSET                                               (UWORD8)(13)                                                                    

#define IC_MEXPFLAG3_MXF14_MASK                                                 (UWORD32)(0x4000u)                                                              
#define IC_MEXPFLAG3_MXF14_OFFSET                                               (UWORD8)(14)                                                                    

#define IC_MEXPFLAG3_MXF15_MASK                                                 (UWORD32)(0x8000u)                                                              
#define IC_MEXPFLAG3_MXF15_OFFSET                                               (UWORD8)(15)                                                                    

#define IC_MEXPFLAG3_MXF16_MASK                                                 (UWORD32)(0x10000u)                                                             
#define IC_MEXPFLAG3_MXF16_OFFSET                                               (UWORD8)(16)                                                                    

#define IC_MEXPFLAG3_MXF17_MASK                                                 (UWORD32)(0x20000u)                                                             
#define IC_MEXPFLAG3_MXF17_OFFSET                                               (UWORD8)(17)                                                                    

#define IC_MEXPFLAG3_MXF18_MASK                                                 (UWORD32)(0x40000u)                                                             
#define IC_MEXPFLAG3_MXF18_OFFSET                                               (UWORD8)(18)                                                                    

#define IC_MEXPFLAG3_MXF19_MASK                                                 (UWORD32)(0x80000u)                                                             
#define IC_MEXPFLAG3_MXF19_OFFSET                                               (UWORD8)(19)                                                                    

#define IC_MEXPFLAG3_MXF20_MASK                                                 (UWORD32)(0x100000u)                                                            
#define IC_MEXPFLAG3_MXF20_OFFSET                                               (UWORD8)(20)                                                                    

#define IC_MEXPFLAG3_MXF21_MASK                                                 (UWORD32)(0x200000u)                                                            
#define IC_MEXPFLAG3_MXF21_OFFSET                                               (UWORD8)(21)                                                                    

#define IC_MEXPFLAG3_MXF22_MASK                                                 (UWORD32)(0x400000u)                                                            
#define IC_MEXPFLAG3_MXF22_OFFSET                                               (UWORD8)(22)                                                                    

#define IC_MEXPFLAG3_MXF23_MASK                                                 (UWORD32)(0x800000u)                                                            
#define IC_MEXPFLAG3_MXF23_OFFSET                                               (UWORD8)(23)                                                                    

#define IC_MEXPFLAG3_MXF24_MASK                                                 (UWORD32)(0x1000000u)                                                           
#define IC_MEXPFLAG3_MXF24_OFFSET                                               (UWORD8)(24)                                                                    

#define IC_MEXPFLAG3_MXF25_MASK                                                 (UWORD32)(0x2000000u)                                                           
#define IC_MEXPFLAG3_MXF25_OFFSET                                               (UWORD8)(25)                                                                    

#define IC_MEXPFLAG3_MXF26_MASK                                                 (UWORD32)(0x4000000u)                                                           
#define IC_MEXPFLAG3_MXF26_OFFSET                                               (UWORD8)(26)                                                                    

#define IC_MEXPFLAG3_MXF27_MASK                                                 (UWORD32)(0x8000000u)                                                           
#define IC_MEXPFLAG3_MXF27_OFFSET                                               (UWORD8)(27)                                                                    

#define IC_MEXPFLAG3_MXF28_MASK                                                 (UWORD32)(0x10000000u)                                                          
#define IC_MEXPFLAG3_MXF28_OFFSET                                               (UWORD8)(28)                                                                    

#define IC_MEXPFLAG3_MXF29_MASK                                                 (UWORD32)(0x20000000u)                                                          
#define IC_MEXPFLAG3_MXF29_OFFSET                                               (UWORD8)(29)                                                                    

#define IC_MEXPFLAG3_MXF30_MASK                                                 (UWORD32)(0x40000000u)                                                          
#define IC_MEXPFLAG3_MXF30_OFFSET                                               (UWORD8)(30)                                                                    

#define IC_MEXPFLAG3_MXF31_MASK                                                 (UWORD32)(0x80000000u)                                                          
#define IC_MEXPFLAG3_MXF31_OFFSET                                               (UWORD8)(31)                                                                    

#define IC_INTMUX1_INTSEL4_MASK                                                 (UWORD32)(0x7fu)                                                                
#define IC_INTMUX1_INTSEL4_OFFSET                                               (UWORD8)(0)                                                                     

#define IC_INTMUX1_INTSEL5_MASK                                                 (UWORD32)(0x7f00u)                                                              
#define IC_INTMUX1_INTSEL5_OFFSET                                               (UWORD8)(8)                                                                     

#define IC_INTMUX1_INTSEL6_MASK                                                 (UWORD32)(0x7f0000u)                                                            
#define IC_INTMUX1_INTSEL6_OFFSET                                               (UWORD8)(16)                                                                    

#define IC_INTMUX1_INTSEL7_MASK                                                 (UWORD32)(0x7f000000u)                                                          
#define IC_INTMUX1_INTSEL7_OFFSET                                               (UWORD8)(24)                                                                    

#define IC_INTMUX2_INTSEL8_MASK                                                 (UWORD32)(0x7fu)                                                                
#define IC_INTMUX2_INTSEL8_OFFSET                                               (UWORD8)(0)                                                                     

#define IC_INTMUX2_INTSEL9_MASK                                                 (UWORD32)(0x7f00u)                                                              
#define IC_INTMUX2_INTSEL9_OFFSET                                               (UWORD8)(8)                                                                     

#define IC_INTMUX2_INTSEL10_MASK                                                (UWORD32)(0x7f0000u)                                                            
#define IC_INTMUX2_INTSEL10_OFFSET                                              (UWORD8)(16)                                                                    

#define IC_INTMUX2_INTSEL11_MASK                                                (UWORD32)(0x7f000000u)                                                          
#define IC_INTMUX2_INTSEL11_OFFSET                                              (UWORD8)(24)                                                                    

#define IC_INTMUX3_INTSEL12_MASK                                                (UWORD32)(0x7fu)                                                                
#define IC_INTMUX3_INTSEL12_OFFSET                                              (UWORD8)(0)                                                                     

#define IC_INTMUX3_INTSEL13_MASK                                                (UWORD32)(0x7f00u)                                                              
#define IC_INTMUX3_INTSEL13_OFFSET                                              (UWORD8)(8)                                                                     

#define IC_INTMUX3_INTSEL14_MASK                                                (UWORD32)(0x7f0000u)                                                            
#define IC_INTMUX3_INTSEL14_OFFSET                                              (UWORD8)(16)                                                                    

#define IC_INTMUX3_INTSEL15_MASK                                                (UWORD32)(0x7f000000u)                                                          
#define IC_INTMUX3_INTSEL15_OFFSET                                              (UWORD8)(24)                                                                    

#define IC_AEGMUX0_AEGSEL0_MASK                                                 (UWORD32)(0xffu)                                                                
#define IC_AEGMUX0_AEGSEL0_OFFSET                                               (UWORD8)(0)                                                                     

#define IC_AEGMUX0_AEGSEL1_MASK                                                 (UWORD32)(0xff00u)                                                              
#define IC_AEGMUX0_AEGSEL1_OFFSET                                               (UWORD8)(8)                                                                     

#define IC_AEGMUX0_AEGSEL2_MASK                                                 (UWORD32)(0xff0000u)                                                            
#define IC_AEGMUX0_AEGSEL2_OFFSET                                               (UWORD8)(16)                                                                    

#define IC_AEGMUX0_AEGSEL3_MASK                                                 (UWORD32)(0xff000000u)                                                          
#define IC_AEGMUX0_AEGSEL3_OFFSET                                               (UWORD8)(24)                                                                    

#define IC_AEGMUX1_AEGSEL4_MASK                                                 (UWORD32)(0xffu)                                                                
#define IC_AEGMUX1_AEGSEL4_OFFSET                                               (UWORD8)(0)                                                                     

#define IC_AEGMUX1_AEGSEL5_MASK                                                 (UWORD32)(0xff00u)                                                              
#define IC_AEGMUX1_AEGSEL5_OFFSET                                               (UWORD8)(8)                                                                     

#define IC_AEGMUX1_AEGSEL6_MASK                                                 (UWORD32)(0xff0000u)                                                            
#define IC_AEGMUX1_AEGSEL6_OFFSET                                               (UWORD8)(16)                                                                    

#define IC_AEGMUX1_AEGSEL7_MASK                                                 (UWORD32)(0xff000000u)                                                          
#define IC_AEGMUX1_AEGSEL7_OFFSET                                               (UWORD8)(24)                                                                    

#define IC_INTXSTAT_DROP_MASK                                                   (UWORD32)(0x1u)                                                                 
#define IC_INTXSTAT_DROP_OFFSET                                                 (UWORD8)(0)                                                                     

#define IC_INTXSTAT_CPUINT_MASK                                                 (UWORD32)(0xff0000u)                                                            
#define IC_INTXSTAT_CPUINT_OFFSET                                               (UWORD8)(16)                                                                    

#define IC_INTXSTAT_SYSINT_MASK                                                 (UWORD32)(0xff000000u)                                                          
#define IC_INTXSTAT_SYSINT_OFFSET                                               (UWORD8)(24)                                                                    

#define IC_INTXCLR_CLEAR_MASK                                                   (UWORD32)(0x1u)                                                                 
#define IC_INTXCLR_CLEAR_OFFSET                                                 (UWORD8)(0)                                                                     

#define IC_INTDMASK_IDM4_MASK                                                   (UWORD32)(0x10u)                                                                
#define IC_INTDMASK_IDM4_OFFSET                                                 (UWORD8)(4)                                                                     

#define IC_INTDMASK_IDM5_MASK                                                   (UWORD32)(0x20u)                                                                
#define IC_INTDMASK_IDM5_OFFSET                                                 (UWORD8)(5)                                                                     

#define IC_INTDMASK_IDM6_MASK                                                   (UWORD32)(0x40u)                                                                
#define IC_INTDMASK_IDM6_OFFSET                                                 (UWORD8)(6)                                                                     

#define IC_INTDMASK_IDM7_MASK                                                   (UWORD32)(0x80u)                                                                
#define IC_INTDMASK_IDM7_OFFSET                                                 (UWORD8)(7)                                                                     

#define IC_INTDMASK_IDM8_MASK                                                   (UWORD32)(0x100u)                                                               
#define IC_INTDMASK_IDM8_OFFSET                                                 (UWORD8)(8)                                                                     

#define IC_INTDMASK_IDM9_MASK                                                   (UWORD32)(0x200u)                                                               
#define IC_INTDMASK_IDM9_OFFSET                                                 (UWORD8)(9)                                                                     

#define IC_INTDMASK_IDM10_MASK                                                  (UWORD32)(0x400u)                                                               
#define IC_INTDMASK_IDM10_OFFSET                                                (UWORD8)(10)                                                                    

#define IC_INTDMASK_IDM11_MASK                                                  (UWORD32)(0x800u)                                                               
#define IC_INTDMASK_IDM11_OFFSET                                                (UWORD8)(11)                                                                    

#define IC_INTDMASK_IDM12_MASK                                                  (UWORD32)(0x1000u)                                                              
#define IC_INTDMASK_IDM12_OFFSET                                                (UWORD8)(12)                                                                    

#define IC_INTDMASK_IDM13_MASK                                                  (UWORD32)(0x2000u)                                                              
#define IC_INTDMASK_IDM13_OFFSET                                                (UWORD8)(13)                                                                    

#define IC_INTDMASK_IDM14_MASK                                                  (UWORD32)(0x4000u)                                                              
#define IC_INTDMASK_IDM14_OFFSET                                                (UWORD8)(14)                                                                    

#define IC_INTDMASK_IDM15_MASK                                                  (UWORD32)(0x8000u)                                                              
#define IC_INTDMASK_IDM15_OFFSET                                                (UWORD8)(15)                                                                    

#define IC_EVTASRT_MXF0_MASK                                                    (UWORD32)(0x1u)                                                                 
#define IC_EVTASRT_MXF0_OFFSET                                                  (UWORD8)(0)                                                                     

#define IC_EVTASRT_MXF1_MASK                                                    (UWORD32)(0x2u)                                                                 
#define IC_EVTASRT_MXF1_OFFSET                                                  (UWORD8)(1)                                                                     

#define IC_EVTASRT_MXF2_MASK                                                    (UWORD32)(0x4u)                                                                 
#define IC_EVTASRT_MXF2_OFFSET                                                  (UWORD8)(2)                                                                     

#define IC_EVTASRT_MXF3_MASK                                                    (UWORD32)(0x8u)                                                                 
#define IC_EVTASRT_MXF3_OFFSET                                                  (UWORD8)(3)                                                                     

#define IC_EVTASRT_MXF4_MASK                                                    (UWORD32)(0x10u)                                                                
#define IC_EVTASRT_MXF4_OFFSET                                                  (UWORD8)(4)                                                                     

#define IC_EVTASRT_MXF5_MASK                                                    (UWORD32)(0x20u)                                                                
#define IC_EVTASRT_MXF5_OFFSET                                                  (UWORD8)(5)                                                                     

#define IC_EVTASRT_MXF6_MASK                                                    (UWORD32)(0x40u)                                                                
#define IC_EVTASRT_MXF6_OFFSET                                                  (UWORD8)(6)                                                                     

#define IC_EVTASRT_MXF7_MASK                                                    (UWORD32)(0x80u)                                                                
#define IC_EVTASRT_MXF7_OFFSET                                                  (UWORD8)(7)                                                                     


/*****************************************************************************
* EXPORTED TYPES
******************************************************************************
*/

/* The following type definitions represent the enumerated values for each bitfield */

typedef UWORD32 ICINTXSTATCPUINTE;
#define ICINTXSTATCPUINTCPUINT0 0x0u
#define ICINTXSTATCPUINTCPUINT1 0x1u
#define ICINTXSTATCPUINTCPUINT2 0x2u
#define ICINTXSTATCPUINTCPUINT3 0x3u
#define ICINTXSTATCPUINTCPUINT4 0x4u
#define ICINTXSTATCPUINTCPUINT5 0x5u
#define ICINTXSTATCPUINTCPUINT6 0x6u
#define ICINTXSTATCPUINTCPUINT7 0x7u
#define ICINTXSTATCPUINTCPUINT8 0x8u
#define ICINTXSTATCPUINTCPUINT9 0x9u
#define ICINTXSTATCPUINTCPUINT10 0xau
#define ICINTXSTATCPUINTCPUINT11 0xbu
#define ICINTXSTATCPUINTCPUINT12 0xcu
#define ICINTXSTATCPUINTCPUINT13 0xdu
#define ICINTXSTATCPUINTCPUINT14 0xeu
#define ICINTXSTATCPUINTCPUINT15 0xfu

typedef UWORD32 ICINTXSTATSYSINTE;
#define ICINTXSTATSYSINTEVT0 0x0u
#define ICINTXSTATSYSINTEVT1 0x1u
#define ICINTXSTATSYSINTEVT2 0x2u
#define ICINTXSTATSYSINTEVT3 0x3u
#define ICINTXSTATSYSINTEVT4 0x4u
#define ICINTXSTATSYSINTEVT5 0x5u
#define ICINTXSTATSYSINTEVT6 0x6u
#define ICINTXSTATSYSINTEVT7 0x7u
#define ICINTXSTATSYSINTEVT8 0x8u
#define ICINTXSTATSYSINTEVT9 0x9u
#define ICINTXSTATSYSINTEVT10 0xau
#define ICINTXSTATSYSINTEVT11 0xbu
#define ICINTXSTATSYSINTEVT12 0xcu
#define ICINTXSTATSYSINTEVT13 0xdu
#define ICINTXSTATSYSINTEVT14 0xeu
#define ICINTXSTATSYSINTEVT15 0xfu
#define ICINTXSTATSYSINTEVT16 0x10u
#define ICINTXSTATSYSINTEVT17 0x11u
#define ICINTXSTATSYSINTEVT18 0x12u
#define ICINTXSTATSYSINTEVT19 0x13u
#define ICINTXSTATSYSINTEVT20 0x14u
#define ICINTXSTATSYSINTEVT21 0x15u
#define ICINTXSTATSYSINTEVT22 0x16u
#define ICINTXSTATSYSINTEVT23 0x17u
#define ICINTXSTATSYSINTEVT24 0x18u
#define ICINTXSTATSYSINTEVT25 0x19u
#define ICINTXSTATSYSINTEVT26 0x1au
#define ICINTXSTATSYSINTEVT27 0x1bu
#define ICINTXSTATSYSINTEVT28 0x1cu
#define ICINTXSTATSYSINTEVT29 0x1du
#define ICINTXSTATSYSINTEVT30 0x1eu
#define ICINTXSTATSYSINTEVT31 0x1fu
#define ICINTXSTATSYSINTEVT32 0x20u
#define ICINTXSTATSYSINTEVT33 0x21u
#define ICINTXSTATSYSINTEVT34 0x22u
#define ICINTXSTATSYSINTEVT35 0x23u
#define ICINTXSTATSYSINTEVT36 0x24u
#define ICINTXSTATSYSINTEVT37 0x25u
#define ICINTXSTATSYSINTEVT38 0x26u
#define ICINTXSTATSYSINTEVT39 0x27u
#define ICINTXSTATSYSINTEVT40 0x28u
#define ICINTXSTATSYSINTEVT41 0x29u
#define ICINTXSTATSYSINTEVT42 0x2au
#define ICINTXSTATSYSINTEVT43 0x2bu
#define ICINTXSTATSYSINTEVT44 0x2cu
#define ICINTXSTATSYSINTEVT45 0x2du
#define ICINTXSTATSYSINTEVT46 0x2eu
#define ICINTXSTATSYSINTEVT47 0x2fu
#define ICINTXSTATSYSINTEVT48 0x30u
#define ICINTXSTATSYSINTEVT49 0x31u
#define ICINTXSTATSYSINTEVT50 0x32u
#define ICINTXSTATSYSINTEVT51 0x33u
#define ICINTXSTATSYSINTEVT52 0x34u
#define ICINTXSTATSYSINTEVT53 0x35u
#define ICINTXSTATSYSINTEVT54 0x36u
#define ICINTXSTATSYSINTEVT55 0x37u
#define ICINTXSTATSYSINTEVT56 0x38u
#define ICINTXSTATSYSINTEVT57 0x39u
#define ICINTXSTATSYSINTEVT58 0x3au
#define ICINTXSTATSYSINTEVT59 0x3bu
#define ICINTXSTATSYSINTEVT60 0x3cu
#define ICINTXSTATSYSINTEVT61 0x3du
#define ICINTXSTATSYSINTEVT62 0x3eu
#define ICINTXSTATSYSINTEVT63 0x3fu
#define ICINTXSTATSYSINTEVT64 0x40u
#define ICINTXSTATSYSINTEVT65 0x41u
#define ICINTXSTATSYSINTEVT66 0x42u
#define ICINTXSTATSYSINTEVT67 0x43u
#define ICINTXSTATSYSINTEVT68 0x44u
#define ICINTXSTATSYSINTEVT69 0x45u
#define ICINTXSTATSYSINTEVT70 0x46u
#define ICINTXSTATSYSINTEVT71 0x47u
#define ICINTXSTATSYSINTEVT72 0x48u
#define ICINTXSTATSYSINTEVT73 0x49u
#define ICINTXSTATSYSINTEVT74 0x4au
#define ICINTXSTATSYSINTEVT75 0x4bu
#define ICINTXSTATSYSINTEVT76 0x4cu
#define ICINTXSTATSYSINTEVT77 0x4du
#define ICINTXSTATSYSINTEVT78 0x4eu
#define ICINTXSTATSYSINTEVT79 0x4fu
#define ICINTXSTATSYSINTEVT80 0x50u
#define ICINTXSTATSYSINTEVT81 0x51u
#define ICINTXSTATSYSINTEVT82 0x52u
#define ICINTXSTATSYSINTEVT83 0x53u
#define ICINTXSTATSYSINTEVT84 0x54u
#define ICINTXSTATSYSINTEVT85 0x55u
#define ICINTXSTATSYSINTEVT86 0x56u
#define ICINTXSTATSYSINTEVT87 0x57u
#define ICINTXSTATSYSINTEVT88 0x58u
#define ICINTXSTATSYSINTEVT89 0x59u
#define ICINTXSTATSYSINTEVT90 0x5au
#define ICINTXSTATSYSINTEVT91 0x5bu
#define ICINTXSTATSYSINTEVT92 0x5cu
#define ICINTXSTATSYSINTEVT93 0x5du
#define ICINTXSTATSYSINTEVT94 0x5eu
#define ICINTXSTATSYSINTEVT95 0x5fu
#define ICINTXSTATSYSINTEVT96 0x60u
#define ICINTXSTATSYSINTEVT97 0x61u
#define ICINTXSTATSYSINTEVT98 0x62u
#define ICINTXSTATSYSINTEVT99 0x63u
#define ICINTXSTATSYSINTEVT100 0x64u
#define ICINTXSTATSYSINTEVT101 0x65u
#define ICINTXSTATSYSINTEVT102 0x66u
#define ICINTXSTATSYSINTEVT103 0x67u
#define ICINTXSTATSYSINTEVT104 0x68u
#define ICINTXSTATSYSINTEVT105 0x69u
#define ICINTXSTATSYSINTEVT106 0x6au
#define ICINTXSTATSYSINTEVT107 0x6bu
#define ICINTXSTATSYSINTEVT108 0x6cu
#define ICINTXSTATSYSINTEVT109 0x6du
#define ICINTXSTATSYSINTEVT110 0x6eu
#define ICINTXSTATSYSINTEVT111 0x6fu
#define ICINTXSTATSYSINTEVT112 0x70u
#define ICINTXSTATSYSINTEVT113 0x71u
#define ICINTXSTATSYSINTEVT114 0x72u
#define ICINTXSTATSYSINTEVT115 0x73u
#define ICINTXSTATSYSINTEVT116 0x74u
#define ICINTXSTATSYSINTEVT117 0x75u
#define ICINTXSTATSYSINTEVT118 0x76u
#define ICINTXSTATSYSINTEVT119 0x77u
#define ICINTXSTATSYSINTEVT120 0x78u
#define ICINTXSTATSYSINTEVT121 0x79u
#define ICINTXSTATSYSINTEVT122 0x7au
#define ICINTXSTATSYSINTEVT123 0x7bu
#define ICINTXSTATSYSINTEVT124 0x7cu
#define ICINTXSTATSYSINTEVT125 0x7du
#define ICINTXSTATSYSINTEVT126 0x7eu
#define ICINTXSTATSYSINTEVT127 0x7fu

/*****************************************************************************
* EXPORTED VARIABLES
******************************************************************************
*/

/*****************************************************************************
* EXPORTED FUNCTIONS
******************************************************************************
*/

#if defined(__cplusplus)
}  /* End of C++ extern block */
#endif /* defined(__cplusplus) */

#endif /* _IC_ACC_INT_H */
/* EOF */

