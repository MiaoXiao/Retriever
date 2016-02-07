#pragma once
#include "GuiBox.h"

#include <string>

class GuiChild: public GuiBox
{
public:
	/*Constructor: Always positioned inside its parent*/
	GuiChild(const Position position, const Position scale,
		const std::string path, 
		const unsigned int id);

	/*Hide or show this gui child
	Parameter: set to true if hiding*/
	void setActive(bool b);
private:
};

