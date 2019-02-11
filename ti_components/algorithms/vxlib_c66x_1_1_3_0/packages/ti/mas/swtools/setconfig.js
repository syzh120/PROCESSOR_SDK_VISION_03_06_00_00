  if(environment['xdc.hostOS'] == undefined)
  {
    environment["xdc.hostOS"] = java.lang.System.getProperty("os.name") + "";
    if (environment["xdc.hostOS"].match(/^Windows/i)) {
        environment["xdc.hostOS"] = "Windows";
    }

  }
  
  var fileModule = xdc.module('xdc.services.io.File');
  var fileName = "tempcfg.bat";
  var Mode = "w";
  var openedFile = fileModule.open(fileName, Mode);
  if(openedFile == undefined)
  {
       print("Unable to create "+ fileName+", Please check your write Permission");
       java.lang.System.exit(2);
 }  
 /* Config.bld Path */
  var path = xdc.findFile("config.bld");
  if( path )
  {
    /* print path */
    path=path.toString().replace(/\\/g, "/");
    var command="set XDCBUILDCFG="+ fileModule.getDOSPath(path);
    openedFile.writeLine(command+"\n");
    openedFile.writeLine("");
  }
 else
  { 
    print(" Error: config.bld not found in swtools directory");
    java.lang.System.exit(1);
  }
 /* Root of ti folder */  
 var path = xdc.findFile("ti//mas//swtools");
 var abspath = path.split("\\ti");
 if(path)
  {
    /* print path */
    abspath[0]=abspath[0].toString().replace(/\\/g, "/");
    var command="set MAS_INSTALL_DIR="+ fileModule.getDOSPath(abspath[0]);
    openedFile.writeLine(command+"\n");
    openedFile.writeLine("");
    var command="set XDCPATH=%XDCPATH%;%MAS_INSTALL_DIR%";
    openedFile.writeLine(command+"\n");
    openedFile.writeLine("");
  }
 else
  { 
    print(" Error: ti//mas//swtools folder not found in the XDCPATH");
    java.lang.System.exit(1);

  }
  openedFile.close()
  