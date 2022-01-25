#include <stdio.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <driver/gpio.h>

#define LED_BLUE 15
#define LED_RED 14

void LedRed(void *pvParameters)
{
    esp_rom_gpio_pad_select_gpio(LED_RED);
    gpio_set_direction(LED_RED, GPIO_MODE_OUTPUT);
    
    while(1)
    {
        printf("Led_Red Task.\n");
        gpio_set_level(LED_RED, 0);
        vTaskDelay(1000 / portTICK_PERIOD_MS);
        gpio_set_level(LED_RED, 1);
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}

void LedBlue(void *pvParameters)
{
    xTaskCreate(LedRed, "Led_Red", 2048, NULL, 6, NULL); 
    esp_rom_gpio_pad_select_gpio(LED_BLUE);
    gpio_set_direction(LED_BLUE, GPIO_MODE_OUTPUT);
    
    while(1)
    {
        printf("Led_Blue Task.\n");
        gpio_set_level(LED_BLUE, 0);
        vTaskDelay(1000 / portTICK_PERIOD_MS);
        gpio_set_level(LED_BLUE, 1);
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}

void app_main()
{
    xTaskCreate(LedBlue, "Led_Blue", 2048, NULL, 8, NULL); 
    printf("Main Task\n");                                          
}