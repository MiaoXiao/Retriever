#pragma once

#include <string>
#include "Globals.h"

#include <allegro5/allegro5.h>
#include <allegro5/allegro_image.h>

/*X and Y position of an entity on screen*/
struct Position
{
public:
	/*CONSTRUCTOR: default*/
	Position() { x = 1; y = 1; }

	/*CONSTRUCTOR: automatically set position*/
	Position(const float x, const float y)
		:x(x), y(y) {}

	/*Set Entity position.
	Parameters: new x pos, new y pos*/
	void set(const float new_x, const float new_y) { x = new_x; y = new_y; }

	/*Get x or y coordinates*/
	float get_x() const { return x; }
	float get_y() const { return y; }

	/*Display current coordinates for this position
	Parameter: name of coordinates*/
	void display(std::string display)
	{
		std::cout << display << std::endl;
		std::cout << "position_x: " << x << std::endl;
		std::cout << "position_y: " << y << std::endl << std::endl;
	}
private:
	float x;
	float y;
};

/*Anything displayed on screen with coordinates and potential to animate*/
class Entity
{
public:
	/*CONSTRUCTOR: Set position and scale, load image*/
	Entity(Position minp, Position s, const std::string path);
	/*DECONSTRUCTOR*/
	~Entity();

	//Top left corner position of bmp
	Position minPos;
	//Bottom right corner position of bmp
	Position maxPos;
	//Dimensions of bmp
	Position dimen;
	//Scale of bmp
	Position scale;

protected:
	/*Load an image from disk. Also sets bitmap height and width
	Parameters: name of path. name of file
	Returns: pointer to bitmap*/
	void loadImage(const std::string path);

	//bitmap tied to this entity
	ALLEGRO_BITMAP* bmp;
private:

};

