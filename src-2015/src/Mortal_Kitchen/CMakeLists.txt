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
  write.h
  write.cpp
  ../../data/scripts/coin.lua
  ../../data/scripts/player.lua
  ../../data/scripts/tomato.lua
  ../../data/scripts/punch.lua
  ../../data/scripts/meatboy.lua
  ../../data/scripts/meat.lua
  ../../data/scripts/level.lua
  ../../data/scripts/life.lua
  ../../data/scripts/salad.lua
  ../../data/scripts/sergio_punch.lua
  ../../data/scripts/punch.lua
  ../../data/scripts/maxipain.lua
  ../../data/scripts/blow.lua
)
  

SET(Mortal_Kitchen_GUID_CMAKE 133776D8-7193-48D5-A5A0-54FF06075653 CACHE INTERNAL "Project GUID")
  
TARGET_LINK_LIBRARIES(Mortal_Kitchen common ${LIBSL_LIBRARIES} ${LIBSL_GL_LIBRARIES} lua luabind Box2D OpenAL32 libsndfile-1)

set_target_properties(Mortal_Kitchen PROPERTIES DEBUG_POSTFIX "-d")
set_target_properties(Mortal_Kitchen PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/../..")
set_target_properties(Mortal_Kitchen PROPERTIES RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_CURRENT_SOURCE_DIR}/../..")
set_target_properties(Mortal_Kitchen PROPERTIES RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_CURRENT_SOURCE_DIR}/../..")


AUTO_BIND_SHADERS( ${SHADERS} )