#include <stdio.h>
#include <stdlib.h>
int main() {
    int a,b,n;
    scanf("%d %d %d",&a,&b,&n);
    char *string=malloc(sizeof(*string)*(n+1));
    if (!string) {
        fprintf(stderr,"string malloc failed");
        exit(1);
    }
    scanf("%s",string);
    char *yn=string;
    for (int i=0;a<b&&i<n;i++,yn++) {
        int m=(a+b)/2;
        if (*yn=='Y') a=m+1;
        else if (*yn=='N') b=m;
        else {
            printf("wrong char");
            break;
        }
    }
    printf("%d",a);
    free(string);
    return 0;
}