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
	void setVisible(bool b);

	/*Intall activate handler for this box
	Parameters: handler type, optional key */
	void installHandler(unsigned int type, unsigned int key);

	/*Draw this GUI*/
	void drawGui();

	/*Reset interface to original values*/
	void resetInterface();

	//id of box
	int gui_id;

	ALLEGRO_BITMAP* buffer;

	//set to true if box should display
	bool visible;

protected:
	//set to true if interface
	bool isInterface;

private:
	//key code to turn interface/box visible or invisible
	unsigned int keyCodeActivate;
};

