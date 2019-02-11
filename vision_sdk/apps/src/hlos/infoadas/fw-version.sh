#!/bin/bash -x

cat > VERSION.txt <<EOF
DATE=>`date`
Firmware Version=>$fw_VERS
Commit-id: vision_sdk=>
`git log -n2 --oneline --decorate 2> /dev/null | tail -n1`
`git diff --shortstat 2> /dev/null | tail -n1`
Commit-id: Starterware=>
`git --git-dir=$starterware_PATH/../.git --work-tree=$starterware_PATH/.. log -n1 --oneline --decorate`
`git --git-dir=$starterware_PATH/../.git --work-tree=$starterware_PATH/.. diff --shortstat 2> /dev/null | tail -n1`
Commit-id: BIOS BSP=>
`git --git-dir=$bsp_PATH/../.git --work-tree=$bsp_PATH/.. log -n1 --oneline --decorate`
`git --git-dir=$bsp_PATH/../.git --work-tree=$bsp_PATH/.. diff --shortstat 2> /dev/null | tail -n1`
EOF
