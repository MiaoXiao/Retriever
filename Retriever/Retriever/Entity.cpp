#include "stdafx.h"
#include "Entity.h"

using namespace std;

//----------------------------PUBLIC----------------------------//
/*CONSTURCTOR: default*/
Entity::Entity()
{	
	position.set(0, 0);
	scale.set(1, 1);
}

/*CONSTRUCTOR: Set position and scale, load image*/
Entity::Entity(Position position, Position scale, const string path)
	:position(position), scale(scale)
{
	loadImage(path);
}

//----------------------------PROTECTED----------------------------//

/*Load an image from disk. Also sets bitmap height and width
Parameters: name of path. name of file
Returns: pointer to bitmap*/
void Entity::loadImage(const string path)
{
	bm = al_load_bitmap(path.c_str());
	if (!bm)
	{
		cerr << "Could not load " << path << endl;
		al_rest(20);
		exit(1);
	}
	dimensions.set(al_get_bitmap_width(bm), al_get_bitmap_height(bm));
}

//----------------------------PRIVATE----------------------------//