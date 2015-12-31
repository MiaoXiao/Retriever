#pragma once

struct Position
{
	float x;
	float y;
};

class Entity
{
public:
	Entity() {};
	//set to true if object is collidable
	bool collidable;
	//top left corner
	Position posBegin;
	//bottom right corner
	Position posEnd;
};

