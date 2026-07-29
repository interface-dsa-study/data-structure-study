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
    int max = 0, change_number = 0;
    for (int i = N; i > 0; i--) {
        for (int j = 0; j < N ; j++ ) {
            if (max < (queue+j)->element) {
                max = (queue+j)->element;
                change_number = j;
            }
        }
        if (max != 0) {
            int tmp = (queue + i)->element;
            sorted_list[i].element = sorted_list[change_number].element;
            sorted_list[change_number].element = tmp;
        }
    }
    for (int i = 0; i < N; i ++) {
        printf(" %d", sorted_list[i].element);
    }
    free(queue);
}