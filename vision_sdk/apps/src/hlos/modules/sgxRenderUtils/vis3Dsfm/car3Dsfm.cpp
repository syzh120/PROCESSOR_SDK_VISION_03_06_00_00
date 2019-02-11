/*
 *******************************************************************************
 *
 * Copyright (C) 2015 Texas Instruments Incorporated - http://www.ti.com/
 * ALL RIGHTS RESERVED
 *
 *******************************************************************************
 */

#include "sgxRender3Dsfm_priv.h"
#include "jeep_object.txt"
#include "OGLES2Tools.h"

#define degreesToRadians(x) x*(3.141592f/180.0f)

/******************************************************************************
 Defines
******************************************************************************/
// Index to bind the attributes to vertex shaders
#define VERTEX_ARRAY    0
#define NORMAL_ARRAY    1
#define TEXCOORD_ARRAY  2

/******************************************************************************
 Content file names
******************************************************************************/

// Source and binary shaders
static const char c_szFragShaderSrcFile[]      = "FragShader3Dsfm.fsh";
static const char c_szFragShaderBinFile[]      = "FragShader3Dsfm.fsc";
static const char c_szVertShaderSrcFile[]      = "VertShader3Dsfm.vsh";
static const char c_szVertShaderBinFile[]      = "VertShader3Dsfm.vsc";

// POD scene files
static const char c_szSceneFile[]                      = "car.pod";

// 3D Model
static CPVRTModelPOD   m_Scene;

// OpenGL handles for shaders, textures and VBOs
static GLuint m_uiVertShader;
static GLuint m_uiFragShader;
static GLuint* m_puiVbo;
static GLuint* m_puiIndexVbo;
static GLuint* m_puiTextureIDs;

// Group shader programs and their uniform locations together
static struct _m_ShaderProgram_t
{
        GLuint uiId;
        GLuint uiMVPMatrixLoc;
        GLuint uiLightDirLoc;
}
m_ShaderProgram;

// static functions
static bool ReleaseView();

int load_texture_from_raw_file(GLuint tex, int width, int height, int textureType, const char* filename, int offset);

bool LoadTextures(CPVRTString* pErrorStr)
{
        /*
                Loads the textures.
                For a more detailed explanation, see Texturing and IntroducingPVRTools
        */

        /*
                Initialises an array to lookup the textures
                for each material in the scene.
        */
        m_puiTextureIDs = new GLuint[m_Scene.nNumMaterial];

        if(!m_puiTextureIDs)
        {
                *pErrorStr = "ERROR: Insufficient memory.";
                return false;
        }

        for(int i = 0; i < (int) m_Scene.nNumMaterial; ++i)
        {
                m_puiTextureIDs[i] = 0;
                SPODMaterial* pMaterial = &m_Scene.pMaterial[i];

                if(pMaterial->nIdxTexDiffuse != -1)
                {
                        char * sTextureName = m_Scene.pTexture[pMaterial->nIdxTexDiffuse].pszName;
                        glGenTextures(1, &m_puiTextureIDs[i]);
                        glActiveTexture(GL_TEXTURE5);
                        glBindTexture(GL_TEXTURE_2D, m_puiTextureIDs[i]);
                        GL_CHECK(glBindTexture);
                        load_texture_from_raw_file( m_puiTextureIDs[i], 1024, 1024, GL_RGB,  sTextureName, 54);
                }
        }

        return true;
}

bool LoadShaders(CPVRTString* pErrorStr)
{
        /*
                Load and compile the shaders from files.
                Binary shaders are tried first, source shaders
                are used as fallback.
        */
        if(PVRTShaderLoadFromFile(
                        c_szVertShaderBinFile, c_szVertShaderSrcFile, GL_VERTEX_SHADER, GL_SGX_BINARY_IMG, &m_uiVertShader, pErrorStr) != PVR_SUCCESS)
        {
        		printf("Failed to load vertex shader\n");
                return false;
        }

        if (PVRTShaderLoadFromFile(
                        c_szFragShaderBinFile, c_szFragShaderSrcFile, GL_FRAGMENT_SHADER, GL_SGX_BINARY_IMG, &m_uiFragShader, pErrorStr) != PVR_SUCCESS)
        {
        		printf("Failed to load fragment shader\n");
                return false;
        }

        /*
                Set up and link the shader program
        */
        const char* aszAttribs[] = { "inVertex", "inNormal", "inTexCoord" };

        if(PVRTCreateProgram(
                        &m_ShaderProgram.uiId, m_uiVertShader, m_uiFragShader, aszAttribs, 3, pErrorStr) != PVR_SUCCESS)
        {
                printf("Failed to create program\n");
                return false;
        }
        // Set the sampler2D variable to the first texture unit
        glUniform1i(glGetUniformLocation(m_ShaderProgram.uiId, "sTexture"), 5);

        // Store the location of uniforms for later use
        m_ShaderProgram.uiMVPMatrixLoc  = glGetUniformLocation(m_ShaderProgram.uiId, "MVPMatrix");
        m_ShaderProgram.uiLightDirLoc   = glGetUniformLocation(m_ShaderProgram.uiId, "LightDirection");

        return true;
}


