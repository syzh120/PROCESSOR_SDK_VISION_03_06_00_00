/*
 *  ======== _copyFile ========
 */
 
function File(srcFile, dstDir)
{
    srcFile=java.io.File(srcFile);
    var dstFile = java.io.File(dstDir + '/' + srcFile.getName());
	if(dstFile.getParentFile() != null)
	{
      dstFile.getParentFile().mkdirs();
	}


    var outs;
    var ins;
    try {
        outs = new java.io.FileOutputStream(dstFile);
        ins = new java.io.FileInputStream(srcFile);
    }
    catch (e) {
        if (ins) ins.close();
        if (outs) outs.close();
        throw new Error(e.message);
    }

    var inc = ins.getChannel();
    var outc = outs.getChannel();
    inc.transferTo(0, inc.size(), outc);

    ins.close();
    outs.close();
}

function Move(srcFile, dstFile)
{
    srcFile=java.io.File(srcFile);
    var dstFile = java.io.File(dstFile);
	if(dstFile.getParentFile() != null)
	{
      dstFile.getParentFile().mkdirs();
	}

    var outs;
    var ins;
    try {
        outs = new java.io.FileOutputStream(dstFile);
        ins = new java.io.FileInputStream(srcFile);
    }
    catch (e) {
        if (ins) ins.close();
        if (outs) outs.close();
        throw new Error(e.message);
    }

    var inc = ins.getChannel();
    var outc = outs.getChannel();
    inc.transferTo(0, inc.size(), outc);

    ins.close();
    outs.close();
    srcFile["delete"]();
}

/*
 *  ======== _copyDirectory ========
 */
function Directory(dirFile, destDir)
{
    var status = '';
    dirFile=java.io.File(dirFile);    
    for each (var f in dirFile.listFiles()) {
        if (!f.isDirectory()) {
            try {
                File(f, destDir);
            }
            catch (e) {
                status = "Cannot copy file " +
                         f.getCanonicalPath() + "\n" +
                         e.message;
                break;                            
            }
        }
        else {
            if (f.listFiles().length) {
                    status = Directory(f, 
                             destDir + '/' + f.getName());
                    if (status.length) {
                        break;
                    }
            }
            else {
                java.io.File(destDir + '/' + f.getName()).mkdirs();
            }
        }
    }
    return (status);
}

function deleteDir(dir) {
    var dir = java.io.File(dir);
    var files = dir.list();
    for (var i = 0; i < files.length; i++) {
        var f = java.io.File(dir, files[i]);
        if (f.isDirectory()) {
            deleteDir(f);
        }
        else {
            f["delete"]();
        }
    }
    dir["delete"]();
}