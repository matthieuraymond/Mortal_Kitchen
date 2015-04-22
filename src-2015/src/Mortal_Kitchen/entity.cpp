// ------------------------------------------------------------------

#include "common.h"
#include "drawimage.h"
#include "script.h"
#include "entity.h"

// ------------------------------------------------------------------

// get access to keys table from main.cpp
extern bool g_Keys[256];

// ------------------------------------------------------------------

const int g_FrameDelay = 100; // ms between frames

Entity *g_Current = NULL;

map<string, DrawImage*> g_Animations;

// ------------------------------------------------------------------

DrawImage *loadAnimation(string filename)
{
  try {
    if (g_Animations.find(filename) == g_Animations.end()) {
      std::string path = executablePath();
      DrawImage *img = new DrawImage((path + "/data/sprites/" + filename).c_str(), v3b(255, 0, 255));
      g_Animations[filename] = img;
      return img;
    } else {
      return g_Animations[filename];
    }
  }
  catch (Fatal& f) { // error handling
    std::cerr << Console::red << f.message() << Console::gray << std::endl;
  }
}

// ------------------------------------------------------------------

void lua_addanim(string filename, int framespacing)
{
  SpriteAnim *s = new SpriteAnim;
  s->animframes = loadAnimation(filename);
  s->framespacing = framespacing;
  s->numframes = (int)ceil(s->animframes->w() / framespacing);
  g_Current->anims[filename] = s;
}

void lua_current(string filename)
{
	g_Current->currentAnim = filename;
}

string lua_get_current()
{
    return g_Current->currentAnim;
}

// ------------------------------------------------------------------

void lua_initanim(string filename, bool looping)
{
  if (g_Current->anims.find(filename) == g_Current->anims.end()) {
    cerr << Console::red << "cannot find anim '" << filename << "'" << Console::gray << endl;
    return;
  }
  g_Current->currentAnim = filename;
  g_Current->currentFrame = 0;
  g_Current->lastAnimUpdate = milliseconds();
  g_Current->animIsPlaying = true;
  g_Current->animIsALoop = looping;
}

void lua_stopanim()
{
	g_Current->animIsPlaying = false;
}

void lua_playanim()
{
	g_Current->animIsPlaying = true;
}

// ------------------------------------------------------------------

void lua_print(string str)
{
  cerr << Console::white << str << Console::gray << endl;
}

// ------------------------------------------------------------------

Entity *entity_create(string name,string script)
{
  Entity *e = new Entity;

  e->name = name;
  e->currentAnim = "";
  e->currentFrame = 0;
  e->lastAnimUpdate = 0;
  e->pos = v2f(0, 0);
  e->killed = false;
  e->animIsPlaying = false;

  e->script = script_create();
  // install our own functions into the script
  {
    module(e->script->lua)
      [
        def("addanim", &lua_addanim),
        def("initanim", &lua_initanim),
        def("print", &lua_print),
		def("playanim", &lua_playanim),
		def("stopanim", &lua_stopanim),
		def("current", &lua_current),
        def("get_current", &lua_get_current)
      ];
  }
  // load the script (global space gets executed)
  g_Current = e;
  script_load(e->script, executablePath() + "/data/scripts/" + script);
  g_Current = NULL;
  return e;
}

// ------------------------------------------------------------------

void    entity_draw(Entity *e)
{
  if (e->killed) {
    return;
  }
  if (e->anims.find(e->currentAnim) == e->anims.end()) {
    // error: the selected animation is unkown
    return;
  }
  // draw on screen
  int fspc = e->anims[e->currentAnim]->framespacing;
  v2i sz = v2i(fspc, e->anims[e->currentAnim]->animframes->h());
  int frame = min(e->currentFrame, e->anims[e->currentAnim]->numframes - 1);
  e->anims[e->currentAnim]->animframes->drawSub(
    v2i(e->pos), sz,
    v2i(frame * fspc, sz[1]), sz
    );
  // next frame
  if (e->animIsPlaying) {
	  time_t now = milliseconds();
	  if (now - e->lastAnimUpdate > g_FrameDelay) {
		  if (e->animIsALoop) {
			  e->currentFrame = (e->currentFrame + 1) % e->anims[e->currentAnim]->numframes;
			  e->lastAnimUpdate = now;
		  }
		  else {
			  if (e->currentFrame == e->anims[e->currentAnim]->numframes - 1) {
				  // call script event
				  try {
					  call_function<void>(e->script->lua, "onAnimeEnd");
				  }
				  catch (luabind::error& e) {
					  cerr << Console::red << e.what() << ' ' << Console::gray << endl;
				  }
				  //increment to number of frame
				  e->currentFrame++;
			  }
			  else if (e->currentFrame < e->anims[e->currentAnim]->numframes) {
				  e->currentFrame++;
			  }
		  }
	}
  }
}

// ------------------------------------------------------------------

void    entity_step(Entity *e,time_t elapsed)
{
  if (e->killed) {
    return;
  }
  g_Current = e;
  // setup global variables in script
  globals(e->script->lua)["elapsed"] = (int)elapsed;
  for (int i = 'a'; i <= 'z'; i++) {
    string name = "Key__";
    name[4] = (char)i;
    globals(e->script->lua)[name] = g_Keys[i];
  }
  globals(e->script->lua)["name"] = e->name;
  globals(e->script->lua)["pos_x"] = e->pos[0];
  globals(e->script->lua)["pos_y"] = e->pos[1];
  globals(e->script->lua)["killed"] = e->killed;
  // call stepping function from script
  try {
    call_function<void>(e->script->lua, "step");
  } catch (luabind::error& e) {
    cerr << Console::red << e.what() << ' ' << Console::gray << endl;
  }
  // feedback globals
  e->pos[0] = luabind::object_cast<float>(globals(e->script->lua)["pos_x"]);
  e->pos[1] = luabind::object_cast<float>(globals(e->script->lua)["pos_y"]);
  e->killed = luabind::object_cast<bool>(globals(e->script->lua)["killed"]);
  g_Current = NULL;
}

// ------------------------------------------------------------------

void    entity_contact(Entity *e, Entity *with)
{
  g_Current = e;
  globals(e->script->lua)["killed"] = e->killed;
  // call stepping function from script
  try {
    call_function<void>(e->script->lua, "contact",with->name);
  } catch (luabind::error& e) {
    cerr << Console::red << e.what() << ' ' << Console::gray << endl;
  }
  e->killed = luabind::object_cast<bool>(globals(e->script->lua)["killed"]);
  g_Current = NULL;
}

// ------------------------------------------------------------------

AAB<2>  entity_bbox(Entity *e)
{
  AAB<2> bx;
  bx.addPoint(v2f(e->pos));
  bx.addPoint(v2f(e->pos) + 
    v2f(e->anims[e->currentAnim]->framespacing, 
    e->anims[e->currentAnim]->animframes->h()));
  return bx;
}

// ------------------------------------------------------------------
