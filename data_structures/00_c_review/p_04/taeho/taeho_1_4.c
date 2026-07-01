#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main() {
    char tmp[101]={0};
    scanf("%s",tmp);
    char *s=(char*)calloc(strlen(tmp)+1,sizeof(char));
    if (s==NULL) {
        printf("calloc failed");
        return -1;
    }
    strcpy(s,tmp);
    for (int i=0;i<strlen(s);i++) {
        printf("%s\n",s);
        char t;
        for (char *p=s;p<s+strlen(s);p++) {
            if (p==s) {
                t=*p;
            }
            if (p==s+strlen(s)-1){
                *p=t;
                break;
            }
            *p=*(p+1);
        }
    }
    free(s);
}