%{
    #include "y.tab.h"
%}
digit      [0-9]
space      [ \t]
%%
"+"        { yylval.cval = '+'; return ADD; }
"-"        { yylval.cval = '-'; return SUB; }
"*"        { yylval.cval = '*'; return MUL; }
"/"        { yylval.cval = '/'; return DIV; }
"("        { return '('; }
")"        { return ')'; }
{digit}+   { yylval.ival = atoi(yytext); return NUM; }
{space}+   { }
\n         { return 0; }
%%
int yywrap() { return 1; }
