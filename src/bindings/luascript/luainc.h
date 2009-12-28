/*
Lua include file for C++
*/

#ifndef __LUA_INC_H__
#define __LUA_INC_H__

extern "C"
{
  #include "lua/include/lua.h"
  #include "lua/include/lauxlib.h"
  #include "lua/include/lualib.h"
}

#include "lunar.h"
#include <luabind/luabind.hpp>
#include <luabind/function.hpp>
#include <luabind/class.hpp>
#include <luabind/operator.hpp>
#include <luabind/object.hpp>
#endif // __LUA_INC_H__
