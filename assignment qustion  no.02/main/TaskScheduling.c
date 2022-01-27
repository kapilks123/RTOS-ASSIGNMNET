#include <stdio.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

TaskHandle_t xHandleTaskLog;
TaskHandle_t xHandleTaskLog2;

void Task1(void * pvParameters)
{
     UBaseType_t stackSize;
    while(1)
    {
    printf("Inside Task1---> \n");
    stackSize = uxTaskGetStackHighWaterMark(NULL);
    printf("%d",stackSize);
    vTaskDelay(pdMS_TO_TICKS(1000));
    }
    //vTaskDelete(xHandleTaskLog);
}

void Task2(void * arg)
{
    UBaseType_t stackSize;

    while(1)
    {
    printf("Inside Task2---> \n");
    stackSize = uxTaskGetStackHighWaterMark(NULL);
    printf("%d",stackSize);
    vTaskDelay(pdMS_TO_TICKS(1000));
    }
    //    vTaskDelete(xHandleTaskLog2);
}


void app_main()
{
    printf("Inside Main\n");
    BaseType_t result;
    
    BaseType_t result2;

    result = xTaskCreate(Task1,"Task1",2048,NULL,1,&xHandleTaskLog);
    if (result == pdPASS)
    {
        printf("Task1 Created!\n");
    }

   result2 = xTaskCreate(Task2,"Task2",2048,NULL,2,&xHandleTaskLog2);
    if (result2 == pdPASS)
    {
        printf("Task2 Created\n");
    }
}



 
