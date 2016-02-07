#pragma once

#include <queue>
#include <string>

#include "Entity.h"
#include "Globals.h"

#include <allegro5/allegro5.h>
#include <allegro5/allegro_image.h>


/*Group of images/animations/buttons for the GUI*/
class Interface: public Entity
{
public:
	/*CONSTRUCTOR: */
	Interface(ALLEGRO_BITMAP* buffer, const Position p, const std::string path, const unsigned int id);

	/*Set active, which decides whether to display interface and all its components
	Parameter: show interface or not*/
	void setActive(bool b);

private:
	//id of interface
	int gui_id;
	//set to true if interface should display
	bool active;

	//list of all boxes inside interface
	//vector<Box> boxList;
};

