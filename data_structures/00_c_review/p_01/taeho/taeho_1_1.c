#include <stdio.h>
int add(int);
int main() {
    int n;
    scanf("%d",&n);
    n=add(n);
    printf("%d",n);
    return 0;
}
int add(int n) {
    if (n==1) {
        return 1;
    }
    return n+add(n-1);
}