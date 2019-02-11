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
#include "system_gl_egl_utils.h"

#ifndef EGL_TI_raw_video
#  define EGL_TI_raw_video             1
#  define EGL_RAW_VIDEO_TI             0x333A   /* eglCreateImageKHR target */
#  define EGL_GL_VIDEO_FOURCC_TI       0x3331   /* eglCreateImageKHR attribute */
#  define EGL_GL_VIDEO_WIDTH_TI        0x3332   /* eglCreateImageKHR attribute */
#  define EGL_GL_VIDEO_HEIGHT_TI       0x3333   /* eglCreateImageKHR attribute */
#  define EGL_GL_VIDEO_BYTE_STRIDE_TI  0x3334   /* eglCreateImageKHR attribute */
#  define EGL_GL_VIDEO_BYTE_SIZE_TI    0x3335   /* eglCreateImageKHR attribute */
#  define EGL_GL_VIDEO_YUV_FLAGS_TI    0x3336   /* eglCreateImageKHR attribute */
#endif

#ifndef EGLIMAGE_FLAGS_YUV_CONFORMANT_RANGE
#  define EGLIMAGE_FLAGS_YUV_CONFORMANT_RANGE (0 << 0)
#  define EGLIMAGE_FLAGS_YUV_FULL_RANGE       (1 << 0)
#  define EGLIMAGE_FLAGS_YUV_BT601            (0 << 1)
#  define EGLIMAGE_FLAGS_YUV_BT709            (1 << 1)
#endif

#define FOURCC(a, b, c, d) ((uint32_t)(uint8_t)(a) | ((uint32_t)(uint8_t)(b) << 8) | ((uint32_t)(uint8_t)(c) << 16) | ((uint32_t)(uint8_t)(d) << 24 ))
#define FOURCC_STR(str)    FOURCC(str[0], str[1], str[2], str[3])

#if defined (QNX_BUILD)
static EGLSyncKHR (*eglCreateSyncKHR)(EGLDisplay dpy, EGLenum type, const EGLint *attrib_list);
static EGLBoolean (*eglDestroySyncKHR)(EGLDisplay dpy, EGLSyncKHR sync);
static EGLint (*eglClientWaitSyncKHR)(EGLDisplay dpy, EGLSyncKHR sync, EGLint flags, EGLTimeKHR timeout);
#endif

void System_eglPrintGLString(const char *name, GLenum s) {

   const char *v = (const char *) glGetString(s);

   Vps_printf(" EGL: GL %s = %s\n", name, v);
}

void System_eglCheckGlError(const char* op) {
   GLint error;

   for (error = glGetError(); error; error = glGetError()) {
       fprintf(stderr, "GL: after %s() glError (0x%x)\n", op, error);
   }
}

void System_eglCheckEglError(const char* op, EGLBoolean returnVal) {
   EGLint error;

   if (returnVal != EGL_TRUE) {
       fprintf(stderr, " EGL: %s() returned %d\n", op, returnVal);
   }

   for (error = eglGetError(); error != EGL_SUCCESS; error = eglGetError()) {
       fprintf(stderr, " EGL: after %s() eglError (0x%x)\n", op, error);
   }
}

#ifdef QNX_BUILD
static void egl_config_verbose(EGLDisplay egl_disp, EGLConfig egl_conf)
{
    int i;

    Vps_printf("EGL_VENDOR = %s\n", eglQueryString(egl_disp, EGL_VENDOR));
    Vps_printf("EGL_VERSION = %s\n", eglQueryString(egl_disp, EGL_VERSION));
    Vps_printf("EGL_CLIENT_APIS = %s\n", eglQueryString(egl_disp, EGL_CLIENT_APIS));
    Vps_printf("EGL_EXTENSIONS = %s\n\n", eglQueryString(egl_disp, EGL_EXTENSIONS));

    i = -1;
    eglGetConfigAttrib(egl_disp, egl_conf, EGL_CONFIG_ID, &i);
    Vps_printf("EGL_CONFIG_ID = %d\n", i);

    i = 0;
    eglGetConfigAttrib(egl_disp, egl_conf, EGL_RED_SIZE, &i);
    Vps_printf("EGL_RED_SIZE = %d\n", i);

    i = 0;
    eglGetConfigAttrib(egl_disp, egl_conf, EGL_GREEN_SIZE, &i);
    Vps_printf("EGL_GREEN_SIZE = %d\n", i);

    i = 0;
    eglGetConfigAttrib(egl_disp, egl_conf, EGL_BLUE_SIZE, &i);
    Vps_printf("EGL_BLUE_SIZE = %d\n", i);

    i = 0;
    eglGetConfigAttrib(egl_disp, egl_conf, EGL_ALPHA_SIZE, &i);
    Vps_printf("EGL_ALPHA_SIZE = %d\n", i);

    i = 0;
    eglGetConfigAttrib(egl_disp, egl_conf, EGL_DEPTH_SIZE, &i);
    Vps_printf("EGL_DEPTH_SIZE = %d\n", i);

    i = 0;
    eglGetConfigAttrib(egl_disp, egl_conf, EGL_LEVEL, &i);
    Vps_printf("EGL_LEVEL = %d\n", i);

    i = 0;
    eglGetConfigAttrib(egl_disp, egl_conf, EGL_NATIVE_RENDERABLE, &i);
    Vps_printf("EGL_NATIVE_RENDERABLE = %s\n", i ? "EGL_TRUE" : "EGL_FALSE");

    i = 0;
    eglGetConfigAttrib(egl_disp, egl_conf, EGL_NATIVE_VISUAL_TYPE, &i);
    Vps_printf("EGL_NATIVE_VISUAL_TYPE = %d\n", i);

    i = 0;
    eglGetConfigAttrib(egl_disp, egl_conf, EGL_RENDERABLE_TYPE, &i);
    Vps_printf("EGL_RENDERABLE_TYPE = 0x%04x\n", i);

    i = 0;
    eglGetConfigAttrib(egl_disp, egl_conf, EGL_SURFACE_TYPE, &i);
    Vps_printf("EGL_SURFACE_TYPE = 0x%04x\n", i);

    i = 0;
    eglGetConfigAttrib(egl_disp, egl_conf, EGL_TRANSPARENT_TYPE, &i);
    if (i == EGL_TRANSPARENT_RGB) {
        Vps_printf("EGL_TRANSPARENT_TYPE = EGL_TRANSPARENT_RGB\n");

        i = 0;
        eglGetConfigAttrib(egl_disp, egl_conf, EGL_TRANSPARENT_RED_VALUE, &i);
        Vps_printf("EGL_TRANSPARENT_RED = 0x%02x\n", i);

        i = 0;
        eglGetConfigAttrib(egl_disp, egl_conf, EGL_TRANSPARENT_GREEN_VALUE, &i);
        Vps_printf("EGL_TRANSPARENT_GREEN = 0x%02x\n", i);

        i = 0;
        eglGetConfigAttrib(egl_disp, egl_conf, EGL_TRANSPARENT_BLUE_VALUE, &i);
        Vps_printf("EGL_TRANSPARENT_BLUE = 0x%02x\n\n", i);
    } else {
        Vps_printf("EGL_TRANSPARENT_TYPE = EGL_NONE\n\n");
    }
}

