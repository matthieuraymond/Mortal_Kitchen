
LibSL - v1.11 - README - 2012-11-29 - Sylvain Lefebvre

Compiling LibSL:
================

# Windows:
----------

- **IMPORTANT** Setup the environment variable LibSL_DIR to your LibSL root directory
- Make sure you have Visual C++ installed, or any other compiler supported by CMake
- [directx only] Install latest Microsoft DirectX SDK. Make sure the DirectX include and lib
  directories are in your VisualC++ paths ( $(DXSDK_DIR)\Include and $(DXSDK_DIR)\Lib\x86 ).
- [directx only] Compile DXUT in $(DXSDK_DIR)\Samples\C++\DXUT\Core\
- Download and install Perl from http://www.activestate.com/activeperl/
- Download and install Python 3
- Use CMake-gui to generate LibSL. Select desired builds
	- select DX only if the SDK is installed
	- GL4 will only work if you have GL4 compliant hardware and drivers
- Build the INSTALL project
- All libraries are now in %LibSL_DIR%\lib

# Linux:
--------

Use CMake. Do *not* use any left over Makefile in the LibSL source tree, these will be removed soon.

Make sure you do not have Mesa drivers (see header of /usr/include/GL/gl.h, there should be no mention
of Mesa there). On NVidia cards, install the nvidia-glx-XXX-dev package to get the headers (where XXX
is the driver version, for instance 180).

Type "make install" in the build tree. Libraries are copied into LibSL/lib/*

(LibSL was initally developped with g++ (GCC) 4.0.2, it is tested with gcc 4.3.3)

Using LibSL:
============

*** Setup the environment variable LibSL_DIR to your LibSL root directory ***

To create a new project using LibSL and for instance LibSL_gl, use the following CmakeLists.txt template:

	CMAKE_MINIMUM_REQUIRED(VERSION 2.6)
	PROJECT(myproject)

	FIND_PACKAGE(LibSL)

	SET(SOURCES
		main.cpp
	)

	SET(HEADERS
		main.h
	)

	INCLUDE_DIRECTORIES( ${LIBSL_INCLUDE_DIR} )

	ADD_EXECUTABLE(myexe ${SOURCES} ${HEADERS})
	TARGET_LINK_LIBRARIES(myexe ${LIBSL_LIBRARIES} ${LIBSL_GL_LIBRARIES})

Documentation:
================

None at the time, but several tutorial are available in LibSL/src/tutorials
Tutorials binaries are compiled into LibSL/bin and meant to be executed
from there.

There is a wiki at http://www.aracknea-core.com/wiki/pmwiki.php/LibSL/?n=LibSL.LibSL
Edition password is 'contains'.

Licence:
========

LibSL is distributed under the CeCILL-C licence (http://www.cecill.info).
See Licence_CeCILL-C_V1-en.txt for the complete licence text.


--
LibSL - (c) Sylvain Lefebvre 2006-2012
