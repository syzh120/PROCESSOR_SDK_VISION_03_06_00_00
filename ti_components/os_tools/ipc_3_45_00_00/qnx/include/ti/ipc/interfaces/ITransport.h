/*
 *  ======== ITransport.h ========
 */

#ifndef ITRANSPORT_H
#define ITRANSPORT_H

/* opaque instance handle */
typedef struct ITransport_Object *ITransport_Handle;

#define ITransport_TypeId 0x01

/* instance object */
typedef struct ITransport_Object {
    Int interfaceType;
} ITransport_Object;

/* instance functions */
static inline
Int ITransport_itype(ITransport_Handle inst)
{
    ITransport_Object *obj = (ITransport_Object *)inst;
    return obj->interfaceType;
}

#endif /* ITRANSPORT_H */
