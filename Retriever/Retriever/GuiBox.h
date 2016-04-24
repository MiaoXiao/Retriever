#pragma once

#include "Entity.h"
#include <vector>
#include <utility>
#include <string>
#include <map>

#include <allegro5/allegro5.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>

/*Type of gui*/
enum GuiType {Box, Button};

class GuiButton;

/*Basic gui element*/
class GuiBox: public Entity
{
public:
	/*CONSTRUCTOR: Default constructor*/
	GuiBox();
	/*CONSTRUCTOR: Parent is interface*/
	GuiBox(ALLEGRO_BITMAP* buffer,
		const Position p, const Position s,
		const std::string path,
		const unsigned int id);

	/*Hides or shows gui element.
	Parameters: set to true if visible*/
	void setVisible(const bool b);
	/*Get box visible status*/
	bool getVisible() const;

	/*Draw this Gui Box*/
	virtual void drawGui();
	
	//id of gui element
	unsigned int gui_id;

	//pointer to parent
	//GuiBox *parent_box;
	//GuiInterface *parent_interface;

	//list of all valid pointers to buttons
	std::vector<GuiButton*> buttonList;
	//List of pointers to boxes that belong to this interface
	std::vector<GuiBox*> childList;

protected:

private:
	//draw buffer
	ALLEGRO_BITMAP* buffer;
	//set to true if box should display
	bool visible;
};

