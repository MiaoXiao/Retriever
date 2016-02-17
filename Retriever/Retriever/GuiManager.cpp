#include "stdafx.h"
#include "GuiManager.h"

using namespace std;

//----------------------------PUBLIC----------------------------//

/*CONSTRUCTOR:*/
GuiManager::GuiManager(ALLEGRO_BITMAP* buffer)
	:buffer(buffer), activeInterfaceId(NULL)
{
}

/*Create Interface for permanent use.
Parameters: position of bitmap, scale of bitmap, path of bitmap, which menu to build*/
void GuiManager::createInterface(
	const Position p, const Position s,
	const string path,
	const unsigned int menu)
{
	cout << "Creating new interface" << endl;
	GuiBox interface(buffer, p, s, path, allInterfaceList.size(), true);

	//Menu test
	switch (menu)
	{
	case 0:
		//cout << "creating first child: " << endl;
		//create child
		Position offset(interface.dimensions.get_x() / 10, interface.dimensions.get_y() / 8);
		Position s(0.2, 0.25);
		addChild(interface, offset, s, path);

		//cout << "creating second child: " << endl;
		//create child
		Position offset2(interface.dimensions.get_x() / 2, interface.dimensions.get_y() / 8);
		Position s2(0.2, 0.25);
		addChild(interface, offset2, s2, path);

		//create child
		Position offset3(interface.dimensions.get_x() / 10, interface.dimensions.get_y() / 2);
		Position s3(0.2, 0.25);
		addChild(interface, offset3, s3, path);

		//create child
		Position offset4(interface.dimensions.get_x() / 2, interface.dimensions.get_y() / 2);
		Position s4(0.2, 0.25);
		addChild(interface, offset4, s4, path);

		//add activate handler
		interface.installHandler(Activate, ALLEGRO_KEY_I, true);
		
		//add cursor
		interface.installCursor(2);
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
				if (allInterfaceList[i].childList[j].getVisible())
				{
					allInterfaceList[i].childList[j].drawGui();
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
		for (unsigned int j = 0; j < allInterfaceList[i].childList.size(); ++j)
		{
			status = 0;
			allInterfaceList[i].childList[j].checkAllHandlers(key, status);
			checkStatus(status, allInterfaceList[i].childList[j]);
		}
	}
}

/*Adds child gui to a GuiBox, given the offset
Parameter: Parent gui, Offset to place child element, scale of new child, filename*/
void GuiManager::addChild(GuiBox &parent, const Position offset, const Position scale, const std::string path)
{
	Position p(parent.position.get_x() + offset.get_x(), parent.position.get_y() + offset.get_y());
	//cout << "position_x: " << parent.position.get_x() << " + " << offset.get_x() << endl;
	//cout << "position_y: " << parent.position.get_y() << " + " << offset.get_y() << endl;
	Position s(parent.scale.get_x() * scale.get_x(), parent.scale.get_y() * scale.get_y());
	//cout << "scale_x: " << parent.scale.get_x() << " * " << scale.get_x() << endl;
	//cout << "scale_y: " << parent.scale.get_y() << " * " << scale.get_y() << endl;

	GuiBox child(buffer, p, s, path, parent.childList.size(), false);
	parent.childList.push_back(child);

	child.parent = &parent;
	//sif (parent.childList[parent.childList.size() - 1]->getVisible()) cout << "dont " << endl;
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