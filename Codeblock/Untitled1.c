#include <stdio.h>

int main(void)
{
  unsigned int uf = 0x0;
 unsigned int sign = uf >> 31;
  unsigned int exp = (uf >> 22) & 0xff;
  unsigned int frac =(~(~0 << 23)) & uf;
  unsigned int reval = 1 << 31;
  printf("%x", sign);
  if (exp == 0xff)
          return reval;
  if (exp == 0)
          return reval;

  exp = exp - 127;
 frac = frac | (1 << 23);




    return 0;
}
