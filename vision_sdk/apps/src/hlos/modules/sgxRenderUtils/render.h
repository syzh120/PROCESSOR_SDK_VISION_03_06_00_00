/*
 *******************************************************************************
 *
 * Copyright (C) 2013 Texas Instruments Incorporated - http://www.ti.com/
 * ALL RIGHTS RESERVED
 *
 *******************************************************************************
 */

#ifndef _RENDER_H_
#define _RENDER_H_

#ifdef __cplusplus
//GLM includes
#define GLM_FORCE_RADIANS
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
extern "C" {
#endif

#ifndef STANDALONE
#include <links_fw/src/hlos/system/system_gl_egl_utils.h>
#else
#ifdef _WIN32
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#else
#include <EGL/egl.h>
#include <GLES2/gl2.h>
void System_eglCheckEglError(const char* op, EGLBoolean returnVal);
void System_eglCheckGlError(const char* op);

#endif
#include <stdlib.h>
#include <stdio.h>

#endif

#include "renderutils.h"

#define ENABLE_VBO_DRAW
#define ENABLE_CPP

#if 0
#define D_PRINTF  printf
#define GL_CHECK(x) \
{ \
int err = glGetError(); \
printf("GL Error = %x for %s\n", err, (char*)(#x)); \
}
#else
static inline void dummy_printf(const char* in, ...){};
#define D_PRINTF dummy_printf
#define GL_CHECK(x)
#endif


typedef struct _gl_state
{
    int program;
    GLuint textureID[4];
    GLuint attribIndices[2];
    GLint mvMatrixOffsetLoc;
    GLint samplerLoc;
    GLuint vboID[4];
    float carMouse[5];    
    float delta[5];
    float carMouseMax[5];    
    float carMouseMin[5];        
}gl_state;

typedef struct
{
	int x;
	int y;
} point2d;

typedef struct
{
	GLfloat x;
	GLfloat y;
	GLfloat z;
} vertex3df;

typedef struct
{
	point2d l;
	point2d r;
	point2d t;
	point2d b;
} intercepts;

#ifdef TEXTURE_FROM_LOCAL
#define TEXTURE_WIDTH 1
#define TEXTURE_HEIGHT 1
#else
#define TEXTURE_WIDTH 1280
#define TEXTURE_HEIGHT 720
#endif

#define MAX_IMAGES      (4)

#ifndef STANDALONE
#ifndef EGL_TI_raw_video
#  define EGL_TI_raw_video 1
#  define EGL_RAW_VIDEO_TI                                      0x333A  /* eglCreateImageKHR target */
#  define EGL_GL_VIDEO_FOURCC_TI                                0x3331  /* eglCreateImageKHR attribute */
#  define EGL_GL_VIDEO_WIDTH_TI                                 0x3332  /* eglCreateImageKHR attribute */
#  define EGL_GL_VIDEO_HEIGHT_TI                                0x3333  /* eglCreateImageKHR attribute */
#  define EGL_GL_VIDEO_BYTE_STRIDE_TI                           0x3334  /* eglCreateImageKHR attribute */
#  define EGL_GL_VIDEO_BYTE_SIZE_TI                             0x3335  /* eglCreateImageKHR attribute */
#  define EGL_GL_VIDEO_YUV_FLAGS_TI                             0x3336  /* eglCreateImageKHR attribute */
#endif

#ifndef EGLIMAGE_FLAGS_YUV_CONFORMANT_RANGE
#  define EGLIMAGE_FLAGS_YUV_CONFORMANT_RANGE (0 << 0)
#  define EGLIMAGE_FLAGS_YUV_FULL_RANGE       (1 << 0)
#  define EGLIMAGE_FLAGS_YUV_BT601            (0 << 1)
#  define EGLIMAGE_FLAGS_YUV_BT709            (1 << 1)
#endif

#define FOURCC(a, b, c, d) ((uint32_t)(uint8_t)(a) | ((uint32_t)(uint8_t)(b) << 8) | ((uint32_t)(uint8_t)(c) << 16) | ((uint32_t)(uint8_t)(d) << 24 ))
#define FOURCC_STR(str)    FOURCC(str[0], str[1], str[2], str[3])

struct EglimgTexMap {
        Bool mapped;
        GLuint tex;
        EGLImageKHR eglimg;
        char *imgbuf;
};
struct GLConfig {
        EGLDisplay display;
        EGLConfig config;
        EGLContext context;
        EGLSurface surface;
};
//struct GLConfig gl;
//struct EglimgTexMap eglMapArray[MAX_IMAGES];
#else
#define SYSTEM_EGL_MAX_TEXTURES 4
typedef struct
{
    GLuint      texYuv[SYSTEM_EGL_MAX_TEXTURES];
//    EGLImageKHR texImg[SYSTEM_EGL_MAX_TEXTURES];
    void        *bufAddr[SYSTEM_EGL_MAX_TEXTURES];
    int numBuf;

    int width;
    int height;

} System_EglObj;
#endif



typedef struct
{
   gl_state car_gl1;

   void * LUT3D;
   void * blendLUT3D;
   void * PALUT3D;
   void * BoxLUT;
   void * BoxPose3D;
   
#ifndef STANDALONE
   System_EglTexProperty texProp;
#endif
   int screen_width;
   int screen_height;

   uint32_t cam_width;
   uint32_t cam_height;
   uint32_t cam_bpp;

   EGLBoolean enableContinousTransitions;

} render_state_t;

#include "srv.h"

int render_teardown(render_state_t *pObj);
int render_setup(render_state_t *pObj);
void render_renderFrame(render_state_t *pObj, System_EglWindowObj *pEglObj, GLuint *texYuv);

/* used by rendering internally.
 * NOT to be used by sgxDisplayLink directly
 */

void  render_updateView();
GLuint render_createProgram(const char* pVertexSource, const char* pFragmentSource); 
void render_renderFrame3DSRV(render_state_t *pObj, System_EglObj *pEglObj, GLuint *texYuv);
void render3dFrame(render_state_t *pObj, System_EglObj *pEglObj, GLuint *texYuv);

void render_ndcToScreen(int *xscr, int *yscr, float xndc, float yndc);
void render_worldToNdc(float *xndc, float *yndc, GLint x, GLint y, GLint z);
void render_worldToScreen(int *xscr, int *yscr, GLint x, GLint y, GLint z);
void render_lineIntercepts(intercepts *intcepts,
		int x1, int y1, int x2, int y2,
		int xleft, int xright, int ytop, int ybottom);
void render_getIntercepts(intercepts *worldx, intercepts *worldy,
		int xleft, int xright, int ytop, int ybottom);

void screen1_draw_vbo(int texYuv);
void screen1_init_vbo();
void render_process_keys(char input);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /*   _RENDER_H_    */
