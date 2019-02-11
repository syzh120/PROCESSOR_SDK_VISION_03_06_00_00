/*
 *******************************************************************************
 *
 * Copyright (C) 2015 Texas Instruments Incorporated - http://www.ti.com/
 * ALL RIGHTS RESERVED
 *
 *******************************************************************************
 */

#include "billboard.h"
#include "OGLES2Tools.h"

/*for printing text*/
static CPVRTPrint3D ctext;

/*** SHADERS  *****/
static const char billboard_vshader[] =
"    attribute vec4 aVertexPosition;\n"
"    attribute vec2 aTextureCoord;\n"
"    varying vec2 oTextureCoord;\n"
"    uniform mat4 uMVMatrix;\n"
"    void main(void) {\n"
"                  gl_Position = uMVMatrix * aVertexPosition;\n"
"               oTextureCoord = aTextureCoord;\n"
"    } \n";

static const char billboard_fshader[] =
" #extension GL_OES_EGL_image_external : require \n"
" precision mediump float;\n "
" uniform samplerExternalOES uSampler0;\n "
" varying vec2 oTextureCoord;\n"
" void main(void) {\n"
"       gl_FragColor = texture2D(uSampler0, oTextureCoord);\n"
"    } \n";

static int billboard_program;
static GLuint billboard_uniform_mvm;
static GLuint billboard_uniform_sampler;
static GLuint billboard_attr_vertex_pos;
static GLuint billboard_attr_tex_coord;

/*VBOs*/
static GLuint billboard_vbo[MAX_BOXES];//Vertex buffer and index buffer
static GLuint billboard_index_vbo;

void billboard_init_shader()
{
    billboard_program = SgxRender3Dsfm_createProgram(billboard_vshader, billboard_fshader);
    if(billboard_program == 0)
    {
       perror("Could not create world map program");
    }

    //set the program
    glUseProgram(billboard_program);
    GL_CHECK(glUseProgram);

    //locate uniforms
    billboard_uniform_mvm = glGetUniformLocation(billboard_program, "uMVMatrix");
    GL_CHECK(glGetUniformLocation);

    //locate uniforms
    billboard_uniform_sampler = glGetUniformLocation(billboard_program, "uSampler0");
    GL_CHECK(glGetUniformLocation);

    //locate attributes
    billboard_attr_vertex_pos = glGetAttribLocation(billboard_program, "aVertexPosition");
    GL_CHECK(glGetAttribLocation);

    //locate attributes
    billboard_attr_tex_coord = glGetAttribLocation(billboard_program, "aTextureCoord");
    GL_CHECK(glGetAttribLocation);
}


int billboard_init()
{
    /* Setup billboard shaders */
    billboard_init_shader();

    /* create buffers */
    glGenBuffers(MAX_BOXES, billboard_vbo);
    glGenBuffers(1, &billboard_index_vbo);

    /* buffer data and indices*/
    int bb;
    for (bb=0; bb<MAX_BOXES;bb++)
    {
    	glBindBuffer(GL_ARRAY_BUFFER, billboard_vbo[bb]);
    	glBufferData(GL_ARRAY_BUFFER, sizeof(float)*(3+2)*4, (void *)0, GL_STREAM_DRAW);
    }

    unsigned short billboard_index_mesh[] = {0, 1, 2, 0, 2, 3};
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, billboard_index_vbo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(billboard_index_mesh), billboard_index_mesh, GL_STATIC_DRAW);

    return 0;
}


