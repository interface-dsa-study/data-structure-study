#include<stdio.h>
#include<stdlib.h>

int hash_function1(int key, int M){
    return key % M;
}

int hash_function2(int key, int M, int q){
    return q - (key % q);
}

int insertItem(int key, int *arr, int M, int q){
    int v = hash_function1(key, M);
    int collision_count = 0;
    int index;
    while (arr[v] != 0){
        v += hash_function2(key, M, q);
        collision_count++;
        v = hash_function1(v, M);
    }
    arr[v] = key;
    for (int i = 0; i < collision_count; i++){
        printf("C");
    }
    printf("%d\n", v);
}

int searchItem(int key, int *arr, int M, int q){
    int v = key % M;
    while (arr[v] != 0 && v < M){
        if (arr[v] == key)
            return v;
        v += hash_function2(key, M, q);
        v = v % M;
    }
    return -1;
}

void print(int *arr, int M){
    for (int i = 0; i < M; i++){
        printf(" %d", arr[i]);
    }
    printf("\n");
}

int main(){
    int *arr;
    int M, n, q;
    int key;
    char input;
    scanf("%d %d %d", &M, &n, &q);
    arr = (int *)malloc(sizeof(int) * M);

    if (arr == NULL){
        printf("FAIL TO ASSIGN");
        return -1;
    }

    for (int i = 0; i < M; i++){
        arr[i] = 0;
    }

    while (1){
        scanf(" %c", &input);
        if (input == 'i'){
            scanf("%d", &key);
            insertItem(key, arr, M, q);
        }
        else if (input == 's'){
            scanf("%d", &key);
            if (searchItem(key, arr, M, q) != -1){
                printf("%d %d\n", searchItem(key, arr, M, q), key);
            }
            else
                printf("%d\n", -1);
        }
        else if (input == 'p'){
            print(arr, M);
        }
        else if (input == 'e'){
            print(arr, M);
            break;
        }
    }
    free(arr);
    return 0;
}