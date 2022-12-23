#include <stdio.h>
#include <stdlib.h>
#include "calc.h"

void error(char* err) {
    printf("%s\n", err);
    exit(1);
}

int charToDigit(char c) {
    if (c >= '0' && c <= '9') {
        return c - '0';
    } else if (c >= 'a' && c <= 'f') {
        return c - 'a' + 10;
    } else if (c >= 'A' && c <= 'F') {
        return c - 'A' + 10;
    } else {
        return -1;
    }
}

/*
 * Converts a string to a number in base 2, 8 or 16
 * @param str - the string to convert
 * @return Num - the number
 */
Num strToNum(const char *str) {
    Num num = {0, 0};

    // Sign calculation
    int isNeg = 0;
    if (str[0] == '-') {
        isNeg = 1;
        str++;
    } else if (str[0] == '+') {
        str++;
    }

    // Base calculation
    if (str[0] == '0' && str[1] == 'x') {
        num.origBase = 16;
        str += 2;
    } else if (str[0] == '0') {
        num.origBase = 8;
        str += 1;
    } else {
        int onlyBin = 1;
        for (int i = 0; str[i] != '\0'; i++) {
            if (str[i] != '0' && str[i] != '1') {
                onlyBin = 0;
                break;
            }
        }
        num.origBase = onlyBin ? 2 : 10;
    }

    if (num.origBase == 10) {
        error("strToNum ERROR: invalid base");
    }

    // String length calculation
    int len = 0;
    for (int i = 0; str[i] != '\0'; i++) {
        len++;
    }

    if (len == 0) {
        error("strToNum ERROR: empty value");
    }

    // Value calculation
    int baseInPow = 1;
    for (int i = 0; str[i] != '\0'; i++) {
        int digit = charToDigit(str[len - i - 1]);
        // ERROR: invalid digit for the base
        if (digit == -1 || digit >= num.origBase) {
            error("strToNum ERROR: invalid digit for the base");
        }
        num.value += digit * baseInPow;
        baseInPow *= num.origBase;
    }

    if (isNeg) {
        num.value = -num.value;
    }

    return num;
}