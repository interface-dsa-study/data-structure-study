#include <stdio.h>
#include <stdlib.h>


int main(void) {
  int a, b, count;

  scanf("%d %d %d", &a, &b, &count);
  char *sentence = malloc(sizeof(*sentence) * (count + 1));
  if (sentence == NULL) {
    exit(EXIT_FAILURE);
  }

  scanf(" %s", sentence);

  for (int index = 0; index < count; index++) {
    if (a == b) {
      break;
    }

    int middle = a + (b - a) / 2;
    if (sentence[index] == 'Y') {
      a = middle + 1;
    } else {
      b = middle;
    }
  }

  printf("%d\n", a);

  free(sentence);
  return EXIT_SUCCESS;
}
