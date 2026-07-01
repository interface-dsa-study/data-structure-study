#include <stdio.h>
#include <stdlib.h>
int main() {
    int n;
    scanf("%d",&n);
    int *a=(int*)calloc(n,sizeof(int));
    if (a==NULL) {
        fprintf(stderr,"calloc failed");
        return -1;
    }
    int *b=(int*)calloc(n,sizeof(int));
    if (b==NULL) {
        fprintf(stderr,"calloc failed");
        free(a);
        return -1;
    }
    int *p=a,*q=b;
    for (;p<a+n;p++) {
        scanf("%d",p);
    }
    for (;q<b+n;q++) {
        scanf("%d",q);
    }
    int *c=(int*)calloc(n,sizeof(int));
    if (c==NULL) {
        fprintf(stderr,"calloc failed");
        free(a);
        free(b);
        return -1;
    }
    int *r=c;
    for (p=a,q=b+n-1;p<a+n;p++,q--,r++) {
        *r=*p+*q;
        printf(" %d",*r);
    }
    free(c);
    free(b);
    free(a);
    return 0;
}