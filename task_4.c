
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

#define SIGNALS_AMOUNT 5

void signal_handler(int sig, siginfo_t *info, void *context) {
    printf(
        "child process received signal: %d (%s), additional data: %d\n", 
        sig, 
        strsignal(sig), 
        info->si_value.sival_int
    );
}

int main() {
    pid_t pid;
    struct sigaction sa;
    union sigval value;

    pid = fork();

    if (pid < 0)
        return 1;

    if (pid == 0) {
        sa.sa_flags = SA_SIGINFO;
        sa.sa_sigaction = signal_handler;
        sigemptyset(&sa.sa_mask);
        if (sigaction(SIGRTMIN, &sa, NULL) == -1)
            exit(1);

        printf("child process started | PID: %d\n", getpid());

        while (1)
            pause();
    } 
    else { 
        printf("parent process started | PID: %d\n", getpid());

        for (int k = 1; k <= SIGNALS_AMOUNT; k++) {
            value.sival_int = k;
            if (sigqueue(pid, SIGRTMIN, value) == -1)
                return 1;

            printf("parent process sent signal: %d (message count: %d)\n", SIGRTMIN, k);
            sleep(1);
        }

        printf("parent process sends SIGTERM signal to the child process\n");
        kill(pid, SIGTERM);

        wait(NULL);
    }

    return 0;
}
