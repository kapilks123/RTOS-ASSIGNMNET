#include <stdio.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <freertos/semphr.h>
#include <freertos/queue.h>
#include<errno.h>


TaskHandle_t send_hook;
TaskHandle_t receive_hook;
BaseType_t send, send2;
BaseType_t receive, receive2;
QueueHandle_t Msg, Msg2;
BaseType_t Msg_Send,Msg_Send2;
BaseType_t Msg_Rec,Msg_Rec2;

static void Sender(void* parameters);
static void Receiver(void* parameters);
static void Sender2(void* parameters);
static void Receiver2(void* parameters);

void app_main()
{
    Msg = xQueueCreate( 10, sizeof(char[100]));
  	if(Msg == NULL)
  	{
  		 perror("Error");
  	}

    Msg2 = xQueueCreate( 10, sizeof(struct hotelStaffData *));
  	if(Msg2== NULL)
  	{
  		 perror("Error");
  	}
   
    send = xTaskCreate( Sender,"sending_msg",4096,NULL,4,NULL);
    if(send == 	errCOULD_NOT_ALLOCATE_REQUIRED_MEMORY)
    {
	   perror("Error--> Sender");
    }
  	//configASSERT(send == pdPASS);
    send2 = xTaskCreate( Sender2,"sending_msg",4096,NULL,4,NULL);
    if(send2 == 	errCOULD_NOT_ALLOCATE_REQUIRED_MEMORY)
    {
	   perror("Error--> Sender");
    }

  	receive = xTaskCreate( Receiver,"Receiving_msg",4096,NULL,3,NULL);
    if(receive == 	errCOULD_NOT_ALLOCATE_REQUIRED_MEMORY)
    {
	   perror("Error--> Sender");
    }

	receive2 = xTaskCreate( Receiver,"Receiving_msg",4096,NULL,3,NULL);
    if(receive == 	errCOULD_NOT_ALLOCATE_REQUIRED_MEMORY)
    {
	   perror("Error--> Sender");
    }
  	//configASSERT(receive == pdPASS);

 
  	//start the freeRTOS Scheduler

  	//vTaskStartScheduler();
}

static void Sender(void* parameters)
{
	char Data[100]= "Passing data from HP Task to LP Task!" ;
	struct hotelStaffData
	{
		char name[20] = "RAMU";
		char From[20]="JAMMU";
		int Age=21;
		int YOE=2;
	}*hotelData

	while(1)
	{
	   Msg_Send = xQueueSend(Msg,hotelData,(TickType_t)100);
	   if(Msg_Send == pdTRUE )
	   {
	   printf("Sending from Send1 Task\n");
	   }
	   printf("Data Send %s:\n",hotelData.name);
	   printf("Data Send %s:\n",hotelData.From);
	   printf("Data Send %d:\n",hotelData.Age);
	   printf("Data Send %d:\n",hotelData.YOE);
	   // taskYIELD();
      vTaskDelay(pdMS_TO_TICKS(1000));
	}
      //vTaskDelete(NULL);
}

static void Sender2(void* parameters)
{
	char Data[100]= "Passing data from HP Task to LP Task!";
    while(1)
	{
	   Msg_Send2 = xQueueSend(Msg,Data,(TickType_t)100);
	   printf("Sending2 Task done ---> %s\n", Data);
	   // taskYIELD();
      vTaskDelay(pdMS_TO_TICKS(1000));
	}
      //vTaskDelete(NULL);
}

static void Receiver(void* parameters)
{
	char RData[100]="\0";
	while(1)
	{
		   Msg_Rec= xQueueReceive(Msg, RData,( TickType_t ) 100);
		   printf("Data Receiver --->%s:\n",RData);
           vTaskDelay(pdMS_TO_TICKS(1000));
	}
		//   taskYIELD();
	   //vTaskDelete(NULL);
}

static void Receiver2(void* parameters)
{
		struct hotelStaffData
	    {
		char name[20]="\0",
		char From[20]="\0",
		int Age=0,
		int YOE=0;
	    }*hotelData_rec ;
	while(1)
	{
		   Msg_Rec= xQueueReceive(Msg2, hotelData_rec,( TickType_t ) 100);
		   	   printf("Data Rec %s:\n",hotelData.name);
	   printf("Data Rec %s:\n",hotelData.From);
	   printf("Data Rec %d:\n",hotelData.Age);
	   printf("Data Rec %d:\n",hotelData.YOE);
           vTaskDelay(pdMS_TO_TICKS(1000));
	}
		//   taskYIELD();
	   //vTaskDelete(NULL);
}

