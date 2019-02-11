#!/bin/bash

export PATHS_SET=TRUE
export DEBUGSERVER=~/ccs/ccsv5/ccs_base/DebugServer
export PATH=$PATH:$DEBUGSERVER/../scripting/
export PATH=$PATH:$DEBUGSERVER/../common/
export PATH=$PATH:$DEBUGSERVER/packages/
export PATH=$PATH:$DEBUGSERVER/packages/ti
export PATH=$PATH:$DEBUGSERVER/packages/ti/dss
export PATH=$PATH:$DEBUGSERVER/../common/uscif/
export PATH=$PATH:$DEBUGSERVER/../common/IDE/
export PATH=$PATH:$DEBUGSERVER/../common/bin/
export PATH=$PATH:$DEBUGSERVER/bin/linux/
export PATH=$PATH:$DEBUGSERVER/linux/components/
export XDCPATH="$DEBUGSERVER/packages/;$DEBUGSERVER/packages/ti/dss"

export XDCROOT="/db/rtree/install/trees/products/xdcprod/xdcprod-o21/product/Linux/xdctools_3_22_01_21"
$XDCROOT/xs -Dxpcom.bridge.executeOnDedicatedThread=yes -Dorg.eclipse.swt.browser.XULRunnerPath="$DEBUGSERVER/linux" -DXPCOM.RUNTIME="$DEBUGSERVER/linux" -f $1 ./settings.xs $2 $3 $4 $5
