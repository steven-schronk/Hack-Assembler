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
command_type();

/*
* Returns symbol or decimal of current command
* Should be called only when command_type() is A_COMMAND or L_COMMAND
*/
char *symbol();

/*
* Returns the dest mnemonic in the current C_COMMAND
* Should be called only when command_type() is C_COMMAND
*/
char *dest();

/*
* Returns comp mnemonic in the current C_COMMAND
* Called only when command_type() is C_COMMAND
*/
char *comp();

/*
* Returns the jump mnemonic in the current C_COMMAND
* Called only when command_type() is C_COMMAND
*/
char *jump();
