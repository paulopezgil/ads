#ifndef LPM_H
#define LPM_H

typedef int IpAddress[4];

typedef struct Subnet
{
    IpAddress ip;
    int mask;
    int id;
} Subnet;

void readInput(int *n, int *m, Subnet **sn, IpAddress **ip);
int transformIp(IpAddress ip, int mask);
int matchingId(IpAdress ip, Subnet *sn, int n);

#endif
