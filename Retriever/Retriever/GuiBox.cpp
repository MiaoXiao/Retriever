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
	:Entity(p, s, path), buffer(buffer), gui_id(id), isInterface(isInterface), hasCursor(false)
{
	visible = true;
	cout << "creating new guibox: " << endl;
	if (buffer == NULL)
	{
		cerr << "Buffer is null" << endl;
		al_rest(10);
		exit(1);
	}
	cout << "Gui id: " << id << endl << endl;
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
	//cout << "test dimensions: " << dimensions.get_x() << " " << dimensions.get_y() << endl << endl;
	//cout << "test position: " << position.get_x() << " " << position.get_y() << endl << endl;
	//cout << "test scale: " << scale.get_x() << " " << scale.get_y() << endl << endl;
	//cout << "drawing" << endl;
	al_draw_scaled_bitmap(bm,
	0, 0,
	dimensions.get_x(), dimensions.get_y(),
	position.get_x(), position.get_y(),
	dimensions.get_x() * scale.get_x(), dimensions.get_y() * scale.get_y(),
	0);

	//draw cursor if neccessary
	if (hasCursor)
	{
		if (cursor == NULL) // default cursor
		{
			al_draw_filled_rectangle(position.get_x() - 5, position.get_y() - 5,
				position.get_x() + 15,
				position.get_y() + 15,
				al_map_rgb(211, 124, 183));
		}
		else //custom cursor
		{

		}
	}

	//cout << "finished drawing" << endl;
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
void GuiBox::setControlHandle(const unsigned int type, const unsigned int key, const bool active)
{
	std::map<int, pair<bool, int> >::iterator it = controlHandlerList.find(key);
	if (it != controlHandlerList.end())
	{
		it->second.first = active;
	}
}

/*Installs gui with cursur. Fills transition grid with children ids
Parameter: n by n size of grid*/
void GuiBox::installCursor(unsigned int size)
{
	if (size == 0 || size == 1)
	{
		cerr << "Error with installing cursor: Size of transition grid cannot be " << size << ". " << endl;
		return;
	}

	//init transition grid
	vector<unsigned int> v;
	for (unsigned int i = 0; i < size; ++i)
	{
		transitionGrid.push_back(v);
	}

	//fill transition grid
	unsigned int j = 0;
	for (unsigned int i = 0; i < size; ++i)
	{
		cout << j << endl;
		for (unsigned k = 0; j < childList.size() && k < size; ++k)
		{
			transitionGrid[i].push_back(childList[j].gui_id);
			++j;
		}
	}

	childList[0].hasCursor = true;
	cursorPos.set(0, 0);
	installHandler(MoveCursor, ALLEGRO_KEY_LEFT, false);
	installHandler(MoveCursor, ALLEGRO_KEY_RIGHT, false);
	installHandler(MoveCursor, ALLEGRO_KEY_UP, false);
	installHandler(MoveCursor, ALLEGRO_KEY_DOWN, false);

	
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
			case MoveCursor:
				//find current cursor
				for (unsigned int i = 0; i < childList.size(); ++i)
				{
					if (childList[i].hasCursor)
					{
						changeCursor(i, key);
						//exit loop
						i = childList.size();
					}
				}
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

/*Change which child now has the cursor.
Parameters: index of child that currently has the cursor, key that was pressed*/
void GuiBox::changeCursor(unsigned int index, unsigned int key)
{
	int x = cursorPos.get_x();
	int y = cursorPos.get_y();
	//cout << "Last pos: " << x << " " << y << endl;
	childList[transitionGrid[x][y]].hasCursor = false;
	switch (key)
	{
	case ALLEGRO_KEY_UP:
		if (x + 1 == transitionGrid.size()) x = 0;
		else x++;
		break;
	case ALLEGRO_KEY_RIGHT:
		if (y + 1 == transitionGrid.size()) y = 0;
		else y++;
		break;
	case ALLEGRO_KEY_DOWN:
		if (x - 1 == -1) x = transitionGrid.size() - 1;
		else x--;
		break;
	case ALLEGRO_KEY_LEFT:
		if (y - 1 == -1) y = transitionGrid.size() - 1;
		else y--;
		break;
	}
	childList[transitionGrid[x][y]].hasCursor = true;
	cursorPos.set(x, y);
	//cout << "current cursor pos: " << x << " " << y << endl << endl;
}