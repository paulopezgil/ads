#ifndef COMMANDS_H
#define COMMANDS_H
#include "tree.h"
#include "path.h"


void cd(Tree *tr, Path pt);
void ls(Tree tr, Path pt);
void cat(Tree tr, Path pt);
void find(Tree tr);
void touch(Tree tr, Path pt);
void echo(char *str, Tree tr, Path pt, char *(*mode)(char *, char const *));
void mkdir(Tree tr, Path pt);


#endif