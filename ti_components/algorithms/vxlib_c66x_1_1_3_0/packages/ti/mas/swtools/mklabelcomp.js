/* 
  xs -f mklabel.js {-nrecurse} {-replace} {COMP_ROOT=....} [LABEL=....] comp1,comp2,comp3....
*/

// function mklabel(arguments)
function getargs(arguments)
{
var optargs={};
var compargs={};
for each( var arg in arguments )
  {
    if (arg.indexOf("-") == 0)
     {
       if (arg == "-replace")
        {
            replace=" -replace";
        }
       if (arg == "-nrecurse")
        {
            recurse="";
        }
     }
     if (/=/.test(arg))
       {
         optargs=arg.split(/=/);
         print (optargs[0]+" = "+optargs[1]); 
         if (optargs[0]=="COMP_ROOT")
          {
             comproot=optargs[1];
             if (fileExists(comproot))
               {
//                 comproot=comproot.replace(/^.:/,"");
                 continue;
               }
             else
               {
                  print("\n\tERROR: Specified Component root \"" + comproot + "\" doesnot exist. Exiting....\n"); 
                  failure=1;
               }
          }
         if (optargs[0]=="LABEL_PREFIX")
          {
             if (/^\s*$/.test(optargs[1]))
               {
                  failure=2;
               }
             else
               {
                   label_prefix=optargs[1].toUpperCase();
                   if (!((label_prefix=="DEV") || (label_prefix=="FCHK")))
                      {
                        failure=4;
                        break;
                      }
               }
          }
         if (optargs[0]=="COMPONENT")
          {
             if (/^\s*$/.test(optargs[1]))
               {
                  failure=3;
               }
             comps=optargs[1];

// The compargs array was created with the idea of labeling multiple components in mind. But we do not have to change the array to make it a variable because the logic still works now with only 1 component being labeled.

             compargs[0]=optargs[1];
             var compname=compargs[0];
             compargs[0]=compname.toString().replace(/\./g, "\\");
             complabelpart=compname.toString().replace(/\./g, "_");
             complabelpart=complabelpart.toUpperCase();
             for (var comp in compargs)
               {
                  var fullcomppath=comproot+"\\"+compargs[comp];
                  if (fileExists(fullcomppath))
                    {
// The following paramarr array is created because the function "formatArgument(rawArg, rule)" in the Ccaseformatargument.js file expects the "rawArg" argument to be an array. If we give a string input, the rawArg.length gives the length of the string (Generally more than 2) and the function fails.
                      var paramarr=[];
                      paramarr[0]=compname;
                      version=readVersion(paramarr);
                      if(checkQuality(paramarr)==false && label_prefix=="DEV")
                      {
                        java.lang.System.exit(1);
                      }
                      if( version == "?.?.?.?" || version == undefined)
                      {
                        print("Error: Version of the package could not be found. Please make sure the package is build before running the script again \n");
                        java.lang.System.exit(1);
                                              
                      }
                      version=version.toString().replace(/\s/g, "");
                      version=version.toString().replace(/\,/g, ".");
                      version=version.toString().replace(/\./g, "_");
                      if (curdir!=comproot)
                        {
                          fullpathcomps[fullpathcomps.length]=fullcomppath;
                        } 
                    }
                  else
                    {
                       print ("\n\tERROR:: COMPONENT "+compargs[comp]+" DOES NOT EXIST UNDER "+comproot+"\n");
                       failure=3;
                    }
               }
               if (curdir!=comproot)
                  {
                     comps=fullpathcomps.join(" ");
                  }
            } 
       }
  } // End main for loop
  
  if ((label_prefix=="") || (complabelpart=="") || (version==""))
    {
       failure=3;
    }
  else
    {
      if(label_prefix != "FCHK")
      {
        label=label_prefix+"_"+complabelpart+"_"+version;
      }
      else
      {
        label=label_prefix+"_"+complabelpart+"_"+version+"_"+year+month+day+myChar;
      }
    }
  var co=findcheckouts(fullcomppath);
  
  if (co==-1)
    {
       print(compname+" IS NOT UNDER CLEARCASE SOURCE CONTROL. LABELING TERMINATED...\n");
       failure=7;
    }
  else if (co==1)
    {
       print("WARNING:::: CHECKOUTS WERE FOUND UNDER "+fullcomppath+".\nPLEASE CHECKIN ALL CHECKOUTS IN THE COMPONENT TO BE LABELED IN THIS VIEW AND RESTART THE LABELING\n");
       failure=6;
    }
  if (comps=="")
    {
      print ("\n\nERROR:: Valid component not specified...\n");
      failure=3;
    }
  if (label=="")
    {
      print ("\n\nERROR:: Valid Label not specified...\n");
      failure=2;
    }
  else if (failure==0)
    {
      mklbtype(label,comproot);
    }
  if (comproot=="\.")
    {
       comproot=curdir;
    }
}

