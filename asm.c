#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

//#include "parse.h"

#define MAXINBUFF 10000
#define MAXOUTBUFF 10000
#define MAXCOMMAND 100

FILE *pInfile;
FILE *pOutfile;

char InBuff[MAXINBUFF];
//char OutBuff[MAXINBUFF];
char FilenameBuff[80];

char *current_command = InBuff;
int current_command_type;

void dump_buffer(const char *buffer)
{
	int i = 0;
	while(buffer[i] != '\0')
	{
		printf("%c", buffer[i++]);
	}
	printf("\n");
}

void exit_error(const int err_num, const char *err_msg)
{
	fprintf(stderr, "ERROR %d: %s\n", err_num, err_msg);
	if(pInfile != NULL) { fclose(pInfile); }
	if(pOutfile != NULL) { fclose(pOutfile); }
	exit(EXIT_FAILURE);
}

void warning_error(const int err_num, const char *err_msg)
{
	fprintf(stderr, "WARNING: %d: %s\n", err_num, err_msg);
}

void line_notification(const int line_num)
{
	fprintf(stderr, "ERROR FOUND ON LINE: %d\n", line_num);
}

/*
* TODO: NEEDS TO BE MOVED TO ANOTHER FILE
*/

#define A_COMMAND 0
#define C_COMMAND 1
#define L_COMMAND 2


/*
* Finds current line number of source file.
* This is done for the convenience of the user.
*/
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
			symbol[i-1] = *(current_command+i);
		}
		return symbol;
	}
	exit_error(8, "Symbol Function Called on Incorrect Command Type.");
	return symbol;
}

/*
* END LINES TO BE MOVED
*/

int main(int argc, char *argv[])
{
	register int i = 0;
	register int k = 0;

	if(argc != 2) { exit_error(1, "No Input Files"); }
	// TODO: future versions will accept more than one file
	if(argc > 2) { exit_error(2, "Too Many Files Listed"); }

	strcpy(FilenameBuff, argv[1]);

	// verify filename extension of file
	i = strlen(FilenameBuff) - 1;
	if(	(FilenameBuff[i-2] != 'a') ||
		(FilenameBuff[i-1] != 's') ||
		(FilenameBuff[i]   != 'm' ) ) { exit_error(5, "Filename Extension Not Correct"); }

	if((pInfile = fopen(FilenameBuff, "rb")) == NULL)
		exit_error(3, "Cannot Open Input (Source) File");

	k = -1;
	while(!feof(pInfile) && k < MAXINBUFF)
		InBuff[++k] = fgetc(pInfile);
	InBuff[k] = '\0';

	if(k < MAXINBUFF)
	{
		printf("Input Buffer Loaded\n");
	} else {
		exit_error(4, "Input Too Large for Input Buffer");
	}

	// modify filename to output filename and then open file
	FilenameBuff[i-2] = 'h';
	FilenameBuff[i-1] = 'a';
	FilenameBuff[i]   = 'c';
	FilenameBuff[i+1] = 'k';
	FilenameBuff[i+2] = '\0';

	if((pOutfile = fopen(FilenameBuff, "w")) == NULL)
		exit_error(6, "Cannot Open Output (Destination) File");

	// TODO: verify output buffer has not been overflowed

	advance(); // find first command
	while(has_more_commands())
	{
		advance();
		print_current_command();
		printf("TYPE: %d\n", command_type());
	}

	return 0;
}
