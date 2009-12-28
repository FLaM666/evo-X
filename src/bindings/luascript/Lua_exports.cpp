#include "Lua_exports.h"
#include "WorldPacket.h"
#include "Player.h"
#include "Creature.h"
#include "GossipDef.h"
#include "QuestDef.h"
#include "Lua_uint64.h"
#include "Log.h"
#include "Mail.h"
#include "Lua_AI.h"
#include "CppScriptMgr.h"

#ifndef WIN32
#include "DynamicObject.h"
#include "Spell.h"
#include "SpellAuras.h"
#endif

#include "luainc.h"

extern uint32 GetSkillLevel(Player *player,uint32 skill);

//wrapper for the debug log
void log_debug_lua(const char* str)
	{
	debug_log("[LUA] %s ",str);
	}
//this is for errors
void log_error_lua(const char* str)
	{
	error_log("[LUA] %s ",str);
	}

void lb_WorldPacket_append_b(WorldPacket* pkt, bool val)
	{
	(*pkt) << val;
	}

void lb_WorldPacket_append_u8(WorldPacket* pkt, uint8 val)
	{
	(*pkt) << val;
	}

void lb_WorldPacket_append_u16(WorldPacket* pkt, uint16 val)
	{
	(*pkt) << val;
	}

void lb_WorldPacket_append_u32(WorldPacket* pkt, uint32 val)
	{
	(*pkt) << val;
	}

void lb_WorldPacket_append_u64(WorldPacket* pkt, lua_uint64& val)
	{
	(*pkt) << val.m_val;
	}

void lb_WorldPacket_append_f(WorldPacket* pkt, float val)
	{
	(*pkt) << val;
	}

void lb_WorldPacket_append_d(WorldPacket* pkt, double val)
	{
	(*pkt) << val;
	}

void lb_WorldPacket_append_str(WorldPacket* pkt, const char* val)
	{
	(*pkt) << val;
	}

bool lb_WorldPacket_read_b( WorldPacket* pkt )
	{
	bool val;
	(*pkt) >> val;
	return val;
	}

uint8 lb_WorldPacket_read_u8( WorldPacket* pkt )
	{
	uint8 val;
	(*pkt) >> val;
	return val;
	}

uint16 lb_WorldPacket_read_u16( WorldPacket* pkt )
	{
	uint16 val;
	(*pkt) >> val;
	return val;
	}

uint32 lb_WorldPacket_read_u32( WorldPacket* pkt )
	{
	uint32 val;
	(*pkt) >> val;
	return val;
	}

lua_uint64 lb_WorldPacket_read_u64( WorldPacket* pkt )
	{
	uint64 val;
	(*pkt) >> val;
	return lua_uint64(val);
	}

double lb_WorldPacket_read_d( WorldPacket* pkt )
	{
	double val;
	(*pkt) >> val;
	return val;
	}

float lb_WorldPacket_read_f( WorldPacket* pkt )
	{
	float val;
	(*pkt) >> val;
	return val;
	}

std::string lb_WorldPacket_read_stds( WorldPacket* pkt )
	{
	std::string val;
	(*pkt) >> val;
	return val;
	}

lua_uint64 lb_Object_GetGUID(Object* ob)
	{
    uint64 val;
	val = ob->GetGUID();
	return lua_uint64(val);
	}

lua_uint64 lb_Object_GetUInt64Value( Object* ob, uint16 index )
	{
    uint64 val;
	val = ob->GetUInt64Value(index);
	return lua_uint64(val);
	}

void lb_Object_SetUInt64Value( Object* ob ,uint16 index, lua_uint64& value )
	{
	ob->SetUInt64Value(index,value.m_val);
	}

int lb_rand_range(int min ,int max)
	{
	if( max == min ) return min;

	return min + ( rand()%(abs(max - min)) );
	}

bool isNULL(Object* ptr)
	{
	return ( ptr == NULL );
	}

bool isNULL(LuaAI_Proxy* ptr)
	{
	return ( ptr == NULL );
	}

 class Spell;
 class Aura;
 class DynamicObject;

