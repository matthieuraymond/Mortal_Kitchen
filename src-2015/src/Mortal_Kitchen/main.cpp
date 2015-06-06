// Sylvain.Lefebvre@inria.fr  2015-03-10
// ------------------------------------------------------------------

#include "common.h"
#include "drawimage.h"

LIBSL_WIN32_FIX;

// ------------------------------------------------------------------

#include "tilemap.h"
#include "entity.h"
#include "background.h"
#include "physics.h"
#include "sound.h"
#include "write.h"

// ------------------------------------------------------------------

// Constants
int    c_ScreenW      = 1280;
int    c_ScreenH      = 760;

// ------------------------------------------------------------------

time_t          g_LastFrame    = 0;

bool            g_Keys[256];

Tilemap        *g_Tilemap      = NULL;
Background     *g_Bkg          = NULL;

vector<Entity*> g_Entities;
Entity*         g_Player       = NULL;
v2i 			g_viewpos      = NULL;

int				g_GameState    = 0; // 0: menu, 1: playing, 2: game over
int				g_Menu		   = 0; // 0: main menu, 1: credits
int				selector	   = 0;
DrawImage		*selectBall    = NULL;
DrawImage		*menu		   = NULL;
DrawImage		*gameOver	   = NULL;
void init_game();

// ------------------------------------------------------------------

// 'mainKeyPressed' is called everytime a key is pressed
void mainKeyPressed(uchar key)
{
	g_Keys[key] = true;

	if (key == ' ') {
		/*Entity *c = entity_create("coin0", "coin.lua");
		entity_set_pos(c, v2f(256 + ((rand() % 128) - 64), 350));
		g_Entities.push_back(c);*/
	}

	/*if (key == 'a'){
		play_sound("ouille.wav");
		g_Player->life -= 10;
	}*/

	// Menu
	if (g_GameState == 0) {
		if (g_Menu == 0) {
			if (key == 'z') {
				selector += 1;
				selector = selector % 2;
			}
			else if (key == 's') {
				selector -= 1;
				selector = abs(selector % 2);
			}
			else if (key == ' ') {
				if (selector == 0) {
					clearScreen();
					drawTextCentered("loading", v2i(c_ScreenW / 2, c_ScreenH / 2));
					background_load(g_Bkg);
					g_GameState = 1;
				}
				else if (selector == 1) {
					g_Menu = 1;
				}
			}
		}
		else if (g_Menu == 1) {
			if (key == ' ') {
				g_Menu = 0;
			}
		}
	}
	if (g_GameState == 2) {
		if (key == ' ') {
			init_game();
			g_GameState = 0;
		}
	}
}
// ------------------------------------------------------------------

// 'mainKeyUnpressed' is called everytime a key is released
void mainKeyUnpressed(uchar key)
{
  g_Keys[key] = false;
}

// ------------------------------------------------------------------

// 'mainRender' is called everytime the screen is drawn
void mainRender()
{
	clearScreen();

	// Menu
	if (g_GameState == 0) {
		if (g_Menu == 0) {
			// Main menu
			drawTextCentered("play", v2i(c_ScreenW / 2, c_ScreenH / 2));
			drawTextCentered("credits", v2i(c_ScreenW / 2, c_ScreenH / 2 - 64));
			selectBall->draw(c_ScreenW / 2 - 150, c_ScreenH / 2 - 64 * selector);
		}
		else if (g_Menu == 1) {
			drawTextCentered("credits", v2i(c_ScreenW / 2, c_ScreenH / 2));
		}
	}
	// Playing
	else if (g_GameState == 1) {

		//// Compute elapsed time
		time_t now = milliseconds();
		time_t el = now - g_LastFrame;
		if (el > 25) {
			g_LastFrame = now;


			//// Physics
			phy_step();

			//// Logic

			// -> step all entities
			for (int a = 0; a < (int)g_Entities.size(); a++) {
				entity_step(g_Entities[a], el);
			}
			// -> update viewpos (x coord only in this 'game')
			g_viewpos[0] = (int)entity_get_pos(g_Player)[0] - c_ScreenW / 4;
		}
		//// Display

		clearScreen();

		// -> draw background
		background_draw(g_Bkg, g_viewpos);
		// -> draw tilemap
		tilemap_draw(g_Tilemap, g_viewpos);
		// -> draw all entities
		for (int a = 0; a < (int)g_Entities.size(); a++) {
			entity_draw(g_Entities[a], g_viewpos);
		}

		// -> draw physics debug layer
		//phy_debug_draw();

		if (g_Player->killed) {
			g_GameState = 2;
		}
	}
	// Game Over
	else if (g_GameState == 2) {
		gameOver->draw(0, 0);
	}
}

