%{
#include <stdio.h>

int tok_cnt = 0;
%}
%%
[a-zA-Z]*	{tok_cnt++;}
[0-9]*	{tok_cnt++;}
[()]	{tok_cnt++;}
[%*+-/]	{tok_cnt++;}
[<=>]	{tok_cnt++;}
[<][=]	{tok_cnt++;}
[>][=]	{tok_cnt++;}
[+-][0-9]*	{tok_cnt++;}
.	{}
\n	{}
%%
int yywrap() {
    return 1;
}
int main() {
    yylex();
    printf("%d\n", tok_cnt);
}
