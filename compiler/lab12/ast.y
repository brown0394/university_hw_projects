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

    typedef enum {INT, OP, LST} TAG;
    typedef enum {UNARY, BINARY, INTVAL} NKind;

    struct Node {
       NKind kind;
       Data *val;
       List son;
       List bro;
    };

    struct Data {
       TAG tag;
       union {
       int intval;
       char opval;
       };
    };

    List cons(Data *n, List ls);
    void addSon(List parent, List son);
    void addBro(List me, List bro);

    Data *mkint(int n);
    Data *mkchr(char c);

    List unary(List p, List son);
    List binary(List p, List son1, List son2);

    List head = NULL;
    void printall(List head);
    void printblank();
%}
%union {
    struct Node *pval;
    int   ival;
}
%token<ival> NUM
%token<pval> ADD SUB MUL DIV MOD
%type<pval> E T F
%%
E     : E ADD T   { $$ = binary($2, $1, $3); head = $$; }
      | E SUB T   { $$ = binary($2, $1, $3); head = $$; }
      | T         { $$ = $1; head = $$; }
      ;
T     : T MUL F   { $$ = binary($2, $1, $3); }
      | T DIV F   { $$ = binary($2, $1, $3); }
      | T MOD F   { $$ = binary($2, $1, $3); }
      | F         { $$ = $1; }
      ;
F     : NUM       { List newnode = cons(mkint($1), NULL); newnode->kind = INTVAL; $$ = newnode; }
      | SUB F     { $$ = unary($1, $2); }
      | ADD F     { $$ = unary($1, $2); }
      | '('E')'   { $$ = $2; }
      ;

%%
int main() { 
   yyparse();
   printall(head);
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
    if (head->kind == INTVAL) printf("%d\n", head->val->intval);
    else if (head->kind == UNARY) printf("(%c)\n", head->val->opval);
    else printf("%c\n", head->val->opval);
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
