#include<stdio.h>
#include<pthread.h>
void  *helloESPThread (void *arg)
{
    printf("Thread function\n");
    return NULL;
}
 
 void app_main()
 {
     pthread_t thread_id;
     printf("hello ESP32!\n");
     pthread_create(&thread_id, NULL, helloESPThread, NULL); 
     pthread_join(thread_id,NULL);  
 }