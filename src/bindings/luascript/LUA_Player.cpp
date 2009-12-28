/*
 * Copyright (C) 2005,2006 MaNGOS <http://www.mangosproject.org/>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */
//by Derex
#include "luainc.h"
#include "LUA_Player.h"
#include "WorldPacket.h"
#include "Player.h"
#include "Creature.h"
#include "GossipDef.h"
#include "SpellAuras.h"
#include "DynamicObject.h"
#include "Lua_uint64.h"
#include "Mail.h"

//For player
void lb_Player_Dump(Player* pl)
{
  //display some info about player
  debug_log("Dumping player %s ",pl->GetName() );
}

void lb_Player_SendPacket(Player* pl, WorldPacket& pct )
{
  pl->GetSession()->SendPacket(&pct);
}

void lb_Player_ADD_GOSSIP_ITEM(Player* pl,uint8 Icon, char const * Message, uint32 dtSender, uint32 dtAction )
{
  pl->PlayerTalkClass->GetGossipMenu()->AddMenuItem(Icon,Message,dtSender,dtAction);
}

void lb_Player_SEND_GOSSIP_MENU(Player* pl,uint32 TitleTextId, lua_uint64 npcGUID)
{
  pl->PlayerTalkClass->SendGossipMenu(TitleTextId,npcGUID.m_val);
}

void lb_Player_CLOSE_GOSSIP_MENU(Player* pl)
{
  pl->PlayerTalkClass->CloseGossip();
}

void lb_Player_SEND_QUEST_DETAILS(Player* pl ,Quest *pQuest, lua_uint64 npcGUID, bool ActivateAccept)
{
  pl->PlayerTalkClass->SendQuestGiverQuestDetails(pQuest,npcGUID.m_val,ActivateAccept);
}

void lb_Player_SEND_REQUESTEDITEMS(Player* pl ,  Quest *pQuest, lua_uint64 npcGUID, bool Completable, bool CloseOnCancel )
{
  pl->PlayerTalkClass->SendQuestGiverRequestItems(pQuest,npcGUID.m_val,Completable,CloseOnCancel);
}

void lb_Player_SEND_VENDORLIST(Player* pl , lua_uint64 guid )
{
  pl->GetSession()->SendListInventory(guid.m_val);
}

void lb_Player_SEND_TRAINERLIST(Player* pl , lua_uint64 guid )
{
  pl->GetSession()->SendTrainerList(guid.m_val);
}

void lb_Player_SEND_BANKERLIST(Player* pl , lua_uint64 guid )
{
  pl->GetSession()->SendShowBank( guid.m_val );
}

void lb_Player_SEND_TABARDLIST(Player* pl , lua_uint64 guid )
{
  pl->GetSession()->SendTabardVendorActivate(guid.m_val);
}

// void lb_Player_SEND_AUCTIONLIST(Player* pl , lua_uint64 guid )
// {
//   pl->GetSession()->SendAuctionHello(guid.m_val);
// }

void lb_Player_SEND_TAXILIST(Player* pl , lua_uint64 guid )
{
  pl->GetSession()->SendTaxiStatus(guid.m_val);
}

void lb_Player_SEND_SPRESURRECT(Player* pl)
{
  pl->GetSession()->SendSpiritResurrect();
}

uint32 lb_Player_GET_HONORRANK(Player* pl)
{
  return pl->GetHonorRank();
}

void lb_Player_SEND_POI(Player* pl ,  float X, float Y, uint32 Icon, uint32 Flags, uint32 Data, char const * locName )
{
  pl->PlayerTalkClass->SendPointOfInterest( X, Y, Icon, Flags, Data, locName );
}

void lb_Player_PrepareQuestMenu(Player* pl , lua_uint64 guid )
{
  pl->PrepareQuestMenu(guid.m_val);
}

void lb_Player_SendPreparedQuest(Player* pl , lua_uint64 guid )
{
  pl->SendPreparedQuest(guid.m_val);
}

void lb_Player_SendQuestUpdateAddCreature(Player* pl , uint32 quest_id, lua_uint64 guid, uint32 creature_idx, uint32 old_count, uint32 add_count )
{
  pl->SendQuestUpdateAddCreature(quest_id,guid.m_val, creature_idx,  old_count,  add_count );
}

