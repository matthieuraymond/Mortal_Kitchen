// ------------------------------------------------------------------

#include "common.h"
#include "drawimage.h"
#include "script.h"
#include "tilemap.h"
#include "entity.h"

// ------------------------------------------------------------------

Tilemap         *g_Current = NULL;

// ------------------------------------------------------------------

void lua_tile(int color,string filename, int x, int y, int w, int h)
{
  try {
    // load image if needed
    if (g_Current->images.find(filename) == g_Current->images.end()) {
      // load!
      DrawImage *image = new DrawImage((executablePath() + "/data/tilemap/" + filename).c_str(),v3b(255,0,255));
      // insert
      g_Current->images[filename] = image;
    }
    // store tile definition
    Tile *tile = new Tile;
    tile->image = g_Current->images[filename];
    tile->x = x;
    tile->y = y;
    tile->w = w;
    tile->h = h;
    g_Current->tiles[v3b(color & 255, (color >> 8) & 255, color>>16)] = tile;
  } catch (Fatal& f) { // error handling
    std::cerr << Console::red << f.message() << Console::gray << std::endl;
  }
}

// ------------------------------------------------------------------

void lua_tilemap(string filename,int tw,int th)
{
  try {
  g_Current->tilemap = loadImageRGBA(executablePath() + "/data/tilemap/" + filename);
  g_Current->tilemap->flipH();
  g_Current->tilew = tw;
  g_Current->tileh = th;
  } catch (Fatal& f) { // error handling
    std::cerr << Console::red << f.message() << Console::gray << std::endl;
  }
}

// ------------------------------------------------------------------

int lua_color(int r, int g, int b)
{
  return (b << 16) + (g << 8) + r;
}

// ------------------------------------------------------------------

int lua_tileat(int i,int j)
{
  try {
    v3b pix = v3b(g_Current->tilemap->pixel<Clamp>(i, j));
    return lua_color(pix[0], pix[1], pix[2]);
  } catch (Fatal& f) { // error handling
    std::cerr << Console::red << f.message() << Console::gray << std::endl;
  }
  return 0;
}

// ------------------------------------------------------------------

void lua_set_tileat(int i, int j,int clr)
{
  try {
    g_Current->tilemap->pixel(i, j)[0] =  clr      & 255;
    g_Current->tilemap->pixel(i, j)[1] = (clr>> 8) & 255;
    g_Current->tilemap->pixel(i, j)[2] = (clr>>16) & 255;
  } catch (Fatal& f) { // error handling
    std::cerr << Console::red << f.message() << Console::gray << std::endl;
  }
}

// ------------------------------------------------------------------

int lua_num_tiles_x()
{
  return g_Current->tilemap->w();
}

// ------------------------------------------------------------------

int lua_num_tiles_y()
{
  return g_Current->tilemap->h();
}

// ------------------------------------------------------------------

Tilemap *tilemap_load(string fname)
{
  Tilemap *tilemap = new Tilemap;

  Script *script = script_create();
  
  // install our own functions into the script
  {
    module(script->lua)
      [
        def("tile", &lua_tile),
        def("tilemap", &lua_tilemap),
        def("color", &lua_color),
        def("tileat", &lua_tileat),
        def("set_tileat", &lua_set_tileat),
        def("num_tiles_x", &lua_num_tiles_x),
        def("num_tiles_y", &lua_num_tiles_y)
      ];
  }
  // load the script (global space gets executed)
  g_Current = tilemap;
  script_load(script, executablePath() + "/data/scripts/" + fname);
  g_Current = NULL;
  // kill the script (no longer needed)
  script_kill(script);
  delete (script);

  return tilemap;
}

// ------------------------------------------------------------------

void tilemap_draw(Tilemap *tmap)
{

  ForImage(tmap->tilemap,i,j) {
    v3b pix = v3b(tmap->tilemap->pixel(i, j));
    Tile *tile = tmap->tiles[pix];
    if (tile) {
      tile->image->drawSub(
        v2i(i*tmap->tilew, j*tmap->tileh), v2i(tile->w, tile->h),  // to
        v2i(tile->x, tile->y), v2i(tile->w, tile->h)); // from
    }
  }

}

// ------------------------------------------------------------------
