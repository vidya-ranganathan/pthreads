/* 
1> master thread is main, which process 25 jobs. 
Until job count is less than 25, jobs are processed.

2> master takes lock and puts the jobAvail switch ON 
and sends conditional signal to slave. 

3> Following mutex is unlocked.

4> mutex lock is taken in slave. 

5> slave thread also process all delegated 25 jobs 
until jobs are less than 25. 

5> if jobAvail is OFF, pthread_cont_wait is made in slave.

6> in slave if jobAvail is ON, some task is done. 
When task is complete jobAvail is made OFF.

7> finally mutex is unlocked in slave. 
The loop continues in slave and master untill all jobs are handled.
*/




#include <stdlib.h>
#include<signal.h>
#include<pthread.h>
#include<stdio.h>
#include<malloc.h>

pthread_mutex_t	m;
pthread_cond_t	cv;
pthread_key_t	key;

int	jobInfo[50];		/* job data passed to thread  */
int	jobAvail = 0;		/* boolean .. jobs available  */
int	i = 0;
int 	jobCount = 0;		/* job index for slave thread  */

void *slave(void *threadID)
{
	int threadNum = *(int *)threadID;
	int	*local_job;
	while(jobCount < 25)
	{
		pthread_mutex_lock(&m);
		while(jobAvail < 1 )
			pthread_cond_wait(&cv,&m);

		local_job = (int *)malloc(4);
		pthread_setspecific(key, (void *)local_job);
		*local_job = jobInfo[jobCount];
		jobCount++;
		jobAvail--;       /* switch OFF  */
		pthread_mutex_unlock(&m);
		printf("thead# %d handling job with local_job#%d\n", \
			threadNum, *local_job);
	}
	pthread_exit(NULL);
}

main()
{
	pthread_t	thd1, thd2, thd3;
	int j = 1;

	pthread_mutex_init(&m, NULL);
	pthread_cond_init(&cv, NULL);

	pthread_create(&thd1, NULL, slave, (void*)&j);
	j++;
	pthread_create(&thd2, NULL, slave, (void*)&j);
	j++;
	pthread_create(&thd3, NULL, slave, (void*)&j);

	while(i<25)
	{
		jobInfo[i] = i;
		i++;
		
		pthread_mutex_lock(&m);
		jobAvail++;     /* switch ON  */
		pthread_cond_signal(&cv);
		pthread_mutex_unlock(&m);
	}
	printf("simulate waiting for others to finish\n");
	sleep(5);

	pthread_join(thd1, NULL);
	pthread_join(thd2, NULL);
	pthread_join(thd3, NULL);

	pthread_mutex_destroy(&m);
	pthread_cond_destroy(&cv);
	exit(0);
}
