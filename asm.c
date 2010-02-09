#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "asm.h"
#include "code.h"
#include "error.h"
#include "parse.h"
#include "symbol.h"

#define MAXOUTBUFF 10000

struct settings settings;

void usage(void)
{
	printf("\n<options> <file>\n");
	printf("<file>	Filename to assemble.\n");
	printf("	Filename must end with .asm.\n");
	printf("-C 	Print code output to stdout - with comments.\n");
	printf("-c	Print code output to stdout - without comments.\n");
	printf("-t	Print final hash table to stdout.\n");
	printf("-v	Verbose output to stdout.\n");
	printf("-x	Print commands to stdout.\n\n");
}

static void settings_init(void)
{
	settings.verbose = 0;
	settings.verbose = 0;
	settings.hash = 0;
	settings.code = 0;
	settings.comments = 0;
	settings.commands = 0;
}

int main(int argc, char *argv[])
{
	char FilenameBuff[80];
	register int i = 0;
	int address = 0;
	int c;

	settings_init();

	if(argc <2) { usage(); return 0;}

	while(-1 != (c = getopt(argc, argv,
		"-v" /* verbose output to stdout */
		"-t" /* print final hash table to stdout */
		"-c" /* print code output to stdout - without comments */
		"-C" /* print code output to stdout - with comments */
		"-x" /* print commands to stdout */
		"--help" /*print out usage statement */
	))) {

		switch (c)
		{
			case 'v':
				settings.verbose = 1;
				settings.hash = 1;
				settings.code = 1;
				settings.comments = 1;
				settings.commands = 1;
				break;
			case 't':
				settings.hash = 1;
				break;
			case 'c':
				settings.code = 1;
				break;
			case 'C':
				settings.code = 1;
				settings.comments = 1;
				break;
			case 'x':
				settings.commands = 1;
				break;
		}
	}

	/* find path location */
	if(argv[1][0] == '-') { c = 2; } else { c = 1; }

	if(argc < 2) { exit_error(1, "No Input Files."); usage(); }
	/* TODO: future versions will accept more than one file */
	if(argc > 3) { exit_error(2, "Too Many Files Listed."); usage(); }

	strcpy(FilenameBuff, argv[c]);

	/* verify filename extension */
	i = strlen(argv[c]) - 1;
	if(	(argv[c][i-2] != 'a') ||
		(argv[c][i-1] != 's') ||
		(argv[c][i]   != 'm' ) ) { exit_error(5, "Filename Extension Not Correct."); usage(); }

	init_parser(FilenameBuff);

	/* modify filename to output filename and then open file */
	FilenameBuff[i-2] = 'h';
	FilenameBuff[i-1] = 'a';
	FilenameBuff[i]   = 'c';
	FilenameBuff[i+1] = 'k';
	FilenameBuff[i+2] = '\0';

	/* load symbol table with pre-defined symbols */
	add_entry("SP", 0);
	add_entry("LCL", 1);
	add_entry("ARG", 2);
	add_entry("THIS", 3);
	add_entry("THAT", 4);
	add_entry("SCREEN", 16384);
	add_entry("KBD", 24576);

	add_entry("R0", 0);
	add_entry("R1", 1);
	add_entry("R2", 2);
	add_entry("R3", 3);
	add_entry("R4", 4);
	add_entry("R5", 5);
	add_entry("R6", 6);
	add_entry("R7", 7);
	add_entry("R8", 8);
	add_entry("R9", 9);
	add_entry("R10", 10);
	add_entry("R11", 11);
	add_entry("R12", 12);
	add_entry("R13", 13);
	add_entry("R14", 14);
	add_entry("R15", 15);

	while(has_more_commands())
	{
		advance();
		if(command_type() == A_COMMAND || command_type() == C_COMMAND)
			inc_rom_address();
		if(command_type() == L_COMMAND)
			symbol_load();
	}

	init_coder(FilenameBuff);
	reset_buffer();

	while(has_more_commands())
	{
		char sym[MAXCOMMAND];

		advance();
		if(command_type() == A_COMMAND || command_type() == L_COMMAND)
		{
			address = symbol(sym);
			if(command_type() == A_COMMAND) { enc_symbol(address); }
		}

		if(command_type() == C_COMMAND)
		{
			if(comp(sym) != 0) { enc_comp(sym); }
			if(dest(sym) != 0) { enc_dest(sym); }
			if(jump(sym) != 0) { enc_jump(sym); }
		}
		if(command_type() != L_COMMAND)
		{
			advance_ouptut_file();
			if(settings.code != 0 || settings.comments != 0 ) { printf(" "); }
		} else {
			if(settings.code != 0 || settings.comments != 0)
			{
				printf("                 ");
			}
		}

		if(settings.commands != 0) { print_current_command(); }
		if(settings.code == 0 || settings.comments == 0) { printf("\n"); }
 	}

	if(settings.hash != 0) { print_hash(); }
	return 0;
}
