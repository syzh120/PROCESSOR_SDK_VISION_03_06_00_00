#!/bin/bash
#
#  ======== validateROM ========
#
#  Compare the newly built ROM with the golden ROM and
#  generate an error if a mismatch is found.
#

NM2000=$TOOLS/vendors/ti/c28/6.1.0/Linux/bin/nm2000
TMPDIR=$(pwd)/ValidateROM
mkdir $TMPDIR

DEVICE=F28004x
ROMDIR=$TMPDIR/$DEVICE

mkdir $ROMDIR

#  Compare new sysbios.lib and golden sysbios.lib's function list
#$NM2000 -t  golden/$DEVICE/sysbios.a28FP | grep " .text" | sort > golden/$DEVICE/sysbios_lib_funcs
$NM2000 -t  $DEVICE/sysbios.a28FP | grep " .text" | sort > $DEVICE/sysbios_lib_funcs
diff golden/$DEVICE/sysbios_lib_funcs $DEVICE/sysbios_lib_funcs > $ROMDIR/libDiff

read line <$ROMDIR/libDiff

if [ -n "$line" ]; then
    echo Error $DEVICE ROM LIBRARY VALIDATION FAILED: New $DEVICE ROM library does not match the golden ROM library
    echo diffs:
    echo
    cat $ROMDIR/libDiff
    echo 
    echo If new $DEVICE/sysbios.a28FP library is ok, copy it to golden/$DEVICE
    rm -rf $TMPDIR
#    exit 1
    exit 0
fi

echo $DEVICE ROM VALIDATION PASSED

# copy newly validated sysbios.a28FP library to golden dir
# cp $DEVICE/sysbios.a28FP golden/$DEVICE/sysbios.a28FP

# commit new validated golden library
if [[ $USER == "xlibrary" ]]
then
    lockFlag=1;
    while [ $lockFlag -eq 1 ]
    do
        while [ -e ../../../../../.git/index.lock ]
        do
            sleep 1
        done
        git ls-files -m | grep golden/$DEVICE/sysbios_lib_funcs
        if [ $? -eq 0 ]
        then
            git commit golden/$DEVICE/sysbios_lib_funcs -m "Latest $DEVICE sysbios_lib_funcs file"
            if [ $? -eq 0 ]
            then
                lockFlag=0;
            fi
        else
            lockFlag=0;
        fi
    done
fi

#  Cleanup before exiting
rm -rf $TMPDIR
exit 0
