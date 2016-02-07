#include "stdafx.h"
#include "GuiInterface.h"

using namespace std;

//----------------------------PUBLIC----------------------------//

/*CONSTRUCTOR: Pass all variables to base class guibox*/
GuiInterface::GuiInterface(ALLEGRO_BITMAP* buffer, 
	const Position position, const Position scale,
	const string path, 
	const unsigned int id)
	:GuiBox(buffer, position, scale, path, id)
{
	isInterface = true;
}

/*Adds child gui to this interface, given the offset
Parameter: Offset to place child element, scale of new child, filename*/
void GuiInterface::addChild(Position offset, Position scale, const std::string path)
{
	Position p(position.get_x() + offset.get_x(), position.get_y() + offset.get_y());
	GuiChild gc(p, scale, path, childList.size());
	childList.push_back(gc);
}

//----------------------------PROTECTED----------------------------//


//----------------------------PRIVATE----------------------------//

