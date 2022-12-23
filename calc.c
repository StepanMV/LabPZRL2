#include <stdio.h>
#include <stdlib.h>
#include "calc.h"

void error(char* err) {
    printf("%s\n", err);
    exit(1);
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
    Num num = {num1.value - num2.value, num1.origBase};
    if (num1.origBase != num2.origBase) {
        error("sub ERROR: different bases");
    }
    return num;
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
