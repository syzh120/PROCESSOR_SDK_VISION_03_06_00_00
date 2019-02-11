/*
 *******************************************************************************
 *
 * Copyright (C) 2013 Texas Instruments Incorporated - http://www.ti.com/
 * ALL RIGHTS RESERVED
 *
 *******************************************************************************
 */

#ifdef _WIN32
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#endif

#include "car.h"
#include "render.h"
#include "renderutils.h"
#include "PVRTModelPOD.h"

#define GLM_FORCE_RADIANS
#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4, glm::ivec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective
#include <glm/gtc/type_ptr.hpp> // glm::value_ptr
#define degreesToRadians(x) x*(3.141592f/180.0f)

#include <limits.h>

#if !defined(SRV_CAR_MODEL_PATH)
#define SRV_CAR_MODEL_PATH "models"
#endif


extern glm::mat4 mProjection[];
extern glm::mat4 mView[];
extern glm::mat4 mMVP_car[];
extern int num_viewports;
/******************************************************************************
 Defines
******************************************************************************/
// Index to bind the attributes to vertex shaders
GLuint aVertex;
GLuint aNormal;
GLuint aTexCoord;
#define VERTEX_ARRAY    aVertex
#define NORMAL_ARRAY    aNormal
#define TEXCOORD_ARRAY  aTexCoord

/******************************************************************************
 Consts
******************************************************************************/
// Camera constants. Used for making the projection matrix
const float g_fCameraNear = 4.0f;
const float g_fCameraFar  = 5000.0f;

const float g_fDemoFrameRate = 1.0f / 30.0f;

// The camera to use from the pod file
const int g_ui32Camera = 0;

/******************************************************************************
 Content file names
******************************************************************************/

static const char vshader_car[] =
"	attribute vec3 inVertex;\n"
"	attribute vec3 inNormal;\n"
"	attribute vec2 inTexCoord;\n"
"	uniform mat4  MVPMatrix;\n"
"	uniform vec3  LightDirection;\n"
"	varying float  LightIntensity;\n"
"	varying vec2   TexCoord;\n"
"	void main()\n"
"	{\n"
"	gl_Position = MVPMatrix * vec4(inVertex, 1.0);\n"
"	    TexCoord = inTexCoord;\n"
"	    LightIntensity = dot(inNormal, -LightDirection);\n"
"    } \n";

static const char fshader_car[] =
"	precision mediump float;\n"
"	uniform sampler2D  sTexture;\n"
"	varying float  LightIntensity;\n"
"	varying vec2   TexCoord;\n"
"	void main()\n"
"	{\n"
"		gl_FragColor.rgb = texture2D(sTexture, TexCoord).bbb;\n"
"		gl_FragColor.a = 1.0;\n"
"   } \n";

// OpenGL handles for shaders, textures and VBOs
GLuint m_uiVertShader;
GLuint m_uiFragShader;

// Group shader programs and their uniform locations together
struct _car_program_t
{
        GLuint uiId;
        GLuint uiMVPMatrixLoc;
        GLuint uiLightDirLoc;
}
car_program;

typedef struct _car_data
{
	const char *foldername;
	const char *filename;
	CPVRTModelPOD   *scene;
	GLuint* vbo;
	GLuint* indices;
	GLuint* texture_ids;
	GLint xrot_degrees;
	GLint yrot_degrees;
	GLint zrot_degrees;
	GLfloat scale;
} car_data_t;

car_data_t car_data[] = {
	{
		foldername   : "jeep",
		filename     : "jeep.pod",
		scene        : NULL,
		vbo          : NULL,
		indices      : NULL,
		texture_ids  : NULL,
		xrot_degrees : 90,
		yrot_degrees : 180,
		zrot_degrees : 0,
		scale        : 25.0f,
	},
	{
		foldername   : "suv",
		filename     : "suv.pod",
		scene        : NULL,
		vbo          : NULL,
		indices      : NULL,
		texture_ids  : NULL,
		xrot_degrees : 90,
		yrot_degrees : 180,
		zrot_degrees : 0,
		scale        : 15.0f,
	},
	{
		foldername   : "sedan_generic",
		filename     : "sedan_generic.pod",
		scene        : NULL,
		vbo          : NULL,
		indices      : NULL,
		texture_ids  : NULL,
		xrot_degrees : 90,
		yrot_degrees : 0,
		zrot_degrees : 0,
		scale        : 25.0f,
#if 0
	},
	{
		foldername   : "car_highpoly",
		filename     : "car_highpoly.pod",
		scene        : NULL,
		vbo          : NULL,
		indices      : NULL,
		texture_ids  : NULL,
		xrot_degrees : 90,
		yrot_degrees : 180,
		zrot_degrees : 0,
		scale        : 0.2f,
#endif
	}
};
car_data_t *active_car;
int active_car_index = 0;
int num_car_models;

