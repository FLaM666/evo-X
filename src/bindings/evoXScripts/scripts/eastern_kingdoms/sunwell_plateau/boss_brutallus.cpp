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
SDName: Boss_Brutallus
SD%Complete: 50
SDComment: Intro not made. Script for Madrigosa to be added here.
EndScriptData */

#include "precompiled.h"
#include "sunwell_plateau.h"

enum Brutallus
{
    YELL_INTRO                      = -1580017,
    YELL_INTRO_BREAK_ICE            = -1580018,
    YELL_INTRO_CHARGE               = -1580019,
    YELL_INTRO_KILL_MADRIGOSA       = -1580020,
    YELL_INTRO_TAUNT                = -1580021,
    YELL_MADR_ICE_BARRIER           = -1580031,
    YELL_MADR_INTRO                 = -1580032,
    YELL_MADR_ICE_BLOCK             = -1580033,
    YELL_MADR_TRAP                  = -1580034,
    YELL_MADR_DEATH                 = -1580035,
    YELL_AGGRO                      = -1580022,
    YELL_KILL1                      = -1580023,
    YELL_KILL2                      = -1580024,
    YELL_KILL3                      = -1580025,
    YELL_LOVE1                      = -1580026,
    YELL_LOVE2                      = -1580027,
    YELL_LOVE3                      = -1580028,
    YELL_BERSERK                    = -1580029,
    YELL_DEATH                      = -1580030,

    SPELL_METEOR_SLASH              = 45150,
    SPELL_BURN                      = 45141,
    SPELL_BURN_AURA                 = 46394,
    SPELL_STOMP                     = 45185,
    SPELL_BERSERK                   = 26662
};

struct MANGOS_DLL_DECL boss_brutallusAI : public ScriptedAI
{
    boss_brutallusAI(Creature* pCreature) : ScriptedAI(pCreature)
    {
        m_pInstance = (ScriptedInstance*)pCreature->GetInstanceData();
        Reset();
    }

    ScriptedInstance* m_pInstance;

    uint32 m_uiSlashTimer;
    uint32 m_uiBurnTimer;
    uint32 m_uiStompTimer;
    uint32 m_uiBerserkTimer;
    uint32 m_uiLoveTimer;
    uint32 m_uiBurnCheckTimer;

    void Reset()
    {
        m_uiBurnCheckTimer = 1000;
        m_uiSlashTimer = 11000;
        m_uiStompTimer = 30000;
        m_uiBurnTimer = 60000;
        m_uiBerserkTimer = 360000;
        m_uiLoveTimer = urand(10000, 17000);
    }

    void Aggro(Unit* pWho)
    {
        DoScriptText(YELL_AGGRO, m_creature);
	    DoPlaySoundToSet(m_creature, 12463);
    }

    void KilledUnit(Unit* pVictim)
    {
        switch(urand(0, 2))
        {
            case 0: DoScriptText(YELL_KILL1, m_creature); break;
            case 1: DoScriptText(YELL_KILL2, m_creature); break;
            case 2: DoScriptText(YELL_KILL3, m_creature); break;
        }
    }

    void JustDied(Unit* pKiller)
    {
        DoScriptText(YELL_DEATH, m_creature);

        if (Creature* Felmist = ((Creature*)Unit::GetUnit(*m_creature, m_pInstance->GetData64(DATA_FELMYST))))
    {
               Felmist->SetVisibility(VISIBILITY_ON);
               Felmist->setFaction(14);
    }
    }

    void UpdateAI(const uint32 uiDiff)
    {
        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;

        if (m_uiBurnCheckTimer < uiDiff)
        {
            std::list<HostileReference *> t_list = m_creature->getThreatManager().getThreatList();
            for(std::list<HostileReference *>::iterator itr = t_list.begin(); itr!= t_list.end(); ++itr)
            {
                Unit *BurnedPlayer = Unit::GetUnit(*m_creature, (*itr)->getUnitGuid());
                if (BurnedPlayer && BurnedPlayer->GetTypeId() == TYPEID_PLAYER && BurnedPlayer->HasAura(SPELL_BURN_AURA))
                {
                    std::list<HostileReference *> t_list = m_creature->getThreatManager().getThreatList();
                    for(std::list<HostileReference *>::iterator itr = t_list.begin(); itr!= t_list.end(); ++itr)
                    {
                        Unit *TargetedPlayer = Unit::GetUnit(*m_creature, (*itr)->getUnitGuid());  
                        if (TargetedPlayer && TargetedPlayer->GetTypeId() == TYPEID_PLAYER && TargetedPlayer->IsWithinDistInMap(BurnedPlayer, 6) && !TargetedPlayer->HasAura(SPELL_BURN_AURA))
                            TargetedPlayer->CastSpell(TargetedPlayer,SPELL_BURN_AURA,true);
                    }
                }
            }          
            m_uiBurnCheckTimer = 1000;        
        }else m_uiBurnCheckTimer -= uiDiff;

        if (m_uiLoveTimer < uiDiff)
        {
            switch(urand(0, 2))
            {
                case 0: DoScriptText(YELL_LOVE1, m_creature); break;
                case 1: DoScriptText(YELL_LOVE2, m_creature); break;
                case 2: DoScriptText(YELL_LOVE3, m_creature); break;
            }
            m_uiLoveTimer = urand(15000, 23000);
        }
        else
            m_uiLoveTimer -= uiDiff;

        if (m_uiSlashTimer < uiDiff)
        {
            if (Unit* pTarget = m_creature->getVictim())
                DoCast(pTarget,SPELL_METEOR_SLASH);
            m_uiSlashTimer = 11000;
        }else m_uiSlashTimer -= uiDiff;

        if (m_uiStompTimer < uiDiff)
        {
            if (Unit* pTarget = m_creature->getVictim())
            {
                DoCast(pTarget,SPELL_STOMP);

                if (pTarget->HasAura(SPELL_BURN_AURA,0))
                   pTarget->RemoveAurasDueToSpell(SPELL_BURN_AURA);
            }
            m_uiStompTimer = 30000;
        }
        else
            m_uiStompTimer -= uiDiff;

        if (m_uiBurnTimer < uiDiff)
        {
            if (Unit* target = SelectUnit(SELECT_TARGET_RANDOM, 0))
            {
                DoCast(target,SPELL_BURN);
                target->CastSpell(target,SPELL_BURN_AURA, true);
            }
            m_uiBurnTimer = 60000;
        }
        else m_uiBurnTimer -= uiDiff;

        if (m_uiBerserkTimer < uiDiff)
        {
            DoScriptText(YELL_BERSERK, m_creature);
            DoCast(m_creature,SPELL_BERSERK);
            m_uiBerserkTimer = 20000;
        }
        else
            m_uiBerserkTimer -= uiDiff;

        DoMeleeAttackIfReady();
    }
};

CreatureAI* GetAI_boss_brutallus(Creature* pCreature)

{
    return new boss_brutallusAI(pCreature);
}

void AddSC_boss_brutallus()
{
    Script *newscript;
    newscript = new Script;
    newscript->Name = "boss_brutallus";
    newscript->GetAI = &GetAI_boss_brutallus;
    newscript->RegisterSelf();
}
