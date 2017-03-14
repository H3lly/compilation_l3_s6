%{
	#include <stdio.h>
	char* var1, var2, num;

	void trad(char* id, char* cmd, char* arg1, char* arg2, char* dest){
		printf("%s	:%s	:%s	:%s	:%s hehehoho\n", id, cmd, arg1, arg2, dest);
}

%}
%option noyywrap

%s C A WRITE

var [a-zA-Z0-9]+
num [0-9]+
af :=


%%
{var}	{ var1=yytext; BEGIN(C);}

<C>:= {BEGIN(A);}
<A>{num}/(;|[:space]|\n)?	{trad("ET0", "Afc", yytext, "", var1);}

%%


int main(int argc,char *argv[]) {
	yylex();
}