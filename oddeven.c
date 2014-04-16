#include <stdio.h>
#include <pthread.h>

static int global;
pthread_t thread1,thread2;

void *even_fun ()
{
        int local;
        local = global;

        if(local % 2 == 0)
        {
                printf("%d ",local);
                global = global++;
        }
        pthread_exit(&global);

}

void *odd_fun ()
{
        int local;
        local = global;

        if(local % 2 == 1)
        {
                printf("%d ",local);
                global = global++;
        }
        pthread_exit(&global);
}


main()
{
        int ret,res;
        void *retval;

	do{
        ret = pthread_create (&thread1,NULL,even_fun,NULL);
        pthread_join(thread1,&retval);

        res = pthread_create (&thread2,NULL,odd_fun,NULL);
        pthread_join(thread2,&retval);
        }while(global < 100);

}
