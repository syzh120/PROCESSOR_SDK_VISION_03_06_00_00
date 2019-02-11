/*
 *  ======== Package.getLibs ========
 *  This function is called when a program's configuration files are
 *  being generated and it returns the name of a library appropriate
 *  for the program's configuration.
 */

function getLibs(prog)
{
    /* get necessary module references */
    var GMACSW     = xdc.module('ti.nsp.drv.GMACSW');
    var NDK        = xdc.module('ti.ndk.config.Global');

    /* determine the lib's suffix-based directory name */
    var suffix      = prog.build.target.suffix;
    var libSuffix   = ".a" + suffix;
    var libsList    = "";
    var libs        = [];

    /* append "e" to lib name for big endian builds */
    libSuffix += (prog.build.target.model.endian == "little") ? "" : "e";
    
    if ((GMACSW.$used) && (NDK.$used))
    {
        var libName = this.$name + ".ndk2nsp";
        var lib = "";

        if (GMACSW.tfdtpBuild)
        {
            /* If TFDTP build is enabled, include TFDTP library and TFDTP+NDK2NSP library */
            {
                /* Include TFDTP library */
                var libName = this.$name + ".tfdtp";
                var lib = "";
        
                if (GMACSW.instrumentedBuild)
                {
                    libName += "_instr";
                }
        
                var profile = ((this.profile + "").match(/whole_program/)) ?
                    "release" : this.profile;
        
                lib = "lib/" + profile + "/" + libName + libSuffix;
        
                if (java.io.File(this.packageBase + lib).exists())
                {
                    print("Inside NSP Driver Package getLibs:");
                    print("\twill link with library: " + lib);
                    libs = libs.concat([""+lib,]);
                }
                else
                {
                    /* could not find any library, return null */
                    print("Error: Library not found: " + lib);
                    return null;
                }
            }

            /* Include TFDTP+NDK2NSP library */
            libName = this.$name + ".ndktfdtp2nsp";
            lib = "";
            if (GMACSW.instrumentedBuild)
            {
                libName += "_instr";
            }            
        }
        else if (GMACSW.instrumentedBuild)
        {
            libName += "_instr";
        }

        var profile = ((this.profile + "").match(/whole_program/)) ?
            "release" : this.profile;

        lib = "lib/" + profile + "/" + libName + libSuffix;

        if (java.io.File(this.packageBase + lib).exists())
        {
            print("Inside NSP Driver Package getLibs:");
            print("\twill link with library: " + lib);
            libs = libs.concat([""+lib,]);
        }
        else
        {
            /* could not find any library, return null */
            print("Error: Library not found: " + lib);
            return null;
        }
    }

    if (GMACSW.$used)
    {
        var libName = this.$name + ".gmacsw";
        var lib = "";

        if (GMACSW.instrumentedBuild)
        {
            libName += "_instr";
        }

        var profile = ((this.profile + "").match(/whole_program/)) ?
            "release" : this.profile;

        var device = "";

        switch (GMACSW.device)
        {
            case GMACSW.DEVICE_VAYU:
                device = "vayu";
                break;
            case GMACSW.DEVICE_TDA3XX:
                device = "vayu";
                break;                
            case GMACSW.DEVICE_J5ECO:
                device = "j5eco";
                break;
            case GMACSW.DEVICE_DM385:
                device = "j5eco";
                break;
            case GMACSW.DEVICE_SUBARCTIC:
                device = "j5eco";
                break;
            case GMACSW.DEVICE_CENTAURUS:
                device = "centaurus";
                break;
        }

        lib = "lib/" + device + '/' + profile + "/" + libName + libSuffix;

        if (java.io.File(this.packageBase + lib).exists())
        {
            print("Inside NSP Driver Package getLibs:");
            print("\twill link with library: " + lib);
            libs = libs.concat([""+lib,]);
        }
        else
        {
            /* could not find any library, return null */
            print("Error: Library not found: " + lib);
            return null;
        }
    }

    // careful: some versions of XDC don't like trailing ; in list of libs
    for (i in libs)
    {
        if (libsList != "")
        {
            libsList += ";" + libs[i];
        }
        else
        {
            libsList = libs[i];
        }
    }

    return libsList;
}

