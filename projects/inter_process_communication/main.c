#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

#define MAX_MESSAGE_SIZE 100

int main() {
    int parent_to_child_pipe[2];
    int child_to_parent_pipe[2];
    pid_t pid;
    char message[MAX_MESSAGE_SIZE];

    // Create pipes
    if (pipe(parent_to_child_pipe) == -1 || pipe(child_to_parent_pipe) == -1) {
        perror("Pipe creation failed\n");
        return 1;
    }

    pid = fork();
    if (pid < 0) {
        perror("Oh for. Fork failed.\n");
        return 1;
    } else if (pid == 0) {  // Child process
        // Close unecessary pipe ends
        close(parent_to_child_pipe[1]);
        close(child_to_parent_pipe[0]);

        // Read message from parent
        ssize_t bytes_read =
            read(parent_to_child_pipe[0], message, MAX_MESSAGE_SIZE);
        if (bytes_read > 0) {
            printf("%s", message);

            char child_message[MAX_MESSAGE_SIZE];
            sprintf(child_message, "Daddy, my name is %d\n", getpid());
            write(child_to_parent_pipe[1], child_message,
                  strlen(child_message) + 1);
        }

        // Close used pipe ends
        close(parent_to_child_pipe[0]);
        close(child_to_parent_pipe[1]);

        return 0;
    } else {  // Parent process
        close(parent_to_child_pipe[0]);
        close(child_to_parent_pipe[1]);

        char parent_message[MAX_MESSAGE_SIZE];
        sprintf(parent_message, "I am your daddy! and my name is %d\n",
                getpid());
        write(parent_to_child_pipe[1], parent_message,
              strlen(parent_message) + 1);

        ssize_t bytes_read =
            read(child_to_parent_pipe[0], message, MAX_MESSAGE_SIZE);
        if (bytes_read > 0) {
            printf("%s", message);
        }

        close(parent_to_child_pipe[1]);
        close(child_to_parent_pipe[0]);

        int status;
        waitpid(pid, &status, 0);
    }

    return 0;
}
