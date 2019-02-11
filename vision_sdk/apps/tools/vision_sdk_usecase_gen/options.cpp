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

 THIS SOFTWARE IS PROVIDED BY TI AND TI’S LICENSORS "AS IS" AND ANY EXPRESS OR
 IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 IN NO EVENT SHALL TI AND TI’S LICENSORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
 OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
******************************************************************************/
#include <iostream>
#include <fstream>
#include <ostream>
#include <string>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

#include "options.h"

Options cmd_options;
extern FILE * yyin;

Options::Options() {
    show_tokens = false;
    write_file = false;
    write_image = false;
    verbose_mode = false;
    log_mode = false;
    output_path = false;
    dynamic_link_id = false;

    os_tokens = NULL;
    os_file = NULL;
    os_header = NULL;
    os_image = NULL;
    os_log = NULL;
}

Options::~Options() {
    if (show_tokens)
        ofs_tokens.close();
    if (write_file) {
        ofs_file.close();
        ofs_header.close();
    }
    if (write_image)
        ofs_image.close();
    if(log_mode)
        ofs_log.close();
}

void Options::close_Image() {
    if (write_image)
        ofs_image.close();
}

bool Options::show_Tokens() {
    return show_tokens;
}
bool Options::write_toFile() {
    return write_file;
}

bool Options::write_toImage() {
    return write_image;
}

bool Options::verboseMode() {
    return verbose_mode;
}

bool Options::useDynamicLinkId() {
    return dynamic_link_id;
}

bool Options::write_tologFile()
{
    return log_mode;
}

ostream * Options::tokens_File() {
    return &ofs_tokens;
}
ostream * Options::write_File() {
    return &ofs_file;
}
ostream * Options::write_Header() {
    return &ofs_header;
}
ostream * Options::write_Image() {
    return &ofs_image;
}
ostream* Options::log_File()
{
    return &ofs_log;
}

