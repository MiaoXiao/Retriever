#include "stdafx.h"
#include "Entity.h"

using namespace std;

//----------------------------PUBLIC----------------------------//

/*CONSTRUCTOR: Set position and scale, load image*/
Entity::Entity(Position p, Position s, const string path)
	:position(p), scale(s)
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