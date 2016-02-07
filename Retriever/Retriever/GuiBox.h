#pragma once

#include "Entity.h"
#include <string>

#include <allegro5/allegro5.h>
#include <allegro5/allegro_image.h>

class GuiBox: public Entity
{
public:
	/*Constructor: */
	GuiBox(ALLEGRO_BITMAP* buffer,
		const Position position, const Position scale,
		const std::string path,
		const unsigned int id);

	/*Hides or shows gui element
	Parameters: set to true if hiding*/
	void setActive(bool b);

	/*Draw this GUI*/
	void drawGui();

	/*Reset interface to original values*/
	void resetInterface();

	//id of box
	int gui_id;

	ALLEGRO_BITMAP* buffer;

	//set to true if box should display
	bool active;
protected:

private:
};