int Options::process_Options(int argc, char * argv[]) {
    bool input_file_given = false;

    string tokens_file_name;

    char * input_file_c_string = NULL;

    string usage =
            " \n"
            " Vision SDK usecase generation tool - (c) Texas Instruments 2014\n"
            " \n"
            " Version : v1.02 ( " + string(__DATE__) + " - " + string(__TIME__) + " )\n"
            " \n"
            " Usage: " + string(argv[0]) + " [options] [input file]\n"
            " \n"
            " Options:\n"
            "   -help            :  Show this help\n"
            "   -file            :  Create usecase .c and .h file \n"
            "   -img             :  Create .jpg image (Needs 'dot' tool from www.graphviz.org to be installed and visible in system path)\n"
            "   -log             :  Creates .txt log file with debugging info\n"
            "   -debug           :  Prints file name and line no of tool source code in error statements (To be used by tool developers only)\n"
            "   -path [pathname] :  Output path where generated files are written. If not specified current directory is used\n"
            "   -v               :  Verbose output on console\n"
            "   -dynamic_link_id :  Let run-time system generate dynamic link ID\n"
            " \n"
            " Supported CPUs: \n"
            "   IPU1_0, IPU1_1, IPU2, A15, DSP1, DSP2, EVE1, EVE2, EVE3, EVE4 \n"
            " \n"
            " Supported Links:  \n"
            "   AvbRx\n"
            "   AvbTx\n"
            "   TfdtpRx\n"
            "   Capture\n"
            "   UltrasonicCapture\n"
            "   VPE\n"
            "   DssM2mWb\n"
            "   Display\n"
            "   DisplayMultiPipe\n"
            "   Encode\n"
            "   Decode\n"
            "   DrmDisplay\n"
            "   DispDistSrc\n"
            "   SgxFrmcpy\n"
            "   Sgx3Dsrv\n"
            "   Sgx3Dsfm\n"
            "   SgxLink\n"
            "   GrpxSrc\n"
            "   IssCapture\n"
            "   IssM2mIsp\n"
            "   IssM2mSimcop\n"
            "   IssM2mResizer\n"
            "   RadarDraw\n"
            "   Hcf\n"
            "   AutosarIpcIn\n"
            "   AutosarIpcOut\n"
            "\n"
            "   Dup\n"
            "   Split\n"
            "   Gate\n"
            "   Merge\n"
            "   Select\n"
            "   Sync\n"
            "   IPCIn\n"
            "   IPCOut\n"
            "   Null\n"
            "   NullSource\n"
            "   DataCollect\n"
            "   DumpLink\n"
            "   UndumpLink\n"
            "\n"
            "   LidarCapture\n"
            "   LidarCloud\n"
            "   LidarCloudXForm\n"
            "   LidarGPCLink\n"
            "\n"
            "   ImuLink\n"
            "   OGLink\n"
            "   Slam\n"
            "\n"
            "   Alg_FrameCopy\n"
            "   Alg_SafeFrameCopy\n"
            "   Alg_SubframeCopy\n"
            "   Alg_ColorToGray\n"
            "   Alg_EdgeDetect\n"
            "   Alg_DmaSwMs\n"
            "   Alg_VpeSwMs\n"
            "   Alg_DenseOptFlow\n"
            "   Alg_VectorToImage\n"
            "   Alg_FeaturePlaneComputation\n"
            "   Alg_ImagePreProcess\n"
            "   Alg_ImgPyramid\n"
            "   Alg_FPCompute\n"
            "   Alg_ObjectDetection\n"
            "   Alg_ObjectClassification\n"
            "   Alg_ObjectDraw\n"
            "   Alg_GeoAlign\n"
            "   Alg_GeoAlign3D\n"
            "   Alg_PhotoAlign\n"
            "   Alg_Synthesis\n"
            "   Alg_SfmLinearTwoView\n"
            "   Alg_SfmMain\n"
            "   Alg_SfmMap\n"
            "   Alg_SfmSurround\n"
            "   Alg_SparseOpticalFlow\n"
            "   Alg_SoftIsp\n"
            "   Alg_IssAewb\n"
            "   Alg_Crc\n"
            "   Alg_UltrasonicFusion\n"
            "   Alg_Census\n"
            "   Alg_DisparityHamDist\n"
            "   Alg_RemapMerge\n"
            "   Alg_StereoPostProcess\n"
            "   Alg_SceneObstructionDetect\n"
            "   Alg_LaneDetect\n"
            "   Alg_Sfm\n"
            "   Alg_Fcw - Forward Collision Warning\n"
            "   Alg_Clr - Circular Light Recognition\n"
            "   Alg_AutoChartDetect\n"
            "   Alg_PoseEstimate\n"
            "   Alg_DeWarp\n"
            "   Alg_OpenCVCanny\n"
            "   Alg_UndistortTracks\n"
            "   Alg_Triangulation\n"
            "   Alg_AutoRemap\n"
            "   Alg_StereoApp\n"
            "   Alg_tidl\n"
            "   Alg_tiop\n"
            "   Alg_tidlpreproc\n"
            "   Alg_tidlpostproc\n"
            "   Alg_drawRearview\n"
            "   Alg_SeamDetection\n"
            "   Alg_Stitching\n"
            "   Alg_AdaptiveBowl\n"
            "\n"
            "   Alg_[Custom alg name]\n"
            "   DefLink_[Custom link name]\n"
            "\n"
            ;

    for (int i = 1; i < argc; i++) {
        char * option = strdup(argv[i]);
        if (strncmp(option, "-", 1) == 0) //check if 1st letter is -, then it is an option
        {
            if (strcmp(option, "-v") == 0)
                verbose_mode = true;
            else if (strcmp(option, "-tokens") == 0) {
                show_tokens = true;
            } else if (strcmp(option, "-file") == 0) {
                write_file = true;
            } else if (strcmp(option, "-img") == 0) {
                write_image = true;
            }else if (strcmp(option, "-log") == 0) {
                log_mode = true;
            }else if (strcmp(option, "-debug") == 0) {
                debug = true;
            }else if (strcmp(option, "-dynamic_link_id") == 0) {
                dynamic_link_id = true;
            }else if (strcmp(option, "-path") == 0) {
                output_path = true;
                if(i+1 < argc)
                {
                    output_path_name = string(argv[i+1]);
                    i++;
                    continue;
                }
                else
                    CHECK_ERROR_ABORT(SHOULD_NOT_REACH, "Error: Output path not provided !!!");
            }else if ((strcmp(option, "--help") == 0)
                    || (strcmp(option, "-help") == 0)
                    || (strcmp(option, "-h") == 0)){
                cerr << usage;
                return -1;
            } else {
                string mesg = "Error: Unknown option [" + string(option) + "] !!!\n";

                cerr << usage;

                CHECK_ERROR_ABORT(SHOULD_NOT_REACH, mesg);
            }
        } else if (input_file_given) {
            string mesg = "Error: Only one input file name can be provided !!!\n" ;

            cerr << usage;

            CHECK_ERROR(SHOULD_NOT_REACH, mesg);

        } else{
            input_file_given = true;
            input_file_c_string = strdup(option);
        }
    }

    if (input_file_given == true) {
        input_file_name = string(input_file_c_string);
        yyin = fopen(input_file_c_string, "r");
        CHECK_ERROR_ABORT(yyin!=NULL, "Error: Input file [" + input_file_name + "] could not be opened !!!");

    } else {
        string mesg = "Error: Input file name not provided !!!";

        cerr << usage;

        CHECK_ERROR_ABORT(SHOULD_NOT_REACH, mesg);


    }

    //need to give initial name to tokens_file_name because filename is set while parsing
    tokens_file_name = input_file_name + "-debug.txt";
    remove(tokens_file_name.c_str());
    if (show_tokens)
        ofs_tokens.open(tokens_file_name.c_str());
    if(output_path)
    {
        if(!(output_path_name.at(output_path_name.length()-1) == '/'))
            output_path_name = output_path_name + "/";
    }
    else
        output_path_name = "";
    return 0;

}

void Options::setFileNames(string filestr) {
    string write_file_name, header_file_name,
            write_image_name, log_file_name;
    write_file_name = output_path_name + filestr + "_priv.c";
    header_file_name = output_path_name + filestr + "_priv.h";
    write_image_name = output_path_name + filestr + "_img.txt";
    log_file_name = output_path_name + filestr + "_log.txt";
    remove(write_file_name.c_str());
    remove(header_file_name.c_str());
    remove(log_file_name.c_str());
    remove(write_image_name.c_str());

    if (write_file) {
        ofs_file.open(write_file_name.c_str());
        ofs_header.open(header_file_name.c_str());
    }
    if (write_image)
        ofs_image.open(write_image_name.c_str());
    if(log_mode)
        ofs_log.open(log_file_name.c_str());
}

string Options::get_output_path_name()
{
    return output_path_name;
}
