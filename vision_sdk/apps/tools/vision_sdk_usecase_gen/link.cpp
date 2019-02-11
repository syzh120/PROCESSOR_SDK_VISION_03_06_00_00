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
#include <utility>
#include <typeinfo>
#include <iomanip>

#include "link.h"
#include "error.h"
#include "support.h"
#include "options.h"

Link::Link() {
    linkIDName = name + string("LinkID");
    prmName = name + string("Prm");
    execPos = -1;
    procID = -1;
    matrixPos = -1;
    cType = cDefLink;
    pType = IPU1_0;
    mulOutQue = false;
    mulInQue = false;
}

Link::~Link(){
}

ProcType Link::getProcType() {
    return pType;
}

ClassType Link::getClassType() {
    return cType;
}

void Link::setProcType(ProcType processor) {
    if (procID == -1) //If ProcID not set already
    {
        pType = processor;
        setProcID();
    }
    else if(pType != processor)
        CHECK_ERROR(SHOULD_NOT_REACH, "Error: Multiple CPU types [" + procName[processor] + "] and [" + procName[pType] + "] assigned to same Link [" + name + "] !!!");
}

void Link::setProcType(string strproc) {
    ProcType proc;
    if (strproc == "IPU1_0")
        proc = IPU1_0;
    else if (strproc == "IPU1_1")
        proc = IPU1_1;
    else if (strproc == "IPU2")
        proc = IPU2;
    else if (strproc == "A15")
        proc = A15;
    else if (strproc == "DSP1")
        proc = DSP1;
    else if (strproc == "DSP2")
        proc = DSP2;
    else if (strproc == "EVE1")
        proc = EVE1;
    else if (strproc == "EVE2")
        proc = EVE2;
    else if (strproc == "EVE3")
        proc = EVE3;
    else if (strproc == "EVE4")
        proc = EVE4;
    else
        CHECK_ERROR_ABORT(SHOULD_NOT_REACH, "Error: Unknown CPU ["+strproc+"] assigned to Link ["+name+"]. Use '-h' option to see list of supported CPUs !!!");
    if (procID == -1) //If ProcID not set already
    {
        pType = proc;
        setProcID();
    }
    else if(pType != proc)
        CHECK_ERROR(SHOULD_NOT_REACH, "Error: Multiple CPU types [" + procName[proc] + "] and [" + procName[pType] + "] assigned to same Link [" + name + "] !!!");
}

void Link::setProcID() {
    procID = proc.getProcID(pType, cType, name);
}

int Link::getProcID() {
    return procID;
}

string Link::getName() {
    return name;
}

void Link::setName(string nm) {
    name = nm;
    linkIDName = name + string("LinkID");
    prmName = name + string("Prm");
}

string Link::getLinkName() {
    return linkIDName;
}

void Link::setLinkName(string nm) {
    linkIDName = nm;
}

string Link::getLinkIDName() {
    return linkIDAsgnName;
}

void Link::setLinkIDName() {
    if (getRoot(name) == "Alg")
    {
        if(cmd_options.useDynamicLinkId())
        {
            linkIDAsgnName = proc.allocDynamicLinkId(pType, cAlg, name);
        }
        else
        {
            linkIDAsgnName = proc.getLinkID(pType, cAlg, procID, name);
        }
    }
    else
    {
        if(cmd_options.useDynamicLinkId())
        {
            linkIDAsgnName = proc.allocDynamicLinkId(pType, cType, name);
        }
        else
        {
            linkIDAsgnName = proc.getLinkID(pType, cType, procID, name);
        }
    }
}

string Link::getPrmName() {
    return prmName;
}

void Link::setPrmName(string nm) {
    prmName = nm;
}

int Link::getMatrixPos() {
    return matrixPos;
}

void Link::setMatrixPos(int pos) {
    matrixPos = pos;
}

int Link::getExecPos() {
    return execPos;
}

void Link::setExecPos(int pos) {
    execPos = pos;
}

bool Link::getMulInQue()
{
    return mulInQue;
}

bool Link::getMulOutQue()
{
    return mulOutQue;
}

void Link::setInQueueID(int objNum, int qid) {
    CHECK_ERROR_ABORT(inLink.size() > objNum, "Error: Input Que ID of Link [" + name + "] should be set after inserting Link in 'inLink' vector !!!");
    (inLink.at(objNum)).second = qid;
}

void Link::setOutQueueID(int objNum, int qid) {
    CHECK_ERROR_ABORT(outLink.size() > objNum, "Error: Output Que ID of Link [" + name + "] should be set after inserting Link in 'outLink' vector !!!");
    (outLink.at(objNum)).second = qid;
}
int Link::getInQueueID(Link* obj) {
    for (int i = 0; i < inLink.size(); i++)
        if ((inLink.at(i)).first == obj)
            return i;
    CHECK_ERROR_ABORT(SHOULD_NOT_REACH, "Error: Link [" + obj->getName() + "] not present in 'inLink' of Link [" + name + "] !!!");
    return -1;
}

int Link::getOutQueueID(Link* obj) {
    for (int i = 0; i < outLink.size(); i++)
        if ((outLink.at(i)).first == obj)
            return i;
    CHECK_ERROR_ABORT(SHOULD_NOT_REACH, "Error: Link [" + obj->getName() + "] not present in outLink of Link [" + name + "] !!!");
    return -1;
}

vector<pair<Link*, int> > * Link::getOutLinkPtr() {
    return &outLink;
}

void Link::printInLink(ostream &out) {
    for (int i = 0; i < inLink.size(); i++)
        out << i << ". (" << ((inLink.at(i)).first)->getName() << ", "
                << ((inLink.at(i)).second) << ")" << endl;
}

void Link::printOutLink(ostream &out) {
    for (int i = 0; i < outLink.size(); i++)
        out << i << ". (" << ((outLink.at(i)).first)->getName() << ", "
                << ((outLink.at(i)).second) << ")" << endl;
}

int Link::getInLinkSize() {
    return inLink.size();
}
int Link::getOutLinkSize() {
    return outLink.size();
}

void Link::genSetLinkID(ostream &fp, string obj) {
    fp << BLOCK_SPACE << obj << "->" << setw(30) << left << linkIDName << " = "
            << linkIDAsgnName << ";" << endl;
}

void Link::genFreeLinkID(ostream &fp, string obj) {
    string linkVarName;
    string linkIdFreeString;

    linkVarName = string(obj) + string("->") + linkIDName;

    if (getRoot(name) == "Alg")
    {
        linkIdFreeString = proc.freeDynamicLinkId(pType, cAlg, linkVarName);
    }
    else
    {
        linkIdFreeString = proc.freeDynamicLinkId(pType, cType, linkVarName);
    }
    fp << BLOCK_SPACE <<  linkIdFreeString << ";" << endl;
}


void Link::genCreate(ostream &fp, string obj) {
    if (linkIDName.compare(0, 16, "Alg_RadarProcess") == 0)
    {
        fp << BLOCK_SPACE << "status = System_linkCreate(" << obj << "->"
            << linkIDName << ", " << obj << "->" << prmName << ", "
            << obj << "->" << prmName << "->baseClassCreate.size);" << endl;
    }
    else if ((name.compare(0, 13, "AutosarIpcOut") == 0) ||
             (name.compare(0, 12, "AutosarIpcIn") == 0))
    {
        fp << BLOCK_SPACE << "status = System_linkCreate(" << obj << "->"
            << linkIDName << ", NULL, 0);" << endl;
    }
    else
    {
        fp << BLOCK_SPACE << "status = System_linkCreate(" << obj << "->"
            << linkIDName << ", &" << obj << "->" << prmName << ", sizeof("
            << obj << "->" << prmName << "));" << endl;
    }
    fp << BLOCK_SPACE << "UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);"
            << endl;
}

void Link::genStart(ostream &fp, string obj) {
    fp << BLOCK_SPACE << "status = System_linkStart(" << obj << "->"
            << linkIDName << ");" << endl;
    fp << BLOCK_SPACE << "UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);"
            << endl;
}

void Link::genStop(ostream &fp, string obj) {
    fp << BLOCK_SPACE << "status = System_linkStop(" << obj << "->"
            << linkIDName << ");" << endl;
    fp << BLOCK_SPACE << "UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);"
            << endl;
}

void Link::genDelete(ostream &fp, string obj) {
    fp << BLOCK_SPACE << "status = System_linkDelete(" << obj << "->"
            << linkIDName << ");" << endl;
    fp << BLOCK_SPACE << "UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);"
            << endl;
}

void Link::genStatistics(ostream &fp, string obj) {
    fp << BLOCK_SPACE <<"System_linkPrintStatistics("<<obj<<"->"<<linkIDName<<");" << endl;
}

void Link::genBufferStatistics(ostream &fp, string obj) {
    fp << BLOCK_SPACE <<"System_linkPrintBufferStatistics("<<obj<<"->"<<linkIDName<<");" << endl;
}
/********************************************************************************/
/********************************************************************************/
AVBReceive::AVBReceive(string nm) {
    cType = cAVBReceive;
    name = nm;
    linkIDName = name + string("LinkID");
    prmName = name + string("Prm");
    matrixPos = -1;
    execPos = -1;
    procID = -1;
    pType = IPU1_1;
    mulInQue = false;
    mulOutQue = false;
}

AVBReceive::~AVBReceive() {
}
void AVBReceive::genIncludes(ostream &fp) {
    CHECK_ERROR_ABORT(inLink.size() == 0, "Error: Link ["+name+"] must have NO incoming link !!!");
    CHECK_ERROR_ABORT(outLink.size() == 1, "Error: Link ["+name+"] must have one outgoing link !!!");
    fp << "#include <include/link_api/avbRxLink.h>"<< endl;
}
void AVBReceive::genLinkID(ostream &fp) {
    fp << BLOCK_SPACE << setw(IDTYPE_WIDTH) << left << "UInt32" << linkIDName << ";" << endl;
}
void AVBReceive::genCreatePrms(ostream &fp) {
    fp << BLOCK_SPACE << setw(TYPENAME_WIDTH) << left << "AvbRxLink_CreateParams " << prmName
            << ";" << endl;
}
void AVBReceive::genResetLinkPrms(ostream &fp, string obj) {
    fp << BLOCK_SPACE << "AvbRxLink_CreateParams_Init(&" << obj << "->"
            << prmName << ");" << endl;
}
int AVBReceive::setInLink(Link* obj) {
    CHECK_ERROR_ABORT(SHOULD_NOT_REACH, "Error: Link ["+name+"] should not have any incoming link !!!");
    return 0;
}
int AVBReceive::setOutLink(Link* obj) {
    CHECK_ERROR_ABORT(outLink.size() == 0, "Error: Link ["+name+"] must have one and only one outgoing link !!!");
    outLink.push_back(make_pair(obj, -1));
    return (outLink.size() - 1);
}
void AVBReceive::genSetLinkPrms(ostream &fp, string obj)
{
}
/********************************************************************************/
AVBTransmit::AVBTransmit(string nm) {
    cType = cAVBTransmit;
    name = nm;
    linkIDName = name + string("LinkID");
    prmName = name + string("Prm");
    matrixPos = -1;
    execPos = -1;
    procID = -1;
    pType = IPU1_1;
    mulInQue = true;
    mulOutQue = false;
}

AVBTransmit::~AVBTransmit() {
}
void AVBTransmit::genIncludes(ostream &fp) {
    CHECK_ERROR_ABORT(inLink.size() > 0, "Error: Link ["+name+"] must have atleast one incoming link !!!");
    CHECK_ERROR_ABORT(outLink.size() == 0, "Error: Link ["+name+"] must have NO outgoing link !!!");
    fp << "#include <include/link_api/avbTxLink.h>"<< endl;
}
void AVBTransmit::genLinkID(ostream &fp) {
    fp << BLOCK_SPACE << setw(10) << left << "UInt32" << linkIDName << ";" << endl;
}
void AVBTransmit::genCreatePrms(ostream &fp) {
    fp << BLOCK_SPACE << setw(40) << left << "AvbTxLink_CreateParams " << prmName
            << ";" << endl;
}
void AVBTransmit::genResetLinkPrms(ostream &fp, string obj) {
    fp << BLOCK_SPACE << "AvbTxLink_CreateParams_Init(&" << obj << "->"
            << prmName << ");" << endl;
}
int AVBTransmit::setInLink(Link* obj) {
    CHECK_ERROR_ABORT(inLink.size() == 0, "Error: Link ["+name+"] must have one and only one incoming link !!!");
    inLink.push_back(make_pair(obj, -1));
    return (inLink.size() - 1);
}
int AVBTransmit::setOutLink(Link* obj) {
   CHECK_ERROR_ABORT(SHOULD_NOT_REACH, "Error: Link ["+name+"] must have NO outgoing link !!!");
   return -1;
}
void AVBTransmit::genSetLinkPrms(ostream &fp, string obj)
{
    fp<<BLOCK_SPACE << "(" << obj << "->" << prmName <<")." << "numInQue = " << inLink.size()<<";"<<endl;
}

/********************************************************************************/
TFDTPReceive::TFDTPReceive(string nm) {
    cType = cTFDTPReceive;
    name = nm;
    linkIDName = name + string("LinkID");
    prmName = name + string("Prm");
    matrixPos = -1;
    execPos = -1;
    procID = -1;
    pType = IPU1_1;
    mulInQue = false;
    mulOutQue = false;
}

TFDTPReceive::~TFDTPReceive() {
}
void TFDTPReceive::genIncludes(ostream &fp) {
    CHECK_ERROR_ABORT(inLink.size() == 0, "Error: Link ["+name+"] must have NO incoming link !!!");
    CHECK_ERROR_ABORT(outLink.size() == 1, "Error: Link ["+name+"] must have one outgoing link !!!");
    fp << "#include <include/link_api/tfdtpRxLink.h>"<< endl;
}
void TFDTPReceive::genLinkID(ostream &fp) {
    fp << BLOCK_SPACE << setw(10) << left << "UInt32" << linkIDName << ";" << endl;
}
void TFDTPReceive::genCreatePrms(ostream &fp) {
    fp << BLOCK_SPACE << setw(40) << left << "TfdtpRxLink_CreateParams " << prmName
            << ";" << endl;
}
void TFDTPReceive::genResetLinkPrms(ostream &fp, string obj) {
    fp << BLOCK_SPACE << "TfdtpRxLink_CreateParams_Init(&" << obj << "->"
            << prmName << ");" << endl;
}
int TFDTPReceive::setInLink(Link* obj) {
    CHECK_ERROR_ABORT(SHOULD_NOT_REACH, "Error: Link ["+name+"] should not have any incoming link !!!");
    return 0;
}
int TFDTPReceive::setOutLink(Link* obj) {
    CHECK_ERROR_ABORT(outLink.size() == 0, "Error: Link ["+name+"] must have one and only one outgoing link !!!");
    outLink.push_back(make_pair(obj, -1));
    return (outLink.size() - 1);
}
void TFDTPReceive::genSetLinkPrms(ostream &fp, string obj)
{
}
/********************************************************************************/
Alg::Alg(string nm) {
    cType = cAlg;
    name = nm;
    linkIDName = name + string("LinkID");
    prmName = name + string("Prm");
    execPos = -1;
    procID = -1;
    pType = IPU1_0;
    mulInQue = false;
    mulOutQue = false;
    mulInQue = false;
}

Alg::~Alg() {
}
void Alg::genIncludes(ostream &fp) {
    fp << "#include <include/link_api/algorithmLink.h>"<< endl;
}
void Alg::genLinkID(ostream &fp) {
    fp << BLOCK_SPACE << setw(IDTYPE_WIDTH) << left << "UInt32" << linkIDName << ";" << endl;
}
void Alg::genCreatePrms(ostream &fp) {
    string prms = "AlgorithmLink_" + getSecRoot(name) + "CreateParams";
    fp << BLOCK_SPACE << setw(TYPENAME_WIDTH) << left << prms << name << "Prm" << ";" << endl;
}
void Alg::genResetLinkPrms(ostream &fp, string obj) {
    string init = "AlgorithmLink_" + getSecRoot(name) + "_Init";
    fp << BLOCK_SPACE << init << "(&" << obj << "->" << prmName << ");" << endl;
}
int Alg::setInLink(Link* obj) //returns QueueID
{
    inLink.push_back(make_pair(obj, -1));
    if(inLink.size() > 1)
        mulInQue = true;
    return (inLink.size() - 1);
}
int Alg::setOutLink(Link* obj) //return QueueID
{
    outLink.push_back(make_pair(obj, -1));
    if(outLink.size() > 1)
        mulOutQue = true;
    return (outLink.size() - 1);
}
void Alg::genSetLinkPrms(ostream &fp, string obj)
{
}
/********************************************************************************/
Alg_ColorToGray::Alg_ColorToGray(string nm) {
    cType = cAlg_ColorToGray;
    name = nm;
    linkIDName = name + string("LinkID");
    prmName = name + string("Prm");
    execPos = -1;
    procID = -1;
    pType = IPU1_0;
    mulInQue = false;
    mulOutQue = false;
}

Alg_ColorToGray::~Alg_ColorToGray() {
}
void Alg_ColorToGray::genIncludes(ostream &fp) {
    CHECK_ERROR_ABORT(inLink.size() == 1, "Error: Link ["+name+"] must have one incoming link !!!");
    CHECK_ERROR_ABORT(outLink.size() == 1, "Error: Link ["+name+"] must have one outgoing link !!!");
    fp << "#include <include/alglink_api/algorithmLink_colorToGray.h>"<< endl;
}
void Alg_ColorToGray::genLinkID(ostream &fp) {
    fp << BLOCK_SPACE << setw(IDTYPE_WIDTH) << left << "UInt32" << linkIDName << ";" << endl;
}
void Alg_ColorToGray::genCreatePrms(ostream &fp) {
    fp << BLOCK_SPACE << setw(TYPENAME_WIDTH) << left
            << "AlgorithmLink_ColorToGrayCreateParams " << name << "Prm" << ";" << endl;
}
void Alg_ColorToGray::genResetLinkPrms(ostream &fp, string obj) {
}

int Alg_ColorToGray::setInLink(Link* obj) //returns QueueID
{
    CHECK_ERROR_ABORT(inLink.size() == 0, "Error: Link ["+name+"] must have one and only one incoming link !!!");
    inLink.push_back(make_pair(obj, -1));
    return (inLink.size() - 1);
}
int Alg_ColorToGray::setOutLink(Link* obj) //return QueueID
{
    CHECK_ERROR_ABORT(outLink.size() == 0, "Error: Link ["+name+"] must have one and only one outgoing link !!!");
    outLink.push_back(make_pair(obj, -1));
    return (outLink.size() - 1);
}
void Alg_ColorToGray::genSetLinkPrms(ostream &fp, string obj)
{
    fp<<BLOCK_SPACE << "(" << obj << "->" << prmName <<")." << "baseClassCreate.size  = sizeof(AlgorithmLink_ColorToGrayCreateParams);"<<endl;
    if(pType == DSP1 || pType == DSP2)
        fp<<BLOCK_SPACE << "(" << obj << "->" << prmName <<")." << "baseClassCreate.algId  = ALGORITHM_LINK_DSP_ALG_COLORTOGRAY;"<<endl;
    else if(pType == A15)
        fp<<BLOCK_SPACE << "(" << obj << "->" << prmName <<")." << "baseClassCreate.algId  = ALGORITHM_LINK_A15_ALG_COLORTOGRAY;"<<endl;
}
/********************************************************************************/
Alg_DMASwMs::Alg_DMASwMs(string nm) {
    cType = cAlg_DMASwMs;
    name = nm;
    linkIDName = name + string("LinkID");
    prmName = name + string("Prm");
    execPos = -1;
    procID = -1;
    pType = IPU1_0;
    mulInQue = false;
    mulOutQue = false;
}

Alg_DMASwMs::~Alg_DMASwMs() {
}
void Alg_DMASwMs::genIncludes(ostream &fp) {
    CHECK_ERROR_ABORT(inLink.size() == 1, "Error: Link ["+name+"] must have one incoming link !!!");
    CHECK_ERROR_ABORT(outLink.size() == 1, "Error: Link ["+name+"] must have one outgoing link !!!");
    fp << "#include <include/alglink_api/algorithmLink_dmaSwMs.h>"<< endl;
}
void Alg_DMASwMs::genLinkID(ostream &fp) {
    fp << BLOCK_SPACE << setw(IDTYPE_WIDTH) << left << "UInt32" << linkIDName << ";" << endl;
}
void Alg_DMASwMs::genCreatePrms(ostream &fp) {
    fp << BLOCK_SPACE << setw(TYPENAME_WIDTH) << left << "AlgorithmLink_DmaSwMsCreateParams"
            << name << "Prm" << ";" << endl;
}
void Alg_DMASwMs::genResetLinkPrms(ostream &fp, string obj) {
    fp << BLOCK_SPACE << "AlgorithmLink_DmaSwMsCreateParams_Init(&" << obj << "->"\
            << prmName << ");" << endl;
}
int Alg_DMASwMs::setInLink(Link* obj) //returns QueueID
{
    CHECK_ERROR_ABORT(inLink.size() == 0, "Error: Link ["+name+"] must have one and only one incoming link !!!");
    inLink.push_back(make_pair(obj, -1));
    return (inLink.size() - 1);
}
int Alg_DMASwMs::setOutLink(Link* obj) //return QueueID
{
    CHECK_ERROR_ABORT(outLink.size() == 0, "Error: Link ["+name+"] must have one and only one outgoing link !!!");
    outLink.push_back(make_pair(obj, -1));
    return (outLink.size() - 1);
}
void Alg_DMASwMs::genSetLinkPrms(ostream &fp, string obj)
{
    fp<<BLOCK_SPACE << "(" << obj << "->" << prmName <<")." << "baseClassCreate.size  = sizeof(AlgorithmLink_DmaSwMsCreateParams);"<<endl;
    if(pType == DSP1 || pType == DSP2)
        fp<<BLOCK_SPACE << "(" << obj << "->" << prmName <<")." << "baseClassCreate.algId  = ALGORITHM_LINK_DSP_ALG_DMA_SWMS;"<<endl;
    else if(pType == A15)
        fp<<BLOCK_SPACE << "(" << obj << "->" << prmName <<")." << "baseClassCreate.algId  = ALGORITHM_LINK_A15_ALG_DMA_SWMS;"<<endl;
    else if(pType == IPU1_0 || pType == IPU1_1 || pType == IPU2)
        fp<<BLOCK_SPACE << "(" << obj << "->" << prmName <<")." << "baseClassCreate.algId  = ALGORITHM_LINK_IPU_ALG_DMA_SWMS;"<<endl;
}
/********************************************************************************/
Alg_VPESwMs::Alg_VPESwMs(string nm) {
    cType = cAlg_VPESwMs;
    name = nm;
    linkIDName = name + string("LinkID");
    prmName = name + string("Prm");
    execPos = -1;
    procID = -1;
    pType = IPU1_0;
    mulInQue = false;
    mulOutQue = false;
}

Alg_VPESwMs::~Alg_VPESwMs() {
}
void Alg_VPESwMs::genIncludes(ostream &fp) {
    CHECK_ERROR_ABORT(inLink.size() == 1, "Error: Link ["+name+"] must have one incoming link !!!");
    CHECK_ERROR_ABORT(outLink.size() == 1, "Error: Link ["+name+"] must have one outgoing link !!!");
    fp << "#include <include/alglink_api/algorithmLink_vpeSwMs.h>"<< endl;
}
void Alg_VPESwMs::genLinkID(ostream &fp) {
    fp << BLOCK_SPACE << setw(IDTYPE_WIDTH) << left << "UInt32" << linkIDName << ";" << endl;
}
void Alg_VPESwMs::genCreatePrms(ostream &fp) {
    fp << BLOCK_SPACE << setw(TYPENAME_WIDTH) << left << "AlgorithmLink_VpeSwMsCreateParams"
            << name << "Prm" << ";" << endl;
}
void Alg_VPESwMs::genResetLinkPrms(ostream &fp, string obj) {
    fp << BLOCK_SPACE << "AlgorithmLink_VpeSwMsCreateParams_Init(&" << obj << "->"\
            << prmName << ");" << endl;
}
int Alg_VPESwMs::setInLink(Link* obj) //returns QueueID
{
    CHECK_ERROR_ABORT(inLink.size() == 0, "Error: Link ["+name+"] must have one and only one incoming link !!!");
    inLink.push_back(make_pair(obj, -1));
    return (inLink.size() - 1);
}
int Alg_VPESwMs::setOutLink(Link* obj) //return QueueID
{
    CHECK_ERROR_ABORT(outLink.size() == 0, "Error: Link ["+name+"] must have one and only one outgoing link !!!");
    outLink.push_back(make_pair(obj, -1));
    return (outLink.size() - 1);
}
void Alg_VPESwMs::genSetLinkPrms(ostream &fp, string obj)
{
    fp<<BLOCK_SPACE << "(" << obj << "->" << prmName <<")." << "baseClassCreate.size  = sizeof(AlgorithmLink_VpeSwMsCreateParams);"<<endl;
    if(pType == IPU1_0 || pType == IPU1_1 || pType == IPU2)
        fp<<BLOCK_SPACE << "(" << obj << "->" << prmName <<")." << "baseClassCreate.algId  = ALGORITHM_LINK_IPU_ALG_VPE_SWMS;"<<endl;
}
/********************************************************************************/
Alg_DenseOptFlow::Alg_DenseOptFlow(string nm) {
    cType = cAlg_DenseOptFlow;
    name = nm;
    linkIDName = name + string("LinkID");
    prmName = name + string("Prm");
    execPos = -1;
    procID = -1;
    pType = IPU1_0;
    mulInQue = false;
    mulOutQue = false;
}

Alg_DenseOptFlow::~Alg_DenseOptFlow() {
}
void Alg_DenseOptFlow::genIncludes(ostream &fp) {
    CHECK_ERROR_ABORT(inLink.size() == 1, "Error: Link ["+name+"] must have one incoming link !!!");
    CHECK_ERROR_ABORT(outLink.size() == 1, "Error: Link ["+name+"] must have one outgoing link !!!");
    fp << "#include <include/alglink_api/algorithmLink_denseOpticalFlow.h>"<< endl;
}
void Alg_DenseOptFlow::genLinkID(ostream &fp) {
    fp << BLOCK_SPACE << setw(IDTYPE_WIDTH) << left << "UInt32" << linkIDName << ";" << endl;
}
void Alg_DenseOptFlow::genCreatePrms(ostream &fp) {
    fp << BLOCK_SPACE << setw(TYPENAME_WIDTH) << left
            << "AlgorithmLink_DenseOptFlowCreateParams " << name << "Prm"
            << ";" << endl;
}
void Alg_DenseOptFlow::genResetLinkPrms(ostream &fp, string obj) {
    fp << BLOCK_SPACE << "AlgorithmLink_DenseOptFlowCreateParams_Init(&" << obj\
            << "->" << prmName << ");" << endl;
}
int Alg_DenseOptFlow::setInLink(Link* obj) //returns QueueID
{
    CHECK_ERROR_ABORT(inLink.size() == 0, "Error: Link ["+name+"] must have one and only one incoming link !!!");
    inLink.push_back(make_pair(obj, -1));
    return (inLink.size() - 1);
}
int Alg_DenseOptFlow::setOutLink(Link* obj) //return QueueID
{
    CHECK_ERROR_ABORT(outLink.size() == 0, "Error: Link ["+name+"] must have one and only one outgoing link !!!");
    outLink.push_back(make_pair(obj, -1));
    return (outLink.size() - 1);
}
void Alg_DenseOptFlow::genSetLinkPrms(ostream &fp, string obj)
{
    fp<<BLOCK_SPACE << "(" << obj << "->" << prmName <<")." << "baseClassCreate.size  = sizeof(AlgorithmLink_DenseOptFlowCreateParams);"<<endl;
    if(pType == EVE1 || pType == EVE2 || pType == EVE3 || pType == EVE4)
        fp<<BLOCK_SPACE << "(" << obj << "->" << prmName <<")." << "baseClassCreate.algId  = ALGORITHM_LINK_EVE_ALG_DENSE_OPTICAL_FLOW;"<<endl;
}
/********************************************************************************/
Alg_EdgeDetect::Alg_EdgeDetect(string nm) {
    cType = cAlg_EdgeDetect;
    name = nm;
    linkIDName = name + string("LinkID");
    prmName = name + string("Prm");
    execPos = -1;
    procID = -1;
    pType = IPU1_0;
    mulInQue = false;
    mulOutQue = false;
}

Alg_EdgeDetect::~Alg_EdgeDetect() {
}
void Alg_EdgeDetect::genIncludes(ostream &fp) {
    CHECK_ERROR_ABORT(inLink.size() == 1, "Error: Link ["+name+"] must have one incoming link !!!");
    CHECK_ERROR_ABORT(outLink.size() == 1, "Error: Link ["+name+"] must have one outgoing link !!!");
    fp << "#include <include/alglink_api/algorithmLink_edgeDetection.h>"<< endl;
}
void Alg_EdgeDetect::genLinkID(ostream &fp) {
    fp << BLOCK_SPACE << setw(IDTYPE_WIDTH) << left << "UInt32" << linkIDName << ";" << endl;
}
void Alg_EdgeDetect::genCreatePrms(ostream &fp) {
    fp << BLOCK_SPACE << setw(TYPENAME_WIDTH) << left
            << "AlgorithmLink_EdgeDetectionCreateParams " << name << "Prm"
            << ";" << endl;
}
void Alg_EdgeDetect::genResetLinkPrms(ostream &fp, string obj) {
}
int Alg_EdgeDetect::setInLink(Link* obj) //returns QueueID
{
    CHECK_ERROR_ABORT(inLink.size() == 0, "Error: Link ["+name+"] must have one and only one incoming link !!!");
    inLink.push_back(make_pair(obj, -1));
    return (inLink.size() - 1);
}
int Alg_EdgeDetect::setOutLink(Link* obj) //return QueueID
{
    CHECK_ERROR_ABORT(outLink.size() == 0, "Error: Link ["+name+"] must have one and only one outgoing link !!!");
    outLink.push_back(make_pair(obj, -1));
    return (outLink.size() - 1);
}
void Alg_EdgeDetect::genSetLinkPrms(ostream &fp, string obj)
{
    fp<<BLOCK_SPACE << "(" << obj << "->" << prmName <<")." << "baseClassCreate.size  = sizeof(AlgorithmLink_EdgeDetectionCreateParams);"<<endl;
    if(pType == EVE1 || pType == EVE2  || pType == EVE3 || pType == EVE4)
        fp<<BLOCK_SPACE << "(" << obj << "->" << prmName <<")." << "baseClassCreate.algId  = ALGORITHM_LINK_EVE_ALG_EDGEDETECTION;"<<endl;
}
/********************************************************************************/
Alg_SoftIsp::Alg_SoftIsp(string nm) {
    cType = cAlg_SoftIsp;
    name = nm;
    linkIDName = name + string("LinkID");
    prmName = name + string("Prm");
    execPos = -1;
    procID = -1;
    pType = IPU1_0;
    mulInQue = false;
    mulOutQue = false;
}

Alg_SoftIsp::~Alg_SoftIsp() {
}
void Alg_SoftIsp::genIncludes(ostream &fp) {
    CHECK_ERROR_ABORT(inLink.size() == 1, "Error: Link ["+name+"] must have one incoming link !!!");
    CHECK_ERROR_ABORT(outLink.size() == 1, "Error: Link ["+name+"] must have one outgoing link !!!");
    fp << "#include <include/alglink_api/algorithmLink_softIsp.h>"<< endl;
}
void Alg_SoftIsp::genLinkID(ostream &fp) {
    fp << BLOCK_SPACE << setw(IDTYPE_WIDTH) << left << "UInt32" << linkIDName << ";" << endl;
}
void Alg_SoftIsp::genCreatePrms(ostream &fp) {
    fp << BLOCK_SPACE << setw(TYPENAME_WIDTH) << left
            << "AlgorithmLink_SoftIspCreateParams " << name << "Prm"
            << ";" << endl;
}
void Alg_SoftIsp::genResetLinkPrms(ostream &fp, string obj) {
    fp << BLOCK_SPACE << "AlgorithmLink_SoftIsp_Init(&" << obj << "->"\
            << prmName << ");" << endl;
}
int Alg_SoftIsp::setInLink(Link* obj) //returns QueueID
{
    CHECK_ERROR_ABORT(inLink.size() == 0, "Error: Link ["+name+"] must have one and only one incoming link !!!");
    inLink.push_back(make_pair(obj, -1));
    return (inLink.size() - 1);
}
int Alg_SoftIsp::setOutLink(Link* obj) //return QueueID
{
    CHECK_ERROR_ABORT(outLink.size() == 0, "Error: Link ["+name+"] must have one and only one outgoing link !!!");
    outLink.push_back(make_pair(obj, -1));
    return (outLink.size() - 1);
}
void Alg_SoftIsp::genSetLinkPrms(ostream &fp, string obj)
{
    fp<<BLOCK_SPACE << "(" << obj << "->" << prmName <<")." << "baseClassCreate.size  = sizeof(AlgorithmLink_SoftIspCreateParams);"<<endl;
    if(pType == EVE1 || pType == EVE2  || pType == EVE3 || pType == EVE4)
        fp<<BLOCK_SPACE << "(" << obj << "->" << prmName <<")." << "baseClassCreate.algId  = ALGORITHM_LINK_EVE_ALG_SOFTISP;"<<endl;
}
/********************************************************************************/
Alg_IssAewb::Alg_IssAewb(string nm) {
    cType = cAlg_IssAewb;
    name = nm;
    linkIDName = name + string("LinkID");
    prmName = name + string("Prm");
    execPos = -1;
    procID = -1;
    pType = IPU1_0;
    mulInQue = false;
    mulOutQue = false;
}

