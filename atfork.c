#include <pthread.h>
#include<stdio.h>
#include<unistd.h>

pthread_t	thd[2];
int		pipefd[2];
static		pthread_once_t	once = PTHREAD_ONCE_INIT;

void init()
{
	pipe(pipefd);
	printf("pipe created .. in init call now\n");
}

void *func(void *unused)
{
	pthread_t	self;
	char		buf[32];
	int i, n;

	/* once shall ensure that only one unnamed pipe is created for
	 * both threads created for read and write respectively.. */

	(void)pthread_once(&once, init);
	
	self= pthread_self();

	/* even if thd[0] is scheduled first , read will wait for 
 	 * data in the pipe and the time slice will be given to 
	 * writer, so thd[1] shall continue to write for reader
	 * in thd[0] utilizes it  */
	if(pthread_equal(self, thd[0]))
	{
		for(i=0; i<10; i++)
			buf[i]=0;

		n = read(pipefd[0], buf, 32);
		buf[n] = 0;
		printf("read:count = %d, buf=%s\n", n, buf);
	}
	if(pthread_equal(self, thd[1]))
	{
		for(i=0; i<10; i++)
			buf[i]='0'+i;
		buf[i++] = 0;
		write(pipefd[1], buf, i);
	}
}

main()
{
	pthread_create(&thd[0], NULL, func, (void *)0);
	pthread_create(&thd[1], NULL, func, (void *)1);
	pthread_exit(NULL);
}
