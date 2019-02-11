#!/bin/bash
# Move binary files out of the directory structure because they're annoying with git

BASEDIR=apps/src/rtos
TARGETDIR=../../../../binary_store


pushd ${BASEDIR}
mkdir -p ${TARGETDIR}

C66FILES=( $(find ./ -regextype posix-egrep -regex ".*(ae66|aem4|aearp32F)") )

for file in "${C66FILES[@]}"
do
    FPATH=$(dirname "${file}")
    FPATH=${FPATH:2}
    FNAME=$(basename "${file}")
    echo "${FPATH}/${FNAME}"
    mkdir -p ${TARGETDIR}/${FPATH}
    mv -f ${FPATH}/${FNAME} ${TARGETDIR}/${FPATH}/${FNAME}
    git checkout "${FPATH}/${FNAME}"
done

popd