static void egl_config_verbose2()
{
    Vps_printf("GL_VENDOR = %s\n", (char *)glGetString(GL_VENDOR));
    Vps_printf("GL_RENDERER = %s\n", (char *)glGetString(GL_RENDERER));
    Vps_printf("GL_VERSION = %s\n", (char *)glGetString(GL_VERSION));
    Vps_printf("GL_EXTENSIONS = %s\n", (char *)glGetString(GL_EXTENSIONS));
}
#endif

int System_eglOpen(System_EglObj *pEglObj, struct control_srv_egl_ctx *eglInfo)
{
    EGLint num_configs;
    EGLint majorVersion;
    EGLint minorVersion;
    int ret, count;
    System_Buffer *nextBuf;
    int status;
    System_EglPixmapVideoFrameBuffer *eglBuf;
    EGLCompatBuffer eglCBuf;
    UInt32 flags = pEglObj->chInfo.flags;

    const EGLint attribs[] = {
       EGL_RED_SIZE, 1,
       EGL_GREEN_SIZE, 1,
       EGL_BLUE_SIZE, 1,
       EGL_ALPHA_SIZE, 0,
       EGL_SURFACE_TYPE, EGL_PIXMAP_BIT,
       EGL_RENDERABLE_TYPE, EGL_OPENGL_ES2_BIT,
       EGL_DEPTH_SIZE, 8,
       EGL_NONE
    };
    EGLint context_attribs[] = { EGL_CONTEXT_CLIENT_VERSION, 2, EGL_NONE };

    memcpy(&(pEglObj->eglInfo), eglInfo, sizeof(pEglObj->eglInfo));

    pEglObj->nativeDisplay = pEglObj->eglInfo.get_egl_native_display();
    pEglObj->display = eglGetDisplay((EGLNativeDisplayType)pEglObj->nativeDisplay);
    System_eglCheckEglError("eglGetDisplay", EGL_TRUE);
    if (pEglObj->display == EGL_NO_DISPLAY) {
       Vps_printf(" EGL: ERROR: eglGetDisplay() returned EGL_NO_DISPLAY !!!\n");
       return -1;
    }

    ret = eglInitialize(pEglObj->display, &majorVersion, &minorVersion);
    System_eglCheckEglError("eglInitialize", ret);
    Vps_printf(" EGL: version %d.%d\n", majorVersion, minorVersion);
    if (ret != EGL_TRUE) {
       Vps_printf(" EGL: eglInitialize() failed !!!\n");
       return -1;
    }

    if (!eglBindAPI(EGL_OPENGL_ES_API)) { // Shiju - add in VSDK
        Vps_printf(" EGL: ERROR - failed to bind api EGL_OPENGL_ES_API\n");
        return -1;
    }

    if (!eglChooseConfig(pEglObj->display, attribs, &pEglObj->config, 1, &num_configs))
    {
       Vps_printf(" EGL: ERROR: eglChooseConfig() failed. Couldn't get an EGL visual config !!!\n");
       return -1;
    }

    pEglObj->context = eglCreateContext(pEglObj->display, pEglObj->config, EGL_NO_CONTEXT, context_attribs);
    System_eglCheckEglError("eglCreateContext", EGL_TRUE);
    if (pEglObj->context == EGL_NO_CONTEXT) {
       Vps_printf(" EGL: eglCreateContext() failed !!!\n");
       return -1;
    }

#ifdef QNX_BUILD
    egl_config_verbose(pEglObj->display, pEglObj->config);
#else
    ret = eglMakeCurrent(pEglObj->display, EGL_NO_SURFACE, EGL_NO_SURFACE, pEglObj->context);
    System_eglCheckEglError("eglMakeCurrent", ret);
    if (ret != EGL_TRUE) {
       Vps_printf(" EGL: eglMakeCurrent() failed !!!\n");
       return -1;
    }

    System_eglPrintGLString("Version", GL_VERSION);
    System_eglPrintGLString("Vendor", GL_VENDOR);
    System_eglPrintGLString("Renderer", GL_RENDERER);
    System_eglPrintGLString("Extensions", GL_EXTENSIONS);
#endif

    status  = OSA_queCreate(&(pEglObj->eglEmptyBufQue), SYSTEM_MAXNUM_EGL_BUFFERS);
    OSA_assert(status == SYSTEM_LINK_STATUS_SOK);

    status  = OSA_queCreate(&(pEglObj->eglFullBufQue), SYSTEM_MAXNUM_EGL_BUFFERS);
    OSA_assert(status == SYSTEM_LINK_STATUS_SOK);

    for (count = 0; count < SYSTEM_MAXNUM_EGL_BUFFERS; count++)
    {
        nextBuf = OSA_memAlloc(sizeof(System_Buffer));
        OSA_assert(nextBuf != NULL);

        nextBuf->payload = OSA_memAlloc(sizeof(System_EglPixmapVideoFrameBuffer));
        OSA_assert(nextBuf->payload != NULL);

        nextBuf->payloadSize = sizeof(System_EglPixmapVideoFrameBuffer);
        nextBuf->bufType = SYSTEM_BUFFER_TYPE_EGLPIXMAP_VIDEO_FRAME;
        nextBuf->chNum = 0;
        nextBuf->frameId = 0;

        eglBuf = nextBuf->payload;
        eglCBuf = pEglObj->eglInfo.get_egl_native_buffer(pEglObj->width, pEglObj->height);
        eglBuf->eglPixmap = eglCBuf.eglPixmap;
        eglBuf->pixmapNative = eglCBuf.pixmapNative;
        eglBuf->bufAddr[0] = eglCBuf.pixmapNative;
#ifdef QNX_BUILD
        eglBuf->pixmapNativePtr = eglCBuf.pixmapNativePtr;
#endif
        eglBuf->eglSurface = (UInt32)eglCreatePixmapSurface(pEglObj->display, pEglObj->config, eglBuf->eglPixmap, NULL);
        OSA_assert(eglBuf->eglSurface != (UInt32)EGL_NO_SURFACE);

        eglBuf->chInfo.flags = System_Link_Ch_Info_Set_Flag_Data_Format(flags, SYSTEM_DF_ARGB32_8888);
        eglBuf->chInfo.pitch[0] = eglCBuf.stride;
        eglBuf->chInfo.pitch[1] = eglCBuf.stride;
        eglBuf->chInfo.pitch[2] = eglCBuf.stride;
        eglBuf->chInfo.width = eglCBuf.width;
        eglBuf->chInfo.height= eglCBuf.height;
        eglBuf->chInfo.startX= 0;
        eglBuf->chInfo.startY= 0;
        eglBuf->flags = System_Link_Ch_Info_Set_Flag_Data_Format(flags, SYSTEM_DF_ARGB32_8888);

        pEglObj->chInfo.width = eglCBuf.width;
        pEglObj->chInfo.height= eglCBuf.height;
        pEglObj->chInfo.pitch[0] = eglCBuf.stride;
        pEglObj->chInfo.pitch[1] = eglCBuf.stride;
        pEglObj->chInfo.pitch[2] = eglCBuf.stride;
        pEglObj->chInfo.startX   = 0;
        pEglObj->chInfo.startY   = 0;
        pEglObj->chInfo.flags = System_Link_Ch_Info_Set_Flag_Data_Format(flags, SYSTEM_DF_ARGB32_8888);

        //Vps_printf("System Buffer created = %p, contains = %p (eglpixmap = %p) eglBuf->pixmapNativeptr = %p\n", nextBuf, eglBuf, eglBuf->eglPixmap,eglBuf->pixmapNativePtr);

        OSA_quePut(&(pEglObj->eglEmptyBufQue), (Int32)nextBuf, OSA_TIMEOUT_FOREVER);
        pEglObj->eglBuffers[count] = nextBuf;
    }
#ifdef QNX_BUILD
    eglBuf = pEglObj->eglBuffers[0]->payload;
    ret = eglMakeCurrent(pEglObj->display, (EGLSurface)eglBuf->eglSurface, (EGLSurface)eglBuf->eglSurface, pEglObj->context);
    OSA_assert(ret != 0);

    egl_config_verbose2();
#endif

    return 0;
}

