%{
#include <stdlib.h> // atoi
#include "y.tab.h"
%}
alpha [a-zA-Z]+
num   [0-9]+
%%
{num}     { yylval.ival = atoi(yytext); return NUM; }
{alpha}   { yylval.sval = yytext; return NAME; }
"+"       { yylval.cval = yytext[0]; return '+'; }
"-"       { yylval.cval = yytext[0]; return '-'; }
"*"       { yylval.cval = yytext[0]; return '*'; }
"/"       { yylval.cval = yytext[0]; return '/'; }
"%"       { yylval.cval = yytext[0]; return '%'; }
"("       { return '('; }
")"       { return ')'; }
[ \t]     { }
\n        { return 0; /* EOI */ }
%%
int yywrap() { return 1; }
