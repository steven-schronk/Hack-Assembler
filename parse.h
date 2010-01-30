
#define MAXCOMMAND 100
#define MAXINBUFF 250000
#define MAXSYMBOL 256

#define pInBuff *(InBuff+i)

/*
* A_COMMAND: @value
*	value is either a non-negative decimal numer of a symbol referring to such a number
*
* C_COMMAND: dest = comp; jump
*	either of the dest or jump fields may be empty
*	if dest is empty, the "=" is omitted
*	if jump is emprty, the ";" is omitted
*/
#define A_COMMAND 0
#define C_COMMAND 1
#define L_COMMAND 2

void dump_buffer();
void init_parser(char *FilenameBuff);

/*
* Finds current line number of source file.
* This is done for the convenience of the user.
*/
int find_line_num();

/*
* Search current command for term.
* Ignores whitespace. Looks for one char only.
*/
int search_command(const char *current_command, const char term);

/*
* Print chars of current command to stdout.
*/
void print_current_command();

/*
* Confirms the existance of more commands in the input
*/
int has_more_commands();

/*
* Read next command from input and makes it the current command
* Should be called only if has_more_commands() is true
* Initialy there is no current command
*/
void advance();

/*
* Returns type of current command
* See Commands comment for more info
*/
int command_type();

/*
* Returns symbol or decimal of current command
* Should be called only when command_type() is A_COMMAND or L_COMMAND
*/
int symbol(char sym[]);

/*
* Returns the dest mnemonic in the current C_COMMAND
* Should be called only when command_type() is C_COMMAND
*/
int dest(char dest[]);

/*
* Returns comp mnemonic in the current C_COMMAND
* Called only when command_type() is C_COMMAND
*/
int comp(char comp[]);

/*
* Returns the jump mnemonic in the current C_COMMAND
* Called only when command_type() is C_COMMAND
*/
int jump(char jump[]);

/*
* Evaluate full text of input file and find all symbols.
* Load symbols into symbol_hash table.
*/
void load_symbols(void);
