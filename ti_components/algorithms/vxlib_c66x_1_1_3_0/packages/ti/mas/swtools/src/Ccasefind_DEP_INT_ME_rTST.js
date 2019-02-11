/******************************************************************************
 * FUNCTION PURPOSE: Compute ME, DEP and INTERNAL portions; find raw data used to computeTST.
 ******************************************************************************
 * DESCRIPTION: 
 *	Each call returns an updated information about the contents of configspec.clearcase. 
 *	It finds ME portion and it computes DEP and INTERNAL portions.
 *	It also computes the raw data needed to compute the TST portion.
 *	Returns a 2D array containing ME, DEP, INTERNAL and raw data for TST.
 *  String[][] find_DEP_INT_ME_rTST(
 *    string	formaArgs	-name of the "package of interest" or "" (depending on original arguments)
 *    String[][]	Content_DEP_INT_ME_rTST	-data structure holding information about configspec.clearcase 
 *    String[]	dontPutInDep)	-list of packages that should be ignored while constructing configspec.clearcase
 *****************************************************************************/
function find_DEP_INT_ME_rTST(formaArgs, Content_DEP_INT_ME_rTST, dontPutInDep){

 if(verbose==1){verboseCtr++;print(verboseCtr+":-\t"+formaArgs+" (package of interest)...Loading package.ext.xml");}
var slashFormaArgs = formaArgs;
slashFormaArgs = slashFormaArgs.toString().replace(/\./g, "\/");
var xmlTreeOfPkg=readXdcXml(slashFormaArgs, "ofPackage"); //Read package.ext.xml of current package of interest at this level of recursion
if(xmlTreeOfPkg==undefined){
	print("Construction of configspec.clearcase is TERMINATED! ");
	print("Because, package.ext.xml file of "+formaArgs+" (package of interest) could not be loaded.");
	print("Please make sure that "+formaArgs+" (package of interest) is built and its package.ext.xml is accessible.");
	xmlNotFound = 1; //This is the ONLY place where xmlNotFound could change value from 0.
}
if(xmlNotFound==1){//Return the empty data structure; then, Ccase.js returns pre-maturely (but robustely)  as well.
	return Content_DEP_INT_ME_rTST;
} //From here on, we are sure that xmlTreeOfPkg is defined and hence we can parse it.
//Read the "curME" (i.e. currentME) package & the package names currently IMPOrted in package.ext.xml
 if(verbose==1){verboseCtr++;print(verboseCtr+":-\t"+"Extracting information from package.ext.xml...");}
var MEandIMPO = parseXdcXml(xmlTreeOfPkg, dontPutInDep); 
var MEname = Content_DEP_INT_ME_rTST[2] = MEandIMPO[0];
var ImpoNamesPkgXml = Content_DEP_INT_ME_rTST[3] = MEandIMPO[1];  //Will be used by tstConstructor()...


 if(verbose==1){verboseCtr++;print(verboseCtr+":-\t"+MEname+
"...Classifying its DEP and INTERNAL packages");}
//Read through the package names & classify them as DEP and INTERNAL
for each (var i in ImpoNamesPkgXml){
	var candidateArr = i.split("."); 
	//CLASSIFICATION RULES
	//package is INTERNAL if prefixed by * (fact confirmed by David Russo)
	//package is ME if its name matches MEname found above.
	//package is DEP if it is neither ME nor INTERNAL and is found in import section of package.ext.xml of Package & is well defined
	var isCandME=0;
	if(i==MEname){
		isCandME=1;
	}	
	var isCandINTERNAL=0;
	//Use Regular Expression rules to check if variable "i" starts with an asterik.
	if(i.toString().search(/(^\*)([\S,\s]{1,})/)==0){
		isCandINTERNAL = 1;
	}

	if(isCandME){
		//This is the ME package; we already have its name saved in MEname
	} else if(!isCandINTERNAL && !isCandME && (i!=undefined)) {
		Content_DEP_INT_ME_rTST[0].push(i);
	} else if(isCandINTERNAL){		
		//Manipulate "i" to get rid of the * prefix before printing.		
		var matchReturn = i.toString().match( /(^\*)([\S,\s]{1,})/);
		if (matchReturn!=null) {
			//The 2nd matched parenthesized sub-expression of RegEx
			//in the above RegEx (i.e. ([\S,\s]{1,}) was stored in matchReturn[2]
			Content_DEP_INT_ME_rTST[1].push(matchReturn[2]);
		}
	}		
}
if(verbose==1){verboseCtr++;print();print(verboseCtr+":-\t"+"DEP set of "+
MEname+" is:-\t{"+Content_DEP_INT_ME_rTST[0]+"}");}
if(verbose==1){verboseCtr++;print();print(verboseCtr+":-\t"+"INTERNAL set of "+
MEname+" is:-\t{"+Content_DEP_INT_ME_rTST[1]+"}");}

return Content_DEP_INT_ME_rTST;
}