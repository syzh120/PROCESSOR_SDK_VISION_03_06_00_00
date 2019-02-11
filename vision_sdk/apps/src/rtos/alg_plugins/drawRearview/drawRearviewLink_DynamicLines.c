/******************************************************************************
Copyright (c) [2012 - 2017] Texas Instruments Incorporated

All rights reserved not granted herein.

Limited License.

 Texas Instruments Incorporated grants a world-wide, royalty-free, non-exclusive
 license under copyrights and patents it now or hereafter owns or controls to
 make,  have made, use, import, offer to sell and sell ("Utilize") this software
 subject to the terms herein.  With respect to the foregoing patent license,
 such license is granted  solely to the extent that any such patent is necessary
 to Utilize the software alone.  The patent license shall not apply to any
 combinations which include this software, other than combinations with devices
 manufactured by or for TI ("TI Devices").  No hardware patent is licensed
 hereunder.

 Redistributions must preserve existing copyright notices and reproduce this
 license (including the above copyright notice and the disclaimer and
 (if applicable) source code license limitations below) in the documentation
 and/or other materials provided with the distribution

 Redistribution and use in binary form, without modification, are permitted
 provided that the following conditions are met:

 * No reverse engineering, decompilation, or disassembly of this software
   is permitted with respect to any software provided in binary form.

 * Any redistribution and use are licensed by TI for use only with TI Devices.

 * Nothing shall obligate TI to provide you with source code for the software
   licensed and provided to you in object code.

 If software source code is provided to you, modification and redistribution of
 the source code are permitted provided that the following conditions are met:

 * Any redistribution and use of the source code, including any resulting
   derivative works, are licensed by TI for use only with TI Devices.

 * Any redistribution and use of any object code compiled from the source code
   and any resulting derivative works, are licensed by TI for use only with TI
   Devices.

 Neither the name of Texas Instruments Incorporated nor the names of its
 suppliers may be used to endorse or promote products derived from this software
 without specific prior written permission.

 DISCLAIMER.

 THIS SOFTWARE IS PROVIDED BY TI AND TIS LICENSORS "AS IS" AND ANY EXPRESS OR
 IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 IN NO EVENT SHALL TI AND TIS LICENSORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
 OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
******************************************************************************/

/*******************************************************************************
 *  INCLUDE FILES
 *******************************************************************************
 */
#include "drawRearviewLink_priv.h"
#include <include/link_api/system_common.h>
#include <src/rtos/utils_common/include/utils_mem.h>

#define L  (110.2*9)                 // Wheelbase: 110.2"
#define W  (61.0*9)                  // Rear wheel tread: 61.0"
#define W2 (W/2.0)

static double sqrtdp (double a)
{
    double    half  =  0.5;
    double    OneP5 =  1.5;
    double    x, y;
    int32_t     i;

    x = _rsqrdp(a);

    #pragma UNROLL(1)

    for( i = 0; i < 3; i++ ) {
        x = x * (OneP5 - (a * x * x * half));
    }

    y = a * x;

    if( a <= 0.0 ) {
        y = 0.0;
    }
    if( a > DBL_MAX ) {
        y = DBL_MAX;
    }

    return (y);
}

