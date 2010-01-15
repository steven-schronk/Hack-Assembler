#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#include "parse.h"
#include "error.h"
#include "code.h"

#define MAXOUTBUFF 10000

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
		char sym[MAXCOMMAND];

		advance();
		/* printf("TYPE: %d ", command_type()); */
		/* print_current_command(); */

		if(command_type() == A_COMMAND || command_type() == L_COMMAND)
		{
			symbol(sym);
			enc_symbol(sym);
		}

		if(command_type() == C_COMMAND)
		{
			enc_start_c();
			if(dest(sym) != 0)
			{
				enc_dest(sym);
			}
			
			if(comp(sym) != 0)
			{
				enc_comp(sym);
			}

			if(jump(sym) != 0)
			{
				enc_jump(sym);
			}
		}
		printf("\n");
	}
	return 0;
}
