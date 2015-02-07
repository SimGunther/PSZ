/*
 * Tokenizer.h
 *
 *  Created on: Jan. 2015
 *      Author: Kevin
 */

#ifndef TOKENIZER_H_
#define TOKENIZER_H_

typedef enum {
		//Fill with token values
} TokenType;

static const char *keywords[] = {
		//Fill with keywords
};

typedef union {
	long long i; 	//Integer data
	float f;		//Decimal data
} TokenData;

typedef struct {
	TokenType type;    /**< The type of token. */
	TokenData data;    /**< The stored data of type \a type. */
	char *image;       /**< The characters that comprise the token. */
	const char *fname; /**< The name of the file containing the token. */
	unsigned int line; /**< The line number the token was on. */
} Token;

class Tokenizer {
public:
	Tokenizer();
	virtual ~Tokenizer();

	int isInteger(const char *);
	int isFloat(const char *);
	int isString(const char *);
	int isIdentifier(const char *);
	Token *isKeyword(LexemeList *, unsigned int *);

	Token *createToken(TokenType, const char *, const char *, unsigned int);
	void deleteToken(Token *);
	int addToken(Token ***, unsigned int *, Token*);
	void deleteTokens(Token **);
	unsigned int acceptLexemes(LexemeList *, unsigned int, const char *);

	Token **tokenizeLexemes(LexemeList *);
};

#endif /* TOKENIZER_H_ */
