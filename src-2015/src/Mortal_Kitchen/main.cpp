// Sylvain.Lefebvre@inria.fr  2015-03-10
// ------------------------------------------------------------------

#include "common.h"
#include "drawimage.h"

LIBSL_WIN32_FIX;

// ------------------------------------------------------------------

#include "tilemap.h"
#include "entity.h"

// ------------------------------------------------------------------

// Constants
const int    c_ScreenW      = 1280;
const int    c_ScreenH      = 760;

// ------------------------------------------------------------------

time_t          g_LastFrame    = 0;

bool            g_Keys[256];

Tilemap        *g_Tilemap      = NULL;

vector<Entity*> g_Entities;

// ------------------------------------------------------------------

// 'mainKeyPressed' is called everytime a key is pressed
void mainKeyPressed(uchar key)
{
  g_Keys[key] = true;
}

// ------------------------------------------------------------------

// 'mainKeyUnpressed' is called everytime a key is released
void mainKeyUnpressed(uchar key)
{
  g_Keys[key] = false;
}

// ------------------------------------------------------------------

void physics(int now, int el) {
    if (el > 50) {
        g_LastFrame = now;
    }
    // -> check for contact between entities
    for (int a = 0; a < (int)g_Entities.size(); a++) {
        for (int b = a + 1; b < (int)g_Entities.size(); b++) {
            if (!g_Entities[a]->killed && !g_Entities[b]->killed) {
                if (entity_bbox(g_Entities[a]).intersect(entity_bbox(g_Entities[b]))) {
                    entity_contact(g_Entities[a], g_Entities[b]);
                    entity_contact(g_Entities[b], g_Entities[a]);
                }
            }
        }
    }
}

void logic(int now, int el) {
    // -> step all entities
    for (int a = 0; a < (int)g_Entities.size(); a++) {
        entity_step(g_Entities[a], el);
    }
}

void display() {

    ////UPDATE Map - WILL BE REMOVED IN RELEASE
    if (g_Keys[' ']) {
        g_Tilemap = tilemap_load("level.lua");
    }

    clearScreen();
    // -> draw background
    g_Tilemap->background->draw(0,0);
    // -> draw tilemap
    tilemap_draw(g_Tilemap);
    // -> draw all entities
    for (int a = 0; a < (int)g_Entities.size(); a++) {
        entity_draw(g_Entities[a]);
    }
}


// 'mainRender' is called everytime the screen is drawn
void mainRender()
{
  // -> compute elapsed time
  time_t now = milliseconds();
  time_t el = now - g_LastFrame;

  physics(now, el);

  logic(now, el);

  display();
}

// ------------------------------------------------------------------
void createCoin(int x, int y, string name) {
	Entity *c = entity_create(name, "coin.lua");
	c->pos = v2f(x, y);
	g_Entities.push_back(c);
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

    ///// Level creation

    // load a tilemap
	g_Tilemap = tilemap_load("level.lua");

	// load a simple entity
	createCoin(256, 128, "coin");
	createCoin(512, 128, "coin");

	Entity *player = entity_create("player", "player.lua");
	player->pos = v2f(16, 16);
	g_Entities.push_back(player);


	g_LastFrame = milliseconds();

    // enter the main loop
    SimpleUI::loop();

    drawimage_terminate();

    // close the window
    SimpleUI::shutdown();

  } catch (Fatal& f) { // error handling
    std::cerr << Console::red << f.message() << Console::gray << std::endl;
  }

  return 0;
}
// ------------------------------------------------------------------
