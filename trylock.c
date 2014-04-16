#include <stdio.h>
#include <pthread.h>
#include <errno.h>

int 	totalBalls;
pthread_mutex_t	m;
pthread_attr_t	attr;

void *redballs(void *arg)
{
	int redBalls = 0;
	long tid = (long)arg;
	int rc, i;
	for(i=0; i< 1000; i++)
	{
		rc = pthread_mutex_trylock(&m);
		if(rc = EBUSY)
		{
				/* keep a local count of balls 
				 * in this thread  */
				redBalls += 5;
		}
		else
		{
				totalBalls += redBalls;
				redBalls = 0;
		}
		pthread_mutex_unlock(&m);
	}

	/* we are out of the loop but never had chance to update 
	 * the totalBalls count , so before leaving this thread
	 * we should update and leave forcibly by grabbing the 
	 * lock  */
	pthread_mutex_trylock(&m);
	totalBalls += redBalls;
	pthread_mutex_unlock(&m);
	
	pthread_exit(NULL);
}

void *blueballs(void *arg)
{
        int blueBalls = 0;
        long tid = (long)arg;
	int rc, i;
        for(i=0; i< 1000; i++)
        {
                rc = pthread_mutex_trylock(&m);
                if(rc = EBUSY)
                {
				/* keep a local count of balls 
				 * in this thread  */
                                blueBalls += 5;
                }
                else
                {
                                totalBalls += blueBalls;
                                blueBalls = 0;
                }
                pthread_mutex_unlock(&m);
        }

        /* we are out of the loop but never had chance to update 
         * the totalBalls count , so before leaving this thread
         * we should update and leave forcibly by grabbing the 
         * lock  */
        pthread_mutex_trylock(&m);
        totalBalls += blueBalls;
        pthread_mutex_unlock(&m);

        pthread_exit(NULL);
}
main()
{
	pthread_t 	thd1, thd2;
	int rc;
	long tid = 0;
	char buffer[]="hi, There ..!";

	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

	tid = 1;
	rc = pthread_create(&thd1, NULL, (void *)redballs, (void *)tid);
	if(rc)
	{
		printf("%s", "pthread create fails");
	}

	tid = 2;
	rc = pthread_create(&thd2, NULL, (void *)blueballs, (void *)tid);
	if(rc)
	{
		printf("%s", "pthread create fails");
	}

	pthread_join(thd1, NULL);
	pthread_join(thd2, NULL);

	printf("Total balls count is %d\n", totalBalls);

	pthread_exit(NULL);
}
