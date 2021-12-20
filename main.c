#include <stdio.h>
#include "interpreter.h"
#include "string.h"

int main(int argc, char *argv[]) {
    if(argc == 1) {
        printf("Error: must supply equation to be solved");
        exit(EXIT_FAILURE);
    }

    int strsize = 0;
    for(int i = 1; i < argc; i++)
        strsize += strlen(argv[i]);

    char* input = (char*)malloc(sizeof(char)*(strsize));
    input[0] = '\0';
    for(int i = 1; i < argc; i++)
        strcat(input, argv[i]);
    input[strsize] = '\0';
    
    printf("%s = %.6f\n", input, calc(input));
    freeArray(&toks);
    free(input);
}