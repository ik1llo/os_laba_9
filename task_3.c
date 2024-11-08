#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <stdlib.h>

int parent_count = 0;
int child_count = 0;
pid_t child_pid;

void parent_signal_handler (int sig) {
    if (parent_count < 5) {
        printf("[parent process]: %d\n", parent_count + 1);

        parent_count++;
        kill(child_pid, SIGUSR1);
    }
}

void child_signal_handler (int sig) {
    if (child_count < 5) {
        printf("[child process]: %d\n", child_count + 1);

        child_count++;
        kill(getppid(), SIGUSR1);
    } 
    else
        exit(0);
}

int main() {
    if (signal(SIGUSR1, parent_signal_handler) == SIG_ERR)
        exit(1);

    child_pid = fork();

    if (child_pid < 0)
        exit(1);

    if (child_pid > 0) {
        kill(child_pid, SIGUSR1);

        while (parent_count < 5)
            pause();

        exit(0);
    } 
    else {
        if (signal(SIGUSR1, child_signal_handler) == SIG_ERR)
            exit(1);

        while (1)
            pause();
    }

    return 0;
}
