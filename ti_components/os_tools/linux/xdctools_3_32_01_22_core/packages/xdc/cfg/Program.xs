/* 
 *  Copyright (c) 2008 Texas Instruments and others.
 *  All rights reserved. This program and the accompanying materials
 *  are made available under the terms of the Eclipse Public License v1.0
 *  which accompanies this distribution, and is available at
 *  http://www.eclipse.org/legal/epl-v10.html
 * 
 *  Contributors:
 *      Texas Instruments - initial implementation
 * 
 * */
var _asmMap = {};
var _pkgTab = [];

var _targMods = [];

/*
 *  ======== _close ========
 */
function _close()
{
    var asmvec = this.$$bind('$$asmvec', []);
    for (var a in _asmMap) {
        /* This code won't work correctly when the name of the assembly
         * relative to its base package contains more than one level. If
         * the name is pkg.subdir.a, the code below will look for
         * pkg/subdir/package/cfg/a, instead of pkg/package/cfg/subdir/a.
         * So, we need to know here the name of the package or require that
         * assemblies are not in subdirectories.
         */
        var k = a.lastIndexOf('.');
	/* If there is a '.' in the assembly name, we assume it separates
	 * components of the package name and the last '.' separates
  	 * the assembly name from the name of its containing package.
	 */
	var fn;
	if (k != -1) {
            fn = a.substring(0, k).replace(/\./g, '/') + '/package/cfg/' +
                a.substring(k + 1) + '.p' + this.build.target.suffix + '.obj';
	}
	else {
	    fn = "./package/cfg/" + a + ".p" + this.build.target.suffix +
	        '.obj';
	}
        var path = xdc.jre.xdc.services.global.Path.search(fn);
        asmvec.push(path);
    }

    var isasm = this.$$isasm && asmvec.length > 0 ? 1 : 0;

    for (var i = 0; i < xdc.om.$packages.length; i++) {
        var pkg = xdc.om.$packages[i].$orig;
        pkg.$$bind('$$genflg', isasm);
    }

    for (var i = 0; i < xdc.om.$modules.length; i++) {
        var mod = xdc.om.$modules[i];
        if (!mod.$hostonly && mod.$used && !mod.$$nortsflag) {
            _targMods.push(mod);
        }
    }
}

/*
 *  ======== exportModule ========
 */
function exportModule(modName)
{
    var mod = xdc.useModule(modName);
    mod.$$bind('$$scope', 1);
}

/*
 *  ======== getSectMap ========
 */
