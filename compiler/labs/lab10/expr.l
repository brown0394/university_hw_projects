%{
   #include <stdlib.h>
   #include "y.tab.h"
%}
%%
[0-9]+   { yylval.ival = atoi(yytext); return NUM; }
[0-9]+[.][0-9]+[f]? { yylval.dval = atof(yytext); return DOUBLE; }
"+"      { return '+'; }
"-"      { return '-'; }
"*"      { return '*'; }
"/"      { return '/'; }
"++"     { return INCR; }
"--"     { return DECR; }
"$*"     { return POW; }
"$/"     { return SQRT; }
"%"      { return '%'; }
"("      { return '('; }
")"      { return ')'; }
"<<"     { return LSHIFT; }
">>"     { return RSHIFT; }
[ \t]    { }
\n       { return 0; }
%%
int yywrap() { return 1; }
