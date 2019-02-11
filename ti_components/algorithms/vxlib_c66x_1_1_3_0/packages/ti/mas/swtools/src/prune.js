/******************************************************************************
 * FUNCTION PURPOSE: Discard repeted listing of packages with 'older' v.r.x.p. information. 
 ******************************************************************************
 * DESCRIPTION:
 *	It takes in the output of sortSecByPkg() and picks one package listing from each set of package
 *	listings with the same package name; the package listing that is picked has the 'latest' v.r.x.p. info.
 *	It also goes through other sections to see if there are name duplicates; if there are, it uses the latest v.r.x.p.
 //ASK BOGDAN
 *	 WHAT ROLE DOES THE VOB PLAY IN PRUNNING........NO ROLE! v.r.x.p decides all! is the guess
 *	It returns the 'pruned' hash table. 
 *    HashTable	prune(
 *    HashTable	sortedPcc	-this is already sorted by pkgName, then by v.r.x.p. and finally by VOB
 *    String	-AorW	-is "w" if the prunning details is to be written onto a new log file; is "a" if prunning details is to be appended to an existing log file)
 *****************************************************************************/
function prune(sortedPcc, AorW){
var pruneLogArr = new Array(); //will help us collect info that is to be printed into a log file.
var prunedPcc = {};//initialize hash table that will contain pruned package clearcase data
for each(var p in ["ME", "DEP", "INTERNAL", "TST"]){
	prunedPcc[p]=new Array();
}
for each (var p in ["ME", "DEP", "INTERNAL", "TST"]){
	if(sortedPcc[p].length!=0){
		var curListing = sortedPcc[p][0][0];
	}
	for (var n=0;n<sortedPcc[p].length;n++){
		if(n==0 || curListing!=sortedPcc[p][n][0]){
			//The following boolean becomes 1 if we have a package with name=curListing & 
			//larger v.r.x.p. than other listings with the same package name.
			var largerFound = 0; 
			curListing = sortedPcc[p][n][0];
			var curLisVRXP = sortedPcc[p][n][1];
			var curLisVOB = sortedPcc[p][n][2];
			//@
            for each (var pp in ["ME", "DEP", "INTERNAL", "TST"]){
                if(pp!=p){
                    var dupInSectPP = 0; // becomes 1 if curListing is found in section pp
                    var ppVRXP;
                    var ppVOB;
                    for (var nn=0; nn<sortedPcc[pp].length;nn++){
                        if(dupInSectPP==0 && curListing==sortedPcc[pp][nn][0]){//save the duplicate in section pp
                            dupInSectPP = 1;
                            ppVRXP=sortedPcc[pp][nn][1];
                            ppVOB=sortedPcc[pp][nn][2];
                            /* if the other package is same.
                            Mark it as duplicate*/
                            if((curLisVRXP==ppVRXP) && (curLisVOB==ppVOB))
                            {
                               sortedPcc[pp][nn][0]="DUP";
                               sortedPcc[pp][nn][1]="";
                               sortedPcc[pp][nn][2]="";

                            }
                        }
                    }//update curLisVRXP and curLisVOB after comparison of vrxp infos
                    if(dupInSectPP==1){
                        var keepPP = 0;//is 1 if ppVRXP is bigger than curLisVRXP
                        var keepCurLis = 0;//is 1 if curLisVRXP is bigger than ppVRXP
                        if(ppVRXP=="?.?.?.?"){
                            keepCurLis = 1;
                        }else if(curLisVRXP=="?.?.?.?"){
                            keepPP = 1;
                        }else{
                            for(var i=0; i<curLisVRXP.length; i++){ 
                                if(ppVRXP[i]>curLisVRXP[i]){
                                    keepPP = 1;
                                    break;
                                }
                                if(curLisVRXP[i]>ppVRXP[i]){
                                    keepCurLis = 1;
                                    break;
                                }                                               
                            }
                        }
                        if(keepPP==1 || keepCurLis==1){
                            /*one listing had a 'larger' OR 'a numerical'
                             v.r.x.p than other listing with the same pkg name.*/
                            largerFound = 1;
                            if(keepPP==1)
                            {
                               curLisVRXP=ppVRXP;
                               curLisVOB=ppVOB;
                             }

                        }

                    }
                }
            }//@
			for(var m=n; m<sortedPcc[p].length; m++){//go through all the next listings within this package
				if(sortedPcc[p][n][0]==sortedPcc[p][m][0]){//listing that comes below is of the same name
					if(sortedPcc[p][n][1]!=sortedPcc[p][m][1]){
						//listing that comes below has a different (i.e. a smaller v.r.x.p. because list is already sorted in decending order)
						largerFound = 1;
					}					
				}
			}
			/* If current package is not duplicate, add to the pruned file*/
			if(curListing != "DUP")
			{
			var keepThis = new Array();
			keepThis = [curListing, curLisVRXP, curLisVOB];
			prunedPcc[p].push(keepThis);
			if(largerFound==1){
				var pruneReport = "\n"+curListing+" package with v.r.x.p. "+curLisVRXP+" is kept in section "+p+
					"\nOther listings of "+curListing+" package with 'smaller' v.r.x.p. were found and pruned!\n";
				print(pruneReport);
				pruneLogArr.push(pruneReport); //in addition, we have chosen to print the same information into a log file in the current working directory.

			}
			}
		}		
	}
}
//finally print details into log file in the current directory.
var pruneFName = "pruningInfo.log";
var pruneLogFile = openUpFile("", pruneFName, AorW, "");
if(pruneLogFile==undefined){
	print(pruneFName+" is not written; because, it could not be accessed for writing in the current working directory.")
} else{
	pruLogFiWritten = pruneLogFile.writeLine((AorW=="w" ? "\t***Prunning details Log File***" : "\n\n\t**<<<(appended) Prunning details Log File>>>\n"));
	if(pruLogFiWritten==true){
		print(pruneFName+" is succesfully "+ (AorW=="w" ? "CREATED" : "UPDATED") +
			  " in the current working directory.");
	}
	for each (var info in pruneLogArr){
		pruneLogFile.writeLine(info);
	}
	pruneLogFile.close();
}
return prunedPcc;
}