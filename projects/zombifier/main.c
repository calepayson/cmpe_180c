/*
 * Write a “C” program that creates a number of zombies (1 through n) processes
 * as specified in the command line arguments to the program: zombiefier –n 10
 * creates 10 zombies. Make sure the program cleans up the zombies upon
 * completion. Zombies must remain in the system until a signal (SIGCONT) is
 * sent to zombifier. BEWARE of solutions posted on the web that may not fulfill
 * these requirements, if you copy such version you most likely will get zero
 * points. Your program must be 100% reliable and create the zombies requested
 * on every run, if it does not, you will receive no points. Programs that are
 * copies of another will all get zero gra
 */
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

void handle_sigcont(int sig) {
    (void)sig;
    return;
}

int main(int argc, char *argv[]) {
    pid_t pid, parent_pid;
    int opt, num_zombies;
    num_zombies = 0;

    while ((opt = getopt(argc, argv, "n:")) != -1) {
        switch (opt) {
            case 'n':
                num_zombies = atoi(optarg);
                break;
            default:
                fprintf(stderr, "Usage: %s [-n NumberOfZombies]\n", argv[0]);
                return 1;
        }
    }

    if (num_zombies <= 0) {
        fprintf(stderr,
                "Please supply a positive integer for NumberOfZombies\n");
        return 1;
    }

    // TODO: Remove
    printf("Zombies: %i\n", num_zombies);

    parent_pid = getpid();
    for (int i = 0; i < num_zombies; i++) {
        if (getpid() == parent_pid) {
            pid = fork();
        }
    }

    switch (pid) {
        case -1:
            fprintf(stderr, "Error during fork.\n");
            exit(EXIT_FAILURE);
        case 0:
            return 0;
        default: {
            int status;

            signal(SIGCONT, handle_sigcont);
            pause();
            if (wait(&status) == -1) {
                fprintf(stderr, "Wait failed.\n");
                return 1;
            }
        }
    }

    return 0;
}
