/*
 *******************************************************************************
 *
 * Copyright (C) 2013 Texas Instruments Incorporated - http://www.ti.com/
 * ALL RIGHTS RESERVED
 *
 *******************************************************************************
 */

#include "sgxRender3Dsfm_priv.h"

#define SCREEN1_POINTS_WIDTH 2
#define SCREEN1_POINTS_HEIGHT 2

static float screen1_mesh[] = { -1,1,0,    0,1,   -1,-1,0,  0,0,  1,-1,0, 1,0,   1,1,0, 1,1};
static unsigned short screen1_index_mesh[] = {0, 1, 2, 0, 2, 3};

static const char vshader_1screen[] =
"    attribute vec4 aVertexPosition;\n"
"    attribute vec2 aTextureCoord1;\n"
"    varying vec2 oTextureCoord1;\n"
"    uniform mat4 uMVMatrix;\n"
"    void main(void) {\n"
"		   gl_Position = aVertexPosition;\n"
"    		oTextureCoord1 = aTextureCoord1;\n"
"    } \n";

static const char fshader_1screen[] =
#ifndef STANDALONE
" #extension GL_OES_EGL_image_external : require \n"
#endif
" precision mediump float;\n "
#ifndef STANDALONE
" uniform samplerExternalOES uSampler0;\n "
#else
" uniform sampler2D uSampler0;\n "
#endif
" varying vec2 oTextureCoord1;\n"
" void main(void) {\n"
"   	gl_FragColor = texture2D(uSampler0, vec2(oTextureCoord1.s, (1.0-oTextureCoord1.t)) );\n"
"    } \n";

static gl_state screen_state1;

void screen1_shader_init(gl_state *screen_state)
{

 // Create the shader program
	screen_state->program = SgxRender3Dsfm_createProgram( vshader_1screen, fshader_1screen);
 if(screen_state->program == 0) 
 {
   D_PRINTF("1screen program could not be created\n"); 
   return;
 }
  
 // Actually use the created program
	glUseProgram(screen_state->program);
	GL_CHECK(glUseProgram);

	//locate sampler uniforms
	screen_state->mvMatrixOffsetLoc = glGetUniformLocation(screen_state->program, "uMVMatrix");
	screen_state->samplerLoc = glGetUniformLocation(screen_state->program, "uSampler0");

	//locate attributes
	screen_state->attribIndices[0] = glGetAttribLocation(screen_state->program, "aVertexPosition");
	GL_CHECK(glGetAttribLocation);
	screen_state->attribIndices[1] = glGetAttribLocation(screen_state->program, "aTextureCoord1");
	GL_CHECK(glGetAttribLocation);
}

void screen1_shader_deinit(gl_state *screen_state)
{
	glDeleteProgram(screen_state->program);
}

static int stride = 3+2; //coords, tex1
static int screen1_init_vertices_vbo(gl_state* screen_state)
{  
	//upload the vertex and texture and image index interleaved array
	//Bowl LUT - Interleaved data (5 data)

	glGenBuffers(1, &screen_state->vboID[0]);
	glBindBuffer(GL_ARRAY_BUFFER, screen_state->vboID[0]);

	glBufferData(GL_ARRAY_BUFFER, stride*SCREEN1_POINTS_WIDTH*SCREEN1_POINTS_HEIGHT*sizeof(float), screen1_mesh, GL_STATIC_DRAW);
	glVertexAttribPointer(screen_state->attribIndices[0], 3, GL_FLOAT, GL_FALSE, (stride)*sizeof(float), 0);
	glVertexAttribPointer(screen_state->attribIndices[1], 2, GL_FLOAT, GL_FALSE, (stride)*sizeof(float), (GLvoid*)(3*sizeof(float)));
	GL_CHECK(glVertexAttribPointer);

	//Index buffer
	glGenBuffers(1, &screen_state->vboID[1]);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, screen_state->vboID[1]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(screen1_index_mesh), screen1_index_mesh, GL_STATIC_DRAW);
	GL_CHECK(glBufferData);

	//Enable for the rendering
	glEnableVertexAttribArray(screen_state->attribIndices[0]);
	glEnableVertexAttribArray(screen_state->attribIndices[1]);

	return 0;
}

 void screen1_state_restore_vbo(gl_state* screen_state, int texYuv)
{

	//set the program we need
	glUseProgram(screen_state->program);
	GL_CHECK(glUseProgram);

	//restore the vertices and indices - not required ?
	glBindBuffer(GL_ARRAY_BUFFER, screen_state->vboID[0]);
	glVertexAttribPointer(screen_state->attribIndices[0], 3, GL_FLOAT, GL_FALSE, (stride)*sizeof(float), 0);
	glVertexAttribPointer(screen_state->attribIndices[1], 2, GL_FLOAT, GL_FALSE, (stride)*sizeof(float), (GLvoid*)(3*sizeof(float)));
	GL_CHECK(glBindBuffer);
	//Index buffer
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, screen_state->vboID[1]);

	//Enable the attributes
	glEnableVertexAttribArray(screen_state->attribIndices[0]);
	glEnableVertexAttribArray(screen_state->attribIndices[1]);
	GL_CHECK(glEnableVertexAttribArray);
 
 //Bind the texture
	//region 0
 glUniform1i(screen_state->samplerLoc, 0); 
	glActiveTexture(GL_TEXTURE0);
#ifndef STANDALONE
 glBindTexture(GL_TEXTURE_EXTERNAL_OES, texYuv);
#else
 glBindTexture(GL_TEXTURE_2D, texYuv);
#endif
 GL_CHECK(glBindTexture);
}

void screen1_sfm_draw_vbo(int texYuv)
{
	screen1_state_restore_vbo(&screen_state1, texYuv);

	glDrawElements(GL_TRIANGLES, (SCREEN1_POINTS_WIDTH-1)*(SCREEN1_POINTS_HEIGHT-1)*6, GL_UNSIGNED_SHORT,  0);
	GL_CHECK(glDrawElements);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void screen1_sfm_init_vbo()
{
	screen1_shader_init(&screen_state1);
	screen1_init_vertices_vbo(&screen_state1);

}

void screen1_sfm_deinit_vbo()
{
	screen1_shader_deinit(&screen_state1);
}