function fileExists(filename)
 {
   f = new java.io.File(filename);
   return f.exists(); 
 }

function currentdir()
 {
     dir1 = new java.io.File (".");
     try 
       {
          return(dir1.getCanonicalPath());
       }
     catch(err) 
       {
          print("\n\tERROR IN currentdir() FUNCTION: "+err.description+"\n");
       }
  }
    
function usage()
 {
     print("\n\tUSAGE:\n");
     print("\t\txs -f mklabel.js {-nrecurse} {-replace} {COMP_ROOT=<Full path to the root of the component tree>} [LABEL=<Label name>] [COMPONENT=comp]\n");
  }

function mklbtype(labelname,comproot)
{
   var stat={}; 
   var patharr=comproot.split(/\\/);
   vob="\\"+patharr[1];
   var command="c:\\progra~1\\rational\\clearcase\\bin\\cleartool.exe mklbtype -nc "+label+"@"+vob;
   print("Creating label type \""+labelname+"\" in VOB "+vob+"\n");
   xdc.exec(command,null,stat);
   var pat="cleartool: Error: Name \""+labelname+"\" already exists";
   if ((stat.output).match(pat) && (replace=="") && (label_prefix == "DEV"))
      {
         failure=5;
      }
   if(label_prefix == "FCHK")  
   {
     while((stat.output).match(pat))
     {
       print("Label type \""+label+"\"already exists in VOB "+vob+"\n");
       myChar=incrementLetter(myChar);
       if(myChar == "A")
       {
         failure=5;
         break;
       }
       else
       {
         label=label_prefix+"_"+complabelpart+"_"+version+"_"+year+month+day+myChar;  
         command="c:\\progra~1\\rational\\clearcase\\bin\\cleartool.exe mklbtype -nc "+label+"@"+vob;
         var pat="cleartool: Error: Name \""+label+"\" already exists";
         print("Creating label type \""+label+"\" in VOB "+vob+"\n");
         xdc.exec(command,null,stat);
         print(stat.output);
       }
       
     }
   }
}

function makeArray() {
     for (i = 0; i<makeArray.arguments.length; i++)
          this[i + 1] = makeArray.arguments[i];
}

function findcheckouts(comproot) 
  {
     var lscocmd="c:\\progra~1\\rational\\clearcase\\bin\\cleartool.exe lsco -r -cview -s "+comproot; 
     print("Checking for Checkouts under "+comproot+"\n");
     xdc.om.$$bind('$$genflg', 1);
     xdc.exec(lscocmd,null,status);
     if (/Not a vob object/.test(status.output))
       {
          return(-1);
       }
     if (status.output!="")
       {
          print("The following files are checkedout in the current view under "+comproot+":\n\n"+status.output);
          return(1);
       }
     return(0);
  }
  
//create a string containing all letters
var alphaChars = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

//initialize a test character to 'A'
var myChar = "A";

