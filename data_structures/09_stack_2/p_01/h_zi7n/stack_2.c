#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *string; int top;
}Stack;

void initStack(Stack *stack) {
    stack->string = (char*)malloc(sizeof(char) * 101);
    stack->top = -1;
}

void push(Stack* stack, char susic) {// 수식 단어가 기억이 안남.
    if (stack->top == 100) return;
    stack->string[++(stack->top)] = susic;
}

char pop(Stack *stack) {
    if (stack->top == -1) return ' ';
    return stack->string[(stack->top)--];
}

int is_Empty(Stack *stack) {
    return stack->top == -1;
}

int main(void) {
    int N; scanf("%d", &N);
    Stack* stack = (Stack*)malloc(sizeof(Stack) * N);
    char sentence[101];
    for (int i = 0; i < N; i++) {
        scanf("%s", sentence);
        initStack(stack);
        for (int j = 0; j < strlen(sentence);j++) {
            if (sentence[j] >= 'A' && sentence[j] <= 'Z') {
                printf("%c", sentence[j]);
            }
            else if (sentence[j] == '(') {
                push(stack + i, sentence[j]);
            }
            else if (sentence[j] == ')') {
                while (!is_Empty(stack + i)) {
                    if (pop(stack + i) == '&') {
                        printf("&&");
                    }
                    else if (pop(stack + i) == '|') {
                        printf("||");
                    }
                    else printf("%c", sentence[j]);
                }
                pop(stack + i);
            }
            else {
                char plusorminus = ' ';
                if (sentence[j] == '+' || sentence[j] == '-') {
                    if (sentence[j - 1] == '(' || j == 0) {
                        if (sentence[j] == '+') plusorminus = 'p';
                        else plusorminus = 'm';
                    }
                }
                else if (sentence[j] == '&' || sentence[j] == '|') {
                    j++;
                }
                while ((stack + i)->top != -1) {
                    // 여기 부분을 모르겠음.
                    if ((stack+i)->string[j] == '!') {

                    }
                    if (pop(stack + i) == '&') printf("&&");
                    else if (pop(stack + i) == '|') printf("||");
                    else if (pop(stack + i) == 'p') printf("+");
                    else if (pop(stack + i) == 'm') printf("-");
                    else printf("%c", pop(stack + i));
                }
                push(stack + i, sentence[j]);
            }
        }
        while ((stack  + i)->top != -1) {
            if (pop(stack + i) == '&') printf("&&");
            else if (pop(stack + i) == '|') printf("||");
            else if (pop(stack + i) == 'p') printf("+");
            else if (pop(stack + i) == 'm') printf("-");
            else printf("%c", pop(stack + i));
        }
        printf("\n");
    }
    free(stack);
}