int load_texture_bmp(GLuint tex, const char *filename);
int load_texture_from_raw_file(GLuint tex, int width, int height, int textureType, const char* filename, int offset);

bool LoadTextures(car_data_t *cd)
{
	    int err;
        cd->texture_ids = new GLuint[cd->scene->nNumMaterial];

        if(!cd->texture_ids)
        {
                printf("ERROR: Insufficient memory.\n");
                return false;
        }

        for(int i = 0; i < (int) cd->scene->nNumMaterial; ++i)
        {
                cd->texture_ids[i] = 0;
                SPODMaterial* pMaterial = &cd->scene->pMaterial[i];

                if(pMaterial->nIdxTexDiffuse != -1)
                {
                        char filename[1024];
                        char * sTextureName = cd->scene->pTexture[pMaterial->nIdxTexDiffuse].pszName;
                        sprintf(filename, "%s/%s/%s", SRV_CAR_MODEL_PATH,
                                cd->foldername,
								sTextureName);
                        glGenTextures(1, &cd->texture_ids[i]);
                        glActiveTexture(GL_TEXTURE5);
                        glBindTexture(GL_TEXTURE_2D, cd->texture_ids[i]);
                        err = load_texture_bmp( cd->texture_ids[i], filename);
                        if(err != 0)
                        {
                            fprintf(stderr, "Failed to load texture: %s\n", filename);
                            return false;
                        }
                }
        }

        return true;
}

bool LoadShaders()
{
		car_program.uiId = renderutils_createProgram(vshader_car, fshader_car);
		if(car_program.uiId == 0)
		{
			printf("Car program could not be created\n");
			return false;
		}
        glUseProgram(car_program.uiId);

		aVertex = glGetAttribLocation(car_program.uiId, "inVertex");
		aNormal = glGetAttribLocation(car_program.uiId, "inNormal");
		aTexCoord = glGetAttribLocation(car_program.uiId, "inTexCoord");

        // Set the sampler2D variable to the first texture unit
        glUniform1i(glGetUniformLocation(car_program.uiId, "sTexture"), 5);

        // Store the location of uniforms for later use
        car_program.uiMVPMatrixLoc  = glGetUniformLocation(car_program.uiId, "MVPMatrix");
        car_program.uiLightDirLoc   = glGetUniformLocation(car_program.uiId, "LightDirection");
        return true;
}

bool LoadVbos(car_data_t *cd)
{
        if(!cd->scene->pMesh[0].pInterleaved)
        {
                printf("ERROR: Only interleaved vertex data is supported.\n");
                return false;
        }

        if (!cd->vbo)      cd->vbo = new GLuint[cd->scene->nNumMesh];
        if (!cd->indices)  cd->indices = new GLuint[cd->scene->nNumMesh];

        /*
                Load vertex data of all meshes in the scene into VBOs

                The meshes have been exported with the "Interleave Vectors" option,
                so all data is interleaved in the buffer at pMesh->pInterleaved.
                Interleaving data improves the memory access pattern and cache efficiency,
                thus it can be read faster by the hardware.
        */
        glGenBuffers(cd->scene->nNumMesh, cd->vbo);
        for (unsigned int i = 0; i < cd->scene->nNumMesh; ++i)
        {
                // Load vertex data into buffer object
                SPODMesh& Mesh = cd->scene->pMesh[i];
                PVRTuint32 uiSize = Mesh.nNumVertex * Mesh.sVertex.nStride;
                glBindBuffer(GL_ARRAY_BUFFER, cd->vbo[i]);
                glBufferData(GL_ARRAY_BUFFER, uiSize, Mesh.pInterleaved, GL_STATIC_DRAW);

                // Load index data into buffer object if available
                cd->indices[i] = 0;
                if (Mesh.sFaces.pData)
                {
                        glGenBuffers(1, &cd->indices[i]);
                        uiSize = PVRTModelPODCountIndices(Mesh) * Mesh.sFaces.nStride;
                        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, cd->indices[i]);
                        glBufferData(GL_ELEMENT_ARRAY_BUFFER, uiSize, Mesh.sFaces.pData, GL_STATIC_DRAW);
                }
	}
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	return true;
}

