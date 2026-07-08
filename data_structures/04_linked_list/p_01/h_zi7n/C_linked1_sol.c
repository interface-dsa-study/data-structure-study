#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
	char data;
	struct Node* next;
	struct Node* prev;
}Node;

typedef struct List {
	struct Node* head;
	struct Node* tail;
}List;

void initialize(List* st) { // 최초 초기화 상태 만들기.
	st->head = (Node*)malloc(sizeof(Node));
	st->tail = (Node*)malloc(sizeof(Node));
	st->head->next = st->tail;
	st->tail->prev = st->head;
	st->head->data = 0; st->tail->data = 0;
}

void add(List* st, int rank, char element);

void delete(List* st, int rank);

char get(List* st, int rank);

void print(List* st);

int main(void) {
	int N; scanf("%d", &N); char cmd, word; int rank;
	List* st = (List*)malloc(sizeof(List));
	initialize(st); // 최초 head와 tail을 연결하기 위한 1회성 함수.
	for (int i = 0; i < N; i++) {
		scanf(" %c", &cmd); // 입력 메인에서 진행
		if (cmd == 'A') { scanf("%d %c", &rank, &word); add(st, rank, word); }
		else if (cmd == 'D') { scanf("%d", &rank); delete(st, rank); }
		else if (cmd == 'G') { scanf("%d", &rank); get(st, rank); }
		else if (cmd == 'P') print(st);
		else printf("none\n");
	}
	free(st);
}

void add(List* st, int rank, char element) {
	Node* new_node = (Node*)malloc(sizeof(Node));
	Node* HEAD = st->head;
	for (int i = 0; i < rank - 1; i++) {
		HEAD = HEAD->next;
		if (HEAD == st->tail) {
			printf("invalid position\n"); return;
		}
	}
	new_node->next = HEAD->next;
	new_node->prev = HEAD;
	HEAD->next = new_node;
	HEAD->next->next->prev = new_node;
	new_node->data = element;
}

void delete(List* st, int rank) {
	Node* HEAD = st->head;
	if (HEAD->next == st->tail) { printf("invalid position\n"); return; }
	for (int i = 0; i < rank; i++) {
		HEAD = HEAD->next;
		if (HEAD == st->tail) {
			printf("invalid position\n"); return;
		}
	}

	HEAD->prev->next = HEAD->next;
	HEAD->next->prev = HEAD->prev;
}

char get(List* st, int rank) {
	Node* HEAD = st->head;
	for (int i = 0; i < rank; i++) {
		HEAD = HEAD->next;
		if (HEAD == st->tail) {
			printf("invalid position\n"); return ' ';
		}
	}
	printf("%c\n", HEAD->data);
}

void print(List* st) {
	Node* HEAD = st->head;
	for (int i = 0;;i++) {
		HEAD = HEAD->next;
		if (HEAD == st->tail) { printf("\n"); return;}
		printf("%c", HEAD->data);
	}
}