/******************************************************************************
 * FUNCTION PURPOSE: Generate maintainance configuration specification file (mcspec)
 ******************************************************************************
 * DESCRIPTION:
 *	It uses the output of pccGen function (pruned package clearcase data) to generate mcspec with correct syntax.
 *****************************************************************************/
utils.importFile("pccGen.js");
var  prunedPcc = pccGen(arguments);
if(reRunIt==0){
	//name of file is of the following format:- pkgName_v_r_x_p_maint.txt
	var mcspecPkgSuf = prunedPcc["ME"][0][0].split(".").pop(); 
	var mcspecFName = "mCspec.txt";
	var mcspecLnxFName = "mCspeclnx.txt";	
	var mcspecFile = openUpFile(prunedPcc["ME"][0][0].replace(/\./g, "\/"), mcspecFName, "w", "");
	//ASK BOGDAN...currenlty mcspec is written where cscc used to be written for a pkgOfInterest -> then may change warnings below
	if(mcspecFile==undefined){
		print(mcspecFName +" is not written; because, it could not be accessed for writing in "+
				prunedPcc["ME"][0][0].replace(/\./g, "\/"));
	}else {
		//The following section of code defines the SYNTAX OF MAINTAINANCE CONFIGURATION SPECIFICATION FILES
		//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
		var mcspecWritten = mcspecFile.writeLine("# Maintenance config spec for "+mcspecPkgSuf.toUpperCase()+" "+
													prunedPcc["ME"][0][1].split(".")[0]+"."+
													prunedPcc["ME"][0][1].split(".")[1]+"."+
													prunedPcc["ME"][0][1].split(".")[2]+"."+
													"x");
		if(mcspecWritten == true){
			print(mcspecFName+" is succesfully created in "+prunedPcc["ME"][0][0].replace(/\./g, "\/"));
		}
		mcspecFile.writeLine("# (the Master version - checkouts allowed for "+mcspecPkgSuf.toUpperCase()+" only!)");
		mcspecFile.writeLine("# Based on DEV_"+prunedPcc["ME"][0][0].split(".").join("_").toUpperCase()+"_"+
											   prunedPcc["ME"][0][1].split(".").join("_"));
		mcspecFile.writeLine("");
		mcspecFile.writeLine("# Show any checkedout files");
		mcspecFile.writeLine("element * CHECKEDOUT");
		mcspecFile.writeLine("");
		mcspecFile.writeLine("# Specify how to select the folders that lead to the packages");
		mcspecFile.writeLine("# and how to select some of the shared folders (e.g. docs, swtools)");
		
		
		//Detect all the roots of packages in order to handle cases when there are multiple roots (i.e. not just ti/mas...)! 
		//This way we can specify how to select folders (the roots & respective folders above it) that lead to the packages
		var pkgRoots = new Array();	//Each of its elements will be arrays with (1) vob  & (2) package root array information.
		for each (var p in ["INTERNAL", "DEP", "TST"]){
			for (var n = 0; n<prunedPcc[p].length; n++){				
				var curPkgRoot;
				if(prunedPcc[p][n][0].split(".").pop()=="test"){
					if(prunedPcc[p][n][0].split(".").length<=2){//This is a VERY rare condition. (eg. ti/test ...-> then root is empty!)
						curPkgRoot = [];
						print("\n\nWARNING!\nThe root of the following TEST package is simply the vob!\n"+
								prunedPcc[p][n][0]+"\n\n");
					}else{
						curPkgRoot = prunedPcc[p][n][0].split(".").slice(0,-2);
					}
				}else {
					curPkgRoot = prunedPcc[p][n][0].split(".").slice(0,-1);
				}
				rootWasAdded = 0;
				for each (var rrr in pkgRoots){
					if(rrr[0]==prunedPcc[p][n][2] && rrr[1].join(".")==curPkgRoot.join(".")){
						rootWasAdded = 1;
					}					
				}
				if(rootWasAdded==0){
					pkgRoots.push([prunedPcc[p][n][2], curPkgRoot]);
				}
			}
		}				
		for (var roo=0; roo<pkgRoots.length; roo++){
			mcspecFile.writeLine("element /"+pkgRoots[roo][0]+"  DEV_"+
							prunedPcc["ME"][0][0].split(".").join("_").toUpperCase()+"_"+
							prunedPcc["ME"][0][1].split(".").join("_")+
							" -nocheckout");
			mcspecFile.writeLine("");
			mcspecFile.writeLine("element /"+pkgRoots[roo][0]+"/lost+found  /main/0");
			
			for (var sss=0; sss<pkgRoots[roo][1].length; sss++){
				var rootPart = pkgRoots[roo][1][0];
				for (var ttt=1; ttt<=sss; ttt++){
					rootPart = rootPart + "/" + pkgRoots[roo][1][ttt];
				}		
				if(sss==(pkgRoots[roo][1].length-1)){//This is the complete root of the package.
					
					mcspecFile.writeLine("# The following line assumes that "+mcspecPkgSuf.toUpperCase()+" branch would be allowed for all "+
										pkgRoots[roo][1][sss]+" packages!"); //we simply printed the name of the root before "packages!"
					mcspecFile.writeLine("#element /"+pkgRoots[roo][0]+"/"+rootPart+
										"/... .../"+prunedPcc["ME"][0][0].split(".").join("_")+"_"+prunedPcc["ME"][0][1].split(".").join("_")+
										"_maint/LATEST");
					mcspecFile.writeLine("");												
					mcspecFile.writeLine("# The following line assumes that "+ pkgRoots[roo][1][sss]+
										 " folder could end up in "+mcspecPkgSuf.toUpperCase()+" branch if modified");					
					
					mcspecFile.writeLine("#element /"+pkgRoots[roo][0]+"/"+rootPart+"\tDEV_"+
										prunedPcc["ME"][0][0].split(".").join("_").toUpperCase()+"_"+
										prunedPcc["ME"][0][1].split(".").join("_")+
										" -mkbranch "+prunedPcc["ME"][0][0].split(".").join("_")+
										"_"+prunedPcc["ME"][0][1].split(".").join("_")+"_maint");
					mcspecFile.writeLine("");	//Finally, display the documentation that comes with the "complete" root of package AND the actual package root 
					mcspecFile.writeLine("element /"+pkgRoots[roo][0]+"/"+rootPart+"\tDEV_"+
								prunedPcc["ME"][0][0].split(".").join("_").toUpperCase()+"_"+
								prunedPcc["ME"][0][1].split(".").join("_")+
								"\t -nocheckout");															
					mcspecFile.writeLine("element /"+pkgRoots[roo][0]+"/"+rootPart+"/docs/...    /main/LATEST \t-nocheckout");
				} else {
					mcspecFile.writeLine("element /"+pkgRoots[roo][0]+"/"+rootPart+"\tDEV_"+
								prunedPcc["ME"][0][0].split(".").join("_").toUpperCase()+"_"+
								prunedPcc["ME"][0][1].split(".").join("_")+
								" -nocheckout");								
				}
				mcspecFile.writeLine("");				
			}
		}				
		mcspecFile.writeLine("# Specify dependent packages (to allow debug branching remove -nocheckout as needed)");
		mcspecFile.writeLine("# mkbranch and end mkbranch lines would allow these packages to appear on "+mcspecPkgSuf.toUpperCase()+" branch!");
		mcspecFile.writeLine("#mkbranch "+prunedPcc["ME"][0][0].split(".").join("_")+"_"+prunedPcc["ME"][0][1].split(".").join("_")+"_maint");
		if(prunedPcc["DEP"].length!=0 || prunedPcc["INTERNAL"].length!=0){
			for each (var p in ["INTERNAL", "DEP"]){
				for (var n = 0; n<prunedPcc[p].length; n++){				
					//there can be duplicate pkgs in INTERNAL and DEP with the same vrxp&vob. Pick one!
					var mHasDuplicate = 0;
					if(p=="INTERNAL"){						
						for(var nn=0; nn<prunedPcc["DEP"].length; nn++){
							if(prunedPcc[p][n][0]==prunedPcc["DEP"][nn][0]){
								mHasDuplicate = 1;
							}
						}
					}														
					if(mHasDuplicate==0){															
						mcspecFile.writeLine("element /"+prunedPcc[p][n][2].toString().toLowerCase()+"/"+prunedPcc[p][n][0].split(".").join("/")+
									"/...   DEV_"+prunedPcc[p][n][0].split(".").join("_").toUpperCase()+
									"_"+prunedPcc[p][n][1].split(".").join("_")+" -nocheckout");
					}
				}
			}
		} else {
			mcspecFile.writeLine("# NONE");
		}
		mcspecFile.writeLine("");
		mcspecFile.writeLine("# Specify packages used for unit testing");
		if(prunedPcc["TST"].length!=0){
			for each (var p in ["TST"]){
				for (var n = 0; n<prunedPcc[p].length; n++){
					mcspecFile.writeLine("element /"+prunedPcc[p][n][2].toString().toLowerCase()+"/"+prunedPcc[p][n][0].split(".").join("/")+
								"/...   DEV_"+prunedPcc[p][n][0].split(".").join("_").toUpperCase()+
								"_"+prunedPcc[p][n][1].split(".").join("_")+" -nocheckout");
				}
			}
		} else {
			mcspecFile.writeLine("# NONE");	
			mcspecFile.writeLine("");	
		}
		mcspecFile.writeLine("#end mkbranch "+prunedPcc["ME"][0][0].split(".").join("_")+"_"+
							prunedPcc["ME"][0][1].split(".").join("_") +"_maint");
		mcspecFile.writeLine("");
		mcspecFile.writeLine("# Specify development/maintenance branch for "+
							prunedPcc["ME"][0][1].split(".")[0]+"."+
							prunedPcc["ME"][0][1].split(".")[1]+"."+
							prunedPcc["ME"][0][1].split(".")[2]+"."+
							"x "+mcspecPkgSuf.toUpperCase());
		mcspecFile.writeLine("element /"+prunedPcc["ME"][0][2].toString().toLowerCase()+"/"+prunedPcc["ME"][0][0].split(".").join("/")+"/... .../"+
							prunedPcc["ME"][0][0].split(".").join("_")+"_"+
							prunedPcc["ME"][0][1].split(".").join("_") +"_maint/LATEST");									
		mcspecFile.writeLine("element /"+prunedPcc["ME"][0][2].toString().toLowerCase()+"/"+prunedPcc["ME"][0][0].split(".").join("/")+"/... DEV_"+
							prunedPcc["ME"][0][0].split(".").join("_").toUpperCase()+"_"+
							prunedPcc["ME"][0][1].split(".").join("_")+" -mkbranch "+
							prunedPcc["ME"][0][0].split(".").join("_")+"_"+
							prunedPcc["ME"][0][1].split(".").join("_")+"_maint");
							
		mcspecFile.writeLine("element /"+prunedPcc["ME"][0][2].toString().toLowerCase()+"/"+prunedPcc["ME"][0][0].split(".").join("/")+"/... /main/0"+
							" -mkbranch "+prunedPcc["ME"][0][0].split(".").join("_")+
							"_"+prunedPcc["ME"][0][1].split(".").join("_")+"_maint");
		mcspecFile.writeLine("");							
		//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@		
		mcspecFile.close();	//Flushs the java.io.PrintStream and closes the underlying java.io.FileOutPutStream.	
	}
   	/* Make a copy of Windows spec for Linux configspec  */
    var openedFile = openUpFile(prunedPcc["ME"][0][0].replace(/\./g, "\/"), mcspecFName, "r", "");    
    if(openedFile == undefined)
	{
		 print(mcspecFName + " cannot be read");
         java.lang.System.exit(1);
    }

    var writeFile = openUpFile(prunedPcc["ME"][0][0].replace(/\./g, "\/"), mcspecLnxFName, "w", "");    
    if(writeFile == undefined)
    {
      print(mcspecLnxFName + " cannot be written to. Please check Writing Permissions.");
	  java.lang.System.exit(1);
    }

    var readLine;
    while((readLine=openedFile.readLine()) != null)
    {
       if(readLine.match("\/dsps_gtmas"))
       {
         readLine=readLine.replace(/\/dsps_gtmas/,"\/vobs\/dsps_gtmas");
       } 
       writeFile.writeLine(readLine);
    }
       
     writeFile.close();      
     openedFile.close();
 
	
} else if(reRunIt==1){
	//Please re-run the script with correct arguments and/or after meeting environment pre-conditions. .... is already displayed
}