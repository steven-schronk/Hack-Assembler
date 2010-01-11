
#include <string.h>
#include <stdio.h>

#include "code.h"
#include "error.h"
#include "parse.h"

int init_coder(char *filename)
{
	return 0;
}

int enc_dest(char *mnemonic)
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

int enc_comp(char *mnemonic)
{
	return 0;
}

int enc_jump(char *mnemonic)
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
	} else if(strcmp(mnemonic, "JEQ") == 0) {
		printf("010");
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
