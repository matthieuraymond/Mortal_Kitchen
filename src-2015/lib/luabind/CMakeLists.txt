CMAKE_MINIMUM_REQUIRED(VERSION 2.6)
PROJECT(luabind)

link_directories    ( 
  ${CMAKE_SOURCE_DIR}/lib/
  ${CMAKE_SOURCE_DIR}/lib/boost/
  )

include_directories ( 
  ${CMAKE_SOURCE_DIR}/lib/
  ${CMAKE_SOURCE_DIR}/lib/boost/
  ${CMAKE_SOURCE_DIR}/lib/luabind
  ${CMAKE_SOURCE_DIR}/lib/lua/src
  )

SET(LIBLUABIND_SOURCES 
src/class.cpp
src/class_info.cpp
src/class_registry.cpp
src/class_rep.cpp
src/create_class.cpp
src/error.cpp
src/exception_handler.cpp
src/function.cpp
src/inheritance.cpp
src/link_compatibility.cpp
src/object_rep.cpp
src/open.cpp
src/pcall.cpp
src/scope.cpp
src/stack_content_by_name.cpp
src/weak_ref.cpp
src/wrapper_base.cpp
)
		
ADD_DEFINITIONS(  )
	
ADD_LIBRARY(luabind STATIC ${LIBLUABIND_SOURCES})

SET_TARGET_PROPERTIES(luabind PROPERTIES DEBUG_POSTFIX "-d")

INSTALL(TARGETS luabind
  RUNTIME DESTINATION ${CMAKE_SOURCE_DIR}/bin/
  LIBRARY DESTINATION ${CMAKE_SOURCE_DIR}/lib/
  ARCHIVE DESTINATION ${CMAKE_SOURCE_DIR}/lib/
)

