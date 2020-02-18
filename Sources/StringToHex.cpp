#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <strsafe.h>
#pragma warning(disable:4996)




char CharToHex(const char str) {

    switch (str) {

    case '1':

        return 1;

        break;

    case '2':

        return 2;

        break;
    case '3':

        return 3;

        break;

    case '4':

        return 4;

        break;
    case '5':

        return 5;

        break;
    case '6':

        return 6;

        break;
    case '7':

        return 7;

        break;
    case '8':

        return 8;

        break;

    case '9':

        return 9;

        break;

    case 'A':

        return 10;

        break;

    case 'B':

        return 11;

        break;

    case 'C':

        return 12;

        break;

    case 'D':

        return 13;

        break;

    case 'E':

        return 14;

        break;
    case 'F':

        return 15;

        break;
    }

    return 0;
}

unsigned long long int StringToHex(const char* str) {

    int size = 1;

    for (int i = 0; str[i] != 0; i++) {
        size = i;
    }

    unsigned long long int value = 0;

    for (int i = size; i >= 0; i--) {

        switch (str[i]) {

        case '1':

            value += (unsigned long long int)(pow(16.0, (double)(size - i))) * 1;

            break;

        case '2':

            value += (unsigned long long int)(pow(16.0, (double)(size - i))) * 2;

            break;
        case '3':

            value += (unsigned long long int)(pow(16.0, (double)(size - i))) * 3;

            break;

        case '4':

            value += (unsigned long long int)(pow(16.0, (double)(size - i))) * 4;

            break;
        case '5':

            value += (unsigned long long int)(pow(16.0, (double)(size - i))) * 5;

            break;
        case '6':

            value += (unsigned long long int)(pow(16.0, (double)(size - i))) * 6;

            break;
        case '7':

            value += (unsigned long long int)(pow(16.0, (double)(size - i))) * 7;

            break;
        case '8':

            value += (unsigned long long int)(pow(16.0, (double)(size - i))) * 8;

            break;

        case '9':

            value += (unsigned long long int)(pow(16.0, (double)(size - i))) * 9;

            break;

        case 'A':

            value += (unsigned long long int)(pow(16.0, (double)(size - i))) * 10;

            break;

        case 'B':

            value += (unsigned long long int)(pow(16.0, (double)(size - i))) * 11;

            break;

        case 'C':

            value += (unsigned long long int)(pow(16.0, (double)(size - i))) * 12;

            break;

        case 'D':

            value += (unsigned long long int)(pow(16.0, (double)(size - i))) * 13;

            break;

        case 'E':

            value += (unsigned long long int)(pow(16.0, (double)(size - i))) * 14;

            break;
        case 'F':

            value += (unsigned long long int)(pow(16.0, (double)(size - i))) * 15;

            break;

        }

    }

    return value;

}


void Scan(FILE* file, const char* str, int strsize) {

    char value[3] = "";
    int i2 = 0;

    for (int i = 0; i < strsize; i++) {

        value[i2] = str[i];
        i2++;

        if (i2 == 2) {

            fprintf(file, "%c", StringToHex(value));
            i2 = 0;

        }

        else if (i == strsize - 1 && i2 % 2 != 0) {
            fprintf(file, "%c", CharToHex(str[i])*16);
        }

    }

}

void Copy(const char* str, char* str2, int str2size) {

    for (int i = 0; i < str2size; i++)
        str2[i] = 0;

    for (int i = 0; i < str2size; i++)
        str2[i] = str[i];


}
void OutPutName(const char* str, char* output, int outputsize) {

    
    int size = 1;

    for (int i = 0; str[i] != 0; i++) {
        size = i;
    }

    if (size + 4 >= outputsize) {
        Copy("__OutOfName__.err.mp", output, outputsize);
        return;
    }

    for (int i2 = 0; i2 < size + 1; i2++) {
        output[i2] = str[i2];
    }

    output[size + 1] = '.';
    output[size + 2] = 'm';
    output[size + 3] = 'p';
    output[size + 4] = 0;

}

int main(int argc, char** argv){

    if (argc != 2)return 0;
    
    FILE* input;
    FILE* output;
    char* buffer;
    long    numbytes;
    char buf2[196];
    input = fopen(argv[1], "r");
    OutPutName(argv[1], buf2, 196);
    output = fopen(buf2, "w");

    if (input == NULL)return 0;

    fseek(input, 0L, SEEK_END);
    numbytes = ftell(input);

    fseek(input, 0L, SEEK_SET);

    buffer = (char*)calloc(numbytes, sizeof(char));

    if (buffer == NULL)return 0;

    fread(buffer, sizeof(char), numbytes, input);

    Scan(output, buffer, numbytes);

    fclose(input);
    fclose(output);
   

    free(buffer);

    return 0;
}