#include <stdio.h>
#include<stdlib.h>
int max(int*,int,int);
int main() {
    int n;
    scanf("%d",&n);
    int *a=(int*)calloc(n,sizeof(int));
    int m=max(a,n,*(a+n));
    return 0;
}
int max(int *a,int n,int p) {
    if (p>*a)return p;
    else if (n==0)return *a;
    return max(a+1,n-1,p);
}
