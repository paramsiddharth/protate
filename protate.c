/*

  PROTATE
  Rotates each character in an ASCII text file by a certain order.
  Author: Param Siddharth.

*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <wchar.h>
#include <assert.h>

#define NDEBUG

// Global variables to be used

FILE* inFile = NULL, 
		* outFile = NULL;

bool hasOutputFilename = false,
	toPreview = false,
	helpWanted = false, 
	numFound = false;

long long int rotNum = 0;

wchar_t* usage = L"PROTATE\n\
Rotates each character in an ASCII text file by a certain order.\n\
Usage: protate FILE_IN N [-o] [FILE_OUT] [-p] [--h, --help, /?]\n\n\
 FILE_IN\tThe input file.\n\
 N\tThe number of ASCII character rotations to do in each character. A negative value would indicate negative rotation.\n\
 -o FILE_OUT\tWould output the result generated from FILE_IN to FILE_OUT. If omitted, the output would be written to ./a.out.\n\
 -p\tPreviews the output instead of saving it to a file.\n\
 --h, --help, /?\tShow usage help.\n\n\
Made with \u2661 by Param Siddharth.\n\n";

// Handler for the arguments
void handler(int acount, char* args[]) {
	// Determining the number of arguments
	if (acount<1) {
		fprintf(stderr,"No arguments.\n\
Use \"/?\" or \"--h\" for usage help.\n\n");
		exit(EXIT_FAILURE);
	}
	if (acount == 1) {
		char* arg = args[0];
		if (
				strcmp(arg,"--h") == 0 ||
				strcmp(arg,"--help") == 0 ||
				strcmp(arg,"/?") == 0
			) {
			helpWanted = true;
			wprintf(L"%ls",usage); // Displaying help
			exit(EXIT_SUCCESS);
		}
		if (arg[0] == '-') {
			fprintf(stderr,"Bad format.\n\
Use ./%s for the filename, and pass the number of rotations.\n\n",arg);
			exit(EXIT_FAILURE);
		}
		// Check for numerical input.
		if (strspn(arg, "-+0123456789") == strlen(arg)) {
			fprintf(stderr,"Bad format.\n\
Use ./%s for filename, and pass the number of rotations.\n\n",arg);
			exit(EXIT_FAILURE);
		}
		fprintf(stderr,"Not enough arguments. Mention the number of rotations.\n\
Use \"/?\" or \"--h\" for usage help.\n\n");
		exit(EXIT_FAILURE);
		
	} else if (acount == 2) {
		
		char* arg1 = args[0],
			* arg2 = args[1];
			
		if (strspn(arg1, "-+0123456789") == strlen(arg1)) {
			rotNum = strtol(arg1, (char**)NULL, 10) % 256;
			numFound = true;
		} else if (arg1[0] == '-') {
			fprintf(stderr,"Bad format.\n\
Use ./%s for the filename.\n\n",arg1);
			exit(EXIT_FAILURE);
		} else {
			inFile = fopen(arg1,"r");
			if (inFile == NULL) {
				fprintf(stderr,"Error: Cannot access file %s.\n\n",arg1);
				exit(EXIT_FAILURE);
			}
		}
		
		if (strspn(arg2, "-+0123456789") == strlen(arg2)) {
			if (numFound) {
				fprintf(stderr,"Bad format.\n\
Use ./%s for the filename.\n\n",arg2);
				exit(EXIT_FAILURE);
			}
			rotNum = strtol(arg2, (char**)NULL, 10) % 256;
			numFound = true;
		} else if (arg2[0] == '-') {
			fprintf(stderr,"Bad format.\n\
Use ./%s for the filename.\n\n",arg2);
			exit(EXIT_FAILURE);
		} else if (inFile != NULL) {
			fclose(inFile);
			fprintf(stderr,"Mention the number of rotations.\n\
Use \"/?\" or \"--h\" for usage help.\n\n");
			exit(EXIT_FAILURE);
		} else if (numFound) {
			inFile = fopen(arg2,"r");
			if (inFile == NULL) {
				fprintf(stderr,"Error: Cannot access file %s.\n\n",arg2);
				exit(EXIT_FAILURE);
			}
		} else {
			fprintf(stderr,"Bad format.\n\
Use \"/?\" or \"--h\" for usage help.\n\n");
			exit(EXIT_FAILURE);
		}
		
		outFile = fopen("a.out", "w");
		if (outFile == NULL) {
			fprintf(stderr,"Error: Cannot access file a.out.\n\n");
			exit(EXIT_FAILURE);
		}
		
	} else if (acount == 3) {
		char* arg1 = args[0],
			* arg2 = args[1],
			* arg3 = args[2];
		
		if (strspn(arg1, "-+0123456789") == strlen(arg1)) {
			rotNum = strtol(arg1, (char**)NULL, 10) % 256;
			numFound = true;
		} else if (arg1[0] == '-') {
			if (strcmp(arg1, "-p") != 0) {
				fprintf(stderr,"Bad format.\n\
Use ./%s for the filename.\n\
Use \"/?\" or \"--h\" for usage help.\n\n",arg1);
				exit(EXIT_FAILURE);
			}
			toPreview = true;
		} else {
			inFile = fopen(arg1,"r");
			if (inFile == NULL) {
				fprintf(stderr,"Error: Cannot access file %s.\n\n",arg1);
				exit(EXIT_FAILURE);
			}
			// printf("OPENED %s.",arg1);
		}
		
		if (strspn(arg2, "-+0123456789") == strlen(arg2)) {
			if (numFound) {
				fprintf(stderr,"Bad format.\n\
Use ./%s for the filename.\n\n",arg2);
				exit(EXIT_FAILURE);
			}
			rotNum = strtol(arg2, (char**)NULL, 10) % 256;
			numFound = true;
		} else if (arg2[0] == '-') {
			if (strcmp(arg2, "-p") != 0) {
					fprintf(stderr,"Bad format.\n\
Use ./%s for the filename.\n\
Use \"/?\" or \"--h\" for usage help.\n\n", arg2);
					exit(EXIT_FAILURE);
			}
			if (toPreview) {
				fprintf(stderr,"Bad format.\n\
Use ./%s for the filename.\n\
Use \"/?\" or \"--h\" for usage help.\n\n", arg2);
				exit(EXIT_FAILURE);
			}
			toPreview = true;
		} else if (inFile == NULL) {
			inFile = fopen(arg2,"r");
			if (inFile == NULL) {
				fprintf(stderr,"Error: Cannot access file %s.\n\n",arg2);
				exit(EXIT_FAILURE);
			}
		} else {
			fprintf(stderr,"Bad format.\n\
Use \"/?\" or \"--h\" for usage help.\n\n");
			exit(EXIT_FAILURE);
		}
		
		if (strspn(arg3, "-+0123456789") == strlen(arg3)) {
			if (numFound) {
				fprintf(stderr,"Bad format.\n\
Use ./%s for the filename.\n\n",arg3);
				exit(EXIT_FAILURE);
			}
			rotNum = strtol(arg3, (char**)NULL, 10) % 256;
			numFound = true;
		} else if (arg3[0] == '-') {
			if (strcmp(arg3, "-p") != 0) {
					fprintf(stderr,"Bad format.\n\
Use ./%s for the filename.\n\
Use \"/?\" or \"--h\" for usage help.\n\n", arg3);
			}
			if (toPreview) {
				fprintf(stderr,"Bad format.\n\
Use ./%s for the filename.\n\
Use \"/?\" or \"--h\" for usage help.\n\n", arg3);
				exit(EXIT_FAILURE);
			}
			toPreview = true;
		} else if (inFile == NULL) {
			inFile = fopen(arg3,"r");
			if (inFile == NULL) {
				fprintf(stderr,"Error: Cannot access file %s.\n\n",arg3);
				exit(EXIT_FAILURE);
			}
		} else {
			fprintf(stderr,"Bad format.\n\
Use \"/?\" or \"--h\" for usage help.\n\n");
			exit(EXIT_FAILURE);
		}
		
		if (!toPreview) {
			outFile = fopen("a.out", "w");
			if (outFile == NULL) {
				fprintf(stderr,"Error: Cannot access file a.out.\n\n");
				exit(EXIT_FAILURE);
			}
		}
	} else if (acount == 4) {
		
		char* arg = args[0];
		int argi = 0;
		bool skipNext = false;
		
		if (strspn(arg, "-+0123456789") == strlen(arg)) {
			rotNum = strtol(arg, (char**)NULL, 10) % 256;
			numFound = true;
		} else if (arg[0] == '-') {
			if (strcmp(arg, "-o") == 0 && argi < 3) {
				skipNext = true;
			} else {
				fprintf(stderr,"Bad format.\n\
Use \"/?\" or \"--h\" for usage help.\n\n");
				exit(EXIT_FAILURE);
			}
		} else {
			inFile = fopen(arg,"r");
			if (inFile == NULL) {
				fprintf(stderr,"Error: Cannot access file %s.\n\n",arg);
				exit(EXIT_FAILURE);
			}
		}
		
		arg = args[++argi];
		
		if (skipNext) {
			outFile = fopen(arg, "w");
			if (outFile == NULL) {
				fprintf(stderr,"Error: Cannot access file %s.\n\n", arg);
				exit(EXIT_FAILURE);
			}
			skipNext = false;
		} else if (strspn(arg, "-+0123456789") == strlen(arg)) {
			if (numFound) {
				fprintf(stderr,"Bad format.\n\
Use ./%s for the filename.\n\n",arg);
				exit(EXIT_FAILURE);
			}
			rotNum = strtol(arg, (char**)NULL, 10) % 256;
			numFound = true;
		} else if (arg[0] == '-') {
			if (strcmp(arg, "-o") == 0 && outFile == NULL) {
				skipNext = true;
			} else {
				fprintf(stderr,"Bad format.\n\
Use \"/?\" or \"--h\" for usage help.\n\n");
				exit(EXIT_FAILURE);
			}
		} else if (inFile == NULL) {
			inFile = fopen(arg,"r");
			if (inFile == NULL) {
				fprintf(stderr,"Error: Cannot access file %s.\n\n",arg);
				exit(EXIT_FAILURE);
			}
		} else {
			fprintf(stderr,"Bad format.\n\
Use \"/?\" or \"--h\" for usage help.\n\n");
			exit(EXIT_FAILURE);
		}
		
		arg = args[++argi];
		
		if (skipNext) {
			outFile = fopen(arg, "w");
			if (outFile == NULL) {
				fprintf(stderr,"Error: Cannot access file %s.\n\n", arg);
				exit(EXIT_FAILURE);
			}
			skipNext = false;
		} else if (strspn(arg, "-+0123456789") == strlen(arg)) {
			if (numFound) {
				fprintf(stderr,"Bad format.\n\
Use ./%s for the filename.\n\n",arg);
				exit(EXIT_FAILURE);
			}
			rotNum = strtol(arg, (char**)NULL, 10) % 256;
			numFound = true;
		} else if (arg[0] == '-') {
			if (strcmp(arg, "-o") == 0 && outFile == NULL) {
				skipNext = true;
			} else {
				fprintf(stderr,"Bad format.\n\
Use \"/?\" or \"--h\" for usage help.\n\n");
				exit(EXIT_FAILURE);
			}
		} else if (inFile == NULL) {
			inFile = fopen(arg,"r");
			if (inFile == NULL) {
				fprintf(stderr,"Error: Cannot access file %s.\n\n",arg);
				exit(EXIT_FAILURE);
			}
		} else {
			fprintf(stderr,"Bad format.\n\
Use \"/?\" or \"--h\" for usage help.\n\n");
			exit(EXIT_FAILURE);
		}
		
		arg = args[++argi];
		
		if (skipNext) {
			outFile = fopen(arg, "w");
			if (outFile == NULL) {
				fprintf(stderr,"Error: Cannot access file %s.\n\n", arg);
				exit(EXIT_FAILURE);
			}
			skipNext = false;
		} else if (strspn(arg, "-+0123456789") == strlen(arg)) {
			if (numFound) {
				fprintf(stderr,"Bad format.\n\
Use ./%s for the filename.\n\n",arg);
				exit(EXIT_FAILURE);
			}
			rotNum = strtol(arg, (char**)NULL, 10) % 256;
			numFound = true;
		} else if (arg[0] == '-') {
			fprintf(stderr,"Bad format.\n\
Use \"/?\" or \"--h\" for usage help.\n\n");
			exit(EXIT_FAILURE);
		} else if (inFile == NULL) {
			inFile = fopen(arg,"r");
			if (inFile == NULL) {
				fprintf(stderr,"Error: Cannot access file %s.\n\n",arg);
				exit(EXIT_FAILURE);
			}
		} else {
			fprintf(stderr,"Bad format.\n\
Use \"/?\" or \"--h\" for usage help.\n\n");
			exit(EXIT_FAILURE);
		}
		
	} else {
		fprintf(stderr, "Too many arguments.\n\
Use \"/?\" or \"--h\" for usage help.\n\n");
		exit(EXIT_FAILURE);
	}
}

int main(int argc, char *argv[]) {
	handler(argc - 1, argv + 1);
	assert(inFile != NULL);
	while (rotNum < 0) rotNum += 256; // Converting the rotation order to a whole number
	
	if (toPreview) {
		int c;
		while ((c = getc(inFile)) != EOF) {
			printf("%c", (char)(c+rotNum)%256);
		} // Previewing the result
	} else {
		int c;
		while ((c = getc(inFile)) != EOF) {
			fprintf(outFile,"%c", (char)(c+rotNum)%256);
		} // Writing the result to the output file
	}
	
	// Closing the files
	fclose(inFile);
	if (outFile != NULL) fclose(outFile);
	
	return 0;
}