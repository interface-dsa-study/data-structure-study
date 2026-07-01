#include <stdio.h>
void ABC(int *a,int k) {
    int *max=a+k;
    for (int *p=a+k;p<a+10;p++) {
        if (*p>*max)max=p;
    }
    int tmp=*max;
    *max=*(a+k);
    *(a+k)=tmp;
}
int main() {
    int a[10]={0};
    for (int *p=a;p<a+10;p++) {
        scanf("%d",p);
    }
    for (int k=0;k<9;k++) {
        ABC(a,k);
    }
    for (int *p=a;p<a+10;p++) {
        printf(" %d",*p);
    }
    return 0;
}