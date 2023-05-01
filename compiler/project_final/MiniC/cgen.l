%{
    #include "y.tab.h"
%}
D [0-9]
L [a-zA-Z_]
space      [ \t]
%%
"+"        { return '+'; }
"-"        { return '-'; }
"++"       { return INCR; }
"--"       { return DECR; }
"*"        { return '*'; }
"/"        { return '/'; }
"<"        { return '<'; }
">"        { return '>'; }
"=="       { return EQUAL; }
"<="       { return LEQUAL; }
">="       { return GEQUAL; }
"("        { return '('; }
")"        { return ')'; }
"{"        { return '{'; }
"}"        { return '}'; }
";"        { return ';'; }
"="        { return '='; }
"while"    { return WHILE; }
"quit"     { return 0; }
{D}+   { yylval.ival = atoi(yytext); return NUM; }
{space}+   { }
{L}({L}|{D})* { yylval.sval = yytext; return ID; }

\n         { }
%%
int yywrap() { return 1; }
