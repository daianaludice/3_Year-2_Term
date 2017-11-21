/*
Identifier list - Recursive Descent

LIST -> LIST , ELEMENT
LIST -> ELEMENT
ELEMENT -> a

우순환

LIST -> ELEMENT LIST'
LIST' -> , ELEMENT LIST'
LIST' -> ℇ
ELEMENT -> a

A -> BC
C -> bBC | ℇ
B -> a
*/

#include <stdio.h>

#define END '\n'

char ch;
int errflag = 0;

/*
Recognition-failed message.
*/
void error()
{
	if (!errflag) {
		puts("FAIL");
		errflag = 1;
	}
}

void pa()
{
	if (ch == 'a')
		ch = getchar();
	else error();
}

void pb()
{
	if (ch == ',')
		ch = getchar();
	else error();
}

// A -> BC
void pA()
{
	void pB(), pC();
	switch (ch) {
	case 'a':
		pB(); pC();
		break;
	default:
		error();
	}
}

// B -> a
void pB()
{
	switch (ch) {
	case 'a':
		pa();
		break;
	default:
		error();
	}
}

/*
C -> bBC
C -> ℇ
*/
void pC()
{
	void pb(), pB(), pC();
	switch (ch) {
	case ',':
		pb(); pB(); pC();
		break;
	case '$':
		break;
	case '\n':
		break;
	default:
		error();
	}
}

void main()
{
	puts("Production Rules:");
	puts("\t LIST -> LIST , ELEMENT ");
	puts("\t LIST -> ELEMENT");
	puts("\t ELEMENT -> a");
	printf("$로 끝나는 string 입력 : ");

	ch = getchar();
	pA();

	if (!errflag && (ch == '$' || ch == '\n')) puts("OK");
	else error();
	getchar();
}