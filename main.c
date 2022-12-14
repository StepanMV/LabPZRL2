#include <stdio.h>
#include <stdlib.h>
#include "calc.h"

Num operations(Num num1, Num num2, char operation) {
    Num num = {0, 0};
    switch (operation) {
        case '+':
            num = add(num1, num2);
            break;
        case '-':
            num = sub(num1, num2);
            break;
        case '*':
            num = mul(num1, num2);
            break;
        case '%':
            num = rem(num1, num2);
            break;
        case '&':
            num = bitAnd(num1, num2);
            break;
        case '|':
            num = bitOr(num1, num2);
            break;
        case '^':
            num = bitXor(num1, num2);
            break;
        case '~':
            num = bitNot(num1);
            break;
        default:
            printf("operations ERROR: unknown operation");
            break;
    }
    return num;
}

int main() {
    char operation = 0;
    char str1[64];
    char str2[64];
    Num num1, num2, result;

    printf("Enter an equation: ");
    operation = (char) fgetc(stdin);
    ungetc(operation, stdin);
    if (operation == '~') {
        scanf("%c%s", &operation, str1);
        num1 = strToNum(str1);
        num2 = strToNum(str1);
    } else {
        scanf("%s %c %s", str1, &operation, str2);
        num1 = strToNum(str1);
        num2 = strToNum(str2);
    }

    // Perform the operation
    result = operations(num1, num2, operation);

    char *resultStr = numToStr(result);
    printf("%s (%d)\n", resultStr, result.value);
    free(resultStr);
    return 0;
}
