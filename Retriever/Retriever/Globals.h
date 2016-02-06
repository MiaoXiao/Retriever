#pragma once
#include "stdafx.h"

#include <iostream>
#include <vector>
#include <stdlib.h>

namespace Globals
{
	//No stat can go past this cap
	const int STAT_CAP = 100;
	//Positive and Negative flat modifier to any swing attacks
	const int RANGE = 5;
	//Probability to run from battle
	const float RUNPROBABILITY = 0.2;
}

namespace Enumerator
{
	enum ABILITYCATEGORY { Attack_C, Support_C, Debuff_C };
	enum ABILITYTYPE { Charged_T, Pierce_T, Area_T, Rapid_T };
	enum ITEMTYPE { Food, Drinks, Helpers, Liars, Circuits, Illuminites, Gadgets, Reminders, Weapons, Dust, Balls };
};

namespace Probability
{
	/*Given a probability (0 - 1), returns outcome
	Parameters: chance to occur
	Returns: Returns true given probability of p*/
	bool chanceToOccur(const float p);

	/*Returns a number 0 - 3, given 4 probabilities that MUST add up to 1
	Parameter: chance of 0, chance of 1, chance of 2, chance of 3
	Returns: Returns 0 - 3, depending on chance to occur*/
	int multipleChanceToOccur(const float prob0, const float prob1, const float prob2, const float prob3);

	/*Generates a random number.
	Parameter: lower exclusive, higher bound exclusive
	Returns: returns the random number between the given range*/
	int generateRandomNumber(const int lb, const int hb);
}

/*
//list of avaliable colors
//ALLEGRO_COLOR black, white, red, lime, blue, yellow, green, purple;
ALLEGRO_COLOR black = al_map_rgb(0, 0, 0);
ALLEGRO_COLOR white = al_map_rgb(255, 255, 255);
ALLEGRO_COLOR red = al_map_rgb(255, 0, 0);
ALLEGRO_COLOR lime = al_map_rgb(0, 255, 0);
ALLEGRO_COLOR blue = al_map_rgb(0, 0, 255);
ALLEGRO_COLOR yellow = al_map_rgb(255, 255, 0);
ALLEGRO_COLOR green = al_map_rgb(0, 128, 0);
ALLEGRO_COLOR purple = al_map_rgb(128, 0, 128);*/
