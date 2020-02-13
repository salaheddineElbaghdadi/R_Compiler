#ifndef LEXICAL
#define LEXICAL

#include "global.h"

static char keywords[TOKEN_LIST_SIZE][20] = {
    // Keywords used in the language
    "if",	  //0
    "else",
    "repeat",
    "while",
    "function",
    "for",
    "in",
    "next",
    "break",
    "TRUE",
    "FALSE",
    "NULL",
    "Inf",
    "NaN",
    "NA",
    "NA_integer_",
    "NA_real_",
    "NA_complex_",
    "NA_character_",
    
    // Operators used in the language
    "+",
    "-",
    "*",
    "/",
    "%%",
    "%/%",
    "^",
    ">",
    "<",
    "==",
    "<=",
    ">=",
    "!=",
    "&",
    "|",
    "!",
    "&&",
    "||",
    "<-",
    "=",
    "<<-",
    "->",
    "->>",

    // Other symbols in the language
    "(",
    ")",
    "[",
    "]",
    "{",
    "}",
    "~",
    "?",
    "@",
    :q
    :q
    :q


    "$",
    ";"


    /*
    ":",
    "%in%",
    "%*%"
    */
};

static bool getNextToken();
static void getNextChar();
static bool isNumber();
static bool isSpecial();
static bool isChar();
static bool isEOF();

static void readNumber();
static void readWord();
static void readSpecial();
static void readError();
static void readSeparator();

#endif
