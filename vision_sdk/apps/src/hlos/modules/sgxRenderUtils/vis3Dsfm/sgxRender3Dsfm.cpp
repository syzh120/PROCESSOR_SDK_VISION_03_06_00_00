/*
 *******************************************************************************
 *
 * Copyright (C) 2013 Texas Instruments Incorporated - http://www.ti.com/
 * ALL RIGHTS RESERVED
 *
 *******************************************************************************
 */

#include "sgxRender3Dsfm.h"
#include "sgxRender3Dsfm_priv.h"
#include "shaders.h"
#include "box.h"
#include "groundMeshLines.h"
#include "billboard.h"
#include "OGLES2Tools.h"

/*For rendering text*/
static CPVRTPrint3D cTryText;

/*definition of the virtual view*/
static float camx = 0.0;
static float camy = 0.0;
static float camz = 640.0f;
static float targetx = 0.0;
static float targety = 0.0;
static float targetz = 0.0;
static float anglex = 0.0f;
static float angley = 0.0f;
static float anglez = 0.0f;
static float aspectRatio; /*aspect ratio of center (ego) view*/

static SgxRender3DsfmSharedObj gShareObj;

int SgxRender3Dsfm_setup(SgxRender3Dsfm_Obj *pubObj)
{

	aspectRatio = 1/(float)SFM_DISP_EGOVIEW_ASPECT_RATIO_INV;

	camx = SFM_DISP_EGOVIEW_PARAM_0;
	camy = SFM_DISP_EGOVIEW_PARAM_1;
	camz = SFM_DISP_EGOVIEW_PARAM_2;
	targetx = SFM_DISP_EGOVIEW_PARAM_3;
	targety = SFM_DISP_EGOVIEW_PARAM_4;
	targetz = SFM_DISP_EGOVIEW_PARAM_5;
	anglex = SFM_DISP_EGOVIEW_PARAM_6;
	angley = SFM_DISP_EGOVIEW_PARAM_7;
	anglez = SFM_DISP_EGOVIEW_PARAM_8;

	gShareObj.publicObj = pubObj;

    //STEP2 - initialise the vertices
    car_init_vertices_vbo(&gShareObj);
    GL_CHECK(car_init_vertices_vbo);
    
    //STEP3 - initialise the individual views
    screen1_sfm_init_vbo();
    GL_CHECK(screen1_sfm_init_vbo);
    
    /*initialize shaders shared by all additional rendering objects*/
    shaders_init(&gShareObj);

    /*initialize additional rendering objects*/
    boxes_init();
    groundMeshLines_init();
#ifdef ENABLE_BILLBOARDS
    	billboard_init();
#endif

    SgxRender3Dsfm_updateView(&gShareObj);
 
    return 0;
}

