#ifndef LABPZRL3_CALC_H
#define LABPZRL3_CALC_H

typedef struct {
    int value;
    int origBase;
} Num;

Num strToNum(const char *str);

int charToDigit(char c);

char* numToStr(Num num);

Num add(Num num1, Num num2);

Num sub(Num num1, Num num2);

Num mul(Num num1, Num num2);

Num rem(Num num1, Num num2);

Num bitAnd(Num num1, Num num2);

Num bitOr(Num num1, Num num2);

Num bitXor(Num num1, Num num2);

Num bitNot(Num num);

#endif //LABPZRL3_CALC_H
