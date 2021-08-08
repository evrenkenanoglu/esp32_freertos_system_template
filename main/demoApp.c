/** @file       demoapp.c
 *  @brief      demo Application
 *  @copyright  (c) 2021- Evren Kenanoglu - All Rights Reserved
 *              Permission to use, reproduce, copy, prepare derivative works,
 *              modify, distribute, perform, display or sell this software and/or
 *              its documentation for any purpose is prohibited without the express
 *              written consent of Evren Kenanoglu.
 *  @author     Evren Kenanoglu
 *  @date       01/08/2021
 */
#define FILE_DEMOAPP_C

/** INCLUDES ******************************************************************/
#include "demoapp.h"
/** CONSTANTS *****************************************************************/
const char* processTag = "Demo App Process";
const char* tagTask1   = "Task1";
/** TYPEDEFS ******************************************************************/

/** MACROS ********************************************************************/
#define TASK_DEMO_DELAY_INTERVAL 1000 // ms

/** VARIABLES *****************************************************************/

/** LOCAL FUNCTION DECLARATIONS ***********************************************/
static void Delay(void);
static void taskDemo1(void* pvParameters);
TaskHandle_t xHandle;

/** INTERFACE FUNCTION DEFINITIONS ********************************************/

PROCESS_INIT_FUNC(demoInit)
{
    ESP_LOGI(processTag, " Process Started!");
    AppParams_t*       params = process->parameters;
    const AppConsts_t* consts = process->constants;
    // UNUSED(params);
    // UNUSED(consts);

    //**Create your tasks and pass the task or process parameters...

    TASK_CREATE(taskDemo1, tagTask1, 4096, &params->task1Params, 5, &xHandle);
    //...
    PROCESS_STATE_CHANGE(process, eProcessStateRunning);
}

PROCESS_SUSPEND_FUNC(demoSuspend)
{
    TASK_SUSPEND(xHandle);
    printf("Process Suspended!\n");
    PROCESS_STATE_CHANGE(process, eProcessStateSuspended);
}

PROCESS_RESUME_FUNC(demoResume)
{
    TASK_RESUME(xHandle);
    printf("Process Resumed!\n");
    PROCESS_STATE_CHANGE(process, eProcessStateRunning);
}


PROCESS_TERMINATE_FUNC(demoTerminate) {
    TASK_TERMINATE(xHandle);
    printf("Process Terminated!\n");
    PROCESS_STATE_CHANGE(process, eProcessStateTerminated);
}
/** LOCAL FUNCTION DEFINITIONS ************************************************/

void taskDemo1(void* pvParameters)
{
    ESP_LOGI(tagTask1, "Running!");
    // printf("Task1: Running!!!\n");
    DemoTaskParams_t* params = (DemoTaskParams_t*)pvParameters;
    for (;;)
    {
        ESP_LOGI(tagTask1, "params->dummyValue [%d];", params->dummyValue);
        params->dummyValue++;

        vTaskDelay(TASK_DEMO_DELAY_INTERVAL / portTICK_PERIOD_MS);
    }
    vTaskDelete(NULL);
}

void Delay()
{
    for (int i = 3; i >= 0; i--)
    {
        printf("Starting in %d seconds...\n", i);
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}
