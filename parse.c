#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "parse.h"
#include "error.h"

FILE *pOutfile;
FILE *pInfile;

char InBuff[MAXINBUFF];

char FilenameBuff[80];

char *current_command = InBuff;
int current_command_type;

int k = 0;

void dump_buffer()
{
	int i = 0;
	while(InBuff[i] != '\0')
	{
		printf("%c", InBuff[i++]);
	}
	printf("\n");
}

int find_line_num()
{
	int i = 1;
	char *k = InBuff;
	while(current_command != k)
	{
		if(*k == '\n') { ++i; }
		++k;
	}
	return i;
}

void print_current_command()
{
	int i = 0;
	printf("CURRENT COMMAND: ");
	while(*(current_command+i) != '\n' && i <= 20)
	{
		printf("%c", *(current_command+i));
		++i;
	}
	printf("\n");
}

void init_parser(char *FilenameBuff)
{
	//if((pOutfile = fopen(FilenameBuff, "w")) == NULL)
		//exit_error(6, "Cannot Open Output (Destination) File");

	if((pInfile = fopen(FilenameBuff, "rb")) == NULL)
		exit_error(3, "Cannot Open Input (Source) File");

	k = -1;
	while(!feof(pInfile) && k < MAXINBUFF)
	{
		InBuff[++k] = fgetc(pInfile);
	}
	InBuff[k] = '\0';

	if(k < MAXINBUFF)
	{
		printf("Input Buffer Loaded\n");
	} else {
		exit_error(4, "Input Too Large for Input Buffer");
	}
}

int has_more_commands()
{
	if(*current_command == '\0') { return 0; }
	return 1;
}

void advance()
{
	while(*current_command != '\n') /* move to end of current command */
	{
		++current_command;
	}

	if(*(current_command+1) == '/') /* ignore comments */
	{
		current_command++;
		advance();
	}

	while(isspace(*current_command)) { ++current_command; } /* skip whitespace */
}

int command_type()
{
	if(*current_command == '@')
	{
		current_command_type = A_COMMAND;
		return A_COMMAND;
	} else if(*current_command == '(') {
		current_command_type = L_COMMAND;
		return L_COMMAND;
	} else if(!isdigit(*current_command)){
		current_command_type = C_COMMAND;
		return C_COMMAND;
	}

	int i = find_line_num();
	line_notification(i);
	exit_error(7, "Incorrect Command Type");
	return -1;
}

char *symbol()
{
	int i = 1;
	char *symbol[MAXCOMMAND];
	/* TODO: Verify that symbol syntax is OK */

	if(current_command_type == A_COMMAND || current_command_type == L_COMMAND)
	{
		while(*(current_command+i) != '\n' || *(current_command+i) != ')')
		{
			*symbol[i-1] = *(current_command+i);
		}
		return *symbol;
	}
	exit_error(8, "Symbol Function Called on Incorrect Command Type.");
	return *symbol;
}
