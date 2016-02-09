#include "stdafx.h"
#include "GameObject.h"

using namespace std;

//----------------------------PUBLIC----------------------------//

/*Return game object name*/
string GameObject::get_Name() const { return name; }
/*Change game object name*/
void GameObject::set_Name(const std::string v) { name = v; }

/*Return game object description*/
std::string GameObject::get_Description() const { return description; }
/*Change game object descriptionn*/
void GameObject::set_Description(const std::string v) { description = v; }

/*Returns game object ID*/
unsigned int GameObject::get_Id() const { return id; }
/*Change game object ID*/
void GameObject::set_Id(unsigned int v) { id = v; }

//----------------------------PROTECTED----------------------------//

//----------------------------PRIVATE----------------------------//