#ifdef ACKERMANNSTEERTINGMODEL
void  AlgorithmLink_drawAckermannSteering(AlgorithmLink_drawRearviewObj *pObj)
{
    AlgorithmLink_RearviewOverlayDrawObj *pRearViewOverlayDrawObj;
    pRearViewOverlayDrawObj = &pObj->rearViewOverlayDrawObj;
    float tand[46] = {0.0001	,	0.0175	,	0.0349	,	0.0524	,	0.0699	,	0.0875	,	0.1051	,	0.1228	,	0.1405	,	0.1584	,	0.1763	,	0.1944	,	0.2126	,	0.2309	,	0.2493	,	0.2679	,	0.2867	,	0.3057	,	0.3249	,	0.3443	,	0.3640	,	0.3839	,	0.4040	,	0.4245	,	0.4452	,	0.4663	,	0.4877	,	0.5095	,	0.5317	,	0.5543	,	0.5774	,	0.6009	,	0.6249	,	0.6494	,	0.6745	,	0.7002	,	0.7265	,	0.7536	,	0.7813	,	0.8098	,	0.8391	,	0.8693	,	0.9004	,	0.9325	,	0.9657	,	1.0000	};

    // Compile Time Inputs
    Int32 x0Driver = 200;
    Int32 x0Pass = x0Driver + W;
    Int32 y0 = Y0;
    float q = 0.003378;

    // Loop Variables
    Bool loopFlag = TRUE;
    Bool genPass = TRUE;
    Bool genDriver = TRUE;
    float xDriverMin = 0;
    float xPassMin = 0;
    Int32 i = 1;
    
    // Calculation Variables
    float Ri;
    float Rri;
    float Rro;
    float rPass;
    float rDriver;
    float rPassSq;
    float rDriverSq;
    float xDriverProjShift;
    float xPassProjShift;
    float xDriverShift;
    float xPassShift;
    float xPass;
    float yPass;
    float xDriver;
    float yDriver;
    float xPassProj;
    float yPassProj;
    float xDriverProj;
    float yDriverProj;
    float xDriverInc;
    float xPassInc;
    
    // Draw Variables
    float xPassPlot;
    float yPassPlot;
    float xDriverPlot;
    float yDriverPlot;
    pRearViewOverlayDrawObj->xPassBuf[0] = x0Pass;
    pRearViewOverlayDrawObj->yPassBuf[0] = y0;
    pRearViewOverlayDrawObj->xDriverBuf[0] = x0Driver;
    pRearViewOverlayDrawObj->yDriverBuf[0] = y0;
    Draw2D_LinePrm linePrm1;
    linePrm1.lineColorFormat = SYSTEM_DF_YUV420SP_UV;
    linePrm1.lineSize = 8;
    linePrm1.lineColor = COLOR_RED;

    if(pRearViewOverlayDrawObj->drawBuf == FALSE)
    {
        Ri = L/(tand[pRearViewOverlayDrawObj->steeringAngle]);   // Radius of curvature of front wheel uses tand as a tanget of angle in degrees LUT
        Rri = sqrtdp((Ri*Ri)-(L*L));           					 // Rear inner tire radius of curvature
        Rro = Rri + W;                   						 // Rear outer tire radius of curvature

        if(pRearViewOverlayDrawObj->turningDir == FALSE)
        {
            rPass = Rro;
            rDriver = Rri;
            rPassSq = rPass*rPass;
            rDriverSq = rDriver*rDriver;
            xDriverProjShift = -rDriver - W2;
            xPassProjShift = -rPass + W2;
            // Figure out center of turning circle such that the lines
            // remain in the same place each iteration
            xDriverShift = x0Driver - rDriver;
            xPassShift = x0Pass - rPass;
            xPass = rPass;
            xDriver = rDriver;
        }
        else if(pRearViewOverlayDrawObj->turningDir == TRUE)
        {
            rPass = Rri;
            rDriver = Rro;
            rPassSq = rPass*rPass;
            rDriverSq = rDriver*rDriver;
            xDriverProjShift = rDriver - W2;
            xPassProjShift = rPass + W2;
            // Figure out center of turning circle such that the lines
            // remain in the same place each iteration
            xDriverShift = x0Driver + rDriver;
            xPassShift = x0Pass + rPass;
            xPass = rPass;
            xDriver = rDriver;
        }
        else
        {
            Vps_printf("ERROR: Turning direction input invalid\n");
            return;
        }

        if(((rPass-xPassMin)/DISCRETE_RES) > 1)
        {
            xPassMin = rPass - DISCRETE_RES;
        }
        if(((rDriver-xDriverMin)/DISCRETE_RES) > 1)
        {
            xDriverMin = rDriver - DISCRETE_RES;
        }
		
        xPassInc = ((rPass-xPassMin)/DISCRETE_RES);
        xDriverInc = ((rDriver-xDriverMin)/DISCRETE_RES);

        do
        {
            if(genPass == TRUE)
            {
                yPass = sqrtdp((rPassSq) - (xPass*xPass));
                if(yPass >= 750)
                {
                    yPass = 750;
                    genPass = FALSE;
                    pRearViewOverlayDrawObj->iPass = i;
                    if(pRearViewOverlayDrawObj->turningDir == FALSE)
                    {
                        loopFlag = FALSE;
                        pRearViewOverlayDrawObj->iDriver = i;
                    }
                }

                if(pRearViewOverlayDrawObj->turningDir == FALSE)
                {
                	xPassProj = (xPass+xPassProjShift)/((q*(yPass))+1);
                }
                else
                {
                        xPassProj = (-xPass+xPassProjShift)/((q*(yPass))+1);
                }

                yPassProj = yPass/((q*(yPass))+1);
                xPassPlot = xPassProj+xPassShift-xPassProjShift;
                yPassPlot = -1*(yPassProj)+y0;

                pRearViewOverlayDrawObj->xPassBuf[i] = xPassPlot;
                pRearViewOverlayDrawObj->yPassBuf[i] = yPassPlot;
            }
            if(genDriver == TRUE)
            {
                yDriver = sqrtdp((rDriverSq) - (xDriver*xDriver));
                if(yDriver >= 750)
                {
                    yDriver = 750;
                    genDriver = FALSE;
                    pRearViewOverlayDrawObj->iDriver = i;
                    if(pRearViewOverlayDrawObj->turningDir == TRUE)
                    {
                       loopFlag = FALSE;
                       pRearViewOverlayDrawObj->iPass = i;
                    }
                }
                if(pRearViewOverlayDrawObj->turningDir == FALSE)
                {
                	xDriverProj = (xDriver+xDriverProjShift)/((q*(yDriver))+1);
                }
                else
                {
                    xDriverProj = (-xDriver+xDriverProjShift)/((q*(yDriver))+1);
                }

                yDriverProj = yDriver/((q*(yDriver))+1);
                xDriverPlot = xDriverProj+xDriverShift-xDriverProjShift;
                yDriverPlot = -1*(yDriverProj)+y0;

                pRearViewOverlayDrawObj->xDriverBuf[i] = xDriverPlot;
                pRearViewOverlayDrawObj->yDriverBuf[i] = yDriverPlot;
            }
            if(i < DISCRETE_RES)
            {
                xPass = xPass - xPassInc;	//From MATLAB algorithm xPass = (bPass:-bPass/DISCRETE_RES:0)
                xDriver = xDriver - xDriverInc;
                i++;
            }
            else if(genDriver == FALSE && genPass == FALSE)
            {
                loopFlag = FALSE;
            }
            else
            {
                loopFlag = FALSE;
            }
        }while(loopFlag == TRUE);
        pRearViewOverlayDrawObj->drawBuf = TRUE;

    }
    else if (pRearViewOverlayDrawObj->drawBuf == TRUE)
    {
    	pRearViewOverlayDrawObj->drawBuf = FALSE;
    }
    else
    {
    	Vps_printf("Error with pRearViewOverlayDrawObj->drawBuf setting to false\n");
    	pRearViewOverlayDrawObj->drawBuf = FALSE;
    }

    Int32 j;
    for(j = 1; j <= pRearViewOverlayDrawObj->iDriver; j++)
    {
        Draw2D_drawLine(pObj->draw2DHndl,
            pRearViewOverlayDrawObj->xDriverBuf[j-1],
            pRearViewOverlayDrawObj->yDriverBuf[j-1],
            pRearViewOverlayDrawObj->xDriverBuf[j],
            pRearViewOverlayDrawObj->yDriverBuf[j],
            &linePrm1);
    }

    for(j = 1; j <= pRearViewOverlayDrawObj->iPass; j++)
    {
        Draw2D_drawLine(pObj->draw2DHndl,
            pRearViewOverlayDrawObj->xPassBuf[j-1],
            pRearViewOverlayDrawObj->yPassBuf[j-1],
            pRearViewOverlayDrawObj->xPassBuf[j],
            pRearViewOverlayDrawObj->yPassBuf[j],
            &linePrm1);
    }

    Draw2D_drawLine(pObj->draw2DHndl,
        pRearViewOverlayDrawObj->xPassBuf[pRearViewOverlayDrawObj->iPass],
        pRearViewOverlayDrawObj->yPassBuf[pRearViewOverlayDrawObj->iPass],
        pRearViewOverlayDrawObj->xDriverBuf[pRearViewOverlayDrawObj->iDriver],
        pRearViewOverlayDrawObj->yDriverBuf[pRearViewOverlayDrawObj->iDriver],
        &linePrm1);
}
#endif

