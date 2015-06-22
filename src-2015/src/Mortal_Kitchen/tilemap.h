// Sylvain.Lefebvre@inria.fr  2015-03-10
#pragma once

// ------------------------------------------------------------------

#include<string>

using namespace std;

// ------------------------------------------------------------------

#include "drawimage.h"
#include "script.h"


// ------------------------------------------------------------------

typedef struct {
  DrawImage *image;
  int x;
  int y;
  int w;
  int h;
} Tile;

typedef struct
{
  Script                 *script;

  map<string, DrawImage*> images;
  map<v3b, Tile*>         tiles;

  ImageRGBA              *tilemap;
  int                     tilew;
  int                     tileh;
} Tilemap;

// ------------------------------------------------------------------

Tilemap *tilemap_load(string fname);
void     tilemap_draw(Tilemap *tmap, v2i viewpos);
void     tilemap_bind_to_physics(Tilemap *tmap);

// ------------------------------------------------------------------
