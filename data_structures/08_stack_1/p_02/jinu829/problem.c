#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

bool isMatch(char open, char close)
{
    if (open == '(' && close == ')')
        return true;
    if (open == '{' && close == '}')
        return true;
    if (open == '[' && close == ']')
        return true;
    return false;
}

int main()
{
    char expr[1005];

    if (fgets(expr, sizeof(expr), stdin) == NULL)
        return 0;

    expr[strcspn(expr, "\n")] = '\0';

    char stack[1005];
    int top = -1;
    int count = 0;
    bool isOk = true;

    for (int i = 0; expr[i] != '\0'; i++)
    {
        char c = expr[i];

        if (c == '(' || c == '{' || c == '[')
        {
            count++;
            stack[++top] = c;
        }
        else if (c == ')' || c == '}' || c == ']')
        {
            count++;
            if (top == -1)
            {
                isOk = false;
            }
            else
            {
                char open = stack[top--];
                if (!isMatch(open, c))
                {
                    isOk = false;
                }
            }
        }
    }

    if (top != -1)
    {
        isOk = false;
    }

    if (isOk)
    {
        printf("OK_%d\n", count);
    }
    else
    {
        printf("Wrong_%d\n", count);
    }

    return 0;
}