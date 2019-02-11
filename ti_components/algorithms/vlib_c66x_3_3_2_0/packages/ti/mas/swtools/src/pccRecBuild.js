/******************************************************************************
 * FUNCTION PURPOSE: Recursively build the contents of Package ClearCase file.
 ******************************************************************************
 * DESCRIPTION: 
 *	It calls ccParse with pkgToParse given; it saves the return value in ccHash.
 *	If firstCall=1, it copies all of ccHash into pccHash. (Unless dontCopy is 1)
 *	If firstCall=0, it copies only relevant parts of ccHash to pccHash (i.e. DEP, INTERNAL) (Unless dontCopy is 1)
 *	If firstCall=1, it goes through DEP, INTERNAL & TST set of ccHash (pkgOfInt) & picks the package names.
 *	if firstCall=0, it goes through DEP, & INTERNAL set of ccHash (current pkg) & picks the package names.
 *	It uses these package names as the 3rd parameter as it calls itself recursively.
 *	During the recursive calls, firstCall is 0, and pccHash is still used as the 2nd parameter.
 *	pccHash floats around throughout the layers of recursive calls gathering more and 
 *	more information (because of copying from ccHash to pccHash).
 *	It returns a hash table pccHash, which is originally taken in as a parameter, after enriching with info it recursively AND
 *	the inconsiBuff array that has recursively collected reports of all inconsistencies in CSCC files recursively visited. 
 *  HashTable	pccRecBuild (
 *    string	firstCall	-is 1 if this is not a recursive call, 0 otherwise
 *    HashTable    pccHash    -cantains the content of Package ClearCase that is being built recursively; is empty for 1st call
 *    string	pkgToParse	-name of Pkg whose configspec.clearcase will be parsed; for 1st call, it is the PkgOfInterest.
 *    String    dontCopy	-is 1 only if the pkgToParse is "descendent" of a pkg that is listed in TST of any package other than pkgOfInterest
 *    string[]	inconsiBuff	-contains list of inconsistencies in the ME portion of CSCC files explored recursively
 *    string	parent	-is formaArgs for 1st call; is the pkgToParse of the previous call for all other recursive calls.
 *    String[]	userFlags	-is an array of options specified by user: 
	  userFlags[0]    -is 0 (by default) when user wants termination in case of inconsistency induced by problems in loading Version.xdc modules
			   -is 1 if user does not want to force termination in case of inconsistency induced *solely* by missing Version.xdc; instead a table of warnings is displayed
 *    string	pRoot	-is the root of the pkgToParse; it consists of drive letter:\ & vob name. It helps us locate the configuration.specification file that we want to parse using ccParser
			It has "" value if root is current Directory.
 *	  history  - Maintains history to avoid recursive build of the packages done in the past)
 *****************************************************************************/
