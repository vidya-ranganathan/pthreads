#include <stdio.h>
#include <pthread.h>

void *funca(void *arg)
{
	char * buffer = arg;
	printf("main thread says - %s\n", buffer);
	pthread_exit(NULL);
}

main()
{
	pthread_t 	thd1;
	int rc;
	char buffer[]="hi, There ..!";

	rc = pthread_create(&thd1, NULL, (void *)funca, (void *)buffer);
	if(rc)
	{
		printf("%s", "pthread create fails");
	}

	pthread_exit(NULL);
}
