#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAXINBUFF 10000
#define MAXOUTBUFF 10000

FILE *pInfile;
FILE *pOutfile;

void dump_buffer(const char *buffer)
{
	int i = 0;
	while(buffer[i] != '\0')
	{
		printf("%c", buffer[i++]);
	}
	printf("\n");
}

void exit_error(const int err_num, const char *err_msg)
{
	fprintf(stderr, "ERROR %d: %s\n", err_num, err_msg);
	if(pInfile != NULL) { fclose(pInfile); }
	if(pOutfile != NULL) { fclose(pOutfile); }
	exit(EXIT_FAILURE);
}

int warning_error(const int err_num, const char *err_msg)
{
	fprintf(stderr, "WARNING: %d: %s\n", err_num, err_msg);
}

int main(int argc, char *argv[])
{
	char InBuff[MAXINBUFF]; // = { '\0' }; // input stored here
	char OutBuff[MAXINBUFF]; // = { '\0' }; // output stored here
	char FilenameBuff[80];

	int i = 0;
	int k = 0;

	if(argc != 2) { exit_error(1, "No Input Files"); }
	// TODO: future versions will accept more than one file
	if(argc > 2) { exit_error(2, "Too Many Files Listed"); }

	strcpy(FilenameBuff, argv[1]);

	// verify filename extension of file
	i = strlen(FilenameBuff) - 1;
	if( 	(FilenameBuff[i-2] != 'a') ||
		(FilenameBuff[i-1] != 's') ||
		(FilenameBuff[i]   != 'm' ) ) { exit_error(5, "Filename Extension Not Correct"); }

	if((pInfile = fopen(FilenameBuff, "rb")) == NULL)
		exit_error(3, "Cannot Open Input (Source) File");

	k = 0;
	while(!feof(pInfile) && k < MAXINBUFF)
		InBuff[k++] = fgetc(pInfile);

	if(k < MAXINBUFF)
	{
		printf("Input Buffer Loaded\n");
	} else {
		exit_error(4, "Input Too Large for Input Buffer");
	}

	// modify filename to output filename and then open file
	FilenameBuff[i-2] = 'h';
	FilenameBuff[i-1] = 'a';
	FilenameBuff[i]   = 'c';
	FilenameBuff[i+1] = 'k';
	FilenameBuff[i+2] = '\0';

	if((pOutfile = fopen(FilenameBuff, "w")) == NULL)
		exit_error(6, "Cannot Open Output (Destination) File");

	// TODO: verify output buffer has not been overflowed

	return 0;
}
