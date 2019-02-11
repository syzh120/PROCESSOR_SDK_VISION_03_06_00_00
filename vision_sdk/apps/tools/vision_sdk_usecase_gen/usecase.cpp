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

#include <iomanip>
#include <ostream>

#include "usecase.h"


Usecase::Usecase() {
    for (int i = 0; i < OBJ_MAX; i++) {
        for (int j = 0; j < OBJ_MAX; j++) {
            matrix[i][j] = false;
            userMat[i][j] = false;
        }
    }
    numIpc = 0;
    fileName = "";
    structName = "";
    logFile = &cout;
}

void Usecase::initialize() {
    if (fileName.length() == 0)
        setFileName("out");
    cmd_options.setFileNames(fileName);
    logFile = cmd_options.log_File();
    assignCPU();
    createAllConn();
    setSequence();
    assignLinkID();
}

void Usecase::print() {
    if(cmd_options.verboseMode())
    {
        //printFileName(&cout);
        printExecSeq(&cout);
        //printTable(&cout);
    }
    if(cmd_options.write_tologFile())
    {
        printFileName(logFile);
        printExecSeq(logFile);
        printTable(logFile);
    }
}

void Usecase::genFiles() {
    if (cmd_options.write_toImage())
        genImgFile();
    if (cmd_options.write_toFile())
        genFile();
}

void Usecase::setFileName(string name) {
    fileName = name;
    structName = name + string("Obj");
}

string Usecase::getFileName() {
    return fileName;
}

void Usecase::setStructName(string name) {
    structName = name;
}

string Usecase::getStructName() {
    return structName;
}

Link* Usecase::getObject(string name) {
    map<string, Link*>::iterator it;
    it = inst_object.find(name);
    if (it == inst_object.end())
        return NULL;
    else
        return it->second;
}

Link* Usecase::createObject(string name) {
    Link* obj = getObject(name);
    if (obj != NULL)
        return obj;
    else {
        createNewObj(name, obj);
        temp_seq.push_back(obj);
        inst_object[name] = obj;
        obj->setMatrixPos(temp_seq.size() - 1);
        return obj;
    }
}

