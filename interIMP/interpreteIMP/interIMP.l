%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "interIMP.tab.h"
%}

%option nounput noinput

%%
:=            {return _Af;}
skip          {return _Sk;}
;             {return _Se;}
if            {return _If;}
then          {return _Th;}
else          {return _El;}
while         {return _Wh;}
do            {return _Do;}
\+            {return _Pl;}
\-            {return _Mo;}
\*            {return _Mu;}
\(            {return _ParL;}
\)            {return _ParR;}
[0-9]+        { yylval.i = atoi(yytext); return I; }
[A-Za-z0-9_]+ { yylval.s = (char*)malloc(strlen(yytext)*sizeof(char)); strcpy(yylval.s, yytext); return V; }
[ \n\t]       {;}

.             {return yytext[0];}

%%
