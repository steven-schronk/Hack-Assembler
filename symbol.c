#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "error.h"
#include "parse.h"
#include "symbol.h"

struct symbol_hash symbol_hash[HASH_SIZE];
int rom_address = 0;

void print_hash()
{
	int i = 0;
	while(i < HASH_SIZE)
	{
		if(symbol_hash[i].name[0] != '\0')
		{
			printf("HASH: %d->%d->%s\n", i, symbol_hash[i].address, symbol_hash[i].name);
		}
		++i;
	}
}

int hash(char symbol[])
{
	int hash = 0;
	int i = 0;
	while(symbol[i] != '\0')
	{
		hash += symbol[i];
		++i;
	}
	hash = hash % HASH_SIZE;
	return hash;
}

int add_entry(char symbol[], int address)
{
	int i = 0;
	int hash_val;
	hash_val = hash(symbol);
	if(symbol_hash[hash_val].name[0] == '\0')
	{
		printf("NEW SYMBOL %s\n", symbol);
		strcpy(symbol_hash[hash_val].name, symbol);
		if(address < 0)
		{
			symbol_hash[hash_val].address = rom_address++;
		} else {
			symbol_hash[hash_val].address = address;
		}
		return 1;
	} else {
		/* compare value of symbol here with input of function */
		if(strcmp(symbol_hash[hash_val].name, symbol) == 0) { return 1; }
		printf("Found Duplicate Hash Value\n");
		do{ ++i; } while (symbol_hash[i].name != NULL && i < HASH_SIZE);
		if( i == HASH_SIZE)
		{
			int i = find_line_num();
			line_notification(i);
			exit_error(13, "Symbol table full");
		}
		strcpy(symbol_hash[hash_val].name, symbol);
		if(address < 0)
		{
			symbol_hash[hash_val].address = rom_address++;
		} else {
			symbol_hash[hash_val].address = address;
		}
		return 1;
	}
	return 0;
}

int get_address(char symbol[])
{
	int hash_val, i = 0, j = 0;
	hash_val = hash(symbol);
	if(symbol_hash[hash_val].name != NULL)
	{
		return hash_val;
	} else {
		/*
		could not find hash -- loop through strings
		for length of symbol_hash looking for a match
		*/
		while(strcmp(symbol_hash[i].name, symbol) != 0 && j < HASH_SIZE)
		{
			if(i == HASH_SIZE){ i = 0; } else { ++i; }
			++j;
		}
		if(strcmp(symbol_hash[i].name, symbol) == 0)
		{
			return i;
		}
	}
	return -1;
}
