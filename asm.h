struct settings
{
	int verbose;
	int hash;
	int code;
	int comments;
	int commands;
};

extern struct settings settings;

/*
* Display usage info for the user.
*/
void usage(void);

/*
* Apply command line settings (arguments) to the settings struct.
* These settings are generally universally applicable to the program.
* Therefore, they are stored and maintained in the settings.
*/
void settings_init(void);

/*
* Helper function to view contents of buffer when needed.
*/
void dump_buffer(void);

/*
* Display Errors to user as needed.
*
* Will send text of error message as well as error number.
* Error number corresponds to number listed in documentation.
*
*/
void exit_error(const int err_num, const char *err_msg);