// ------------------------------------------------------------------
void init_game() {

	///// Level creation

	// create background
	g_Bkg = background_init(c_ScreenW, c_ScreenH);

	// load a tilemap
	g_Tilemap = tilemap_load("level.lua");

	// init physics
	phy_init();

	// bind tilemap to physics
	tilemap_bind_to_physics(g_Tilemap);
	g_Entities.clear();
	// load a simple entity
	/*{
		Entity *c = entity_create("coin0", "coin.lua");
		entity_set_pos(c, v2f(32, 32));
		g_Entities.push_back(c);
	} {
		Entity *c = entity_create("coin1", "coin.lua");
		entity_set_pos(c, v2f(96, 32));
		g_Entities.push_back(c);
	} {
		Entity *c = entity_create("coin2", "coin.lua");
		entity_set_pos(c, v2f(128, 32));
		g_Entities.push_back(c);
	}*/ {
		Entity *c = entity_create("player", "player.lua");
		entity_set_pos(c, v2f(c_ScreenW / 4, 256));
		c->alive = true;
		c->life = 150;
		g_Player = c;
		g_Entities.push_back(c);
	} {
		Entity *c = entity_create("enemy", "tomato.lua");
		entity_set_pos(c, v2f(c_ScreenW, 256));
		c->alive = true;
		c->life = 50;
		g_Entities.push_back(c);
	}
	{
		Entity *c = entity_create("enemy", "meatboy.lua");
		entity_set_pos(c, v2f(1.8*c_ScreenW, 256));
		c->alive = true;
		c->life = 100;
		g_Entities.push_back(c);
	}
	g_LastFrame = milliseconds();

	//init sound 
	init_sound();
}




// 'main' is the starting point of the application
int main(int argc,const char **argv)
{
  try { // error handling

    // opens a window
    SimpleUI::init(c_ScreenW,c_ScreenH,"Mortal Kitchen");
    // set the render function to be 'mainRender' defined above
    SimpleUI::onRender       = mainRender;
    // set the keyboard function
    SimpleUI::onKeyPressed   = mainKeyPressed;
    SimpleUI::onKeyUnpressed = mainKeyUnpressed;

    // init drawimage library
    drawimage_init( c_ScreenW,c_ScreenH );

    // keys
    for (int i = 0; i < 256; i++) {
      g_Keys[i] = false;
    }

	initText();

	string name = executablePath() + "/data/screens/menu.png";
	cerr << "attemtping to load " << name << endl;
	if (LibSL::System::File::exists(name.c_str())) {
		menu = new DrawImage(name.c_str());
	}
	name = executablePath() + "/data/screens/gameover.png";
	cerr << "attemtping to load " << name << endl;
	if (LibSL::System::File::exists(name.c_str())) {
		gameOver = new DrawImage(name.c_str());
	}
	name = executablePath() + "/data/select.png";
	cerr << "attemtping to load " << name << endl;
	if (LibSL::System::File::exists(name.c_str())) {
		selectBall = new DrawImage(name.c_str());
	}

	init_game();

    // enter the main loop
    SimpleUI::loop();
    
    // terminate physics
    phy_terminate();
    // terminate drawimage
    drawimage_terminate();

    // close the window
    SimpleUI::shutdown();

  } catch (Fatal& f) { // error handling
    std::cerr << Console::red << f.message() << Console::gray << std::endl;
  }

  return 0;
}

// ------------------------------------------------------------------

