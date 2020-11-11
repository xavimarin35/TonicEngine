#include "Globals.h"

#include "Libraries/pcg-c-0.94/include/pcg_variants.h"
#include "Libraries/pcg-c-0.94/extras/entropy.h"

#include <time.h>
#include <math.h>

pcg32_random_t rndNum;

void InitSeed()
{
	pcg32_srandom_r(&rndNum, time(NULL), (intptr_t)&rndNum);
}

float GenerateRandomFloat()
{
	return ldexp(pcg32_random_r(&rndNum), -32);
}

int GenerateRandomInt()
{
	return pcg32_random_r(&rndNum);
}

int GenerateRandomBetween(int bound)
{
	return pcg32_boundedrand_r(&rndNum, bound);
}