#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arbre_syntaxique.h"


AST new_cell(int type, void* argv){
  AST newcell = (AST)malloc(sizeof(struct cell_ast));
  if (DEBUG) fprintf(stderr, "Create new cell of type: ");

  /* Si type = TYPE_FUNC, alors void** function = void** argv; */
  if (type == TYPE_FUNC){
    newcell->type = TYPE_FUNC;
    if (DEBUG) fprintf(stderr, "func...");
    newcell->val.function = (long int*) malloc(4*sizeof(long int));
    long int* func = (long int*)argv;
    if (DEBUG) fprintf(stderr, "{");
    for(int i=0; i<4; ++i){
      newcell->val.function[i] = func[i];
      if (DEBUG) fprintf(stderr, "%p, ", (AST)func[i]);
    }
    if (DEBUG) fprintf(stderr, "}...");
  }

  /* Si type = TYPE_STRING, alors char* name = argv[0]; */
  if (type == TYPE_STRING){
    newcell->type = TYPE_STRING;
    if (DEBUG) fprintf(stderr, "string...");
    newcell->val.name = (char*) malloc(strlen((char*)argv)*sizeof(char));
    strcpy(newcell->val.name,(char*)argv);
    if (DEBUG) fprintf(stderr, "%s...", (char*)argv);
  }

  /* Si TYPE_INT, alors int value = (int)*(argv[0]); */
  if (type == TYPE_INT){
    newcell->type = TYPE_INT;
    if (DEBUG) fprintf(stderr, "int...");
    newcell->val.value = *((int*)argv);
    if (DEBUG) fprintf(stderr, "%d...", *((int*)argv));
  }

  if (DEBUG) fprintf(stderr, "%p success\n", newcell);
  return newcell;

}

int command(AST tree, ENV* prho){
  if (tree == NULL) {fprintf(stderr, "arbre suntaxique NULL"); exit(1);}
  long int op = tree->val.function[0];
  int e;
  switch(op){
    case Sk:
      if (DEBUG) fprintf(stderr, "Sk\n");
      return 0;
      break;
    case Se:
      if (DEBUG) fprintf(stderr, "Se {%p, %p}\n", (AST)tree->val.function[1], (AST)tree->val.function[2]);
      execute((AST)tree->val.function[1], prho);
      execute((AST)tree->val.function[2], prho);
      return 0;
      break;
    case Pl:
    case Mo:
    case Mu:
      if (DEBUG){
        if (op == Pl) fprintf(stderr, "Pl {%p, %p}\n", (AST)tree->val.function[1], (AST)tree->val.function[2]);
        if (op == Pl) fprintf(stderr, "Mo {%p, %p}\n", (AST)tree->val.function[1], (AST)tree->val.function[2]);
        if (op == Pl) fprintf(stderr, "Mu {%p, %p}\n", (AST)tree->val.function[1], (AST)tree->val.function[2]);
      }
      return eval(op, execute((AST)tree->val.function[1], prho), execute((AST)tree->val.function[2], prho));
      break;
    case Af:
      if (DEBUG) fprintf(stderr, "Af {%p, %p}\n=> %s := (", (AST)tree->val.function[1], (AST)tree->val.function[2], ((AST)tree->val.function[1])->val.name);
      e = execute((AST)tree->val.function[2], prho);
      if (DEBUG) fprintf(stderr, ") = %d\n", e);
      initenv(prho, ((AST)tree->val.function[1])->val.name);
      affect(*prho, ((AST)tree->val.function[1])->val.name, e);
      return 0;
      break;
    case Wh:
      if (DEBUG) fprintf(stderr, "Wh {%p, %p}:\n", (AST)tree->val.function[1], (AST)tree->val.function[2]);
      while(execute((AST)tree->val.function[1], prho))
        execute((AST)tree->val.function[2], prho);
      return 0;
      break;
    case If:
      if (DEBUG) fprintf(stderr, "If {%p, %p, %p}:\n ", (AST)tree->val.function[1], (AST)tree->val.function[2], (AST)tree->val.function[3]);
      if(execute((AST)tree->val.function[1], prho)){
        if (DEBUG) fprintf(stderr, "Th => ");
        execute((AST)tree->val.function[2], prho);
      }
      else{
        if (DEBUG) fprintf(stderr, "El => ");
        execute((AST)tree->val.function[3], prho);
      }
      break;
    default: fprintf(stderr, "Unknown operand cell->val.function[0]: %ld", op); exit(1);
  }
  return 0;
}


int execute(AST tree, ENV* prho){
  if (tree == NULL) {fprintf(stderr, "arbre suntaxique NULL"); exit(1);}
  switch(tree->type){
    case TYPE_FUNC:
      if (DEBUG) fprintf(stderr, "execute func...");
      return command(tree, prho);
      break;
    case TYPE_STRING:
      if (DEBUG) fprintf(stderr, "ask for variable: %s; ", tree->val.name);
      return valch(*prho, tree->val.name);
      break;
    case TYPE_INT:
      if (DEBUG) fprintf(stderr, "ask for value: %d; ", tree->val.value);
      return tree->val.value;
      break;
    default: fprintf(stderr, "Unknown AST cell->type: %d", tree->type); exit(1);
  }
}
