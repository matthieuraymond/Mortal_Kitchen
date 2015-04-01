// SL 2015-03-10

// ------------------------------------------------------------------

#include <LibSL/LibSL.h>

#include "script.h"

// ------------------------------------------------------------------

/*
try {
call_function<void>(L,"step");
} catch (luabind::error& e) {
cerr << e.what() << ' ' << endl;
exit(-1);
}
*/

// ------------------------------------------------------------------

void lua_log(string s)
{
  cerr << "[lua] " << s << endl;
}

// ------------------------------------------------------------------

Script *script_create()
{
  Script *s = new Script;

  // lua
  lua_State *L = lua_open();
  s->lua = L;

  luabind::open(L);

  lua_pushcfunction(L, luaopen_base);
  lua_pushliteral(L, "");
  lua_call(L, 1, 0);

  lua_pushcfunction(L, luaopen_math);
  lua_pushliteral(L, LUA_TABLIBNAME);
  lua_call(L, 1, 0);

  lua_pushcfunction(L, luaopen_table);
  lua_pushliteral(L, LUA_TABLIBNAME);
  lua_call(L, 1, 0);

  lua_pushcfunction(L, luaopen_package);
  lua_pushliteral(L, LUA_TABLIBNAME);
  lua_call(L, 1, 0);

  lua_pushcfunction(L, luaopen_string);
  lua_pushliteral(L, LUA_TABLIBNAME);
  lua_call(L, 1, 0);

  {
    module(L)
      [
        def("log", &lua_log)
      ];
  }

  return s;
}

// ------------------------------------------------------------------

void script_load(Script *s, string fname)
{
  int ret = 0;
  try {
    string program = loadFileIntoString(fname.c_str());
    ret            = luaL_dostring(s->lua, program.c_str());
  } catch (Fatal& f) {
    cerr << Console::yellow;
    cerr << f.message() << endl;
    cerr << Console::gray;
  }
  if (ret) {
    char str[4096];
    sprintf(str,"[[LUA]exit] %s", lua_tostring(s->lua, -1));
    cerr << Console::yellow;
    cerr << str;
    cerr << Console::gray;
  }
}

// ------------------------------------------------------------------

void script_kill(Script *s)
{
  lua_close(s->lua);
  s->lua = NULL;
}

// ------------------------------------------------------------------
