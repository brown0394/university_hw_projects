MiniC
                                                               최성찬
                                                               2021.12.15
1. SYNOPSIS
C를 모방한 간단한 기능만을 가진 컴파일러 입니다.

2. FILES
cgen.l - scanner 기능을 하는 lex파일
cgen.y - parser 기능을 하는 bison 파일
data.h - code generation에 필요한 함수들을 정의
data.c -  code generation에 필요한 함수들을 구현

3. HOW TO BUILD
동봉된 Makefile을 make 명령어를 통해 실행시키면 cgen.exe 프로그램이
생성된다. 이후 동봉된 a.txt 파일을 ./cgen < a.txt와 같은 명령어로
실행시키면 cgen.t 파일이 생성되고 이를 TVM을 통해 실행해볼 수 있다.
실행시 tvm -s cgen.t를 사용하면 진행과정을 확인할 수 있다.