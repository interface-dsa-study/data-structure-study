#include <stdio.h>
#include <string.h>

int getPrec(const char *op)
{
    if (strcmp(op, "!") == 0 || strcmp(op, "U+") == 0 || strcmp(op, "U-") == 0)
        return 6;
    if (strcmp(op, "*") == 0 || strcmp(op, "/") == 0)
        return 5;
    if (strcmp(op, "+") == 0 || strcmp(op, "-") == 0)
        return 4;
    if (strcmp(op, ">") == 0 || strcmp(op, "<") == 0)
        return 3;
    if (strcmp(op, "&&") == 0)
        return 2;
    if (strcmp(op, "||") == 0)
        return 1;
    return 0;
}

int hasHigherOrEqualPrecedence(const char *top, const char *incoming, int isIncomingUnary)
{
    int p1 = getPrec(top);
    int p2 = getPrec(incoming);

    if (isIncomingUnary)
    {
        return p1 > p2;
    }
    else
    {
        return p1 >= p2;
    }
}

const char *formatOp(const char *op)
{
    if (strcmp(op, "U+") == 0)
        return "+";
    if (strcmp(op, "U-") == 0)
        return "-";
    return op;
}

void solveProblem1()
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

        char stack[200][5];
        int top = -1;
        char out[400] = "";
        int prevWasOperandOrCloseParen = 0;

        for (int j = 0; j < len; j++)
        {
            char c = expr[j];

            if (c >= 'A' && c <= 'Z')
            {
                int outLen = strlen(out);
                out[outLen] = c;
                out[outLen + 1] = '\0';
                prevWasOperandOrCloseParen = 1;
            }
            else if (c == '(')
            {
                strcpy(stack[++top], "(");
                prevWasOperandOrCloseParen = 0;
            }
            else if (c == ')')
            {
                while (top != -1 && strcmp(stack[top], "(") != 0)
                {
                    strcat(out, formatOp(stack[top--]));
                }
                if (top != -1)
                    top--;
                prevWasOperandOrCloseParen = 1;
            }
            else
            {
                char op[5] = "";
                int isUnary = 0;

                if (c == '&' && j + 1 < len && expr[j + 1] == '&')
                {
                    strcpy(op, "&&");
                    j++;
                }
                else if (c == '|' && j + 1 < len && expr[j + 1] == '|')
                {
                    strcpy(op, "||");
                    j++;
                }
                else if (c == '!')
                {
                    strcpy(op, "!");
                    isUnary = 1;
                }
                else if (c == '+' || c == '-')
                {
                    if (!prevWasOperandOrCloseParen)
                    {
                        strcpy(op, (c == '+') ? "U+" : "U-");
                        isUnary = 1;
                    }
                    else
                    {
                        op[0] = c;
                        op[1] = '\0';
                    }
                }
                else
                {
                    op[0] = c;
                    op[1] = '\0';
                }

                while (top != -1 && strcmp(stack[top], "(") != 0)
                {
                    if (hasHigherOrEqualPrecedence(stack[top], op, isUnary))
                    {
                        strcat(out, formatOp(stack[top--]));
                    }
                    else
                    {
                        break;
                    }
                }
                strcpy(stack[++top], op);
                prevWasOperandOrCloseParen = 0;
            }
        }

        while (top != -1)
        {
            strcat(out, formatOp(stack[top--]));
        }

        printf("%s\n", out);
    }
}

int main()
{
    solveProblem1();
    return 0;
}