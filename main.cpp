using namespace std;
#include<cstdlib>
#include<time.h>
#include<iostream>


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

void e10ToExp2(struct Float102 *pn)
{
	// in this function, convert the number pointed to b
	// pn from a base-10 coefficient and exponent to a base-2
	// coefficient and exponent
}
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>




int main(){
    cout << "hi" << endl;
    srand(time(0));
    const int upperLimitOfInt = 1.84467441E19;
    int randomInt = rand();
    int testInt = 3147;
    int powerOfTwo = 0;

while (testInt <= upperLimitOfInt){
    powerOfTwo++;
    int multiplier = 2;
    for (int i = 1; i <= powerOfTwo; i++){
        multiplier *= 2;
        cout << multiplier << endl;
    }
    testInt *= multiplier;
    //cout << testInt << endl;
    //hi
}

    return 0;
}
