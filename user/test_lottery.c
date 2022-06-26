#include "kernel/types.h"
#include "user/user.h"

int main(int argc, char *argv[])
{
  if(fork() == 0)
  {
    settickets(getpid(), 10);
    for(int i=0;i<20;i++)
      write(1,"A",1);
    exit(0);
  }

  if(fork() == 0)
  {
    settickets(getpid(), 10);
    for(int i=0;i<20;i++)
      write(1,"B",1);
    exit(0);
  }
  wait(0);
  wait(0);
  exit(0);
  //return 0;
}