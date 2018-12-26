/*
 * Lexer.h
 *
 *  Created on: Jan. 2015
 *      Author: Mr. SG
 */

#ifndef LEXER_H_
#define LEXER_H_

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

/**
 * Stores a lexeme.  A lexeme is a group of contiguous characters, stripped of
 * surrounding whitespace or other lexemes.
 */
typedef struct {
	char *image;       // The string that identifies the lexeme.
	const char *fname; // The name of the file containing the lexeme.
	unsigned int line; // The line number the lexeme occurred on.
} Lexeme;

/**
 * Stores a list of lexemes.
 */
typedef struct {
	unsigned int num; // The number of lexemes stored.
	Lexeme **lexemes; // The array of stored lexemes.
} LexemeList;

class Lexer {
public:
	Lexer();
	virtual ~Lexer();

	/**
	 * Helper functions for lexeme construction/destruction
	 */
	static Lexeme *createLexeme(char *, const char *, unsigned int);
	static void deleteLexeme(Lexeme *);
	static LexemeList *createLexemeList(void);
	static Lexeme *addLexeme(LexemeList *, Lexeme*);
	static void deleteLexemeList(LexemeList *);

	/**
	 * Generates lexemes from a character buffer.
	 */
	static LexemeList *scanBuffer(char *, unsigned int, char *);
};

#endif /* LEXER_H_ */
