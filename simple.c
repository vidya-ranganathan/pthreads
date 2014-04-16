#include <stdio.h>
#include <pthread.h>

/* a simple program for thread create  */

void *funca(void *arg)
{
	long tid = (long)arg;
	printf("thread id is %ld\n", tid);
	pthread_exit(NULL);
}

main()
{
	pthread_t 	thd1;
	int rc;
	long tid = 99;
	char buffer[]="hi, There ..!";

	rc = pthread_create(&thd1, NULL, (void *)funca, (void *)tid);
	if(rc)
	{
		printf("%s", "pthread create fails");
	}

	pthread_exit(NULL);
}
