/*##########################################*/
/*@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*/
/*##########################################*/
/*		***Instructions***		*/
/*This script is used to generate a configspec.clearcase ASCII file for a package that is built.*/
/*We refer to the package, whose configspec.clearcase is to be generated, as 'the package of interest'*/
/*The script can be called from any directory which is a built package.*/
/*If the script is called from the package of interest, no parameter needs to be given.*/
/*If the script is not called from the package of interest, the full name of the package should be given*/ 
/*The package of interest should be in the same VOB as the package which is the current directory*/
/*		***Parameters***		*/
/*There are 2 parameters refering to (1)<name of package built> & (2)<verbose option?>.*/
/*(1) <name of package built> can either be full name of the package, or "".*/
/*-It is "" if the current directory is the same as the package of interest; if the current directory*/
/*is not a built package & this parameter is "", we will get an error!*/
/*-If it is not "", it is an existing full name of a package which is just built*/
/*(2) <verbose option> can only take on a value "-quiet". If it is not specified*/
/*the default non-verbose option is used.*/
/*		***Description***			*/
/*The script commands a set of subroutines which read package.ext.XML files*/
/*and Version.xdc modules of the package of interest and its dependents.*/
/*All its sub-routines are saved in <src> folder in parallel with the Ccase.js script.*/
/*The sub-routine script files are named with a Ccase prefix followed by the only function they define.*/
/*The variables defined in Ccase.js are visible to the sub-routines.*/
/*Once the sub-routines are imported in Ccase.js using utils.importFile(), it is as if the text of those*/
/*sub-routines (functions) is written in this Ccase.js file.*/
/*The objective is to synthesize configspec.clearcase automatically for the package of interest.*/
/*Any irregularities are written to Ccase.log file in the same directory as configspec.clearcase*/
/*Fatal Errors or reports on successfull completions are always reported on the command line.*/
/*Under the verbose mode, step by step details of the script operation is reported on the command line.*/
/*##########################################*/
/*@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*/
/*##########################################*/
//Global variables:-
var reRunIt = 0;	//This will be set to 1 if a 'fatal' error would result b/c of parameter/pre-condition violations.
var pkgOfMainScript="ti.mas.swtools";	//default package for this script to reside in. We'll get warning if this isn't true.
if((xdc.csd().match(pkgOfMainScript)[0])!=(pkgOfMainScript.replace(/\./g, "\\"))
    && (xdc.csd().match(pkgOfMainScript)[0])!=(pkgOfMainScript.replace(/\./g, "/"))){
	//directory of Ccase.js script doesn't match default package for Ccase.js script (ti.mas.swtools)
	print("Ccase.js script is not inside the default"+pkgOfMainScript+" package. Put it there!");
	reRunIt = 1;
}
var warningBuffer=new Array();
var defaultVOB="dsps_gtmas";	//default VOB; this is also the VOB where this script resides in.
if((xdc.csd().toString().search(defaultVOB)!=-1)){//defaultVOB is part of the path to this script
} else{
	warningBuffer.push("\n####Ignore this warning if you want "+defaultVOB+" to be your defaultVOB####\nWARNING"+
	"The defaultVOB parameter is currently set to:- "+defaultVOB+" inside the Ccase.js script located in "+xdc.csd()+
	"However, the CcaseccParser.js script is aparently NOT in "+defaultVOB+"\n\n\n");
}
var verbose = 1;	//used to turn on/off verbose mode of operation
var verboseCtr = 0; //used to label line# of verbose output
var compaKeyMisMatch = 0;	//detects mismatch between C.K. required & defined by package.xdc of PkgOfInterest & other Pkgs respectively.
var csccInconsista=0; //detects mismatch between v.r.x.p. defined in Version.xdc of a Pkg & v.r.x.p. stated in ME section of CSCC file of the same Pkg.
//The following variables defined here are visible Globally:- {xmlNotFound, ccaseModule, dontPutInDep, ignorePkgOfInterest}

utils.importFile("src/CcaseformatArgument.js");
utils.importFile("src/Ccasefind_DEP_INT_ME_rTST.js");
utils.importFile("src/Ccasefind_TST_andPrint.js");
utils.importFile("src/CcasetstConstructor.js");
utils.importFile("src/CcaseprintConfigspecCC.js");
utils.importFile("src/CcasereadVersion.js");
utils.importFile("src/CcasereadXdcXml.js");
utils.importFile("src/CcaseparseXdcXml.js");
utils.importFile("src/CcaseopenUpFile.js");
utils.importFile("src/CcasefindVisiblePkgRepo.js");
utils.importFile("src/CcasefindVOB.js");
utils.importFile("src/CcaseprintWarnings.js");
utils.importFile("src/CcaseccParser.js");
utils.importFile("src/CcasefindFilePlus.js");


