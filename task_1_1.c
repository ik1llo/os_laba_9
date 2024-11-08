#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

void handle_SIGINT (int sig) { printf("captured signal SIGINT\n"); }

void handle_SIGTERM (int sig) { printf("captured signal SIGTERM\n"); }

void handle_SIGUSR1 (int sig) {
    printf("process is terminating due to signal SIGUSR1\n");
    exit(0);
}

void handle_SIGPROF (int sig) {
    signal(SIGPROF, SIG_DFL);
    printf("restored default behavior for signal SIGPROF\n");
}

int main() {
    printf("process ID (PID): %d\n", getpid());

    signal(SIGINT, handle_SIGINT);
    signal(SIGTERM, handle_SIGTERM);
    signal(SIGUSR1, handle_SIGUSR1);
    signal(SIGPROF, handle_SIGPROF);
    signal(SIGHUP, SIG_IGN);

    while(1)
        pause();

    return 0;
}
