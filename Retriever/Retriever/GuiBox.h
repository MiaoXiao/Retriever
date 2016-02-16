#pragma once

#include "Entity.h"
#include <vector>
#include <utility>
#include <string>
#include <map>

#include <allegro5/allegro5.h>
#include <allegro5/allegro_image.h>

//Handler Types
enum HandlerType {Activate, GuiTransition, Button};

/*Status Return Types
SetNewInterface: Determines that this gui is now the new active interface
InterfaceDeactivated: This gui interface was deactivated
*/
enum StatusType {SetNewInterface = 1, InterfaceDeactivated};

/*Basic gui element*/
class GuiBox: public Entity
{
public:
	/*CONSTRUCTOR: Set status of interface, pass off vars to Entity*/
	GuiBox(ALLEGRO_BITMAP* buffer,
		const Position p, const Position s,
		const std::string path,
		const unsigned int id,
		const bool isInterface);

	/*Hides or shows gui element.
	Parameters: set to true if hiding*/
	void setVisible(const bool b);

	/*Get box visible status*/
	bool getVisible() const;

	/*Draw this Gui Box*/
	void drawGui();

	/*Reset interface to original values*/
	void resetInterface();

	/*Install activate handler for this box, by adding to the handlerList
	Parameters: handler type, optional key that handler is responsible for,
	control set to true if handler can be enabled or disabled manually: false if enabled only during visible=true*/
	void installHandler(const unsigned int type, const unsigned int key, const bool control);

	/*Set an existing specific control handler to true or false
	Parameters: control handler type, control handler key, set the control handler to true/false*/
	void setControlHandler(const unsigned int type, const unsigned int key, const bool active);

	/*Check all handlers to see if event has occured.
	Parameters: key that was pressed this tick, status variable that may be returned*/
	void checkAllHandlers(const unsigned int key, unsigned int &status);

	//id of gui element
	int gui_id;
	//set to true if interface
	bool isInterface;
	//List of children pointers that belong to this box/interface
	std::vector<GuiBox> childList;
protected:

private:
	//draw buffer
	ALLEGRO_BITMAP* buffer;

	//set to true if box should display
	bool visible;

	//list of all valid guids to transition to
	std::vector<unsigned int> transitionList;

	//List of all handlers that are only enabled when gui is visible
	std::map<int, int> handlerList;

	//List of all handlers that can be enabled/disabled at any time
	//value is set to true or false depending on whether it is active or not
	std::map<int, std::pair<bool, int> > controlHandlerList;

};