void SgxRender3Dsfm_renderFrame(SgxRender3Dsfm_Obj *pObj, GLuint *texYuv)
{

	/* PRE-PROCESSING OF INCOMING DATA */
	/***********************************/
	Pose3D_f *M_ew_in = (Pose3D_f *)pObj->egoposePtr;
	Pose3D_f *M_cw_in = (Pose3D_f *)pObj->camposesPtr;
	ObjectBox *objBoxes_in = (ObjectBox *)pObj->boxesPtr;

	//local copies
	static Pose3D_f M_ew;
	static Pose3D_f M_cw[4];
	static Pose3D_f M_wc[4];
	static Pose3D_f M_ec[4];
	static ObjectBox boxes[MAX_BOXES];

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    System_eglCheckGlError("glClearColor");
    glClear(GL_COLOR_BUFFER_BIT);
    System_eglCheckGlError("glClear");

    glDisable(GL_DEPTH_TEST);
#ifdef ENABLE_GLOBAL_BLENDING    
    glEnable(GL_BLEND);
    glBlendEquation(GL_FUNC_ADD);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
#endif    
    //cull
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

	M_ew = *M_ew_in;
	UInt32 ii;
	for (ii=0; ii<4; ii++)
		M_cw[ii] = M_cw_in[ii];
	for (ii=0; ii<4; ii++)
	   pose3Dinv(&M_cw[ii],&M_wc[ii]);
	for (ii=0; ii<4; ii++)
		pose3Dcat(&M_ec[ii],&M_ew, &M_wc[ii]);
	for (ii = 0; ii < MAX_BOXES; ii++)
		boxes[ii] = objBoxes_in[ii];

	//copy boxes into local variable
	UInt32 cnt;
	float boxes_local[MAX_BOXES][24];
	Point3D_f base[MAX_BOXES]; //base points for billboards
	ObjectBox objectBoxes[MAX_BOXES];
	UInt32 numBoxes = 0;
	for (ii = 0; ii < MAX_BOXES; ii++)
    {
		if(boxes[ii].age > 0)
	    {
    		objectBoxes[numBoxes] = boxes[ii];
    		for(cnt=0;cnt<8;cnt++)
    		{
    			boxes_local[numBoxes][3*cnt]   = (float)boxes[ii].box.vertex[cnt].x;
    			boxes_local[numBoxes][3*cnt+1] = (float)boxes[ii].box.vertex[cnt].y;
    			boxes_local[numBoxes][3*cnt+2] = (float)boxes[ii].box.vertex[cnt].z;
    		}
    		base[numBoxes].x = boxes[ii].center.x;
    		base[numBoxes].y = boxes[ii].center.y;
    		base[numBoxes].z = 2*boxes[ii].center.z + SFM_DISP_BILLBOARD_HALF_WIDTH + SFM_DISP_BILLBOARD_OFFSET_Z;

    		numBoxes++;
	    }
	}

	static UInt8 bTileFree[SFM_DISP_MAX_NUM_FREE_TILES];
	updateFreeTiles(boxes, (Pose3D_f *)&M_ew, bTileFree);

	static float boxDistancesToCar[MAX_BOXES];
	getDistancesBetweenBoxesAndCar(objectBoxes,  numBoxes, &M_ew, M_ec, boxDistancesToCar);


	/* EGO VIEW */
	/***************/
	glViewport(260+50+30, 150, 1000, 1000*SFM_DISP_EGOVIEW_ASPECT_RATIO_INV);
	groundMeshLines_draw(&gShareObj, (Pose3D_f *)&M_ew, boxes,bTileFree,0);
	car_draw_vbo(&gShareObj);
	boxes_draw(&gShareObj, boxes_local, numBoxes, (Pose3D_f *)&M_ew, 0);

#ifdef ENABLE_BILLBOARDS
	billboard_draw(&gShareObj, boxes_local, base, numBoxes, (Pose3D_f *)&M_ew, (Pose3D_f *)M_cw, texYuv);
#endif
#ifdef ENABLE_DISTANCE_INFO
	distance_info_draw(&gShareObj, base, numBoxes, (Pose3D_f *)&M_ew, boxDistancesToCar);
#endif

    /* WORLD MAP / RIGHT VIEW  */
    /***************************/
    glViewport(510+880, 160,500.0f,500.0f/SFM_DISP_WORDLMAP_ASPECT_RATIO);
	groundMeshLines_draw(&gShareObj, (Pose3D_f *)&M_ew, boxes, bTileFree,1);
	boxes_draw(&gShareObj, boxes_local, numBoxes, (Pose3D_f *)&M_ew, 1);

	/* LEGEND */
	/**********/
	glViewport(260+50+30, 20, 1000, 160);
	boxes_legend_draw(&gShareObj);
	cTryText.SetTextures(NULL, 1000, 160, 0);
	cTryText.Print3D(13.5f, 55.0f, 0.85f, 0xffffffff, " = Free Space");
	cTryText.Print3D(60.0f, 55.0f, 0.85f, 0xffffffff, " = Occupied Space");
	cTryText.Flush();

	/* INPUT IMAGES */
	/****************/
#define OFFSETX (20)
#define OFFSETY (10)
#define MARGINY (35)
#define HEIGHT (230)
#define WIDTH (279)
#define TEXT_HEIGHT (30)
#define TEXT_SIZE (0.65f)

    /*CHANNEL 0*/
	glViewport(OFFSETX,1080 - OFFSETY-(HEIGHT+MARGINY) ,WIDTH, HEIGHT);
	screen1_sfm_draw_vbo(texYuv[0]);
	boxes_inputImage_draw(&gShareObj, boxes_local, numBoxes, (Pose3D_f *)M_cw, 0);

	glViewport(OFFSETX,1080 -OFFSETY -TEXT_HEIGHT  ,WIDTH, TEXT_HEIGHT);
	cTryText.SetTextures(NULL, WIDTH, TEXT_HEIGHT, 0);
	cTryText.Print3D(0.0f, -(float)(0*TEXT_HEIGHT), TEXT_SIZE, 0xffffffff, "Front Camera:");
	cTryText.Flush();

	/*CHANNEL 1*/
	glViewport(OFFSETX, 1080-OFFSETY-2*(HEIGHT+MARGINY),WIDTH,HEIGHT);
	screen1_sfm_draw_vbo(texYuv[1]);
	boxes_inputImage_draw(&gShareObj, boxes_local, numBoxes, (Pose3D_f *)M_cw, 1);

	glViewport(OFFSETX,1080 -OFFSETY - (HEIGHT+MARGINY)-TEXT_HEIGHT  ,WIDTH, TEXT_HEIGHT);
	cTryText.SetTextures(NULL, WIDTH, TEXT_HEIGHT, 0);
	cTryText.Print3D(0.0f, -(float)(0*TEXT_HEIGHT), TEXT_SIZE, 0xffffffff, "Right Camera:");
	cTryText.Flush();

	/*CHANNEL 2*/
	glViewport(OFFSETX, 1080-OFFSETY-3*(HEIGHT+MARGINY),WIDTH,HEIGHT);
	screen1_sfm_draw_vbo(texYuv[2]);
	boxes_inputImage_draw(&gShareObj, boxes_local, numBoxes, (Pose3D_f *)M_cw, 2);

	glViewport(OFFSETX,1080 -OFFSETY - 2*(HEIGHT+MARGINY)-TEXT_HEIGHT  ,WIDTH, TEXT_HEIGHT);
	cTryText.SetTextures(NULL, WIDTH, TEXT_HEIGHT, 0);
	cTryText.Print3D(0.0f, -(float)(0*TEXT_HEIGHT), TEXT_SIZE, 0xffffffff, "Rear Camera:");
	cTryText.Flush();

	/*CHANNEL 3*/
	glViewport(OFFSETX, 1080-OFFSETY-4*(HEIGHT+MARGINY),WIDTH,HEIGHT);
	screen1_sfm_draw_vbo(texYuv[3]);
	boxes_inputImage_draw(&gShareObj, boxes_local, numBoxes, (Pose3D_f *)M_cw, 3);

	glViewport(OFFSETX,1080 -OFFSETY - 3*(HEIGHT+MARGINY)-TEXT_HEIGHT  ,WIDTH, TEXT_HEIGHT);
	cTryText.SetTextures(NULL, WIDTH, TEXT_HEIGHT, 0);
	cTryText.Print3D(0.0f, -(float)(0*TEXT_HEIGHT), TEXT_SIZE, 0xffffffff, "Left Camera:");
	cTryText.Flush();

	/*TEXT INFO*/
	/***********/
#define MAP_INFO_TEXT_SIZE (0.7f)
#define MAP_INFO_STEPY (10.0f)
#define MAP_INFO_OFFSETY (50.0f)
#define MAP_INFO_OFFSETX (70.0f)

	glViewport(1400, 0, 500, 400);
	cTryText.SetTextures(NULL, 500, 400, 0);
	cTryText.Print3D(0.0f,                  MAP_INFO_OFFSETY, MAP_INFO_TEXT_SIZE, 0xffffffff,"Map Resolution:");
	cTryText.Print3D(0.0f,   MAP_INFO_STEPY+MAP_INFO_OFFSETY, MAP_INFO_TEXT_SIZE, 0xffffffff,"# Tracked Points:");
	cTryText.Print3D(0.0f, 2*MAP_INFO_STEPY+MAP_INFO_OFFSETY, MAP_INFO_TEXT_SIZE, 0xffffffff,"Tracking:");
	cTryText.Print3D(0.0f, 3*MAP_INFO_STEPY+MAP_INFO_OFFSETY, MAP_INFO_TEXT_SIZE, 0xffffffff,"Triangulation:");
	cTryText.Print3D(MAP_INFO_OFFSETX,                  MAP_INFO_OFFSETY, MAP_INFO_TEXT_SIZE, 0xffffffff,"2 cm");
	cTryText.Print3D(MAP_INFO_OFFSETX,   MAP_INFO_STEPY+MAP_INFO_OFFSETY, MAP_INFO_TEXT_SIZE, 0xffffffff,"4 x 900");
	cTryText.Print3D(MAP_INFO_OFFSETX, 2*MAP_INFO_STEPY+MAP_INFO_OFFSETY, MAP_INFO_TEXT_SIZE, 0xffffffff,"30 fps");
	cTryText.Print3D(MAP_INFO_OFFSETX, 3*MAP_INFO_STEPY+MAP_INFO_OFFSETY, MAP_INFO_TEXT_SIZE, 0xffffffff,"5 fps");
	cTryText.Flush();

	return;
}