bool LoadVbos(CPVRTString* pErrorStr)
{
        if(!m_Scene.pMesh[0].pInterleaved)
        {
                printf("ERROR: IntroducingPOD requires the pod data to be interleaved. Please re-export with the interleaved option enabled.\n");
                return false;
        }

        if (!m_puiVbo)      m_puiVbo = new GLuint[m_Scene.nNumMesh];
        if (!m_puiIndexVbo) m_puiIndexVbo = new GLuint[m_Scene.nNumMesh];

        /*
                Load vertex data of all meshes in the scene into VBOs

                The meshes have been exported with the "Interleave Vectors" option,
                so all data is interleaved in the buffer at pMesh->pInterleaved.
                Interleaving data improves the memory access pattern and cache efficiency,
                thus it can be read faster by the hardware.
        */
        glGenBuffers(m_Scene.nNumMesh, m_puiVbo);
        for (unsigned int i = 0; i < m_Scene.nNumMesh; ++i)
        {
                // Load vertex data into buffer object
                SPODMesh& Mesh = m_Scene.pMesh[i];
                PVRTuint32 uiSize = Mesh.nNumVertex * Mesh.sVertex.nStride;
                glBindBuffer(GL_ARRAY_BUFFER, m_puiVbo[i]);
                glBufferData(GL_ARRAY_BUFFER, uiSize, Mesh.pInterleaved, GL_STATIC_DRAW);

                // Load index data into buffer object if available
                m_puiIndexVbo[i] = 0;
                if (Mesh.sFaces.pData)
                {
                        glGenBuffers(1, &m_puiIndexVbo[i]);
                        uiSize = PVRTModelPODCountIndices(Mesh) * Mesh.sFaces.nStride;
                        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_puiIndexVbo[i]);
                        glBufferData(GL_ELEMENT_ARRAY_BUFFER, uiSize, Mesh.sFaces.pData, GL_STATIC_DRAW);
                }
        }
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

        return true;
}

bool ReleaseView()
{
        // Deletes the textures
        glDeleteTextures(m_Scene.nNumMaterial, &m_puiTextureIDs[0]);

        // Frees the texture lookup array
        delete[] m_puiTextureIDs;
        m_puiTextureIDs = 0;

        // Delete program and shader objects
        glDeleteProgram(m_ShaderProgram.uiId);

        glDeleteShader(m_uiVertShader);
        glDeleteShader(m_uiFragShader);

        // Delete buffer objects
        glDeleteBuffers(m_Scene.nNumMesh, m_puiVbo);
        glDeleteBuffers(m_Scene.nNumMesh, m_puiIndexVbo);

        // Release Print3D Textures
        //m_Print3D.ReleaseTextures();

        return true;
}

