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

vector<BackgroundSprite*> g_BkgSprites;

vector<Entity*> g_Entities;
Entity*         g_Player       = NULL;
Entity*         g_Boss         = NULL;
v2i 			g_viewpos      = NULL;

enum        	g_State {menu, playing, cinematic, boss, over, winner };
enum            g_Loading {no, requested, yes};
bool            g_CinPlayed     = false;
g_State         g_GameState    = menu;
g_Loading       g_LoadState    = no;
enum			g_Menu { mainMenu, credits, levelSelect };
g_Menu			g_MenuState    = mainMenu;
int				selector	   = 0;
int             g_animStart    = 0;
int             g_Level        = 1;
DrawImage		*selectBall    = NULL;
DrawImage		*gameOver	   = NULL;
DrawImage       *menuBkg       = NULL;
DrawImage       *loadingBkg    = NULL;
DrawImage       *img_credits       = NULL;
DrawImage       *gameWinner        = NULL;
void init_game();
void menuKey(uchar key);

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
	if (g_GameState == menu) {
		menuKey(key);
	}
	if (g_GameState == over || g_GameState == winner) {
		if (key == ' ') {
			g_GameState = menu;
		}
	}
}
// ------------------------------------------------------------------

// 'mainKeyUnpressed' is called everytime a key is released
void mainKeyUnpressed(uchar key)
{
  g_Keys[key] = false;
}

void menuKey(uchar key) {
	if (g_MenuState == mainMenu) {
		if (key == 'z') {
			if (selector == 0) {
				selector = 2;
			}
			else {
				selector -= 1;
				selector = selector % 3;
			}
		}
		else if (key == 's') {
			selector += 1;
			selector = selector % 3;
		}
		else if (key == ' ') {
			if (selector == 0) {
				g_LoadState = requested;
			}
			else if (selector == 1) {
				g_MenuState = levelSelect;
				selector = 0;
			}
			else if (selector == 2) {
				g_MenuState = credits;
			}
		}
	}
	else if (g_MenuState == credits) {
		if (key == ' ') {
			g_MenuState = mainMenu;
		}
	}
	else if (g_MenuState == levelSelect) {
		if (key == 'z') {
			if (selector == 0) {
				selector = 2;
			}
			else {
				selector -= 1;
				selector = selector % 3;
			}
		}
		else if (key == 's') {
			selector += 1;
			selector = selector % 3;
		}
		else if (key == ' ') {
			if (selector == 0) {
				g_Level = 1;
				g_LoadState = requested;
			}
			else if (selector == 1) {
				g_Level = 2;
				g_LoadState = requested;
			}
			else if (selector == 2) {
				g_MenuState = mainMenu;
				selector = 0;
			}
		}
	}
}

// ------------------------------------------------------------------

void gameLoop() {
	//// Compute elapsed time
	time_t now = milliseconds();
	time_t el = now - g_LastFrame;
	if (el > 20) {
		g_LastFrame = now;

		//// Physics
		phy_step();

		//// Logic

		// -> step all entities
		for (int a = 0; a < (int)g_Entities.size(); a++) {
			entity_step(g_Entities[a], el);
		}
		// -> update viewpos (x coord only in this 'game')
		if (g_GameState == playing) {
			g_viewpos[0] = (int)entity_get_pos(g_Player)[0] - c_ScreenW / 4;
		}
	}
	//// Display

	clearScreen();

	// -> draw background
	background_draw(g_Bkg, g_viewpos);
	// -> draw background sprites
	for (int a = 0; a < (int)g_BkgSprites.size(); a++) {
		backgroundSprite_draw(g_BkgSprites[a], g_viewpos);
	}
	
	// -> draw tilemap
	tilemap_draw(g_Tilemap, g_viewpos);

	// -> draw all entities
	for (int a = 0; a < (int)g_Entities.size(); a++) {
		entity_draw(g_Entities[a], g_viewpos);
	}

	// -> draw life
	string life_str = "";
	for (int i = 0; i < (g_Player->life / 50); i++) {
		life_str = life_str.append("+");
	}
	drawText(life_str, v2i(25, c_ScreenH - 75));

	// -> draw physics debug layer
	//phy_debug_draw();

	if (g_GameState == playing) {
		if (entity_get_pos(g_Player)[0] > 6.5 * c_ScreenW && !(g_CinPlayed)) {
			g_animStart = milliseconds();
			g_Player->animIsPlaying = false;
			g_GameState = cinematic;
		}

		if (g_Player->killed) {
			play_sound("mort.wav");
			g_GameState = over;
		}

		if (g_Boss != NULL && g_Boss->killed) {
			play_sound("winner.wav");
			g_GameState = winner;
		}
	}

	//play sound
	if (g_GameState == playing) {
		play_sound("game.wav");
	}
	else if (g_GameState == boss) {
		play_sound("boss.wav");
	}
}

