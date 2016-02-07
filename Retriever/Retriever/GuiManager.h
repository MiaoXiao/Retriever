#pragma once

#include <allegro5/allegro5.h>
#include <allegro5/allegro_image.h>

#include <string>
#include <vector>
#include <map>

#include "Entity.h"
#include "GuiInterface.h"
#include "Globals.h"

/*Manages and displays graphic user interface elements*/
class GuiManager
{
public:
	/*CONSTRUCTOR:*/
	GuiManager();

	/*Create interface for permanent use.
	Parameters: position of bitmap, scale of bitmap, path of bitmap, which menu to build*/
	void createInterface(ALLEGRO_BITMAP* buffer, 
		const Position position, const Position scale,
		const std::string path, 
		const unsigned int menu);

	/*Check Handlers: visible on/off, switching interfaces, buttons*/
	void checkHandlers();

	/*Draw all non hidden interfaces and its non hidden children.*/
	void drawInterfaces();

private:
	//pointer to draw screen
	ALLEGRO_BITMAP* buffer;
	//stores all interfaces which may display in game
	std::vector<GuiInterface> interfaceList;

	//id of active interface
	unsigned int activeInterface;
};

