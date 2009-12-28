AM_CXXFLAGS = @COMPILER_OPTIONS@ @EXTRA_COMPILER_OPTIONS@

SUBDIRS = lua

INCLUDES += -I./../../../src/shared -I./../../../src/framework -I./../../../dep/include -I./ -I./lua/include -I./../../dep/include -I./lua/src -I./cpp-scripts -I./../../../src/mangosd -I./../../../src/game
pkglibdir = $(libdir)

lib_LTLIBRARIES = libMaNGOSScript.la

libMaNGOSScript_la_LIBADD=./lua/lib/liblua.a ./lua/lib/liblualib.a
libMaNGOSScript_la_LDFLAGS=-export-dynamic

libMaNGOSScript_la_SOURCES = \
CppScriptMgr.h \
LUA_Engine.h \
LUA_Player.h \
Lua_AI.h \
Lua_Creature.h \
Lua_Unit.h \
Lua_exports.h \
Lua_uint64.h \
ScriptMgr.h \
config.h \
lua_defines.h \
luainc.h \
sc_defines.h \
cpp-scripts/CppScripts.cpp \
CppScriptMgr.cpp \
LUA_Engine.cpp \
LUA_Player.cpp \
Lua_Creature.cpp \
Lua_Unit.cpp \
Lua_exports.cpp \
Lua_uint64.cpp \
ScriptMgr.cpp \
sc_defines.cpp \
system.cpp \
Lua_AI.cpp \
luabind/class.cpp \
luabind/class_info.cpp \
luabind/class_registry.cpp \
luabind/class_rep.cpp \
luabind/create_class.cpp \
luabind/error.cpp \
luabind/find_best_match.cpp \
luabind/function.cpp \
luabind/implicit_cast.cpp \
luabind/link_compatibility.cpp \
luabind/object_rep.cpp \
luabind/open.cpp \
luabind/overload_rep.cpp \
luabind/pcall.cpp \
luabind/ref.cpp \
luabind/scope.cpp \
luabind/stack_content_by_name.cpp \
luabind/weak_ref.cpp \
luabind/wrapper_base.cpp \
cpp-scripts/custom/sc_marshal_mcbride.cpp \
cpp-scripts/custom/sc_silas_darkmoon.cpp \
cpp-scripts/custom/sc_skorn_whitecloud.cpp \
cpp-scripts/guards/sc_guard_bluffwatcher.cpp \
cpp-scripts/guards/sc_guard_darnassus.cpp \
cpp-scripts/guards/sc_guard_dunmorogh.cpp \
cpp-scripts/guards/sc_guard_durotar.cpp \
cpp-scripts/guards/sc_guard_elwynnforest.cpp \
cpp-scripts/guards/sc_guard_ironforge.cpp \
cpp-scripts/guards/sc_guard_mulgore.cpp \
cpp-scripts/guards/sc_guard_orgrimmar.cpp \
cpp-scripts/guards/sc_guard_stormwind.cpp \
cpp-scripts/guards/sc_guard_teldrassil.cpp \
cpp-scripts/guards/sc_guard_tirisfal.cpp \
cpp-scripts/guards/sc_guard_undercity.cpp \
cpp-scripts/honor/alliance/sc_alliance_commander.cpp \
cpp-scripts/honor/alliance/sc_alliance_corporal.cpp \
cpp-scripts/honor/alliance/sc_alliance_field_marshal.cpp \
cpp-scripts/honor/alliance/sc_alliance_grand_marshal.cpp \
cpp-scripts/honor/alliance/sc_alliance_knight-captain.cpp \
cpp-scripts/honor/alliance/sc_alliance_knight-lieutenant.cpp \
cpp-scripts/honor/alliance/sc_alliance_knight.cpp \
cpp-scripts/honor/alliance/sc_alliance_knight_champion.cpp \
cpp-scripts/honor/alliance/sc_alliance_lieutenant_commander.cpp \
cpp-scripts/honor/alliance/sc_alliance_marshal.cpp \
cpp-scripts/honor/alliance/sc_alliance_master_sergeant.cpp \
cpp-scripts/honor/alliance/sc_alliance_private.cpp \
cpp-scripts/honor/alliance/sc_alliance_sergeant.cpp \
cpp-scripts/honor/alliance/sc_alliance_sergeant_major.cpp \
cpp-scripts/honor/horde/sc_horde_blood_guard.cpp \
cpp-scripts/honor/horde/sc_horde_centurion.cpp \
cpp-scripts/honor/horde/sc_horde_champion.cpp \
cpp-scripts/honor/horde/sc_horde_first_sergeant.cpp \
cpp-scripts/honor/horde/sc_horde_general.cpp \
cpp-scripts/honor/horde/sc_horde_grunt.cpp \
cpp-scripts/honor/horde/sc_horde_high_warlord.cpp \
cpp-scripts/honor/horde/sc_horde_legionaire.cpp \
cpp-scripts/honor/horde/sc_horde_lieutenant_general.cpp \
cpp-scripts/honor/horde/sc_horde_scout.cpp \
cpp-scripts/honor/horde/sc_horde_senior_sergeant.cpp \
cpp-scripts/honor/horde/sc_horde_sergeant.cpp \
cpp-scripts/honor/horde/sc_horde_stone_guard.cpp \
cpp-scripts/honor/horde/sc_horde_warlord.cpp \
cpp-scripts/serveus/sc_battlemaster.cpp \
cpp-scripts/serveus/sc_guildmaster.cpp \
cpp-scripts/serveus/sc_travelmaster.cpp 