Alg_IssAewb::~Alg_IssAewb() {
}
void Alg_IssAewb::genIncludes(ostream &fp) {
    CHECK_ERROR_ABORT(inLink.size() == 1, "Error: Link ["+name+"] must have one incoming link !!!");
    CHECK_ERROR_ABORT(outLink.size() == 0, "Error: Link ["+name+"] must NO outgoing link !!!");
    fp << "#include <src/rtos/iss/include/algorithmLink_issAewb.h>"<< endl;
}
void Alg_IssAewb::genLinkID(ostream &fp) {
    fp << BLOCK_SPACE << setw(IDTYPE_WIDTH) << left << "UInt32" << linkIDName << ";" << endl;
}
void Alg_IssAewb::genCreatePrms(ostream &fp) {
    fp << BLOCK_SPACE << setw(TYPENAME_WIDTH) << left
            << "AlgorithmLink_IssAewbCreateParams " << name << "Prm"
            << ";" << endl;
}
void Alg_IssAewb::genResetLinkPrms(ostream &fp, string obj) {
    fp << BLOCK_SPACE << "AlgorithmLink_IssAewb_Init(&" << obj << "->"\
            << prmName << ");" << endl;
}
int Alg_IssAewb::setInLink(Link* obj) //returns QueueID
{
    CHECK_ERROR_ABORT(inLink.size() == 0, "Error: Link ["+name+"] must have one and only one incoming link !!!");
    inLink.push_back(make_pair(obj, -1));
    return (inLink.size() - 1);
}
int Alg_IssAewb::setOutLink(Link* obj) //return QueueID
{
    CHECK_ERROR(SHOULD_NOT_REACH, "Error: Link ["+name+"] must have NO outgoing link !!!");
    return -1;
}
void Alg_IssAewb::genSetLinkPrms(ostream &fp, string obj)
{
    fp<<BLOCK_SPACE << "(" << obj << "->" << prmName <<")." << "baseClassCreate.size  = sizeof(AlgorithmLink_IssAewbCreateParams);"<<endl;
    fp<<BLOCK_SPACE << "(" << obj << "->" << prmName <<")." << "baseClassCreate.algId  = ALGORITHM_LINK_IPU_ALG_ISS_AEWB1;"<<endl;
}
/********************************************************************************/
Alg_Crc::Alg_Crc(string nm) {
    cType = cAlg_Crc;
    name = nm;
    linkIDName = name + string("LinkID");
    prmName = name + string("Prm");
    execPos = -1;
    procID = -1;
    pType = IPU1_0;
    mulInQue = false;
    mulOutQue = false;
}

Alg_Crc::~Alg_Crc() {
}
void Alg_Crc::genIncludes(ostream &fp) {
    CHECK_ERROR_ABORT(inLink.size() == 1, "Error: Link ["+name+"] must have one incoming link !!!");
    CHECK_ERROR_ABORT(outLink.size() == 0, "Error: Link ["+name+"] must NO outgoing link !!!");
    fp << "#include <include/alglink_api/algorithmLink_crc.h>"<< endl;
}
void Alg_Crc::genLinkID(ostream &fp) {
    fp << BLOCK_SPACE << setw(IDTYPE_WIDTH) << left << "UInt32" << linkIDName << ";" << endl;
}
void Alg_Crc::genCreatePrms(ostream &fp) {
    fp << BLOCK_SPACE << setw(TYPENAME_WIDTH) << left
            << "AlgorithmLink_CrcCreateParams " << name << "Prm"
            << ";" << endl;
}
void Alg_Crc::genResetLinkPrms(ostream &fp, string obj) {
    fp << BLOCK_SPACE << "AlgorithmLink_Crc_Init(&" << obj << "->"\
            << prmName << ");" << endl;
}
int Alg_Crc::setInLink(Link* obj) //returns QueueID
{
    CHECK_ERROR_ABORT(inLink.size() == 0, "Error: Link ["+name+"] must have one and only one incoming link !!!");
    inLink.push_back(make_pair(obj, -1));
    return (inLink.size() - 1);
}
int Alg_Crc::setOutLink(Link* obj) //return QueueID
{
    CHECK_ERROR(SHOULD_NOT_REACH, "Error: Link ["+name+"] must have NO outgoing link !!!");
    return -1;
}
void Alg_Crc::genSetLinkPrms(ostream &fp, string obj)
{
    fp<<BLOCK_SPACE << "(" << obj << "->" << prmName <<")." << "baseClassCreate.size  = sizeof(AlgorithmLink_CrcCreateParams);"<<endl;
    fp<<BLOCK_SPACE << "(" << obj << "->" << prmName <<")." << "baseClassCreate.algId  = ALGORITHM_LINK_IPU_ALG_HW_CRC;"<<endl;
}
/********************************************************************************/
Alg_FeaturePlaneComputation::Alg_FeaturePlaneComputation(string nm) {
    cType = cAlg_FeaturePlaneComputation;
    name = nm;
    linkIDName = name + string("LinkID");
    prmName = name + string("Prm");
    execPos = -1;
    procID = -1;
    pType = IPU1_0;
    mulInQue = false;
    mulOutQue = false;
}

Alg_FeaturePlaneComputation::~Alg_FeaturePlaneComputation() {
}
void Alg_FeaturePlaneComputation::genIncludes(ostream &fp) {
    CHECK_ERROR_ABORT(inLink.size() == 1, "Error: Link ["+name+"] must have one incoming link !!!");
    CHECK_ERROR_ABORT(outLink.size() == 1, "Error: Link ["+name+"] must have one outgoing link !!!");
    fp << "#include <include/alglink_api/algorithmLink_featurePlaneComputation.h>"<< endl;
}
void Alg_FeaturePlaneComputation::genLinkID(ostream &fp) {
    fp << BLOCK_SPACE << setw(IDTYPE_WIDTH) << left << "UInt32" << linkIDName << ";" << endl;
}
void Alg_FeaturePlaneComputation::genCreatePrms(ostream &fp) {
    fp << BLOCK_SPACE << setw(TYPENAME_WIDTH) << left\
            << "AlgorithmLink_FeaturePlaneComputationCreateParams " << name << "Prm" << ";" << endl;
}
void Alg_FeaturePlaneComputation::genResetLinkPrms(ostream &fp, string obj) {
    fp << BLOCK_SPACE << "AlgorithmLink_FeatureComputation_Init(&" << obj << "->"\
            << prmName << ");" << endl;
}
int Alg_FeaturePlaneComputation::setInLink(Link* obj) //returns QueueID
{
    CHECK_ERROR_ABORT(inLink.size() == 0, "Error: Link ["+name+"] must have one and only one incoming link !!!");
    inLink.push_back(make_pair(obj, -1));
    return (inLink.size() - 1);
}
int Alg_FeaturePlaneComputation::setOutLink(Link* obj) //return QueueID
{
    CHECK_ERROR_ABORT(outLink.size() == 0, "Error: Link ["+name+"] must have one and only one outgoing link !!!");
    outLink.push_back(make_pair(obj, -1));
    return (outLink.size() - 1);
}
void Alg_FeaturePlaneComputation::genSetLinkPrms(ostream &fp, string obj)
{
    fp<<BLOCK_SPACE << "(" << obj << "->" << prmName <<")." << "baseClassCreate.size  = sizeof(AlgorithmLink_FeaturePlaneComputationCreateParams);"<<endl;
    if(pType == EVE1 || pType == EVE2  || pType == EVE3 || pType == EVE4)
        fp<<BLOCK_SPACE << "(" << obj << "->" << prmName <<")." << "baseClassCreate.algId  = ALGORITHM_LINK_EVE_ALG_FEATUREPLANECOMPUTE;"<<endl;
}
/********************************************************************************/
Alg_ImagePreProcess::Alg_ImagePreProcess(string nm) {
    cType = cAlg_ImagePreProcess;
    name = nm;
    linkIDName = name + string("LinkID");
    prmName = name + string("Prm");
    execPos = -1;
    procID = -1;
    pType = EVE1;
    mulInQue = false;
    mulOutQue = false;
}

Alg_ImagePreProcess::~Alg_ImagePreProcess() {
}
void Alg_ImagePreProcess::genIncludes(ostream &fp) {
    CHECK_ERROR_ABORT(inLink.size() == 1, "Error: Link ["+name+"] must have one incoming link !!!");
    CHECK_ERROR_ABORT(outLink.size() == 1, "Error: Link ["+name+"] must have one outgoing link !!!");
    fp << "#include <include/alglink_api/algorithmLink_imagePreProcess.h>"<< endl;
}
void Alg_ImagePreProcess::genLinkID(ostream &fp) {
    fp << BLOCK_SPACE << setw(IDTYPE_WIDTH) << left << "UInt32" << linkIDName << ";" << endl;
}
void Alg_ImagePreProcess::genCreatePrms(ostream &fp) {
    fp << BLOCK_SPACE << setw(TYPENAME_WIDTH) << left\
            << "AlgorithmLink_ImagePreProcessCreateParams " << name << "Prm" << ";" << endl;
}
void Alg_ImagePreProcess::genResetLinkPrms(ostream &fp, string obj) {
    fp << BLOCK_SPACE << "AlgorithmLink_ImagePreProcess_Init(&" << obj << "->"\
            << prmName << ");" << endl;
}
int Alg_ImagePreProcess::setInLink(Link* obj) //returns QueueID
{
    CHECK_ERROR_ABORT(inLink.size() == 0, "Error: Link ["+name+"] must have one and only one incoming link !!!");
    inLink.push_back(make_pair(obj, -1));
    return (inLink.size() - 1);
}
int Alg_ImagePreProcess::setOutLink(Link* obj) //return QueueID
{
    CHECK_ERROR_ABORT(outLink.size() == 0, "Error: Link ["+name+"] must have one and only one outgoing link !!!");
    outLink.push_back(make_pair(obj, -1));
    return (outLink.size() - 1);
}
void Alg_ImagePreProcess::genSetLinkPrms(ostream &fp, string obj)
{
    fp<<BLOCK_SPACE << "(" << obj << "->" << prmName <<")." << "baseClassCreate.size  = sizeof(AlgorithmLink_ImagePreProcessCreateParams);"<<endl;
    if(pType == EVE1 || pType == EVE2  || pType == EVE3 || pType == EVE4)
        fp<<BLOCK_SPACE << "(" << obj << "->" << prmName <<")." << "baseClassCreate.algId  = ALGORITHM_LINK_EVE_ALG_IMAGEPREPROCESS;"<<endl;
}
/********************************************************************************/
Alg_ImgPyramid::Alg_ImgPyramid(string nm) {
    cType = cAlg_ImgPyramid;
    name = nm;
    linkIDName = name + string("LinkID");
    prmName = name + string("Prm");
    execPos = -1;
    procID = -1;
    pType = IPU1_0;
    mulInQue = false;
    mulOutQue = false;
}

Alg_ImgPyramid::~Alg_ImgPyramid() {
}
void Alg_ImgPyramid::genIncludes(ostream &fp) {
    CHECK_ERROR_ABORT(inLink.size() == 1, "Error: Link ["+name+"] must have one incoming link !!!");
    CHECK_ERROR_ABORT(outLink.size() == 1, "Error: Link ["+name+"] must have one outgoing link !!!");
    fp << "#include <include/alglink_api/algorithmLink_imgPyramid.h>"<< endl;
}
void Alg_ImgPyramid::genLinkID(ostream &fp) {
    fp << BLOCK_SPACE << setw(IDTYPE_WIDTH) << left << "UInt32" << linkIDName << ";" << endl;
}
void Alg_ImgPyramid::genCreatePrms(ostream &fp) {
    fp << BLOCK_SPACE << setw(TYPENAME_WIDTH) << left\
            << "AlgorithmLink_ImgPyramidCreateParams " << name << "Prm" << ";" << endl;
}
void Alg_ImgPyramid::genResetLinkPrms(ostream &fp, string obj) {
    fp << BLOCK_SPACE << "AlgorithmLink_ImgPyramid_Init(&" << obj << "->"\
            << prmName << ");" << endl;
}
int Alg_ImgPyramid::setInLink(Link* obj) //returns QueueID
{
    CHECK_ERROR_ABORT(inLink.size() == 0, "Error: Link ["+name+"] must have one and only one incoming link !!!");
    inLink.push_back(make_pair(obj, -1));
    return (inLink.size() - 1);
}
int Alg_ImgPyramid::setOutLink(Link* obj) //return QueueID
{
    CHECK_ERROR_ABORT(outLink.size() == 0, "Error: Link ["+name+"] must have one and only one outgoing link !!!");
    outLink.push_back(make_pair(obj, -1));
    return (outLink.size() - 1);
}
void Alg_ImgPyramid::genSetLinkPrms(ostream &fp, string obj)
{
    fp<<BLOCK_SPACE << "(" << obj << "->" << prmName <<")." << "baseClassCreate.size  = sizeof(AlgorithmLink_ImgPyramidCreateParams);"<<endl;
    if(pType == IPU1_0 || pType == IPU1_1)
        fp<<BLOCK_SPACE << "(" << obj << "->" << prmName <<")." << "baseClassCreate.algId  = ALGORITHM_LINK_IPU_ALG_IMG_PYRAMID;"<<endl;
}
/********************************************************************************/
Alg_FPCompute::Alg_FPCompute(string nm) {
    cType = cAlg_FPCompute;
    name = nm;
    linkIDName = name + string("LinkID");
    prmName = name + string("Prm");
    execPos = -1;
    procID = -1;
    pType = EVE1;
    mulInQue = false;
    mulOutQue = false;
}

Alg_FPCompute::~Alg_FPCompute() {
}
void Alg_FPCompute::genIncludes(ostream &fp) {
    CHECK_ERROR_ABORT(inLink.size() == 1, "Error: Link ["+name+"] must have one incoming link !!!");
    CHECK_ERROR_ABORT(outLink.size() == 1, "Error: Link ["+name+"] must have one outgoing link !!!");
    fp << "#include <include/alglink_api/algorithmLink_fpCompute.h>"<< endl;
}
void Alg_FPCompute::genLinkID(ostream &fp) {
    fp << BLOCK_SPACE << setw(IDTYPE_WIDTH) << left << "UInt32" << linkIDName << ";" << endl;
}
void Alg_FPCompute::genCreatePrms(ostream &fp) {
    fp << BLOCK_SPACE << setw(TYPENAME_WIDTH) << left\
            << "AlgorithmLink_FPComputeCreateParams " << name << "Prm" << ";" << endl;
}
void Alg_FPCompute::genResetLinkPrms(ostream &fp, string obj) {
    fp << BLOCK_SPACE << "AlgorithmLink_FPCompute_Init(&" << obj << "->"\
            << prmName << ");" << endl;
}
int Alg_FPCompute::setInLink(Link* obj) //returns QueueID
{
    CHECK_ERROR_ABORT(inLink.size() == 0, "Error: Link ["+name+"] must have one and only one incoming link !!!");
    inLink.push_back(make_pair(obj, -1));
    return (inLink.size() - 1);
}
int Alg_FPCompute::setOutLink(Link* obj) //return QueueID
{
    CHECK_ERROR_ABORT(outLink.size() == 0, "Error: Link ["+name+"] must have one and only one outgoing link !!!");
    outLink.push_back(make_pair(obj, -1));
    return (outLink.size() - 1);
}
void Alg_FPCompute::genSetLinkPrms(ostream &fp, string obj)
{
    fp<<BLOCK_SPACE << "(" << obj << "->" << prmName <<")." << "baseClassCreate.size  = sizeof(AlgorithmLink_FPComputeCreateParams);"<<endl;
    if(pType == EVE1 || pType == EVE2  || pType == EVE3 || pType == EVE4)
        fp<<BLOCK_SPACE << "(" << obj << "->" << prmName <<")." << "baseClassCreate.algId  = ALGORITHM_LINK_EVE_ALG_FPCOMPUTE;"<<endl;
}

/********************************************************************************/
Alg_ObjectDetection::Alg_ObjectDetection(string nm) {
    cType = cAlg_ObjectDetection;
    name = nm;
    linkIDName = name + string("LinkID");
    prmName = name + string("Prm");
    execPos = -1;
    procID = -1;
    pType = IPU1_0;
    mulInQue = false;
    mulOutQue = false;
}

Alg_ObjectDetection::~Alg_ObjectDetection() {
}
void Alg_ObjectDetection::genIncludes(ostream &fp) {
    CHECK_ERROR_ABORT(inLink.size() == 1, "Error: Link ["+name+"] must have one incoming link !!!");
    CHECK_ERROR_ABORT(outLink.size() == 1, "Error: Link ["+name+"] must have one outgoing link !!!");

    fp << "#include <include/alglink_api/algorithmLink_objectDetection.h>"<< endl;
}
void Alg_ObjectDetection::genLinkID(ostream &fp) {

    fp << BLOCK_SPACE << setw(IDTYPE_WIDTH) << left << "UInt32" << linkIDName << ";" << endl;
}
void Alg_ObjectDetection::genCreatePrms(ostream &fp) {

    fp << BLOCK_SPACE << setw(TYPENAME_WIDTH) << left\
            << "AlgorithmLink_ObjectDetectionCreateParams " << name << "Prm" << ";" << endl;
}
void Alg_ObjectDetection::genResetLinkPrms(ostream &fp, string obj) {
    fp << BLOCK_SPACE << "AlgorithmLink_ObjectDetection_Init(&" << obj << "->"\
            << prmName << ");" << endl;
}
int Alg_ObjectDetection::setInLink(Link* obj) //returns QueueID
{
    CHECK_ERROR_ABORT(inLink.size() == 0, "Error: Link ["+name+"] must have one and only one incoming link !!!");
    inLink.push_back(make_pair(obj, -1));
    return (inLink.size() - 1);
}
int Alg_ObjectDetection::setOutLink(Link* obj) //return QueueID
{
    CHECK_ERROR_ABORT(outLink.size() == 0, "Error: Link ["+name+"] must have one and only one outgoing link !!!");
    outLink.push_back(make_pair(obj, -1));
    return (outLink.size() - 1);
}
void Alg_ObjectDetection::genSetLinkPrms(ostream &fp, string obj)
{
    fp<<BLOCK_SPACE << "(" << obj << "->" << prmName <<")." << "baseClassCreate.size  = sizeof(AlgorithmLink_ObjectDetectionCreateParams);"<<endl;
    if(pType == DSP1 || pType == DSP2)
        fp<<BLOCK_SPACE << "(" << obj << "->" << prmName <<")." << "baseClassCreate.algId  = ALGORITHM_LINK_DSP_ALG_OBJECTDETECTION;"<<endl;
}
/********************************************************************************/
Alg_ObjectClassification::Alg_ObjectClassification(string nm) {
    cType = cAlg_ObjectClassification;
    name = nm;
    linkIDName = name + string("LinkID");
    prmName = name + string("Prm");
    execPos = -1;
    procID = -1;
    pType = IPU1_0;
    mulInQue = false;
    mulOutQue = false;
}

Alg_ObjectClassification::~Alg_ObjectClassification() {
}
void Alg_ObjectClassification::genIncludes(ostream &fp) {
    CHECK_ERROR_ABORT(inLink.size() == 1, "Error: Link ["+name+"] must have one incoming link !!!");
    CHECK_ERROR_ABORT(outLink.size() == 1, "Error: Link ["+name+"] must have one outgoing link !!!");

    fp << "#include <include/alglink_api/algorithmLink_objectClassification.h>"<< endl;
}
void Alg_ObjectClassification::genLinkID(ostream &fp) {

    fp << BLOCK_SPACE << setw(IDTYPE_WIDTH) << left << "UInt32" << linkIDName << ";" << endl;
}
void Alg_ObjectClassification::genCreatePrms(ostream &fp) {

    fp << BLOCK_SPACE << setw(TYPENAME_WIDTH) << left\
            << "AlgorithmLink_ObjectClassificationCreateParams " << name << "Prm" << ";" << endl;
}
void Alg_ObjectClassification::genResetLinkPrms(ostream &fp, string obj) {
    fp << BLOCK_SPACE << "AlgorithmLink_ObjectClassification_Init(&" << obj << "->"\
            << prmName << ");" << endl;
}
int Alg_ObjectClassification::setInLink(Link* obj) //returns QueueID
{
    CHECK_ERROR_ABORT(inLink.size() == 0, "Error: Link ["+name+"] must have one and only one incoming link !!!");
    inLink.push_back(make_pair(obj, -1));
    return (inLink.size() - 1);
}
int Alg_ObjectClassification::setOutLink(Link* obj) //return QueueID
{
    CHECK_ERROR_ABORT(outLink.size() == 0, "Error: Link ["+name+"] must have one and only one outgoing link !!!");
    outLink.push_back(make_pair(obj, -1));
    return (outLink.size() - 1);
}
void Alg_ObjectClassification::genSetLinkPrms(ostream &fp, string obj)
{
    fp<<BLOCK_SPACE << "(" << obj << "->" << prmName <<")." << "baseClassCreate.size  = sizeof(AlgorithmLink_ObjectClassificationCreateParams);"<<endl;
    if(pType == DSP1 || pType == DSP2)
        fp<<BLOCK_SPACE << "(" << obj << "->" << prmName <<")." << "baseClassCreate.algId  = ALGORITHM_LINK_DSP_ALG_OBJECTCLASSIFICATION;"<<endl;
}
/********************************************************************************/
Alg_DriverMonitor::Alg_DriverMonitor(string nm) {
    cType = cAlg_DriverMonitor;
    name = nm;
    linkIDName = name + string("LinkID");
    prmName = name + string("Prm");
    execPos = -1;
    procID = -1;
    pType = IPU1_0;
    mulInQue = false;
    mulOutQue = false;
}

Alg_DriverMonitor::~Alg_DriverMonitor() {
}
void Alg_DriverMonitor::genIncludes(ostream &fp) {
    CHECK_ERROR_ABORT(inLink.size() == 1, "Error: Link ["+name+"] must have one incoming link !!!");
    fp << "#include <include/link_api/algorithmLink_driverMonitor.h>"<< endl;
}
void Alg_DriverMonitor::genLinkID(ostream &fp) {

    fp << BLOCK_SPACE << setw(IDTYPE_WIDTH) << left << "UInt32" << linkIDName << ";" << endl;
}
void Alg_DriverMonitor::genCreatePrms(ostream &fp) {

    fp << BLOCK_SPACE << setw(TYPENAME_WIDTH) << left\
            << "AlgorithmLink_DriverMonitorCreateParams " << name << "Prm" << ";" << endl;
}
void Alg_DriverMonitor::genResetLinkPrms(ostream &fp, string obj) {
    fp << BLOCK_SPACE << "AlgorithmLink_DriverMonitor_Init(&" << obj << "->"\
            << prmName << ");" << endl;
}
int Alg_DriverMonitor::setInLink(Link* obj) //returns QueueID
{
    CHECK_ERROR_ABORT(inLink.size() == 0, "Error: Link ["+name+"] must have one and only one incoming link !!!");
    inLink.push_back(make_pair(obj, -1));
    return (inLink.size() - 1);
}
int Alg_DriverMonitor::setOutLink(Link* obj) //return QueueID
{
    CHECK_ERROR_ABORT(outLink.size() == 0, "Error: Link ["+name+"] must have one and only one outgoing link !!!");
    outLink.push_back(make_pair(obj, -1));
    return (outLink.size() - 1);
}
void Alg_DriverMonitor::genSetLinkPrms(ostream &fp, string obj)
{
    fp<<BLOCK_SPACE << "(" << obj << "->" << prmName <<")." << "baseClassCreate.size  = sizeof(AlgorithmLink_DriverMonitorCreateParams);"<<endl;
    if(pType == DSP1 || pType == DSP2)
        fp<<BLOCK_SPACE << "(" << obj << "->" << prmName <<")." << "baseClassCreate.algId  = ALGORITHM_LINK_DSP_ALG_DRIVER_MONITOR;"<<endl;
}
/********************************************************************************/
Alg_FrameCopy::Alg_FrameCopy(string nm) {
    cType = cAlg_FrameCopy;
    name = nm;
    linkIDName = name + string("LinkID");
    prmName = name + string("Prm");
    execPos = -1;
    procID = -1;
    pType = IPU1_0;
    mulInQue = false;
    mulOutQue = false;
}

Alg_FrameCopy::~Alg_FrameCopy() {
}
void Alg_FrameCopy::genIncludes(ostream &fp) {
    CHECK_ERROR_ABORT(inLink.size() == 1, "Error: Link ["+name+"] must have one incoming link !!!");
    CHECK_ERROR_ABORT(outLink.size() == 1, "Error: Link ["+name+"] must have one outgoing link !!!");

    fp << "#include <include/alglink_api/algorithmLink_frameCopy.h>"<< endl;
}
void Alg_FrameCopy::genLinkID(ostream &fp) {

    fp << BLOCK_SPACE << setw(IDTYPE_WIDTH) << left << "UInt32" << linkIDName << ";" << endl;
}
void Alg_FrameCopy::genCreatePrms(ostream &fp) {

    fp << BLOCK_SPACE << setw(TYPENAME_WIDTH) << left\
            << "AlgorithmLink_FrameCopyCreateParams " << name << "Prm" << ";" << endl;
}
void Alg_FrameCopy::genResetLinkPrms(ostream &fp, string obj) {
    //fp << BLOCK_SPACE << "AlgorithmLink_FrameCopy_initPlugin(&" << obj << "->"\
            << prmName << ");" << endl;
}
int Alg_FrameCopy::setInLink(Link* obj) //returns QueueID
{
    CHECK_ERROR_ABORT(inLink.size() == 0, "Error: Link ["+name+"] must have one and only one incoming link !!!");
    inLink.push_back(make_pair(obj, -1));
    return (inLink.size() - 1);
}
int Alg_FrameCopy::setOutLink(Link* obj) //return QueueID
{
    CHECK_ERROR_ABORT(outLink.size() == 0, "Error: Link ["+name+"] must have one and only one outgoing link !!!");
    outLink.push_back(make_pair(obj, -1));
    return (outLink.size() - 1);
}

void Alg_FrameCopy::genSetLinkPrms(ostream &fp, string obj)
{
    fp<<BLOCK_SPACE << "(" << obj << "->" << prmName <<")." << "baseClassCreate.size  = sizeof(AlgorithmLink_FrameCopyCreateParams);"<<endl;
    if(pType == DSP1 || pType == DSP2)
        fp<<BLOCK_SPACE << "(" << obj << "->" << prmName <<")." << "baseClassCreate.algId  = ALGORITHM_LINK_DSP_ALG_FRAMECOPY;"<<endl;
    else if(pType == EVE1 || pType == EVE2 || pType == EVE3 || pType == EVE4)
        fp<<BLOCK_SPACE << "(" << obj << "->" << prmName <<")." << "baseClassCreate.algId  = ALGORITHM_LINK_EVE_ALG_FRAMECOPY;"<<endl;
    else if(pType == A15)
            fp<<BLOCK_SPACE << "(" << obj << "->" << prmName <<")." << "baseClassCreate.algId  = ALGORITHM_LINK_A15_ALG_FRAMECOPY;"<<endl;
}

/********************************************************************************/
Alg_SafeFrameCopy::Alg_SafeFrameCopy(string nm) {
    cType = cAlg_SafeFrameCopy;
    name = nm;
    linkIDName = name + string("LinkID");
    prmName = name + string("Prm");
    execPos = -1;
    procID = -1;
    pType = IPU1_0;
    mulInQue = false;
    mulOutQue = false;
}

Alg_SafeFrameCopy::~Alg_SafeFrameCopy() {
}
void Alg_SafeFrameCopy::genIncludes(ostream &fp) {
    CHECK_ERROR_ABORT(inLink.size() == 1, "Error: Link ["+name+"] must have one incoming link !!!");
    CHECK_ERROR_ABORT(outLink.size() == 1, "Error: Link ["+name+"] must have one outgoing link !!!");

    fp << "#include <include/alglink_api/algorithmLink_safeFrameCopy.h>"<< endl;
}
void Alg_SafeFrameCopy::genLinkID(ostream &fp) {

    fp << BLOCK_SPACE << setw(IDTYPE_WIDTH) << left << "UInt32" << linkIDName << ";" << endl;
}
void Alg_SafeFrameCopy::genCreatePrms(ostream &fp) {

    fp << BLOCK_SPACE << setw(TYPENAME_WIDTH) << left\
            << "AlgorithmLink_SafeFrameCopyCreateParams " << name << "Prm" << ";" << endl;
}
void Alg_SafeFrameCopy::genResetLinkPrms(ostream &fp, string obj) {
    //fp << BLOCK_SPACE << "AlgorithmLink_SafeFrameCopy_initPlugin(&" << obj << "->"\
            << prmName << ");" << endl;
}
int Alg_SafeFrameCopy::setInLink(Link* obj) //returns QueueID
{
    CHECK_ERROR_ABORT(inLink.size() == 0, "Error: Link ["+name+"] must have one and only one incoming link !!!");
    inLink.push_back(make_pair(obj, -1));
    return (inLink.size() - 1);
}
int Alg_SafeFrameCopy::setOutLink(Link* obj) //return QueueID
{
    CHECK_ERROR_ABORT(outLink.size() == 0, "Error: Link ["+name+"] must have one and only one outgoing link !!!");
    outLink.push_back(make_pair(obj, -1));
    return (outLink.size() - 1);
}

void Alg_SafeFrameCopy::genSetLinkPrms(ostream &fp, string obj)
{
    fp<<BLOCK_SPACE << "(" << obj << "->" << prmName <<")." << "baseClassCreate.size  = sizeof(AlgorithmLink_SafeFrameCopyCreateParams);"<<endl;
    if(pType == DSP1 || pType == DSP2)
        fp<<BLOCK_SPACE << "(" << obj << "->" << prmName <<")." << "baseClassCreate.algId  = ALGORITHM_LINK_DSP_ALG_SAFEFRAMECOPY;"<<endl;
    else if(pType == EVE1 || pType == EVE2 || pType == EVE3 || pType == EVE4)
        fp<<BLOCK_SPACE << "(" << obj << "->" << prmName <<")." << "baseClassCreate.algId  = ALGORITHM_LINK_EVE_ALG_SAFEFRAMECOPY;"<<endl;
    else if(pType == A15)
            fp<<BLOCK_SPACE << "(" << obj << "->" << prmName <<")." << "baseClassCreate.algId  = ALGORITHM_LINK_A15_ALG_SAFEFRAMECOPY;"<<endl;
}

/********************************************************************************/
Alg_MyAlgFinish::Alg_MyAlgFinish(string nm) {
    cType = cAlg_MyAlgFinish;
    name = nm;
    linkIDName = name + string("LinkID");
    prmName = name + string("Prm");
    execPos = -1;
    procID = -1;
    pType = IPU1_0;
    mulInQue = false;
    mulOutQue = false;
}

Alg_MyAlgFinish::~Alg_MyAlgFinish() {
}
void Alg_MyAlgFinish::genIncludes(ostream &fp) {
    CHECK_ERROR_ABORT(inLink.size() == 1, "Error: Link ["+name+"] must have one incoming link !!!");
    CHECK_ERROR_ABORT(outLink.size() == 1, "Error: Link ["+name+"] must have one outgoing link !!!");

    fp << "#include <apps/src/rtos/alg_plugins/myCustomAlg/myCustomLink.h>"<< endl;
}
void Alg_MyAlgFinish::genLinkID(ostream &fp) {

    fp << BLOCK_SPACE << setw(IDTYPE_WIDTH) << left << "UInt32" << linkIDName << ";" << endl;
}
void Alg_MyAlgFinish::genCreatePrms(ostream &fp) {

    fp << BLOCK_SPACE << setw(TYPENAME_WIDTH) << left\
            << "AlgorithmLink_MyAlgFinishCreateParams " << name << "Prm" << ";" << endl;
}
void Alg_MyAlgFinish::genResetLinkPrms(ostream &fp, string obj) {
    fp << BLOCK_SPACE << "AlgorithmLink_MyAlgFinishCreateParams_Init(&" << obj << "->"\
            << prmName << ");" << endl;
}
int Alg_MyAlgFinish::setInLink(Link* obj) //returns QueueID
{
    CHECK_ERROR_ABORT(inLink.size() == 0, "Error: Link ["+name+"] must have one and only one incoming link !!!");
    inLink.push_back(make_pair(obj, -1));
    return (inLink.size() - 1);
}
int Alg_MyAlgFinish::setOutLink(Link* obj) //return QueueID
{
    CHECK_ERROR_ABORT(outLink.size() == 0, "Error: Link ["+name+"] must have one and only one outgoing link !!!");
    outLink.push_back(make_pair(obj, -1));
    return (outLink.size() - 1);
}

void Alg_MyAlgFinish::genSetLinkPrms(ostream &fp, string obj)
{
    fp<<BLOCK_SPACE << "(" << obj << "->" << prmName <<")." << "baseClassCreate.size  = sizeof(AlgorithmLink_MyAlgFinishCreateParams);"<<endl;
    if(pType == IPU1_0)
        fp<<BLOCK_SPACE << "(" << obj << "->" << prmName <<")." << "baseClassCreate.algId  = ALGORITHM_LINK_IPU_ALG_MYALGFINISH;"<<endl;
}

/********************************************************************************/
Alg_MyAlg1::Alg_MyAlg1(string nm) {
    cType = cAlg_MyAlg1;
    name = nm;
    linkIDName = name + string("LinkID");
    prmName = name + string("Prm");
    execPos = -1;
    procID = -1;
    pType = IPU1_0;
    mulInQue = false;
    mulOutQue = false;
}

