#include "kernel/types.h"
#include "user/user.h"

int main(int argc, char *argv[])
{
    char buf1[] = {'A'}; // one byte
	char buf2[] = {'B'};
	char buf3[] = {'C'};
    int n = sizeof(buf1);

    if(fork() == 0)
	{
		for(int i=0;i<10;i++)
		{
			write(1,buf1,n);
			sleep(2);
		}
		exit(0);
    }
    if(fork() == 0)
	{
		//sleep(1);
		for(int i=0;i<10;i++)
		{
			write(1,buf2,n);
			sleep(2);
		}
		exit(0);
    }
	if(fork() == 0)
	{
		//sleep(1);
		for(int i=0;i<10;i++)
		{
			write(1,buf3,n);
			sleep(2);
		}
		exit(0);
    }
	wait(0);
	wait(0);
	write(1,"\n",n);
	exit(0);
}