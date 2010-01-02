/*
 * Copyright (C) 2005-2009 MaNGOS <http://getmangos.com/>
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

#include "Player.h"
#include "BattleGround.h"
#include "BattleGroundDS.h"
#include "Language.h"
#include "ObjectMgr.h"
#include "WorldPacket.h"

BattleGroundDS::BattleGroundDS()
{

    m_StartDelayTimes[BG_STARTING_EVENT_FIRST]  = BG_START_DELAY_1M;
    m_StartDelayTimes[BG_STARTING_EVENT_SECOND] = BG_START_DELAY_30S;
    m_StartDelayTimes[BG_STARTING_EVENT_THIRD]  = BG_START_DELAY_15S;
    m_StartDelayTimes[BG_STARTING_EVENT_FOURTH] = BG_START_DELAY_NONE;
    //we must set messageIds
    m_StartMessageIds[BG_STARTING_EVENT_FIRST]  = LANG_ARENA_ONE_MINUTE;
    m_StartMessageIds[BG_STARTING_EVENT_SECOND] = LANG_ARENA_THIRTY_SECONDS;
    m_StartMessageIds[BG_STARTING_EVENT_THIRD]  = LANG_ARENA_FIFTEEN_SECONDS;
    m_StartMessageIds[BG_STARTING_EVENT_FOURTH] = LANG_ARENA_HAS_BEGUN;
}

BattleGroundDS::~BattleGroundDS()
{

}

void BattleGroundDS::Update(uint32 diff)
{
    BattleGround::Update(diff);
}

void BattleGroundDS::StartingEventCloseDoors()
{
}

void BattleGroundDS::StartingEventOpenDoors()
{
  OpenDoorEvent(BG_EVENT_DOOR);
}

void BattleGroundDS::AddPlayer(Player *plr)
{
    BattleGround::AddPlayer(plr);
    //create score and add it to map, default values are set in constructor
    BattleGroundDSScore* sc = new BattleGroundDSScore;

    m_PlayerScores[plr->GetGUID()] = sc;
	
  UpdateWorldState(0xe11, GetAlivePlayersCountByTeam(ALLIANCE));
  UpdateWorldState(0xe10, GetAlivePlayersCountByTeam(HORDE));
}

void BattleGroundDS::RemovePlayer(Player * /*plr*/, uint64 /*guid*/)
{
  if (GetStatus() == STATUS_WAIT_LEAVE)
    return;

  UpdateWorldState(0xe11, GetAlivePlayersCountByTeam(ALLIANCE));
  UpdateWorldState(0xe10, GetAlivePlayersCountByTeam(HORDE));

  CheckArenaWinConditions();
}

void BattleGroundDS::HandleKillPlayer(Player* player, Player* killer)
{
   if (GetStatus() != STATUS_IN_PROGRESS)
    return;

  if (!killer)
  {
    sLog.outError("BattleGroundNA: Killer player not found");
    return;
  }

  BattleGround::HandleKillPlayer(player,killer);

  UpdateWorldState(0xe11, GetAlivePlayersCountByTeam(ALLIANCE));
  UpdateWorldState(0xe10, GetAlivePlayersCountByTeam(HORDE));

  CheckArenaWinConditions();
}

void BattleGroundDS::HandleAreaTrigger(Player * /*Source*/, uint32 /*Trigger*/)
{
}

void BattleGroundDS::FillInitialWorldStates(WorldPacket &data)
{
  data << uint32(0xe11) << uint32(GetAlivePlayersCountByTeam(ALLIANCE));           // 7
  data << uint32(0xe10) << uint32(GetAlivePlayersCountByTeam(HORDE));           // 8
  data << uint32(0xa11) << uint32(1);           // 9
}

bool BattleGroundDS::SetupBattleGround()
{
    return true;
}
