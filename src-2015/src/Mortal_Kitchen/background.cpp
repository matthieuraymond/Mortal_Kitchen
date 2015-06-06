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
