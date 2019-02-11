/*
 *******************************************************************************
 *
 * Copyright (C) 2013 Texas Instruments Incorporated - http://www.ti.com/
 * ALL RIGHTS RESERVED
 *
 *******************************************************************************
 */

#include "render.h"
#include <math.h>


GLuint vertexPositionAttribLoc; //3 panes+1 car
GLuint vertexTexCoord1AttribLoc; //4 panes+1 car
GLuint vertexTexCoord2AttribLoc; //4 panes+1 car
GLuint vertexIndexImage1AttribLoc; //4 panes+1 car
GLuint vertexIndexImage2AttribLoc; //4 panes+1 car
GLuint blendAttribLoc; //blend of LUT
GLuint uiProgramObject;

GLint samplerLocation0;
GLint samplerLocation1;
GLint samplerLocation2;
GLint samplerLocation3;
GLint projMatrixLocation;
GLint mvMatrixLocation;
GLint uniform_select;
#ifndef STATIC_COORDINATES
GLint uniform_rangex;
GLint uniform_rangey;
GLint uniform_texturex;
GLint uniform_texturey;
#endif

int shader_output_select = 0;
GLenum render_mode = GL_TRIANGLE_STRIP;

extern bool srv_render_to_file;

extern glm::mat4 mMVP_bowl[];


//Mesh splitting logic
#define MAX_VBO_MESH_SPLIT 8
static GLuint vboId[MAX_VBO_MESH_SPLIT*3];

static void * prevLUT=(void *)0xdead;

#define MAX_INDEX_BUFFERS 2

typedef struct {
	unsigned int *buffer;
	unsigned int length;
} t_index_buffer;

t_index_buffer index_buffers[MAX_INDEX_BUFFERS];
unsigned int active_index_buffer = 1;
bool index_buffer_changed = 0;

//Shaders for surround view
static const char srv_vert_shader_lut[] =
" attribute vec3 aVertexPosition;\n "
" attribute vec2 aTextureCoord1;\n "
" attribute vec2 aTextureCoord2;\n "
" attribute vec2 blendVals;\n "
" uniform mat4 uMVMatrix;\n "
" varying vec2 outNormTexture;\n "
" varying vec2 outNormTexture1;\n "
" varying vec2 outBlendVals;\n "
" varying float outFloatChannelX;\n "
" varying float outFloatChannelY;\n "
" varying float outFloatChannelZ;\n "
#ifdef STATIC_COORDINATES
" float uRangeX = 440.0; \n "
" float uRangeY = 540.0; \n "
" float uTextureX = 20480.0; \n "
" float uTextureY = 11520.0;\n "
#else
" uniform float uRangeX; \n "
" uniform float uRangeY; \n "
" uniform float uTextureX; \n "
" uniform float uTextureY;\n "
#endif
" void main(void) {\n "
"     gl_Position = uMVMatrix * vec4(aVertexPosition.x, aVertexPosition.y, aVertexPosition.z, 1.0);\n "
"     outFloatChannelX = aVertexPosition.x/(uRangeX * 2.0);\n"
"     outFloatChannelY = aVertexPosition.y/(uRangeY * 2.0);\n"
"     outFloatChannelZ = aVertexPosition.z/450.0f;\n"
"     outNormTexture.x = aTextureCoord1.t/uTextureX;\n"
"     outNormTexture.y = aTextureCoord1.s/uTextureY;\n"
"     outNormTexture1.x = aTextureCoord2.t/uTextureX;\n"
"     outNormTexture1.y = aTextureCoord2.s/uTextureY;\n"
"     outBlendVals = blendVals;\n"
" }\n"
;

static const char srv_frag_shader_lut[] =
#ifndef STANDALONE
" #extension GL_OES_EGL_image_external : require \n"
" precision mediump float;\n "
#endif
#ifndef STANDALONE
" uniform samplerExternalOES uSampler[2];\n "
#else
" uniform sampler2D uSampler[2];\n "
#endif

