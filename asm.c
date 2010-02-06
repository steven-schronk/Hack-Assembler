#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#include "code.h"
#include "error.h"
#include "parse.h"
#include "symbol.h"

#define MAXOUTBUFF 10000

int main(int argc, char *argv[])
{
	char FilenameBuff[80];
	register int i = 0;
	int address = 0;

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
		if(command_type() != L_COMMAND) { printf("\n"); }
 	}

	return 0;
}
