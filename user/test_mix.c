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
		changepri(getpid(),24);
    char buf[100];
    int fd;
    for(int i=0;i<1000;i++){
      fd=open("a", 0x002|0x200);
      read(fd,buf,sizeof(buf));
      write(fd,buf,sizeof(buf));
      close(fd);
    }
    exit(0);
	}
  if (fork() == 0)
	{
		changepri(getpid(),24);
    char buf[100];
    int fd;
    for(int i=0;i<1000;i++){
      fd=open("b", 0x002|0x200);
      read(fd,buf,sizeof(buf));
      write(fd,buf,sizeof(buf));
      close(fd);
    }
    exit(0);
	}
  if (fork() == 0)
	{
		changepri(getpid(),24);
    char buf[100];
    int fd;
    for(int i=0;i<1000;i++){
      fd=open("c", 0x002|0x200);
      read(fd,buf,sizeof(buf));
      write(fd,buf,sizeof(buf));
      close(fd);
    }
    exit(0);
	}
  if (fork() == 0)
	{
		changepri(getpid(),24);
    char buf[100];
    int fd;
    for(int i=0;i<1000;i++){
      fd=open("d", 0x002|0x200);
      read(fd,buf,sizeof(buf));
      write(fd,buf,sizeof(buf));
      close(fd);
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
	exit(0);
}