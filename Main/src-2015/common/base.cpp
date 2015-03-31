// Sylvain.Lefebvre@inria.fr  2012-04-10
// ------------------------------------------------------------------

#include "base.h"

// ------------------------------------------------------------------

ImageRGBA *loadImageRGBA(const char *fname)
{
  ImageRGBA *img = NULL;

  try {
    img = loadImage<ImageRGBA>( fname );
  } catch (Fatal& ) {
    try {
      img = loadImage<ImageRGB>( fname )->cast<ImageRGBA>();
    } catch (Fatal& f) {
      std::cerr << Console::red << f.message() << Console::gray << std::endl;
      exit (-1);
    }
  }
  return img;

}

// ------------------------------------------------------------------

ImageRGBA *loadImageRGBA(std::string str)
{
  return loadImageRGBA(str.c_str());
}

// ------------------------------------------------------------------

m4x4f      rotationMatrix(float angle,const v3f& axis)
{
  return quatf(axis,angle).toMatrix();
}

// ------------------------------------------------------------------

std::string executablePath()
{
  return std::string(LibSL::System::Application::executablePath());
}

// ------------------------------------------------------------------

std::string sourcePath()
{
  return std::string(DATA_PATH);
}

// ------------------------------------------------------------------

VertexBuffer *makeBox()
{
  VertexBuffer *box = new VertexBuffer();

  box->begin(GPUMESH_TRIANGLELIST);

  box->color0_3(1,1,1);

  box->normal(0,-1,0);

  box->texcoord0_2(0,0);  box->vertex_3(0,0,0); //0
  box->texcoord0_2(1,1);  box->vertex_3(1,0,1); //2
  box->texcoord0_2(1,0);  box->vertex_3(1,0,0); //1

  box->texcoord0_2(0,0);  box->vertex_3(0,0,0); //0
  box->texcoord0_2(0,1);  box->vertex_3(0,0,1); //3
  box->texcoord0_2(1,1);  box->vertex_3(1,0,1); //2

  ////

  box->normal(0, 1,0);

  box->texcoord0_2(0,0);  box->vertex_3(0,1,0); //4
  box->texcoord0_2(1,0);  box->vertex_3(1,1,0); //5
  box->texcoord0_2(1,1);  box->vertex_3(1,1,1); //6

  box->texcoord0_2(0,0);  box->vertex_3(0,1,0); //4
  box->texcoord0_2(1,1);  box->vertex_3(1,1,1); //6
  box->texcoord0_2(0,1);  box->vertex_3(0,1,1); //7

  ////

  box->normal( 1,0,0);

  box->texcoord0_2(0,0);  box->vertex_3(1,0,0); //1
  box->texcoord0_2(0,1);  box->vertex_3(1,0,1); //2
  box->texcoord0_2(1,1);  box->vertex_3(1,1,1); //6

  box->texcoord0_2(0,0);  box->vertex_3(1,0,0); //1
  box->texcoord0_2(1,1);  box->vertex_3(1,1,1); //6
  box->texcoord0_2(1,0);  box->vertex_3(1,1,0); //5

  ////

  box->normal(-1,0,0);  
  
  box->texcoord0_2(0,0);  box->vertex_3(0,0,0); //0
  box->texcoord0_2(1,0);  box->vertex_3(0,1,0); //4
  box->texcoord0_2(0,1);  box->vertex_3(0,0,1); //3

  box->texcoord0_2(0,1);  box->vertex_3(0,0,1); //3
  box->texcoord0_2(1,0);  box->vertex_3(0,1,0); //4
  box->texcoord0_2(1,1);  box->vertex_3(0,1,1); //7

  ////

  box->normal(0,0,-1);

  box->texcoord0_2(0,0);  box->vertex_3(0,0,0); //0
  box->texcoord0_2(1,0);  box->vertex_3(1,0,0); //1
  box->texcoord0_2(1,1);  box->vertex_3(1,1,0); //5

  box->texcoord0_2(0,0);  box->vertex_3(0,0,0); //0
  box->texcoord0_2(1,1);  box->vertex_3(1,1,0); //5
  box->texcoord0_2(0,1);  box->vertex_3(0,1,0); //4

  ////

  box->normal(0,0, 1);

  box->texcoord0_2(0,0);  box->vertex_3(0,0,1); //3
  box->texcoord0_2(1,1);  box->vertex_3(1,1,1); //6
  box->texcoord0_2(1,0);  box->vertex_3(1,0,1); //2

  box->texcoord0_2(0,0);  box->vertex_3(0,0,1); //3
  box->texcoord0_2(0,1);  box->vertex_3(0,1,1); //7
  box->texcoord0_2(1,1);  box->vertex_3(1,1,1); //6

  box->end();

  return box;
}

// ------------------------------------------------------------------
