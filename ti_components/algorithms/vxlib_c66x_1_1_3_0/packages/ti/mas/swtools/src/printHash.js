/******************************************************************************
 * FUNCTION PURPOSE: Print the contents of a given hash table (pcc data) into a log file in the package of interest.
 ******************************************************************************
 * DESCRIPTION:
 *	It creates (or opens if it already exists) a file in the package specified for writing (usually PkgOfInterest).
 *	It prints the contents of the given hash table into the file opened.
 *  void	printHash(
 *    string	pkgForPcc	-name of the package where pcc data will be written to.
 *    string	typeOfPcc	-"Raw" or "Sorted" or "Pruned" ... depending on the kind of the Package ClearCase data. 
 *    HashTable	pccData	-contains the data about the package clearcase file.
   *    String	pRoot		-is the root of the pkgForPcc; it consists of drive letter:\ & vob name. It helps us locate the folder of the file that we want to print to. It has "" value if root is current Directory)
 *****************************************************************************/
function printHash(pkgForPcc, typeOfPcc, pccData, pRoot){
if(typeOfPcc!="Formatted"){
	var fileNameUsed = typeOfPcc+"_Pcc.log"
	var pccFile = openUpFile(pkgForPcc, fileNameUsed, "w", pRoot);
	if (pccFile==undefined){
		print(fileNameUsed +" is not written; because, it could not be accessed for writing in"+pkgForPcc);
	} else { 
		var startedWriting = pccFile.writeLine("\n"+"\n"+"\n"+"***"+typeOfPcc+" Package_ClearCase File***"+"\n");
		if(startedWriting == true){
			print(fileNameUsed+" is succesfully created in "+(pkgForPcc=="" ? "the current package directory" : pkgForPcc));
		}
		for each (var p in ["ME", "DEP", "INTERNAL", "TST"]){	
			pccFile.writeLine("		"+p);
			for (var n=0;n<pccData[p].length;n++){
				pccFile.writeLine(pccData[p][n][0]+"	"+pccData[p][n][1]+"	"+pccData[p][n][2]);
			}	
		}		
		pccFile.close();	//Flushs the java.io.PrintStream and closes the underlying java.io.FileOutPutStream.		
	}
}else if(typeOfPcc=="Formatted"){//Apply the syntax of package clearcase files to hash printing! 
}
}