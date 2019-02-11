/******************************************************************************
 * FUNCTION PURPOSE: Load package.ext.xml files of either a built package or its test package.
 ******************************************************************************
 * DESCRIPTION: 
 *	It loads package.ext.xml file of either a built package (if xdcXmlType=="ofPackage"). 
 *	It loads package.ext.xml file of test package of a built package (if xdcXmlType=="ofTest").
 *	It returns xml tree which is of type "xml".
 *	It returns undefined if xml file could not be loaded.
 *  xml readXdcXml (
 *    string	pkgConsidered	-name of a package being explored (could be package of interest) (its sub-strings should be delimited by / not .)
 *    string	xdcXmlType)	-this is either "ofPackage" or "ofTest" depending on the 'type of package' explored.
 *****************************************************************************/
function readXdcXml(pkgConsidered, xdcXmlType){
var xmlTree;
try{
	if (pkgConsidered==""){
		//If pkgConsidered is the same as the current working directory,
		if(xdcXmlType=="ofPackage"){
			xmlTree= xdc.loadXML("./package/package.ext.xml");
		} else if (xdcXmlType=="ofTest"){
			xmlTree= xdc.loadXML("./test/package/package.ext.xml");
		}  else {
			throw new Error("Error internal to Ccase.js script:-xdcXmlType of readXdcXml can only be ofPackage or ofTest.");
		}
	} else {
		//If pkgConsidered is NOT the same as the current working directory,
		var pathOfPkgConsi = findFilePlus(pkgConsidered);
		if(pathOfPkgConsi!=null){
			if(xdcXmlType=="ofPackage"){
				xmlTree= xdc.loadXML(pathOfPkgConsi + "/package/package.ext.xml");
			} else if (xdcXmlType=="ofTest"){
				xmlTree= xdc.loadXML(pathOfPkgConsi + "/test/package/package.ext.xml");
			} else {
				throw new Error("Error internal to Ccase.js script:- xdcXmlType of readXdcXml can only be ofPackage or ofTest.");
			}
		} else if(pathOfPkgConsi==null){//double checking: becuase this must have been checked by formatArguments ...
			throw new Error(pathOfPkgConsi +"could not be found!");
		}
	}
} catch (ex) {
	if(xdcXmlType=="ofPackage"){
		warningBuffer.push("Trying to read /package/package.ext.xml of"+(pkgConsidered=="" ? "current (package) directory": pkgConsidered)+"\n"+ex);
	} else if(xdcXmlType=="ofTest"){
		warningBuffer.push("Ignore this specific warning IF you know that "+(pkgConsidered=="" ? "the current (package) directory": pkgConsidered)+
		" does NOT have a TEST package\n"+
		"Trying to read (for TST) /test/package/package.ext.xml of"+(pkgConsidered=="" ? "the current (package) directory": pkgConsidered)+"\n"+ex);
	}
}
return xmlTree;	
}