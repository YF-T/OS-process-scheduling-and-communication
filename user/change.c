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
        int priority = atoi(argv[2]);

        if (priority < 0 || priority >31)
        {
            printf(0, "priority num error\n");
            exit(0);
        }
        else
        {
            changepri(pidnum, priority);
        }
    }
    exit(0);
}
