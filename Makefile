
default:
	gcc lexical.c syntaxic.c lexical.h -o compiler

clearn:
	rm compiler