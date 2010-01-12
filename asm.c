#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#include "parse.h"
#include "error.h"
#include "code.h"

#define MAXOUTBUFF 10000

/* char OutBuff[MAXINBUFF]; */

int main(int argc, char *argv[])
{
	char FilenameBuff[80];
	register int i = 0;

	if(argc != 2) { exit_error(1, "No Input Files."); }
	/* TODO: future versions will accept more than one file */
	if(argc > 2) { exit_error(2, "Too Many Files Listed."); }

	strcpy(FilenameBuff, argv[1]);

	/* verify filename extension */
	i = strlen(argv[1]) - 1;
	if(	(argv[1][i-2] != 'a') ||
		(argv[1][i-1] != 's') ||
		(argv[1][i]   != 'm' ) ) { exit_error(5, "Filename Extension Not Correct."); }

	init_parser(argv[1]);

	/* modify filename to output filename and then open file */
	FilenameBuff[i-2] = 'h';
	FilenameBuff[i-1] = 'a';
	FilenameBuff[i]   = 'c';
	FilenameBuff[i+1] = 'k';
	FilenameBuff[i+2] = '\0';

	init_coder(FilenameBuff);

	/* TODO: verify output buffer has not been overflowed */

	while(has_more_commands())
	{
		advance();
		printf("TYPE: %d ", command_type());
		print_current_command();

		if(command_type() == C_COMMAND)
		{

			char *destination = dest();
			if(destination != NULL)
			{
				enc_dest(destination);
				/*
				printf("DEST: ");
				while(*destination != '\0')
				{
					printf("%c", *destination++);
				}
				printf(" ");
				*/
			}

			char *comparison = comp();
			if(comparison != NULL)
			{
				enc_comp(comparison);
				/*
				printf("COMP: ");
				while(*comparison != '\0')
				{
					printf("%c", *comparison++);
				}
				printf(" ");
				*/
			}

			char *jumpsymbol = jump();
			if(jumpsymbol != NULL)
			{
				enc_jump(jumpsymbol);
				/*
				printf("JUMP: ");
				while(*jumpsymbol != '\0')
				{
					printf("%c", *jumpsymbol++);
				}
				printf(" ");
				*/
			}
		}
		printf("\n");
		/* TODO: Add comp and jump here when implemented */
	}
	return 0;
}
