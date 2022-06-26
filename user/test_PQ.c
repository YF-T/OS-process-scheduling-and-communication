#include "kernel/types.h"
#include "user/user.h"

int main(int argc, char *argv[])
{
	int a = 0;
  if (fork() == 0)
  {
    changepri(getpid(), 100);
    while(1);
  }
  if (fork() == 0)
  {
    changepri(getpid(), 100);
    while(1);
  }
	if (fork() == 0)
	{
		changepri(getpid(), 1);
    for(int i=0; i< 50000000;i++){
      if(i%5 == 0){
        i++;
      }
    }
    for (int i = 0; i < 10; i++)
			write(1, "a", 1);
		for(int i=0; i< 50000000;i++){
      if(i%5 == 0){
        i++;
      }
    }
		exit(0);
	}
	if (fork() == 0)
	{
		changepri(getpid(), 2);
    for(int i=0; i< 50000000;i++){
      if(i%5 == 0){
        i++;
      }
    }
    for (int i = 0; i < 10; i++)
			write(1, "b", 1);
		for(int i=0; i< 50000000;i++){
      if(i%5 == 0){
        i++;
      }
    }
		exit(0);
	}
	if (fork() == 0)
	{
		changepri(getpid(), 3);
    for(int i=0; i< 50000000;i++){
      if(i%5 == 0){
        i++;
      }
    }
    for (int i = 0; i < 10; i++)
			write(1, "c", 1);
		for(int i=0; i< 50000000;i++){
      if(i%5 == 0){
        i++;
      }
    }
		exit(0);
	}
	for (int i = 0; i < 1000000000; i++)
		a += 1;
	
	wait(0);
	wait(0);
	wait(0);
  printf("\n");
	exit(0);
}