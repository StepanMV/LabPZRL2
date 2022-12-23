#include <stdio.h>
#include <stdlib.h>
#include "calc.h"

void error(char* err) {
    printf("%s\n", err);
    exit(1);
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