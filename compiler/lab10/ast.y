%{
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    int yyerror(const char *msg), yylex();
    struct Data;
    typedef struct Data Data;

    struct Node;
    typedef struct Node Node;
    typedef struct Node *List;

    typedef enum {INT, OP, DBL} TAG;
    typedef enum {UNARY, BINARY, TERMINAL} NKind;

    struct Node {
       NKind kind;
       Data *val;
       List son;
       List bro;
    };

    struct Data {
       TAG tag;
       char opval;
       union {
       int intval;
       double dval;
       };
    };

    List cons(Data *n, List ls);
    void addSon(List parent, List son);
    void addBro(List me, List bro);

    Data *mkint(int n);
    Data *mkchr(char c);
    Data *mkdbl(double d);

    List unary(List p, List son);
    List binary(List p, List son1, List son2);

    List head = NULL;
    void printall(List head);
    void printblank();

    void add(List l);
    void sub(List l);
    void mul(List l);
    void divide(List l);
    void mod(List l);
    void negate(List l);
    void printResult(List l);
    void freeTree(List head);
%}
%union {
    struct Node *pval;
    int   ival;
    double dval;
}
%token<dval> DOUBLE
%token<ival> NUM
%token<pval> ADD SUB MUL DIV MOD
%type<pval> E T F
%%
E     : E ADD T   { $$ = binary($2, $1, $3); add($$); head = $$; }
      | E SUB T   { $$ = binary($2, $1, $3); sub($$); head = $$; }
      | T         { $$ = $1; head = $$; }
      ;
T     : T MUL F   { $$ = binary($2, $1, $3); mul($$); }
      | T DIV F   { $$ = binary($2, $1, $3); divide($$); }
      | T MOD F   { $$ = binary($2, $1, $3); mod($$); }
      | F         { $$ = $1; }
      ;
F     : NUM       { $$ = cons(mkint($1), NULL); $$->kind = TERMINAL; }
      | DOUBLE    { $$ = cons(mkdbl($1), NULL); $$->kind = TERMINAL; }
      | SUB F     { $$ = unary($1, $2); negate($$);}
      | ADD F     { $$ = unary($1, $2); }
      | '('E')'   { $$ = $2; }
      ;

%%
int main() { 
   yyparse();
   printall(head);
   printResult(head);
   freeTree(head);
   return 0;
}
int yyerror(const char *msg) { fputs(msg, stderr); }
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

Data *mkdbl(double d) {
    Data* newdata = (Data *)malloc(sizeof *newdata);
    newdata->tag = DBL;
    newdata->dval = d;
    return newdata;
}

List unary(List p, List son) {
    p->kind = UNARY;
    addSon(p, son);
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
List binary(List p, List son1, List son2) {
    p->kind = BINARY;
    addBro(son1, son2);
    addSon(p, son1);
    return p;
}
void printall(List head) {
    static int cnt = 0;
    for (int i = 0; i < cnt; ++i) { printblank(); }
    switch (head->kind) {
        case TERMINAL : {
            switch(head->val->tag) {
               case INT : { printf("%d\n", head->val->intval); break; }
               case DBL : { printf("%.2f\n", head->val->dval); break; }
            }
            break;
        }
        case UNARY : {printf("(%c)\n", head->val->opval); break; }
        case BINARY : {printf("%c\n", head->val->opval); break; }
    }

    if (head->son != NULL) {
       ++cnt;
       printall(head->son);
       --cnt;
    }
    if(head->bro != NULL) {
       printall(head->bro);
    }
}
void printblank() {
    printf("  ");
}

void add(List l) {
   List son1 = l->son;
   List son2 = son1->bro;
   if (son1->val->tag == son2->val->tag) {
       if (son1->val-> tag == INT) {
           l->val->intval = son1->val->intval + son2->val->intval;
           l->val->tag = INT;
       }
       else {
           l->val->dval = son1->val->dval + son2->val->dval;
           l->val->tag = DBL;
       }
   }
   else {
       switch (son1->val->tag) {
          case INT : { l->val->dval = son1->val->intval + son2->val->dval; break; }
          case DBL : { l->val->dval = son1->val->dval + son2->val->intval; break; }
       }
       l->val->tag = DBL;
   }
}

void sub(List l) {
   List son1 = l->son;
   List son2 = son1->bro;
   if (son1->val->tag == son2->val->tag) {
       if (son1->val-> tag == INT) {
           l->val->intval = son1->val->intval - son2->val->intval;
           l->val->tag = INT;
       }
       else {
           l->val->dval = son1->val->dval - son2->val->dval;
           l->val->tag = DBL;
       }
   }
   else {
       switch (son1->val->tag) {
          case INT : { l->val->dval = son1->val->intval - son2->val->dval; break; }
          case DBL : { l->val->dval = son1->val->dval - son2->val->intval; break; }
       }
       l->val->tag = DBL;
   }
}

void mul(List l) {
   List son1 = l->son;
   List son2 = son1->bro;
   if (son1->val->tag == son2->val->tag) {
       if (son1->val-> tag == INT) {
           l->val->intval = son1->val->intval * son2->val->intval;
           l->val->tag = INT;
       }
       else {
           l->val->dval = son1->val->dval * son2->val->dval;
           l->val->tag = DBL;
       }
   }
   else {
       switch (son1->val->tag) {
          case INT : { l->val->dval = son1->val->intval * son2->val->dval; break; }
          case DBL : { l->val->dval = son1->val->dval * son2->val->intval; break; }
       }
       l->val->tag = DBL;
   }
}

void divide(List l) {
   List son1 = l->son;
   List son2 = son1->bro;
   if (son1->val->tag == son2->val->tag) {
       if (son1->val-> tag == INT) {
           l->val->dval = son1->val->intval / (double)son2->val->intval;
           l->val->tag = DBL;
       }
       else {
           l->val->dval = son1->val->dval / son2->val->dval;
           l->val->tag = DBL;
       }
   }
   else {
       switch (son1->val->tag) {
          case INT : { l->val->dval = son1->val->intval / son2->val->dval; break; }
          case DBL : { l->val->dval = son1->val->dval / son2->val->intval; break; }
       }
       l->val->tag = DBL;
   }
}

void mod(List l) {
   List son1 = l->son;
   List son2 = son1->bro;
   if (son1->val->tag == son2->val->tag) {
       if (son1->val-> tag == INT) {
           l->val->intval = son1->val->intval % son2->val->intval;
           l->val->tag = INT;
       }
       else {
           l->val->intval = (int)son1->val->dval % (int)son2->val->dval;
           l->val->tag = INT;
       }
   }
   else {
       switch (son1->val->tag) {
          case INT : { l->val->intval = son1->val->intval % (int)son2->val->dval; break; }
          case DBL : { l->val->intval = (int)son1->val->dval % son2->val->intval; break; }
       }
       l->val->tag = INT;
   }
}


void negate(List l) {
   switch (l->son->val->tag) {
      case INT : { l->val->intval = ~(l->son->val->intval) + 1; l->val->tag = INT; break; }
      case DBL : { l->val->dval = l->son->val->dval * -1; l->val->tag = DBL; break; }
   }
}

void printResult(List l) {
    switch (l->val->tag) {
      case INT : { printf("%d\n", l->val->intval); break; }
      case DBL : { printf("%f\n", l->val->dval); break; }
   }
}

void freeTree(List head) {
    if (head->son != NULL) {
       freeTree(head->son);
    }
    if(head->bro != NULL) {
       freeTree(head->bro);
    }
    free(head->val);
    free(head);
}
