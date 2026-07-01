#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct {
    char *name;
    int k,e,m;
    double avg;
}S;
int main() {
    int n;
    scanf("%d",&n);
    getchar();
    S *s=(S*)calloc(n,sizeof(S));
    if (s==NULL) {
        fprintf(stderr,"calloc failed");
        return -1;
    }
    S *p=s;
    double avg=0;
    for (;p<s+n;p++) {
        char tmp[8]={0};
        scanf("%s %d %d %d",tmp,&p->k,&p->e,&p->m);
        p->name=(char*)malloc(strlen(tmp)+1);
        if (p->name==NULL) {
            printf("malloc failed");
            for (S *q=s;q<p;q++) {
                free(q);
            }
            free(s);
            return -1;
        }
        strcpy(p->name,tmp);
        p->avg=(double)(p->k+p->e+p->m)/3.0;
        printf("%s %.1f",p->name,p->avg);
        if (p->k>=90||p->e>=90||p->m>=90) {
            printf(" GREAT");
        }
        if (p->k<70||p->e<70||p->m<70) {
            printf(" BAD");
        }
        printf("\n");
    }
}