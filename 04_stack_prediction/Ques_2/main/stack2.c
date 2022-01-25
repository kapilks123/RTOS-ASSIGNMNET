#include <stdio.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>


TaskHandle_t xHandleTask1, xHandleTask2;

void Task1(void *pvParameters)
{
    while(1)
    {
        printf("Priority of Task1: %d\n", uxTaskPriorityGet(NULL));
        printf("Unused stack by Task1: %d\n", uxTaskGetStackHighWaterMark(NULL));  
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}

void Task2(void *pvParameters)
{
    while(1)
    {
        printf("Priority of Task2: %d\n", uxTaskPriorityGet(NULL));
        printf("Unused stack by Task2: %d\n", uxTaskGetStackHighWaterMark(NULL));  
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}

void app_main()
{
    printf("Priority of Main Task: %d\n", uxTaskPriorityGet(NULL));
    xTaskCreate(Task1, "Task1", 1550, NULL, 5, &xHandleTask1);
    xTaskCreate(Task2, "Task2", 1550, NULL, 7, &xHandleTask2);
    printf("Unused stack by main task: %d\n", uxTaskGetStackHighWaterMark(NULL));                      
}
