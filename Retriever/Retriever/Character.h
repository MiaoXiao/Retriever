#pragma once

#include "Entity.h"
#include "Globals.h"

#include <iostream>
#include <algorithm> 
#include <fstream>
#include <string>
#include <stdlib.h>
#include <vector>

//stat points given for each level
#define STATPOINTS 4

//Container for character stats
struct Stats
{
private:
	//PRIMARY STATS: stats you can level up throughout the game
	
	//Maximum health points of this character.
	unsigned int maxhealth = 0;
	//Current health points of this character. Character is wiped out if health is reduced to 0
	int currhealth = 0;
	//Maximum energy points of this character.
	unsigned int maxenergy = 0;
	//Current energy points of this character. Energy is how often a character can use battle specific actions.
	int currenergy = 0;
	//How quickly this character can have their turn in a battle. This is the only stat that is more beneficial the smaller it is.
	unsigned int reaction = 0;
	//Base damage for this character.
	unsigned int swing = 0;
	//Character's chance to resist hostile abilities
	unsigned int resistance = 0;
	//Character's chance to evade hostile swing attacks
	unsigned int evasiveness = 0;

	//UNIQUE STATS: stats that cannot be improved by normal means
	
	//Used to measure battle behaviors.
	unsigned int intelligence = 0;
	//Character's chance to inflict a critical attack when using a swing attack.
	unsigned int focus = 0;
	//Multiplier used to calculate a critical attack
	unsigned int focusmultiplier = 0;
	//When this character defends, the percentage of damage reflected to the attacker when damaged by any hostile swing attack.
	float reflectpercentage = 0;

	//HIDDEN STATS: stats that are not shown to the player
	
	//Energy needed/gained for a swing attack
	int swingEnergy = -5;
	//Extra energy needed/gained for using any of this character's abilities
	int abilityEnergy = 0;
	//Energy needed/gained for defending
	int defendEnergy = 2;
	//Energy needed/gained for using an item
	int itemEnergy = 2;
	//Energy needed/gained for waiting
	int waitEnergy = 10;
	//Energy needed/gained for running
	int runEnergy = -10;

public:

	/*Allows character to allocate points to stats and abilities
	Parameter: number of times leveled up*/
	void levelUpStats(unsigned int points)
	{
		unsigned int statPoints = points * STATPOINTS;

		//temp changes
		unsigned int mhChange = 0;
		unsigned int meChange = 0;
		unsigned int reacChange = 0;
		unsigned int sChange = 0;
		unsigned int rChange = 0;
		unsigned int eChange = 0;

		std::cout << statPoints << " stat points to allocate." << std::endl;

		bool done = false;
		int choice;

		while (!done)
		{
			std::cout << "Choose which stats to improve. " << std::endl;
			std::cout << statPoints << " points left." << std::endl;

			std::cout << "0: MaxHealth " << get_MaxHealth() + mhChange << std::endl;
			std::cout << "1: MaxEnergy " << get_MaxEnergy() + meChange << std::endl;
			std::cout << "2: Reaction " << get_Reaction() - reacChange << std::endl;
			std::cout << "3: Swing " << get_Swing() + sChange << std::endl;
			std::cout << "4: Resistance " << get_Resistance() + rChange << std::endl;
			std::cout << "5: Evasiveness " << get_Evasiveness() + eChange << std::endl << std::endl;

			std::cin >> choice;
			std::cout << std::endl;

			if (choice < 0 || choice > 5)
			{
				std::cout << "Not a valid stat, try again." << std::endl;
			}
			else
			{
				statPoints--;
				switch (choice)
				{
				case 0: mhChange++;
					break;
				case 1: meChange++;
					break;
				case 2: reacChange++;
					break;
				case 3: sChange++;
					break;
				case 4: rChange++;
					break;
				case 5: eChange++;
					break;
				}
			}

			//check if all points allocated
			if (statPoints == 0)
			{
				std::cout << "Press '0' to confirm changes, or anything else to reallocate points." << std::endl;

				std::cout << "0: MaxHealth " << get_MaxHealth() << " -> " << get_MaxHealth() + mhChange << std::endl;
				std::cout << "1: MaxEnergy " << get_MaxEnergy() << " -> " << get_MaxEnergy() + meChange << std::endl;
				std::cout << "2: Reaction " << get_Reaction() << " -> " << get_Reaction() - reacChange << std::endl;
				std::cout << "3: Swing " << get_Swing() << " -> " << get_Swing() + sChange << std::endl;
				std::cout << "4: Resistance " << get_Resistance() << " -> " << get_Resistance() + rChange << std::endl;
				std::cout << "5: Evasiveness " << get_Evasiveness() << " -> " << get_Evasiveness() + eChange << std::endl << std::endl;

				std::cin >> choice;
				std::cout << std::endl;

				if (choice == 0)
				{
					done = true;
					change_MaxHealth(mhChange);
					change_MaxEnergy(meChange);
					change_Reaction(-reacChange);
					change_Swing(-sChange);
					change_Resistance(rChange);
					change_Evasiveness(eChange);
				}
				else
				{
					mhChange = 0;
					meChange = 0;
					reacChange = 0;
					sChange = 0;
					rChange = 0;
					eChange = 0;
					statPoints = points * STATPOINTS;
				}
			}
		}
	}

