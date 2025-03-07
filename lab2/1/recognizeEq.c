#include <stdio.h>  /* getchar, printf */
#include <stdlib.h> /* NULL */
#include <string.h> /* strcmp */
#include "scanner.h"
#include "recognizeEq.h"

int acceptNumber(List *lp) {
  if (*lp != NULL && (*lp)->tt == Number) {
    *lp = (*lp)->next;
    return 1;
  }
  return 0;
}

int acceptIdentifier(List *lp) {
  if (*lp != NULL && (*lp)->tt == Identifier) {
    *lp = (*lp)->next;
    return 1;
  }
  return 0;
}

int acceptCharacter(List *lp, char c) {
  if (*lp != NULL && (*lp)->tt == Symbol && ((*lp)->t).symbol == c) {
    *lp = (*lp)->next;
    return 1;
  }
  return 0;
}

int acceptTerm(List *lp)
{
    int result;

    /* if it begins with <nat> then it's a valid term */
    result = acceptNumber(lp);

    /* Check for the pattern [<nat>] <identifier> ['^' <nat>] */
    if (acceptIdentifier(lp))
    {
        result = 1;
        if (acceptCharacter(lp, '^'))
            return acceptNumber(lp);
    }

    return result;
}

int acceptExpression(List *lp)
{
    /* Check for optional '-' */
    acceptCharacter(lp, '-');

    if (!acceptTerm(lp))
        return 0;

    while (acceptCharacter(lp, '+') || acceptCharacter(lp, '-'))
        if (!acceptTerm(lp))
            return 0;
    
    /* no + or -, so we reached the end of the equation */
    return 1;
}

int acceptEquation(List *lp)
{
    return
    (   acceptExpression(lp)
    &&  acceptCharacter(lp, '=')
    &&  acceptExpression(lp));
}

int isOneVariable(List lp)
{
    int varCount = 0;
    Token var;

    while (lp != NULL)
    {
        if (lp->tt == Identifier)
        {
            /* If it's the first variable, save it */
            if (varCount == 0)
            {
                var = lp->t;
                varCount++;
            }

            /* If a different variable is found, return 0 */
            if (varCount == 1 && strcmp(var.identifier, lp->t.identifier) != 0)
                return 0;
        }
        lp = lp->next;
    }
    return varCount;
}

int degree(List lp)
{
    int highestDegree = 0;

    /* Search for the highest exponentiation */
    while(lp != NULL)
    {
        if (lp->tt == Identifier)
        {
            lp = lp->next;
            
            /* Check if the variable is raised to some power */
            if (lp != NULL && lp->tt == Symbol && lp->t.symbol == '^')
            {
                lp = lp->next;
                if (lp->t.number > highestDegree)
                    highestDegree = lp->t.number;
            }

            /* If not, it's a 1st degree variable */
            else if (highestDegree == 0)
                highestDegree = 1;

            if (lp == NULL)
                break;
        }

        lp = lp->next;
    }

    return highestDegree;
}

/* The function recognizeEquations demonstrates the recognizer. */
void recognizeEquations()
{
    char *ar;
    List tl, tl1;
    
    /* Read the input into a string */
    printf("give an equation: ");
    ar = readInput();

    while (ar[0] != '!')
    {
        /* Read ar and put the tokens that are read in a list */
        tl = tokenList(ar);

        /* Print the equation */
        printList(tl);

        /* Check if the input is an equation */
        tl1 = tl;
        if (acceptEquation(&tl1) && tl1 == NULL)
        {
            printf("this is an equation");

            /* Check if the equation is in 1 variable or not */
            if (isOneVariable(tl))
                printf(" in 1 variable of degree %d\n", degree(tl));
            else
                printf(", but not in 1 variable\n");
        }
        else
            printf("this is not an equation\n");

        /* Free the used memory and repeat until end of input */
        free(ar);
        freeTokenList(tl);
        printf("\ngive an equation: ");
        ar = readInput();
    }

    free(ar);
    printf("good bye\n");
}