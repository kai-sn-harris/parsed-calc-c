#pragma once

enum nodeType { N_NUM, N_BINOP };
typedef enum nodeType nodeType;

struct Node {
    nodeType type;
    union {
        struct {
            int value;
        } num;
        struct {
            char op;
            struct Node *left, *right;
        } binop;
    } node;
};

typedef struct Node Node;