Alg_MyAlg1::~Alg_MyAlg1() {
}
void Alg_MyAlg1::genIncludes(ostream &fp) {
    CHECK_ERROR_ABORT(inLink.size() == 1, "Error: Link ["+name+"] must have one incoming link !!!");
    CHECK_ERROR_ABORT(outLink.size() == 1, "Error: Link ["+name+"] must have one outgoing link !!!");

    fp << "#include <apps/src/rtos/alg_plugins/myCustomAlg/myCustomLink.h>"<< endl;
}
void Alg_MyAlg1::genLinkID(ostream &fp) {

    fp << BLOCK_SPACE << setw(IDTYPE_WIDTH) << left << "UInt32" << linkIDName << ";" << endl;
}
void Alg_MyAlg1::genCreatePrms(ostream &fp) {

    fp << BLOCK_SPACE << setw(TYPENAME_WIDTH) << left\
            << "AlgorithmLink_MyAlg1CreateParams " << name << "Prm" << ";" << endl;
}
void Alg_MyAlg1::genResetLinkPrms(ostream &fp, string obj) {
    fp << BLOCK_SPACE << "AlgorithmLink_MyAlg1CreateParams_Init(&" << obj << "->"\
            << prmName << ");" << endl;
}
int Alg_MyAlg1::setInLink(Link* obj) //returns QueueID
{
    CHECK_ERROR_ABORT(inLink.size() == 0, "Error: Link ["+name+"] must have one and only one incoming link !!!");
    inLink.push_back(make_pair(obj, -1));
    return (inLink.size() - 1);
}
int Alg_MyAlg1::setOutLink(Link* obj) //return QueueID
{
    CHECK_ERROR_ABORT(outLink.size() == 0, "Error: Link ["+name+"] must have one and only one outgoing link !!!");
    outLink.push_back(make_pair(obj, -1));
    return (outLink.size() - 1);
}

void Alg_MyAlg1::genSetLinkPrms(ostream &fp, string obj)
{
    fp<<BLOCK_SPACE << "(" << obj << "->" << prmName <<")." << "baseClassCreate.size  = sizeof(AlgorithmLink_MyAlg1CreateParams);"<<endl;
    if(pType == DSP1 || pType == DSP2)
        fp<<BLOCK_SPACE << "(" << obj << "->" << prmName <<")." << "baseClassCreate.algId  = ALGORITHM_LINK_DSP_ALG_MYALG1;"<<endl;
    else
    if(pType == IPU1_0 || pType == IPU1_1 || pType == IPU2)
        fp<<BLOCK_SPACE << "(" << obj << "->" << prmName <<")." << "baseClassCreate.algId  = ALGORITHM_LINK_IPU_ALG_MYALG1;"<<endl;
    else if(pType == EVE1 || pType == EVE2 || pType == EVE3 || pType == EVE4)
        fp<<BLOCK_SPACE << "(" << obj << "->" << prmName <<")." << "baseClassCreate.algId  = ALGORITHM_LINK_EVE_ALG_MYALG1;"<<endl;
    else if(pType == A15)
            fp<<BLOCK_SPACE << "(" << obj << "->" << prmName <<")." << "baseClassCreate.algId  = ALGORITHM_LINK_A15_ALG_MYALG1;"<<endl;
}

/********************************************************************************/
Alg_MyAlg2::Alg_MyAlg2(string nm) {
    cType = cAlg_MyAlg2;
    name = nm;
    linkIDName = name + string("LinkID");
    prmName = name + string("Prm");
    execPos = -1;
    procID = -1;
    pType = IPU1_0;
    mulInQue = false;
    mulOutQue = false;
}

Alg_MyAlg2::~Alg_MyAlg2() {
}
void Alg_MyAlg2::genIncludes(ostream &fp) {
    CHECK_ERROR_ABORT(inLink.size() == 1, "Error: Link ["+name+"] must have one incoming link !!!");
    CHECK_ERROR_ABORT(outLink.size() == 1, "Error: Link ["+name+"] must have one outgoing link !!!");

    fp << "#include <apps/src/rtos/alg_plugins/myCustomAlg/myCustomLink.h>"<< endl;
}
void Alg_MyAlg2::genLinkID(ostream &fp) {

    fp << BLOCK_SPACE << setw(IDTYPE_WIDTH) << left << "UInt32" << linkIDName << ";" << endl;
}
void Alg_MyAlg2::genCreatePrms(ostream &fp) {

    fp << BLOCK_SPACE << setw(TYPENAME_WIDTH) << left\
            << "AlgorithmLink_MyAlg2CreateParams " << name << "Prm" << ";" << endl;
}
void Alg_MyAlg2::genResetLinkPrms(ostream &fp, string obj) {
    fp << BLOCK_SPACE << "AlgorithmLink_MyAlg2CreateParams_Init(&" << obj << "->"\
            << prmName << ");" << endl;
}
int Alg_MyAlg2::setInLink(Link* obj) //returns QueueID
{
    CHECK_ERROR_ABORT(inLink.size() == 0, "Error: Link ["+name+"] must have one and only one incoming link !!!");
    inLink.push_back(make_pair(obj, -1));
    return (inLink.size() - 1);
}
int Alg_MyAlg2::setOutLink(Link* obj) //return QueueID
{
    CHECK_ERROR_ABORT(outLink.size() == 0, "Error: Link ["+name+"] must have one and only one outgoing link !!!");
    outLink.push_back(make_pair(obj, -1));
    return (outLink.size() - 1);
}

void Alg_MyAlg2::genSetLinkPrms(ostream &fp, string obj)
{
    fp<<BLOCK_SPACE << "(" << obj << "->" << prmName <<")." << "baseClassCreate.size  = sizeof(AlgorithmLink_MyAlg2CreateParams);"<<endl;
    if(pType == DSP1 || pType == DSP2)
        fp<<BLOCK_SPACE << "(" << obj << "->" << prmName <<")." << "baseClassCreate.algId  = ALGORITHM_LINK_DSP_ALG_MYALG2;"<<endl;
    else if(pType == IPU1_0 || pType == IPU1_1 || pType == IPU2)
        fp<<BLOCK_SPACE << "(" << obj << "->" << prmName <<")." << "baseClassCreate.algId  = ALGORITHM_LINK_IPU_ALG_MYALG2;"<<endl;
    else if(pType == EVE1 || pType == EVE2 || pType == EVE3 || pType == EVE4)
        fp<<BLOCK_SPACE << "(" << obj << "->" << prmName <<")." << "baseClassCreate.algId  = ALGORITHM_LINK_EVE_ALG_MYALG2;"<<endl;
    else if(pType == A15)
        fp<<BLOCK_SPACE << "(" << obj << "->" << prmName <<")." << "baseClassCreate.algId  = ALGORITHM_LINK_A15_ALG_MYALG2;"<<endl;
}

/********************************************************************************/
Alg_MyAlg3::Alg_MyAlg3(string nm) {
    cType = cAlg_MyAlg3;
    name = nm;
    linkIDName = name + string("LinkID");
    prmName = name + string("Prm");
    execPos = -1;
    procID = -1;
    pType = IPU1_0;
    mulInQue = false;
    mulOutQue = false;
}

Alg_MyAlg3::~Alg_MyAlg3() {
}
void Alg_MyAlg3::genIncludes(ostream &fp) {
    CHECK_ERROR_ABORT(inLink.size() == 1, "Error: Link ["+name+"] must have one incoming link !!!");
    CHECK_ERROR_ABORT(outLink.size() == 1, "Error: Link ["+name+"] must have one outgoing link !!!");

    fp << "#include <apps/src/rtos/alg_plugins/myCustomAlg/myCustomLink.h>"<< endl;
}
void Alg_MyAlg3::genLinkID(ostream &fp) {

    fp << BLOCK_SPACE << setw(IDTYPE_WIDTH) << left << "UInt32" << linkIDName << ";" << endl;
}
void Alg_MyAlg3::genCreatePrms(ostream &fp) {

    fp << BLOCK_SPACE << setw(TYPENAME_WIDTH) << left\
            << "AlgorithmLink_MyAlg3CreateParams " << name << "Prm" << ";" << endl;
}
void Alg_MyAlg3::genResetLinkPrms(ostream &fp, string obj) {
    fp << BLOCK_SPACE << "AlgorithmLink_MyAlg3CreateParams_Init(&" << obj << "->"\
            << prmName << ");" << endl;
}
int Alg_MyAlg3::setInLink(Link* obj) //returns QueueID
{
    CHECK_ERROR_ABORT(inLink.size() == 0, "Error: Link ["+name+"] must have one and only one incoming link !!!");
    inLink.push_back(make_pair(obj, -1));
    return (inLink.size() - 1);
}
int Alg_MyAlg3::setOutLink(Link* obj) //return QueueID
{
    CHECK_ERROR_ABORT(outLink.size() == 0, "Error: Link ["+name+"] must have one and only one outgoing link !!!");
    outLink.push_back(make_pair(obj, -1));
    return (outLink.size() - 1);
}

void Alg_MyAlg3::genSetLinkPrms(ostream &fp, string obj)
{
    fp<<BLOCK_SPACE << "(" << obj << "->" << prmName <<")." << "baseClassCreate.size  = sizeof(AlgorithmLink_MyAlg3CreateParams);"<<endl;
    if(pType == DSP1 || pType == DSP2)
        fp<<BLOCK_SPACE << "(" << obj << "->" << prmName <<")." << "baseClassCreate.algId  = ALGORITHM_LINK_DSP_ALG_MYALG3;"<<endl;
    else if(pType == IPU1_0 || pType == IPU1_1 || pType == IPU2)
        fp<<BLOCK_SPACE << "(" << obj << "->" << prmName <<")." << "baseClassCreate.algId  = ALGORITHM_LINK_IPU_ALG_MYALG3;"<<endl;
    else if(pType == EVE1 || pType == EVE2 || pType == EVE3 || pType == EVE4)
        fp<<BLOCK_SPACE << "(" << obj << "->" << prmName <<")." << "baseClassCreate.algId  = ALGORITHM_LINK_EVE_ALG_MYALG3;"<<endl;
    else if(pType == A15)
            fp<<BLOCK_SPACE << "(" << obj << "->" << prmName <<")." << "baseClassCreate.algId  = ALGORITHM_LINK_A15_ALG_MYALG;"<<endl;
}

/********************************************************************************/
Alg_Census::Alg_Census(string nm) {
    cType = cAlg_Census;
    name = nm;
    linkIDName = name + string("LinkID");
    prmName = name + string("Prm");
    execPos = -1;
    procID = -1;
    pType = IPU1_0;
    mulInQue = false;
    mulOutQue = false;
}

Alg_Census::~Alg_Census() {
}
void Alg_Census::genIncludes(ostream &fp) {
    CHECK_ERROR_ABORT(inLink.size() == 1, "Error: Link ["+name+"] must have one incoming link !!!");
    CHECK_ERROR_ABORT(outLink.size() == 1, "Error: Link ["+name+"] must have one outgoing link !!!");

    fp << "#include <include/alglink_api/algorithmLink_census.h>"<< endl;
}
void Alg_Census::genLinkID(ostream &fp) {

    fp << BLOCK_SPACE << setw(IDTYPE_WIDTH) << left << "UInt32" << linkIDName << ";" << endl;
}
void Alg_Census::genCreatePrms(ostream &fp) {

    fp << BLOCK_SPACE << setw(TYPENAME_WIDTH) << left\
            << "AlgorithmLink_CensusCreateParams " << name << "Prm" << ";" << endl;
}
void Alg_Census::genResetLinkPrms(ostream &fp, string obj) {
    fp << BLOCK_SPACE << "AlgorithmLink_Census_Init(&" << obj << "->"\
            << prmName << ");" << endl;
}
int Alg_Census::setInLink(Link* obj) //returns QueueID
{
    CHECK_ERROR_ABORT(inLink.size() == 0, "Error: Link ["+name+"] must have one and only one incoming link !!!");
    inLink.push_back(make_pair(obj, -1));
    return (inLink.size() - 1);
}
int Alg_Census::setOutLink(Link* obj) //return QueueID
{
    CHECK_ERROR_ABORT(outLink.size() == 0, "Error: Link ["+name+"] must have one and only one outgoing link !!!");
    outLink.push_back(make_pair(obj, -1));
    return (outLink.size() - 1);
}

void Alg_Census::genSetLinkPrms(ostream &fp, string obj)
{
    fp<<BLOCK_SPACE << "(" << obj << "->" << prmName <<")." << "baseClassCreate.size  = sizeof(AlgorithmLink_CensusCreateParams);"<<endl;
    if(pType == EVE1 || pType == EVE2 || pType == EVE3 || pType == EVE4)
        fp<<BLOCK_SPACE << "(" << obj << "->" << prmName <<")." << "baseClassCreate.algId  = ALGORITHM_LINK_EVE_ALG_CENSUS;"<<endl;
}
/********************************************************************************/
Alg_DisparityHamDist::Alg_DisparityHamDist(string nm) {
    cType = cAlg_DisparityHamDist;
    name = nm;
    linkIDName = name + string("LinkID");
    prmName = name + string("Prm");
    execPos = -1;
    procID = -1;
    pType = IPU1_0;
    mulInQue = false;
    mulOutQue = false;
}

Alg_DisparityHamDist::~Alg_DisparityHamDist() {
}
void Alg_DisparityHamDist::genIncludes(ostream &fp) {
    CHECK_ERROR_ABORT(inLink.size() == 1, "Error: Link ["+name+"] must have one incoming link !!!");
    CHECK_ERROR_ABORT(outLink.size() == 1, "Error: Link ["+name+"] must have one outgoing link !!!");

    fp << "#include <include/alglink_api/algorithmLink_disparityHamDist.h>"<< endl;
}
void Alg_DisparityHamDist::genLinkID(ostream &fp) {

    fp << BLOCK_SPACE << setw(IDTYPE_WIDTH) << left << "UInt32" << linkIDName << ";" << endl;
}
void Alg_DisparityHamDist::genCreatePrms(ostream &fp) {

    fp << BLOCK_SPACE << setw(TYPENAME_WIDTH) << left\
            << "AlgorithmLink_DisparityHamDistCreateParams " << name << "Prm" << ";" << endl;
}
void Alg_DisparityHamDist::genResetLinkPrms(ostream &fp, string obj) {
    fp << BLOCK_SPACE << "AlgorithmLink_DisparityHamDist_Init(&" << obj << "->"\
            << prmName << ");" << endl;
}
int Alg_DisparityHamDist::setInLink(Link* obj) //returns QueueID
{
    CHECK_ERROR_ABORT(inLink.size() == 0, "Error: Link ["+name+"] must have one and only one incoming link !!!");
    inLink.push_back(make_pair(obj, -1));
    return (inLink.size() - 1);
}
int Alg_DisparityHamDist::setOutLink(Link* obj) //return QueueID
{
    CHECK_ERROR_ABORT(outLink.size() == 0, "Error: Link ["+name+"] must have one and only one outgoing link !!!");
    outLink.push_back(make_pair(obj, -1));
    return (outLink.size() - 1);
}

void Alg_DisparityHamDist::genSetLinkPrms(ostream &fp, string obj)
{
    fp<<BLOCK_SPACE << "(" << obj << "->" << prmName <<")." << "baseClassCreate.size  = sizeof(AlgorithmLink_DisparityHamDistCreateParams);"<<endl;
    if(pType == EVE1 || pType == EVE2 || pType == EVE3 || pType == EVE4)
        fp<<BLOCK_SPACE << "(" << obj << "->" << prmName <<")." << "baseClassCreate.algId  = ALGORITHM_LINK_EVE_ALG_DISPARITY_HAMDIST;"<<endl;
}
/********************************************************************************/
Alg_UltrasonicFusion::Alg_UltrasonicFusion(string nm) {
    cType = cAlg_UltrasonicFusion;
    name = nm;
    linkIDName = name + string("LinkID");
    prmName = name + string("Prm");
    execPos = -1;
    procID = -1;
    pType = DSP2;
    mulInQue = true;
    mulOutQue = true;
}

Alg_UltrasonicFusion::~Alg_UltrasonicFusion() {
}
void Alg_UltrasonicFusion::genIncludes(ostream &fp) {
    CHECK_ERROR_ABORT(inLink.size() == 2, "Error: Link ["+name+"] must have two incoming links !!!");
    CHECK_ERROR_ABORT(outLink.size() <= 1, "Error: Link ["+name+"] must have <= 1 outgoing link !!!");

    fp << "#include <include/alglink_api/algorithmLink_ultrasonicFusion.h>"<< endl;
}
void Alg_UltrasonicFusion::genLinkID(ostream &fp) {

    fp << BLOCK_SPACE << setw(IDTYPE_WIDTH) << left << "UInt32" << linkIDName << ";" << endl;
}
void Alg_UltrasonicFusion::genCreatePrms(ostream &fp) {

    fp << BLOCK_SPACE << setw(TYPENAME_WIDTH) << left\
            << "AlgorithmLink_UltrasonicFusionCreateParams " << name << "Prm" << ";" << endl;
}
void Alg_UltrasonicFusion::genResetLinkPrms(ostream &fp, string obj) {
    //fp << BLOCK_SPACE << "AlgorithmLink_UltrasonicFusion_initPlugin(&" << obj << "->"\
            << prmName << ");" << endl;
}
int Alg_UltrasonicFusion::setInLink(Link* obj) //returns QueueID
{
    inLink.push_back(make_pair(obj, -1));
    return (inLink.size() - 1);
}
int Alg_UltrasonicFusion::setOutLink(Link* obj) //return QueueID
{
    outLink.push_back(make_pair(obj, -1));
    return (outLink.size() - 1);
}

void Alg_UltrasonicFusion::genSetLinkPrms(ostream &fp, string obj)
{
    fp<<BLOCK_SPACE << "(" << obj << "->" << prmName <<")." << "baseClassCreate.size  = sizeof(AlgorithmLink_UltrasonicFusionCreateParams);"<<endl;
    if(pType == DSP1 || pType == DSP2)
        fp<<BLOCK_SPACE << "(" << obj << "->" << prmName <<")." << "baseClassCreate.algId  = ALGORITHM_LINK_DSP_ALG_ULTRASONICFUSION;"<<endl;
}
/********************************************************************************/
Alg_GeoAlign::Alg_GeoAlign(string nm) {
    cType = cAlg_GeoAlign;
    name = nm;
    linkIDName = name + string("LinkID");
    prmName = name + string("Prm");
    execPos = -1;
    procID = -1;
    pType = IPU1_0;
    mulInQue = true;
    mulOutQue = true;
}

Alg_GeoAlign::~Alg_GeoAlign() {
}
void Alg_GeoAlign::genIncludes(ostream &fp) {
    CHECK_ERROR_ABORT(inLink.size() == 1, "Error: Link ["+name+"] must have one incoming link !!!");
    CHECK_ERROR_ABORT(outLink.size() >= 1, "Error: Link ["+name+"] must have alteast one outgoing link(s) !!!");

    fp << "#include <include/alglink_api/algorithmLink_geometricAlignment.h>"<< endl;
}
void Alg_GeoAlign::genLinkID(ostream &fp) {
    fp << BLOCK_SPACE << setw(IDTYPE_WIDTH) << left << "UInt32" << linkIDName << ";" << endl;
}
void Alg_GeoAlign::genCreatePrms(ostream &fp) {
    fp << BLOCK_SPACE << setw(TYPENAME_WIDTH) << left << "AlgorithmLink_GAlignCreateParams"
            << name << "Prm" << ";" << endl;
}
void Alg_GeoAlign::genResetLinkPrms(ostream &fp, string obj) {
}
int Alg_GeoAlign::setInLink(Link* obj) //returns QueueID
{
    inLink.push_back(make_pair(obj, -1));
    return (inLink.size() - 1);
}
int Alg_GeoAlign::setOutLink(Link* obj) //return QueueID
{
    outLink.push_back(make_pair(obj, -1));
    return (outLink.size() - 1);
}
void Alg_GeoAlign::genSetLinkPrms(ostream &fp, string obj)
{
    fp<<BLOCK_SPACE << "(" << obj << "->" << prmName <<")." << "baseClassCreate.size  = sizeof(AlgorithmLink_GAlignCreateParams);"<<endl;
    if(pType == DSP1 || pType == DSP2)
        fp<<BLOCK_SPACE << "(" << obj << "->" << prmName <<")." << "baseClassCreate.algId  = ALGORITHM_LINK_DSP_ALG_GALIGNMENT;"<<endl;
}
/********************************************************************************/
Alg_GeoAlign3D::Alg_GeoAlign3D(string nm) {
    cType = cAlg_GeoAlign3D;
    name = nm;
    linkIDName = name + string("LinkID");
    prmName = name + string("Prm");
    execPos = -1;
    procID = -1;
    pType = IPU1_0;
    mulInQue = true;
    mulOutQue = true;
}

Alg_GeoAlign3D::~Alg_GeoAlign3D() {
}
void Alg_GeoAlign3D::genIncludes(ostream &fp) {
    //CHECK_ERROR_ABORT(inLink.size() == 1, "Error: Link ["+name+"] must have one incoming link !!!");
       CHECK_ERROR_ABORT(inLink.size() >= 1, "Error: Link ["+name+"] must have at least one incoming link !!!");
    CHECK_ERROR_ABORT(outLink.size() >= 1, "Error: Link ["+name+"] must have at least one outgoing link(s) !!!");

    fp << "#include <include/alglink_api/algorithmLink_geometricAlignment3D.h>"<< endl;
}
void Alg_GeoAlign3D::genLinkID(ostream &fp) {
    fp << BLOCK_SPACE << setw(IDTYPE_WIDTH) << left << "UInt32" << linkIDName << ";" << endl;
}
void Alg_GeoAlign3D::genCreatePrms(ostream &fp) {
    fp << BLOCK_SPACE << setw(TYPENAME_WIDTH) << left << "AlgorithmLink_GAlign3DCreateParams"
            << name << "Prm" << ";" << endl;
}
void Alg_GeoAlign3D::genResetLinkPrms(ostream &fp, string obj) {
}
int Alg_GeoAlign3D::setInLink(Link* obj) //returns QueueID
{
    inLink.push_back(make_pair(obj, -1));
    return (inLink.size() - 1);
}
int Alg_GeoAlign3D::setOutLink(Link* obj) //return QueueID
{
    outLink.push_back(make_pair(obj, -1));
    return (outLink.size() - 1);
}
void Alg_GeoAlign3D::genSetLinkPrms(ostream &fp, string obj)
{
    fp<<BLOCK_SPACE << "(" << obj << "->" << prmName <<")." << "baseClassCreate.size  = sizeof(AlgorithmLink_GAlign3DCreateParams);"<<endl;
    if(pType == DSP1 || pType == DSP2)
        fp<<BLOCK_SPACE << "(" << obj << "->" << prmName <<")." << "baseClassCreate.algId  = ALGORITHM_LINK_DSP_ALG_GALIGNMENT_3D;"<<endl;
}
/********************************************************************************/
Alg_ObjectDraw::Alg_ObjectDraw(string nm) {
    cType = cAlg_ObjectDraw;
    name = nm;
    linkIDName = name + string("LinkID");
    prmName = name + string("Prm");
    execPos = -1;
    procID = -1;
    pType = IPU1_0;
    mulInQue = false;
    mulOutQue = false;
}

Alg_ObjectDraw::~Alg_ObjectDraw() {
}
void Alg_ObjectDraw::genIncludes(ostream &fp) {
    CHECK_ERROR_ABORT(inLink.size() == 1, "Error: Link ["+name+"] must have one incoming link !!!");
    CHECK_ERROR_ABORT(outLink.size() == 1, "Error: Link ["+name+"] must have one outgoing link !!!");

    fp << "#include <include/alglink_api/algorithmLink_objectDraw.h>"<< endl;
}
void Alg_ObjectDraw::genLinkID(ostream &fp) {
    fp << BLOCK_SPACE << setw(IDTYPE_WIDTH) << left << "UInt32" << linkIDName << ";" << endl;
}
void Alg_ObjectDraw::genCreatePrms(ostream &fp) {
    fp << BLOCK_SPACE << setw(TYPENAME_WIDTH) << left << "AlgorithmLink_ObjectDrawCreateParams "
            << name << "Prm" << ";" << endl;
}
void Alg_ObjectDraw::genResetLinkPrms(ostream &fp, string obj) {
    fp << BLOCK_SPACE << "AlgorithmLink_ObjectDraw_Init(&" << obj << "->"\
            << prmName << ");" << endl;
}
int Alg_ObjectDraw::setInLink(Link* obj) //returns QueueID
{
    CHECK_ERROR_ABORT(inLink.size() == 0, "Error: Link ["+name+"] must have one and only one incoming link !!!");
    inLink.push_back(make_pair(obj, -1));
    return (inLink.size() - 1);
}
int Alg_ObjectDraw::setOutLink(Link* obj) //return QueueID
{
    CHECK_ERROR_ABORT(outLink.size() == 0, "Error: Link ["+name+"] must have one and only one outgoing link !!!");
    outLink.push_back(make_pair(obj, -1));
    return (outLink.size() - 1);
}
void Alg_ObjectDraw::genSetLinkPrms(ostream &fp, string obj)
{
    fp<<BLOCK_SPACE << "(" << obj << "->" << prmName <<")." << "baseClassCreate.size  = sizeof(AlgorithmLink_ObjectDrawCreateParams);"<<endl;
    if(pType == IPU1_0 || pType == IPU1_1 || pType == IPU2)
        fp<<BLOCK_SPACE << "(" << obj << "->" << prmName <<")." << "baseClassCreate.algId  = ALGORITHM_LINK_IPU_ALG_OBJECT_DRAW;"<<endl;
    if(pType == DSP1 || pType == DSP2)
        fp<<BLOCK_SPACE << "(" << obj << "->" << prmName <<")." << "baseClassCreate.algId  = ALGORITHM_LINK_DSP_ALG_OBJECT_DRAW;"<<endl;
    if(pType == A15)
        fp<<BLOCK_SPACE << "(" << obj << "->" << prmName <<")." << "baseClassCreate.algId  = ALGORITHM_LINK_A15_ALG_OBJECT_DRAW;"<<endl;
}
/********************************************************************************/
Alg_PhotoAlign::Alg_PhotoAlign(string nm) {
    cType = cAlg_PhotoAlign;
    name = nm;
    linkIDName = name + string("LinkID");
    prmName = name + string("Prm");
    execPos = -1;
    procID = -1;
    pType = IPU1_0;
    mulInQue = true;
    mulOutQue = true;
}

Alg_PhotoAlign::~Alg_PhotoAlign() {
}
void Alg_PhotoAlign::genIncludes(ostream &fp) {
    CHECK_ERROR_ABORT(inLink.size() == 1, "Error: Link ["+name+"] must have one incoming link !!!");
    CHECK_ERROR_ABORT(outLink.size() == 1, "Error: Link ["+name+"] must have one outgoing link !!!");

    fp << "#include <include/alglink_api/algorithmLink_photoAlignment.h>"<< endl;
}
void Alg_PhotoAlign::genLinkID(ostream &fp) {
    fp << BLOCK_SPACE << setw(IDTYPE_WIDTH) << left << "UInt32" << linkIDName << ";" << endl;
}
void Alg_PhotoAlign::genCreatePrms(ostream &fp) {
    fp << BLOCK_SPACE << setw(TYPENAME_WIDTH) << left << "AlgorithmLink_PAlignCreateParams"
            << name << "Prm" << ";" << endl;
}
void Alg_PhotoAlign::genResetLinkPrms(ostream &fp, string obj) {
}
int Alg_PhotoAlign::setInLink(Link* obj) //returns QueueID
{
    inLink.push_back(make_pair(obj, -1));
    return (inLink.size() - 1);
}
int Alg_PhotoAlign::setOutLink(Link* obj) //return QueueID
{
    outLink.push_back(make_pair(obj, -1));
    return (outLink.size() - 1);
}
void Alg_PhotoAlign::genSetLinkPrms(ostream &fp, string obj)
{
    fp<<BLOCK_SPACE << "(" << obj << "->" << prmName <<")." << "baseClassCreate.size  = sizeof(AlgorithmLink_PAlignCreateParams);"<<endl;
    if(pType == DSP1 || pType == DSP2)
        fp<<BLOCK_SPACE << "(" << obj << "->" << prmName <<")." << "baseClassCreate.algId  = ALGORITHM_LINK_DSP_ALG_PALIGNMENT;"<<endl;
}
/********************************************************************************/
Alg_Synthesis::Alg_Synthesis(string nm) {
    cType = cAlg_Synthesis;
    name = nm;
    linkIDName = name + string("LinkID");
    prmName = name + string("Prm");
    execPos = -1;
    procID = -1;
    pType = IPU1_0;
    mulInQue = true;
    mulOutQue = true;
}

Alg_Synthesis::~Alg_Synthesis() {
}
void Alg_Synthesis::genIncludes(ostream &fp) {
    CHECK_ERROR_ABORT(inLink.size() >= 2 , "Error: Link ["+name+"] must have >= 2 && <= 3 incoming links !!!");
    CHECK_ERROR_ABORT(inLink.size() <= 3 , "Error: Link ["+name+"] must have >= 2 && <= 3 incoming links !!!");
    CHECK_ERROR_ABORT(outLink.size() >= 2 , "Error: Link ["+name+"] must have >= 2 && <= 3 outgoing links !!!");
    CHECK_ERROR_ABORT(outLink.size() <= 3 , "Error: Link ["+name+"] must have >= 2 && <= 3 outgoing links !!!");
    fp << "#include <include/alglink_api/algorithmLink_synthesis.h>"<< endl;
}
void Alg_Synthesis::genLinkID(ostream &fp) {
    fp << BLOCK_SPACE << setw(IDTYPE_WIDTH) << left << "UInt32" << linkIDName << ";" << endl;
}
void Alg_Synthesis::genCreatePrms(ostream &fp) {
    fp << BLOCK_SPACE << setw(TYPENAME_WIDTH) << left
            << "AlgorithmLink_SynthesisCreateParams " << name << "Prm" << ";" << endl;
}
void Alg_Synthesis::genResetLinkPrms(ostream &fp, string obj) {
}
int Alg_Synthesis::setInLink(Link* obj) //returns QueueID
{
    inLink.push_back(make_pair(obj, -1));
    return (inLink.size() - 1);
}
int Alg_Synthesis::setOutLink(Link* obj) //return QueueID
{
    outLink.push_back(make_pair(obj, -1));
    return (outLink.size() - 1);
}
void Alg_Synthesis::genSetLinkPrms(ostream &fp, string obj)
{
    fp<<BLOCK_SPACE << "(" << obj << "->" << prmName <<")." << "baseClassCreate.size  = sizeof(AlgorithmLink_SynthesisCreateParams);"<<endl;
    if(pType == DSP1 || pType == DSP2)
        fp<<BLOCK_SPACE << "(" << obj << "->" << prmName <<")." << "baseClassCreate.algId  = ALGORITHM_LINK_DSP_ALG_SYNTHESIS;"<<endl;
}
/********************************************************************************/
Alg_SparseOpticalFlow::Alg_SparseOpticalFlow(string nm) {
    cType = cAlg_SparseOpticalFlow;
    name = nm;
    linkIDName = name + string("LinkID");
    prmName = name + string("Prm");
    execPos = -1;
    procID = -1;
    pType = IPU1_0;
    mulInQue = false;
    mulOutQue = false;
}

Alg_SparseOpticalFlow::~Alg_SparseOpticalFlow() {
}
void Alg_SparseOpticalFlow::genIncludes(ostream &fp) {
    CHECK_ERROR_ABORT(inLink.size() == 1, "Error: Link ["+name+"] must have one incoming link !!!");
    CHECK_ERROR_ABORT(outLink.size() == 1, "Error: Link ["+name+"] must have one outgoing link !!!");

    fp << "#include <include/alglink_api/algorithmLink_sparseOpticalFlow.h>"<< endl;
}
void Alg_SparseOpticalFlow::genLinkID(ostream &fp) {
    fp << BLOCK_SPACE << setw(IDTYPE_WIDTH) << left << "UInt32" << linkIDName << ";" << endl;
}
void Alg_SparseOpticalFlow::genCreatePrms(ostream &fp) {
    fp << BLOCK_SPACE << setw(TYPENAME_WIDTH) << left
            << "AlgorithmLink_SparseOpticalFlowCreateParams " << name << "Prm" << ";"
            << endl;
}
void Alg_SparseOpticalFlow::genResetLinkPrms(ostream &fp, string obj) {
    fp << BLOCK_SPACE << "AlgorithmLink_SparseOpticalFlow_Init(&" << obj\
            << "->" << prmName << ");" << endl;
}
int Alg_SparseOpticalFlow::setInLink(Link* obj) //returns QueueID
{
    CHECK_ERROR_ABORT(inLink.size() == 0, "Error: Link ["+name+"] must have one and only one incoming link !!!");
    inLink.push_back(make_pair(obj, -1));
    return (inLink.size() - 1);
}
int Alg_SparseOpticalFlow::setOutLink(Link* obj) //return QueueID
{
    CHECK_ERROR_ABORT(outLink.size() == 0, "Error: Link ["+name+"] must have one and only one outgoing link !!!");
    outLink.push_back(make_pair(obj, -1));
    return (outLink.size() - 1);
}
void Alg_SparseOpticalFlow::genSetLinkPrms(ostream &fp, string obj)
{
    fp<<BLOCK_SPACE << "(" << obj << "->" << prmName <<")." << "baseClassCreate.size  = sizeof(AlgorithmLink_SparseOpticalFlowCreateParams);"<<endl;
    fp<<BLOCK_SPACE << "(" << obj << "->" << prmName <<")." << "baseClassCreate.algId  = ALGORITHM_LINK_EVE_ALG_SPARSE_OPTICAL_FLOW;"<<endl;
}
/********************************************************************************/
Alg_LaneDetect::Alg_LaneDetect(string nm) {
    cType = cAlg_LaneDetect;
    name = nm;
    linkIDName = name + string("LinkID");
    prmName = name + string("Prm");
    execPos = -1;
    procID = -1;
    pType = IPU1_0;
    mulInQue = false;
    mulOutQue = false;
}

