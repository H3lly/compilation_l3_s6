#ifndef ARBRE_SYNTAXIQUE_H
#define ARBRE_SYNTAXIQUE_H

#include "environ.h"
/* ----------------------------types--------------------------------------------*/
/* sommet de l'arbre syntaxique */
typedef struct cell_ast {
  int type;
  union {
    long int* function;  /* function[0]= (int) opérateur; function[1-3]= (AST) Fils; */
    char* name;          /* nom de la variable; */
    int value;           /* valeur brut; */
  }val;
} *AST;

enum { TYPE_FUNC, TYPE_STRING, TYPE_INT };
/*------------------FONCTIONS ---------------------------------------------------*/
extern AST new_cell(int type, void* argv);
extern int command(AST tree, ENV* prho);
extern int execute(AST tree, ENV* prho);
/* ------------------CONSTANTES -------------------------------------------------*/
#define Se 256
#define Wh 255
#define If 254

#define DEBUG 0

#endif