int lb_Export_Misc(lua_State* L)
	{
	using namespace luabind;

module(L)
    [
		def("DisableCppScript", &cppDisableScript ),
		def("isNULL",( bool(*)(LuaAI_Proxy*) )&isNULL),
		def("isNULL",( bool(*)(Object*) )&isNULL),
        def("log_debug", &log_debug_lua),    //debug log
		def("log_error",   &log_error_lua),       //error log
		def("GetSkillLevel", &GetSkillLevel ),  //to get skill level
		def("rand_range", &lb_rand_range)    //random number between min and max
    ];

module(L)
[
    class_<WorldPacket>("WorldPacket")
	.def(constructor<>())
	.def(constructor<const WorldPacket&>())
	.def("Initialize", &WorldPacket::Initialize )
	.def("append_b", &lb_WorldPacket_append_b )
	.def("append_u8", &lb_WorldPacket_append_u8 )
	.def("append_u16", &lb_WorldPacket_append_u16 )
	.def("append_u32", &lb_WorldPacket_append_u32 )
	.def("append_u64", &lb_WorldPacket_append_u64 )
	.def("append_f", &lb_WorldPacket_append_f )
	.def("append_d", &lb_WorldPacket_append_d )
	.def("append_s", &lb_WorldPacket_append_str )
	.def("read_b", &lb_WorldPacket_read_b )
	.def("read_u8", &lb_WorldPacket_read_u8 )
	.def("read_u16", &lb_WorldPacket_read_u16 )
	.def("read_u32", &lb_WorldPacket_read_u32 )
	.def("read_u64", &lb_WorldPacket_read_u64 )
	.def("read_f", &lb_WorldPacket_read_f )
	.def("read_d", &lb_WorldPacket_read_d )
	.def("read_s", &lb_WorldPacket_read_stds )
];

module(L)
[
    class_<Object>("Object")
	.def("IsInWorld",           &Object::IsInWorld )
	.def("GetGUID",            &lb_Object_GetGUID )
	.def("GetGUIDLow",    &Object::GetGUIDLow )
	.def("GetGUIDHigh",   &Object::GetGUIDHigh )
	.def("GetEntry",             &Object::GetEntry )
	.def("GetPositionX",     &Object::GetPositionX )
	.def("GetPositionY",     &Object::GetPositionY )
	.def("GetPositionZ",     &Object::GetPositionZ )
	.def("GetOrientation", &Object::GetOrientation )
	.def("GetObjectSize",   &Object::GetObjectSize )
	.def("IsPositionValid", &Object::IsPositionValid )
	.def("SetMapId",            &Object::SetMapId )
	.def("GetMapId",           &Object::GetMapId )
	.def("GetZoneId",          &Object::GetZoneId )
	.def("GetAreaId",          &Object::GetAreaId )
	.def("GetUInt32Value", &Object::GetUInt32Value )
	.def("GetUInt64Value", &lb_Object_GetUInt64Value )
	.def("GetFloatValue",   &Object::GetFloatValue )
	.def("SetUInt32Value", &Object::SetUInt32Value )
	.def("SetUInt64Value", &lb_Object_SetUInt64Value )
	.def("SetFloatValue", &Object::SetFloatValue )
	.def("ApplyModUInt32Value",  &Object::ApplyModUInt32Value )
	/*.def("ApplyModUInt64Value",  &Object::ApplyModUInt64Value ) strangely why linker cant find this :?: i cant find it with find too :) */
	.def("ApplyModFloatValue",      &Object::ApplyModFloatValue )
	.def("ApplyPercentModFloatValue", &Object::ApplyPercentModFloatValue )
	.def("SetFlag",  &Object::SetFlag )
	.def("RemoveFlag", &Object::RemoveFlag )
	.def("HasFlag", &Object::HasFlag )
	.def("ApplyModFlag", &Object::ApplyModFlag )
	.def("ClearUpdateMask", &Object::ClearUpdateMask )
	.def("GetDistanceSq", ( float (Object::*)(const Object*) const )&Object::GetDistanceSq )
	.def("GetDistanceSq", ( float (Object::*)( const float, const float, const float) const )&Object::GetDistanceSq )
	.def("GetDistance2dSq", &Object::GetDistance2dSq )
	.def("GetDistanceZ", &Object::GetDistanceZ )
	.def("IsWithinDistInMap", &Object::IsWithinDistInMap )
	.def("IsWithinDist", &Object::IsWithinDist )
	.def("GetAngle", ( float (Object::*)(const Object*) const )                 &Object::GetAngle )
	.def("GetAngle", ( float (Object::*)( const float,const float) const )  &Object::GetAngle )
	.def("HasInArc", &Object::HasInArc )
	.def("SendMessageToSet", &Object::SendMessageToSet )
	.def("LoadValues", &Object::LoadValues )
	.def("InitValues", &Object::InitValues )
	.def("GetSpeed",         (  float (Object::*)() const)                              &Object::GetSpeed )
	.def("GetSpeed",         (  float (Object::*)(ObjMoveType) const)    &Object::GetSpeed )
	.def("SetSpeed",                  &Object::SetSpeed )
	.def("addQuest",                 &Object::addQuest )
	.def("addInvolvedQuest", &Object::addInvolvedQuest )
	.def("hasQuest",                  &Object::hasQuest )
	.def("hasInvolvedQuest", &Object::hasInvolvedQuest )
];

//TODO export more
module(L)
[
    class_<Aura>("Aura")
];

//TODO export more
module(L)
[
    class_<Spell>("Spell")
];

//TODO export more
module(L)
[
    class_<Quest>("Quest")
];

//TODO export more
module(L)
[
    class_<Mail>("Mail")
];

//TODO export more
module(L)
[
	class_<std::string>("std_string")
];

//TODO export more
module(L)
[
    class_<Item>("Item")
	.def("GetEntry", &Item::GetEntry )
	.def("GetCount", &Item::GetCount )
	.def("SetCount", &Item::SetCount )
	.def("GetSlot", &Item::GetSlot )
	.def("SetSlot", &Item::SetSlot )
];

//TODO export more
module(L)
[
    class_<DynamicObject>("DynamicObject")
];
return 0;
	}
