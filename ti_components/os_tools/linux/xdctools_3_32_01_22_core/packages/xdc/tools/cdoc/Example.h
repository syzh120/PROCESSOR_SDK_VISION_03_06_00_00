/*
 *  Do not modify this file; it is automatically 
 *  generated and any modifications will be overwritten.
 *
 * @(#) xdc-B21
 */

/*
 * ======== GENERATED SECTIONS ========
 *     
 *     PROLOGUE
 *     INCLUDES
 *     
 *     INTERNAL DEFINITIONS
 *     MODULE-WIDE CONFIGS
 *     FUNCTION DECLARATIONS
 *     SYSTEM FUNCTIONS
 *     
 *     EPILOGUE
 *     STATE STRUCTURES
 *     PREFIX ALIASES
 */


/*
 * ======== PROLOGUE ========
 */

#ifndef xdc_tools_cdoc_Example__include
#define xdc_tools_cdoc_Example__include

#ifndef __nested__
#define __nested__
#define xdc_tools_cdoc_Example__top__
#endif

#ifdef __cplusplus
#define __extern extern "C"
#else
#define __extern extern
#endif

#define xdc_tools_cdoc_Example___VERS 160


/*
 * ======== INCLUDES ========
 */

#include <xdc/std.h>

#include <xdc/runtime/xdc.h>
#include <xdc/runtime/Types.h>
#include <xdc/tools/cdoc/package/package.defs.h>

#include <xdc/runtime/IModule.h>


/*
 * ======== AUXILIARY DEFINITIONS ========
 */

/* AStruct */
struct xdc_tools_cdoc_Example_AStruct {
    xdc_Int aField;
};

/* AnEnum */
enum xdc_tools_cdoc_Example_AnEnum {
    xdc_tools_cdoc_Example_AVALUE
};
typedef enum xdc_tools_cdoc_Example_AnEnum xdc_tools_cdoc_Example_AnEnum;

/* AUnion */
union xdc_tools_cdoc_Example_AUnion {
    xdc_String aString;
    xdc_Int anInt;
};

/* ATypedEnum */
enum  {
    xdc_tools_cdoc_Example_LOOP = 6,
    xdc_tools_cdoc_Example_PRINT = 28
};
typedef xdc_Int xdc_tools_cdoc_Example_ATypedEnum;

/* __struct__1 */
struct xdc_tools_cdoc_Example___struct__1 {
    xdc_Int count;
};

/* __struct__2 */
struct xdc_tools_cdoc_Example___struct__2 {
    xdc_String msg;
};

/* __struct__3 */
union xdc_tools_cdoc_Example___struct__3 {
    xdc_tools_cdoc_Example___struct__1 loop;
    xdc_tools_cdoc_Example___struct__2 print;
};

/* ACmd */
struct xdc_tools_cdoc_Example_ACmd {
    xdc_tools_cdoc_Example_ATypedEnum cmdId;
    xdc_tools_cdoc_Example___struct__3 args;
};


/*
 * ======== INTERNAL DEFINITIONS ========
 */


/*
 * ======== MODULE-WIDE CONFIGS ========
 */

/* Module__diagsEnabled */
typedef xdc_Bits32 CT__xdc_tools_cdoc_Example_Module__diagsEnabled;
__extern __FAR__ const CT__xdc_tools_cdoc_Example_Module__diagsEnabled xdc_tools_cdoc_Example_Module__diagsEnabled__C;

/* Module__diagsIncluded */
typedef xdc_Bits32 CT__xdc_tools_cdoc_Example_Module__diagsIncluded;
__extern __FAR__ const CT__xdc_tools_cdoc_Example_Module__diagsIncluded xdc_tools_cdoc_Example_Module__diagsIncluded__C;

/* Module__diagsMask */
typedef xdc_Bits16 *CT__xdc_tools_cdoc_Example_Module__diagsMask;
__extern __FAR__ const CT__xdc_tools_cdoc_Example_Module__diagsMask xdc_tools_cdoc_Example_Module__diagsMask__C;

/* Module__gateObj */
typedef xdc_Ptr CT__xdc_tools_cdoc_Example_Module__gateObj;
__extern __FAR__ const CT__xdc_tools_cdoc_Example_Module__gateObj xdc_tools_cdoc_Example_Module__gateObj__C;

/* Module__gatePrms */
typedef xdc_Ptr CT__xdc_tools_cdoc_Example_Module__gatePrms;
__extern __FAR__ const CT__xdc_tools_cdoc_Example_Module__gatePrms xdc_tools_cdoc_Example_Module__gatePrms__C;

/* Module__id */
typedef xdc_runtime_Types_ModuleId CT__xdc_tools_cdoc_Example_Module__id;
__extern __FAR__ const CT__xdc_tools_cdoc_Example_Module__id xdc_tools_cdoc_Example_Module__id__C;

