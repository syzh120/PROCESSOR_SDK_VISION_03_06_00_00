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
 * \file system_gbm_allocator.c
 *
 * \brief   System level allocator for GBM buffers
 *          These buffers are shared between IPU, GPU, and A15.
 *
 *******************************************************************************
 */
#ifndef ANDROID
#ifndef QNX_BUILD
#include <stdlib.h>
#include <drm.h>

#include <omap_drmif.h>

#include <xf86drm.h>
#include <gbm.h>

#include "dmabuf-ioctl.h"
#include <sys/ioctl.h>

#include <links_fw/src/hlos/osa/include/osa_mem.h>


#include "system_gl_egl_utils.h"
#include "system_gbm_allocator.h"

int fd = -1;
struct gbm_device *dev = NULL;
struct omap_device *odev = NULL;

EGLNativeDisplayType gbm_allocator_get_native_display ()
{
   if(fd == -1) {
       fd = drmOpen("omapdrm", NULL);
   }
   if(fd > 0 && dev == NULL) {
       dev = gbm_create_device(fd);
       odev = omap_device_new(fd);
   }

   return (EGLNativeDisplayType)dev;
}

EGLCompatBuffer gbm_allocator_get_native_buffer (uint32_t width, uint32_t height)
{
   EGLCompatBuffer eglCBuf;
   Void *buffer;
   UInt32 stride = 0;
   Int32 dbuf_fd = -1;
   struct dmabuf_vmem_export exp;

    dbuf_fd = open("/dev/vmemexp", O_RDWR | O_CLOEXEC);
   if (dbuf_fd < 0) {
        Vps_printf("Error opening virt mem dmabuf exporter");
   }

   stride = width * 4;
   buffer = OSA_memAllocSR(OSA_HEAPID_DDR_CACHED_SR1, stride * height,
                            SYSTEM_BUFFER_ALIGNMENT);

    exp.vaddr = (unsigned long) buffer;
    exp.size = (width * 4 * height);

    /* Export as DMAbuf handle */
    ioctl(dbuf_fd, DBUFIOC_EXPORT_VIRTMEM, &exp);

   struct gbm_import_fd_data ifdd = {
       .width = width,
       .height = height,
       .stride = stride,
       .format = GBM_FORMAT_XRGB8888,
       .fd = exp.fd
   };
   struct gbm_bo *bo = gbm_bo_import(dev,
   GBM_BO_IMPORT_FD,
   &ifdd,
   GBM_BO_USE_SCANOUT | GBM_BO_USE_RENDERING);

   eglCBuf.width = gbm_bo_get_width(bo);
   eglCBuf.height = gbm_bo_get_height(bo);
   eglCBuf.stride = gbm_bo_get_stride(bo);
   eglCBuf.eglPixmap = (EGLNativePixmapType) bo;
   eglCBuf.pixmapNative = (void *)buffer;

   close(exp.fd);
   close(dbuf_fd);

   return eglCBuf;
}

void gbm_allocator_destroy_native_buffer (EGLCompatBuffer buffer)
{
   uint32_t stride, height;
   struct gbm_bo *bo = (struct gbm_bo *)buffer.eglPixmap;

   height = gbm_bo_get_height(bo);
   stride = gbm_bo_get_stride(bo);

   gbm_bo_destroy(bo);
   OSA_memFreeSR(OSA_HEAPID_DDR_CACHED_SR1, buffer.pixmapNative, stride * height);
}

EGLNativeWindowType gbm_wrap_native_buffers (
                EGLCompatBuffer *buffers, uint32_t count)
{
	int i;
	struct gbm_bo **arr = calloc(count, sizeof(struct gbm_bo *));
	struct gbm_surface *surf;

	OSA_assert(arr != NULL);

	for(i = 0; i < count; i++)
		arr[i] = (struct gbm_bo *)(buffers[i].eglPixmap);

	surf = gbm_surface_import(dev,
			buffers[0].width, buffers[0].height,
			GBM_FORMAT_XRGB8888,
			GBM_BO_USE_SCANOUT | GBM_BO_USE_RENDERING,
			arr, count);
	OSA_assert(surf != NULL);

	free(arr);

	return (EGLNativeWindowType)surf;
}

