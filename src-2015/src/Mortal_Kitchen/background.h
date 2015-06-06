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
  time_t	tm_last_used;
  int i;
  int j;
} Screen;

typedef struct
{
  map<v2i, DrawImage*>    screens;

//  v2i                     viewpos;
  
  int                     screenw;
  int                     screenh;
} Background;

typedef struct
{
	map<v2i, DrawImage*>    screens;

	int                     screenw;
	int                     screenh;
	int                     max;
	int                     current;
	string                  folder;
	t_time                  last_switch;
	int                     speed;
} BackgroundSprite;

// ------------------------------------------------------------------

Background *background_init(int w, int h);
BackgroundSprite *backgroundSprite_init(int screenw, int screenh, int range, string folder, int speed);
void        background_draw(Background*, v2i viewpos);
void        backgroundSprite_draw(BackgroundSprite *bkg, v2i viewpos);
void        background_load(Background *bkg);
void        backgroundSprite_load(BackgroundSprite *bkg);

// ------------------------------------------------------------------
