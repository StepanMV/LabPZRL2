#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "calc.h"

char *strToNumErrors(int err) {
    switch (err) {
        case -1:
            return "strToNumError: invalid base";
        case -2:
            return "strToNumError: empty value";
        case -3:
            return "strToNumError: invalid digit for the base";
        default:
            return "strToNumError: unknown error";
    }
}

char *operationsErrors(int err) {
    switch (err) {
        case -1:
            return "operationsError: different bases";
        case -2:
            return "operationsError: negative number";
        case -3:
            return "operationsError: division by zero";
        default:
            return "operationsError: unknown error";
    }
}

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
        default:
            printf("operationsError: unknown operation");
            break;
    }
    return num;
}

int isOperator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '%' || c == '&' || c == '|' || c == '^' || c == '~';
}

int main() {
    char equation[128];
    char operation = 0;
    char str1[64];
    char str2[64];
    Num num1, num2, result;

    printf("Enter an equation: ");
    fgets(equation, sizeof(equation), stdin);

    // Remove spaces and new line in equation
    char *p = equation;
    while (*p != '\0') {
        if (*p == ' ' || *p == '\n') {
            strcpy(p, p + 1);
        } else {
            p++;
        }
    }

    // Find an operator and split the equation
    int i = 0;
    while (equation[i] != '\0') {
        if (isOperator(equation[i])) {
            operation = equation[i];
            equation[i] = '\0';
            break;
        }
        i++;
    }

    if (operation == 0) {
        printf("mainError: no operator found");
        return 1;
    }

    strcpy(str1, equation);
    strcpy(str2, equation + i + 1);
    num1 = strToNum(str1);
    num2 = strToNum(str2);

    // Check for number reading errors
    if (num1.origBase < 0) {
        printf("%s\n", strToNumErrors(num1.origBase));
        return 1;
    } else if (num2.origBase < 0 && operation != '~') {
        printf("%s\n", strToNumErrors(num2.origBase));
        return 1;
    }

    // Perform the operation
    if (operation == '~') {
        result = bitNot(num1);
    } else {
        result = operations(num1, num2, operation);
    }

    // Check for operation errors
    if (result.origBase < 0) {
        printf("%s\n", operationsErrors(result.origBase));
        return 1;
    }

    char* resultStr = numToStr(result);
    printf("%s (%d)\n", resultStr, result.value);
    free(resultStr);
    return 0;
}
