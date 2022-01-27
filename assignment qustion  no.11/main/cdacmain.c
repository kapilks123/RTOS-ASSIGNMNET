#include <stdio.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <driver/gpio.h>

TaskHandle_t xHandle_1;


void sensortask_1(void *pvparameters)
{
    uint32_t count=0;
    while(1)
    {
        printf("SENSOR TASK  RUNNING\n");
        vTaskDelay(1000/ portTICK_PERIOD_MS);
        count++;
        if(count==5)
        {
            vTaskDelete(xHandle_1); 
        }
    }
}

void app_main()
{
    BaseType_t result;
    
    result=xTaskCreate(sensortask_1,"sensortask_1",2048,NULL,5,&xHandle_1);

    if(result==pdPASS)
    {
        printf("sensortask created\n");
    }
    
}