void Usecase::createNewObj(string name, Link* &obj) {
    string root = getRoot(name);
    if (root == "AvbRx")
        obj = new AVBReceive(name);
    else if (root == "AvbTx")
        obj = new AVBTransmit(name);
    else if (root == "TfdtpRx")
        obj = new TFDTPReceive(name);
    else if (root == "Alg") {
        string sec = getSecRoot(name);
        if (sec == "ColorToGray")
            obj = new Alg_ColorToGray(name);
        else if (sec == "DenseOptFlow")
            obj = new Alg_DenseOptFlow(name);
        else if (sec == "DmaSwMs")
            obj = new Alg_DMASwMs(name);
        else if (sec == "VpeSwMs")
            obj = new Alg_VPESwMs(name);
        else if (sec == "EdgeDetect")
            obj = new Alg_EdgeDetect(name);
        else if (sec == "SoftIsp")
            obj = new Alg_SoftIsp(name);
        else if (sec == "IssAewb")
            obj = new Alg_IssAewb(name);
        else if (sec == "ObjectDetection")
            obj = new Alg_ObjectDetection(name);
        else if (sec == "ObjectClassification")
            obj = new Alg_ObjectClassification(name);
        else if (sec == "DriverMonitor")
            obj = new Alg_DriverMonitor(name);
        else if (sec == "FeaturePlaneComputation")
            obj = new Alg_FeaturePlaneComputation(name);
        else if (sec == "ImagePreProcess")
            obj = new Alg_ImagePreProcess(name);
        else if (sec == "ImgPyramid")
            obj = new Alg_ImgPyramid(name);
        else if (sec == "FPCompute")
            obj = new Alg_FPCompute(name);
        else if (sec == "FrameCopy")
            obj = new Alg_FrameCopy(name);
        else if (sec == "SafeFrameCopy")
            obj = new Alg_SafeFrameCopy(name);
        else if (sec == "MyAlgFinish")
            obj = new Alg_MyAlgFinish(name);
        else if (sec == "MyAlg1")
            obj = new Alg_MyAlg1(name);
        else if (sec == "MyAlg2")
            obj = new Alg_MyAlg2(name);
        else if (sec == "MyAlg3")
            obj = new Alg_MyAlg3(name);
        else if (sec == "Census")
            obj = new Alg_Census(name);
        else if (sec == "DisparityHamDist")
            obj = new Alg_DisparityHamDist(name);
        else if (sec == "UltrasonicFusion")
            obj = new Alg_UltrasonicFusion(name);
        else if (sec == "GeoAlign")
            obj = new Alg_GeoAlign(name);
        else if (sec == "GeoAlign3D")
            obj = new Alg_GeoAlign3D(name);
        else if (sec == "ObjectDraw")
            obj = new Alg_ObjectDraw(name);
        else if (sec == "PhotoAlign")
            obj = new Alg_PhotoAlign(name);
        else if (sec == "Synthesis")
            obj = new Alg_Synthesis(name);
        else if (sec == "SparseOpticalFlow")
            obj = new Alg_SparseOpticalFlow(name);
        else if (sec == "SfmLinearTwoView")
            obj = new Alg_SfmLinearTwoView(name);
        else if (sec == "SfmMain")
            obj = new Alg_SfmMain(name);
        else if (sec == "SfmMap")
            obj = new Alg_SfmMap(name);
        else if (sec == "SfmSurround")
            obj = new Alg_SfmSurround(name);
        else if (sec == "LaneDetect")
            obj = new Alg_LaneDetect(name);
        else if (sec == "Sfm")
            obj = new Alg_Sfm(name);
        else if (sec == "Clr")
            obj = new Alg_Clr(name);
        else if (sec == "Fcw")
            obj = new Alg_Fcw(name);
        else if (sec == "VectorToImage")
            obj = new Alg_VectoImg(name);
        else if (sec == "SubframeCopy")
            obj = new Alg_SubframeCopy(name);
        else if (sec == "RemapMerge")
            obj = new Alg_RemapMerge(name);
        else if (sec == "StereoPostProcess")
            obj = new Alg_StereoPostProcess(name);
        else if (sec == "SceneObstructionDetect")
            obj = new Alg_SceneObstructionDetect(name);
        else if (sec == "Crc")
            obj = new Alg_Crc(name);
        else if (sec == "AutoChartDetect")
            obj = new Alg_AutoChartDetect(name);
        else if (sec == "PoseEstimate")
            obj = new Alg_PoseEstimate(name);
        else if (sec == "DeWarp")
            obj = new Alg_DeWarp(name);
        else if (sec == "OpenCVCanny")
            obj = new Alg_OpenCVCanny(name);
        else if (sec == "RadarProcess")
            obj = new Alg_RadarProcess(name);
        else if (sec == "UndistortTracks")
            obj = new Alg_UndistortTracks(name);
        else if (sec == "Triangulation")
            obj = new Alg_Triangulation(name);
        else if (sec == "AutoRemap")
            obj = new Alg_AutoRemap(name);
        else if (sec == "StereoApp")
            obj = new Alg_StereoApp(name);
        else if (sec == "tidl")
            obj = new Alg_tidl(name);
        else if (sec == "tiop")
            obj = new Alg_tiop(name);
        else if (sec == "tidlpreproc")
            obj = new Alg_tidlpreproc(name);
        else if (sec == "tidlpostproc")
            obj = new Alg_tidlpostproc(name);
        else if (sec == "drawRearview")
        	obj = new Alg_drawRearview(name);
        else if (sec == "SeamDetection")
            obj = new Alg_SeamDetection(name);
        else if (sec == "Stitching")
            obj = new Alg_Stitching(name);
        else if (sec == "AdaptiveBowl")
            obj = new Alg_AdaptiveBowl(name);
        else{
            obj = new Alg(name);
            cout << "Warning: Custom defined Algorithm plugin Link [" << sec << "] found !!!" << endl;
        }
    } else if (root == "Capture")
        obj = new Capture(name);
    else if (root == "IssCapture")
        obj = new IssCapture(name);
    else if (root == "IssM2mIsp")
        obj = new IssM2mIsp(name);
    else if (root == "IssM2mSimcop")
        obj = new IssM2mSimcop(name);
    else if (root == "IssM2mResizer")
        obj = new IssM2mResizer(name);
    else if (root == "RadarDraw")
        obj = new RadarDraw(name);
    else if (root == "UltrasonicCapture")
        obj = new UltrasonicCapture(name);
    else if (root == "Decode")
        obj = new Decode(name);
    else if (root == "DisplayCtrl")
        obj = new DisplayCtrl(name);
    else if (root == "Display")
        obj = new Display(name);
    else if (root == "DisplayMultiPipe")
        obj = new DisplayMultiPipe(name);
    else if (root == "Dup")
        obj = new Dup(name);
    else if (root == "Split")
        obj = new Split(name);
    else if (root == "Gate")
        obj = new Gate(name);
    else if (root == "Encode")
        obj = new Encode(name);
    else if (root == "GrpxSrc")
        obj = new GrpxSrc(name);
    else if (root == "IPCIn")
        obj = new IPCIn(name);
    else if (root == "IPCOut")
        obj = new IPCOut(name);
    else if (root == "Merge")
        obj = new Merge(name);
    else if (root == "Null")
            obj = new Null(name);
    else if (root == "DataCollect")
            obj = new DataCollect(name);
    else if (root == "NullSource")
        obj = new NullSource(name);
    else if (root == "Select")
        obj = new Select(name);
    else if (root == "Sync")
        obj = new Sync(name);
    else if (root == "SgxFrmcpy")
        obj = new SgxFrmcpy(name);
    else if (root == "DrmDisplay")
        obj = new DrmDisplay(name);
    else if (root == "DispDistSrc")
        obj = new DispDistSrc(name);
    else if (root == "Sgx3Dsrv")
        obj = new Sgx3Dsrv(name);
    else if (root == "Sgx3Dsfm")
        obj = new Sgx3Dsfm(name);
    else if (root == "SgxLink")
        obj = new SgxLink(name);
    else if (root == "VPE")
        obj = new VPE(name);
    else if (root == "DssM2mWb")
        obj = new DssM2mWb(name);
    else if (root == "Hcf")
        obj = new Hcf(name);
    else if (root == "DefLink")
        obj = new DefLink(name);
    else if (root == "EpSink")
        obj = new EpLink(name);
    else if (root == "EpSource")
        obj = new EpLink(name);
    else if (root == "LidarCapture")
        obj = new LidarCapture(name);
    else if (root == "LidarCloud")
        obj = new LidarCloud(name);
    else if (root == "LidarCloudXForm")
        obj = new LidarCloudXForm(name);
    else if (root == "LidarGPCLink")
        obj = new LidarGPCLink(name);
    else if (root == "ImuLink")
        obj = new ImuLink(name);
    else if (root == "DumpLink")
        obj = new DumpLink(name);
    else if (root == "UndumpLink")
        obj = new UndumpLink(name);
    else if (root == "OGLink")
        obj = new OGLink(name);
    else if (root == "Slam")
        obj = new Slam(name);
    else if (root == "NetworkTx")
        obj = new NetworkTx(name);
    else if (root == "NetworkRx")
        obj = new NetworkRx(name);
    else if (root == "AutosarIpcIn")
        obj = new AutosarIpcIn(name);
    else if (root == "AutosarIpcOut")
        obj = new AutosarIpcOut(name);
    else
        CHECK_ERROR_ABORT(false, "Error: Link [" + name + "] name does not match supported links. Use '-h' option to see list of supported links !!!");
}

