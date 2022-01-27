#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "rom/gpio.h"
#include "freertos/semphr.h"

#define ESP_INR_FLAG_DEFAULT 0
#define CONFIG_BUTTON_PIN 16
#define CONFIG_LED_PIN 2

TaskHandle_t ISR = NULL;
TaskHandle_t button = NULL;
BaseType_t Task1,Task2;
SemaphoreHandle_t sem_isr;
bool led_status;

//ISR TASK
void IRAM_ATTR button_isr_handler(void * pvParameters)
{
   // printf("Button Pressed!\n");
   
    xSemaphoreGiveFromISR( sem_isr, NULL);
    portYIELD_FROM_ISR();
}
//Dereffered Task
void isrHelperTask(void * pvParameter)
{
    printf("Inside ISR Helper Task!\n");
    led_status =false;
    
    while(1)
    {
        
        if(xSemaphoreTake(sem_isr,portMAX_DELAY) == pdTRUE)
        {
           printf("Waiting for button Pressing\n");
           taskYIELD();
        }
        led_status = 1;
        gpio_set_level(CONFIG_LED_PIN,led_status);
        //vTaskDelay(pdMS_TO_TICKS(5000));
    }
}

//Button Task
void buttonTask(void * pvParameter)
{
    printf("Inside button Task!\n");
    uint32_t count =0;
    while(1)
    {
    if(count == 0)
    {
    led_status = true;
    gpio_set_level(CONFIG_LED_PIN,led_status);
    count++;
    }
    else
    {
    //vTaskDelay(pdMS_TO_TICKS(1000));
    led_status = false;
     gpio_set_level(CONFIG_LED_PIN,led_status);
     count=0;
    }
    //vTaskDelay(pdMS_TO_TICKS(1000));
    }
    
}

void app_main()
{
    printf("Inside Main\n");
    sem_isr=xSemaphoreCreateBinary();

    //xSemaphoreTake(sem_isr,portMAX_DELAY);

    esp_rom_gpio_pad_select_gpio(CONFIG_BUTTON_PIN);
    esp_rom_gpio_pad_select_gpio(CONFIG_LED_PIN);

    //set the correct direction
    gpio_set_direction(CONFIG_BUTTON_PIN,GPIO_MODE_INPUT);
    gpio_set_direction(CONFIG_LED_PIN,GPIO_MODE_OUTPUT);

    //enable interrupt on falling (0->1) edge for button pin
    gpio_set_intr_type(CONFIG_BUTTON_PIN,GPIO_INTR_NEGEDGE|GPIO_INTR_POSEDGE);

    //install the drivers GPIO ISR handler services which allows per pin GPIO interrupt handler.
    gpio_install_isr_service(ESP_INR_FLAG_DEFAULT);

    //attach the interrupt service routine
    gpio_isr_handler_add(CONFIG_BUTTON_PIN,button_isr_handler,NULL);

    //Creating Task to be executed
    Task1 = xTaskCreate(buttonTask,"Button_TASK",2048,NULL,4,&button);
    if(Task1 == pdPASS)
    {
        printf("Task Created Successfully!\n");
    }

    Task2 = xTaskCreate(isrHelperTask,"isrHelper",2048,NULL,5,&ISR);
    if(Task2 == pdPASS)
    {
        printf("HelperTask Created Successfully!\n");
    }
    
}
