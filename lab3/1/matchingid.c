#include "lpm.h"

int matchingId(IpAdress, Subnet *sn, int n)
{
    int maxMatch, matchId;

    for (int pos = 0; pos != n; ++pos)
    {
        int match = 0;

        

        if (match > maxMatch)
        {
            maxMatch = match;
            matchId = pos;
        }

        if (match == maxMatch)
        {

        }

    }

    return matchId;
}