#ifdef ELLIPSISSTEERTINGMODEL
void  AlgorithmLink_drawEllipsis(AlgorithmLink_drawRearviewObj *pObj, float aPass, float bPass, float aDriver, float bDriver)
{
    Int32 x0Pass;
    Int32 y0Pass = 488;
    Int32 x0Driver;
    Int32 y0Driver = y0Pass;
    Int32 x0DriverTemp;
    Int32 x0PassTemp;

    float xPass = bPass;
    float xDriver = bDriver;
    float yPass = 0;
    float yDriver = 0;
    float yPassPrev = 0;
    float yDriverPrev = 0;
    float xPassProjCur;
    float yPassProjCur;
    Int32 xPassProjPrev = 750;
    Int32 yPassProjPrev = y0Pass;
    float xDriverProjCur;
    float yDriverProjCur;
    Int32 xDriverProjPrev = 200;
    Int32 yDriverProjPrev = y0Driver;
    Int32 i = 0;
    char loopFlag = 1;
    float q = 0.003378;
    Int32 plotPass = 1;
    Int32 plotDriver = 1;



    // left turn case
    if(bPass > bDriver)
    {
        x0PassTemp = -bPass+150;
        x0DriverTemp = -bDriver-150;
        x0Driver = 200 - bDriver;
        x0Pass = 750 - bPass;
    }
    // right turn case
    else if(bPass < bDriver)
    {
        x0PassTemp = bPass+150;
        x0DriverTemp = bDriver-150;
        x0Driver = 200 + bDriver;
        x0Pass = 750 + bPass;
    }

    Draw2D_LinePrm linePrm4;
    linePrm4.lineColorFormat = SYSTEM_DF_YUV420SP_UV;
    linePrm4.lineSize = 16;
    linePrm4.lineColor = COLOR_RED;

     /*******************************************************************************************
     * Here we generate the animated backup lines curve. Wheel to the left turn case only.      *
     * First we generate the passenger side tire, because it is longer than the driver side.    *
     * Given the standard form of a vertical ellipse equation where                             *
     * b is the minor axis and a is the major axis: X^2/b^2 + Y^2/a^2 = 1                       *
     * it follows that: Y = sqrtdp[a^2 * (1 - {X^2/b^2})].                                      *
     * Then we perform a two point perspective projection that modifies the x and y coordinates *
     * based on where they should be perceived in 3D space.                                     *
     * The equation used has the form: x = x/(px+qy+1), y = y/(px+qy+1)                         *
     ********************************************************************************************/

    do
    {
        if(plotPass == 1)
        {
            yPass = (aPass*aPass*(1 - ((xPass*xPass)/(bPass*bPass))));
            yPass = (sqrtdp(yPass));
            if(bPass < bDriver)
            {
                xPassProjCur = (-1*xPass+x0PassTemp)/((q*(yPass))+1);
            }
            else if(bPass > bDriver)
            {
                xPassProjCur = (xPass+x0PassTemp)/((q*(yPass))+1);				
            }

            yPassProjCur = (yPass/((q*(yPass))+1));
            xPassProjCur = xPassProjCur+x0Pass-x0PassTemp;
            yPassProjCur = -1*(yPassProjCur) + y0Pass;

            if(yPass > YELLINE_YMAX)
            {
                if(yPassPrev < YELLINE_YMAX && plotPass == 1)
                {
                    linePrm4.lineColor = COLOR_YELLOW;
                    Draw2D_drawLine(pObj->draw2DHndl,
                        xPassProjPrev,
                        yPassProjPrev,
                        xPassProjCur,
                        YELLINE_YMAX_Proj,
                        &linePrm4);
                    yPassProjPrev = YELLINE_YMAX_Proj;
                    xPassProjPrev = xPassProjCur;
                }

                linePrm4.lineColor = COLOR_GREEN;

            }
            else if(yPass > REDLINE_YMAX)
            {
                if(yPassPrev < REDLINE_YMAX && plotPass == 1)
                {
                    linePrm4.lineColor = COLOR_RED;
                    Draw2D_drawLine(pObj->draw2DHndl,
                        xPassProjPrev,
                        yPassProjPrev,
                        xPassProjCur,
                        REDLINE_YMAX_Proj,
                        &linePrm4);
                    yPassProjPrev = REDLINE_YMAX_Proj;
                    xPassProjPrev = xPassProjCur;
                }
                linePrm4.lineColor = COLOR_YELLOW; 
            }
            else
            {
                linePrm4.lineColor = COLOR_RED;
            }
            Draw2D_drawLine(pObj->draw2DHndl,
                xPassProjPrev,
                yPassProjPrev,
                xPassProjCur,
                yPassProjCur,
                &linePrm4);
            yPassPrev = yPass;
            xPassProjPrev = xPassProjCur;
            yPassProjPrev = yPassProjCur;
        }
        if(plotDriver == 1)
        {
            yDriver = (aDriver*aDriver*(1 - ((xDriver*xDriver)/(bDriver*bDriver))));
            yDriver = (sqrtdp(yDriver));
            if(bPass < bDriver)
            {
                xDriverProjCur = (-1*xDriver+x0DriverTemp)/((q*(yDriver))+1);
            }
            else if(bPass > bDriver)
            {
                xDriverProjCur = (xDriver+x0DriverTemp)/((q*(yDriver))+1);				
            }
            yDriverProjCur = (yDriver/((q*(yDriver))+1));
            xDriverProjCur = xDriverProjCur+x0Driver-x0DriverTemp;
            yDriverProjCur = -1*(yDriverProjCur) + y0Driver;
            if(yDriver > YELLINE_YMAX)
            {
                if(yDriverPrev < YELLINE_YMAX && plotDriver == 1)
                {
                    linePrm4.lineColor = COLOR_YELLOW;
                    Draw2D_drawLine(pObj->draw2DHndl,
                        xDriverProjPrev,
                        yDriverProjPrev,
                        xDriverProjCur,
                        YELLINE_YMAX_Proj,
                        &linePrm4);
                    yDriverProjPrev = YELLINE_YMAX_Proj;
                    xDriverProjPrev = xDriverProjCur;
                }
                linePrm4.lineColor = COLOR_GREEN;
            }
            else if(yDriver > REDLINE_YMAX)
            {
                if(yDriverPrev < REDLINE_YMAX && plotDriver == 1)
                {
                    linePrm4.lineColor = COLOR_RED;
                    Draw2D_drawLine(pObj->draw2DHndl,
                        xDriverProjPrev,
                        yDriverProjPrev,
                        xDriverProjCur,
                        REDLINE_YMAX_Proj,
                        &linePrm4);
                    yDriverProjPrev = REDLINE_YMAX_Proj;
                    xDriverProjPrev = xDriverProjCur;
                }
                linePrm4.lineColor = COLOR_YELLOW;
            }
            else
            {
                linePrm4.lineColor =COLOR_RED;
            }
                Draw2D_drawLine(pObj->draw2DHndl,
                    xDriverProjPrev,
                    yDriverProjPrev,
                    xDriverProjCur,
                    yDriverProjCur,
                    &linePrm4);

                yDriverPrev = yDriver;
                xDriverProjPrev = xDriverProjCur;
                yDriverProjPrev = yDriverProjCur;
        }		

        if(xPass <= 0 || i >= DISCRETE_RES || xDriver <= 0)
        {
            loopFlag = 0;
        }
        else if((yPass <= 750 && bPass > bDriver) || (yDriver <= 750 && bDriver > bPass))
        {
            xPass = xPass - (bPass/DISCRETE_RES);	//From MATLAB algorithm xPass = (bPass:-bPass/DISCRETE_RES:0)
            xDriver = xDriver - (bDriver/DISCRETE_RES);
            i++;	
        }
        else if(yPass > 750 && yDriver <= 650 && bPass > bDriver)
        {
            plotPass = 0;
            xDriver = xDriver - (bDriver/DISCRETE_RES);
            i++;
        }
        else if(yPass <= 650 && yDriver > 750 && bPass < bDriver)
        {
            plotDriver = 0;
            xPass = xPass - (bPass/DISCRETE_RES);
            i++;
        }
        else
        {
            loopFlag = 0;
        }

    }while(loopFlag == 1);
}

