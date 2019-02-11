/******************************************************************************
 * FUNCTION PURPOSE: Parse a configspec.clearcase file into a hash table.
 ******************************************************************************
 * DESCRIPTION: 
 *	It reads the configspec.clearcase of pkgOfcscc specified.
 *	It parses the file read and organizes and puts the data into ccAsAHash hash table.
 *	It returns the ccAsAHash hash table bundled (in an array) with a  flag called legalSyntax.
 *	The legalSyntax is: 0 if syntax is legal, 1 if syntax is illegal, -1 if cscc could not be opened(which is most probably a problem in pkgOfcscc name)
 *	ccAsAHash is empty, {}, if problems are encountered while reading configspe.clearcase.
 *	ccAsAHash has some (legal) parts of its portions (ME, DEP...) if parsing problem is encountered.
 * 	A commented code at the bottom of this code demonstrates how the hash table can be read.
 *  HashTable	ccParser (
 *    string	pkgOfcscc	-name of package of the configspec.clearcase being considered or "" if curDir==pkgOfInt
 *    String	pRoot		-is the root of the pkgOfcscc; it consists of drive letter:\ & vob name. It helps us locate the configuration.specification file that we want to parse. It has "" value if root is current Directory)
 *****************************************************************************/
function ccParser(pkgOfcscc, pRoot){
var ccAsAHash = {};//Initialize hash table that holds parsed data of configspec.clearcase of pkgOfcscc
fileNameToParse = "configspec.clearcase";
var legalSyntax = 1;
var pkgOfcscc = pkgOfcscc.replace(/\./g, "\/");
csccFile = openUpFile(pkgOfcscc, fileNameToParse, "r", pRoot);
if(csccFile==undefined){
	print(fileNameToParse+" of "+pkgOfcscc+" could NOT be read for parsing. Please, check its file permissions."+
			"\nMost probably, "+pkgOfcscc+" is not a package.");
	legalSyntax = -1;
	return [ccAsAHash, legalSyntax];
}

var csccLineRead = csccFile.readLine();
try{
while(csccLineRead!=null || csccLineRead!=undefined){//EOF is not reached...look for Begin_
	if(csccLineRead.toString().search(/^#/)==0 || csccLineRead==""){//Skip this line &...look for Begin_	
		csccLineRead = csccFile.readLine();
	} else if(null!=csccLineRead.toString().match(/(End_)([a-zA-Z0-9]{1,})/)){//Error
		legalSyntax=0;
		throw new Error(csccLineRead+" is found while looking for 'Begin_' statement in configspec.clearcase in "+
			(pkgOfcscc=="" ? "current (pkg) directory." : pkgOfcscc));
	} else{//Line is not {comment, empty, EOF, End_}...look for Begin_
		var testIfBegin = csccLineRead.toString().match(/(Begin_)([a-zA-Z0-9]{1,})/);
		if(testIfBegin!=null){
			var BeginedPart = testIfBegin[2]; //Begined Part can be "ME", "DEP", "INTERNAL", "TST"...
			var tempContainer = new Array(); //look for End_; put info here during that time.
			csccLineRead = csccFile.readLine();
			if(csccLineRead==null || csccLineRead==undefined){//Error: EOF comes right after Begin_
				legalSyntax=0;
				throw new Error("Begin_ statement is found at the End Of File of configspec.clearcase in "+
					(pkgOfcscc=="" ? "current (pkg) directory." : pkgOfcscc));
			}
			while(csccLineRead.toString().match(/(End_)([a-zA-Z0-9]{1,})/)==null){//keep on looking for End_
				if(csccLineRead.toString().search(/^#/)==0 || csccLineRead==""){//Skip this line & look for End_
					csccLineRead = csccFile.readLine();
				} else if(null!=csccLineRead.toString().match(/(Begin_)([a-zA-Z0-9]{1,})/)){//Error
					legalSyntax=0;
					throw new Error(csccLineRead+" is found while looking for 'End_' statement in configspec.clearcase in "+
						(pkgOfcscc=="" ? "current (pkg) directory." : pkgOfcscc));					
				} else {//Line is not {End_, EOF, comment, empty, Begin_}...try parsing it & look for End
					var pkgVerVobLine = csccLineRead.toString().match(/(^[\s]{0,})([\S]{1,})([\s]{1,})([\S]{1,})([\s]{0,})([\S]{0,})([\s]{0,})/);
					var pkgVerVob = new Array();						
					if(pkgVerVobLine!=null){
						pkgVerVob.push(pkgVerVobLine[2].toString());	//pkgVerVob[0] is Package name
						pkgVerVob.push(pkgVerVobLine[4].toString());	//pkgVerVob[1] is Version
						if(pkgVerVobLine[6].toString()==""){
							pkgVerVob.push(defaultVOB);	//use defaultVOB if user optionally did not enter the vob name						
						}else {
							pkgVerVob.push(pkgVerVobLine[6].toString());	//pkgVerVob[2] is Vob
						}
						tempContainer.push(pkgVerVob);	//save the parsed line for later copying into ccAsAHash[BeginedPart]
						csccLineRead = csccFile.readLine();	
					} else {//Error: unrecognized format of <PkgName, Version, Vob> 
						legalSyntax=0;
						throw new Error("Unrecognized format of <PkgName, Version, Vob> in configspec.clearcase in"+
							(pkgOfcscc=="" ? "current (pkg) directory." : pkgOfcscc));
					}					
				}
				if(csccLineRead==null || csccLineRead==undefined){//Error: found EOF while looking for End_
					legalSyntax=0;
					throw new Error("End Of File is found while looking for End_ in configspec.clearcase in "+
						(pkgOfcscc=="" ? "current (pkg) directory." : pkgOfcscc));
				}								
			}
			//by now Begin must have matched End
			var EndedPart = csccLineRead.toString().match(/(End_)([a-zA-Z0-9]{1,})/)[2];
			if(EndedPart!=BeginedPart){//Error
				legalSyntax=0;
				throw new Error("Begin_"+BeginedPart+" does not match End_"+EndedPart+" in configspec.clearcase in "+
					(pkgOfcscc=="" ? "current (pkg) directory." : pkgOfcscc));
			} else{
				if(ccAsAHash[BeginedPart]==undefined){
					ccAsAHash[BeginedPart]=new Array();
				}
				ccAsAHash[BeginedPart] = tempContainer;				
				csccLineRead = csccFile.readLine();	//..and continue to look for another Begin_
			}			
		} else{//Error: During search for Begin_, a line that is not EOF, "", #, or End_ is encountered
			legalSyntax=0;
			throw new Error(csccLineRead+" is found while looking for 'Begin_' statement in configspec.clearcase in "+
				(pkgOfcscc=="" ? "current (pkg) directory." : pkgOfcscc));
		}		
	}
}
} catch (ex){
	//NOTE: This exception (ex) could have been thrown by readLine() of java.io.BufferedReader, which has been extended by xdc.services.io.File.xs file.
	//However, the xdc.services.io.File.xs file does not have a catch statement for it (probably) with the intention of allowing the exception to show up 
	//as IO exceptions in this case should be rare. Thus, I also will let this exception to print to command line directly.
	if(legalSyntax==0){
		print("\n\n\nPROBLEM PARSING configspec.clearcase in "+(pkgOfcscc=="" ? "current (pkg) directory." : pkgOfcscc)+"\n");
		print("Regenerate this configspec.clearcase before proceeding");
		print("The following illegal configspec.clearcase formats were detected.");
	}
	print("\n\n"+ex);
	print("\n\n\n");
	try{
		csccFile.close();//closes the underlying java.io.BufferedReader steam.
	}catch(exx){
		print("The following IO problem is encountered while closing configspec.clearcase of "+pkgOfcscc+"\n"+exx);
	}
	return [ccAsAHash, legalSyntax];	//return the hash table with its legal portions built so far!		
}
/****************************************************************************************
// The following is an example on how we can READ the hash table constructed above.
portiCC = ["ME", "DEP", "INTERNAL", "TST"];
for each (var p in portiCC){	print("	Portion of configspec.clearcase Hash (ccAsAHash) "+ p);
	for (var n=0;n<ccAsAHash[p].length;n++){
		print(ccAsAHash[p][n][0]);
		print(ccAsAHash[p][n][1]);
		print(ccAsAHash[p][n][2]);
	}	
}
*****************************************************************************************/
try{
	csccFile.close();//closes the underlying java.io.BufferedReader steam.
}catch(exx){
	print("The following IO problem is encountered while closing configspec.clearcase of "+pkgOfcscc+"\n"+exx);
}
return [ccAsAHash, legalSyntax];
}