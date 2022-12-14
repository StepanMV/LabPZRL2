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
        str += 2;
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

/*
 * Converts a number to a string in base 2, 8 or 16
 * @param num - the number to convert
 * @return char* - the string
 * @errors:
 *     NULL - invalid base
 */
char *numToStr(Num num) {
    if (num.origBase != 2 && num.origBase != 8 && num.origBase != 16) {
        return NULL;
    }

    // Length of num calculation
    int len = 0; // total length

    // Add sign and prefix to length
    len += num.value < 0 ? 1 : 0;
    if (num.origBase == 8) {
        len += 1;
    } else if (num.origBase == 16) {
        len += 2;
    }

    // Add digits to length
    int valLen = 0;
    for (int i = num.value; i != 0; i /= num.origBase) {
        valLen++;
    }
    valLen += valLen == 0 ? 1 : 0; // if value is 0, add 1 to length
    len += valLen;

    char *str = calloc(len + 1, sizeof(char));
    str[len] = '\0';

    // Add sign and prefix to string
    int offset = 0;
    if (num.value < 0) {
        str[0] = '-';
        offset++;
    }
    if (num.origBase == 8) {
        str[offset] = '0';
    } else if (num.origBase == 16) {
        str[offset] = '0';
        str[offset + 1] = 'x';
    }

    // Add digits to string
    int value = num.value < 0 ? -num.value : num.value;
    for (int i = 0; i < valLen; i++) {
        int digit = value % num.origBase;
        if (digit < 10) {
            str[len - 1 - i] = (char) (digit + '0');
        } else {
            str[len - 1 - i] = (char) (digit - 10 + 'a');
        }
        value /= num.origBase;
    }
    return str;
}

/*
 * Adds two numbers
 * @param num1 - the first number
 * @param num2 - the second number
 * @return Num - the result
 */
Num add(Num num1, Num num2) {
    Num num = {num1.value + num2.value, num1.origBase};
    if (num1.origBase != num2.origBase) {
        error("add ERROR: different bases");
    }
    return num;
}

/*
 * Subtracts two numbers
 * @param num1 - the first number
 * @param num2 - the second number
 * @return Num - the result
 */
Num sub(Num num1, Num num2) {
    return add(num1, (Num) {-num2.value, num2.origBase});
}

/*
 * Multiplies two numbers
 * @param num1 - the first number
 * @param num2 - the second number
 * @return Num - the result
 */
Num mul(Num num1, Num num2) {
    Num num = {num1.value * num2.value, num1.origBase};
    if (num1.origBase != num2.origBase) {
        error("mul ERROR: different bases");
    }
    return num;
}

/*
 * Calculates the remainder of two numbers
 * @param num1 - the first number
 * @param num2 - the second number
 * @return Num - the result
 */
Num rem(Num num1, Num num2) {
    if (num2.value == 0) {
        error("rem ERROR: division by zero");
    }
    Num num = {num1.value % num2.value, num1.origBase};
    if (num1.origBase != num2.origBase) {
        error("rem ERROR: different bases");
    }
    return num;
}

/*
 * Calculates bitwise AND of two numbers
 * @param num1 - the first number
 * @param num2 - the second number
 * @return Num - the result
 */
Num bitAnd(Num num1, Num num2) {
    Num num = {num1.value & num2.value, num1.origBase};
    if (num1.origBase != num2.origBase) {
        error("bitAnd ERROR: different bases");
    } else if (num1.value < 0 || num2.value < 0) {
        error("bitAnd ERROR: negative value");
    }
    return num;
}

/*
 * Calculates bitwise OR of two numbers
 * @param num1 - the first number
 * @param num2 - the second number
 * @return Num - the result
 */
Num bitOr(Num num1, Num num2) {
    Num num = {num1.value | num2.value, num1.origBase};
    if (num1.origBase != num2.origBase) {
        error("bitOr ERROR: different bases");
    } else if (num1.value < 0 || num2.value < 0) {
        error("bitOr ERROR: negative value");
    }
    return num;
}

/*
 * Calculates bitwise XOR of two numbers
 * @param num1 - the first number
 * @param num2 - the second number
 * @return Num - the result
 */
Num bitXor(Num num1, Num num2) {
    Num num = {num1.value ^ num2.value, num1.origBase};
    if (num1.origBase != num2.origBase) {
        error("bitXor ERROR: different bases");
    } else if (num1.value < 0 || num2.value < 0) {
        error("bitXor ERROR: negative value");
    }
    return num;
}

/*
 * Calculates bitwise NOT of a number
 * @param num - the number
 * @return Num - the result
 */
Num bitNot(Num num) {
    num.value = ~num.value;
    return num;
}