#endif




Int32 AlgorithmLink_drawOverlaysRun(AlgorithmLink_drawRearviewObj *pObj)
{
    AlgorithmLink_RearviewOverlayDrawObj *pRearViewOverlayDrawObj;

    pRearViewOverlayDrawObj = &pObj->rearViewOverlayDrawObj;


    if(pRearViewOverlayDrawObj->isFirstTime)
    {
        //Set up initial parameters for loop implementation
        pRearViewOverlayDrawObj->isFirstTime = FALSE;
        #ifdef ELLIPSISSTEERTINGMODEL
        pRearViewOverlayDrawObj->aLong = 500;
        #endif
        #ifdef ACKERMANNSTEERTINGMODEL
        pRearViewOverlayDrawObj->steeringAngle = 45;
        #endif
        pRearViewOverlayDrawObj->state = 2;
        pRearViewOverlayDrawObj->delay = 0;
    }

    #ifdef ELLIPSISSTEERTINGMODEL
        Draw2D_LinePrm linePrm4;
        linePrm4.lineColorFormat = SYSTEM_DF_YUV420SP_UV;
        linePrm4.lineSize = 16;
        linePrm4.lineColor = COLOR_RED;
    #endif

    switch(pRearViewOverlayDrawObj->state)
    {
         case 0:
         {
             //State 0: Draw Straight Lines
            #ifdef ACKERMANNSTEERTINGMODEL
            pRearViewOverlayDrawObj->steeringAngle = 0;
            AlgorithmLink_drawAckermannSteering(pObj);
            #endif

            #ifdef ELLIPSISSTEERTINGMODEL
                //Found the equation of the lines formed by (750,Y0) to (PROJXPASS,PROJXPASS) and (200,Y0) to (PROJXDRIVER, PROJYDRIVER)
                //then found the x and y values on the boundaries of the different color segments
                //Draw the red segment
                linePrm4.lineColor = COLOR_RED;
                Draw2D_drawLine(pObj->draw2DHndl,
                    750,
                    Y0,
                    699,
                    388,
                    &linePrm4);
                Draw2D_drawLine(pObj->draw2DHndl,
                    200,
                    Y0,
                    250,
                    388,
                    &linePrm4);

                //Draw the yellow segment
                linePrm4.lineColor = COLOR_YELLOW;
                Draw2D_drawLine(pObj->draw2DHndl,
                    699,
                    388,
                    673,
                    338,
                    &linePrm4);
                Draw2D_drawLine(pObj->draw2DHndl,
                    250,
                    388,
                    275,
                    338,
                    &linePrm4);

                //Draw the green segment
                linePrm4.lineColor = COLOR_GREEN;
                Draw2D_drawLine(pObj->draw2DHndl,
                    673,
                    338,
                    PROJXPASS,
                    PROJYPASS,
                    &linePrm4);
                Draw2D_drawLine(pObj->draw2DHndl,
                    275,
                    338,
                    PROJXDRIVER,
                    PROJYDRIVER,
                    &linePrm4);
            #endif

            if(pRearViewOverlayDrawObj->delay < 100)
            {
                pRearViewOverlayDrawObj->state = 0;
                pRearViewOverlayDrawObj->delay += 1;
            }
            else
            {
                if(pRearViewOverlayDrawObj->prevState == 2)
                {
                    pRearViewOverlayDrawObj->state = 3;
                    pRearViewOverlayDrawObj->turningDir = TRUE;
                }
                else
                {
                    pRearViewOverlayDrawObj->state = 1;
                    pRearViewOverlayDrawObj->turningDir = FALSE;
                }
                pRearViewOverlayDrawObj->prevState = 0;
                pRearViewOverlayDrawObj->delay = 0;
            }

            break;
        }
        case 1:
        {
            //State 1: Draw left turn lines going further left
            #ifdef ELLIPSISSTEERTINGMODEL
                pRearViewOverlayDrawObj->aLong = pRearViewOverlayDrawObj->aLong - 10;
                AlgorithmLink_drawEllipsis(pObj, pRearViewOverlayDrawObj->aLong, 500, pRearViewOverlayDrawObj->aLong/2, 250);

                if(pRearViewOverlayDrawObj->aLong <= 500)
                {
                    pRearViewOverlayDrawObj->state = 2;
                }
                else
                {
                    pRearViewOverlayDrawObj->aLong = pRearViewOverlayDrawObj->aLong - 10;
                }
            #endif

            #ifdef ACKERMANNSTEERTINGMODEL
                AlgorithmLink_drawAckermannSteering(pObj);
                if(pRearViewOverlayDrawObj->steeringAngle == 44)
                {
                    if(pRearViewOverlayDrawObj->delay < 50)
                    {
                        pRearViewOverlayDrawObj->delay += 1;
                    }
                    else
                    {
                        pRearViewOverlayDrawObj->state = 2;
                        pRearViewOverlayDrawObj->delay = 0;
                        pRearViewOverlayDrawObj->steeringAngle = 44;
                        pRearViewOverlayDrawObj->turningDir = FALSE;
                    }
                }
                else
                {
                    pRearViewOverlayDrawObj->steeringAngle += 1;
                }
            #endif
            pRearViewOverlayDrawObj->prevState = 1;
            break;
        }
        case 2:
        {
            //State 2: Draw left turn lines going further right
            #ifdef ELLIPSISSTEERTINGMODEL
                AlgorithmLink_drawEllipsis(pObj, pRearViewOverlayDrawObj->aLong, 500, pRearViewOverlayDrawObj->aLong/2, 250);

                if(pRearViewOverlayDrawObj->aLong >= 1500)
                {
                    pRearViewOverlayDrawObj->state = 0;
                }
                else
                {
                    pRearViewOverlayDrawObj->aLong = pRearViewOverlayDrawObj->aLong + 10;	
                }
                pRearViewOverlayDrawObj->prevState = 2;
            #endif

            #ifdef ACKERMANNSTEERTINGMODEL
                AlgorithmLink_drawAckermannSteering(pObj);
                if(pRearViewOverlayDrawObj->steeringAngle == 0)
                {
                    pRearViewOverlayDrawObj->state = 0;
                    pRearViewOverlayDrawObj->turningDir = TRUE;
                }
                else
                {
                    pRearViewOverlayDrawObj->steeringAngle -= 1;
                }
            #endif

            pRearViewOverlayDrawObj->prevState = 2;
            break;
        }
        case 3:
        {
            //State 3: Draw right turn lines going further right
            #ifdef ELLIPSISSTEERTINGMODEL
                AlgorithmLink_drawEllipsis(pObj, pRearViewOverlayDrawObj->aLong/2, 250, pRearViewOverlayDrawObj->aLong, 500);
                //Vps_printf("aPass = //d, aDriver = //d\n", pRearViewOverlayDrawObj->aLong/2, pRearViewOverlayDrawObj->aLong);
                if(pRearViewOverlayDrawObj->aLong <= 500)
                {
                    pRearViewOverlayDrawObj->state = 4;
                }
                else
                {
                    pRearViewOverlayDrawObj->aLong = pRearViewOverlayDrawObj->aLong - 10;
                }
            #endif
			
            #ifdef ACKERMANNSTEERTINGMODEL
                AlgorithmLink_drawAckermannSteering(pObj);
                if(pRearViewOverlayDrawObj->steeringAngle == 44)
                {
                    if(pRearViewOverlayDrawObj->delay < 50)
                    {
                        pRearViewOverlayDrawObj->delay += 1;
                    }
                    else
                    {
                        pRearViewOverlayDrawObj->state = 4;
                        pRearViewOverlayDrawObj->turningDir = TRUE;
                        pRearViewOverlayDrawObj->steeringAngle = 44;
                        pRearViewOverlayDrawObj->delay = 0;
                    }
                }
                else
                {
                    pRearViewOverlayDrawObj->steeringAngle += 1;
                }
            #endif

            pRearViewOverlayDrawObj->prevState = 3;
            break;
        }
        case 4:
        {
            //State 4: Draw right turn lines going further left

            #ifdef ELLIPSISSTEERTINGMODEL
                AlgorithmLink_drawEllipsis(pObj, pRearViewOverlayDrawObj->aLong/2, 250, pRearViewOverlayDrawObj->aLong, 500);

                if(pRearViewOverlayDrawObj->aLong >= 1500)
                {
                    // Go to straight line state
                    pRearViewOverlayDrawObj->state = 0;
                }
                else
                {
                    pRearViewOverlayDrawObj->aLong = pRearViewOverlayDrawObj->aLong + 10;	
                }
            #endif

            #ifdef ACKERMANNSTEERTINGMODEL
                AlgorithmLink_drawAckermannSteering(pObj);
                if(pRearViewOverlayDrawObj->steeringAngle == 0)
                {
                    pRearViewOverlayDrawObj->state = 0;
                    pRearViewOverlayDrawObj->turningDir = FALSE;
                }
                else
                {
                    pRearViewOverlayDrawObj->steeringAngle -= 1;
                }
            #endif

            pRearViewOverlayDrawObj->prevState = 4;
            break;
        }
        default:
        {
            Vps_printf("Invalid Case Resetting to Straight Line Case\n");
            pRearViewOverlayDrawObj->state = 0;
            break;
        }
     }

     return 0;
}


