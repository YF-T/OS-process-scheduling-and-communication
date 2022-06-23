#include "kernel/types.h"
#include "user/user.h"

int main(int argc, char *argv[])
{
  char a[]="abcd";
  char b[]="1234";
  char c[]="9876";
  char d[]="1234567890123456789012345678901234567890123456789012345678901234567890";
  if(fork()==0){
    //write
    //sleep(1000);
    mqpush(1,a,sizeof(a));
    mqpush(2,d,sizeof(d));
    sleep(3);
    mqpush(1,c,sizeof(c));
    mqpush(1,b,sizeof(b));
    exit(0);
  }
  if(fork()==0){
    //read 1
    sleep(1);
    char buff[100];
    while(mqtypepop(1,buff,100)==-1);
    printf("1: %s\n",buff);
    while(mqtypepop(1,buff,100)==-1);
    printf("1: %s\n",buff);
    exit(0);
  }
  if(fork()==0){
    //read 2
    char buff[100];
    while(mqtypepop(2,buff,100)==-1);
    printf("2: %s\n",buff);
    exit(0);
  }
  wait(0);
  wait(0);
  wait(0);
	exit(0);
}