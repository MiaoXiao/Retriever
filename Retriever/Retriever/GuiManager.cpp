#include "stdafx.h"
#include "GuiManager.h"

using namespace std;

/*CONSTRUCTOR:*/
GuiManager::GuiManager()
{
}

/*Create GuiBox for permanent use.
Parameters: position of bitmap, scale of bitmap, path of bitmap, which menu to build*/
void GuiManager::createGuiBox(ALLEGRO_BITMAP* buffer,
	const Position p, const Position s,
	const string path,
	const unsigned int menu)
{
	GuiBox interface(buffer, p, s, path, interfaceList.size(), true);

	//Menu 0: creat test menu, with child 50% smaller in center of parent
	switch (menu)
	{
	case 0:
		//create child
		Position offset(interface.dimensions.get_x() / 2, interface.dimensions.get_y() / 2);
		Position s(0.5, 0.5);
		addChild(interface, offset, s, path);
		break;
	}
	interfaceList.push_back(interface);
}

/*Draw all interfaces and its children.*/
void GuiManager::drawInterfaces()
{
	for (unsigned int i = 0; i < interfaceList.size(); ++i)
	{
		if (interfaceList[i].visible)
		{
			//cout << "drawing interface" << endl;
			interfaceList[i].drawGui();
			//cout << interfaceList[i].childList.size() << endl;
			for (unsigned int j = 0; j < interfaceList[i].childList.size(); ++j)
			{
				//cout << "checking child" << endl;
				if (interfaceList[i].childList[j]->visible)
				{
					//cout << "drawing child" << endl;
					interfaceList[i].childList[j]->drawGui();
				}
			}
		}
	}
}

/*Handle all keyboard events for any visible Gui elements
Parameter: Key that was pressed this tick*/
void GuiManager::allHandlers(unsigned int key)
{
}

/*Adds child gui to a GuiBox, given the offset
Parameter: Parent gui, Offset to place child element, scale of new child, filename*/
void GuiManager::addChild(GuiBox &parent, Position offset, Position scale, const std::string path)
{
	Position p(parent.position.get_x() + offset.get_x(), parent.position.get_y() + offset.get_y());
	GuiBox child(buffer, p, scale, path, parent.childList.size(), false);
	boxList.push_back(child);
	parent.childList.push_back(&boxList[boxList.size() - 1]);
	//cout << "child size: " << parent.childList.size() << endl;
}
