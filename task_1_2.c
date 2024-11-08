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
    struct sigaction sa;
    sa.sa_handler = SIG_DFL;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    sigaction(SIGPROF, &sa, NULL);
    printf("restored default behavior for signal SIGPROF\n");
}

int main() {
    printf("process ID (PID): %d\n", getpid());

    struct sigaction sa_SIGINT, sa_SIGTERM, sa_SIGUSR1, sa_SIGPROF, sa_SIGHUP;

    sa_SIGINT.sa_handler = handle_SIGINT;
    sigemptyset(&sa_SIGINT.sa_mask);
    sa_SIGINT.sa_flags = 0;
    sigaction(SIGINT, &sa_SIGINT, NULL);

    sa_SIGTERM.sa_handler = handle_SIGTERM;
    sigemptyset(&sa_SIGTERM.sa_mask);
    sa_SIGTERM.sa_flags = 0;
    sigaction(SIGTERM, &sa_SIGTERM, NULL);

    sa_SIGUSR1.sa_handler = handle_SIGUSR1;
    sigemptyset(&sa_SIGUSR1.sa_mask);
    sa_SIGUSR1.sa_flags = 0;
    sigaction(SIGUSR1, &sa_SIGUSR1, NULL);

    sa_SIGPROF.sa_handler = handle_SIGPROF;
    sigemptyset(&sa_SIGPROF.sa_mask);
    sa_SIGPROF.sa_flags = 0;
    sigaction(SIGPROF, &sa_SIGPROF, NULL);

    sa_SIGHUP.sa_handler = SIG_IGN;
    sigemptyset(&sa_SIGHUP.sa_mask);
    sa_SIGHUP.sa_flags = 0;
    sigaction(SIGHUP, &sa_SIGHUP, NULL);

    while(1)
        pause();

    return 0;
}
