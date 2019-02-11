/*
 *******************************************************************************
 *
 * Copyright (C) 2015 Texas Instruments Incorporated - http://www.ti.com/
 * ALL RIGHTS RESERVED
 *
 *******************************************************************************
 */

#include "shaders.h"

/*Vertex & Fragment Shaders*/
static const char* vshader = "\
    precision mediump float; \
	attribute vec4 aVertexPosition;\
	uniform mat4 uMVMatrix;\
    void main(void) {\
    gl_Position = uMVMatrix * aVertexPosition;\
    }";

static const char* fshader = "\
    precision mediump float; \
    uniform vec4 uColor; \
    void main(void) {\
        gl_FragColor = uColor;\
    }";

int shaders_init(SgxRender3DsfmSharedObj *pShareObj)
{
    /* Create program and link */
    GLuint uiFragShader, uiVertShader;		// Used to hold the fragment and vertex shader handles

    // Create the fragment shader object
    uiFragShader = glCreateShader(GL_FRAGMENT_SHADER);

    // Load the source code into it
    glShaderSource(uiFragShader, 1, (const char**)&fshader, NULL);
    // Compile the source code
    glCompileShader(uiFragShader);

    // Check if compilation succeeded
    GLint bShaderCompiled;
    glGetShaderiv(uiFragShader, GL_COMPILE_STATUS, &bShaderCompiled);

    if (!bShaderCompiled)
    {
        D_PRINTF("Error in frag shader!\n");
    }
    // Loads the vertex shader in the same way
    uiVertShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(uiVertShader, 1, (const char**)&vshader, NULL);

    glCompileShader(uiVertShader);
    glGetShaderiv(uiVertShader, GL_COMPILE_STATUS, &bShaderCompiled);

    if (!bShaderCompiled)
    {
        GLint infoLogLength;
	glGetShaderiv(uiVertShader, GL_INFO_LOG_LENGTH, &infoLogLength);

        GLchar* strInfoLog = new GLchar[infoLogLength + 1];
	glGetShaderInfoLog(uiVertShader, infoLogLength, NULL, strInfoLog);

        fprintf(stderr, "Compilation error in shader: %s\n", strInfoLog);
        delete[] strInfoLog;

        D_PRINTF("Error: compiling vert shader\n");
    }
    // Create the shader program
    pShareObj->points_program = glCreateProgram();

    // Attach the fragment and vertex shaders to it
    glAttachShader(pShareObj->points_program, uiFragShader);
    glAttachShader(pShareObj->points_program, uiVertShader);

    // Link the program
    glLinkProgram(pShareObj->points_program);

    // Check if linking succeeded in the same way we checked for compilation success
    GLint bLinked;
    glGetProgramiv(pShareObj->points_program, GL_LINK_STATUS, &bLinked);

    //set the program
    glUseProgram(pShareObj->points_program);

    if (!bLinked)
    {
        D_PRINTF("Error: linking prog\n");
    }

    //locate sampler uniforms
    pShareObj->points_mvMatrixOffsetLoc = glGetUniformLocation(pShareObj->points_program, "uMVMatrix");
    GL_CHECK(glGetUniformLocation);

    //locate color uniform
    pShareObj->colorLoc = glGetUniformLocation(pShareObj->points_program, "uColor");
    GL_CHECK(glGetUniformLocation);

    //locate attributes
    pShareObj->vertexAttribPosition = glGetAttribLocation(pShareObj->points_program, "aVertexPosition");
    GL_CHECK(glGetAttribLocation);

    return 0;
}

