/******************************************************************************
 * FUNCTION PURPOSE: Generate integration configuration specification file (icspec)
 ******************************************************************************
 * DESCRIPTION:
 *	It uses the output of iCcase.js script to generate icspec with correct syntax.
 *****************************************************************************/
utils.importFile("IpccGen.js");
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
//NOTE::: FUTURE WORK: In the future, we will be handling more than one VOB. So, we will NOT need to pass a "LABEL" argument
//to icspecGen.js script. For now, this argument is extracted from the arguments array at this EARLY stage of the execution of the script 
//in order to minimize future changes that need to be done. 

//(label) ARGUMENT CONVENTION: In addition to the argument conventions specified in iFormatArg.js, we add the following here.
//The label arguments should be the last set of arguments. List of lables should be preceeded by "-l". Thus, everything entered 
//after -l is considered as a label. 
var labelStarted = 0;
var labelArg = new Array();
var nonLabArg = new Array();
for (var n=0; n<arguments.length; n++){//Look for {-l label1, label2, label3,...}  at the end of the arguments.
	if(arguments[n]=="-l"){
		labelStarted = 1;
	}
	if(arguments[n]!="-l" && labelStarted==1){
		labelArg.push(arguments[n]);		
	} else if(labelStarted==0){
		nonLabArg.push(arguments[n]); //keep all the parts of arguments before "-l"
	}	
}
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
var  allHashPru = IpccGen(nonLabArg);
if(reRunIt==0){

	//name of file is of the following format:- iCSPEC.txt 		//ASK BOGDAN
	var icspecFName = "iCSPEC.txt";	
	var icspecFile = openUpFile("", icspecFName, "w", "");
	if(icspecFile==undefined){
		print(icspecFName +" is not written; because, it could not be accessed for writing in "+
				"the current working directory");
	}else {
		//The following section of code defines the SYNTAX OF INTEGRATION CONFIGURATION SPECIFICATION FILES
		//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
		var icspecWritten = icspecFile.writeLine("# Integration config spec");
		if(icspecWritten == true){
			print(icspecFName+" is succesfully created in"+" the current working directory");
		}
		icspecFile.writeLine("");
		icspecFile.writeLine("# Show any checkedout files");
		icspecFile.writeLine("element * CHECKEDOUT");
		icspecFile.writeLine("");
		icspecFile.writeLine("# Specify how to select the folders that lead to the packages");
		icspecFile.writeLine("# and how to select some of the shared folders (e.g. docs)");
		
		//NOTE::: In the future, the following may be done slightly differently.<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
		// But for now, go through the ARGUMENT for list of labels of dummy packages. These 
		//"labels" also contain <vob> information. So, extract the <vob> and print commands which enable access to <vob>, <vob>\x, <vob>\x\...\y (where y is 
		//the dummy package). The label provided as argument is *considered* as a pureLabel and is applied in iCSPEC. 
		//Extracting the <vob> may be impossible because it can have "_", which is also present in other parts of the label. So, get a list of <vob>s from
		//the allHashPru (which is also used to generate integration configuration.specification file.).		
		var allVobs = new Array();	//make a NON-repetitive list of all the vobs listed in DEP & INTERNAL parts of allHashPru
		for each(var p in ["DEP", "INTERNAL"]){
			for(var n=0; n<allHashPru[p].length; n++){//consider all <vob>s	
				var wasAdded = 0;
				for(m=0; m<allVobs.length; m++){
					if(allHashPru[p][n][2]==allVobs[m]){
						wasAdded = 1;
						break;
					}
				}
				if(wasAdded==0){
					allVobs.push(allHashPru[p][n][2]);
				}
			}
		}
		
		for each(var lvDummy in labelArg){
			var pureLabel;//lvDummy consists pureLabel & pureVob; the goal is to separate these two.
			var pureVob;
			for each(var vvv in allVobs){
					//note that the rest of label is just collection of ASCII word characters (including "_")
					var vvvUpper = vvv.toString().toUpperCase(); //This is done because users may give us vob names in any form
					var lArgPattern = new RegExp("(^DEV\\_)(" + vvvUpper + ")(\\_)([\\w]{1,})" );
					var lvMatch = lvDummy.toString().toUpperCase().match(lArgPattern); 
					if(lvMatch!=null){
						pureLabel = lvDummy;
						pureVob = vvv.toString().toLowerCase();
					}					
			}
			if(allVobs.length!=0 && (pureLabel==undefined || pureLabel==null)){//******This IS THE ONLY UNCAUGHT EXCEPTION AS A RESULT OF INCORRECT ARGUMENTS
				throw new Error("\n\n\nPlease review the label-ARGUMENT you entered for the dummy packages & re-run script\n"+
				"The VOB information in it could not be matched to contents of integration configuration.specification file\n"+
				lvDummy+"\n\n\n");
			} else{			
				icspecFile.writeLine("element /"+pureVob+" "+pureLabel+" -nocheckout"); //  /<vob> is accessed with dummy package's label provided!
				icspecFile.writeLine("");
				icspecFile.writeLine("element /"+pureVob+"/lost+found/..."+" /main/0");
				// Next, access /<vob>/xxx, <vob>/xxx/yyy, <vob>/xxx/yyy/.../ddd, with dummy package's label provided, where ddd is the dummy package.
				var plArr = pureLabel.split("_");
				plArr.reverse();
				plArr.pop(); //get rid of "DEV"
				plArr.reverse();
				for(var zzz = 0; zzz<(plArr.length-4); zzz++){//Do "plArr.length-4"; because the last four are version numbers
					var folderName = pureVob;
					for(var yyy=0; yyy<=zzz; yyy++){
						folderName = folderName + "/" + plArr[yyy];
					}
					folderName = folderName.toString().toLowerCase();
					icspecFile.writeLine("element /"+folderName+"\t"+pureLabel+" -nocheckout");
					if(zzz==(plArr.length-1-4)){
						icspecFile.writeLine("element /"+folderName+"/docs...\t/main/LATEST -nocheckout");
					} else{
						icspecFile.writeLine(""); //leave empty space in between for readability
					}
				}				
				icspecFile.writeLine("");
			}
		}
		icspecFile.writeLine("");
		//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
		icspecFile.writeLine("# Specify dependent packages");
		if(allHashPru["DEP"].length!=0 || allHashPru["INTERNAL"].length!=0){
			for each (var p in ["INTERNAL", "DEP"]){
				for (var n = 0; n<allHashPru[p].length; n++){
					//there can be duplicate pkgs in INTERNAL and DEP with the same vrxp&vob. Pick one!
					var dHasDuplicate = 0;
					if(p=="INTERNAL"){						
						for(var nn=0; nn<allHashPru["DEP"].length; nn++){
							if(allHashPru[p][n][0]==allHashPru["DEP"][nn][0]){
								dHasDuplicate = 1;
							}
						}
					}														
					if(dHasDuplicate==0){
						icspecFile.writeLine("element /"+allHashPru[p][n][2]+"/"+allHashPru[p][n][0].split(".").join("/")+
									"/...   DEV_"+allHashPru[p][n][0].split(".").join("_").toUpperCase()+
									"_"+allHashPru[p][n][1].split(".").join("_")+" -nocheckout");
					}
				}
			}
		} else {
			icspecFile.writeLine("# NONE");
		}
		icspecFile.writeLine("");															
		//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@		
		icspecFile.close();	//Flushs the java.io.PrintStream and closes the underlying java.io.FileOutPutStream.	
	}
} else if(reRunIt==1){
	//Please re-run the script with correct arguments and/or after meeting environment pre-conditions. .... is already displayed
}