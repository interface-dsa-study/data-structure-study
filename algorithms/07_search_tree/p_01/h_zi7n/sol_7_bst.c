#include<stdio.h>
#include<stdlib.h>

typedef int key;

typedef struct Node {
    key value;
    struct Node *iChild, *rChild, *parent;
}Node;

void initNode(Node *node) {
    node->iChild = NULL;
    node->rChild = NULL;
    node = NULL;
}

Node *treeSearch(key value) {

}

void insertitem(key ikey) {// ikey 는 인서트 키를 의미함.(현재 삽입하고자 하는 원소값)
    Node *node; treeSearch(ikey);
    if (node == NULL) node->value = ikey;
    else if (ikey < node->value) {
        if (node->iChild != NULL) node->iChild->value = ikey;
    }
    else if (ikey > node->value) {
        if (node->rChild != NULL) node->rChild->value = ikey;
    }

}

key findElement(key value) {

}


Node reduceExternal(Node z) {

}

key removeElement(key value) {

}

int isExternal(Node w) {

}

int isInternal(Node w) {

}

Node inOrderSucc(Node w) {

}

void Print(Node* root) {
    if (root->iChild != NULL) Print(root->iChild);
    if (root->rChild != NULL) Print(root->rChild);
}

int main() {
    char order; key value; Node* node; initNode(node);
    while (1) {
        scanf(" %c", &order);
        if (order == 'q') break;
        if (order == 'i') { scanf("%d", &value); insertitem(value); }
        if (order == 'd') { scanf("%d", &value); removeElement(value);}
        if (order == 's') { scanf("%d", &value); findElement(value); }
        if (order == 'p') { Print(node); }
    }
}