/** @file       demoapp2.h
 *  @brief      demoApp2
 *  @copyright  (c) 2021- Evren Kenanoglu - All Rights Reserved
 *              Permission to use, reproduce, copy, prepare derivative works,
 *              modify, distribute, perform, display or sell this software and/or
 *              its documentation for any purpose is prohibited without the express
 *              written consent of Evren Kenanoglu.
 *  @author     Evren Kenanoglu
 *  @date       14/08/2021
 */
#ifndef FILE_DEMOAPP2_H
#define FILE_DEMOAPP2_H

/** INCLUDES ******************************************************************/
#include "system.h"
/** CONSTANTS *****************************************************************/

/** TYPEDEFS ******************************************************************/
typedef struct
{
    uint8_t dummyValue;
} DemoTask2Params_t;

    typedef struct
{
    const uint8_t const_dummy;
} DemoApp2Consts_t;

typedef struct
{
    DemoTask2Params_t task2Params;
} DemoApp2Params_t;

/** MACROS ********************************************************************/
#ifndef FILE_DEMOAPP2_C
#define INTERFACE extern
#else
#define INTERFACE
#endif

#define APP_DEMO_2_CREATE(_name, _enum)                                                                                                                                                                \
    DemoApp2Params_t _name##Params = {                                                                                                                                                                 \
        .task2Params =                                                                                                                                                                                 \
            {                                                                                                                                                                                          \
                .dummyValue = 0,                                                                                                                                                                       \
            },                                                                                                                                                                                         \
    };                                                                                                                                                                                                 \
    DemoApp2Consts_t _name##Consts = {                                                                                                                                                                 \
        .const_dummy = 10,                                                                                                                                                                             \
    };                                                                                                                                                                                                 \
    PROCESS_CREATE(_name, _enum, demo2Init, demo2Suspend, demo2Resume, demo2Terminate, &_name##Params, &_name##Consts)

/** VARIABLES *****************************************************************/

/** FUNCTIONS *****************************************************************/

#undef INTERFACE // Should not let this roam free

#endif // FILE_DEMOAPP2_H
