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
const char* processTag = "Demo Process 1";
const char* tagTask1   = "Task1";
/** TYPEDEFS ******************************************************************/

/** MACROS ********************************************************************/
#define TASK_DEMO_DELAY_INTERVAL 1000 // ms
#define TASK_DEMO_1_QUEUE_SIZE 5
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

    globalQueueList[eTaskDemo1] = xQueueCreate(TASK_DEMO_1_QUEUE_SIZE, sizeof(Message_t *));
    TASK_CREATE(taskDemo1, tagTask1, 4096, process, 5, &xHandle);
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
    Process_t *process = (Process_t*) pvParameters;
    AppParams_t*       params = process->parameters;
    const AppConsts_t* consts = process->constants;
    BaseType_t xStatus;
    Message_t *receivedMessage ; //= { 0, 0, 0,};
    const TickType_t tickToWait = pdMS_TO_TICKS(0);
    
    for (;;)
    {
        ESP_LOGI(tagTask1, "params->dummyValue [%d];", params->task1Params.dummyValue);
        params->task1Params.dummyValue++;

        if(uxQueueMessagesWaiting(globalQueueList[eTaskDemo1]) != 0)
        {
            printf("Queue is not empty\n");       
        }

        xStatus = xQueueReceive(globalQueueList[eTaskDemo1], &receivedMessage, tickToWait);
        
        if(xStatus != pdPASS)
        {
            printf("Couldn't received anything from queue!\n");
        }
        else
        {
            printf("\nMessage Received from Process: %d | Task: %d \n", receivedMessage->senderProcess, receivedMessage->senderTask);
            printf("Received message: %d \n\n", receivedMessage->data);

            if(receivedMessage->senderProcess == eProcessDemo2)
            {
                printf("\nProcess2 Found! \n");
                if(receivedMessage->senderTask == eTaskDemo2)
                {
                    printf("\nTask2 Found! \n");
                }
                else
                {
                    printf("\nTask2 Not Found! \n");
                }
            }
            //printf("Received message: %d \n", receivedValue);
        }

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
