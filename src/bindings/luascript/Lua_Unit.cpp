//by Derex
#include "luainc.h"
#include "Lua_Unit.h"
#include "WorldPacket.h"
#include "Player.h"
#include "Unit.h"
#include "Creature.h"
#include "GossipDef.h"
#include "Lua_uint64.h"
#include "Log.h"
#include "luainc.h"

class DynamicObject;
class GameObject;
class Aura;
class Spell;


void lb_Unit_AddHostil(Unit* u, lua_uint64 guid, float hostility)
{
  u->AddHostil(guid.m_val,hostility);
}

float lb_Unit_GetHostility(Unit*u , lua_uint64 guid)
{
  return u->GetHostility(guid.m_val);
}

float lb_Unit_GetHostilityDistance(Unit*u , lua_uint64 guid)
{
  return u->GetHostilityDistance(guid.m_val);
}

void lb_Unit_LookAt(Unit*u ,Unit* target)
	{
	if(! u->HasInArc( 0.1f,target) )
		{
		    u->SetInFront(target);
            if( target->GetTypeId() == TYPEID_PLAYER )
                u->SendUpdateToPlayer( (Player*)target );
		}

	}


int lb_Export_Unit(lua_State* L)
{
  using namespace luabind;
  class_<Unit , Object >   lua_unit("Unit");

  lua_unit.def("setAttackTimer", &Unit::setAttackTimer )
  /*Some custom helper funcs */
  .def("LookAt", &lb_Unit_LookAt )
  .def("resetAttackTimer", &Unit::resetAttackTimer )
  .def("getAttackTimer", &Unit::getAttackTimer )
  .def("isAttackReady", &Unit::isAttackReady )
  .def("haveOffhandWeapon", &Unit::haveOffhandWeapon )
  .def("canReachWithAttack", &Unit::canReachWithAttack )
  .def("_addAttacker", &Unit::_addAttacker )
  .def("_removeAttacker", &Unit::_removeAttacker )
  .def("getAttackerForHelper", &Unit::getAttackerForHelper )
  .def("Attack", &Unit::Attack )
  .def("AttackStop", &Unit::AttackStop )
  .def("RemoveAllAttackers", &Unit::RemoveAllAttackers )
  .def("isInCombatWithPlayer", &Unit::isInCombatWithPlayer )
  .def("getVictim", &Unit::getVictim )
  .def("CombatStop", &Unit::CombatStop )
  .def("addUnitState", &Unit::addUnitState )
  .def("hasUnitState", &Unit::hasUnitState )
  .def("clearUnitState", &Unit::clearUnitState )
  .def("getLevel", &Unit::getLevel )
  .def("SetLevel", &Unit::SetLevel )
  .def("getRace", &Unit::getRace )
  .def("getRaceMask", &Unit::getRaceMask )
  .def("getClass", &Unit::getClass )
  .def("getClassMask", &Unit::getClassMask )
  .def("getGender", &Unit::getGender )
  .def("GetStat", &Unit::GetStat )
  .def("SetStat", &Unit::SetStat )
  .def("ApplyStatMod", &Unit::ApplyStatMod )
  .def("ApplyStatPercentMod", &Unit::ApplyStatPercentMod )
  .def("GetArmor", &Unit::GetArmor )
  .def("SetArmor", &Unit::SetArmor )
  .def("ApplyArmorMod", &Unit::ApplyArmorMod )
  .def("ApplyArmorPercentMod", &Unit::ApplyArmorPercentMod )
  .def("GetResistance", &Unit::GetResistance )
  .def("SetResistance", &Unit::SetResistance )
  .def("ApplyResistanceMod", &Unit::ApplyResistanceMod )
  .def("ApplyResistancePercentMod", &Unit::ApplyResistancePercentMod )
  .def("GetHealth", &Unit::GetHealth )
  .def("GetMaxHealth", &Unit::GetMaxHealth )
  .def("SetHealth", &Unit::SetHealth )
  .def("SetMaxHealth", &Unit::SetMaxHealth )
  .def("ModifyHealth", &Unit::ModifyHealth )
  .def("ApplyMaxHealthMod", &Unit::ApplyMaxHealthMod )
  .def("ApplyMaxHealthPercentMod", &Unit::ApplyMaxHealthPercentMod )
  .def("getPowerType", &Unit::getPowerType )
  .def("setPowerType", &Unit::setPowerType )
  .def("GetPower", &Unit::GetPower )
  .def("GetMaxPower", &Unit::GetMaxPower )
  .def("SetPower", &Unit::SetPower )
  .def("SetMaxPower", &Unit::SetMaxPower )
  .def("ModifyPower", &Unit::ModifyPower )
  .def("ApplyPowerMod", &Unit::ApplyPowerMod )
  .def("ApplyPowerPercentMod", &Unit::ApplyPowerPercentMod )
  .def("ApplyMaxPowerMod", &Unit::ApplyMaxPowerMod )
  .def("ApplyMaxPowerPercentMod", &Unit::ApplyMaxPowerPercentMod )
  .def("SetAttackTime", &Unit::SetAttackTime )
  .def("ApplyAttackTimePercentMod", &Unit::ApplyAttackTimePercentMod )
  .def("getFaction", &Unit::getFaction )
  .def("setFaction", &Unit::setFaction )
  /*.def("getFactionTemplateEntry", &Unit::getFactionTemplateEntry )/**/
  .def("IsHostileTo", &Unit::IsHostileTo )
  .def("IsHostileToAll", &Unit::IsHostileToAll )
  .def("IsFriendlyTo", &Unit::IsFriendlyTo )
  .def("IsNeutralToAll", &Unit::IsNeutralToAll )
  .def("getStandState", &Unit::getStandState )
  .def("IsMounted", &Unit::IsMounted )
  .def("GetMountID", &Unit::GetMountID )
  .def("Mount", &Unit::Mount )
  .def("Unmount", &Unit::Unmount )
  .def("DealDamage", &Unit::DealDamage )
  /*.def("DoAttackDamage", &Unit::DoAttackDamage ) cant be exported .. too many arguments probably need some struct probably*/
  .def("CalDamageReduction", &Unit::CalDamageReduction )
  .def("ProcDamageAndSpell", &Unit::ProcDamageAndSpell )
  .def("HandleEmoteCommand", &Unit::HandleEmoteCommand )
  .def("AttackerStateUpdate", &Unit::AttackerStateUpdate )
  /*.def("SpellMissChanceCalc", &Unit::SpellMissChanceCalc )*/
  .def("MeleeMissChanceCalc", &Unit::MeleeMissChanceCalc )
  .def("GetUnitDodgeChance", &Unit::GetUnitDodgeChance )
  .def("GetUnitParryChance", &Unit::GetUnitParryChance )
  .def("GetUnitBlockChance", &Unit::GetUnitBlockChance )
  .def("GetUnitCriticalChance", &Unit::GetUnitCriticalChance )
  .def("GetUnitMeleeSkill", &Unit::GetUnitMeleeSkill );


  lua_unit.def("GetDefenceSkillValue", &Unit::GetDefenceSkillValue )
  .def("GetPureDefenceSkillValue", &Unit::GetPureDefenceSkillValue )
  .def("GetWeaponSkillValue", &Unit::GetWeaponSkillValue )
  .def("GetPureWeaponSkillValue", &Unit::GetPureWeaponSkillValue )
  .def("GetWeaponProcChance", &Unit::GetWeaponProcChance )
  .def("RollMeleeOutcomeAgainst", &Unit::RollMeleeOutcomeAgainst )
  .def("isVendor", &Unit::isVendor )
  .def("isTrainer", &Unit::isTrainer )
  .def("isQuestGiver", &Unit::isQuestGiver )
  .def("isGossip", &Unit::isGossip )
  .def("isTaxi", &Unit::isTaxi )
  .def("isGuildMaster", &Unit::isGuildMaster )
  .def("isBattleMaster", &Unit::isBattleMaster )
  .def("isBanker", &Unit::isBanker )
  .def("isInnkeeper", &Unit::isInnkeeper )
  .def("isSpiritHealer", &Unit::isSpiritHealer )
  .def("isTabardVendor", &Unit::isTabardVendor )
  .def("isAuctioner", &Unit::isAuctioner )
  .def("isArmorer", &Unit::isArmorer )
  .def("isServiceProvider", &Unit::isServiceProvider )
  .def("isGuard", &Unit::isGuard )
  .def("isInFlight", &Unit::isInFlight )
  .def("isInCombat", &Unit::isInCombat )
  /*.def("GetInCombatState", &Unit::GetInCombatState )*/
  /*.def("LeaveCombatState", &Unit::LeaveCombatState )*/
  .def("isAttacking", &Unit::isAttacking )
  .def("isAttacked", &Unit::isAttacked )
  .def("HasAuraType", &Unit::HasAuraType )
  .def("HasAura", &Unit::HasAura )
  /*.def("isStealth", &Unit::isStealth )*/
  /*.def("isInvisible", &Unit::isInvisible )*/
  .def("isTargetableForAttack", &Unit::isTargetableForAttack )
  .def("IsInWater", &Unit::IsInWater )
  .def("IsUnderWater", &Unit::IsUnderWater )
  .def("isInAccessablePlaceFor", &Unit::isInAccessablePlaceFor )
  .def("SendHealSpellOnPlayer", &Unit::SendHealSpellOnPlayer )
  .def("SendHealSpellOnPlayerPet", &Unit::SendHealSpellOnPlayerPet );

  lua_unit.def("SpellNonMeleeDamageLog", &Unit::SpellNonMeleeDamageLog )
  .def("CastSpell", (void (Unit::*)(Unit*, uint32, bool, Item*))&Unit::CastSpell )
  .def("DeMorph", &Unit::DeMorph )
  .def("isAlive", &Unit::isAlive )
  .def("isDead", &Unit::isDead )
  .def("MoveOutOfRange", &Unit::MoveOutOfRange )
  .def("getDeathState", &Unit::getDeathState )
  .def("GetPetGUID", &Unit::GetPetGUID )
  .def("GetCharmGUID", &Unit::GetCharmGUID )
  .def("GetPet", &Unit::GetPet )
  .def("GetCharm", &Unit::GetCharm )
  .def("SetPet", &Unit::SetPet )
  .def("SetCharm", &Unit::SetCharm )
  /*.def("AddAura", &Unit::AddAura )*/
  .def("RemoveFirstAuraByDispel", &Unit::RemoveFirstAuraByDispel )
  .def("RemoveAura", (void (Unit::*)(uint32,uint32))&Unit::RemoveAura )
  .def("RemoveAurasDueToSpell", &Unit::RemoveAurasDueToSpell )
  .def("RemoveSpellsCausingAura", &Unit::RemoveSpellsCausingAura )
  .def("RemoveRankAurasDueToSpell", &Unit::RemoveRankAurasDueToSpell )
  /*.def("RemoveNoStackAurasDueToAura", &Unit::RemoveNoStackAurasDueToAura )*/
  /*.def("RemoveAreaAurasByOthers", &Unit::RemoveAreaAurasByOthers )/*uint64*/
  .def("RemoveAllAuras", &Unit::RemoveAllAuras )
  .def("RemoveAllAurasOnDeath", &Unit::RemoveAllAurasOnDeath )
  .def("DelayAura", &Unit::DelayAura )
  /*.def("castSpell", &Unit::castSpell )*/
  .def("InterruptSpell", &Unit::InterruptSpell )
  .def("isInFront", &Unit::isInFront )
  .def("SetInFront", &Unit::SetInFront )
  .def("GetHostility", &lb_Unit_GetHostility )
  .def("GetHostilityDistance", &lb_Unit_GetHostilityDistance )
  .def("AddHostil", &lb_Unit_AddHostil )
  .def("SelectHostilTarget", &Unit::SelectHostilTarget )
  /*.def("GetAura", &Unit::GetAura )*/
  .def("GetTotalAuraModifier", &Unit::GetTotalAuraModifier )
  .def("SendMoveToPacket", &Unit::SendMoveToPacket )
  .def("AddItemEnchant", &Unit::AddItemEnchant );

  lua_unit.def("setTransForm", &Unit::setTransForm )
  .def("getTransForm", &Unit::getTransForm )
  /*.def("AddDynObject", &Unit::AddDynObject )*/
  .def("RemoveDynObject", (void (Unit::*)(uint32))&Unit::RemoveDynObject )
  /*.def("AddGameObject", &Unit::AddGameObject )*/
  /*.def("RemoveGameObject", (void (Unit::*)(GameObject*,bool))&Unit::RemoveGameObject )*/
  .def("RemoveGameObject", (void (Unit::*)(uint32,bool))&Unit::RemoveGameObject )
  /*.def("GetDynObject", (DynamicObject* (Unit::*)(uint32,uint32))&Unit::GetDynObject )*/
  .def("CalculateDamage", &Unit::CalculateDamage )
  .def("SetStateFlag", &Unit::SetStateFlag )
  .def("RemoveStateFlag", &Unit::RemoveStateFlag )
  .def("ApplyStats", &Unit::ApplyStats )
  .def("UnsummonTotem", &Unit::UnsummonTotem )
  /*.def("SpellDamageBonus", &Unit::SpellDamageBonus )*/
  /*.def("SpellHealingBonus", &Unit::SpellHealingBonus )*/
  /*.def("SpellCriticalBonus", &Unit::SpellCriticalBonus )*/
  .def("MeleeDamageBonus", &Unit::MeleeDamageBonus )
  .def("ApplySpellImmune", &Unit::ApplySpellImmune );

  module(L) [ lua_unit ];

  return 0;
}