/*=======================================================================
*
* Name:        billboard_draw(float boxes[][24], Point3D_f base[],
* 					  UInt32 numBoxes, Pose3D_f *pose_ew,
* 					  Pose3D_f *poses_cw, GLuint *texYuv)
*
* Description: draw billboards on top of boxes
*
=======================================================================*/
void billboard_draw(SgxRender3DsfmSharedObj *pObj, float boxes[][24], Point3D_f base[],  UInt32 numBoxes,
			Pose3D_f *pose_ew, Pose3D_f *poses_cw, GLuint *texYuv)
{
	glm::mat4 mModel_box;
	glm::mat4 scale;
	glm::mat4 mMVP_billboard;

	if (numBoxes==0)
		return;

	scale = glm::scale(glm::mat4(1.0f), glm::vec3(SGXRENDER3DSFM_GRID_CELL_SIZE_INV, SGXRENDER3DSFM_GRID_CELL_SIZE_INV, SGXRENDER3DSFM_GRID_CELL_SIZE_INV));

	float m[16] = {(float)pose_ew->R.xx, (float)pose_ew->R.yx, (float)pose_ew->R.zx, 0,
				(float)pose_ew->R.xy, (float)pose_ew->R.yy, (float)pose_ew->R.zy, 0,
				(float)pose_ew->R.xz, (float)pose_ew->R.yz, (float)pose_ew->R.zz, 0,
				(float)pose_ew->t.x, (float)pose_ew->t.y, (float)pose_ew->t.z, 1};

	/*BILLBOARDS*/
	/******************/
	/*render setup*/
	static int billboard_stride = 5;
	glUseProgram(billboard_program);
	GL_CHECK(glUseProgram);

	glUniform1i(billboard_uniform_sampler, 0);
	glActiveTexture(GL_TEXTURE0);

	/*initializations*/
	UInt32 ii;
	int tex;
	float image_x0, image_y0, image_x1, image_y1;

	glm::mat4 mMV_billboard = glm::make_mat4(m);

	Point3D_f xyzc, xyzw, xyd;
	UInt32 cc;
	Int32 bestCamNo;
	Flouble ratio, ratioBest;
	Flouble xmin, ymin , xmax, ymax;
	UInt32 ldcstatus;
	UInt32 status;

	for (ii = 0; ii < numBoxes; ii++)
	{
		/*Compute pixel coordinates*/
		/******************************/
		/*check from which camera box is seen best*/
		bestCamNo = -1;
		ratioBest = FLOUBLE_MAX;
		for (cc = 0; cc< 4; cc++)
		{
			pose3Dtransform(&poses_cw[cc], &base[ii], &xyzc);
			if (xyzc.z<=0)
				continue;
			ratio = (xyzc.x*xyzc.x+xyzc.y*xyzc.y)/(xyzc.z*xyzc.z);
			if (ratio < ratioBest)
			{
				bestCamNo = (Int32)cc;
				ratioBest = ratio;
			}
		}

		if (bestCamNo < 0 || bestCamNo > 3 )
		{
			status = 1;
			continue;
		}
		else
			status = 0;

		if(status==0)
		{
			/*project box vertices in respective camera
			  and find min & max of projected x & y*/
			xmin = FLOUBLE_MAX; ymin = FLOUBLE_MAX;
			xmax = -FLOUBLE_MAX; ymax = -FLOUBLE_MAX;
			for (cc=0; cc< 8; cc++)
			{
				xyzw.x = boxes[ii][3*cc];
				xyzw.y = boxes[ii][3*cc+1];
				xyzw.z = boxes[ii][3*cc+2];
				pose3Dtransform(&poses_cw[bestCamNo], &xyzw, &xyzc);
				ldcstatus = project3DPointToImage(&xyzc, &xyd);
				if (ldcstatus!=0)
					continue;

				if (xyd.x<xmin)
					xmin = xyd.x;
				if (xyd.y<ymin)
					ymin = xyd.y;
				if (xyd.x>xmax)
					xmax = xyd.x;
				if (xyd.y>ymax)
					ymax = xyd.y;
			}

			tex = bestCamNo;
			image_x0 = (float)(xmin/pObj->publicObj->inFramesWidth);
			image_x0 = image_x0 < 0 ? 0 : image_x0;
			image_x0 = image_x0 > 1 ? 1 : image_x0;
			image_x1 = (float)(xmax/pObj->publicObj->inFramesWidth);
			image_x1 = image_x1 < 0 ? 0 : image_x1;
			image_x1 = image_x1 > 1 ? 1 : image_x1;
			image_y0 = (float)(ymin/pObj->publicObj->inFramesHeight);
			image_y0 = image_y0 < 0 ? 0 : image_y0;
			image_y0 = image_y0 > 1 ? 1 : image_y0;
			image_y1 = (float)(ymax/pObj->publicObj->inFramesHeight);
			image_y1 = image_y1 < 0 ? 0 : image_y1;
			image_y1 = image_y1 > 1 ? 1 : image_y1;
		}
		else
		{
			tex = 0;
			image_x0 = 0;
			image_x1 = 0;
			image_y0 = 0;
			image_y1 = 0;
		}

		/*adjust angle at which billboard is seen*/
		Pose3D_f P_hat;
		Matrix3D_f R_hat;
		Point3D_f t_hat;
		Point3D_f center_e;
		Point3D_f center_w;
		center_w = base[ii];
		pose3Dtransform(pose_ew, &center_w, &center_e);

		Matrix3D_f R_ev;
		R_ev.xx = (Flouble)pObj->mView[0][0]; R_ev.xy = (Flouble)pObj->mView[0][1]; R_ev.xz = (Flouble)pObj->mView[0][2];
		R_ev.yx = (Flouble)pObj->mView[1][0]; R_ev.yy = (Flouble)pObj->mView[1][1]; R_ev.yz = (Flouble)pObj->mView[1][2];
		R_ev.zx = (Flouble)pObj->mView[2][0]; R_ev.zy = (Flouble)pObj->mView[2][1]; R_ev.zz = (Flouble)pObj->mView[2][2];

		Matrix3D_f R_fix;
		matrix3Dinit(&R_fix, 0);
		R_fix.xy = 1;
		R_fix.yz = 1;
		R_fix.zx = 1;

		matrix3Dcat(&R_ev, &R_fix, &R_hat);

		Matrix3D_f R_diff = R_hat;
		R_diff.xx-=1;
		R_diff.yy-=1;
		R_diff.zz-=1;
		matrix3Dtransform(&R_diff, &center_e, &t_hat);
		point3Dnegate(&t_hat);

		P_hat.R = R_hat;
		P_hat.t = t_hat;

		float mtrack[16] = {(float)P_hat.R.xx, (float)P_hat.R.yx, (float)P_hat.R.zx, 0,
						(float)P_hat.R.xy, (float)P_hat.R.yy, (float)P_hat.R.zy, 0,
						(float)P_hat.R.xz, (float)P_hat.R.yz, (float)P_hat.R.zz, 0,
						(float)P_hat.t.x, (float)P_hat.t.y, (float)P_hat.t.z, 1};
		glm::mat4 track = glm::make_mat4(mtrack);

		mMVP_billboard = pObj->mProjection * pObj->mView * scale * track * mMV_billboard;
		glUniformMatrix4fv(billboard_uniform_mvm, 1, GL_FALSE, &mMVP_billboard[0][0]);

		/*setup billboard mesh*/
		float billboard_mesh[] = {
			base[ii].x,
			base[ii].y + SFM_DISP_BILLBOARD_HALF_WIDTH,
			base[ii].z - SFM_DISP_BILLBOARD_HALF_WIDTH,
			image_x1, image_y1,

			base[ii].x,
			base[ii].y + SFM_DISP_BILLBOARD_HALF_WIDTH,
			base[ii].z + SFM_DISP_BILLBOARD_HALF_WIDTH,
			image_x1, image_y0,

			base[ii].x,
			base[ii].y - SFM_DISP_BILLBOARD_HALF_WIDTH,
			base[ii].z + SFM_DISP_BILLBOARD_HALF_WIDTH,
			image_x0, image_y0,

			base[ii].x,
			base[ii].y - SFM_DISP_BILLBOARD_HALF_WIDTH,
			base[ii].z - SFM_DISP_BILLBOARD_HALF_WIDTH,
			image_x0, image_y1
		};

		/*render*/
        glBindBuffer(GL_ARRAY_BUFFER, billboard_vbo[ii]);
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(billboard_mesh), (void *)billboard_mesh);
		glVertexAttribPointer(billboard_attr_vertex_pos, 3, GL_FLOAT, GL_FALSE, (billboard_stride)*sizeof(float), 0);
		glVertexAttribPointer(billboard_attr_tex_coord, 2, GL_FLOAT, GL_FALSE, (billboard_stride)*sizeof(float), (GLvoid*)(3*sizeof(float)));
		GL_CHECK(glVertexAttribPointer);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, billboard_index_vbo);
		GL_CHECK(glBufferData);

		glEnableVertexAttribArray(billboard_attr_vertex_pos);
		glEnableVertexAttribArray(billboard_attr_tex_coord);

		glBindTexture(GL_TEXTURE_EXTERNAL_OES, texYuv[tex]);
		GL_CHECK(glBindTexture);

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT,  0);
		GL_CHECK(glDrawElements);
	}
}