/* Module__loggerDefined */
typedef xdc_Bool CT__xdc_tools_cdoc_Example_Module__loggerDefined;
__extern __FAR__ const CT__xdc_tools_cdoc_Example_Module__loggerDefined xdc_tools_cdoc_Example_Module__loggerDefined__C;

/* Module__loggerObj */
typedef xdc_Ptr CT__xdc_tools_cdoc_Example_Module__loggerObj;
__extern __FAR__ const CT__xdc_tools_cdoc_Example_Module__loggerObj xdc_tools_cdoc_Example_Module__loggerObj__C;

/* Module__loggerFxn0 */
typedef xdc_runtime_Types_LoggerFxn0 CT__xdc_tools_cdoc_Example_Module__loggerFxn0;
__extern __FAR__ const CT__xdc_tools_cdoc_Example_Module__loggerFxn0 xdc_tools_cdoc_Example_Module__loggerFxn0__C;

/* Module__loggerFxn1 */
typedef xdc_runtime_Types_LoggerFxn1 CT__xdc_tools_cdoc_Example_Module__loggerFxn1;
__extern __FAR__ const CT__xdc_tools_cdoc_Example_Module__loggerFxn1 xdc_tools_cdoc_Example_Module__loggerFxn1__C;

/* Module__loggerFxn2 */
typedef xdc_runtime_Types_LoggerFxn2 CT__xdc_tools_cdoc_Example_Module__loggerFxn2;
__extern __FAR__ const CT__xdc_tools_cdoc_Example_Module__loggerFxn2 xdc_tools_cdoc_Example_Module__loggerFxn2__C;

/* Module__loggerFxn4 */
typedef xdc_runtime_Types_LoggerFxn4 CT__xdc_tools_cdoc_Example_Module__loggerFxn4;
__extern __FAR__ const CT__xdc_tools_cdoc_Example_Module__loggerFxn4 xdc_tools_cdoc_Example_Module__loggerFxn4__C;

/* Module__loggerFxn8 */
typedef xdc_runtime_Types_LoggerFxn8 CT__xdc_tools_cdoc_Example_Module__loggerFxn8;
__extern __FAR__ const CT__xdc_tools_cdoc_Example_Module__loggerFxn8 xdc_tools_cdoc_Example_Module__loggerFxn8__C;

/* Module__startupDoneFxn */
typedef xdc_Bool (*CT__xdc_tools_cdoc_Example_Module__startupDoneFxn)(void);
__extern __FAR__ const CT__xdc_tools_cdoc_Example_Module__startupDoneFxn xdc_tools_cdoc_Example_Module__startupDoneFxn__C;

/* Object__count */
typedef xdc_Int CT__xdc_tools_cdoc_Example_Object__count;
__extern __FAR__ const CT__xdc_tools_cdoc_Example_Object__count xdc_tools_cdoc_Example_Object__count__C;

/* Object__heap */
typedef xdc_runtime_IHeap_Handle CT__xdc_tools_cdoc_Example_Object__heap;
__extern __FAR__ const CT__xdc_tools_cdoc_Example_Object__heap xdc_tools_cdoc_Example_Object__heap__C;

/* Object__sizeof */
typedef xdc_SizeT CT__xdc_tools_cdoc_Example_Object__sizeof;
__extern __FAR__ const CT__xdc_tools_cdoc_Example_Object__sizeof xdc_tools_cdoc_Example_Object__sizeof__C;

/* Object__table */
typedef xdc_Ptr CT__xdc_tools_cdoc_Example_Object__table;
__extern __FAR__ const CT__xdc_tools_cdoc_Example_Object__table xdc_tools_cdoc_Example_Object__table__C;

/* u */
#define xdc_tools_cdoc_Example_u (xdc_tools_cdoc_Example_u__C)
typedef xdc_tools_cdoc_Example_AUnion CT__xdc_tools_cdoc_Example_u;
__extern __FAR__ const CT__xdc_tools_cdoc_Example_u xdc_tools_cdoc_Example_u__C;


/*
 * ======== FUNCTION DECLARATIONS ========
 */

/* Module_startup */
#define xdc_tools_cdoc_Example_Module_startup( state ) (-1)

/* Module__startupDone__S */
xdc__CODESECT(xdc_tools_cdoc_Example_Module__startupDone__S, "xdc_tools_cdoc_Example_Module__startupDone__S")
__extern xdc_Bool xdc_tools_cdoc_Example_Module__startupDone__S( void );

