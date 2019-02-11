/******************************************************************************
 * FUNCTION PURPOSE: Print the contents of the global warning buffer into a log file in the package of interest.
 ******************************************************************************
 * DESCRIPTION:
 *	It creates (or opens if it already exists) Ccase.log file in the package of interest. 
 *	It prints the contents of the global warning buffer into Ccase.log.
 *  void	printWarnings(
 *    string	formaArgs	-name of the package of interest or "" if curDir is pkgOfInt.
 *    String	pRoot		-is the root of the pkgForPcc; it consists of drive letter:\ & vob name. It helps us locate the folder of the file that we want to print to. It has "" value if root is current Directory))
 *****************************************************************************/
function printWarnings(formaArgs, pRoot){
if(warningBuffer.length!=0){
	 if(verbose==1){verboseCtr++;print(verboseCtr+":-\tWriting Ccase.log file...");}
	var fileNameUsed = "Ccase.log";
	warningLogFile = openUpFile(formaArgs, fileNameUsed, "w", pRoot);
	if (warningLogFile==undefined){
		print(fileNameUsed +" is not written; because, it could not be accessed for writing in"+
			(formaArgs=="" ? "current (pkg) directory" : formaArgs));
	} else { 
		var startedWriting = warningLogFile.writeLine("\n"+"\n"+"\n"+"***Warnings File***"+"\n");
		if(startedWriting == true){
			print(fileNameUsed+" is succesfully created.");
		}
	
		warningCounter = 1;
		for each (n in warningBuffer){
			warningLogFile.writeLine("Warning # " + warningCounter);
			warningLogFile.writeLine(n); warningLogFile.writeLine("\n");
			warningCounter++;	
		}
		warningLogFile.close();	//Flushs the java.io.PrintStream and closes the underlying java.io.FileOutPutStream.
	}
} else {//log file should never contain old information;
	 if(verbose==1){verboseCtr++;print(verboseCtr+":-\tDeleting contents of old Ccase.log file to keep it empty...");}
	var fileNameUsed = "Ccase.log";
	warningLogFile = openUpFile(formaArgs, fileNameUsed, "w", "");
	if (warningLogFile==undefined){
		print("The contents of the old "+fileNameUsed +" are not deleted; because, it could not be found for writing in "+
		(formaArgs=="" ? "current (pkg) directory" : formaArgs));
	} else { 
		var startedDeleting = warningLogFile.writeLine("\n"+"\n"+"\n"+"***Empty Warnings File***"+"\n");
		if(startedDeleting == true){
			print("Old "+fileNameUsed+" is succesfully deleted & a new EMPTY "+fileNameUsed+" is created.");
		}
		warningLogFile.close();	//Flushs the java.io.PrintStream and closes the underlying java.io.FileOutPutStream.		
	}	
}
}