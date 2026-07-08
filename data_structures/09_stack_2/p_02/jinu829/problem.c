#include <stdio.h>
#include <string.h>

void solveProblem2()
{
    int n;
    if (scanf("%d", &n) != 1)
        return;
    getchar();

    for (int i = 0; i < n; i++)
    {
        char expr[200];
        if (!fgets(expr, sizeof(expr), stdin))
            break;

        int len = strlen(expr);
        while (len > 0 && (expr[len - 1] == '\n' || expr[len - 1] == '\r'))
        {
            expr[len - 1] = '\0';
            len--;
        }

        int stack[200];
        int top = -1;

        for (int j = 0; j < len; j++)
        {
            char c = expr[j];

            if (c >= '0' && c <= '9')
            {
                stack[++top] = c - '0';
            }
            else
            {
                int operand2 = stack[top--];
                int operand1 = stack[top--];

                switch (c)
                {
                case '+':
                    stack[++top] = operand1 + operand2;
                    break;
                case '-':
                    stack[++top] = operand1 - operand2;
                    break;
                case '*':
                    stack[++top] = operand1 * operand2;
                    break;
                case '/':
                    stack[++top] = operand1 / operand2;
                    break;
                }
            }
        }

        printf("%d\n", stack[top]);
    }
}

int main()
{
    solveProblem2();
    return 0;
}