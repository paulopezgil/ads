#ifndef EVALEXP_H
#define EVALEXP_H

int valueNumber(List *lp, double *vp);
int valueTerm(List *lp, double *a, double *b, int sign);
int valueExpression(List *lp, double *a, double *b, int sign);
int valueEquation(List *lp, double *a, double *b);
void evaluateEquations();

#endif
