#pragma once

#include <allegro5/allegro5.h>
#include <allegro5/allegro_image.h>

#include <string>
#include <vector>
#include <map>

#include "Entity.h"
#include "GuiBox.h"
#include "Globals.h"

/*Manages and displays graphic user interface elements*/
class GuiManager
{
public:
	/*CONSTRUCTOR:*/
	GuiManager();

	/*Create GuiBox for permanent use.
	Parameters: position of bitmap, scale of bitmap, path of bitmap, which menu to build*/
	void createGuiBox(ALLEGRO_BITMAP* buffer, 
		const Position position, const Position scale,
		const std::string path, 
		const unsigned int menu);

	/*Draw all interfaces and its children.*/
	void drawInterfaces();

	/*Handle all keyboard events for any visible Gui elements
	Parameter: Key that was pressed this tick*/
	void allHandlers(unsigned int key);

	/*Adds child gui to a GuiBox, given the offset
	Parameter: Parent gui, Offset to place child element, scale of new child, filename*/
	void addChild(GuiBox parent, Position offset, Position scale, const std::string path);

private:
	//pointer to draw screen
	ALLEGRO_BITMAP* buffer;

	//stores all interfaces
	std::vector<GuiBox> interfaceList;
	//stores all children
	std::vector<GuiBox> boxList;

	//id of active interface
	unsigned int activeInterface;
};

