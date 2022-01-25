#include <stdio.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>


TaskHandle_t xHandleTask1, xHandleTask2, xHandleTask3, xHandleTask4;


void Task2(void *pvParameters)
{
    while(1)
    {
        printf("Task2: Priority = 8\n");
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}

void Task3(void *pvParameters)
{
    while(1)
    {
        printf("Task3: Priority = 4\n");
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}


void Task4(void *pvParameters)
{
    while(1)
    {
        printf("Task4: Priority = 6\n");
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}
void init_Task1(void *pvParameters)
{
    xTaskCreate(Task2, "Task2", 2048, NULL, 8, &xHandleTask2);
    printf("Task 2 has created inside the init task with highest priority i.e. 10."); 
    xTaskCreate(Task3, "Task3", 2048, NULL, 4, &xHandleTask3);
    printf("Task 3 has created inside the init task with highest priority i.e. 10."); 
    xTaskCreate(Task4, "Task4", 2048, NULL, 6, &xHandleTask4); 
    printf("Task 4 has created inside the init task with highest priority i.e. 10.");
    vTaskDelete( xHandleTask1 ); 
}


void app_main()
{
    xTaskCreate(init_Task1, "Task1", 2048, NULL, 10, &xHandleTask1);             
}
