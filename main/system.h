/** @file       system.h
 *  @brief      System Wide Components
 *  @copyright  (c) 2021-Evren Kenanoglu - All Rights Reserved
 *              Permission to use, reproduce, copy, prepare derivative works,
 *              modify, distribute, perform, display or sell this software and/or
 *              its documentation for any purpose is prohibited without the express
 *              written consent of Evren Kenanoglu.
 *  @author     Evren Kenanoglu
 *  @date       01/08/2021
 */
#ifndef FILE_SYSTEM_H
#define FILE_SYSTEM_H

/** INCLUDES ******************************************************************/

///** Standard Library Includes **///
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

///** FreeRTOS Includes **///
#include "freertos/FreeRTOS.h"
#include "freertos/list.h"
#include "freertos/queue.h"
#include "freertos/semphr.h"
#include "freertos/task.h"
#include "freertos/timers.h"

//** Process Architecture Includes **//
#include "porting.h"
#include "process.h"

///** uController Includes **///
#include "esp_log.h"

/** CONSTANTS *****************************************************************/
#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1

#define QUEUE_SIZE   32 // Default Queue List Size

/** TYPEDEFS ******************************************************************/

typedef enum
{
    eTaskDemo1 = 0,
    eTaskDemo2,
} eTaskID_t;

typedef enum
{
    eProcessDemo = 0,
    eProcessMax  = 255,
} eProcessID_t;

typedef struct
{
    eProcessID_t processID;
    eTaskID_t    taskID;
    void*        data;
} Message_t;

/** MACROS ********************************************************************/

#define GLOBAL_QUEUE_LIST_CREATE(_size) \ ///< Inter-Tasks Communications
QueueHandle_t globalQueueList[QUEUE_SIZE];

#ifndef FILE_SYSTEM_C
#define INTERFACE extern
#else
#define INTERFACE
#endif

/** VARIABLES *****************************************************************/

/** FUNCTIONS *****************************************************************/

#undef INTERFACE // Should not let this roam free

#endif // FILE_SYSTEM_H
