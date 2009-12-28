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
SDName: Boss_Gluth
SD%Complete: 70
SDComment:
SDCategory: Naxxramas
EndScriptData */

#include "precompiled.h"
#include "naxxramas.h"

enum
{
    EMOTE_ZOMBIE      = -1533119,

    SPELL_MORTALWOUND = 25646,
    SPELL_DECIMATE    = 28374,
    SPELL_ENRAGE      = 28371,
    SPELL_ENRAGE_H    = 54427,
    SPELL_BERSERK     = 26662,

    NPC_ZOMBIE_CHOW   = 16360,
    SPELL_INFECTED_WOUND = 29306
};

#define ADD_1X 3269.590
#define ADD_1Y -3161.287
#define ADD_1Z 297.423

#define ADD_2X 3277.797
#define ADD_2Y -3170.352
#define ADD_2Z 297.423

#define ADD_3X 3267.049
#define ADD_3Y -3172.820
#define ADD_3Z 297.423

#define ADD_4X 3252.157
#define ADD_4Y -3132.135
#define ADD_4Z 297.423

#define ADD_5X 3259.990
#define ADD_5Y -3126.590
#define ADD_5Z 297.423

#define ADD_6X 3259.815
#define ADD_6Y -3137.576
#define ADD_6Z 297.423

#define ADD_7X 3308.030
#define ADD_7Y -3132.135
#define ADD_7Z 297.423

#define ADD_8X 3303.046
#define ADD_8Y -3180.682
#define ADD_8Z 297.423

#define ADD_9X 3313.283
#define ADD_9Y -3180.766
#define ADD_9Z 297.423

struct MANGOS_DLL_DECL mob_zombie_chowsAI : public ScriptedAI
{
    mob_zombie_chowsAI(Creature* pCreature) : ScriptedAI(pCreature)
    {
        Reset();
    }

    bool bIsForceMove;

    void Reset()
    {
        bIsForceMove = false;
    }
    void JustDied(Unit* Killer) {}

    void DoMeleeAttackIfReady()
    {
        //If we are within range melee the target
        if (m_creature->IsWithinDistInMap(m_creature->getVictim(), ATTACK_DISTANCE))
        {
            //Make sure our attack is ready and we aren't currently casting
            if (m_creature->isAttackReady() && !m_creature->IsNonMeleeSpellCasted(false))
            {
                DoCast(m_creature->getVictim(), SPELL_INFECTED_WOUND, true);
                m_creature->AttackerStateUpdate(m_creature->getVictim());
                m_creature->resetAttackTimer();
            }
        }
    }

    void UpdateAI(const uint32 diff)
    {
        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim() || bIsForceMove)
            return;

        DoMeleeAttackIfReady();
    }
};

struct MANGOS_DLL_DECL boss_gluthAI : public ScriptedAI
{
    boss_gluthAI(Creature* pCreature) : ScriptedAI(pCreature)
    {
        m_pInstance = (ScriptedInstance*)pCreature->GetInstanceData();
        m_bIsHeroicMode = false;//pCreature->GetMap()->IsRaidOrHeroicDungeon();
        Reset();
    }

    ScriptedInstance* m_pInstance;
    bool m_bIsHeroicMode;

    uint32 m_uiMortalWoundTimer;
    uint32 m_uiDecimateTimer;
    uint32 m_uiEnrageTimer;
    uint32 Summon_Timer;

    uint32 m_uiBerserkTimer;

    uint32 RangeCheck_Timer;
    std::list<uint64> m_lZombieGUIDList;

    void Reset()
    {
        m_uiMortalWoundTimer = 8000;
        m_uiDecimateTimer = 100000;
        m_uiEnrageTimer = 60000;
        Summon_Timer = 10000;

        m_uiBerserkTimer = MINUTE*8*IN_MILISECONDS;

        RangeCheck_Timer = 1000;
        m_lZombieGUIDList.clear();
    }

    void JustDied(Unit* pKiller)
    {
        if (m_pInstance)
            m_pInstance->SetData(TYPE_GLUTH, DONE);
    }

    void Aggro(Unit* pWho)
    {
        if (m_pInstance)
            m_pInstance->SetData(TYPE_GLUTH, IN_PROGRESS);
    }

    void JustReachedHome()
    {
        if (m_pInstance)
            m_pInstance->SetData(TYPE_GLUTH, FAIL);
    }

    void JustSummoned(Creature* summoned)
    {
        summoned->SetSpeed(MOVE_RUN, 0.8f);
    }

