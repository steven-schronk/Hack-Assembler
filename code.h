struct {
	char one,
	char two,
	char three
} tri;

struct {
	char one,
	char two,
	char three,
	char four,
	char five,
	char six,
	char seven
} sept;

/*
* Returns binary code of the dest mnemonic
*/
tri dest(char *mnemonic);

/*
* Returns binary code of the comp mnemonic
*/
sept comp(char *mnemonic);

/*
* Returns binary code of the jump mnemonic
*/
tri jump(char *mnemonic);