Alg_LaneDetect::~Alg_LaneDetect() {
}
void Alg_LaneDetect::genIncludes(ostream &fp) {
    CHECK_ERROR_ABORT(inLink.size() == 1, "Error: Link ["+name+"] must have one incoming link !!!");
    CHECK_ERROR_ABORT(outLink.size() == 1, "Error: Link ["+name+"] must have one outgoing link !!!");

    fp << "#include <include/alglink_api/algorithmLink_laneDetect.h>"<< endl;
}
void Alg_LaneDetect::genLinkID(ostream &fp) {
    fp << BLOCK_SPACE << setw(IDTYPE_WIDTH) << left << "UInt32" << linkIDName << ";" << endl;
}
void Alg_LaneDetect::genCreatePrms(ostream &fp) {
    fp << BLOCK_SPACE << setw(TYPENAME_WIDTH) << left
            << "AlgorithmLink_LaneDetectCreateParams " << name << "Prm" << ";"
            << endl;
}
void Alg_LaneDetect::genResetLinkPrms(ostream &fp, string obj) {
    fp << BLOCK_SPACE << "AlgorithmLink_LaneDetect_Init(&" << obj\
            << "->" << prmName << ");" << endl;
}
int Alg_LaneDetect::setInLink(Link* obj) //returns QueueID
{
    CHECK_ERROR_ABORT(inLink.size() == 0, "Error: Link ["+name+"] must have one and only one incoming link !!!");
    inLink.push_back(make_pair(obj, -1));
    return (inLink.size() - 1);
}
int Alg_LaneDetect::setOutLink(Link* obj) //return QueueID
{
    CHECK_ERROR_ABORT(outLink.size() == 0, "Error: Link ["+name+"] must have one and only one outgoing link !!!");
    outLink.push_back(make_pair(obj, -1));
    return (outLink.size() - 1);
}
void Alg_LaneDetect::genSetLinkPrms(ostream &fp, string obj)
{
    fp<<BLOCK_SPACE << "(" << obj << "->" << prmName <<")." << "baseClassCreate.size  = sizeof(AlgorithmLink_LaneDetectCreateParams);"<<endl;
    fp<<BLOCK_SPACE << "(" << obj << "->" << prmName <<")." << "baseClassCreate.algId  = ALGORITHM_LINK_DSP_ALG_LANE_DETECT;"<<endl;
}

/********************************************************************************/
Alg_SfmMain::Alg_SfmMain(string nm) {
    cType = cAlg_SfmMain;
    name = nm;
    linkIDName = name + string("LinkID");
    prmName = name + string("Prm");
    execPos = -1;
    procID = -1;
    pType = IPU1_0;
    mulInQue = true;
    mulOutQue = true;
}

Alg_SfmMain::~Alg_SfmMain() {
}
void Alg_SfmMain::genIncludes(ostream &fp) {
    CHECK_ERROR_ABORT(inLink.size() == 1, "Error: Link ["+name+"] must have 1 incoming link !!!");
    CHECK_ERROR_ABORT(outLink.size() == 3, "Error: Link ["+name+"] must have 3 outgoing link !!!");

    fp << "#include <include/alglink_api/algorithmLink_sfmMain.h>"<< endl;
}
void Alg_SfmMain::genLinkID(ostream &fp) {
    fp << BLOCK_SPACE << setw(IDTYPE_WIDTH) << left << "UInt32" << linkIDName << ";" << endl;
}
void Alg_SfmMain::genCreatePrms(ostream &fp) {
    fp << BLOCK_SPACE << setw(TYPENAME_WIDTH) << left
            << "AlgorithmLink_SfmMainCreateParams " << name << "Prm" << ";"
            << endl;
}
void Alg_SfmMain::genResetLinkPrms(ostream &fp, string obj) {
}
int Alg_SfmMain::setInLink(Link* obj) //returns QueueID
{
    inLink.push_back(make_pair(obj, -1));
    return (inLink.size() - 1);
}
int Alg_SfmMain::setOutLink(Link* obj) //return QueueID
{
    outLink.push_back(make_pair(obj, -1));
    return (outLink.size() - 1);
}
void Alg_SfmMain::genSetLinkPrms(ostream &fp, string obj)
{
    fp<<BLOCK_SPACE << "(" << obj << "->" << prmName <<")." << "baseClassCreate.size  = sizeof(AlgorithmLink_SfmMainCreateParams);"<<endl;
    if(pType == DSP1 || pType == DSP2)
        fp<<BLOCK_SPACE << "(" << obj << "->" << prmName <<")." << "baseClassCreate.algId  = ALGORITHM_LINK_DSP_ALG_SFMMAIN;"<<endl;
}
/********************************************************************************/
Alg_SfmLinearTwoView::Alg_SfmLinearTwoView(string nm) {
    cType = cAlg_SfmLinearTwoView;
    name = nm;
    linkIDName = name + string("LinkID");
    prmName = name + string("Prm");
    execPos = -1;
    procID = -1;
    pType = IPU1_0;
    mulInQue = true;
    mulOutQue = true;
}

Alg_SfmLinearTwoView::~Alg_SfmLinearTwoView() {
}
void Alg_SfmLinearTwoView::genIncludes(ostream &fp) {
    CHECK_ERROR_ABORT(inLink.size() >= 1, "Error: Link ["+name+"] must have one incoming link !!!");
    CHECK_ERROR_ABORT(outLink.size() == 0, "Error: Link ["+name+"] must have no outgoing links !!!");

    fp << "#include <include/alglink_api/algorithmLink_sfmLinearTwoView.h>"<< endl;
}
void Alg_SfmLinearTwoView::genLinkID(ostream &fp) {
    fp << BLOCK_SPACE << setw(IDTYPE_WIDTH) << left << "UInt32" << linkIDName << ";" << endl;
}
void Alg_SfmLinearTwoView::genCreatePrms(ostream &fp) {
    fp << BLOCK_SPACE << setw(TYPENAME_WIDTH) << left
            << "AlgorithmLink_SfmLinearTwoViewCreateParams " << name << "Prm" << ";"
            << endl;
}
void Alg_SfmLinearTwoView::genResetLinkPrms(ostream &fp, string obj) {
}
int Alg_SfmLinearTwoView::setInLink(Link* obj) //returns QueueID
{
    inLink.push_back(make_pair(obj, -1));
    return (inLink.size() - 1);
}
int Alg_SfmLinearTwoView::setOutLink(Link* obj) //return QueueID
{
    outLink.push_back(make_pair(obj, -1));
    return (outLink.size() - 1);
}
void Alg_SfmLinearTwoView::genSetLinkPrms(ostream &fp, string obj)
{
    fp<<BLOCK_SPACE << "(" << obj << "->" << prmName <<")." << "baseClassCreate.size  = sizeof(AlgorithmLink_SfmLinearTwoViewCreateParams);"<<endl;
    if(pType == DSP1 || pType == DSP2)
        fp<<BLOCK_SPACE << "(" << obj << "->" << prmName <<")." << "baseClassCreate.algId  = ALGORITHM_LINK_DSP_ALG_SFMLTV;"<<endl;
}
/********************************************************************************/
Alg_SfmMap::Alg_SfmMap(string nm) {
    cType = cAlg_SfmMap;
    name = nm;
    linkIDName = name + string("LinkID");
    prmName = name + string("Prm");
    execPos = -1;
    procID = -1;
    pType = IPU1_0;
    mulInQue = true;
    mulOutQue = true;
}

Alg_SfmMap::~Alg_SfmMap() {
}
void Alg_SfmMap::genIncludes(ostream &fp) {
    CHECK_ERROR_ABORT(inLink.size() == 2, "Error: Link ["+name+"] must have two incoming links !!!");
    CHECK_ERROR_ABORT(outLink.size() == 1, "Error: Link ["+name+"] must have one outgoing link !!!");

    fp << "#include <include/alglink_api/algorithmLink_sfmMap.h>"<< endl;
}
void Alg_SfmMap::genLinkID(ostream &fp) {
    fp << BLOCK_SPACE << setw(IDTYPE_WIDTH) << left << "UInt32" << linkIDName << ";" << endl;
}
void Alg_SfmMap::genCreatePrms(ostream &fp) {
    fp << BLOCK_SPACE << setw(TYPENAME_WIDTH) << left
            << "AlgorithmLink_SfmMapCreateParams " << name << "Prm" << ";"
            << endl;
}
void Alg_SfmMap::genResetLinkPrms(ostream &fp, string obj) {
}
int Alg_SfmMap::setInLink(Link* obj) //returns QueueID
{
    inLink.push_back(make_pair(obj, -1));
    return (inLink.size() - 1);
}
int Alg_SfmMap::setOutLink(Link* obj) //return QueueID
{
    outLink.push_back(make_pair(obj, -1));
    return (outLink.size() - 1);
}
void Alg_SfmMap::genSetLinkPrms(ostream &fp, string obj)
{
    fp<<BLOCK_SPACE << "(" << obj << "->" << prmName <<")." << "baseClassCreate.size  = sizeof(AlgorithmLink_SfmMapCreateParams);"<<endl;
    if(pType == DSP1 || pType == DSP2)
        fp<<BLOCK_SPACE << "(" << obj << "->" << prmName <<")." << "baseClassCreate.algId  = ALGORITHM_LINK_DSP_ALG_SFMMAP;"<<endl;
}
/********************************************************************************/
Alg_SfmSurround::Alg_SfmSurround(string nm) {
    cType = cAlg_SfmSurround;
    name = nm;
    linkIDName = name + string("LinkID");
    prmName = name + string("Prm");
    execPos = -1;
    procID = -1;
    pType = IPU1_0;
    mulInQue = true;
    mulOutQue = true;
}

Alg_SfmSurround::~Alg_SfmSurround() {
}
void Alg_SfmSurround::genIncludes(ostream &fp) {
    CHECK_ERROR_ABORT(inLink.size() == 1, "Error: Link ["+name+"] must have 1 incoming link !!!");
    CHECK_ERROR_ABORT(outLink.size() >= 2, "Error: Link ["+name+"] must have at least 2 outgoing links !!!");

    fp << "#include <include/link_api/algorithmLink_sfmSurround.h>"<< endl;
}
void Alg_SfmSurround::genLinkID(ostream &fp) {
    fp << BLOCK_SPACE << setw(IDTYPE_WIDTH) << left << "UInt32" << linkIDName << ";" << endl;
}
void Alg_SfmSurround::genCreatePrms(ostream &fp) {
    fp << BLOCK_SPACE << setw(TYPENAME_WIDTH) << left
            << "AlgorithmLink_SfmSurroundCreateParams " << name << "Prm" << ";"
            << endl;
}
void Alg_SfmSurround::genResetLinkPrms(ostream &fp, string obj) {
}
int Alg_SfmSurround::setInLink(Link* obj) //returns QueueID
{
    inLink.push_back(make_pair(obj, -1));
    return (inLink.size() - 1);
}
int Alg_SfmSurround::setOutLink(Link* obj) //return QueueID
{
    outLink.push_back(make_pair(obj, -1));
    return (outLink.size() - 1);
}
void Alg_SfmSurround::genSetLinkPrms(ostream &fp, string obj)
{
    fp<<BLOCK_SPACE << "(" << obj << "->" << prmName <<")." << "baseClassCreate.size  = sizeof(AlgorithmLink_SfmSurroundCreateParams);"<<endl;
    if(pType == DSP1 || pType == DSP2)
        fp<<BLOCK_SPACE << "(" << obj << "->" << prmName <<")." << "baseClassCreate.algId  = ALGORITHM_LINK_DSP_ALG_SFMSURROUND;"<<endl;
}
/********************************************************************************/
Alg_Clr::Alg_Clr(string nm) {
    cType = cAlg_Clr;
    name = nm;
    linkIDName = name + string("LinkID");
    prmName = name + string("Prm");
    execPos = -1;
    procID = -1;
    pType = IPU1_0;
    mulInQue = false;
    mulOutQue = false;
}

Alg_Clr::~Alg_Clr() {
}
void Alg_Clr::genIncludes(ostream &fp) {
    CHECK_ERROR_ABORT(inLink.size() == 1, "Error: Link ["+name+"] must have one incoming link !!!");
    CHECK_ERROR_ABORT(outLink.size() == 1, "Error: Link ["+name+"] must have one outgoing link !!!");

    fp << "#include <include/alglink_api/algorithmLink_clr.h>"<< endl;
}
void Alg_Clr::genLinkID(ostream &fp) {
    fp << BLOCK_SPACE << setw(IDTYPE_WIDTH) << left << "UInt32" << linkIDName << ";" << endl;
}
void Alg_Clr::genCreatePrms(ostream &fp) {
    fp << BLOCK_SPACE << setw(TYPENAME_WIDTH) << left
            << "AlgorithmLink_ClrCreateParams " << name << "Prm" << ";"
            << endl;
}
void Alg_Clr::genResetLinkPrms(ostream &fp, string obj) {
    fp << BLOCK_SPACE << "AlgorithmLink_Clr_Init(&" << obj\
            << "->" << prmName << ");" << endl;
}
int Alg_Clr::setInLink(Link* obj) //returns QueueID
{
    CHECK_ERROR_ABORT(inLink.size() == 0, "Error: Link ["+name+"] must have one and only one incoming link !!!");
    inLink.push_back(make_pair(obj, -1));
    return (inLink.size() - 1);
}
int Alg_Clr::setOutLink(Link* obj) //return QueueID
{
    CHECK_ERROR_ABORT(outLink.size() == 0, "Error: Link ["+name+"] must have one and only one outgoing link !!!");
    outLink.push_back(make_pair(obj, -1));
    return (outLink.size() - 1);
}
void Alg_Clr::genSetLinkPrms(ostream &fp, string obj)
{
    fp<<BLOCK_SPACE << "(" << obj << "->" << prmName <<")." << "baseClassCreate.size  = sizeof(AlgorithmLink_ClrCreateParams);"<<endl;
    fp<<BLOCK_SPACE << "(" << obj << "->" << prmName <<")." << "baseClassCreate.algId  = ALGORITHM_LINK_DSP_ALG_CLR;"<<endl;
}
/********************************************************************************/
Alg_Sfm::Alg_Sfm(string nm) {
    cType = cAlg_Sfm;
    name = nm;
    linkIDName = name + string("LinkID");
    prmName = name + string("Prm");
    execPos = -1;
    procID = -1;
    pType = IPU1_0;
    mulInQue = false;
    mulOutQue = false;
}

Alg_Sfm::~Alg_Sfm() {
}
void Alg_Sfm::genIncludes(ostream &fp) {
    CHECK_ERROR_ABORT(inLink.size() == 1, "Error: Link ["+name+"] must have one incoming link !!!");
    CHECK_ERROR_ABORT(outLink.size() == 1, "Error: Link ["+name+"] must have one outgoing link !!!");

    fp << "#include <include/alglink_api/algorithmLink_sfm.h>"<< endl;
}
void Alg_Sfm::genLinkID(ostream &fp) {
    fp << BLOCK_SPACE << setw(IDTYPE_WIDTH) << left << "UInt32" << linkIDName << ";" << endl;
}
void Alg_Sfm::genCreatePrms(ostream &fp) {
    fp << BLOCK_SPACE << setw(TYPENAME_WIDTH) << left
            << "AlgorithmLink_SfmCreateParams " << name << "Prm" << ";"
            << endl;
}
void Alg_Sfm::genResetLinkPrms(ostream &fp, string obj) {
    fp << BLOCK_SPACE << "AlgorithmLink_Sfm_Init(&" << obj\
            << "->" << prmName << ");" << endl;
}
int Alg_Sfm::setInLink(Link* obj) //returns QueueID
{
    CHECK_ERROR_ABORT(inLink.size() == 0, "Error: Link ["+name+"] must have one and only one incoming link !!!");
    inLink.push_back(make_pair(obj, -1));
    return (inLink.size() - 1);
}
int Alg_Sfm::setOutLink(Link* obj) //return QueueID
{
    CHECK_ERROR_ABORT(outLink.size() == 0, "Error: Link ["+name+"] must have one and only one outgoing link !!!");
    outLink.push_back(make_pair(obj, -1));
    return (outLink.size() - 1);
}
void Alg_Sfm::genSetLinkPrms(ostream &fp, string obj)
{
    fp<<BLOCK_SPACE << "(" << obj << "->" << prmName <<")." << "baseClassCreate.size  = sizeof(AlgorithmLink_SfmCreateParams);"<<endl;
    fp<<BLOCK_SPACE << "(" << obj << "->" << prmName <<")." << "baseClassCreate.algId  = ALGORITHM_LINK_DSP_ALG_SFM;"<<endl;
}

/********************************************************************************/
Alg_Fcw::Alg_Fcw(string nm) {
    cType = cAlg_Fcw;
    name = nm;
    linkIDName = name + string("LinkID");
    prmName = name + string("Prm");
    execPos = -1;
    procID = -1;
    pType = IPU1_0;
    mulInQue = false;
    mulOutQue = false;
}

Alg_Fcw::~Alg_Fcw() {
}
void Alg_Fcw::genIncludes(ostream &fp) {
    CHECK_ERROR_ABORT(inLink.size() == 1, "Error: Link ["+name+"] must have one incoming link !!!");
    CHECK_ERROR_ABORT(outLink.size() == 1, "Error: Link ["+name+"] must have one outgoing link !!!");

    fp << "#include <include/alglink_api/algorithmLink_fcw.h>"<< endl;
}
void Alg_Fcw::genLinkID(ostream &fp) {
    fp << BLOCK_SPACE << setw(IDTYPE_WIDTH) << left << "UInt32" << linkIDName << ";" << endl;
}
void Alg_Fcw::genCreatePrms(ostream &fp) {
    fp << BLOCK_SPACE << setw(TYPENAME_WIDTH) << left
            << "AlgorithmLink_FcwCreateParams " << name << "Prm" << ";"
            << endl;
}
void Alg_Fcw::genResetLinkPrms(ostream &fp, string obj) {
    fp << BLOCK_SPACE << "AlgorithmLink_Fcw_Init(&" << obj\
            << "->" << prmName << ");" << endl;
}
int Alg_Fcw::setInLink(Link* obj) //returns QueueID
{
    CHECK_ERROR_ABORT(inLink.size() == 0, "Error: Link ["+name+"] must have one and only one incoming link !!!");
    inLink.push_back(make_pair(obj, -1));
    return (inLink.size() - 1);
}
int Alg_Fcw::setOutLink(Link* obj) //return QueueID
{
    CHECK_ERROR_ABORT(outLink.size() == 0, "Error: Link ["+name+"] must have one and only one outgoing link !!!");
    outLink.push_back(make_pair(obj, -1));
    return (outLink.size() - 1);
}
void Alg_Fcw::genSetLinkPrms(ostream &fp, string obj)
{
    fp<<BLOCK_SPACE << "(" << obj << "->" << prmName <<")." << "baseClassCreate.size  = sizeof(AlgorithmLink_FcwCreateParams);"<<endl;

    if(pType == DSP1 || pType == DSP2)
        fp<<BLOCK_SPACE << "(" << obj << "->" << prmName <<")." << "baseClassCreate.algId  = ALGORITHM_LINK_DSP_ALG_FCW;"<<endl;
}
/********************************************************************************/
Alg_VectoImg::Alg_VectoImg(string nm) {
    cType = cAlg_VectoImg;
    name = nm;
    linkIDName = name + string("LinkID");
    prmName = name + string("Prm");
    execPos = -1;
    procID = -1;
    pType = IPU1_0;
    mulInQue = false;
    mulOutQue = false;
}

Alg_VectoImg::~Alg_VectoImg() {
}
void Alg_VectoImg::genIncludes(ostream &fp) {
    CHECK_ERROR_ABORT(inLink.size() == 1, "Error: Link ["+name+"] must have one incoming link !!!");
    CHECK_ERROR_ABORT(outLink.size() == 1, "Error: Link ["+name+"] must have one outgoing link !!!");
    fp << "#include <include/alglink_api/algorithmLink_vectorToImage.h>"<< endl;
}
void Alg_VectoImg::genLinkID(ostream &fp) {
    fp << BLOCK_SPACE << setw(IDTYPE_WIDTH) << left << "UInt32" << linkIDName << ";" << endl;
}
void Alg_VectoImg::genCreatePrms(ostream &fp) {
    fp << BLOCK_SPACE << setw(TYPENAME_WIDTH) << left
            << "AlgorithmLink_VectorToImageCreateParams " << name << "Prm" << ";"
            << endl;
}
void Alg_VectoImg::genResetLinkPrms(ostream &fp, string obj) {
    fp << BLOCK_SPACE << "AlgorithmLink_VectorToImageCreateParams_Init(&" << obj\
            << "->" << prmName << ");" << endl;
}
int Alg_VectoImg::setInLink(Link* obj) //returns QueueID
{
    CHECK_ERROR_ABORT(inLink.size() == 0, "Error: Link ["+name+"] must have one and only one incoming link !!!");
    inLink.push_back(make_pair(obj, -1));
    return (inLink.size() - 1);
}
int Alg_VectoImg::setOutLink(Link* obj) //return QueueID
{
    CHECK_ERROR_ABORT(outLink.size() == 0, "Error: Link ["+name+"] must have one and only one outgoing link !!!");
    outLink.push_back(make_pair(obj, -1));
    return (outLink.size() - 1);
}
void Alg_VectoImg::genSetLinkPrms(ostream &fp, string obj)
{
    fp<<BLOCK_SPACE << "(" << obj << "->" << prmName <<")." << "baseClassCreate.size  = sizeof(AlgorithmLink_VectorToImageCreateParams);"<<endl;
    if(pType == DSP1 || pType == DSP2)
        fp<<BLOCK_SPACE << "(" << obj << "->" << prmName <<")." << "baseClassCreate.algId  = ALGORITHM_LINK_DSP_ALG_VECTORTOIMAGE;"<<endl;
}
/********************************************************************************/
Alg_DeWarp::Alg_DeWarp(string nm) {
    cType = cAlg_DeWarp;
    name = nm;
    linkIDName = name + string("LinkID");
    prmName = name + string("Prm");
    execPos = -1;
    procID = -1;
    pType = IPU1_0;
    mulInQue = false;
    mulOutQue = false;
}

Alg_DeWarp::~Alg_DeWarp() {
}
void Alg_DeWarp::genIncludes(ostream &fp) {
    CHECK_ERROR_ABORT(outLink.size() == 1, "Error: Link ["+name+"] must have one outgoing link !!!");

    fp << "#include <include/alglink_api/algorithmLink_deWarp.h>"<< endl;
}
void Alg_DeWarp::genLinkID(ostream &fp) {
    fp << BLOCK_SPACE << setw(IDTYPE_WIDTH) << left << "UInt32" << linkIDName << ";" << endl;
}
void Alg_DeWarp::genCreatePrms(ostream &fp) {
    fp << BLOCK_SPACE << setw(TYPENAME_WIDTH) << left
            << "AlgLink_DeWarpCreateParams " << name << "Prm" << ";"
            << endl;
}
void Alg_DeWarp::genResetLinkPrms(ostream &fp, string obj) {
    fp << BLOCK_SPACE << "AlgLink_DeWarpCreateParams_Init(&" << obj\
            << "->" << prmName << ");" << endl;
}
int Alg_DeWarp::setInLink(Link* obj) //returns QueueID
{
    inLink.push_back(make_pair(obj, -1));
    return (inLink.size() - 1);
}
int Alg_DeWarp::setOutLink(Link* obj) //return QueueID
{
    CHECK_ERROR_ABORT(outLink.size() == 0, "Error: Link ["+name+"] must have one and only one outgoing link !!!");
    outLink.push_back(make_pair(obj, -1));
    return (outLink.size() - 1);
}
void Alg_DeWarp::genSetLinkPrms(ostream &fp, string obj)
{
    fp<<BLOCK_SPACE << "(" << obj << "->" << prmName <<")." << "baseClassCreate.size  = sizeof(AlgLink_DeWarpCreateParams);"<<endl;
    fp<<BLOCK_SPACE << "(" << obj << "->" << prmName <<")." << "baseClassCreate.algId  = ALGORITHM_LINK_IPU_ALG_DEWARP;"<<endl;
}
/********************************************************************************/
Alg_RadarProcess::Alg_RadarProcess(string nm) {
    cType = cAlg_RadarProcess;
    name = nm;
    linkIDName = name + string("LinkID");
    prmName = name + string("Prm");
    execPos = -1;
    procID = -1;
    pType = IPU1_0;
    mulInQue = false;
    mulOutQue = false;
}
Alg_RadarProcess::~Alg_RadarProcess() {
}
void Alg_RadarProcess::genIncludes(ostream &fp) {
    CHECK_ERROR_ABORT(inLink.size() == 1, "Error: Link ["+name+"] must have one incoming link !!!");

    fp << "#include <include/alglink_api/algorithmLink_radarProcess.h>"<< endl;
}
void Alg_RadarProcess::genLinkID(ostream &fp) {
    fp << BLOCK_SPACE << setw(10) << left << "UInt32" << linkIDName << ";" << endl;
}
void Alg_RadarProcess::genCreatePrms(ostream &fp) {
    fp << BLOCK_SPACE << setw(40) << left << "AlgorithmLink_RadarProcessCreateParams *" << name << "Prm" << ";" << endl;
}
void Alg_RadarProcess::genResetLinkPrms(ostream &fp, string obj) {
    fp << BLOCK_SPACE << "AlgorithmLink_RadarProcess_Init(" << obj << "->" << prmName << ");" << endl;
}
int Alg_RadarProcess::setInLink(Link* obj) //returns QueueID
{
    CHECK_ERROR_ABORT(inLink.size() == 0, "Error: Link ["+name+"] must have one and only one incoming link !!!");
    inLink.push_back(make_pair(obj, -1));
    return (inLink.size() - 1);
}
int Alg_RadarProcess::setOutLink(Link* obj) //return QueueID
{
    CHECK_ERROR_ABORT(outLink.size() == 0, "Error: Link ["+name+"] must have one and only one outgoing link !!!");
    outLink.push_back(make_pair(obj, -1));
    return (outLink.size() - 1);
}
void Alg_RadarProcess::genSetLinkPrms(ostream &fp, string obj)
{
    if(pType == DSP1 || pType == DSP2)
        fp<<BLOCK_SPACE << obj << "->" << prmName << "->" << "baseClassCreate.algId  = ALGORITHM_LINK_DSP_ALG_RADAR_PROCESS;"<<endl;
    if(pType == EVE1 || pType == EVE2  || pType == EVE3 || pType == EVE4)
        fp<<BLOCK_SPACE << obj << "->" << prmName << "->" << "baseClassCreate.algId  = ALGORITHM_LINK_EVE_ALG_RADAR_PROCESS;"<<endl;
    if(pType == IPU1_0 || pType == IPU1_1 || pType == IPU2)
        fp<<BLOCK_SPACE << obj << "->" << prmName << "->" << "baseClassCreate.algId  = ALGORITHM_LINK_IPU_ALG_RADAR_PROCESS;"<<endl;
    if(pType == A15)
        fp<<BLOCK_SPACE << obj << "->" << prmName << "->" << "baseClassCreate.algId  = ALGORITHM_LINK_A15_ALG_RADAR_PROCESS;"<<endl;
}
/********************************************************************************/
Alg_tidl::Alg_tidl(string nm) {
    cType = cAlg_tidl;
    name = nm;
    linkIDName = name + string("LinkID");
    prmName = name + string("Prm");
    execPos = -1;
    procID = -1;
    pType = IPU1_0;
    mulInQue = true;
    mulOutQue = true;
}

Alg_tidl::~Alg_tidl() {
}
void Alg_tidl::genIncludes(ostream &fp) {
    CHECK_ERROR_ABORT(outLink.size() == 1, "Error: Link ["+name+"] must have one outgoing link !!!");

    fp << "#include <include/alglink_api/algorithmLink_tidl.h>"<< endl;
}
void Alg_tidl::genLinkID(ostream &fp) {
    fp << BLOCK_SPACE << setw(10) << left << "UInt32" << linkIDName << ";" << endl;
}
void Alg_tidl::genCreatePrms(ostream &fp) {
    fp << BLOCK_SPACE << setw(40) << left
            << "AlgorithmLink_tidlCreateParams " << name << "Prm" << ";"
            << endl;
}
void Alg_tidl::genResetLinkPrms(ostream &fp, string obj) {
    fp << BLOCK_SPACE << "AlgorithmLink_tidlCreateParams_Init(&" << obj\
            << "->" << prmName << ");" << endl;
}
int Alg_tidl::setInLink(Link* obj) //returns QueueID
{
    inLink.push_back(make_pair(obj, -1));
    return (inLink.size() - 1);
}
int Alg_tidl::setOutLink(Link* obj) //return QueueID
{
    outLink.push_back(make_pair(obj, -1));
    return (outLink.size() - 1);
}
void Alg_tidl::genSetLinkPrms(ostream &fp, string obj)
{
    fp<<BLOCK_SPACE << "(" << obj << "->" << prmName <<")." << "baseClassCreate.size  = sizeof(AlgorithmLink_tidlCreateParams);"<<endl;
    if(pType == DSP1 || pType == DSP2)
        fp<<BLOCK_SPACE << "(" << obj << "->" << prmName <<")." << "baseClassCreate.algId  = ALGORITHM_LINK_DSP_ALG_TIDL;"<<endl;
    if(pType == EVE1 || pType == EVE2  || pType == EVE3 || pType == EVE4)
        fp<<BLOCK_SPACE << "(" << obj << "->" << prmName <<")." << "baseClassCreate.algId  = ALGORITHM_LINK_EVE_ALG_TIDL;"<<endl;
}
/********************************************************************************/
Alg_tiop::Alg_tiop(string nm) {
    cType = cAlg_tiop;
    name = nm;
    linkIDName = name + string("LinkID");
    prmName = name + string("Prm");
    execPos = -1;
    procID = -1;
    pType = IPU1_0;
    mulInQue = true;
    mulOutQue = true;
}

Alg_tiop::~Alg_tiop() {
}
void Alg_tiop::genIncludes(ostream &fp) {
    CHECK_ERROR_ABORT(outLink.size() == 1, "Error: Link ["+name+"] must have one outgoing link !!!");

    fp << "#include <include/alglink_api/algorithmLink_tiop.h>"<< endl;
}
void Alg_tiop::genLinkID(ostream &fp) {
    fp << BLOCK_SPACE << setw(10) << left << "UInt32" << linkIDName << ";" << endl;
}
void Alg_tiop::genCreatePrms(ostream &fp) {
    fp << BLOCK_SPACE << setw(40) << left
            << "AlgorithmLink_tiopCreateParams " << name << "Prm" << ";"
            << endl;
}
void Alg_tiop::genResetLinkPrms(ostream &fp, string obj) {
    fp << BLOCK_SPACE << "AlgorithmLink_tiopCreateParams_Init(&" << obj\
            << "->" << prmName << ");" << endl;
}
int Alg_tiop::setInLink(Link* obj) //returns QueueID
{
    inLink.push_back(make_pair(obj, -1));
    return (inLink.size() - 1);
}
int Alg_tiop::setOutLink(Link* obj) //return QueueID
{
    outLink.push_back(make_pair(obj, -1));
    return (outLink.size() - 1);
}
void Alg_tiop::genSetLinkPrms(ostream &fp, string obj)
{
    fp<<BLOCK_SPACE << "(" << obj << "->" << prmName <<")." << "baseClassCreate.size  = sizeof(AlgorithmLink_tiopCreateParams);"<<endl;
    fp<<BLOCK_SPACE << "(" << obj << "->" << prmName <<")." << "baseClassCreate.algId  = ALGORITHM_LINK_DSP_ALG_TIOP;"<<endl;
}
/********************************************************************************/
Alg_tidlpreproc::Alg_tidlpreproc(string nm) {
    cType = cAlg_tidlpreproc;
    name = nm;
    linkIDName = name + string("LinkID");
    prmName = name + string("Prm");
    execPos = -1;
    procID = -1;
    pType = IPU1_0;
    mulInQue = false;
    mulOutQue = true;
}

Alg_tidlpreproc::~Alg_tidlpreproc() {
}
void Alg_tidlpreproc::genIncludes(ostream &fp) {

    fp << "#include <include/alglink_api/algorithmLink_tidlpreproc.h>"<< endl;
}
void Alg_tidlpreproc::genLinkID(ostream &fp) {
    fp << BLOCK_SPACE << setw(10) << left << "UInt32" << linkIDName << ";" << endl;
}
void Alg_tidlpreproc::genCreatePrms(ostream &fp) {
    fp << BLOCK_SPACE << setw(40) << left
            << "AlgorithmLink_tidlpreprocCreateParams " << name << "Prm" << ";"
            << endl;
}
void Alg_tidlpreproc::genResetLinkPrms(ostream &fp, string obj) {
    fp << BLOCK_SPACE << "AlgorithmLink_tidlpreprocCreateParams_Init(&" << obj\
            << "->" << prmName << ");" << endl;
}
int Alg_tidlpreproc::setInLink(Link* obj) //returns QueueID
{
    inLink.push_back(make_pair(obj, -1));
    return (inLink.size() - 1);
}
int Alg_tidlpreproc::setOutLink(Link* obj) //return QueueID
{
    outLink.push_back(make_pair(obj, -1));
    return (outLink.size() - 1);
}
void Alg_tidlpreproc::genSetLinkPrms(ostream &fp, string obj)
{
    fp<<BLOCK_SPACE << "(" << obj << "->" << prmName <<")." << "baseClassCreate.size  = sizeof(AlgorithmLink_tidlpreprocCreateParams);"<<endl;
    if(pType == A15)
        fp<<BLOCK_SPACE << "(" << obj << "->" << prmName <<")." << "baseClassCreate.algId  = ALGORITHM_LINK_A15_ALG_TIDLPREPROC;"<<endl;
    if(pType == IPU1_0)
        fp<<BLOCK_SPACE << "(" << obj << "->" << prmName <<")." << "baseClassCreate.algId  = ALGORITHM_LINK_IPU_ALG_TIDLPREPROC;"<<endl;
}
/********************************************************************************/
Alg_tidlpostproc::Alg_tidlpostproc(string nm) {
    cType = cAlg_tidlpostproc;
    name = nm;
    linkIDName = name + string("LinkID");
    prmName = name + string("Prm");
    execPos = -1;
    procID = -1;
    pType = IPU1_0;
    mulInQue = true;
    mulOutQue = false;
}

