#include <stdio.h>
int is_operator(char value) {
    return value=='*'||
        value=='%'||
        value=='/'||
        value=='+'||
        value=='-'||
        value=='<'||
        value=='>'||
        value=='='||
        value=='&'||
        value=='|';
}
int is_unary(char value) {
    return value=='p'||
        value=='m'||
        value=='!';
}
int calculate(char *string,int *index) {
    if ('0'<=string[*index]&&string[*index]<='9') return string[(*index)++]-'0';
    else if (is_unary(string[*index])) {
        (*index)++;
        switch (string[*index-1]) {
            case 'p':
                return calculate(string,index);
            case 'm':
                return -1*calculate(string,index);
            case '!':
                return !calculate(string,index);
        }
    }
    else if (is_operator(string[*index])) {
        char operator=string[(*index)++];
        int left=calculate(string,index);
        int right=calculate(string,index);
        switch (operator) {
            case '*':
                return left*right;
            case '%':
                return left%right;
            case '/':
                return left/right;
            case '+':
                return left+right;
            case '-':
                return left-right;
            case '<':
                return left<right;
            case '>':
                return left>right;
            case '=':
                return left==right;
            case '&':
                return left&&right;
            case '|':
                return left||right;
        }
    }
    else {
        return 0;
    }
}
int main() {
    int count;
    scanf("%d",&count);
    for (int i=0;i<count;i++){
        char string[101]={0};
        int index=0;
        scanf("%s",string);
        printf("%d\n",calculate(string,&index));
    }
}