#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int	g_count = 0;

pthread_mutex_t	g_count_mutex;


void *callFunc(void *unused)
{
	int i;
	
	for(i=0;i<10;i++)
	{
		pthread_mutex_lock(&g_count_mutex);
		g_count++;
		pthread_mutex_unlock(&g_count_mutex);
		printf("count in secondary thread is %d\n", g_count);
		sleep(1);
	}

	pthread_exit(NULL);
}
main()
{
	pthread_t	callThd;
	int ret;
	int i;

	pthread_mutex_init(&g_count_mutex, NULL);	/* initialize mutex  */
	ret = pthread_create(&callThd, NULL, callFunc, NULL);	/* attr and rc are NULL  , create thread  */
	if(ret)
	{
		printf("pthread create failed , rc = %d\n", ret);
	}
	for(i=0;i<10;i++)
	{
		pthread_mutex_lock(&g_count_mutex);
		g_count++;
		pthread_mutex_unlock(&g_count_mutex);
		printf("count in primary thread is %d\n", g_count);
		sleep(1);
	}


	pthread_mutex_destroy(&g_count_mutex);
	pthread_exit(NULL);
}
