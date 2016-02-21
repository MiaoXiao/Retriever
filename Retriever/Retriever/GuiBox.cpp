#include "stdafx.h"
#include "GuiBox.h"

using namespace std;

//----------------------------PUBLIC----------------------------//

/*CONSTRUCTOR: Set status of interface, pass off vars to Entity*/
GuiBox::GuiBox(ALLEGRO_BITMAP* buffer,
	const Position p, const Position s,
	const std::string path,
	const unsigned int id,
	GuiBox* parent)
	:Entity(p, s, path), buffer(buffer), gui_id(id), parent(parent), visible(false), hasCursor(false)
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
	al_draw_bitmap(bmp, minPos.get_x(), minPos.get_y(), 0);
	//draw cursor if neccessary
	if (hasCursor)
	{
		al_draw_filled_rectangle(minPos.get_x() - 5, minPos.get_y() - 5,
			minPos.get_x() + 15,
			minPos.get_y() + 15,
			al_map_rgb(211, 124, 183));
	}
	//recursively draw its children
	for (unsigned int i = 0; i < childList.size(); ++i)
	{
		childList[i]->drawGui();
	}

}

//----------------------------PROTECTED----------------------------//

/*Adds child gui to a GuiBox, given the offset
Parameter: Parent gui, Offset to place child element, scale of new child, filename*/
void GuiBox::addChild(const Position offset, const Position scaleModifier, const std::string path)
{
	Position p(minPos.get_x() + offset.get_x(), minPos.get_y() + offset.get_y());
	Position s(scale.get_x() * scaleModifier.get_x(), scale.get_y() * scaleModifier.get_y());

	GuiBox* child = new GuiBox(buffer, p, s, path, childList.size(), this);
	childList.push_back(child);
}


//----------------------------PRIVATE----------------------------//
