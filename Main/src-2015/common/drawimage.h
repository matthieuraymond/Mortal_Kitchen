// SL 2012-02-07
#pragma once

// --------------------------------------------------------

#include <LibSL/LibSL.h>
#include <LibSL/LibSL_gl.h>

// --------------------------------------------------------

// a drawable image is a texture
class DrawImage
{
private:

  Tex2DRGBA_Ptr m_Tex;

public:

  // loads an image from file
  DrawImage(std::string filename);
  DrawImage(std::string filename,v3b transparent_color);

  // draw the image on screen at pixel position x,y
  void draw(int x,int y);

  // draw a subpart of the image on screen at pixel position x,y
  void drawSub(v2i screen_pos,v2i screen_size,v2i table_pos,v2i table_size);

  // return width/height
  uint w() const { return m_Tex->w(); }
  uint h() const { return m_Tex->h(); }

};

// --------------------------------------------------------

void drawimage_init(int w,int h);
void drawimage_terminate();

// --------------------------------------------------------
