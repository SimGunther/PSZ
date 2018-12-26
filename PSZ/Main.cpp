/*
 * Main.cpp
 *
 *  Created on: Jan. 2015
 *      Author: Mr. SG
 */

#include "Main.h"
using namespace std;

//Current version of this interpreter is v0.01
char *revision = "v0.01";
char *programName;
#define READSIZE 512

//List of options from getopt, long and short
static char *shortopt = "hv";
static struct option longopt[] = {
	{ "help", no_argument, NULL, (int)'h' },
	{ "version", no_argument, NULL, (int)'v' },
	{ 0, 0, 0, 0 }
};

/**
 * Message to display the help message
 * and how to use Objective-CASM
 */
static void help(void) {
	fprintf(stderr, "\
Usage: %s [FILE] ... \n\
Interpret FILE(s) as Objective-CASM code. Let FILE be '-' for stdin.\n\
  -h, --help\t\toutput this help\n\
  -v, --version\t\tprogram version\n", programName);
}
/**
 * Displays the current working version of Objective-CASM
 */
static void version (char *revision1) {
	printf("%s %s\n", programName, revision1);
}


/**
 * Main driver of Compilation
 */
int main(int argc, char **argv) {
	//Import classes here
	Lexer lex;
	Tokenizer token;
	Error err;

	//Initialize all variables here..
	int ch;
	unsigned int size = 0;
	unsigned int length = 0;
	char *buffer = NULL;
	LexemeList *lexList = NULL;
	Token **tokens = NULL;
	MainNode *node = NULL;
	char *fname = NULL;
	FILE *file = NULL;

	programName = argv[0];

	//while loop to get options from command prompt
		while((ch = getopt_long(argc, argv, shortopt, longopt, NULL)) != -1) {
		   switch(ch) {
			   default:
				   help();
					exit(EXIT_FAILURE);
				case 'h':
				   help();
				   exit(EXIT_SUCCESS);
				case 'v':
				   version(revision);
				   exit(EXIT_SUCCESS);
			}
		}

		//loop here
		for (; optind < argc; optind++) {
			size = length = 0;
			buffer = fname = NULL;
			lexList = NULL;
			file = NULL;

			if (!strncmp(argv[optind],"-\0",2)) {
				file = stdin;
				fname = "stdin";
			}
			else {
				file = fopen(argv[optind], "r");
				fname = argv[optind];
			}

			if (!file) {
				err.error(MN_ERROR_OPENING_FILE, argv[optind]);
				return 1;
			}

			while (!feof(file)) {
				size += READSIZE;
				buffer = (char *)realloc(buffer, sizeof(char) * size);
				length += fread((buffer + size) - READSIZE,
						1,
						READSIZE,
						file);
			}

			if (fclose(file) != 0) {
				err.error(MN_ERROR_CLOSING_FILE, argv[optind]);
				if (buffer) free(buffer);
				return 1;
			}
			if (!buffer) return 1;
			buffer[length] = '\0';

			/* Remove hash bang line if run as a standalone script */
			if (buffer[0] == '#' && buffer[1] == '!') {
				unsigned int n;
				for (n = 0; buffer[n] != '\n' && buffer[n] != '\r'; n++)
					buffer[n] = ' ';
			}

			/*
			 * Remove UTF-8 BOM if present and add it to the output stream
			 * (we assume here that if a BOM is present, the system will
			 * also expect the output to include a BOM).
			 */
			if (buffer[0] == (char)0xef
					|| buffer[1] == (char)0xbb
					|| buffer[2] == (char)0xbf) {
				buffer[0] = ' ';
				buffer[1] = ' ';
				buffer[2] = ' ';
				printf("%c%c%c", 0xef, 0xbb, 0xbf);
			}

			/* Begin main pipeline */
			if (!(lexList = lex.scanBuffer(buffer, length, fname))) {
				free(buffer);
				return 1;
			}
			free(buffer);
			if (!(tokens = token.tokenizeLexemes(lexList))) {
				lex.deleteLexemeList(lexList);
				return 1;
			}
			lex.deleteLexemeList(lexList);
			if (!(node = parseMainNode(tokens))) {
				token.deleteTokens(tokens);
				return 1;
			}
			token.deleteTokens(tokens);
			if (interpretMainNode(node)) {
				deleteMainNode(node);
				return 1;
			}
			deleteMainNode(node);
			/* End main pipeline */

		}
	return EXIT_SUCCESS;
}

Main::Main() {
	//LEAVE THIS BLANK!!
}

Main::~Main() {
	//LEAVE THIS BLANK!!
}
