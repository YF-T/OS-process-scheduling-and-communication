#include "kernel/types.h"
#include "user/user.h"
#include "kernel/stat.h"

int main(int argc, char* argv[])
{
    if (fork()== 0)//Child
   	{
   		printf("Child %d is created!\n", getpid());
   		for (int a = 0; a < 100000000000; a++)
   		{
        	for (int b = 0; b < 100000000; b++)
        	{
                   a*=b;
      		}
   		}
      	exit(0);
  	} 
    wait(0);
    exit(0);
}

