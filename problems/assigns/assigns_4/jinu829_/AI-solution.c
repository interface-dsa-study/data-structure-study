#include <stdio.h>
#include <string.h>

// 전위표기식을 재귀적으로 계산하는 함수
// 수식 문자열을 가리키는 포인터의 주소를 받아 문자열을 앞에서부터 한 글자씩 소모합니다.
int evaluatePrefix(char **expr) {
    // 현재 포인터가 가리키는 문자를 가져오고 포인터를 다음 문자로 이동
    char op = **expr;
    (*expr)++;

    // 피연산자인 경우 (0 ~ 9 사이의 숫자)
    if (op >= '0' && op <= '9') {
        return op - '0';
    }

    // 단항 연산자 처리
    if (op == 'p' || op == 'm' || op == '!') {
        int operand = evaluatePrefix(expr); // 재귀적으로 하나의 피연산자 값을 구함
        
        if (op == 'p') return operand;              // + 부호
        if (op == 'm') return -operand;             // - 부호
        if (op == '!') return (operand == 0) ? 1 : 0; // NOT 연산 (참이면 0, 거짓이면 1)
    }

    // 이항 연산자 처리 (산술, 관계, 논리)
    // 전위표기식이므로 첫 번째 재귀 호출로 왼쪽 피연산자, 두 번째 호출로 오른쪽 피연산자를 구합니다.
    int left = evaluatePrefix(expr);
    int right = evaluatePrefix(expr);

    switch (op) {
        // 산술 연산
        case '+': return left + right;
        case '-': return left - right;
        case '*': return left * right;
        case '/': return left / right; // 정수 나눗셈 (몫 계산)
        case '%': return left % right;

        // 관계 연산
        case '<': return (left < right) ? 1 : 0;
        case '>': return (left > right) ? 1 : 0;
        case '=': return (left == right) ? 1 : 0;

        // 논리 연산
        case '&': return (left && right) ? 1 : 0;
        case '|': return (left || right) ? 1 : 0;
    }

    return 0;
}

int main() {
    int n;
    // 수식의 개수 입력
    if (scanf("%d", &n) != 1) return 0;

    for (int i = 0; i < n; i++) {
        char expr[105];
        scanf("%s", expr);

        // evaluatePrefix 함수가 문자열 포인터 자체를 이동시킬 수 있도록
        // 문자열의 시작 주소를 가리키는 포인터 변수를 생성하여 주소값을 넘겨줍니다.
        char *ptr = expr;
        int result = evaluatePrefix(&ptr);

        // 결과 출력
        printf("%d\n", result);
    }

    return 0;
}