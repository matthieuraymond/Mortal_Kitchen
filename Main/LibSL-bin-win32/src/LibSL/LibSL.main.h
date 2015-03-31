/* --------------------------------------------------------------------
Author: Sylvain Lefebvre    sylvain.lefebvre@inria.fr

                  Simple Library for Graphics (LibSL)

This software is a computer program whose purpose is to offer a set of
tools to simplify programming real-time computer graphics applications
under OpenGL and DirectX.

This software is governed by the CeCILL-C license under French law and
abiding by the rules of distribution of free software.  You can  use, 
modify and/ or redistribute the software under the terms of the CeCILL-C
license as circulated by CEA, CNRS and INRIA at the following URL
"http://www.cecill.info". 

As a counterpart to the access to the source code and  rights to copy,
modify and redistribute granted by the license, users are provided only
with a limited warranty  and the software's author,  the holder of the
economic rights,  and the successive licensors  have only  limited
liability. 

In this respect, the user's attention is drawn to the risks associated
with loading,  using,  modifying and/or developing or reproducing the
software by the user in light of its specific status of free software,
that may mean  that it is complicated to manipulate,  and  that  also
therefore means  that it is reserved for developers  and  experienced
professionals having in-depth computer knowledge. Users are therefore
encouraged to load and test the software's suitability as regards their
requirements in conditions enabling the security of their systems and/or 
data to be ensured and,  more generally, to use and operate it in the 
same conditions as regards security. 

The fact that you are presently reading this means that you have had
knowledge of the CeCILL-C license and that you accept its terms.
-------------------------------------------------------------------- */
// ------------------------------------------------------
// LibSL - main include file
// ------------------------------------------------------
//
// 
//
// ------------------------------------------------------
// Sylvain Lefebvre - 2006-03-09
// ------------------------------------------------------

#pragma once
#define LIBSL_CORE_INCLUDED

#pragma message("Including LibSL.main.h")

#include <LibSL/LibSL.config.h>

#ifdef WIN32
#include <windows.h>
#endif

#include <LibSL/Errors/Errors.h>
#include <LibSL/Memory/Pointer.h>

#include <LibSL/System/System.h>

#include <LibSL/CppHelpers/CppHelpers.h>
#include <LibSL/CppHelpers/BasicParser.h>
#include <LibSL/StlHelpers/StlHelpers.h>

#include <LibSL/TemplateHelpers/TemplateHelpers.h>

/// namespace declaration

#ifndef LIBSL_SAFE_NAMESPACE

using namespace LibSL;
using namespace LibSL::Errors;
using namespace LibSL::System::Types;
using namespace LibSL::System::Time;
using namespace LibSL::System::File;
// using namespace LibSL::System;     // DO NOT include System due to collisions with X11
using namespace LibSL::CppHelpers;
using namespace LibSL::StlHelpers;
using namespace LibSL::TemplateHelpers;

#endif

// ------------------------------------------------------
