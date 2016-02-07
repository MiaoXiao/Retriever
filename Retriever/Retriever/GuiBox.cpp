#include "stdafx.h"
#include "GuiBox.h"

using namespace std;

//----------------------------PUBLIC----------------------------//

/*Constructor: Set status of interface, pass off vars to Entity*/
GuiBox::GuiBox(ALLEGRO_BITMAP* buffer,
	const Position position, const Position scale,
	const string path,
	const unsigned int id)
	:Entity(position, scale, path)
{
	if (buffer != NULL) buffer = buffer;
	setActive(true);
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

/*Hides or shows gui element
Parameters: set to true if hiding*/
void GuiBox::setActive(bool b) { active = b; }

//----------------------------PROTECTED----------------------------//


//----------------------------PRIVATE----------------------------//