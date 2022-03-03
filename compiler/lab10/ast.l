%{
//    #include <stdlib.h>
    #include "y.tab.h"
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
    List consl(Data *n, List ls);
    Data *mkchrl(char c);

%}
digit      [0-9]
space      [ \t]
%%
"+"                     { yylval.pval = consl(mkchrl('+'), NULL); return ADD; }
"-"                     { yylval.pval = consl(mkchrl('-'), NULL); return SUB; }
"%"                     { yylval.pval = consl(mkchrl('%'), NULL); return MOD; }
"*"                     { yylval.pval = consl(mkchrl('*'), NULL); return MUL; }
"/"                     { yylval.pval = consl(mkchrl('/'), NULL); return DIV; }
"("                     { return '('; }
")"                     { return ')'; }
{digit}+                { yylval.ival = atoi(yytext); return NUM; }
{digit}+[.]{digit}+     { yylval.dval = atof(yytext); return DOUBLE; }
{space}+                { }
\n                      { return 0; }
%%
int yywrap() { return 1; }
List consl(Data* n, List ls) {
    List newnode = (List)malloc(sizeof *newnode);
    newnode->son = ls;
    newnode->bro = NULL;
    newnode->val = n;
    return newnode;
}

Data *mkchrl(char c) {
    Data* newdata = (Data *)malloc(sizeof *newdata);
    newdata->opval = c;
    return newdata;
}
