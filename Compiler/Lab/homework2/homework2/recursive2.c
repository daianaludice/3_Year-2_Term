/*
Identifier list - Recursive Descent

E -> E + T | T
T -> T * F | F
F -> ( E ) | a

우순환

E -> TE'
E' -> +TE' | ℇ
T -> FT'
T' -> *FT' | ℇ
F -> (E) | a
*/

#include <stdio.h>

char ch;
int errflag = 0;

void error() {
	if (!errflag) {
		puts("FAIL");
		errflag = 1;
	}
}

void pplus() {
	if (ch == '+')
		ch = getchar();
	else error();
}

void pmult() {
	if (ch == '*')
		ch = getchar();
	else error();
}


void pleft() {
	if (ch == '(')
		ch = getchar();
	else error();
}

void pright() {
	if (ch == ')')
		ch = getchar();
	else error();
}

void pa() {
	if (ch == 'a')
		ch = getchar();
	else error();
}


// E -> TE'
void pE() {
	void pT(), pEP();
	if (ch == '(' || ch == 'a') {
		pT(); pEP();
	}
	else error();
}

/*
E' --> +TE'
E' --> ℇ
*/
void pEP() {
	void pplus(), pT(), pEP();
	if (ch == '+') {
		pplus(); pT(); pEP();
	}
	else if (ch == ')' || ch == '$' || ch == '\n') {
		;
	}
	else error();
}


//    T -> FT'
void pT() {
	void pF(), pTP();
	if (ch == '(' || ch == 'a') {
		pF(); pTP();
	}
	else error();
}

/*
T' -> *FT'
T' -> ℇ
*/
void pTP() {
	void pmult(), pF(), pTP();
	if (ch == '*') {
		pmult(); pF(); pTP();
	}
	else if (ch == '+' || ch == '$' || ch == ')' || ch == '\n') {
		;
	}
	else error();
}

/*
F -> (E)
F -> a
*/
void pF() {
	void pleft(), pE(), pright(), pa();
	if (ch == '(') {
		pleft(); pE(); pright();
	}
	else if (ch == 'a') {
		pa();
	}
	else error();
}


void main() {
	puts("Production Rules : ");
	puts("\t E -> E + T | T");
	puts("\t T -> T * F | F");
	puts("\t F -> ( E ) | a");
	printf("$로 끝나는 string 입력 : ");

	ch = getchar();
	pE();

	if (!errflag && (ch == '$' || ch == '\n')) puts("OK");
	else error();
}