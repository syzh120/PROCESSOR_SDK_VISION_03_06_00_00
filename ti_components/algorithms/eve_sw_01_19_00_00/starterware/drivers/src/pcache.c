/*
*
* Copyright (c) 2009-2017 Texas Instruments Incorporated
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

#include "GlobalTypes.h"
#include "cram.h"

/*#pragma CHECK_MISRA ("none")*/
#include "baseaddress.h"
#include "eve_control_cred.h"
/*#pragma RESET_MISRA ("required")*/

#include "pcache.h"


void EVE_PROGCACHE_BlockInvalidate
(
    CRED_index_t  component,
    const UWORD32  *address,
    UWORD32  num_bytes
)
{
    UWORD32 value;

     /* CHECK_MISRA("-10.3")  -> Disable rule 10.3  */
     /* CHECK_MISRA("-11.3")  -> Disable rule 11.3  */
     /* MISRA.CAST.INT/ MISRA.CAST.PTR_TO_INT : The value of a complex expression of integer type shall only be */
     /* cast to a type of the same signedness that is no wider than the underlying type of the expression */
     /* Memory mapped regsiters and other hardware features access requires typecasting of pointer to integer.
     The address space is 32 bit and type casting to integer will not result into any loss because of TI's
     compiler teratment to integer.   */

    /* Write the address and number of bytes to invaidate the cache */
    WR_REG_32(component, EVE_CONTROL__EVE_PC_IBAR, address);
    WR_REG_32(component, EVE_CONTROL__EVE_PC_IBC,  num_bytes);

    /* Read PC_IBC and ensure that it goes down to 0, to ensure completion*/
    value = RD_REG_32 (component, EVE_CONTROL__EVE_PC_IBC);

    while (value != 0x0)
    {
        value = RD_REG_32 (component, EVE_CONTROL__EVE_PC_IBC);
    }
    /*RESET_MISRA("11.3")  -> Reset rule 11.3 for MISRA.CAST.PTR_TO_INT */
    /*RESET_MISRA("10.3")  -> Reset rule 10.3 for MISRA.CAST.INT */
}

void EVE_PROGCACHE_GlobalInvalidate (CRED_index_t  component)
{
    UWORD32 value;

    /* CHECK_MISRA("-10.3")  -> Disable rule 10.3  */
    /* CHECK_MISRA("-11.3")  -> Disable rule 11.3  */
    /* MISRA.CAST.INT/ MISRA.CAST.PTR_TO_INT : The value of a complex expression of integer type shall only be */
    /* cast to a type of the same signedness that is no wider than the underlying type of the expression */
    /* Memory mapped regsiters and other hardware features access requires typecasting of pointer to integer.
    The address space is 32 bit and type casting to integer will not result into any loss because of TI's
    compiler teratment to integer.   */

    /* Write a 0x1 to cause global invalidation of cache */
    WR_REG_32(component, EVE_CONTROL__EVE_PC_INV, 0x1);

    /* Read back and make sure value went to 0x0, to confirm global inv. */
    value = RD_REG_32 (component, EVE_CONTROL__EVE_PC_INV);

    while (value != 0x0)
    {
        value = RD_REG_32 (component, EVE_CONTROL__EVE_PC_INV);
    }
    /*RESET_MISRA("11.3")  -> Reset rule 11.3 for MISRA.CAST.PTR_TO_INT */
    /*RESET_MISRA("10.3")  -> Reset rule 10.3 for MISRA.CAST.INT */
}


void EVE_PROGCACHE_Prefetch (CRED_index_t component, const UWORD32 *addr, UWORD32 sizePrefetch)
{
    UWORD32 value;

    /* CHECK_MISRA("-10.3")  -> Disable rule 10.3  */
    /* CHECK_MISRA("-11.3")  -> Disable rule 11.3  */
    /* MISRA.CAST.INT/ MISRA.CAST.PTR_TO_INT : The value of a complex expression of integer type shall only be */
    /* cast to a type of the same signedness that is no wider than the underlying type of the expression */
    /* Memory mapped regsiters and other hardware features access requires typecasting of pointer to integer.
    The address space is 32 bit and type casting to integer will not result into any loss because of TI's
    compiler teratment to integer.   */
    WR_REG_32(component, EVE_CONTROL__EVE_PC_PBAR, addr);
    WR_REG_32(component,  EVE_CONTROL__EVE_PC_PBC,  sizePrefetch);

    value = RD_REG_32 (component, EVE_CONTROL__EVE_PC_PBC);

    while (value != 0x0)
    {
        value = RD_REG_32 (component, EVE_CONTROL__EVE_PC_PBC);
    }
    /*RESET_MISRA("11.3")  -> Reset rule 11.3 for MISRA.CAST.PTR_TO_INT */
    /*RESET_MISRA("10.3")  -> Reset rule 10.3 for MISRA.CAST.INT */
}



