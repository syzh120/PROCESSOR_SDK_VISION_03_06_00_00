/******************************************************************************
 * FUNCTION PURPOSE: Extract the name of the package & all other package names imported in the package.ext.xml tree provided.
 *				 Also, check that the compatibility key of these packages stated in the XML files MATCHES what is defined in thier package.xdc files!
 ******************************************************************************
 * DESCRIPTION: 
 *	It sets default xml namespace declarations of the xml object passed in order to enable parsing of XML using E4X. 
 *	It extracts the name of the package that this xml file is associated with (var PN contains this info).
 *	It extracts the names of packages that are listed in the 'import' sub-tree of this xml object(var impoNamesXdcXml contains this info).
 *	It checks that the compatibility key of these packages stated in the XML files MATCHES what is defined in thier package.xdc files!
 *	In case of discrepancy, it sets the compaKeyMisMatch global boolean to 1, and displays warnings that will help fix the discrepancy.
 *	Return value: It bundles string "PN" & array(of strings)  "impoNamesArr" into another array and returns this bundle (array).
 *	DISCLAIMER:- This is a function which is dependent on the contents of the internal file package.ext.xml.
 *	The 'grammar' (format)  of the file package.ext.xml is unlikely to change in future XDC releases; but, it could change! 
 *	In that case, this function should be reviewed!
 *    String[][] parseXdcXml(
 *    xml	pXmlTree	-This is an xml object that is to be parsed to extract some information from it.
 *    String[]	dontPutInDep	-list of packages in xml files that should be ignored)
 *****************************************************************************/
function parseXdcXml(pXmlTree, dontPutInDep){
var PN = new String(pXmlTree["package"].@name.toXMLString()).toString();	//Read the package name from the xml tree.
	
//Requirement:- Default namespace should be set to the value of "xmlns" variable in the package.ext.xml if 
//"xmlns" is non-empty. If "xmlns" is empty, E4X parsing can be achieved with no other modification of default xmlns.
//Fact:- The "xmlns" of package.ext.xml is almost always "xdc/services/spec".
//But, we do not want to hardcode this information; instead, we use RegEx to get the value of "xmlns" of
//package.ext.xml, then we use that value to set the default XML namespace in this JavaScript code.

//Thus...Get ready TO Read all the package names "imported" in package.ext.xml
var stringPXmlTree = pXmlTree.toXMLString().toString();
/*var xmlnsRead = stringPXmlTree.match(/(xmlns=")([^"]{0,})(")/)[2]; //want 2nd parenthesized part
if (xmlnsRead!=null && xmlnsRead!=""){
	if(xmlnsRead == "xdc/services/spec"){
		default xml namespace = xmlnsRead;
	} else { 
		//This case is out of the ordinary; but, continue after reporting it.
		warningBuffer.push("NOTE: The XML namespace (xmlns) of package.ext.xml is not 'xdc/services/spec'"+
		"\n"+"This Ccase.js script may be at RISK of being INCOMPATIBLE with the latest XDC tools...");
		default xml namespace = xmlnsRead;
	}
} else {
	//No xml namespace is specified or it was ""; so, no need to reset the default value!
}*/

var path = environment["xdc.path"].split(";");
var browser = new Packages.xdc.services.spec.BrowserSession(path);


var pkg = browser.findPkg(PN);


var requires = pkg.getRequires().toArray(); /* convert Java list to an array for easier use below */

var tempArray = new Array(); 

for (var i = 0; i < requires.length; i++) {

    var req = requires[i];
    var split_temp = req.getText().toString().split("\\{");
    tempArray[split_temp[0]]=split_temp[1];
}


//MOTIVATION to setting compaKeyMisMatch = 1 
//The compatibility key of all these packages found here has an associated compatibility key in package.ext.xml files.
//(Note: this compatibility key is actually always erroneously labeled as "version" in these XML files we parse. )
//This compatibility key was originally SPECIFIED in the package.xdc of the package of interest under the label "requires ..."
//This information should match the DEFINED compatibility key of all these packages in their own package.xdc files!
var impoNamesArr = new Array();  //Make a fresh "non-xml" copy of all the Pkg names imported.
for (var m in tempArray){
	var toBeIgnored = 0;
	var mSt = m.toString();
	for each (var ignoListMember in dontPutInDep){
			if(mSt==ignoListMember){
			toBeIgnored = 1;					
		}
	}
	if(toBeIgnored==0){
		impoNamesArr.push(m);
	}
}

var pXmlTreeCopy = new XML(pXmlTree); //Read a clean copy to avoid any XML problems later.
for each (var nnn in impoNamesArr){
	var impNameCkX = tempArray[nnn];
	var impNameCk = new String(impNameCkX).toString();
	if(impNameCk!=""){
		var impName;
		//Check if the impName package starts with asterik (i.e. is internally required...if so remove asterik and make note of this action
		var internalRequired = 0;
		if(nnn.toString().search(/^\*/)==0){
			var copyNnn = new String(nnn).toString();
			var asterRemove = copyNnn.match( /(^\*)([\S,\s]{1,})/);		
			impName = new String(asterRemove[2]).toString();
			internalRequired = 1;
		} else { 
			impName = new String(nnn).toString();
		} 
		xdc.om.$$bind('$$genflg', 1);
		var ckPkgXdc = xdc.loadPackage(impName).$vers; //array containing C.Keys DEFINED in respective package.xdc file	

		if(ckPkgXdc==null || ckPkgXdc==undefined || ckPkgXdc.length<4){
		
			warningBuffer.push("Problem reading 4 Digit compatibility key of "+impName+" from its package.xdc file!");
		} else { 
			var ckPkgXdcForma = ckPkgXdc[0]; //this is the formated version
			for (var e=1; e<4; e++){ //because compatibility keys are formed by 4 numbers!
				ckPkgXdcForma = ckPkgXdcForma + ", " + ckPkgXdc[e]; 
			}
			if(impNameCk==ckPkgXdcForma){//Good news: Compa.Keys 'defined' & 'required' do match!
			} else {
				compaKeyMisMatch = 1;	//This is the only place where this global boolean can change its value.
				warningBuffer.push("\n"+"MISMATCH between Compatibility Key DEFINED in package.xdc of "+impName+
				" & Compatibility Key REQUIRED in package.xdc of "+PN+"!!!\n"+
				PN+" REQUIRES "+impName+" package with C.K. "+impNameCk+"\nBUT,\n"+impName+" DEFINES its C.K. as "+
				ckPkgXdcForma+" in its package.xdc file."+
				"\n\n####################################\n"+
				"AS A REMEDY TO THE ABOVE WARNING...\nYou can CUT-PASTE the following Defined compatibility "+
				"keys of "+impName+" TO the package.xdc of "+ PN+" (Package of interest)\n"+
				"requires "+ (internalRequired==0 ? " " : "internal ") +
				impName+"["+ckPkgXdcForma.replace(/[\s]/g,"")+"];\n  Please NOTE that YOU WILL keep on seeing this "+
				"message UNTIL you RE-BUILD package "+PN+
				";\n Because, the changes you've just made in package.xdc will be detected by this script only after re-build."+
				"\n####################################"+
				"\n OTHERWISE, consider using a different version of "+impName+" with a compatibility key "+impNameCk);					
			}		
		}
	}
}
return [PN ,impoNamesArr]
}