//this function accepts a character, increments it
//by one, and returns it
function incrementLetter(letterToIncrement){

 //find where the letter is at in the alphaChars string
 var indexOfLetter = alphaChars.search(letterToIncrement);

 //if it's not the last letter, then return the next
 //letter in the string
 if (indexOfLetter+1 < alphaChars.length) {
   return(alphaChars.charAt(indexOfLetter+1));
 }

 //otherwise return the input letter
 else{
   return("A");
 }
}
  

/* MAIN ROUTINE FROM HERE */

var args={};
var params=[];
var replace="";
var recurse=" -recurse";
var comproot=".";
var label="";
var complabelpart="";
var comps="";
var fullpathcomps=[];
var failure=0;
var curdir=currentdir();
var status={};
var out;
var day;
var year;
var month;
var hour;
var minutes;
var versionName;
var date=new java.util.Date();
var months = new makeArray('January','February','March', 'April','May','June','July','August','September', 'October','November','December');
var vob;
var warningBuffer = new Array();
year=date.getYear();
year+=1900;
month=date.getMonth();
month+=1;
if(month < 10)
{
 month = "0"+month;
}
hour=date.getHours();
day=date.getDate();
if(day < 10)
{
 day = "0"+day;
}
minutes=date.getMinutes();
var version;
var outputFileName;
utils.importFile("src/CcasereadVersion.js");
if(arguments.length == 0)
{
  print("USAGE:");
  print("xs -f mklabelcomp.js  COMP_ROOT=\\dsps_gtmas COMPONENT=ti.mas.xxx LABEL_PREFIX=DEV/FCHK\n");
  java.lang.System.exit(1);
}
for each( var arg in arguments )
  {
     params[params.length]=arg;
  }

print ("Current date is " + java.util.Date());
// mklabel(params);
getargs(params);

if (failure==0)
   {
      outputFileName="c:\\temp\\"+label+"_"+months[month]+"_"+day+"_"+year+"_"+hour+"_"+minutes+".txt";
      var tmppath="\\";
      var count=0;
      var paths=[];
      for each (var path in comps.split(/\\/))
        {
          if (/^$/.test(path))
             {
               continue;
             }
          else
             {
                paths[paths.length]=path;
             }
        }
      var pathlength=paths.length;
      for each (var path in paths)
        {
          tmppath+=path;
          count++;
          if ((/^.:$/.test(tmppath)) || (/^\\$/.test(tmppath)) || (/^\s*$/.test(tmppath)))
           {
              tmppath+="\\";          
              continue;
           }
          print("Applying the label \""+label+"\" on "+tmppath+"\n");
          if (count!=pathlength)
           {
             var command="c:\\progra~1\\rational\\clearcase\\bin\\cleartool.exe mklabel"+" "+replace+" "+" "+label+" "+tmppath;
           }
          else
           {
            var command="c:\\progra~1\\rational\\clearcase\\bin\\cleartool.exe mklabel"+" "+replace+" "+recurse+" "+label+" "+comps;
           }
          xdc.exec(command,{outName: outputFileName},"-");
          tmppath+="\\";          
        }
   }
else if (failure==3)
   {
      print("\n\tERROR: Component is empty. Exiting....\n"); 
   }
else if (failure==4)
   {
     print("ERROR: Illegal Label prefix used.\nPlease use only \"DEV\" or \"FCHK\" label prefixes.");
   }
else if (failure==5)
   {
     print("Label \""+label+"\" already exists in VOB "+vob+"\n");
     print("Please use the -replace option to do relabeling\n");
   }
else if (failure==6)
   {
     print("Please Checkin the elements and restart the labeling\n");
   }
else if (failure==7)
    {
       print(compname+" IS NOT UNDER CLEARCASE SOURCE CONTROL. LABELING TERMINATED...\n");
    }
else
   {
      usage();
   }
if (fileExists(outputFileName))
print("Log of the labeling is at "+outputFileName+"\n");
