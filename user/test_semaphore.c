#include "kernel/types.h"
#include "user/user.h"

int main(int argc, char *argv[])
{
  int semid = semalloc(1);
  if(fork() == 0){
    sempend(semid);
    for(int i=0;i<5;i++){
			write(1,"A",1);
			sleep(10);
		}
    sempost(semid);
    sleep(10);
    sempend(semid);
    for(int i=0;i<5;i++){
			write(1,"A",1);
			sleep(10);
		}
    sempost(semid);
		exit(0);
  }
  if(fork() == 0){
    sempend(semid);
    for(int i=0;i<5;i++){
			write(1,"B",1);
			sleep(10);
		}
    sempost(semid);
    sleep(10);
    sempend(semid);
    for(int i=0;i<5;i++){
			write(1,"B",1);
			sleep(10);
		}
    sempost(semid);
		exit(0);
  }
	wait(0);
	wait(0);
  write(1,"\n",1);
  semfree(semid);
	exit(0);
}