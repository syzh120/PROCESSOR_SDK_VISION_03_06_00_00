#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include "render.h"
#include "ldc_config.h"
#include "lens_distortion_correction.h"
#include "lens_distortion_correction.cxx"

#define min(a,b) (((a)<(b))?(a):(b))
#define max(a,b) (((a)>(b))?(a):(b))


#define QUADBASED
#define NUM_CAMERAS 4
#define CALMAT_T_SHIFT 10
#define CALMAT_R_SHIFT 30

#define PI 3.14159265

#if !defined(SRV_LDC_LENS_BIN_FILE)
#define SRV_LDC_LENS_BIN_FILE "./LENS.BIN"
#endif
#if !defined(SRV_CALMAT_BIN_FILE)
#define SRV_CALMAT_BIN_FILE "./CALMAT.BIN"
#endif

#define OVERLAP_REGION_ANGULAR_WIDTH_DEGREES 10.0f

float temp_lochor;
float temp_locver;
int32_t calmat[3*4*4];
uint16_t distortionCenters[2 * NUM_CAMERAS];
uint16_t focalLength[NUM_CAMERAS];
uint16_t camWidth;
uint16_t camHeight;
LensDistortionCorrection ldc[NUM_CAMERAS];
glm::mat4 mRT[NUM_CAMERAS];
glm::mat4 mK[NUM_CAMERAS];
glm::mat4 mP[NUM_CAMERAS]; //[P] = [K][RT]
glm::vec3 vTc[NUM_CAMERAS];
glm::vec3 vTw[NUM_CAMERAS];
glm::mat4 mRw[NUM_CAMERAS];
glm::mat4 mRTw[NUM_CAMERAS];
/*===============================================================================
*
* Name:        svProjectiveTransform_float()
*
* Description: Transform a given world point according to camera co-ordinates
*
*
* Input:
*   sv:        Handle for the SV structure
*
* Returns:
*
* Effects:
*
===============================================================================*/
void svProjectiveTransform_float(uint32_t regmark, float *SV_origin, float X, float Y, float Z)
{
    float x_norm, y_norm;

    glm::vec4 vIn;
    glm::vec4 vOut = glm::vec4(0.0f);
    glm::vec4 vOut1 = glm::vec4(0.0f);
    vIn = glm::vec4(X, Y, Z, 1.0f);

    vOut = mP[regmark] * vIn;
    if ( vOut.z < 0)
	    vOut.z *= (-1);
    x_norm = (vOut.x) / (vOut.z);
    y_norm = (vOut.y) / (vOut.z);
    temp_lochor = x_norm * 16;
    temp_locver = y_norm * 16;
}

/*===============================================================================
*
* Name:        svFisheyeTransform_distort_LDC()
*
* Description: Transform a given point according to the given fisheye parameters
*
*
* Input:
*   sv:        Handle for the SV structure
*
* Returns:
*
* Effects:
*
===============================================================================*/
void svFisheyeTransform_distort_LDC(uint32_t regmark)
{
    dtype point_u[2];
    dtype point_d[2];

    point_u[0] = (dtype)temp_lochor / (dtype)16;
    point_u[1] = (dtype)temp_locver / (dtype)16;

    // Convert pixel location from undistorted to distorted location
    Int32 status = LDC_UndistToDist(&ldc[regmark], point_u, point_d);

    if (status == LDC_STATUS_FAIL)
    {
        printf("WARNING: LDC stepped out of bounds");
    }

    temp_locver = (float)(point_d[1] * 16);
    temp_lochor = (float)(point_d[0] * 16);

    // Repeat pixels if we try to access a pixel outside the camera input image
    if (temp_locver < 0)
        temp_locver = 0;
    if (temp_lochor < 0)
        temp_lochor = 0;
    if (temp_locver >((camHeight - 2) << 4))
        temp_locver = ((camHeight- 2) << 4);
    if (temp_lochor >((camWidth - 2) << 4))
        temp_lochor = ((camWidth - 2) << 4);
}