lua_uint64 lb_Player_GetSelection(Player* pl )
{
  return lua_uint64(pl->GetSelection());
}

lua_uint64 lb_Player_GetTarget(Player* pl )
{
  return lua_uint64(pl->GetTarget());
}

void lb_Player_SetSelection(Player* pl , lua_uint64 guid)
{
  pl->SetSelection(guid.m_val);
}


void lb_Player_SetTarget(Player* pl , lua_uint64 guid)
{
  pl->SetTarget(guid.m_val);
}

//Here we export from c++ to lua ... here are all definitions of funcs
int lb_Export_Player(lua_State *L)
{
  using namespace luabind;

  module(L)
      [
      class_<Player, bases<Unit, Object> >("Player")
      .def("ADD_GOSSIP_ITEM"        ,&lb_Player_ADD_GOSSIP_ITEM)
          .def("SEND_GOSSIP_MENU"   ,&lb_Player_SEND_GOSSIP_MENU)
          .def("CLOSE_GOSSIP_MENU" ,&lb_Player_CLOSE_GOSSIP_MENU)
          .def("SEND_POI", &lb_Player_SEND_POI )
          .def("SEND_QUEST_DETAILS", &lb_Player_SEND_QUEST_DETAILS )
          .def("SEND_REQUESTEDITEMS",&lb_Player_SEND_REQUESTEDITEMS )
          .def("SEND_VENDORLIST",&lb_Player_SEND_VENDORLIST )
          .def("SEND_TRAINERLIST",&lb_Player_SEND_TRAINERLIST )
          .def("SEND_BANKERLIST",&lb_Player_SEND_BANKERLIST )
          .def("SEND_TABARDLIST",&lb_Player_SEND_TABARDLIST )
//           .def("SEND_AUCTIONLIST",&lb_Player_SEND_AUCTIONLIST )
          .def("SEND_TAXILIST",&lb_Player_SEND_TAXILIST )
          .def("SEND_SPRESURRECT",&lb_Player_SEND_SPRESURRECT )
          .def("GET_HONORRANK",&lb_Player_GET_HONORRANK )
          .def("SEND_REQUESTEDITEMS",&lb_Player_SEND_REQUESTEDITEMS )
          .def("Dump"                                   ,&lb_Player_Dump)
          .def("SendPacket",                         &lb_Player_SendPacket)
          .def("TeleportTo", &Player::TeleportTo)
          .def("ToggleAFK", &Player::ToggleAFK)
          .def("ToggleDND", &Player::ToggleDND)
          .def("isAFK", &Player::isAFK)
          .def("isDND", &Player::isDND)
          .def("SendFriendlist", &Player::SendFriendlist)
          .def("SendIgnorelist", &Player::SendIgnorelist)
          .def("GetTaximask", &Player::GetTaximask)
          .def("SetTaximask", &Player::SetTaximask)
          .def("ClearTaxiDestinations", &Player::ClearTaxiDestinations)
          .def("AddTaxiDestination", &Player::AddTaxiDestination)
          .def("GetTaxiSource", &Player::GetTaxiSource)
          .def("isAcceptTickets", &Player::isAcceptTickets)
          .def("SetAcceptTicket", &Player::SetAcceptTicket)
          .def("isAcceptWhispers", &Player::isAcceptWhispers)
          .def("SetAcceptWhispers", &Player::SetAcceptWhispers)
          .def("isGameMaster", &Player::isGameMaster)
          .def("SetGameMaster", &Player::SetGameMaster)
          .def("isTaxiCheater", &Player::isTaxiCheater)
          .def("SetTaxiCheater", &Player::SetTaxiCheater)
          .def("isGMVisible", &Player::isGMVisible)
          .def("SetGMVisible", &Player::SetGMVisible)
          .def("GetName", &Player::GetName)
          .def("GiveXP", &Player::GiveXP)
          .def("GiveLevel", &Player::GiveLevel)
          .def("setDismountCost", &Player::setDismountCost)
          .def("setDeathState", &Player::setDeathState)
          .def("InnEnter", &Player::InnEnter)
          .def("GetRestBonus", &Player::GetRestBonus)
          .def("SetRestBonus", &Player::SetRestBonus)
          .def("GetRestType", &Player::GetRestType)
          .def("SetRestType", &Player::SetRestType)
          .def("GetInnPosX", &Player::GetInnPosX)
          .def("GetInnPosY", &Player::GetInnPosY)
          .def("GetInnPosZ", &Player::GetInnPosZ)
          .def("UpdateInnerTime", &Player::UpdateInnerTime)
          .def("GetTimeInnEter", &Player::GetTimeInnEter)
          .def("UnsummonPet", &Player::UnsummonPet)
          .def("UnTamePet", &Player::UnTamePet)
          .def("Uncharm", &Player::Uncharm)
          .def("SetVirtualItemSlot", &Player::SetVirtualItemSlot)
          .def("SetSheath", &Player::SetSheath)
          .def("FindEquipSlot", &Player::FindEquipSlot)
          .def("CreateItem", &Player::CreateItem)
          .def("GetItemCount", &Player::GetItemCount)
          .def("GetBankItemCount", &Player::GetBankItemCount)
          /*.def("GetPosByGuid", &Player::GetPosByGuid)/*u64*/
          .def("GetItemByPos", ( Item* (Player::*)( uint16  ) const)&Player::GetItemByPos)
          .def("GetItemByPos", (Item* (Player::*)( uint8 , uint8 ) const) &Player::GetItemByPos)
          .def("HasBankBagSlot", &Player::HasBankBagSlot)
          .def("IsInventoryPos", &Player::IsInventoryPos)
          .def("IsEquipmentPos", &Player::IsEquipmentPos)
          .def("IsBankPos", &Player::IsBankPos)
          .def("HasItemCount", &Player::HasItemCount)
          .def("CanStoreNewItem", &Player::CanStoreNewItem)
          .def("CanStoreItem", &Player::CanStoreItem)
          .def("CanEquipItem", &Player::CanEquipItem)
          .def("CanUnequipItem", &Player::CanUnequipItem)
          .def("CanBankItem", &Player::CanBankItem)
          .def("CanUseAmmo", &Player::CanUseAmmo)
          .def("StoreNewItem", &Player::StoreNewItem)
          .def("StoreItem", &Player::StoreItem)
          .def("EquipItem", &Player::EquipItem)
          .def("VisualizeItem", &Player::VisualizeItem)
          .def("BankItem", &Player::BankItem)
          .def("RemoveItem", &Player::RemoveItem)
          .def("RemoveItemCount", &Player::RemoveItemCount)
          .def("DestroyItem", &Player::DestroyItem)
          .def("DestroyItemCount", (void (Player::*)( uint32,uint32, bool))&Player::DestroyItemCount)
          .def("DestroyItemCount", (void (Player::*)( Item*, uint32& ,bool ))&Player::DestroyItemCount)
          .def("SplitItem", &Player::SplitItem)
          .def("SwapItem", &Player::SwapItem)
          .def("AddItemToBuyBackSlot", &Player::AddItemToBuyBackSlot)
          .def("GetItemFromBuyBackSlot", &Player::GetItemFromBuyBackSlot)
          .def("RemoveItemFromBuyBackSlot", &Player::RemoveItemFromBuyBackSlot)
          .def("SendEquipError", &Player::SendEquipError)
          .def("SendBuyError", &Player::SendBuyError)
          .def("SendSellError", &Player::SendSellError)
          .def("AddWeaponProficiency", &Player::AddWeaponProficiency)
          .def("AddArmorProficiency", &Player::AddArmorProficiency)
          .def("GetWeaponProficiency", &Player::GetWeaponProficiency)
          .def("GetArmorProficiency", &Player::GetArmorProficiency)
          .def("GetTrader", &Player::GetTrader)
          .def("TradeCancel", &Player::TradeCancel)
          .def("ClearTrade", &Player::ClearTrade)
          .def("PrepareQuestMenu", &lb_Player_PrepareQuestMenu )
          .def("SendPreparedQuest", &lb_Player_SendPreparedQuest)
          .def("GetActiveQuest", &Player::GetActiveQuest)
          .def("GetNextQuest", &Player::GetNextQuest)
          .def("CanSeeStartQuest", &Player::CanSeeStartQuest)
          .def("CanTakeQuest", &Player::CanTakeQuest)
          .def("CanAddQuest", &Player::CanAddQuest)
          .def("CanCompleteQuest", &Player::CanCompleteQuest)
          .def("CanRewardQuest", (bool (Player::*)( Quest*, bool )) &Player::CanRewardQuest)
          .def("CanRewardQuest",(bool (Player::*)( Quest*,uint32, bool ))&Player::CanRewardQuest)
          .def("AddQuest", &Player::AddQuest)
          .def("CompleteQuest", &Player::CompleteQuest)
          .def("IncompleteQuest", &Player::IncompleteQuest)
          .def("RewardQuest", &Player::RewardQuest)
          .def("FailQuest", &Player::FailQuest)
          .def("FailTimedQuest", &Player::FailTimedQuest)
          .def("SatisfyQuestClass", &Player::SatisfyQuestClass)
          .def("SatisfyQuestLevel", &Player::SatisfyQuestLevel)
          .def("SatisfyQuestLog", &Player::SatisfyQuestLog)
          .def("SatisfyQuestPreviousQuest", &Player::SatisfyQuestPreviousQuest)
          .def("SatisfyQuestRace", &Player::SatisfyQuestRace)
          .def("SatisfyQuestReputation", &Player::SatisfyQuestReputation)
          .def("SatisfyQuestSkill", &Player::SatisfyQuestSkill)
          .def("SatisfyQuestStatus", &Player::SatisfyQuestStatus)
          .def("SatisfyQuestTimed", &Player::SatisfyQuestTimed)
          .def("SatisfyQuestExclusiveGroup", &Player::SatisfyQuestExclusiveGroup)
          .def("GiveQuestSourceItem", &Player::GiveQuestSourceItem)
          .def("TakeQuestSourceItem", &Player::TakeQuestSourceItem)
          .def("GetQuestRewardStatus", &Player::GetQuestRewardStatus)
          .def("GetQuestStatus", &Player::GetQuestStatus)
          .def("AdjustQuestReqItemCount", &Player::AdjustQuestReqItemCount)
          .def("SetQuestStatus", &Player::SetQuestStatus)
          .def("GetQuestSlot", &Player::GetQuestSlot)
          .def("AreaExplored", &Player::AreaExplored)
          .def("KilledMonster", &Player::KilledMonster)
          .def("MoneyChanged", &Player::MoneyChanged)
          .def("HaveQuestForItem", &Player::HaveQuestForItem)
          .def("SendQuestComplete", &Player::SendQuestComplete)
          .def("SendQuestReward", &Player::SendQuestReward)
          .def("SendQuestFailed", &Player::SendQuestFailed)
          .def("SendQuestTimerFailed", &Player::SendQuestTimerFailed)
          .def("SendCanTakeQuestResponse", &Player::SendCanTakeQuestResponse)
          .def("SendPushToPartyResponse", &Player::SendPushToPartyResponse)
          .def("SendQuestUpdateAddItem", &Player::SendQuestUpdateAddItem)
          .def("SendQuestUpdateAddCreature", &lb_Player_SendQuestUpdateAddCreature)
          .def("GetInGameTime", &Player::GetInGameTime)
          .def("SetInGameTime", &Player::SetInGameTime)
          .def("AddTimedQuest", &Player::AddTimedQuest)
          .def("GetSelection", &lb_Player_GetSelection)
          .def("GetTarget", &lb_Player_GetTarget)
          .def("ModifyMoney", &Player::ModifyMoney)
          .def("SetMoney", &Player::SetMoney)
          .def("GetMoney", &Player::GetMoney)
          .def("SetSelection", &lb_Player_SetSelection)
          .def("SetTarget", &lb_Player_SetTarget)
          .def("AddMail", &Player::AddMail)
//           .def("SetMail", &Player::SetMail)
          .def("RemoveMail", &Player::RemoveMail)
          .def("GetMailSize", &Player::GetMailSize)
          .def("GetMail", &Player::GetMail)
          .def("HasSpell", &Player::HasSpell)
          .def("CanLearnProSpell", &Player::CanLearnProSpell)
          .def("SendProficiency", &Player::SendProficiency)
          .def("addSpell", &Player::addSpell)
          .def("learnSpell", &Player::learnSpell)
          .def("removeSpell", &Player::removeSpell)
          .def("resetTalents", &Player::resetTalents)
          .def("resetTalentsCost", &Player::resetTalentsCost)
          /*.def("setResurrect", &Player::setResurrect)/*64*/
          /*.def("SetPVPCount", &Player::SetPVPCount)*/
          .def("addAction", &Player::addAction)
          .def("removeAction", &Player::removeAction)
          .def("GetGroupLeader", &Player::GetGroupLeader)
          .def("SetInGuild", &Player::SetInGuild)
          .def("SetRank", &Player::SetRank)
          .def("SetGuildIdInvited", &Player::SetGuildIdInvited)
          .def("GetGuildId", &Player::GetGuildId)
          .def("GetRank", &Player::GetRank)
          .def("CheckDuelDistance", &Player::CheckDuelDistance)
          .def("DuelComplete", &Player::DuelComplete)
//           .def("GetCurrentBuybackSlot", &Player::GetCurrentBuybackSlot)
//           .def("SetCurrentBuybackSlot", &Player::SetCurrentBuybackSlot)
          .def("IsGroupMember", &Player::IsGroupMember)
          .def("UpdateSkill", &Player::UpdateSkill)
          .def("UpdateSkillPro", &Player::UpdateSkillPro)
          .def("GetLootGUID", &Player::GetLootGUID)
          .def("SetLootGUID", &Player::SetLootGUID)
          .def("SendOutOfRange", &Player::SendOutOfRange)
          .def("PlaySound", &Player::PlaySound)
          .def("SendExplorationExperience", &Player::SendExplorationExperience)
          .def("SendMessageToOwnTeamSet", &Player::SendMessageToOwnTeamSet)
          .def("SetPosition", &Player::SetPosition)
          .def("KillPlayer", &Player::KillPlayer)
          .def("ResurrectPlayer", &Player::ResurrectPlayer)
          .def("BuildPlayerRepop", &Player::BuildPlayerRepop)
          .def("RepopAtGraveyard", &Player::RepopAtGraveyard)
          .def("DurabilityLossAll", &Player::DurabilityLossAll)
          .def("DurabilityLoss", &Player::DurabilityLoss)
          .def("DurabilityRepairAll", &Player::DurabilityRepairAll)
          .def("DurabilityRepair", &Player::DurabilityRepair)
          .def("SetMovement", &Player::SetMovement)
          .def("SetPlayerSpeed", &Player::SetPlayerSpeed)
          .def("BroadcastPacketToFriendListers", &Player::BroadcastPacketToFriendListers)
          .def("SetSkill", &Player::SetSkill)
          .def("HasSkill", &Player::HasSkill)
          .def("SetDontMove", &Player::SetDontMove)
          .def("GetDontMove", &Player::GetDontMove)
          .def("GetTeam", &Player::GetTeam)
          .def("SetStanding", &Player::SetStanding)
          .def("SetDrunkValue", &Player::SetDrunkValue)
          .def("UpdateHonor", &Player::UpdateHonor)
          .def("SetTotalHonor", &Player::SetTotalHonor)
          .def("GetTotalHonor", &Player::GetTotalHonor)
          .def("GetHonorHighestRank", &Player::GetHonorHighestRank)
          .def("SetHonorHighestRank", &Player::SetHonorHighestRank)
          .def("GetHonorRating", &Player::GetHonorRating)
          .def("SetHonorRating", &Player::SetHonorRating)
          .def("GetHonorLastWeekStanding", &Player::GetHonorLastWeekStanding)
          .def("SetHonorLastWeekStanding", &Player::SetHonorLastWeekStanding)
          .def("GetDrunkValue", &Player::GetDrunkValue)
          .def("GetDeathTimer", &Player::GetDeathTimer)
          .def("SetSoulStoneSpell", &Player::SetSoulStoneSpell)
          .def("SetSoulStone", &Player::SetSoulStone)
          ];



      return 0;
}
