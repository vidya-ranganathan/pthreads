#include <stdio.h>
#include <pthread.h>

void *funca(void *arg)
{
	printf("thread says .. %s\n", (char *)arg);
	pthread_exit((void *)99);
}

int
main()
{
	pthread_t	thd1;
	pthread_attr_t	attr;

	int rc;
	char buffer[]="hi, there";
	int thd1_rc;

	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
	rc = pthread_create(&thd1, &attr, funca, (void *)buffer);
	if(rc)
	{
		printf("pthread create fails \n");
	}

	pthread_join(thd1, (void **)&thd1_rc);
	printf("thread return val , rc = %d\n", thd1_rc);
	pthread_exit((void *)NULL);
}