void Usecase::assignCPU() {
    for (int i = 0; i < temp_seq.size(); i++)
        (temp_seq.at(i))->setProcType((temp_seq.at(i))->getProcType());
}

void Usecase::assignLinkID() {
    for (int i = 0; i < exec_seq.size(); i++)
        (exec_seq.at(i))->setLinkIDName();
}



/**For each head:
 * //if no parent || all parents assigned/visited
        //if not assigned,
        1. assign itself -- set all false

        2. find a child unassigned, call func assign on to child - child visited true
        3. if all child assigned, move assign parent

//if all parents not assigned
1. find a parent unassigned, unvisited call assign func on it -- visited mark true
 */

void Usecase::assignSeq(int curr, bool* asgn, bool* visited, bool* done) {

    int N = temp_seq.size(), parv = -1, parAsgn=-1, child = -1, par = -1;
    bool allAsgn = true;
    for (int i = 0; i < N; i++) {
        if(matrix[i][curr] == true && !(asgn[i]||visited[i])) //if parent
        {
            parAsgn = i;
            allAsgn = false;
        }
        else if(matrix[i][curr] == true && visited[i] && !asgn[i])
            parv = i;
    }


    if(allAsgn == true)
    {
        //if not visited yet
        if(visited[curr] == false)
        {
            if(parv == -1) //all parent assigned
            {
                //assign itself
                if(asgn[curr] == false)
                {
                    exec_seq.push_back(temp_seq.at(curr));
                    (temp_seq.at(curr))->setExecPos(exec_seq.size() - 1);
                    asgn[curr] = true;
                    for (int k = 0; k < N; k++)
                        visited[k] = false;
                }
                //find a child unassigned
                for (int i = 0; i < N; i++)
                    if(matrix[curr][i] == true && asgn[i] == false)
                        child = i;

                if(child != -1)
                    assignSeq(child, asgn, visited, done);
                else //if all child assign visit all parents again
                {
                    done[curr] = true;
                    for (int i = 0; i < N; i++) {
                        if(matrix[i][curr] == true && done[i] == false)
                            assignSeq(i, asgn, visited, done);
                    }
                }
            }
            else
            {
                visited[curr] = true;
                assignSeq(parv, asgn, visited, done);
            }
        }
        else
        {
            if(asgn[curr] == false)
            {
                //assign itself
                exec_seq.push_back(temp_seq.at(curr));
                (temp_seq.at(curr))->setExecPos(exec_seq.size() - 1);
                asgn[curr] = true;
                for (int k = 0; k < N; k++)
                    visited[k] = false;
            }

            //find a child unassigned
            for (int i = 0; i < N; i++)
                if(matrix[curr][i] == true && asgn[i] == false)
                    child = i;

            if(child != -1)
                assignSeq(child, asgn, visited, done);
            else //if all child assign visit all parents again
            {
                done[curr] = true;
                for (int i = 0; i < N; i++) {
                    if(matrix[i][curr] == true && done[i] == false)
                        assignSeq(i, asgn, visited, done);
                }
            }
        }
    }
    else
    {
        visited[curr] = true;
        assignSeq(parAsgn, asgn, visited, done);
    }
}

void Usecase::setSequence() {
    //All links with no incoming link is assigned sequence number
    int N = temp_seq.size();
    bool asgn[N], visited[N], done[N];
    bool head = true;

    for (int i = 0; i < N; i++) {
        asgn[i] = false;
        visited[i] = false;
        done[i] = false;
    }

    for (int i = 0; i < N; i++) {
        head = true;
        //checks if any incoming link i.e any link with seq num not assigned
        for (int j = 0; j < N; j++) {
            if (matrix[j][i] == true) {
                head = false;
                break;
            }
        }
        if (head == true) { //For each head
            assignSeq(i, asgn, visited, done);
        }
    }
}

void Usecase::printFileName(ostream* out) {
    (*out) << "UseCase Name: " << fileName << endl;
}

void Usecase::printMatrix(ostream* out) {
    (*out) << "*******" << endl;
    for (int i = 0; i < temp_seq.size(); i++)
        (*out) << (temp_seq.at(i))->getName() << " "
                << (temp_seq.at(i))->getMatrixPos() << endl;

    for (int i = 0; i < temp_seq.size(); i++) {
        for (int j = 0; j < temp_seq.size(); j++)
            (*out) << matrix[i][j] << " ";
        (*out) << endl;
    }
}

