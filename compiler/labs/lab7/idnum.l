%{
#include <stdio.h>
%}
%%
[a-zA-Z][a-zA-Z0-9_]* {printf("ID(%s) ", yytext);}
[_]+[a-zA-Z0-9_]+     {printf("ID(%s) ", yytext);}
[/][/].*              {}
\n                    {ECHO;}
[0-9]*                {printf("INT(%s)", yytext);}
[+-][1-9]+[0-9]*      {printf("INT(%s)", yytext);}
.                     {}
[\t ]+                {ECHO;}
[0-9]+[.][0-9]+       {}
["].*["]              {}
['].[']               {}
[0-9]+[a-zA-Z_]+      {}
[^a-zA-Z0-9\n\t ]+[a-zA-Z0-9_]* {}
[_]+[a-zA-Z0-9_]*[^a-zA-Z0-9\n\t ]+[a-zA-Z0-9_]* {}
%%
int yywrap() {
    return 1;
}
int main() {
    yylex();
    return 0;
}
