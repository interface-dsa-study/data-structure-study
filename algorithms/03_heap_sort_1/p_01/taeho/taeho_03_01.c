#include <stdio.h>
#include <stdlib.h>
int H[100]={0};//1 base && key amount < 100
int n=0;
void swap(int *a,int *b) {
    int tmp=*a;
    *a=*b;
    *b=tmp;
}
void upheap(int index) {
    int child_index=index;//inserted index
    while (child_index>1) {
        int parent_index=child_index/2;
        if (H[parent_index]<H[child_index]) {
            swap(H+parent_index,H+child_index);
            child_index=parent_index;
        }
        else break;
    }
}
void downheap(int index) {
    int parent_index=index;//deleted index
    while (parent_index*2<=n) {
        int child_index=parent_index*2;
        if (H[child_index]<H[child_index+1]) child_index++;
        if (H[parent_index]<H[child_index]) {
            swap(H+parent_index,H+child_index);
            parent_index=child_index;
        }
        else break;
    }
}
void insert_item() {
    if (n==99) {
        printf("heap is full");
        return;
    }
    int key;
    scanf("%d",&key);
    H[++n]=key;
    upheap(n);
    printf("0");
}
void delete_item(){
    if (!n) {
        printf("heap is empty");
        return;
    }
    printf(" %d",H[1]);
    H[1]=H[n--];
    downheap(1);
}
void print_heap() {
    for (int i=1;i<=n;i++) {
        printf(" %d",H[i]);
    }
}
int main() {
    setbuf(stdout,NULL);
    char input;
    while (1) {
        scanf(" %c",&input);
        switch (input) {
            case'i':
                insert_item();
                break;
            case'd':
                delete_item();
                break;
            case'p':
                print_heap();
                break;
            case'q':
                return 0;
        }
        printf("\n");
    }
}