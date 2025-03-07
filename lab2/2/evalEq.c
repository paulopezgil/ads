#include <stdio.h>  /* getchar, printf */
#include <stdlib.h> /* NULL */
#include "scanner.h"
#include "recognizeEq.h" /* acceptIdentifier, acceptCharacter,
                            isOneVariable, degree */
#include "evalEq.h"

int valueNumber(List *lp, double *vp)
{
    if (*lp != NULL && (*lp)->tt == Number)
    {
        *vp = (*lp)->t.number;
        *lp = (*lp)->next;
        return 1;
    }
    return 0;
}

int valueTerm(List *lp, double *a, double *b, int sign)
{
    int result;
    double readNum = 1, readExp;

    /* if it begins with <nat> then it's a valid term */
    result = valueNumber(lp, &readNum);

    /* Check for the pattern [<nat>] <identifier> ['^' <nat>] */
    if (acceptIdentifier(lp))
    {
        /* If at this point result = 0, then readNum = 1 (e.g. case x^4)*/
        /* First case: exponentiated variable (e.g. 2x^4)*/
        if (acceptCharacter(lp, '^'))
        {
            if (valueNumber(lp, &readExp))
            {
                if (readExp == 0)
                    *b += readNum * sign;
                else
                    *a += readNum * sign;

                return 1;
            }
            else
                return 0;
        }
        
        /* Second case: 1st degree variable (e.g. 3x) */
        *a += readNum * sign;
        return 1;
    }

    /* At this point, we've read a natural number */
    *b += readNum * sign;
    return result;
}

int valueExpression(List *lp, double *a, double *b, int sign)
{
    /* Check for optional '-' */
    int firstSign = sign * (1 - 2 * acceptCharacter(lp, '-'));

    /* Compute the value of the first term */
    if (!valueTerm(lp, a, b, firstSign))
        return 0;

    /* Compute the value of the optional terms */
    int readPlus;
    while ((readPlus = acceptCharacter(lp, '+')) || acceptCharacter(lp, '-'))
        if (!valueTerm(lp, a, b, readPlus ? sign : -sign))
            return 0;
    
    /* no + or -, so we reached the end of the equation */
    return 1;
}

int valueEquation(List *lp, double *a, double *b)
{
    return
    (   valueExpression(lp, a, b, 1)
    &&  acceptCharacter(lp, '=')
    &&  valueExpression(lp, a, b, -1));
}

/* The function valueEquations demonstrates the evaluator. */
void evaluateEquations()
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

        /* The equation is solved in the form ax + b = 0 */
        double a = 0, b = 0;

        /* Print the equation */
        printList(tl);

        /* Check if the input is an equation */
        tl1 = tl;
        if (valueEquation(&tl1, &a, &b) && tl1 == NULL)
        {
            printf("this is an equation");

            /* Check if the equation is in 1 variable or not */
            if (isOneVariable(tl))
            {
                int d = degree(tl);
                printf(" in 1 variable of degree %d\n", d);

                /* Solve the equation when it's in 1 variable and 1st degree */
                if (d == 1)
                {
                    if (a == 0)
                        printf("not solvable\n");
                    else
                    {
                        double solution = -b/a;
                        if (-0.0005 < solution && solution < 0.0005)
                            solution = 0;
                        printf("solution: %.3f\n", solution);
                    }
                }
            }
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