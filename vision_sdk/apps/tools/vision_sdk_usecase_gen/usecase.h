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
#ifndef USECASE_H
#define USECASE_H

#include <iostream>
#include <string>
#include <vector>
#include <map>

#include "link.h"
#include "options.h"
#include "error.h"
#include "support.h"

#define OBJ_MAX 128 //Changeable TODO: put this in documentation

extern Processor proc;
extern Options cmd_options;
using namespace std;

class Usecase {

	string fileName;
	string structName;
	ostream* logFile;
	map<string, Link*> inst_object; //Map of link name and Link object
	vector<Link*> exec_seq;
	vector<Link*> temp_seq;
	bool matrix[OBJ_MAX][OBJ_MAX]; //Matrix of connections
	bool userMat[OBJ_MAX][OBJ_MAX]; //Matrix of connections according to user, i.e as mentioned in testcase
	int numIpc;	//Number of ipc Links generated, used to name ipc Link uniquely
	vector<vector<Link*> > connections;

	void createNewObj(string name, Link* &obj);

	//initialize Links
	void assignCPU();
	void assignLinkID();
	void assignSeq(int curr, bool* asgn, bool* visited, bool* done);
	void setSequence();
	void connect(Link* obj1, Link* obj2); //insert the object in map
	void createAllConn();

	//print Link summary
	void printFileName(ostream* out);
	void printMatrix(ostream* out);
	void printExecSeq(ostream* out);
	void printTable(ostream* out);

	//Generate files
	void genFile();
	void genImgFile();

	/**********************/
	void initFiles(ostream& fp, ostream& fph);
	void genIncludes(ostream& fp, ostream& fph);
	void genStruct(ostream& fp, ostream& fph);
	void genSetLinkID(ostream& fp, ostream& fph);
    void genFreeLinkID(ostream& fp, ostream& fph);
	void genResetLinkPrms(ostream& fp, ostream& fph);
	void genSetLinkPrms(ostream& fp, ostream& fph);
	void genConnectLinks(ostream& fp, ostream& fph);
	void genCreate(ostream& fp, ostream& fph);
	void genEGLFunc(ostream& fp, ostream& fph);
	void genStart(ostream& fp, ostream& fph);
	void genStop(ostream& fp, ostream& fph);
	void genDelete(ostream& fp, ostream& fph);
	void genBufferStatistics(ostream& fp, ostream& fph);
	void genStatistics(ostream& fp, ostream& fph);
	void endFiles(ostream& fp, ostream& fph);

	/****************************/

public:

	Usecase();
	//~Usecase();

	void initialize();
	void print();
	void genFiles();

	void setFileName(string name);
	string getFileName();
	void setStructName(string name);
	string getStructName();

	Link* getObject(string name); //Return object from inst_object if present, else return NULL
	Link* createObject(string name); //Return object from inst_object if present, else create new Object

	void setNewConn(vector<Link*>* vec);
};
#endif
