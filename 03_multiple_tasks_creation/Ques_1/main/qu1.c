#include <stdio.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>


TaskHandle_t xHandleTask1, xHandleTask2;

void Task1(void *pvParameters)
{
    while(1)
    {
        printf("Task1: Priority = 5\n");
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}

void Task2(void *pvParameters)
{
    while(1)
    {
        printf("Task2: Priority = 10\n");
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}

void app_main()
{
    BaseType_t result1, result2;
    result1 = xTaskCreate(Task1, "Task1", 1024, NULL, 5, &xHandleTask1);
    if(result1 == pdPASS)
    {
        printf("Task1 Created\n");
    }

    result2 = xTaskCreate(Task2, "Task2", 1024, NULL, 10, &xHandleTask2);
    if(result2 == pdPASS)
    {
        printf("Task2 Created\n");
    }                        
}