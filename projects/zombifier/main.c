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
    pid_t child_pids[1024];
    int opt, num_zombies, children_created;
    num_zombies = children_created = 0;

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

    if (num_zombies <= 0 || num_zombies > 1024) {
        fprintf(stderr,
                "Please supply a positive integer within [1, 1024] for "
                "NumberOfZombies\n");
        return 1;
    }

    for (int i = 0; i < num_zombies; i++) {
        pid_t pid = fork();

        if (pid == -1) {
            fprintf(stderr, "Failed to fork.\n");
            exit(EXIT_FAILURE);
        } else if (pid == 0) {
            // Child process - immediately become a zombie
            exit(0);
        } else {
            child_pids[children_created++] = pid;
        }
    }

    // Wait for SIGCONT
    signal(SIGCONT, handle_sigcont);
    pause();

    for (int i = 0; i < children_created; i++) {
        int status;
        pid_t result = waitpid(child_pids[i], &status, 0);
        if (result == -1) {
            fprintf(stderr, "waitpid failed.\n");
        }
    }

    return 0;
}
