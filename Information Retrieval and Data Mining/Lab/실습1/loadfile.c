/*--------------------------------------------------------------------------
	File-name	: loadFile.c
	Description	: Load a file to memory
	Written-by	: Kang, Seung-Shik
--------------------------------------------------------------------------*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*
	입력 파일 전체를 memory로 load
*/
unsigned char *loadFile(char *filename)
{
	long n;
	unsigned char *p;
	FILE *fp;

	fp = fopen(filename, "rb");	// [주의] 'fp'은 "rb"로 open
	if (!fp) {
		p = (unsigned char *) malloc(strlen(filename)+1);
		strcpy(p, filename);	// file명 자체를 return
		return p;
	}

	fseek(fp, 0L, 2);
	n = ftell(fp);	// n: byte size of file 'fp'
	if (n < 3) return NULL;

	p = (unsigned char *) malloc(n+1);	// memory allocation
	if (p == NULL) return NULL;

//	memset(p, 0, n+1);
	fseek(fp, 0L, 0);
	fread(p, sizeof(unsigned char), n, fp);	// read 'fp' to 'p'
	*(p+n) = '\0';

	fclose(fp);
	return p;
}

/*
	8 진수로 출력
*/
void put_octal(char *text)
{
	char *p=text;

//	printf("%s", p);
	puts("octal");
	printf("%o%o", *p, *(p+1));
}

/*
	16 진수로 출력
*/
void put_hexa(char *text)
{
	char *p=text;

//	printf("%s", p);
	puts("hexa");
	printf("%x%x", *p, *(p+1));
}

typedef enum { NONE, EUCKR, UTF8, UTF16BE, UTF16LE } CODETYPE;

CODETYPE codescan(char *text)	// 한글코드 자동 인식
{
	return NONE;
}

void usage() {
	puts("C> run [-o/-x] input_file_name");
}

/*
	파일 내용 전체를 memory로 dump
*/
main(int argc, char *argv[])
{
	unsigned char *text;	// input text: 입력 파일 전체
	int i = argc-1, codeType;
	char *opt = "none";

	if (argc < 2) { usage(); return 0; }
	if (argv[1][0] == '-') opt = argv[1];

	if ((text=loadFile(argv[i])) == NULL)
		return -1;	// text file --> 'text'

	if (!strcmp(opt, "-o")) put_octal(text);
	else if (!strcmp(opt, "-x")) put_hexa(text);
	else printf("%s", text);

	codeType = codescan(text);	// 한글코드 자동 인식

	free(text);	// malloc() in 'loadFile()'
	return 0;
}
/*-------------------------- end of loadFile.c ------------------------*/
