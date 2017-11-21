/*
	DFA by goto statement.

	Regular expression for "(a+b)*a".
*/
#include <stdio.h>

#define FAIL 0;
#define OKAY 1;

int ch;

int dfa()
{
	ch = getchar();
	X:
		if (ch == 'b') {
			ch = getchar();
			goto X;
                else if (ch == 'a') {
                        ch = getchar();
                        goto Y;
		} else return FAIL;

	Y:
                if (ch == 'b') {
                        ch = getchar();
                        goto X;
		else if (ch == 'a') {
			ch = getchar();
			goto Y;
		else if (ch == '\n'){
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
