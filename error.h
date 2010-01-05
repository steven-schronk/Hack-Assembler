/*
* Prints error to stdout along with error number and string desc of problem.
* Exits program without recourse.
*/
void exit_error(const int err_num, const char *err_msg);

/*
* Prints warning to stdout with warning number and string sdec of problem.
* Continues to execute program.
*/
void warning_error(const int err_num, const char *err_msg);

/*
* Prints line number that error/warning occured for user.
*/
void line_notification(const int line_num);
