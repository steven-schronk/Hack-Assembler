
/*
* Initialize ouptut file for writing
*/
int init_coder(char *filename);

/*
* Returns binary code of the dest mnemonic
*/
int enc_dest(char *mnemonic);

/*
* Returns binary code of the comp mnemonic
*/
int enc_comp(char *mnemonic);

/*
* Returns binary code of the jump mnemonic
*/
int enc_jump(char *mnemonic);

