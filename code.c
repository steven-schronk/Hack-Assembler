#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "code.h"
#include "error.h"
#include "parse.h"

int init_coder(const char *filename)
{
	return 0;
}

int enc_symbol(const char mnemonic[])
{
	int value = 0;
	int i = 0;

	value = strtol(mnemonic, NULL, 10);
	for( i = 15; i >= 0; i--)
   	{
        	if( (1 << i) & value)
			putchar('1');
		else
			putchar('0');
   	}
	return 0;
}

void enc_start_c()
{
	printf("111X");
}

int enc_dest(const char mnemonic[])
{

	if(strcmp(mnemonic, "") == 0) {
		printf("000");
		return 1;
	} else if (strcmp(mnemonic, "M") == 0) {
		printf("001");
		return 1;
	} else if(strcmp(mnemonic, "D") == 0) {
		printf("010");
		return 1;
	} else if(strcmp(mnemonic, "MD") == 0) {
		printf("011");
		return 1;
	} else if(strcmp(mnemonic, "A") == 0) {
		printf("100");
		return 1;
	} else if(strcmp(mnemonic, "AM") == 0) {
		printf("101");
		return 1;
	} else if(strcmp(mnemonic, "AD") == 0) {
		printf("110");
		return 1;
	} else if(strcmp(mnemonic, "AMD") == 0) {
		printf("111");
		return 1;
	} else {
		int i = find_line_num();
		line_notification(i);
		exit_error(10, "Symbol Not Found In Dest Lookup Table.");
	}
	return 0;
}

int enc_comp(const char mnemonic[])
{
	int a = 0;
	if(a == 0)
	{
		if(strcmp(mnemonic, "0") == 0) {
			printf("101010");
			return 1;
		} else if(strcmp(mnemonic, "1") == 0) {
			printf("111111");
			return 1;
		} else if(strcmp(mnemonic, "-1") == 0) {
			printf("111010");
			return 1;
		} else if(strcmp(mnemonic, "D") == 0) {
			printf("001100");
			return 1;
		} else if(strcmp(mnemonic, "A") == 0) {
			printf("110000");
			return 1;
		} else if(strcmp(mnemonic, "!D") == 0) {
			printf("001101");
			return 1;
		} else if(strcmp(mnemonic, "!A") == 0) {
			printf("110001");
			return 1;
		} else if(strcmp(mnemonic, "-D") == 0) {
			printf("001111");
			return 1;
		} else if(strcmp(mnemonic, "-A") == 0) {
			printf("110011");
			return 1;
		} else if(strcmp(mnemonic, "D+1") == 0) {
			printf("011111");
			return 1;
		} else if(strcmp(mnemonic, "A+1") == 0) {
			printf("110111");
			return 1;
		} else if(strcmp(mnemonic, "D-1") == 0) {
			printf("001110");
			return 1;
		} else if(strcmp(mnemonic, "A-1") == 0) {
			printf("110010");
			return 1;
		} else if(strcmp(mnemonic, "D+A") == 0) {
			printf("000010");
			return 1;
		} else if(strcmp(mnemonic, "D-A") == 0) {
			printf("010011");
			return 1;
		} else if(strcmp(mnemonic, "A-D") == 0) {
			printf("000111");
			return 1;
		} else if(strcmp(mnemonic, "D&A") == 0) {
			printf("000000");
			return 1;
		} else if(strcmp(mnemonic, "D|A") == 0) {
			printf("010101");
			return 1;
		} else if(strcmp(mnemonic, "M") == 0) {
			printf("110000");
			return 1;
		} else if(strcmp(mnemonic, "!M") == 0) {
			printf("110001");
			return 1;
		} else if(strcmp(mnemonic, "-M") == 0) {
			printf("110011");
			return 1;
		} else if(strcmp(mnemonic, "M+1") == 0) {
			printf("110111");
			return 1;
		} else if(strcmp(mnemonic, "M-1") == 0) {
			printf("110010");
			return 1;
		} else if(strcmp(mnemonic, "D+M") == 0) {
			printf("000010");
			return 1;
		} else if(strcmp(mnemonic, "D-M") == 0) {
			printf("010011");
			return 1;
		} else if(strcmp(mnemonic, "M-D") == 0) {
			printf("000111");
			return 1;
		} else if(strcmp(mnemonic, "D&M") == 0) {
			printf("000000");
			return 1;
		} else if(strcmp(mnemonic, "D|M") == 0) {
			printf("010101");
			return 1;
		} else {
			int i = find_line_num();
			line_notification(i);
			exit_error(11, "Symbol Not Found In Encode Lookup Table.");
		}

	} else {


	}


	return 0;
}

int enc_jump(const char mnemonic[])
{
	if(strcmp(mnemonic, "") == 0) {
		printf("000");
		return 1;
	} else if(strcmp(mnemonic, "JGT") == 0) {
		printf("001");
		return 1;
	} else if(strcmp(mnemonic, "JEQ") == 0) {
		printf("010");
		return 1;
	} else if(strcmp(mnemonic, "JGE") == 0) {
		printf("011");
		return 1;
	} else if(strcmp(mnemonic, "JLT") == 0) {
		printf("100");
		return 1;
	} else if(strcmp(mnemonic, "JNE") == 0) {
		printf("101");
		return 1;
	} else if(strcmp(mnemonic, "JLE") == 0) {
		printf("110");
		return 1;
	} else if(strcmp(mnemonic, "JMP") == 0) {
		printf("111");
		return 1;
	} else {
		int i = find_line_num();
		line_notification(i);
		exit_error(11, "Symbol Not Found In Jump Lookup Table.");
	}
	return 0;
}
