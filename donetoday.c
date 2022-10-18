#ifndef NUMBER_H
#define NUMBER_H
#include <stdint.h>
struct Float102
{
  int sign;
  uint64_t coefficient;
  int16_t e10;
  int16_t e2;
};
#endif
#ifndef EXP10TO2
#define EXP10TO2
void e10ToExp2(struct Float102 *pn);
#endif
#ifndef PARSE_H
#define PARSE_H
#include <stdint.h>
struct ParseState
{
const char *ptr;
struct Float102 *pn;
};
int parse(const char *str, struct Float102 *pn);
#endif
int parseSign(struct ParseState *pps)
{
int retValue = 0;
switch (*pps->ptr)
{
case '+':
++pps->ptr; // skip, default sign is fine
break;
case '-':
++pps->ptr; // advance
retValue = 1;
break;
default:
break;
}
return retValue;
}
int isDigit(const char p)
{
return (p >= '0') && (p <= '9');
}
uint64_t parseUnsignedInt(uint64_t n, struct ParseState *pps)
{
while (isDigit(*pps->ptr))
{
n = n * 10 + (*pps->ptr - '0');
++pps->ptr;
}
return n;
}
void parseMantissa(struct ParseState *pps)
{
// after sign, parse the main part
pps->pn->coefficient = 0;
pps->pn->e10 = 0;
{
const char *oldPtr = pps->ptr;
pps->pn->coefficient = parseUnsignedInt(0,pps);
if (oldPtr != pps->ptr) // pointer advanced
{
if (*pps->ptr == '.')
{
++pps->ptr;
const char *oldPtr = pps->ptr;
pps->pn->coefficient =
  parseUnsignedInt(pps->pn->coefficient, pps);
pps->pn->e10 -= (pps->ptr - oldPtr);
}
}
}
}
int parse(const char *str, struct Float102 *pn)
{
struct ParseState ps;
int error = 0;
ps.ptr = str;
ps.pn = pn;
pn->e10 = 0;
pn->e2=0;
pn->sign = parseSign(&ps);
{
const char *oldPtr = ps.ptr;
        parseMantissa(&ps);
if (oldPtr != ps.ptr)
{
if (*ps.ptr == 'e')
{
int expSign;
uint64_t exp = 0;
++ps.ptr;
expSign = parseSign(&ps);
exp = parseUnsignedInt(exp, &ps);
pn->e10 += (expSign ? -exp : exp);
}
}
else
{
error = 1;
}
}
return error;
}
#include <stdio.h>
#include <limits.h>
void e10ToExp2(struct Float102 *pn)
{
uint64_t bigNumber = UINT64_MAX;// this is basically using the limits.h library to set bigNumber to the max int
//for (int i = 0; i <63; i++){ I tried using this for loop to get the bigNumber but it didn't work, could you please explain
       //bigNumber *=2;
//}
//printf("big = %u \n", bigNumber); used this to test whether the right value was held
printf("mantissa = %zu exp10 = %d, exp2 = %d \n", pn->coefficient, pn->e10, pn->e2);
while (pn->e10 > 0){ //essentially followed the logic of the spreadsheet for this while loop
    printf("mantissa = %zu exp10 = %d, exp2 = %d \n", pn->coefficient, pn->e10, pn->e2);
    while((pn->coefficient)<=bigNumber/10){
        pn->coefficient *= 10;
        pn->e10-=1;
    }
    printf("mantissa = %zu exp10 = %d, exp2 = %d \n", pn->coefficient, pn->e10, pn->e2);
    
    while ((pn->coefficient) > bigNumber/10){
        pn->coefficient = (pn->coefficient  + 1)/2;
        pn->e2+=1;
    }
    //printf("mantissa = %zu exp10 = %d ,exp2 = %d \n", pn->coefficient, pn->e10, pn->e2);
}
/*while((pn->coefficient)<bigNumber/2){ //brings the coefficient to its actual max
        pn->coefficient *= 10;
        pn->e10-=1;
        printf("coefficient = %zu \n e2 = %d \n", pn->coefficient, pn->e2);
    }*/
}

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main(int argc, const char **argv)
{
    const char *numberStr = NULL;
struct Float102 n;
int error = 0;
    --argc; ++argv; // skip name of executable itself
    while (!error && argc)
    {
        if (strcmp(*argv,"-n") == 0)
        {
            --argc; ++argv;
            if (argc)
            {
                numberStr = *argv;
                --argc; ++argv;
            }
            else
            {
fprintf(stderr,"-n should be followed by a number\n");
error = 1;
            }
        }
    }
    if (!error && numberStr)
{
// no errors encountered
parse(numberStr, &n);
e10ToExp2(&n);
}
    return 0;
}