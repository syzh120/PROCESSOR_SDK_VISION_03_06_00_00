/******************************************************************************
 * FUNCTION PURPOSE: Add a hashtable with contents of a cscc to a hashtable that is growing towards being a PkgClearCase file.
 ******************************************************************************
 * DESCRIPTION: 
 *	It copies portions of ccHashOri to corresponding portions of pccHashDest.
 *	Those portions to be copied are given as an argument; the argument is an array of portion names.
 *	It returns a hash table, pccHashDest, that has no less information than the parameter pccHash (has more info if ccHashOri is non-empty.
 *  HashTable mergeToPcc (
 *    HashTable	ccHashOri	-hashtable with contents of a configspec.clearcase file.
 *    HashTable	pccHashDest	-hashtable that will eventually contain contents of Package ClearCase file. 
 *    Array	ccPartsToCopy	-array of strings; the strings are some of the names of the portions of configspec.clearcase.)
 *****************************************************************************/
function mergeToPcc(ccHashOri, pccHashDest, ccPartsToCopy){
for each (var p in ccPartsToCopy){
	if(ccHashOri[p]!=undefined){
		if(pccHashDest[p]!=undefined){
			for (var n=0;n<ccHashOri[p].length;n++){
				pccHashDest[p].push(ccHashOri[p][n]);						
			}
		} else {//can't happen b/c pccHashDest was originally initialized with all parts!
		}			
	} else {//Ignore , b/c there is nothing to copy over to pccHashDest from ccHashOri
	}
}
return pccHashDest;
}