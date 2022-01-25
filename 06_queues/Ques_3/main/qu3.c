#include <stdio.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <freertos/queue.h>

QueueHandle_t array_queue;

void send_array(void *pvParameters)
{
    char arrS[4][15] = {"kapil", "9998887776", "Dehradun", "B.Tech"};
    while(1)
    {
        for(int i = 0; i<4; i++)
        {
            xQueueSend(array_queue, arrS+i, portMAX_DELAY);
            printf("Send Data: %s\n", *(arrS+i));
            vTaskDelay(1000 / portTICK_PERIOD_MS);
        }
    }
}

void recv_array(void *pvParameters)
{
    char arrR[4][15];
    while(1)
    {
        for(int i = 0; i<4; i++)
        {
            xQueueReceive(array_queue, arrR+i, portMAX_DELAY);
            printf("Received Data: %s\n", *(arrR+i));
        }
    }
}

void app_main()
{
    array_queue = xQueueCreate(4, 20);
    xTaskCreate(send_array, "Sending_array", 2048, NULL, 7, NULL);
    xTaskCreate(recv_array, "Receiving_array", 2048, NULL, 5, NULL); 
    printf("Main Task\n");                   
}
