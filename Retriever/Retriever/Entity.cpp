#include "stdafx.h"
#include "Entity.h"

using namespace std;

//----------------------------PUBLIC----------------------------//
/*CONSTRUCTOR: */
Entity::Entity()
{
	
}

/*Load an image from disk
Parameters: name of path. name of file
Returns: pointer to bitmap*/
void Entity::loadImage(string path)
{
	bm = al_load_bitmap(path.c_str());
	if (!bm)
	{
		cerr << "Could not load " << path << endl;
		al_rest(20);
		exit(1);
	}
	
}

//----------------------------PROTECTED----------------------------//

//----------------------------PRIVATE----------------------------//