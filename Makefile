
default:
	gcc lexical.c lexical.h syntaxic.c -o compiler

clearn:
	rm compiler