%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "environ.h"
#include "arbre_syntaxique.h"

int yylex();
int yyerror(char *s);

AST tree;

%}

%union{
	int i;
	char* s;
	long int addr;
}
%token _Af _Sk _Se _If _Th _El _Wh _Do _Pl _Mo _Mu _ParL _ParR
%token <i> I
%token <s> V
%type <addr> E T F C

%left _Pl _Mo _Mu _Se

%%

S: C									{ tree = (AST)$1; }
	;

E: E _Pl T						{ long int func[] = {Pl,$1,$3,0}; $$ = (long int)new_cell( TYPE_FUNC, func); }
 | E _Mo T						{ long int func[] = {Mo,$1,$3,0}; $$ = (long int)new_cell( TYPE_FUNC, func); }
 | T									{ $$ = $1; }
 ;

T: T _Mu F						{ long int func[] = {Mu,$1,$3,0}; $$ = (long int)new_cell( TYPE_FUNC, func); }
 | F									{ $$ = $1; }
 ;

F: _ParL E _ParR			{ $$ = $2; }
 | I									{ $$ = (long int)new_cell(TYPE_INT, &($1)); }
 | V									{ $$ = (long int)new_cell(TYPE_STRING, $1); }
 ;

C: V _Af E						{ long int v = (long int)new_cell( TYPE_STRING, $1); long int func[] = {Af,v,$3,0}; $$ = (long int)new_cell(TYPE_FUNC, func); }
 | _Sk								{ long int func[] = {Sk,0,0,0}; $$ = (long int)new_cell(TYPE_FUNC, func); }
 |  _ParL C _ParR			{ $$ = $2; }
 | _If E _Th C _El C	{ long int func[] = {If,$2,$4,$6}; $$ = (long int)new_cell(TYPE_FUNC, func); }
 | _Wh E _Do C				{ long int func[] = {Wh,$2,$4,0}; $$ = (long int)new_cell(TYPE_FUNC, func); }
 | C _Se C						{ long int func[] = {Se,$1,$3,0}; $$ = (long int)new_cell(TYPE_FUNC, func); }
 ;

%%
int yyerror(char *s){
	fprintf(stderr, "*** ERROR: %s\n", s);
	return 0;
}
int yywrap(){
	return -1;
}
int main(int argn, char **argv){
	ENV rho = NULL;
	yyparse();
	if (DEBUG) fprintf(stderr, "Start interpretation:\n");
	execute(tree, &(rho));
	ecrire_env(rho);
	return 0;
}
