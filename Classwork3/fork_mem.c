#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

int svar = 0;

int main() {
    int lvar = 0;
    int* dvar = malloc(sizeof(int));
    *dvar = 0;
    pid_t pid;

    pid = fork();

    if (pid == 0) {
        svar  += 1;
        lvar  += 2;
        *dvar += 3;
        return 0;
    } else if (pid > 0) {
        wait(NULL);
        printf ("PARENT: svar=%i, lvar=%i, dvar=%i\n", svar, lvar, *dvar);
        return 0;
    }
    free(dvar);
}