Alg_tidlpostproc::~Alg_tidlpostproc() {
}
void Alg_tidlpostproc::genIncludes(ostream &fp) {

    fp << "#include <include/alglink_api/algorithmLink_tidlpostproc.h>"<< endl;
}
void Alg_tidlpostproc::genLinkID(ostream &fp) {
    fp << BLOCK_SPACE << setw(10) << left << "UInt32" << linkIDName << ";" << endl;
}
void Alg_tidlpostproc::genCreatePrms(ostream &fp) {
    fp << BLOCK_SPACE << setw(40) << left
            << "AlgorithmLink_tidlpostprocCreateParams " << name << "Prm" << ";"
            << endl;
}
void Alg_tidlpostproc::genResetLinkPrms(ostream &fp, string obj) {
    fp << BLOCK_SPACE << "AlgorithmLink_tidlpostprocCreateParams_Init(&" << obj\
            << "->" << prmName << ");" << endl;
}
int Alg_tidlpostproc::setInLink(Link* obj) //returns QueueID
{
    inLink.push_back(make_pair(obj, -1));
    return (inLink.size() - 1);
}
int Alg_tidlpostproc::setOutLink(Link* obj) //return QueueID
{
    outLink.push_back(make_pair(obj, -1));
    return (outLink.size() - 1);
}
void Alg_tidlpostproc::genSetLinkPrms(ostream &fp, string obj)
{
    fp<<BLOCK_SPACE << "(" << obj << "->" << prmName <<")." << "baseClassCreate.size  = sizeof(AlgorithmLink_tidlpostprocCreateParams);"<<endl;
    fp<<BLOCK_SPACE << "(" << obj << "->" << prmName <<")." << "baseClassCreate.algId  = ALGORITHM_LINK_A15_ALG_TIDLPOSTPROC;"<<endl;
}
/********************************************************************************/
Capture::Capture(string nm) {
    cType = cCapture;
    name = nm;
    linkIDName = name + string("LinkID");
    prmName = name + string("Prm");
    execPos = -1;
    procID = -1;
    pType = IPU1_0;
    mulInQue = false;
    mulOutQue = false;
}

Capture::~Capture() {
}
void Capture::genIncludes(ostream &fp) {
    CHECK_ERROR_ABORT(inLink.size() == 0, "Error: Link ["+name+"] must have NO incoming link !!!");
    CHECK_ERROR_ABORT(outLink.size() == 1, "Error: Link ["+name+"] must have one outgoing link !!!");
    fp << "#include <include/link_api/captureLink.h>"<< endl;
}
void Capture::genLinkID(ostream &fp) {
    fp << BLOCK_SPACE << setw(IDTYPE_WIDTH) << left << "UInt32" << linkIDName << ";" << endl;
}
void Capture::genCreatePrms(ostream &fp) {
    fp << BLOCK_SPACE << setw(TYPENAME_WIDTH) << left << "CaptureLink_CreateParams"
            << prmName << ";" << endl;
}
void Capture::genResetLinkPrms(ostream &fp, string obj) {
    fp << BLOCK_SPACE << "CaptureLink_CreateParams_Init(&" << obj << "->"
            << prmName << ");" << endl;
}

int Capture::setInLink(Link* obj) //returns QueueID
{
    CHECK_ERROR_ABORT(SHOULD_NOT_REACH, "Error: Link ["+name+"] should not have any incoming link !!!");
    return -1;
}
int Capture::setOutLink(Link* obj) //return QueueID
{
    CHECK_ERROR_ABORT(outLink.size() == 0, "Error: Link ["+name+"] must have one and only one outgoing link !!!");
    outLink.push_back(make_pair(obj, -1));
    return (outLink.size() - 1);
}
void Capture::genSetLinkPrms(ostream &fp, string obj)
{
}
/********************************************************************************/
IssCapture::IssCapture(string nm) {
    cType = cIssCapture;
    name = nm;
    linkIDName = name + string("LinkID");
    prmName = name + string("Prm");
    execPos = -1;
    procID = -1;
    pType = IPU1_0;
    mulInQue = false;
    mulOutQue = false;
}

IssCapture::~IssCapture() {
}
void IssCapture::genIncludes(ostream &fp) {
    CHECK_ERROR_ABORT(inLink.size() == 0, "Error: Link ["+name+"] must have NO incoming link !!!");
    CHECK_ERROR_ABORT(outLink.size() == 1, "Error: Link ["+name+"] must have one outgoing link !!!");
    fp << "#include <include/link_api/issCaptureLink.h>"<< endl;
}
void IssCapture::genLinkID(ostream &fp) {
    fp << BLOCK_SPACE << setw(IDTYPE_WIDTH) << left << "UInt32" << linkIDName << ";" << endl;
}
void IssCapture::genCreatePrms(ostream &fp) {
    fp << BLOCK_SPACE << setw(TYPENAME_WIDTH) << left << "IssCaptureLink_CreateParams"
            << prmName << ";" << endl;
}
void IssCapture::genResetLinkPrms(ostream &fp, string obj) {
    fp << BLOCK_SPACE << "IssCaptureLink_CreateParams_Init(&" << obj << "->"
            << prmName << ");" << endl;
}

int IssCapture::setInLink(Link* obj) //returns QueueID
{
    CHECK_ERROR_ABORT(SHOULD_NOT_REACH, "Error: Link ["+name+"] should not have any incoming link !!!");
    return -1;
}
int IssCapture::setOutLink(Link* obj) //return QueueID
{
    CHECK_ERROR_ABORT(outLink.size() == 0, "Error: Link ["+name+"] must have one and only one outgoing link !!!");
    outLink.push_back(make_pair(obj, -1));
    return (outLink.size() - 1);
}
void IssCapture::genSetLinkPrms(ostream &fp, string obj)
{
}
/********************************************************************************/
IssM2mIsp::IssM2mIsp(string nm) {
    cType = cIssM2mIsp;
    name = nm;
    linkIDName = name + string("LinkID");
    prmName = name + string("Prm");
    execPos = -1;
    procID = -1;
    pType = IPU1_0;
    mulInQue = true;
    mulOutQue = true;
}

IssM2mIsp::~IssM2mIsp() {
}
void IssM2mIsp::genIncludes(ostream &fp) {
    CHECK_ERROR_ABORT(inLink.size() >= 1, "Error: Link ["+name+"] must have atleast one incoming link !!!");
    CHECK_ERROR_ABORT(inLink.size() <= 2, "Error: Link ["+name+"] must have less than two incoming link's !!!");
    CHECK_ERROR_ABORT(outLink.size() >= 1, "Error: Link ["+name+"] must have atleast one outgoing link's !!!");
    CHECK_ERROR_ABORT(outLink.size() <= 4, "Error: Link ["+name+"] must have less than three outgoing link's !!!");
    fp << "#include <include/link_api/issM2mIspLink.h>"<< endl;
}
void IssM2mIsp::genLinkID(ostream &fp) {
    fp << BLOCK_SPACE << setw(IDTYPE_WIDTH) << left << "UInt32" << linkIDName << ";" << endl;
}
void IssM2mIsp::genCreatePrms(ostream &fp) {
    fp << BLOCK_SPACE << setw(TYPENAME_WIDTH) << left << "IssM2mIspLink_CreateParams"
            << prmName << ";" << endl;
}
void IssM2mIsp::genResetLinkPrms(ostream &fp, string obj) {
    fp << BLOCK_SPACE << "IssM2mIspLink_CreateParams_Init(&" << obj << "->"
            << prmName << ");" << endl;
}

int IssM2mIsp::setInLink(Link* obj) //returns QueueID
{
    inLink.push_back(make_pair(obj, -1));
    return (inLink.size() - 1);
}
int IssM2mIsp::setOutLink(Link* obj) //return QueueID
{
    outLink.push_back(make_pair(obj, -1));
    return (outLink.size() - 1);
}
void IssM2mIsp::genSetLinkPrms(ostream &fp, string obj)
{
}
/********************************************************************************/
IssM2mSimcop::IssM2mSimcop(string nm) {
    cType = cIssM2mSimcop;
    name = nm;
    linkIDName = name + string("LinkID");
    prmName = name + string("Prm");
    execPos = -1;
    procID = -1;
    pType = IPU1_0;
    mulInQue = true;
    mulOutQue = false;
}

IssM2mSimcop::~IssM2mSimcop() {
}
void IssM2mSimcop::genIncludes(ostream &fp) {
    //CHECK_ERROR_ABORT(inLink.size() > 2, "Error: Link ["+name+"] must have one or two incoming link !!!"+toString(inLink.size()));
    //CHECK_ERROR_ABORT(inLink.size() > 0, "Error: Link ["+name+"] must have one or two incoming link !!!"+toString(inLink.size()));
    CHECK_ERROR_ABORT(outLink.size() == 1, "Error: Link ["+name+"] must have one outgoing link !!!");
    fp << "#include <include/link_api/issM2mSimcopLink.h>"<< endl;
}
void IssM2mSimcop::genLinkID(ostream &fp) {
    fp << BLOCK_SPACE << setw(IDTYPE_WIDTH) << left << "UInt32" << linkIDName << ";" << endl;
}
void IssM2mSimcop::genCreatePrms(ostream &fp) {
    fp << BLOCK_SPACE << setw(TYPENAME_WIDTH) << left << "IssM2mSimcopLink_CreateParams"
            << prmName << ";" << endl;
}
void IssM2mSimcop::genResetLinkPrms(ostream &fp, string obj) {
    fp << BLOCK_SPACE << "IssM2mSimcopLink_CreateParams_Init(&" << obj << "->"
            << prmName << ");" << endl;
}

int IssM2mSimcop::setInLink(Link* obj) //returns QueueID
{
    //char str[10];
    //sprintf(str, "%d", inLink.size());
    //CHECK_ERROR_ABORT(inLink.size() == 0, "Error: Link ["+name+"] must have one and only one incoming link !!! "+str);
    inLink.push_back(make_pair(obj, -1));
    return (inLink.size() - 1);
}
int IssM2mSimcop::setOutLink(Link* obj) //return QueueID
{
    CHECK_ERROR_ABORT(outLink.size() == 0, "Error: Link ["+name+"] must have one and only one outgoing link !!!");
    outLink.push_back(make_pair(obj, -1));
    return (outLink.size() - 1);
}
void IssM2mSimcop::genSetLinkPrms(ostream &fp, string obj)
{
    fp<<BLOCK_SPACE << "(" << obj << "->" << prmName <<")." << "numInQue = " << inLink.size()<<";"<<endl;
}
/********************************************************************************/
IssM2mResizer::IssM2mResizer(string nm) {
    cType = cIssM2mResizer;
    name = nm;
    linkIDName = name + string("LinkID");
    prmName = name + string("Prm");
    execPos = -1;
    procID = -1;
    pType = IPU1_0;
    mulInQue = false;
    mulOutQue = true;
}

IssM2mResizer::~IssM2mResizer() {
}
void IssM2mResizer::genIncludes(ostream &fp) {
    CHECK_ERROR_ABORT(inLink.size() >= 1, "Error: Link ["+name+"] must have atleast one incoming link !!!");
    CHECK_ERROR_ABORT(inLink.size() <= 2, "Error: Link ["+name+"] must have less than two incoming link's !!!");
    CHECK_ERROR_ABORT(outLink.size() >= 1, "Error: Link ["+name+"] must have atleast one outgoing link's !!!");
    CHECK_ERROR_ABORT(outLink.size() <= 2, "Error: Link ["+name+"] must have less than three outgoing link's !!!");
    fp << "#include <include/link_api/issM2mResizerLink.h>"<< endl;
}
void IssM2mResizer::genLinkID(ostream &fp) {
    fp << BLOCK_SPACE << setw(IDTYPE_WIDTH) << left << "UInt32" << linkIDName << ";" << endl;
}
void IssM2mResizer::genCreatePrms(ostream &fp) {
    fp << BLOCK_SPACE << setw(TYPENAME_WIDTH) << left << "IssRszLink_CreateParams"
            << prmName << ";" << endl;
}
void IssM2mResizer::genResetLinkPrms(ostream &fp, string obj) {
    fp << BLOCK_SPACE << "IssRszLink_CreateParams_Init(&" << obj << "->"
            << prmName << ");" << endl;
}

int IssM2mResizer::setInLink(Link* obj) //returns QueueID
{
    inLink.push_back(make_pair(obj, -1));
    return (inLink.size() - 1);
}
int IssM2mResizer::setOutLink(Link* obj) //return QueueID
{
    outLink.push_back(make_pair(obj, -1));
    return (outLink.size() - 1);
}
void IssM2mResizer::genSetLinkPrms(ostream &fp, string obj)
{
}

/********************************************************************************/
RadarDraw::RadarDraw(string nm) {
    cType = cRadarDraw;
    name = nm;
    linkIDName = name + string("LinkID");
    prmName = name + string("Prm");
    execPos = -1;
    procID = -1;
    pType = IPU1_0;
    mulInQue = false;
    mulOutQue = false;
}

RadarDraw::~RadarDraw() {
}
void RadarDraw::genIncludes(ostream &fp) {
    //CHECK_ERROR_ABORT(inLink.size() > 2, "Error: Link ["+name+"] must have one or two incoming link !!!"+toString(inLink.size()));
    CHECK_ERROR_ABORT(inLink.size() == 1, "Error: Link ["+name+"] must have one or two incoming link !!!"+toString(inLink.size()));
    CHECK_ERROR_ABORT(outLink.size() == 1, "Error: Link ["+name+"] must have one outgoing link !!!");
    fp << "#include <include/link_api/radarDrawLink.h>"<< endl;
}
void RadarDraw::genLinkID(ostream &fp) {
    fp << BLOCK_SPACE << setw(10) << left << "UInt32" << linkIDName << ";" << endl;
}
void RadarDraw::genCreatePrms(ostream &fp) {
    fp << BLOCK_SPACE << setw(40) << left << "RadarDrawLink_CreateParams"
            << prmName << ";" << endl;
}
void RadarDraw::genResetLinkPrms(ostream &fp, string obj) {
    fp << BLOCK_SPACE << "RadarDrawLink_CreateParams_Init(&" << obj << "->"
            << prmName << ");" << endl;
}

int RadarDraw::setInLink(Link* obj) //returns QueueID
{
    //char str[10];
    //sprintf(str, "%d", inLink.size());
    //CHECK_ERROR_ABORT(inLink.size() == 0, "Error: Link ["+name+"] must have one and only one incoming link !!! "+str);
    inLink.push_back(make_pair(obj, -1));
    return (inLink.size() - 1);
}
int RadarDraw::setOutLink(Link* obj) //return QueueID
{
    CHECK_ERROR_ABORT(outLink.size() == 0, "Error: Link ["+name+"] must have one and only one outgoing link !!!");
    outLink.push_back(make_pair(obj, -1));
    return (outLink.size() - 1);
}
void RadarDraw::genSetLinkPrms(ostream &fp, string obj)
{
}

/********************************************************************************/
UltrasonicCapture::UltrasonicCapture(string nm) {
    cType = cUltrasonicCapture;
    name = nm;
    linkIDName = name + string("LinkID");
    prmName = name + string("Prm");
    execPos = -1;
    procID = -1;
    pType = IPU1_0;
    mulInQue = false;
    mulOutQue = false;
}

UltrasonicCapture::~UltrasonicCapture() {
}
void UltrasonicCapture::genIncludes(ostream &fp) {
    CHECK_ERROR_ABORT(inLink.size() == 0, "Error: Link ["+name+"] must have NO incoming link !!!");
    CHECK_ERROR_ABORT(outLink.size() == 1, "Error: Link ["+name+"] must have one outgoing link !!!");
    fp << "#include <include/link_api/ultrasonicCaptureLink.h>"<< endl;
}
void UltrasonicCapture::genLinkID(ostream &fp) {
    fp << BLOCK_SPACE << setw(IDTYPE_WIDTH) << left << "UInt32" << linkIDName << ";" << endl;
}
void UltrasonicCapture::genCreatePrms(ostream &fp) {
    fp << BLOCK_SPACE << setw(TYPENAME_WIDTH) << left << "UltrasonicCaptureLink_CreateParams"
            << prmName << ";" << endl;
}
void UltrasonicCapture::genResetLinkPrms(ostream &fp, string obj) {
    fp << BLOCK_SPACE << "UltrasonicCaptureLink_CreateParams_Init(&" << obj << "->"
            << prmName << ");" << endl;
}

int UltrasonicCapture::setInLink(Link* obj) //returns QueueID
{
    CHECK_ERROR_ABORT(SHOULD_NOT_REACH, "Error: Link ["+name+"] should not have any incoming link !!!");
    return -1;
}
int UltrasonicCapture::setOutLink(Link* obj) //return QueueID
{
    CHECK_ERROR_ABORT(outLink.size() == 0, "Error: Link ["+name+"] must have one and only one outgoing link !!!");
    outLink.push_back(make_pair(obj, -1));
    return (outLink.size() - 1);
}
void UltrasonicCapture::genSetLinkPrms(ostream &fp, string obj)
{
}


/********************************************************************************/
Decode::Decode(string nm) {
    cType = cDecode;
    name = nm;
    linkIDName = name + string("LinkID");
    prmName = name + string("Prm");
    execPos = -1;
    procID = -1;
    pType = IPU1_0;
    mulInQue = false;
    mulOutQue = false;
}

Decode::~Decode() {
}
void Decode::genIncludes(ostream &fp) {
    CHECK_ERROR_ABORT(inLink.size() == 1, "Error: Link ["+name+"] must have one incoming link !!!");
    CHECK_ERROR_ABORT(outLink.size() == 1, "Error: Link ["+name+"] must have one outgoing link !!!");
    fp << "#include <include/link_api/decLink.h>"<< endl;
}
void Decode::genLinkID(ostream &fp) {
    fp << BLOCK_SPACE << setw(IDTYPE_WIDTH) << left << "UInt32" << linkIDName << ";" << endl;
}
void Decode::genCreatePrms(ostream &fp) {
    fp << BLOCK_SPACE << setw(TYPENAME_WIDTH) << left << "DecLink_CreateParams " << prmName << ";"
            << endl;
}
void Decode::genResetLinkPrms(ostream &fp, string obj) {
    fp << BLOCK_SPACE << "DecLink_CreateParams_Init(&" << obj << "->" << prmName
            << ");" << endl;
}
int Decode::setInLink(Link* obj) {
    CHECK_ERROR_ABORT(inLink.size() == 0, "Error: Link ["+name+"] must have one and only one incoming link !!!");
    inLink.push_back(make_pair(obj, -1));
    return (inLink.size() - 1);
}
int Decode::setOutLink(Link* obj) {
    CHECK_ERROR_ABORT(outLink.size() == 0, "Error: Link ["+name+"] must have one and only one outgoing link !!!");
    outLink.push_back(make_pair(obj, -1));
    return (outLink.size() - 1);
}
void Decode::genSetLinkPrms(ostream &fp, string obj)
{
}
/********************************************************************************/
DisplayCtrl::DisplayCtrl(string nm) {
    cType = cDisplayCtrl;
    name = nm;
    linkIDName = name + string("LinkID");
    prmName = name + string("Prm");
    execPos = -1;
    procID = -1;
    pType = IPU1_0;
    mulInQue = false;
    mulOutQue = false;
}

DisplayCtrl::~DisplayCtrl() {
}
void DisplayCtrl::genIncludes(ostream &fp) {
    CHECK_ERROR_ABORT(inLink.size() == 0, "Error: Link ["+name+"] must have NO incoming link !!!");
    CHECK_ERROR_ABORT(outLink.size() == 0, "Error: Link ["+name+"] must have NO outgoing link !!!");

    fp << "#include <include/link_api/displayCtrlLink.h>"<< endl;
}
void DisplayCtrl::genLinkID(ostream &fp) {
    fp << BLOCK_SPACE << setw(IDTYPE_WIDTH) << left << "UInt32" << linkIDName << ";" << endl;
}
void DisplayCtrl::genCreatePrms(ostream &fp) {
    fp << BLOCK_SPACE << setw(TYPENAME_WIDTH) << left << "DisplayCtrlLink_ConfigParams"
            << name << "Prm" << ";" << endl;
}
void DisplayCtrl::genResetLinkPrms(ostream &fp, string obj) {
    fp << BLOCK_SPACE << "DisplayCtrlLink_CreateParams_Init(&" << obj << "->"
            << prmName << ");" << endl;
}
int DisplayCtrl::setInLink(Link* obj) {
    CHECK_ERROR_ABORT(inLink.size() == 0, "Error: Link ["+name+"] must have one and only one incoming link !!!");
    inLink.push_back(make_pair(obj, -1));
    return (inLink.size() - 1);
}
int DisplayCtrl::setOutLink(Link* obj) {
    CHECK_ERROR_ABORT(outLink.size() == 0, "Error: Link ["+name+"] must have one and only one outgoing link !!!");
    outLink.push_back(make_pair(obj, -1));
    return (outLink.size() - 1);
}

void DisplayCtrl::genSetLinkPrms(ostream &fp, string obj)
{
}
/********************************************************************************/
Display::Display(string nm) {
    cType = cDisplay;
    name = nm;
    linkIDName = name + string("LinkID");
    prmName = name + string("Prm");
    execPos = -1;
    procID = -1;
    pType = IPU1_0;
    mulInQue = false;
    mulOutQue = false;
}

Display::~Display() {
}
void Display::genIncludes(ostream &fp) {
    CHECK_ERROR_ABORT(inLink.size() == 1, "Error: Link ["+name+"] must have one incoming link !!!");
    CHECK_ERROR_ABORT(outLink.size() == 0, "Error: Link ["+name+"] must have NO outgoing link !!!");
    fp << "#include <include/link_api/displayLink.h>"<< endl;
}
void Display::genLinkID(ostream &fp) {
    //UInt32              displayLinkId;
    fp << BLOCK_SPACE << setw(IDTYPE_WIDTH) << left << "UInt32" << linkIDName << ";" << endl;
}
void Display::genCreatePrms(ostream &fp) {
    //DisplayLink_CreateParams                displayPrm;
    fp << BLOCK_SPACE << setw(TYPENAME_WIDTH) << left << "DisplayLink_CreateParams"
            << prmName << ";" << endl;
}
void Display::genResetLinkPrms(ostream &fp, string obj) {
    fp << BLOCK_SPACE << "DisplayLink_CreateParams_Init(&" << obj << "->"
            << prmName << ");" << endl;
}
int Display::setInLink(Link* obj) //returns QueueID
{
    CHECK_ERROR_ABORT(inLink.size() == 0, "Error: Link ["+name+"] must have one and only one incoming link !!!");
    inLink.push_back(make_pair(obj, -1));
    return (inLink.size() - 1);
}
int Display::setOutLink(Link* obj) //return QueueID
{
    CHECK_ERROR_ABORT(SHOULD_NOT_REACH, "Error: Link ["+name+"] should not have outgoing links !!!");
    return -1;
}
void Display::genSetLinkPrms(ostream &fp, string obj)
{
}
/********************************************************************************/
DisplayMultiPipe::DisplayMultiPipe(string nm) {
    cType = cDisplayMultiPipe;
    name = nm;
    linkIDName = name + string("LinkID");
    prmName = name + string("Prm");
    execPos = -1;
    procID = -1;
    pType = IPU1_0;
    mulInQue = false;
    mulOutQue = false;
}

DisplayMultiPipe::~DisplayMultiPipe() {
}
void DisplayMultiPipe::genIncludes(ostream &fp) {
    CHECK_ERROR_ABORT(inLink.size() == 1, "Error: Link ["+name+"] must have one incoming link !!!");
    CHECK_ERROR_ABORT(outLink.size() == 0, "Error: Link ["+name+"] must have NO outgoing link !!!");
    fp << "#include <include/link_api/displayMultiPipeLink.h>"<< endl;
}
void DisplayMultiPipe::genLinkID(ostream &fp) {
    //UInt32              displayLinkId;
    fp << BLOCK_SPACE << setw(10) << left << "UInt32" << linkIDName << ";" << endl;
}
void DisplayMultiPipe::genCreatePrms(ostream &fp) {
    //DisplayLink_CreateParams                displayPrm;
    fp << BLOCK_SPACE << setw(40) << left << "DisplayMpLink_CreateParams"
            << prmName << ";" << endl;
}
void DisplayMultiPipe::genResetLinkPrms(ostream &fp, string obj) {
    fp << BLOCK_SPACE << "DisplayMpLink_CreateParams_Init(&" << obj << "->"
            << prmName << ");" << endl;
}
int DisplayMultiPipe::setInLink(Link* obj) //returns QueueID
{
    CHECK_ERROR_ABORT(inLink.size() == 0, "Error: Link ["+name+"] must have one and only one incoming link !!!");
    inLink.push_back(make_pair(obj, -1));
    return (inLink.size() - 1);
}
int DisplayMultiPipe::setOutLink(Link* obj) //return QueueID
{
    CHECK_ERROR_ABORT(SHOULD_NOT_REACH, "Error: Link ["+name+"] should not have outgoing links !!!");
    return -1;
}
void DisplayMultiPipe::genSetLinkPrms(ostream &fp, string obj)
{
}
/********************************************************************************/
GrpxSrc::GrpxSrc(string nm) {
    cType = cGrpxSrc;
    name = nm;
    linkIDName = name + string("LinkID");
    prmName = name + string("Prm");
    execPos = -1;
    procID = -1;
    pType = IPU1_0;
    mulInQue = false;
    mulOutQue = false;
}

GrpxSrc::~GrpxSrc() {
}
void GrpxSrc::genIncludes(ostream &fp) {
    CHECK_ERROR_ABORT(inLink.size() <= 1, "Error: Link ["+name+"] must have <= 1 incoming link !!!");
    CHECK_ERROR_ABORT(outLink.size() == 1, "Error: Link ["+name+"] must have one outgoing link !!!");
    fp << "#include <include/link_api/grpxSrcLink.h>"<< endl; //TODO: Check
}
void GrpxSrc::genLinkID(ostream &fp) {
    //UInt32              DupLinkId;
    fp << BLOCK_SPACE << setw(IDTYPE_WIDTH) << left << "UInt32" << linkIDName << ";" << endl;
}
void GrpxSrc::genCreatePrms(ostream &fp) {
    //DupLink_CreateParams                    ipuDupPrm;
    fp << BLOCK_SPACE << setw(TYPENAME_WIDTH) << left << "GrpxSrcLink_CreateParams"
            << prmName << ";" << endl;
}
void GrpxSrc::genResetLinkPrms(ostream &fp, string obj) {
    fp << BLOCK_SPACE << "GrpxSrcLink_CreateParams_Init(&" << obj << "->"
            << prmName << ");" << endl;
}
int GrpxSrc::setInLink(Link* obj) //returns QueueID
{
    inLink.push_back(make_pair(obj, -1));
    return (inLink.size() - 1);
}

int GrpxSrc::setOutLink(Link* obj) //return QueueID
{
    outLink.push_back(make_pair(obj, -1));
    return (outLink.size() - 1);
}
void GrpxSrc::genSetLinkPrms(ostream &fp, string obj)
{
}
/********************************************************************************/
Dup::Dup(string nm) {
    cType = cDup;
    name = nm;
    linkIDName = name + string("LinkID");
    prmName = name + string("Prm");
    execPos = -1;
    procID = -1;
    pType = IPU1_0;
    mulInQue = false;
    mulOutQue = true;
}

Dup::~Dup() {
}
void Dup::genIncludes(ostream &fp) {
    CHECK_ERROR_ABORT(inLink.size() == 1, "Error: Link ["+name+"] must have one incoming link !!!");
    CHECK_ERROR_ABORT(outLink.size() > 0, "Error: Link ["+name+"] must have atleast one outgoing link !!!");
    fp << "#include <include/link_api/dupLink.h>"<< endl;
}
void Dup::genLinkID(ostream &fp) {
    //UInt32              DupLinkId;
    fp << BLOCK_SPACE << setw(IDTYPE_WIDTH) << left << "UInt32" << linkIDName << ";" << endl;
}
void Dup::genCreatePrms(ostream &fp) {
    //DupLink_CreateParams                    ipuDupPrm;
    fp << BLOCK_SPACE << setw(TYPENAME_WIDTH) << left << "DupLink_CreateParams " << prmName
            << ";" << endl;
}
void Dup::genResetLinkPrms(ostream &fp, string obj) {
    fp << BLOCK_SPACE << "DupLink_CreateParams_Init(&" << obj << "->" << prmName
            << ");" << endl;
}
int Dup::setInLink(Link* obj) //returns QueueID
{
    CHECK_ERROR_ABORT(inLink.size() == 0, "Error: Link ["+name+"] must have one and only one incoming link !!!");
    inLink.push_back(make_pair(obj, -1));
    return (inLink.size() - 1);
}

int Dup::setOutLink(Link* obj) //return QueueID
{
    outLink.push_back(make_pair(obj, -1));
    return (outLink.size() - 1);
}
void Dup::genSetLinkPrms(ostream &fp, string obj)
{
    fp<<BLOCK_SPACE << "(" << obj << "->" << prmName <<")." << "numOutQue = " << outLink.size()<<";"<<endl;
}

/********************************************************************************/
Split::Split(string nm) {
    cType = cSplit;
    name = nm;
    linkIDName = name + string("LinkID");
    prmName = name + string("Prm");
    execPos = -1;
    procID = -1;
    pType = IPU1_0;
    mulInQue = false;
    mulOutQue = false;
}

Split::~Split() {
}
void Split::genIncludes(ostream &fp) {
    CHECK_ERROR_ABORT(inLink.size() == 1, "Error: Link ["+name+"] must have one incoming link !!!");
    CHECK_ERROR_ABORT(outLink.size() > 0, "Error: Link ["+name+"] must have atleast one outgoing link !!!");
    fp << "#include <include/link_api/splitLink.h>"<< endl;
}
void Split::genLinkID(ostream &fp) {
    //UInt32              SplitLinkId;
    fp << BLOCK_SPACE << setw(IDTYPE_WIDTH) << left << "UInt32" << linkIDName << ";" << endl;
}
void Split::genCreatePrms(ostream &fp) {
    //SplitLink_CreateParams                    ipuSplitPrm;
    fp << BLOCK_SPACE << setw(TYPENAME_WIDTH) << left << "SplitLink_CreateParams " << prmName
            << ";" << endl;
}
void Split::genResetLinkPrms(ostream &fp, string obj) {
    fp << BLOCK_SPACE << "SplitLink_CreateParams_Init(&" << obj << "->" << prmName
            << ");" << endl;
}
int Split::setInLink(Link* obj) //returns QueueID
{
    CHECK_ERROR_ABORT(inLink.size() == 0, "Error: Link ["+name+"] must have one and only one incoming link !!!");
    inLink.push_back(make_pair(obj, -1));
    return (inLink.size() - 1);
}

int Split::setOutLink(Link* obj) //return QueueID
{
    outLink.push_back(make_pair(obj, -1));
    return (outLink.size() - 1);
}
void Split::genSetLinkPrms(ostream &fp, string obj)
{
}

/********************************************************************************/
Gate::Gate(string nm) {
    cType = cGate;
    name = nm;
    linkIDName = name + string("LinkID");
    prmName = name + string("Prm");
    execPos = -1;
    procID = -1;
    pType = IPU1_0;
    mulInQue = false;
    mulOutQue = false;
}

Gate::~Gate() {
}
void Gate::genIncludes(ostream &fp) {
    CHECK_ERROR_ABORT(inLink.size() == 1, "Error: Link ["+name+"] must have one incoming link !!!");
    CHECK_ERROR_ABORT(outLink.size() == 1, "Error: Link ["+name+"] must have one outgoing link !!!");
    fp << "#include <include/link_api/gateLink.h>"<< endl;
}
void Gate::genLinkID(ostream &fp) {
    fp << BLOCK_SPACE << setw(IDTYPE_WIDTH) << left << "UInt32" << linkIDName << ";" << endl;
}
void Gate::genCreatePrms(ostream &fp) {
    fp << BLOCK_SPACE << setw(TYPENAME_WIDTH) << left << "GateLink_CreateParams " << prmName
            << ";" << endl;
}
void Gate::genResetLinkPrms(ostream &fp, string obj) {
    fp << BLOCK_SPACE << "GateLink_CreateParams_Init(&" << obj << "->" << prmName
            << ");" << endl;
}
int Gate::setInLink(Link* obj)
{
    CHECK_ERROR_ABORT(inLink.size() == 0, "Error: Link ["+name+"] must have one and only one incoming link !!!");
    inLink.push_back(make_pair(obj, -1));
    return (inLink.size() - 1);
}

int Gate::setOutLink(Link* obj)
{
    outLink.push_back(make_pair(obj, -1));
    return (outLink.size() - 1);
}
void Gate::genSetLinkPrms(ostream &fp, string obj)
{
}
/********************************************************************************/
Encode::Encode(string nm) {
    cType = cEncode;
    name = nm;
    linkIDName = name + string("LinkID");
    prmName = name + string("Prm");
    execPos = -1;
    procID = -1;
    pType = IPU1_0;
    mulInQue = false;
    mulOutQue = false;
}

