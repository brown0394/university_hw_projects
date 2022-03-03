#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "data.h"

TableList cons(char *id, char* value, TableList ls) {
    TableList newnode = (TableList)malloc(sizeof *newnode);
    newnode->nxt = ls;
    newnode->id = id;
    newnode->val = value;
    return newnode;
}

char *mkstr(char *s) {
    char* newstr = (char *)calloc(strlen(s)+1, 1);
    strcpy(newstr, s);
    return newstr;
}

char *car(TableList ls){
    if (NULL != ls)
        return ls->val;
    return NULL;
}

TableList cdr(TableList ls) {
    if (ls != NULL)
        return ls->nxt;
    return NULL;
}


void addNxt(TableList me, TableList nxt) {
    TableList temp = me;
    while (cdr(temp) != NULL) {
       temp = cdr(temp);
    }
    temp->nxt = nxt;
}

int tbidxCheck(char a) {
    if (a == '_') return 26;
    if (a < 'a') a += 32;
    return a - 'a';
}

void putInTable(TableHead** symtable, char *id) {
    int idx = tbidxCheck(id[0]);
    if (symtable[idx] == NULL) {
        symtable[idx] = (TableHead*)malloc(sizeof(*symtable[idx]));
        symtable[idx]->nxt = cons(id, NULL, NULL);
        symtable[idx]->last = symtable[idx]->nxt;
    }
    else {
        symtable[idx]->last->nxt = cons(id, NULL, NULL);
        symtable[idx]->last = symtable[idx]->last->nxt;
    }
}

void putInTableV(TableHead** symtable, char *id, char *value) {
    int idx = tbidxCheck(id[0]);
    if (symtable[idx] == NULL) {
        symtable[idx] = (TableHead*)malloc(sizeof(*symtable[idx]));
        symtable[idx]->nxt = cons(id, value, NULL);
        symtable[idx]->last = symtable[idx]->nxt;
    }
    else {
        symtable[idx]->last->nxt = cons(id, value, NULL);
        symtable[idx]->last = symtable[idx]->last->nxt;
    }
}

TableList checkTable(TableHead** symtable, char *id) {
    int idx = tbidxCheck(id[0]);
    TableList cur = symtable[idx]->nxt;

    while (cur != NULL) {
        if (strcmp(cur->id, id) == 0) {
            return cur;
        }
        cur = cur->nxt;
    }

    return NULL;
}

Data *mkData(char *s) {
    Data *newdata = (Data*)malloc(sizeof *newdata);
    if (s[0] <= '9' && s[0] >= '0')
        newdata->tag = INTEGER;
    else
        newdata->tag = IDENTIFIER;
    newdata->sval = s;
    return newdata;
}

int fprintData(TableHead** symtable, FILE* fp, Data *data) {
    if (data->tag == INTEGER) {
        fprintf(fp, "ldc %s\n", data->sval);
        return 0;
    }
    TableList search = checkTable(symtable, data->sval);
    if (search != NULL) {
        fprintf(fp, "ldc %s\n", search->val);
        return 0;       
    }
    return -1;
}

int updateTable(TableHead** symtable, Data *id, Data *value) {
    TableList node = checkTable(symtable, id->sval);
    if (node == NULL) return -1;
    if (node->val != NULL) {
        free(node->val);
    }
    node->val = value->sval;

    return 0;
}