#pragma once

#include "node.h"
#include "lex.h"

Token curTok;
int tokPos = -1;
TokArray toks;

Token getNextToken() {
    tokPos++;
    curTok = toks.array[tokPos];
    return curTok;
}

void eat(tokType type) {
    if(curTok.type == type)
        curTok = getNextToken();
    else {
        printf("Expected type %d but got type %d\n", type, curTok.type);
        exit(EXIT_FAILURE);
    }
}

// prototype so it can be used before definition
Node AddSubTerm();

Node factor() {
    if(curTok.type == NUM) {
        Node num;
        num.type = N_NUM;
        num.node.num.value = curTok.value;
        curTok = getNextToken();
        return num;
    } else if(curTok.type == LPAREN) {
        eat(LPAREN);
        Node node = AddSubTerm();
        eat(RPAREN);          
        return node;
    } else {
        printf("expected num but u did some dumbass shit lmao %d\n", curTok.type);
        exit(EXIT_FAILURE);
    }
}

Node MulDivTerm() {
    Node num = factor();

    while(curTok.type == MUL || curTok.type == DIV) {
        Node binop;
        binop.type = N_BINOP;
        binop.node.binop.op = curTok.type == MUL ? '*' : '/';
        curTok = getNextToken();
        
        Node *left = NULL;
        left = (Node*)malloc(sizeof(Node));
        *left = num;
        binop.node.binop.left = left;

        Node raw = factor();
        Node *right = NULL;
        right = (Node*)malloc(sizeof(Node));
        *right = raw;
        binop.node.binop.right = right;

        num = binop;
    }
    return num;
}

Node AddSubTerm() {
    Node mulDiv = MulDivTerm();

    while(curTok.type == ADD || curTok.type == SUB) {
        Node binop;
        binop.type = N_BINOP;
        binop.node.binop.op = curTok.type == ADD ? '+' : '-';
        curTok = getNextToken();

        Node *left = NULL;
        left = (Node*)malloc(sizeof(Node));
        *left = mulDiv;
        binop.node.binop.left = left;

        Node raw = MulDivTerm();
        Node *right = NULL;
        right = (Node*)malloc(sizeof(Node));
        *right = raw;
        binop.node.binop.right = right;

        mulDiv = binop;
    }
    return mulDiv;
}

Node parse(const char * input) {
    toks = lex(input);
    curTok = getNextToken();
    return AddSubTerm();
}
