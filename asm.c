#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#include "parse.h"
#include "error.h"

#define MAXOUTBUFF 10000

/* char OutBuff[MAXINBUFF]; */

int main(int argc, char *argv[])
{
	char FilenameBuff[80];
	register int i = 0;

	if(argc != 2) { exit_error(1, "No Input Files"); }
	/* TODO: future versions will accept more than one file */
	if(argc > 2) { exit_error(2, "Too Many Files Listed"); }

	strcpy(FilenameBuff, argv[1]);

	/* verify filename extension */
	i = strlen(argv[1]) - 1;
	if(	(argv[1][i-2] != 'a') ||
		(argv[1][i-1] != 's') ||
		(argv[1][i]   != 'm' ) ) { exit_error(5, "Filename Extension Not Correct"); }

	init_parser(argv[1]);

	/* modify filename to output filename and then open file */
	FilenameBuff[i-2] = 'h';
	FilenameBuff[i-1] = 'a';
	FilenameBuff[i]   = 'c';
	FilenameBuff[i+1] = 'k';
	FilenameBuff[i+2] = '\0';

	/* TODO: verify output buffer has not been overflowed */

	advance(); /* find first command */

	/*dump_buffer(); */

	while(has_more_commands())
	{
		advance();
		print_current_command();
		printf("TYPE: %d\n", command_type());
	}

	return 0;
}
