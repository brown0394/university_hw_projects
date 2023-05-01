%{
    #include <stdio.h>
    #include <ctype.h>
    #include <math.h>
    int yylex();
    void yyerror(const char *s);
    int finalval = 0;
    double finalvalf = 0;
    int isdouble = 0;
%}
%union {int ival; double dval;}
%token NUM INCR DECR POW LSHIFT RSHIFT DOUBLE SQRT
%%
E    : E LSHIFT S   { if (isdouble) { yyerror("invalid operand type error"); YYABORT;} else {$<ival>$ = $<ival>1 << $<ival>3; finalval = $<ival>$;} }
     | E RSHIFT S   { if (isdouble) { yyerror("invalid operand type error"); YYABORT;} else {$<ival>$ = $<ival>1 >> $<ival>3; finalval = $<ival>$;} }
     | S            { if (isdouble) {$<dval>$ = $<dval>1; finalvalf = $<dval>$;} else {$<ival>$ = $<ival>1; finalval = $<ival>$; } }
     ;
S    : S '+' T      { if (isdouble) $<dval>$ = $<dval>1 + $<dval>3; else $<ival>$ = $<ival>1 + $<ival>3; }
     | S '-' T      { if (isdouble) $<dval>$ = $<dval>1 - $<dval>3; else $<ival>$ = $<ival>1 - $<ival>3; }
     | T            { if (isdouble) $<dval>$ = $<dval>1; else $<ival>$ = $<ival>1; }
     ;
T    : T '*' F      { if (isdouble) $<dval>$ = $<dval>1 * $<dval>3; else $<ival>$ = $<ival>1 * $<ival>3; }
     | T '/' F      { if (isdouble) $<dval>$ = $<dval>1 / $<dval>3; else $<ival>$ = $<ival>1 / $<ival>3; }
     | T '%' F      { if (isdouble) { yyerror("invalid operand type error"); YYABORT;} else $<ival>$ = $<ival>1 % $<ival>3; }
     | T POW F      { if (isdouble) $<dval>$ = pow($<dval>1, $<dval>3); else $<ival>$ = pow($<ival>1, $<ival>3); }
     | T SQRT F     { if (isdouble) $<dval>$ = pow($<dval>1, 1/$<dval>3); else { yyerror("invalid operand type error"); YYABORT;} }
     | F            { if (isdouble) $<dval>$ = $<dval>1;else $<ival>$ = $<ival>1; }
     ;
F    : NUM          { $<ival>$ = $<ival>1; }
     | DOUBLE       { $<dval>$ = $<dval>1; isdouble = 1;}
     | '-' F        { if (isdouble) $<dval>$ = $<dval>2 * -1; else $<ival>$ = $<ival>2 * -1;}
     | '+' F        { if (isdouble) $<dval>$ = $<dval>2; else $<ival>$ = $<ival>2; }
     | INCR F       { if (isdouble) $<dval>$ = $<dval>2 + 1; else $<ival>$ = $<ival>2 + 1;}
     | DECR F       { if (isdouble) $<dval>$ = $<dval>2 - 1; else $<ival>$ = $<ival>2 - 1;}
     | '('E')'      { if (isdouble) $<dval>$ = $<dval>2; else $<ival>$ = $<ival>2;}
     ;
%%
int main() {
    if(yyparse()){ return 0; }
    if (isdouble) printf("%f\n", finalvalf);
    else printf("%d\n", finalval);
    return 0;
}
void yyerror(const char *msg) {
    fputs(msg, stderr);
}
