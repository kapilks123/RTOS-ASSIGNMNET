#include <stdio.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>


TaskHandle_t xHandleTask, xHandleTask1, xHandleTask2;



void Task1(void *pvParameters)
{
    while(1)
    {
        printf("Task1: Priority = 5\n");
    }
}

void Task2(void *pvParameters)
{
    while(1)
    {
        printf("Task2: Priority = 7\n");
    }
}
void init_task(void *pvParameters)
{
    printf("Initial task: Priority = 8\n");
    xTaskCreate(Task1, "Task1", 2048, NULL, 5, &xHandleTask1);
    xTaskCreate(Task2, "Task2", 2048, NULL, 7, &xHandleTask2); 
    printf("Initial task is finishing after creating two tasks with same priorities.\n");
    vTaskDelete( xHandleTask ); 
}

void app_main()
{
    xTaskCreate(init_task, "Initial_Task", 2048, NULL, 8, &xHandleTask);                      
}
