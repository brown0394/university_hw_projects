#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "data.h"

List cons(Data* n, List ls) {
    List newnode = (List)malloc(sizeof *newnode);
    newnode->son = ls;
    newnode->bro = NULL;
    newnode->val = n;
    newnode->kind = EMPTY;
    newnode->gen = -1;
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
    newdata->intval = n;
    return newdata;
}

Data *mkchr(char c) {
    Data* newdata = (Data *)malloc(sizeof *newdata);
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

void generateTf(FILE* fp, List head, TableHead** symtable) {
    if (head->son != NULL) {
       generateTf(fp, cdr(head), symtable);
    }
    switch (head->kind) {
        case INTVAL : { fprintf(fp, "ldc %d\n", car(head)->intval); break; }
        case UNARY : { 
                switch (car(head)->opval) {
                    case '-' : {
                        if (head->gen == -1) {
                            fprintf(fp, "neg\n", car(head)->opval);
                            break;
                        }
                        fprintf(fp, "ldc -1\nadd\nsro %d\n", getIdLoc(symtable, car(head->son)->sval));
                        break;
                    }
                    case '+' : {
                        if (head->gen == -1) break;
                        fprintf(fp, "ldc 1\nadd\nsro %d\n", getIdLoc(symtable, car(head->son)->sval));
                        break;
                    }
                }
                break; 
            }
        case BINARY : {
            switch(car(head)->opval) {
                case '+': { fprintf(fp, "add\n"); break; }
                case '-': { fprintf(fp, "sub\n"); break; }
                case '*': { fprintf(fp, "mul\n"); break; }
                case '/': { fprintf(fp, "div\n"); break; }
                case '=': { if(head->gen == -1) fprintf(fp, "sro %d\n", getIdLoc(symtable, car(head->son)->sval));
                            else fprintf(fp, "equ\n"); break;}
                case '<': { if(head->gen == -1) fprintf(fp, "les\n"); 
                            else fprintf(fp, "leq\n"); break; }
                case '>': { if(head->gen == -1) fprintf(fp, "grt\n"); 
                            else fprintf(fp, "geq\n"); break;}
            }
            break;
        }
        case IDNUM : { if (head->gen == -1)fprintf(fp, "ldo %d\n", getIdLoc(symtable, car(head)->sval)); break;}
        case JMP : { 
            switch(head->gen) {
                case -1 : {fprintf(fp, "l%s: ", head->val->sval); break;}
                case -2 : {fprintf(fp, "fjp l%s\n", head->val->sval); break;}
                case -3 : {fprintf(fp, "%s", head->val->sval); break;}
            }
            
        }
        default : break;
    }

    if(head->bro != NULL) {
       generateTf(fp, head->bro, symtable);
    }
}

void freeTree(List head) {
    if (cdr(head) != NULL) {
       freeTree(cdr(head));
    }
    if(head->bro != NULL) {
       freeTree(head->bro);
    }
    free(head);
}

Data *mkstr(char *s) {
    Data* newdata = (Data *)malloc(sizeof *newdata);
    newdata->sval = (char *)calloc(strlen(s)+1, 1);
    strcpy(newdata->sval, s);
    return newdata;
}

int tbidxCheck(char a) {
    if (a == '_') return 26;
    if (a < 'a') a += 32;
    return a - 'a';
}

TableList tcons(Data *n, TableList ls) {
    TableList newnode = (TableList)malloc(sizeof *newnode);
    newnode->id = n;
    newnode->nxt = ls;
    newnode->sploc = -1;
    return newnode;
}

void putInTable(TableHead** symtable, Data *id, int *loc) {
    int idx = tbidxCheck(id->sval[0]);
    if (symtable[idx] == NULL) {
        symtable[idx] = (TableHead*)malloc(sizeof(*symtable[idx]));
        symtable[idx]->nxt = tcons(id, NULL);
        symtable[idx]->last = symtable[idx]->nxt;
        symtable[idx]->nxt->sploc = (*loc)++;
    }
    else {
        TableList ls = checkTable(symtable, id->sval);
        if (ls == NULL) {
            symtable[idx]->last->nxt = tcons(id, NULL);
            symtable[idx]->last = symtable[idx]->last->nxt;
            symtable[idx]->last->sploc = (*loc)++;
        }
    }
}

TableList checkTable(TableHead** symtable, char *id) {
    int idx = tbidxCheck(id[0]);
    TableList cur = symtable[idx]->nxt;

    while (cur != NULL) {
        if (strcmp(cur->id->sval, id) == 0) {
            return cur;
        }
        cur = cur->nxt;
    }
    return NULL;
}

int getIdLoc(TableHead** symtable, char *id) {
    TableList ls = checkTable(symtable, id);
    return ls->sploc;
}