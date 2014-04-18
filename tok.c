/* this is a non reentrant code , 
 * a reentrant code shall not have static variables.
 * for multithreading , we have strtok_r
 */

#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <malloc.h>

void func()
{
	char* util = 0;
char* sptr;
char buffer[] = "This is a test\n";
char tokens[] = "s\n";

/* First call has the first argument of the string to examine */
util = (char *)strtok_r( buffer, tokens, &sptr );
do 
{
   printf( "Token = '%s'\n", util );
}
while( util = strtok_r( NULL, tokens, &sptr ));
}


main()
{
	func();
}
