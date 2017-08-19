#include <CoreFoundation/CoreFoundation.h>
#include <spawn.h>
#include <sys/stat.h>

static int run_sysctl(char *path, char *cmd)
{
    char *args[] = {"/usr/sbin/sysctl", cmd, path, NULL};
    pid_t pid;
    int stat;
    posix_spawn(&pid, args[0], NULL, NULL, args, NULL);
    waitpid(pid, &stat, 0);
    return stat;
}

int main(int argc, char **argv, char **envp)
{
    if (geteuid() != 0)
    {
        printf("Failed Root, Quitting");
        return 1;
    }
    
    run_sysctl("kern.maxvnodes=8000", "-w");
    
    return 0;
}
