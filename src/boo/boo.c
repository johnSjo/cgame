#include <stdio.h>

int main()
{
  int foo[100];
  int doo = 12;
  // int *goo = malloc(2000);
  int poo = 2;

  // memset(goo, 1, 2000);

  printf("\nsize: %l", sizeof(foo));
  printf("\nadress: %p", &foo);
  printf("\nsize: %l", sizeof(doo));
  printf("\nadress: %p", &doo);
  // printf("\nsize: %l", sizeof(goo));
  // printf("\nadress: %p", &goo);
  // printf("\ngoo: %p", goo);
  printf("\nsize: %l", sizeof(poo));
  printf("\nadress: %p", &poo);

  return 0;
}