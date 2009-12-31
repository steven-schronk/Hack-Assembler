#include "asm.c"

/*
* Helper function to view contents of buffer when needed.
*/
void dump_buffer(const char *buffer);

/*
* Display Errors to user as needed.
*
* Will send text of error message as well as error number.
* Error number corresponds to number listed in documentation.
*
*/
void exit_error(const int err_num, const char *err_msg);

/*
* Display Warnings about assembler status as needed.
*
* These are messages to the user that contain both an error number
* as well as simple description of what went wrong.
* 
* Error number corresponds to number listed in documentation.
*
*/
int warning_error(const int err_num, const char *err_msg);