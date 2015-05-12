cmake_minimum_required(VERSION 2.6)
project(Mortal_Kitchen)

ADD_EXECUTABLE(Mortal_Kitchen
  main.cpp 
  script.cpp 
  script.h
  tilemap.cpp
  tilemap.h
  entity.cpp
  entity.h
  background.cpp
  background.h
  physics.cpp
  physics.h
  sound.cpp
  sound.h
  ../../data/scripts/coin.lua
  ../../data/scripts/player.lua
  ../../data/scripts/ennemy.lua
  ../../data/scripts/level.lua
)
  
TARGET_LINK_LIBRARIES(Mortal_Kitchen common ${LIBSL_LIBRARIES} ${LIBSL_GL_LIBRARIES} lua luabind Box2D)

AUTO_BIND_SHADERS( ${SHADERS} )
 