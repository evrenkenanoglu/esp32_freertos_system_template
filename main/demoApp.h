/** @file       demoapp.h
 *  @brief      demo Application
 *  @copyright  (c) 2021- Evren Kenanoglu - All Rights Reserved
 *              Permission to use, reproduce, copy, prepare derivative works,
 *              modify, distribute, perform, display or sell this software and/or
 *              its documentation for any purpose is prohibited without the express
 *              written consent of Evren Kenanoglu.
 *  @author     Evren Kenanoglu
 *  @date       01/08/2021
 */
#ifndef FILE_DEMOAPP_H
#define FILE_DEMOAPP_H

/** INCLUDES ******************************************************************/

#include "main/system.h"

/** CONSTANTS *****************************************************************/

/** TYPEDEFS ******************************************************************/

typedef struct
{
    uint8_t dummy;
} AppParams_t;

/** MACROS ********************************************************************/

#ifndef FILE_DEMOAPP_C
#define INTERFACE extern
#else
#define INTERFACE
#endif

#define APP_DEMO_CREATE(_name, _processEnum)                                                                                                                                                           \
    AppParams_t _name##Params = {                                                                                                                                                                      \
        0,                                                                                                                                                                                             \
    };

/** VARIABLES *****************************************************************/

/** FUNCTIONS *****************************************************************/



#undef INTERFACE // Should not let this roam free

#endif // FILE_DEMOAPP_H