int System_eglWindowOpen(System_EglWindowObj *pEglWindowObj, struct control_srv_egl_ctx *eglInfo)
{
    EGLint num_configs;
    EGLint majorVersion;
    EGLint minorVersion;
    int ret, count;
    System_Buffer *nextBuf;
    System_EglPixmapVideoFrameBuffer *eglBuf;
    EGLCompatBuffer eglCBuf;
    UInt32 flags = pEglWindowObj->chInfo.flags;
    EGLCompatBuffer eglCBufArray[SYSTEM_MAXNUM_EGL_BUFFERS];

    const EGLint attribs[] = {
       EGL_RED_SIZE, 1,
       EGL_GREEN_SIZE, 1,
       EGL_BLUE_SIZE, 1,
       EGL_ALPHA_SIZE, 0,
       EGL_SURFACE_TYPE, EGL_WINDOW_BIT,
       EGL_RENDERABLE_TYPE, EGL_OPENGL_ES2_BIT,
       EGL_DEPTH_SIZE, 8,
       EGL_NONE
    };
    EGLint context_attribs[] = { EGL_CONTEXT_CLIENT_VERSION, 2, EGL_NONE };

    memcpy(&(pEglWindowObj->eglInfo), eglInfo, sizeof(pEglWindowObj->eglInfo));

    pEglWindowObj->nativeDisplay = pEglWindowObj->eglInfo.get_egl_native_display();
    pEglWindowObj->display = eglGetDisplay((EGLNativeDisplayType)pEglWindowObj->nativeDisplay);
    System_eglCheckEglError("eglGetDisplay", EGL_TRUE);
    if (pEglWindowObj->display == EGL_NO_DISPLAY) {
       Vps_printf(" EGL: ERROR: eglGetDisplay() returned EGL_NO_DISPLAY !!!\n");
       return -1;
    }

    ret = eglInitialize(pEglWindowObj->display, &majorVersion, &minorVersion);
    System_eglCheckEglError("eglInitialize", ret);
    Vps_printf(" EGL: version %d.%d\n", majorVersion, minorVersion);
    if (ret != EGL_TRUE) {
       Vps_printf(" EGL: eglInitialize() failed !!!\n");
       return -1;
    }

    if (!eglBindAPI(EGL_OPENGL_ES_API)) { // Shiju - add in VSDK
        Vps_printf(" EGL: ERROR - failed to bind api EGL_OPENGL_ES_API\n");
        return -1;
    }

    if (!eglChooseConfig(pEglWindowObj->display, attribs, &pEglWindowObj->config, 1, &num_configs))
    {
       Vps_printf(" EGL: ERROR: eglChooseConfig() failed. Couldn't get an EGL visual config !!!\n");
       return -1;
    }

    pEglWindowObj->context = eglCreateContext(pEglWindowObj->display, pEglWindowObj->config, EGL_NO_CONTEXT, context_attribs);
    System_eglCheckEglError("eglCreateContext", EGL_TRUE);
    if (pEglWindowObj->context == EGL_NO_CONTEXT) {
       Vps_printf(" EGL: eglCreateContext() failed !!!\n");
       return -1;
    }

    System_eglPrintGLString("Version", GL_VERSION);
    System_eglPrintGLString("Vendor", GL_VENDOR);
    System_eglPrintGLString("Renderer", GL_RENDERER);
    System_eglPrintGLString("Extensions", GL_EXTENSIONS);

    for (count = 0; count < SYSTEM_MAXNUM_EGL_BUFFERS; count++)
    {
        nextBuf = OSA_memAlloc(sizeof(System_Buffer));
        OSA_assert(nextBuf != NULL);

	memset(nextBuf, 0, sizeof(*nextBuf));

        nextBuf->payload = OSA_memAlloc(sizeof(System_EglPixmapVideoFrameBuffer));
        OSA_assert(nextBuf->payload != NULL);

        nextBuf->payloadSize = sizeof(System_EglPixmapVideoFrameBuffer);
        nextBuf->bufType = SYSTEM_BUFFER_TYPE_EGLPIXMAP_VIDEO_FRAME;
        nextBuf->chNum = 0;
        nextBuf->frameId = 0;

        eglBuf = nextBuf->payload;
        eglCBuf = pEglWindowObj->eglInfo.get_egl_native_buffer(pEglWindowObj->width, pEglWindowObj->height);
        eglBuf->eglPixmap = eglCBuf.eglPixmap;
        eglBuf->pixmapNative = eglCBuf.pixmapNative;
        eglBuf->bufAddr[0] = eglCBuf.pixmapNative;
#ifdef QNX_BUILD
        eglBuf->pixmapNativePtr = eglCBuf.pixmapNativePtr;
#endif

        eglBuf->chInfo.flags = System_Link_Ch_Info_Set_Flag_Data_Format(flags, SYSTEM_DF_ARGB32_8888);
        eglBuf->chInfo.pitch[0] = eglCBuf.stride;
        eglBuf->chInfo.pitch[1] = eglCBuf.stride;
        eglBuf->chInfo.pitch[2] = eglCBuf.stride;
        eglBuf->chInfo.width = eglCBuf.width;
        eglBuf->chInfo.height= eglCBuf.height;
        eglBuf->chInfo.startX= 0;
        eglBuf->chInfo.startY= 0;
        eglBuf->flags = System_Link_Ch_Info_Set_Flag_Data_Format(flags, SYSTEM_DF_ARGB32_8888);

        pEglWindowObj->chInfo.width = eglCBuf.width;
        pEglWindowObj->chInfo.height= eglCBuf.height;
        pEglWindowObj->chInfo.pitch[0] = eglCBuf.stride;
        pEglWindowObj->chInfo.pitch[1] = eglCBuf.stride;
        pEglWindowObj->chInfo.pitch[2] = eglCBuf.stride;
        pEglWindowObj->chInfo.startX   = 0;
        pEglWindowObj->chInfo.startY   = 0;
        pEglWindowObj->chInfo.flags = System_Link_Ch_Info_Set_Flag_Data_Format(flags, SYSTEM_DF_ARGB32_8888);

        //Vps_printf("System Buffer created = %p, contains = %p (eglpixmap = %p) eglBuf->pixmapNativeptr = %p\n", nextBuf, eglBuf, eglBuf->eglPixmap,eglBuf->pixmapNativePtr);

        pEglWindowObj->eglBuffers[count] = nextBuf;
	eglCBufArray[count] = eglCBuf;
    }

    pEglWindowObj->windowNative = pEglWindowObj->eglInfo.wrap_native_buffers(eglCBufArray, SYSTEM_MAXNUM_EGL_BUFFERS);

    pEglWindowObj->surface = eglCreateWindowSurface(pEglWindowObj->display, pEglWindowObj->config, pEglWindowObj->windowNative, NULL);
    System_eglCheckEglError("eglCreateWindowSurface", EGL_TRUE);
    if (pEglWindowObj->surface == EGL_NO_SURFACE) {
       Vps_printf(" EGL: eglCreateWindowSurface() failed !!!\n");
       return -1;
    }

    ret = eglMakeCurrent(pEglWindowObj->display, pEglWindowObj->surface, pEglWindowObj->surface, pEglWindowObj->context);
    System_eglCheckEglError("eglMakeCurrent", ret);
    if (ret != EGL_TRUE) {
       Vps_printf(" EGL: eglMakeCurrent() failed !!!\n");
       return -1;
    }

    pEglWindowObj->tsHolderRdIdx = 0;
    pEglWindowObj->tsHolderWtIdx = 0;

    return 0;
}

