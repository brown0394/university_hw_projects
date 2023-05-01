#include <stdio.h>

int main() {
    int a[] = {1, 2, 3};

    printf("%d", sizeof(a) / sizeof(a[0]));


}