%{
	#include <stdio.h>
	#include <string.h>

	char var1[200];
	char var2[200];
	char tmp[200];
	void trad(char* id, char* cmd, char* arg1, char* arg2, char* dest){
		printf(":%s :%s	:%s	:%s	:%s\n", id, cmd, arg1, arg2, dest);
}

%}
%option noyywrap

%s C A AF PL Mo Mu

var [a-zA-Z0-9]+
num [0-9]+
af :=
eol (;|[:space:]|\n)?
op (\+|-|\*)


%%
{var}	{strcpy(var1, yytext);BEGIN(C);}

<C>{af} {strcpy(var2, yytext); BEGIN(A);}

<A>{num}/{eol}	{trad("ET0", "Afc", yytext, "", var1);}
<A>({num}|{var})/{op}	{BEGIN(AF);}


<AF>\+{BEGIN(PL);}


<PL>({num}|{var})/{eol} {trad("ETX", "Pl", var2, yytext, var1)}


. {}
%%


int main(int argc,char *argv[]) {
	yylex();
}