#include "stdafx.h"
#include "GuiBox.h"

using namespace std;

//----------------------------PUBLIC----------------------------//

/*CONSTRUCTOR: Set status of interface, pass off vars to Entity*/
GuiBox::GuiBox(ALLEGRO_BITMAP* buffer,
	const Position p, const Position s,
	const std::string path,
	const unsigned int id,
	const bool isInterface)
	:Entity(p, s, path), buffer(buffer), isInterface(isInterface)
{
	visible = true;
}

/*Hides or shows gui element.
Parameters: set to true if hiding*/
void GuiBox::setVisible(bool b) 
{
	visible = b;
}

/*Get box visible status*/
bool GuiBox::getVisible() const 
{
	return visible;
}

/*Draw this Gui Box*/
void GuiBox::drawGui()
{
	al_draw_scaled_bitmap(bm,
	0, 0,
	dimensions.get_x(), dimensions.get_y(),
	position.get_x(), position.get_y(),
	dimensions.get_x() * scale.get_x(), dimensions.get_y() * scale.get_y(),
	0);
}

/*Reset interface to original values*/
void GuiBox::resetInterface()
{

}

/*Install activate handler for this box, by adding to the handlerList
Parameters: handler type, optional key that handler is responsible for, 
control set to true if handler type can be enabled or disabled manually
false if enabled only during visible=true*/
void GuiBox::installHandler(const unsigned int type, const unsigned int key, const bool control)
{
	if (control) controlHandlerList[key] = make_pair(control, type);
	else handlerList[key] = type;
}

/*Set an existing specific control handler to true or false
Parameters: control handler type, control handler key, set the control handler to true/false*/
void GuiBox::setControlHandler(const unsigned int type, const unsigned int key, const bool active)
{
	std::map<int, pair<bool, int> >::iterator it = controlHandlerList.find(key);
	if (it != controlHandlerList.end())
	{
		it->second.first = active;
	}
}

/*Check all handlers to see if event has occured.
Parameters: key that was pressed this tick, status variable that may be returned*/
void GuiBox::checkAllHandlers(const unsigned int key, unsigned int &status)
{
	//if no keys exist in both handler lists, return
	if (handlerList.count(key) == 0 && controlHandlerList.count(key) == 0) return;

	//check control list
	for (map<int, pair <bool, int> >::iterator it = controlHandlerList.begin(); it != controlHandlerList.end(); it++)
	{
		//if key matches and handler is active
		if (it->first == key && it->second.first)
		{
			//check if this map element matches the inputted key
			if (it->first == key)
			{
				//cout << it->second.second << endl;
				switch (it->second.second)
				{
				case Activate:
					visible = !visible;
					if (isInterface)
					{
						if (visible) status = SetNewInterface;
						else status = InterfaceDeactivated;
					}
					break;
				default:
					cerr << "Invalid GUI control handler event." << endl;
				}
				return;
			}
		}
	}

	//check handler list, but make sure this gui is active
	for (map<int, int>::iterator it = handlerList.begin(); visible && it != handlerList.end(); it++)
	{
		//check if this map element matches the inputted key
		if (it->first == key)
		{
			switch (it->second)
			{
			case Activate:
				visible = false;
				if (isInterface) status = InterfaceDeactivated;
				break;
			case Button:
				break;
			default:
				cerr << "Invalid GUI handler event." << endl;
			}
			return;
		}
	}
}

//----------------------------PROTECTED----------------------------//


//----------------------------PRIVATE----------------------------//