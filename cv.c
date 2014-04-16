#include <signal.h>
#include <stdio.h>
#include <pthread.h>

int ready = 0;
pthread_mutex_t		m;
pthread_cond_t		cv;


void *
slave(void *threadid)
{
	int threadNum = *(int *)threadid;
	pthread_mutex_lock(&m);
		while(ready != 0)
			pthread_cond_wait(&cv, &m);
	pthread_mutex_unlock(&m);
	printf("thread %d processing ...\n", threadNum);

	pthread_exit(NULL);
}

main()
{
	pthread_t	thd1, thd2, thd3;
	int tid;

	pthread_mutex_init(&m, NULL);
	pthread_cond_init(&cv, NULL);

	tid=1;
	pthread_create(&thd1, NULL, slave, (int *)&tid);
	tid++;
	pthread_create(&thd2, NULL, slave, (int *)&tid);
	tid++;
	pthread_create(&thd2, NULL, slave, (int *)&tid);

	/* do work  */
	printf("%s\n", "main - start work ");
	pthread_mutex_lock(&m);
	ready = 1;
	pthread_cond_broadcast(&cv);
	pthread_mutex_unlock(&m);
	printf("%s\n", "main - work done ");
	sleep(5);

	
	pthread_mutex_destroy(&m);
	pthread_cond_destroy(&cv);

	pthread_exit((void *)0);
}
