%{
	#include <stdio.h>
	char* id, cmd, arg1, arg2, dest;
	char* var1, var2, num;
%}

%s A WRITE

var [a-zA-Z0-9]+
num [0-9]+



%%
{var}\:=	{begin(A); var1=yytext;}

<A>{num}/(;|[:space]|\n)?	{id=nextId(), cmd="Afc", arg1=yylex, arg2=" ", dest=var1; begin<WRITE>;}


<WRITE>	{printf("%s %s %s %s %s\n", id, cmd, arg1, arg2, dest);}
%%

int yywrap(){
  return 1;
}
int main(int argc,char *argv[]) {
	yylex();
}