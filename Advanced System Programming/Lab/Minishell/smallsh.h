* smallsh.h - defs for smallsh command processor */
#include <stdio.h>
#include <unistd.h>

#define EOL 1     /* ���� �� */
#define ARG 2     /* ������ �μ� */
#define AMPERSAND 3
#define SEMICOLON 4
#define INTERRUPT 5

#define MAXARG 512  /* ����μ��� �ִ�� */
#define MAXBUF 512  /* �Է����� �ִ����*/

#define FOREGROUND 0
#define BACKGROUND 1

#define END_CMD "goodbye"