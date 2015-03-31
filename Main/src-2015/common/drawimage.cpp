//  Sylvain.Lefebvre@inria.fr  2012-02-07
// ------------------------------------------------------------------

#include "drawimage.h"

#include "drawimage_sh.h"
AutoBindShader::drawimage_sh s_DrawImage;

static int  s_Width  = 1;
static int  s_Height = 1;
static bool s_Initialized = false;

// ------------------------------------------------------------------

// initialized shader, record screen size
void drawimage_init(int w,int h)
{
  s_DrawImage.init();
  s_Width       = w;
  s_Height      = h;
  s_Initialized = true;
}

// ------------------------------------------------------------------

// terminates the shader
void drawimage_terminate()
{
  s_DrawImage.terminate();
}

// ------------------------------------------------------------------

// loads an image from file
DrawImage::DrawImage(std::string filename)
{
  ImageRGBA_Ptr img;
  try {
    img = ImageRGBA_Ptr(loadImage<ImageRGB>(filename.c_str())->cast<ImageRGBA>());
    ForImage(img,i,j) { // fill up alpha with 255
      img->pixel(i,j)[3] = 255;
    }
  } catch (...) {
    img = ImageRGBA_Ptr(loadImage<ImageRGBA>(filename.c_str()));
  }
  m_Tex             = Tex2DRGBA_Ptr(new Tex2DRGBA(img->pixels()));
}

// ------------------------------------------------------------------

// loads an image from file
DrawImage::DrawImage(std::string filename,v3b transparent_color)
{
  ImageRGBA_Ptr img;
  try {
    img = ImageRGBA_Ptr(loadImage<ImageRGB>(filename.c_str())->cast<ImageRGBA>());
    ForImage(img, i, j) {
      if (v3b(img->pixel(i, j)) == transparent_color) {
        img->pixel(i, j)[3] = 0;
      } else {
        img->pixel(i, j)[3] = 255;
      }
    }
  } catch (...) {
    img = ImageRGBA_Ptr(loadImage<ImageRGBA>(filename.c_str()));
  }
  m_Tex = Tex2DRGBA_Ptr(new Tex2DRGBA(img->pixels()));
}

// ------------------------------------------------------------------

// draw the image on screen at pixel position x,y
void  DrawImage::draw(int x,int y)
{
  static Shapes::Square sq;
  glPushAttrib(GL_ENABLE_BIT);
  glDisable   (GL_CULL_FACE);
  glDisable   (GL_DEPTH_TEST);
  glEnable    (GL_ALPHA_TEST);
  glAlphaFunc (GL_GREATER,0);
  s_DrawImage.begin();
  m_Tex->bind();
  s_DrawImage.u_Image    .set(0);
  v2f dim = V2F((float)s_Width,(float)s_Height);
  s_DrawImage.u_Scale    .set( V2F((float)m_Tex->w(),(float)m_Tex->h()) / dim);
  s_DrawImage.u_Translate.set( V2F((float)x,(float)y) / dim );
  s_DrawImage.u_ImageSize.set( V2F((float)m_Tex->w(),(float)m_Tex->h()) );
  s_DrawImage.u_UVWH     .set( V4F(0,0,(float)m_Tex->w(),(float)m_Tex->h()) );
  sq.render();
  s_DrawImage.end(); 
  glPopAttrib();
}

// ------------------------------------------------------------------

void DrawImage::drawSub(v2i screen_pos,v2i screen_size,v2i table_pos,v2i table_size)
{
  static Shapes::Square sq;
  glPushAttrib(GL_ENABLE_BIT);
  glDisable   (GL_CULL_FACE);
  glDisable   (GL_DEPTH_TEST);
  glEnable    (GL_ALPHA_TEST);
  glAlphaFunc (GL_GREATER,0);
  s_DrawImage.begin();
  m_Tex->bind();
  s_DrawImage.u_Image    .set(0);
  v2f dim = V2F((float)s_Width,(float)s_Height);
  s_DrawImage.u_Scale    .set( V2F((float)screen_size[0],(float)screen_size[1]) / dim);
  s_DrawImage.u_Translate.set( V2F((float)screen_pos[0] ,(float)screen_pos[1]) / dim );
  s_DrawImage.u_ImageSize.set( V2F((float)m_Tex->w(),(float)m_Tex->h()) );
  s_DrawImage.u_UVWH.set(V4F((float)table_pos[0], (float)table_pos[1], (float)table_size[0], (float)table_size[1]));
  sq.render();
  s_DrawImage.end(); 
  glPopAttrib();
}

// ------------------------------------------------------------------
