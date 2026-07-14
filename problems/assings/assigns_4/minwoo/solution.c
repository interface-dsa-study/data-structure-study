#pragma warning(disable:4996)
#include <stdio.h>
#include<string.h>
#include <stdlib.h>

int cal(char ch, int a, int b) {
    switch (ch) {
        case 'p': return a;
        case 'm': return -a;
        case '!': return a != 0 ? 0 : 1;
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/': return a / b;
        case '%': return a % b;
        case '>': return a > b;
        case '<': return a < b;
        case '=': return a == b;
        case '&': return a && b;
        case '|': return a || b;

    }
    return 0;
}

int Prefix(char ch[], int *len) {
    char ch1;
    int a, b = 0;
    ch1 = ch[*len];
    if (ch[*len] == '\0') {
        return 0;
    }
    (*len)++;
    if (ch1 >= '0' && ch1 <= '9') {
        return ch1 - '0';
    }
    else {
        if (ch1 == '!' || ch1 == 'm' || ch1 == 'p') {
            a = Prefix(ch, len);
        }
        else {
            a = Prefix(ch, len);
            b = Prefix(ch, len);
        }
        return cal(ch1, a, b);
    }
}

int main() {
    char ch[101];
    int N, i, len, result;

    scanf("%d", &N);

    getchar();

    result = 0;

    for (i = 0;i < N;i++) {
        scanf("%s", ch);
        len = 0;
        result = Prefix(ch, &len);
        printf("%d\n", result);
    }
    return 0;
}