#pragma once

#include <string>

//Game object that is displayed on screen
class Entity
{
public:
	/*Return entity name*/
	std::string get_Name() const;
	/*Change entity name*/
	void set_Name(const std::string v);

	/*Return entity description*/
	std::string get_Description() const;
	/*Change entity descriptionn*/
	void set_Description(const std::string v);

	/*Returns entity ID*/
	unsigned int get_Id() const;
	/*Change entity ID*/
	void set_Id(unsigned int v);

protected:
	//Name of entity
	std::string name;

	//Description of entity
	std::string description;

	//ID of entity
	unsigned int id;
};

