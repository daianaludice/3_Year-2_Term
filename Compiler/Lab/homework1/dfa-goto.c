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
	A:
		if (ch == 'a') {
			ch = getchar();
			goto A;
                if (ch == 'b') {
                        ch = getchar();
                        goto A;
		} else return FAIL;

	B:
		if (ch == '\n') {
			return OKAY;
		} else return FAIL;

}

main()
{
	if (dfa())
		puts("OK");
	else puts("FAIL");
}