	/*Get max health*/
	int get_MaxHealth() const { return maxhealth; }
	/*Set max health to v.*/
	void set_MaxHealth(const unsigned int v)
	{
		if (v < currhealth) currhealth = maxhealth;
		else maxhealth = v;
	}
	/*Change max health, by adding v to max health.*/
	void change_MaxHealth(const int v)
	{
		if (v + maxhealth < 1) maxhealth = 1;
		else set_MaxHealth(v + maxhealth);
	}

	/*Get current health*/
	int get_CurrHealth() const { return currhealth; }
	/*Set current health to v.*/
	void set_CurrHealth(const unsigned int v)
	{
		if (v >= maxhealth) currhealth = maxhealth;
		else currhealth = v;
	}
	/*Change current health, by adding v to curr health*/
	void change_CurrHealth(const int v)
	{
		if (v + currhealth < 0) currhealth = 0;
		else set_CurrHealth(v + currhealth);
	}

	/*Get max energy*/
	int get_MaxEnergy() const { return maxenergy; }
	/*Set max energy. if brought below curr energy, match curr energy to max energy*/
	void set_MaxEnergy(const unsigned int v)
	{
		if (v < currenergy) currenergy = maxenergy;
		else maxenergy = v;
	}
	/*Change max energy, by adding v to max energy.*/
	void change_MaxEnergy(const int v)
	{
		if (v + maxenergy < 1) maxenergy = 1;
		else set_MaxEnergy(v + maxenergy);
	}

	/*Get current energy*/
	int get_CurrEnergy() const { return currenergy; }
	/*Set current energy*/
	void set_CurrEnergy(const unsigned int v)
	{
		if (v >= maxenergy) currenergy = maxenergy;
		else currenergy = v;
	}
	/*change current energy, by adding v to curr energy*/
	void change_CurrEnergy(const int v)
	{
		if (v + currenergy < 0) currenergy = 0;
		else set_CurrEnergy(v + currenergy);
	}

	/*Get reaction*/
	int get_Reaction() const { return reaction; }
	/*Set reaction*/
	void set_Reaction(const unsigned int v) { reaction = v; }
	/*Change reaction, by adding v to reaction*/
	void change_Reaction(const int v)
	{
		if (v + reaction < 0) reaction = 0;
		else set_Reaction(reaction + v);
	}

	/*Get swing (damage)*/
	int get_Swing() const { return swing; }
	/*Set swing (damage)*/
	void set_Swing(const unsigned int v) { swing = v; }
	/*Change swing, by adding v to swing*/
	void change_Swing(const int v)
	{
		if (v + swing < 0) swing = 0;
		else set_Swing(v + swing);
	}

	/*Get resistance*/
	int get_Resistance() const { return resistance; }
	/*Set resistance*/
	void set_Resistance(const unsigned int v) { resistance = v; }
	/*Change resistance, by adding v to resistance*/
	void change_Resistance(const int v)
	{
		if (v + resistance < 0) resistance = 0;
		else set_Resistance(v + resistance);
	}

	/*Get evasiveness*/
	int get_Evasiveness() const { return evasiveness; }
	/*Set evasiveness*/
	void set_Evasiveness(const unsigned int v) { evasiveness = v; }
	/*Change evasiveness, by adding v to evasiveness*/
	void change_Evasiveness(const int v)
	{
		if (v + evasiveness < 0) evasiveness = 0;
		else set_Evasiveness(v + evasiveness);
	}

	/*Get intelligence*/
	int get_Intelligence() const { return intelligence; }
	/*Set intelligence*/
	void set_Intelligence(const unsigned int v) { intelligence = v; }
	/*Change intelligence, by adding v to intelligence*/
	void change_Intelligence(const int v)
	{
		if (v + intelligence < 0) intelligence = 0;
		else set_Intelligence(v + intelligence);
	}

