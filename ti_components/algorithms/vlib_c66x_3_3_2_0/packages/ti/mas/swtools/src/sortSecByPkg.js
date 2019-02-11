/******************************************************************************
 * FUNCTION PURPOSE: Sort a specified section of pccToSort (raw data for package clearcase) using set of keys specified.
 ******************************************************************************
 * DESCRIPTION:
 *	It sorts a specified section (if it exists)  of pccToSort (raw data for package clearcase)  by using specified keys.
 *	It sorts using either of these keys: (0) PkgName, or (1) PkgName and then Version#, or (2) PkgName, then Version# and finally VOB.
 *	It returns the sorted hash table.
 *  HashTable	printHash(
 *    HashTable	pccToSort	-contains the raw package clearcase data to be sorted.
 *    Array	secToSort	-array specifiying section of pccToSort that will be sorted. (eg.["DEP"].
 *    string	numKeys	-if 0, sort by PkgName; if 1, sort by PkgName & then Version; if 2, sort by Pkgname, Version & VOB
 *****************************************************************************/
function sortSecByPkg(pccToSort, secToSort, numKeys){
for each (var secOfPcc in secToSort){
	if(pccToSort[secOfPcc]!=undefined){
		//Use a sorting algorithm on pccToSort["DEP"][...] using pccToSort["DEP"][...][0] as key
		pccToSort[secOfPcc].sort(//Use the following 1-time-use function literal 
			function(a, b){//a and b are arrays in pccToSort[secOfPcc] holding info for 2 distinct Pkgs	
				for(var key=0; key<numKeys; key++){ //key=0,1,2 refers to sorting by Pkgname, Version & vob respectively
					var keyA = a[key].split("."); 
					var keyB = b[key].split(".");
					var syl; //number of "syllables" separated by "." in keys we are using while sorting
					var sameLength=0;
					if(keyA.length == keyB.length){
						sameLength = 1;
						syl = keyB.length;
					} else if(keyA.length < keyB.length){
						syl=keyA.length;
					} else if(keyA.length > keyB.length){
						syl = keyB.length;
					}
					//Compare the keys "syllable" by "syllable"...
					for(var n=0; n<syl; n++){
						if(keyA[n]==keyB[n]){
							if(n==(syl-1) &&sameLength==1){//a&b ARE the same, based on keys used so far!
								if(key==(numKeys-1)){//all keys are used, and a&b are equal. thus, give "keep-order sorting rule"
									return -1; 
								} else {//There are more keys for sorting; so, use them.
									break;
								}
							} else if(n==(syl-1) && syl==keyA.length){//keyA is subset of keyB; list it first.
								return -1;
							} else if(n==(syl-1) && syl==keyB.length){//keyB is subset of keyA; list it first.
								return 1;
							}
						} else{//The two keys are NOT the same! So, find out their alphabetical OR numerical order.
							var compaRes;
							if (key==0 || key==2){//package and vobs are sorted alphabetically
								compaRes=[keyA[n], keyB[n]].sort();
							} else if(key==1){//version numbers are sorted numerically
								compaRes=[keyA[n], keyB[n]].sort(
									function(aaa,bbb){
										return bbb-aaa;	//smaller appears later
									}
								);
							}
							if(compaRes[0]==keyA[n]){//list keyA first
								return -1;
							}else if(compaRes[0]==keyB[n]){//list keyB first
								return 1;
							}
						}
					}	
				}
			}
		);
	} else{//No sorting needed if the section to sort does not even exist!
	}
}
return pccToSort;
}