void Usecase::connect(Link* obj1, Link* obj2) {
    if (obj2 != NULL) {
        int pos1 = obj1->getMatrixPos();
        int pos2 = obj2->getMatrixPos();

        if (userMat[pos1][pos2] == false) // Not already connected
        {
            //cout<<obj1->getProcType()<<" "<<obj2->getProcType()<<endl;
            if ((obj1->getProcType() == obj2->getProcType()) ||
                    obj2->getClassType() == cAlg_SubframeCopy ||
                    ((obj1->getClassType() == cIPCOut)
                            && (obj2->getClassType()) == cIPCIn)) { //If same processor types, or if both links are IPC's

                if(cmd_options.verboseMode())
                    cout << obj1->getName() << " is connected to "
                        << obj2->getName() << endl;

                if(cmd_options.write_tologFile())
                    *logFile << obj1->getName() << " is connected to "
                        << obj2->getName() << endl;

                int i = 0, pos1 = -1, pos2 = -1;
                while ((pos1 == -1 || pos2 == -1) && i < temp_seq.size()) {
                    if (temp_seq.at(i) == obj1)
                        pos1 = i;
                    else if (temp_seq.at(i) == obj2)
                        pos2 = i;
                    i++;
                }

                int q1 = obj1->setOutLink(obj2);
                int q2 = obj2->setInLink(obj1);
                obj1->setOutQueueID(q1, q2);
                obj2->setInQueueID(q2, q1);

                matrix[pos1][pos2] = true;
                userMat[pos1][pos2] = true;

                if ((obj1->getClassType() == cIPCOut)
                        && (obj2->getClassType() == cIPCIn)) {
                    obj2->setName(
                            "IPCIn_" + procName[obj2->getProcType()] + "_"
                                    + procName[obj1->getProcType()] + "_"
                                    + toString(obj2->getProcID()));
                    obj1->setName(
                            "IPCOut_" + procName[obj1->getProcType()] + "_"
                                    + procName[obj2->getProcType()] + "_"
                                    + toString(obj1->getProcID()));
                }
            } else {
                if(cmd_options.verboseMode())
                    cout << obj1->getName() << ", " << obj2->getName()
                        << ": On different Processor, Intermediate IPCs needed"
                        << endl;
                if(cmd_options.write_tologFile())
                    (*logFile) << obj1->getName() << ", " << obj2->getName()
                        << ": On different Processor, Intermediate IPCs needed"
                        << endl;


                userMat[pos1][pos2] = true; //Mark link as connected(user sees them as connected, even though intermediate IPC's are needed)

                //Create to ipc links
                if (getRoot(obj1->getName()) != "IPCOut"
                        && getRoot(obj2->getName()) != "IPCIn") //not either one is IPC
                {
                    string ipc = "IPCOut_" + toString(numIpc);
                    numIpc++;
                    string ipc2 = "IPCIn_" + toString(numIpc);
                    numIpc++;

                    Link* IPC1 = createObject(ipc);
                    IPC1->setProcType(obj1->getProcType());
                    Link* IPC2 = createObject(ipc2);
                    IPC2->setProcType(obj2->getProcType());

                    connect(obj1, IPC1);
                    connect(IPC1, IPC2);
                    connect(IPC2, obj2);

                } else if (getRoot(obj1->getName()) == "IPCOut") {
                    string ipc2 = "IPCIn_" + toString(numIpc);
                    numIpc++;

                    Link* IPC2 = createObject(ipc2);
                    IPC2->setProcType(obj2->getProcType());

                    connect(obj1, IPC2);
                    connect(IPC2, obj2);
                } else if (getRoot(obj2->getName()) == "IPCIn") {
                    string ipc = "IPCOut_" + toString(numIpc); // Some no
                    numIpc++;

                    Link* IPC1 = createObject(ipc);
                    IPC1->setProcType(obj1->getProcType());

                    connect(obj1, IPC1);
                    connect(IPC1, obj2);
                }
            }
        }
    }
}

