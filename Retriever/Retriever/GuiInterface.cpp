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

//----------------------------PROTECTED----------------------------//


//----------------------------PRIVATE----------------------------//

