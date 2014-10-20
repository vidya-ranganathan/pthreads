#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int	glob = 0;

pthread_mutex_t	glob_mutex;


void *odd(void *unused)
{
	int i;
	int local = glob;
	
	for(i=0;i<100;i++)
	{
		if(local % 2 == 1){
			printf("%d....\n", glob);
			pthread_mutex_lock(&glob_mutex);
			glob++;
			pthread_mutex_unlock(&glob_mutex);
			sleep(1);
		}
	}

	pthread_exit(NULL);
}

void *even(void *unused)
{
        int i;
        int local = glob;

        for(i=0;i<100;i++)
        {
		if(local % 2 == 0){
			printf("%d....\n", glob);
                        pthread_mutex_lock(&glob_mutex);
                        glob++;
                        pthread_mutex_unlock(&glob_mutex);
                        sleep(1);
		}
        }

        pthread_exit(NULL);
}


main()
{
	pthread_t	tid1, tid2;
	int ret;
	int i;

	pthread_mutex_init(&glob_mutex, NULL);	/* initialize mutex  */

	ret = pthread_create(&tid1, NULL, even, NULL);	/* attr and rc are NULL  , create thread  */
	if(ret)
	{
		printf("pthread create failed , rc = %d\n", ret);
	}

	ret = pthread_create(&tid2, NULL, odd, NULL);	/* attr and rc are NULL  , create thread  */
	if(ret)
	{
		printf("pthread create failed , rc = %d\n", ret);
	}

	pthread_mutex_destroy(&glob_mutex);

	pthread_join(tid1, NULL);
	pthread_join(tid2, NULL);
	pthread_exit(NULL);
}
