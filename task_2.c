#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

char* message;

void alarm_handler (int sig) { printf("%s\n", message); }

int main (int argc, char* argv[]) {
    if (argc != 3)
        return 1;

    int time_in_seconds = atoi(argv[1]);
    if (time_in_seconds <= 0)
        return 1;

    message = argv[2];

    signal(SIGALRM, alarm_handler);
    alarm(time_in_seconds);
    pause();

    return 0;
}
