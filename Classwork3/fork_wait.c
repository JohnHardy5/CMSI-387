#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    pid_t pid;

    pid = fork();

    if (pid == 0) {
        printf("I'm just a kid so I see pid = 0: %d\n", pid);
        // [!] Arrested development
        while(1) {}

    } else {
        printf("I'm Papa Process; my kid has pid: %d\n", pid);
        int status;
        wait(&status);
        printf("All done! Result was: %i\n", status);
    }

    return 0;
}
