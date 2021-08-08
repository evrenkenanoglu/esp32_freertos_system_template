/** @file       process.c
 *  @brief      Process
 *  @copyright  (c) 2021- Evren Kenanoglu - All Rights Reserved
 *              Permission to use, reproduce, copy, prepare derivative works,
 *              modify, distribute, perform, display or sell this software and/or
 *              its documentation for any purpose is prohibited without the express
 *              written consent of Evren Kenanoglu.
 *  @author     Deniz Fer;
 *              Evren Kenanoglu;
 *  @date       07/08/2021
 */
#define FILE_PROCESS_C

/** INCLUDES ******************************************************************/
#include "process.h"

/** CONSTANTS *****************************************************************/

/** TYPEDEFS ******************************************************************/

/** MACROS ********************************************************************/

/** VARIABLES *****************************************************************/

/** LOCAL FUNCTION DECLARATIONS ***********************************************/

/** INTERFACE FUNCTION DEFINITIONS ********************************************/

uint8_t processStart(Process_t* process)
{
    if ((process->state == eProcessStateIdle) || (process->state == eProcessStateTerminated))
    {
        // Critical Sections Enter

        process->init(process);

        // Critical Section Stop

        // Debug print for starting

        return EXIT_SUCCESS;
    }
    else
    {
        return EXIT_FAILURE;
    }
}

uint8_t processSuspend(Process_t* process)
{
    if (process->state == eProcessStateRunning)
    {
        // Critical Sections Enter

        process->suspend(process);

        // Critical Section Stop

        // Debug print for suspend

        return EXIT_SUCCESS;
    }
    else
    {
        return EXIT_FAILURE;
    }
}

uint8_t processResume(Process_t* process)
{
    if (process->state == eProcessStateSuspended)
    {
        // Critical Sections Enter
        process->resume(process);

        // Critical Section Stop

        // Debug print for suspend

        return EXIT_SUCCESS;
    }
    else
    {
        return EXIT_FAILURE;
    }
}


uint8_t processTerminate(Process_t* process)
{
    if ((process->state == eProcessStateRunning) || (process->state == eProcessStateSuspended))
    {
        // Critical Sections Enter

        process->terminate(process);

        // Critical Section Stop

        // Debug print for termination

        return EXIT_SUCCESS;
    }
    else
    {
        return EXIT_FAILURE;
    }
}

/** LOCAL FUNCTION DEFINITIONS ************************************************/
