#include "stdafx.h"
#include "Entity.h"

using namespace std;

//----------------------------PUBLIC----------------------------//

/*CONSTRUCTOR: Set position and scale, load image*/
Entity::Entity(Position minp, Position s, const string path)
	:minPos(minp), scale(s)
{
	loadImage(path);
	maxPos.set(dimen.get_x() + minPos.get_x(), dimen.get_y() + minPos.get_y());
	/*
	p.display("Position");
	dimen.display("Dimensions");
	s.display("Scale");
	*/
}

/*DECONSTRUCTOR*/
Entity::~Entity()
{
	//al_destroy_bitmap(bmp);
}

//----------------------------PROTECTED----------------------------//

/*Load an image from disk. Also sets bitmap height and width
Parameters: name of path. name of file
Returns: pointer to bitmap*/
void Entity::loadImage(const string path)
{
	//cout << "Loading Image" << endl;
	ALLEGRO_BITMAP *loaded_bmp, *prev_target;

	//cout << "Load original bitmap" << endl;
	//load original bitmap
	loaded_bmp = al_load_bitmap(path.c_str());
	if (!loaded_bmp)
	{
		cerr << "Could not load " << path << ". Exiting. " << endl;
		al_rest(20);
		exit(1);
	}

	//cout << "Create resized bitmap" << endl;
	//create template for resized bitmap
	bmp = al_create_bitmap(al_get_bitmap_width(loaded_bmp) * scale.get_x(), al_get_bitmap_height(loaded_bmp) * scale.get_y());
	if (!bmp)
	{
		cerr << "Could not load empty bitmap. Exiting." << endl;
		al_rest(20);
		exit(1);
	}

	//temporarily set new target
	prev_target = al_get_target_bitmap();
	al_set_target_bitmap(bmp);

	//cout << "Copying over bitmap" << endl;
	//copy the loaded bitmap to the resized bmp
	al_draw_scaled_bitmap(loaded_bmp,
		0, 0,                                // source origin
		al_get_bitmap_width(loaded_bmp),     // source width
		al_get_bitmap_height(loaded_bmp),    // source height
		0, 0,                                // target origin
		al_get_bitmap_width(bmp),					//target width
		al_get_bitmap_height(bmp),					 //target height
		0                                    // flags
		);

	//restore target bitmap
	al_set_target_bitmap(prev_target);
	//al_destroy_bitmap(loaded_bmp);
	
	//set new scaled dimensions
	dimen.set(al_get_bitmap_width(bmp), al_get_bitmap_height(bmp));
	
	//cout << "End load image" << endl;
}

//----------------------------PRIVATE----------------------------//