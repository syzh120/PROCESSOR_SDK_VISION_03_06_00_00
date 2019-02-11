/*
 * Copyright (c) 2014-2015 Texas Instruments Incorporated - http://www.ti.com
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/**
 *  @file linux/include/ti/ipc/interfaces/ITransport.h
 *
 *  @brief Base interface for all message transports
 *
 *  All message transport interfaces must inherit from this base class.
 *
 *  The ITransport interface includes the following instance methods:
 *
 *  itype - return the derived interface type
 */

/*
 *  ======== ITransport.h ========
 */

#ifndef ITRANSPORT_H
#define ITRANSPORT_H

#if defined (__cplusplus)
extern "C" {
#endif

/*!
 *  @brief  Interface type ID
 *
 *  When adding a new interface type, please ensure to define a
 *  unique ID value for each new type.
 */
#define ITransport_TypeId 0x01

/*!
 *  @brief ITransport_Handle type
 *
 *  An opaque instance handle.
 */
typedef struct ITransport_Object *ITransport_Handle;

/*!
 *  @brief The instance object definition for ITransport
 */
typedef struct ITransport_Object {

    Int interfaceType;
    /*!< Interface type ID
     *
     *  This field is initialized by the constructor of the derived
     *  implementation. It should be assigned the interface type ID
     *  which is being implemented.
     */
} ITransport_Object;

/*!
 *  @brief Identify the derived interface type
 *
 *  Identify the interface type which is implemented by the instance
 *  object. Transport users (e.g. MessageQ) would use this method to
 *  identify the interface type and then downcast the ITransport_Handle
 *  to that interface type.
 *
 *  @param[in]  inst        Instance handle
 *
 *  @return     Derived interface type ID
 */
static inline
Int ITransport_itype(ITransport_Handle inst)
{
    ITransport_Object *obj = (ITransport_Object *)inst;
    return obj->interfaceType;
}

#if defined (__cplusplus)
}
#endif
#endif /* ITRANSPORT_H */
