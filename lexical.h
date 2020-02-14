#ifndef LEXICAL
#define LEXICAL

#include "global.h"

static char keywords[KEYWORDS_LIST_SIZE][20] = {
    // Keywords used in the language
    "if",	  //1
    "else",
    "repeat",
    "while",
    "function",	  //5
    "for",
    "in",
    "next",
    "break",
    "TRUE",	  //10
    "FALSE",
    "NULL",
    "Inf",
    "NaN",
    "NA",	  //15
    "NA_integer_",
    "NA_real_",
    "NA_complex_",
    "NA_character_",
    
    // Operators used in the language
    "+",	  //20
    "-",
    "*",
    "/",
    "%%",
    "%/%",	  //25
    "^",
    ">",
    "<",
    "==",
    "<=",	  //30
    ">=",
    "!=",
    "&",
    "|",
    "!",	  //35
    "&&",
    "||",
    "<-",
    //"=", //"<<-",
    "->",
    //"->>",

    // Other symbols in the language
    "(",	  //40
    ")"		  //41
    /*
    "[",
    "]",
    "{",
    "}",
    "~",
    "?",
    "@",
    "$",
    ";"
    */


    /*
    ":",
    "%in%",
    "%*%"
    */
};

static bool get_next_token();
static void get_next_char();

static bool is_number();
static bool is_special();
static bool is_char();
static bool is_legal_char();
static bool is_EOF();
static bool is_separator();
static bool is_comment();
static bool is_end_of_line();
static bool is_double_quote();
static bool is_single_quote();
static bool is_legal_numeric();

static void read_number();
static void read_word();
static void read_special();
static void read_error();
static void read_separator();
static void read_comment();
static void read_string();
static void read_EOF();

#endif
