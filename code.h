#include "code.c"

/*
typedef struct codetab
{
	char *string;
	int code;
};
*/

typedef struct type_tri
{
	char one;
	char two;
	char three;
} tri;

typedef struct type_sept
{
	char one;
	char two;
	char three;
	char four;
	char five;
	char six;
	char seven;
} sept;

/*
* Returns binary code of the dest mnemonic
*/
int dest(char *mnemonic);

/*
* Returns binary code of the comp mnemonic
*/
sept comp(char *mnemonic);

/*
* Returns binary code of the jump mnemonic
*/
tri jump(char *mnemonic);

