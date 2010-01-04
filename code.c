
#define dest_null 000
#define dest_M    001
#define dest_D    010
#define dest_MD   011
#define dest_A    100
#define dest_AM   101
#define dest_AD   110
#define dest_AMD  111

//tri dest(char *mnemonic)
int dest(char *mnemonic)
{
 	codetab dest[] =
	{
		{"null",	000 },
		{"M",		001 },
		{"D",		010 },
	};

	tri ans;

	int i = 0;
	for(i = 0; i < sizeof(dest); i++)
		if(dest[i] == mnemonic) { return i; }



	return -1;
}

sept comp(char *mnemonic)
{
	sept ans;

	return sept;
}

tri jump(char *mnemonic)
{

	tri ans;

	return ans;
}
