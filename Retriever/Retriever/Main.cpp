#include "stdafx.h"
#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_native_dialog.h>

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

#include "GuiManager.h"
#include "tinyxml2.h"
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

//Resoultions
unsigned int WINDOWWIDTH = 1300;
unsigned int WINDOWHEIGHT = 700;
unsigned int SCREENWIDTH = WINDOWWIDTH;
unsigned int SCREENHEIGHT = WINDOWHEIGHT;

//color
struct COLOR
{
	ALLEGRO_COLOR black = al_map_rgb(0, 0, 0);
	ALLEGRO_COLOR white = al_map_rgb(255, 255, 255);
};

//Current x mouse position
int MPOSX = -1;
//Current y mouse position
int MPOSY = -1;

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

/*Init Allegro Display. Exits if failure.*/
void initDisplay()
{
	//Init Display and window name
	al_set_app_name(APPNAME);
	DISPLAY = al_create_display(WINDOWWIDTH, WINDOWHEIGHT);
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

/*Load an image from disk
Parameters: name of path. name of file
Returns: pointer to bitmap*/
ALLEGRO_BITMAP* loadImage(string path, string filename)
{
	string fullpath = path + "/" + filename;
	ALLEGRO_BITMAP *bm = al_load_bitmap(fullpath.c_str());
	if (!bm)
	{
		cerr << "Could not load " << fullpath << endl;
		al_rest(20);
		exit(1);
	}
	return bm;
}

int main(int argc, char** argv)
{
	//Init Allegro
	if (!al_init())
	{
		al_show_native_message_box(DISPLAY, "Error", "Error", "Failed to initialize allegro!",
			NULL, ALLEGRO_MESSAGEBOX_ERROR);
		exit(1);
	}

	COLOR color;
	initAudio();
	initImages();
	initDisplay();

	//buffer for entire game
	ALLEGRO_BITMAP *buffer = al_create_bitmap(SCREENWIDTH, SCREENHEIGHT);
	
	//sample
	ALLEGRO_BITMAP* drawing = loadImage("Images", "picture.png");

	//SCREENWIDTH = al_get_display_width(DISPLAY);
	SCREENHEIGHT -= 100;

	// calculate scaling factor
	int sx = WINDOWWIDTH / SCREENWIDTH;
	int sy = WINDOWHEIGHT / SCREENHEIGHT;
	int scale = min(sx, sy);

	// calculate how much the buffer should be scaled
	int scaleW = SCREENWIDTH * scale;
	int scaleH = SCREENHEIGHT * scale;
	int scaleX = (WINDOWWIDTH - scaleW) / 2;
	int scaleY = (WINDOWHEIGHT - scaleH) / 2;

	//fonts in the game
	vector<string> fontnames;

	//install addons, keyboard and mouse
	al_init_primitives_addon();
	al_install_keyboard();
	al_install_mouse();

	//Event Queue
	ALLEGRO_TIMER *timer = al_create_timer(1.0 / FPS);
	ALLEGRO_EVENT_QUEUE *event_queue = al_create_event_queue();
	al_register_event_source(event_queue, al_get_keyboard_event_source());
	al_register_event_source(event_queue, al_get_timer_event_source(timer));
	al_register_event_source(event_queue, al_get_mouse_event_source());

	//set to true of exiting game
	bool done = false;
	//set to true if drawing next frame
	bool draw = false;	

	/*
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
	}*/

	GuiManager guimanager(buffer);

	float widthDifference = (WINDOWWIDTH - SCREENWIDTH) / 2;
	float heightDifference = (WINDOWHEIGHT - SCREENHEIGHT) / 2;
	//cout << "hd: " << heightDifference << endl;
	Position p((SCREENWIDTH / 12) + widthDifference, (SCREENHEIGHT / 12) + heightDifference);
	
	/*
	cout << "Screenw: " << SCREENWIDTH << endl;
	cout << "Screenh: " << SCREENHEIGHT << endl;
	cout << "Windoww: " << WINDOWWIDTH << endl;
	cout << "Windowh: " << WINDOWHEIGHT << endl;
	*/
	Position s(.75, .75);
	guimanager.createInterface(p, s, "Images/gui.jpg", 0);
	
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
				default:
					guimanager.handleGuiEvents(events.keyboard.keycode);
				}
				break;
			case ALLEGRO_EVENT_MOUSE_AXES:
				MPOSX = events.mouse.x;
				MPOSY = events.mouse.y;
				break;
			case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
				cout << MPOSX << " " << MPOSY << endl;
				break;
			case ALLEGRO_EVENT_TIMER:
				draw = true;
				break;
			}
		}

		//draw calls
		if (draw)
		{
			draw = false;

			// render a frame
			al_set_target_bitmap(buffer);
			al_clear_to_color(color.white);

			// Draw these Objects
			al_draw_bitmap(drawing, SCREENWIDTH / 2, SCREENHEIGHT / 2, 0);
			guimanager.drawInterfaces();

			//render back display
			al_set_target_backbuffer(DISPLAY);
			al_clear_to_color(color.black);

			al_draw_scaled_bitmap(buffer, 0, 0, SCREENWIDTH, SCREENHEIGHT, scaleX, scaleY, scaleW, scaleH, 0);

			al_flip_display();
		}

	}

	al_destroy_event_queue(event_queue);
	al_destroy_display(DISPLAY);
	return 0;
}

