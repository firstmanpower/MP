#include <stdio.h>
#include <stdlib.h>

#pragma warning(disable:4996)

int main(int argc, char** argv){

	if (argc != 3)return 0;

    FILE* input;
    FILE* output;
    char* buffer;
    long    numbytes;

    input = fopen(argv[2], "r");
    output = fopen(argv[1], "a");

    if (input == NULL)return 0;

    fseek(input, 0L, SEEK_END);
    numbytes = ftell(input)+1;

    fseek(input, 0L, SEEK_SET);

    buffer = (char*)calloc(numbytes, sizeof(char));

    if (buffer == NULL)return 0;

    fread(buffer, sizeof(char), numbytes, input);
    
    
    buffer[numbytes - 1] = 0;

    fprintf(output, "%s", buffer);

    

    fclose(input);
    fclose(output);
    free(buffer);

    return 0;
}