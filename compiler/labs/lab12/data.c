#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "data.h"

List cons(Data* n, List ls) {
    List newnode = (List)malloc(sizeof *newnode);
    newnode->son = ls;
    newnode->bro = NULL;
    newnode->val = n;
    return newnode;
}

Data *car(List ls){
    if (NULL != ls)
        return ls->val;
    return NULL;
}

List cdr(List ls) {
    if (ls != NULL)
        return ls->son;
    return NULL;
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
List unary(char c, List son) {
    List p = cons(mkchr(c), son);
    p->kind = UNARY;
    return p;
}
void addSon(List parent, List son) {
    if (parent->son == NULL) parent->son = son;
    else addBro(parent->son, son);
}
void addBro(List me, List bro) {
    List temp = me;
    while (temp->bro != NULL) {
       temp = temp->bro;
    }
    temp->bro = bro;
}
List binary(char c, List son1, List son2) {
    addBro(son1, son2);
    List p = cons(mkchr(c), son1);
    p->kind = BINARY;
    return p;
}

void printStack(List head) {
    if (head->son != NULL) {
       printStack(cdr(head));
    }


    if (head->kind == INTVAL) printf("ldc %d\n", car(head)->intval);
    else if (head->kind == UNARY) {
        if (car(head)->opval == '-') printf("neg\n", car(head)->opval);
    }
    else {
         switch(car(head)->opval) {
             case '+': { printf("add\n"); break; }
             case '-': { printf("sub\n"); break; }
             case '*': { printf("mul\n"); break; }
             case '/': { printf("div\n"); break; }
	 }
    }
    if(head->bro != NULL) {
       printStack(head->bro);
    }
}

void printall(List head) {
    static int cnt = 0;
    for (int i = 0; i < cnt; ++i) { printblank(); }
    if (head->kind == INTVAL) printf("%d\n", car(head)->intval);
    else if (head->kind == UNARY) printf("(%c)\n", car(head)->opval);
    else printf("%c\n", head->val->opval);
    if (cdr(head) != NULL) {
       ++cnt;
       printall(cdr(head));
       --cnt;
    }
    if(head->bro != NULL) {
       printall(head->bro);
    }
}
void printblank() {
    printf("  ");
}

void generateTf(FILE* fp, List head) {
    if (head->son != NULL) {
       generateTf(fp, cdr(head));
    }


    if (head->kind == INTVAL) fprintf(fp, "ldc %d\n", car(head)->intval);
    else if (head->kind == UNARY) {
        if (car(head)->opval == '-') fprintf(fp, "neg\n", car(head)->opval);
    }
    else {
         switch(car(head)->opval) {
             case '+': { fprintf(fp, "add\n"); break; }
             case '-': { fprintf(fp, "sub\n"); break; }
             case '*': { fprintf(fp, "mul\n"); break; }
             case '/': { fprintf(fp, "div\n"); break; }
	 }
    }
    if(head->bro != NULL) {
       generateTf(fp, head->bro);
    }
}
