#include "stdafx.h"
#include "Entity.h"

using namespace std;

//----------------------------PUBLIC----------------------------//

/*Return entity name*/
string Entity::get_Name() const { return name; }
/*Change entity name*/
void Entity::set_Name(const std::string v) { name = v; }

/*Return entity description*/
std::string Entity::get_Description() const { return description; }
/*Change entity descriptionn*/
void Entity::set_Description(const std::string v) { description = v; }

/*Returns entity ID*/
unsigned int Entity::get_Id() const { return id; }
/*Change entity ID*/
void Entity::set_Id(unsigned int v) { id = v; }

//----------------------------PROTECTED----------------------------//

//----------------------------PRIVATE----------------------------//