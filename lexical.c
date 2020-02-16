#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "global.h"
#include "lexical.h"

void init(){
  nextChar=' ';
}




bool is_separator(){
  switch (nextChar){
    case ' ': return true;
    //case '\n':	return true;
    case '\r' :	return true;
    case ';' :	return true;
    default :
    return false;
  }

}


void assignToken(tokens _token) {
  if (_token == NOTHING) {
    for (int i = 0; i < KEYWORDS_LIST_SIZE; i++) {
      if (strcmp(buffer, keywords[i]) == 0) {
        token = i;
        return;
      }
    }
    token = ID_TOKEN;
    return;
  }
  token = _token;
}

void addChartoBuffer(){
	buffer[offssetBuffer++]= nextChar;
	buffer[offssetBuffer]= '\0'; 
}

char what_is_next() {
  char original = nextChar;
  //printf("original %c\n", original);
  get_next_char();
  char next = nextChar;
  //printf("next %c\n", next);
  fseek(f, -1, SEEK_CUR);
  nextChar = original;
  //printf("next char %c\n", nextChar);
  return next;
}

void clearBuffer(){
	offssetBuffer=0;
	buffer[offssetBuffer]= '\0';
}

void get_next_char(){
	nextChar= getc(f);
}

bool get_next_token(){
	
	do {
	  clearBuffer();
	  if(is_number()) {
      //printf("is reading number\n");
	    read_number();
    }
	  else if (is_legal_char()) {
      //printf("is reading legal character\n");
	    read_word();
    }
    else if (is_comment()) {
      read_comment();
    }
    else if (is_single_quote()) {
      read_string();
    }
    else if (is_double_quote()) {
      read_string();
    }
    else if (is_end_of_line()) {
      read_end_of_line();
    }
	  else if( is_special()) {
      //printf("is reading special\n");
	    read_special();
      //printf(" ----- buffer %s\n", buffer);
    }
	  else if (is_separator()) {
      //printf("is reading separator\n");
	    read_separator();
    }
	  else if(is_EOF()) {
      //printf("is reading EOF\n");
      if (token == EOF_TOKEN) {
        return false;
      }
      read_EOF();
	    //return false;
      return true;
    }
	  else
	    read_error();
	} while(offssetBuffer ==0);
	return true;
}

bool is_number(){
	if(nextChar>='0' && nextChar<='9'){
		return true ;
	}
	else
		return false;	
}

bool is_legal_numeric() {
  if (nextChar == '.' || nextChar == 'L')
    return true;
  else
    return false;
}

bool is_char(){
	if((nextChar>='a' && nextChar<='z')| (nextChar>='A' && nextChar<='Z') ){
		return true ;
	}
	else
		return false;	
}

bool is_legal_char() {
  if (nextChar == '_' || is_char())
    return true;
  else
    return false;
}

bool is_special(){
	switch(nextChar){
		case '+':
      return true;
    case '-':
      return true;
    case '*':
      return true;
    case '/':
      return true;  
    case '%':
      return true;
    case '^':
      return true;
    case '>':
      return true;
    case '<':
      return true;
    case '=':
      return true;
    case '!':
      return true;
    case '|':
      return true;       
    case '&':
      return true;
    case '(':
      return true;
    case ')':
      return true;
    case '[':
      return true;
    case ']':
      return true;
    case '{':
      return true;
    case '}':
      return true;
    case ';':
      return true;
    case ',':
      return true;
	}
	return false;

}

bool is_double_quote() {
  if (nextChar == '"')
    return true;
  else
    return false;
}

bool is_single_quote() {
  if (nextChar == '\'')
    return true;
  else
    return false;
}

bool is_comment() {
  if (nextChar == '#')
    return true;
  else
    return false;
}

bool is_end_of_line() {
  if (nextChar == '\n')
    return true;
  else
    return false;
}

bool is_EOF(){
  if(nextChar == EOF ){
    return true ;
  }
  else
    return false;	
}

void read_word(){
	do {
			addChartoBuffer();
			get_next_char();

	}while (is_char() || is_number() || is_legal_char());
  assignToken(NOTHING);
}


void read_number(){
	do {
			addChartoBuffer();
			get_next_char();

	}while ( is_number());
  assignToken(NUMERIC_TOKEN);
}

