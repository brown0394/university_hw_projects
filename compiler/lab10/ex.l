%{
//    #include <stdlib.h>
    #include "y.tab.h"   
%}
digit      [0-9]
alpha      [a-zA-Z]
space      [ \t]
%%
"+"        { return '+'; }
"."        { return '.'; }
{digit}+   { yylval.ival = atoi(yytext); return NUMBER; }
{alpha}+   { yylval.sval = yytext; return NAME; }
{space}+   { }
\n         { return 0; }
%%
int yywrap() { return 1; }