void Usecase::genImgFile() {
    ostream& fp = *(cmd_options.write_Image());

    fp << "digraph " << fileName << " {\n" << endl;
    //Nodes
    /*
     * Color Code:
     * IPU1_0 : lightblue
     * IPU1_1 : darkturquoise
     * IPU2   : hotpink
     * A15    : lightsalmon
     * DSP1   : palegreen
     * DSP2   : darkolivegreen1
     * EVE1   : yellow
     * EVE2   : gold
     * EVE3   : orange
     * EVE4   : goldenrod4
     */
    //TODO: Mention in documentation change color here
    //Colour Scheme
    fp << BLOCK_SPACE << "ColorScheme [shape=none, margin=0, label=<\n";
    fp << BLOCK_SPACE
            << "<TABLE BORDER=\"0\" CELLBORDER=\"1\" CELLSPACING=\"0\" CELLPADDING=\"4\">\n";

    if (proc.getObjsAssgn(IPU1_0))
        fp << BLOCK_SPACE << "<TR><TD bgcolor=\"lightblue\">IPU1_0</TD></TR>\n";
    if (proc.getObjsAssgn(IPU1_1))
        fp << BLOCK_SPACE
                << "<TR><TD bgcolor=\"darkturquoise\">IPU1_1</TD></TR>\n";
    if (proc.getObjsAssgn(IPU2))
        fp << BLOCK_SPACE
                << "<TR><TD bgcolor=\"hotpink\">IPU2</TD></TR>\n";
    if (proc.getObjsAssgn(DSP1))
        fp << BLOCK_SPACE << "<TR><TD bgcolor=\"palegreen\">DSP1</TD></TR>\n";
    if (proc.getObjsAssgn(DSP2))
        fp << BLOCK_SPACE
                << "<TR><TD bgcolor=\"darkolivegreen1\">DSP2</TD></TR>\n";
    if (proc.getObjsAssgn(EVE1))
        fp << BLOCK_SPACE << "<TR><TD bgcolor=\"yellow\">EVE1</TD></TR>\n";
    if (proc.getObjsAssgn(EVE2))
        fp << BLOCK_SPACE << "<TR><TD bgcolor=\"gold\">EVE2</TD></TR>\n";
    if (proc.getObjsAssgn(EVE3))
        fp << BLOCK_SPACE << "<TR><TD bgcolor=\"orange\">EVE3</TD></TR>\n";
    if (proc.getObjsAssgn(EVE4))
        fp << BLOCK_SPACE << "<TR><TD bgcolor=\"goldenrod4\">EVE4</TD></TR>\n";
    if (proc.getObjsAssgn(A15))
        fp << BLOCK_SPACE << "<TR><TD bgcolor=\"lightsalmon\">A15</TD></TR>\n";

    fp << BLOCK_SPACE << "</TABLE>>];\n" << endl;

    //Links
    if (exec_seq.size())
        fp << BLOCK_SPACE
                << "/************** LINKS ************************/\n";
    for (int i = 0; i < exec_seq.size(); i++) {
        ProcType pType = (exec_seq.at(i))->getProcType();
        if (pType == IPU1_0)
            fp << BLOCK_SPACE << (exec_seq.at(i))->getName()
                    << " [color=lightblue, style=filled]" << endl; //shape=box
        else if (pType == IPU1_1)
            fp << BLOCK_SPACE << (exec_seq.at(i))->getName()
                    << " [color=darkturquoise, style=filled]" << endl;
        else if (pType == IPU2)
            fp << BLOCK_SPACE << (exec_seq.at(i))->getName()
                    << " [color=hotpink, style=filled]" << endl;
        else if (pType == A15)
            fp << BLOCK_SPACE << (exec_seq.at(i))->getName()
                    << " [color=lightsalmon, style=filled]" << endl;
        else if (pType == DSP1)
            fp << BLOCK_SPACE << (exec_seq.at(i))->getName()
                    << " [color=palegreen, style=filled]" << endl;
        else if (pType == DSP2)
            fp << BLOCK_SPACE << (exec_seq.at(i))->getName()
                    << " [color=darkolivegreen1, style=filled]" << endl;
        else if (pType == EVE1)
            fp << BLOCK_SPACE << (exec_seq.at(i))->getName()
                    << " [color=yellow, style=filled]" << endl;
        else if (pType == EVE2)
            fp << BLOCK_SPACE << (exec_seq.at(i))->getName()
                    << " [color=gold, style=filled]" << endl;
        else if (pType == EVE3)
            fp << BLOCK_SPACE << (exec_seq.at(i))->getName()
                    << " [color=orange, style=filled]" << endl;
        else if (pType == EVE4)
            fp << BLOCK_SPACE << (exec_seq.at(i))->getName()
                    << " [color=goldenrod4, style=filled]" << endl;
    }
    fp << endl;

    //Connections
    fp << BLOCK_SPACE
            << "/************** CONNECTIONS ************************/\n";
    for (int i = 0; i < temp_seq.size(); i++) {
        for (int j = 0; j < temp_seq.size(); j++) {
            if (matrix[i][j] == true) {
                //[taillabel=Q0, headlabel=Q0, minlen=2, labeldistance=2]
                if ((temp_seq.at(i))->getOutLinkSize() > 1
                        && (temp_seq.at(j))->getInLinkSize() > 1)
                    fp << BLOCK_SPACE << (temp_seq.at(i))->getName() << " -> "
                            << (temp_seq.at(j))->getName() << "[headlabel=Q"
                            << (temp_seq.at(j))->getInQueueID(temp_seq.at(i))
                            << ", taillabel=Q"
                            << (temp_seq.at(i))->getOutQueueID(temp_seq.at(j))
                            << ", minlen=2, labeldistance=3]" << endl;
                else if ((temp_seq.at(i))->getOutLinkSize() > 1)
                    fp << BLOCK_SPACE << (temp_seq.at(i))->getName() << " -> "
                            << (temp_seq.at(j))->getName() << "[taillabel=Q"
                            << (temp_seq.at(i))->getOutQueueID(temp_seq.at(j))
                            << ", minlen=2, labeldistance=3]" << endl;
                else if ((temp_seq.at(j))->getInLinkSize() > 1)
                    fp << BLOCK_SPACE << (temp_seq.at(i))->getName() << " -> "
                            << (temp_seq.at(j))->getName() << "[headlabel=Q"
                            << (temp_seq.at(j))->getInQueueID(temp_seq.at(i))
                            << " minlen=2, labeldistance=3]" << endl;
                else
                    fp << BLOCK_SPACE << (temp_seq.at(i))->getName() << " -> "
                            << (temp_seq.at(j))->getName() << endl;
            }
        }
    }

    fp << "}" << endl;

    cmd_options.close_Image();
    string outputPath = cmd_options.get_output_path_name();
    //TODO: Mention in documentation requirements
    string cmd = "dot -Tjpg " + outputPath + fileName + "_img.txt -o "+outputPath+ fileName + ".jpg";
    system(cmd.c_str());
}

void Usecase::genFile() {

    ostream& fp = *(cmd_options.write_File());
    ostream& fph = *(cmd_options.write_Header());
    initFiles(fp, fph);
    genIncludes(fp, fph);
    genStruct(fp, fph);
    genSetLinkID(fp, fph);
    genFreeLinkID(fp, fph);
    genResetLinkPrms(fp, fph);
    genSetLinkPrms(fp, fph);
    genConnectLinks(fp, fph);
    genCreate(fp, fph);
    genStart(fp, fph);
    genStop(fp, fph);
    genDelete(fp, fph);
    genBufferStatistics(fp, fph);
    genStatistics(fp, fph);
    endFiles(fp, fph);

}

