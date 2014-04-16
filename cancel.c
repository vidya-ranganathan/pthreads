#include <stdio.h>
#include <pthread.h>

pthread_mutex_t	m;

void	cleanup_m(void *m)
{
	printf("in cleanup handler \n");
	pthread_mutex_unlock((pthread_mutex_t *)m);
}

void *thread_starter(void *unused)
{
	printf("in thread_starter ..\n");
	pthread_mutex_lock(&m);
	/* add a cleanup function for cleanup on cancellation */
	pthread_cleanup_push(cleanup_m, (void *)&m);	
	sleep(1);
	/* establishes a cancellation point  */
	pthread_testcancel();		
	printf("i have reached here, i am not cancelled\n");
	/* removes the instructions from cleanup stack and optionally executes them.
	 * the param to cleanup_pop() indicates whether execution of stack should take place.
	 **/
	pthread_cleanup_pop(0);
	pthread_mutex_unlock(&m);
	pthread_exit(NULL);
}

main()
{
	pthread_t	thd1;
	
	pthread_mutex_init(&m, NULL);
	pthread_create(&thd1, NULL, thread_starter, NULL);

	/* enables thread to cancel as soon as cancellation point is reached.
	 * a cancellation point is reached when either pthread_testcancel, is issued or a
	 * cancellation point call is issued with pthread_join or pthread_cond_wait or
	 * pthread_cond_timedwait  */
	pthread_cancel(thd1);

	pthread_mutex_destroy(&m);
	pthread_exit(NULL);
}
