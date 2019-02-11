/******************************************************************************
 * FUNCTION PURPOSE: Return VOB of the specified package using table built by findVisiblePkgRepo function; return "" if no match is found.
 ******************************************************************************
 * DESCRIPTION: 
 *	It uses the visiblePkgRepo 2D array built by findVisiblePkgRepo function, which is called here. 
 *	visiblePkgRepo contains pairs of package name & corresponding VOB.
 *	It looks up the table using the package name to find the corresponding VOB.
 *	If package is not found in this list (that is a function the current System_Package_Path viewed 
 *	from within the current working directory), findFilePlus() function is utilized to look for the
 *	package (pkgName) in the directory structure surrounding the current directory; then, the VOB 
 * 	information is readily extracted.
 *	The VOB is returned.
 *	If the VOB is can't be determined (because the package can't be found) "????" is returned.
 *  string	findVOB(
 *    string	pkgName	-name of the package whose VOB is needed).
 *****************************************************************************/
function findVOB(pkgName){
//We need the following to use findVOB(some_pkg_name) function.
var visiblePkgRepo = findVisiblePkgRepo();
pkgName = pkgName.toString().replace(/\//g, "\."); //Allow flexibility in format of inputs
var foundVob="";
//Look for pkgName in "visiblePkgRepo" to find its corresponding repository
//"visiblePkgRepo" is defined and constructed inside findVisiblePkgRepo()
for each (pkgVobPair in visiblePkgRepo){
	if(pkgVobPair[0]==pkgName){
		foundVob = pkgVobPair[1];
	}
}
//Format the full repository name (i.e. C:\repository..) by removing the drive letter
//the colon and the backward (forward in Unix) slash.
if(foundVob.toString().search(/(^[A-Z]\:\\)([\S,\s]{1,})/) == 0) {
	var matchRes = foundVob.toString().match(/(^[A-Z]\:\\)([\S,\s]{1,})/);
	if(matchRes!=null){
	    foundVob = matchRes[2];
	    var temp = foundVob.toString().split("\\"); 
	    if(temp.length > 1)
		{
		  foundVob=temp[temp.length-1];
		}
	}
}
/* Linux  */
var temp = foundVob.toString().split("/"); 
if(temp.length > 1)
{
  foundVob=temp[temp.length-1];
}




if(foundVob==""){
	//So far we looked for the package name withn the System_Package_Path, which is 
	//{XDCPATH, XDCROOT, & ^-current PACKAGE directory (WHICH MAY BE non-existent if current working directory is not a built package)}.
	//Now, look for the package across the directory structure using the findFilePlus() function.
	//The motivation is to make sure that the VOB is found when the current working directory
	var pkgActuPath = findFilePlus(pkgName.toString().replace(/\./g, "\/"));
	if(pkgActuPath==null){//package is not found	
		foundVob="????";
	} else { //process pkgActuPath to determine the VOB information that is embeded in it
		pkgActuPath = pkgActuPath.replace(/\//g, "\\");
		if(pkgActuPath.toString().search(/(^[A-Z]\:\\)([^\\]{1,})/) == 0) {
			var matchRes2 = pkgActuPath.toString().match(/(^[A-Z]\:\\)([^\\]{1,})/);
			if(matchRes2!=null){
				foundVob = matchRes2[2]; //extracted from non-null result of findFilePlus
			}
		} else {	
			foundVob = "????";
		}		
	}
}
return foundVob;
}