/*
void read_number() {
  do {

    if (is_legal_numeric()) {
      // Numeric / Real if we read '.'
      if (nextChar == '.') {
        do {
          addChartoBuffer();
          get_next_char();
        } while (is_number());
        assignToken(NUMERIC_TOKEN);
        return ;
      }

      if (nextChar == 'L') {
        addChartoBuffer();
        get_next_char();
        assignToken(INTEGER_TOKEN);
        return;
      }

      token = NUMERIC_TOKEN;
    }

    addChartoBuffer();
    get_next_char();
  } while (is_number() || is_legal_numeric());
}*/

void read_string() {
  if (is_double_quote()) {
    do {
      addChartoBuffer();
      get_next_char();
    } while (!is_double_quote());
    addChartoBuffer();
    get_next_char();
  }
  else if (is_single_quote()) {
    do {
      addChartoBuffer();
      get_next_char();
    } while (!is_single_quote());
    addChartoBuffer();
    get_next_char();
  }
  assignToken(STRING_TOKEN);
}

void read_end_of_line() {
  do {
    addChartoBuffer();
    get_next_char();
  } while(is_end_of_line());
  assignToken(EOL_TOKEN);
}

/*
void read_special() {
  do {
    //printf("is spetical\n");
    addChartoBuffer();
    get_next_char();
  } while (is_special());
  assignToken(NOTHING);
}*/

/*
void read_special() {
  addChartoBuffer();
  char first_special = nextChar;
  printf("== buffer %s == current char %c\n", buffer, first_special);
  get_next_char();
  printf("reading special\n");
  printf("buffer %s\n", buffer);

  if (is_special()) {
    printf("second is special\n");
    if (nextChar == '=') {
      switch (first_special)
      {
      case '=':
      case '<':
      case '>':
      case '!':
        addChartoBuffer();
        assignToken(NOTHING);
        get_next_char();
        break;
      }
    }
    else if (nextChar == '&' && first_special == '&') {
      addChartoBuffer();
      assignToken(NOTHING);
      get_next_char();
    }
    else if (nextChar == '|' && first_special == '|') {
      addChartoBuffer();
      assignToken(NOTHING);
      get_next_char();
    }
    else if (nextChar == '-' && first_special == '<') {
      addChartoBuffer();
      assignToken(NOTHING);
      get_next_char();
    }
    else if (nextChar == '>' && first_special == '-') {
      addChartoBuffer();
      assignToken(NOTHING);
      get_next_char();
    }
    else {
      printf("else\n");
      previous();
      get_next_char();
      clearBuffer();
      addChartoBuffer();
      assignToken(NOTHING);
      get_next_char();
    }
  }

  assignToken(NOTHING);
}
*/

void read_special() {
  char next = what_is_next();

  if (nextChar == '=' || next == '=') {
    addChartoBuffer();
    get_next_char();
    addChartoBuffer();
    get_next_char();
    assignToken(NOTHING);
  }
  else if (nextChar == '<') {
    switch (next)
    {
    case '-':
    case '=':
      addChartoBuffer();
      get_next_char();
      addChartoBuffer();
      get_next_char();
      assignToken(NOTHING);
    }
  }
  else if (nextChar == '>' || next == '=') {
    addChartoBuffer();
    get_next_char();
    addChartoBuffer();
    get_next_char();
    assignToken(NOTHING);
  }
  else if (nextChar == '-' || next == '>') {
    addChartoBuffer();
    get_next_char();
    addChartoBuffer();
    get_next_char();
    assignToken(NOTHING);
  }
  else if (nextChar == '|' || next == '|') {
    addChartoBuffer();
    get_next_char();
    addChartoBuffer();
    get_next_char();
    assignToken(NOTHING);
  }
  else if (nextChar == '&' || next == '&') {
    addChartoBuffer();
    get_next_char();
    addChartoBuffer();
    get_next_char();
    assignToken(NOTHING);
  }
  else {
    addChartoBuffer();
    get_next_char();
    assignToken(NOTHING);
  }
}

void read_error(){
  printf (" \t error\n");
  get_next_char();
}

void read_separator(){
  do {
    get_next_char();
  } while(is_separator());
  assignToken(SEPARATOR_TOKEN);
}

void read_comment() {
  do {
    get_next_char();
  } while(!is_end_of_line());
  assignToken(COMMENT_TOKEN);
}

void read_EOF() {
  assignToken(EOF_TOKEN);
}

int main(int argc,char**argv){

	f=fopen("code.R","r");
	clearBuffer();
	get_next_char();
	while(get_next_token()){
		
		printf(" %d",token);
		printf("   %s   \n",buffer);
		
		//clearBuffer();
	}

	printf("  fin   !!\n");

	return 0;
}
