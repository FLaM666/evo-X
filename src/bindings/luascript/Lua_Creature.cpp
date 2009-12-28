#include "luainc.h"
#include "Lua_Creature.h"
#include "WorldPacket.h"
#include "Player.h"
#include "Creature.h"
#include "GossipDef.h"
#include "SpellAuras.h"
#include "DynamicObject.h"
#include "Lua_uint64.h"
#include "Lua_AI.h"


const char* lb_Creature_GetScriptName(Creature* _Creature)
	{
	return _Creature->GetCreatureInfo()->ScriptName;
	}

uint32 lb_Creature_QUEST_DIALOG_STATUS(Creature* cr,Player *pPlayer, uint32 defstatus)
	{
return cr->getDialogStatus(pPlayer, defstatus);
	}

void lb_Creature_MonsterSay(Creature* cr, char const *text, uint32 language, lua_uint64 targetGUID)
	{
	cr->MonsterSay(text,language,targetGUID.m_val);
	}

LuaAI_Proxy* lb_Creature_GetLuaAI(Creature* cr) 
	{
	debug_log("lb_Creature_GetLuaAI");
	if( isRegistered_LuaAI(cr) )
		return  ( (LuaAI*)&cr->AI() )->m_proxy ;
	error_log("[Lua] : AI : WARNING : Trying to get LuaAI of creature that dont have such");
	return NULL;
	}

int lb_Export_Creature(lua_State* L)
	{
using namespace luabind;

module(L)
[
    class_<Creature , Unit >("Creature")
	.def("GetLuaAI", &lb_Creature_GetLuaAI)
	.def("GetScriptName"                        ,&lb_Creature_GetScriptName)
	.def("QUEST_DIALOG_STATUS"  ,&lb_Creature_QUEST_DIALOG_STATUS)
	/*from Creature.h */
	.def("isPet",&Creature::isPet)
	.def("isTotem",&Creature::isTotem)
	.def("isCivilian",&Creature::isCivilian)
	.def("isCanSwimOrFly",&Creature::isCanSwimOrFly)
	.def("isCanWalkOrFly",&Creature::isCanWalkOrFly)
	.def("isCanTrainingOf",&Creature::isCanTrainingOf)
	.def("isCanTrainingAndResetTalentsOf",&Creature::isCanTrainingAndResetTalentsOf)
	.def("isElite",&Creature::isElite)
	.def("GetOwner",&Creature::GetOwner)
	.def("setMoveRandomFlag",&Creature::setMoveRandomFlag)
	.def("setMoveRunFlag",&Creature::setMoveRunFlag)
	.def("getMoveRandomFlag",&Creature::getMoveRandomFlag)
	.def("getMoveRunFlag",&Creature::getMoveRunFlag)
	.def("IsStopped",&Creature::IsStopped)
	.def("StopMoving",&Creature::StopMoving)
	.def("GetBlockValue",&Creature::GetBlockValue)
	.def("GetItemCount",(uint32 (Creature::*)(uint32) const)&Creature::GetItemCount)
	.def("GetItemCount",(uint8 (Creature::*)(void) const)&Creature::GetItemCount)
	.def("GetItemId",&Creature::GetItemId)
	.def("GetMaxItemCount",&Creature::GetMaxItemCount)
	.def("GetItemIncrTime",&Creature::GetItemIncrTime)
	.def("GetItemLastIncr",&Creature::GetItemLastIncr)
	.def("SetItemCount",&Creature::SetItemCount)
	.def("SetItemLastIncr",&Creature::SetItemLastIncr)
	.def("AddItem",&Creature::AddItem)
	.def("GetTrainerSpellsSize",&Creature::GetTrainerSpellsSize)
	.def("getDialogStatus",&Creature::getDialogStatus)
	.def("prepareGossipMenu",&Creature::prepareGossipMenu)
	.def("sendPreparedGossip",&Creature::sendPreparedGossip)
	.def("OnGossipSelect",&Creature::OnGossipSelect)
	.def("OnPoiSelect",&Creature::OnPoiSelect)
	.def("GetGossipTextId",&Creature::GetGossipTextId)
	.def("GetNpcTextId",&Creature::GetNpcTextId)
	.def("LoadGossipOptions",&Creature::LoadGossipOptions)
	.def("GetGossipTitle",&Creature::GetGossipTitle)
	.def("GetGossipCount",&Creature::GetGossipCount)
	.def("addGossipOption",&Creature::addGossipOption)
	.def("setEmoteState",&Creature::setEmoteState)
	.def("setDeathState",&Creature::setDeathState)
	.def("Say",&Creature::Say)
	.def("MonsterSay",&lb_Creature_MonsterSay)
	.def("getloyalty",&Creature::getloyalty)
	.def("getUsedTrainPoint",&Creature::getUsedTrainPoint)
	.def("GivePetLevel",&Creature::GivePetLevel)
	.def("GetDefaultMovementType",&Creature::GetDefaultMovementType)
	.def("SetDefaultMovementType",&Creature::SetDefaultMovementType)
];
return 0;
	}
