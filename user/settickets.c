#include "kernel/types.h"
#include "user/user.h"

int main(int argc, char *argv[])
{
    if (argc < 3)
    {
        printf(0, "error(params)\n");
        printf(0, "the buffer is not enough\n");
        exit(0);
    }
    else
    {
        int pidnum = atoi(argv[1]);
        int tickets = atoi(argv[2]);

        if (tickets < 0 || tickets > 30)
        {
            printf("tickets num error\n");
            exit(0);
        }
        else
        {
            settickets(pidnum, tickets);
        }
    }
    exit(0);
}