formaArgs = formatArgument(arguments, "ccase");
if (reRunIt==0){	//Compute & print configspec.clearcase and warnings if arguments are legal.

	 if(verbose==1){verboseCtr++;print(verboseCtr+":-\tGathering information to populate configspec.clearcase...");}
	/***NOTE***/
	//Until RTSC tools BUG is fixed, we have to use the following HACK
	//xdc.$$make_om('cfg');  /* hack! only for xdc 2.94 access to Version modules */
	//Find out packages that should be ignored while building configspec.clearcase file (save them in "dontPutInDep" var).
	try{
		var ccaseModule = xdc.module(pkgOfMainScript+'.Ccase');
		var dontPutInDep = ccaseModule.ignoreList;
		if(dontPutInDep==undefined || dontPutInDep==null){
			throw new Error("Ignore-list in Ccase.xdc module of "+pkgOfMainScript+" is undefined or null");
		}
	} catch(ex){
		warningBuffer.push("Problem accessing list of packages to IGNORE inside Ccase.xdc module of "+pkgOfMainScript+"\n"+ex);
		dontPutInDep=[];
	}
	//Check to see if the package of interest is one of those specified in Ccase.xdc to be ignored! (This is unlikely, but should be checked,)
	var ignorePkgOfInterest = 0;
	for each (var ignoListMember in dontPutInDep){
		if(formaArgs==ignoListMember){
			ignorePkgOfInterest = 1;					
		}
	}
	if(ignorePkgOfInterest==1){
		print(formaArgs+" (package of interest) was specified to be ignored in Ccase.xdc!");
		print("Edit Ccase.xdc & build its package before attempting to generate configspec.clearcase for (package of interest) "+formaArgs);
	} else if(ignorePkgOfInterest==0){		
		//rTST below stands for RAW DATA needed for TST
		var Content_DEP_INT_ME_rTST = new Array(4); //initialize 2D array used to store contents of configspec.clearcase
		for(var ccc=0; ccc<Content_DEP_INT_ME_rTST.length;ccc++){
			Content_DEP_INT_ME_rTST[ccc] = new Array();
		}
		var xmlNotFound = 0;  //This will be set to 1 if any of the package.ext.xml files needed can't be loaded.
		//Refer to description of parameters of the function find_DEP_INT_ME_rTST(...)
		Content_DEP_INT_ME_rTST = find_DEP_INT_ME_rTST(formaArgs, Content_DEP_INT_ME_rTST, dontPutInDep);
		if(xmlNotFound==1){
			//Stop the script pre-maturely; fatal error was already reported on command line when xmlNotFound changed its boolean value (0)!
		} else if (xmlNotFound==0){
			find_TST_andPrint(formaArgs, Content_DEP_INT_ME_rTST, dontPutInDep);
		}
	}
	printWarnings(formaArgs, "");
	//CHECK CONDITIONS FOR TERMINATION OF SCRIPT CALLING Ccase.js
	//These are messages displayed on command line before termination of the script that called Ccase.js
	var ckMmMessage="\n\n\n"+"@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"+
	"\nSERIOUS MISMATCH of Compatibility Keys has resulted in the TERMINATION of the program that called Ccase.js"+
	"\n#######\nPLEASE READ Ccase.log file to correct the Compatibility Key mismatch in package.xdc files.\n#######\n"+
	"@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"+"\n\n\n";	
	var verIncoMessage="\n\n\n"+"@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"+
	"\nSERIOUS MISMATCH b/n information in ME portion of configspec.clearcase of some packages AND "+
	"their actual {PkgName, V.R.X.P. or VOB} info has resulted in the TERMINATION of the program that called Ccase.js"+
	"\n#######\nPLEASE follow the suggestions printed above & run Ccase.js on the packages specified above first\n#######\n"
	"@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"+"\n\n\n";
	if(compaKeyMisMatch == 0){
		if(csccInconsista==0){
		} else if(csccInconsista==1){
			print(verIncoMessage);
			throw new Error("Inconsistent information in ME part of configspec.clearcase of some pkgs");					
		}
	} else if(compaKeyMisMatch == 1){
		if(csccInconsista==0){
			print(ckMmMessage);
			throw new Error("Compatibility Key Mismatch b/n package.xdc & package.ext.xml");
		} else if(csccInconsista==1){
			print(verIncoMessage+ckMmMessage);
			throw new Error("Inconsistent information in ME part of configspec.clearcase of some pkgs &\n"+
							"Compatibility Key Mismatch b/n package.xdc & package.ext.xml");
		}	
	}
} else {
	print("\n"+" Please re-run the script with correct arguments and/or after meeting environment pre-conditions.");
}