Encode::~Encode() {
}
void Encode::genIncludes(ostream &fp) {
    CHECK_ERROR_ABORT(inLink.size() == 1, "Error: Link ["+name+"] must have one incoming link !!!");
    CHECK_ERROR_ABORT(outLink.size() == 1, "Error: Link ["+name+"] must have one outgoing link !!!");
    fp << "#include <include/link_api/encLink.h>"<< endl;
}
void Encode::genLinkID(ostream &fp) {
    fp << BLOCK_SPACE << setw(IDTYPE_WIDTH) << left << "UInt32" << linkIDName << ";" << endl;
}
void Encode::genCreatePrms(ostream &fp) {
    fp << BLOCK_SPACE << setw(TYPENAME_WIDTH) << left << "EncLink_CreateParams " << prmName
            << ";" << endl;
}
void Encode::genResetLinkPrms(ostream &fp, string obj) {
    fp << BLOCK_SPACE << "EncLink_CreateParams_Init(&" << obj << "->" << prmName
            << ");" << endl;
}
int Encode::setInLink(Link* obj) //returns QueueID
{
    CHECK_ERROR_ABORT(inLink.size() == 0, "Error: Link ["+name+"] must have one and only one incoming link !!!");
    inLink.push_back(make_pair(obj, -1));
    return (inLink.size() - 1);
}
int Encode::setOutLink(Link* obj) //return QueueID
{
    CHECK_ERROR_ABORT(outLink.size() == 0, "Error: Link ["+name+"] must have one and only one outgoing link !!!");
    outLink.push_back(make_pair(obj, -1));
    return (outLink.size() - 1);
}
void Encode::genSetLinkPrms(ostream &fp, string obj)
{
}
/********************************************************************************/
IPCIn::IPCIn(string nm) {
    cType = cIPCIn;
    name = nm;
    linkIDName = name + string("LinkID");
    prmName = name + string("Prm");
    execPos = -1;
    procID = -1;
    pType = IPU1_0;
    mulInQue = false;
    mulOutQue = false;
    ipcName = "";
}

IPCIn::~IPCIn() {
}
void IPCIn::genIncludes(ostream &fp) {
    fp << "#include <include/link_api/ipcLink.h>"<< endl;
}
void IPCIn::genLinkID(ostream &fp) {
    //UInt32              ipcInLink_IPU1_0_Id;
    fp << BLOCK_SPACE << setw(IDTYPE_WIDTH) << left << "UInt32" << linkIDName << ";" << endl;
}
void IPCIn::genCreatePrms(ostream &fp) {
    //IpcLink_CreateParams                    ipcInLink_IPU1_0_Prm;
    fp << BLOCK_SPACE << setw(TYPENAME_WIDTH) << left << "IpcLink_CreateParams " << prmName
            << ";" << endl;
}
void IPCIn::genResetLinkPrms(ostream &fp, string obj) {
    fp << BLOCK_SPACE << "IpcLink_CreateParams_Init(&" << obj << "->"
            << prmName << ");" << endl;
}
int IPCIn::setInLink(Link* obj) //returns QueueID
{
    CHECK_ERROR_ABORT(inLink.size() == 0, "Error: Link ["+name+"] must have one and only one incoming link !!!");
    inLink.push_back(make_pair(obj, -1));
    return (inLink.size() - 1);
}
int IPCIn::setOutLink(Link* obj) //return QueueID
{
    CHECK_ERROR_ABORT(outLink.size() == 0, "Error: Link ["+name+"] must have one and only one outgoing link !!!");
    outLink.push_back(make_pair(obj, -1));
    return (outLink.size() - 1);
}
void IPCIn::genSetLinkPrms(ostream &fp, string obj)
{
}
/********************************************************************************/
IPCOut::IPCOut(string nm) {
    cType = cIPCOut;
    name = nm;
    linkIDName = name + string("LinkID");
    prmName = name + string("Prm");
    execPos = -1;
    procID = -1;
    pType = IPU1_0;
    mulInQue = false;
    mulOutQue = false;
    ipcName = "";
}

IPCOut::~IPCOut() {
}
void IPCOut::genIncludes(ostream &fp) {
    //No need in IPCOut, for every IPCOut there will be IPCIn
    //fp << "#include <include/link_api/ipcLink.h>"<< endl;
}
void IPCOut::genLinkID(ostream &fp) {
    //UInt32              ipcInLink_IPU1_0_Id;
    fp << BLOCK_SPACE << setw(IDTYPE_WIDTH) << left << "UInt32" << linkIDName << ";" << endl;
}
void IPCOut::genCreatePrms(ostream &fp) {
    //IpcLink_CreateParams                    ipcInLink_IPU1_0_Prm;
    fp << BLOCK_SPACE << setw(TYPENAME_WIDTH) << left << "IpcLink_CreateParams " << prmName
            << ";" << endl;
}
void IPCOut::genResetLinkPrms(ostream &fp, string obj) {
    fp << BLOCK_SPACE << "IpcLink_CreateParams_Init(&" << obj << "->"
            << prmName << ");" << endl;
}
int IPCOut::setInLink(Link* obj) //returns QueueID
{
    CHECK_ERROR_ABORT(inLink.size() == 0, "Error: Link ["+name+"] must have one and only one incoming link !!!");
    inLink.push_back(make_pair(obj, -1));
    return (inLink.size() - 1);
}
int IPCOut::setOutLink(Link* obj) //return QueueID
{
    CHECK_ERROR_ABORT(outLink.size() == 0, "Error: Link ["+name+"] must have one and only one outgoing link !!!");
    outLink.push_back(make_pair(obj, -1));
    return (outLink.size() - 1);
}
void IPCOut::genSetLinkPrms(ostream &fp, string obj)
{
}
/********************************************************************************/
Merge::Merge(string nm) {
    cType = cMerge;
    name = nm;
    linkIDName = name + string("LinkID");
    prmName = name + string("Prm");
    execPos = -1;
    procID = -1;
    pType = IPU1_0;
    mulInQue = true;
    mulOutQue = false;
}

Merge::~Merge() {
}
void Merge::genIncludes(ostream &fp) {
    CHECK_ERROR_ABORT(inLink.size() > 0, "Error: Link ["+name+"] must have atleast one incoming link !!!");
    CHECK_ERROR_ABORT(outLink.size() == 1, "Error: Link ["+name+"] must have one outgoing link !!!");
    fp << "#include <include/link_api/mergeLink.h>"<< endl;
}
void Merge::genLinkID(ostream &fp) {
    //UInt32              dspMergeLinkId;
    fp << BLOCK_SPACE << setw(IDTYPE_WIDTH) << left << "UInt32" << linkIDName << ";" << endl;
}
void Merge::genCreatePrms(ostream &fp) {
    //MergeLink_CreateParams                  dspMergePrm;
    fp << BLOCK_SPACE << setw(TYPENAME_WIDTH) << left << "MergeLink_CreateParams " << prmName
            << ";" << endl;
}
void Merge::genResetLinkPrms(ostream &fp, string obj) {
    fp << BLOCK_SPACE << "MergeLink_CreateParams_Init(&" << obj << "->"
            << prmName << ");" << endl;
}
int Merge::setInLink(Link* obj) //returns QueueID
{
    inLink.push_back(make_pair(obj, -1));
    return (inLink.size() - 1);
}
int Merge::setOutLink(Link* obj) //return QueueID
{
    CHECK_ERROR_ABORT(outLink.size() == 0, "Error: Link ["+name+"] must have one and only one outgoing link !!!");
    outLink.push_back(make_pair(obj, -1));
    return (outLink.size() - 1);
}
void Merge::genSetLinkPrms(ostream &fp, string obj)
{
    fp<<BLOCK_SPACE << "(" << obj << "->" << prmName <<")." << "numInQue = " << inLink.size()<<";"<<endl;
}
/********************************************************************************/
NullSource::NullSource(string nm) {
    cType = cNullSource;
    name = nm;
    linkIDName = name + string("LinkID");
    prmName = name + string("Prm");
    execPos = -1;
    procID = -1;
    pType = IPU1_0;
    mulInQue = false;
    mulOutQue = false;
}

NullSource::~NullSource() {
}
void NullSource::genIncludes(ostream &fp) {
    CHECK_ERROR_ABORT(inLink.size() == 0, "Error: Link ["+name+"] must have NO incoming link !!!");
    CHECK_ERROR_ABORT(outLink.size() == 1, "Error: Link ["+name+"] must have one outgoing link !!!");
    fp << "#include <include/link_api/nullSrcLink.h>"<< endl;
}
void NullSource::genLinkID(ostream &fp) {
    fp << BLOCK_SPACE << setw(IDTYPE_WIDTH) << left << "UInt32" << linkIDName << ";" << endl;
}
void NullSource::genCreatePrms(ostream &fp) {
    fp << BLOCK_SPACE << setw(TYPENAME_WIDTH) << left << "NullSrcLink_CreateParams"
            << prmName << ";" << endl;
}
void NullSource::genResetLinkPrms(ostream &fp, string obj) {
    fp << BLOCK_SPACE << "NullSrcLink_CreateParams_Init(&" << obj << "->"
            << prmName << ");" << endl;
}
int NullSource::setInLink(Link* obj) {
    CHECK_ERROR_ABORT(inLink.size() == 0, "Error: Link ["+name+"] must have one and only one incoming link !!!");
    inLink.push_back(make_pair(obj, -1));
    return (inLink.size() - 1);
}
int NullSource::setOutLink(Link* obj) {
    CHECK_ERROR_ABORT(outLink.size() == 0, "Error: Link ["+name+"] must have one and only one outgoing link !!!");
    outLink.push_back(make_pair(obj, -1));
    return (outLink.size() - 1);
}
void NullSource::genSetLinkPrms(ostream &fp, string obj)
{
}
/********************************************************************************/
Null::Null(string nm) {
    cType = cNull;
    name = nm;
    linkIDName = name + string("LinkID");
    prmName = name + string("Prm");
    execPos = -1;
    procID = -1;
    pType = IPU1_0;
    mulInQue = true;
    mulOutQue = false;
}

Null::~Null() {
}
void Null::genIncludes(ostream &fp) {
    CHECK_ERROR_ABORT(inLink.size() > 0, "Error: Link ["+name+"] must have atleast one incoming link !!!");
    CHECK_ERROR_ABORT(outLink.size() == 0, "Error: Link ["+name+"] must have NO outgoing link !!!");
    fp << "#include <include/link_api/nullLink.h>"<< endl;
}
void Null::genLinkID(ostream &fp) {
    fp << BLOCK_SPACE << setw(IDTYPE_WIDTH) << left << "UInt32" << linkIDName << ";" << endl;
}
void Null::genCreatePrms(ostream &fp) {
    fp << BLOCK_SPACE << setw(TYPENAME_WIDTH) << left << "NullLink_CreateParams " << prmName << ";"
            << endl;
}
void Null::genResetLinkPrms(ostream &fp, string obj) {
    fp << BLOCK_SPACE << "NullLink_CreateParams_Init (&" << obj << "->"
            << prmName << ");" << endl;
}

int Null::setInLink(Link* obj) {
    inLink.push_back(make_pair(obj, -1));
    return (inLink.size() - 1);
}
int Null::setOutLink(Link* obj) {
   CHECK_ERROR_ABORT(SHOULD_NOT_REACH, "Error: Link ["+name+"] must have NO outgoing link !!!");
   return -1;
}
void Null::genSetLinkPrms(ostream &fp, string obj)
{
    fp<<BLOCK_SPACE << "(" << obj << "->" << prmName <<")." << "numInQue = " << inLink.size()<<";"<<endl;
}
/********************************************************************************/
NetworkRx::NetworkRx(string nm) {
    cType = cNetworkRx;
    name = nm;
    linkIDName = name + string("LinkID");
    prmName = name + string("Prm");
    execPos = -1;
    procID = -1;
    pType = IPU1_0;
    mulInQue = false;
    mulOutQue = false;
}

NetworkRx::~NetworkRx() {
}
void NetworkRx::genIncludes(ostream &fp) {
    CHECK_ERROR_ABORT(inLink.size() == 0, "Error: Link ["+name+"] must have NO incoming link !!!");
    CHECK_ERROR_ABORT(outLink.size() == 1, "Error: Link ["+name+"] must have one outgoing link !!!");
    fp << "#include <include/link_api/networkRxLink.h>"<< endl;
}
void NetworkRx::genLinkID(ostream &fp) {
    fp << BLOCK_SPACE << setw(IDTYPE_WIDTH) << left << "UInt32" << linkIDName << ";" << endl;
}
void NetworkRx::genCreatePrms(ostream &fp) {
    fp << BLOCK_SPACE << setw(TYPENAME_WIDTH) << left << "NetworkRxLink_CreateParams"
            << prmName << ";" << endl;
}
void NetworkRx::genResetLinkPrms(ostream &fp, string obj) {
    fp << BLOCK_SPACE << "NetworkRxLink_CreateParams_Init(&" << obj << "->"
            << prmName << ");" << endl;
}
int NetworkRx::setInLink(Link* obj) {
    CHECK_ERROR_ABORT(inLink.size() == 0, "Error: Link ["+name+"] must have one and only one incoming link !!!");
    inLink.push_back(make_pair(obj, -1));
    return (inLink.size() - 1);
}
int NetworkRx::setOutLink(Link* obj) {
    CHECK_ERROR_ABORT(outLink.size() == 0, "Error: Link ["+name+"] must have one and only one outgoing link !!!");
    outLink.push_back(make_pair(obj, -1));
    return (outLink.size() - 1);
}
void NetworkRx::genSetLinkPrms(ostream &fp, string obj)
{
}
/********************************************************************************/
NetworkTx::NetworkTx(string nm) {
    cType = cNetworkTx;
    name = nm;
    linkIDName = name + string("LinkID");
    prmName = name + string("Prm");
    execPos = -1;
    procID = -1;
    pType = IPU1_0;
    mulInQue = true;
    mulOutQue = false;
}

NetworkTx::~NetworkTx() {
}
void NetworkTx::genIncludes(ostream &fp) {
    CHECK_ERROR_ABORT(inLink.size() > 0, "Error: Link ["+name+"] must have atleast one incoming link !!!");
    CHECK_ERROR_ABORT(outLink.size() == 0, "Error: Link ["+name+"] must have NO outgoing link !!!");
    fp << "#include <include/link_api/networkTxLink.h>"<< endl;
}
void NetworkTx::genLinkID(ostream &fp) {
    fp << BLOCK_SPACE << setw(IDTYPE_WIDTH) << left << "UInt32" << linkIDName << ";" << endl;
}
void NetworkTx::genCreatePrms(ostream &fp) {
    fp << BLOCK_SPACE << setw(TYPENAME_WIDTH) << left << "NetworkTxLink_CreateParams " << prmName << ";"
            << endl;
}
void NetworkTx::genResetLinkPrms(ostream &fp, string obj) {
    fp << BLOCK_SPACE << "NetworkTxLink_CreateParams_Init (&" << obj << "->"
            << prmName << ");" << endl;
}

int NetworkTx::setInLink(Link* obj) {
    inLink.push_back(make_pair(obj, -1));
    return (inLink.size() - 1);
}
int NetworkTx::setOutLink(Link* obj) {
   CHECK_ERROR_ABORT(SHOULD_NOT_REACH, "Error: Link ["+name+"] must have NO outgoing link !!!");
   return -1;
}
void NetworkTx::genSetLinkPrms(ostream &fp, string obj)
{
    fp<<BLOCK_SPACE << "(" << obj << "->" << prmName <<")." << "numInQue = " << inLink.size()<<";"<<endl;
}
DataCollect::DataCollect(string nm) {
    cType = cDataCollect;
    name = nm;
    linkIDName = name + string("LinkID");
    prmName = name + string("Prm");
    execPos = -1;
    procID = -1;
    pType = A15;
    mulInQue = false;
    mulOutQue = false;
}

DataCollect::~DataCollect() {
}
void DataCollect::genIncludes(ostream &fp) {
    CHECK_ERROR_ABORT(inLink.size() == 1, "Error: Link ["+name+"] must have exactly ONE incoming link !!!");
    CHECK_ERROR_ABORT(outLink.size() == 0, "Error: Link ["+name+"] must have NO outgoing link !!!");
    fp << "#include <link_api/dataCollectLink.h>"<< endl;
}
void DataCollect::genLinkID(ostream &fp) {
    fp << BLOCK_SPACE << setw(IDTYPE_WIDTH) << left << "UInt32" << linkIDName << ";" << endl;
}
void DataCollect::genCreatePrms(ostream &fp) {
    fp << BLOCK_SPACE << setw(TYPENAME_WIDTH) << left << "DataCollectLink_CreateParams " << prmName << ";"
            << endl;
}
void DataCollect::genResetLinkPrms(ostream &fp, string obj) {
    fp << BLOCK_SPACE << "DataCollectLink_CreateParams_Init (&" << obj << "->"
            << prmName << ");" << endl;
}

int DataCollect::setInLink(Link* obj) {
    inLink.push_back(make_pair(obj, -1));
    return (inLink.size() - 1);
}
int DataCollect::setOutLink(Link* obj) {
   CHECK_ERROR_ABORT(SHOULD_NOT_REACH, "Error: Link ["+name+"] must have NO outgoing link !!!");
   return -1;
}
void DataCollect::genSetLinkPrms(ostream &fp, string obj)
{
//    fp<<BLOCK_SPACE << "(" << obj << "->" << prmName <<")." << "numInQue = " << inLink.size()<<";"<<endl;
}
/********************************************************************************/
Select::Select(string nm) {
    cType = cSelect;
    name = nm;
    linkIDName = name + string("LinkID");
    prmName = name + string("Prm");
    execPos = -1;
    procID = -1;
    pType = IPU1_0;
    mulInQue = false;
    mulOutQue = true;
}
Select::~Select() {
}
void Select::genIncludes(ostream &fp) {
    CHECK_ERROR_ABORT(inLink.size() == 1, "Error: Link ["+name+"] must have one incoming link !!!");
    CHECK_ERROR_ABORT(outLink.size() > 0, "Error: Link ["+name+"] must have atleast one outgoing link !!!");
    fp << "#include <include/link_api/selectLink.h>"<< endl;
}
void Select::genLinkID(ostream &fp) {
    //UInt32              DupLinkId;
    fp << BLOCK_SPACE << setw(IDTYPE_WIDTH) << left << "UInt32" << linkIDName << ";" << endl;
}
void Select::genCreatePrms(ostream &fp) {
    //DupLink_CreateParams                    ipuDupPrm;
    fp << BLOCK_SPACE << setw(TYPENAME_WIDTH) << left << "SelectLink_CreateParams"
            << prmName << ";" << endl;
}
void Select::genResetLinkPrms(ostream &fp, string obj) {
    fp << BLOCK_SPACE << "SelectLink_CreateParams_Init(&" << obj << "->"
            << prmName << ");" << endl;
}

int Select::setInLink(Link* obj) //returns QueueID
{
    CHECK_ERROR_ABORT(inLink.size() == 0, "Error: Link ["+name+"] must have one and only one incoming link !!!");
    inLink.push_back(make_pair(obj, -1));
    return (inLink.size() - 1);
}

int Select::setOutLink(Link* obj) //return QueueID
{
    outLink.push_back(make_pair(obj, -1));
    return (outLink.size() - 1);
}
void Select::genSetLinkPrms(ostream &fp, string obj)
{
    fp<<BLOCK_SPACE << "(" << obj << "->" << prmName <<")." << "numOutQue = " << outLink.size()<<";"<<endl;
}
/********************************************************************************/
DrmDisplay::DrmDisplay(string nm) {
    cType = cDrmDisplay;
    name = nm;
    linkIDName = name + string("LinkID");
    prmName = name + string("Prm");
    execPos = -1;
    procID = -1;
    pType = IPU1_0;
    mulInQue = true;
    mulOutQue = false;
}
DrmDisplay::~DrmDisplay() {
}
void DrmDisplay::genIncludes(ostream &fp) {
    CHECK_ERROR_ABORT(outLink.size() == 0, "Error: Link ["+name+"] must have NO outgoing link !!!");
    fp << "#include <include/link_api/drmDisplayLink.h>"<< endl;
}
void DrmDisplay::genLinkID(ostream &fp) {

    fp << BLOCK_SPACE << setw(IDTYPE_WIDTH) << left << "UInt32" << linkIDName << ";" << endl;
}
void DrmDisplay::genCreatePrms(ostream &fp) {

    fp << BLOCK_SPACE << setw(TYPENAME_WIDTH) << left << "DrmDisplayLink_CreateParams"
            << prmName << ";" << endl;
}
void DrmDisplay::genResetLinkPrms(ostream &fp, string obj) {
    fp << BLOCK_SPACE << "DrmDisplayLink_CreateParams_Init(&" << obj << "->"
            << prmName << ");" << endl;
}

int DrmDisplay::setInLink(Link* obj) //returns QueueID
{
    inLink.push_back(make_pair(obj, -1));
    return (inLink.size() - 1);
}

int DrmDisplay::setOutLink(Link* obj) //return QueueID
{
   CHECK_ERROR(SHOULD_NOT_REACH, "Error: Link ["+name+"] must have NO outgoing link !!!");
   return -1;
}
void DrmDisplay::genSetLinkPrms(ostream &fp, string obj)
{
    fp<<BLOCK_SPACE << "(" << obj << "->" << prmName <<")." << "numInQue = " << inLink.size()<<";"<<endl;
}
/********************************************************************************/
DispDistSrc::DispDistSrc(string nm) {
    cType = cDispDistSrc;
    name = nm;
    linkIDName = name + string("LinkID");
    prmName = name + string("Prm");
    execPos = -1;
    procID = -1;
    pType = A15;
    mulInQue = false;
    mulOutQue = false;
}
DispDistSrc::~DispDistSrc() {
}
void DispDistSrc::genIncludes(ostream &fp) {
    CHECK_ERROR_ABORT(inLink.size() == 0, "Error: Link ["+name+"] must have NO incoming link !!!");
    CHECK_ERROR_ABORT(outLink.size() == 1, "Error: Link ["+name+"] must have one outgoing link !!!");
    fp << "#include <include/link_api/dispDistSrcLink.h>"<< endl;
}
void DispDistSrc::genLinkID(ostream &fp) {

    fp << BLOCK_SPACE << setw(IDTYPE_WIDTH) << left << "UInt32" << linkIDName << ";" << endl;
}
void DispDistSrc::genCreatePrms(ostream &fp) {

    fp << BLOCK_SPACE << setw(TYPENAME_WIDTH) << left << "DispDistSrcLink_CreateParams"
            << prmName << ";" << endl;
}
void DispDistSrc::genResetLinkPrms(ostream &fp, string obj) {
    fp << BLOCK_SPACE << "DispDistSrcLink_CreateParams_Init(&" << obj << "->"
            << prmName << ");" << endl;
}

int DispDistSrc::setInLink(Link* obj) //returns QueueID
{
    CHECK_ERROR_ABORT(SHOULD_NOT_REACH, "Error: Link ["+name+"] should not have any incoming link !!!");
    return -1;
}

int DispDistSrc::setOutLink(Link* obj) //return QueueID
{
    CHECK_ERROR_ABORT(outLink.size() == 0, "Error: Link ["+name+"] must have one and only one outgoing link !!!");
    outLink.push_back(make_pair(obj, -1));
    return (outLink.size() - 1);
}
void DispDistSrc::genSetLinkPrms(ostream &fp, string obj)
{
}
/********************************************************************************/
SgxFrmcpy::SgxFrmcpy(string nm) {
    cType = cSgxFrmcpy;
    name = nm;
    linkIDName = name + string("LinkID");
    prmName = name + string("Prm");
    execPos = -1;
    procID = -1;
    pType = IPU1_0;
    mulInQue = false;
    mulOutQue = false;
}
SgxFrmcpy::~SgxFrmcpy() {
}
void SgxFrmcpy::genIncludes(ostream &fp) {
    CHECK_ERROR_ABORT(inLink.size() == 1, "Error: Link ["+name+"] must have only ONE incoming link !!!");
    CHECK_ERROR_ABORT(outLink.size() == 1, "Error: Link ["+name+"] must have only ONE outgoing link !!!");
    fp << "#include <include/link_api/sgxFrmcpyLink.h>"<< endl;
}
void SgxFrmcpy::genLinkID(ostream &fp) {

    fp << BLOCK_SPACE << setw(IDTYPE_WIDTH) << left << "UInt32" << linkIDName << ";" << endl;
}
void SgxFrmcpy::genCreatePrms(ostream &fp) {

    fp << BLOCK_SPACE << setw(40) << left << "SgxFrmcpyLink_CreateParams"
            << prmName << ";" << endl;
}
void SgxFrmcpy::genResetLinkPrms(ostream &fp, string obj) {
    fp << BLOCK_SPACE << "SgxFrmcpyLink_CreateParams_Init(&" << obj << "->"
            << prmName << ");" << endl;
}

int SgxFrmcpy::setInLink(Link* obj) //returns QueueID
{
    CHECK_ERROR(inLink.size() == 0, "Error: Link ["+name+"] should have only one incoming link !!!");
    inLink.push_back(make_pair(obj, -1));
    return (inLink.size() - 1);
}

int SgxFrmcpy::setOutLink(Link* obj) //return QueueID
{
    CHECK_ERROR(outLink.size() == 0, "Error: Link ["+name+"] should have only ONE outgoing link !!!");
    outLink.push_back(make_pair(obj, -1));
    return (outLink.size() - 1);
}

void SgxFrmcpy::genSetLinkPrms(ostream &fp, string obj)
{
}
/********************************************************************************/
Sgx3Dsrv::Sgx3Dsrv(string nm) {
    cType = cSgx3Dsrv;
    name = nm;
    linkIDName = name + string("LinkID");
    prmName = name + string("Prm");
    execPos = -1;
    procID = -1;
    pType = IPU1_0;
    mulInQue = true;
    mulOutQue = false;
}
Sgx3Dsrv::~Sgx3Dsrv() {
}
void Sgx3Dsrv::genIncludes(ostream &fp) {
    CHECK_ERROR_ABORT(inLink.size() > 3, "Error: Link ["+name+"] must have alteast 4 incoming link(s) !!!");
    CHECK_ERROR_ABORT(outLink.size() == 1, "Error: Link ["+name+"] must have ONE outgoing link !!!");
    fp << "#include <include/link_api/sgx3DsrvLink.h>"<< endl;
}
void Sgx3Dsrv::genLinkID(ostream &fp) {

    fp << BLOCK_SPACE << setw(IDTYPE_WIDTH) << left << "UInt32" << linkIDName << ";" << endl;
}
void Sgx3Dsrv::genCreatePrms(ostream &fp) {

    fp << BLOCK_SPACE << setw(TYPENAME_WIDTH) << left << "Sgx3DsrvLink_CreateParams"
            << prmName << ";" << endl;
}
void Sgx3Dsrv::genResetLinkPrms(ostream &fp, string obj) {
    fp << BLOCK_SPACE << "Sgx3DsrvLink_CreateParams_Init(&" << obj << "->"
            << prmName << ");" << endl;
}

int Sgx3Dsrv::setInLink(Link* obj) //returns QueueID
{
    CHECK_ERROR(inLink.size() < 5, "Error: Link ["+name+"] must have less than 5 incoming links !!!");
    inLink.push_back(make_pair(obj, -1));
    return (inLink.size() - 1);
}

int Sgx3Dsrv::setOutLink(Link* obj) //return QueueID
{
    CHECK_ERROR(outLink.size() == 0, "Error: Link ["+name+"] must have one outgoing link !!!");
    outLink.push_back(make_pair(obj, -1));
    return (outLink.size() - 1);
}
void Sgx3Dsrv::genSetLinkPrms(ostream &fp, string obj)
{
}
/********************************************************************************/
Sgx3Dsfm::Sgx3Dsfm(string nm) {
    cType = cSgx3Dsfm;
    name = nm;
    linkIDName = name + string("LinkID");
    prmName = name + string("Prm");
    execPos = -1;
    procID = -1;
    pType = IPU1_0;
    mulInQue = true;
    mulOutQue = false;
}
Sgx3Dsfm::~Sgx3Dsfm() {
}
void Sgx3Dsfm::genIncludes(ostream &fp) {
    CHECK_ERROR_ABORT(inLink.size() > 2, "Error: Link ["+name+"] must have alteast 3 incoming link(s) !!!");
    CHECK_ERROR_ABORT(outLink.size() == 1, "Error: Link ["+name+"] must have ONE outgoing link !!!");
    fp << "#include <include/link_api/sgx3DsfmLink.h>"<< endl;
}
void Sgx3Dsfm::genLinkID(ostream &fp) {

    fp << BLOCK_SPACE << setw(IDTYPE_WIDTH) << left << "UInt32" << linkIDName << ";" << endl;
}
void Sgx3Dsfm::genCreatePrms(ostream &fp) {

    fp << BLOCK_SPACE << setw(TYPENAME_WIDTH) << left << "Sgx3DsfmLink_CreateParams"
            << prmName << ";" << endl;
}
void Sgx3Dsfm::genResetLinkPrms(ostream &fp, string obj) {
    fp << BLOCK_SPACE << "Sgx3DsfmLink_CreateParams_Init(&" << obj << "->"
            << prmName << ");" << endl;
}

int Sgx3Dsfm::setInLink(Link* obj) //returns QueueID
{
    CHECK_ERROR(inLink.size() < 4, "Error: Link ["+name+"] must have less than 4 incoming links !!!");
    inLink.push_back(make_pair(obj, -1));
    return (inLink.size() - 1);
}

int Sgx3Dsfm::setOutLink(Link* obj) //return QueueID
{
    CHECK_ERROR(outLink.size() == 0, "Error: Link ["+name+"] must have one outgoing link !!!");
    outLink.push_back(make_pair(obj, -1));
    return (outLink.size() - 1);
}
void Sgx3Dsfm::genSetLinkPrms(ostream &fp, string obj)
{
}
/********************************************************************************/
SgxLink::SgxLink(string nm) {
    cType = cSgxLink;
    name = nm;
    linkIDName = name + string("LinkID");
    prmName = name + string("Prm");
    execPos = -1;
    procID = -1;
    pType = A15;
    mulInQue = true;
    mulOutQue = false;
}
SgxLink::~SgxLink() {
}
void SgxLink::genIncludes(ostream &fp) {
    CHECK_ERROR_ABORT(inLink.size() >= 1, "Error: Link ["+name+"] must have at least 1 incoming link !!!");
    CHECK_ERROR_ABORT(outLink.size() == 1, "Error: Link ["+name+"] must have exactly 1 outgoing link !!!");
    fp << "#include <link_api/sgxLink.h>" << endl;
}
void SgxLink::genLinkID(ostream &fp) {

    fp << BLOCK_SPACE << setw(IDTYPE_WIDTH) << left << "uint32_t" << linkIDName << ";" << endl;
}
void SgxLink::genCreatePrms(ostream &fp) {

    fp << BLOCK_SPACE << setw(TYPENAME_WIDTH) << left << "SgxLink_CreateParams"
            << prmName << ";" << endl;
}
void SgxLink::genResetLinkPrms(ostream &fp, string obj) {
    fp << BLOCK_SPACE << "SgxLink_CreateParams_Init(&" << obj << "->"
            << prmName << ");" << endl;
}
int SgxLink::setInLink(Link* obj) //returns QueueID
{
    CHECK_ERROR(inLink.size() < 5, "Error: Link ["+name+"] must have less than 5 incoming links !!!");
    inLink.push_back(make_pair(obj, -1));
    return (inLink.size() - 1);
}
int SgxLink::setOutLink(Link* obj) //return QueueID
{
    CHECK_ERROR(outLink.size() == 0, "Error: Link ["+name+"] must have one outgoing link !!!");
    outLink.push_back(make_pair(obj, -1));
    return (outLink.size() - 1);
}
void SgxLink::genSetLinkPrms(ostream &fp, string obj)
{
}
/********************************************************************************/
Sync::Sync(string nm) {
    cType = cSync;
    name = nm;
    linkIDName = name + string("LinkID");
    prmName = name + string("Prm");
    execPos = -1;
    procID = -1;
    pType = IPU1_0;
    mulInQue = false;
    mulOutQue = false;
}
Sync::~Sync() {
}
void Sync::genIncludes(ostream &fp) {
    CHECK_ERROR_ABORT(inLink.size() == 1, "Error: Link ["+name+"] must have one incoming link !!!");
    CHECK_ERROR_ABORT(outLink.size() == 1, "Error: Link ["+name+"] must have one outgoing link !!!");
    fp << "#include <include/link_api/syncLink.h>"<< endl;
}
void Sync::genLinkID(ostream &fp) {
    fp << BLOCK_SPACE << setw(IDTYPE_WIDTH) << left << "UInt32" << linkIDName << ";" << endl;
}
void Sync::genCreatePrms(ostream &fp) {
    fp << BLOCK_SPACE << setw(TYPENAME_WIDTH) << left << "SyncLink_CreateParams " << prmName << ";"
            << endl;
}
void Sync::genResetLinkPrms(ostream &fp, string obj) {
    fp << BLOCK_SPACE << "SyncLink_CreateParams_Init(&" << obj << "->"
            << prmName << ");" << endl;
}

int Sync::setInLink(Link* obj) {
    CHECK_ERROR(inLink.size() == 0, "Error: Link ["+name+"] must have one and only one incoming link !!!");
    inLink.push_back(make_pair(obj, -1));
    return (inLink.size() - 1);
}
int Sync::setOutLink(Link* obj) {
    CHECK_ERROR(outLink.size() == 0, "Error: Link ["+name+"] must have one and only one outgoing link !!!");
    outLink.push_back(make_pair(obj, -1));
    return (outLink.size() - 1);
}
void Sync::genSetLinkPrms(ostream &fp, string obj)
{
}

