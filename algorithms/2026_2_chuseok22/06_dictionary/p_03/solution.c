#include <stdio.h>
#include <stdlib.h>

int main(void) {
  int a, b, count;
  char command;
  scanf("%d %d %d", &a, &b, &count);

  for (int i = 0; i < count; i++) {
    scanf(" %c", &command);
    // 중간값 계산
    int middle = (a + b) / 2;

    // N 입력
    if (command == 'N') {
      // b 를 middle 로 바꿈
      b = middle;
    } else if (command == 'Y') {
      // a 를 middle + 1 로 바꿈
      a = middle + 1;
    } else {
      exit(EXIT_FAILURE);
    }
  }
  printf("%d", a);
  return EXIT_SUCCESS;
}
