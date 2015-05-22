// ------------------------------------------------------------------

#include "common.h"
#include "drawimage.h"
#include "script.h"
#include "entity.h"

// The World (in physics.cpp)
extern b2World *g_World;

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
      DrawImage *img = new DrawImage((executablePath() + "/data/sprites/" + filename).c_str(), v3b(255, 0, 255));
      g_Animations[filename] = img;
      return img;
    } else {
      return g_Animations[filename];
    }
  }
  catch (Fatal& f) { // error handling
    std::cerr << Console::red << f.message() << Console::gray << std::endl;
  }
  return NULL;
}

// ------------------------------------------------------------------

void lua_addanim(string filename, int framespacing)
{
  sl_assert(g_Current != NULL);
  SpriteAnim *s = new SpriteAnim;
  s->animframes = loadAnimation(filename);
  s->framespacing = framespacing;
  s->numframes = (int)ceil(s->animframes->w() / framespacing);
  g_Current->anims[filename] = s;
}

// ------------------------------------------------------------------

void lua_playanim(string filename, bool looping)
{
  sl_assert(g_Current != NULL);
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

// ------------------------------------------------------------------

void lua_stopanim()
{
  sl_assert(g_Current != NULL);
  g_Current->animIsPlaying = false;
}

// ------------------------------------------------------------------

void lua_print(string str)
{
  cerr << Console::white << str << Console::gray << endl;
}

// ------------------------------------------------------------------

void lua_set_velocity_x(float v)
{
  sl_assert(g_Current != NULL);
  b2Vec2 vel = g_Current->body->GetLinearVelocity();
  g_Current->body->SetLinearVelocity(b2Vec2(v, vel.y));
}

// ------------------------------------------------------------------

void lua_set_velocity_y(float v)
{
  sl_assert(g_Current != NULL);
  b2Vec2 vel = g_Current->body->GetLinearVelocity();
  g_Current->body->SetLinearVelocity(b2Vec2(vel.x, v));
}

// ------------------------------------------------------------------

void lua_set_impulse(float v)
{
  g_Current->body->ApplyLinearImpulse(
  g_Current->body->GetMass() * b2Vec2(0,v),
  g_Current->body->GetLocalCenter());
}

// ------------------------------------------------------------------

void begin_script_call(Entity *e)
{
  g_Current = e;
  for (int i = 'a'; i <= 'z'; i++) {
    string name = "Key__";
    name[4] = (char)i;
    globals(e->script->lua)[name] = g_Keys[i];
  }
  globals(e->script->lua)["name"] = e->name;
  v2f pos = entity_get_pos(e);
  globals(e->script->lua)["pos_x"] = pos[0];
  globals(e->script->lua)["pos_y"] = pos[1];
  globals(e->script->lua)["killed"] = e->killed;
}

// ------------------------------------------------------------------

void end_script_call(Entity *e)
{
  // feedback globals
  //e->pos[0] = luabind::object_cast<float>(globals(e->script->lua)["pos_x"]);
  //e->pos[1] = luabind::object_cast<float>(globals(e->script->lua)["pos_y"]);
  e->killed = luabind::object_cast<bool>(globals(e->script->lua)["killed"]);
  g_Current = NULL;
}

// ------------------------------------------------------------------

Entity *entity_create(string name,string script)
{
  Entity *e = new Entity;

  e->name = name;
  e->currentAnim = "";
  e->currentFrame = 0;
  e->lastAnimUpdate = 0;
  e->killed = false;
  e->animIsPlaying = false;

  /// scripting
  e->script = script_create();
  // install our own functions into the script
  {
    module(e->script->lua)
      [
        def("addanim",  &lua_addanim),
        def("playanim", &lua_playanim),
        def("print",    &lua_print),
        def("stopanim", &lua_stopanim),
        def("set_velocity_x", &lua_set_velocity_x),
        def("set_velocity_y", &lua_set_velocity_y),
        def("set_impulse", &lua_set_impulse)
      ];
  }
  // load the script (global space gets executed)
  g_Current = e;
  script_load(e->script, executablePath() + "/data/scripts/" + script);
  g_Current = NULL;

  // read physics properties
  float ctrx = in_meters(luabind::object_cast<float>(globals(e->script->lua)["physics_center_x"]));
  float ctry = in_meters(luabind::object_cast<float>(globals(e->script->lua)["physics_center_y"]));
  float szx = in_meters(luabind::object_cast<float>(globals(e->script->lua)["physics_size_x"]));
  float szy = in_meters(luabind::object_cast<float>(globals(e->script->lua)["physics_size_y"]));
  bool  can_sleep  = luabind::object_cast<bool>(globals(e->script->lua)["physics_can_sleep"]);
  bool  can_rotate = luabind::object_cast<bool>(globals(e->script->lua)["physics_rotation"]);

  /// physics
  // define the dynamic body
  b2BodyDef bodyDef;
  bodyDef.type = b2_dynamicBody;
  bodyDef.position.Set(0.0f, 0.0f);
  e->body = g_World->CreateBody(&bodyDef);
  e->body->SetSleepingAllowed(can_sleep);
  e->body->SetFixedRotation(!can_rotate);
  // setup damping
  //e->body->SetLinearDamping(0.2f);
  //e->body->SetAngularDamping(0.2f);
  // define a box shape for our dynamic body.
  b2PolygonShape box;
  box.SetAsBox(szx,szy,b2Vec2(ctrx,ctry),0.0f);
  // define the dynamic body fixture.
  b2FixtureDef fixtureDef;
  fixtureDef.shape = &box;
  // set the box density to be non-zero, so it will be dynamic.
  fixtureDef.density = 2.0f;
  // override the default friction.
  fixtureDef.friction = 0.9f;
  // how bouncy?
  fixtureDef.restitution = 0.2f;
  // user data (pointer to entity being created)
  fixtureDef.userData = (void*)(e);
  // add the shape to the body.
  e->body->CreateFixture(&fixtureDef);
  return e;
}

// ------------------------------------------------------------------

v2f     entity_get_pos(Entity *e)
{
  b2Vec2 position = e->body->GetTransform().position;
  return v2f(in_px(position.x), in_px(position.y));
}

// ------------------------------------------------------------------

float   entity_get_angle(Entity *e)
{
  return e->body->GetTransform().R.GetAngle();
}

// ------------------------------------------------------------------

void    entity_set_pos(Entity *e, v2f p)
{
  e->body->SetTransform(b2Vec2(in_meters(p[0]),in_meters(p[1])),0.0f);
}

// ------------------------------------------------------------------

void    entity_draw(Entity *e, v2i viewpos)
{
  if (e->killed) {
    return;
  }
  if (e->anims.find(e->currentAnim) == e->anims.end()) {
    // error: the selected animation is unkown
    return;
  }
  // draw on screen
  int fspc  = e->anims[e->currentAnim]->framespacing;
  v2i sz    = v2i(fspc, e->anims[e->currentAnim]->animframes->h());
  int frame = min(e->currentFrame, e->anims[e->currentAnim]->numframes - 1);
  v2i pos   = (v2i)entity_get_pos(e) - viewpos;
  e->anims[e->currentAnim]->animframes->drawSub(
    v2i(pos) - sz/2 /*centered to match physics*/, sz,
    v2i(frame * fspc, 0), sz
    );
  // next frame
  if (e->animIsPlaying) {
    time_t now = milliseconds();
    if (now - e->lastAnimUpdate > g_FrameDelay) {
      if (e->animIsALoop) {
        e->currentFrame = (e->currentFrame + 1) % e->anims[e->currentAnim]->numframes;
      } else {
        if (e->currentFrame == e->anims[e->currentAnim]->numframes - 1) {
          // call script event 
          begin_script_call(e);
          try {
            call_function<void>(e->script->lua, "onAnimEnd");
          } catch (luabind::error& e) {
            cerr << Console::red << e.what() << ' ' << Console::gray << endl;
          }
          end_script_call(e);
          // increment to number of frame
          e->currentFrame++;
        } else if (e->currentFrame < e->anims[e->currentAnim]->numframes) {
          e->currentFrame ++;
        }
      }
      e->lastAnimUpdate = now;
    }
  }
}

// ------------------------------------------------------------------

void    entity_step(Entity *e,time_t elapsed)
{
  if (e->killed) {
    // does the body still exist?
    if (e->body != NULL) {
      // remove from simulation!
      g_World->DestroyBody(e->body);
      e->body = NULL;
    }
    return;
  }
  g_Current = e;
  // setup global variables in script
  globals(e->script->lua)["elapsed"] = (int)elapsed;
  // call stepping function from script
  begin_script_call(e);
  try {
    call_function<void>(e->script->lua, "step");
  } catch (luabind::error& e) {
    cerr << Console::red << e.what() << ' ' << Console::gray << endl;
  }
  end_script_call(e);
}

// ------------------------------------------------------------------

void    entity_contact(Entity *e, Entity *with)
{
  // call stepping function from script
  begin_script_call(e);
  try {
    call_function<void>(e->script->lua, "contact",with->name);
  } catch (luabind::error& e) {
    cerr << Console::red << e.what() << ' ' << Console::gray << endl;
  }
  end_script_call(e);
}

// ------------------------------------------------------------------

void    entity_onfloor(Entity *e)
{
  // call stepping function from script
  begin_script_call(e);
  try {
    call_function<void>(e->script->lua, "onFloor");
  }
  catch (luabind::error& e) {
    cerr << Console::red << e.what() << ' ' << Console::gray << endl;
  }
  end_script_call(e);
}

// ------------------------------------------------------------------

AAB<2>  entity_bbox(Entity *e)
{
  AAB<2> bx;
  v2f sz = v2f(e->anims[e->currentAnim]->framespacing, e->anims[e->currentAnim]->animframes->h());
  v2f pos = entity_get_pos(e);
  bx.addPoint(pos - sz/2.0f);
  bx.addPoint(pos + sz/2.0f);
  return bx;
}

// ------------------------------------------------------------------
