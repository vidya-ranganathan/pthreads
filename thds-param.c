/* demonstrates message passing via struct to thread */


#include <unistd.h>     /* Symbolic Constants */
#include <sys/types.h>  /* Primitive System Data Types */ 
#include <errno.h>      /* Errors */
#include <stdio.h>      /* Input/Output */
#include <stdlib.h>     /* General Utilities */
#include <pthread.h>    /* POSIX Threads */
#include <string.h>     /* String handling */

/* prototype for thread routine */
void printMsg ( void *ptr );

typedef struct str_thrdata
{
	int 	thread_no;
	char	message[100];
} thdata;

int main()
{
	pthread_t thread1, thread2;	/* thread identifiers  */
	thdata data1, data2;

	/* initialize data  */
	data1.thread_no = 1;
	strcpy(data1.message, "Hello!");

	data2.thread_no = 2;
	strcpy(data2.message, "Hi!");

	pthread_create(&thread1, NULL, ( void *)&printMsg, (void *) &data1);	
	pthread_create(&thread2, NULL, ( void *)&printMsg, (void *) &data2);	

	/* block main until both threads complete their jobs  */
	pthread_join(thread1, NULL);
	pthread_join(thread2, NULL);

	exit(0);
}

/* call from thread  */
void printMsg ( void *ptr )
{
    thdata *data;            
    data = (thdata *) ptr;  /* type cast to a pointer to thdata */
    
    /* do the work */
    printf("Thread %d says %s \n", data->thread_no, data->message);
    
    pthread_exit(0); /* exit */
} /* printMsg ( void *ptr ) */