/*=======================================================================
*
* Name:  void distance_info_draw(Point3D_f base[],  UInt32 numBoxes,
* 					Pose3D_f *pose, float dists[])
*
* Description: print distance between car chassis and box on top
* 				of boxes in ego view
*
=======================================================================*/
void distance_info_draw(SgxRender3DsfmSharedObj *pObj, Point3D_f base[],  UInt32 numBoxes,
							Pose3D_f *pose, float dists[])
{
	ctext.SetTextures(NULL, 1000, 700, 0);
	
	if (numBoxes==0)
			return;

	float m[16] = {(float)pose->R.xx, (float)pose->R.yx, (float)pose->R.zx, 0,
						(float)pose->R.xy, (float)pose->R.yy, (float)pose->R.zy, 0,
						(float)pose->R.xz, (float)pose->R.yz, (float)pose->R.zz, 0,
						(float)pose->t.x, (float)pose->t.y, (float)pose->t.z, 1};

	glm::mat4 mModel = glm::make_mat4(m);
	glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(SGXRENDER3DSFM_GRID_CELL_SIZE_INV, SGXRENDER3DSFM_GRID_CELL_SIZE_INV, SGXRENDER3DSFM_GRID_CELL_SIZE_INV));
	glm::mat4 M_pvm = pObj->mProjection * pObj->mView * scale * mModel;

	Pose3D_f M;
	M.R.xx = M_pvm[0][0]; M.R.xy = M_pvm[1][0]; M.R.xz = M_pvm[2][0];
	M.R.yx = M_pvm[0][1]; M.R.yy = M_pvm[1][1]; M.R.yz = M_pvm[2][1];
	M.R.zx = M_pvm[0][2]; M.R.zy = M_pvm[1][2]; M.R.zz = M_pvm[2][2];
	M.t.x =  M_pvm[3][0]; M.t.y =  M_pvm[3][1]; M.t.z =  M_pvm[3][2];

	Pose3D_f M_we;
	pose3Dinv(pose, &M_we);

	Point3D_f p_proj;
	Point2D_f p_img;
	UInt32 nn;
	float distCm;
	char str[10];

	for (nn=0; nn<numBoxes; nn++)
	{
		/*point in viewport*/
		pose3Dtransform(&M, &base[nn], &p_proj);
		p_img.x = (p_proj.x/p_proj.z + 1)*50;
		p_img.y = 100-(p_proj.y/p_proj.z + 1)*50;

		/*distance*/
		distCm = dists[nn]*0.1f;
		if (distCm>999.9f)
			distCm = 999.9f;

		/*print*/
		sprintf(str, "%3.1fcm", distCm);
		ctext.Print3D(p_img.x, p_img.y, 0.8f, 0xffffffff, str);
	}
	ctext.Flush();


}

