#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#pragma warning(disable : 4996)

int calculatorone(int a, char x)
{
    switch (x)
    {
    case '!':
        return a != 0 ? 0 : 1;
    case 'p':
        return a;
    case 'm':
        return -a;
    }
}

int calculatortwo(int a, int b, char x)
{
    switch (x)
    {
    case '*':
        return a * b;
    case '%':
        return a % b;
    case '/':
        return a / b;
    case '+':
        return a + b;
    case '-':
        return a - b;
    case '<':
        return a < b;
    case '>':
        return a > b;
    case '=':
        return a == b;
    // case '==':
    // return a == b;
    case '&':
        return a && b;
    case '|':
        return a || b;
    }
}

int prefix(char *str, int index, int maxindex)
{
    printf("%c\n", str[index]);
    if (index == maxindex)
        return str[index] - '0';
    if (str[index] == 'p' || str[index] == 'm' || str[index] == '!')
        return calculatorone(prefix(str, index + 1, maxindex), str[index]);
    else if (str[index] >= '0' && str[index] <= '9')
        return str[index] - '0';
    else
        return calculatortwo(prefix(str, index + 1, maxindex), prefix(str, index + 2, maxindex), str[index]);
}

int main()
{
    int numberofinput;
    int index;
    int print;
    char **str;
    char tmp[101];
    scanf("%d", &numberofinput);
    str = (char **)malloc(sizeof(char *) * numberofinput);
    for (int i = 0; i < numberofinput; i++)
    {
        scanf(" %s", tmp);
        str[i] = (char *)malloc(sizeof(char) * (strlen(tmp) + 1));
        strcpy(str[i], tmp);
        index = strlen(str[i]);
        print = prefix(str[i], 0, strlen(str[i]) - 1);
        printf("%d\n", print);
    }
    return 0;
}

/*
전위수식


*/