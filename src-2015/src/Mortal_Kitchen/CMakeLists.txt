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
  

SET(Mortal_Kitchen_GUID_CMAKE 294DC6F4-1323-4375-9431-A6A6A3C23155 CACHE INTERNAL "Project GUID")
  
TARGET_LINK_LIBRARIES(Mortal_Kitchen common ${LIBSL_LIBRARIES} ${LIBSL_GL_LIBRARIES} lua luabind Box2D OpenAL32 libsndfile-1)

set_target_properties(Mortal_Kitchen PROPERTIES DEBUG_POSTFIX "-d")
set_target_properties(Mortal_Kitchen PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/../..")
set_target_properties(Mortal_Kitchen PROPERTIES RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_CURRENT_SOURCE_DIR}/../..")
set_target_properties(Mortal_Kitchen PROPERTIES RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_CURRENT_SOURCE_DIR}/../..")


AUTO_BIND_SHADERS( ${SHADERS} )