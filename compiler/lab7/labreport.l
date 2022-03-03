%{
#include <stdio.h>
%}
%%
[t][r][u][e]          {printf("LOGIC(%s)", yytext);}
[f][a][l][s][e]       {printf("LOGIC(%s)", yytext);}
[a-zA-Z][a-zA-Z0-9_]* {printf("ID(%s) ", yytext);}
[_]+[a-zA-Z0-9_]+     {printf("ID(%s) ", yytext);}
[/][/].*              {printf("COMMENT(%s)", yytext);}
[0-9]*                {printf("INT(%s)", yytext);}
[0-9]+[.][0-9]+       {printf("FLOAT(%s)", yytext);}
[0-9]+[$][0-9]+       {printf("FRACTION(%s)", yytext);}
[+-][1-9]+[0-9]*      {printf("INT(%s)", yytext);}
[+-][0-9]+[.][0-9]+   {printf("FLOAT(%s)", yytext);}
[0-9]+[a-zA-Z_]+      {}
[\t ]+                {ECHO;}
["].*["]              {printf("STRING(%s)", yytext);}
['].[']               {printf("CHR(%s)", yytext);}
[*][a-zA-Z0-9_]+      {printf("PTR(%s)", yytext);}
[%*+-/]               {printf("MATHOP(%s)", yytext);}
[$][*]                {printf("MATHOP(%s)", yytext);}
[$][/]                {printf("MATHOP(%s)", yytext);}
[!]                   {printf("LOGOP(%s)", yytext);}
[&^|~]                {printf("BITOP(%s)", yytext);}
[&][&]                {printf("LOGOP(%s)", yytext);}
[|][|]                {printf("LOGOP(%s)", yytext);}
[<>]                  {printf("COMP(%s)", yytext);}
[<][=]                {printf("COMP(%s)", yytext);}
[>][=]                {printf("COMP(%s)", yytext);}
[=][=]                {printf("COMP(%s)", yytext);}
[<][<]                {printf("SHIFT(%s)", yytext);}
[>][>]                {printf("SHIFT(%s)", yytext);}
[@]                   {printf("NULL(%s)", yytext);}
\n                    {ECHO;}
.                     {}
%%
int yywrap() {
    return 1;
}
int main() {
    yylex();
    return 0;
}
