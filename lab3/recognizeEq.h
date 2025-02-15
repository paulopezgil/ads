/* recognizeExp.h, Gerard Renardel, 29 January 2014 */

#ifndef RECOGNIZEEXP_H
#define RECOGNIZEEXP_H

int acceptNumber(List *lp); /* Same */
int acceptIdentifier(List *lp); /* Same */
int acceptCharacter(List *lp, char c); /* Same*/

/* New or modified functions */
int acceptTerm(List *lp);
int acceptExpression(List *lp);
int acceptEquation(List *lp);
int isOneVariable(List lp);
int degree(List lp);
void recognizeEquations();



#endif