EGLNativePixmapType gbm_wrapper_get_next_buffer (
                EGLNativeWindowType window)
{
	return (EGLNativePixmapType)(gbm_surface_lock_front_buffer((struct gbm_surface *)window));
}

void gbm_wrapper_put_buffer (
                EGLNativeWindowType window,
		EGLNativePixmapType buffer)
{
	gbm_surface_release_buffer((struct gbm_surface *)window, (struct gbm_bo *)buffer);
}

void gbm_unwrap_native_buffers (
                EGLNativeWindowType window)
{
	gbm_surface_destroy((struct gbm_surface *)window);
}
#else //QNX
#include <stdlib.h>
#include <drm.h>

#include <omap_drmif.h>

#include <xf86drm.h>
#include <gbm.h>

#include <links_fw/src/hlos/osa/include/osa_mem.h>


#include "system_gl_egl_utils.h"
#include "system_gbm_allocator.h"

int fd = -1;
struct gbm_device *dev = NULL;
struct omap_device *odev = NULL;

EGLNativeDisplayType gbm_allocator_get_native_display ()
{
   if(fd == -1) {
       fd = drmOpen("omapdrm", NULL);
   }
   if(fd > 0 && dev == NULL) {
       dev = gbm_create_device(fd);
       odev = omap_device_new(fd);
   }

   return (EGLNativeDisplayType)dev;
} 

EGLCompatBuffer gbm_allocator_get_native_buffer (uint32_t width, uint32_t height)
{
   EGLCompatBuffer eglCBuf;
   Void *buffer, *pbuffer;
   uint32_t stride;
   uint32_t gemname;
   struct omap_bo *obo;


   gbm_device_precalculate_stride(dev, width, GBM_FORMAT_XRGB8888, &stride);
   buffer = OSA_memAllocSR(OSA_HEAPID_DDR_CACHED_SR1, stride * height, 32);	
   pbuffer = (Void *)OSA_memVirt2Phys((unsigned int)buffer, OSA_MEM_REGION_TYPE_SR1);
   obo = omap_bo_new_paddr(odev, stride * height, (uint32_t)pbuffer, OMAP_BO_WC);
   omap_bo_get_name(obo, &gemname);

   struct alloc_bufname_import data = {
       .width = width,
       .height = height,
       .stride = stride,
       .format = GBM_FORMAT_XRGB8888,
       .buffer_name = gemname,
   };


   struct gbm_bo *bo = gbm_bo_import(dev,
   GBM_BO_IMPORT_ALLOC_HANDLE,
   &data,
   GBM_BO_USE_SCANOUT | GBM_BO_USE_RENDERING);

   omap_bo_del(obo);

   eglCBuf.width = gbm_bo_get_width(bo);
   eglCBuf.height = gbm_bo_get_height(bo);
   eglCBuf.stride = gbm_bo_get_stride(bo);
   eglCBuf.eglPixmap = (EGLNativePixmapType) bo;
   eglCBuf.pixmapNative = (void *)buffer;

   return eglCBuf;
}

void gbm_allocator_destroy_native_buffer (EGLCompatBuffer buffer)
{
   uint32_t stride, height;
   struct gbm_bo *bo = (struct gbm_bo *)buffer.eglPixmap;

   height = gbm_bo_get_height(bo);
   stride = gbm_bo_get_stride(bo);

   gbm_bo_destroy(bo);
   OSA_memFreeSR(OSA_HEAPID_DDR_CACHED_SR1, buffer.pixmapNative, stride * height);
}
#endif
#endif //ANDROID
