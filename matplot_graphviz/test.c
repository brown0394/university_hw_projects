#include <stdio.h>
#include <string.h>
#include "data.h"

TableHead *table[27];

int main(void) {
    int loc = 0;
    List id = cons(mkstr("ab"), NULL);
    id->kind = IDNUM;
    List id2 = cons(mkstr("ab"), NULL);
    id2->kind = IDNUM;
    List incr = cons(mkchr('-'), NULL);
    incr->kind = UNARY; incr->gen = 0;
    List decr = cons(mkchr('+'), NULL);
    decr->kind = UNARY; decr->gen = 0;

    putInTable(table, id->val, &loc);

    incr->son = id;
    decr->son = id2;
    List head;
    head = cons(NULL, NULL);
    List cur = head;

    cur->son = incr;
    cur->bro = cons(NULL, NULL);
    cur = cur->bro;
    cur->son = decr;
    FILE *fp;
    fp  = fopen("test.t", "w");
    generateTf(fp, head, table);
    
}