#pragma once
#include "Character.h"

#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>

//Instance that the game-player controls.
class Player : public Character
{
public:
	/*CONSTRUCTOR: Initialize instance of player character
	Parameters: filename for player info, player id*/
	Player(std::string fn, unsigned int index)
		:digits(0), fullParty(false)
	{
		status.set_IsPlayer(true);
		assign_StartInfo(fn, index);

		//initial ability info
		//abilities.get_AbilityList().reserve(100);
		//abilities.get_EnergyRequirement().reserve(100);
	}

	/*Get this player character's current funds*/
	int get_Digits();
	/*Set current funds to v*/
	void set_Digits(const unsigned int v);
	/*Change current funds by adding v to digits*/
	void change_Digits(const int v);

	/*Get this player character's enemy point score*/
	int get_Eps();
	/*Set enemy point score to v*/
	void set_Eps(const unsigned int v);
	/*Change current eps by addving v to eps*/
	void change_Eps(const int v);

private:
	//Current funds
	int digits;
	//Enemy point score
	int eps;
	//Set to true if both party members are active. set to false if only Tylor is active
	bool fullParty;

	/*Assign starting stats and other information for this player character.
	Parameter: filename, player character ID*/
	void assign_StartInfo(std::string filename, const unsigned int id);

	//set index
	//void set_Index(unsigned int v);
};
