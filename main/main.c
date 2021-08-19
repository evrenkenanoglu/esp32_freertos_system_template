/**
 * @file main.c
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2021-08-07
 *
 * @copyright Copyright (c) 2021
 *
 */

#include "demoApp.h"
#include "demoApp2.h"
#include "system.h"

#include <stdlib.h>

APP_DEMO_CREATE(appDemo, eProcessDemo1)
APP_DEMO_2_CREATE(appDemo2, eProcessDemo2)

static void startupDelay(void);

void app_main(void)
{
    startupDelay();
    processStart(&appDemo);
    processStart(&appDemo2);

    vTaskStartScheduler();
    while (1)
    {
        // processStart(&appDemo);
        // processStart(&appDemo2);
        // vTaskDelay(3000 / portTICK_PERIOD_MS);
        // processSuspend(&appDemo);
        // processSuspend(&appDemo2);
        // vTaskDelay(3000 / portTICK_PERIOD_MS);
        // processResume(&appDemo);
        // processResume(&appDemo2);
        // vTaskDelay(3000/ portTICK_PERIOD_MS);
        // processTerminate(&appDemo);
        // processTerminate(&appDemo2);
        // vTaskDelay(3000/ portTICK_PERIOD_MS);

        // vTaskDelay(2000 / portTICK_PERIOD_MS);
        // processTerminate(&appDemo2);

        // vTaskDelay(2000 / portTICK_PERIOD_MS);
        // processTerminate(&appDemo);

        vTaskDelay(2000 / portTICK_PERIOD_MS);
    }
}

void startupDelay()
{
    for (int i = 3; i >= 0; i--)
    {
        printf("Starting in %d seconds...\n", i);
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}
