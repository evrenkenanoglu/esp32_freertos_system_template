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
#include "system.h"

APP_DEMO_CREATE(appDemo, eProcessDemo)

static void startupDelay(void);

void app_main(void)
{
    startupDelay();
    while (1)
    {
        processStart(&appDemo);
        vTaskDelay(3000 / portTICK_PERIOD_MS);
        processSuspend(&appDemo);
        vTaskDelay(3000 / portTICK_PERIOD_MS);
        processResume(&appDemo);
        vTaskDelay(3000/ portTICK_PERIOD_MS);
        processTerminate(&appDemo);
        vTaskDelay(3000/ portTICK_PERIOD_MS);
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
