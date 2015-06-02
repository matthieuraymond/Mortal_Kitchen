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
DrawImage		*menu		   = NULL;
DrawImage		*gameOver	   = NULL;

// ------------------------------------------------------------------

// 'mainKeyPressed' is called everytime a key is pressed
void mainKeyPressed(uchar key)
{
  g_Keys[key] = true;

  if (key == ' ') {
    Entity *c = entity_create("coin0", "coin.lua");
    entity_set_pos(c, v2f(256 + ((rand() % 128) - 64), 350));
    g_Entities.push_back(c);
  }


  if (key == 'a'){
	  play_sound("ouille.wav");
	  g_Player->life -= 10;
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

	// Menu
	if (g_GameState == 0) {
		menu->draw(0, 0);
		if (g_Keys['p']) {
			g_GameState = 1;
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
		// phy_debug_draw();

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

    ///// Level creation

    // create background
    g_Bkg = background_init(c_ScreenW, c_ScreenH);

    // load a tilemap
    g_Tilemap = tilemap_load("level.lua");

    // init physics
    phy_init();

    // bind tilemap to physics
    tilemap_bind_to_physics(g_Tilemap);

    // load a simple entity
    {
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
	} {
		Entity *c = entity_create("player", "player.lua");
		entity_set_pos(c, v2f(c_ScreenW / 4, 128));
		c->alive = true;
		c->life = 100;
		g_Player = c;
		g_Entities.push_back(c);
	} {
		Entity *c = entity_create("enemy", "ennemy.lua");
		entity_set_pos(c, v2f(c_ScreenW, 128));
		g_Entities.push_back(c);
    }

    g_LastFrame = milliseconds();

    //init sound 
    init_sound();

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