" uniform int select;\n "
" varying vec2 outNormTexture;\n "
" varying vec2 outNormTexture1;\n "
" varying vec2 outBlendVals;\n "
" varying float outFloatChannelX;\n "
" varying float outFloatChannelY;\n "
" varying float outFloatChannelZ;\n "
" vec4 iFragColor1; \n "
" vec4 iFragColor2; \n "
" vec4 outColor; \n "
" vec4 packFloatToVec4i(const float value)\n"
" {\n"
"	  const vec4 bitSh = vec4(256.0*256.0*256.0, 256.0*256.0, 256.0, 1.0);\n"
"     const vec4 bitMsk = vec4(0.0, 1.0/256.0, 1.0/256.0, 1.0/256.0);\n"
"     vec4 res = fract(value * bitSh);\n"
"     res -= res.xxyz * bitMsk;\n"
"     return res;\n"
" }\n"
" float unpackFloatFromVec4i(const vec4 value)\n"
" {\n"
"     const vec4 bitSh = vec4(1.0/(256.0*256.0*256.0), 1.0/(256.0*256.0), 1.0/256.0, 1.0);\n"
"     return(dot(value, bitSh));\n"
" }\n"
" void main(){\n"
"     iFragColor1  = texture2D(uSampler[0], outNormTexture);\n "
"     iFragColor2  = texture2D(uSampler[1], outNormTexture1);\n "
"     if (select == 0) \n"
"     { \n"
"     	   outColor = packFloatToVec4i(outFloatChannelX);\n "
"     } \n"
"     else if (select == 1) \n"
"     { \n"
"     	   outColor = packFloatToVec4i(outFloatChannelY);\n "
"     } \n"
"     else if (select == 2) \n"
"     { \n"
"     	   outColor = packFloatToVec4i(outFloatChannelZ);\n "
"     } \n"
"     else \n"
"     { \n"
"     	   outColor = iFragColor1;\n "
"     	   outColor = (outBlendVals.x)*iFragColor1 + (outBlendVals.y)*iFragColor2;\n "
"     } \n"
"     gl_FragColor.rgba = outColor.abgr;\n "
" }\n"
;

static const char srv_vert_shader[] =
" attribute vec3 aVertexPosition;\n "
" attribute vec2 aTextureCoord1;\n "
" attribute vec2 aTextureCoord2;\n "
" attribute vec2 blendVals;\n "
" uniform mat4 uMVMatrix;\n "
" varying vec2 outNormTexture;\n "
" varying vec2 outNormTexture1;\n "
" varying vec2 outBlendVals;\n "
#ifdef STATIC_COORDINATES
" float uRangeX = 440.0; \n "
" float uRangeY = 540.0; \n "
" float uTextureX = 20480.0; \n "
" float uTextureY = 11520.0;\n "
#else
" uniform float uRangeX; \n "
" uniform float uRangeY; \n "
" uniform float uTextureX; \n "
" uniform float uTextureY;\n "
#endif

" void main(void) {\n "
"     gl_Position = uMVMatrix * vec4(aVertexPosition.x, aVertexPosition.y, aVertexPosition.z, 1.0);\n "
"     outNormTexture.x = aTextureCoord1.t/uTextureX;\n"
"     outNormTexture.y = aTextureCoord1.s/uTextureY;\n"
"     outNormTexture1.x = aTextureCoord2.t/uTextureX;\n"
"     outNormTexture1.y = aTextureCoord2.s/uTextureY;\n"
"     outBlendVals = blendVals;\n"
" }\n"
;

static const char srv_frag_shader[] =
#ifndef STANDALONE
" #extension GL_OES_EGL_image_external : require \n"
#endif
" precision mediump float;\n "
#ifndef STANDALONE
" uniform samplerExternalOES uSampler[2];\n "
#else
" uniform sampler2D uSampler[2];\n "
#endif

" uniform int select;\n "
" varying vec2 outNormTexture;\n "
" varying vec2 outNormTexture1;\n "
" varying vec2 outBlendVals;\n "
" vec4 iFragColor1; \n "
" vec4 iFragColor2; \n "
" void main(){\n"
"     iFragColor1  = texture2D(uSampler[0], outNormTexture);\n "
"     iFragColor2  = texture2D(uSampler[1], outNormTexture1);\n "
"     gl_FragColor = (outBlendVals.x)*iFragColor1 + (outBlendVals.y)*iFragColor2;\n "
" }\n"
;

void generate_indices(t_index_buffer *index_buffer, int xlength, int ylength, int gap)
{
	unsigned int *buffer = index_buffer->buffer;
	unsigned int x, y, k=0;
	for (y=0; y<ylength-gap; y+=gap)
	{
		if(y>0)
			buffer[k++]=(unsigned int) (y*xlength);
		for (x=0; x<xlength; x+=gap)
		{
			buffer[k++]=(unsigned int) (y*xlength + x);
			buffer[k++]=(unsigned int) ((y+gap)*xlength + x);
		}
		if(y < ylength - 1 - gap)
			buffer[k++]=(unsigned int) ((y+gap)*xlength + (xlength -1));
	}
	index_buffer->length = k;
}

