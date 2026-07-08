#include <stdio.h>
#include <stdlib.h>

int main()
{
    int q, n;

    /* 큐 크기 및 명령 개수 입력 */
    scanf("%d", &q);
    scanf("%d", &n);

    /* 동적 할당으로 크기 q인 배열 생성 (calloc으로 0 초기화) */
    int *queue = (int *)calloc(q, sizeof(int));
    int front = 0;
    int rear = 0;

    for (int i = 0; i < n; i++)
    {
        char cmd;
        scanf(" %c", &cmd);

        if (cmd == 'I')
        {
            /* 삽입(Insert) */
            int val;
            scanf("%d", &val);

            /* 포화 상태 검사: (rear + 1) % q == front */
            if ((rear + 1) % q == front)
            {
                printf("overflow");
                for (int j = 0; j < q; j++)
                {
                    printf(" %d", queue[j]);
                }
                printf("\n");
                free(queue);
                return 0;
            }

            rear = (rear + 1) % q;
            queue[rear] = val;
        }
        else if (cmd == 'D')
        {
            /* 삭제(Delete) */

            /* 공백 상태 검사: front == rear */
            if (front == rear)
            {
                printf("underflow\n");
                free(queue);
                return 0;
            }

            front = (front + 1) % q;
            queue[front] = 0; /* 삭제된 자리를 0으로 치환 */
        }
        else if (cmd == 'P')
        {
            /* 출력(Print): 배열 원소 전체를 인덱스 0부터 차례로 출력 */
            for (int j = 0; j < q; j++)
            {
                printf(" %d", queue[j]);
            }
            printf("\n");
        }
    }

    free(queue);
    return 0;
}