#include "stdafx.h"
#include "Globals.h"

using namespace std;

/*Gets a random percentage between 0 - 1
Returns: Returns the percentage */
float givePercentage() { return (double)rand() / (RAND_MAX); }

/*Given a probability (0 - 1), returns outcome
Parameters: chance to occur
Returns: Returns true given probability of p*/
bool Probability::chanceToOccur(const float p)
{
	if (p < 0 || p > 1)
	{
		cerr << "Probability not between 0 and 1. Exiting." << endl;
		exit(1);
	}

	return p >= givePercentage();
}

/*Returns a number 0 - 3, given 4 probabilities that MUST add up to 1
Parameter: chance of 0, chance of 1, chance of 2, chance of 3
Returns: Returns 0 - 3, depending on chance to occur*/
int Probability::multipleChanceToOccur(const float prob0, const float prob1, const float prob2, const float prob3)
{
	float randnum = givePercentage();

	if (randnum <= prob0) return 0;
	randnum -= prob0;
	if (randnum <= prob1) return 1;
	randnum -= prob1;
	if (randnum <= prob2) return 2;
	randnum -= prob2;
	if (randnum <= prob3) return 4;

	cerr << "Could not finalize multipleChanceToOccur. Exiting." << endl;
	exit(1);
}

/*Generates a random number.
Parameter: lower bound exclusive, higher bound exclusive
Returns: returns the random number between the given range*/
int Probability::generateRandomNumber(const int lb, const int hb) { return rand() % hb + lb; }