int srv_setup(render_state_t *pObj)
{
	if(pObj->LUT3D == NULL)
	{
		// Generate the LUT if it wasn't passed
		pObj->LUT3D = malloc(sizeof(int16_t) * (POINTS_WIDTH/POINTS_SUBX) * (POINTS_HEIGHT/POINTS_SUBY) * 9 * 2);
		srv_generate_lut(POINTS_WIDTH, POINTS_HEIGHT,
				pObj->cam_width,
				pObj->cam_height,
				POINTS_SUBX,
				POINTS_SUBY,
				(srv_lut_t *)pObj->LUT3D);
	}

#ifndef SRV_INTERLEAVED_BLEND
	if(pObj->blendLUT3D == NULL)
	{
		// Generate the BlendLUT if it wasn't passed
		pObj->blendLUT3D = malloc(sizeof(int16_t) * (POINTS_WIDTH/POINTS_SUBX) * (POINTS_HEIGHT/POINTS_SUBY) * 9 * 2);
		srv_generate_blend_lut(POINTS_WIDTH, POINTS_HEIGHT,
				POINTS_SUBX,
				POINTS_SUBY,
				(srv_blend_lut_t *)pObj->blendLUT3D);
	}
#endif
	if(srv_render_to_file == true)
	{
		uiProgramObject = render_createProgram(
				srv_vert_shader_lut,
				srv_frag_shader_lut
				);
	}
	else
	{
#if 1
		uiProgramObject = renderutils_createProgram(
				srv_vert_shader,
				srv_frag_shader
				);
#else
		uiProgramObject = renderutils_loadAndCreateProgram("srv_vert.vsh", "srv_frag.fsh");
#endif
	}
	if (uiProgramObject==0)
	{
		return -1;
	}

	glUseProgram(uiProgramObject);
	System_eglCheckGlError("glUseProgram");

	//locate sampler uniforms
	uniform_select = glGetUniformLocation(uiProgramObject, "select");
	GL_CHECK(glGetAttribLocation);
	samplerLocation0 = glGetUniformLocation(uiProgramObject, "uSampler[0]");
	glUniform1i(samplerLocation0, 0);
	GL_CHECK(glUniform1i);
	samplerLocation1 = glGetUniformLocation(uiProgramObject, "uSampler[1]");
	glUniform1i(samplerLocation1, 1);
	GL_CHECK(glUniform1i);
	mvMatrixLocation = glGetUniformLocation(uiProgramObject, "uMVMatrix");
	GL_CHECK(glGetAttribLocation);

#ifndef STATIC_COORDINATES
	uniform_rangex = glGetUniformLocation(uiProgramObject, "uRangeX");
	GL_CHECK(glGetUniformLocation);
	uniform_rangey = glGetUniformLocation(uiProgramObject, "uRangeY");
	GL_CHECK(glGetUniformLocation);
	uniform_texturex = glGetUniformLocation(uiProgramObject, "uTextureX");
	GL_CHECK(glGetUniformLocation);
	uniform_texturey= glGetUniformLocation(uiProgramObject, "uTextureY");
	GL_CHECK(glGetUniformLocation);
	glUniform1f(uniform_rangex, (GLfloat)float(POINTS_WIDTH/2));
	GL_CHECK(glUniform1f);
	glUniform1f(uniform_rangey, (GLfloat)float(POINTS_HEIGHT/2));
	GL_CHECK(glUniform1f);
	glUniform1f(uniform_texturex, (GLfloat)float(pObj->cam_width * 16));
	GL_CHECK(glUniform1f);
	glUniform1f(uniform_texturey, (GLfloat)float(pObj->cam_height * 16));
	GL_CHECK(glUniform1f);
#endif

	vertexPositionAttribLoc = glGetAttribLocation(uiProgramObject, "aVertexPosition");
	GL_CHECK(glGetAttribLocation);
	blendAttribLoc = glGetAttribLocation(uiProgramObject, "blendVals");
	GL_CHECK(glGetAttribLocation);
	vertexTexCoord1AttribLoc = glGetAttribLocation(uiProgramObject, "aTextureCoord1");
	GL_CHECK(glGetAttribLocation);
	vertexTexCoord2AttribLoc = glGetAttribLocation(uiProgramObject, "aTextureCoord2");
	GL_CHECK(glGetAttribLocation);

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	System_eglCheckGlError("glClearColor");
	glClear( GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
	System_eglCheckGlError("glClear");

	glDisable(GL_DEPTH_TEST);
#ifdef ENABLE_GLOBAL_BLENDING
	glEnable(GL_BLEND);
	glBlendEquation(GL_FUNC_ADD);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
#endif

	//Generate indices
	for (int i = 0; i < MAX_INDEX_BUFFERS; i++)
	{
		index_buffers[i].buffer = (unsigned int *)malloc(QUADRANT_WIDTH * QUADRANT_HEIGHT * 3 * sizeof(unsigned int));
		generate_indices((t_index_buffer *)&index_buffers[i], QUADRANT_WIDTH, QUADRANT_HEIGHT, pow(2,i));
	}

	// Generate named buffers for indices and vertices
	glGenBuffers(QUADRANTS*3, vboId);

}

//Vertices init for surround view (VBO approach)
static int surroundview_init_vertices_vbo(render_state_t *pObj, GLuint vertexId, GLuint indexId, GLuint blendId,
		void* vertexBuff, void* indexBuff, void * blendBuff,
		int vertexBuffSize, int indexBuffSize, int blendBuffSize
		)
{
	//upload the vertex and texture and image index interleaved array
	//Bowl LUT - Interleaved data (5 data)
	glBindBuffer(GL_ARRAY_BUFFER, vertexId);

	glBufferData(GL_ARRAY_BUFFER, vertexBuffSize, vertexBuff, GL_STATIC_DRAW);
	glVertexAttribPointer(vertexPositionAttribLoc, 3, GL_VERTEX_ENUM, GL_FALSE, sizeof(srv_lut_t), 0);
	glVertexAttribPointer(vertexTexCoord1AttribLoc, 2, GL_TEXCOORD_ENUM, GL_FALSE, sizeof(srv_lut_t), (GLvoid*)(offsetof(srv_lut_t, u1)));
	glVertexAttribPointer(vertexTexCoord2AttribLoc, 2, GL_TEXCOORD_ENUM, GL_FALSE, sizeof(srv_lut_t), (GLvoid*)(offsetof(srv_lut_t, u2)));
#ifdef SRV_INTERLEAVED_BLEND
	glVertexAttribPointer(blendAttribLoc, 2, GL_BLEND_ENUM, GL_TRUE, sizeof(srv_lut_t), (GLvoid*)(offsetof(srv_lut_t, blend1)));
#endif
	GL_CHECK(glVertexAttribPointer);

#ifndef SRV_INTERLEAVED_BLEND
	glBindBuffer(GL_ARRAY_BUFFER, blendId);
	glBufferData(GL_ARRAY_BUFFER, blendBuffSize, blendBuff, GL_STATIC_DRAW);
	glVertexAttribPointer(blendAttribLoc, 2, GL_BLEND_ENUM, GL_TRUE, sizeof(_srv_blend_lut_t), 0);
	GL_CHECK(glVertexAttribPointer);
#endif

	//Index buffer
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexId);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexBuffSize, indexBuff, GL_STATIC_DRAW);
	GL_CHECK(glBufferData);

	//Enable for the rendering
	glEnableVertexAttribArray(vertexPositionAttribLoc);
	glEnableVertexAttribArray(vertexTexCoord1AttribLoc);
	glEnableVertexAttribArray(vertexTexCoord2AttribLoc);
	glEnableVertexAttribArray(blendAttribLoc);

	return 0;
}

