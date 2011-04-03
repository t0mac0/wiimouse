/*!
 * \file os.c
 *
 * \brief 
 *
 *
 * \date Mar 6, 2011
 * \author Dan Riedler
 *
 */

/*-----------------------------------------------------------------------------
 Includes
------------------------------------------------------------------------------*/
#include "os.h"

#ifdef DEV_MOD_OS

/*-----------------------------------------------------------------------------
 Defines
------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
 Macros
------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
 Typedefs
------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
 Function Prototypes
------------------------------------------------------------------------------*/
PROTECTED void OsHardwareInit( void );

/*-----------------------------------------------------------------------------
 Data Members
------------------------------------------------------------------------------*/


//*****************************************************************************
//
// Exported Functions
//
//*****************************************************************************

/******************************************************************************/
PUBLIC Result OS_Init( void )
{
    Result result = OS_RESULT_INIT();
    uint32 i;

    LOG_Printf("Initializing OS\n");

    for( i = 0; i < OS_MODULE_COUNT; i++ )
    {
        if( osModules[i].Init != NULL && RESULT_IS_SUCCESS(result, osModules[i].Init()) )
        {
            osModules[i].IsInitialized = TRUE;
        }
        else
        {
           return result;
        }
    }

    // Initialize hardware needed by OS
    OsHardwareInit();

    LOG_RegisterModule(MOD_MGR_OS, NULL_MOD, TRUE);


    return result;
}


//*****************************************************************************
//
// Local Functions
//
//*****************************************************************************


#endif
