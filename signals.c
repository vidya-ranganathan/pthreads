#include <stdio.h>
#include <pthread.h>
#include <signal.h>
#include <string.h>
#include <unistd.h>

void *threadfunc(void *unused)
{
	int sig;
	sigset_t	set, oset;
	sigemptyset(&set);
	sigaddset(&set, SIGKILL);
	pthread_sigmask(SIG_BLOCK, &set, NULL);
	for(;;)
	{
		sigwait(&set, &sig);
		printf("sigwait returned signal = %d\n", sig);
	}
}

void *sigwaiter_thread(void *unused)
{
	int sig, ret;
	sigset_t	set, oset;
	sigemptyset(&set);
	sigaddset(&set, SIGQUIT);
	pthread_sigmask(SIG_BLOCK, &set, NULL);

	for(;;)
	{
		sigwait(&set, &sig);
		printf("sigwait returned signal = %d\n", sig);
	}
}


main()
{
	pthread_t	waiterthd, thd;
	int	status;
	sigset_t	set, oset;
	pthread_attr_t		attr;

	/* block the signals  */
	sigemptyset(&set);
	sigaddset(&set, SIGQUIT);
	pthread_sigmask(SIG_BLOCK, &set, NULL);

	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

	pthread_create(&waiterthd, &attr, sigwaiter_thread, NULL);
	pthread_create(&thd, &attr, threadfunc, NULL);

	sleep(2);
	pthread_join(thd, (void **)&status);
	pthread_join(thd, (void **)&status);
}
