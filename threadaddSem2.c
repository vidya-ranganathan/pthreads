#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>

#define NITER 1000000

int count = 0;
sem_t	mutex;

void * ThreadAdd(void * a)
{
    int i, tmp, num;

    num = *(int *)a;
    for(i = 0; i < NITER; i++)
    {
       sem_wait(&mutex);
		/* enter critical section */
		tmp = count;      /* copy the global count locally */
		tmp = tmp+1;      /* increment the local copy */
		count = tmp;      /* store the local value into the global count */ 
		/* exit critical section */
       printf("thread#%d , count #%d\n", num, count);
       sem_post(&mutex);

    }
}

int main(int argc, char * argv[])
{
    pthread_t tid1, tid2;
    sem_init(&mutex, 0, 1);

    int thnum[2];

    thnum[0] = 1;
    thnum[1] = 2;

    if(pthread_create(&tid1, NULL, ThreadAdd,(void *)&thnum[0] ))
    {
      printf("\n ERROR creating thread 1");
      exit(1);
    }

    if(pthread_create(&tid2, NULL, ThreadAdd, (void *)&thnum[1]))
    {
      printf("\n ERROR creating thread 2");
      exit(1);
    }

    if(pthread_join(tid1, NULL))	/* wait for the thread 1 to finish */
    {
      printf("\n ERROR joining thread");
      exit(1);
    }

    if(pthread_join(tid2, NULL))        /* wait for the thread 2 to finish */
    {
      printf("\n ERROR joining thread");
      exit(1);
    }

    if (count < 2 * NITER) 
        printf("\n BOOM! count is [%d], should be %d\n", count, 2*NITER);
    else
        printf("\n OK! count is [%d]\n", count);
  
    pthread_exit(NULL);
    sem_destroy(&mutex);
}
