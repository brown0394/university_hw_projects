%{
#include <stdio.h>
%}
%%
.	ECHO;
\n      { putchar('_') ; ECHO; }
%%
int main() {
  yylex();
  return 0;
}

int yywrap() {
  return 1;
}

