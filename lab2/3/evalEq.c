#include <stdio.h>  /* getchar, printf */
#include <stdlib.h> /* NULL */
#include <math.h>   /* sqrt */
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

int valueTerm(List *lp, double *a, double *b, double *c, int sign)
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
                switch ((int)readExp)
                {
                    case 0:     /* case cx^0 */
                        *c += readNum * sign;
                        break;
                    case 1:     /* case bx^1 */
                        *b += readNum * sign;
                        break;
                    default:    /* case ax^2 */
                        *a += readNum * sign;
                        break;
                }

                return 1;
            }
            else
                return 0;
        }
        
        /* Second case: 1st degree variable (e.g. 3x) */
        *b += readNum * sign;
        return 1;
    }

    /* At this point, we've read a natural number */
    *c += readNum * sign;
    return result;
}

int valueExpression(List *lp, double *a, double *b, double *c, int sign)
{
    /* Check for optional '-' */
    int firstSign = sign * (1 - 2 * acceptCharacter(lp, '-'));

    /* Compute the value of the first term */
    if (!valueTerm(lp, a, b, c, firstSign))
        return 0;

    /* Compute the value of the optional terms */
    int readPlus;
    while ((readPlus = acceptCharacter(lp, '+')) || acceptCharacter(lp, '-'))
        if (!valueTerm(lp, a, b, c, readPlus ? sign : -sign))
            return 0;
    
    /* no + or -, so we reached the end of the equation */
    return 1;
}

int valueEquation(List *lp, double *a, double *b, double *c)
{
    return
    (   valueExpression(lp, a, b, c, 1)
    &&  acceptCharacter(lp, '=')
    &&  valueExpression(lp, a, b, c, -1));
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

        /* The equation is solved in the form ax^2 + bx + c = 0 */
        double a = 0, b = 0, c = 0;

        /* Print the equation */
        printList(tl);

        /* Check if the input is an equation */
        tl1 = tl;
        if (valueEquation(&tl1, &a, &b, &c) && tl1 == NULL)
        {
            printf("this is an equation");

            /* Check if the equation is in 1 variable or not */
            if (isOneVariable(tl))
            {
                int d = degree(tl);
                printf(" in 1 variable of degree %d\n", d);

                /* 1st degree equation */
                /* Case ax^2 + bx + c = 0 with a = 0 */
                if (d == 1 || (d == 2 && a == 0))
                {
                    if (b == 0)
                        printf("not solvable\n");
                    else
                    {
                        double solution = -c/b;
                        if (-0.0005 < solution && solution < 0.0005)
                            solution = 0;
                        printf("solution: %.3f\n", solution);
                    }
                }

                /* Second degree equation */
                /* Case ax^2 + bx + c = 0 with a != 0 */
                else if (d == 2)
                {
                    /* complex solution */
                    if (b*b < 4 * a * c)
                        printf("not solvable\n");
                    else
                    {
                        double solution1 = (-b + sqrt(b*b - 4 * a * c)) / (2 * a);
                        double solution2 = (-b - sqrt(b*b - 4 * a * c)) / (2 * a);
                        if (-0.0005 < solution1 && solution1 < 0.0005)
                            solution1 = 0;
                        if (-0.0005 < solution2 && solution2 < 0.0005)
                            solution2 = 0;
    
                        if (solution1 == solution2)
                            printf("solution: %.3f\n", solution1);
                        else
                            printf("solution: %.3f and %.3f\n", solution1, solution2);
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