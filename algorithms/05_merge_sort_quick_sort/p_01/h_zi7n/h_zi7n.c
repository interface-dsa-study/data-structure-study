#include <stdio.h>
#include <stdlib.h>

typedef int baeyul[];
typedef int buffer[];

void mergeSort(baeyul,buffer, int left, int right) {
    for (int i = left; i < right; i++) {
        buffer[i] = baeyul[i];
    }
    for (int i = left; i < right; i++) {
        for (int j = i; j < right; j++) {
            if (buffer[i] > buffer[j]) {
                int tmp = buffer[i];
                buffer[i] = buffer[j];
                buffer[j] = tmp;
            }
        }
    }
    for (int i = left; i < right; i++) {
        baeyul[i] = buffer[i];
    }
}

void merge(baeyul, buffer, int left, int middle, int right) {

}

int main() {
    int N; scanf("%d", &N);
    baeyul = (int*)malloc(sizeof(int)*N);
    buffer = (int*)malooc(sizeof(int)*N);
    int integer;
    for (int i = 0; i < N; i++){
        scanf("%d", &integer);
        baeyul[i] = integer;
    }
    
}