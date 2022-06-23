#include "kernel/types.h"
#include "user/user.h"
int main(int argc, char *argv[])
{
  if(fork() == 0){
    int a = 0;
    for(int j = 0; j < 10; j++){
      mqpush(1,"1",2);
      for (int i = 0; i < 10000000; i++) {
        a += 1;
      }
        
    }
    exit(0);
  }
  if(fork() == 0){
    int a = 0;
    for(int j = 0; j < 10; j++){
      mqpush(1,"2",2);
      for (int i = 0; i < 10000000; i++)
        a += 1;
    }
    exit(0);
  }
  if(fork() == 0){
    int a = 0;
    for(int j = 0; j < 10; j++){
      mqpush(1,"3",2)
      for (int i = 0; i < 10000000; i++)
        a += 1;
    }
    exit(0);
  }
  wait(0);
  wait(0);
  wait(0);
  char buff[10] = "";
  int *b = 0;
  while(mqpop(b,buff,10)!=-1){
    printf("%s",buff);
  }
  exit(0);
}