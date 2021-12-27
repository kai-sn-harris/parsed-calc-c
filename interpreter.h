#pragma once

#include "parser.h"
#include "node.h"

float visit(Node node) {
    if(node.type == N_NUM)
        return (float)node.node.num.value;
    if(node.node.binop.op == '+')
        return visit(*node.node.binop.left) + visit(*node.node.binop.right);
    if(node.node.binop.op == '-')
        return visit(*node.node.binop.left) - visit(*node.node.binop.right);
    if(node.node.binop.op == '*')
        return visit(*node.node.binop.left) * visit(*node.node.binop.right);
    if(node.node.binop.op == '/')
        return visit(*node.node.binop.left) / visit(*node.node.binop.right);
    return -1.0f;
}

float calc(const char* input) {
    return visit(parse(input));
}
