#
#  Copyright 2013 by Texas Instruments Incorporated.
#  
#

#!/bin/sh

#
#  Copyright (c) 2006-2012, Texas Instruments Incorporated
#  All rights reserved.
#
#  Redistribution and use in source and binary forms, with or without
#  modification, are permitted provided that the following conditions
#  are met:
#
#  *  Redistributions of source code must retain the above copyright
#     notice, this list of conditions and the following disclaimer.
#
#  *  Redistributions in binary form must reproduce the above copyright
#     notice, this list of conditions and the following disclaimer in the
#     documentation and/or other materials provided with the distribution.
#
#  *  Neither the name of Texas Instruments Incorporated nor the names of
#     its contributors may be used to endorse or promote products derived
#     from this software without specific prior written permission.
#
#  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
#  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
#  THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
#  PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
#  CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
#  EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
#  PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
#  OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
#  WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
#  OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
#  EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
#
#

# startqti - shell script to let users run QualiTI without worrying about XDCPATH setup
#
# See packages/ti/xdais/quality/README.txt for further QualiTI documentation.
#
# Pls ensure XDC tools are in your path via e.g.
# [>] export PATH=$PATH:/home/user/xdc_3_00_05
#

#-----------------------------------------------------------------------------
# If no "xs" executable, then quit
#-----------------------------------------------------------------------------
which xs > /dev/null
if [ $? -ne 0 ]
then
   echo 'xs command not in the path, giving up ...'
   echo 'Pls add XDC tools to your path e.g. [>] export PATH=$PATH:/home/user/xdc_3_00_05'
   exit 1
fi

echo 'QualiTI user: You can ignore any warnings below about Mozilla this or that missing.'
xs --xdcpath=`dirname $0`/packages ti.xdais.wizards.genalg -g $1 $2 $3 $4 $5 $6 $7 $8 $9

#
#  @(#) xdais_7_24_00_04; 1, 0, 0,1; 5-20-2013 12:17:15; /db/wtree/library/trees/dais/dais-x04/src/ xlibrary

#