bool InitView()
{

	EPVRTError err;
	int at_least_one_model = 0;
	num_car_models = sizeof(car_data)/sizeof(car_data_t);
	for(int i = 0; i < num_car_models; i++)
	{
		CPVRTModelPOD scene;
		car_data[i].scene = new CPVRTModelPOD;
		char filename[1024];
		sprintf(filename, "%s/%s/%s", SRV_CAR_MODEL_PATH,
				car_data[i].foldername,
				car_data[i].filename);
		// Load the scene
		if(scene.ReadFromFile(filename) != PVR_SUCCESS)
		{
			printf("Couldn't load .pod file: %s\n", car_data[i].filename);
			delete car_data[i].scene;
			car_data[i].scene = NULL;
			continue;
		}

		// Make sure meshes are non-interleaved for flattening to world space
		for (unsigned int m = 0; m < scene.nNumMesh; ++m)
		{
			// Load vertex data into buffer object
			SPODMesh& Mesh = scene.pMesh[m];
			if(Mesh.pInterleaved)
				PVRTModelPODToggleInterleaved(Mesh, 1);
		}

		err = PVRTModelPODFlattenToWorldSpace(scene, *(car_data[i].scene));
		if(err)
		{
			printf("Could not flatten POD model: %d\n", err);
			delete car_data[i].scene;
			car_data[i].scene = NULL;
			continue;
		}

		// Make sure meshes are interleaved for use in our code
		for (unsigned int m = 0; m < car_data[i].scene->nNumMesh; ++m)
		{
			// Load vertex data into buffer object
			SPODMesh& Mesh = car_data[i].scene->pMesh[m];
			if(!Mesh.pInterleaved)
				PVRTModelPODToggleInterleaved(Mesh, 1);
		}

		/*
		   Initialize VBO data
		 */
		if(!LoadVbos(&car_data[i]))
		{
			printf("Couldn't load vbos for .pod file: %s\n", car_data[i].filename);
			delete car_data[i].scene;
			delete car_data[i].vbo;
			delete car_data[i].indices;
			car_data[i].scene = NULL;
			car_data[i].vbo = NULL;
			car_data[i].indices = NULL;
			continue;	
		}

		/*
		   Load textures
		 */
		if(!LoadTextures(&car_data[i]))
		{
			printf("Couldn't load textures for .pod file: %s\n", car_data[i].filename);
			delete car_data[i].scene;
			delete car_data[i].vbo;
			delete car_data[i].indices;
			delete car_data[i].texture_ids;
			car_data[i].scene = NULL;
			car_data[i].vbo = NULL;
			car_data[i].indices = NULL;
			car_data[i].texture_ids = NULL;
			continue;
		}
		at_least_one_model = 1;
	}
	
	if(!at_least_one_model)
	{
		printf("ERROR: Couldn't load any car model\n");
		return false;
	}

	while(car_data[active_car_index].scene == NULL)
		active_car_index = (active_car_index + 1) % num_car_models;

        /*
                Load and compile the shaders & link programs
        */
        if(!LoadShaders())
        {
        		printf("Failed to load shaders\n");
                //PVRShellSet(prefExitMessage, ErrorStr.c_str());
                return false;
        }

        /*
                Initialize Print3D
        */

        // Enable backface culling and depth test
        glCullFace(GL_BACK);
        glEnable(GL_CULL_FACE);

        return true;
}

