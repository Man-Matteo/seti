#include <stdio.h>


char *myread () {
    int N = sizeof(stdin);
    char a[N];
    fgets(a, N + 1, stdin);
    return a;
}

int mystdinsize () {
  return sizeof(stdin);
}

int main() {
    for (;;) {
      char *input = myread();
      printf("%s", input);
    }
}