// ----------------------------------------------------------------------------------

void cinematicLoop() {

	//// Compute elapsed time
	time_t now = milliseconds();
	time_t el = now - g_LastFrame;
	if (el > 20) {
		g_viewpos[0] += 10;
		if (g_viewpos[0] >= 7 * c_ScreenW) {
			g_viewpos[0] = 7 * c_ScreenW;
		}

		g_LastFrame = now;

		//// Physics
		phy_step();

	}
	//// Display

	clearScreen();

	// -> draw background
	background_draw(g_Bkg, g_viewpos);
	// -> draw background sprites
	for (int a = 0; a < (int)g_BkgSprites.size(); a++) {
		backgroundSprite_draw(g_BkgSprites[a], g_viewpos);
	}
	
	// -> draw tilemap
	tilemap_draw(g_Tilemap, g_viewpos);

	// -> draw all entities
	for (int a = 0; a < (int)g_Entities.size(); a++) {
		entity_draw(g_Entities[a], g_viewpos);
	}

	// -> draw physics debug layer
	// phy_debug_draw();

	if (g_viewpos[0] >= 6.95 * c_ScreenW && g_viewpos[0] < 7 * c_ScreenW) {
		g_Player->animIsPlaying = true;
		entity_set_pos(g_Player, v2f(6.8 * c_ScreenW, 256));
		entity_set_pos(g_Boss, v2f(8.2 * c_ScreenW, 256));
		g_Player->body->SetLinearVelocity(b2Vec2(3, 6));
		g_Boss->body->SetLinearVelocity(b2Vec2(-5, 7));
	}

	if ((now - g_animStart) > 4000) {
		{
			Entity *c = entity_create("wall", "wall.lua");
			entity_set_pos(c, v2f(7 * c_ScreenW, 256));
			g_Entities.push_back(c);
		}
		{
		Entity *c = entity_create("wall", "wall.lua");
		entity_set_pos(c, v2f(8 * c_ScreenW, 256));
		g_Entities.push_back(c);
		}
		g_CinPlayed = true;
		g_GameState = boss;
	}

}

// ----------------------------------------------------------------------------------

void menuLoop() {

	//play sound
	play_sound("menu.wav");
	if (g_LoadState == yes) {
		init_game();
		background_load(g_Bkg);
		for (int a = 0; a < (int)g_BkgSprites.size(); a++) {
			backgroundSprite_load(g_BkgSprites[a]);
		}
		g_LoadState = no;
		g_GameState = playing;
	}
	else if (g_LoadState == requested) {
		loadingBkg->draw(0, 0);
		drawTextCentered("loading", v2i(c_ScreenW / 2, c_ScreenH - 100));
		g_LoadState = yes;
	}
	else {
		menuBkg->draw(0, 0);
		if (g_MenuState == mainMenu) {
			// Main menu
			drawTextCentered("new game", v2i(c_ScreenW / 2, c_ScreenH / 2));
			drawTextCentered("load game", v2i(c_ScreenW / 2, c_ScreenH / 2 - 64));
			drawTextCentered("credits", v2i(c_ScreenW / 2, c_ScreenH / 2 - 128));
			selectBall->draw(c_ScreenW / 2 - 170, c_ScreenH / 2 - 64 * selector);
		}
		else if (g_MenuState == credits) {
			img_credits->draw(c_ScreenW / 2 - 400, c_ScreenH / 2 - 250);

		}
		else if (g_MenuState == levelSelect) {
			// Select level
			drawTextCentered("level one", v2i(c_ScreenW / 2, c_ScreenH / 2));
			drawTextCentered("level two", v2i(c_ScreenW / 2, c_ScreenH / 2 - 64));
			drawTextCentered("back", v2i(c_ScreenW / 2, c_ScreenH / 2 - 128));
			selectBall->draw(c_ScreenW / 2 - 170, c_ScreenH / 2 - 64 * selector);
		}
	}
}

