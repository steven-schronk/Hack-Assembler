
#include <string.h>
#include <stdio.h>

#include "code.h"
#include "error.h"
#include "parse.h"

int init_coder(const char *filename)
{
	return 0;
}

int enc_dest(const char *mnemonic)
{
	char command[MAXCOMMAND];
	char *pcommand = command;

	strcpy(pcommand, mnemonic);

	if(strcmp(mnemonic, "") == 0) {
		printf("D000");
		return 1;
	} else if (strcmp(mnemonic, "M") == 0) {
		printf("D001");
		return 1;
	} else if(strcmp(mnemonic, "D") == 0) {
		printf("D010");
		return 1;
	} else if(strcmp(mnemonic, "MD") == 0) {
		printf("D011");
		return 1;
	} else if(strcmp(mnemonic, "A") == 0) {
		printf("D100");
		return 1;
	} else if(strcmp(mnemonic, "AM") == 0) {
		printf("D101");
		return 1;
	} else if(strcmp(mnemonic, "AD") == 0) {
		printf("D110");
		return 1;
	} else if(strcmp(mnemonic, "AMD") == 0) {
		printf("D111");
		return 1;
	} else {
		int i = find_line_num();
		line_notification(i);
		exit_error(10, "Symbol Not Found In Dest Lookup Table.");
	}
	return 0;
}

int enc_comp(const char *mnemonic)
{
	return 0;
}

int enc_jump(const char *mnemonic)
{
	char command[MAXCOMMAND];
	char *pcommand = command;

	strcpy(pcommand, mnemonic);

	if(strcmp(pcommand, "") == 0) {
		printf("J000");
		return 1;
	} else if(strcmp(pcommand, "JGT") == 0) {
		printf("001");
		return 1;
	} else if(strcmp(pcommand, "JEQ") == 0) {
		printf("010");
		return 1;
	} else if(strcmp(pcommand, "JGE") == 0) {
		printf("011");
		return 1;
	} else if(strcmp(pcommand, "JLT") == 0) {
		printf("100");
		return 1;
	} else if(strcmp(pcommand, "JNE") == 0) {
		printf("J101");
		return 1;
	} else if(strcmp(pcommand, "JLE") == 0) {
		printf("J110");
		return 1;
	} else if(strcmp(pcommand, "JMP") == 0) {
		printf("J111");
		return 1;
	} else {
		int i = find_line_num();
		line_notification(i);
		exit_error(11, "Symbol Not Found In Jump Lookup Table.");
	}
	return 0;
}
