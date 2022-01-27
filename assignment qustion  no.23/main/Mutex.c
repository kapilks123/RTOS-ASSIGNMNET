#include <stdio.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <freertos/semphr.h>
#include <string.h>
char usr_msg[250]={0};
uint8_t count;

TaskHandle_t xTaskHandle1=NULL;
TaskHandle_t xTaskHandle2=NULL;

// The task to be created.  Two instances of this task are created.
static void prvPrintTask( void *parameters );
// The function that uses a mutex to control access to standard out.

static void prvNewPrintString(void *parameters );

//void vApplicationIdleHook( void );

SemaphoreHandle_t xMutex;

void app_main()
{
    printf("Inside Main\n");

    //printf(usr_msg);
	xMutex = xSemaphoreCreateMutex();
	//srand( 567 );
	if(xMutex != NULL)
	{
		xTaskCreate( prvPrintTask, "Print1", 2048, "Task 1 ******************************************\r\n", 3, NULL );
		xTaskCreate( prvNewPrintString, "Print2", 2048, "Task 2 ------------------------------------------\r\n", 2, NULL );
	}
}

static void prvNewPrintString( void * parameter )
{

	static char cBuffer[80]="Task 2 ------------------------------------------\n";

	//printf("TASK2 buffer: %s",cBuffer);
	while(1)
	{
	if(count != 0)
	{
        xSemaphoreTake(xMutex, portMAX_DELAY);
	    count++;
        strcpy(usr_msg,cBuffer);
        count =0;
	    printf("Global Buffer Value from TASK2: %s %d\n",usr_msg,count);
        //xSemaphoreGive(xMutex);
	}
	else
	{
         xSemaphoreGive(xMutex);
         printf("Task2 released the critical section!");
    }

	//xSemaphoreGive(xMutex);
	vTaskDelay(1000000/portTICK_PERIOD_MS);
    }
}

static void prvPrintTask( void * parameter )
{
   static char dBuffer[80]="Task 1 ******************************************\n";
   //printf("TASK1 buffer: %s",dBuffer);
   while(1)
   {
    xSemaphoreTake(xMutex, portMAX_DELAY);

    strcpy(usr_msg,dBuffer);
    count++;
    printf("Global Buffer Value from Task 1: %s %d",usr_msg,count);

    xSemaphoreGive(xMutex);

   vTaskDelay(1000000/portTICK_PERIOD_MS);
   }
}

/*void vApplicationIdleHook( void )
{
  printf("No processor running , system in Eco Mode\n");
}*/
