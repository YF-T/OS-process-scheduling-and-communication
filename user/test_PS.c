#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main(int args,char *argv[])
{
    showpid();
    exit(0);
}