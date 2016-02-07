#pragma once

#include <queue>
#include <string>

#include "GuiBox.h"
#include "GuiChild.h"

#include <allegro5/allegro5.h>
#include <allegro5/allegro_image.h>

/*Parent of images/animations/buttons for the GUI*/
class GuiInterface: public GuiBox
{
public:
	/*CONSTRUCTOR: Pass all variables to base class guibox*/
	GuiInterface(ALLEGRO_BITMAP* buffer,
		const Position position, const Position scale,
		const std::string path,
		const unsigned int id);


	/*Adds child gui to this interface, given the offset
	Parameter: Offset to place child element, scale of new child, filename*/
	void addChild(Position offset, Position scale, const std::string path);

	//list of all children inside this interface
	std::vector<GuiChild> childList;
private:

};

