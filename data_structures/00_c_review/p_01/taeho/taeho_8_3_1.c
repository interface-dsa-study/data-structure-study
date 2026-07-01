#include <stdio.h>
#include <stdlib.h>
int main() {
    setbuf(stdout,NULL);
    int n;
    scanf("%d",&n);
    int *s=(int*)malloc(n*sizeof(int));
    if (s==NULL) {
        printf("malloc failed");
        return 1;
    }
    int *p=s;
    for (;p<s+n;p++) {
        scanf("%d",p);
    }
    int d;
    scanf("%d",&d);
    int *tmp=(int*)realloc(s,(n-d)*sizeof(int));
    if (tmp==NULL) {
        printf("realloc failed");
        free(s);
        return -1;
    }
    s=tmp;
    n-=d;
    for (p=s;p<s+n;p++) {
        printf("%d\n",*p);
    }
    free(s);
    return 0;
}