// Sylvain.Lefebvre@inria.fr  2015-03-24
#pragma once

// ------------------------------------------------------------------

#include<string>

using namespace std;

// ------------------------------------------------------------------

#include "drawimage.h"
#include "script.h"

// ------------------------------------------------------------------

typedef struct {
  DrawImage *animframes;
  int        framespacing;
  int        numframes;
} SpriteAnim;

// ------------------------------------------------------------------

typedef struct
{
  string                   name;
  map<string, SpriteAnim*> anims;

  string                   currentAnim;
  int                      currentFrame;
  time_t                   lastAnimUpdate;
  bool                     animIsPlaying;
  bool                     animIsALoop;

  v2f                      pos;
  bool                     killed;

  Script                  *script;
} Entity;

// ------------------------------------------------------------------

Entity *entity_create(string fname, string script);
void    entity_draw(Entity *e);
void    entity_step(Entity *e, time_t elapsed);
void    entity_contact(Entity *e,Entity *with);
AAB<2>  entity_bbox(Entity *e);

// ------------------------------------------------------------------
