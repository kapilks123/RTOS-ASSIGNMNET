#include <stdio.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include<freertos/timers.h>


TimerHandle_t ST[2];


void timerCallback(TimerHandle_t xTimer);
void timerCallback2(TimerHandle_t xTimer);

void app_main()
{
    UBaseType_t GetPriority;

	printf("Inside Main Function!");
	
    GetPriority = uxTaskPriorityGet(NULL);

    printf("%d",GetPriority);
    
    ST[0]= xTimerCreate("TimerDemo",pdMS_TO_TICKS(2000),pdTRUE,NULL,timerCallback);

	if(ST[0] == NULL)
	{
		perror("Error:");

	}
	else
	{
      xTimerStart(ST[0],pdMS_TO_TICKS(100));
	}

    ST[1]= xTimerCreate("TimerDemo",pdMS_TO_TICKS(2000),pdFALSE,NULL,timerCallback2);

	if(ST[1] == NULL)
	{
		perror("Error:");

	}
	else
	{
      xTimerStart(ST[1],pdMS_TO_TICKS(100));
	}


	while(1)
	{
		printf("Main Task!\n");
		vTaskDelay(pdMS_TO_TICKS(1000));

	}
}

void timerCallback(TimerHandle_t xTimer)
{
   	printf("Inside first Callback\n");
}

void timerCallback2(TimerHandle_t xTimer)
{
   	printf("Inside second Callback\n");
}