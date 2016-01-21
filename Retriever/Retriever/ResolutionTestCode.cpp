// test.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "allegro5\allegro5.h"
#include "allegro5/allegro_image.h"
#include "allegro5/allegro_native_dialog.h"
#include <iostream>
#include <algorithm>
using namespace std;

int main()
{
	al_init();

	ALLEGRO_DISPLAY *display = nullptr;
	al_set_app_name("Hello World from Allegro 5.1!");
	//display = al_create_display(640, 480);

	if (!al_init_image_addon())
	{
		cout << "Couldn't init image addon" << endl;
		al_rest(5.0);
		return EXIT_FAILURE;
	}

	//int screenWidth = 800;
	//int screenHeight = 600;
	//int windowWidth = 640;
	//int windowHeight = 480;
	int screenWidth = 800; //desired resolution
	int screenHeight = 300;
	int windowWidth = 900;
	int windowHeight = 400;
	al_set_new_display_flags(ALLEGRO_WINDOWED + ALLEGRO_RESIZABLE);
	//al_set_new_display_flags(ALLEGRO_FULLSCREEN);
	//al_set_new_display_flags(ALLEGRO_FULLSCREEN_WINDOW);
	display = al_create_display(windowWidth, windowHeight);
	ALLEGRO_BITMAP* buffer = al_create_bitmap(screenWidth, screenHeight);
	ALLEGRO_BITMAP* drawing = al_load_bitmap("Images/pic.png");
	windowWidth = al_get_display_width(display);
	windowHeight = al_get_display_height(display);

	if (display == nullptr)
	{
		std::cerr << "Well, something is not working..." << std::endl;
		al_rest(5.0);
		return EXIT_FAILURE;
	}
	if (drawing == nullptr)
	{
		cout << "Drawing was not loaded" << endl;
		al_rest(5.0);
		return EXIT_FAILURE;
	}

	// calculate scaling factor
	int sx = windowWidth / screenWidth;
	int sy = windowHeight / screenHeight;
	int scale = min(sx, sy);

	// calculate how much the buffer should be scaled
	int scaleW = screenWidth * scale;
	int scaleH = screenHeight * scale;
	int scaleX = (windowWidth - scaleW) / 2;
	int scaleY = (windowHeight - scaleH) / 2;

	// render a frame
	al_set_target_bitmap(buffer);
	al_clear_to_color(al_map_rgb(255, 255, 255));
	// draw everything in between here
	al_draw_bitmap(drawing, screenWidth / 2, screenHeight / 2, 0);

	al_set_target_backbuffer(display);
	al_clear_to_color(al_map_rgb(0, 0, 0));
	al_draw_scaled_bitmap(buffer, 0, 0, screenWidth, screenHeight, scaleX, scaleY, scaleW, scaleH, 0);
	cout << "Screen W: " << screenWidth << endl;
	cout << "Scrren H: " << screenHeight << endl;
	cout << "Scale X: " << scaleX << endl;
	cout << "Scale Y: " << scaleY << endl;
	cout << "Scale W: " << scaleW << endl;
	cout << "Scale H: " << scaleH << endl;
	al_flip_display();
	al_rest(30);

	return 0;
}


