#pragma once

#include <string>

#include "Entity.h"
#include "Globals.h"

//Any Entity that is not part of the GUI
class GameObject: public Entity
{
public:
	/*CONSTRUCTOR: set all variables to null*/
	GameObject();

	/*Return game object name*/
	std::string get_Name() const;
	/*Change game object name*/
	void set_Name(const std::string v);

	/*Return game object description*/
	std::string get_Description() const;
	/*Change game object descriptionn*/
	void set_Description(const std::string v);

	/*Returns game object ID*/
	unsigned int get_Id() const;
	/*Change game object ID*/
	void set_Id(unsigned int v);

protected:
	//Name of game object
	std::string name;

	//Description of game object
	std::string description;

	//ID of game object
	unsigned int id;
};