void surroundview_init_vertices_vbo_wrap(render_state_t *pObj)
{
	int i;
	int vertexoffset = 0;
	int blendoffset = 0;

	for(i = 0;i < QUADRANTS;i ++)
	{
		vertexoffset = i * (sizeof(srv_lut_t)*QUADRANT_WIDTH*QUADRANT_HEIGHT);
		blendoffset = i * (sizeof(srv_blend_lut_t)*QUADRANT_WIDTH*QUADRANT_HEIGHT);

		surroundview_init_vertices_vbo(
				pObj,
				vboId[i*3], vboId[i*3+1], vboId[i*3+2],
				(char*)pObj->LUT3D + vertexoffset,
				(char*)(index_buffers[active_index_buffer].buffer),
				(char*)pObj->blendLUT3D + blendoffset,
				sizeof(srv_lut_t)*QUADRANT_WIDTH*QUADRANT_HEIGHT,
				sizeof(int)*(index_buffers[active_index_buffer].length),
				sizeof(srv_blend_lut_t)*QUADRANT_WIDTH*QUADRANT_HEIGHT
				);
	}
	index_buffer_changed = false;
}

void onscreen_mesh_state_restore_program_textures_attribs(render_state_t *pObj, GLuint *texYuv, int tex1, int tex2, int viewport_id)
{
	//set the program we need
	glUseProgram(uiProgramObject);

	glUniform1i(samplerLocation0, 0);
	glActiveTexture(GL_TEXTURE0);

#ifndef STANDALONE
	glBindTexture(GL_TEXTURE_EXTERNAL_OES, texYuv[tex1]);
	glTexParameteri(GL_TEXTURE_EXTERNAL_OES, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_EXTERNAL_OES, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
#else
	glBindTexture(GL_TEXTURE_2D, texYuv[tex1]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
#endif
	GL_CHECK(glBindTexture);

	glUniform1i(samplerLocation1, 1);
	glActiveTexture(GL_TEXTURE1);

#ifndef STANDALONE
	glBindTexture(GL_TEXTURE_EXTERNAL_OES, texYuv[tex2]);
	glTexParameteri(GL_TEXTURE_EXTERNAL_OES, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_EXTERNAL_OES, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
#else
	glBindTexture(GL_TEXTURE_2D, texYuv[tex2]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
#endif
	GL_CHECK(glBindTexture);

	//Enable the attributes
	glEnableVertexAttribArray(vertexPositionAttribLoc);
	glEnableVertexAttribArray(vertexTexCoord1AttribLoc);
	glEnableVertexAttribArray(vertexTexCoord2AttribLoc);
	glEnableVertexAttribArray(blendAttribLoc);

	glUniformMatrix4fv(mvMatrixLocation, 1, GL_FALSE, &mMVP_bowl[viewport_id][0][0]);
	GL_CHECK(glUniformMatrix4fv);

	glUniform1i(uniform_select, shader_output_select);

}

void onscreen_mesh_state_restore_vbo(render_state_t *pObj,
		GLuint vertexId, GLuint indexId, GLuint blendId)
{

	//restore the vertices and indices
	glBindBuffer(GL_ARRAY_BUFFER, vertexId);
	glVertexAttribPointer(vertexPositionAttribLoc, 3, GL_VERTEX_ENUM, GL_FALSE, sizeof(srv_lut_t), 0);
	glVertexAttribPointer(vertexTexCoord1AttribLoc, 2, GL_TEXCOORD_ENUM, GL_FALSE, sizeof(srv_lut_t), (GLvoid*)(offsetof(srv_lut_t, u1)));
	glVertexAttribPointer(vertexTexCoord2AttribLoc, 2, GL_TEXCOORD_ENUM, GL_FALSE, sizeof(srv_lut_t), (GLvoid*)(offsetof(srv_lut_t, u2)));
#ifdef SRV_INTERLEAVED_BLEND
	glVertexAttribPointer(blendAttribLoc, 2, GL_BLEND_ENUM, GL_TRUE, sizeof(srv_lut_t), (GLvoid*)(offsetof(srv_lut_t, blend1)));
#else
	glBindBuffer(GL_ARRAY_BUFFER, blendId);
	glVertexAttribPointer(blendAttribLoc, 2, GL_BLEND_ENUM, GL_TRUE, sizeof(_srv_blend_lut_t), 0);
#endif
	//Index buffer
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexId);
}

void srv_draw(render_state_t *pObj, GLuint *texYuv, int viewport_id)
{
	int i;
	if(prevLUT != pObj->LUT3D || index_buffer_changed == true)
	{
		prevLUT = pObj->LUT3D;
		surroundview_init_vertices_vbo_wrap(pObj);
	}

	//First setup the program once
	glUseProgram(uiProgramObject);
	//then change the meshes and draw
	for(i = 0;i < QUADRANTS;i ++)
	{
		onscreen_mesh_state_restore_program_textures_attribs(
				pObj, texYuv, (0+i)%4, (3+i)%4, viewport_id);
		onscreen_mesh_state_restore_vbo(
				pObj, vboId[i*3], vboId[i*3+1], vboId[i*3+2]);
		GL_CHECK(onscreen_mesh_state_restore_vbo);
		glDrawElements(render_mode, index_buffers[active_index_buffer].length, GL_UNSIGNED_INT,  0);
		GL_CHECK(glDrawElements);
	}
	glFlush();
}
