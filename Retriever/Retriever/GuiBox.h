#pragma once

#include "Entity.h"
#include <vector>
#include <utility>
#include <string>
#include <map>

#include <allegro5/allegro5.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>

//Handler Types
enum HandlerType {Activate, MoveCursor, GuiTransition};

/*Status Return Types
SetNewInterface: Determines that this gui is now the new active interface
InterfaceDeactivated: This gui interface was deactivated
InterfaceChange: interface is changing to another*/
enum StatusType {SetNewInterface = 1, InterfaceDeactivated, InterfaceChange};

/*Basic gui element*/
class GuiBox: public Entity
{
public:
	/*CONSTRUCTOR: Set status of interface, pass off vars to Entity*/
	GuiBox(ALLEGRO_BITMAP* buffer,
		const Position p, const Position s,
		const std::string path,
		const unsigned int id,
		GuiBox* parent);

	/*Hides or shows gui element.
	Parameters: set to true if visible*/
	void setVisible(const bool b);
	/*Get box visible status*/
	bool getVisible() const;

	/*Draw this Gui Box*/
	void drawGui();
	
	//id of gui element
	int gui_id;
	//pointer to parent
	GuiBox *parent;

	//does this box have the cursor?
	bool hasCursor;

	/*Adds a new child gui to this GuiBox, given the offset
	Parameter: Parent gui, Offset to place child element, scale of new child, filename*/
	void addChild(const Position offset, const Position scaleModifier, const std::string path);

protected:
	//List of pointers to children that belong to this interface
	std::vector<GuiBox*> childList;

private:
	//draw buffer
	ALLEGRO_BITMAP* buffer;
	//set to true if box should display
	bool visible;
};

