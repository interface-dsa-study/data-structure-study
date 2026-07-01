#include <stdio.h>
int gcd(int,int);
int main() {
    int a,b;
    scanf("%d %d",&a,&b);
    int gcd_value=gcd(a,b);
    printf("%d",gcd_value);
}
int gcd(int a,int b) {
    ///a<-b
    ///b<-a%b
    if (b==0)return a;
        int t=a;
        a=b;
        b=t%b;
    return gcd(a,b);
}