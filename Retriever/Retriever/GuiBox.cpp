#include "stdafx.h"
#include "GuiBox.h"

using namespace std;

//----------------------------PUBLIC----------------------------//

/*Constructor: Set status of interface, pass off vars to Entity*/
GuiBox::GuiBox(ALLEGRO_BITMAP* buffer,
	const Position position, const Position scale,
	const std::string path,
	const unsigned int id,
	const bool isInterface)
	:Entity(position, scale, path), buffer(buffer), isInterface(isInterface)
{
	visible = true;
}

/*Hides or shows gui element. If visible and an interface, make it the active interface
Parameters: set to true if hiding
Returns: true if this is the new active interface*/
bool GuiBox::setVisible(bool b)
{ 
	visible = b;
	return isInterface && b;
}

/*Draw this Gui Box*/
void GuiBox::drawGui()
{
	al_draw_bitmap(bm, position.get_x(), position.get_y(), 0);

	//How does scaling this work???
	/*
	al_draw_scaled_bitmap(bm, 0, 0,
	dimensions.get_x(), dimensions.get_y(),
	0,
	0,
	(dimensions.get_x() * scale.get_x()),
	(dimensions.get_y() * scale.get_y()), 0);*/
}

/*Reset interface to original values*/
void GuiBox::resetInterface()
{

}

/*Install activate handler for this box, by adding to the handlerList
Parameters: handler type, optional key that handler is responsible for */
void GuiBox::installHandler(unsigned int type, unsigned int key)
{
	handlerList[key] = type;
}

/*Check all handlers to see if event has occured
Parameters: key that was pressed this tick*/
void GuiBox::checkHandlers(unsigned int key)
{

}

//----------------------------PROTECTED----------------------------//


//----------------------------PRIVATE----------------------------//