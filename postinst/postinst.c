#include <CoreFoundation/CoreFoundation.h>
#include <spawn.h>
#include <sys/stat.h>

static int run_vnode()
{
    char *args[] = {"/usr/bin/Maxvnode++", NULL};
    pid_t pid;
    int stat;
    posix_spawn(&pid, args[0], NULL, NULL, args, NULL);
    waitpid(pid, &stat, 0);
    return stat;
}

int main(int argc, char **argv, char **envp)
{
    if (geteuid() != 0) {
        printf("Failed Root, Quitting");
        return 1;
    }
    
    chown("/Library/LaunchDaemons/com.cryptic.maxvnode++.plist", 0, 0);
    chmod("/Library/LaunchDaemons/com.cryptic.maxvnode++.plist", 0644);
    
    run_vnode();
    
	return 0;
}
