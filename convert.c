#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include "convert.h"

void div_convert(uint32_t n, int base, char *out) {   //follows the Implementation Hints for the div_convert function
    char temp[65] = "";
    int pos = 0;

    if (n == 0) {
        strcpy(out, "0");
        return;
    }

    while (n > 0) {    
    int remainder = n % base;
    n/=base;
        if (remainder < 10){
            temp[pos++] = '0' + remainder;
        } else {
            temp[pos++] = 'A' + (remainder - 10);
        }
    }
    for (int i = 0; i < pos; i++) {                 //takes the result string and reverses the orders of the digits from most to least
        out[i] = temp[pos - i - 1];   
    }
    out[pos] = '\0';   
}

void sub_convert(uint32_t n, int base, char *out) {
    char temp[65] = "";
    int pos = 0;
    uint32_t power = 1;      //power variable that the integer raises itself to

    if (n == 0) {           //handles for cases of 0
        strcpy(out, "0"); 
        return;
    }

    while (power <= n/(uint32_t)base) {     //raises power variable by the base until it is greater than n
        power*=(uint32_t)base;              //reduces power variable so that it is the largest possible while still less than n
    }

    while (power > 0) {
        uint32_t coefficient = n/power;     //gives the place digit for that value     
        n -= coefficient * power;           //subtracts out the already known place digit, leaving only the remainders to find
        if (coefficient < 10) {             //sets the digits to their corresponding characters
            temp[pos++] = '0' + coefficient;
        } else {
            temp[pos++] = 'A' + (coefficient - 10);
        }
        power/=(uint32_t)base;              //reduces the power variable for the next iteration
    }
    temp[pos] = '\0';
    strcpy(out, temp);
}

void print_tables(uint32_t n) {
    char bin[33], oct[12], hex[9];

    div_convert(n, 2, bin);
    div_convert(n, 8, oct);
    div_convert(n, 16, hex);
    printf("Original: Binary=%s Octal=%s Decimal=%u Hex=%s\n", bin, oct, n, hex);

    uint32_t shifted = n << 3;
    div_convert(shifted, 2, bin);
    div_convert(shifted, 8, oct);
    div_convert(shifted, 16, hex);
    printf("Left Shift by 3: Binary=%s Octal=%s Decimal=%u Hex=%s\n", bin, oct, shifted, hex);

    uint32_t masked = n & 0xFF;
    div_convert(masked, 2, bin);
    div_convert(masked, 8, oct);
    div_convert(masked, 16, hex);
    printf("AND with 0xFF: Binary=%s Octal=%s Decimal=%u Hex=%s\n", bin, oct, masked, hex);
}