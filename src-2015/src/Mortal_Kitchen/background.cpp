// ------------------------------------------------------------------

#include "common.h"
#include "drawimage.h"
#include "script.h"
#include "background.h"

// ------------------------------------------------------------------

Background *background_init(int screenw,int screenh)
{
  Background *bkg = new Background;
//  viewpos = v2i(screenw / 2, 0);
  bkg->screenw = screenw;
  bkg->screenh = screenh;
  return bkg;
}

BackgroundSprite *backgroundSprite_init(int screenw, int screenh, int range, string folder, int speed)
{
	BackgroundSprite *bkg = new BackgroundSprite;
	//  viewpos = v2i(screenw / 2, 0);
	bkg->screenw = screenw;
	bkg->screenh = screenh;
	bkg->max = range;
	bkg->current = 0;
	bkg->folder = folder;
	bkg->last_switch = milliseconds();
	bkg->speed = speed;
	return bkg;
}

// ------------------------------------------------------------------

void background_draw(Background *bkg, v2i viewpos)
{
  // find the screen image locations required to draw
  v2i mincorner = v2i( 
    floor( 
      v2f(viewpos) 
    / v2f(bkg->screenw, bkg->screenh) ) );
  v2i maxcorner = v2i(
    ceil(
      v2f(viewpos + v2i(bkg->screenw, bkg->screenh))
    / v2f(bkg->screenw, bkg->screenh)) );

  // draw!
  for (int j = mincorner[1]; j < maxcorner[1]; j++) {
    for (int i = mincorner[0]; i < maxcorner[0]; i++) {
      // check if image is loaded
      map<v2i, DrawImage*>::iterator S = bkg->screens.find(v2i(i, j));
      if (S != bkg->screens.end()) {
        // yes, draw
        S->second->draw(i*bkg->screenw - viewpos[0], j*bkg->screenh + viewpos[1]);
      }
    }
  }
}

// ------------------------------------------------------------------
void backgroundSprite_draw(BackgroundSprite *bkg, v2i viewpos)
{
	// find the screen image locations required to draw
	v2i mincorner = v2i(
		floor(
		v2f(viewpos)
		/ v2f(bkg->screenw, bkg->screenh)));
	v2i maxcorner = v2i(
		ceil(
		v2f(viewpos + v2i(bkg->screenw, bkg->screenh))
		/ v2f(bkg->screenw, bkg->screenh)));

	// draw!
	for (int j = mincorner[1]; j < maxcorner[1]; j++) {
		for (int i = mincorner[0]; i < maxcorner[0]; i++) {
			//search which sprite to draw
			t_time current = milliseconds();
			int k = bkg->current;
			if (current - bkg->last_switch > bkg->speed) {
				k = (k + 1) % bkg->max;
				bkg->current = k;
				bkg->last_switch = current;
			}
			// check if image is loaded
			map<v2i, DrawImage*>::iterator S = bkg->screens.find(v2i(i, k));
			if (S != bkg->screens.end()) {
				// yes, draw
				S->second->draw(i*bkg->screenw - viewpos[0], j*bkg->screenh + viewpos[1]);
			}
		}
	}
}

// ------------------------------------------------------------------

void background_load(Background *bkg) {
	set<v2i> required;
	for (int i = -1; i < 10; i++){
		required.insert(v2i(i, 0));
	}
	// load every screens
	for (set<v2i>::iterator R = required.begin(); R != required.end(); R++) {
		//for (int R = 0; R < 9; R++) {
		// already known?
		if (bkg->screens.find(*R) == bkg->screens.end()) {
			//no: load
			string name = executablePath() + "/data/screens/" + to_string((*R)[0]) + "_" + to_string((*R)[1]) + ".png";
			//cerr << "attemtping to load " << name << endl;
			if (LibSL::System::File::exists(name.c_str())) {
				DrawImage *image = new DrawImage(name.c_str());
				bkg->screens[*R] = image;
			}
		}
	}
}

void backgroundSprite_load(BackgroundSprite *bkg) {
	bkg->last_switch = milliseconds();
	set<v2i> required;
	for (int i = -1; i < 10; i++){
		for (int j = -1; j < bkg->max; j++){
			required.insert(v2i(i, j));
		}
	}
	// load every screens
	for (set<v2i>::iterator R = required.begin(); R != required.end(); R++) {
		//for (int R = 0; R < 9; R++) {
		// already known?
		if (bkg->screens.find(*R) == bkg->screens.end()) {
			//no: load
			string name = executablePath() + "/data/screens/" + bkg->folder + "/" + to_string((*R)[0]) + "_" + to_string((*R)[1]) + ".png";
			cerr << "attemtping to load " << name << endl;
			if (LibSL::System::File::exists(name.c_str())) {
				DrawImage *image = new DrawImage(name.c_str());
				bkg->screens[*R] = image;
			}
		}
	}
}
