#include "lpm.h"

int transformIp(IpAddress ip, int mask)
{
    int result = 0;

    /* transform the IpAdress into an int */
    result |= (ip[0] << 24);
    result |= (ip[1] << 16);
    result |= (ip[2] << 8);
    result |= ip[3];

    /* All the bits greater than mask are 0 */
    result &= (0xFFFFFFFF << (32 - mask));

    return result;
}