bool ReleaseView()
{
	for(int i = 0; i < num_car_models; i++)
	{
		// Deletes the textures
		if(car_data[i].scene)
		{
			glDeleteTextures(car_data[i].scene->nNumMaterial, &car_data[i].texture_ids[0]);

			// Delete buffer objects
			glDeleteBuffers(car_data[i].scene->nNumMesh, car_data[i].vbo);
			glDeleteBuffers(car_data[i].scene->nNumMesh, car_data[i].indices);

			// Free resources
			delete[] car_data[i].vbo;
			delete[] car_data[i].indices;
			delete[] car_data[i].texture_ids;
			delete car_data[i].scene;

			car_data[i].vbo = NULL;
			car_data[i].indices = NULL;
			car_data[i].texture_ids = NULL;
			car_data[i].scene = NULL;
		}
	}

	// Delete program and shader objects
	glDeleteProgram(car_program.uiId);

	glDeleteShader(m_uiVertShader);
	glDeleteShader(m_uiFragShader);

        return true;
}

void DrawMesh(car_data_t *cd, int i32NodeIndex)
{
        int i32MeshIndex = cd->scene->pNode[i32NodeIndex].nIdx;
        SPODMesh* pMesh = &cd->scene->pMesh[i32MeshIndex];

		//FIXME: Hack for jeep model to remove the back wheel
		//if(i32NodeIndex == 5)
		//	return;

        // bind the VBO for the mesh
        glBindBuffer(GL_ARRAY_BUFFER, cd->vbo[i32MeshIndex]);
        // bind the index buffer, won't hurt if the handle is 0
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, cd->indices[i32MeshIndex]);

        // Enable the vertex attribute arrays
        glEnableVertexAttribArray(VERTEX_ARRAY);
        glEnableVertexAttribArray(NORMAL_ARRAY);
        glEnableVertexAttribArray(TEXCOORD_ARRAY);

        // Set the vertex attribute offsets
        glVertexAttribPointer(VERTEX_ARRAY, 3, GL_FLOAT, GL_FALSE, pMesh->sVertex.nStride, pMesh->sVertex.pData);
        glVertexAttribPointer(NORMAL_ARRAY, 3, GL_FLOAT, GL_FALSE, pMesh->sNormals.nStride, pMesh->sNormals.pData);
        glVertexAttribPointer(TEXCOORD_ARRAY, 2, GL_FLOAT, GL_FALSE, pMesh->psUVW[0].nStride, pMesh->psUVW[0].pData);

        if(pMesh->nNumStrips == 0)
        {
                if(cd->indices[i32MeshIndex])
                {
                        // Indexed Triangle list

                        // Are our face indices unsigned shorts? If they aren't, then they are unsigned ints
                        GLenum type = (pMesh->sFaces.eType == EPODDataUnsignedShort) ? GL_UNSIGNED_SHORT : GL_UNSIGNED_INT;
                        glDrawElements(GL_TRIANGLES, pMesh->nNumFaces*3, type, 0);
                }
                else
                {
                        // Non-Indexed Triangle list
                        glDrawArrays(GL_TRIANGLES, 0, pMesh->nNumFaces*3);
                }
        }
        else
        {
                PVRTuint32 offset = 0;

                // Are our face indices unsigned shorts? If they aren't, then they are unsigned ints
                GLenum type = (pMesh->sFaces.eType == EPODDataUnsignedShort) ? GL_UNSIGNED_SHORT : GL_UNSIGNED_INT;

                for(int i = 0; i < (int)pMesh->nNumStrips; ++i)
                {
                        if(cd->indices[i32MeshIndex])
                        {
                                // Indexed Triangle strips
                                glDrawElements(GL_TRIANGLE_STRIP, pMesh->pnStripLength[i]+2, type, (void*) (offset * pMesh->sFaces.nStride));
                        }
                        else
                        {
                                // Non-Indexed Triangle strips
                                glDrawArrays(GL_TRIANGLE_STRIP, offset, pMesh->pnStripLength[i]+2);
                        }
                        offset += pMesh->pnStripLength[i]+2;
                }
        }

        // Safely disable the vertex attribute arrays
        glDisableVertexAttribArray(VERTEX_ARRAY);
        glDisableVertexAttribArray(NORMAL_ARRAY);
		glDisableVertexAttribArray(TEXCOORD_ARRAY);

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

