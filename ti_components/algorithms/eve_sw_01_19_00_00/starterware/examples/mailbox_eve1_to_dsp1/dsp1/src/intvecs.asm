* ==========================================================================================*
*                                                                                           *
* Copyright (c) {YEAR} Texas Instruments Incorporated                                       *
*                                                                                           *
* All rights reserved not granted herein.                                                   *
*                                                                                           *
* Limited License.                                                                          *
*                                                                                           *
* Texas Instruments Incorporated grants a world-wide, royalty-free, non-exclusive           *
* license under copyrights and patents it now or hereafter owns or controls to make,        *
* have made, use, import, offer to sell and sell ("Utilize") this software subject to the   *
* terms herein.  With respect to the foregoing patent license, such license is granted      *
* solely to the extent that any such patent is necessary to Utilize the software alone.     *
* The patent license shall not apply to any combinations which include this software,       *
* other than combinations with devices manufactured by or for TI ("TI Devices").            *
* No hardware patent is licensed hereunder.                                                 *
*                                                                                           *
* Redistributions must preserve existing copyright notices and reproduce this license       *
* (including the above copyright notice and the disclaimer and (if applicable) source       *
* code license limitations below) in the documentation and/or other materials provided      *
* with the distribution                                                                     *
*                                                                                           *
* Redistribution and use in binary form, without modification, are permitted provided       *
* that the following conditions are met:                                                    *
*                                                                                           *
* *       No reverse engineering, decompilation, or disassembly of this software is         *
* permitted with respect to any software provided in binary form.                           *
*                                                                                           *
* *       any redistribution and use are licensed by TI for use only with TI Devices.       *
*                                                                                           *
* *       Nothing shall obligate TI to provide you with source code for the software        *
* licensed and provided to you in object code.                                              *
*                                                                                           *
* If software source code is provided to you, modification and redistribution of the        *
* source code are permitted provided that the following conditions are met:                 *
*                                                                                           *
* *       any redistribution and use of the source code, including any resulting derivative *
* works, are licensed by TI for use only with TI Devices.                                   *
*                                                                                           *
* *       any redistribution and use of any object code compiled from the source code       *
* and any resulting derivative works, are licensed by TI for use only with TI Devices.      *
*                                                                                           *
* Neither the name of Texas Instruments Incorporated nor the names of its suppliers         *
*                                                                                           *
* may be used to endorse or promote products derived from this software without             *
* specific prior written permission.                                                        *
*                                                                                           *
* DISCLAIMER.                                                                               *
*                                                                                           *
* THIS SOFTWARE IS PROVIDED BY TI AND TI'S LICENSORS "AS IS" AND ANY EXPRESS                *
* OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES              *
* OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.                   *
* IN NO EVENT SHALL TI AND TI'S LICENSORS BE LIABLE FOR ANY DIRECT, INDIRECT,               *
* INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,                      *
* BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,             *
* DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY              *
* OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE        *
* OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED         *
* OF THE POSSIBILITY OF SUCH DAMAGE.                                                        *
*                                                                                           *
* ==========================================================================================*

*
*------------------------------------------------------------------------------
* Global symbols defined here and exported out of this file
*------------------------------------------------------------------------------
   .global _vectors
   .global _vector0
   .global _vector1
   .global _vector2
   .global _vector3
   .global _vector4
   .global _vector5
   .global _vector6
   .global _vector7
   .global _vector8
   .global _vector9
   .global _vector10
   .global _vector11
   .global _vector12
   .global _vector13
   .global _vector14
   .global _vector15
	 .global	_INT_SetWaitForInterrupt


*------------------------------------------------------------------------------
* Global symbols referenced in this file but defined somewhere else.
* Remember that your interrupt service routines need to be referenced here.
*------------------------------------------------------------------------------
   .ref _IRQ_intTable
   .ref __ISR_Table
   .ref _main
   .ref _c_int00
   .ref __stack
   .ref __STACK_SIZE
   .ref $bss

