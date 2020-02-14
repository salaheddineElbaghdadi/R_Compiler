#ifndef GLOBAL
#define GLOBAL
#include<stdio.h>
#define KEYWORDS_LIST_SIZE 46

#define MAXSIZE 10000


FILE *f;
char buffer[MAXSIZE];
char nextChar;
int offssetBuffer ;



typedef enum _bool {
  false, true
} bool;

typedef enum _tokens {
  // Other tokens ??
  NOTHING = -1,

  // keyword tokens
  IF_TOKEN,
  ELSE_TOKEN,
  REPEAT_TOKEN,
  WHILE_TOKEN,
  FUNCTION_TOKEN,
  FOR_TOKEN,
  IN_TOKEN,
  NEXT_TOKEN,
  BREAK_TOKEN,
  TRUE_TOKEN,
  FALSE_TOKEN,
  NULL_TOKEN,
  INF_TOKEN,
  NAN_TOKEN,
  NA_TOKEN,
  NA_INTEGER_TOKEN,
  NA_REAL_TOKEN,
  NA_COMPLEX_TOKEN,
  NA_CHARACTER_TOKEN,

  // Symbol tokens
  PLUS_TOKEN,
  SUBSTRACT_TOKEN,
  MULTIPLY_TOKEN,
  DEVIDE_TOKEN,
  MODULO_TOKEN,
  QUOTIENT_TOKEN,
  POWER_TOKEN,
  LESS_TOKEN,
  GREATER_TOKEN,
  EQUAL_TOKEN,
  LESS_EQUAL_TOKEN,
  GREATER_EQUAL_TOKEN,
  NOT_EQUAL_TOKEN,
  AND_TOKEN,
  OR_TOKEN,
  NOT_TOKEN,
  LOGICAL_AND_TOKEN,
  LOGICAL_OR_TOKEN,
  LEFT_ASSIGN_TOKEN,
  RIGHT_ASSIGN_TOKEN,
  OPENING_PARENTHESES_TOKEN,
  CLOSING_PARENTHESES_TOKEN,
  OPENING_SQUARE_BRACKETS_TOKEN,
  CLOSING_SQUARE_BRACKETS_TOKEN,
  OPENING_CURLY_BRACKETS_TOKEN,
  CLOSING_CURLY_BRACKETS_TOKEN,
  SEMICOLON_TOKEN,

  // Special tokens
  ID_TOKEN,
  STRING_TOKEN,
  NUMERIC_TOKEN,
  INTEGER_TOKEN,
  COMPLEX_TOKEN,

  // Separator token
  SEPARATOR_TOKEN,
  
  EOF_TOKEN,
  COMMENT_TOKEN
} tokens;

tokens token ;

#endif
