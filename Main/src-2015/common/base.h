#pragma once

#include "base.h"

#include <LibSL/LibSL.h>
#include <LibSL/LibSL_gl.h>

typedef MeshFormat_dae::t_VertexFormat                            VertexFormat;
typedef MeshFormat_dae::t_VertexData                              VertexData;

typedef LibSL::GPUMesh::GPUMesh_VertexBuffer<VertexFormat>               VertexBuffer;
typedef LibSL::GPUMesh::GPUMesh_Indexed_VertexBuffer<VertexFormat, uint>  IndexedVertexBuffer;

ImageRGBA    *loadImageRGBA(const char *fname);
ImageRGBA    *loadImageRGBA(std::string str);
m4x4f         rotationMatrix(float angle,const v3f& axis);

std::string   executablePath();
std::string   sourcePath();

VertexBuffer *makeBox();
