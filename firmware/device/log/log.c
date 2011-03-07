/*!
 * \file log.c
 *
 * \brief 
 *
 *
 * \date Mar 5, 2011
 * \author Dan Riedler
 *
 */

/*-----------------------------------------------------------------------------
 Includes
------------------------------------------------------------------------------*/
#include <stdarg.h>
#include "log.h"
#include "hw_mgr/hw_mgr.h"
#include "os/os.h"

#ifdef DEV_MOD_LOG

/*-----------------------------------------------------------------------------
 Defines
------------------------------------------------------------------------------*/
#define TOTAL_MODULE_COUNT (MOD_MGR_MODULE_COUNT+HW_MGR_MODULE_COUNT+OS_MODULE_COUNT)

/*-----------------------------------------------------------------------------
 Macros
------------------------------------------------------------------------------*/
#define LOG_RESULT()( RESULT(NULL, MOD_MGR_LOG, NULL_MOD, NULL))

/*-----------------------------------------------------------------------------
 Typedefs
------------------------------------------------------------------------------*/
typedef struct {
    uint32 ModId;
    uint32 SubModId;
    bool Enabled;
} ModuleInfo, *pModuleInfo;

typedef struct {
    pLIB_PRINTF_PutChr Dest;
    bool Enabled;
} OutputDestInfo;

/*-----------------------------------------------------------------------------
 Local Function Prototypes
------------------------------------------------------------------------------*/
PRIVATE pModuleInfo FindModule(uint32 ModId, uint32 SubModId);

/*-----------------------------------------------------------------------------
 Data Members
------------------------------------------------------------------------------*/
// TODO implement this as dynamic array
PRIVATE ModuleInfo moduleInfo[TOTAL_MODULE_COUNT];
PRIVATE uint32 moduleInfoCount;
PRIVATE OutputDestInfo outputDestInfo[LOG_OUTPUT_DESTINATION_COUNT];

//*****************************************************************************
//
// Exported Functions
//
//*****************************************************************************

/******************************************************************************/
Result LOG_Init( void )
{
    Result result = LOG_RESULT();

    ZeroMemory(moduleInfo, sizeof(ModuleInfo)*TOTAL_MODULE_COUNT);
    ZeroMemory(outputDestInfo, sizeof(OutputDestInfo)*LOG_OUTPUT_DESTINATION_COUNT);
    moduleInfoCount = 0;

    return result;
}


/******************************************************************************/
PUBLIC Result LOG_RegisterModule(uint32 ModId, uint32 SubModId, bool Enabled)
{
    Result result = LOG_RESULT();


    // make sure it hasn't been registered
    ASSERT(!FindModule(ModId, SubModId));

    moduleInfo[moduleInfoCount].ModId = ModId;
    moduleInfo[moduleInfoCount].SubModId = SubModId;
    moduleInfo[moduleInfoCount].Enabled = Enabled;
    moduleInfoCount++;

    return result;
}


/******************************************************************************/
PUBLIC Result LOG_RegisterOutputDest(LOG_DestinationId DestId, void (*Dest)(void *, char), bool Enabled)
{
    Result result = LOG_RESULT();

    ASSERT(DestId < LOG_OUTPUT_DESTINATION_COUNT);
    // assert destination not already enabled
    ASSERT(outputDestInfo[DestId].Dest == NULL);
    ASSERT(Dest != NULL);

    outputDestInfo[DestId].Dest = Dest;
    outputDestInfo[DestId].Enabled = Enabled;

    return result;
}


/******************************************************************************/
PUBLIC Result LOG(LOG_DestinationId DestId, uint32 ModId, uint32 SubModId, char* Format, ...)
{
    Result result = LOG_RESULT();
    pModuleInfo mod = NULL;

    mod = FindModule(ModId, SubModId);
    if( mod != NULL && mod->Enabled )
    {
        if( DestId < LOG_OUTPUT_DESTINATION_COUNT && outputDestInfo[DestId].Enabled )
        {
            va_list va;
            va_start(va,Format);
            LIB_PRINTF_PrintfVaArgs(outputDestInfo[DestId].Dest, Format, va);
            va_end(va);
        }
        else if( DestId == LOG_OUTPUT_ALL )
        {
            uint32 i;
            for( i = 0; i < LOG_OUTPUT_DESTINATION_COUNT; i++ )
            {
                if( outputDestInfo[i].Enabled )
                {
                    va_list va;
                    va_start(va,Format);
                    LIB_PRINTF_PrintfVaArgs(outputDestInfo[DestId].Dest, Format, va);
                    va_end(va);
                }
            }
        }
    }

    return result;
}

/******************************************************************************/
PUBLIC Result LOG_CatchError(Result result)
{
    Result res = LOG_RESULT();
    CString str;

    // TODO log to all enabled output sources
    str = MOD_MGR_GetResultCodeStr(result);
    LOG_Printf("%s\n", str);

    return res;
}


/******************************************************************************/
PUBLIC Result LOG_Printf( char* Format, ...)
{
    Result result = LOG_RESULT();

    ASSERT(outputDestInfo[LOG_OUTPUT_DEFAULT].Dest);
    ASSERT(outputDestInfo[LOG_OUTPUT_DEFAULT].Enabled);

    va_list va;
    va_start(va,Format);
    LIB_PRINTF_PrintfVaArgs(outputDestInfo[LOG_OUTPUT_DEFAULT].Dest, Format, va);
    va_end(va);

    return result;
}



/******************************************************************************/
PUBLIC Result LOG_SetModuleEnabled(uint32 ModId, uint32 SubModId, bool Enabled)
{
    Result result = LOG_RESULT();
    pModuleInfo mod = NULL;

    mod = FindModule(ModId, SubModId);
    ASSERT(mod);

    mod->Enabled = Enabled;

    return result;
}


/******************************************************************************/
PUBLIC Result LOG_SetOutputDestEnabled(LOG_DestinationId DestId, bool Enabled)
{
    Result result = LOG_RESULT();

    ASSERT(DestId < LOG_OUTPUT_DESTINATION_COUNT);
    // assert destination enabled
    ASSERT(outputDestInfo[DestId].Dest != NULL);

    outputDestInfo[DestId].Enabled = Enabled;

    return result;
}





//*****************************************************************************
//
// Local Functions
//
//*****************************************************************************
PRIVATE pModuleInfo FindModule(uint32 ModId, uint32 SubModId)
{
    uint32 i;
    pModuleInfo mod = NULL;

    for( i = 0; i < moduleInfoCount; i++ )
    {
        if( moduleInfo[i].ModId == ModId && moduleInfo[i].SubModId == SubModId )
        {
            mod = &moduleInfo[i];
            break;
        }

    }

    return mod;
}


#endif
