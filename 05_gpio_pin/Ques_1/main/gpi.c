#include <stdio.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <driver/gpio.h>

#define LED_PIN 15

void SensorTask(void *pvParameters)
{
    while(1)
    {
        printf("Sensor Task\n");
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}

void LedTask(void *pvParameters)
{
    esp_rom_gpio_pad_select_gpio(LED_PIN);
    gpio_set_direction(LED_PIN, GPIO_MODE_OUTPUT);

    while(1)
    {
        gpio_set_level(LED_PIN, 0);
        vTaskDelay(1000 / portTICK_PERIOD_MS);
        gpio_set_level(LED_PIN, 1);
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}

void app_main()
{
    xTaskCreate(SensorTask, "Sensor_Task", 1024, NULL, 8, NULL); 
    xTaskCreate(LedTask, "Led_Task", 1024, NULL, 8, NULL); 
    printf("Main Task\n");                                          
}