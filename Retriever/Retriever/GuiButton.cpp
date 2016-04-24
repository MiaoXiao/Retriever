#include "stdafx.h"
#include "GuiButton.h"

using namespace std;

/*CONSTRUCTOR:*/
GuiButton::GuiButton(ALLEGRO_BITMAP* cursor, ALLEGRO_BITMAP* buffer,
	const Position p, const Position s,
	const std::string path,
	const unsigned int id)
	:GuiBox(buffer, p, s, path, id), cursor(cursor), hasCursor(false){}

/*Draw Button*/
void GuiButton::drawGui()
{
	//draw cursor if neccessary
	if (hasCursor)
	{
		al_draw_filled_rectangle(minPos.get_x() - 5, minPos.get_y() - 5,
			minPos.get_x() + 15,
			minPos.get_y() + 15,
			al_map_rgb(211, 124, 183));
	}

	al_draw_bitmap(bmp, minPos.get_x(), minPos.get_y(), 0);
	//recursively draw its children
	for (unsigned int i = 0; i < childList.size(); ++i)
	{
		childList[i]->drawGui();
	}
}
