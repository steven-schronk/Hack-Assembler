
/*
* Initialize ouptut file for writing
*/
int init_coder(const char *filename);

/*
* Adds newline to end of output file.
*/
void advance_ouptut_file();

/*
* Returns binary code of A_COMMAND and L_COMMAND
* mnemonic is array of chars with A_COMMAND or L_COMMAND.
* code array will be modified to binary chars of command.
*/
void enc_symbol(int number);

/*
* Returns binary code of the dest mnemonic
*/
int enc_dest(const char mnemonic[]);

/*
* Returns binary code of the comp mnemonic
*/
int enc_comp(const char mnemonic[]);

/*
* Returns binary code of the jump mnemonic
*/
int enc_jump(const char mnemonic[]);
