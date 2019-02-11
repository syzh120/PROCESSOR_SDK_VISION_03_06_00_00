/******************************************************************************
 * FUNCTION PURPOSE: Generate development configuration specification file (dcspec)
 ******************************************************************************
 * DESCRIPTION:
 *	It uses the output of pccGen function (pruned package clearcase data) to generate dcspec with correct syntax.
 *****************************************************************************/
utils.importFile("pccGen.js");
var  prunedPcc = pccGen(arguments);
if(reRunIt==0){
	//name of file is of the following format:- pkgName_v_r_x_p_dev.txt
	var dcspecPkgSuf = prunedPcc["ME"][0][0].split(".").pop(); 
	var dcspecFName = "dcSpec.txt";	
	var dcspecLnxFName = "dcSpeclnx.txt";	
	var dcspecFile = openUpFile(prunedPcc["ME"][0][0].replace(/\./g, "\/"), dcspecFName, "w", "");
	//ASK BOGDAN...currenlty dcspec is written where cscc used to be written for a pkgOfInterest -> then may change warnings below
	if(dcspecFile==undefined){
		print(dcspecFName +" is not written; because, it could not be accessed for writing in "+
				prunedPcc["ME"][0][0].replace(/\./g, "\/"));
	}else {
		//The following section of code defines the SYNTAX OF DEVELOPMENT CONFIGURATION SPECIFICATION FILES
		//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
		var dcspecWritten = dcspecFile.writeLine("# Development config spec for "+dcspecPkgSuf.toUpperCase()+" "+
													prunedPcc["ME"][0][1]+" and later");
		if(dcspecWritten == true){
			print(dcspecFName+" is succesfully created in "+prunedPcc["ME"][0][0].replace(/\./g, "\/"));
		}
		dcspecFile.writeLine("# (the Master version - checkouts allowed for "+dcspecPkgSuf.toUpperCase()+" only!)");
		dcspecFile.writeLine("# Based on the tip of the main branch for "+dcspecPkgSuf.toUpperCase()+".");
		dcspecFile.writeLine("#");
		dcspecFile.writeLine("# Please note that the "+prunedPcc["ME"][0][0].split(".").join("_")+"_V_R_X_P_dev branch does NOT exist!");
		dcspecFile.writeLine("");
		dcspecFile.writeLine("# Show any checkedout files");
		dcspecFile.writeLine("element * CHECKEDOUT");
		dcspecFile.writeLine("");
		dcspecFile.writeLine("# Specify how to select the folders that lead to the packages");
		dcspecFile.writeLine("# and how to select some of the shared folders (e.g. docs)");
		
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
			dcspecFile.writeLine("element /"+pkgRoots[roo][0]+" /main/LATEST -nocheckout");
			dcspecFile.writeLine("");
			dcspecFile.writeLine("element /"+pkgRoots[roo][0]+"/lost+found  /main/0");
			for (var sss=0; sss<pkgRoots[roo][1].length; sss++){
				var rootPart = pkgRoots[roo][1][0];
				for (var ttt=1; ttt<=sss; ttt++){
					rootPart = rootPart + "/" + pkgRoots[roo][1][ttt];
				}
				dcspecFile.writeLine("element /"+pkgRoots[roo][0]+"/"+rootPart+"             /main/LATEST -nocheckout");
				if(sss==(pkgRoots[roo][1].length-1)){//Display the documentation that comes with the "complete" root of package
					dcspecFile.writeLine("element /"+pkgRoots[roo][0]+"/"+rootPart+"/docs/...    /main/LATEST -nocheckout");
				}
				dcspecFile.writeLine("");				
			}
		}
		
		dcspecFile.writeLine("# Specify dependent packages (to allow debug branching remove -nocheckout as needed)");
		dcspecFile.writeLine("# mkbranch and end mkbranch lines would allow these packages to appear on "+dcspecPkgSuf.toUpperCase()+" branch!");
		dcspecFile.writeLine("#mkbranch "+prunedPcc["ME"][0][0].split(".").join("_")+"_V_R_X_P_dev");
		if(prunedPcc["DEP"].length!=0 || prunedPcc["INTERNAL"].length!=0){
			for each (var p in ["INTERNAL", "DEP"]){
				for (var n = 0; n<prunedPcc[p].length; n++){
					//there can be duplicate pkgs in INTERNAL and DEP with the same vrxp&vob. Pick one!
					var dHasDuplicate = 0;
					if(p=="INTERNAL"){						
						for(var nn=0; nn<prunedPcc["DEP"].length; nn++){
							if(prunedPcc[p][n][0]==prunedPcc["DEP"][nn][0]){
								dHasDuplicate = 1;
							}
						}
					}														
					if(dHasDuplicate==0){
						dcspecFile.writeLine("element /"+prunedPcc[p][n][2].toString().toLowerCase()+"/"+prunedPcc[p][n][0].split(".").join("/")+
									"/...   DEV_"+prunedPcc[p][n][0].split(".").join("_").toUpperCase()+
									"_"+prunedPcc[p][n][1].split(".").join("_")+" -nocheckout");
					}
				}
			}
		} else {
			dcspecFile.writeLine("# NONE");
		}
		dcspecFile.writeLine("");
		dcspecFile.writeLine("# Specify packages used for unit testing");
		if(prunedPcc["TST"].length!=0){
			for each (var p in ["TST"]){
				for (var n = 0; n<prunedPcc[p].length; n++){
					dcspecFile.writeLine("element /"+prunedPcc[p][n][2].toString().toLowerCase()+"/"+prunedPcc[p][n][0].split(".").join("/")+
								"/...   DEV_"+prunedPcc[p][n][0].split(".").join("_").toUpperCase()+
								"_"+prunedPcc[p][n][1].split(".").join("_")+" -nocheckout");
				}
			}
		} else {
			dcspecFile.writeLine("# NONE");	
			dcspecFile.writeLine("");	
		}
		dcspecFile.writeLine("#end mkbranch "+prunedPcc["ME"][0][0].split(".").join("_")+"_V_R_X_P_dev");
		dcspecFile.writeLine("");
		dcspecFile.writeLine("# Normal development in /main branch");
		dcspecFile.writeLine("element /"+prunedPcc["ME"][0][2].toString().toLowerCase()+"/"+prunedPcc["ME"][0][0].split(".").join("/")+"/... /main/LATEST");
		dcspecFile.writeLine("");
		//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@		
		dcspecFile.close();	//Flushs the java.io.PrintStream and closes the underlying java.io.FileOutPutStream.	
	}
   	/* Make a copy of Windows spec for Linux configspec  */
    
    var openedFile = openUpFile(prunedPcc["ME"][0][0].replace(/\./g, "\/"), dcspecFName, "r", "");    
    if(openedFile == undefined)
	{
		 print(dcspecFName + " cannot be read");
         java.lang.System.exit(1);
    }

    var writeFile = openUpFile(prunedPcc["ME"][0][0].replace(/\./g, "\/"), dcspecLnxFName, "w", "");    
    if(writeFile == undefined)
    {
      print(dcspecLnxFName + " cannot be written to. Please check Writing Permissions.");
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