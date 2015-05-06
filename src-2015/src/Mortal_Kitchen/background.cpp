// ------------------------------------------------------------------

#include "common.h"
#include "drawimage.h"
#include "script.h"
#include "background.h"

// ------------------------------------------------------------------

Background *background_init(int screenw,int screenh)
{
  Background *bkg = new Background;
  bkg->viewpos = v2i(screenw / 2, 0);
  bkg->screenw = screenw;
  bkg->screenh = screenh;
  return bkg;
}

// ------------------------------------------------------------------

void        background_draw(Background *bkg)
{
  // find the screen image locations required to draw
  v2i mincorner = v2i( 
    floor( 
      v2f(bkg->viewpos - v2i(bkg->screenw / 2, bkg->screenh / 2)) 
    / v2f(bkg->screenw, bkg->screenh) ) );
  v2i maxcorner = v2i(
    ceil(
      v2f(bkg->viewpos + v2i(bkg->screenw / 2, bkg->screenh / 2))
    / v2f(bkg->screenw, bkg->screenh)) );
  set<v2i> required;
  for (int j = mincorner[1]; j < maxcorner[1]; j++) {
    for (int i = mincorner[0]; i < maxcorner[0]; i++) {
      required.insert(v2i(i, j));
    }
  }
  // free screen images that are no longer required
  map<v2i, DrawImage*>::iterator S = bkg->screens.begin();
  while ( S != bkg->screens.end() ) {
    // is this screen image required?
    if (required.find(S->first) == required.end()) {
      // no! delete
      cerr << "unloading screen " << S->first << endl;
      delete (S->second);
      S = bkg->screens.erase(S);
    } else {
      // yes, next
      S++;
    }
  }
  // load if necessary
  for (set<v2i>::iterator R = required.begin(); R != required.end(); R++) {
    // already known?
    if (bkg->screens.find(*R) == bkg->screens.end()) {
      // no: load
      string name = sourcePath() + "/data/screens/" + to_string((*R)[0]) + "_" + to_string((*R)[1]) + ".jpg";
      // cerr << "attemtping to load " << name << endl;
      if (LibSL::System::File::exists(name.c_str())) {
        DrawImage *image = new DrawImage(name.c_str());
        bkg->screens[*R] = image;
      }
    }
  }
  // draw!
  for (int j = mincorner[1]; j < maxcorner[1]; j++) {
    for (int i = mincorner[0]; i < maxcorner[0]; i++) {
      // check if image is loaded
      map<v2i, DrawImage*>::iterator S = bkg->screens.find(v2i(i, j));
      if (S != bkg->screens.end()) {
        // yes, draw
        S->second->draw(i*bkg->screenw - bkg->viewpos[0] + bkg->screenw / 2, j*bkg->screenh + bkg->viewpos[1]);
      }
    }
  }
}

// ------------------------------------------------------------------
