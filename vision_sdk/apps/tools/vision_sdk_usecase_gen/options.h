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
#ifndef OPTIONS_H
#define OPTIONS_H

#include <iostream>
#include <cstdio>
#include <fstream>
#include <ostream>
#include "error.h"

extern bool debug;
using namespace std;

class Options {
	bool show_tokens;
	bool write_file;
	bool write_image;
	bool verbose_mode;
	bool log_mode;
	bool output_path;
    bool dynamic_link_id;
	/* Output streams */

	ostream* os_tokens;
	ostream* os_file;
	ostream* os_header;
	ostream* os_image;
	ostream* os_log;

	/*
	 Privately, we also need objects of ofstream which can be opened
	 if required and their addresses set to the pointers above.
	 */

	ofstream ofs_tokens;
	ofstream ofs_file;
	ofstream ofs_header;
	ofstream ofs_image;
	ofstream ofs_log;

	string input_file_name;

public:
	string output_path_name;

	Options();
	~Options();

	bool show_Tokens();
	bool write_toFile();
	bool write_toImage();
	bool verboseMode();
	bool write_tologFile();
    bool useDynamicLinkId();

	int process_Options(int argc, char * argv[]);
	void setFileNames(string filestr);
	void close_Image();

	//Return output file with appropriate suffix attached, if no input file then cout
	ostream* tokens_File();
	ostream* write_File();
	ostream* write_Header();
	ostream* write_Image();
	ostream* log_File();

	string get_output_path_name();
};

extern Options cmd_options;
#endif
