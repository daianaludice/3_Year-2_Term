/*
   DFA by goto statement.

   Regular expression for "a+b+".
*/
#include <stdio.h>

#define FAIL 1;
#define OKAY 0;

int ch;

int dfa()
{
   ch = getchar();
   S:
      if (ch == 'a') {
         ch = getchar();
         goto A;
      } else return FAIL;
   A:
      if (ch == 'a') {
         ch = getchar();
         goto A;
      } else if (ch == 'b') {
         ch = getchar();
         goto B;
      } else return FAIL;
   B:
      if (ch == 'b') {
         ch = getchar();
         goto B;
      } else if (ch == '\n') {
         return OKAY;
      }
      else return FAIL;

}

main()
{
   if (dfa())
      puts("OK");
   else puts("FAIL");
}