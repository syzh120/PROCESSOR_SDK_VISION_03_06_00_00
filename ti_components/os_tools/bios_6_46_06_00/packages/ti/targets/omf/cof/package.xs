/*
 *  Copyright 2016 by Texas Instruments Incorporated.
 *
 */

/*
 *  ======== package.xs ========
 *
 */

function getLibs() 
{
    var mode;
    if (this.Settings.mode == this.Settings.MOTOROLA) {
        mode = "mot";
    }
    else {
        mode = "ti";
    }

    if ("findSuffix" in Program.build.target) {
        /* use findSuffix if it's supported */
        var suffix = Program.build.target.findSuffix(this);
        if (suffix != null) {
            if (suffix == "86") {
                return ("lib/" + this.profile + "/cof_" + mode + ".lib");
            }
            else {
                return ("lib/cof_" + mode + ".a" + suffix);
            }
        }
    }
    else {
        /* otherwise, use "old school" suffix naming conventions */
        var lib = "lib/cof_" + mode + ".a" + Program.build.target.suffix;
    
        if (Program.build.target.name == "VC98") {
            if (this.profile == "debug") {
                lib = "lib/debug/cof_" + mode + ".lib";
            }
            lib = "lib/release/cof_" + mode + ".lib";
        }
    
        if (java.io.File(this.packageBase + lib).exists()) {
            return (lib);
        }
    }

    /* if we get here, the library to use Cof does not exist, we siliently
     * ignore the request to use this package and let the linker complain.
     * Alternatively, We could (should?) return the name and let the config
     * step fail letting the user know that it's this package that failed.
     */
    return (null);
}
/*
 *  @(#) ti.targets.omf.cof; 1,0,0,0; 10-21-2016 18:37:05; /db/ztree/library/trees/xdctargets/xdctargets-l07/src/ xlibrary

 */