/*Common/Shared/Utility Functions*/
/********************************/
#define degreesToRadians(x) x*(3.141592f/180.0f)
void  SgxRender3Dsfm_updateView(SgxRender3DsfmSharedObj *pShareObj)
{
    pShareObj->mProjection = glm::perspective(degreesToRadians(40), aspectRatio, 1.0f, 5000.0f);
    pShareObj->mView       = glm::lookAt(
            glm::vec3(camx, camy, camz), // Camera is at (4,3,3), in World Space
            glm::vec3(targetx,targety,targetz), // and looks at the origin
            glm::vec3(0,1,0)  // Head is up (set to 0,-1,0 to look upside-down)
    );
    pShareObj->mView = glm::rotate(pShareObj->mView, anglex, glm::vec3(1.0, 0.0, 0.0));
    pShareObj->mView = glm::rotate(pShareObj->mView, angley, glm::vec3(0.0, 1.0, 0.0));
    pShareObj->mView = glm::rotate(pShareObj->mView, anglez, glm::vec3(0.0, 0.0, 1.0));
}

GLuint SgxRender3Dsfm_loadShader(GLenum shaderType, const char* pSource) {
   GLuint shader = glCreateShader(shaderType);
   if (shader) {
       glShaderSource(shader, 1, &pSource, NULL);
       glCompileShader(shader);
       GLint compiled = 0;
       glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
       if (!compiled) {
           GLint infoLen = 0;
           glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLen);
           if (infoLen) {
               char* buf = (char*) malloc(infoLen);
               if (buf) {
                   glGetShaderInfoLog(shader, infoLen, NULL, buf);
                   D_PRINTF(" GL: Could not compile shader %d:\n%s\n",
                       shaderType, buf);
                   free(buf);
               }
           } else {
               D_PRINTF(" GL: Guessing at GL_INFO_LOG_LENGTH size\n");
               char* buf = (char*) malloc(0x1000);
               if (buf) {
                   glGetShaderInfoLog(shader, 0x1000, NULL, buf);
                   D_PRINTF(" GL: Could not compile shader %d:\n%s\n",
                   shaderType, buf);
                   free(buf);
               }
           }
           glDeleteShader(shader);
           shader = 0;
       }
   }
   return shader;
}