/********************************************************************************/
VPE::VPE(string nm) {
    cType = cVPE;
    name = nm;
    linkIDName = name + string("LinkID");
    prmName = name + string("Prm");
    matrixPos = -1;
    execPos = -1;
    procID = -1;
    pType = IPU1_0;
    mulInQue = false;
    mulOutQue = true;
}
VPE::~VPE() {
}
void VPE::genIncludes(ostream &fp) {
    CHECK_ERROR_ABORT(inLink.size() == 1, "Error: Link ["+name+"] must have one incoming link !!!");
    CHECK_ERROR_ABORT(outLink.size() == 1, "Error: Link ["+name+"] must have one outgoing link !!!");
    fp << "#include <include/link_api/vpeLink.h>"<< endl;
}
void VPE::genLinkID(ostream &fp) {
    fp << BLOCK_SPACE << setw(IDTYPE_WIDTH) << left << "UInt32" << linkIDName << ";" << endl;
}
void VPE::genCreatePrms(ostream &fp) {
    fp << BLOCK_SPACE << setw(TYPENAME_WIDTH) << left << "VpeLink_CreateParams " << prmName << ";"
            << endl;
}
void VPE::genResetLinkPrms(ostream &fp, string obj) {
    fp << BLOCK_SPACE << "VpeLink_CreateParams_Init(&" << obj << "->" << prmName
            << ");" << endl;
}

int VPE::setInLink(Link* obj) {
    CHECK_ERROR(inLink.size() == 0, "Error: Link ["+name+"] must have one and only one incoming link !!!");
    inLink.push_back(make_pair(obj, -1));
    return (inLink.size() - 1);
}
int VPE::setOutLink(Link* obj) {
    CHECK_ERROR(outLink.size() == 0, "Error: Link ["+name+"] must have one and only one outgoing link !!!");
    outLink.push_back(make_pair(obj, -1));
    return (outLink.size() - 1);
}
void VPE::genSetLinkPrms(ostream &fp, string obj)
{
}
/********************************************************************************/
DssM2mWb::DssM2mWb(string nm) {
    cType = cDssM2mWb;
    name = nm;
    linkIDName = name + string("LinkID");
    prmName = name + string("Prm");
    matrixPos = -1;
    execPos = -1;
    procID = -1;
    pType = IPU1_0;
    mulInQue = false;
    mulOutQue = false;
}
DssM2mWb::~DssM2mWb() {
}
void DssM2mWb::genIncludes(ostream &fp) {
    CHECK_ERROR_ABORT(inLink.size() == 1, "Error: Link ["+name+"] must have one incoming link !!!");
    CHECK_ERROR_ABORT(outLink.size() == 1, "Error: Link ["+name+"] must have one outgoing link !!!");
    fp << "#include <include/link_api/dssM2mWbLink.h>"<< endl;
}
void DssM2mWb::genLinkID(ostream &fp) {
    fp << BLOCK_SPACE << setw(IDTYPE_WIDTH) << left << "UInt32" << linkIDName << ";" << endl;
}
void DssM2mWb::genCreatePrms(ostream &fp) {
    fp << BLOCK_SPACE << setw(TYPENAME_WIDTH) << left << "DssM2mWbLink_CreateParams " << prmName << ";"
            << endl;
}
void DssM2mWb::genResetLinkPrms(ostream &fp, string obj) {
    fp << BLOCK_SPACE << "DssM2mWbLink_CreateParams_Init(&" << obj << "->" << prmName
            << ");" << endl;
}

int DssM2mWb::setInLink(Link* obj) {
    CHECK_ERROR(inLink.size() == 0, "Error: Link ["+name+"] must have one and only one incoming link !!!");
    inLink.push_back(make_pair(obj, -1));
    return (inLink.size() - 1);
}
int DssM2mWb::setOutLink(Link* obj) {
    CHECK_ERROR(outLink.size() == 0, "Error: Link ["+name+"] must have one and only one outgoing link !!!");
    outLink.push_back(make_pair(obj, -1));
    return (outLink.size() - 1);
}
void DssM2mWb::genSetLinkPrms(ostream &fp, string obj)
{
}
/********************************************************************************/
Hcf::Hcf(string nm) {
    cType = cHcf;
    name = nm;
    linkIDName = name + string("LinkID");
    prmName = name + string("Prm");
    matrixPos = -1;
    execPos = -1;
    procID = -1;
    pType = IPU1_0;
    mulInQue = false;
    mulOutQue = false;
}
Hcf::~Hcf() {
}
void Hcf::genIncludes(ostream &fp) {
    CHECK_ERROR_ABORT(inLink.size() == 1, "Error: Link ["+name+"] must have one incoming link !!!");
    CHECK_ERROR_ABORT(outLink.size() == 1, "Error: Link ["+name+"] must have one outgoing link !!!");
    fp << "#include <include/link_api/hcfLink.h>"<< endl;
}
void Hcf::genLinkID(ostream &fp) {
    fp << BLOCK_SPACE << setw(IDTYPE_WIDTH) << left << "UInt32" << linkIDName << ";" << endl;
}
void Hcf::genCreatePrms(ostream &fp) {
    fp << BLOCK_SPACE << setw(TYPENAME_WIDTH) << left << "HcfLink_CreateParams " << prmName << ";"
            << endl;
}
void Hcf::genResetLinkPrms(ostream &fp, string obj) {
    fp << BLOCK_SPACE << "HcfLink_CreateParams_Init(&" << obj << "->" << prmName
            << ");" << endl;
}

int Hcf::setInLink(Link* obj) {
    CHECK_ERROR(inLink.size() == 0, "Error: Link ["+name+"] must have one and only one incoming link !!!");
    inLink.push_back(make_pair(obj, -1));
    return (inLink.size() - 1);
}
int Hcf::setOutLink(Link* obj) {
    CHECK_ERROR(outLink.size() == 0, "Error: Link ["+name+"] must have one and only one outgoing link !!!");
    outLink.push_back(make_pair(obj, -1));
    return (outLink.size() - 1);
}
void Hcf::genSetLinkPrms(ostream &fp, string obj)
{
}


/********************************************************************************/
DefLink::DefLink(string nm) {
    cType = cDefLink;
    name = nm;
    linkIDName = name + string("LinkID");
    prmName = name + string("Prm");
    execPos = -1;
    procID = -1;
    pType = IPU1_0;
    mulInQue = false;
    mulOutQue = false;
}
DefLink::~DefLink() {
}
void DefLink::genIncludes(ostream &fp) {
    //fp << "#include <include/link_api/vpeLink.h>"<< endl;
}
void DefLink::genLinkID(ostream &fp) {
    fp << BLOCK_SPACE << setw(IDTYPE_WIDTH) << left << "UInt32" << linkIDName << ";" << endl;
}
void DefLink::genCreatePrms(ostream &fp) {
    CHECK_ERROR(SHOULD_NOT_REACH, "Warning: Manually edit the create parameters structure of Link [" + name + "] in header file !!!");
    fp<<BLOCK_SPACE<<setw(TYPENAME_WIDTH) << left<<"DefLink_CreateParams"<<prmName<<" //Warning: Change DefLink_CreateParams"<<endl;
}
void DefLink::genResetLinkPrms(ostream &fp, string obj) {
}

int DefLink::setInLink(Link* obj) {
    inLink.push_back(make_pair(obj, -1));
    if(inLink.size() > 1)
        mulInQue = true;
    return (inLink.size() - 1);
}
int DefLink::setOutLink(Link* obj) {
    outLink.push_back(make_pair(obj, -1));
    if(outLink.size() > 1)
        mulOutQue = true;
    return (outLink.size() - 1);
}
void DefLink::genSetLinkPrms(ostream &fp, string obj)
{
}
/********************************************************************************/
Alg_SubframeCopy::Alg_SubframeCopy(string nm) {
    cType = cAlg_SubframeCopy;
    name = nm;
    linkIDName = name + string("LinkID");
    prmName = name + string("Prm");
    execPos = -1;
    procID = -1;
    pType = IPU1_0;
    mulInQue = false;
    mulOutQue = false;
}

Alg_SubframeCopy::~Alg_SubframeCopy() {
}
void Alg_SubframeCopy::genIncludes(ostream &fp) {
    CHECK_ERROR_ABORT(inLink.size() == 1, "Error: Link ["+name+"] must have one incoming link !!!");
    CHECK_ERROR_ABORT(outLink.size() == 1, "Error: Link ["+name+"] must have one outgoing link !!!");

    fp << "#include <include/alglink_api/algorithmLink_subframeCopy.h>"<< endl;
}
void Alg_SubframeCopy::genLinkID(ostream &fp) {
    fp << BLOCK_SPACE << setw(IDTYPE_WIDTH) << left << "UInt32" << linkIDName << ";" << endl;
}
void Alg_SubframeCopy::genCreatePrms(ostream &fp) {
    fp << BLOCK_SPACE << setw(TYPENAME_WIDTH) << left\
            << "AlgorithmLink_SubframeCopyCreateParams " << name << "Prm" << ";" << endl;
}
void Alg_SubframeCopy::genResetLinkPrms(ostream &fp, string obj) {
    //fp << BLOCK_SPACE << "AlgorithmLink_SubframeCopy_initPlugin(&" << obj << "->"\
            << prmName << ");" << endl;
}
int Alg_SubframeCopy::setInLink(Link* obj) //returns QueueID
{
    CHECK_ERROR_ABORT(inLink.size() == 0, "Error: Link ["+name+"] must have one and only one incoming link !!!");
    inLink.push_back(make_pair(obj, -1));
    return (inLink.size() - 1);
}
int Alg_SubframeCopy::setOutLink(Link* obj) //return QueueID
{
    CHECK_ERROR_ABORT(outLink.size() == 0, "Error: Link ["+name+"] must have one and only one outgoing link !!!");
    outLink.push_back(make_pair(obj, -1));
    return (outLink.size() - 1);
}

void Alg_SubframeCopy::genSetLinkPrms(ostream &fp, string obj)
{
    fp<<BLOCK_SPACE << "(" << obj << "->" << prmName <<")." << "baseClassCreate.size  = sizeof(AlgorithmLink_SubframeCopyCreateParams);"<<endl;
    fp<<BLOCK_SPACE << "(" << obj << "->" << prmName <<")." << "baseClassCreate.algId  = ALGORITHM_LINK_EVE_ALG_SUBFRAMECOPY;"<<endl;
}
/********************************************************************************/
Alg_RemapMerge::Alg_RemapMerge(string nm) {
    cType = cAlg_RemapMerge;
    name = nm;
    linkIDName = name + string("LinkID");
    prmName = name + string("Prm");
    execPos = -1;
    procID = -1;
    pType = IPU1_0;
    mulInQue = false;
    mulOutQue = false;
}

Alg_RemapMerge::~Alg_RemapMerge() {
}
void Alg_RemapMerge::genIncludes(ostream &fp) {
    CHECK_ERROR_ABORT(inLink.size() == 1, "Error: Link ["+name+"] must have one incoming link !!!");
    CHECK_ERROR_ABORT(outLink.size() == 1, "Error: Link ["+name+"] must have one outgoing link !!!");
    fp << "#include <include/alglink_api/algorithmLink_remapMerge.h>"<< endl;
}
void Alg_RemapMerge::genLinkID(ostream &fp) {
    fp << BLOCK_SPACE << setw(IDTYPE_WIDTH) << left << "UInt32" << linkIDName << ";" << endl;
}
void Alg_RemapMerge::genCreatePrms(ostream &fp) {
    fp << BLOCK_SPACE << setw(TYPENAME_WIDTH) << left
            << "AlgorithmLink_RemapMergeCreateParams " << name << "Prm"
            << ";" << endl;
}
void Alg_RemapMerge::genResetLinkPrms(ostream &fp, string obj) {
    fp << BLOCK_SPACE << "AlgorithmLink_RemapMerge_Init(&" << obj << "->"\
            << prmName << ");" << endl;
}
int Alg_RemapMerge::setInLink(Link* obj) //returns QueueID
{
    CHECK_ERROR_ABORT(inLink.size() == 0, "Error: Link ["+name+"] must have one and only one incoming link !!!");
    inLink.push_back(make_pair(obj, -1));
    return (inLink.size() - 1);
}
int Alg_RemapMerge::setOutLink(Link* obj) //return QueueID
{
    CHECK_ERROR_ABORT(outLink.size() == 0, "Error: Link ["+name+"] must have one and only one outgoing link !!!");
    outLink.push_back(make_pair(obj, -1));
    return (outLink.size() - 1);
}
void Alg_RemapMerge::genSetLinkPrms(ostream &fp, string obj)
{
    fp<<BLOCK_SPACE << "(" << obj << "->" << prmName <<")." << "baseClassCreate.size  = sizeof(AlgorithmLink_RemapMergeCreateParams);"<<endl;
    if(pType == EVE1 || pType == EVE2  || pType == EVE3 || pType == EVE4)
        fp<<BLOCK_SPACE << "(" << obj << "->" << prmName <<")." << "baseClassCreate.algId  = ALGORITHM_LINK_EVE_ALG_REMAPMERGE;"<<endl;
}
/********************************************************************************/
Alg_StereoPostProcess::Alg_StereoPostProcess(string nm) {
    cType = cAlg_StereoPostProcess;
    name = nm;
    linkIDName = name + string("LinkID");
    prmName = name + string("Prm");
    execPos = -1;
    procID = -1;
    pType = IPU1_0;
    mulInQue = false;
    mulOutQue = true;
}

Alg_StereoPostProcess::~Alg_StereoPostProcess() {
}
void Alg_StereoPostProcess::genIncludes(ostream &fp) {
    CHECK_ERROR_ABORT(inLink.size() == 1, "Error: Link ["+name+"] must have one incoming link !!!");
    CHECK_ERROR_ABORT(outLink.size() == 1 || outLink.size() == 2, "Error: Link ["+name+"] must have one or two outgoing link !!!");

    fp << "#include <include/alglink_api/algorithmLink_stereoPostProcess.h>"<< endl;
}
void Alg_StereoPostProcess::genLinkID(ostream &fp) {
    fp << BLOCK_SPACE << setw(IDTYPE_WIDTH) << left << "UInt32" << linkIDName << ";" << endl;
}
void Alg_StereoPostProcess::genCreatePrms(ostream &fp) {
    fp << BLOCK_SPACE << setw(TYPENAME_WIDTH) << left\
            << "AlgorithmLink_StereoPostProcessCreateParams " << name << "Prm" << ";" << endl;
}
void Alg_StereoPostProcess::genResetLinkPrms(ostream &fp, string obj) {
    fp << BLOCK_SPACE << "AlgorithmLink_StereoPostProcess_Init(&" << obj << "->"\
            << prmName << ");" << endl;
}
int Alg_StereoPostProcess::setInLink(Link* obj) //returns QueueID
{
    CHECK_ERROR_ABORT(inLink.size() == 0, "Error: Link ["+name+"] must have one and only one incoming link !!!");
    inLink.push_back(make_pair(obj, -1));
    return (inLink.size() - 1);
}
int Alg_StereoPostProcess::setOutLink(Link* obj) //return QueueID
{
    CHECK_ERROR_ABORT(outLink.size() <= 1, "Error: Link ["+name+"] must have one or two outgoing link !!!");
    outLink.push_back(make_pair(obj, -1));
    return (outLink.size() - 1);
}

void Alg_StereoPostProcess::genSetLinkPrms(ostream &fp, string obj)
{
    fp<<BLOCK_SPACE << "(" << obj << "->" << prmName <<")." << "baseClassCreate.size  = sizeof(AlgorithmLink_StereoPostProcessCreateParams);"<<endl;
    if(pType == DSP1 || pType == DSP2)
        fp<<BLOCK_SPACE << "(" << obj << "->" << prmName <<")." << "baseClassCreate.algId  = ALGORITHM_LINK_DSP_ALG_STEREO_POST_PROCESS;"<<endl;
}
/********************************************************************************/
Alg_SceneObstructionDetect::Alg_SceneObstructionDetect(string nm) {
    cType = cAlg_SceneObstructionDetect;
    name = nm;
    linkIDName = name + string("LinkID");
    prmName = name + string("Prm");
    execPos = -1;
    procID = -1;
    pType = IPU1_0;
    mulInQue = false;
    mulOutQue = false;
}

Alg_SceneObstructionDetect::~Alg_SceneObstructionDetect() {
}
void Alg_SceneObstructionDetect::genIncludes(ostream &fp) {
    CHECK_ERROR_ABORT(inLink.size() == 1, "Error: Link ["+name+"] must have one incoming link !!!");
    CHECK_ERROR_ABORT(outLink.size() == 1, "Error: Link ["+name+"] must have one outgoing link !!!");

    fp << "#include <include/alglink_api/algorithmLink_sceneObstructionDetect.h>"<< endl;
}
void Alg_SceneObstructionDetect::genLinkID(ostream &fp) {
    fp << BLOCK_SPACE << setw(IDTYPE_WIDTH) << left << "UInt32" << linkIDName << ";" << endl;
}
void Alg_SceneObstructionDetect::genCreatePrms(ostream &fp) {
    fp << BLOCK_SPACE << setw(TYPENAME_WIDTH) << left\
            << "AlgorithmLink_SceneObstructionDetectCreateParams " << name << "Prm" << ";" << endl;
}
void Alg_SceneObstructionDetect::genResetLinkPrms(ostream &fp, string obj) {
    fp << BLOCK_SPACE << "AlgorithmLink_SceneObstructionDetect_Init(&" << obj << "->"\
            << prmName << ");" << endl;
}
int Alg_SceneObstructionDetect::setInLink(Link* obj) //returns QueueID
{
    CHECK_ERROR_ABORT(inLink.size() == 0, "Error: Link ["+name+"] must have one and only one incoming link !!!");
    inLink.push_back(make_pair(obj, -1));
    return (inLink.size() - 1);
}
int Alg_SceneObstructionDetect::setOutLink(Link* obj) //return QueueID
{
    CHECK_ERROR_ABORT(outLink.size() == 0, "Error: Link ["+name+"] must have one and only one outgoing link !!!");
    outLink.push_back(make_pair(obj, -1));
    return (outLink.size() - 1);
}

void Alg_SceneObstructionDetect::genSetLinkPrms(ostream &fp, string obj)
{
    fp<<BLOCK_SPACE << "(" << obj << "->" << prmName <<")." << "baseClassCreate.size  = sizeof(AlgorithmLink_SceneObstructionDetectCreateParams);"<<endl;
    if(pType == DSP1 || pType == DSP2)
        fp<<BLOCK_SPACE << "(" << obj << "->" << prmName <<")." << "baseClassCreate.algId  = ALGORITHM_LINK_DSP_ALG_SCENE_OBSTRUCTION_DETECT;"<<endl;
       if(pType == IPU1_0 || pType == IPU1_1)
        fp<<BLOCK_SPACE << "(" << obj << "->" << prmName <<")." << "baseClassCreate.algId  = ALGORITHM_LINK_IPU_ALG_SCENE_OBSTRUCTION_DETECT;"<<endl;
}

/********************************************************************************/
Alg_AutoChartDetect::Alg_AutoChartDetect(string nm) {
    cType = cAlg_AutoChartDetect;
    name = nm;
    linkIDName = name + string("LinkID");
    prmName = name + string("Prm");
    execPos = -1;
    procID = -1;
    pType = IPU1_0;
    mulInQue = true;
    mulOutQue = true;
}

Alg_AutoChartDetect::~Alg_AutoChartDetect() {
}
void Alg_AutoChartDetect::genIncludes(ostream &fp) {
    CHECK_ERROR_ABORT(inLink.size() >= 1, "Error: Link ["+name+"] must have one incoming link !!!");
    CHECK_ERROR_ABORT(outLink.size() == 1, "Error: Link ["+name+"] must have one outgoing link !!!");

    fp << "#include <include/alglink_api/algorithmLink_autoChartDetect.h>"<< endl;
}
void Alg_AutoChartDetect::genLinkID(ostream &fp) {
    fp << BLOCK_SPACE << setw(IDTYPE_WIDTH) << left << "UInt32" << linkIDName << ";" << endl;
}
void Alg_AutoChartDetect::genCreatePrms(ostream &fp) {
    fp << BLOCK_SPACE << setw(TYPENAME_WIDTH) << left
            << "AlgorithmLink_ACDetectCreateParams " << name << "Prm" << ";"
            << endl;
}
void Alg_AutoChartDetect::genResetLinkPrms(ostream &fp, string obj) {
}
int Alg_AutoChartDetect::setInLink(Link* obj) //returns QueueID
{
    inLink.push_back(make_pair(obj, -1));
    return (inLink.size() - 1);
}
int Alg_AutoChartDetect::setOutLink(Link* obj) //return QueueID
{
    outLink.push_back(make_pair(obj, -1));
    return (outLink.size() - 1);
}
void Alg_AutoChartDetect::genSetLinkPrms(ostream &fp, string obj)
{
    fp<<BLOCK_SPACE << "(" << obj << "->" << prmName <<")." << "baseClassCreate.size  = sizeof(AlgorithmLink_ACDetectCreateParams);"<<endl;
    if(pType == DSP1 || pType == DSP2)
        fp<<BLOCK_SPACE << "(" << obj << "->" << prmName <<")." << "baseClassCreate.algId  = ALGORITHM_LINK_DSP_ALG_AUTO_CHART_DETECT;"<<endl;
}
/********************************************************************************/
Alg_PoseEstimate::Alg_PoseEstimate(string nm) {
    cType = cAlg_PoseEstimate;
    name = nm;
    linkIDName = name + string("LinkID");
    prmName = name + string("Prm");
    execPos = -1;
    procID = -1;
    pType = IPU1_0;
    mulInQue = true;
    mulOutQue = true;
}

Alg_PoseEstimate::~Alg_PoseEstimate() {
}
void Alg_PoseEstimate::genIncludes(ostream &fp) {
    CHECK_ERROR_ABORT(inLink.size() >= 1, "Error: Link ["+name+"] must have one incoming link !!!");
    CHECK_ERROR_ABORT(outLink.size() == 1, "Error: Link ["+name+"] must have one outgoing link !!!");

    fp << "#include <include/alglink_api/algorithmLink_poseEstimate.h>"<< endl;
}
void Alg_PoseEstimate::genLinkID(ostream &fp) {
    fp << BLOCK_SPACE << setw(IDTYPE_WIDTH) << left << "UInt32" << linkIDName << ";" << endl;
}
void Alg_PoseEstimate::genCreatePrms(ostream &fp) {
    fp << BLOCK_SPACE << setw(TYPENAME_WIDTH) << left
            << "AlgorithmLink_PEstimateCreateParams " << name << "Prm" << ";"
            << endl;
}
void Alg_PoseEstimate::genResetLinkPrms(ostream &fp, string obj) {
}
int Alg_PoseEstimate::setInLink(Link* obj) //returns QueueID
{
    inLink.push_back(make_pair(obj, -1));
    return (inLink.size() - 1);
}
int Alg_PoseEstimate::setOutLink(Link* obj) //return QueueID
{
    outLink.push_back(make_pair(obj, -1));
    return (outLink.size() - 1);
}
void Alg_PoseEstimate::genSetLinkPrms(ostream &fp, string obj)
{
    fp<<BLOCK_SPACE << "(" << obj << "->" << prmName <<")." << "baseClassCreate.size  = sizeof(AlgorithmLink_PEstimateCreateParams);"<<endl;
    if(pType == DSP1 || pType == DSP2)
        fp<<BLOCK_SPACE << "(" << obj << "->" << prmName <<")." << "baseClassCreate.algId  = ALGORITHM_LINK_DSP_ALG_POSE_ESTIMATE;"<<endl;
}

/********************************************************************************/
Alg_AutoRemap::Alg_AutoRemap(string nm) {
    cType = cAlg_AutoRemap;
    name = nm;
    linkIDName = name + string("LinkID");
    prmName = name + string("Prm");
    execPos = -1;
    procID = -1;
    pType = DSP1;
    mulInQue = false;
    mulOutQue = false;
}

Alg_AutoRemap::~Alg_AutoRemap() {
}
void Alg_AutoRemap::genIncludes(ostream &fp) {
    CHECK_ERROR_ABORT(inLink.size() == 1, "Error: Link ["+name+"] must have one incoming link !!!");
    CHECK_ERROR_ABORT(outLink.size() == 0, "Error: Link ["+name+"] must have no outgoing link !!!");

    fp << "#include <include/alglink_api/algorithmLink_autoRemap.h>"<< endl;
}
void Alg_AutoRemap::genLinkID(ostream &fp) {
    fp << BLOCK_SPACE << setw(IDTYPE_WIDTH) << left << "UInt32" << linkIDName << ";" << endl;
}
void Alg_AutoRemap::genCreatePrms(ostream &fp) {
    fp << BLOCK_SPACE << setw(TYPENAME_WIDTH) << left
            << "AlgorithmLink_AutoRemapCreateParams " << name << "Prm" << ";"
            << endl;
}
void Alg_AutoRemap::genResetLinkPrms(ostream &fp, string obj) {
    fp << BLOCK_SPACE << "AlgorithmLink_AutoRemap_Init(&" << obj << "->"\
            << prmName << ");" << endl;
}
int Alg_AutoRemap::setInLink(Link* obj) //returns QueueID
{
    inLink.push_back(make_pair(obj, -1));
    return (inLink.size() - 1);
}
int Alg_AutoRemap::setOutLink(Link* obj) //return QueueID
{
    outLink.push_back(make_pair(obj, -1));
    return (outLink.size() - 1);
}
void Alg_AutoRemap::genSetLinkPrms(ostream &fp, string obj)
{
    fp<<BLOCK_SPACE << "(" << obj << "->" << prmName <<")." << "baseClassCreate.size  = sizeof(AlgorithmLink_AutoRemapCreateParams);"<<endl;
    if(pType == DSP1 || pType == DSP2)
        fp<<BLOCK_SPACE << "(" << obj << "->" << prmName <<")." << "baseClassCreate.algId  = ALGORITHM_LINK_DSP_ALG_AUTOREMAP;"<<endl;
}

/********************************************************************************/
Alg_SeamDetection::Alg_SeamDetection(string nm) {
    cType = cAlg_SeamDetection;
    name = nm;
    linkIDName = name + string("LinkID");
    prmName = name + string("Prm");
    execPos = -1;
    procID = -1;
    pType = DSP1;
    mulInQue = true;
    mulOutQue = true;
}

Alg_SeamDetection::~Alg_SeamDetection() {
}
void Alg_SeamDetection::genIncludes(ostream &fp) {
    CHECK_ERROR_ABORT(inLink.size() == 1, "Error: Link ["+name+"] must have one incoming link !!!");
    CHECK_ERROR_ABORT(outLink.size() == 1, "Error: Link ["+name+"] must have one outgoing link !!!");

    fp << "#include <include/alglink_api/algorithmLink_seamDetection.h>"<< endl;
}
void Alg_SeamDetection::genLinkID(ostream &fp) {
    fp << BLOCK_SPACE << setw(IDTYPE_WIDTH) << left << "UInt32" << linkIDName << ";" << endl;
}
void Alg_SeamDetection::genCreatePrms(ostream &fp) {
    fp << BLOCK_SPACE << setw(TYPENAME_WIDTH) << left
            << "AlgorithmLink_SeamDetectionCreateParams " << name << "Prm" << ";"
            << endl;
}
void Alg_SeamDetection::genResetLinkPrms(ostream &fp, string obj) {
}
int Alg_SeamDetection::setInLink(Link* obj) //returns QueueID
{
    inLink.push_back(make_pair(obj, -1));
    return (inLink.size() - 1);
}
int Alg_SeamDetection::setOutLink(Link* obj) //return QueueID
{
    outLink.push_back(make_pair(obj, -1));
    return (outLink.size() - 1);
}
void Alg_SeamDetection::genSetLinkPrms(ostream &fp, string obj)
{
    fp<<BLOCK_SPACE << "(" << obj << "->" << prmName <<")." << "baseClassCreate.size  = sizeof(AlgorithmLink_SeamDetectionCreateParams);"<<endl;
    if(pType == DSP1 || pType == DSP2)
        fp<<BLOCK_SPACE << "(" << obj << "->" << prmName <<")." << "baseClassCreate.algId  = ALGORITHM_LINK_DSP_ALG_SEAMDETECTION;"<<endl;
}

/********************************************************************************/
Alg_Stitching::Alg_Stitching(string nm) {
    cType = cAlg_Stitching;
    name = nm;
    linkIDName = name + string("LinkID");
    prmName = name + string("Prm");
    execPos = -1;
    procID = -1;
    pType = DSP1;
    mulInQue = true;
    mulOutQue = true;
}

Alg_Stitching::~Alg_Stitching() {
}
void Alg_Stitching::genIncludes(ostream &fp) {
    CHECK_ERROR_ABORT(inLink.size() == 2, "Error: Link ["+name+"] must have two incoming links !!!");
    CHECK_ERROR_ABORT(outLink.size() == 1, "Error: Link ["+name+"] must have one outgoing link !!!");

    fp << "#include <include/alglink_api/algorithmLink_stitching.h>"<< endl;
}
void Alg_Stitching::genLinkID(ostream &fp) {
    fp << BLOCK_SPACE << setw(IDTYPE_WIDTH) << left << "UInt32" << linkIDName << ";" << endl;
}
void Alg_Stitching::genCreatePrms(ostream &fp) {
    fp << BLOCK_SPACE << setw(TYPENAME_WIDTH) << left
            << "AlgorithmLink_StitchingCreateParams " << name << "Prm" << ";"
            << endl;
}
void Alg_Stitching::genResetLinkPrms(ostream &fp, string obj) {
}
int Alg_Stitching::setInLink(Link* obj) //returns QueueID
{
    inLink.push_back(make_pair(obj, -1));
    return (inLink.size() - 1);
}
int Alg_Stitching::setOutLink(Link* obj) //return QueueID
{
    outLink.push_back(make_pair(obj, -1));
    return (outLink.size() - 1);
}
void Alg_Stitching::genSetLinkPrms(ostream &fp, string obj)
{
    fp<<BLOCK_SPACE << "(" << obj << "->" << prmName <<")." << "baseClassCreate.size  = sizeof(AlgorithmLink_StitchingCreateParams);"<<endl;
    if(pType == DSP1 || pType == DSP2)
        fp<<BLOCK_SPACE << "(" << obj << "->" << prmName <<")." << "baseClassCreate.algId  = ALGORITHM_LINK_DSP_ALG_STITCHING;"<<endl;
}

/********************************************************************************/
Alg_AdaptiveBowl::Alg_AdaptiveBowl(string nm) {
    cType = cAlg_Stitching;
    name = nm;
    linkIDName = name + string("LinkID");
    prmName = name + string("Prm");
    execPos = -1;
    procID = -1;
    pType = DSP1;
    mulInQue = true;
    mulOutQue = true;
}

Alg_AdaptiveBowl::~Alg_AdaptiveBowl() {
}
void Alg_AdaptiveBowl::genIncludes(ostream &fp) {
    CHECK_ERROR_ABORT(outLink.size() == 1, "Error: Link ["+name+"] must have one outgoing link !!!");

    fp << "#include <include/alglink_api/algorithmLink_adaptiveBowl.h>"<< endl;
}
void Alg_AdaptiveBowl::genLinkID(ostream &fp) {
    fp << BLOCK_SPACE << setw(IDTYPE_WIDTH) << left << "UInt32" << linkIDName << ";" << endl;
}
void Alg_AdaptiveBowl::genCreatePrms(ostream &fp) {
    fp << BLOCK_SPACE << setw(TYPENAME_WIDTH) << left
            << "AlgorithmLink_AdaptiveBowlCreateParams " << name << "Prm" << ";"
            << endl;
}
void Alg_AdaptiveBowl::genResetLinkPrms(ostream &fp, string obj) {
}
int Alg_AdaptiveBowl::setInLink(Link* obj) //returns QueueID
{
    inLink.push_back(make_pair(obj, -1));
    return (inLink.size() - 1);
}
int Alg_AdaptiveBowl::setOutLink(Link* obj) //return QueueID
{
    outLink.push_back(make_pair(obj, -1));
    return (outLink.size() - 1);
}
void Alg_AdaptiveBowl::genSetLinkPrms(ostream &fp, string obj)
{
    fp<<BLOCK_SPACE << "(" << obj << "->" << prmName <<")." << "baseClassCreate.size  = sizeof(AlgorithmLink_AdaptiveBowlCreateParams);"<<endl;
    if(pType == DSP1 || pType == DSP2)
        fp<<BLOCK_SPACE << "(" << obj << "->" << prmName <<")." << "baseClassCreate.algId  = ALGORITHM_LINK_DSP_ALG_ADAPTIVEBOWL;"<<endl;
}

/********************************************************************************/
EpLink::EpLink(string nm) {
    cType = cEpLink;
    name = nm;
    linkIDName = name + string("LinkID");
    prmName = name + string("Prm");
    execPos = -1;
    procID = -1;
    pType = A15;
    mulInQue = false;
    mulOutQue = false;
}

