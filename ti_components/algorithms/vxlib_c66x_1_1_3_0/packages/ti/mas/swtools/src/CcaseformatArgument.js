/******************************************************************************
 * FUNCTION PURPOSE: Change package name format, set verbose mode, & facilitate script termination if fatal error is predicted.
 ******************************************************************************
 * DESCRIPTION: 
 *	It changes pacakge names formatted as x.y.z into x/y/z format. 
 *	If 'quiet' is specified in the arguments, it changes the default verbose option to non-verbose.
 *	It facilitates a clean termination of the script if the arguments specified would lead to fatal error.
 *  void formatArgument (
 *    string        rawArg	-the raw argument passed to script.
 *    string	   rule		-this specifies the rules that should be followed while formating & depends on the script calling formatArgument.
			: "ccase"	if called by Ccase.js, we are generating configspec.clearcase and the precondition is having a built package
			: "pccgen"	if called by pccGen.js. Here we should not impose the above mentioned precondition.
 *****************************************************************************/
function formatArgument(rawArg, rule){
var formaArgs;
var curDirIsBuiltPkg = 1; //indicates if current directory is legal (i.e. a built package)
//Under rule="CCASE":- Force Re-Run of script if the current directory is not a built package (pre-condition)
if(rule=="ccase" && xdc.findFile("./package")==null){
	print("\n"+"Problem meeting pre-conditions before running script:-");
	print("The Current Working Directory MUST BE A BUILT package before calling Ccase.js from within it."+"\n");
	reRunIt = 1;
	curDirIsBuiltPkg = 0;
}
//Force Re-Run of script if the package of interest (specified in arguments implicitly or explicitly) cannot be found.
if(rawArg.length==0){
	formaArgs = "";
	if(rule=="ccase" && xdc.findFile("./package")==null){
		print("\n"+"Problem specifiying arguments to script:-");
		print("You attempted to generate configspec.clearcase for the current working directory");
		print("The current working directory needs to be a BUILT package to generate configspec.clearcase for it."+"\n");	
		reRunIt = 1;		
	}
} else if(rawArg.length==1) {
	if(rawArg=="-quiet") {
		verbose = 0;
		formaArgs = "";
		if(rule=="ccase" && xdc.findFile("./package")==null){
			print("\n"+"Problem specifiying arguments to script:-");
			print("You attempted to generate configspec.clearcase for the current working directory");
			print("The current working directory needs to be a BUILT package to generate configspec.clearcase for it."+ 
				  "\n");	
 			reRunIt = 1;		
		}
	} else { 
		formaArgs = rawArg.toString().replace(/\./g, "\/");
		if(rule=="ccase" && findFilePlus(formaArgs+"/package")==null){
			print("\n"+"Problem specifiying arguments to script:-");
			print("You attempted to generate configspec.clearcase for "+formaArgs);			
			print("configspec.clearcase can only be generated for BUILT packages.");			
			print("script's argument needs revision! "+formaArgs+"...No such BUILT package is found"+"\n");			
			reRunIt = 1;	
		}
		if(rule=="ccase" && findFilePlus(formaArgs)==null){
			print("script's argument needs revision! "+formaArgs+"... No such package is found"+"\n");
			reRunIt = 1;
		}
	}
} else if (rawArg.length==2){
	if(rawArg[1]=="-quiet"){
		verbose = 0;
	} else if(rule=="ccase"){
		print("\n"+"Problem specifiying arguments to script:-");
		print("2nd arg of script can only be '-quiet'; 2nd arg is ignored!"+"\n");
	} 
	formaArgs = rawArg[0].toString().replace(/\./g, "\/");
	if(rule=="ccase" && findFilePlus(formaArgs+"/package")==null){
		print("\n"+"Problem specifiying arguments to script:-");
		print("You attempted to generate configspec.clearcase for "+formaArgs);			
		print("configspec.clearcase can only be generated for BUILT packages.");			
		print("script's argument needs revision! "+formaArgs+"... No such BUILT package is found"+"\n");
		reRunIt = 1;	
	}
	if(rule=="ccase" && findFilePlus(formaArgs)==null){
		print("script's argument needs revision! "+formaArgs+"... No such package is found"+"\n");
		reRunIt = 1;
	}
} else if (rawArg.length>2){
	print("\n"+"Problem specifiying arguments to script:-");
	print("Too many (i.e. " + rawArg.length + ") args given; Only the 1st one is used!"+"\n");
	formaArgs = rawArg[0].toString().replace(/\./g, "\/");
	if(rule=="ccase" && findFilePlus(formaArgs+"/package")==null){
		print("\n"+"Problem specifiying arguments to script:-");
		print("You attempted to generate configspec.clearcase for "+formaArgs);			
		print("configspec.clearcase can only be generated for BUILT packages.");			
		print("script's argument needs revision! "+formaArgs+"... No such BUILT package is found"+"\n");
		reRunIt = 1;	
	}
	if(rule=="ccase" && findFilePlus(formaArgs)==null){
		print("script's argument needs revision! "+formaArgs+"... No such package is found"+"\n");
		reRunIt = 1;
	}
}
if(verbose==1){verboseCtr++;print(verboseCtr+":-\tFormatted the arguments.");}
return formaArgs;
}