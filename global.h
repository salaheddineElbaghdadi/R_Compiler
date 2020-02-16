#ifndef GLOBAL
#define GLOBAL
#include<stdio.h>
#define KEYWORDS_LIST_SIZE 47

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
  IF_TOKEN, //0
  ELSE_TOKEN, //1
  REPEAT_TOKEN,//2
  WHILE_TOKEN,//3
  FUNCTION_TOKEN,//4
  FOR_TOKEN,//5
  IN_TOKEN,//6
  NEXT_TOKEN,//7
  BREAK_TOKEN,//8
  TRUE_TOKEN,//9
  FALSE_TOKEN,//10
  NULL_TOKEN,//11
  INF_TOKEN,//12
  NAN_TOKEN,//13
  NA_TOKEN,//14
  NA_INTEGER_TOKEN,//15
  NA_REAL_TOKEN,//16
  NA_COMPLEX_TOKEN,//17
  NA_CHARACTER_TOKEN,//18

  // Symbol tokens
  PLUS_TOKEN,//19
  SUBSTRACT_TOKEN,//20
  MULTIPLY_TOKEN,//21
  DEVIDE_TOKEN,//22
  MODULO_TOKEN,//23
  QUOTIENT_TOKEN,//24
  POWER_TOKEN,//25
  LESS_TOKEN,//26
  GREATER_TOKEN,//27
  EQUAL_TOKEN,//28
  LESS_EQUAL_TOKEN,//29
  GREATER_EQUAL_TOKEN,//30
  NOT_EQUAL_TOKEN,//31
  AND_TOKEN,//32
  OR_TOKEN,//33
  NOT_TOKEN,//34
  LOGICAL_AND_TOKEN,//35
  LOGICAL_OR_TOKEN,//36
  LEFT_ASSIGN_TOKEN,//37
  RIGHT_ASSIGN_TOKEN,//38
  OPENING_PARENTHESES_TOKEN,//39
  CLOSING_PARENTHESES_TOKEN,//40
  OPENING_SQUARE_BRACKETS_TOKEN,//41
  CLOSING_SQUARE_BRACKETS_TOKEN,//42
  OPENING_CURLY_BRACKETS_TOKEN,//43
  CLOSING_CURLY_BRACKETS_TOKEN,//44
  SEMICOLON_TOKEN,//45
  COMMA_TOKEN,//46

  // Special tokens
  ID_TOKEN,//47
  STRING_TOKEN,//48
  NUMERIC_TOKEN,//49
  INTEGER_TOKEN,//50
  COMPLEX_TOKEN,//51

  // Separator token
  SEPARATOR_TOKEN,//52
  EOL_TOKEN,//53
  
  EOF_TOKEN,//54
  COMMENT_TOKEN //55
} tokens;

tokens token ;

#endif
