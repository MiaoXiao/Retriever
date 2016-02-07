#include "stdafx.h"
#include "GuiManager.h"

using namespace std;

/*CONSTRUCTOR: */
GuiManager::GuiManager(ALLEGRO_BITMAP* buffer)
	:buffer(buffer)
{

}

/*Create interface for permanent use. Add interface to list given unique id
Parameters: position of bitmap, path of bitmap*/
void GuiManager::createInterface(const Position p, const string path)
{
	Interface i(buffer, p, path, interfaceList.size());
	interfaceList.push_back(i);
}