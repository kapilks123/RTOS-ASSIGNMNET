/*#include<stdio.h>
#include<freertos/FreeRTOS.h>
#include<freertos/semphr.h>
#include <freertos/task.h>

SemaphoreHandle_t x;
TaskHandle_t task1;
TaskHandle_t task2;
TaskHandle_t task3;
TaskHandle_t task4;
// 
//RESOURCE
//
int global=0;
int var=0;
//needed varibles
int count1=1;
int count2=2;

void task_1(void *pv)
{
    while(1)
    {
        while(count1==1)
        {
            
            if(xSemaphoreTake(x,portMAX_DELAY)== pdTRUE)
            {
            global++;
            count1--;
            printf("TASK 1:%d\n",global);
            }
            else
            {
                perror("Error ");
                count1--;
            }
            xSemaphoreGive(x);
            
            vTaskDelay(1000/portTICK_PERIOD_MS);
        }
        
    }
}
void task_2(void *pv)
{
   while(1)
   {
       while(count1==1)
        {
            
            if(xSemaphoreTake(x,portMAX_DELAY)== pdTRUE)
            {
            global++;
            printf("TASK 2:%d\n",global);
            count1--;
            }
            else
            {
                perror("Error ");
                count1--;
            }
            xSemaphoreGive(x);
            
            vTaskDelay(1000/portTICK_PERIOD_MS);
        }
        
   } 
}
void task_3(void *pv)
{
   while(1)
   {
       while(count2==1)
        {
            
            if(xSemaphoreTake(x,portMAX_DELAY)==pdTRUE)
            {
            global++;
            printf("TASK 3:%d\n",var);
            count2--;
            }
            else
            {
                perror("Error ");
                count2--;
            }

            xSemaphoreGive(x);
            
            vTaskDelay(1000/portTICK_PERIOD_MS);
        }
   } 
}
void task_4(void *pv)
{
    while(1)
    {
        while(count2 != 0)
        {
           //xSemaphoreGive(x);
           //xSemaphoreGive(x);
           count2-- ;
        }
        count1++ ;
         vTaskDelay(1000/portTICK_PERIOD_MS);
    }
}

void app_main()
{
    x=xSemaphoreCreateCounting(2,2);
    xTaskCreate(task_1,"task_1",2048,NULL,5,&task1);
    xTaskCreate(task_2,"task_2",2048,NULL,5,&task2);
    xTaskCreate(task_3,"task_3",2048,NULL,5,&task3);
    xTaskCreate(task_4,"task_4",2048,NULL,5,&task4);
}*/

#include<stdio.h>
#include<freertos/FreeRTOS.h>
#include<freertos/semphr.h>
#include <freertos/task.h>

SemaphoreHandle_t x;
TaskHandle_t task1;
TaskHandle_t task2;
TaskHandle_t task3;
TaskHandle_t task4;
/* 
RESOURCE
*/
int global=0;
int var=0;
//needed varibles
int count1=1;
int count2=1;

void task_1(void *pv)
{
    while(1)
    {
        while(count1==1)
        {
            count1--;
            xSemaphoreTake(x,portMAX_DELAY);
            global++;
            printf("TASK 1:%d\n",global);
            xSemaphoreGive(x);
            count1++;
            vTaskDelay(1000/portTICK_PERIOD_MS);
        }
        
    }
}
void task_2(void *pv)
{
   while(1)
   {
       while(count1==1)
        {
            count1--;
            xSemaphoreTake(x,portMAX_DELAY);
            global++;
            printf("TASK 2:%d\n",global);
            xSemaphoreGive(x);
            count1++;
            vTaskDelay(1000/portTICK_PERIOD_MS);
        }
        
   } 
}
void task_3(void *pv)
{
   while(1)
   {
       while(count2==1)
        {
            count2--;
            xSemaphoreTake(x,portMAX_DELAY);
            var++;
            printf("TASK 3:%d\n",var);
            xSemaphoreGive(x);
            count2++;
            vTaskDelay(1000/portTICK_PERIOD_MS);
        }
   } 
}
void task_4(void *pv)
{
    while(1)
    {
        while(count2==1)
        {
            count2--;
            xSemaphoreTake(x,portMAX_DELAY);
            var++;
            printf("TASK 4:%d\n",var);
            xSemaphoreGive(x);
            count2++;
            vTaskDelay(1000/portTICK_PERIOD_MS);
        }
    }
}

void app_main()
{
    x=xSemaphoreCreateCounting(2,2);
    xTaskCreate(task_1,"task_1",2048,NULL,5,&task1);
    xTaskCreate(task_2,"task_2",2048,NULL,5,&task2);
    xTaskCreate(task_3,"task_3",2048,NULL,5,&task3);
    xTaskCreate(task_4,"task_4",2048,NULL,5,&task4);
}