/******************************************************************************
 * FUNCTION PURPOSE: Open up and return the file that we want to populate with information OR read.
 ******************************************************************************
 * DESCRIPTION: 
 *	It can operate either in "write", "read" or "append"  mode, as specified by the third paramter.
 *	In "write" mode, it creates (or opens) a file by the name "fileNameUsed" inside formaArgs. 
 *	In "read" mode, it opens a file by the name "fileNameUsed" inside formaArgs.
  *	In "append" mode, it creates (or opens) a file by the name "fileNameUsed" inside formaArgs & gets it ready for writing (or appending)
 *	It returns the file opened.
 * 	It may return undefined after reporting problems encountered.
 *  file object	openUpFile (
 *    string	formaArgs	-name of package of interest, where the fileNameUsed is (will be) in.
 *    string	fileNameUsed	-the name of the file to be opened.
 *    string	rwMode	-specifies readwrite mode; can only take "w", "r", or "a" values.
  *    String	pRoot		-is the root of the formaArgs; it consists of drive letter:\ & vob name. It helps us locate the folder of the file that we want to open. It has "" value if root is current Directory)
 *****************************************************************************/
function openUpFile(formaArgs, fileNameUsed, rwMode, pRoot) {
var fileModule = xdc.module('xdc.services.io.File');
var openedFile;
var fileLoc;
try{
if(formaArgs==""){//formaArgs is meant to refer to the current working directory
	if(rwMode=="w"){
		try{
			openedFile = fileModule.open(fileNameUsed, rwMode);
		} catch (ex){
			throw new Error(fileNameUsed + " inside the current directory cannot be written to."+" Please check Writing Permissions.");
		}
	} else if(rwMode=="r"){
		try{
			openedFile = fileModule.open(fileNameUsed, rwMode);
		} catch (ex){
			throw new Error(fileNameUsed + " inside the current directory cannot be read."+" Please check Reading Permissions or its existence.");
		}	
	} else if(rwMode=="a"){
		try{
			openedFile = fileModule.open(fileNameUsed, rwMode);
		} catch (ex){
			throw new Error(fileNameUsed + " inside the current directory can't be appended to."+" Please check File Permissions or its existence.");
		}				
	} else {
		throw new Error("Error internal to Ccase scripts:- rwMode parameter of openUpFile() can only take 'r' or 'w' values");
	}	
} else {//formaArgs is not meant to refer to the the current working directory
/*	formaArgs = formaArgs.toString().replace(/\//g, "\\");*/
	formaArgs = formaArgs.toString().replace(/\./g, "/");
	if(pRoot!=""){//pRoot is not the same as the current working directory, so pre-append it to formaArgs
		pRoot = pRoot.toString().replace(/\//g, "\\");
		pRoot = pRoot.replace(/\\$/, "");
		formaArgs = pRoot+"\\"+formaArgs;
	}
	fileLoc = findFilePlus(formaArgs);
	if(fileLoc==null){
			throw new Error("Folder ("+formaArgs+") that should hold "+fileNameUsed+" file is not found.");	
	} else {
		if(rwMode=="w"){
			try{
				openedFile = fileModule.open(fileLoc+"/"+fileNameUsed, rwMode);
			} catch (ex){
				throw new Error(fileNameUsed+" inside "+fileLoc+" cannot be written to."+" Please check Writing Permissions.");
			}
		} else if(rwMode=="r"){
			try{
				openedFile = fileModule.open(fileLoc+"/"+fileNameUsed, rwMode);
			} catch (ex){
				throw new Error(fileNameUsed+" inside "+fileLoc+" cannot be read."+" Please check Reading Permissions or its existence.");
			}	
		} else if(rwMode=="a"){
			try{
				openedFile = fileModule.open(fileLoc+"/"+fileNameUsed, rwMode);
			} catch (ex){
				throw new Error(fileNameUsed+" inside "+fileLoc+" can't be appended to."+" Please check File Permissions or its existence.");
			}				
		} else {
			throw new Error("Error internal to Ccase scripts:- rwMode parameter of openUpFile() can only take 'r' or 'w' values");
		}
	}
}
}catch (e) {
	if(rwMode=="w" || rwMode=="r" || rwMode=="a"){
		print(e);
	} else {
		print("Error internal to Ccase scripts:-"+"\n"+e)
	}
}
return openedFile;
}