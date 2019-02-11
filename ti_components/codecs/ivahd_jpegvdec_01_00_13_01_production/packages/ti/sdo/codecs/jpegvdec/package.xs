/*
 *  ======== package.xs ========
 *
 */

/*
 *  ======== getLibs ========
 */
function getLibs(prog)
{
    var lib = null;
  
    if (prog.build.target.isa == "v7M") {        
        if ( this.JPEGVDEC.watermark == false ) {
                lib = "lib/jpegvdec_ti_host.lib";
        }
        else {
                lib = null;
        }
        print("    will link with " + this.$name + ":" + lib);
    }
    return (lib);
}

/*
 *  ======== getSects ========
 */
function getSects()
{
    var template = null;

   if (prog.build.target.isa == "v7M" || prog.build.target.isa == "v7M4") {
        template = "ti/sdo/codecs/jpegvdec/link.xdt";
    }

    return (template);
}
