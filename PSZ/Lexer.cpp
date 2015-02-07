/*
 * Lexer.cpp
 *
 *  Created on: Jan. 2015
 *      Author: Kevin
 */

#include "Lexer.h"

/**
 * Constructor of this class (Lexer.cpp)
 */
Lexer::Lexer() {
	//LEAVE THIS BLANK!!
}

/**
 * Deconstructor of this class (Lexer.cpp)
 */
Lexer::~Lexer() {
	//LEAVE THIS BLANK!!
}

/**
 * Creates a lexeme
 *
 * @param image The string identifying the lexeme.
 * @param fName The name of the file containing the lexeme.
 * @param lineNum The line number where the lexeme occurred.
 *
 * @return Returns the created lexeme.
 */
Lexeme* Lexer::createLexeme(char* image, const char* fName,
		unsigned int lineNum) {
	//Creates lexeme
	Lexeme *lex = (Lexeme *)malloc(sizeof(Lexeme));
	if(!lex) {
		printf("Error: Could not create lexeme\n");
		return NULL;
	}

	//Stores image into new lexeme
	lex->image = (char *)malloc(sizeof(char) * (strlen(image) + 1));
	if(!(lex->image)) {
		free(lex);
		printf("Error: Could not store image to lex\n");
		return NULL;
	}
	strcpy(lex->image, image);

	//We can store filename and line number onto lexeme
	lex->fname = fName;
	lex->line = lineNum;
#ifdef DEBUG
	fprintf(stderr, "Creating lexeme[%s]\n", image);
#endif
	return lex;
}

/**
 * Deletes the lexeme
 *
 * @param lexeme The lexeme to be deleted
 */
void Lexer::deleteLexeme(Lexeme* lexeme) {
	//Free image if lexeme exists
	if(!lexeme) return;
	free(lexeme->image);

	//We don't free file name from lexeme
	free(lexeme);
}

/**
 * Constructor for the list of lexemes
 *
 * @return A new empty lexeme list.
 * @return NULL if memory allocation failed.
 */
LexemeList* Lexer::createLexemeList(void) {
	//Allocate memory for LexemeList
	LexemeList *p = (LexemeList *)malloc(sizeof(LexemeList));
	if(!p) {
		printf("Error: Could not allocate memory for LexemeList\n");
		return NULL;
	}

	//Initialize number of lexemes and blank list of lexemes
	p->num = 0;
	p->lexemes = NULL;
	return p;
}

/**
 * Adds a lexeme to the list of lexemes
 *
 * @param list The list of lexemes to add the new lexeme to.
 * @param lexeme The new lexeme to add to the lexeme list.
 *
 * @post lexeme will be added to the end of list and the size
 * of list will be updated.
 *
 * @return A pointer to the added lexeme (which will be the same as lexeme)
 * @return NULL if memory alloction failed.
 */
Lexeme* Lexer::addLexeme(LexemeList* list, Lexeme* lexeme) {
	//initialize temporary variables
	unsigned int newsize;
	void *mem = NULL;
	if(!list) return NULL;

	//If it is a valid list, Do the following
	newsize = list->num + 1;
	mem = realloc(list->lexemes, sizeof(Lexeme *) * newsize);
	if(!mem) {
		printf("Error: could not reallocate memory for LexemeList\n");
		return NULL;
	}

	//If memory could reallocate, reinitialize list
	list->lexemes = (Lexeme **)mem;
	list->lexemes[list->num] = lexeme;
	list->num = newsize;
	return lexeme;
}

/**
 * Deletes a list of lexemes
 *
 * @param list The list of lexemes to delete from memory
 *
 * @post The memory at list and all of its members will be freed.
 */
void Lexer::deleteLexemeList(LexemeList* list) {
	//Validate the lexeme list
	if(!list) return;

	//If it is valid, free all memory inside lexeme list
	for(unsigned int i = 0; i < list->num; i++)
		deleteLexeme(list->lexemes[i]);
	free(list->lexemes);
	free(list);
}

/**
 * Scans a buffer, removing unnecessary characters and grouping characters into lexemes.
 * Lexemes are strings of characters separated by whitespace (although
 * newline characters are considered separate lexemes).  String literals are
 * handled a bit differently:  Starting at the first quotation character,
 * characters are collected until either a non-escaped quotation character is
 * read (i.e., a quotation character not preceded by a colon which itself is not
 * preceded by a colon) or a newline or carriage return character is read,
 * whichever comes first.
 *
 * @param buffer The characters to turn into lexemes.
 * @param size The number of characters in buffer
 * @param fName The name of the file buffer was read from.
 *
 * @return A list of lexemes created from the contents of buffer.
 */
LexemeList* Lexer::scanBuffer(char* buffer, unsigned int size,
		char* fname) {
	//Initialize temporary variables
	const char *start = buffer;
	LexemeList *list = NULL;
	unsigned int line = 1;
	if(!list) return NULL;

	//starts buffer scan
	while(start < buffer + size) {
		char *temp = NULL;
		unsigned int len = 1;
		/* */
	}

	return NULL;
}
