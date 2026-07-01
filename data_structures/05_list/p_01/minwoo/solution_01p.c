#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
	struct Node* next;
	int coef, exp;
}Node;

void add_node(Node **pnode, int mcoef, int mexp) {
	Node* temp;
	Node* node = (Node*)malloc(sizeof(Node));
	node->next = NULL;
	node->coef = mcoef;
	node->exp = mexp;
	temp = (*pnode)->next;
	if (temp == NULL) {
		(*pnode)->next = node;
	}
	else {
		while (temp->next != NULL) {
			temp = temp->next;
		}
		temp->next = node;
	}
}

void sum(Node** r, Node *pnode1, Node *pnode2) {
	Node* tmp1 = pnode1->next;
	Node* tmp2 = pnode2->next;

	while (tmp1 != NULL && tmp2 != NULL) {
		Node* tmp3 = (*r)->next;
		Node* node = (Node*)malloc(sizeof(Node));
		node->next = NULL;
		if (tmp1->exp > tmp2->exp) {
			node->coef = tmp1->coef;
			node->exp = tmp1->exp;
			tmp1 = tmp1->next;
		}
		else if (tmp1->exp == tmp2->exp) {
			if (tmp1->coef + tmp2->coef == 0) {
				tmp1 = tmp1->next;
				tmp2 = tmp2->next;
				free(node);
				continue;
			}
			else {
				node->coef = tmp1->coef + tmp2->coef;
				node->exp = tmp1->exp;
				tmp1 = tmp1->next;
				tmp2 = tmp2->next;
			}
		}
		else {
			node->coef = tmp2->coef;
			node->exp = tmp2->exp;
			tmp2 = tmp2->next;

		}
		if (tmp3 == NULL) {
			(*r)->next = node;
		}
		else {
			while (tmp3->next != NULL) {
				tmp3 = tmp3->next;
			}
			tmp3->next = node;
		}
	}
	if (tmp1 != NULL) {
		while (tmp1) {
			Node* tmp3 = (*r);
			Node* node = (Node*)malloc(sizeof(Node));
			node->next = NULL;
			node->coef = tmp1->coef;
			node->exp = tmp1->exp;
			while(tmp3->next != NULL) {
				tmp3 = tmp3->next;
			}
			tmp3->next = node;
			tmp1 = tmp1->next;
		}
	}
	else if (tmp2 != NULL) {
		while (tmp2) {
			Node* tmp3 = (*r);
			Node* node = (Node*)malloc(sizeof(Node));
			node->next = NULL;
			node->coef = tmp2->coef;
			node->exp = tmp2->exp;
			while (tmp3->next != NULL) {
				tmp3 = tmp3->next;
			}
			tmp3->next = node;
			tmp2 = tmp2->next;
		}
	}
}

void print(Node* pnode) {
	Node* temp = pnode->next;
	while (temp) {
		printf(" %d %d", temp->coef, temp->exp);
		temp = temp->next;
	}
}

void free_list(Node* node) {
	if (node) {
		free_list(node->next);
		free(node);
	}
}

int main() {
	Node* node1 = (Node *)malloc(sizeof(Node));
	Node* node2 = (Node *)malloc(sizeof(Node));
	Node* result = (Node*)malloc(sizeof(Node));
	int N, mcoef, mexp, i;

	node1->next = NULL;
	node2->next = NULL;
	result->next = NULL;

	scanf("%d", &N);

	for (i = 0; i < N; i++) {
		scanf("%d %d", &mcoef, &mexp);
		add_node(&node1, mcoef, mexp);
	}

	scanf("%d", &N);

	for (i = 0; i < N; i++) {
		scanf("%d %d", &mcoef, &mexp);
		add_node(&node2, mcoef, mexp);
	}

	sum(&result, node1, node2);

	print(result);

	free_list(node1);

	free_list(node2);

	free_list(result);

	return 0;

}