GLuint SgxRender3Dsfm_createProgram(const char* pVertexSource, const char* pFragmentSource) {
   GLuint vertexShader = SgxRender3Dsfm_loadShader(GL_VERTEX_SHADER, pVertexSource);
   if (!vertexShader) {
       return 0;
   }

   GLuint pixelShader = SgxRender3Dsfm_loadShader(GL_FRAGMENT_SHADER, pFragmentSource);
   if (!pixelShader) {
       return 0;
   }

   GLuint program = glCreateProgram();
   if (program) {
       glAttachShader(program, vertexShader);
       System_eglCheckGlError("glAttachShader");
       glAttachShader(program, pixelShader);
       System_eglCheckGlError("glAttachShader");
       glLinkProgram(program);
       GLint linkStatus = GL_FALSE;
       glGetProgramiv(program, GL_LINK_STATUS, &linkStatus);
       if (linkStatus != GL_TRUE) {
           GLint bufLength = 0;
           glGetProgramiv(program, GL_INFO_LOG_LENGTH, &bufLength);
           if (bufLength) {
               char* buf = (char*) malloc(bufLength);
               if (buf) {
                   glGetProgramInfoLog(program, bufLength, NULL, buf);
                   D_PRINTF(" GL: Could not link program:\n%s\n", buf);
                   free(buf);
               }
           }
           glDeleteProgram(program);
           program = 0;
       }
   }
   if(vertexShader && pixelShader && program)
   {
     glDeleteShader(vertexShader);
     glDeleteShader(pixelShader);
    }
   return program;
}
