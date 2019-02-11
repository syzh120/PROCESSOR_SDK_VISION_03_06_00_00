/******************************************************************************
 * FUNCTION PURPOSE: Call a function that constructs TST from raw data given(tstConstructor); call printConfigspecCC function.
 ******************************************************************************
 * DESCRIPTION: 
 *	It calls tstConstructor function using the TST raw data computed by find_DEP_INT_ME_rTST. 
 *	It calls printConfigspecCC function to write the file.
 *  void find_TST_andPrint(
 *    string	formaArgs	-name of Package of interest or "" if curDir is pkgOfInt
 *    String[][]	Content_DEP_INT_ME_rTST	-data computed by find_DEP_INT_ME_rTST function.
 *    String[]	-dontPutInDep	-list of packages in xml files that should be ignored.)
 *****************************************************************************/
function find_TST_andPrint(formaArgs, Content_DEP_INT_ME_rTST, dontPutInDep){
var Content_DEP=Content_DEP_INT_ME_rTST[0];
var Content_INTERNAL=Content_DEP_INT_ME_rTST[1];
var MEname=Content_DEP_INT_ME_rTST[2];
var impoNamesPkgXml = Content_DEP_INT_ME_rTST[3];
 if(verbose==1){verboseCtr++;print(verboseCtr+":-\tClassifying TST packages...");}
 //Use the TST raw data to call tstConstructor, which will compute TST.										
var Content_TST = tstConstructor(formaArgs, MEname, impoNamesPkgXml, dontPutInDep);

printConfigspecCC(formaArgs, MEname, Content_DEP, Content_INTERNAL, Content_TST);

}