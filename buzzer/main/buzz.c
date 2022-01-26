#include <stdio.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <driver/gpio.h>

#define ALARM_PIN 15

void SensorTask (void *pv)
{
    while (1)
    {    
    printf("Sensor task : %d \n",uxTaskGetStackHighWaterMark(NULL));
    printf("Sensor Task : CPU ID %d\n",xTaskGetAffinity(NULL));
    vTaskDelay (1000 /  portTICK_PERIOD_MS);
    }
}

void AlarmTask (void *pv)
{
   esp_rom_gpio_pad_select_gpio(ALARM_PIN);
    gpio_set_direction(ALARM_PIN,GPIO_MODE_OUTPUT);
    while (1)
    {    
    printf("Stack task : %d \n",uxTaskGetStackHighWaterMark(NULL));
    printf("Alarm Task : CPU ID %d\n",xTaskGetAffinity(NULL));
    gpio_set_level(ALARM_PIN,0 );
   vTaskDelay (100/  portTICK_PERIOD_MS);
    gpio_set_level(ALARM_PIN,1 );
     vTaskDelay (100 /  portTICK_PERIOD_MS);
    }
}
void app_main ()
{
   xTaskCreate(SensorTask,"sensortask",2048,NULL,5,NULL);
    xTaskCreate(AlarmTask,"Alarmtask",2048,NULL,5,NULL);
    printf("hello world ! \n");
}
