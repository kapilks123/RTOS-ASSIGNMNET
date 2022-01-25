#include <stdio.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <freertos/queue.h>

QueueHandle_t sensor_queue;
BaseType_t queue_send;

void Temp_Sensor(void *pvParameters)
{
    int temp_send = 15;
    while(1)
    {
        queue_send = xQueueSend(sensor_queue, &temp_send, pdMS_TO_TICKS(2000));
        if(queue_send == errQUEUE_FULL)
        {
            printf("Queue is full.\n");
        }  
        else
        {
            printf("Send Data: %d\n", temp_send);
            temp_send++;
        }
    }
}

void Temp_Processor(void *pvParameters)
{
    int temp_recv = 0;
    while(1)
    {
        vTaskDelay(10000 / portTICK_PERIOD_MS); 
        //xQueueReceive(sensor_queue, &temp_recv, portMAX_DELAY);
        //printf("Received Data: %d\n", temp_recv);
    }
}

void app_main()
{
    sensor_queue = xQueueCreate(10, sizeof(int));
    xTaskCreate(Temp_Sensor, "Temp_Sensor", 2048, NULL, 7, NULL);
    xTaskCreate(Temp_Processor, "Temp_Processor", 2048, NULL, 5, NULL); 
    printf("Main Task\n");                   
}
