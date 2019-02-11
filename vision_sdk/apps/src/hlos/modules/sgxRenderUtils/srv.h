/*
 *******************************************************************************
 *
 * Copyright (C) 2016 Texas Instruments Incorporated - http://www.ti.com/
 * ALL RIGHTS RESERVED
 *
 *******************************************************************************
 */

#ifndef _SRV_H_
#define _SRV_H_

#ifdef __cplusplus
extern "C" {
#endif

// srv types and defines
#define POINTS_WIDTH (1080)
#define POINTS_HEIGHT (1080)
#define POINTS_SUBX 4
#define POINTS_SUBY 4

#define QUADRANTS 4
#define QUADRANT_WIDTH (POINTS_WIDTH/(POINTS_SUBX * 2)+1)
#define QUADRANT_HEIGHT (POINTS_HEIGHT/(POINTS_SUBY * 2)+1)
#define QUADRANT_SIZE (QUADRANT_WIDTH * QUADRANT_HEIGHT)

typedef unsigned char BLENDLUT_DATATYPE;
#define GL_BLENDLUT_DATATYPE GL_UNSIGNED_BYTE

#define GL_VERTEX_ENUM     GL_SHORT
#define GL_VERTEX_DATATYPE GLshort

#define GL_BLEND_ENUM     GL_UNSIGNED_BYTE
#define GL_BLEND_DATATYPE unsigned char
//GLubyte

#define USE_SHORT_TEXCOORDS // Enable if using short coordinates
#ifdef USE_SHORT_TEXCOORDS
#define GL_TEXCOORD_ENUM GL_SHORT
#define GL_TEXCOORD_DATATYPE GLshort
#else
#define GL_TEXCOORD_ENUM GL_FLOAT
#define GL_TEXCOORD_DATATYPE GLfloat
#endif

typedef struct _srv_lut_t
{
	GL_VERTEX_DATATYPE x, y, z;
	GL_TEXCOORD_DATATYPE u1, v1, u2, v2;
#ifdef SRV_INTERLEAVED_BLEND
	GL_BLEND_DATATYPE blend1, blend2;
#endif
} srv_lut_t;

typedef struct _srv_blend_lut_t
{
	GL_BLEND_DATATYPE blend1, blend2;
} srv_blend_lut_t;

//srv functions
int srv_setup(render_state_t *pObj);
void srv_draw(render_state_t *pObj, GLuint *texYuv, int viewport_id);
int srv_generate_lut(uint32_t width, uint32_t height,
		uint32_t camw, uint32_t camh,
		uint32_t subx, uint32_t suby, srv_lut_t *lut);
int srv_generate_blend_lut(uint32_t width, uint32_t height,
		uint32_t subx, uint32_t suby, srv_blend_lut_t *lut);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /*   _SRV_H_    */
