#include <stdio.h>
void rindex(int);
int main() {
    int n;
    scanf("%d",&n);
    rindex(n);
    return 0;
}
void rindex(int n) {
    if (n>=10)rindex(n/10);
    printf("%d\n",n%10);
}