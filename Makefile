
default:
	gcc lexical.c syntaxic.c lexical.h -o compiler

lexical:
	gcc lexical.c lexical.h -o compiler

clearn:
	rm compiler