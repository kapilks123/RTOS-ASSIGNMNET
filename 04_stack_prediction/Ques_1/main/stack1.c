#include <stdio.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>


TaskHandle_t xHandleTask1, xHandleTask2;

void Task1(void *pvParameters)
{
    while(1)
    {
        printf("Task1: Priority = 5\n");
        printf("Unused stack by Task1: %d\n", uxTaskGetStackHighWaterMark(NULL));  
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}

void Task2(void *pvParameters)
{
    while(1)
    {
        int a = 90, b = 18;
        printf("Task2: Priority = 7\n");
        printf("sum of a and b is %d\n", a + b);
        printf("Unused stack by Task2: %d\n", uxTaskGetStackHighWaterMark(NULL));  
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}

void app_main()
{
    xTaskCreate(Task1, "Task1", 1550, NULL, 5, &xHandleTask1);
    xTaskCreate(Task2, "Task2", 1550, NULL, 7, &xHandleTask2);
    printf("Unused stack by main task: %d\n", uxTaskGetStackHighWaterMark(NULL));                      
}