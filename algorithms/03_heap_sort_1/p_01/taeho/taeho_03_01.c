#include <stdio.h>
#include <stdlib.h>
int H[99]={0};
int n=0;
void upheap(int index) {
    int inserted_index=index+1;
    while (inserted_index>1) {
        int parent_index=(inserted_index-(inserted_index%2))/2;
        if (H[parent_index-1]<H[inserted_index-1]) {
            int tmp=H[parent_index-1];
            H[parent_index-1]=H[inserted_index-1];
            H[inserted_index-1]=tmp;
            inserted_index=parent_index;
        }
        else break;
    }
}
int downheap(int index) {
    int deleted_index=index+1;
    while (deleted_index<n/2) {
        int left_index=deleted_index*2;
        int right_index=deleted_index*2+1;
        if (H[left_index-1]>H[deleted_index-1]&&H[left_index-1]>H[right_index-1]) {
            int tmp=H[left_index-1];
            H[left_index-1]=H[deleted_index-1];
            H[deleted_index-1]=tmp;
            deleted_index=left_index;
        }
        else if (H[right_index-1]>H[deleted_index-1]&&H[right_index-1]>H[left_index-1]) {
            int tmp=H[right_index-1];
            H[right_index-1]=H[deleted_index-1];
            H[deleted_index-1]=tmp;
            deleted_index=right_index;
        }
        else break;
    }
}
void insert_item(int key) {
    H[n]=key;
    upheap(n);
    n++;
}
int delete(){
    int target=H[0];
    H[0]=H[--n];
    downheap(0);
    return target;
}
void print() {
    for (int i=0;i<n;i++) {
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
                int key;
                scanf("%d",&key);
                insert_item(key);
                printf("0");
                break;
            case'd':
                printf("%d",delete());
                break;
            case'p':
                print();
                break;
            case'q':
                return 0;
        }
        printf("\n");
    }
}