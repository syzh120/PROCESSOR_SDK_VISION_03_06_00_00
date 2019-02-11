/******************************************************************************
 * FUNCTION PURPOSE: If the package conforms to IVersion standard, return v.r.x.p.; otherwise, return "".
 ******************************************************************************
 * DESCRIPTION: 
 *	It loads the Version.xdc module of the package name provided to extract the v.r.x.p. information. 
 *	According to the IVersion standard v.r.x.p. stands for VERSION, REVISION, XVERTICAL and PATCH.
 *	If the package conforms to the IVersion standard, its formatted v.r.x.p. info is returned.
 *	If the package does not conform to the IVersion standard, an "NOT-IVersion" is returned after logging warnings.
 *	If the package's Version module can not be loaded, "?.?.?.?" is returned after logging warnings. 
 *  string	readVersion (
 *    string	pkgName)	-Name of the package whose v.r.x.p. information is to be read.
 *****************************************************************************/
function readVersion(pkgName){
/***NOTE***/
//Until RTSC tools BUG is fixed, we have to use the following HACK
//xdc.$$make_om('cfg');  /* hack! only for xdc 2.94 access to Version modules */
xdc.om.$$bind('$$genflg', 1);

pkgName = pkgName.toString().replace(/\//g, "\."); //Allow flexibility in format of inputs
var verModNotFound = 0;
try{
	var versionMod = xdc.module(pkgName + ".Version");
} catch(e){//b/c module throws error if module is not found.
	verModNotFound = 1;
	warningBuffer.push("Trying to read Version of a package:- " + pkgName + "'s Version module could NOT be loaded\n"+e);
}
var VRXPforma;
if(verModNotFound==0){
	try{
	    if(versionMod.PKGSTD == 1)
	      var VRXP = [versionMod.MAJOR, versionMod.MINOR, versionMod.XVERTICAL, versionMod.PATCH];
	    else if(versionMod.PKGSTD == 2)
	      var VRXP = [versionMod.MAJOR, versionMod.MINOR, versionMod.PATCH, versionMod.BUILD];
	    else
	    {
	     print("Error: Old Version Interface detected. Please do a clean and build packages again");
	    }
	        
	      
		for(var elem=0; elem<VRXP.length; elem++){
			if(VRXP[elem]==null || VRXP[elem]==undefined){
				throw new Error("Could not read VRXP information of "+pkgName+" from the Version.xdc module");
			}
		}
		//Format it to the form "v.r.x.p"
		VRXPforma = VRXP[0]; //this is the formated version	
		for (var eleme=1; eleme<VRXP.length; eleme++){
			VRXPforma = VRXPforma + "." + VRXP[eleme]; 
		}		
	} catch (ex){
		warningBuffer.push("Trying to read Version of a package:- " + pkgName + 
		" does not conform to the IVersion standard. Thus V.R.X.P is set to empty string." + "\n" + ex);
		//Reset VRXPforma to empty since some exceptions were thrown in the above operations.
		VRXPforma="NOT-IVersion";  //Appropriate warnings can later be displayed (by other functions using this function) based on this return value.
	}

}else if(verModNotFound==1){
	VRXPforma = "?.?.?.?";
}
return VRXPforma;
}


function checkQuality(pkgName){

xdc.om.$$bind('$$genflg', 1);

pkgName = pkgName.toString().replace(/\//g, "\."); //Allow flexibility in format of inputs
var verModNotFound = 0;
try{
	var versionMod = xdc.module(pkgName + ".Version");
} catch(e){//b/c module throws error if module is not found.
	verModNotFound = 1;
	warningBuffer.push("Trying to read Version of a package:- " + pkgName + "'s Version module could NOT be loaded\n"+e);
	return false;
}
if(verModNotFound==0){
     if(versionMod.PKGSTD == 1)
     {
	   print("Error: Please change the Version to support latest Packaging Standard"); 
	   return false;   
	 }
	 else if(versionMod.PKGSTD == 2)
	 {
	    var Quality = versionMod.QUALITY;
	    var Btype = versionMod.BTYPE;
	    
	 }
  }
 return true; 
}	      

function returnQualityString(pkgName){

xdc.om.$$bind('$$genflg', 1);

pkgName = pkgName.toString().replace(/\//g, "\."); //Allow flexibility in format of inputs
var verModNotFound = 0;
try{
	var versionMod = xdc.module(pkgName + ".Version");
} catch(e){//b/c module throws error if module is not found.
	verModNotFound = 1;
	warningBuffer.push("Trying to read Version of a package:- " + pkgName + "'s Version module could NOT be loaded\n"+e);
	return false;
}
if(verModNotFound==0){
     if(versionMod.PKGSTD == 1)
     {
	   print("Error: Please change the Version to support latest Packaging Standard"); 
	   java.lang.System.exit(1);   
	 }
	 else if(versionMod.PKGSTD == 2)
	 {
       var quality;
       var btype;
       switch(versionMod.QUALITY)
       {
        case 0:
               quality="_prealpha";
               break;
        case 1:
               quality="_alpha";
               break; 
        case 2:
               quality="_beta";
               break; 
        case 3:
               quality="";
               break; 
        default:
               print("Error: Quality is wrongly specified in Package.version");
               java.lang.System.exit(1);
               break;
       }
       
	  
	 }
  }
 return quality; 
}	   