// -----------------------------------------------------------------------------------

// 'mainRender' is called everytime the screen is drawn
void mainRender()
{
	clearScreen();

	// Menu
	if (g_GameState == menu) {
		menuLoop();
	}
	// Playing
	else if (g_GameState == playing || g_GameState == boss) {
		gameLoop();
	}
	else if (g_GameState == cinematic) {
		cinematicLoop();
	}
	// Game Over
	else if (g_GameState == over) {
		gameOver->draw(0, 0);
	}
	// Winner
	else if (g_GameState == winner) {
		gameWinner->draw(0, 0);
	}
}

// ------------------------------------------------------------------
void init_game() {
	///// Level creation
	if (g_Level == 1) {
		g_BkgSprites.push_back(backgroundSprite_init(c_ScreenW, c_ScreenH, 3, "friteuse", 250));
		g_BkgSprites.push_back(backgroundSprite_init(c_ScreenW, c_ScreenH, 3, "cuiseur", 150));
	}

	string levelScript = "level" + to_string(g_Level) + ".lua";

	// init physics
	phy_init();
	
	// load a tilemap
	g_Tilemap = tilemap_load(levelScript);

	// bind tilemap to physics
	tilemap_bind_to_physics(g_Tilemap);
	g_Entities.clear(); // needed when restarting

	//add entities
	call_function<void>(g_Tilemap->script->lua, "init_entities");

	{ // Always keep sergio last so he's over
		Entity *c = entity_create("player", "player.lua");
		entity_set_pos(c, v2f(c_ScreenW / 4, 256)); //6*c_ScreenW
		c->alive = true;
		c->life = 250;
		g_Player = c;
		g_Entities.push_back(c);
	}
	g_LastFrame = milliseconds();
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
	init_sound();

	string name = executablePath() + "/data/screens/menu.png";
	cerr << "attemtping to load " << name << endl;
	if (LibSL::System::File::exists(name.c_str())) {
		menuBkg = new DrawImage(name.c_str());
	}
	name = executablePath() + "/data/screens/loading.png";
	cerr << "attemtping to load " << name << endl;
	if (LibSL::System::File::exists(name.c_str())) {
		loadingBkg = new DrawImage(name.c_str());
	}
	name = executablePath() + "/data/screens/gameover.png";
	cerr << "attemtping to load " << name << endl;
	if (LibSL::System::File::exists(name.c_str())) {
		gameOver = new DrawImage(name.c_str());
	}
	name = executablePath() + "/data/screens/winner.png";
	cerr << "attemtping to load " << name << endl;
	if (LibSL::System::File::exists(name.c_str())) {
		gameWinner = new DrawImage(name.c_str());
	}
	name = executablePath() + "/data/select.png";
	cerr << "attemtping to load " << name << endl;
	if (LibSL::System::File::exists(name.c_str())) {
		selectBall = new DrawImage(name.c_str());
	}
	name = executablePath() + "/data/screens/credits.png";
	cerr << "attemtping to load " << name << endl;
	if (LibSL::System::File::exists(name.c_str())) {
		img_credits = new DrawImage(name.c_str());
	}

	// create background
	g_Bkg = background_init(c_ScreenW, c_ScreenH);

	// init physics
	phy_init();

	g_LastFrame = milliseconds();

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

