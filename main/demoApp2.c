/** @file       demoapp2.c
 *  @brief      demoApp2
 *  @copyright  (c) 2021- Evren Kenanoglu - All Rights Reserved
 *              Permission to use, reproduce, copy, prepare derivative works,
 *              modify, distribute, perform, display or sell this software and/or
 *              its documentation for any purpose is prohibited without the express
 *              written consent of Evren Kenanoglu.
 *  @author     Evren Kenanoglu
 *  @date       14/08/2021
 */
#define FILE_DEMOAPP2_C

/** INCLUDES ******************************************************************/
#include "demoapp2.h"

/** CONSTANTS *****************************************************************/

const char* processTag2 = "Demo Process 2";
const char* tagTask2    = "Task2";

/** TYPEDEFS ******************************************************************/

/** MACROS ********************************************************************/
#define TASK_DEMO_2_DELAY_INTERVAL 3000
#define TASK_DEMO_2_QUEUE_SIZE     5

/** VARIABLES *****************************************************************/

/** LOCAL FUNCTION DECLARATIONS ***********************************************/

static void  Delay(void);
static void  taskDemo2(void* pvParameters);
TaskHandle_t xHandleDemo2;

/** INTERFACE FUNCTION DEFINITIONS ********************************************/

PROCESS_INIT_FUNC(demo2Init)
{
    ESP_LOGI(processTag2, " Process Started!");
    DemoApp2Params_t*       params = process->parameters;
    const DemoApp2Consts_t* consts = process->constants;
    // UNUSED(params);
    // UNUSED(consts);

    //**Create your tasks and pass the task or process parameters...

    globalQueueList[eTaskDemo2] = xQueueCreate(TASK_DEMO_2_QUEUE_SIZE, sizeof(uint32_t));
    TASK_CREATE(taskDemo2, tagTask2, 4096, process, 5, &xHandleDemo2);

    //...
    PROCESS_STATE_CHANGE(process, eProcessStateRunning);
}

PROCESS_SUSPEND_FUNC(demo2Suspend)
{
    TASK_SUSPEND(xHandleDemo2);
    printf("Process Suspended!\n");
    PROCESS_STATE_CHANGE(process, eProcessStateSuspended);
}

PROCESS_RESUME_FUNC(demo2Resume)
{
    TASK_RESUME(xHandleDemo2);
    printf("Process Resumed!\n");
    PROCESS_STATE_CHANGE(process, eProcessStateRunning);
}

PROCESS_TERMINATE_FUNC(demo2Terminate)
{
    TASK_TERMINATE(xHandleDemo2);
    printf("Process Terminated!\n");
    PROCESS_STATE_CHANGE(process, eProcessStateTerminated);
}

/** LOCAL FUNCTION DEFINITIONS ************************************************/

void taskDemo2(void* pvParameters)
{
    ESP_LOGI(tagTask2, "Running!");
    Process_t*              process = (Process_t*)pvParameters;
    DemoApp2Params_t*       params  = process->parameters;
    const DemoApp2Consts_t* consts  = process->constants;
    BaseType_t              xStatus;
    Message_t*              messageTask2;
    const TickType_t        tickToWait = pdMS_TO_TICKS(0);

    for (;;)
    {
        ESP_LOGI(tagTask2, "params->dummyValue [%d];", params->task2Params.dummyValue);
        params->task2Params.dummyValue++;

        static uint8_t state = 0;
        if (state == 0)
        {
            messageTask2->senderProcess = process->ID;
            messageTask2->senderTask    = eTaskDemo2;
            messageTask2->data          = 16000;
        }
        else
        {
            messageTask2->senderProcess = 255;
            messageTask2->senderTask    = eTaskDemo2;
            messageTask2->data          = 16000;
        }
        state = !state;

        xStatus = uxQueueSpacesAvailable(globalQueueList[eTaskDemo1]);
        printf("Available Space in Queue of Task1: %d\n", xStatus);
        if (xStatus == 0)
        {
            // printf("No available space in Queue of Task1\n");
        }
        else
        {
            xStatus = xQueueSend(globalQueueList[eTaskDemo1], &messageTask2, tickToWait);
            if (xStatus != pdPASS)
            {
                printf("Message Couldn't Send!\n");
            }
            else
            {
                printf("Message Send Succesfull\n");
            }
        }

        vTaskDelay(TASK_DEMO_2_DELAY_INTERVAL / portTICK_PERIOD_MS);
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