/*=======================================================================
*
* Name:  void getDistancesBetweenBoxesAndCar(ObjectBox boxes[],
* 					 UInt32 numBoxes, Pose3D_f *pose_ew,
* 					 Pose3D_f pose_ec[], float dists[])
*
* Description: compute distance between car chassis and boxes
*
=======================================================================*/
void getDistancesBetweenBoxesAndCar(ObjectBox boxes[],  UInt32 numBoxes,
		Pose3D_f *pose_ew, Pose3D_f pose_ec[], float dists[])
{
	Point3D_f car_e[4]; /*car rectangle in ego coords*/
	Point3D_f box_e[4]; /*box rectangle in ego coords*/
	Point3D_f boxcenter_e;
	Pose3D_f pose_we;
	Int32 zone; /*which zone does the box lie in?*/

	/*car box constructed from camera locations*/
    car_e[0].x =  pose_ec[3].t.x;  car_e[0].y = pose_ec[2].t.y; car_e[0].z = 0;
    car_e[1].x =  pose_ec[3].t.x;  car_e[1].y = pose_ec[0].t.y; car_e[1].z = 0;
    car_e[2].x =  pose_ec[1].t.x;  car_e[2].y = pose_ec[0].t.y; car_e[2].z = 0;
    car_e[3].x =  pose_ec[1].t.x;  car_e[3].y = pose_ec[2].t.y; car_e[3].z = 0;

    pose3Dinv(pose_ew, &pose_we);

    UInt32 ii, bb;
    for  (bb=0; bb<numBoxes; bb++)
    {
    	/*transform boxes to ego coordinates*/
    	pose3Dtransform(pose_ew, &boxes[bb].center, &boxcenter_e);
    	boxcenter_e.z = 0;
    	for (ii=0; ii<4; ii++)
    	{
    		pose3Dtransform(pose_ew, &boxes[bb].box.vertex[ii], &box_e[ii]);
    		box_e[ii].z = 0;
    	}

    	/*get zone that box lies in*/
    	zone = getZone(boxcenter_e, car_e);

    	/*get distance based on zone*/
    	if (zone == 8)
    		dists[bb] = 0;
    	else
    		dists[bb] = getDistanceCustom(box_e, car_e, zone);
    }

    return;
}

