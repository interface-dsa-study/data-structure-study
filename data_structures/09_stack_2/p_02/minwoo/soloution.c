#pragma warning(disable:4996)
#include <stdio.h>
#include<string.h>
#include <stdlib.h>

typedef struct stack {
    int st[101];
    int top;
}stack;

int cal(int a, int b, char ch) {
    switch (ch) {
        case '*': return a * b;
        case '/': return a / b;
        case '+': return a + b;
        case '-': return a - b;
    }
}

void Postfix(char ch[], int len, stack *s) {
    int i, a, b;
    for (i = 0;i < len;i++) {
        if (ch[i] >= '0' && ch[i] <= '9') {
            s->st[++(s->top)] = ch[i] - '0';
        }
        else {
            b = s->st[s->top--];
            a = s->st[s->top--];
            s->st[++(s->top)] = cal(a, b, ch[i]);
        }
    }
    printf("%d\n", s->st[s->top]);
}

int main() {
    stack s;
    char ch[101];
    int N, i, len;

    scanf("%d", &N);

    getchar();

    for (i = 0;i < N;i++) {
        scanf("%s", ch);
        len = strlen(ch);
        s.top = -1;
        Postfix(ch, len, &s);
    }

    return 0;
}