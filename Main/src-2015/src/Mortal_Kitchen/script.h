// Sylvain.Lefebvre@inria.fr  2015-03-10
#pragma once

// ------------------------------------------------------------------

#include<string>

using namespace std;

// ------------------------------------------------------------------

// Lua and Luabind headers

extern "C" {
#include <lua.h>
#include <lualib.h>
}

#include <luabind/luabind.hpp>
#include <luabind/adopt_policy.hpp>
#include <luabind/out_value_policy.hpp>
#include <luabind/operator.hpp>
#include <luabind/exception_handler.hpp>
#include <luabind/object.hpp>

using namespace luabind;

// ------------------------------------------------------------------

typedef struct
{
  lua_State *lua;
} Script;

// ------------------------------------------------------------------

Script *script_create();
void    script_kill(Script *);
void    script_load(Script *,string fname);

// ------------------------------------------------------------------