/*=======================================================================
*
* Name:  Flouble getDistanceCustom(Point3D_f box_e[],
* 						Point3D_f car_e[], Int32 zone)
*
* Description: compute distance between car chassis and box given
* 				zone that box lies in
*
=======================================================================*/
Flouble getDistanceCustom(Point3D_f box_e[], Point3D_f car_e[], Int32 zone)
{
	UInt32 ii;

	if (zone<4)
	{
		Flouble carCoord;
		Flouble boxCoord[4];
		switch (zone)
		{
			case 0:
				carCoord = car_e[2].y;
				for (ii=0;ii<4;ii++)
					boxCoord[ii] = box_e[ii].y;
				break;
			case 1:
				carCoord = car_e[2].x;
				for (ii=0;ii<4;ii++)
					boxCoord[ii] = box_e[ii].x;
				break;
			case 2:
				carCoord = car_e[2].y;
				for (ii=0;ii<4;ii++)
					boxCoord[ii] = -box_e[ii].y;
				break;
			case 3:
				carCoord = car_e[2].x;
				for (ii=0;ii<4;ii++)
					boxCoord[ii] = -box_e[ii].x;
				break;
			default:
				return 0;
		}

		Flouble minDist = FLOUBLE_MAX;
		Flouble tmpDist;
		for (ii=0;ii<4;ii++)
		{
			tmpDist = boxCoord[ii] - carCoord;
			if (tmpDist < minDist)
				minDist = tmpDist;
		}
		if (minDist < 0)
			return 0;
		else
			return minDist;
	}
	else
	{
		Point3D_f carpoint;
		switch (zone)
		{
			case 4:
				carpoint = car_e[2];
				break;
			case 5:
				carpoint = car_e[3];
				break;
			case 6:
				carpoint = car_e[0];
				break;
			case 7:
				carpoint = car_e[1];
				break;
			default:
				return 0;
		}

		Flouble minDist = FLOUBLE_MAX;
		Flouble tmpDist;
		Int32 zone;
		for (ii=0;ii<4;ii++)
		{
			zone = getZone(box_e[ii], car_e);
			if (zone==8)
				tmpDist = 0;
			else
				tmpDist = dist3D(&box_e[ii], &carpoint);

			if (tmpDist < minDist)
				minDist = tmpDist;
		}
		return minDist;
	}

	return 0;


}

/*=======================================================================
*
* Name:  Int32 getZone(Point3D_f p_e, Point3D_f car_e[])
*
* Description: get zone for a point for a given point
*
=======================================================================*/
Int32 getZone(Point3D_f p_e, Point3D_f car_e[])
{
	Int32 zone;
    if (p_e.x < car_e[0].x)
    {
    		if (p_e.y < car_e[0].y)
    		{
    			zone = 6;
    		}
    		else if (p_e.y > car_e[2].y)
    		{
    			zone = 7;
    		}
    		else
    		{
    			zone = 3;
    		}
    }
    else if (p_e.x > car_e[2].x)
    {
    		if (p_e.y < car_e[0].y)
    		{
    			zone = 5;
    		}
    		else if (p_e.y > car_e[2].y)
    		{
    			zone = 4;
    		}
    		else
    		{
    			zone = 1;
    		}
    }
    else
    {
    		if (p_e.y < car_e[0].y)
    		{
    			zone = 2;
    		}
    		else if (p_e.y > car_e[2].y)
    		{
    			zone = 0;
    		}
    		else
    		{
    			zone = 8;
    		}
    }

    return zone;
}


