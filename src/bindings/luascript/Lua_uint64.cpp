#include "luainc.h"
#include "Lua_uint64.h"
#include "Log.h"

	lua_uint64::lua_uint64()
			{
			m_val = 0;
			}

	lua_uint64::lua_uint64(const lua_uint64& val)
			{
			this->m_val = val.m_val;
			}

	lua_uint64::lua_uint64(const uint64& val) //wont be exported
			{
			this->m_val = val;
			}

	lua_uint64::lua_uint64(const char* val)
			{
			this->m_val = atol(val);   //this isnt good _strtoui64 may be better
			}

	void lua_uint64::set(const char* val)
			{
			this->m_val = atol(val);   //this isnt good _strtoui64 may be better
			}

	void lua_uint64::set(lua_uint64& val)
			{
			this->m_val = val.m_val;
			}

	lua_uint64& lua_uint64::operator=(lua_uint64& val)
		   {
		   this->m_val = val.m_val;
		   return *this;
		   }

	lua_uint64 lua_uint64::operator+(lua_uint64& val)
		   {
		   lua_uint64 res(*this);
		   res.m_val += val.m_val;
		   return res;
		   }

	lua_uint64 lua_uint64::operator-(lua_uint64& val)
		   {
		   lua_uint64 res(*this);
		   res.m_val -= val.m_val;
		   return res;
		   }

   	lua_uint64 lua_uint64::operator*(lua_uint64& val)
		   {
		   lua_uint64 res(*this);
		   res.m_val *= val.m_val;
		   return res;
		   }

	lua_uint64 lua_uint64::operator/(lua_uint64& val)
		   {
		   lua_uint64 res(*this);
		   res.m_val /= val.m_val;
		   return res;
		   }

	 void lua_uint64::dump()
		   {
		   debug_log("[LUA] Dumping uint64 %e ", double(this->m_val)  );
		   }

int lb_Export_uint64(lua_State* L)
{
using namespace luabind;
		   module(L)
			[
		class_<lua_uint64>("uint64")
		.def(constructor<>())
		.def(constructor<const lua_uint64&>())
		.def(constructor<const char*>())
                       /*.def("dump", lua_uint64::dump ) TMP FIX for linux build*/
		.def("set", (void (lua_uint64::*)(const char*))&lua_uint64::set )
		.def("set", (void (lua_uint64::*)(lua_uint64& val))&lua_uint64::set )
		.def(self + lua_uint64())
		.def(self - lua_uint64())
		.def(self * lua_uint64())
		.def(self / lua_uint64())
		];
return 0;
}