function getSectMap()
{
    var sectMap = {};
    for (sn in this.build.target.sectMap) {
        var space = this.build.target.sectMap[sn];

        sectMap[sn] = new this.SectionSpec();
        sectMap[sn].loadSegment = this.platform[space + "Memory"];
    }

    for (sn in this.platform.sectMap) {
         /* platform may override target */
        sectMap[sn].loadSegment = this.platform.sectMap[sn];
    }

    for (sn in this.sectMap) {
        /* prog may override platform and target */
        if (typeof(this.sectMap[sn]) == "string" || this.sectMap[sn] == null) {
            if (this.sectMap[sn] == null) {
                Program.$logWarning("Entry for the section '" + sn + "' in "
                    + "Program.sectMap is set to 'undefined'. This section "
                    + "allocation will be ignored.", Program.sectMap);
            } 
            sectMap[sn] = new this.SectionSpec();
            sectMap[sn].loadSegment = this.sectMap[sn];
        }
        else if (typeof(this.sectMap[sn]) == "object") {
            sectMap[sn] = new this.SectionSpec(this.sectMap[sn]);
            if (this.sectMap[sn].loadSegment == null
                && this.sectMap[sn].runSegment == null
                && this.sectMap[sn].loadAddress == null
                && this.sectMap[sn].runAddress == null
                && this.sectMap[sn].type != "COPY"
                && this.sectMap[sn].type != "DSECT") {
                Program.$logWarning("Entry for the section '" + sn + "' in "
                    + "Program.sectMap is set to 'undefined'. This section "
                    + "allocation will be ignored.", Program.sectMap[sn]);
            }
            
        }
    }
    
    /* one more loop to figure out if we have '|' entries and pages */
    for (sn in sectMap) {

        /* segment may include more than one memory name separated by '|' */
        if (sectMap[sn].loadSegment != null) {
            var ma = sectMap[sn].loadSegment.split(/[\s\|]+/);
            var result = "";
            var page = "";
            for (var i = 0; i < ma.length; i++) {
                var mem = null;
                for (var j = 0; j < this.cpu.memoryMap.length; j++) {
                    if (ma[i] == this.cpu.memoryMap[j].name) {
                        mem = this.cpu.memoryMap[j];
                    }
                }

                if (mem != null) {
                    result += (i == 0 ? '' : " | ") + mem.name;
                    if (mem.page != null) {
                        page = ' PAGE ' + mem.page;
                    }
                }
                else {
                    result += (i == 0 ? '' : " | ") + ma[i];
                }
            }
            sectMap[sn].loadSegment = result + page;
        }

        if (sectMap[sn].runSegment == null) {
            continue;
        }
        var ma = sectMap[sn].runSegment.split(/[\s\|]+/);

        var result = "";
        var page = "";
        for (var i = 0; i < ma.length; i++) {
            var mem = null;
            for (var j = 0; j < this.cpu.memoryMap.length; j++) {
                if (ma[i] == this.cpu.memoryMap[j].name) {
                    mem = this.cpu.memoryMap[j];
                }	
            }
            if (mem != null) {
                result += (i == 0 ? '' : " | ") + mem.name;
                if (mem.page != null) {
                    page = ' PAGE ' + mem.page;
                }
            }
            else {
                result += (i == 0 ? '' : " | ") + ma[i];
            }
        }
        sectMap[sn].runSegment = result + page;
    }

    /* The final check to remove all entries that are 'null' for all
     * relevant properties.
     */
    for (var sn in sectMap) {
        if (sectMap[sn].loadSegment == null && sectMap[sn].runSegment == null
            && sectMap[sn].loadAddress == null
            && sectMap[sn].runAddress == null && sectMap[sn].type == null) {
            delete sectMap[sn];
        }
    }    
    return (sectMap);
}

/*
 *  ======== importAssembly ========
 */
function importAssembly(asmName)
{
    Program.system = null;
    if (_asmMap[asmName]) {
        return;
    }

    _asmMap[asmName] = true;
}

/*
 *  ======== instSize ========
 */
function instSize(inst)
{
    var mod = inst.$module;
    var nmSz = 0;

    var named = mod.common$.namedInstance;
    named |= mod.common$.namedInstance === undefined && xdc.module('xdc.runtime.Defaults').common$.namedInstance;

    if (named) {
        nmSz = Program.build.target.stdTypes['t_Ptr'].size;
    }

    return mod.Instance_State.$sizeof() + nmSz;
}

/*
 *  ======== targetModules ========
 */
function targetModules()
{
    return _targMods;
}

/*
 *  ======== freezeRomConfig ========
 */
function freezeRomConfig(modName, cfgName)
{
}

/*
 *  ======== freezeRomConfig2 ========
 */
function freezeRomConfig2(mod, cfgName)
{
}

/*
 *  ======== freezeRomParams ========
 */
function freezeRomParams(mod)
{
}

/*
 *  ======== frozenRomConfig ========
 */
function frozenRomConfig(modName, cfgName)
{
    return (false);
}

/*
 *  ======== frozenRomConfig2 ========
 */
function frozenRomConfig2(mod, cfgName)
{
    return (false);
}
/*
 *  @(#) xdc.cfg; 1, 0, 2,0; 7-26-2016 11:44:55; /db/ztree/library/trees/xdc/xdc-B21/src/packages/
 */

