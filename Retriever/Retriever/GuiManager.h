#pragma once

#include <allegro5/allegro5.h>
#include <allegro5/allegro_image.h>

#include <string>
#include <vector>
#include <map>

#include "Entity.h"
#include "GuiBox.h"
#include "GuiInterface.h"
#include "Globals.h"

/*Manages and displays graphic user interface elements*/
class GuiManager
{
public:
	/*CONSTRUCTOR:*/
	GuiManager(ALLEGRO_BITMAP* buffer);

	/*Create Interface for permanent use.
	Parameters: position of bitmap, scale of bitmap, path of bitmap, which menu to build*/
	void createInterface(const Position p, const Position s,
		const std::string path, 
		const unsigned int menu);

	/*Draw all interfaces.*/
	void drawInterfaces();

	/*Handle all keyboard events for current GUI interface
	Parameter: Key that was pressed this tick*/
	void handleGuiEvents(const unsigned int key);

	//id of active interface
	GuiInterface* activeInterface;

protected:

private:
	//pointer to draw screen
	ALLEGRO_BITMAP* buffer;

	//stores all interfaces
	std::vector<GuiInterface> allInterfaceList;

	/* Checks return status, based on the handler
	Parameters: current status, reference to guibox for possible edits*/
	void checkStatus(const unsigned int status, const int newid, GuiInterface &gui);
};