void lut_add_entry(srv_lut_t *entry,
		float X, float Y, float Z,
		float step_size, float *SV_origin,
		uint32_t cam_id1, uint32_t cam_id2,
		float cornerx, float cornery)
{
    float angle_corner_degrees;
    float angle_point_degrees;
    float angle_offset_degrees; // Angle offset of point from corner line

    entry->x = round(X/step_size); // X co-ordinate
    entry->y = round(Y/step_size); // Y co-ordinate
    entry->z = Z;

    svProjectiveTransform_float(cam_id1, SV_origin, X, Y, Z);
    svFisheyeTransform_distort_LDC(cam_id1);  /* AYK */

    entry->u1 = temp_locver;
    entry->v1 = temp_lochor;

    svProjectiveTransform_float(cam_id2, SV_origin, X, Y, Z);
    svFisheyeTransform_distort_LDC(cam_id2);  /* AYK */

    entry->u2 = temp_locver;
    entry->v2 = temp_lochor;

#ifdef SRV_INTERLEAVED_BLEND
    angle_corner_degrees = atan2(cornery,cornerx) * 180.0/PI;
    if(entry->y == (GL_VERTEX_DATATYPE)0)
    {
        if(entry->x >= 0)
	{
		angle_point_degrees = 0;
	}
	else
	{
		angle_point_degrees = 180;
	}
    }
    else
    {
	angle_point_degrees = atan2((float)entry->y,(float)entry->x) * 180.0/PI;
    }
    angle_offset_degrees = angle_point_degrees - angle_corner_degrees;

    if(angle_offset_degrees > 180.0)
    {
	angle_offset_degrees -= 360.0;
    }
    if(fabsf(angle_offset_degrees) < OVERLAP_REGION_ANGULAR_WIDTH_DEGREES)
    {
        entry->blend1 = 128 - int(127.0 * angle_offset_degrees/OVERLAP_REGION_ANGULAR_WIDTH_DEGREES);
	entry->blend2 = 255 - entry->blend1;
    }
    else if((angle_offset_degrees >= 0.0))
    {
	entry->blend1 = 0;
	entry->blend2 = 255;
    }
    else
    {
	entry->blend1 = 255;
	entry->blend2 = 0;
    }
#endif //SRV_INTERLEAVED_BLEND
}

void blend_lut_add_entry(srv_blend_lut_t *entry,
		float X, float Y,
		float cornerx, float cornery)
{
    float angle_corner_degrees;
    float angle_point_degrees;
    float angle_offset_degrees; // Angle offset of point from corner line
    GL_VERTEX_DATATYPE x, y;

    x = round(X); // X co-ordinate
    y = round(Y); // Y co-ordinate

    angle_corner_degrees = atan2(cornery,cornerx) * 180.0/PI;
    if(y == (GL_VERTEX_DATATYPE)0)
    {
        if(x >= 0)
	{
		angle_point_degrees = 0;
	}
	else
	{
		angle_point_degrees = 180;
	}
    }
    else
    {
	angle_point_degrees = atan2((float)y,(float)x) * 180.0/PI;
    }
    angle_offset_degrees = angle_point_degrees - angle_corner_degrees;

    if(angle_offset_degrees > 180.0)
    {
	angle_offset_degrees -= 360.0;
    }
    if(fabsf(angle_offset_degrees) < OVERLAP_REGION_ANGULAR_WIDTH_DEGREES)
    {
        entry->blend1 = 128 - int(127.0 * angle_offset_degrees/OVERLAP_REGION_ANGULAR_WIDTH_DEGREES);
	entry->blend2 = 255 - entry->blend1;
    }
    else if((angle_offset_degrees >= 0.0))
    {
	entry->blend1 = 0;
	entry->blend2 = 255;
    }
    else
    {
	entry->blend1 = 255;
	entry->blend2 = 0;
    }
}

float X1max = 1500, X1min = 1000, Y1max = 500, Y1min = 450, Z1 = 100;
float X2max = -1000, X2min = -1400, Y2max = -300, Y2min = -400, Z2 = 50;

