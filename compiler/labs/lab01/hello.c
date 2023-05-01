#include <stdio.h>

int main(){
	int a;
	scanf("%d", &a);
	int b = a + 2;
	int c = b + 2;
	printf("t(%d) = %d\nt(%d) = %d\n", a, b, a, c);
	return 0;
}
