/* Hash size must be a prime number. */
#define HASH_SIZE 2039

struct symbol_hash
{
	char name[MAXSYMBOL];
	int address;
};

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
* Returns address associated with symbol.
* If array found in hash, address is returned,
* otherwise return -1
*/
int get_address(char symbol[]);
