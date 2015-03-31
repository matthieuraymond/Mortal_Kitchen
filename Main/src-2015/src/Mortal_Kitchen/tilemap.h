// Sylvain.Lefebvre@inria.fr  2015-03-10
#pragma once

// ------------------------------------------------------------------

#include<string>

using namespace std;

// ------------------------------------------------------------------

#include "drawimage.h"

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
  map<string, DrawImage*> images;
  map<v3b, Tile*>         tiles;

  ImageRGBA              *tilemap;
  int                     tilew;
  int                     tileh;
} Tilemap;

// ------------------------------------------------------------------

Tilemap *tilemap_load(string fname);
void     tilemap_draw(Tilemap*);

// ------------------------------------------------------------------
