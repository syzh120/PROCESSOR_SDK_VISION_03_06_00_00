/******************************************************************************
 * FUNCTION PURPOSE: Generate package clearcase file.
 ******************************************************************************
 * DESCRIPTION:
 *	It calls sub-routine functions to generate package clearcase file.
 *	It prints the raw, sorted, and pruned versions of the package clearcase file using (an approximate) configspec.clearcase format.
 *	It returns the pruned data of package clearcase in the form of a hash table 
 *  HashTable	pccGen()
 *****************************************************************************/
//These are global variables used by sub-routines of pccGen
var verbose = 1;	//used to turn on/off verbose mode of operation
var reRunIt = 0;	//This will be set to 1 if a 'fatal' error would result b/c of parameter/pre-condition violations.
var verboseCtr = 0; //used to label line# of verbose output
var warningBuffer=new Array();
var defaultVOB="dsps_gtmas";	//default VOB; this is also the VOB where this script resides in.
if((xdc.csd().toString().search(defaultVOB)!=-1)){//defaultVOB is part of the path to this script
} else{
	warningBuffer.push("\n####Ignore this warning if you want "+defaultVOB+" to be your defaultVOB####\nWARNING"+
	"The defaultVOB parameter is currently set to:- "+defaultVOB+" inside the Ccase.js script located in "+xdc.csd()+
	"However, the CcaseccParser.js script is aparently NOT in "+defaultVOB+"\n\n\n");
}
var csccInconsista=0; //detects mismatch between v.r.x.p. defined in Version.xdc of a Pkg & v.r.x.p. stated in ME section of CSCC file of the same Pkg.

function pccGen(arguments){

utils.importFile("src/CcaseopenUpFile.js");
utils.importFile("src/CcaseccParser.js");
utils.importFile("src/mergeToPcc.js");
utils.importFile("src/pccRecBuild.js");
utils.importFile("src/printHash.js");
utils.importFile("src/sortSecByPkg.js");
utils.importFile("src/CcaseformatArgument.js");
utils.importFile("src/CcasereadVersion.js");
utils.importFile("src/CcasefindVisiblePkgRepo.js");
utils.importFile("src/CcasefindVOB.js");
utils.importFile("src/prune.js");
utils.importFile("src/CcasefindFilePlus.js");
utils.importFile("src/CcaseprintWarnings.js");

//###ARGUMENT PROCESSING###//
var pccArgs1 = new Array(); //This is the portion of the arguments that is the same as that of Ccase.js's arguments. Thus, this can be passed to formatArgument() for processing.
var pccArgs2 = new Array(); //This are the additional arguments that are used by pccGen.js 

//LAW change<<<
//initialize pccArgs2 array with default optinal argument values
pccArgs2 = [0]; //0<->don't -ignore; ...
for (var n=0; n<arguments.length; n++){//Rule: first arg is pkgName if not prefixed by '-'; all args are checked against recognizable args with '-' prefix
	if(arguments[n].search(/^\-/) != -1){ // is "-x.."
		if(arguments[n]=="-quiet"){
			pccArgs1.push(arguments[n]);
		} else {//here check that it is a RECOGNIZABLE optional argument
			if(arguments[n]=="-ignore"){
					pccArgs2[0]=1;	//reset the appropriate default value used to initialize pccArgs2
			} //else if(arguments[n]=="-xxx"){} ...					
		}				
	} else if(n==0){//this must be package name
		pccArgs1.push(arguments[n]);
	}
}
//LAW change>>>
/*
//old argument LAW<<<
if(typeof[arguments.length-1]!="object"){//If users only provided arguments that would be given for Ccase.js, use default values
	pccArgs1 = arguments;
	pccArgs2 = [0]; //default values: 
	//pccArgs2[0] -> if this is 1, ignore missing Versions, which could cause termination because of vrxp inconsistency that is detected; and don't ignore if 0
} else if(typeof[arguments.length-1]=="object"){
	pccArgs1 = arguments;
	pccArgs2.push(pccArgs1.pop());
}
//old argument LAW>>>
*/
var formaArgs = formatArgument(pccArgs1, "pccgen");
if(reRunIt==0){//no problems detected by formatArgumment
	if(pccArgs2[0]==0){//if user does not specify all arguments than those for Ccase.js, report the situation and the default values used
		print("\n\n***UNSOLICITED SUGGESTIONS...***\nYou have not specified all the optional argument values.\n"+
			  "You can re-run the script with the following values if you do not want the default values for these arguments.\n"+
			  "Use \"-ignore\" if you do NOT want the script to terminate because of inconsistency induced ONLY by un-loadable Version modules\n"+
			  "Use \"\" if ... \n"+
			  "Use \"\" if ... \n"+
			  "***Thanks for reading the above unsolicited suggestion***\n\n");
	}
	//###ARGUMENT PROCESSING###//
	var pccHashI = {};//initialize hash table containing package clearcase data
	var portiCC = ["ME", "DEP", "INTERNAL", "TST"];
	for each(var p in portiCC){
		pccHashI[p]=new Array();
	}
	var inconsiBuff = new Array();
	var history = new Array();
	var pccRBret = pccRecBuild(1, pccHashI, formaArgs, 0, inconsiBuff, formaArgs, pccArgs2, "",history);//parent & pkgToParse are the same for 1st call. The root has default "" value
	var pccHash = pccRBret[0];
	inconsiBuff = pccRBret[1];
	if(csccInconsista==1){
		print("\n\n\n"+"@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@");
		print("***	Inconsistent configspec.clearcase is Detected:-	***\n");
		print("Problems are found in the configspec.clearcase of the following packages:-");	
		print("- - - - - - - - - - - - - - - - - - - - - - - - -");
		for(var row=0; row<inconsiBuff.length; row++){
			print(inconsiBuff[row][0]);//sort and prune messages by inconsiBuff[row][1] 
		}
		print("- - - - - - - - - - - - - - - - - - - - - - - - -");
		print("\n#######");
		print("The configspec.clearcase of all the packages listed above MUST BE generated using Ccase.js first!");
		print("#######\n");
		print("......therefore, Package-Clearcase FILE IS NOT CREATED.");
		print("@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"+"\n\n\n");
		printWarnings(formaArgs, "");
		
		throw new Error("Inconsistent configspec.clearcase is Detected.");	
	} else {
		printHash(formaArgs,"Raw",pccHash, "");//This is intermediate data that is printed to swtools
		var sortedPcc = sortSecByPkg(pccHash, ["DEP", "INTERNAL", "TST"], 2);
		printHash(formaArgs,"Sorted",sortedPcc, "");
		var prunedPcc = prune(sortedPcc, "w");//use "w" because we want a new pruningInfo log file to be created.
		printHash(formaArgs, "Pruned", prunedPcc, "");
		printWarnings(formaArgs, "");
	}

	return prunedPcc;
} else if (reRunIt==1){
	print("\n"+" Please re-run the script with correct arguments and/or after meeting environment pre-conditions.");
	return {};
}
}