#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include "convert.c"

int main() {
    FILE *testFile = fopen("A1_tests.txt", "r");       //opens the test file to read
    FILE *outFile = fopen("output.txt", "w");          //creates an output file to display results

    if (testFile == NULL || outFile == NULL) {                //handles if either files are missing/not correct
        printf("Error: File could not be open or found");
        return 1;
    }

    int testNum = 1;          
    int passCount = 0;            
    char line[256];
    while (fgets(line, sizeof(line), testFile) != NULL) {
        line[strcspn(line, "\n")] = '\0';                     //removes newline

        char *tokens[50];
        int count = 0;

        char *token = strtok(line, " ");        //divides the variables in each line by the " " delimiter and setting them to the tokens array
        while (token != NULL && count < 50) {
            tokens[count++] = token;
            token = strtok(NULL, " ");
        }

        if (count == 0) continue;

        char *endptr;
        char *func = tokens[0];
        char output[256];

        if (strcmp(func, "div_convert") == 0) {             //checks to see which function to call before setting variables and calling the tests to run
            uint32_t num = strtoul(tokens[1], &endptr, 0);
            int base = strtol(tokens[2], &endptr, 0);
            char *expected = tokens[3];                  
            div_convert(num, base, output);
            if (strcmp(output, expected) == 0) {          //compares the outputted string with the expected one to see if it matches
                fprintf(outFile, "Test %d: %s(%u, %d) -> Expected: %s, Got: %s [PASS]\n", testNum, func, num, base, expected, output);
                passCount++;
            } else {
                fprintf(outFile, "Test %d: %s(%u, %d) -> Expected: %s, Got: %s [FAILED]\n", testNum, func, num, base, expected, output);
            } 
        } 
        else if (strcmp(func, "sub_convert") == 0) {         //same as div_convert with the exception of calling sub_convert instead
            uint32_t num = strtoul(tokens[1], &endptr, 0);
            int base = strtol(tokens[2], &endptr, 0);
            char *expected = tokens[3];
            sub_convert(num, base, output);
            if (strcmp(output, expected) == 0) {
                fprintf(outFile, "Test %d: %s(%u, %d) -> Expected: %s, Got: %s [PASS]\n", testNum, func, num, base, expected, output);
                passCount++;
            } else {
                fprintf(outFile, "Test %d: %s(%u, %d) -> Expected: %s, Got: %s [FAILED]\n", testNum, func, num, base, expected, output);
            }
        } 
        else if (strcmp(func, "print_tables") == 0) {
           uint32_t num = strtoul(tokens[1], &endptr, 0);
            char bin[33], oct[12], hex[9];
            char bin1[33], oct1[12], hex1[9];
            char bin2[33], oct2[12], hex2[9];

            div_convert(num, 2, bin);
            div_convert(num, 8, oct);
            div_convert(num, 16, hex);

            uint32_t shifted = num << 3;
            div_convert(shifted, 2, bin1);
            div_convert(shifted, 8, oct1);
            div_convert(shifted, 16, hex1);

            uint32_t masked = num & 0xFF;
            div_convert(masked, 2, bin2);
            div_convert(masked, 8, oct2);
            div_convert(masked, 16, hex2);

            char expected[1024];                     //makes an expected string to compare the output of print_tables to
            snprintf(expected, sizeof(expected),
                "Original: Binary=%s Octal=%s Decimal=%u Hex=%s\n"
                "Left Shift by 3: Binary=%s Octal=%s Decimal=%u Hex=%s\n"
                "AND with 0xFF: Binary=%s Octal=%s Decimal=%u Hex=%s\n",
                bin, oct, num, hex,
                bin1, oct1, shifted, hex1,
                bin2, oct2, masked, hex2 );

            FILE *tmp = freopen("tmp_output.txt", "w", stdout);     //makes a temporary file to write the output of print_tables to
            print_tables(num);
            fflush(stdout);
            freopen("CON", "w", stdout);

            FILE *tmp_read = fopen("tmp_output.txt", "r");          //sets the output of print_tables to a string to compare to expected
            char buffer[1024];
            size_t len = fread(buffer, 1, sizeof(buffer) - 1, tmp_read);
            buffer[len] = '\0';
            fclose(tmp_read);

            if (strcmp(buffer, expected) == 0) {       //compares the two strings to see if they match
                fprintf(outFile, "Test %d: print_tables(%u) -> [FORMATTED OUTPUT CHECK] [PASS]\n", testNum, num);
                passCount++;
            } else {
                fprintf(outFile, "Test %d: print_tables(%u) -> [FORMATTED OUTPUT CHECK] [FAILED]\n", testNum, num);
            }
        }
        testNum++;
    }
    
    fprintf(outFile, "\nSummary: %d/%d tests passed\n", passCount, testNum - 1);

    fclose(outFile);
    fclose(testFile);
    fprintf(stderr, "File was successfully written to.\n");

    return 0;
}