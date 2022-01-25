#include <stdio.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <freertos/semphr.h>

SemaphoreHandle_t semph;

void Task_1(void *pvParameters)
{
    int temp = 0;
    while(1)
    {
        
        printf("In Task1: temp = %d\n", temp);
        temp++;
        vTaskDelay(1000 / portTICK_PERIOD_MS);
        if(temp == 8)
        {
            xSemaphoreGive(semph);
            temp = 0;
        }
    }
}

void Task_2(void *pvParameters)
{
    while(1)
    {
        xSemaphoreTake(semph, portMAX_DELAY);
        printf("In Task_2: after value of temp = 7 in Task_1\n");
    }
}

void app_main()
{
    semph = xSemaphoreCreateBinary();
    xTaskCreate(Task_1, "Task_1", 2048, NULL, 5, NULL);
    xTaskCreate(Task_2, "Task_2", 2048, NULL, 7, NULL); 
    xSemaphoreTake(semph, portMAX_DELAY);
    printf("Main Task\n");                   
}