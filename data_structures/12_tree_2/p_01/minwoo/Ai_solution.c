#pragma warning(disable:4996)
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct Node {
	struct Node* right;
	struct Node* left;
	int data;
	int id;
}Node;

Node* insert_root(int data, Node* right, Node* left, int iD) {
	Node* newnode = (Node*)malloc(sizeof(Node));
	newnode->data = data;
	newnode->right = right;
	newnode->left = left;
	newnode->id = iD;

	return newnode;
}

int Pre_Traversal(Node* root, int Id) {
	if (root == NULL) {
		return 0;
	}

	if (root->id == Id) {
		printf(" %d", root->data);

		Pre_Traversal(root->left, root->left ? root->left->id : 0);
		Pre_Traversal(root->right, root->right ? root->right->id : 0);

		return 1;
	}

	if (Pre_Traversal(root->left, Id) == 1) {
		return 1;
	}

	if (Pre_Traversal(root->right, Id) == 1) {
		return 1;
	}

	return 0;
}

int In_Traversal(Node* root, int Id) {
	if (root == NULL) {
		return 0;
	}
	if (root->id == Id) {
		In_Traversal(root->left, root->left ? root->left->id : 0);
		printf(" %d", root->data);
		In_Traversal(root->right, root->right ? root->right->id : 0);
		return 1;
	}
	if (In_Traversal(root->left, Id) == 1) {
		return 1;
	}

	if (In_Traversal(root->right, Id) == 1) {
		return 1;
	}

	return 0;
}

int Post_Traversal(Node* root, int Id) {
	if (root == NULL) {
		return 0;
	}
	if (root->id == Id) {
		Post_Traversal(root->left, root->left ? root->left->id : 0);
		Post_Traversal(root->right, root->right ? root->right->id : 0);
		printf(" %d", root->data);
		return 1;
	}
	if (Post_Traversal(root->left, Id) == 1) {
		return 1;
	}

	if (Post_Traversal(root->right, Id) == 1) {
		return 1;
	}

	return 0;
}

int main() {
	Node* node[8];
	int num, i, ID;
	node[7] = insert_root(80, NULL, NULL, 8);
	node[6] = insert_root(130, NULL, NULL, 7);
	node[5] = insert_root(120, node[7], node[6], 6);
	node[4] = insert_root(90, NULL, NULL, 5);
	node[3] = insert_root(70, NULL, NULL, 4);
	node[2] = insert_root(50, node[5], NULL, 3);
	node[1] = insert_root(30, node[4], node[3], 2);
	node[0] = insert_root(20, node[2], node[1], 1);

	scanf("%d %d", &num, &ID);

	if (ID >= 9) {
		printf("-1");
		return 0;
	}

	if (num == 1) {
		Pre_Traversal(node[0], ID);
	}
	else if (num == 2) {
		In_Traversal(node[0], ID);
	}
	else {
		Post_Traversal(node[0], ID);
	}
}