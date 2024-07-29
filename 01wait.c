
#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define ERR_EXIT(m)         \
    do                      \
    {                       \
        perror(m);          \
        exit(EXIT_FAILURE); \
    } while (0)

int main(int argc, char const *argv[])
{

    pid_t pid = fork();

    if (pid == -1)
        ERR_EXIT("fork");
    if (pid == 0)
    {
        sleep(3);
        printf("this is child\n");
        // exit(17);
        abort();
    }
    printf("this is parent\n");
    int status,ret;

    // ret = waitpid(-1,&status,0);
    ret = waitpid(pid,&status,0);


    printf("ret = %d pid = %d \n",ret,pid);
    if (WIFEXITED(status))
    {
        printf("normal exit");
    }else if (WIFSIGNALED(status))
    {
        printf("child exit abnormal signal number=%d\n",WTERMSIG(status));
    }else if (WIFSTOPPED(status))
    {
        printf("child stopped signal number=%d\n",WSTOPSIG(status));
    }
    
    
    
    printf("status = %d\n",WEXITSTATUS(status));

    return 0;
}
