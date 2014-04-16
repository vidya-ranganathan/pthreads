#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

#define NTHREADS 2

typedef struct th_data
{
	int	th_num;
} thdata;


void *dummy_func(thdata *data)
{
	printf("thread number is = %d\n", data->th_num);
	pthread_exit(NULL);
}

int main()
{
	int i, j, rc, detachstate;
	pthread_t tid;
	pthread_attr_t	attr;

	thdata tdata;

	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

	for(j = 0; j<NTHREADS; j++)
	{
		tdata.th_num = j ;
		rc = pthread_create(&tid, &attr, (void *)&dummy_func, (thdata *)&tdata);
		if(rc) 
		{
			printf("rc = %d, thread create fails \n", rc);
			exit(rc);
		}
		/* wait for the thread */
		rc = pthread_join(tid, NULL);
		if(rc)
		{
			printf("rc = %d, pthread_join fails\n", rc);
			exit(rc);
		}
	}

	pthread_attr_destroy(&attr);
	pthread_exit(NULL);
}
