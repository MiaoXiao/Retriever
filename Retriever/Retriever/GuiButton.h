#pragma once

#include "GuiBox.h"

/*Gui element that can be selected, and can obtain the cursor*/
class GuiButton: public GuiBox
{
public:
	/*CONSTRUCTOR:*/
	GuiButton(ALLEGRO_BITMAP* cursor, ALLEGRO_BITMAP* buffer,
		const Position p, const Position s,
		const std::string path,
		const unsigned int id);

	/*Draw Button*/
	void drawGui();

	//does this button have the cursor?
	bool hasCursor;
private:
	//cursor picture
	ALLEGRO_BITMAP* cursor;
};

