/*
 *  ======== mem_segment_definition_512mb.xs ========
 *
 */

/*
 * Copyright (C) 2013 Texas Instruments Incorporated - http://www.ti.com/
 *
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions
 *  are met:
 *
 *    Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 *    Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the
 *    distribution.
 *
 *    Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 *  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 *  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 *  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 *  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 *  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 *  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 *  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
*/

function getMemSegmentDefinition_external()
{

	var CUSTOM_HOST_CODE_ADDR;
	var CUSTOM_HOST_CODE_SIZE;

	var CUSTOM_HOST_DATA_ADDR;
	var CUSTOM_HOST_DATA_SIZE;

	var CUSTOM_HOST_BSS_ADDR;
	var CUSTOM_HOST_BSS_SIZE;

	var MB = 1024*1024;
	var DDR3_BASE_ADDR_0;

	var CUSTOM_HOST_TFDTPBUF_ADDR;
	var CUSTOM_HOST_NDKBUF_ADDR;
	var CUSTOM_HOST_TFDTPBUF_SIZE;

	CUSTOM_HOST_BUFF_DESC_SIZE       =   2*MB;
	CUSTOM_HOST_CODE_SIZE            =   2*MB;
	CUSTOM_HOST_BSS_SIZE             =  50*MB;
	CUSTOM_HOST_DATA_SIZE            =   4*MB;
	CUSTOM_HOST_DATA_SIZE            =   4*MB;
	CUSTOM_HOST_NDKBUF_SIZE          =   50*MB;
	CUSTOM_HOST_TFDTPBUF_SIZE        =   50*MB;

	DDR3_BASE_ADDR_0            = 0x80000000;


	/* Need to keep CPDMA buff descriptors at 0x80000000 as AMMU small page is mapped for this address to make it non-cacheable */
	CUSTOM_HOST_BUFF_DESC_ADDR       = DDR3_BASE_ADDR_0;
	CUSTOM_HOST_CODE_ADDR            = CUSTOM_HOST_BUFF_DESC_ADDR       + CUSTOM_HOST_BUFF_DESC_SIZE;
	CUSTOM_HOST_DATA_ADDR            = CUSTOM_HOST_CODE_ADDR      + CUSTOM_HOST_CODE_SIZE;
	CUSTOM_HOST_BSS_ADDR             = CUSTOM_HOST_DATA_ADDR      + CUSTOM_HOST_DATA_SIZE;
	CUSTOM_HOST_TFDTPBUF_ADDR             = CUSTOM_HOST_BSS_ADDR      + CUSTOM_HOST_BSS_SIZE;
	CUSTOM_HOST_NDKBUF_ADDR             = CUSTOM_HOST_TFDTPBUF_ADDR      + CUSTOM_HOST_TFDTPBUF_SIZE;
    var memory = new Array();
    var index = 0;

    memory[index++] = ["CUSTOM_HOST_BUFF_DESC_MEM", {
            comment : "CUSTOM_HOST_BUFF_DESC_MEM",
            name    : "CUSTOM_HOST_BUFF_DESC_MEM",
            base    : CUSTOM_HOST_BUFF_DESC_ADDR,
            len     : CUSTOM_HOST_BUFF_DESC_SIZE
        }];
     memory[index++] = ["CUSTOM_HOST_CODE_MEM", {
            comment : "CUSTOM_HOST_CODE_MEM",
            name    : "CUSTOM_HOST_CODE_MEM",
            access  : "RWX",
            base    : CUSTOM_HOST_CODE_ADDR,
            len     : CUSTOM_HOST_CODE_SIZE
        }];
    memory[index++] = ["CUSTOM_HOST_DATA_MEM", {
            comment : "CUSTOM_HOST_DATA_MEM",
            name    : "CUSTOM_HOST_DATA_MEM",
            access  : "RWX",
            base    : CUSTOM_HOST_DATA_ADDR,
            len     : CUSTOM_HOST_DATA_SIZE
        }];
    memory[index++] = ["CUSTOM_HOST_BSS_MEM", {
            comment : "CUSTOM_HOST_BSS_MEM",
            name    : "CUSTOM_HOST_BSS_MEM",
            access  : "RWX",
            base    : CUSTOM_HOST_BSS_ADDR,
            len     : CUSTOM_HOST_BSS_SIZE
        }];
    memory[index++] = ["CUSTOM_HOST_TFDTPBUF_MEM", {
            comment : "CUSTOM_HOST_TFDTPBUF_MEM",
            name    : "CUSTOM_HOST_TFDTPBUF_MEM",
            base    : CUSTOM_HOST_TFDTPBUF_ADDR,
            len     : CUSTOM_HOST_TFDTPBUF_SIZE
        }];
    memory[index++] = ["CUSTOM_HOST_NDKBUF_MEM", {
            comment : "CUSTOM_HOST_NDKBUF_MEM",
            name    : "CUSTOM_HOST_NDKBUF_MEM",
            base    : CUSTOM_HOST_NDKBUF_ADDR,
            len     : CUSTOM_HOST_NDKBUF_SIZE
        }];
        return (memory);
}