void Usecase::initFiles(ostream& fp, ostream& fph)
{
    string headcmmt = "\
/****************************************************************************\n\
Copyright (c) [2012 - 2017] Texas Instruments Incorporated\n\
\n\
All rights reserved not granted herein.\n\
\n\
Limited License.\n\
\n\
 Texas Instruments Incorporated grants a world-wide, royalty-free, non-exclusive\n\
 license under copyrights and patents it now or hereafter owns or controls to\n\
 make,  have made, use, import, offer to sell and sell ('Utilize') this software\n\
 subject to the terms herein.  With respect to the foregoing patent license,\n\
 such license is granted  solely to the extent that any such patent is necessary\n\
 to Utilize the software alone.  The patent license shall not apply to any\n\
 combinations which include this software, other than combinations with devices\n\
 manufactured by or for TI ('TI Devices').  No hardware patent is licensed\n\
 hereunder.\n\
\n\
 Redistributions must preserve existing copyright notices and reproduce this\n\
 license (including the above copyright notice and the disclaimer and\n\
 (if applicable) source code license limitations below) in the documentation\n\
 and/or other materials provided with the distribution\n\
\n\
 Redistribution and use in binary form, without modification, are permitted\n\
 provided that the following conditions are met:\n\
\n\
 * No reverse engineering, decompilation, or disassembly of this software\n\
   is permitted with respect to any software provided in binary form.\n\
\n\
 * Any redistribution and use are licensed by TI for use only with TI Devices.\n\
\n\
 * Nothing shall obligate TI to provide you with source code for the software\n\
   licensed and provided to you in object code.\n\
\n\
 If software source code is provided to you, modification and redistribution of\n\
 the source code are permitted provided that the following conditions are met:\n\
\n\
 * Any redistribution and use of the source code, including any resulting\n\
   derivative works, are licensed by TI for use only with TI Devices.\n\
\n\
 * Any redistribution and use of any object code compiled from the source code\n\
   and any resulting derivative works, are licensed by TI for use only with TI\n\
   Devices.\n\
\n\
 Neither the name of Texas Instruments Incorporated nor the names of its\n\
 suppliers may be used to endorse or promote products derived from this software\n\
 without specific prior written permission.\n\
\n\
 DISCLAIMER.\n\
\n\
 THIS SOFTWARE IS PROVIDED BY TI AND TI’S LICENSORS 'AS IS' AND ANY EXPRESS OR\n\
 IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF\n\
 MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.\n\
 IN NO EVENT SHALL TI AND TI’S LICENSORS BE LIABLE FOR ANY DIRECT, INDIRECT,\n\
 INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT\n\
 LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR\n\
 PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF\n\
 LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE\n\
 OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF\n\
 ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.\n\
******************************************************************************\n\
*/\n\
/*\n\
*******************************************************************************\n\
*\n\
* IMPORTANT NOTE:\n\
*  This file is AUTO-GENERATED by Vision SDK use case generation tool\n\
*\n\
*******************************************************************************\n\
*/";

    fp<<headcmmt<<endl;
    fph<<headcmmt<<endl;

    fph << endl;
    fph<<"#ifndef _"<<fileName<<"_H_"<<endl;
    fph<<"#define _"<<fileName<<"_H_"<<endl;
    fph << endl;
    fp<<"#include \""<<fileName<<"_priv.h\""<<endl;

}

void Usecase::genIncludes(ostream& fp, ostream& fph)
{
    bool unique;
    fph<<"#include <include/link_api/system.h>"<<endl;
    if(cmd_options.useDynamicLinkId())
    {
        fph<<"#include <include/link_api/system_linkId_alloc.h>"<<endl;
    }
    for (int i = 0; i < exec_seq.size(); i++)
    {
        unique = true;
        for (int j = i+1; j < exec_seq.size(); j++)
        {
            if((exec_seq.at(i))->getClassType() == (exec_seq.at(j))->getClassType())
                unique = false;
        }
        if(unique)
            (exec_seq.at(i))->genIncludes(fph);
    }

}

void Usecase::genStruct(ostream& fp, ostream& fph) {
    fph << "\n";
    fph << "typedef struct {" << endl;
    for (int i = 0; i < exec_seq.size(); i++)
        (exec_seq.at(i))->genLinkID(fph);
    fph << "\n";
    for (int i = 0; i < exec_seq.size(); i++)
        (exec_seq.at(i))->genCreatePrms(fph);
    fph << "} " << structName << ";" << endl;
    fph << "\n";
}

void Usecase::genSetLinkID(ostream& fp, ostream& fph) {
    string obj = "pObj";
    fph << "Void " << fileName << "_SetLinkId(" << structName << " *" << obj
            << ");\n" << endl; //header line
    fp << "Void " << fileName << "_SetLinkId(" << structName << " *" << obj
            << "){" << endl;
    for (int i = 0; i < exec_seq.size(); i++)
        (exec_seq.at(i))->genSetLinkID(fp, obj);
    fp << "}\n" << endl;
}

void Usecase::genFreeLinkID(ostream& fp, ostream& fph) {
    if(cmd_options.useDynamicLinkId())
    {
        string obj = "pObj";
        fph << "Void " << fileName << "_FreeLinkId(" << structName << " *" << obj
                << ");\n" << endl; //header line
        fp << "Void " << fileName << "_FreeLinkId(" << structName << " *" << obj
                << "){" << endl;
        for (int i = 0; i < exec_seq.size(); i++)
            (exec_seq.at(i))->genFreeLinkID(fp, obj);
        fp << "}\n" << endl;
    }
}

