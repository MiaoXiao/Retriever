#include "stdafx.h"
#include "GuiManager.h"

using namespace std;

//----------------------------PUBLIC----------------------------//

/*CONSTRUCTOR:*/
GuiManager::GuiManager(ALLEGRO_BITMAP* buffer)
	:buffer(buffer){}

/*Create Interface for permanent use.
Parameters: position of bitmap, scale of bitmap, path of bitmap, which menu to build*/
void GuiManager::createInterface(
	const Position p, const Position s,
	const string path,
	const unsigned int menu)
{
	GuiInterface interface(buffer, p, s, path, allInterfaceList.size());

	//Menu test
	switch (menu)
	{
	case 0:
	{
		//cout << "creating first child: " << endl;
		//create child
		Position offset(interface.dimen.get_x() / 8, interface.dimen.get_y() / 8);
		Position s(0.2, 0.25);
		interface.addChild(offset, s, path);

		//cout << "creating second child: " << endl;
		//create child
		Position offset2(interface.dimen.get_x() / 1.5, interface.dimen.get_y() / 8);
		Position s2(0.2, 0.25);
		interface.addChild(offset2, s2, path);

		//create child
		Position offset3(interface.dimen.get_x() / 8, interface.dimen.get_y() / 1.5);
		Position s3(0.2, 0.25);
		interface.addChild(offset3, s3, path);

		//create child
		Position offset4(interface.dimen.get_x() / 1.5, interface.dimen.get_y() / 1.5);
		Position s4(0.2, 0.25);
		interface.addChild(offset4, s4, path);

		//add activate handler
		interface.installHandler(Activate, ALLEGRO_KEY_I, true);

		//add cursor
		//interface.installCursor(2, false, false);
		break;
	}
	case 1:
	{
		//create child
		Position testoffset(interface.dimen.get_x() / 8, interface.dimen.get_y() / 8);
		Position tests(0.2, 0.25);
		interface.addChild(testoffset, tests, path);

		//cout << "creating second child: " << endl;
		//create child
		Position testoffset2(interface.dimen.get_x() / 1.5, interface.dimen.get_y() / 8);
		Position tests2(0.2, 0.25);
		interface.addChild(testoffset2, tests2, path);

		//add cursor
		interface.installCursor(2, false, false);
		interface.installHandler(Activate, ALLEGRO_KEY_Q, true);
		break;
	}
	}
	allInterfaceList.push_back(interface);
}

/*Draw all interfaces.*/
void GuiManager::drawInterfaces()
{
	for (unsigned int i = 0; i < allInterfaceList.size(); ++i)
	{
		if (allInterfaceList[i].getVisible())
		{
			//cout << "drawing interface" << endl;
			allInterfaceList[i].drawGui();
		}
	}
}

/*Handle all keyboard events for every interface
Parameter: Key that was pressed this tick*/
void GuiManager::handleGuiEvents(const unsigned int key)
{
	unsigned int status;
	int newid;
	for (unsigned int i = 0; i < allInterfaceList.size(); ++i)
	{
		//cout << "checking events for interface: " << allInterfaceList[i].gui_id << endl;
		status = 0;
		newid = allInterfaceList[i].checkAllHandlers(key, status);
		checkStatus(status, newid, allInterfaceList[i]);
	}
}

//----------------------------PROTECTED----------------------------//

//----------------------------PRIVATE----------------------------//

/* Checks return status, based on the handler
Parameters: current status, guibox that caused the status change*/
void GuiManager::checkStatus(const unsigned int status, const int newid, GuiInterface &gui)
{
	//if status == 0, no status to check
	if (status == 0) return;
	switch (status)
	{
	case SetNewInterface:
		activeInterface = &(allInterfaceList[gui.gui_id]);
		break;
	case InterfaceDeactivated:
		activeInterface = NULL;
		break;
	case InterfaceChange:
		if (newid == -1)
		{
			cerr << "No interface to switch to specified. Error!" << endl;
			return;
		}
		activeInterface = &(allInterfaceList[newid]);
		activeInterface->setVisible(true);
		break;
	default:
		cerr << "Invalid handler status was returned." << endl;
	}
}