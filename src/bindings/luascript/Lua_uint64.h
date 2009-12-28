#ifndef LUA_UINT64_H
#define LUA_UINT64_H

#include "luainc.h"
#include "Common.h"

//Adding uint64 support to lua :)
class lua_uint64
	{
	public:
	lua_uint64();
	lua_uint64(const lua_uint64& val);
	lua_uint64(const uint64& val) ;//wont be exported
	lua_uint64(const char* val);

	void set(const char* val);
	void set(lua_uint64& val);

    lua_uint64& operator= (lua_uint64& val);
	lua_uint64    operator+ (lua_uint64& val);
	lua_uint64    operator-  (lua_uint64& val);
   	lua_uint64    operator*  (lua_uint64& val);
	lua_uint64    operator/ (lua_uint64& val);

	 void dump();

		uint64 m_val;
	};

int lb_Export_uint64(lua_State* L);

#endif //LUA_UINT64_H
