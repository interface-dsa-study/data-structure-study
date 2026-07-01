#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct {
    char *name;
    int score;
}S;
int main() {
    S s[5];
    S *p=s;
    double avg=0;
    for (;p<s+5;p++) {
        char tmp[10]={0};
        scanf("%s %d",tmp,&p->score);
        p->name=(char*)malloc(strlen(tmp)+1);
        if (p->name==NULL) {
            printf("malloc failed");
            for (S *q=s;q<p;q++) {
                free(q);
            }
            return -1;
        }
        avg+=(double)p->score;
        strcpy(p->name,tmp);
    }
    avg/=5.0;
    for (p=s;p<s+5;p++) {
        if ((double)p->score<=avg) {
            printf("%s\n",p->name);
        }
    }
    for (p=s;p<s+5;p++) {
        free(p->name);
    }
    return 0;
}