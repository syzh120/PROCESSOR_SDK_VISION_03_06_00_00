/*
 * Copyright (c) 2012, Texas Instruments Incorporated
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * */
/*
 *  ======== usingPackage ========
 */
function usingPackage(packageName)
{
    var packageUsed = false;
    var packageFound = false;
    var pkgList = $om.$packages;

    for (var i = 0; i < pkgList.length; i++) {

        if (pkgList[i] == packageName) {

            packageFound = true;

            for (var j = 0; j < pkgList[i].$modules.length; j++) {

                if (pkgList[i].$modules[j].$used) {
                    packageUsed = true;
                    break;
                }
            }

            break;
        }
    }

    if (!packageUsed) {
        return (false);
    }
    return (true);
}

/*
 * ======== compareArray =======
 */
function compareArray(array1, array2)
{
    var length = array1.length;

    if (array2.length > length) {
        length = array2.length;
    }

    for (i = 0; i < length; i++) {
        if (array1[i] != array2[i]) {
            return (0);
        }
    }
    return (1);
}

function arrayUndef(Array1)
{
    var status = true;
    for (i =0 ; i < Array1.length; i++) {
        if (undefined != Array1[i]) {
            return false;
        }
    }
    return status;
}

/*
 *  ======== usingPackageIn ========
 */
function usingPackageIn(pathName)
{
    var packageUsed = false;
    var packageFound = false;
    var pkgList = $om.$packages;
    var match;
    var pkgArray = new Array;
    var count = 0;

/*      print("GUNMOD: pathName " + pathName);*/

    for (i = 0; i < pkgList.length; i++) {

/*          var pkg = new String(pkgList[i]);*/
         var pkg = pkgList[i].$name;

/*           print("GUNMOD: pkg " + pkg);*/
         match = pkg.substring(0,14);

          if ( pathName == match ) {

/*              print("GUNMOD: Found a match " + pkg);*/
            packageFound = true;

            pkgArray[count] = pkgList[i];
            count++;

/*
            for (var j = 0; j < (pkgList[i]).$modules.length; j++) {

                print("GUNMOD: pkgList modules " + pkgList[i].$modules[j]);

                if ((pkgList[i]).$modules[j].$used) {
                    packageUsed = true;
                    print("GUNMOD: Package is used " + pkg);
                    pkgArray[count] = pkgList[i];
                    count++;
                }
            }
*/
         }
    }

/*     if (!packageUsed) {*/
    if (!packageFound) {
        return (null);
    }
    return (pkgArray);
}
