
/*
* Initialize ouptut file for writing
*/
int init_coder(const char *filename);

/*
* Returns binary code of the dest mnemonic
*/
int enc_dest(const char *mnemonic);

/*
* Returns binary code of the comp mnemonic
*/
int enc_comp(const char *mnemonic);

/*
* Returns binary code of the jump mnemonic
*/
int enc_jump(const char *mnemonic);