function pccRecBuild(firstCall, pccHash, pkgToParse, dontCopy, inconsiBuff, parent, userFlags, pRoot, history){
//ASK BOGDAN..add pkgToParse's VRXP & vob as parameter & check if equals ME's vrxp&vob?..if so, what's the point of prunning by latest ver...all will have the same ver right?
/* If pccRecBuild was called by pccGen.js */  
  if(pRoot=="")
  {
      for(n=0;n<history.length;n++)
      {
	     /* if this package is already parsed simply return*/
		 if(history[n]== pkgToParse)
		   {
		      return [pccHash, inconsiBuff];
           }
      }
      /* Push the current package in history buffer */
	  history.push(pkgToParse.replace(/\//g, "\.")); 
   }

var ccHaAndFla = ccParser(pkgToParse, pRoot);
var ccHash = ccHaAndFla[0];
var legalOfpkgToP = ccHaAndFla[1]; //is 0 if cscc has legal syntax; 1 if has illegal syntax; -1 if cscc of pkgNToParse couldn't be found(read)
if(firstCall==1 && dontCopy==0){//Note: during 1st call, dontCopy is always 0
	pccHash=mergeToPcc(ccHash, pccHash, ["ME", "DEP", "INTERNAL", "TST"]);
}else if(dontCopy==0 && firstCall==0){
	pccHash=mergeToPcc(ccHash, pccHash, ["DEP", "INTERNAL"]);//Gather DEP & INTERNAL  info recursively.	
}
//Format pkgToParse as a package name; if it is empty, 
var pkgNToParse = pkgToParse.replace(/\//g, "\.");
if(pkgNToParse == "" && firstCall==1){
	pkgNToParse = ccHash["ME"][0][0]; //because this was read from configspec.clearcase in CurDir; 
}

//Check the consistency of information in the ME portion of configspec.clearcase of the package being visited at this stage of recursion.
var corrVer = readVersion(pkgNToParse); //corrVer/Vob is for correct ver/vob
var corrVob;
if(pRoot==""){//this means that pccRecBuild was called by pccGen.js (development)
	corrVob = findVOB(pkgNToParse);
} else {//this means pccRecBuild was called by iCcase.js; in this case, users gave us the full path to the package, hence, we have the VOB information.
	corrVob = pRoot.split("\\")[1].toString(); //b/c pRoot has the following structure: <D:>\<vob>
}
//@
var ignoVerIfNoMod = 0;
if(corrVer=="?.?.?.?"){//note that this string is one of the return types of readVersion function		
	print("\nVersion.xdc of "+pkgNToParse+" could NOT be loaded.\n");
	if(userFlags[0]==1){//only warning
		ignoVerIfNoMod = 1;
	} else if(userFlags[0]==0){//warning + inconsistency error that results in termination
		ignoVerIfNoMod = 0;				
	}
}
if(ccHash["ME"]==undefined){//here legalOfpkgToP can only be -1 or 0; b/c, if legal it would have Begin_ME-Begin_DEP
	if(legalOfpkgToP==0){
		csccInconsista = 1; 
		inconsiBuff.push(["Correct Info:-\t\t"+pkgNToParse+"\t"+corrVer+"\t"+corrVob+"\t"+"\n"+
		"ME of CSCC:-"+" of "+pkgNToParse+" does NOT have a Begin_ME-End_ME portion with correct syntax.", pkgNToParse]);				
	} else if(legalOfpkgToP==-1){//the problem is with spelling of pkgNToParse or with access to its cscc file; so force users to look at this cscc
		csccInconsista = 1;
		inconsiBuff.push(["\n"+pkgNToParse+" is listed in "+parent+"'s configspec.clearcase;\nBUT "+
					pkgNToParse+"'s configspec.clearcase could NOT be found & read;\nPlease regenerate configspec.clearcase of:- "+
					parent+" and "+pkgNToParse+"(if it's actually a package\n", parent]); //list this warning by parent because that's probably the real CSCC that needs a fix
	}
} else if(ccHash["ME"].length==0){
	csccInconsista = 1;
	inconsiBuff.push(["Correct Info:-\t\t"+pkgNToParse+"\t"+corrVer+"\t"+corrVob+"\t"+"\n"+
	"ME of CSCC:-"+" of "+pkgNToParse+" has EMPTY ME portion.", pkgNToParse]);
} else if(pkgNToParse==ccHash["ME"][0][0] && corrVer==ccHash["ME"][0][1] && corrVob==ccHash["ME"][0][2]){
	//No {name, version, or vob}  inconsistency b/n ME portion (of CSCC of pkgNToParse) & its path name or Version.xdc
} else {
	if(ignoVerIfNoMod==0){//user wants termination in cases when Version.xdc could not be loaded for some packages
		csccInconsista = 1; 
		inconsiBuff.push(["{"+
			(pkgNToParse!=ccHash["ME"][0][0]? "Package Name, ":"")+
			(corrVer!=ccHash["ME"][0][1]? "v.r.x.p, ":"")+
			(corrVob!=ccHash["ME"][0][2]? "VOB, ":"")+"} information of "+pkgNToParse+" is wrong!\n"+
			(corrVer=="?.?.?.?" && "?.?.?.?"!=ccHash["ME"][0][1] ?
			"..Particularly, "+ccHash["ME"][0][1]+" could not be verified as v.r.x.p. of "+pkgNToParse+";\nbecause "+pkgNToParse+
				"'s Version.xdc could NOT be loaded\n":"")+
			"Correct Info:-\t\t"+pkgNToParse+"\t"+corrVer+"\t"+corrVob+"\t"+"\n"+
			"ME of CSCC:-\t\t"+ccHash["ME"][0][0]+"\t"+ccHash["ME"][0][1]+"\t"+
			ccHash["ME"][0][2]+"\t"+"\n", pkgNToParse]);							
	} else if(ignoVerIfNoMod==1){//user does not want to enforce termination even though Version.xdc of some packages (at 2nd or more level of dependency) can't be loaded
		if(pkgNToParse!=ccHash["ME"][0][0] || corrVob!=ccHash["ME"][0][2]){//declare inconsistancy only if it is b/c of name/vob inconsistancy
			csccInconsista = 1; 
			inconsiBuff.push(["{"+
				(pkgNToParse!=ccHash["ME"][0][0]? "Package Name, ":"")+
				(corrVob!=ccHash["ME"][0][2]? "VOB, ":"")+"} information of "+pkgNToParse+" is wrong!\n"+
				"..and.. "+ccHash["ME"][0][1]+" could not be verified as v.r.x.p. of "+pkgNToParse+";\nbecause "+pkgNToParse+
				"'s Version.xdc could NOT be loaded\n"+
				"Correct Info:-\t\t"+pkgNToParse+"\t"+corrVer+"\t"+corrVob+"\t"+"\n"+
				"ME of CSCC:-\t\t"+ccHash["ME"][0][0]+"\t"+ccHash["ME"][0][1]+"\t"+
				ccHash["ME"][0][2]+"\t"+"\n", pkgNToParse]);		
		}
	}
}//@			
//Also check that the information in the ME section of this package matches the info listed in its "parent package in the tree of dependency that is being explored recursively."
//ASK BOGDAN.... if we do this there is nothing to prune.... each package 'instance' will have exactly the same vob and vrxp info.
//well I guess we just don't need to do this.



var recVisitList = new Array();
//# of pkgs at the end of recVisitList, which should be visited NOT-with-the-#intent#-to-copy-their DEP and INT set.
//But, with the #intent# of checking the consistency of information in the ME portion of their configspec.clearcase file.
var numNotToCopy=0; 
if(ccHash["DEP"]!=undefined){
	recVisitList = recVisitList.concat(ccHash["DEP"]);
}else{//This is #part# of the condition for the recurssion to bottom out.(i.e. current pkg being explored has empty DEP set)
}
if(ccHash["INTERNAL"]!=undefined){
	recVisitList = recVisitList.concat(ccHash["INTERNAL"]);
}else{//This is #part# of the condition for the recurssion to bottom out.(i.e. current pkg being explored has empty INTERNAL set)
}
if(ccHash["TST"]!=undefined){
	recVisitList = recVisitList.concat(ccHash["TST"]);		
	if(firstCall==1){
		//we visit members of TST of PkgOfInterest with-the-intent of copying their DEP & INT set.
		//Therefore, we should leave numNotToCopy to stay at 0. In that way we call pccRecBuild on this packages with dontCopy=0 (not 1).
	} else if(firstCall==0){
		//this will help us in calling pccRecBuild with the appropriate value of dontCopy	
		numNotToCopy = ccHash["TST"].length; 
	}
}else{//This is #part# of the condition for the recurssion to bottom out.(i.e. pkgOfInterest has empty TST set)
}

for (var n=0; n<recVisitList.length;n++){//explore DEP, INT, & TST if this is 1st call; otherwise, explore DEP & INT only.
	if(n<(recVisitList.length-numNotToCopy)){
		recRet = pccRecBuild(0, pccHash, recVisitList[n][0], dontCopy, inconsiBuff, pkgNToParse, userFlags, pRoot, history); //pkgNToParse becomes parent
		pccHash = recRet[0]; inconsiBuff = recRet[1];
	} else {//here is the only time dontCopy would be 1. Once this recurssion collapses, it will go back to being what it is right now (most probably 0)
		recRet = pccRecBuild(0, pccHash, recVisitList[n][0], 1, inconsiBuff, pkgNToParse, userFlags, pRoot, history); //pkgNToParse becomes parent
		pccHash = recRet[0]; inconsiBuff = recRet[1];
	}
}
return [pccHash, inconsiBuff];
}