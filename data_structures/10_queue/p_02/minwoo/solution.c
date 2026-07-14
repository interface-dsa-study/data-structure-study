#pragma warning(disable:4996)
#include <stdio.h>
#include<string.h>
#include <stdlib.h>

typedef struct deque {
	struct deque* prev;
	struct deque* next;
	int data;
}deque;

void add_front(deque** phead, int num) {
	deque* newnode = (deque*)malloc(sizeof(deque));
	newnode->prev = NULL;
	newnode->next = NULL;
	newnode->data = num;
	if (*phead == NULL) {
		*phead = newnode;
	}
	else {
		newnode->next = *phead;
		(*phead)->prev = newnode;
		*phead = newnode;
	}
}

void add_rear(deque** phead, int num) {
	deque* newnode = (deque*)malloc(sizeof(deque));
	newnode->prev = NULL;
	newnode->next = NULL;
	newnode->data = num;
	if (*phead == NULL) {
		*phead = newnode;
	}
	else {
		deque* temp = *phead;
		while (temp->next) {
			temp = temp->next;
		}
		temp->next = newnode;
		newnode->prev = temp;
	}
}

int delete_front(deque** phead) {
	if (*phead == NULL) {
		printf("underflow");
		return 0;
	}
	else {
		deque* temp;
		temp = *phead;
		(*phead) = (*phead)->next;
		temp->next->prev = NULL;
		temp->next = NULL;
		free(temp);
	}
	return 1;
}

int delete_rear(deque** phead) {
	if (*phead == NULL) {
		printf("underflow");
		return 0;
	}
	else {
		if ((*phead)->next == NULL) {
			*phead = NULL;
			free(*phead);
		}
		else {
			deque* temp = *phead;
			while (temp->next) {
				temp = temp->next;
			}
			temp->prev->next = NULL;
			temp->prev = NULL;
			free(temp);
		}
	}
	return 1;
}

void print(deque* deq) {
	deque* temp = deq;
	while (temp) {
		printf(" %d", temp->data);
		temp = temp->next;
	}
	printf("\n");
}

int main() {
	deque* deq = NULL;
	char ch[3];
	int N, num, i;

	scanf("%d", &N);

	getchar();

	for (i = 0;i < N;i++) {
		scanf(" %s", ch);
		if (strcmp(ch, "AF") == 0) {
			scanf("%d", &num);
			add_front(&deq, num);
		}
		else if (strcmp(ch, "AR") == 0) {
			scanf("%d", &num);
			add_rear(&deq, num);
		}
		else if (strcmp(ch, "DF") == 0) {
			if (delete_front(&deq) == 0) {
				break;
			}
		}
		else if (strcmp(ch, "DR") == 0) {
			if (delete_rear(&deq) == 0) {
				break;
			}
		}
		else {
			print(deq);
		}
	}
	return 0;
}