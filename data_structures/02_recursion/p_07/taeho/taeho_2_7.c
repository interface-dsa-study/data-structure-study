#include <stdio.h>
#include <string.h>
int count(char*,int,char);
int main() {
    char string[101]={0};
    scanf("%s",string);
    getchar();
    char searching_char;
    scanf("%c",&searching_char);
    int cnt=count(string,strlen(string),searching_char);
    printf("%d",cnt);
    return 0;
}
int count(char *string,int string_length,char searching_char) {
    if (string_length==0)return 0;
    int cnt=0;
    cnt+=count(string,string_length-1,searching_char);
    if (searching_char==*(string+string_length-1))return cnt+1;
    return cnt;
}