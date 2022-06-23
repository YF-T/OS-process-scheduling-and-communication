#include "kernel/types.h"
#include "user/user.h"

int main(int argc, char *argv[])
{
  if(fork() == 0)
  {
    write(1,"1\n",2);
    exit(0);
  }
  if(fork() == 0)
  {
    write(1,"2\n",2);
    exit(0);
  }
  if(fork() == 0)
  {
    write(1,"3\n",2);
    exit(0);
  }
  int a=0;
  for(int i = 0; i < 100000000; i++)
    a += 1;
  wait(0);
  wait(0);
  wait(0);
  exit(0);
}