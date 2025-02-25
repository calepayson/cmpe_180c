#include <signal.h>    // signal()
#include <stdio.h>     // fprintf(), printf(), stderr
#include <stdlib.h>    // exit()
#include <sys/wait.h>  // waitpid(), WEXITSTATUS(), WIFEXITED
#include <unistd.h>    // pid_t fork()

// Dummy signal handler. Satisfies the signal() function without doing anything
void handle_sigint(int sig) {
    (void)sig;  // Tell the compiler that we're purposefully not using sig
    return;
}

int main() {
    pid_t pid;

    /*
     * WARNING: Long description but it's worth it.
     *
     * fork() is a wild function. When called, fork duplicates the current
     * process creating parent and child processes. In the parent function,
     * fork() returns the PID of the newly created child process. In the child
     * process, fork() returns 0.
     *
     * Understanding this is key to understanding the following code.
     */
    pid = fork();

    if (pid < 0) {  // Failed to create child process
        fprintf(stderr, "Oh fork: Unable to fork ;)\n");
        return 1;
    } else if (pid == 0) {  // Child process
        signal(SIGINT, handle_sigint);
        printf("%d\n", getpid());  // Print the child's pid
        pause();                   // Pause until a signal is recieved
        exit(5);
    } else {  // Parent process
        int status;

        // Wait for child to exit and handle any errors
        if (wait(&status) == -1) {  //
            fprintf(stderr, "wait failed\n");
            return 1;
        }

        // Check if the child exited normally then print its pid and exit status
        // NOTE: A process can return a non-zero error code while exiting
        // normally
        if (WIFEXITED(status)) {
            int exit_status = WEXITSTATUS(status);
            printf("childpid=%d,exitstatus=%d\n", pid, exit_status);
        }
    }

    return 0;
}
