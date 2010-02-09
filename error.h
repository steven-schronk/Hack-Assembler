/*
* Prints error to stdout along with error number and string desc of problem.
* Exits program without recourse.
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
void warning_error(const int err_num, const char *err_msg);

/*
* Prints line number that error/warning occured for user.
*/
void line_notification(const int line_num);
