#include "node.h"

List cons(Data* n, List ls) {
    List newnode = (List)malloc(sizeof *newnode);
    newnode->son = ls;
    newnode->bro = NULL;
    newnode->val = n;
    return newnode;
}

Data *mkint(int n) {
    Data* newdata = (Data *)malloc(sizeof *newdata);
    newdata->tag = INT;
    newdata->intval = n;
    return newdata;
}

Data *mkchr(char c) {
    Data* newdata = (Data *)malloc(sizeof *newdata);
    newdata->tag = OP;
    newdata->opval = c;
    return newdata;
}
List negate(List p, List son) {
    son->val->intval *= -1;
    p->kind = UNARY;
    addSon(p, son);
    return p;
}
List positiv(List p, List son) {
    p->kind = UNARY;
    addSon(p, son);
    return p;
}
void addSon(List parent, List son) {
    if (parent->son == NULL) parent->son = son;
    else addBro(parent->son, son);
