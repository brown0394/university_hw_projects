%{
    #include "y.tab.h"
%}
digit      [0-9]
space      [ \t]
charac     [a-zA-Z_]
idchar     [0-9a-zA-Z_]
%%
"+"        { return '+'; }
"-"        { return '-'; }
"*"        { return '*'; }
"/"        { return '/'; }
"%"	   { return '%'; }
";"        { return ';'; }
"=="       { return(equal); }
"!="       { return(nequal); }
"<"        { return '<'; }
">"        { return '>'; }
"<="       { return(lequal); }
">="       { return(bequal); }
"("        { return '('; }
")"        { return ')'; }
"int"      { return(INT); }
"quit"     { return 0; }
{digit}+   { yylval.sval = yytext; return(NUM); }
{space}+   { }
{charac}+{idchar}*  { yylval.sval = yytext; return(ID); }
\n         { }
%%
int yywrap() { return 1; }
