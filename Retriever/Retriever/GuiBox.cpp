#include "stdafx.h"
#include "GuiBox.h"

using namespace std;

//----------------------------PUBLIC----------------------------//

/*CONSTRUCTOR: Parent is interface*/
GuiBox::GuiBox(ALLEGRO_BITMAP* buffer,
	const Position p, const Position s,
	const std::string path,
	const unsigned int id)
	:Entity(p, s, path), buffer(buffer), gui_id(id), visible(false)
{
	if (buffer == NULL)
	{
		cerr << "Buffer is null" << endl;
		al_rest(10);
		exit(1);
	}
}

/*Hides or shows gui element.
Parameters: set to true if visible*/
void GuiBox::setVisible(bool b) 
{
	visible = b;
	for (unsigned int i = 0; i < childList.size(); ++i)
	{
		childList[i]->setVisible(b);
	}
}

/*Get box visible status*/
bool GuiBox::getVisible() const 
{
	return visible;
}

/*Draw this Gui Box*/
void GuiBox::drawGui()
{
	//cout << "test dimensions: " << dimensions.get_x() << " " << dimensions.get_y() << endl << endl;
	//cout << "test position: " << position.get_x() << " " << position.get_y() << endl << endl;
	//cout << "test scale: " << scale.get_x() << " " << scale.get_y() << endl << endl;
	if (getVisible()) al_draw_bitmap(bmp, minPos.get_x(), minPos.get_y(), 0);
	//recursively draw its children
	for (unsigned int i = 0; i < childList.size(); ++i)
	{
		childList[i]->drawGui();
	}

}

//----------------------------PROTECTED----------------------------//


//----------------------------PRIVATE----------------------------//
