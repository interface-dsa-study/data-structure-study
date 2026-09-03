#pragma warning(disable:4996)
#include <stdio.h>
#include<string.h>
#include <stdlib.h>
#include <time.h>
#include<stdbool.h>

typedef struct graph {
    int nodenum;
    int weight;
    struct graph* nextvertex;
    struct graph* nextedge;
}graph;

graph* make_node(int num, int weight) {
    graph* newnode = malloc(sizeof(graph));
    newnode->nodenum = num;
    newnode->weight = weight;
    newnode->nextvertex = NULL;
    newnode->nextedge = NULL;
    return newnode;
}

void make_graph(graph** node, int startnum, int weight, int endnum) {
    if (*node == NULL) {
        *node = make_node(startnum, 0);
    }
    graph* tempvertex = *node;
    while (tempvertex->nextvertex!= NULL && tempvertex->nodenum != startnum) {
        tempvertex = tempvertex->nextvertex;
    }
    if (tempvertex->nodenum != startnum) {
        tempvertex->nextvertex = make_node(startnum, 0);
        tempvertex = tempvertex->nextvertex;
    }
    graph* tempedge = tempvertex;
    while (tempedge->nextedge) {
        tempedge = tempedge->nextedge;
    }
    tempedge->nextedge = make_node(endnum, weight);
    if (startnum == endnum) {
        return;
    }
    graph* temp = *node;
    while (temp->nextvertex != NULL && temp->nodenum != endnum) {
        temp = temp->nextvertex;
    }
    if (temp->nodenum != endnum) {
        temp->nextvertex = make_node(endnum, 0);
        temp = temp->nextvertex;
    }
    while (temp->nextedge) {
        temp = temp->nextedge;
    }
    temp->nextedge = make_node(startnum, weight);
}

void change(graph* adjacencylist, int a, int b, int weight) {
    graph* vertexA = adjacencylist;
    graph* vertexB = adjacencylist;
    graph* tempedgeA = NULL;
    graph* tempedgeB = NULL;
    graph* prev1 = NULL;
    graph* prev2 = NULL;
    while (vertexA != NULL && vertexA->nodenum != a) {
        vertexA = vertexA->nextvertex;
    }

    while (vertexB != NULL && vertexB->nodenum != b) {
        vertexB = vertexB->nextvertex;
    }
    if (vertexA == NULL || vertexB == NULL) {
        printf("-1");
        return;
    }
    tempedgeA = vertexA->nextedge;
    tempedgeB = vertexB->nextedge;
    if (weight == 0) {
        while (tempedgeA != NULL && tempedgeA->nodenum != b) {
            prev1 = tempedgeA;
            tempedgeA = tempedgeA->nextedge;
        }
        while (tempedgeB != NULL && tempedgeB->nodenum != a) {
            prev2 = tempedgeB;
            tempedgeB = tempedgeB->nextedge;
        }
        if (tempedgeA == NULL || tempedgeB == NULL) {
            return;
        }
        else {
            if (tempedgeA->nextedge == NULL) {
                prev1->nextedge = NULL;
            }
            else {
                prev1->nextedge = tempedgeA->nextedge;
            }
            if (tempedgeB->nextedge == NULL) {
                prev2->nextedge = NULL;
            }
            else {
                prev2->nextedge = tempedgeB->nextedge;
            }
            free(tempedgeA);
            free(tempedgeB);
            tempedgeA = NULL;
            tempedgeB = NULL;
        }
    }
    else {
        while (tempedgeA != NULL && tempedgeA->nodenum != b) {
            prev1 = tempedgeA;
            tempedgeA = tempedgeA->nextedge;
        }
        while (tempedgeB != NULL && tempedgeB->nodenum != a) {
            prev2 = tempedgeB;
            tempedgeB = tempedgeB->nextedge;
        }
        if (tempedgeA == NULL || tempedgeB == NULL) {
            tempedgeA = vertexA->nextedge;
            tempedgeB = vertexB->nextedge;
            prev1 = NULL;
            prev2 = NULL;
            if (tempedgeA->nodenum > b) {
                prev1 = tempedgeA;
            }
            else {
                while (tempedgeA != NULL && tempedgeA->nodenum < b) {
                    prev1 = tempedgeA;
                    tempedgeA = tempedgeA->nextedge;
                }
            }
            if (tempedgeB->nodenum > a) {
                prev2 = tempedgeB;
            }
            else {
                while (tempedgeB != NULL && tempedgeB->nodenum < a) {
                    prev2 = tempedgeB;
                    tempedgeB = tempedgeB->nextedge;
                }
            }
            graph* next;
            if (prev1->nextedge == NULL) {
                prev1->nextedge = make_node(b, weight);
            }
            else {
                next = make_node(b, weight);
                next->nextedge = prev1->nextedge;
            }
            if (prev1->nextedge == NULL) {
                prev2->nextedge = make_node(a, weight);
            }
            else {
                next = make_node(a, weight);
            }

        }
        else {

        }
    }

}

void print(graph* adjacencylist, int findnode) {
    graph* vertexA = adjacencylist;
    while (vertexA != NULL && vertexA->nodenum != findnode) {
        vertexA = vertexA->nextvertex;
    }
    if (vertexA == NULL) {
        printf("-1");
        return;
    }
    graph* vertexB = vertexA->nextedge;
    while (vertexB) {
        printf(" %d %d", vertexB->nodenum, vertexB->weight);
        vertexB = vertexB->nextedge;
    }
    printf("\n");
}
int main() {
    graph* adjacencylist = NULL;
    make_graph(&adjacencylist, 1, 1, 2);
    make_graph(&adjacencylist, 1, 1, 3);
    make_graph(&adjacencylist, 1, 1, 4);
    make_graph(&adjacencylist, 2, 1, 3);
    make_graph(&adjacencylist, 3, 4, 5);
    make_graph(&adjacencylist, 1, 2, 6);
    make_graph(&adjacencylist, 5, 4, 5);
    make_graph(&adjacencylist, 5, 3, 6);
    char ch;
    int nodenumber, a, b, w;
    while (1) {
        scanf(" %c", &ch);
        if (ch == 'a') {
            scanf("%d", &nodenumber);
            print(adjacencylist, nodenumber);
        }
        else if (ch == 'm') {
            scanf("%d %d %d", &a, &b, &w);
            change(adjacencylist, a, b, w);
        }
        else {
            break;
        }
    }
    return 0;
}