void Usecase::genResetLinkPrms(ostream& fp, ostream& fph) {
    string obj = "pObj";
    fph << "Void " << fileName << "_ResetLinkPrms(" << structName << " *" << obj
            << ");\n" << endl; //header line
    fp << "Void " << fileName << "_ResetLinkPrms(" << structName << " *" << obj
            << "){" << endl;
    for (int i = 0; i < exec_seq.size(); i++)
        (exec_seq.at(i))->genResetLinkPrms(fp, obj);
    fp << "}\n" << endl;
}

void Usecase::genSetLinkPrms(ostream& fp, ostream& fph)
{
    string obj = "pObj";
    fph << "Void " << fileName << "_SetPrms(" << structName << " *" << obj
            << ");\n" << endl; //header line
    fp << "Void " << fileName << "_SetPrms(" << structName << " *" << obj
            << "){" << endl;
    for (int i = 0; i < exec_seq.size(); i++)
        (exec_seq.at(i))->genSetLinkPrms(fp, obj);
    fp << "}\n" << endl;
}

void Usecase::genConnectLinks(ostream& fp, ostream& fph) {
    string obj = "pObj";
    fph << "Void " << fileName << "_ConnectLinks(" << structName << " *" << obj
            << ");\n" << endl; //header line
    fp << "Void " << fileName << "_ConnectLinks(" << structName << " *" << obj
            << "){\n" << endl;
    for (int i = 0; i < exec_seq.size(); i++) {
        Link* A = exec_seq.at(i);
        string dot = ".";
        string arrow = "->";
        string toprint;
        vector<pair<Link*, int> >* outLinkPtr =
                (exec_seq.at(i))->getOutLinkPtr();
        for (int j = 0; j < (outLinkPtr->size()); j++) {
            Link* B = (outLinkPtr->at(j)).first;
            int num = (outLinkPtr->at(j)).second;
            fp << BLOCK_SPACE << "//" << A->getName() << " -> " << B->getName()
                    << endl;
            if (A->getPrmName().compare(0, 16, "Alg_RadarProcess") == 0)
            {
                toprint.assign(arrow);
            }
            else
            {
                toprint.assign(dot);
            }
            if(A->getMulOutQue())
                fp << BLOCK_SPACE << obj << "->" << A->getPrmName() << toprint
                        << "outQueParams["<<j<<"].nextLink = " << obj << "->"
                        << B->getLinkName() << ";\n";
            else
                fp << BLOCK_SPACE << obj << "->" << A->getPrmName() << toprint
                                    << "outQueParams.nextLink = " << obj << "->"
                                    << B->getLinkName() << ";\n";
            if (B->getPrmName().compare(0, 16, "Alg_RadarProcess") == 0)
            {
                toprint.assign(arrow);
            }
            else
            {
                toprint.assign(dot);
            }

            if(B->getMulInQue())
            {
                fp << BLOCK_SPACE << obj << "->" << B->getPrmName() << toprint
                        << "inQueParams["<<num<<"].prevLinkId = " << obj << "->"
                        << A->getLinkName() << ";\n";
                fp << BLOCK_SPACE << obj << "->" << B->getPrmName() << toprint
                        << "inQueParams["<<num<<"].prevLinkQueId = " << j << ";\n\n";
            }
            else
            {
                fp << BLOCK_SPACE << obj << "->" << B->getPrmName() << toprint
                        << "inQueParams.prevLinkId = " << obj << "->"
                        << A->getLinkName() << ";\n";
                fp << BLOCK_SPACE << obj << "->" << B->getPrmName() << toprint
                        << "inQueParams.prevLinkQueId = " << j << ";\n\n";
            }
        }
    }
    fp << "}\n" << endl;
}

void Usecase::genCreate(ostream& fp, ostream& fph) {
    string obj = "pObj";
    fph << "Int32 " << fileName << "_Create(" << structName << " *" << obj
            << ", Void *appObj);\n" << endl; //header line
    fp << "Int32 " << fileName << "_Create(" << structName << " *" << obj
            << ", Void *appObj){" << endl;
    fp << "\n"<<BLOCK_SPACE <<"Int32 status;\n" << endl;
    fp << BLOCK_SPACE << fileName << "_SetLinkId(" << obj << ");\n";
    fp << BLOCK_SPACE << fileName << "_ResetLinkPrms(" << obj << ");\n";
    fp<<endl;
    fp << BLOCK_SPACE << fileName << "_SetPrms(" << obj << ");\n";
    fp << BLOCK_SPACE << fileName << "_SetAppPrms(" << obj << ", appObj);\n";
    fp<<endl;
    fp << BLOCK_SPACE << fileName << "_ConnectLinks(" << obj << ");\n";

    for (int i = 0; i < exec_seq.size(); i++) {
        (exec_seq.at(i))->genCreate(fp, obj);
        fp << endl;
    }

    fp << BLOCK_SPACE << "return status;"<<endl;
    fp << "}\n" << endl;
}