    void UpdateAI(const uint32 uiDiff)
    {
        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;

        // Mortal Wound
        if (m_uiMortalWoundTimer < uiDiff)
        {
            DoCast(m_creature->getVictim(), SPELL_MORTALWOUND);
            m_uiMortalWoundTimer = 10000;
        }
        else
            m_uiMortalWoundTimer -= uiDiff;

         //Decimate_Timer
        if (m_uiDecimateTimer < uiDiff)
        {
            DoCast(m_creature->getVictim(),SPELL_DECIMATE); // need core support

            // workaround below
            std::list<HostileReference*> t_list = m_creature->getThreatManager().getThreatList();
            if (t_list.size())
            {
                //begin + 1 , so we don't target the one with the highest threat
                std::list<HostileReference*>::iterator itr = t_list.begin();
                std::advance(itr, 1);
                for(; itr!= t_list.end(); ++itr)
                {
                    Unit *target = Unit::GetUnit(*m_creature, (*itr)->getUnitGuid());
                    if (target && target->isAlive() && target->GetTypeId() == TYPEID_PLAYER &&
                        (target->GetHealth() > target->GetMaxHealth() * 0.05))
                        target->SetHealth(target->GetMaxHealth() * 0.05);
                }
            }
            // Move Zombies
            if (!m_lZombieGUIDList.empty())
            {
                for(std::list<uint64>::iterator itr = m_lZombieGUIDList.begin(); itr != m_lZombieGUIDList.end(); ++itr)
                    if (Creature* pTemp = (Creature*)Unit::GetUnit(*m_creature, *itr))
                        if (pTemp->isAlive())
                        {
                            ((mob_zombie_chowsAI*)pTemp->AI())->bIsForceMove = true;
                            if (m_creature->GetHealth() > m_creature->GetMaxHealth() * 0.05) // remove when SPELL_DECIMATE is working
                                pTemp->SetHealth(pTemp->GetMaxHealth() * 0.02);
                            pTemp->AddThreat(m_creature, 1000000000.0f); // force move toward to Gluth
                        }
            }
            m_uiDecimateTimer = (m_bIsHeroicMode ? 120000 : 100000);
        }else m_uiDecimateTimer -= uiDiff;

        // Enrage
        if (m_uiEnrageTimer < uiDiff)
        {
            DoCast(m_creature, m_bIsHeroicMode?SPELL_ENRAGE_H:SPELL_ENRAGE);
            m_uiEnrageTimer = 60000;
        }
        else m_uiEnrageTimer -= uiDiff;

        if (RangeCheck_Timer < uiDiff)
        {
            if (!m_lZombieGUIDList.empty())
            {
                for(std::list<uint64>::iterator itr = m_lZombieGUIDList.begin(); itr != m_lZombieGUIDList.end(); ++itr)
                    if (Creature* pTemp = (Creature*)Unit::GetUnit(*m_creature, *itr))
                        if (pTemp->isAlive() && m_creature->IsWithinDistInMap(pTemp, ATTACK_DISTANCE))
                        {
                            DoScriptText(EMOTE_ZOMBIE, m_creature);
                            m_creature->SetHealth(m_creature->GetHealth() + m_creature->GetMaxHealth() * 0.05);
                            pTemp->ForcedDespawn();
                        }
            }
            RangeCheck_Timer = 1000;
        }else RangeCheck_Timer -= uiDiff;

        //Summon_Timer
        if (Summon_Timer < uiDiff)
        {
            for(uint8 i = 0; i < (m_bIsHeroicMode ? 2 : 1); i++)
            {
                if (Creature* pZombie = m_creature->SummonCreature(NPC_ZOMBIE_CHOW,ADD_1X,ADD_1Y,ADD_1Z,0,TEMPSUMMON_TIMED_OR_DEAD_DESPAWN,80000))
                {
                    if (Unit* pTarget = SelectUnit(SELECT_TARGET_RANDOM,0))
                    {
                        pZombie->AI()->AttackStart(pTarget);
                        m_lZombieGUIDList.push_back(pZombie->GetGUID());
                    }
                }
            }
            Summon_Timer = 10000;
        } else Summon_Timer -= uiDiff;

        // Berserk
        if (m_uiBerserkTimer < uiDiff)
        {
            DoCast(m_creature, SPELL_BERSERK, true);
            m_uiBerserkTimer = MINUTE*5*IN_MILISECONDS;
        }
        else
            m_uiBerserkTimer -= uiDiff;

        DoMeleeAttackIfReady();
    }
};

CreatureAI* GetAI_boss_gluth(Creature* pCreature)
{
    return new boss_gluthAI(pCreature);
}

CreatureAI* GetAI_mob_zombie_chows(Creature* pCreature)
{
    return new mob_zombie_chowsAI(pCreature);
}

void AddSC_boss_gluth()
{
    Script* NewScript;
    NewScript = new Script;
    NewScript->Name = "boss_gluth";
    NewScript->GetAI = &GetAI_boss_gluth;
    NewScript->RegisterSelf();

    NewScript = new Script;
    NewScript->Name = "mob_zombie_chows";
    NewScript->GetAI = &GetAI_mob_zombie_chows;
    NewScript->RegisterSelf();
}