#include "stdafx.h"
#include "Character.h"
#include "Globals.h"

using namespace std;

//----------------------------PUBLIC----------------------------//

/*Given the following action, returns the energy required to complete it.
Parameter: which action
Returns: energy difference*/
int Character::get_EnergyDifference(const unsigned int action)
{
	switch (action)
	{
	case 0: //swing
		return stats.get_SwingEnergy();
	case 1: //ability
		return stats.get_AbilityEnergy();
	case 2: //defend
		return stats.get_DefendEnergy();
	case 3: //item
		return stats.get_ItemEnergy();
	case 4: //wait
		return stats.get_WaitEnergy();
	case 5: //run
		return stats.get_RunEnergy();
	default:
		cerr << "Not a valid action. Exiting." << endl;
		exit(1);
	}
}

/*When a swing attack is used, check if the attack is a critical.
Returns: True, given a probability based on this character's focus stat*/
bool Character::check_Critical() const
{
	return Probability::chanceToOccur(stats.get_Focus() * 0.01);
}

/*When this character is attacked, check if this character can evade.
Returns: True, given a probability based on this character's evasiveness stat*/
bool Character::check_Evasion() const
{
	//cout << "dodge: " << stats.get_Evasiveness() * 0.01 << endl;
	if (status.get_Defending()) return false;
	return Probability::chanceToOccur(stats.get_Evasiveness() * 0.01);
}

/*When this character attacks another, calculate this character's damage.
Parameter: modifier to the swing stat
Returns: final damage done*/
int Character::calculate_Damage(const float swingMultiplier)
{
	//cout << "inflict swing" << endl;
	return Probability::generateRandomNumber(-Globals::RANGE, Globals::RANGE) + stats.get_Swing() * swingMultiplier;
}

/*This function is called when this character is attacked by a swing based attack.
First checks if the attack is evaded, then whether the attack was a critical attack, then whether this character is defending.
Parameter: pointer to the character who is attacking this character, modifier to the swing stat*/
void Character::take_SwingDamage(Character *attacker, const float swingMultiplier)
{
	//reduce energy
	attacker->stats.change_CurrEnergy(attacker->stats.get_SwingEnergy());

	//damage (pos value)
	unsigned int damage = 0;
	//EVASION check
	if (check_Evasion())
	{
		//PROMPT
		cout << get_Name() << " evades the attack!" << endl;
	}
	else
	{
		//DAMAGE calculation
		damage = attacker->calculate_Damage(swingMultiplier);

		cout << "DEBUG: Total Damage: " << damage << endl;

		//CRITICAL check
		if (attacker->check_Critical())
		{
			//CALCULATION
			damage *= attacker->stats.get_FocusMultiplier();
			//PROMPT
			cout << attacker->get_Name() << " lands a critical attack!" << endl;
		}

		//DEFENSE check
		if (status.get_Defending()) //calculate damage against defender
		{
			attacker->take_Retaliation(damage, this);
		}
		else //calculate damage as normal
		{
			take_NormalDamage(damage);
		}
	}
	//showall_Stats();
}

/*This function is calld when this character is attacked by a NON swing based attack
Parameters: flat damage delt*/
void Character::take_NormalDamage(const int damage)
{
	stats.change_CurrHealth(-damage);

	//if currhealth is 0 or below, character is defeated
	if (stats.get_CurrHealth() == 0) status.set_IsAlive(false);

	//PROMPT
	cout << get_Name() << " takes " << damage << " damage!" << endl;
}

/*This character will set its defense to true.*/
void Character::defend()
{
	status.set_Defending(true);
	stats.change_CurrEnergy(stats.get_DefendEnergy());
	cout << get_Name() << " forms a defensive stance and restores " << stats.get_DefendEnergy() << " energy." << endl;
}

/*This function is called when this character recieves retaliation damage, which occurs when this character attacks a defending target.
Parameters: raw damage done to the defender, pointer to the defender*/
void Character::take_Retaliation(const int damage, Character *defender)
{
	int damageToDefender = damage * (1.0 - defender->stats.get_ReflectPercentage());
	int damageToAttacker = damage * defender->stats.get_ReflectPercentage();

	//at least 1 damage must be reflected
	if (damageToAttacker == 0) damageToAttacker = 1;

	//PROMPT
	cout << defender->get_Name() << " defends against the attack and returns some damage back to " << get_Name() << "!" << endl;

	//damage defender
	defender->take_NormalDamage(damageToDefender);
	//damage attacker
	take_NormalDamage(damageToAttacker);
}

/*Passes this character's turn in battle.*/
void Character::wait()
{
	stats.change_CurrEnergy(stats.get_WaitEnergy());
	cout << get_Name() << " catches " << pronoun << " breath and restores " << abs(stats.get_WaitEnergy()) << " energy." << endl;
}

/*Your entire party attempts to run from battle.
Returns: Returns true if run is successful, given probability.*/
bool Character::run()
{
	cout << get_Name() << " and company use " << abs(stats.get_RunEnergy()) << " energy in an attempt to run away!" << endl;
	stats.change_CurrEnergy(stats.get_RunEnergy());
	if (Probability::chanceToOccur(Globals::RUNPROBABILITY))
	{
		cout << "Run was successful!" << endl;
		return true;
	}
	cout << "Running was not successful!" << endl;
	return false;
}

//----------------------------PROTECTED----------------------------//

//----------------------------PRIVATE----------------------------//