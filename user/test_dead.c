#include "kernel/types.h"
#include "user/user.h"

int main(int argc, char *argv[])
{
	if (fork() == 0)
  {
    changepri(getpid(), 10);
    while(1);
    exit(0);
  }
  if (fork() == 0)
  {
    changepri(getpid(), 10);
    while(1);
    exit(0);
  }
  if (fork() == 0)
	{
		//settickets(getpid(), 1);
    changepri(getpid(), 13);
    int j = 0;
    for(int i=0; j< 200000000;i++){
      if(i%5 == 0){
        j++;
      }
    }
		exit(0);
	}
	if (fork() == 0)
	{
		//settickets(getpid(), 1);
    changepri(getpid(), 14);
    int j = 0;
    for(int i=0; j< 200000000;i++){
      if(i%5 == 0){
        j++;
      }
    }
		exit(0);
	}
  if (fork() == 0)
	{
		//settickets(getpid(), 1);
    changepri(getpid(), 15);
    int j = 0;
    for(int i=0; j< 200000000;i++){
      if(i%5 == 0){
        j++;
      }
    }
		exit(0);
	}
  if (fork() == 0)
	{
    //settickets(getpid(), 1);
    changepri(getpid(), 16);
    int j = 0;
    for(int i=0; j< 200000000;i++){
      if(i%5 == 0){
        j++;
      }
    }
		exit(0);
	}
	
	
	printf("\n");
	wait(0);
	wait(0);
  wait(0);
  wait(0);
	wait(0);
  wait(0);
	exit(0);
}