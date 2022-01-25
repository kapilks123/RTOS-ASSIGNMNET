#include <stdio.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <freertos/queue.h>

QueueHandle_t sensor_queue;

void Temp_Sensor(void *pvParameters)
{
    int temp_send = 15;
    while(1)
    {
        printf("Send Data: Temperature sensed in celcius: %d\n", temp_send);
        xQueueSend(sensor_queue, &temp_send, portMAX_DELAY);
        temp_send++;
        if(temp_send == 23)
        {
            vTaskDelay(2000 / portTICK_PERIOD_MS);
            temp_send = 15;
        }
    }
}

void Temp_Processor(void *pvParameters)
{
    int temp_recv;
    while(1)
    {
        xQueueReceive(sensor_queue, &temp_recv, portMAX_DELAY);
        printf("Received Data: Temperature in Kelvin: %d\n", temp_recv + 273);
    }
}

void app_main()
{
    sensor_queue = xQueueCreate(7, sizeof(int));
    xTaskCreate(Temp_Sensor, "Temp_Sensor", 2048, NULL, 7, NULL);
    xTaskCreate(Temp_Processor, "Temp_Processor", 2048, NULL, 5, NULL); 
    printf("Main Task\n");                   
}