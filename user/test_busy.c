#include "kernel/types.h"
#include "user/user.h"

int main(int argc, char *argv[])
{
	if (fork() == 0)
	{
		//settickets(getpid(), 1);
    changepri(getpid(), 12);
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
    changepri(getpid(), 12);
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
    changepri(getpid(), 12);
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
    changepri(getpid(), 12);
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
    changepri(getpid(), 12);
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
		//settickets(getpid(), 2);
    changepri(getpid(), 25);
    int j = 0;
    for(int i=0; j< 100000000;i++){
      if(i%5 == 0){
        j++;
      }
    }
		exit(0);
	}
	if (fork() == 0)
	{
		//settickets(getpid(), 2);
    changepri(getpid(), 25);
    int j = 0;
    for(int i=0; j< 100000000;i++){
      if(i%5 == 0){
        j++;
      }
    }
		exit(0);
	}
  if (fork() == 0)
	{
		//settickets(getpid(), 3);
    changepri(getpid(), 50);
    int j = 0;
    for(int i=0; j< 50000000;i++){
      if(i%5 == 0){
        j++;
      }
    }
		exit(0);
	}
  if (fork() == 0)
	{
		//settickets(getpid(), 3);
    changepri(getpid(), 50);
    int j = 0;
    for(int i=0; j< 50000000;i++){
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
  wait(0);
  wait(0);
	wait(0);
	exit(0);
}