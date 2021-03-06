/* Hash size must be a prime number. */
#define HASH_SIZE 104729

struct symbol_hash
{
	char name[MAXSYMBOL];
	int address;
};

/*
* Returns current value of RAM address.
*/
int get_ram_address();

/*
* Increments ROM Address value.
* ROM Address used to store location of instruction tied to symbols.
* This number correponds to the instruction number of the "jump" instruction.
*/
void inc_rom_address();

/*
* Returns current value of ROM address.
*/
int get_rom_address();

/*
* Prints out hash.
* Must pass hash pointer and length of hash array
*/
void print_hash();

/*
* Calculates Hash value.
* Returns integer value of hash based on string input
*/
int hash(char symbol[]);

/*
* Adds pair (symbol, address) to the table.
* If address is set to < 0, hash chooses address.
* Returns 1 if entry added to table and 0 otherwise.
*/
int add_entry(char symbol[], int address);

/*
* Look from beginning of hash for an empty slot and return it's address
* This should be used only when a hash collision occurs as there is a
* performance penalty for finding this value later.
*/
int next_hash_space(void);

/*
* Returns address associated with symbol.
* If array found in hash, address is returned,
* otherwise return -1
*/
int get_address(char symbol[]);
