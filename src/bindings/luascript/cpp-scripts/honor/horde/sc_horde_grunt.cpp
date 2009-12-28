/*
 * Copyright (C) 2005,2006 ScriptDev <https://opensvn.csie.org/ScriptDev/>
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

#include "./sc_defines.h"

bool GossipHello_grunt_horde(Player *player, Creature *_Creature)
{
    {
        player->ADD_GOSSIP_ITEM( 1, "I'd like to browse your goods.", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_TRADE);
    }

    return true;
}

bool GossipSelect_grunt_horde(Player *player, Creature *_Creature, uint32 sender, uint32 action )
{

                                                            // This function is not tested and will not work
    if(action == GOSSIP_ACTION_TRADE && player->GET_HONORRANK() > 1)
    {
        player->SEND_VENDORLIST( _Creature->GetGUID() );
    }
    else

        player->ADD_GOSSIP_ITEM( 0, "You need to be Grunt to browse my goods", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_TRADE);

    return true;
}

bool GossipSelectWithCode_grunt_horde( Player *player, Creature *_Creature, uint32 sender, uint32 action, char* sCode )
{

    return false;
}

uint32 NPCDialogStatus_grunt_horde(Player *player, Creature *_Creature )
{
    return _Creature->QUEST_DIALOG_STATUS(player, DIALOG_STATUS_CHAT);
}

void AddSC_grunt_horde()
{
    Script *newscript;

    newscript = new Script;
    newscript->Name="grunt_horde";
    newscript->pGossipHello          = &GossipHello_grunt_horde;
    newscript->pGossipSelect         = &GossipSelect_grunt_horde;
    newscript->pGossipSelectWithCode = &GossipSelectWithCode_grunt_horde;
    newscript->pNPCDialogStatus      = &NPCDialogStatus_grunt_horde;
    m_scripts[nrscripts++] = newscript;
}
