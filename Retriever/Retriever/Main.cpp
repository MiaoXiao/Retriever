#include "stdafx.h"
#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_native_dialog.h>
#include "tinyxml2.h"
#include <Otter.h>

#include <iostream>
#include <string>
#include <vector>

#include "Globals.h"

using namespace std;
using namespace tinyxml2;

//FILE PATHS
#define FONTPATH "fonts/"

//GAME INFO
#define APPNAME "Retriever"
#define AUDIO_CHANNELS 5
#define FPS 60
ALLEGRO_DISPLAY *DISPLAY = NULL;

//current mouse position
int MPOS_X = -1;
int MPOS_Y = -1;

/*Init Allegro Audio. Exits if failure.*/
void initAudio()
{
	if (!al_install_audio()) {
		al_show_native_message_box(DISPLAY, "Error", "Error", "Failed to initialize audio!",
			NULL, ALLEGRO_MESSAGEBOX_ERROR);
		exit(1);
	}

	if (!al_init_acodec_addon()) {
		al_show_native_message_box(DISPLAY, "Error", "Error", "Failed to initialize audio codecs!",
			NULL, ALLEGRO_MESSAGEBOX_ERROR);
		exit(1);
	}

	if (!al_reserve_samples(AUDIO_CHANNELS)) {
		al_show_native_message_box(DISPLAY, "Error", "Error", "Failed to reserve samples!",
			NULL, ALLEGRO_MESSAGEBOX_ERROR);
		exit(1);
	}
}

/*Init Allegro Images. Exits if failure.*/
void initImages()
{
	if (!al_init_image_addon()) {
		al_show_native_message_box(DISPLAY, "Error", "Error", "Failed to initialize al_init_image_addon!",
			NULL, ALLEGRO_MESSAGEBOX_ERROR);
		exit(1);
	}
}

/*init Allegro Display. Exits if failure.*/
void initDisplay()
{
	//Init Display and window name
	al_set_app_name(APPNAME);
	DISPLAY = al_create_display(SCREENWIDTH, SCREENHEIGHT);
	if (!DISPLAY)
	{
		al_show_native_message_box(DISPLAY, "Error", "Error", "Failed to create display!",
			NULL, ALLEGRO_MESSAGEBOX_ERROR);
		exit(1);
	}
}

/*Init Allegro Fonts. Exits if failure
Parameters: List of font names
Returns: vector of allego fonts.*/
vector<ALLEGRO_FONT*> initFonts(vector<string> fontnames)
{
	vector<ALLEGRO_FONT*> f;
	//Init fonts
	al_init_font_addon();
	al_init_ttf_addon();

	for (unsigned int i = 0; i < fontnames.size(); ++i)
	{
		string fn = FONTPATH + fontnames[i] + ".ttf";
		ALLEGRO_FONT *font = al_load_font(fn.c_str(), 24, 0);
		if (!font)
		{
			al_show_native_message_box(DISPLAY, "Error", "Error", "Failed to load font!",
				NULL, ALLEGRO_MESSAGEBOX_ERROR);
			exit(1);
		}
		f.push_back(font);
	}
	return f;
}

//EXAMPLE CODE
//draw circle
//al_draw_filled_circle(w / 2, h / 2, 30, Color.yellow);
//draw images
//al_draw_bitmap(image, 200, 200, 0);
//draw fonts
//al_draw_text(font24, Color.yellow, 50, 50, 0, "Hi!!!!");

/*
ALLEGRO_BITMAP *star = al_load_bitmap("images/star.png");
if (!star)
{
al_show_native_message_box(DISPLAY, "Error", "Error", "Failed to load star!",
NULL, ALLEGRO_MESSAGEBOX_ERROR);
al_destroy_display(DISPLAY);
exit(1);
}*/

int main(int argc, char** argv)
{
	//Init Allegro
	if (!al_init())
	{
		al_show_native_message_box(DISPLAY, "Error", "Error", "Failed to initialize allegro!",
			NULL, ALLEGRO_MESSAGEBOX_ERROR);
		exit(1);
	}

	initAudio();
	initImages();
	initDisplay();

	//fonts in the game
	vector<string> fontnames;

	//install addons, keyboard and mouse
	al_init_primitives_addon();
	al_install_keyboard();
	al_install_mouse();

	//Event Queue
	ALLEGRO_TIMER *timer = al_create_timer(1.0 / FPS);
	ALLEGRO_EVENT_QUEUE *event_queue = NULL;
	event_queue = al_create_event_queue();
	al_register_event_source(event_queue, al_get_keyboard_event_source());
	al_register_event_source(event_queue, al_get_timer_event_source(timer));
	al_register_event_source(event_queue, al_get_mouse_event_source());

	//set to true of exiting game
	bool done = false;
	//set to true if drawing next frame
	bool draw = false;

	/*
	gSystem = new Otter::System(2 * 1024 * 1024);
	gRenderer = new D3DRenderer();
	gFileSys = new SampleFileSystem();
	gSystemHandler = new SampleSystemHandler();

	gSystem->SetRenderer(gRenderer);
	gSystem->SetFileSystem(gFileSys);
	gSystem->SetSystemHandler(gSystemHandler);
	*/

	//open test.xml
	XMLDocument doc;
	doc.LoadFile("test.xml");
	if (doc.ErrorID())
	{
		cout << "xml file not found" << endl;
		exit(1);
	}
	//loop through all book authors
	XMLElement *bookstore = doc.FirstChildElement();
	for (XMLElement* child = bookstore->FirstChildElement(); child != NULL; child = child->NextSiblingElement())
	{
		const char* author = child->FirstChildElement("author")->GetText();
		const char* gender = child->FirstChildElement("author")->Attribute("gender");
		// do something with each child element
		if (author && gender)
		{
			cout << author << endl;
			cout << gender << endl << endl;
		}
		else
		{
			cout << "author or/and gender could not be found" << endl;
		}
	}

	al_start_timer(timer);
	while (!done)
	{
		while (!al_is_event_queue_empty(event_queue))
		{
			ALLEGRO_EVENT events;
			al_wait_for_event(event_queue, &events);

			switch (events.type)
			{
			case ALLEGRO_EVENT_KEY_DOWN:
				switch (events.keyboard.keycode)
				{
				case ALLEGRO_KEY_ESCAPE:
					done = true;
					break;
				case ALLEGRO_KEY_ENTER:
					break;
				case ALLEGRO_KEY_R:
					break;
				}
				break;
			case ALLEGRO_EVENT_MOUSE_AXES:
				MPOS_X = events.mouse.x;
				MPOS_Y = events.mouse.y;
				break;
			case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
				break;
			case ALLEGRO_EVENT_TIMER:
				draw = true;
				break;
			}
		}

		//DRAW CALLS
		if (draw)
		{
			draw = false;
			al_flip_display();
			al_clear_to_color(al_map_rgb(255, 255, 255));
		}

	}

	al_destroy_event_queue(event_queue);
	al_destroy_display(DISPLAY);
	return 0;
}

