/******************************************************************************
 * FUNCTION PURPOSE: Format the arguments for the generation of integration configuration specification.
 ******************************************************************************
 * DESCRIPTION:
 *	It formats the arguments for the generation of integration configuration specification.
 *	The argument list contains 3 parts: (1) list of packages to be integrated, (2) list of architectures & 
 *	(3) array of optional booleans with a default value (Specifically verbose = 1 & ignore = 0 by default)
 *	Neither of the above parts can be empty!
 *	(1) List of packages in the same drive need to be preceded by "-r" followed by portion of their path that
 *	can readily be appended to the packages to form their actual path!
 *	If the list of packages is in the same drive as the current directory, the "-r" tag is optional.
 *	(2) List of architectures must be preceeded by "-a" AND architectures should come before any optional parameters
 *	(3) Optional parameters come AFTER the list of architectures. 
 *	The optional parameters are used to change default values of global variables. 
 *	These parameters are -ignore (to set ignore to 1) & -verbose (to reset verobose to 0)
 *	
 *	WARNING: These method should NEVER  be called from config scripts or build scripts because it changes the XDCPATH.
 *
 *	IGNORED ARGUMENTS:- All arguments that are typed after a listing of optional parameter are ignored. This is
 *	reported as a warning on command line. All mistyped optional arguments are also ignored with a warning. (eg. -iggnore, -quitte)
 *
 *	It THROWS various self explanatory EXCEPTIONS if the syntax of the arguments is not obeyed.
 *	Particularly, it throws exceptions if (1) -a is missing to separate list of packages from list of architectures,
 *	(2) if a "-r" is not followed by list of packages (3) if the packages (interpreted according to the above
 *	syntax) are not found by findFilePlus function, (4) if any of the architectures is not supported in Germantown.
 *
 *	It returns [pkgPathArr, archArr], which is a bundle of an array that contain full-path of each of the 
 *	packages specified by user AND an array that contains all the architectures specified.
 *
 *	[String[], String[]]	iFormatArg(
 *	String     -arguments	-this is the arguments passed directly to the function generating integration configspec files.)
 *****************************************************************************/
