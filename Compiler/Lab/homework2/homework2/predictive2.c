/*
Predictive parser
2017.11.03 by Kang, Seung-Shik at Kookmin University
*/
#include <stdio.h>
#include <string.h>

#define NONTERMINALS 5
#define TERMINALS 5
#define RULESIZE 8
#define MAX 100

#define INPUT_END_MARK ('a'+TERMINALS)
#define STACK_BOTTOM_MARK '_'

char create_rule[RULESIZE][MAX];
int parsing_table[NONTERMINALS][TERMINALS + 1];
char stack[999];
int top;

void initTable(int parsing_table[NONTERMINALS][TERMINALS + 1])
{
	for (int i = 0; i < NONTERMINALS; i++)
	{
		for (int j = 0; j < TERMINALS + 1; j++)
		{
			parsing_table[i][j] = -1;
		}
	}
}

void replace_char(char *str, int len)
{
	for (int i = 0; i<len; i++)
	{
		if (str[i] == '+')
			str[i] = 'b';
		else if (str[i] == '*')
			str[i] = 'c';
		else if (str[i] == '(')
			str[i] = 'd';
		else if (str[i] == ')')
			str[i] = 'e';
	}
}

void input_data(char *str)
{
	int len;

	printf("Input'a+(a+a*(a+a))*a+(a)' : ");
	scanf("%s", str);
	len = strlen(str);

	replace_char(str, len);

	str[len] = INPUT_END_MARK;
	str[len + 1] = 0;
	printf("Input string : %s (%c is an endig mark)\n", str, INPUT_END_MARK);
}

/*
������Ģ
G = ({E, T, F}, {a, (, ), +, *}, P, E)
P: E -> E + T
E -> T
T -> T * F
T -> F
F -> (E)
F -> a

remove left-recursion
G = ({E, E', T, T', F}, {a, (, ), +, *}, P, E)

P : 0.E -> TE'
1.E' -> +TE'
2.E' -> ��
3.T -> FT'
4.T' -> *FT'
5.T'-> ��
6.F -> (E)
7.F -> a

���ڸ� �ε����� ǥ���ϱ� ���Ͽ� �Ʒ��� ���� ���ʴ�� A, B..nonterminal �̸� ����.

P : 0.A -> CB
1.B -> bCB
2.B -> ��
3.C -> ED
4.D -> cED
5.D -> ��
6.E -> dAe
7.E -> a
*/
void load_create_rule()
{
	strcpy(create_rule[0], "CB");
	strcpy(create_rule[1], "bCB");
	strcpy(create_rule[2], "");
	strcpy(create_rule[3], "ED");
	strcpy(create_rule[4], "cED");
	strcpy(create_rule[5], "");
	strcpy(create_rule[6], "dAe");
	strcpy(create_rule[7], "a");
}

/*
Vn/Vt |	a	b	c	d	e	$
----------------------------------------
A	 |	0	-1	-1	0	-1	-1
B	 |	-1	1	-1	-1	2	2
C	 |	3	-1	-1	3	-1	-1
D	 |	-1	5	4	-1	5	5
E	 |	7	-1	-1	6	-1	-1

���� ��Ģ�� ���� ��ĭ�� -1 �� ǥ��.

P : 0.A -> CB
1.B -> bCB
2.B -> ��
3.C -> ED
4.D -> cED
5.D -> ��
6.E -> dAe
7.E -> a
*/
void load_parsing_table()
{
	parsing_table[0][0] = 0;
	parsing_table[0][3] = 0;
	parsing_table[1][1] = 1;
	parsing_table[1][4] = 2;
	parsing_table[1][5] = 2;
	parsing_table[2][0] = 3;
	parsing_table[2][3] = 3;
	parsing_table[3][1] = 5;
	parsing_table[3][2] = 4;
	parsing_table[3][4] = 5;
	parsing_table[3][5] = 5;
	parsing_table[4][0] = 7;
	parsing_table[4][3] = 6;
}

char stack_top()
{
	return stack[top - 1];
}

void push(char ch)
{
	stack[top++] = ch;
}

void pop()
{
	top--;
}

void init_stack()
{
	top = 0;
	push(STACK_BOTTOM_MARK);
	push('A');
}

int is_nonterminal(char ch)
{
	if ('A' <= ch && ch <= 'Z') return 1;
	else return 0;
}

int is_terminal(char ch)
{
	return (is_nonterminal(ch) == 0);
}

void predictive_parsing(int table[NONTERMINALS][TERMINALS + 1], char rule[RULESIZE][MAX], char *input)
{
	char *p = input;
	char *str_p;
	int i, index = 0, len;

	while (1) {
		if (stack_top() == STACK_BOTTOM_MARK) {
			if (*p == INPUT_END_MARK)
				printf("[accept]\n");	// parsing OK
			else printf("[error] -- Input is not empty!\n");
			return;
		}

		if (is_terminal(stack_top())) {	// pop -- terminal symbol
			if (*p == stack_top()) {
				pop();
				p++;
			}
			else {
				printf("[error] -- Stack is not empty!\n");
				return;
			}
		}
		else { // expand -- nonterminal
			index = parsing_table[stack_top() - 'A'][*p - 'a'];
			if (index != -1) {
				str_p = rule[index];
				len = strlen(str_p);
				printf("[CFG %d] %c -> %s\n", index, stack_top(), str_p);
				pop();
				for (i = len - 1; i >= 0; i--) {
					push(str_p[i]);
				}
			}
			else { // error
				printf("[error] %c -> %c\n", stack_top(), *p);
				return;
			}
		}
	}
}

int main()
{
	char input[100];

	initTable(parsing_table);

	load_create_rule();
	load_parsing_table();

	input_data(input);
	init_stack();

	predictive_parsing(parsing_table, create_rule, input);
	system("pause");
	return 0;
}