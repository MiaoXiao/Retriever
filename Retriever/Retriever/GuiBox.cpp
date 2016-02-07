#include "stdafx.h"
#include "GuiBox.h"

using namespace std;

//----------------------------PUBLIC----------------------------//

/*Constructor: Set status of interface, pass off vars to Entity*/
GuiBox::GuiBox(ALLEGRO_BITMAP* buffer,
	const Position position, const Position scale,
	const string path,
	const unsigned int id)
	:Entity(position, scale, path), keyCodeActivate(NULL)
{
	if (buffer != NULL) buffer = buffer;
	setVisible(true);
}

/*Hides or shows gui element. If visible and an interface, make it the active interface
Parameters: set to true if hiding*/
void GuiBox::setVisible(bool b)
{ 
	visible = b;
}

/*Install activate handler for this box
Parameters: handler type, optional key */
void GuiBox::installHandler(unsigned int type, unsigned int key)
{
	keyCodeActivate = key;
}

/*Draw this GUI*/
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


//----------------------------PROTECTED----------------------------//


//----------------------------PRIVATE----------------------------//