function iFormatArg(arguments){
var argString = arguments.join(",");
argString = argString.replace(/\,$/,"");//handle the case when user puts the unnecessary comma at the very end of list of architectures
argString = argString.replace(/\,\,/g, ",");//handle the case when user supplies arguments delimited by "comman & white space".
//split the arguments into the ones to the right and left of "-a" tag
var divideByA = argString.toString().match(/([\s,\S]{1,})([\,]{1})([\-]{1})([a]{1})([\,]{1})([\s,\S]{1,})/);
if(divideByA!=null){
	var rawPkgPath = divideByA[1];
	var rawArchAndOp = divideByA[6]; //contains the architectures AND possibly the optional "-" parameters such as -ignore & -quiet
} else {
	throw new Error("Problem specifying arguments:-\nThe list of packages & list of architectures is NOT separated by '-a' tag");
}
var optArr = new Array(); 	//LIST OF OPTIONAL PARAMETERS (if any)
optArr.push(1); 			//DEFAULT VALUE OF OPTIONAL ARGUMENT VERBOSE == 1;
optArr.push(0); 			//DEFAULT VALUE OF OPTIONAL ARGUMENT IGNORE == 0;
var archArr = new Array(); 		//LIST OF ARCHITECTURES
//Classify Architecture Parameters & Optional Parameters...
var copyArchOp = rawArchAndOp.split(",");
var endOfArchList = 0;
for each (var xx in copyArchOp){//check if optional parameters have been specified along with architectures; if so, do not consider unrecognized parameters that come after that
	if(xx=="-ignore"){
		endOfArchList = 1;
		optArr[1]=1; //change from default value
	} else if(xx=="-quiet"){
		endOfArchList = 1;
		optArr[0]=0; //change from default value
	}
	if(endOfArchList==0){//all parameters listed before optional parameters are Candidates to be in the list of architectures.
		archArr.push(xx);
	} else if(endOfArchList==1 && xx!="-ignore" && xx!="-quiet" && xx.search(/^[\-]{1}/)!=-1){
		print("\nWARNING!\nThe following ARGUMENT value is unrecognized and is IGNORED:-\n"+xx+"\n\n");
	} else if(endOfArchList==1 && xx!="-ignore" && xx!="-quiet" && xx.search(/^[\-]{1}/)==-1){
		print("\nWARNING!\nThe following ARGUMENT value was entered after after an optional parameter"+
		" (i.e. -ignore or -quiet). Thus IT IS IGNORED!:-\n"+xx+"\n\n");
	}
}

//Process the list of packages
var compaPkgPath = new Array(); 
if(rawPkgPath.search(/^[\-]{1}[r]{1}/)!=-1){//no default root to be assumed
	rawPkgPath = rawPkgPath.replace(/^[\-]{1}[r]{1}[,]{1}/, ""); //delete the "-r," at the begining 
	compaPkgPath = rawPkgPath.split(",-r,");
} else{//assume default root for the first part of the list
	var fileModule = xdc.module('xdc.services.io.File');
	var curFullRoot = fileModule.getCanonicalPath("");//ASK BOGDAN: can we just use first syllable after drive letter:\ (eg. X:\dsps_gtmas)
	curFullRoot = curFullRoot.toString().replace(/\//g, "\\");
	curRoot = curFullRoot.toString().match(/(^[A-Z]\:\\[^\\]{1,})([\\]{1})/)[1];	
	rawPkgPath = curRoot + "," + rawPkgPath; //use default root
	compaPkgPath = rawPkgPath.split(",-r,");	
}
//Now, each of compaPkgpath's elements should contain COMPACT pkg path info: (i.e. {Common_Root, pkg1, pkg2, ...pkgk})
var pkgPathArr = new Array(); //LIST OF PACKAGE PATHS
for(var n=0; n<compaPkgPath.length; n++){
	var comRootPkgs = compaPkgPath[n].toString().split(",");
	if(comRootPkgs.length>1){
		comRoot = comRootPkgs[0].toString().replace(/\//g, "\\");
		comRoot = comRoot.replace(/\\$/,"");		
		for(var m=1; m<comRootPkgs.length; m++){			
			pkgPathArr.push(comRoot+"\\"+comRootPkgs[m].replace(/\./g, "\\"));
		}
		//@@@@@@@@@@
		//MODIFY THE XDCPATH so that we can load modules that are within all these different roots provided. 
		//WARNING!!! Keep the following message from Dave Russo in mind.
		//Having done the following iFormatArg.js should never be called from (directly or indirectly) config or bld scripts
		//Dave Russo: "There are several methods that are currently used to change the package path from within a script.  
		//These methods should _never_ be called from config scripts or build scripts; many parts of these models assume 
		//the path does not change during execution of the script.  However, some independent tools/scripts do need to manipulate 
		//the path at startup to do they work and, in these case, it is ok to use the following methods."
		var newPath = comRoot + ";" + xdc.curPath();
		Packages.xdc.services.global.Path.setPath(newPath.split(';'));
		//@@@@@@@@@@
	} else {
		throw new Error("Problem specifying arguments:-\nNO packages are listed after -root "+comRootPkgs[0]);
	}
}
//Announce all the packages specified that could not be found.
var missingPkgs = new Array();
for each (var x in pkgPathArr){
	if(null==findFilePlus(x)){
		missingPkgs.push(x);
	}
}
//Announce all the architectures that are not currently supported by Texas Instruments, Inc at Germantown, Maryland.
var germanTownArch = ["C54", "C55", "C55_large", "C64", "C64_big_endian", "C64Plus", "C64Plus_big_endian"];
var unSupportedA = new Array();
for each (var candi in archArr){
	var illegal = 1;
	for each (var legal in germanTownArch){
		if(candi==legal){
			illegal = 0;
		}
	}
	if(illegal==1){
		unSupportedA.push(candi);
	}
}

if(missingPkgs.length!=0){
	if(unSupportedA.length!=0){
		print("\n\n\nArchitectures supported in Germantown:-\n\t"+germanTownArch.join("\n\t")+"\n\n\n");	
		throw new Error("Problem specifying arguments:-\nThe following packages could NOT be found\n"+missingPkgs.join(", ")+"\n"+
						"The following architectures are NOT supported in Germantown\n"+unSupportedA.join(", ")+"\n");
	} else{
		throw new Error("Problem specifying arguments:-\nThe following packages could NOT be found\n"+missingPkgs.join(", ")+"\n");
	}
	
} else {
	if(unSupportedA.length!=0){
		print("\n\n\nArchitectures supported in Germantown:-\n\t"+germanTownArch.join("\n\t")+"\n\n\n");	
		throw new Error("Problem specifying arguments:-\n"+
						"The following architectures are NOT supported in Germantown\n"+unSupportedA.join(", ")+"\n");
	}
}
return [pkgPathArr, archArr, optArr];
}