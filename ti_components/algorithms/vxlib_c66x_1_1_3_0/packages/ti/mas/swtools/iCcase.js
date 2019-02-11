/******************************************************************************
 * FUNCTION PURPOSE: Generate integration configuration.specification file
 ******************************************************************************
 * DESCRIPTION:
 *	It generates integration configuration.specification file with DEP, INTERNAL & ARCH parts.
 *****************************************************************************/
utils.importFile("IpccGen.js");
var  allHashPru = IpccGen(arguments);
if(reRunIt==0){
	//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@		
	//PRINT  INTEGRATION CONFIGURATION.SPECIFICATION FILE WITH THE CORRECT SYNTAX!
	//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@		
	//First try finding a file named configuration.specification AND see if it has Begin_ME part. 
	//If it has "Begin_ME", it is *Development* configuration.specification file; so, 	ASK BOGDAN
	//Otherwise, it is *Integration* configuration.specification file; so,			ASK BOGDAN
	var commonFName = "configuration.specification"; //both integration & development versions have the same name.
	var IcsccFile = openUpFile("", commonFName, "w", ""); //ASK BOGDAN...current working directory ("') ...?
	if(IcsccFile==undefined){
		print(commonFName +" is not written; because, it could not be accessed for writing in "+
		"the current working directory.");	//ASK BOGDAN...current working directory .??
	} else {
		IcsWritten = IcsccFile.writeLine("# This is the Integration configuration.specification file.");
		if(IcsWritten==true){
			print(commonFName+" is succesfully created in "+"the current working directory.");//ASK BOGDAN...current working directory .??
		}

		IcsccFile.writeLine("# These are the packages needed for integration"+"\n");
		IcsccFile.writeLine(allHashPru.DEP.length==0 ? "#Begin_DEP": "Begin_DEP");
		if(allHashPru.DEP.length==0){
		IcsccFile.writeLine("#  "+"<pname1> <M1>.<m1>.<p1>.<b1>");
		IcsccFile.writeLine("#  "+"<pname2> <M2>.<m2>.<p2>.<b2>");
		IcsccFile.writeLine("#  ...");
		IcsccFile.writeLine("#  "+"<pnameN> <MN>.<mN>.<pN>.<bN>");
		} else{
			for (var n=0; n<allHashPru.DEP.length; n++){
				IcsccFile.writeLine("  " +allHashPru.DEP[n][0] + "	" + allHashPru.DEP[n][1] + "  "+ allHashPru.DEP[n][2]);
			}
		}
		IcsccFile.writeLine(allHashPru.DEP.length==0 ? "#End_DEP" : "End_DEP");

		IcsccFile.writeLine("\n"+"# These are the packages needed internally"+"\n");
		IcsccFile.writeLine(allHashPru.INTERNAL.length==0 ? "#Begin_INTERNAL": "Begin_INTERNAL");
		if(allHashPru.INTERNAL.length==0){
		IcsccFile.writeLine("#  "+"<pname1> <M1>.<m1>.<p1>.<b1>");
		IcsccFile.writeLine("#  "+"<pname2> <M2>.<m2>.<p2>.<b2>");
		IcsccFile.writeLine("#  ...");
		IcsccFile.writeLine("#  "+"<pnameN> <MN>.<mN>.<pN>.<bN>");
		} else{
			for (var n=0; n<allHashPru.INTERNAL.length; n++){
				IcsccFile.writeLine("  " +allHashPru.INTERNAL[n][0] + "	" + allHashPru.INTERNAL[n][1] + "  " + allHashPru.INTERNAL[n][2]);
			}
		}
		IcsccFile.writeLine(allHashPru.INTERNAL.length==0 ? "#End_INTERNAL": "End_INTERNAL");
		
		IcsccFile.writeLine("\n"+"# These are the architectures supported"+"\n");
		IcsccFile.writeLine(allHashPru.ARCH.length==0 ? "#Begin_ARCH": "Begin_ARCH");
		if(allHashPru.ARCH.length==0){
			//This case is prevented by argument processing!
		} else{
			for (var n=0; n<allHashPru.ARCH.length; n++){
				IcsccFile.writeLine("  " +allHashPru.ARCH[n]);
			}
		}
		IcsccFile.writeLine(allHashPru.ARCH.length==0 ? "#End_ARCH": "End_ARCH");
									
		IcsccFile.writeLine("\n"+"# nothing past this point");
		IcsccFile.close();	//Flushs the java.io.PrintStream and closes the underlying java.io.FileOutPutStream.						
	}	
} else if(reRunIt==1){
	//Please re-run the script with correct arguments and/or after meeting environment pre-conditions. .... is already displayed
}	