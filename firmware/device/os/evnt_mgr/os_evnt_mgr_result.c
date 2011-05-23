/*!
 * \file os_evnt_mgr_result.c
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
/*-----------------------------------------------------------------------------
 Includes
------------------------------------------------------------------------------*/
#include "os_evnt_mgr_result.h"

#ifdef OS_MOD_EVNT_MGR

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
 Local Function Prototypes
------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
 Data Members
------------------------------------------------------------------------------*/


//*****************************************************************************
//
// Exported Functions
//
//*****************************************************************************


//*****************************************************************************//
PROTECTED CString EVNT_MGR_GetResultCodeStr(Result result)
{
   CString str;

   switch(RESULT_CODE(result))
   {
   default:
       str = "result code undefined!";
   }

   return str;
}


//*****************************************************************************
//
// Local Functions
//
//*****************************************************************************

#endif