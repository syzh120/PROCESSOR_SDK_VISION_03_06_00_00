/*
Copyright (c) [2012 - 2017] Texas Instruments Incorporated

All rights reserved not granted herein.

Limited License.

 Texas Instruments Incorporated grants a world-wide, royalty-free, non-exclusive
 license under copyrights and patents it now or hereafter owns or controls to
 make,  have made, use, import, offer to sell and sell ("Utilize") this software
 subject to the terms herein.  With respect to the foregoing patent license,
 such license is granted  solely to the extent that any such patent is necessary
 to Utilize the software alone.  The patent license shall not apply to any
 combinations which include this software, other than combinations with devices
 manufactured by or for TI ("TI Devices").  No hardware patent is licensed
 hereunder.

 Redistributions must preserve existing copyright notices and reproduce this
 license (including the above copyright notice and the disclaimer and
 (if applicable) source code license limitations below) in the documentation
 and/or other materials provided with the distribution

 Redistribution and use in binary form, without modification, are permitted
 provided that the following conditions are met:

 * No reverse engineering, decompilation, or disassembly of this software
   is permitted with respect to any software provided in binary form.

 * Any redistribution and use are licensed by TI for use only with TI Devices.

 * Nothing shall obligate TI to provide you with source code for the software
   licensed and provided to you in object code.

 If software source code is provided to you, modification and redistribution of
 the source code are permitted provided that the following conditions are met:

 * Any redistribution and use of the source code, including any resulting
   derivative works, are licensed by TI for use only with TI Devices.

 * Any redistribution and use of any object code compiled from the source code
   and any resulting derivative works, are licensed by TI for use only with TI
   Devices.

 Neither the name of Texas Instruments Incorporated nor the names of its
 suppliers may be used to endorse or promote products derived from this software
 without specific prior written permission.

 DISCLAIMER.

 THIS SOFTWARE IS PROVIDED BY TI AND TI’S LICENSORS "AS IS" AND ANY EXPRESS OR
 IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 IN NO EVENT SHALL TI AND TI’S LICENSORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
 OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

/**
 *******************************************************************************
 * \file system_gl_egl_utils.c
 *
 * \brief   System level helper functions for GL/EGL.
 *
 */
#ifndef _SYSTEM_GL_EGL_UTILS_H_
#define _SYSTEM_GL_EGL_UTILS_H_

#include <osa.h>
#include <osa_que.h>
#include <include/link_api/system_const.h>

#include <EGL/egl.h>
#include <EGL/eglext.h>
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>

#include "system_egl_context.h"

#define SYSTEM_MAXNUM_EGL_BUFFERS               (4)
#define SYSTEM_EGL_MAX_TEXTURES                 (100)

/**
 *******************************************************************************
 *
 * \brief Maximum number of output queues that SGX link supports.
 *
 * SUPPORTED in ALL platforms
 *
 *******************************************************************************
 */
#define  SGX_LINK_MAX_OUT_QUE                   (1U)

typedef struct {

    System_VideoDataFormat dataFormat;
    /**< SUPPORTED Formats,
     *    SYSTEM_DF_YUV420SP_UV
     */

    UInt32 width;
    /**< in pixels */

    UInt32 height;
    /**< in lines */

    UInt32 pitch[SYSTEM_MAX_PLANES];
    /**< in bytes, only pitch[0] used right now */

} System_EglTexProperty;

typedef struct
{
    EGLDisplay display;
    EGLNativeDisplayType nativeDisplay;
    /**< Native display device */
    EGLConfig config;
    EGLContext context;
    System_Buffer *eglBuffers[SYSTEM_MAXNUM_EGL_BUFFERS];

    EGLNativeWindowType windowNative;
    EGLSurface surface;

    struct control_srv_egl_ctx eglInfo;
    /**< EGL functions to obtain pixmap buffers */

    GLuint      texYuv[SYSTEM_EGL_MAX_TEXTURES];
    EGLImageKHR texImg[SYSTEM_EGL_MAX_TEXTURES];
    Void        *bufAddr[SYSTEM_EGL_MAX_TEXTURES];
    int         dmaBufFd[SYSTEM_EGL_MAX_TEXTURES];
    int numBuf;

    int width;
    int height;

    System_LinkChInfo chInfo;

    UInt64 tsHolder[SYSTEM_MAXNUM_EGL_BUFFERS];
    UInt32 tsHolderRdIdx;
    UInt32 tsHolderWtIdx;

} System_EglWindowObj;

typedef struct
{
    EGLDisplay display;
    EGLNativeDisplayType nativeDisplay;
    /**< Native display device */
    EGLConfig config;
    EGLContext context;
    System_Buffer *eglBuffers[SYSTEM_MAXNUM_EGL_BUFFERS];

    OSA_QueHndl eglEmptyBufQue;
    /**< The queue that will hold the empty buffers */

    OSA_QueHndl eglFullBufQue;
    /**< The queue that will hold the rendered buffers */

    struct control_srv_egl_ctx eglInfo;
    /**< EGL functions to obtain pixmap buffers */

    GLuint      texYuv[SYSTEM_EGL_MAX_TEXTURES];
    EGLImageKHR texImg[SYSTEM_EGL_MAX_TEXTURES];
    Void        *bufAddr[SYSTEM_EGL_MAX_TEXTURES];
#ifdef QNX_BUILD
    Void        *eglPixmap[SYSTEM_EGL_MAX_TEXTURES];
#else
    int         dmaBufFd[SYSTEM_EGL_MAX_TEXTURES];
#endif
    int numBuf;

    int width;
    int height;

    System_LinkChInfo chInfo;

} System_EglObj;


void System_eglCheckGlError(const char* op);
void System_eglCheckEglError(const char* op, EGLBoolean returnVal);
void System_eglPrintGLString(const char *name, GLenum s);
int System_eglOpen(System_EglObj *pEglObj, struct control_srv_egl_ctx *eglInfo);
int System_eglWindowOpen(System_EglWindowObj *pEglWindowObj, struct control_srv_egl_ctx *eglInfo);
int System_eglMakeCurrentBuffer(System_EglObj *pEglObj, EGLSurface surface);
int System_eglMakeCurrentNill(System_EglObj *pEglObj);
#ifdef QNX_BUILD
GLuint System_eglGetTexYuv(System_EglObj *pEglObj, System_EglTexProperty *pProp, void *bufAddr);
#else
GLuint System_eglGetTexYuv(System_EglObj *pEglObj, System_EglTexProperty *pProp, int dmaBufFd);
GLuint System_eglWindowGetTexYuv(System_EglWindowObj *pEglWindowObj, System_EglTexProperty *pProp, int dmaBufFd);
#endif
void System_eglWaitSync(System_EglObj *pEglObj);
void System_eglSwap(System_EglWindowObj *pEglWindowObj, UInt64 srcTimeStamp);
System_Buffer *System_eglWindowGetNextBuffer(System_EglWindowObj *pEglWindowObj, UInt64 *srcTimeStamp);
void System_eglWindowPutBuffer(System_EglWindowObj *pEglWindowObj, System_Buffer *nextBuf);
int System_eglClose(System_EglObj *pEglObj);
int System_eglWindowClose(System_EglWindowObj *pEglWindowObj);

#endif
