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

bool eof() {
     return LA == EOF;
}

int A(), L(), S();

int main() {
    LA = yylex();
    A();
}

// A: eof | L A
int A() {
    if (eof())
        exit(0);
    else { L(); A (); }
}

// L: S newline
int L() {
    S(); match('\n');
}

// S: ( S ) S | e
int S() {
    if (LA == '(') {
	match('('); S(); match(')'); S();
    }
    else{}
}
