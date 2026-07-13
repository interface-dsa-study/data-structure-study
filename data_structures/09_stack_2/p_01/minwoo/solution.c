#pragma warning(disable:4996)
#include <stdio.h>
#include<string.h>
#include <stdlib.h>

typedef struct stack {
	char st[101];
	int top;
}stack;

int priority(char c) {
	switch (c) {
	case'm': return 6;
	case'p': return 6;
	case '!': return 6;
	case '*': return 5;
	case '/': return 5;
	case '+': return 4;
	case '-': return 4;
	case '>': return 3;
	case '<': return 3;
	case '&': return 2;
	case '|': return 1;
	}

	return 0;
}

void change(stack* s1, int length, char exp[]) {
	for (int i = 0;i < length;i++) {
		if (exp[i] >= 'A' && exp[i] <= 'Z') {
			printf("%c", exp[i]);
		}
		else if (exp[i] == '(') {
			s1->st[++(s1->top)] = exp[i];
		}
		else if (exp[i] == ')') {
			while (s1->top != -1 && s1->st[s1->top] != '(') {
				if (s1->st[s1->top] == '&' || s1->st[s1->top] == '|') {
					s1->st[s1->top] == '&' ? printf("&&") : printf("||");
				}
				else if (s1->st[s1->top] == 'm' || s1->st[s1->top] == 'p') {
					s1->st[s1->top] == 'm' ? printf("-") : printf("+");
				}
				else {
					printf("%c", s1->st[s1->top]);
				}
				s1->top--;
			}
			s1->top--;
		}
		else {
			if (exp[i] == '-' || exp[i] == '+') {
				if (i == 0 || !((exp[i-1] >= 'A' && exp[i-1] <= 'Z') ||  exp[i - 1] == ')')) {
					exp[i] = exp[i] == '-' ? 'm' : 'p';
				}
			}
			if (s1->top == -1) {
				s1->st[++(s1->top)] = exp[i];
			}
			else {
				if (priority(s1->st[s1->top]) >= priority(exp[i])) {
					while (s1->top != -1 && priority(s1->st[s1->top]) >= priority(exp[i])) {
						if (s1->st[s1->top] == '&' || s1->st[s1->top] == '|') {
							s1->st[s1->top] == '&' ? printf("&&") : printf("||");
						}
						else if (s1->st[s1->top] == 'm' || s1->st[s1->top] == 'p') {
							s1->st[s1->top] == 'm' ? printf("-") : printf("+");
						}
						else {
							printf("%c", s1->st[s1->top]);
						}
						s1->top--;
					}
				}
				s1->st[++s1->top] = exp[i];
			}
			if (exp[i] == '&' || exp[i] == '|') {
				i++;
			}
		}
	}
	if (s1->top != -1) {
		while (s1->top != -1) {
			if (s1->st[s1->top] == '&' || s1->st[s1->top] == '|') {
				s1->st[s1->top] == '&' ? printf("&&") : printf("||");
			}
			else if (s1->st[s1->top] == 'm' || s1->st[s1->top] == 'p') {
				s1->st[s1->top] == 'm' ? printf("-") : printf("+");
			}
			else {
				printf("%c", s1->st[s1->top]);
			}
			s1->top--;
		}
	}
	printf("\n");
}

int main() {
	int N, i, len;
	stack s;
	char exp[101];

	scanf("%d", &N);

	getchar();

	for (i = 0;i < N;i++) {
		scanf("%s", exp);
		len = strlen(exp);
		s.top = -1;
		change(&s, len, exp);
	}

	return 0;
}