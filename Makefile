
default:
	gcc lexical.c lexical.h syntaxic.c -o compiler

lexical:
	gcc lexical.c lexical.h -o compiler

clearn:
	rm compiler