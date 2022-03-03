%{
    #include <stdio.h>
    #include <stdlib.h>
    #include "data.h"
    int yyerror(const char *msg), yylex();
    //List head = NULL;
    FILE* fp;
    Head *table[27];

%}
%union {
    struct Data *data;
    char*  sval;
}
%token INT equal nequal lequal bequal
%token<sval> ID NUM
%type<data> varaiable binaryop assign
%%
statement      : statement expression {}
               | expression {}
               ;
expression     : assign ';' { }
               ;
assign         : ID '=' binaryop {if (updateTable(table, mkData(mkstr($1)), $3) == -1) {yyerror("wrong id\n"); return 0;}}
               | binaryop
               ;
binaryop       : binaryop '+' varaiable  {if ((fprintData(table, fp, $1) && fprintData(table, fp, $3)) == -1) {yyerror("wrong id\n"); return 0;} fprintf(fp, "add\n");}
               | declaration {  }
               | varaiable
               ;
varaiable      : ID         { $$ = mkData(mkstr($1)); }
               | NUM        { $$ = mkData(mkstr($1)); }
               ;

declaration    : INT ID  { putInTable(table, mkstr($2)); }
		  | INT ID '=' NUM   { putInTableV(table, mkstr($2), mkstr($4)); }
		  ;
%%

int main() {
  fp = fopen("cgen.t", "w");
  if(!fp) return 0;
  yyparse();
  
  fprintf(fp, "out\nstop\n");
  fclose(fp);
  return 0;
}
int yyerror(const char *msg) { fputs(msg, stderr); }