void Usecase::genStart(ostream& fp, ostream& fph) {
    //in reverse Order
    string obj = "pObj";
    fph << "Int32 " << fileName << "_Start(" << structName << " *" << obj
            << ");\n" << endl; //header line
    fp << "Int32 " << fileName << "_Start(" << structName << " *" << obj << "){"
            << endl;
    fp << "\n"<<BLOCK_SPACE <<"Int32 status;\n" << endl;
    for (int i = exec_seq.size() - 1; i >= 0; i--) {
        (exec_seq.at(i))->genStart(fp, obj);
        fp << endl;
    }

    fp << BLOCK_SPACE << "return status;"<<endl;
    fp << "}\n" << endl;
}

void Usecase::genStop(ostream& fp, ostream& fph) {
    //in reverse Order
    string obj = "pObj";
    fph << "Int32 " << fileName << "_Stop(" << structName << " *" << obj
            << ");\n" << endl; //header line
    fp << "Int32 " << fileName << "_Stop(" << structName << " *" << obj << "){"
            << endl;
    fp << "\n"<<BLOCK_SPACE <<"Int32 status;\n" << endl;
    for (int i = exec_seq.size() - 1; i >= 0; i--) {
        (exec_seq.at(i))->genStop(fp, obj);
        fp << endl;
    }

    fp << BLOCK_SPACE << "return status;"<<endl;
    fp << "}\n" << endl;
}

void Usecase::genDelete(ostream& fp, ostream& fph) {
    //in reverse Order
    string obj = "pObj";
    fph << "Int32 " << fileName << "_Delete(" << structName << " *" << obj
            << ");\n" << endl; //header line
    fp << "Int32 " << fileName << "_Delete(" << structName << " *" << obj << "){"
            << endl;
    fp << "\n"<<BLOCK_SPACE <<"Int32 status;\n" << endl;
    for (int i = exec_seq.size() - 1; i >= 0; i--) {
        (exec_seq.at(i))->genDelete(fp, obj);
        fp << endl;
    }
    if(cmd_options.useDynamicLinkId())
    {
        fp << BLOCK_SPACE << fileName << "_FreeLinkId(" << obj << ");\n";
    }

    fp <<BLOCK_SPACE << "return status;"<<endl;
    fp << "}\n" << endl;
}

void Usecase::genBufferStatistics(ostream& fp, ostream& fph)
{
    string obj = "pObj";
    fph << "Void " << fileName << "_printBufferStatistics(" << structName << " *" << obj
            << ");\n" << endl; //header line
    fp << "Void " << fileName << "_printBufferStatistics(" << structName << " *" << obj
            << "){" << endl;
    for (int i = 0; i < exec_seq.size(); i++)
    {
        (exec_seq.at(i))->genBufferStatistics(fp, obj);
        if((i==exec_seq.size()-1) || ((exec_seq.at(i)->getProcType() != (exec_seq.at(i+1))->getProcType())))
            fp << BLOCK_SPACE <<"Task_sleep(500);" <<endl;
    }

    fp << "}\n" << endl;
}

void Usecase::genStatistics(ostream& fp, ostream& fph)
{
    string obj = "pObj";
    fph << "Void " << fileName << "_printStatistics(" << structName << " *" << obj
            << ");\n" << endl; //header line
    fp << "Void " << fileName << "_printStatistics(" << structName << " *" << obj
            << "){" << endl;
    for (int i = 0; i < exec_seq.size(); i++)
    {
        (exec_seq.at(i))->genStatistics(fp, obj);
        if((i==exec_seq.size()-1) || ((exec_seq.at(i)->getProcType() != (exec_seq.at(i+1))->getProcType())))
            fp << BLOCK_SPACE <<"Task_sleep(500);" <<endl;
    }
    fp << "}\n" << endl;
}

void Usecase::endFiles(ostream& fp, ostream& fph)
{
    fph<<"Void "<<fileName<<"_SetAppPrms("<<structName<<" *pObj, Void *appObj);\n"<<endl;
    fph<<"#endif /* _"<<fileName<<"_H_ */"<<endl;
}

void Usecase::setNewConn(vector<Link*>* vec) {
    connections.push_back(*vec);
}

void Usecase::createAllConn() {
    int sz = connections.size();
    for (int i = 0; i < sz; i++) {
        int vsz = (connections.at(i)).size();
        for (int j = vsz - 2; j >= 0; j--) {
            connect((connections.at(i)).at(j + 1), (connections.at(i)).at(j));
            //cout<<((connections.at(i)).at(j+1))->getName()<<" "<<((connections.at(i)).at(j))->getName()<<endl;
        }
    }
}

void Usecase::printExecSeq(ostream* out)
{
    (*out) << "\n********" << endl;
    (*out) << "Execution Sequence: " << endl;
    for (int i = 0; i < exec_seq.size(); i++)
        (*out) << (exec_seq.at(i))->getName() << endl;
}

void Usecase::printTable(ostream* out) {

    (*out) << endl;
    (*out) << "***********" << endl;
    (*out) << "Name\t    CPU\t       LinkType\t  INSTNum" << endl;
    for (int i = 0; i < exec_seq.size(); i++) {
        (*out) << setw(10) << left << (exec_seq.at(i))->getName() << "  ";
        (*out) << setw(10) << left << procName[(exec_seq.at(i))->getProcType()]
                << "  ";
        (*out) << setw(10) << left << getRoot((exec_seq.at(i))->getName())
                << "  ";
        (*out) << setw(10) << left << (exec_seq.at(i))->getProcID() << endl;
        //print each object's inLink and Outlink along with Queue ID
        (*out) << "InLink: " << endl;
        (exec_seq.at(i))->printInLink(*out);
        (*out) << "OutLink: " << endl;
        (exec_seq.at(i))->printOutLink(*out);
        (*out) << "--------------------------------------" << endl;
    }
}
