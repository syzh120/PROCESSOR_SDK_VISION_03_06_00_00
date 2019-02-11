#!/bin/bash
# Restore binaries previously moved out of the tree, for instance when they are needed to rebuild
# non-A15 code

BASEDIR=../binary_store
TARGETDIR=../vision_sdk/apps/src/rtos

pushd ${BASEDIR}

C66FILES=( $(find ./ -regextype posix-egrep -regex ".*(ae66|aem4|aearp32F)") )

for file in "${C66FILES[@]}"
do
    FPATH=$(dirname "${file}")
    FPATH=${FPATH:2}
    FNAME=$(basename "${file}")
    echo "${FPATH}/${FNAME} to ${TARGETDIR}/${FPATH}/${FNAME}"
    mkdir -p ${TARGETDIR}/${FPATH}
    mv -f ${FPATH}/${FNAME} ${TARGETDIR}/${FPATH}/${FNAME}
done

popd
