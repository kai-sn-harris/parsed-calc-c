#pragma once

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

enum tokType { NUM, ADD, SUB, MUL, DIV, END };
typedef enum tokType tokType;

struct Token {
    tokType type;
    int value;
};

typedef struct Token Token;

struct TokArray {
    Token* array;
    size_t used;
    size_t size;
};

typedef struct TokArray TokArray;

void initArray(TokArray* array) {
    array->array = (Token*)malloc(sizeof(Token));
    array->used = 0;
    array->size = 0;
}

void arrayAdd(TokArray* array, Token item) {
    array->size++;
    array->array = (Token*)realloc(array->array, sizeof(Token)*array->size);
    array->array[array->used] = item;
    array->used++;
}

void freeArray(TokArray* array) {
    free(array->array);
    array->array = NULL;
    array->used = array->size = 0;
}

TokArray lex(const char *input) {
    TokArray toks;
    initArray(&toks);
    for(int i = 0; i < strlen(input); i++) {
        // is a number
        if(input[i] <= 57 && input[i] >= 48) {
            char* raw = (char*)malloc(10*sizeof(char));
            raw[0] = '\0';
            int j = i;
            while(input[j] <= 57 && input[j] >= 49) {
                strncat(raw, &input[j], 1);
                j++;
            }
            // j lands on the + char in the equation 32+32 for example, so sub 1 to account for this
            i = j-1;
            Token num;
            num.value = atoi(raw);
            free(raw);
            num.type = NUM;
            arrayAdd(&toks, num);
            continue;
        }
        Token op;
        op.value = -1;
        if(input[i] == '+') op.type = ADD;
        if(input[i] == '-') op.type = SUB;
        if(input[i] == '*') op.type = MUL;
        if(input[i] == '/') op.type = DIV;
        arrayAdd(&toks, op);
    }
    return toks;
}