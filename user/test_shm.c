#include "kernel/types.h"
#include "user/user.h"

int main(int argc, char *argv[])
{
  int semid = semalloc(0);
  int shmid = shmalloc();
  if(fork() == 0){
    shmwrite(shmid, "abcdefg", 1, 8);
    sempost(semid);
		exit(0);
  }
  if(fork() == 0){
    char* buff[10];
    sempend(semid);
    shmread(shmid, buff, 1, 8);
    write(1, buff, 8);
    exit(0);
  }
	wait(0);
	wait(0);
  write(1,"\n",1);
  semfree(semid);
  shmfree(shmid);
	exit(0);
}