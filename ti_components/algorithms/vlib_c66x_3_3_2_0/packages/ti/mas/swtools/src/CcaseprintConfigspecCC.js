/******************************************************************************
 * FUNCTION PURPOSE: Take (as a parameter) a file created for configspec.clearcase and populate it with all the information gathered so far.
 ******************************************************************************
 * DESCRIPTION: 
  *	It calls openUpFile function to set up the ASCII file where configspec.clearcase contents will be written to.
 *	It writes the information gathered so far into configspec.clearcase file in a formatted way. 
 *	The information gathered so far is also passed into this function as parameter values. 
 *	It uses readVersion and findVOB functions to display the version and vob information in configspec.clearcase.
 *	NOTE: if the info{name, version, vob} about packages considered here does NOT match(is inconsistent with) their info specified 
 *	in the ME section of their own configspec.clearcase, this function stops short of writing the current ConfigSpec.ClearCase file.
 *	Instead, it reports an error on the command window telling user to go (re)generate configspec.clearcase files
 *	of other packages to get rid of this inconsistency of information in other CSCC files(probably caused by manual editing)
 *  void printConfigspecCC(
 *    string	formaArgs	-name of Package of interest or "" if curDir is pkgOfInt
 *    string	MEname	-name of package of interest.
 *    String[]	Content_DEP	-array containing all the dependent packages of the package of interest.
 *    String[]	Content_INTERNAL	-array containing all the packages required internally by the package of interest.
 *    String[]	Content_TST)	-array containing all the unit test packages of the package of interest. 
 *****************************************************************************/