	/*Get focus*/
	int get_Focus() const { return focus; }
	/*Set focus*/
	void set_Focus(const unsigned int v) { focus = v; }
	/*Change focus, by adding v to focus*/
	void change_Focus(const int v)
	{
		if (v + focus < 0) focus = 0;
		else set_Focus(v + focus);
	}

	/*Get focus multiplier*/
	int get_FocusMultiplier() const { return focusmultiplier; }
	/*Set focus multiplier*/
	void set_FocusMultiplier(const float v) { focusmultiplier = v; }
	/*Change focus multiplier, by adding v to focus multiplier*/
	void change_FocusMultiplier(const float v)
	{
		if (v + focusmultiplier < 0) focusmultiplier = 0;
		else set_FocusMultiplier(v + focusmultiplier);
	}

	/*Get reflect percentage*/
	float get_ReflectPercentage() const { return reflectpercentage; }
	/*Set reflect percentage*/
	void set_ReflectPercentage(const float v) { reflectpercentage = v; }
	/*Change reflect percentage, by adding v to reflect percentage*/
	void change_ReflectPercentage(const float v)
	{
		if (v + reflectpercentage < 0) reflectpercentage = 0;
		else set_ReflectPercentage(v + reflectpercentage);
	}

	/*Set swingEnergy*/
	int get_SwingEnergy() const { return swingEnergy; }
	/*Set swingEnergy*/
	void set_SwingEnergy(const unsigned int v) { swingEnergy = v; }
	/*Change swingEnergy, by adding v to swingEnergy*/
	void change_SwingEnergy(const int v)
	{
		if (v + swingEnergy < 0) swingEnergy = 0;
		else set_SwingEnergy(v + swingEnergy);
	}

	/*Get abilityEnergy*/
	int get_AbilityEnergy() const { return abilityEnergy; }
	/*Set abilityEnergy*/
	void set_AbilityEnergy(const unsigned int v) { abilityEnergy = v; }
	/*Change abilityEnergy, by adding v to abilityEnergy*/
	void change_AbilityEnergy(const int v)
	{
		if (v + abilityEnergy < 0) abilityEnergy = 0;
		else set_AbilityEnergy(v + abilityEnergy);
	}

	/*Get defendEnergy*/
	int get_DefendEnergy() const { return defendEnergy; }
	/*Set defendEnergy*/
	void set_DefendEnergy(const unsigned int v) { defendEnergy = v; }
	/*Change defendEnergy, by adding v to defendEnergy*/
	void change_DefendEnergy(const int v)
	{
		if (v + defendEnergy < 0) defendEnergy = 0;
		else set_DefendEnergy(v + defendEnergy);
	}

	/*Get itemEnergy*/
	int get_ItemEnergy() const { return itemEnergy; }
	/*Set defendEnergy*/
	void set_ItemEnergy(const unsigned int v) { itemEnergy = v; }
	/*Change defendEnergy, by adding v to defendEnergy*/
	void change_ItemEnergy(const int v)
	{
		if (v + itemEnergy < 0) itemEnergy = 0;
		else set_ItemEnergy(v + itemEnergy);
	}

	/*Get waitEnergy*/
	int get_WaitEnergy() const { return waitEnergy; }
	/*Set waitEnergy*/
	void set_WaitEnergy(const unsigned int v) { waitEnergy = v; }
	/*Change waitEnergy, by adding v to waitEnergy*/
	void change_WaitEnergy(const int v)
	{
		if (v + waitEnergy < 0) waitEnergy = 0;
		else set_WaitEnergy(v + waitEnergy);
	}

	/*Get runEnergy*/
	int get_RunEnergy() const { return runEnergy; }
	/*Set runEnergy*/
	void set_RunEnergy(const unsigned int v) { runEnergy = v; }
	/*Change runEnergy, by adding v to runEnergy*/
	void change_RunEnergy(const int v)
	{
		if (v + runEnergy < 0) runEnergy = 0;
		else set_RunEnergy(v + runEnergy);
	}

