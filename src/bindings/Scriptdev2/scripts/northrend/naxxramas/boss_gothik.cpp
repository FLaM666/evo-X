/* Copyright (C) 2006 - 2009 ScriptDev2 <https://scriptdev2.svn.sourceforge.net/>
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

/* ScriptData
SDName: Boss_Gothik
SD%Complete: 0
SDComment: Placeholder
SDCategory: Naxxramas
EndScriptData */

#include "precompiled.h"
#include "naxxramas.h"

enum
{
    SAY_SPEECH                = -1533040,
    SAY_KILL                  = -1533041,
    SAY_DEATH                 = -1533042,
    SAY_TELEPORT              = -1533043,

    //Gothik
    SPELL_HARVESTSOUL         = 28679,
    SPELL_SHADOWBOLT          = 29317,
    H_SPELL_SHADOWBOLT        = 56405,

    //Unrelenting Trainee
    SPELL_EAGLECLAW           = 30285,
    SPELL_KNOCKDOWN_PASSIVE   = 6961,

    //Unrelenting Deathknight
    SPELL_CHARGE              = 22120,
    SPELL_SHADOW_MARK         = 27825,

    //Unrelenting Rider
    SPELL_UNHOLY_AURA         = 55606,
    H_SPELL_UNHOLY_AURA       = 55608,
    SPELL_SHADOWBOLT_VOLLEY   = 27831,                      //Search thru targets and find those who have the SHADOW_MARK to cast this on
    H_SPELL_SHADOWBOLT_VOLLEY = 55638,

    //Spectral Trainee
    SPELL_ARCANE_EXPLOSION    = 27989,

    //Spectral Deathknight
    SPELL_WHIRLWIND           = 28334,
    SPELL_SUNDER_ARMOR        = 25051,                      //cannot find sunder that reduces armor by 2950
    SPELL_CLEAVE              = 20677,
    SPELL_MANA_BURN           = 17631,

    //Spectral Rider
    SPELL_LIFEDRAIN           = 24300,
    //USES SAME UNHOLY AURA AS UNRELENTING RIDER

    //Spectral Horse
    SPELL_STOMP               = 27993
};
