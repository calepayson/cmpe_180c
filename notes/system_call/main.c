#include <stdio.h>  // Needed for printf() stdc library
#include <stdlib.h> // Needed for atoi() stdc library

#include <errno.h>    // Needed for errno
#include <string.h>   // Needed for strerror()
#include <sys/stat.h> // Needed for stat()

int factorial(int n) {
  int f = 1;
  for (int i = 1; i <= n; i++) {
    f = f * i;
  }
  return f;
}

int main(int argc, char *argv[]) {
  printf("argc = %d\n", argc);
  printf("argc[0] = %s\n", argv[0]);
  if (argc < 2) {
    fprintf(stderr, "Argument count should be 2 or larger\n");
    return 1;
  }
  int n = atoi(argv[1]);
  fprintf(stdout, "The factorial(%d) is %d\n", n, factorial(n));
  struct stat s;
  if (stat("ERROR.txt", &s) != 0) {
    fprintf(stderr, "stat() system call failed! errno=%d, %s\n", errno,
            strerror(errno));
    return 1;
  }

  return 0;
}
