#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int LA = 0;

int yylex() {
    return getchar();
}

void error() {
     fprintf(stderr, "Sytnax error near '%c'\n", LA);
     exit(-1);
}

void match(int tok) {
     if (tok == LA)
	 LA = yylex();
     else
	 error();
}

void matchop(int tok) {
     switch (tok) {
        case '+' : 
	case '-' : 
	case '*' : 
	case '/' :
	case '%' : { LA = yylex(); break; }
        default : error(); break;
     }
}

bool eof() {
     return LA == EOF;
}

int A(), L(), S(), T(), O();

int main() {
    LA = yylex();
    A();
}

// A: eof | L A
// // <A> ::= { <L> } eof
// <A> ::= { <S> newline } eof
int A() {
    while (!eof()) { L(); }//{ S(); match('\n');} // removing l()
    exit(0);
}

// L: S newline
int L() {
    S(); match('\n');
}

// S: ( S ) S | e
// // <S> ::= { '(' <S> ')' }
int S() {
    while (LA == '(') {
	match('('); T(); O(); S(); match(')'); O();
    }
}

int O() {
    while (LA == ' ') {
        match(' '); matchop(LA); match(' '); S(); T();
    }
}

int T() {
    while ((LA >= '0') && (LA <= '9')) {
        match(LA);
    }
    while (((LA >= 'a') && (LA <= 'z')) || ((LA >= 'A') && (LA <= 'Z'))) {
        match(LA);
    }
}
