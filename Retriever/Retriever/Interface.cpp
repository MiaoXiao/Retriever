#include "stdafx.h"
#include "Interface.h"

using namespace std;

Interface::Interface(ALLEGRO_BITMAP* buffer, const Position p, const string path, const unsigned int id)
	:active(false), gui_id(id)
{
	loadImage(path);
	position = p;
}

/*Set active, which decides whether to display interface and all its components
Parameter: show interface or not*/
void Interface::setActive(bool b) { active = b;}
