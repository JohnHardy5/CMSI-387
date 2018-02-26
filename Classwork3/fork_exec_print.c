#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    pid_t pid;

    /* fork a child process */
    pid = fork();

    if (pid == 0) {
        printf("Child %d\n", pid);
        execlp("/bin/ls","ls",NULL);
        printf("WILL I PRINT?!");
    }
    else {
        printf("Parent %d\n",pid);
        wait(NULL);
        printf("Child Complete\n");
    }

    return 0;
}
