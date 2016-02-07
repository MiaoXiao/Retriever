#pragma once

#include <string>
#include "Globals.h"

#include <allegro5/allegro5.h>
#include <allegro5/allegro_image.h>

/*X and Y position of an entity screen*/
struct Position
{
public:
	/*CONSTRUCTOR: default*/
	Position() { x = 0; y = 0; }
	/*CONSTRUCTOR: automatically set position*/
	Position(const int x, const int y)
		:x(x), y(y) {}

	/*Set Entity position.
	Parameters: new x pos, new y pos*/
	void set(const int new_x, const int new_y) { x = new_x; y = new_y; }
private:
	int x;
	int y;
};

/*Anything displayed on screen with coordinates and potential to animate*/
class Entity
{
public:
	/*CONSTRUCTOR: */
	Entity();

	/*Load an image from disk
	Parameters: name of path. name of file
	Returns: pointer to bitmap*/
	void loadImage(std::string path);

	Position position;
private:
	//bitmap tied to this entity
	ALLEGRO_BITMAP* bm;
};

