#include "kernel/types.h"
#include "user/user.h"

int main(int argc, char *argv[])
{
	int a = 0;
	if (fork() == 0)
	{
		for (int i = 0; i < 10; i++)
			write(1, "a", 1);
		for (int i = 0; i < 10000000; i++)
		a += 1;
		exit(0);
	}
	if (fork() == 0)
	{
		for (int i = 0; i < 10; i++)
			write(1, "b", 1);
		for (int i = 0; i < 10000000; i++)
		a += 1;
		exit(0);
	}
	if (fork() == 0)
	{
		for (int i = 0; i < 10; i++)
			write(1, "c", 1);
		for (int i = 0; i < 10000000; i++)
		a += 1;
		exit(0);
	}
	for (int i = 0; i < 1000000000; i++)
		a += 1;
	printf("\n");
	wait(0);
	wait(0);
	wait(0);
	exit(0);
}