*------------------------------------------------------------------------------
* This is a macro that instantiates one entry in the interrupt service table.
*------------------------------------------------------------------------------
ISR_ENTRY .macro addr
    STW   B0,*--B15
    MVKL  addr,B0
    MVKH  addr,B0
    LDW	  *B0,B0
    NOP	  5
    B     B0
    LDW   *B15++,B0
    NOP   5
   .endm


*------------------------------------------------------------------------------
* This is the actual interrupt service table (IST). It is properly aligned and
* is located in the section .vecs. Remember to set the ISTP register to point
* to this table.
*------------------------------------------------------------------------------
 .sect ".vects"
 .align 1024

_vectors:
_vector0:  	B init_regs
		NOP 5
		NOP 5
		NOP 5
		NOP 5
		NOP 5
		NOP 5
		NOP 5
_vector1:   ISR_ENTRY __ISR_Table+4  		; NMI
_vector2:   ISR_ENTRY __ISR_Table+8		; RSVD
_vector3:   ISR_ENTRY __ISR_Table+12		; RSVD
_vector4:   ISR_ENTRY __ISR_Table+16		; CONFIGURABLE
_vector5:   ISR_ENTRY __ISR_Table+20		; CONFIGURABLE
_vector6:   ISR_ENTRY __ISR_Table+24		; CONFIGURABLE
_vector7:   ISR_ENTRY __ISR_Table+28		; CONFIGURABLE
_vector8:   ISR_ENTRY __ISR_Table+32		; CONFIGURABLE
_vector9:   ISR_ENTRY __ISR_Table+36		; CONFIGURABLE
_vector10:  ISR_ENTRY __ISR_Table+40		; CONFIGURABLE
_vector11:  ISR_ENTRY __ISR_Table+44		; CONFIGURABLE
_vector12:  ISR_ENTRY __ISR_Table+48		; CONFIGURABLE
_vector13:  ISR_ENTRY __ISR_Table+52		; CONFIGURABLE
_vector14:  ISR_ENTRY __ISR_Table+56		; CONFIGURABLE
_vector15:  ISR_ENTRY __ISR_Table+60		; CONFIGURABLE

*------------------------------------------------------------------------------

init_regs:
		MVKL 0,B1
		MVKH 0,B1
		MVKL 0,A0
		MVKH 0,A0
		MV B1,B2
		MV B1,B3
	||	MV B2,B4
		MV B1,B5
	||	MV B2,B6
		MV B1,B7
	||	MV B2,B8
		MV B1,B9
	||	MV B2,B10
		MV B1,B11
	||	MV B2,B12
		MV B1,B13
	||	MV B2,B14
		MV B1,B15
	||	MV B2,B16
		MV B1,B17
	||	MV B2,B18
		MV B1,B19
	||	MV B2,B20
		MV B1,B21
	||	MV B2,B22
		MV B1,B23
	||	MV B2,B24
		MV B1,B25
	||	MV B2,B26
		MV B1,B27
	||	MV B2,B28
		MV B1,B29
	||	MV B2,B30
		MV B1,B31

		MV A0,A1
		MV A1,A2
		MV A1,A3
	||	MV A2,A4
		MV A1,A5
	||	MV A2,A6
		MV A1,A7
	||	MV A2,A8
		MV A1,A9
	||	MV A2,A10
		MV A1,A11
	||	MV A2,A12
		MV A1,A13
	||	MV A2,A14
		MV A1,A15
	||	MV A2,A16
		MV A1,A17
	||	MV A2,A18
		MV A1,A19
	||	MV A2,A20
		MV A1,A21
	||	MV A2,A22
		MV A1,A23
	||	MV A2,A24
		MV A1,A25
	||	MV A2,A26
		MV A1,A27
	||	MV A2,A28
		MV A1,A29
	||	MV A2,A30
		MV A1,A31

		NOP 5

		MVKL _c_int00,B0
		MVKH _c_int00,B0
		B B0

		NOP 5
		NOP 5
		NOP 5
		NOP 5
		NOP 5


_INT_SetWaitForInterrupt:
    IDLE
		RETNOP  B3,5

