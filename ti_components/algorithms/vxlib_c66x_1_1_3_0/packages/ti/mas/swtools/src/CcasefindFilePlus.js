/******************************************************************************
 * FUNCTION PURPOSE: Extend functionality of xdc's findFile() by searching across the driectory structure starting from cur. working dir.
 ******************************************************************************
 * DESCRIPTION:
 *	It uses xdc's findFile() to search for formaArgs within the System Package Path, which is  {$XDCPATH;$XDCROOT/packages;^}
 *	Here ^ is the “current” package’s repository _if_ there is a current package (otherwise ^ is empty).
 *	If findFile() returns null findFilePlus() finds the current directory and looks for formaArgs within the directory structure by a
 *	string matching procedure.
 *	It returns the full path name of formaArgs if found.
 *	It returns null if formaArgs is not found in the System Package Path & the directory structure "surrounding" the current working directory.
 *  string	findFilePlus(
 *    string	formaArgs	-name of the directory whose actual path we are looking for (this is usually a package name ...eg. ti/mas/aer)
*    )
 *****************************************************************************/
function findFilePlus(formaArgs){
xdc.om.$$bind('$$genflg', 1);
var fileModule = xdc.module('xdc.services.io.File');
var fileLoc = xdc.findFile(formaArgs);
try{
if(fileLoc==null){
	//findFile() returned null because it could not find formaArgs in the System Package Path =
	//Note that ^ is empty if current working directory is NOT A BUILT PACKAGE. In such cases we need to supply the following code that searches 
	//the directory structure for 'formaArgs' starting from the current working directory (which is not a package in this case assuming that the formaArgs directory actually exists)
	try{
		var curWorkDir = fileModule.getCanonicalPath("");
	} catch (cwdE){
		throw new Error("Problem is encountered while trying to determine the current working directory \n" + cwdE);
	}
	var cwdArray = curWorkDir.split("/");	
	var fasArray = formaArgs.split("/");
	//Mechanism:- Slide fasArray across cwdArray looking for a match!!		
	var breakOuterLoop = 0;
	for (var c=0; c<cwdArray.length; c++){
		var cand = cwdArray.slice(0,c+1).concat(fasArray);
		try{
			if(fileModule.isDirectory(cand.join("/"))){//got it!
				fileLoc = cand.join("/");
				break;
			}
		} catch (isDiE1){
			throw new Error("Problem is encountered while checking if "+cand.join("/")+" is a Directory\n" + isDiE1);
		}
		for (var f=0; f<fasArray.length; f++){					
			if(f<=c){	
				//check to see the first f 'syllables' of fasArray match the last f 'syllables' of cwdArray				
				var isSubSet = 1;	
				for(var ggg=0; ggg<=f; ggg++){
					if(fasArray[ggg]!=cwdArray[c-f+ggg]){
						isSubSet = 0;
					}
				}
				if(isSubSet == 1){
					var candSub = cwdArray.slice(0,c+1).concat(fasArray.slice(f+1));
					try{
						if(fileModule.isDirectory(candSub.join("/"))){//got it!
							fileLoc = candSub.join("/");
							breakOuterLoop=1;
							break;
						}
					} catch (isDiE2){
						throw new Error("Problem is encountered while checking if "+candSub.join("/")+" is a Directory\n" + isDiE2);
					}
				}
			}
		}
		if(breakOuterLoop==1){
			break;
		}
	}
	//If fileLoc remains null after all this search across the directory structure...
	if(fileLoc==null){
		throw new Error("Folder ("+formaArgs+") is NOT found in \n(1)$XDCPATH,\n(2)$XDCROOT/packages, \n"+
						"(3) the current package's repository (if the current directory is a package),...and finally\n"+
						"(4) the directory structure based around the current working directory!\n");
	}
}
} catch (e){
	print(e);
}
return fileLoc;
}