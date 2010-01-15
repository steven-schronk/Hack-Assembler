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

int search_command(const char *current_command, const char term)
{
	int i = 0;
	int found = 0;
	while(*(current_command+i) != '\r' && *(current_command+i) != '\n' && *(current_command+i) != '\0')
	{
		if(*(current_command+i) == term) { ++found; }
		++i;
	}
	return found;
}

void print_current_command()
{
	int i = 0;
	printf("CURRENT COMMAND: ");
	while(*(current_command+i) != '\r' && *(current_command+i) != '\n' && *(current_command+i) != '\0' && i <= 20)
	{
		printf("%c", *(current_command+i));
		++i;
	}
	printf("\n");
}

void init_parser(char *FilenameBuff)
{
	/*if((pOutfile = fopen(FilenameBuff, "w")) == NULL)
		exit_error(6, "Cannot Open Output (Destination) File"); */

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
	int i = 0;
	while(*(current_command+i) != '\0' && *(current_command+i) != '\n') { ++i; }
	if(*(current_command+i) == '\0') { return 0; }
	return 1;
}

void advance()
{
	do {
		++current_command;
	} while(*current_command != '\n' && *current_command != '\0');
	while(isspace(*current_command)) { ++current_command; }
	if(*(current_command+1) == '/')
	{
		++current_command;
		advance();
	}
}

int command_type()
{
	if(*current_command == '@')
	{
		current_command_type = A_COMMAND;
		return A_COMMAND;
	} else if(search_command(current_command, '(') > 0 || search_command(current_command, ')') > 0) {
		current_command_type = L_COMMAND;
		return L_COMMAND;
	} else if(!isdigit(*current_command)){
		current_command_type = C_COMMAND;
		return C_COMMAND;
	} else if(isdigit(*current_command)){
		current_command_type = C_COMMAND;
		return C_COMMAND;
	} else {
		int i = find_line_num();
		line_notification(i);
		exit_error(7, "Incorrect Command Type");
		return -1;
	}
}

int symbol(char sym[])
{
	int i = 0;

	if(current_command_type == A_COMMAND)
	{
		while(!isspace(*(current_command+i+1)))
		{
			sym[i] = *(current_command+i+1);
			++i;
		}
		sym[i++] = '\0';
		return 1;
	}

	if(current_command_type == L_COMMAND)
	{
		while(!isspace(*(current_command+i+1)) && *(current_command+i+1) != ')')
		{
			sym[i] = *(current_command+i+1);
			++i;
		}
		sym[i++] = '\0';
		return 1;
	}
	exit_error(8, "Symbol Function Called on Incorrect Command Type.");
	return 0;
}

int dest(char dest[])
{
	int i = 0;
	int dest_exist = 0;

	if(current_command_type == C_COMMAND)
	{
		while(*(current_command+i) != '\n' && *(current_command+i) != '\0')
		{
			if(*(current_command+i) == '=') { ++dest_exist; }
			++i;
		}
		if(dest_exist == 0) { return 0; } /* no dest in command */

		i = 0;
		while(*(current_command+i) != '=')
		{
			dest[i] = *(current_command+i);
			i++;
		}
		dest[i] = '\0';
		return 1;
	}
	i = find_line_num();
	line_notification(i);
	exit_error(8, "Symbol Function Called on Incorrect Command Type.");
	return 0;
}

int comp(char comp[])
{
	int i = 0;
	int eq_exist = 0;
	int semi_exist = 0;
	char *delimiter = NULL;

	while(*(current_command+i) != '\n' && *(current_command+i) != '\0')
	{
		if(*(current_command+i) == '=') { ++eq_exist; delimiter = current_command+i; }
		if(*(current_command+i) == ';') { ++semi_exist; }
		++i;
	}

	if(!semi_exist && !eq_exist)
	{
		line_notification(i);
		exit_error(9, "Command Does Not Contain Proper Delimiter.");
		return 0;
	}

	if(current_command_type == C_COMMAND)
	{
		if(eq_exist) /* found '=' in command -- skip to char after equal and copy till new line */
		{
			i = 0;
			++delimiter;
			while(*(delimiter+i) != ';' && !isspace(*(delimiter+i)) && *(delimiter+i) != '\0')
			{
				comp[i] = *(delimiter+i);
				i++;
			}
		} else { /* no '=' in command -- copy until semicolon found */
			i = 0;
			while(*(current_command+i) != ';')
			{
				comp[i] = *(current_command+i);
				i++;
			}
		}
		comp[i] = '\0';
		return 1;
	}
	i = find_line_num();
	line_notification(i);
	exit_error(8, "Symbol Function Called on Incorrect Command Type.");
	return 0;
}

int jump(char jump[])
{
	int i = 0;
	char *delimiter = NULL;
	int valid_command = 0;
	if(current_command_type == C_COMMAND)
	{
		/* Test for semicolon before newline char */
		i = 0;
		while(*(current_command+i) != '\n' && *(current_command+i) != '\0')
		{
			if(*(current_command+i) == ';') { ++valid_command; }
			++i;
		}
		if(valid_command == 0) { return 0; } /* no jump in command */
		delimiter = strchr(current_command, ';');
		++delimiter;
		i = 0;
		while(!isspace(*(delimiter+i)) && *(delimiter+i) != '\0')
		{
			jump[i] = *(delimiter+i);
			++i;
		}
		jump[i] = '\0';
		return 1;
	}
	i = find_line_num();
	line_notification(i);
	exit_error(8, "Symbol Function Called on Incorrect Command Type.");
	return 0;
}