	/*DEBUG: Print all current stats.*/
	void show_Stats() const
	{
		//base stats
		std::cout << "Max Health: " << maxhealth << std::endl;
		std::cout << "Current Health: " << currhealth << std::endl;
		std::cout << "Max Energy: " << maxenergy << std::endl;
		std::cout << "Current Energy: " << currenergy << std::endl;
		std::cout << "Reaction: " << reaction << std::endl;
		std::cout << "Swing: " << swing << std::endl;
		std::cout << "Resistance: " << resistance << std::endl;
		std::cout << "Evasiveness: " << evasiveness << std::endl;
		//unique stats
		std::cout << "Intelligence: " << intelligence << std::endl;
		std::cout << "Focus: " << focus << std::endl;
		std::cout << "FocusMultiplier: " << focusmultiplier << std::endl;
		std::cout << "ReflectPercentage: " << reflectpercentage << std::endl << std::endl;
		//hidden stats

	}
};

//Manages ability IDs of this character
struct Abilities
{
private:
	//Vector of ability IDs that this character has
	std::vector<unsigned int> abilityList;
	//Vector of energy requirement for each ability
	std::vector<int> energyRequirement;

	//Current charged ability (-1 means no current charged ability)
	unsigned int currentChargeId = -1;
	//All targets for the charged attack
	unsigned int chargeTarget;

public:
	/*Get ability list*/
	std::vector<unsigned int> get_AbilityList() const { return abilityList; }
	/*REMOVE: Set ability list to v*/
	void set_AbilityList(const std::vector<unsigned int> v) { abilityList = v; }

	/*REMOVE: Get ability energy req list*/
	std::vector<int> get_EnergyRequirement() const { return energyRequirement; }

	//REORGANIZE

	/*Get ID of current charge ability*/
	int get_CurrentChargeId() const { return currentChargeId; }
	/*Set ID of current charge ability*/
	void set_CurrentChargeId(const int v) { currentChargeId = v; }
	/*Get charge targetID*/
	int get_ChargeTarget() const { return chargeTarget; }
	/*Set charge targetID*/
	void set_ChargeTarget(const int v) { chargeTarget = v; }

	//Return current number of Character's abilities
	unsigned int get_Size() const { return abilityList.size(); }

};


//Manages current status and any current statis effects for this character.
struct Status
{
private:
	//Used to measure diolouge behavior, -5 and 5 inclusive
	int mood = 0;

	//Set to false if this character is wiped out/destroyed
	bool isAlive = true;

	//Set to true if player, false otherwise
	bool isPlayer;

	//Set to true if character is currently defending
	bool defending = false;

	//Set to true if character is stunned. Cannot perform any action
	bool stunned = false;
	//Set to true if character is poisoned. Percent damage every turn, does not stack
	bool poison = false;
	//Set to true if character is silenced. Cannot use any abilities
	bool silenced = false;
	//Set to true if character is swing silenced. Cannot use any swing attacks
	bool swingsilenced = false;
	//Set to true if character is uncertain. Crit chance reduced to 0 and removes any crit modifiers
	bool uncertain = false;
	//Set to true if character is broken. Receives more damage from hostile swing attack
	bool broken = false;
	//Set to true if character is lethargic. Evasion chance is reduced by half
	bool lethargic = false;

public:
	/*Get defense*/
	bool get_Defending() const { return defending; }
	/*set defense to v (true or false)*/
	void set_Defending(const bool v) { defending = v; }

	/*Get isAlive status*/
	bool get_IsAlive() const { return isAlive; }
	/*Set isAlive to v (true or false)*/
	void set_IsAlive(const bool v) { isAlive = v; }

	/*Get isPlayer status*/
	bool get_IsPlayer() const { return isPlayer; }
	/*Set isPlayer to v (true or false)*/
	void set_IsPlayer(const bool v) { isPlayer = v; }

	/*Set all status affects to false, except poison*/
	void reset_Status()
	{
		defending = false;
		stunned = false;
		silenced = false;
		swingsilenced = false;
		uncertain = false;
		broken = false;
		lethargic = false;
	}
};

//Handles message prompts for this character
struct Message
{
private:
public:
};

//Manages character leveling/experience
struct Level
{
private:
	//current combat level
	int level = 0;
	/*Character's current exp or amount of exp awarded upon enemy death*/
	int experience = 0;

	//REMOVE: experience needed to reach the next level
	int levelRange[50] = { 50, 150, 300, 600, 1200, 2400, 4800 };

public:
	/*Get level*/
	int get_Level() const { return level; }
	/*set level to v*/
	void set_Level(const unsigned int v) { level = v; }
	/*Change level by adding v to level*/
	void change_Level(const int v)
	{
		if (v + level < 1) level = 1;
		else set_Level(v + level);
	}

