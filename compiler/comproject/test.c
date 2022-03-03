#include <stdio.h>
#include <string.h>
#include "data.h"


int main(void) {
    char* a = "1";
    char* b = "2";
	Data* data = mkData(mkstr(a));
    Data* data2 = mkData(mkstr(b));
    printf("ldc %s\n", data->sval);
	printf("ldc %s\n", data2->sval);

}