void DrawMesh(int i32NodeIndex)
{
        int i32MeshIndex = m_Scene.pNode[i32NodeIndex].nIdx;
        SPODMesh* pMesh = &m_Scene.pMesh[i32MeshIndex];

        // bind the VBO for the mesh
        glBindBuffer(GL_ARRAY_BUFFER, m_puiVbo[i32MeshIndex]);
        // bind the index buffer, won't hurt if the handle is 0
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_puiIndexVbo[i32MeshIndex]);

        // Enable the vertex attribute arrays
        glEnableVertexAttribArray(VERTEX_ARRAY);
        glEnableVertexAttribArray(NORMAL_ARRAY);
        glEnableVertexAttribArray(TEXCOORD_ARRAY);

        // Set the vertex attribute offsets
        glVertexAttribPointer(VERTEX_ARRAY, 3, GL_FLOAT, GL_FALSE, pMesh->sVertex.nStride, pMesh->sVertex.pData);
        glVertexAttribPointer(NORMAL_ARRAY, 3, GL_FLOAT, GL_FALSE, pMesh->sNormals.nStride, pMesh->sNormals.pData);
        glVertexAttribPointer(TEXCOORD_ARRAY, 2, GL_FLOAT, GL_FALSE, pMesh->psUVW[0].nStride, pMesh->psUVW[0].pData);

        /*
                The geometry can be exported in 4 ways:
                - Indexed Triangle list
                - Non-Indexed Triangle list
                - Indexed Triangle strips
                - Non-Indexed Triangle strips
        */

        if(pMesh->nNumStrips == 0)
        {
                if(m_puiIndexVbo[i32MeshIndex])
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
                        if(m_puiIndexVbo[i32MeshIndex])
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

int car_init_vertices_vbo(SgxRender3DsfmSharedObj *pObj)
{

    CPVRTString ErrorStr;

    // Load the scene
    if(m_Scene.ReadFromFile(c_szSceneFile) != PVR_SUCCESS)
    {
            printf("Couldn't load .pod file\n");
            return false;
    }
    /*
            Initialize VBO data
    */
    if(!LoadVbos(&ErrorStr))
    {
            printf("Couldn't load vbos\n");
            return false;
    }
    /*
            Load textures
    */
    if(!LoadTextures(&ErrorStr))
    {
            printf("Couldn't load textures\n");
    }

    /*
            Load and compile the shaders & link programs
    */
    if(!LoadShaders(&ErrorStr))
    {
            printf("Failed to load shaders\n");
            return false;
    }

    /*
            Set OpenGL ES render states needed for this training course
    */
    // Enable backface culling and depth test
    glCullFace(GL_BACK);
    glEnable(GL_CULL_FACE);

    return 0;
}

void car_draw_vbo(SgxRender3DsfmSharedObj *pObj)
{
    glClear(GL_DEPTH_BUFFER_BIT);
    glDepthFunc(GL_LEQUAL);
    glEnable(GL_DEPTH_TEST);

    // Use shader program
    glUseProgram(m_ShaderProgram.uiId);

    // Sets the scene animation to this frame
    m_Scene.SetFrame(0.0);

    /*
            Get the direction of the first light from the scene.
    */
    PVRTVec4 vLightDirection;
    vLightDirection = m_Scene.GetLightDirection(0);
    // For direction vectors, w should be 0
    vLightDirection.w = 0.0f;

    for (unsigned int i = 0; i < m_Scene.nNumMeshNode; ++i)
    {
            SPODNode& Node = m_Scene.pNode[i];

            PVRTMat4 mWorld;
            mWorld = m_Scene.GetWorldMatrix(Node);

            // Pass the model-view-projection matrix (MVP) to the shader to transform the vertices
            glm::mat4 mModelView, mMVP;
            glm::mat4 mView_car, mWorld_glm;
            mWorld_glm = glm::make_mat4(mWorld.f);

            mView_car = glm::scale(pObj->mView, glm::vec3(pObj->publicObj->carScale));
            mView_car = glm::rotate(mView_car, degreesToRadians(90), glm::vec3(1.0, 0.0, 0.0));
            mView_car = glm::rotate(mView_car, degreesToRadians(180), glm::vec3(0.0, 1.0, 0.0));
            mModelView = mView_car * mWorld_glm;
            mMVP = pObj->mProjection * mModelView;
            glUniformMatrix4fv(m_ShaderProgram.uiMVPMatrixLoc, 1, GL_FALSE, &mMVP[0][0]);

            // Pass the light direction in model space to the shader
            PVRTVec4 vLightDir;
            vLightDir = mWorld.inverse() * vLightDirection;

            PVRTVec3 vLightDirModel = *(PVRTVec3*)&vLightDir;
            vLightDirModel.normalize();

            glUniform3fv(m_ShaderProgram.uiLightDirLoc, 1, &vLightDirModel.x);

            // Load the correct texture using our texture lookup table
            GLuint uiTex = 0;

            if(Node.nIdxMaterial != -1)
                    uiTex = m_puiTextureIDs[Node.nIdxMaterial];

            glActiveTexture(GL_TEXTURE5);
            glBindTexture(GL_TEXTURE_2D, uiTex);

            /*
                    Now that the model-view matrix is set and the materials are ready,
                    call another function to actually draw the mesh.
            */
            DrawMesh(i);
    }

    // Display the demo name using the tools. For a detailed explanation, see the training course IntroducingPVRTools
    //m_Print3D.DisplayDefaultTitle("IntroducingPOD", "", ePVRTPrint3DSDKLogo);
    //m_Print3D.Flush();
    glDisable(GL_DEPTH_TEST);
}


