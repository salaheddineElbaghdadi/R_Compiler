#include"syntaxic.h"

void main(int argc,char**argv){
	f=fopen("code.R","r");
	clearBuffer();
	get_next_char();
	get_next_token();
	if(PROG()){
		printf("fin!!\n");
	}
	else{
		printf("syntax error\n");
	}

}

bool PROG(){
	
	if(BLOC()){
		while(BLOC());
		if(END()){
			printf("-->PROG\n");
			return true;
		}
		else{
			return false;
		}
	}
	else if(END()){
		printf("-->PROG\n");
		return true;
	}
	else{
		return false;
	}
}

bool BLOC(){
	if(DECISION()){
		get_next_token();
		if(token==EOL_TOKEN){
			get_next_token();
			while(token==EOL_TOKEN){
				get_next_token();
			}
			printf("--->BLOC\n");
			return true;
		}
	}
	else if(OPERATION()){
		get_next_token();
		if(token==EOL_TOKEN){
			get_next_token();
			while(token==EOL_TOKEN){
				get_next_token();
			}
			printf("--->BLOC\n");
			return true;
		}
	}
	else{
		return false;
	}
}

bool END(){
	
	if(token==EOF_TOKEN){
		printf("--->END\n");
		printf("fin du fichier\n");
		
		return true;
	}
	else{
		return false;
	}
}
bool CALLFUNCTION(){
	return false;
	printf("--->CALLFUNCTION\n");
	
}

bool IDENTIF(){
	if(token==NUMERIC_TOKEN){
		get_next_token();
		printf("--->IDENTIF\n");
		return true;
	}
	else if(token==ID_TOKEN){
		
		get_next_token();
		printf("--->IDENTIF\n");
		return true;
	}
	else if(CALLFUNCTION()){
		get_next_token();
		printf("--->IDENTIF\n");
		return true;
	}
	else{
		return false;
	}
}

bool OPERATOR(){
	
	switch(token){
		case EQUAL_TOKEN:{get_next_token();printf("--->OPERATOR\n");return true;}
		case LESS_TOKEN:{get_next_token();printf("--->OPERATOR\n");return true;}
		case LESS_EQUAL_TOKEN:{get_next_token();printf("--->OPERATOR\n");return true;}
		case GREATER_TOKEN:{get_next_token();printf("--->OPERATOR\n");return true;}
		case GREATER_EQUAL_TOKEN:{get_next_token();printf("--->OPERATOR\n");return true;}
		case PLUS_TOKEN:{get_next_token();printf("--->OPERATOR\n");return true;}
		case SUBSTRACT_TOKEN:{get_next_token();printf("--->OPERATOR\n");return true;}
		case MULTIPLY_TOKEN:{get_next_token();printf("--->OPERATOR\n");return true;}
		case DEVIDE_TOKEN:{get_next_token();printf("--->OPERATOR\n");return true;}
		case NOT_TOKEN:{get_next_token();printf("--->OPERATOR\n");return true;}
		case AND_TOKEN:{get_next_token();printf("--->OPERATOR\n");return true;}
		case LOGICAL_AND_TOKEN:{get_next_token();printf("--->OPERATOR\n");return true;}
		case OR_TOKEN:{get_next_token();printf("--->OPERATOR\n");return true;}
		case LOGICAL_OR_TOKEN:{get_next_token();printf("--->OPERATOR\n");return true;}
		case NOT_EQUAL_TOKEN:{get_next_token();printf("--->OPERATOR\n");return true;}
		case MODULO_TOKEN:{get_next_token();printf("--->OPERATOR\n");return true;}
		case POWER_TOKEN:{get_next_token();printf("--->OPERATOR\n");return true;}
		case QUOTIENT_TOKEN:{get_next_token();printf("--->OPERATOR\n");return true;}
		default:{
			return false;
		}
		

	}
}

bool OPERATION(){
	
	if(IDENTIF()){
		get_next_token();
		while(OPERATOR()){
			if(IDENTIF()){
				get_next_token();
				if(token==EOL_TOKEN){
					get_next_token();
					while(token==EOL_TOKEN){get_next_token();};
					get_next_token();
					printf("--->OPERATION\n");
					return true;
				}
	
			}
			else{
				return false;
			}
		}
		get_next_token();
		printf("--->OPERATION\n");
		return true;
	}
	/*
	else if(token==OPENING_PARENTHESES_TOKEN){
		printf("read (\n");
		get_next_token();
		printf("token: %d\n",token);
		if(OPERATION()){
			printf("token: %d\n",token);
			while(OPERATION());
			printf("token: %d\n",token);
			if(token==CLOSING_PARENTHESES_TOKEN){
				printf("read )\n");
				get_next_token();
				if(token==EOL_TOKEN){
					get_next_token();
					while(token==EOL_TOKEN){get_next_token();};
					printf("--->OPERATION\n");
					return true;

				}
				
				
			}
			else{
				return false;
			}
		}
		else{
			return false;
		}
		

	}*/
	else{
		return false;
	}
}




bool DECISION(){
	if(token==IF_TOKEN){

		get_next_token();
		if(token==OPENING_PARENTHESES_TOKEN){

			get_next_token();
			if(OPERATION()){
				if(token==CLOSING_PARENTHESES_TOKEN){

					get_next_token();
					if(token==EOL_TOKEN){

						get_next_token();
						if(token==OPENING_CURLY_BRACKETS_TOKEN){
							get_next_token();
							if(BLOC()){
								if(token==CLOSING_CURLY_BRACKETS_TOKEN){
									get_next_token();
									while(token==EOL_TOKEN){
										get_next_token();
									}
									//printf("function syn correcte\n");
									printf("--->DECISION\n");
									return true;
								}
								else{
									return false;
								}
							}
							else{
								return false;
							}
						}
						else{
							return false;
						}
					}
					else if(token==OPENING_CURLY_BRACKETS_TOKEN){
							get_next_token();
							if(BLOC()){
								if(token==CLOSING_CURLY_BRACKETS_TOKEN){

									get_next_token();
									while(token==EOL_TOKEN){
										get_next_token();
									}
									printf("--->DECISION\n");
									//printf("function syn correcte\n");
									return true;
								}
								else{
									return false;
								}
							}
							else{
								return false;
							}
			
						}
						else{
							return false;
						}
					
					
				}
			}
			else{
				return false;
			}
		}
		else{
			return false;
		}
	}
	else{
		return false;
	}
}
bool EXPRESSION(){
	if(token==ID_TOKEN){
		get_next_token();
		if(token==LEFT_ASSIGN_TOKEN){
			get_next_token();
			if(OPERATION()){
				get_next_token();
				if(token==EOL_TOKEN){
					get_next_token();
					while(token==EOL_TOKEN){
						get_next_token();
					}
				}
				return true;
				
			}
			else{
				return false;
			}
		}
		else{
			return false;
		}
	
	}
	else{
		return false;
		}
}