bool RenderScene(car_data_t *cd, int viewport_id)
{
        // Clear the color and depth buffer
        glClear(GL_DEPTH_BUFFER_BIT);
        glDepthFunc(GL_LEQUAL);
        glEnable(GL_DEPTH_TEST);
        // Use shader program
        glUseProgram(car_program.uiId);

        /*
                Get the direction of the first light from the scene.
        */

        for (unsigned int i = 0; i < cd->scene->nNumMeshNode; ++i)
        {
		SPODNode& Node = cd->scene->pNode[i];

		// Pass the model-view-projection matrix (MVP) to the shader to transform the vertices
		glUniformMatrix4fv(car_program.uiMVPMatrixLoc, 1, GL_FALSE, &mMVP_car[viewport_id][0][0]);

		// Load the correct texture using our texture lookup table
		GLuint uiTex = 0;

		if(Node.nIdxMaterial != -1)
			uiTex = cd->texture_ids[Node.nIdxMaterial];

		glActiveTexture(GL_TEXTURE5);
		glBindTexture(GL_TEXTURE_2D, uiTex);

		/*
		   Now that the model-view matrix is set and the materials are ready,
                        call another function to actually draw the mesh.
                */
                DrawMesh(cd, i);
        }

        glDisable(GL_DEPTH_TEST);
        return true;
}

int car_init()
{
	InitView();
	return 0;
}

int car_deinit()
{
	ReleaseView();
	return 0;
}

void car_draw(int viewport_id)
{
    RenderScene(&car_data[active_car_index], viewport_id);
}

void car_updateView(int i)
{
	glm::mat4 mView_car;
	mView_car = glm::scale(mView[i], glm::vec3(car_data[active_car_index].scale));
	mView_car = glm::rotate(mView_car, degreesToRadians(car_data[active_car_index].xrot_degrees), glm::vec3(1.0, 0.0, 0.0));
	mView_car = glm::rotate(mView_car, degreesToRadians(car_data[active_car_index].yrot_degrees), glm::vec3(0.0, 1.0, 0.0));
	mView_car = glm::rotate(mView_car, degreesToRadians(car_data[active_car_index].zrot_degrees), glm::vec3(0.0, 0.0, 1.0));
	mMVP_car[i] = mProjection[i] * mView_car;
}

void car_change()
{
	do
	{
		active_car_index = (active_car_index + 1) % num_car_models;
	}
	while (car_data[active_car_index].scene == NULL);
	for (int i = 0; i < num_viewports; i++)
		car_updateView(i);
}

void car_worldToNdc(float *xndc, float *yndc, GLfloat x, GLfloat y, GLfloat z)
{
        glm::vec4 vTransformedVector = mMVP_car[0] * glm::vec4(x, y, z, 1);
        *xndc = vTransformedVector.x/vTransformedVector.z;
        *yndc = vTransformedVector.y/vTransformedVector.z;
}

void car_worldToScreen(int *xscr, int *yscr, GLfloat x, GLfloat y, GLfloat z)
{
        float xndc, yndc;
        car_worldToNdc(&xndc, &yndc, x, y, z);
        render_ndcToScreen(xscr, yscr, xndc, yndc);
}

void car_getScreenLimits(int *xmin, int *xmax, int *ymin, int *ymax)
{
	int x, y;
	car_data_t *cd = &car_data[active_car_index];
	*xmin = INT_MAX;
	*xmax = -INT_MAX;
	*ymin = INT_MAX;
	*ymax = -INT_MAX;

        for (unsigned int i = 0; i < cd->scene->nNumMesh; ++i)
        {
                // Load vertex data into buffer object
		SPODMesh& Mesh = cd->scene->pMesh[i];
		for (unsigned int j = 0; j < Mesh.nNumVertex; j++)
		{
			vertex3df *v = (vertex3df *)((uint8_t *)(Mesh.pInterleaved) + (Mesh.sVertex.nStride * j));
			car_worldToScreen(&x, &y, v->x, v->y, v->z);
			if(x < *xmin) *xmin = x;
			if(x > *xmax) *xmax = x;
			if(y < *ymin) *ymin = y;
			if(y > *ymax) *ymax = y;
		}
	}
}
