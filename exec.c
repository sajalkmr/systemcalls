#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

void main(void)
{
    pid_t pid = 0;
    int status;
    pid = fork();
    if (pid == 0)
    {
        printf("I am the child.");
        execl("/bin/ls", "ls", "-l", "/home/ubuntu/", (char *)0);
        perror("In exex():");
    }

    if (pid > 0)
    {
        printf("I am the parent, and the child is %d.\n", pid);
        pid = wait(&status);
        printf("End of process %d:", pid);
    }
    if (WIFEXITED(status))
    {
        printf("The process ended with exit(%d).\n", WEXITSTATUS(status));
    }
    if (WIFSIGNALED(status))
    {
        printf("The process ended with kill -%d.\n", WTERMSIG(status));
    }

    if (pid < 0)
    {
        perror("In fork():");
    }
    exit(0);
}

/* output
 * I am the parent, and the child is 1945.
ls: cannot access '/home/ubuntu/': No such file or directory
End of process 1945:The process ended with exit(2). */
