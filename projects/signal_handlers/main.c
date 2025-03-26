#include <signal.h>
#include <stdbool.h>
#include <stdio.h>

bool DEBUG = false;
bool TERMINATE = false;

void sigint_handler(int signum);
void sigusr1_handler(int signum);

int main() {
    signal(SIGINT, sigint_handler);
    signal(SIGUSR1, sigusr1_handler);

    long long counter = 0;
    long long max = 9223372036854775807;

    while (!TERMINATE) {
        counter++;
        if (DEBUG) {
            printf("Iteration: %lld\n", counter);
        }

        if (counter >= max) {
            fprintf(stderr, "Max counter value reached.\n");
            return 1;
        }
    }

    return 0;
}

void sigint_handler(int signum) {
    signum = signum;
    DEBUG = (DEBUG) ? false : true;
}

void sigusr1_handler(int signum) {
    signum = signum;
    TERMINATE = true;
}
