/******************************************************************************
 * FUNCTION PURPOSE: Construct the TST portion of configspec.clearcase.
 ******************************************************************************
 * DESCRIPTION: 
 *	It takes impoNamesPkgXml as parameter.
 *	It finds out names of packages imported in the package.ext.xml of "test sub-package" of the package of interest.
 *	It does a "set difference" computation on the above two sets to get the TST portion of configspec.clearcase.
 *	It returns the Content_TST list computed. 
 *  String[]  tstConstructor(
 *    string	formaArgs	-name of package of interest (its sub-strings are delimited by "/" and not by ".").
 *    string	MEname	-name of package of interest (its sub-strings are delimited by "." and not by "/").
 *    string	impoNamesPkgXml	-names of packages imported in package.ext.xml of the package of interest.
 *    String[]	dontPutInDep	-list of packages in xml files that should be ignored.)
 *****************************************************************************/
function tstConstructor(formaArgs, MEname, impoNamesPkgXml, dontPutInDep){
var Content_TST = [];
var tstCounter = 0;
var tstXmlTree=readXdcXml(formaArgs, "ofTest");
var nameOfPkgTst;	
var pkgsForTst;
if(tstXmlTree!=undefined){
	var TSTandIMPO = parseXdcXml(tstXmlTree, dontPutInDep);
	nameOfPkgTst = TSTandIMPO[0];
	pkgsForTst = TSTandIMPO[1];
}
//Evaluate <pkgsForTst - MEname> (or set TTT) 
//#without# 
//<impoNamesPkgXml> (or set PPP). (Set Theoretic)
//The result will be setDifference=Content_TST, and will be returned.
var setDifference = [];	
for each (tt in pkgsForTst){
	var ttIsInPPP = 0;
	for each (pp in impoNamesPkgXml){
		if(tt==pp){
			ttIsInPPP = 1;
			break;
			//break off this inner for loop, because we know by now 
			//that this tt should not be put in "setDifference" array.
		}
	}
	if(ttIsInPPP==0 && MEname!=tt){
		setDifference.push(tt);
	}
}
Content_TST = setDifference;
if(verbose==1){verboseCtr++;print();print(verboseCtr+":-\t"+"TST set of "+
MEname+" is:-\t{"+Content_TST+"}");}
return Content_TST;
}