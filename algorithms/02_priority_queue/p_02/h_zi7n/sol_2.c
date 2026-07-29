#include <stdio.h>
#include <stdlib.h>

typedef struct priority_queue {
    int element;
} priority_queue;

int main(void) {
    int N; scanf("%d", &N);
    priority_queue* queue = (priority_queue*)malloc(sizeof(priority_queue) * N);
    for (int i = 0; i < N; i++) {
        scanf("%d", &(queue + i)->element);
    }
    priority_queue* sorted_list = queue;
    for (int i = 0; i < N; i++) {
        for (int j = i - 1; j > 0; j--) {
            if ((sorted_list + j)->element > (queue + i)->element) {
                (sorted_list + j + 1)->element = (sorted_list + j)->element;
                (sorted_list + j)->element = (queue + i)->element;
            }
            else continue;
        }
    }
    for (int i = 0; i < N; i ++) {
        printf(" %d", sorted_list[i].element);
    }
    free(queue);
}