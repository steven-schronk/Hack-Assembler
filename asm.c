#include <stdio.h>
#include <stdlib.h>

void exit_error(const int err_num, const char *err_msg)
{
	fprintf(stderr, "ERROR %d: %s\n", err_num, err_msg);
	// TODO: close file handles here
	exit(EXIT_FAILURE);
}

int warning_error(const int err_num, const char *err_msg)
{
	fprintf(stderr, "WARNING: %d: %s\n", err_num, err_msg);
}

int main(int argc, char *argv[])
{
	printf("%d\n", argc);
	if(argc != 2) { exit_error('1', "No Input Files"); }
	// TODO: future versions will accept more than one file
	if(argc > 2) {exit_error('2', "Too Many Files Listed"); }

	return 0;
}