EpLink::~EpLink() {
}
void EpLink::genIncludes(ostream &fp) {
    fp << "#include <include/link_api/epLink.h>"<< endl;
}
void EpLink::genLinkID(ostream &fp) {
    fp << BLOCK_SPACE << setw(IDTYPE_WIDTH) << left << "UInt32" << linkIDName << ";" << endl;
}
void EpLink::genCreatePrms(ostream &fp) {
    fp << BLOCK_SPACE << setw(TYPENAME_WIDTH) << left << "EpLink_CreateParams"
            << prmName << ";" << endl;
}
void EpLink::genResetLinkPrms(ostream &fp, string obj) {
}
int EpLink::setInLink(Link* obj) {
    string root = getRoot(name);

    if (root == "EpSink") {
        CHECK_ERROR_ABORT(inLink.size() != 1, "Error: Link ["+name+"] must have one and only one incoming link !!!");
    } else if (root == "EpSource") {
        CHECK_ERROR_ABORT(inLink.size() != 0, "Error: Link ["+name+"] must have NO incoming link !!!");
    }
    inLink.push_back(make_pair(obj, -1));
    return (inLink.size() - 1);
}
int EpLink::setOutLink(Link* obj) {
    string root = getRoot(name);

    if (root == "EpSink") {
        CHECK_ERROR_ABORT(outLink.size() > 0, "Error: Link ["+name+"] must have NO outgoing link !!!");
    } else if (root == "EpSource") {
        CHECK_ERROR_ABORT(outLink.size() != 1, "Error: Link ["+name+"] must have one and only outgoing link !!!");
    }
    outLink.push_back(make_pair(obj, -1));
    return (outLink.size() - 1);
}
void EpLink::genSetLinkPrms(ostream &fp, string obj)
{
}
/********************************************************************************/
Alg_OpenCVCanny::Alg_OpenCVCanny(string nm) {
    cType = cAlg_OpenCVCanny;
    name = nm;
    linkIDName = name + string("LinkID");
    prmName = name + string("Prm");
    execPos = -1;
    procID = -1;
    pType = A15;
    mulInQue = false;
    mulOutQue = false;
}

Alg_OpenCVCanny::~Alg_OpenCVCanny() {
}

void Alg_OpenCVCanny::genIncludes(ostream &fp) {
    fp << "#include <include/alglink_api/algorithmLink_opencvcanny.h>" << endl;
}

void Alg_OpenCVCanny::genLinkID(ostream &fp) {
    fp << BLOCK_SPACE << setw(10) << left << "UInt32" << linkIDName << ";" << endl;
}

void Alg_OpenCVCanny::genCreatePrms(ostream &fp) {
    fp << BLOCK_SPACE << setw(40) << left << "Alg_OpenCVCanny_CreateParams"
            << prmName << ";" << endl;
}

void Alg_OpenCVCanny::genResetLinkPrms(ostream &fp, string obj) {

}

int Alg_OpenCVCanny::setInLink(Link* obj) //returns QueueID
{
    CHECK_ERROR_ABORT(inLink.size() == 0, "Error: Link ["+name+"] must have one and only one incoming link !!!");
    inLink.push_back(make_pair(obj, -1));
    return (inLink.size() - 1);
}
int Alg_OpenCVCanny::setOutLink(Link* obj) //return QueueID
{
    CHECK_ERROR_ABORT(outLink.size() == 0, "Error: Link ["+name+"] must have one and only one outgoing link !!!");
    outLink.push_back(make_pair(obj, -1));
    return (outLink.size() - 1);
}

void Alg_OpenCVCanny::genSetLinkPrms(ostream &fp, string obj)
{
    fp<<BLOCK_SPACE << "(" << obj << "->" << prmName <<")." << "baseClassCreate.size  = sizeof(AlgorithmLink_OpenCVCannyCreateParams);"<<endl;
    fp<<BLOCK_SPACE << "(" << obj << "->" << prmName <<")." << "baseClassCreate.algId  = ALGORITHM_LINK_A15_ALG_OPENCVCANNY;"<<endl;
}

/********************************************************************************/
LidarCapture::LidarCapture(string nm)
{
    cType = cLidarCapture;
    name = nm;
    linkIDName = name + string("LinkID");
    prmName = name + string("Prm");
    execPos = -1;
    procID = -1;
    pType = A15;
    mulInQue = false;
    mulOutQue = false;
}

LidarCapture::~LidarCapture() {}

void LidarCapture::genIncludes(ostream& fp)
{
    CHECK_ERROR_ABORT(inLink.size() == 0, "Error: Link ["+name+"] must have NO incoming links !!!");
    CHECK_ERROR_ABORT(outLink.size() == 1, "Error: Link ["+name+"] must have ONE outgoing link !!!");
    fp << "#include <link_api/lidarCapture.h>" << endl;
}
void LidarCapture::genLinkID(ostream& fp)
{
    fp << BLOCK_SPACE << setw(IDTYPE_WIDTH) << left << "uint32_t" << linkIDName << ";" << endl;
}
void LidarCapture::genCreatePrms(ostream& fp)
{
    fp << BLOCK_SPACE << setw(TYPENAME_WIDTH) << left << "LidarCaptureLink_CreateParams"
        << prmName << ";" << endl;
}
void LidarCapture::genResetLinkPrms(ostream& fp, string obj)
{
    fp << BLOCK_SPACE << "LidarCaptureLink_CreateParams_Init(&" << obj << "->" << prmName << ");"
        << endl;
}
int LidarCapture::setInLink(Link* obj)
{
    CHECK_ERROR_ABORT(SHOULD_NOT_REACH, "Error: Link ["+name+"] should not have any incoming link !!!");
    return -1;
}
int LidarCapture::setOutLink(Link* obj)
{
    CHECK_ERROR(outLink.size() == 0, "Error: Link ["+name+"] should have ONE outgoing link !!!");
    outLink.push_back(make_pair(obj, -1));
    return outLink.size() - 1;
}
void LidarCapture::genSetLinkPrms(ostream& fp, string obj) {}
/********************************************************************************/
LidarCloud::LidarCloud(string nm)
{
    cType = cLidarCloud;
    name = nm;
    linkIDName = name + string("LinkID");
    prmName = name + string("Prm");
    execPos = -1;
    procID = -1;
    pType = A15;
    mulInQue = false;
    mulOutQue = false;
}
LidarCloud::~LidarCloud() {}
void LidarCloud::genIncludes(ostream& fp)
{
    CHECK_ERROR_ABORT(inLink.size() == 1, "Error: Link ["+name+"] must have ONE incoming link !!!");
    CHECK_ERROR_ABORT(outLink.size() == 1, "Error: Link ["+name+"] must have ONE outgoing link !!!");
    fp << "#include <link_api/lidarCloud.h>" << endl;
}
void LidarCloud::genLinkID(ostream& fp)
{
    fp << BLOCK_SPACE << setw(IDTYPE_WIDTH) << left << "uint32_t" << linkIDName << ";" << endl;
}
void LidarCloud::genCreatePrms(ostream& fp)
{
    fp << BLOCK_SPACE << setw(TYPENAME_WIDTH) << left << "LidarCloudLink_CreateParams"
        << prmName << ";" << endl;
}
void LidarCloud::genResetLinkPrms(ostream& fp, string obj)
{
    fp << BLOCK_SPACE << "LidarCloudLink_CreateParams_Init(&" << obj << "->" << prmName << ");"
        << endl;
}
int LidarCloud::setInLink(Link* obj)
{
    CHECK_ERROR(inLink.size() == 0, "Error: Link ["+name+"] should have ONE incoming link !!!");
    inLink.push_back(make_pair(obj, -1));
    return inLink.size() - 1;
}
int LidarCloud::setOutLink(Link* obj)
{
    CHECK_ERROR(outLink.size() == 0, "Error: Link ["+name+"] should have ONE outgoing link !!!");
    outLink.push_back(make_pair(obj, -1));
    return outLink.size() - 1;
}
void LidarCloud::genSetLinkPrms(ostream& fp, string obj) {}
/********************************************************************************/
LidarCloudXForm::LidarCloudXForm(string nm)
{
    cType = cLidarCloudXForm;
    name = nm;
    linkIDName = name + string("LinkID");
    prmName = name + string("Prm");
    execPos = -1;
    procID = -1;
    pType = A15;
    mulInQue = false;
    mulOutQue = false;
}
LidarCloudXForm::~LidarCloudXForm() {}
void LidarCloudXForm::genIncludes(ostream& fp)
{
    CHECK_ERROR_ABORT(inLink.size() == 1, "Error: Link ["+name+"] must have ONE incoming link !!!");
    CHECK_ERROR_ABORT(outLink.size() == 1, "Error: Link ["+name+"] must have ONE outgoing link !!!");
    fp << "#include <link_api/lidarCloudTransform.h>" << endl;
}
void LidarCloudXForm::genLinkID(ostream& fp)
{
    fp << BLOCK_SPACE << setw(IDTYPE_WIDTH) << left << "uint32_t" << linkIDName << ";" << endl;
}
void LidarCloudXForm::genCreatePrms(ostream& fp)
{
    fp << BLOCK_SPACE << setw(TYPENAME_WIDTH) << left << "LidarCloudTransformLink_CreateParams"
        << prmName << ";" << endl;
}
void LidarCloudXForm::genResetLinkPrms(ostream& fp, string obj)
{
    fp << BLOCK_SPACE << "LidarCloudTransformLink_CreateParams_Init(&" << obj << "->" << prmName << ");"
        << endl;
}
int LidarCloudXForm::setInLink(Link* obj)
{
    CHECK_ERROR(inLink.size() == 0, "Error: Link ["+name+"] should have ONE incoming link !!!");
    inLink.push_back(make_pair(obj, -1));
    return inLink.size() - 1;
}
int LidarCloudXForm::setOutLink(Link* obj)
{
    CHECK_ERROR(outLink.size() == 0, "Error: Link ["+name+"] should have ONE outgoing link !!!");
    outLink.push_back(make_pair(obj, -1));
    return outLink.size() - 1;
}
void LidarCloudXForm::genSetLinkPrms(ostream& fp, string obj) {}
/********************************************************************************/
LidarGPCLink::LidarGPCLink(string nm)
{
    cType = cLidarGPCLink;
    pType = DSP1;
    name = nm;
    linkIDName = name + string("LinkID");
    prmName = name + string("Prm");
}
LidarGPCLink::~LidarGPCLink() {}
void LidarGPCLink::genIncludes(ostream& fp)
{
    CHECK_ERROR_ABORT(inLink.size() == 1, "Error: Link ["+name+"] must have ONE incoming link !!!");
    CHECK_ERROR_ABORT(outLink.size() == 1, "Error: Link ["+name+"] must have ONE outgoing link !!!");
    fp << "#include <link_api/lidar/lidarGPCLink.h>" << endl;
}
void LidarGPCLink::genLinkID(ostream& fp)
{
    fp << BLOCK_SPACE << setw(IDTYPE_WIDTH) << left << "uint32_t" << linkIDName << ";" << endl;
}
void LidarGPCLink::genCreatePrms(ostream& fp)
{
    fp << BLOCK_SPACE << setw(TYPENAME_WIDTH) << left << "LidarGPCLink_CreateParams"
        << prmName << ";" << endl;
}
void LidarGPCLink::genResetLinkPrms(ostream& fp, string obj)
{
    fp << BLOCK_SPACE << "LidarGPCLink_CreateParams_Init(&" << obj << "->" << prmName << ");"
        << endl;
}
int LidarGPCLink::setInLink(Link* obj)
{
    CHECK_ERROR(inLink.size() == 0, "Error: Link ["+name+"] should have ONE incoming link !!!");
    inLink.push_back(make_pair(obj, -1));
    return inLink.size() - 1;
}
int LidarGPCLink::setOutLink(Link* obj)
{
    CHECK_ERROR(outLink.size() == 0, "Error: Link ["+name+"] should have ONE outgoing link !!!");
    outLink.push_back(make_pair(obj, -1));
    return outLink.size() - 1;
}
void LidarGPCLink::genSetLinkPrms(ostream& fp, string obj) {}
/********************************************************************************/
ImuLink::ImuLink(string nm)
{
    cType = cImuLink;
    name = nm;
    linkIDName = name + string("LinkID");
    prmName = name + string("Prm");
    execPos = -1;
    procID = -1;
    pType = A15;
    mulInQue = false;
    mulOutQue = false;
}
ImuLink::~ImuLink() {}
void ImuLink::genIncludes(ostream& fp)
{
    CHECK_ERROR_ABORT(inLink.size() == 0, "Error: Link ["+name+"] must have NO incoming links !!!");
    CHECK_ERROR_ABORT(outLink.size() <= 1, "Error: Link ["+name+"] must have AT MOST ONE outgoing link !!!");
    fp << "#include <link_api/imuLink.h>" << endl;
}
void ImuLink::genLinkID(ostream& fp)
{
    fp << BLOCK_SPACE << setw(IDTYPE_WIDTH) << left << "uint32_t" << linkIDName << ";" << endl;
}
void ImuLink::genCreatePrms(ostream& fp)
{
    fp << BLOCK_SPACE << setw(TYPENAME_WIDTH) << left << "ImuLink_CreateParams"
       << prmName << ";" << endl;
}
void ImuLink::genResetLinkPrms(ostream& fp, string obj)
{
    fp << BLOCK_SPACE << "ImuLink_CreateParams_Init(&" << obj << "->" << prmName << ");" << endl;
}
int ImuLink::setInLink(Link* obj)
{
    CHECK_ERROR(SHOULD_NOT_REACH, "Error: Link ["+name+"] should have NO incoming links !!!");
    return 0;
}
int ImuLink::setOutLink(Link* obj)
{
    CHECK_ERROR(outLink.size() < 1, "Error: Link ["+name+"] should have only one outgoing link !!!");
    outLink.push_back(make_pair(obj, -1));
    return outLink.size() - 1;
}
void ImuLink::genSetLinkPrms(ostream& fp, string obj) {}
/********************************************************************************/
DumpLink::DumpLink(string nm)
{
    cType = cDumpLink;
    name = nm;
    linkIDName = name + string("LinkID");
    prmName = name + string("Prm");
    execPos = -1;
    procID = -1;
    pType = A15;
    mulInQue = false;
    mulOutQue = false;
}
DumpLink::~DumpLink() {}
void DumpLink::genIncludes(ostream& fp)
{
    CHECK_ERROR_ABORT(inLink.size() == 1, "Error: Link ["+name+"] must have ONE incoming link !!!");
    CHECK_ERROR_ABORT(outLink.size() == 1, "Error: Link ["+name+"] must have ONE outgoing link !!!");
    fp << "#include <link_api/dumpLink.h>" << endl;
}
void DumpLink::genLinkID(ostream& fp)
{
    fp << BLOCK_SPACE << setw(IDTYPE_WIDTH) << left << "uint32_t" << linkIDName << ";" << endl;
}
void DumpLink::genCreatePrms(ostream& fp)
{
    fp << BLOCK_SPACE << setw(TYPENAME_WIDTH) << left << "DumpLink_CreateParams"
       << prmName << ";" << endl;
}
void DumpLink::genResetLinkPrms(ostream& fp, string obj)
{
    fp << BLOCK_SPACE << "DumpLink_CreateParams_Init(&" << obj << "->" << prmName << ");" << endl;
}
int DumpLink::setInLink(Link* obj)
{
    CHECK_ERROR(inLink.size() == 0, "Error: Link ["+name+"] should have ONE incoming link !!!");
    inLink.push_back(make_pair(obj, -1));
    return inLink.size() - 1;
}
int DumpLink::setOutLink(Link* obj)
{
    CHECK_ERROR(outLink.size() == 0, "Error: Link ["+name+"] should have ONE outgoing link !!!");
    outLink.push_back(make_pair(obj, -1));
    return outLink.size() - 1;
}
void DumpLink::genSetLinkPrms(ostream& fp, string obj) {}

/********************************************************************************/
UndumpLink::UndumpLink(string nm)
{
    cType = cUndumpLink;
    name = nm;
    linkIDName = name + string("LinkID");
    prmName = name + string("Prm");
    execPos = -1;
    procID = -1;
    pType = A15;
    mulInQue = false;
    mulOutQue = false;
}
UndumpLink::~UndumpLink() {}
void UndumpLink::genIncludes(ostream& fp)
{
    CHECK_ERROR_ABORT(inLink.size() == 0, "Error: Link ["+name+"] must have ZERO incoming links !!!");
    CHECK_ERROR_ABORT(outLink.size() == 1, "Error: Link ["+name+"] must have ONE outgoing link !!!");
    fp << "#include <link_api/undumpLink.h>" << endl;
}
void UndumpLink::genLinkID(ostream& fp)
{
    fp << BLOCK_SPACE << setw(IDTYPE_WIDTH) << left << "uint32_t" << linkIDName << ";" << endl;
}
void UndumpLink::genCreatePrms(ostream& fp)
{
    fp << BLOCK_SPACE << setw(TYPENAME_WIDTH) << left << "UndumpLink_CreateParams"
       << prmName << ";" << endl;
}
void UndumpLink::genResetLinkPrms(ostream& fp, string obj)
{
    fp << BLOCK_SPACE << "UndumpLink_CreateParams_Init(&" << obj << "->" << prmName << ");" << endl;
}
int UndumpLink::setInLink(Link* obj)
{
    CHECK_ERROR_ABORT(SHOULD_NOT_REACH, "Error: Link ["+name+"] should not have any incoming link !!!");
}
int UndumpLink::setOutLink(Link* obj)
{
    CHECK_ERROR(outLink.size() == 0, "Error: Link ["+name+"] should have ONE outgoing link !!!");
    outLink.push_back(make_pair(obj, -1));
    return outLink.size() - 1;
}
void UndumpLink::genSetLinkPrms(ostream& fp, string obj) {}

/********************************************************************************/
OGLink::OGLink(string nm)
{
    cType = cOGLink;
    name = nm;
    linkIDName = name + string("LinkID");
    prmName = name + string("Prm");
    execPos = -1;
    procID = -1;
    pType = A15;
    mulInQue = false;
    mulOutQue = false;
}
OGLink::~OGLink() {}
void OGLink::genIncludes(ostream& fp)
{
    CHECK_ERROR_ABORT(inLink.size() == 1, "Error: Link ["+name+"] must have ONE incoming link !!!");
    CHECK_ERROR_ABORT(outLink.size() == 1, "Error: Link ["+name+"] must have ONE outgoing link !!!");
    fp << "#include <link_api/ogLink.h>" << endl;
}
void OGLink::genLinkID(ostream& fp)
{
    fp << BLOCK_SPACE << setw(IDTYPE_WIDTH) << left << "uint32_t" << linkIDName << ";" << endl;
}
void OGLink::genCreatePrms(ostream& fp)
{
    fp << BLOCK_SPACE << setw(TYPENAME_WIDTH) << left << "OGLink_CreateParams"
       << prmName << ";" << endl;
}
void OGLink::genResetLinkPrms(ostream& fp, string obj)
{
    fp << BLOCK_SPACE << "OGLink_CreateParams_Init(&" << obj << "->" << prmName << ");" << endl;
}
int OGLink::setInLink(Link* obj)
{
    CHECK_ERROR(inLink.size() == 0, "Error: Link ["+name+"] should have ONE incoming link !!!");
    inLink.push_back(make_pair(obj, -1));
    return inLink.size() - 1;
}
int OGLink::setOutLink(Link* obj)
{
    CHECK_ERROR(outLink.size() == 0, "Error: Link ["+name+"] should have ONE outgoing link !!!");
    outLink.push_back(make_pair(obj, -1));
    return outLink.size() - 1;
}
void OGLink::genSetLinkPrms(ostream& fp, string obj) {}

/********************************************************************************/
Alg_UndistortTracks::Alg_UndistortTracks(string nm) {
    cType = cAlg_UndistortTracks;
    name = nm;
    linkIDName = name + string("LinkID");
    prmName = name + string("Prm");
    execPos = -1;
    procID = -1;
    pType = IPU1_0;
    mulInQue = true;
    mulOutQue = true;
}

Alg_UndistortTracks::~Alg_UndistortTracks() {
}
void Alg_UndistortTracks::genIncludes(ostream &fp) {
    CHECK_ERROR_ABORT(inLink.size() == 1, "Error: Link ["+name+"] must have 1 incoming link !!!");
    CHECK_ERROR_ABORT(outLink.size() == 1, "Error: Link ["+name+"] must have 1 outgoing link !!!");

    fp << "#include <include/link_api/algorithmLink_undistortTracks.h>"<< endl;
}
void Alg_UndistortTracks::genLinkID(ostream &fp) {
    fp << BLOCK_SPACE << setw(IDTYPE_WIDTH) << left << "UInt32" << linkIDName << ";" << endl;
}
void Alg_UndistortTracks::genCreatePrms(ostream &fp) {
    fp << BLOCK_SPACE << setw(TYPENAME_WIDTH) << left
            << "AlgorithmLink_UndistortTracksCreateParams " << name << "Prm" << ";"
            << endl;
}
void Alg_UndistortTracks::genResetLinkPrms(ostream &fp, string obj) {
    fp << BLOCK_SPACE << "AlgorithmLink_undistortTracks_Init(&" << obj\
            << "->" << prmName << ");" << endl;
}
int Alg_UndistortTracks::setInLink(Link* obj) //returns QueueID
{
    inLink.push_back(make_pair(obj, -1));
    return (inLink.size() - 1);
}
int Alg_UndistortTracks::setOutLink(Link* obj) //return QueueID
{
    outLink.push_back(make_pair(obj, -1));
    return (outLink.size() - 1);
}
void Alg_UndistortTracks::genSetLinkPrms(ostream &fp, string obj)
{
    fp<<BLOCK_SPACE << "(" << obj << "->" << prmName <<")." << "baseClassCreate.size  = sizeof(AlgorithmLink_UndistortTracksCreateParams);"<<endl;
    if(pType == DSP1 || pType == DSP2)
        fp<<BLOCK_SPACE << "(" << obj << "->" << prmName <<")." << "baseClassCreate.algId  = ALGORITHM_LINK_DSP_ALG_UNDISTORTTRACKS;"<<endl;
}

/********************************************************************************/
Slam::Slam(string nm)
{
    cType = cSlam;
    name = nm;
    linkIDName = name + string("LinkID");
    prmName = name + string("Prm");
    execPos = -1;
    procID = -1;
    pType = A15;
    mulInQue = true;
    mulOutQue = true;
}
Slam::~Slam() {}
void Slam::genIncludes(ostream& fp)
{
    CHECK_ERROR_ABORT(inLink.size() <= 2, "Error: Link ["+name+"] must have AT MOST TWO incoming links !!!");
    CHECK_ERROR_ABORT(outLink.size() == 2, "Error: Link ["+name+"] must have TWO outgoing links !!!");
    fp << "#include <link_api/slamLink.h>" << endl;
}
void Slam::genLinkID(ostream& fp)
{
    fp << BLOCK_SPACE << setw(IDTYPE_WIDTH) << left << "uint32_t" << linkIDName << ";" << endl;
}
void Slam::genCreatePrms(ostream& fp)
{
    fp << BLOCK_SPACE << setw(TYPENAME_WIDTH) << left << "SlamLink_CreateParams"
        << prmName << ";" << endl;
}
void Slam::genResetLinkPrms(ostream& fp, string obj)
{
    fp << BLOCK_SPACE << "SlamLink_CreateParams_Init(&" << obj << "->" << prmName << ");"
        << endl;
}
int Slam::setInLink(Link* obj)
{
    inLink.push_back(make_pair(obj, -1));
    return (inLink.size() - 1);
}
int Slam::setOutLink(Link* obj)
{
    outLink.push_back(make_pair(obj, -1));
    return (outLink.size() - 1);
}
void Slam::genSetLinkPrms(ostream& fp, string obj){}

/********************************************************************************/
Alg_Triangulation::Alg_Triangulation(string nm) {
    cType = cAlg_Triangulation;
    name = nm;
    linkIDName = name + string("LinkID");
    prmName = name + string("Prm");
    execPos = -1;
    procID = -1;
    pType = IPU1_0;
    mulInQue = true;
    mulOutQue = true;
}

Alg_Triangulation::~Alg_Triangulation() {
}
void Alg_Triangulation::genIncludes(ostream &fp) {
    CHECK_ERROR_ABORT(inLink.size() == 1, "Error: Link ["+name+"] must have 1 incoming link !!!");
    CHECK_ERROR_ABORT(outLink.size() == 1, "Error: Link ["+name+"] must have 1 outgoing link !!!");

    fp << "#include <include/link_api/algorithmLink_triangulation.h>"<< endl;
}
void Alg_Triangulation::genLinkID(ostream &fp) {
    fp << BLOCK_SPACE << setw(IDTYPE_WIDTH) << left << "UInt32" << linkIDName << ";" << endl;
}
void Alg_Triangulation::genCreatePrms(ostream &fp) {
    fp << BLOCK_SPACE << setw(TYPENAME_WIDTH) << left
            << "AlgorithmLink_TriangulationCreateParams " << name << "Prm" << ";"
            << endl;
}
void Alg_Triangulation::genResetLinkPrms(ostream &fp, string obj) {
    fp << BLOCK_SPACE << "AlgorithmLink_triangulation_Init(&" << obj\
            << "->" << prmName << ");" << endl;
}
int Alg_Triangulation::setInLink(Link* obj) //returns QueueID
{
    inLink.push_back(make_pair(obj, -1));
    return (inLink.size() - 1);
}
int Alg_Triangulation::setOutLink(Link* obj) //return QueueID
{
    outLink.push_back(make_pair(obj, -1));
    return (outLink.size() - 1);
}
void Alg_Triangulation::genSetLinkPrms(ostream &fp, string obj)
{
    fp<<BLOCK_SPACE << "(" << obj << "->" << prmName <<")." << "baseClassCreate.size  = sizeof(AlgorithmLink_TriangulationCreateParams);"<<endl;
    if(pType == DSP1 || pType == DSP2)
        fp<<BLOCK_SPACE << "(" << obj << "->" << prmName <<")." << "baseClassCreate.algId  = ALGORITHM_LINK_DSP_ALG_TRIANGULATION;"<<endl;
}

/********************************************************************************/
Alg_StereoApp::Alg_StereoApp(string nm) {
    cType = cAlg_StereoApp;
    name = nm;
    linkIDName = name + string("LinkID");
    prmName = name + string("Prm");
    execPos = -1;
    procID = -1;
    pType = IPU1_0;
    mulInQue = true;
    mulOutQue = true;
}

Alg_StereoApp::~Alg_StereoApp() {
}
void Alg_StereoApp::genIncludes(ostream &fp) {
    CHECK_ERROR_ABORT(inLink.size() == 1, "Error: Link ["+name+"] must have one incoming link !!!");
    CHECK_ERROR_ABORT(outLink.size() == 2, "Error: Link ["+name+"] must have two outgoing link !!!");

    fp << "#include <include/alglink_api/algorithmLink_stereoApp.h>"<< endl;
}
void Alg_StereoApp::genLinkID(ostream &fp) {
    fp << BLOCK_SPACE << setw(IDTYPE_WIDTH) << left << "UInt32" << linkIDName << ";" << endl;
}
void Alg_StereoApp::genCreatePrms(ostream &fp) {
    fp << BLOCK_SPACE << setw(TYPENAME_WIDTH) << left
            << "AlgorithmLink_StereoAppCreateParams " << name << "Prm" << ";"
            << endl;
}
void Alg_StereoApp::genResetLinkPrms(ostream &fp, string obj) {
    fp << BLOCK_SPACE << "AlgorithmLink_StereoApp_Init(&" << obj\
            << "->" << prmName << ");" << endl;
}
int Alg_StereoApp::setInLink(Link* obj) //returns QueueID
{
    CHECK_ERROR_ABORT(inLink.size() == 0, "Error: Link ["+name+"] must have an incoming link !!!");
    inLink.push_back(make_pair(obj, -1));
    return (inLink.size() - 1);
}
int Alg_StereoApp::setOutLink(Link* obj) //return QueueID
{
    CHECK_ERROR_ABORT(outLink.size() < 2, "Error: Link ["+name+"] must have outgoing link !!!");
    outLink.push_back(make_pair(obj, -1));
    return (outLink.size() - 1);
}
void Alg_StereoApp::genSetLinkPrms(ostream &fp, string obj)
{
    fp<<BLOCK_SPACE << "(" << obj << "->" << prmName <<")." << "baseClassCreate.size  = sizeof(AlgorithmLink_StereoAppCreateParams);"<<endl;
    fp<<BLOCK_SPACE << "(" << obj << "->" << prmName <<")." << "baseClassCreate.algId  = ALGORITHM_LINK_DSP_ALG_STEREO_APP;"<<endl;
}
/********************************************************************************/
Alg_drawRearview::Alg_drawRearview(string nm) {
    cType = cAlg_drawRearview;
    name = nm;
    linkIDName = name + string("LinkID");
    prmName = name + string("Prm");
    execPos = -1;
    procID = -1;
    pType = DSP1;
    mulInQue = false;
    mulOutQue = false;
}

Alg_drawRearview::~Alg_drawRearview() {
}
void Alg_drawRearview::genIncludes(ostream &fp) {
    CHECK_ERROR_ABORT(inLink.size() == 1, "Error: Link ["+name+"] must have one incoming link !!!");
    CHECK_ERROR_ABORT(outLink.size() == 1, "Error: Link ["+name+"] must have one outgoing link !!!");

    fp << "#include <include/alglink_api/algorithmLink_drawRearview.h>"<< endl;
}
void Alg_drawRearview::genLinkID(ostream &fp) {
    fp << BLOCK_SPACE << setw(IDTYPE_WIDTH) << left << "UInt32" << linkIDName << ";" << endl;
}
void Alg_drawRearview::genCreatePrms(ostream &fp) {
    fp << BLOCK_SPACE << setw(TYPENAME_WIDTH) << left
            << "AlgorithmLink_drawRearviewCreateParams " << name << "Prm" << ";"
            << endl;
}
void Alg_drawRearview::genResetLinkPrms(ostream &fp, string obj) {
}
int Alg_drawRearview::setInLink(Link* obj) //returns QueueID
{
    CHECK_ERROR_ABORT(inLink.size() == 0, "Error: Link ["+name+"] must have an incoming link !!!");
    inLink.push_back(make_pair(obj, -1));
    return (inLink.size() - 1);
}
int Alg_drawRearview::setOutLink(Link* obj) //return QueueID
{
    CHECK_ERROR_ABORT(outLink.size() < 1, "Error: Link ["+name+"] must have outgoing link !!!");
    outLink.push_back(make_pair(obj, -1));
    return (outLink.size() - 1);
}
void Alg_drawRearview::genSetLinkPrms(ostream &fp, string obj)
{
    fp<<BLOCK_SPACE << "(" << obj << "->" << prmName <<")." << "baseClassCreate.size  = sizeof(AlgorithmLink_drawRearviewCreateParams);"<<endl;
    fp<<BLOCK_SPACE << "(" << obj << "->" << prmName <<")." << "baseClassCreate.algId  = ALGORITHM_LINK_DSP_ALG_DRAWREARVIEW;"<<endl;
}
/********************************************************************************/
AutosarIpcIn::AutosarIpcIn(string nm) {
    cType = cAutosarIpcIn;
    name = nm;
    linkIDName = name + string("LinkID");
    prmName = name + string("Prm");
    execPos = -1;
    procID = -1;
    pType = IPU1_0;
    mulInQue = false;
    mulOutQue = false;
}

AutosarIpcIn::~AutosarIpcIn() {
}
void AutosarIpcIn::genIncludes(ostream &fp) {
    CHECK_ERROR_ABORT(inLink.size() == 0, "Error: Link ["+name+"] must have NO incoming link !!!");
    CHECK_ERROR_ABORT(outLink.size() == 0, "Error: Link ["+name+"] must have NO outgoing link !!!");
    fp << "#include <include/link_api/autosar_ipcLink.h>"<< endl;
}
void AutosarIpcIn::genLinkID(ostream &fp) {
    fp << BLOCK_SPACE << setw(IDTYPE_WIDTH) << left << "UInt32" << linkIDName << ";" << endl;
}
void AutosarIpcIn::genCreatePrms(ostream &fp)
{
}
void AutosarIpcIn::genResetLinkPrms(ostream &fp, string obj)
{
}
int AutosarIpcIn::setInLink(Link* obj) {
    CHECK_ERROR_ABORT(SHOULD_NOT_REACH, "Error: Link ["+name+"] should not have any incoming link !!!");
    return -1;
}
int AutosarIpcIn::setOutLink(Link* obj) {
    CHECK_ERROR_ABORT(SHOULD_NOT_REACH, "Error: Link ["+name+"] should not have any outgoing link !!!");
    return -1;
}
void AutosarIpcIn::genSetLinkPrms(ostream &fp, string obj)
{
}
/********************************************************************************/
AutosarIpcOut::AutosarIpcOut(string nm) {
    cType = cAutosarIpcOut;
    name = nm;
    linkIDName = name + string("LinkID");
    prmName = name + string("Prm");
    execPos = -1;
    procID = -1;
    pType = IPU1_0;
    mulInQue = false;
    mulOutQue = false;
}

AutosarIpcOut::~AutosarIpcOut() {
}
void AutosarIpcOut::genIncludes(ostream &fp) {
    CHECK_ERROR_ABORT(inLink.size() == 0, "Error: Link ["+name+"] must have NO incoming link !!!");
    CHECK_ERROR_ABORT(outLink.size() == 0, "Error: Link ["+name+"] must have NO outgoing link !!!");
    fp << "#include <include/link_api/autosar_ipcLink.h>"<< endl;
}
void AutosarIpcOut::genLinkID(ostream &fp) {
    fp << BLOCK_SPACE << setw(IDTYPE_WIDTH) << left << "UInt32" << linkIDName << ";" << endl;
}
void AutosarIpcOut::genCreatePrms(ostream &fp)
{
}
void AutosarIpcOut::genResetLinkPrms(ostream &fp, string obj)
{
}
int AutosarIpcOut::setInLink(Link* obj) {
   CHECK_ERROR_ABORT(SHOULD_NOT_REACH, "Error: Link ["+name+"] must have NO incoming link !!!");
   return -1;
}
int AutosarIpcOut::setOutLink(Link* obj) {
   CHECK_ERROR_ABORT(SHOULD_NOT_REACH, "Error: Link ["+name+"] must have NO outgoing link !!!");
   return -1;
}
void AutosarIpcOut::genSetLinkPrms(ostream &fp, string obj)
{
}

