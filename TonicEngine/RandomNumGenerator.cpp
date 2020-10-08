#include "Globals.h"

#include "pcg-c-0.94/include/pcg_variants.h"
#include "pcg-c-0.94/extras/entropy.h"

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
	// From 0 to 5
	return pcg32_boundedrand_r(&rndNum, bound);
}