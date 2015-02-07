/*
 * Tokenizer.cpp
 *
 *  Created on: Jan 20, 2015
 *      Author: Kevin-Lenovo
 */

#include "Tokenizer.h"

Tokenizer::Tokenizer() {
	// TODO Auto-generated constructor stub

}

Tokenizer::~Tokenizer() {
	// TODO Auto-generated destructor stub
}

int Tokenizer::isInteger(const char* tok) {
}

int Tokenizer::isFloat(const char* tok) {
}

int Tokenizer::isString(const char* tok) {
}

int Tokenizer::isIdentifier(const char* tok) {
}

Token* Tokenizer::isKeyword(LexemeList* lexList, unsigned int* start) {
}

Token* Tokenizer::createToken(TokenType type, const char* tok,
		const char* fname, unsigned int lineNum) {
}

void Tokenizer::deleteToken(Token* tok) {
}

int Tokenizer::addToken(Token*** list, unsigned int* num, Token* tok) {
}

void Tokenizer::deleteTokens(Token** list) {
}

unsigned int Tokenizer::acceptLexemes(LexemeList* lexemes, unsigned int start,
		const char* match) {
}

Token** Tokenizer::tokenizeLexemes(LexemeList* list) {
}
