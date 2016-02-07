#include "stdafx.h"
#include "GuiChild.h"

using namespace std;

//----------------------------PUBLIC----------------------------//

/*Constructor: Always positioned inside its parent*/
GuiChild::GuiChild(const Position position, const Position scale,
	const std::string path,
	const unsigned int id)
	:GuiBox(NULL, position, scale, path, id)
{
	isInterface = false;
}

//----------------------------PROTECTED----------------------------//


//----------------------------PRIVATE----------------------------//
