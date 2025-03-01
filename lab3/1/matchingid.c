#include "lpm.h"

int matchingId(IpAddress ip, Subnet *sn, int n)
{
    int matchId = -1, maxMask = 0;

    for (int pos = 0; pos != n; ++pos)
    {
        /* store current mask for efficiency*/
        int mask = sn[pos].mask;

        /* check if the 2 IPs match and if the mask is the greatest matching one found */
        if ((transformIp(ip, mask) == transformIp(sn[pos].ip, mask)) && (maxMask < mask))
        {
            matchId = sn[pos].id;
            maxMask = mask;
        }
    }
    return matchId;
}

