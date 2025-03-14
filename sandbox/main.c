#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    int pid = fork();
    if (pid != 0) {
        for (int i = 0; i < 2; i++) {
            pid = fork();
            printf("pid: %d\n", pid);
            if (!pid) break;
        }
    }
}
