/* this example demonstrates thread specific data usage. 
 * a key is used to attach allocated data to a thread.
 * Thread specific data is global only to a particular thread.
 * however its retrieval is only via global key. The key will
 * point to an address in memory where the data for the current
 * thread is actually located. Once a function has retrieved the 
 * address of the data, it can manipulate it at the will using
 * that address.

 * key is mapped to thread#id ; thread specific data is mapped to
 * key.

 * wrtten by Vidya, R
 **/

#include <pthread.h>
#include <stdio.h>
#include <malloc.h>

pthread_key_t	count_key;
void getdata();

void *thread_starter(void *TID)
{
	int *ThreadID;
	ThreadID = (int *)TID;

	int *ptr;
	ptr= (int *)malloc(4);
	if(!ptr)
		printf("ENOMEM");

	*ptr = 97;
	pthread_setspecific(count_key, ptr);

	(*ptr)++;
	getdata();
	(*ptr)++;
	printf("Thread# %d count should be 100 now, The pointer says :%d\n", *ThreadID, *ptr);
}

void getdata()
{
	void *local_p;
	local_p = pthread_getspecific(count_key);
}

void count_key_destructor(void *data)
{
	free(data);
}

main()
{
	pthread_t	tid1;
	int tid;
	
	pthread_key_create(&count_key, count_key_destructor);
	tid = 1;
	pthread_create(&tid1, NULL, thread_starter, &tid);
	
	while(pthread_key_delete(count_key) != 0)
		sleep(1);
	pthread_exit(NULL);
}
