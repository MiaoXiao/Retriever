#include "stdafx.h"
#include "GuiManager.h"

using namespace std;

//----------------------------PUBLIC----------------------------//

/*CONSTRUCTOR:*/
GuiManager::GuiManager()
	:activeInterfaceId(NULL)
{
}

/*Create Interface for permanent use.
Parameters: position of bitmap, scale of bitmap, path of bitmap, which menu to build*/
void GuiManager::createInterface(ALLEGRO_BITMAP* buffer,
	const Position p, const Position s,
	const string path,
	const unsigned int menu)
{
	GuiBox interface(buffer, p, s, path, allInterfaceList.size(), true);

	//Menu 0: creat test menu, with child 50% smaller in center of parent
	switch (menu)
	{
	case 0:
		//create child
		Position offset(interface.dimensions.get_x() / 2, interface.dimensions.get_y() / 2);
		Position s(0.5, 0.5);
		addChild(interface, offset, s, path);

		//add activate handler
		interface.installHandler(Activate, ALLEGRO_KEY_I, true);
		break;
	}
	allInterfaceList.push_back(interface);
}

/*Draw all interfaces and its children.*/
void GuiManager::drawInterfaces()
{
	for (unsigned int i = 0; i < allInterfaceList.size(); ++i)
	{
		if (allInterfaceList[i].getVisible())
		{
			//cout << "drawing interface" << endl;
			allInterfaceList[i].drawGui();
			//cout << interfaceList[i].childList.size() << endl;
			for (unsigned int j = 0; j < allInterfaceList[i].childList.size(); ++j)
			{
				//cout << "checking child" << endl;
				if (allInterfaceList[i].childList[j]->getVisible())
				{
					//cout << "drawing child" << endl;
					allInterfaceList[i].childList[j]->drawGui();
				}
			}
		}
	}
}

/*Handle all keyboard events for every valid interface and its children
Parameter: Key that was pressed this tick*/
void GuiManager::handleGuiEvents(const unsigned int key)
{
	unsigned int status;
	for (unsigned int i = 0; i < allInterfaceList.size(); ++i)
	{
		status = 0;
		allInterfaceList[i].checkAllHandlers(key, status);
		checkStatus(status, allInterfaceList[i]);
	}
	for (unsigned int i = 0; i < allChildrenList.size(); ++i)
	{
		status = 0;
		allChildrenList[i].checkAllHandlers(key, status);
		checkStatus(status, allChildrenList[i]);
	}


}

/*Adds child gui to a GuiBox, given the offset
Parameter: Parent gui, Offset to place child element, scale of new child, filename*/
void GuiManager::addChild(GuiBox &parent, const Position offset, const Position scale, const std::string path)
{
	Position p(parent.position.get_x() + offset.get_x(), parent.position.get_y() + offset.get_y());
	GuiBox child(buffer, p, scale, path, parent.childList.size(), false);
	allChildrenList.push_back(child);
	parent.childList.push_back(&allChildrenList[allChildrenList.size() - 1]);
	//cout << "child size: " << parent.childList.size() << endl;
}

//----------------------------PROTECTED----------------------------//

//----------------------------PRIVATE----------------------------//

/* Checks return status, based on the handler
Parameters: current status, guibox that caused the status change
*/
void GuiManager::checkStatus(const unsigned int status, const GuiBox guibox)
{
	//if status == 0, no status to check
	if (status == 0) return;
	switch (status)
	{
	case SetNewInterface:
		activeInterfaceId = guibox.gui_id;
		break;
	case InterfaceDeactivated:
		activeInterfaceId = NULL;
		break;
	default:
		cerr << "Invalid handler status was returned." << endl;
	}
}