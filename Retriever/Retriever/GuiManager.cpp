#include "stdafx.h"
#include "GuiManager.h"

using namespace std;

/*CONSTRUCTOR:*/
GuiManager::GuiManager()
{
}

/*Create interface for permanent use.
Parameters: draw buffer, position of bitmap, scale of bitmap, path of bitmap, which menu to build*/
void GuiManager::createInterface(ALLEGRO_BITMAP* buffer,
	const Position position, const Position scale,
	const string path,
	const unsigned int menu)
{
	GuiInterface i(buffer, position, scale, path, interfaceList.size());
	
	//Menu 0: create a child menu 50% smaller in the center of the parent interface
	switch (menu)
	{
	case 0:
		//create child
		Position offset(20, 20);
		Position s;
		i.addChild(offset, s, path);
		break;
	}
	interfaceList.push_back(i);
}

/*Draw all non hidden interfaces and its non hidden children.*/
void GuiManager::drawInterfaces()
{
	for (unsigned int i = 0; i < interfaceList.size(); ++i)
	{
		if (interfaceList[i].active)
		{
			//cout << "drawing interface" << endl;
			interfaceList[i].drawGui();
			for (unsigned int j = 0; j < interfaceList[i].childList.size(); ++j)
			{
				if (interfaceList[i].childList[j].active)
				{
					//cout << "drawing child" << endl;
					interfaceList[i].childList[j].drawGui();
				}
			}
		}
	}
}