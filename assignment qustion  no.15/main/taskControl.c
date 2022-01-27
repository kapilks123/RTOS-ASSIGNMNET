#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include<stdio.h>

TaskHandle_t TaskHandle_1;
TaskHandle_t TaskHandle_2;

void MyTask1(void* pvParameters)
{
    while(1)
    {
    printf("Task 1 is running\n");
    vTaskDelay(pdMS_TO_TICKS(1200));  
    printf("Task 1 is resuming task 2 \n");
    vTaskResume(TaskHandle_2);
    }
    
}

void MyTask2(void* pvParameters)
{   
    while(1)
    {
         
    printf("Task2, is running \n");  
    vTaskDelay(pdMS_TO_TICKS(1200));                
    printf("task 2 is suspending itself\n");
    vTaskSuspend(NULL);
    } 

}

void app_main()
{  
 

  xTaskCreate(MyTask1, "Task1", 2048, NULL, 3, &TaskHandle_1);
  xTaskCreate(MyTask2, "Task2", 2048, NULL, 5, &TaskHandle_2);
}