	/*Get experience*/
	int get_Experience() const { return experience; }
	/*Set experience to v*/
	void set_Experience(const unsigned int v) { experience = v; }
	/*Change experience by adding v to experience*/
	void change_Experience(const int v)
	{
		if (v + experience < 1) experience = 0;
		else set_Experience(v + experience);
	}

	/*Check if character has leveled up.
	Returns: true if character is past next experience threshold*/
	bool checkLevelUp() const
	{
		if (get_Experience() >= levelRange[get_Level()]) return true;
		return false;
	}
};

//Manages item IDs that this charachter currently owns
struct Inventory
{
private:
	//List of all item IDs
	std::vector<unsigned int> itemsList;

	//FIX: (should be pointer to an element in itemsList) List of all pouch IDs
	std::vector<unsigned int> pouchList;

	//Max inventory size
	unsigned int maxcapacity;
	//Current inventory size
	unsigned int currentcapacity = 0;

public:
	/*Get all item IDs that this character has*/
	std::vector<unsigned int> get_ItemsList() const { return itemsList; }

	/*Get all pouch IDs*/
	std::vector<unsigned int> get_PouchList() const { return pouchList; }

	/*Add item ID to items list.
	Returns: true if item can be added*/
	bool add_Item(const unsigned int id, const unsigned int itemsize)
	{
		if (itemsize + currentcapacity > maxcapacity) return false;
		currentcapacity += itemsize;
		itemsList.push_back(id);
		std::sort(itemsList.begin(), itemsList.end());
		return true;
	}

	/*Removes an item from your inventory
	Parameter: ID of item to remove, weight of item*/
	void remove_Item(const unsigned int id, const unsigned int itemsize)
	{
		currentcapacity -= itemsize;
		itemsList.erase(find(itemsList.begin(), itemsList.end(), id));
	}

	/*Exchange item from pouch and inventory*/
	void change_Pouch()
	{

	}

	/*Removes an item from a pouch, but does not replace the now empty slot.*/
	void remove_Pouch()
	{

	}

	/*Get max inventory capacity*/
	int get_MaxCapacity() const { return maxcapacity; }
	/*Set max inventory capacity to v*/
	void set_MaxCapacity(const unsigned int v) { maxcapacity = v; }
	/*Change max inventory capacity by adding v to max size*/
	void change_MaxCapacity(const int v)
	{
		if (v + maxcapacity < 1) maxcapacity = 0;
		else set_MaxCapacity(v + maxcapacity);
	}
};

//Any Entity that can fight in battle
class Character : public Entity
{
public:
	//Pronoun for prompts
	std::string pronoun;

	//Index for which player/figment type
	std::string index;

	//Combat stats
	Stats stats;
	//Combat abilities
	Abilities abilities;
	//Current status
	Status status;
	//Current level
	Level level;
	//Messages specific to this character
	Message message;
	//Stores items tied to this character
	Inventory inventory;

	/*Given the following action, returns the energy required to complete it.
	Parameter: which action
	Returns: energy difference*/
	int get_EnergyDifference(const unsigned int action);
	/*When a swing attack is used, check if the attack is a critical.
	Returns: True, given a probability based on this character's focus stat*/
	bool check_Critical() const;
	/*When this character is attacked, check if this character can evade.
	Returns: True, given a probability based on this character's evasiveness stat*/
	bool check_Evasion() const;

	/*When this character attacks another, calculate this character's damage.
	Parameter: modifier to the swing stat
	Returns: final damage done*/
	int calculate_Damage(const float swingModifier);
	/*This function is called when this character is attacked by a swing based attack.
	First checks if the attack is evaded, then whether the attack was a critical attack, then whether this character is defending.
	Parameter: pointer to the character who is attacking this character, modifier to the swing stat*/
	void take_SwingDamage(Character *attacker, const float swingMultiplier);
	/*This function is calld when this character is attacked by a NON swing based attack
	Parameters: flat damage delt*/
	void take_NormalDamage(const int damage);

	/*This character will set its defense to true.*/
	void defend();
	/*This function is called when this character recieves retaliation damage, which occurs when this character attacks a defending target.
	Parameters: raw damage done to the defender, pointer to the defender*/
	void take_Retaliation(const int damage, Character *defender);

	/*Passes this character's turn in battle.*/
	void wait();

	/*Your entire party attempts to run from battle.
	Returns: Returns true if run is successful, given probability.*/
	bool run();

	virtual int get_Digits() = 0;
	virtual int get_Eps() = 0;

protected:
	virtual void assign_StartInfo(std::string filename, const unsigned int number) = 0;

};