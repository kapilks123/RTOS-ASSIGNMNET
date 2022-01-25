#include <stdio.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

TaskHandle_t xHandleTaskLog;

void TaskLog(void *pvParameters)    // Run to completion task
{
    printf("TaskLog\n");
    vTaskDelete(xHandleTaskLog);
}

void app_main()
{
    BaseType_t result;
    result = xTaskCreate(TaskLog, "TaskLog", 1024, NULL, 5, &xHandleTaskLog);
    if(result == pdPASS)
    {
        printf("TaskLog Created\n");
    }                        
}