function printConfigspecCC(formaArgs, MEname, Content_DEP, Content_INTERNAL, Content_TST){
//Before writing, we should gather Version and VOB information and pack it all in a hash table.
//While doing so, we can check if Version of Pkgs is consistent (same) with their Version specified in ME portion of their own CSCC files.
//If there is inconsistency, this configspec.clearcase is NOT written; instead, error messages are printed prompting regeneration of other CSCC files.
var csccTable = {};
var csccTitles = ["ME", "DEP", "INTERNAL", "TST"];
var csccContents = [[MEname], Content_DEP, Content_INTERNAL, Content_TST];
var inconsistaBuffer = new Array(); //list of inconsistancies are stored here for later printing
for (var n=0; n<csccTitles.length; n++){
	csccTable[csccTitles[n]] = new Array();
	for each (var pName in csccContents[n]){
		var pVer = readVersion(pName);
		var pVob = findVOB(pName);
		
		if(pName!=MEname){//because, we are about to write ME portion of MEname CSCC file... 	
			var hashAndFlag = ccParser(pName, ""); //csccInconsista global var. changes its value only below; pRoot is "" b/c current directory is the package root
			var ccHashOfpName = hashAndFlag[0];
			var legalityOfpName = hashAndFlag[1]; //is 0 if cscc has legal syntax; 1 if has illegal syntax; -1 if cscc of pName couldn't be found(read)
			if(ccHashOfpName["ME"]==undefined){//here legalityOfpName can only be -1 or 0; b/c, if legal it would have Begin_ME-Begin_DEP
				if(legalityOfpName==0){
					csccInconsista = 1; 
					inconsistaBuffer.push("Correct Info:-\t\t"+pName+"\t"+pVer+"\t"+pVob+"\t"+"\n"+
					"ME of CSCC:-"+" of "+pName+" does NOT have a Begin_ME-End_ME portion with correct syntax.");				
				} else if(legalityOfpName==-1){//the problem is with pName or with access to its cscc file; so force users to look at this cscc
					csccInconsista = 1; 
					inconsistaBuffer.push(pName+"'s configspec.clearcase could NOT be read; Please, inspect & regenerate it!");					
				}
			} else if(ccHashOfpName["ME"].length==0){
				csccInconsista = 1;
				inconsistaBuffer.push("Correct Info:-\t\t"+pName+"\t"+pVer+"\t"+pVob+"\t"+"\n"+
				"ME of CSCC:-"+" of "+pName+" has EMPTY ME portion.");
			} else if(pName==ccHashOfpName["ME"][0][0] && pVer==ccHashOfpName["ME"][0][1] && pVob==ccHashOfpName["ME"][0][2]){
				//No {name, version, or vob}  inconsistency b/n ME portion (of CSCC of pName) & its path name or Version.xdc
			} else {
				csccInconsista = 1; 
				inconsistaBuffer.push("{"+
					(pName!=ccHashOfpName["ME"][0][0]? "Package Name, ":"")+
					(pVer!=ccHashOfpName["ME"][0][1]? "v.r.x.p, ":"")+
					(pVob!=ccHashOfpName["ME"][0][2]? "VOB, ":"")+"} information of "+pName+" is wrong!\n"+											
					"Correct Info:-\t\t"+pName+"\t"+pVer+"\t"+pVob+"\t"+"\n"+
					"ME of CSCC:-\t\t"+ccHashOfpName["ME"][0][0]+"\t"+ccHashOfpName["ME"][0][1]+"\t"+
					ccHashOfpName["ME"][0][2]+"\t"+"\n");							
			}
		}		
		csccTable[csccTitles[n]].push([pName, pVer, pVob]);
	}
}

if(csccInconsista==1){
	print("\n\n\n"+"@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@");
	print("***	Inconsistent configspec.clearcase is Detected:-	***\n");
	print("The following problems are found in the ME portion of configspec.clearcase of the following packages:-");	
	print("- - - - - - - - - - - - - - - - - - - - - - - - -");
	for(var row=0; row<inconsistaBuffer.length; row++){
		print(inconsistaBuffer[row]);
	}
	print("- - - - - - - - - - - - - - - - - - - - - - - - -");
	print("\n#######");
	print("The configspec.clearcase of all the packages listed above MUST BE generated using Ccase.js first!");
	print("#######\n");
	print("......therefore, CONFIGSPEC.CLEARCASE FILE IS NOT CREATED.");
	print("@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"+"\n\n\n");
} else {

	//Open configspec.clearcase and write to it.
	 if(verbose==1){verboseCtr++;print(verboseCtr+":-\tAccessing configspec.clearcase file for writing...");}
	var fileNameUsed = "configspec.clearcase";
	var configspecCC = openUpFile(formaArgs, fileNameUsed, "w", "");
	if(configspecCC==undefined){
		print("configspec.clearcase is NOT written! Because, it could not be accessed for writing in "+
		(formaArgs=="" ? "the current package directory" : formaArgs));
	} else {
	if(verbose==1){verboseCtr++;print(verboseCtr+":-\tWriting to configspec.clearcase file...");}
		var startedWriting = configspecCC.writeLine("# This is my name and my current version number");
		if(startedWriting == true){
			print(fileNameUsed + " file is succesfully created.");
		}

		configspecCC.writeLine("\n"+"Begin_ME");
		configspecCC.writeLine("  " +csccTable.ME[0][0] + "	" + csccTable.ME[0][1] + "  " + csccTable.ME[0][2]);
		configspecCC.writeLine("End_ME"+"\n");

		configspecCC.writeLine("# These are the packages I need for proper operation within the system"+"\n");
		configspecCC.writeLine(csccTable.DEP.length==0 ? "#Begin_DEP": "Begin_DEP");
		if(csccTable.DEP.length==0){
		configspecCC.writeLine("#  "+"<pname1> <M1>.<m1>.<p1>.<b1>");
		configspecCC.writeLine("#  "+"<pname2> <M2>.<m2>.<p2>.<b2>");
		configspecCC.writeLine("#  ...");
		configspecCC.writeLine("#  "+"<pnameN> <MN>.<mN>.<pN>.<bN>");
		} else{
			for (var n=0; n<csccTable.DEP.length; n++){
				configspecCC.writeLine("  " +csccTable.DEP[n][0] + "	" + csccTable.DEP[n][1] + "  "+ csccTable.DEP[n][2]);
			}
		}
		configspecCC.writeLine(csccTable.DEP.length==0 ? "#End_DEP" : "End_DEP");

		configspecCC.writeLine("\n"+"# These are the packages I need internally"+"\n");
		configspecCC.writeLine(csccTable.INTERNAL.length==0 ? "#Begin_INTERNAL": "Begin_INTERNAL");
		if(csccTable.INTERNAL.length==0){
		configspecCC.writeLine("#  "+"<pname1> <M1>.<m1>.<p1>.<b1>");
		configspecCC.writeLine("#  "+"<pname2> <M2>.<m2>.<p2>.<b2>");
		configspecCC.writeLine("#  ...");
		configspecCC.writeLine("#  "+"<pnameN> <MN>.<mN>.<pN>.<bN>");
		} else{
			for (var n=0; n<csccTable.INTERNAL.length; n++){
				configspecCC.writeLine("  " +csccTable.INTERNAL[n][0] + "	" + csccTable.INTERNAL[n][1] + "  " + csccTable.INTERNAL[n][2]);
			}
		}
		configspecCC.writeLine(csccTable.INTERNAL.length==0 ? "#End_INTERNAL": "End_INTERNAL");

		configspecCC.writeLine("\n"+"# These are the additional packages I need for unit testing"+"\n");
		configspecCC.writeLine(csccTable.TST.length==0 ? "#Begin_TST": "Begin_TST");
		if(csccTable.TST.length==0){
			configspecCC.writeLine("#  "+ "<pnameT> <MT>.<mT>.<pT>.<bT>");
		} else{
			for (var n=0; n<csccTable.TST.length; n++){
				configspecCC.writeLine("  " +csccTable.TST[n][0] + "	" + csccTable.TST[n][1] + "  " + csccTable.TST[n][2]);
			}
		}
		configspecCC.writeLine(csccTable.TST.length==0 ? "#End_TST": "End_TST");
		configspecCC.writeLine("\n"+"# nothing past this point");
		configspecCC.close();	//Flushs the java.io.PrintStream and closes the underlying java.io.FileOutPutStream.		
	}
}
}