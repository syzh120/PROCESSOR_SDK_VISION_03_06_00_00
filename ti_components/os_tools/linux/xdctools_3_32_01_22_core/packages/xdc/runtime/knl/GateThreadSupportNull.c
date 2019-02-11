/*
 *  ======== GateThreadSupportNull.c ========
 */

#include <xdc/std.h>

#include "package/internal/GateThreadSupportNull.xdc.h"

/*
 *  ======== GateThreadSupportNull_enter ========
 */
IArg GateThreadSupportNull_enter(GateThreadSupportNull_Handle gate)
{
    return (0);
}

/*
 *  ======== GateThreadSupportNull_leave ========
 */
Void GateThreadSupportNull_leave(GateThreadSupportNull_Handle gate, IArg key)
{
}

/*
 *  ======== GateThreadSupportNull_query ========
 */
Bool GateThreadSupportNull_query(Int qual)
{
    return (TRUE);
}
/*
 *  @(#) xdc.runtime.knl; 1, 0, 0,0; 7-26-2016 11:46:36; /db/ztree/library/trees/xdc/xdc-B21/src/packages/
 */

