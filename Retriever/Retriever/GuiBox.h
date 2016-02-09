#pragma once

#include "Entity.h"
#include <vector>
#include <string>
#include <map>

#include <allegro5/allegro5.h>
#include <allegro5/allegro_image.h>

/*Basic gui element*/
class GuiBox: public Entity
{
public:
	/*Constructor: Set status of interface, pass off vars to Entity*/
	GuiBox(ALLEGRO_BITMAP* buffer,
		const Position p, const Position s,
		const std::string path,
		const unsigned int id,
		const bool isInterface);

	/*Hides or shows gui element. If visible and an interface, make it the active interface
	Parameters: set to true if hiding
	Returns: true if this is the new active interface*/
	bool setVisible(bool b);

	/*Draw this Gui Box*/
	void drawGui();

	/*Reset interface to original values*/
	void resetInterface();

	/*Install activate handler for this box
	Parameters: handler type, optional key that handler is responsible for */
	void installHandler(unsigned int type, unsigned int key);

	/*Check Handlers: visible on/off, switching interfaces, buttons
	Parameters: key that was pressed this tick*/
	void checkHandlers(unsigned int key);

	//id of gui element
	int gui_id;
	//set to true if box should display
	bool visible;
	//set to true if interface
	bool isInterface;
	//List of children pointers that belong to this box/interface
	std::vector<GuiBox*> childList;
protected:

private:
	//draw buffer
	ALLEGRO_BITMAP* buffer;

	//List of all handlers
	std::map<int, int> handlerList;

};

