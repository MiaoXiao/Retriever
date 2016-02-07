#pragma once

#include <allegro5/allegro5.h>
#include <allegro5/allegro_image.h>

#include <string>
#include <vector>
#include <map>

#include "Interface.h"
#include "Globals.h"

/*Manages and displays graphic user interface elements*/
class GuiManager
{
public:
	/*CONSTRUCTOR: */
	GuiManager(ALLEGRO_BITMAP* buffer);

	/*Create interface for permanent use. Add interface to list given unique id
	Parameters: buffer for drawing, position of bitmap, path of bitmap*/
	void createInterface(const Position p, const std::string path);

private:
	//pointer to draw screen
	ALLEGRO_BITMAP* buffer;
	//stores all interfaces which may display in game
	std::vector<Interface> interfaceList;
};

