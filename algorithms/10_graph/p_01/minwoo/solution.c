#pragma warning(disable:4996)
#include <stdio.h>
#include<string.h>
#include <stdlib.h>
#include <time.h>
#include<stdbool.h>

typedef struct graph {
    int nodenum;
    int weight;
    struct graph* nextnode;
    struct graph* nextlist;
}graph;

graph* make_graph(int nodenum, int weight) {
    graph* newnode = malloc(sizeof(graph));
    newnode->nodenum = nodenum;
    newnode->weight = weight;
    newnode->nextnode = NULL;
    newnode->nextlist = NULL;
}

void change(graph* adjacencylist, int a, int b, int weight) {
    graph* temp1 = adjacencylist;
    graph* temp2 = adjacencylist;
    while (temp1) {
        if (temp1->nodenum == a) {
            break;
        }
        temp1->nextnode;
    }
    while (temp2) {
        if (temp2->nodenum == b) {
            break;
        }
        temp2 = temp2->nextnode;
    }
    if (temp1 == NULL || temp2 == NULL) {
        printf("-1");
        return;
    }
    temp1 = temp1->nextlist;
    while (temp1) {
        if (temp1->nodenum == temp2->nextnode) {
            break;
        }
        temp1 = temp1->nextlist;
    }
    if (temp1->nextlist->weight != weight) {
        temp1->nextlist->weight = weight;
    }

}

void print(graph* adjacencylist, int findnode) {
    graph* temp1 = adjacencylist;
    while (temp1->nodenum != findnode) {
        temp1 = temp1->nextnode;
    }
    graph* temp2 = temp1->nextlist;
    while (temp2) {
        printf(" %d %d", temp2->nodenum, temp2->weight);
        temp2 = temp2->nextlist;
    }
    printf("\n");
}
int main() {
    graph* adjacencylist = NULL;
    adjacencylist = make_graph(1, 0);
    adjacencylist->nextlist = make_graph(2,1);
    adjacencylist->nextlist->nextlist = make_graph(3, 1);
    adjacencylist->nextlist->nextlist->nextlist = make_graph(4, 1);
    adjacencylist->nextnode = make_graph(2, 0);
    adjacencylist->nextnode->nextlist = make_graph(1, 1);
    adjacencylist->nextnode->nextlist->nextlist = make_graph(3, 1);
    adjacencylist->nextnode->nextnode = make_graph(3, 0);
    adjacencylist->nextnode->nextnode->nextlist = make_graph(1, 1);
    adjacencylist->nextnode->nextnode->nextlist->nextlist = make_graph(5, 4);
    adjacencylist->nextnode->nextnode->nextnode = make_graph(4, 0);
    adjacencylist->nextnode->nextnode->nextnode->nextlist = make_graph(1, 1);
    adjacencylist->nextnode->nextnode->nextnode->nextnode = make_graph(5, 0);
    adjacencylist->nextnode->nextnode->nextnode->nextnode->nextlist = make_graph(3, 4);
    adjacencylist->nextnode->nextnode->nextnode->nextnode->nextlist->nextlist = make_graph(5, 4);
    adjacencylist->nextnode->nextnode->nextnode->nextnode->nextlist->nextlist = make_graph(6, 3);
    adjacencylist->nextnode->nextnode->nextnode->nextnode->nextnode = make_graph(6, 0);
    adjacencylist->nextnode->nextnode->nextnode->nextnode->nextnode->nextlist = make_graph(1, 2);
    adjacencylist->nextnode->nextnode->nextnode->nextnode->nextnode->nextlist->nextlist = make_graph(5, 3);
    char ch;
    int nodenumber, a, b, m;
    while (1) {
        scanf(" %c", &ch);
        if (ch == 'a') {
            scanf("%d", &nodenumber);
            print(adjacencylist, nodenumber);
        }
        else if (ch == 'm') {
            scanf("%d %d %d", &a, &b, &m);
        }
        else {
            break;
        }
    }
    return 0;
}