void System_eglWaitSync(System_EglObj *pEglObj)
{
#if defined (QNX_BUILD)
    int ret;
    EGLSyncKHR sync = NULL;

    if (eglCreateSyncKHR)
    {
        sync = eglCreateSyncKHR(pEglObj->display, EGL_SYNC_FENCE_KHR, NULL);
    }
    if(sync != EGL_NO_SYNC_KHR)
    {
        ret = eglClientWaitSyncKHR(pEglObj->display, sync,
                           EGL_SYNC_FLUSH_COMMANDS_BIT_KHR, 1000 * 1000 * 32);
        if (ret == EGL_TIMEOUT_EXPIRED_KHR)
        {
        Vps_printf(" SGXDISPLAY: wait for egl sync timed out\n");
        }
        else if (ret != EGL_CONDITION_SATISFIED_KHR)
        {
        Vps_printf(" SGXDISPLAY: failed to wait for egl sync: %x\n", eglGetError());
        }
        if (!eglDestroySyncKHR(pEglObj->display, sync))
        {
        Vps_printf(" SGXDISPLAY: error at eglDestroySyncKHR: %x\n", eglGetError());
        }
    }
#else
    eglWaitGL();
#endif
    return;
}

System_Buffer *System_eglWindowGetNextBuffer(System_EglWindowObj *pEglWindowObj, UInt64 *srcTimeStamp)
{
    Int32 i;
    System_Buffer *nextBuf;
    System_EglPixmapVideoFrameBuffer *eglBuf;
    EGLNativePixmapType bo;

    bo = pEglWindowObj->eglInfo.wrapper_get_next_buffer(pEglWindowObj->windowNative);
    for(i = 0; i < SYSTEM_MAXNUM_EGL_BUFFERS; i++)
    {
        nextBuf = pEglWindowObj->eglBuffers[i];
        eglBuf = nextBuf->payload;
        if(eglBuf->eglPixmap == bo)
            break;
    }
    OSA_assert(i < SYSTEM_MAXNUM_EGL_BUFFERS);

    *srcTimeStamp = pEglWindowObj->tsHolder[pEglWindowObj->tsHolderRdIdx];
    pEglWindowObj->tsHolderRdIdx++;
    pEglWindowObj->tsHolderRdIdx %= SYSTEM_MAXNUM_EGL_BUFFERS;

    return nextBuf;
}

