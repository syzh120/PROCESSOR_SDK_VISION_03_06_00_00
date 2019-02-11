/*
 *******************************************************************************
 *
 * Copyright (C) 2013 Texas Instruments Incorporated - http://www.ti.com/
 * ALL RIGHTS RESERVED
 *
 *******************************************************************************
 */

#ifndef _SGXRENDER3Dsfm_H_
#define _SGXRENDER3Dsfm_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <links_fw/src/hlos/system/system_gl_egl_utils.h>

static inline void dummy_printf(const char* in, ...){};
#define D_PRINTF dummy_printf
#define GL_CHECK(x)

typedef struct
{
   /*algorithm data pointers*/
   void * egoposePtr; /*pointing to current ego (vehicle) pose data*/
   void * camposesPtr; /*pointing to current camera poses data*/
   void * boxesPtr; /*pointing to current boxes data*/
   
   /*render utilities*/
   System_EglTexProperty texProp;
   int screen_width;
   int screen_height;
   int inFramesWidth; /*width of input frames*/
   int inFramesHeight; /*height of input frames*/
   float carScale; /*scale of the car model*/

} SgxRender3Dsfm_Obj;

/* public interface for link*/
int SgxRender3Dsfm_setup(SgxRender3Dsfm_Obj *pObj);
void SgxRender3Dsfm_renderFrame(SgxRender3Dsfm_Obj *pObj, GLuint *texYuv);


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /*   _SGXRENDER3Dsfm_H_    */
