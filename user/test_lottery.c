#include "kernel/types.h"
#include "user/user.h"

int main(int argc, char *argv[])
{
  if(fork() == 0)
  {
    settickets(getpid(), 10);
    write(1,"10\n",3);
  }

  if(fork() == 0)
  {
    settickets(getpid(), 30);
    write(1,"30\n",3);
  }
  wait(0);
  wait(0);
  exit(0);
  return 0;
}