void System_eglWindowPutBuffer(System_EglWindowObj *pEglWindowObj, System_Buffer *nextBuf)
{
    System_EglPixmapVideoFrameBuffer *eglBuf;

    eglBuf = nextBuf->payload;
    pEglWindowObj->eglInfo.wrapper_put_buffer(pEglWindowObj->windowNative, eglBuf->eglPixmap);
}

void System_eglSwap(System_EglWindowObj *pEglWindowObj, UInt64 srcTimeStamp)
{
    eglSwapBuffers(pEglWindowObj->display, pEglWindowObj->surface);

    pEglWindowObj->tsHolder[pEglWindowObj->tsHolderWtIdx] = srcTimeStamp;
    pEglWindowObj->tsHolderWtIdx++;
    pEglWindowObj->tsHolderWtIdx %= SYSTEM_MAXNUM_EGL_BUFFERS;
}

#ifndef QNX_BUILD
static GLuint System_eglWindowSetupYuvTexSurface(System_EglWindowObj *pObj, System_EglTexProperty *pProp, int dmaBufFd, int texIndex)
{
    EGLint attr[32];
    int attrIdx;
    PFNEGLCREATEIMAGEKHRPROC eglCreateImageKHR;
    PFNGLEGLIMAGETARGETTEXTURE2DOESPROC glEGLImageTargetTexture2DOES;

    attrIdx = 0;

    attr[attrIdx++] = EGL_LINUX_DRM_FOURCC_EXT;
    attr[attrIdx++] = FOURCC_STR("NV12");

    attr[attrIdx++] = EGL_WIDTH;
    attr[attrIdx++] = pProp->width;

    attr[attrIdx++] = EGL_HEIGHT;
    attr[attrIdx++] = pProp->height;

    attr[attrIdx++] = EGL_DMA_BUF_PLANE0_PITCH_EXT;
    attr[attrIdx++] = pProp->pitch[0];

    attr[attrIdx++] = EGL_DMA_BUF_PLANE1_PITCH_EXT;
    attr[attrIdx++] = pProp->pitch[0];

    attr[attrIdx++] = EGL_DMA_BUF_PLANE0_OFFSET_EXT;
    attr[attrIdx++] = 0;

    attr[attrIdx++] = EGL_DMA_BUF_PLANE1_OFFSET_EXT;
    attr[attrIdx++] = 0;

    attr[attrIdx++] = EGL_DMA_BUF_PLANE0_FD_EXT;
    attr[attrIdx++] = dmaBufFd;

    attr[attrIdx++] = EGL_DMA_BUF_PLANE1_FD_EXT;
    attr[attrIdx++] = dmaBufFd;

    attr[attrIdx++] = EGL_NONE;

    eglCreateImageKHR =
        (PFNEGLCREATEIMAGEKHRPROC)eglGetProcAddress("eglCreateImageKHR");
    glEGLImageTargetTexture2DOES =
        (PFNGLEGLIMAGETARGETTEXTURE2DOESPROC)eglGetProcAddress("glEGLImageTargetTexture2DOES");

    pObj->texImg[texIndex] = eglCreateImageKHR(
                                pObj->display,
                                EGL_NO_CONTEXT,
                                EGL_LINUX_DMA_BUF_EXT,
                                NULL,
                                attr
                              );

    System_eglCheckEglError("eglCreateImageKHR", EGL_TRUE);
    if (pObj->texImg[texIndex] == EGL_NO_IMAGE_KHR) {
        Vps_printf(" EGL: ERROR: eglCreateImageKHR failed !!!\n");
        return -1;
    }

    glGenTextures(1, &pObj->texYuv[texIndex]);
    System_eglCheckGlError("glGenTextures");

    glBindTexture(GL_TEXTURE_EXTERNAL_OES, pObj->texYuv[texIndex]);
    System_eglCheckGlError("glBindTexture");

    glTexParameteri(GL_TEXTURE_EXTERNAL_OES, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_EXTERNAL_OES, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    System_eglCheckGlError("glTexParameteri");

    glEGLImageTargetTexture2DOES(GL_TEXTURE_EXTERNAL_OES, (GLeglImageOES)pObj->texImg[texIndex]);
    System_eglCheckGlError("glEGLImageTargetTexture2DOES");

    pObj->dmaBufFd[texIndex] = dmaBufFd;
    return 0;
}
#endif

#ifdef QNX_BUILD
static GLuint System_eglSetupYuvTexSurface(System_EglObj *pObj, System_EglTexProperty *pProp, void *bufAddr, int texIndex)
#else
static GLuint System_eglSetupYuvTexSurface(System_EglObj *pObj, System_EglTexProperty *pProp, int dmaBufFd, int texIndex)
#endif
{
#ifdef QNX_BUILD
    EGLCompatBuffer eglCBuf;
#else
    EGLint attr[32];
    int attrIdx;
#endif
    PFNEGLCREATEIMAGEKHRPROC eglCreateImageKHR;
    PFNGLEGLIMAGETARGETTEXTURE2DOESPROC glEGLImageTargetTexture2DOES;

#ifndef QNX_BUILD
    attrIdx = 0;

    attr[attrIdx++] = EGL_LINUX_DRM_FOURCC_EXT;
    attr[attrIdx++] = FOURCC_STR("NV12");

    attr[attrIdx++] = EGL_WIDTH;
    attr[attrIdx++] = pProp->width;

    attr[attrIdx++] = EGL_HEIGHT;
    attr[attrIdx++] = pProp->height;

    attr[attrIdx++] = EGL_DMA_BUF_PLANE0_PITCH_EXT;
    attr[attrIdx++] = pProp->pitch[0];

    attr[attrIdx++] = EGL_DMA_BUF_PLANE1_PITCH_EXT;
    attr[attrIdx++] = pProp->pitch[0];

    attr[attrIdx++] = EGL_DMA_BUF_PLANE0_OFFSET_EXT;
    attr[attrIdx++] = 0;

    attr[attrIdx++] = EGL_DMA_BUF_PLANE1_OFFSET_EXT;
    attr[attrIdx++] = 0;

    attr[attrIdx++] = EGL_DMA_BUF_PLANE0_FD_EXT;
    attr[attrIdx++] = dmaBufFd;

    attr[attrIdx++] = EGL_DMA_BUF_PLANE1_FD_EXT;
    attr[attrIdx++] = dmaBufFd;

    attr[attrIdx++] = EGL_NONE;
#endif

    eglCreateImageKHR =
        (PFNEGLCREATEIMAGEKHRPROC)eglGetProcAddress("eglCreateImageKHR");
    glEGLImageTargetTexture2DOES =
        (PFNGLEGLIMAGETARGETTEXTURE2DOESPROC)eglGetProcAddress("glEGLImageTargetTexture2DOES");

#ifdef QNX_BUILD
    eglCBuf = pObj->eglInfo.get_egl_attach_buffer(pProp->width, pProp->height, SYSTEM_DF_YUV420SP_UV, bufAddr);
    pObj->eglPixmap[texIndex] = eglCBuf.eglPixmap;

    pObj->texImg[texIndex] = eglCreateImageKHR(
                            pObj->display,
                            EGL_NO_CONTEXT,
                            EGL_NATIVE_PIXMAP_KHR,
                            (EGLNativePixmapType)(pObj->eglPixmap[texIndex]),
                            NULL
                          );
#else
    pObj->texImg[texIndex] = eglCreateImageKHR(
                                pObj->display,
                                EGL_NO_CONTEXT,
                                EGL_LINUX_DMA_BUF_EXT,
                                NULL,
                                attr
                              );
#endif

    System_eglCheckEglError("eglCreateImageKHR", EGL_TRUE);
    if (pObj->texImg[texIndex] == EGL_NO_IMAGE_KHR) {
        Vps_printf(" EGL: ERROR: eglCreateImageKHR failed !!!\n");
        return -1;
    }

    glGenTextures(1, &pObj->texYuv[texIndex]);
    System_eglCheckGlError("eglCreateImageKHR");

    glBindTexture(GL_TEXTURE_EXTERNAL_OES, pObj->texYuv[texIndex]);
    System_eglCheckGlError("glBindTexture");

    glTexParameteri(GL_TEXTURE_EXTERNAL_OES, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_EXTERNAL_OES, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    System_eglCheckGlError("glTexParameteri");

    glEGLImageTargetTexture2DOES(GL_TEXTURE_EXTERNAL_OES, (GLeglImageOES)pObj->texImg[texIndex]);
    System_eglCheckGlError("glEGLImageTargetTexture2DOES");

#ifdef QNX_BUILD
    pObj->bufAddr[texIndex] = bufAddr;
#else
    pObj->dmaBufFd[texIndex] = dmaBufFd;
#endif
    return 0;
}

#ifndef QNX_BUILD
GLuint System_eglGetTexYuv(System_EglObj *pEglObj, System_EglTexProperty *pProp, int dmaBufFd)
{
    GLuint texYuv = 0;
    int texFound = 0, i, status;

    for(i=0; i<pEglObj->numBuf; i++)
    {
        if(pEglObj->dmaBufFd[i]==dmaBufFd)
        {
            texYuv = pEglObj->texYuv[i];
            texFound = 1;
            break;
        }
    }
    if(texFound==0)
    {
        OSA_assert(i<SYSTEM_EGL_MAX_TEXTURES);

        status = System_eglSetupYuvTexSurface(
                        pEglObj,
                        pProp,
                        dmaBufFd,
                        i
                        );
        if(status!=0)
        {
            Vps_printf(" EGL: ERROR: Unable to bind texture[%d] to dmabuf fd [%d] !!!\n", i, dmaBufFd);
        }
        OSA_assert(status==0);

        texYuv = pEglObj->texYuv[i];

        pEglObj->numBuf++;
    }

    return texYuv;
}
GLuint System_eglWindowGetTexYuv(System_EglWindowObj *pEglWindowObj, System_EglTexProperty *pProp, int dmaBufFd)
{
    GLuint texYuv = 0;
    int texFound = 0, i, status;

    for(i=0; i<pEglWindowObj->numBuf; i++)
    {
        if(pEglWindowObj->dmaBufFd[i]==dmaBufFd)
        {
            texYuv = pEglWindowObj->texYuv[i];
            texFound = 1;
            break;
        }
    }
    if(texFound==0)
    {
        OSA_assert(i<SYSTEM_EGL_MAX_TEXTURES);

        status = System_eglWindowSetupYuvTexSurface(
                        pEglWindowObj,
                        pProp,
                        dmaBufFd,
                        i
                        );
        if(status!=0)
        {
            Vps_printf(" EGL: ERROR: Unable to bind texture[%d] to dmabuf fd [%d] !!!\n", i, dmaBufFd);
        }
        OSA_assert(status==0);

        texYuv = pEglWindowObj->texYuv[i];

        pEglWindowObj->numBuf++;
    }

    return texYuv;
}
#else
GLuint System_eglGetTexYuv(System_EglObj *pEglObj, System_EglTexProperty *pProp, void *bufAddr)
{
    GLuint texYuv = 0;
    int texFound = 0, i, status;

    for(i=0; i<pEglObj->numBuf; i++)
    {
        if(pEglObj->bufAddr[i]==bufAddr)
        {
            texYuv = pEglObj->texYuv[i];
            texFound = 1;
            break;
        }
    }
    if(texFound==0)
    {
        OSA_assert(i<SYSTEM_EGL_MAX_TEXTURES);

        status = System_eglSetupYuvTexSurface(
                        pEglObj,
                        pProp,
                        bufAddr,
                        i
                        );
        if(status!=0)
        {
            Vps_printf(" EGL: ERROR: Unable to bind texture[%d] to address [0x%08x] !!!\n", i, (unsigned int)bufAddr);
        }
        OSA_assert(status==0);

        texYuv = pEglObj->texYuv[i];

        pEglObj->numBuf++;
    }

    return texYuv;
}
#endif
int System_eglMakeCurrentNill(System_EglObj *pEglObj)
{
#ifdef QNX_BUILD
    int ret = eglMakeCurrent(pEglObj->display, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);
#else
    int ret = eglMakeCurrent(pEglObj->display, EGL_NO_SURFACE, EGL_NO_SURFACE, pEglObj->context);
#endif
    System_eglCheckEglError("eglMakeCurrent", ret);
    if (ret != EGL_TRUE) {
       Vps_printf(" EGL: eglMakeCurrent() failed !!!\n");
       return -1;
    }

    return 0;
}

int System_eglMakeCurrentBuffer(System_EglObj *pEglObj, EGLSurface surface)
{
    int ret = eglMakeCurrent(pEglObj->display, surface, surface, pEglObj->context);
    System_eglCheckEglError("eglMakeCurrent", ret);
    if (ret != EGL_TRUE) {
       Vps_printf(" EGL: eglMakeCurrent() failed !!!\n");
       return -1;
    }
#ifndef QNX_BUILD
    glViewport(0, 0, pEglObj->width, pEglObj->height);
#endif
    return 0;
}

int System_eglClose(System_EglObj *pEglObj)
{
    int count;
    System_Buffer *nextBuf;
    System_EglPixmapVideoFrameBuffer *eglBuf;
    EGLCompatBuffer eglCBuf;
#ifdef QNX_BUILD
    PFNEGLDESTROYIMAGEKHRPROC eglDestroyImageKHR;
    eglDestroyImageKHR = (PFNEGLDESTROYIMAGEKHRPROC)eglGetProcAddress("eglDestroyImageKHR");

    for(count = 0; count < pEglObj->numBuf; count++)
    {
        if(pEglObj->eglPixmap[count] != NULL)
        {
            eglCBuf.eglPixmap = pEglObj->eglPixmap[count];
            pEglObj->eglInfo.destroy_egl_native_buffer(eglCBuf);
            pEglObj->eglPixmap[count] = 0;
        }
        if(pEglObj->texYuv[count] != NULL)
        {
            glDeleteTextures(1, &pEglObj->texYuv[count]);
            pEglObj->texYuv[count] = 0;
        }
        if(pEglObj->texImg[count] != NULL)
        {
            eglDestroyImageKHR(pEglObj->display, pEglObj->texImg[count]);
            pEglObj->texImg[count] = 0;
        }
    }
#endif

    eglMakeCurrent(pEglObj->display,EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);
    for (count = 0; count < SYSTEM_MAXNUM_EGL_BUFFERS; count++)
    {
        nextBuf = pEglObj->eglBuffers[count];
        eglBuf = nextBuf->payload;
        eglDestroySurface(pEglObj->display, (EGLSurface)eglBuf->eglSurface);
        eglCBuf.eglPixmap = eglBuf->eglPixmap;
        eglCBuf.pixmapNative = eglBuf->pixmapNative;
        pEglObj->eglInfo.destroy_egl_native_buffer(eglCBuf);
        OSA_memFree(eglBuf);
        OSA_memFree(nextBuf);
    }

    eglDestroyContext(pEglObj->display, pEglObj->context);
#ifdef BUILD_INFOADAS
    eglTerminate(pEglObj->display);
#endif
    OSA_queDelete(&(pEglObj->eglEmptyBufQue));
    OSA_queDelete(&(pEglObj->eglFullBufQue));

    return 0;

}

int System_eglWindowClose(System_EglWindowObj *pEglWindowObj)
{
    int count;
    System_Buffer *nextBuf;
    System_EglPixmapVideoFrameBuffer *eglBuf;
    EGLCompatBuffer eglCBuf;

    PFNEGLDESTROYIMAGEKHRPROC eglDestroyImageKHR;
    eglDestroyImageKHR = (PFNEGLDESTROYIMAGEKHRPROC)eglGetProcAddress("eglDestroyImageKHR");

    for(count = 0; count < pEglWindowObj->numBuf; count++)
    {
        if(pEglWindowObj->texYuv[count] != 0)
        {
            glDeleteTextures(1, &pEglWindowObj->texYuv[count]);
            pEglWindowObj->texYuv[count] = 0;
        }
        if(pEglWindowObj->texImg[count] != NULL)
        {
            eglDestroyImageKHR(pEglWindowObj->display, pEglWindowObj->texImg[count]);
            pEglWindowObj->texImg[count] = 0;
        }
    }
    eglMakeCurrent(pEglWindowObj->display,EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);

    eglDestroySurface(pEglWindowObj->display, pEglWindowObj->surface);
    pEglWindowObj->eglInfo.unwrap_native_buffers(pEglWindowObj->windowNative);

    for (count = 0; count < SYSTEM_MAXNUM_EGL_BUFFERS; count++)
    {
        nextBuf = pEglWindowObj->eglBuffers[count];
        eglBuf = nextBuf->payload;
        eglCBuf.eglPixmap = eglBuf->eglPixmap;
        eglCBuf.pixmapNative = eglBuf->pixmapNative;
        pEglWindowObj->eglInfo.destroy_egl_native_buffer(eglCBuf);
        OSA_memFree(eglBuf);
        OSA_memFree(nextBuf);
    }

    eglDestroyContext(pEglWindowObj->display, pEglWindowObj->context);
    eglTerminate(pEglWindowObj->display);

    return 0;

}
