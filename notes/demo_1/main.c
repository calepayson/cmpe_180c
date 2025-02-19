#include <stdio.h>  // Needed for printf() stdc library
#include <stdlib.h> // Needed for atoi() stdc library

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

  return 0;
}
