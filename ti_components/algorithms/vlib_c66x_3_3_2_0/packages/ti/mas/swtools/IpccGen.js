/******************************************************************************
 * FUNCTION PURPOSE: Gather information that will be used by iCcase & icspec scripts to populate
 *				integration configuration.specification & iCSPEC files respectively.
 ******************************************************************************
 * DESCRIPTION:
 *	It calls sub-routine functions to generate package clearcase file.
 *	It prints the raw, sorted, and pruned versions of the data collected using (an approximate) configspec.clearcase format.
 *	It returns the pruned data collected in the form of a hash table 
 *	Apparently, this script has a similar duty as pccGen.js; and hence the name.
 *  HashTable	IpccGen()
 *****************************************************************************/
//These are global variables used by sub-routines of IpccGen
var verbose = 1;	//used to turn on/off verbose mode of operation (default value is 1)
var verboseCtr = 0; //used to label line# of verbose output
var csccInconsista=0; //detects mismatch between v.r.x.p. defined in Version.xdc of a Pkg & v.r.x.p. stated in ME section of CSCC file of the same Pkg.
var warningBuffer=new Array();
var defaultVOB="dsps_gtmas";	//default VOB; this is also the VOB where this script resides in.
if((xdc.csd().toString().search(defaultVOB)!=-1)){//defaultVOB is part of the path to this script
} else{
	warningBuffer.push("\n####Ignore this warning if you want "+defaultVOB+" to be your defaultVOB####\nWARNING"+
	"The defaultVOB parameter is currently set to:- "+defaultVOB+" inside the Ccase.js script located in "+xdc.csd()+
	"However, the CcaseccParser.js script is aparently NOT in "+defaultVOB+"\n\n\n");
}
var reRunIt = 0;
function IpccGen(arguments){

utils.importFile("src/iFormatArg.js");
utils.importFile("src/CcasefindFilePlus.js");
utils.importFile("src/pccRecBuild.js");
utils.importFile("src/CcaseccParser.js");
utils.importFile("src/mergeToPcc.js");
utils.importFile("src/CcasereadVersion.js");
utils.importFile("src/CcasefindVOB.js");
utils.importFile("src/CcasefindVisiblePkgRepo.js");
utils.importFile("src/sortSecByPkg.js");
utils.importFile("src/prune.js");
utils.importFile("src/CcaseopenUpFile.js");
utils.importFile("src/printHash.js");
utils.importFile("src/CcaseprintWarnings.js");

try{
	var proArgs=iFormatArg(arguments);
} catch(e){//Rerun script!
	print("\nPlease re-run the script!\n");
	reRunIt = 1;
	print(e);
	return {};
}

var paths = proArgs[0]; 
var archs = proArgs[1];

var optArgs = proArgs[2];
verbose = optArgs[0];
var allIncosiBuf = new Array(); //will contain all the inconsistency warnings collected
var allHash = {}; //will contain the (filtered) information about (dev) configuration.specification of all packages in "paths"
for each(var xxx in ["ME", "DEP", "INTERNAL", "TST"]){
		allHash[xxx]=new Array();
}
var pruneLogOpened = 0; //becomes 1 when we create a log file to display pruning details
for each (var pa in paths){
	var p = pa.split("\\"); //Extract the package-name from the path-of-the package & save it in variable "p"
	var pRoot = p.splice(0,2); //The first two "syllables" in the path are the (1) the drive letter :\ & (2) the vob ....Save those in pRoot
	pRoot = pRoot.join("\\"); //This has a form of <D:\<vob>. It will be used when calling pccRecBuild below.
	p = p.join("\.");
	var pHash = {};//initialize hash table that will contian the package-clearcase data for package "p"
	for each(var xxx in ["ME", "DEP", "INTERNAL", "TST"]){ //note that the TST part will eventually be dropped
		pHash[xxx]=new Array();
	}
	var pInconsiBuff = new Array();	//contains warnings about inconsistencies in the ME portion of (developement) configspec.clearcase files read	
	var prbRet = pccRecBuild(1, pHash, p, 0, pInconsiBuff, p, [optArgs[1]], pRoot,"");
	pHash = prbRet[0];
	pInconsiBuff = prbRet[1];
	var pHashSor = sortSecByPkg(pHash, ["DEP", "INTERNAL", "TST"], 2);
	var pHashPru = prune(pHashSor, (pruneLogOpened==0 ? "w" : "a"));   
	pruneLogOpened = 1;
	//Finally, SAVE the information, which is gathered recursively starting from the (dev) configuration.specification file of package "p", INTO "allHash"
	allHash = mergeToPcc(pHashPru, allHash, ["DEP", "INTERNAL"]);
	allHash["DEP"].push(pHash["ME"][0]); //besides, keep the information about package "p" in DEP section.		
	allIncosiBuf = allIncosiBuf.concat(pInconsiBuff); //store the warnings for later printing.		
}
if(csccInconsista==0){//no problems in (dev) configuration.specification files that were read.
	printHash("", "Integration_RAW", allHash, "");	//for now, print these log files to the current working directory.//ASK BOGDAN IF we need to print raw, sorted, pruned data for integration	
	var allHashSor = sortSecByPkg(allHash, ["DEP", "INTERNAL"], 2);
	printHash("", "Integration_SORTED", allHashSor, "");			//ASK BOGDAN IF we need to print raw, sorted, pruned data for integration	
	var allHashPru = prune(allHashSor, "a");
	//EMBED THE ARCHITECTURE informatino INTO the hash table that contains all the rest of data
	allHashPru["ARCH"] = new Array();
	allHashPru["ARCH"] = archs;
	printHash("", "Integration_PRUNED", allHashPru, "");			//ASK BOGDAN IF we need to print raw, sorted, pruned data for integration
	printWarnings("", "");
	
} else {
	print("\n\n\n"+"@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@");
	print("***	Inconsistent (dev) configspec.clearcase is Detected:-	***\n");
	print("Problems are found in the (dev) configspec.clearcase of the following packages:-");	
	print("- - - - - - - - - - - - - - - - - - - - - - - - -");
	for(var row=0; row<allIncosiBuf.length; row++){
		print(allIncosiBuf[row][0]);//sort and prune messages by inconsiBuff[row][1] (This is possible future work, which will make the command line print out more compact!)
	}
	print("- - - - - - - - - - - - - - - - - - - - - - - - -");
	print("\n#######");
	print("The (dev) configspec.clearcase of all the packages listed above MUST BE generated using Ccase.js first!");
	print("#######\n");
	print("......therefore, the Integration configuration.specification FILE IS NOT CREATED.");
	print("@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"+"\n\n\n");
	printWarnings("", "");
	
	throw new Error("Inconsistent (dev) configspec.clearcase is Detected.");		
}
return allHashPru;
}