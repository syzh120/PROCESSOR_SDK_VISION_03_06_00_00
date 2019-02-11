;*
;*
;* Copyright (c) 2013-2017 Texas Instruments Incorporated
;*
;* All rights reserved not granted herein.
;*
;* Limited License.
;*
;* Texas Instruments Incorporated grants a world-wide, royalty-free, non-exclusive
;* license under copyrights and patents it now or hereafter owns or controls to make,
;* have made, use, import, offer to sell and sell ("Utilize") this software subject to the
;* terms herein.  With respect to the foregoing patent license, such license is granted
;* solely to the extent that any such patent is necessary to Utilize the software alone.
;* The patent license shall not apply to any combinations which include this software,
;* other than combinations with devices manufactured by or for TI ("TI Devices").
;* No hardware patent is licensed hereunder.
;*
;* Redistributions must preserve existing copyright notices and reproduce this license
;* (including the above copyright notice and the disclaimer and (if applicable) source
;* code license limitations below) in the documentation and/or other materials provided
;* with the distribution
;*
;* Redistribution and use in binary form, without modification, are permitted provided
;* that the following conditions are met:
;*
;* *       No reverse engineering, decompilation, or disassembly of this software is
;* permitted with respect to any software provided in binary form.
;*
;* *       any redistribution and use are licensed by TI for use only with TI Devices.
;*
;* *       Nothing shall obligate TI to provide you with source code for the software
;* licensed and provided to you in object code.
;*
;* If software source code is provided to you, modification and redistribution of the
;* source code are permitted provided that the following conditions are met:
;*
;* *       any redistribution and use of the source code, including any resulting derivative
;* works, are licensed by TI for use only with TI Devices.
;*
;* *       any redistribution and use of any object code compiled from the source code
;* and any resulting derivative works, are licensed by TI for use only with TI Devices.
;*
;* Neither the name of Texas Instruments Incorporated nor the names of its suppliers
;*
;* may be used to endorse or promote products derived from this software without
;* specific prior written permission.
;*
;* DISCLAIMER.
;*
;* THIS SOFTWARE IS PROVIDED BY TI AND TI'S LICENSORS "AS IS" AND ANY EXPRESS
;* OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
;* OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
;* IN NO EVENT SHALL TI AND TI'S LICENSORS BE LIABLE FOR ANY DIRECT, INDIRECT,
;* INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
;* BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
;* DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY
;* OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
;* OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
;* OF THE POSSIBILITY OF SUCH DAMAGE.
;*
;*

    .data
    .global _my_stack
_my_stack:
    .word 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0

    .text   
	.global	main
	.global	_c_int00
	.global exit
	.global _vec_table
	.global _reset_handler
	.global _dummy_handler

    .ref NMI_IRQ
    .ref SWI_IRQ
    .ref INTH_IRQ4
    .ref INTH_IRQ5
    .ref INTH_IRQ6
    .ref INTH_IRQ7
    .ref INTH_IRQ8
    .ref INTH_IRQ9
    .ref INTH_IRQ10
    .ref INTH_IRQ11
    .ref INTH_IRQ12
    .ref INTH_IRQ13
    .ref INTH_IRQ14
    .ref INTH_IRQ15

;******************************************************************************
;* Interrupt Service Table (IST)                                              *
;******************************************************************************
    .sect ".intvecs"

_vec_table:
    .word _reset_handler      ; RESET
    .word NMI_IRQ             ; NMI
    .word SWI_IRQ             ; SWI
    .word _dummy_handler      ; Reserved
    .word INTH_IRQ4           ; INT4
    .word INTH_IRQ5           ; INT5
    .word INTH_IRQ6           ; INT6
    .word INTH_IRQ7           ; INT7
    .word INTH_IRQ8           ; INT7
    .word INTH_IRQ8           ; INT8
    .word INTH_IRQ9           ; INT9
    .word INTH_IRQ10          ; INT10
    .word INTH_IRQ11          ; INT11
    .word INTH_IRQ12          ; INT12
    .word INTH_IRQ13          ; INT13
    .word INTH_IRQ14          ; INT14
    .word INTH_IRQ15          ; INT15


;******************************************************************************
;* Reset handler                                                              *
;******************************************************************************
    .sect ".inthandler"

_reset_handler:
  	MVC	   1,         CSR     ; enable GIE
	MVC	   0xFFF3,    IER     ; 
	MVC	   _my_stack, SP
	MVCH   _my_stack, SP
	CALL	_c_int00
	NOP
	CALL	exit
	NOP
	MVK	    _vec_table, R7
	MVK	    main, R6
	MVK	    _reset_handler, R6

;******************************************************************************
;* Dummy handler                                                              *
;******************************************************************************
    .sect ".inthandler"
_dummy_handler:
	NOP
	NOP
	B	_dummy_handler
	NOP

;----------------------------------------------------------------------
; Exit simulation
;----------------------------------------------------------------------
	.sect	".exitlocation"
	.global	end_of_test
	        NOP       ; -- 0x100
    
	        NOP       ; -- 0x104
	        NOP       ; -- 0x108
end_of_test: 
	        MVKS	-1, R0       
	        MVKS	-1, R1       
	        MVKS	-1, R2       
	        MVKS	-1, R3       
	        MVKS	-1, R4       
	        MVKS	-1, R5       
	        MVKS	-1, R6       
	        MVKS	-1, R7      
	        
;----------------------------------------------------------------------

