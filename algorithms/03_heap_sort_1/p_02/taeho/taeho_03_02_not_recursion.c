#include <stdio.h>
#include <stdlib.h>
int H[100]={0};
int n=0;
void swap(int *a,int *b) {
    int tmp=*a;
    *a=*b;
    *b=tmp;
}
void downheap(int index) {
    int parent_index=index;
    while (parent_index*2<=n) {
        int child_index=parent_index*2;
        if (H[child_index]<H[child_index+1])child_index++;
        if (H[parent_index]<H[child_index]) {
            swap(H+parent_index,H+child_index);
            parent_index=child_index;
        }
        else break;
    }
}
void build_heap() {
    for (int i=n/2;i>0;i--) {
        downheap(i);
    }
}
void print_heap() {
    for (int i=1;i<=n;i++) {
        printf(" %d",H[i]);
    }
}
int main() {
    setbuf(stdout,NULL);
    scanf("%d",&n);
    for (int i=1;i<=n;i++){
        scanf("%d",&H[i]);
    }
    build_heap();
    print_heap();
}