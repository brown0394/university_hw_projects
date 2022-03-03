D [0-9]
L [a-zA-Z_]
%{

#include <stdio.h>
#include "y.tab.h"
void

%}

 

%%

"/*" { comment(); }
"break" { return(BREAK); }
"else" { return(ELSE); }
"for" { return(FOR); }
"if" { return(IF); }
"int" { return(INT); }
"return" { return(RETURN); }
"void" { return(VOID); }
"while" { return(WHILE); }

{L}({L}|{D})* { return(IDENTIFIER); }
{D}+ { return(CONSTANT); }


"..." { return(ELLIPSIS); }

"+=" { return(ADD_ASSIGN); }
"-=" { return(SUB_ASSIGN); }
"*=" { return(MUL_ASSIGN); }
"/=" { return(DIV_ASSIGN); }
"%=" { return(MOD_ASSIGN); }
"&=" { return(AND_ASSIGN); }
"^=" { return(XOR_ASSIGN); }
"|=" { return(OR_ASSIGN); }


"++" { return(INC_OP); }
"--" { return(DEC_OP); }
"->" { return(PTR_OP); }
"&&" { return(AND_OP); }
"||" { return(OR_OP); }
"<=" { return(LE_OP); }
">=" { return(GE_OP); }
"==" { return(EQ_OP); }
"!=" { return(NE_OP); }
";" { return(';'); }

("{"|"<%") { return('{'); }
("}"|"%>") { return('}'); }
"," { return(','); }
":" { return(':'); }
"=" { return('='); }
"(" { return('('); }
")" { return(')'); }

("["|"<:") { return('['); }
("]"|":>") { return(']'); }

"." { return('.'); }
"&" { return('&'); }
"!" { return('!'); }
"~" { return('~'); }
"-" { return('-'); }
"+" { return('+'); }
"*" { return('*'); }
"/" { return('/'); }
"%" { return('%'); }
"<" { return('<'); }
">" { return('>'); }
"^" { return('^'); }
"|" { return('|'); }
"?" { return('?'); }

[ \t\v\n\f] { }

%%

 

yywrap() { return(1); }

comment() { 
    char c, c1;
    loop:
    while ((c = input()) != '*' && c != 0)
        putchar(c);
    if ((c1 = input()) != '/' && c != 0) {
        unput(c1);
        goto loop;
    }
    if (c != 0)
        putchar(c1);
}
