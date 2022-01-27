#include <stdio.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>


TaskHandle_t xHandle_1;
TaskHandle_t xHandle_2;


void sensortask_1(void *pvparameters)
{
    while(1)
    {
        printf("SENSOR TASK  RUNNING\n");
        vTaskDelay(1000/ portTICK_PERIOD_MS);
    }
}
void Alarmtask_1(void *pvparameters)
{
    
    while(1)
    {
        printf("ALARM TASK  RUNNING\n");
       
        vTaskDelay(1000/ portTICK_PERIOD_MS);
    }
}
void app_main()
{
    BaseType_t result;
    
    result=xTaskCreate(sensortask_1,"sensortask_1",1024,NULL,10,&xHandle_1);

    if(result==pdPASS)
    {
        printf("sensortask created\n");
    }
    result=xTaskCreate(Alarmtask_1,"Alarmtask_1",1024,NULL,20,&xHandle_2);

    if(result==pdPASS)
    {
        printf("Alarmtask created\n");
    }
}