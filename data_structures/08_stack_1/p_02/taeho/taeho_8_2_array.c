#include <stdio.h>
void check(char *string) {
    int count=0;
    int flag=2;//아직 아무것도 모르는 상태
    char stack[501]={0};
    char *stack_pointer=stack;
    char *string_pointer=string;
    for (;string_pointer<string+1000&&*string_pointer!='\n';string_pointer++) {
        switch (*string_pointer) {
            case '(':
            case '{':
            case '[':
                stack_pointer++;
                *stack_pointer=*string_pointer;
                count++;
                break;
            case ')':
                if (stack_pointer==stack&&flag==2) flag=0;
                if (*stack_pointer=='(') {
                    *stack_pointer='\0';
                    if (stack_pointer>stack) stack_pointer--;
                }
                else flag=0;
                count++;
                break;
            case '}':
                if (stack_pointer==stack&&flag==2) flag=0;
                if (*stack_pointer=='{') {
                    *stack_pointer='\0';
                    if (stack_pointer>stack) stack_pointer--;
                }
                else flag=0;
                count++;
                break;
            case ']':
                if (stack_pointer==stack&&flag==2) flag=0;
                if (*stack_pointer=='[') {
                    *stack_pointer='\0';
                    if (stack_pointer>stack) stack_pointer--;
                }
                else flag=0;
                count++;
                break;
        }
    }
    if (stack_pointer==stack&&flag==2)flag=1;
    switch (flag) {
        case 0:
            printf("Wrong");
            break;
        case 1:
            printf("OK");
            break;
        case 2:
            printf("problem");
            break;
    }
    printf("_%d",count);
}
int main() {
    char string[1001]={0};
    gets(string);
    check(string);
    return 0;
}