int srv_generate_lut (uint32_t width, uint32_t height,
		uint32_t camw, uint32_t camh,
		uint32_t subx, uint32_t suby, srv_lut_t *lut)
{
    uint16_t i,j,j_offset,i_offset;
    float X,Y,Z;
    uint32_t count=0;
    float maxZ=0;

    #ifndef QUADBASED
    uint16_t ind_i,ind_j;
    //uint32_t img_count=0;
    #else
    uint32_t quad_count1=0, quad_count2=0, quad_count3=0, quad_count4=0;
    uint32_t no_of_elems = 9;
    #endif

    float rel_dist_bowl=0;

    // TBD User parameter .. needs to go to alg_plugin
    // For rectangular base
    int32_t offsetXleft = -400;
    int32_t offsetXright = 400;
    //uint32_t offsetY = 150;
    int32_t offsetYfront = -400;
    int32_t offsetYback = 400;
    int32_t offsetXmin;
    int32_t offsetYmin;

    int32_t doll = 72;
    int32_t jeep = 14;

    uint32_t max_dist=0;

    // Grid cell size in real-world measrements
    float step_size = 5; // in mm
    float SV_origin[2] = {0,0};
    float FC_loc[2] = {0,0};
    float BC_loc[2] = {0,0};
    float cam_distance=0;
    float rshift;
    float tshift;
    srv_lut_t *lut_region;

    // Calmat bin file
    FILE *f_calmatbin;
    //LDC binary file
    FILE *f_ldcbin;
    ldc_lensParameters lp;
    size_t bytes_read;


    rshift = (float)pow(2, CALMAT_R_SHIFT);
    tshift = (float)pow(2, CALMAT_T_SHIFT);

    camHeight = (uint16_t)camh;
    camWidth = (uint16_t)camw;

    //Calibration matrix
    f_calmatbin = fopen(SRV_CALMAT_BIN_FILE, "rb");
    if(!f_calmatbin)
    {
	    fprintf(stderr, "Fatal: Unable to open calibtable binary file: %s\n",
			    SRV_CALMAT_BIN_FILE);
	    return -1;
    }

    // FIXME: This is not the right way. We need to read the header
    fseek(f_calmatbin, 32 * 4, 0);
    bytes_read = fread((void *)&calmat, sizeof(int32_t), 3*4*4, f_calmatbin);
    if(bytes_read <= 0)
    {
	    fprintf(stderr, "Fatal: Cannot read calibration table from: %s\n",
			    SRV_CALMAT_BIN_FILE);
	    fclose(f_calmatbin);
	    return -1;
    }
    // Don't need the file anymore
    fclose(f_calmatbin);

    for(count=0;count<NUM_CAMERAS;count++)
    {
	float xc, yc, zc;
        // -R't to calculate origin (>>20 for both t and R because they are multiplied)

        //SV_origin[0] += - ( ( sv->persmat[0+12*count]*((sv->persmat[9+12*count])>>20) + sv->persmat[1+12*count]*((sv->persmat[10+12*count])>>20) + sv->persmat[2+12*count]*((sv->persmat[11+12*count])>>20) )>>20 )/4;
        //SV_origin[1] += - ( ( sv->persmat[3+12*count]*((sv->persmat[9+12*count])>>20) + sv->persmat[4+12*count]*((sv->persmat[10+12*count])>>20) + sv->persmat[5+12*count]*((sv->persmat[11+12*count])>>20) )>>20 )/4;

        // Typecast to floats

        xc = -(((float)(calmat[0 + 12 * count]) / pow(2, CALMAT_R_SHIFT)) * ((float)(calmat[9 + 12 * count]) / pow(2, CALMAT_T_SHIFT))\
                               + ((float)(calmat[1 + 12 * count]) / pow(2, CALMAT_R_SHIFT)) * ((float)(calmat[10 + 12 * count]) / pow(2, CALMAT_T_SHIFT))\
                               + ((float)(calmat[2 + 12 * count]) / pow(2, CALMAT_R_SHIFT)) * ((float)(calmat[11 + 12 * count]) / pow(2, CALMAT_T_SHIFT)));
	SV_origin[0] += xc/NUM_CAMERAS;

        yc = -(((float)(calmat[3 + 12 * count]) / pow(2, CALMAT_R_SHIFT)) * ((float)(calmat[9 + 12 * count]) / pow(2, CALMAT_T_SHIFT))\
                               + ((float)(calmat[4 + 12 * count]) / pow(2, CALMAT_R_SHIFT)) * ((float)(calmat[10 + 12 * count]) / pow(2, CALMAT_T_SHIFT))\
                               + ((float)(calmat[5 + 12 * count]) / pow(2, CALMAT_R_SHIFT)) * ((float)(calmat[11 + 12 * count]) / pow(2, CALMAT_T_SHIFT)));
	SV_origin[1] += yc/NUM_CAMERAS;

        zc = -(((float)(calmat[6 + 12 * count]) / pow(2, CALMAT_R_SHIFT)) * ((float)(calmat[9 + 12 * count]) / pow(2, CALMAT_T_SHIFT))\
                               + ((float)(calmat[7 + 12 * count]) / pow(2, CALMAT_R_SHIFT)) * ((float)(calmat[10 + 12 * count]) / pow(2, CALMAT_T_SHIFT))\
                               + ((float)(calmat[8 + 12 * count]) / pow(2, CALMAT_R_SHIFT)) * ((float)(calmat[11 + 12 * count]) / pow(2, CALMAT_T_SHIFT)));

	vTc[count] = glm::vec3(xc, yc, zc);

        printf("SV_Origin :%f\t%f\n", SV_origin[0], SV_origin[1]);
    }

    //Load LDC parameters from lens binary
    f_ldcbin = fopen(SRV_LDC_LENS_BIN_FILE, "rb");
    if(!f_ldcbin)
    {
	    fprintf(stderr, "Fatal: Unable to open lens parameters binary file: %s\n",
			    SRV_LDC_LENS_BIN_FILE);
	    return -1;
    }
    bytes_read = fread((void *)&lp, sizeof(ldc_lensParameters), 1, f_ldcbin);
    if(bytes_read <= 0)
    {
	    fprintf(stderr, "Fatal: Cannot read lens parameters from: %s\n",
			    SRV_LDC_LENS_BIN_FILE);
            fclose(f_ldcbin);
	    return -1;
    }

    // Don't need the file anymore
    fclose(f_ldcbin);

    for(j = 0; j < lp.ldcLUT_numCams; j++)
    {
	    focalLength[j] = lp.ldcLUT_focalLength;
	    distortionCenters[2*j] = (uint16_t)lp.ldcLUT_distortionCenters[2*j + 1];
	    distortionCenters[2*j + 1] = (uint16_t)lp.ldcLUT_distortionCenters[2*j];
	    //Initialize LDC
	    LDC_Init(&ldc[j], (dtype)lp.ldcLUT_distortionCenters[2 * j], (dtype)lp.ldcLUT_distortionCenters[2 * j + 1], lp.ldcLUT_focalLength,
			    NULL, 0, 0,
			    lp.ldcLUT_U2D_table, lp.ldcLUT_U2D_length, lp.ldcLUT_U2D_step);
	    mRT[j] = glm::mat4((float)(calmat[j * 12 + 0])/rshift, (float)(calmat[j * 12 + 1])/rshift, (float)(calmat[j * 12 + 2])/rshift, 0.0f,
			       (float)(calmat[j * 12 + 3])/rshift, (float)(calmat[j * 12 + 4])/rshift, (float)(calmat[j * 12 + 5])/rshift, 0.0f,
			       (float)(calmat[j * 12 + 6])/rshift, (float)(calmat[j * 12 + 7])/rshift, (float)(calmat[j * 12 + 8])/rshift, 0.0f,
			       (float)(calmat[j * 12 + 9])/tshift, (float)(calmat[j * 12 + 10])/tshift, (float)(calmat[j * 12 + 11])/tshift, 1.0f);
	    mRT[j] = glm::translate(mRT[j], glm::vec3((float) SV_origin[0], (float)SV_origin[1], 0.0f));
	    mK[j] = glm::mat4((float)(focalLength[j]), 0.0f, 0.0f, 0.0f,
			       0.0f, (float)(focalLength[j]), 0.0f, 0.0f,
			       (float)distortionCenters[2 * j + 1], (float)distortionCenters[2 * j], 1.0f, 0.0f,
			       0.0f, 0.0f, 0.0f, 1.0f);
	    mP[j] = mK[j] * mRT[j];

    }
	printf("Initialized mRT\n");

    // Calculate step_size from calmat (scale correction)

        // Front camera
        count =0;
        // Typecast to floats
        FC_loc[0] = -(((float)(calmat[0 + 12 * count]) / pow(2, CALMAT_R_SHIFT)) * ((float)(calmat[9 + 12 * count]) / pow(2, CALMAT_T_SHIFT))\
                               + ((float)(calmat[1 + 12 * count]) / pow(2, CALMAT_R_SHIFT)) * ((float)(calmat[10 + 12 * count]) / pow(2, CALMAT_T_SHIFT))\
                               + ((float)(calmat[2 + 12 * count]) / pow(2, CALMAT_R_SHIFT)) * ((float)(calmat[11 + 12 * count]) / pow(2, CALMAT_T_SHIFT)));

        FC_loc[1] = -(((float)(calmat[3 + 12 * count]) / pow(2, CALMAT_R_SHIFT)) * ((float)(calmat[9 + 12 * count]) / pow(2, CALMAT_T_SHIFT))\
                               + ((float)(calmat[4 + 12 * count]) / pow(2, CALMAT_R_SHIFT)) * ((float)(calmat[10 + 12 * count]) / pow(2, CALMAT_T_SHIFT))\
                               + ((float)(calmat[5 + 12 * count]) / pow(2, CALMAT_R_SHIFT)) * ((float)(calmat[11 + 12 * count]) / pow(2, CALMAT_T_SHIFT)));


        // Back camera
        count=2;
        // Typecast to floats
        BC_loc[0] = -(((float)(calmat[0 + 12 * count]) / pow(2, CALMAT_R_SHIFT)) * ((float)(calmat[9 + 12 * count]) / pow(2, CALMAT_T_SHIFT))\
                               + ((float)(calmat[1 + 12 * count]) / pow(2, CALMAT_R_SHIFT)) * ((float)(calmat[10 + 12 * count]) / pow(2, CALMAT_T_SHIFT))\
                               + ((float)(calmat[2 + 12 * count]) / pow(2, CALMAT_R_SHIFT)) * ((float)(calmat[11 + 12 * count]) / pow(2, CALMAT_T_SHIFT)));

        BC_loc[1] = -(((float)(calmat[3 + 12 * count]) / pow(2, CALMAT_R_SHIFT)) * ((float)(calmat[9 + 12 * count]) / pow(2, CALMAT_T_SHIFT))\
                               + ((float)(calmat[4 + 12 * count]) / pow(2, CALMAT_R_SHIFT)) * ((float)(calmat[10 + 12 * count]) / pow(2, CALMAT_T_SHIFT))\
                               + ((float)(calmat[5 + 12 * count]) / pow(2, CALMAT_R_SHIFT)) * ((float)(calmat[11 + 12 * count]) / pow(2, CALMAT_T_SHIFT)));


// Front to back camera distance gives scale of car

    cam_distance = sqrt( (FC_loc[0]-BC_loc[0])*(FC_loc[0]-BC_loc[0]) + (FC_loc[1]-BC_loc[1])*(FC_loc[1]-BC_loc[1]) );

    // Step_size divides the length of the vehicle into hundred grid points. (100 can be user defined parameter)
    step_size = cam_distance/100;

    #ifdef FLATWORDVIEW
    maxZ = 0; //in mm
    #else
   // maxZ = 30 * 150*step_size; //in mm
    maxZ = 150*step_size; //in mm
    #endif

    for(j = 0; j < NUM_CAMERAS; j++)
    {
	    glm::mat4 mTw;
	    mRw[j] = glm::mat4(glm::mat3(glm::transpose(mRT[j])));
	    vTw[j] = (vTc[j] - glm::vec3((float)SV_origin[0], (float)SV_origin[1], 0.0f))/(float)step_size;
	    mTw = glm::translate(glm::mat4(1.0f),vTw[j]);
	    mRTw[j] = mTw * mRw[j];
    }

    // Max dist set to diagonal
    //max_dist = sqrt( ((height-offsetX)*(height-offsetX)) + ((width-offsetY)*(width-offsetY)) );
    max_dist = sqrt( ((height/2)*(height/2)) + ((width/2)*(width/2)) );

    /*

    view id 1 is Dominant Image
    view id 2 is Secondary Image


                                    view0
                        |-----------------------|
                        | Quadrant1 | Quadrant2 |
                    view3   |-----------------------| view1
                                | Quadrant4|  Quadrant3 |
                        |-----------------------|
                                view2


    GALUT format:

    For each output grid vertex the followind are stored in the array:

    0 - O/p X co-ordinate
    1 - O/p Y co-ordinate
    2 - O/p Z co-ordinate
    3 - Image 1 x co-ordinate (Dominant view)
    4 - Image 1 y co-ordinate (Dominant view)
    5 - Image 2 x co-ordinate
    6 - Image 2 y co-ordinate
    7 - View id 1 (Dominant view)
    8 - View id 2


    */

    quad_count1 = 0;//0*no_of_elems *( (1+width/2/subx) * (1+height/2/suby));
    quad_count2 = 0;//1*no_of_elems *( (1+width/2/subx) * (1+height/2/suby));
    quad_count3 = 0;//2*no_of_elems *( (1+width/2/subx) * (1+height/2/suby));
    quad_count4 = 0;//3*no_of_elems *( (1+width/2/subx) * (1+height/2/suby));

    offsetXmin = min(offsetXright, offsetXleft);
    offsetYmin = min(offsetYfront, offsetYback);

    rel_dist_bowl = 0;


    for (i=0; i<height; i+=suby){
        for (j=0; j<width; j+=subx){

#ifdef QNX_BUILD
            j_offset = abs(int(j - width/2));
            i_offset = abs(int(i - height/2));
#else
            j_offset = abs(j - width/2);
            i_offset = abs(i - height/2);
#endif
            int32_t j_dist = j - width/2;
            int32_t i_dist = i - height/2;

            rel_dist_bowl = 0;


    //        offsetYfront = -(jeep * 10 + floor(cam_distance/2))/step_size;
    //        offsetYback  = (doll * 10 + floor(cam_distance/2))/step_size;

            // Bowl with rectangular base (rel_dist for bowl z height)
            // Max distance updatesd for non-uniform sampling
	    if(i_dist <= offsetYfront)
	    {
		    if(j_dist >= offsetXright)
		    {
			    rel_dist_bowl = sqrt((i_dist-offsetYfront)*(i_dist-offsetYfront) + (j_dist-offsetXright)*(j_dist-offsetXright));
			    rel_dist_bowl = (rel_dist_bowl/(max_dist-( sqrt(offsetYmin*offsetYmin+offsetXmin*offsetXmin))));
		    }
		    else if(j_dist <= offsetXleft)
		    {
			    rel_dist_bowl = sqrt((i_dist-offsetYfront)*(i_dist-offsetYfront) + (j_dist-offsetXleft)*(j_dist-offsetXleft));
			    rel_dist_bowl = (rel_dist_bowl/(max_dist-( sqrt(offsetYmin*offsetYmin+offsetXmin*offsetXmin))));

		    }
		    else
		    {
			    rel_dist_bowl = abs(i_dist-offsetYfront);
			    rel_dist_bowl = (rel_dist_bowl/(max_dist-( sqrt(offsetYmin*offsetYmin+offsetXmin*offsetXmin))));
		    }
	    }

	    else if(i_dist >= offsetYback)
	    {
		    if(j_dist >= offsetXright)
		    {
			    rel_dist_bowl = sqrt((i_dist-offsetYback)*(i_dist-offsetYback) + (j_dist-offsetXright)*(j_dist-offsetXright));
			    rel_dist_bowl = (rel_dist_bowl/(max_dist-( sqrt(offsetYmin*offsetYmin+offsetXmin*offsetXmin))));
		    }
		    else if(j_dist <= offsetXleft)
		    {
			    rel_dist_bowl = sqrt((i_dist-offsetYback)*(i_dist-offsetYback) + (j_dist-offsetXleft)*(j_dist-offsetXleft));
			    rel_dist_bowl = (rel_dist_bowl/(max_dist-( sqrt(offsetYmin*offsetYmin+offsetXmin*offsetXmin))));

		    }
		    else
		    {
			    rel_dist_bowl = abs(i_dist-offsetYback);
			    rel_dist_bowl = (rel_dist_bowl/(max_dist-( sqrt(offsetYmin*offsetYmin+offsetXmin*offsetXmin))));
		    }
	    }
	    else
	    {
		    if(j_dist >= offsetXright)
		    {
			    rel_dist_bowl = abs(j_dist-offsetXright);
			    rel_dist_bowl = (rel_dist_bowl/(max_dist-( sqrt(offsetYmin*offsetYmin+offsetXmin*offsetXmin))));
		    }
		    else if(j_dist <= offsetXleft)
		    {
			    rel_dist_bowl = abs(j_dist-offsetXleft);
			    rel_dist_bowl = (rel_dist_bowl/(max_dist-( sqrt(offsetYmin*offsetYmin+offsetXmin*offsetXmin))));
		    }
		    else
		    {
			    rel_dist_bowl = 0;
		    }

	    }



#if 0

            if(i_offset > offsetY && j_offset > offsetX)
            {
                  rel_dist_bowl = sqrt((i_offset-offsetY)*(i_offset-offsetY) + (j_offset-offsetX)*(j_offset-offsetX));
                  rel_dist_bowl = (rel_dist_bowl/(max_dist-( sqrt(offsetY*offsetY+offsetX*offsetX))));
            }
            else if (i_offset <= offsetY && j_offset > offsetX)
            {
                  rel_dist_bowl = (j_offset-offsetX);
                  rel_dist_bowl = (rel_dist_bowl/(max_dist-( sqrt(offsetY*offsetY+offsetX*offsetX))));
            }
            else if (i_offset > offsetY && j_offset <= offsetX)
            {
                  rel_dist_bowl = (i_offset-offsetY);
                  rel_dist_bowl = (rel_dist_bowl/(max_dist-( sqrt(offsetY*offsetY+offsetX*offsetX))));
            }
            else
            {
                  rel_dist_bowl=0;
            }
#endif
                // Calculate World points
                X = (float)(((float)j - (float)width/2.0) * (float)step_size);
                Y = (float)(((float)i - (float)height/2.0) * (float)step_size);
                Z = (float)(maxZ*((rel_dist_bowl)));
                //Z=0;

            Y=-Y;

#if 1
	    if((X <= X1max) && (X >= X1min) && (Y <= Y1max) && (Y >= Y1min))
	    {
		    Z = Z1;
	    }

	    if((X <= X2max) && (X >= X2min) && (Y <= Y2max) && (Y >= Y2min))
	    {
		    Z = Z2;
	    }
#endif

        // Quadrant 1
        if (j<=width/2 && i<=height/2) {
		lut_region = &lut[0 * QUADRANT_SIZE + quad_count1];
		lut_add_entry(lut_region, X, Y, Z,
			step_size, SV_origin,
			0, 3, 0 - ((float)width)/2, ((float)height)/2);
		quad_count1++;
	}

        // Quadrant 2
        if (j>=(width/2-subx) && i<=height/2) {
		lut_region = &lut[1 * QUADRANT_SIZE + quad_count2];
		lut_add_entry(lut_region, X, Y, Z,
			step_size, SV_origin,
			1, 0, ((float)width)/2, ((float)height)/2);
		quad_count2++;
	}

        // Quadrant 3
        if (j>=(width/2-subx) && i>=(height/2-suby)) {
		lut_region = &lut[2 * QUADRANT_SIZE + quad_count3];
		lut_add_entry(lut_region, X, Y, Z,
			step_size, SV_origin,
			2, 1, ((float)width)/2, 0 - ((float)height)/2);
		quad_count3++;
	}

        // Quadrant 4
        if (j<=width/2 && i>=(height/2-suby)){
		lut_region = &lut[3 * QUADRANT_SIZE + quad_count4];
		lut_add_entry(lut_region, X, Y, Z,
			step_size, SV_origin,
			3, 2, 0 - ((float)width)/2, 0 - ((float)height)/2);
		quad_count4++;
	}

        }

    }

    #ifdef PC_VERSION
        //Test
        fp = fopen("GAlingLUT3D.txt","w");
        count = ( ( (2+width/subsampleratio)*(2+height/subsampleratio) ) ) *9;
        for(index=0; index<count; index+=1){
                    fprintf(fp, " %d,", lut[index]);
        }
        fclose(fp);
    #endif
}

