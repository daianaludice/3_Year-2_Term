* smallsh.h - defs for smallsh command processor */
#include <stdio.h>
#include <unistd.h>

#define EOL 1     /* 줄의 끝 */
#define ARG 2     /* 정상적 인수 */
#define AMPERSAND 3
#define SEMICOLON 4
#define INTERRUPT 5

#define MAXARG 512  /* 명령인수의 최대수 */
#define MAXBUF 512  /* 입력줄의 최대길이*/

#define FOREGROUND 0
#define BACKGROUND 1

#define END_CMD "goodbye"