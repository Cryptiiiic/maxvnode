#include <CoreFoundation/CoreFoundation.h>
#include <spawn.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

static int run_sysctl(char *args[])
{
	char *path = "/usr/sbin/sysctl";
	pid_t pid;
	int stat;
	if(!posix_spawn(&pid, path, NULL, NULL, args, NULL))
		return -1;
	waitpid(pid, &stat, 0);
	return stat;
}

int main(int argc, char **argv, char **envp)
{
	if (getuid() != 0 && getgid() != 0)
	{
		printf("Failed root, quitting.");
		exit(1);
	}

	char *args[] = { "-w", "kern.maxvnodes=6000" };
	if(!run_sysctl(args))
	{
		printf("Changing maxvnodes failed, quitting.");
		exit(1);
	}

    return 0;
}
