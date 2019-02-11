/*
 *******************************************************************************
 *
 * Copyright (C) 2013 Texas Instruments Incorporated - http://www.ti.com/
 * ALL RIGHTS RESERVED
 *
 *******************************************************************************
 */

#ifndef _SGXRENDER3DSFMPRIV_H_
#define _SGXRENDER3DSFMPRIV_H_

#define GLM_FORCE_RADIANS
#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4, glm::ivec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective
#include <glm/gtc/type_ptr.hpp> // glm::value_ptr

#include "sgxRender3Dsfm.h"
#include "sgxRender3DsfmDefs.h"
#include "single_view_sfm.h"

/*One over the size of one grid cell in mm*/
/*Note: technically, this is not needed anymore, since there is no surround view grid,
 *      but to preserve the original layout, we keep this.*/
#define SGXRENDER3DSFM_GRID_CELL_SIZE_INV (1.0f/5.0f)

/*info that needs to be shared across cpp files*/
typedef struct
{
    /*pointer to render link's render object*/
    SgxRender3Dsfm_Obj *publicObj;

    /*MVP for center (ego) view*/
    /*note: model matrix is constructed in the each submodule at runtime*/
    glm::mat4 mProjection; /*projection matrix (P) of center (ego) view*/
    glm::mat4 mView; /*view matrix (V) of center (ego) view*/

    /*Program & Attributes for center (ego) view */
    int points_program;
    GLuint vertexAttribPosition;
    GLint points_mvMatrixOffsetLoc;
    GLint colorLoc;

} SgxRender3DsfmSharedObj;

/*used in shader.cpp and car.cpp*/
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

int car_init_vertices_vbo(SgxRender3DsfmSharedObj *pObj);
void car_draw_vbo(SgxRender3DsfmSharedObj *pObj);

void screen1_draw_vbo(int texYuv);
void screen1_init_vbo(void);

void  SgxRender3Dsfm_updateView(SgxRender3DsfmSharedObj *pObj);
void  SgxRender3Dsfm_updateView(SgxRender3DsfmSharedObj *pObj);
GLuint SgxRender3Dsfm_createProgram(const char* pVertexSource, const char* pFragmentSource);

#endif /*   _SGXRENDER3Dsfm_H_    */
