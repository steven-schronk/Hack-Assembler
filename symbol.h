/*
* Adds pair (symbol, address) to the table
*/
void add_entry();

/*
* Does the symbol table contain the given symbol
*/
int contains(char *symbol, int address);

/*
* Returns address associated with symbol
*/
int get_address(char *symbol);