/* aFunction__E */
#define xdc_tools_cdoc_Example_aFunction xdc_tools_cdoc_Example_aFunction__E
xdc__CODESECT(xdc_tools_cdoc_Example_aFunction__E, "xdc_tools_cdoc_Example_aFunction")
__extern xdc_Void xdc_tools_cdoc_Example_aFunction__E( xdc_Int aParam );
xdc__CODESECT(xdc_tools_cdoc_Example_aFunction__F, "xdc_tools_cdoc_Example_aFunction")
__extern xdc_Void xdc_tools_cdoc_Example_aFunction__F( xdc_Int aParam );


/*
 * ======== SYSTEM FUNCTIONS ========
 */

/* Module_startupDone */
#define xdc_tools_cdoc_Example_Module_startupDone() xdc_tools_cdoc_Example_Module__startupDone__S()

/* Object_heap */
#define xdc_tools_cdoc_Example_Object_heap() xdc_tools_cdoc_Example_Object__heap__C

/* Module_heap */
#define xdc_tools_cdoc_Example_Module_heap() xdc_tools_cdoc_Example_Object__heap__C

/* Module_id */
static inline CT__xdc_tools_cdoc_Example_Module__id xdc_tools_cdoc_Example_Module_id( void ) 
{
    return xdc_tools_cdoc_Example_Module__id__C;
}

/* Module_hasMask */
static inline xdc_Bool xdc_tools_cdoc_Example_Module_hasMask( void ) 
{
    return (xdc_Bool)(xdc_tools_cdoc_Example_Module__diagsMask__C != NULL);
}

/* Module_getMask */
static inline xdc_Bits16 xdc_tools_cdoc_Example_Module_getMask( void ) 
{
    return xdc_tools_cdoc_Example_Module__diagsMask__C != NULL ? *xdc_tools_cdoc_Example_Module__diagsMask__C : (xdc_Bits16)0;
}

/* Module_setMask */
static inline xdc_Void xdc_tools_cdoc_Example_Module_setMask( xdc_Bits16 mask ) 
{
    if (xdc_tools_cdoc_Example_Module__diagsMask__C != NULL) {
        *xdc_tools_cdoc_Example_Module__diagsMask__C = mask;
    }
}


/*
 * ======== EPILOGUE ========
 */

#ifdef xdc_tools_cdoc_Example__top__
#undef __nested__
#endif

#endif /* xdc_tools_cdoc_Example__include */


/*
 * ======== STATE STRUCTURES ========
 */

#if defined(__config__) || (!defined(__nested__) && defined(xdc_tools_cdoc_Example__internalaccess))

#ifndef xdc_tools_cdoc_Example__include_state
#define xdc_tools_cdoc_Example__include_state


#endif /* xdc_tools_cdoc_Example__include_state */

#endif

/*
 * ======== PREFIX ALIASES ========
 */

#if !defined(__nested__) && !defined(xdc_tools_cdoc_Example__nolocalnames)

#ifndef xdc_tools_cdoc_Example__localnames__done
#define xdc_tools_cdoc_Example__localnames__done

/* module prefix */
#define Example_AStruct xdc_tools_cdoc_Example_AStruct
#define Example_AnEnum xdc_tools_cdoc_Example_AnEnum
#define Example_AUnion xdc_tools_cdoc_Example_AUnion
#define Example_ATypedEnum xdc_tools_cdoc_Example_ATypedEnum
#define Example___struct__1 xdc_tools_cdoc_Example___struct__1
#define Example___struct__2 xdc_tools_cdoc_Example___struct__2
#define Example___struct__3 xdc_tools_cdoc_Example___struct__3
#define Example_ACmd xdc_tools_cdoc_Example_ACmd
#define Example_AVALUE xdc_tools_cdoc_Example_AVALUE
#define Example_LOOP xdc_tools_cdoc_Example_LOOP
#define Example_PRINT xdc_tools_cdoc_Example_PRINT
#define Example_u xdc_tools_cdoc_Example_u
#define Example_aFunction xdc_tools_cdoc_Example_aFunction
#define Example_Module_name xdc_tools_cdoc_Example_Module_name
#define Example_Module_id xdc_tools_cdoc_Example_Module_id
#define Example_Module_startup xdc_tools_cdoc_Example_Module_startup
#define Example_Module_startupDone xdc_tools_cdoc_Example_Module_startupDone
#define Example_Module_hasMask xdc_tools_cdoc_Example_Module_hasMask
#define Example_Module_getMask xdc_tools_cdoc_Example_Module_getMask
#define Example_Module_setMask xdc_tools_cdoc_Example_Module_setMask
#define Example_Object_heap xdc_tools_cdoc_Example_Object_heap
#define Example_Module_heap xdc_tools_cdoc_Example_Module_heap

#endif /* xdc_tools_cdoc_Example__localnames__done */
#endif
/*
 *  @(#) xdc.tools.cdoc; 1, 0, 0,0; 7-26-2016 11:49:18; /db/ztree/library/trees/xdc/xdc-B21/src/packages/
 */