int srv_generate_blend_lut (uint32_t width, uint32_t height,
		uint32_t subx, uint32_t suby, srv_blend_lut_t *lut)
{
    uint16_t i,j;
    float X,Y;
    uint32_t count=0;

    #ifndef QUADBASED
    uint16_t ind_i,ind_j;
    //uint32_t img_count=0;
    #else
    uint32_t quad_count1=0, quad_count2=0, quad_count3=0, quad_count4=0;
    #endif

    srv_blend_lut_t *lut_region;

    /*

    view id 1 is Dominant Image
    view id 2 is Secondary Image


                                    view0
                        |-----------------------|
                        | Quadrant1 | Quadrant2 |
                    view3   |-----------------------| view1
                                | Quadrant4|  Quadrant3 |
                        |-----------------------|
                                view2


    Blend LUT format:

    For each output grid vertex the followind are stored in the array:

    0 - Blend 1
    1 - Blend 2


    */

    quad_count1 = 0;//0*no_of_elems *( (1+width/2/subx) * (1+height/2/suby));
    quad_count2 = 0;//1*no_of_elems *( (1+width/2/subx) * (1+height/2/suby));
    quad_count3 = 0;//2*no_of_elems *( (1+width/2/subx) * (1+height/2/suby));
    quad_count4 = 0;//3*no_of_elems *( (1+width/2/subx) * (1+height/2/suby));

    for (i=0; i<height; i+=suby){
        for (j=0; j<width; j+=subx){

		// Calculate World points
		X = (float)(((float)j - (float)width/2.0));
		Y = (float)(((float)i - (float)height/2.0));
		Y=-Y;

        // Quadrant 1
        if (j<=width/2 && i<=height/2) {
		lut_region = &lut[0 * QUADRANT_SIZE + quad_count1];
		blend_lut_add_entry(lut_region, X, Y,
			0 - ((float)width)/2, ((float)height)/2);
		quad_count1++;
	}

        // Quadrant 2
        if (j>=(width/2-subx) && i<=height/2) {
		lut_region = &lut[1 * QUADRANT_SIZE + quad_count2];
		blend_lut_add_entry(lut_region, X, Y,
			((float)width)/2, ((float)height)/2);
		quad_count2++;
	}

        // Quadrant 3
        if (j>=(width/2-subx) && i>=(height/2-suby)) {
		lut_region = &lut[2 * QUADRANT_SIZE + quad_count3];
		blend_lut_add_entry(lut_region, X, Y,
			((float)width)/2, 0 - ((float)height)/2);
		quad_count3++;
	}

        // Quadrant 4
        if (j<=width/2 && i>=(height/2-suby)){
		lut_region = &lut[3 * QUADRANT_SIZE + quad_count4];
		blend_lut_add_entry(lut_region, X, Y,
			0 - ((float)width)/2, 0 - ((float)height)/2);
		quad_count4++;
	}

        }

    }
}
