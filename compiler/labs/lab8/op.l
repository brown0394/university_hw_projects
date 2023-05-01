%{
#include "y.tab.h"
%}
%%
[0-9]*     { return NUM; }
[+-][0-9]+ { return NUM; }
"+"        { return '+'; }
"-"        { return '-'; }
"*"        { return '*'; }
"/"        { return '/'; }
[ \t]      { }
\n         { return 0; }
%%
int yywrap() { return 1; }
