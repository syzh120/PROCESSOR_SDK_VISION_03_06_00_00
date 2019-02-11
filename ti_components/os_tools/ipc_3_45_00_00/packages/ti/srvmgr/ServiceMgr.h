/*
 * Copyright (c) 2011-2013, Texas Instruments Incorporated
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
/*
 *  ======== service_mgr.c ========
 *  Simple server that handles requests to create threads (services) by name
 *  and provide an endpoint to the new thread.
 *
 */

#ifndef ti_srvmgr_ServiceMgr__include
#define ti_srvmgr_ServiceMgr__include

#include <xdc/std.h>

#include <ti/sysbios/knl/Task.h>
#include <ti/grcm/RcmServer.h>


#if defined (__cplusplus)
extern "C" {
#endif


/* Max number of known service types: */
#define ServiceMgr_NUMSERVICETYPES         16

/*!
 *  @brief Service instance object handle
 */
typedef RcmServer_Handle  Service_Handle;

/*!
 *  @brief Service disconnect notifier hook function type definition
 */
typedef Void (*ServiceMgr_disconnectFuncPtr)(Service_Handle srvc, Ptr data);

/*
 *  ======== ServiceMgr_init ========
 */
/*!
 *  @brief Initialize the ServiceMgr.
 *
 *  Currently, this simply initializes the RcmServer module.a
 *
 */
Void ServiceMgr_init();

/*
 *  ======== ServiceMgr_registerSrvTask ========
 */
/*!
 *  @brief Register a task associated with a service
 *
 *  This function registers a service task function with the ServiceMgr module.
 *  This allows the service tasks to be outside the scope of the ServiceMgr
 *  module, and allow users to define their own services with its associated
 *  task function. After all the registrations are done, a ServiceMgr_start
 *  would start these tasks.
 *
 *  @param[in] reserved    Reserved for future scalability
 *  @param[in] func        Task function to run for a particular service task
 *  @param[in] taskParams  Initialized task parameters that will be used to
 *                         create the task
 *
 *  @sa ServiceMgr_start
 */
Bool ServiceMgr_registerSrvTask(UInt16 reserved, Task_FuncPtr func,
                                Task_Params *taskParams);

/*
 *  ======== ServiceMgr_start ========
 */
/*!
 *  @brief Start the ServiceMgr services
 *
 *  This function creates all the task functions associated with the individual
 *  services. Each of the tasks is responsible for publishing a service to the
 *  remote processor and service all the incoming connection requests on that
 *  service.
 *
 *  @param[in] reserved    Reserved for future scalability
 *
 *  @sa ServiceMgr_registerTask
 */
UInt ServiceMgr_start(UInt16 reserved);

/*
 *  ======== ServiceMgr_register ========
 */
/*!
 *  @brief Register a service with its static function table.
 *
 *  This function stores the RcmServerParams structure with the name key, which
 *  the ServiceMgr will find on a subsequent connect call to instantiate an
 *  RcmServer of this name.
 *
 *  @param[in] name    The name of the server that messages will be sent to for
 *  executing commands. The name must be a system-wide unique name.
 *
 *  @param[in] rcmServerParams  The RcmServer_create params used to initialize
 *                              the service instance.
 *
 *  @sa RcmServer_create
 */
Bool ServiceMgr_register(String name, RcmServer_Params *rcmServerParams);

/*
 *  ======== ServiceMgr_send ========
 */
/*!
 *  @brief Send an asynchrounous message to a service's client endpoint.
 *
 *  This function uses the reply endpoint registered with the given service
 *  by the ServiceMgr, to send a message to the client.  It is meant to
 *  be used for asynchronous callbacks from service functions, where the
 *  callbacks do not expect a reply (hence, no ServiceMgr_recv is defined).
 *
 *  @param[in]  srvc    Handle to a service, passed into every service function.
 *  @param[in]  data    Data payload to be copied and sent. First structure
 *                      must be an omx_hdr
 *  @param[in]  len     Amount of data to be copied.
 *
 */
Void ServiceMgr_send(Service_Handle srvc, Ptr data, UInt16 len);

/*
 *  ======== ServiceMgr_registerdisconnectFxn =======
 */
/*!
 *  @brief Registers a application-specific service disconnect callback function
 *
 *  @param[in]  srvc           Handle to a service, passed into every service
 *                             function
 *  @param[in]  data           Pointer to application-specific data passed back
 *                             to the disconnect hook function
 *  @param[in]  func           Hook function to be called on a service disconnect
 *
 */
Bool ServiceMgr_registerDisconnectFxn(Service_Handle srvc, Ptr data,
                                      ServiceMgr_disconnectFuncPtr func);

/*
 *  ======== ServiceMgr_createService =======
 */
/*!
 *  @brief Create a RCM Server instance associated with a service
 *
 *  Create a RCM server instance using the set of functions associated with the
 *  name, and returns an end point address registered for the service.
 *
 *  @param[in]  name           Name associated with RCM function set
 *  @param[in]  endPt          Endpoint pointer address
 *
 */
UInt32 ServiceMgr_createService(Char * name, UInt32 * endPt);

/*
 *  ======== ServiceMgr_deleteService =======
 */
/*!
 *  @brief Delete the RCM Server instance associated with an endpoint address
 *
 *  Deletes the RCM Servver instance associated with a particular endpoint
 *  address.
 *
 *  @param[in]  addr          EndPoint pointer address associated with the
 *                            service to delete.
 *
 */
UInt32 ServiceMgr_deleteService(UInt32 addr);


#if defined (__cplusplus)
}
#endif /* defined (__cplusplus) */

#endif /* ti_srvmgr_ServiceMgr__include */
