#pragma once
#include "GuiBox.h"

/*A generic menu, contains child guiboxes, buttons, and fonts.
Can install handlers which allow events to occur within interface*/
class GuiInterface: public GuiBox
{
public:
	/*CONSTRUCTOR:*/
	GuiInterface(ALLEGRO_BITMAP* buffer,
		const Position p, const Position s,
		const std::string path,
		const unsigned int id);

	/*Install an event handler for this interface, by adding to the handlerList
	Parameters: handler type, optional key that handler is responsible for,
	control set to true if handler can be enabled or disabled manually: false if enabled only during visible=true*/
	void installHandler(const unsigned int type, const unsigned int key, const bool control);

	/*Set an existing control handler to true or false
	Parameters: control handler type, control handler key, set the control handler to true/false*/
	void setControlHandle(const unsigned int type, const unsigned int key, const bool active);

	/*Installs gui with cursur. Fills transition grid with children ids
	Parameter: size of each row, whether cursor should horizontally, whether cursor should vertically*/
	void installCursor(unsigned int rowsize, bool wh, bool wv);

	/*Install transition to another interface
	Parameters: guiid to transition from, gui to transition to*/
	void installTransition(unsigned int child1, unsigned int child2);

	/*Check all handlers to see if event has occured.
	Parameters: key that was pressed this tick, status variable that may be returned
	Returns: return id if applicable, otherwise return -1*/
	int checkAllHandlers(const unsigned int key, unsigned int &status);


private:
	//cursor picture
	ALLEGRO_BITMAP* cursor;
	//grid for switching cursor
	std::vector< std::vector<unsigned int> > cursorGrid;
	//Position in grid where cursor is located
	Position cursorPos;
	//Whether cursor should wrap if it goes out of bounds
	bool wrapVertical;
	bool wrapHorizontal;

	//List of all handlers that are only enabled when gui is visible
	std::map<int, int> handlerList;

	//List of all control handlers that can be enabled/disabled at any time
	//value is set to true or false depending on whether it is active or not
	std::map<int, std::pair<bool, int> > controlHandlerList;

	/*Change which child now has the cursor.
	Parameters: index of child that currently has the cursor, key that was pressed*/
	void changeCursor(unsigned int index, unsigned int key);
};

