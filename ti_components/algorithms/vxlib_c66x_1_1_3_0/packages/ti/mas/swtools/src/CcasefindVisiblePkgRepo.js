/******************************************************************************
 * FUNCTION PURPOSE: Return 2D array containing names of all visible packages and thier repositories. 
 ******************************************************************************
 * DESCRIPTION: 
 *	It takes advantage of the xdc.tools.path tool to get names of all visible packages and their repositories. 
 *	DISCLAIMER:- Thus, it is dependent on the functionality of xdc.tools.path tool, 
 *	which is assumed to remain invariant through releases of XDC tools. In case it changes, this function needs a review.
 *	It stores pairs of package name and repository in the visiblePkgRepo array.
 *	This function is designed as a helper function for findVOB function.
 *	It returns the visiblePkgRepo array.
 *  String[] findVisiblePkgRepo()
 *****************************************************************************/
function findVisiblePkgRepo(){
/***NOTE***/
//Until RTSC tools BUG is fixed, we have to use the following HACK
//xdc.$$make_om('cfg');  /* hack! only for xdc 2.94 access to Version modules */
xdc.om.$$bind('$$genflg', 1);

var toolsPathMod = xdc.module('xdc.tools.path.Main');
//The logic of the following code becomes apparent after running the
//command "xs xdc.tools.path" in the Command Line.
var allInfo = toolsPathMod.exec();
var arrayOfAllInfo = allInfo.split("\n\n");
var table = new Array(arrayOfAllInfo.length);
var tableCounter = 0;
for each (m in arrayOfAllInfo){
	var arrayOfPkgInfo = m.split("\n");
	//Save the Name of Package and its repository in "table"
	table[tableCounter] = new Array(2); //Each table cell contains a pair of package name & corresponding VOB
	//WARNING: The number of white spaces given to split below are
	//dependent on the source code of xdc.tools.path.Main. Don't alter the white space below.
	//Once again, trying xs xdc.tools.path in the Command line would explain this code.
	table[tableCounter][0] = arrayOfPkgInfo[0].split("      ")[1]; //package name
	table[tableCounter][1] = arrayOfPkgInfo[1].split("        ")[1]; //corresponding VOB
	tableCounter++;
}
var visiblePkgRepo = table;
return visiblePkgRepo;
}