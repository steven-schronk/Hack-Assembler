#define HASH_SIZE 509

/*
* Prints out hash.
* Must pass hash pointer and length of hash array
*/
void print_hash();

/*
* Hash function.
* Returns integer value of hash based on string input
*/
int hash(char symbol[]);

/*
* Adds pair (symbol, address) to the table
* Returns 1 if entry added to table and 0 otherwise.
*/
int add_entry(char symbol[]);

/*
* Does the symbol table contain the given symbol
*/
int contains(char symbol[]);

/*
* Returns address associated with symbol
* If array found in hash, address is returned,
* otherwise return -1
*/
int get_address(char symbol[]);
