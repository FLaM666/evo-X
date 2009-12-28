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
SDName: Boss_Razuvious
SD%Complete: 75%
SDComment: TODO: Timers and sounds need confirmation, implement spell Hopeless
SDCategory: Naxxramas
EndScriptData */

#include "precompiled.h"
#include "naxxramas.h"

enum
{
    SAY_AGGRO1               = -1533120,
    SAY_AGGRO2               = -1533121,
    SAY_AGGRO3               = -1533122,
    SAY_SLAY1                = -1533123,
    SAY_SLAY2                = -1533124,
    SAY_COMMAND1             = -1533125,
    SAY_COMMAND2             = -1533126,
    SAY_COMMAND3             = -1533127,
    SAY_COMMAND4             = -1533128,
    SAY_DEATH                = -1533129,

    SPELL_UNBALANCING_STRIKE = 26613,
    SPELL_DISRUPTING_SHOUT   = 55543,
    SPELL_DISRUPTING_SHOUT_H = 29107,
    SPELL_JAGGED_KNIFE       = 55550,
    SPELL_HOPELESS           = 29125,

    NPC_DEATH_KNIGHT_UNDERSTUDY = 16803
};

struct MANGOS_DLL_DECL boss_razuviousAI : public ScriptedAI
{
    boss_razuviousAI(Creature* pCreature) : ScriptedAI(pCreature)
    {
        m_pInstance = (ScriptedInstance*)pCreature->GetInstanceData();
        m_bIsHeroicMode = false;//pCreature->GetMap()->IsRaidOrHeroicDungeon();
        Reset();
    }

    ScriptedInstance* m_pInstance;
    bool m_bIsHeroicMode;

    std::list<uint64> DeathKnightList;

    uint32 UnbalancingStrike_Timer;
    uint32 DisruptingShout_Timer;
    uint32 CommandSound_Timer;

    void Reset()
    {
        UnbalancingStrike_Timer = 30000;                    //30 seconds
        DisruptingShout_Timer = 25000;                      //25 seconds
        CommandSound_Timer = 40000;                         //40 seconds

        if (m_pInstance)
            m_pInstance->SetData(TYPE_RAZUVIOUS, NOT_STARTED);
    }

    void KilledUnit(Unit* Victim)
    {
        if (rand()%3)
            return;

        switch (rand()%2)
        {
            case 0:
                DoPlaySoundToSet(m_creature, SAY_SLAY1);
                break;
            case 1:
                DoPlaySoundToSet(m_creature, SAY_SLAY2);
                break;
        }
    }

    void JustDied(Unit* Killer)
    {
        DoPlaySoundToSet(m_creature, SAY_DEATH);

        if (m_pInstance)
            m_pInstance->SetData(TYPE_RAZUVIOUS, DONE);

        if (!DeathKnightList.empty())
        {
            for(std::list<uint64>::iterator itr = DeathKnightList.begin(); itr != DeathKnightList.end(); ++itr)
            {
                Creature* pDeathKnight = NULL;
                pDeathKnight = ((Creature*)Unit::GetUnit(*m_creature, *itr));

                if (pDeathKnight)
                    if (pDeathKnight->isAlive())
                        pDeathKnight->CastSpell(pDeathKnight, SPELL_HOPELESS, true);
            }
        }
    }

    void Aggro(Unit *who)
    {
        switch (rand()%3)
        {
            case 0:
                DoPlaySoundToSet(m_creature, SAY_AGGRO1);
                break;
            case 1:
                DoPlaySoundToSet(m_creature, SAY_AGGRO2);
                break;
            case 2:
                DoPlaySoundToSet(m_creature, SAY_AGGRO3);
                break;
        }

        if (m_pInstance)
            m_pInstance->SetData(TYPE_RAZUVIOUS, IN_PROGRESS);

        FindDeathKnight();

        if (!DeathKnightList.empty())
        {
            for(std::list<uint64>::iterator itr = DeathKnightList.begin(); itr != DeathKnightList.end(); ++itr)
            {
                if (Creature* pDeathKnight = ((Creature*)Unit::GetUnit(*m_creature, *itr)))
                {
                    if (pDeathKnight->isDead())
                    {
                        pDeathKnight->RemoveCorpse();
                        pDeathKnight->Respawn();
                    }

                    pDeathKnight->AI()->AttackStart(who);
                }
            }
        }
    }

    void UpdateAI(const uint32 diff)
    {
        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;

        //UnbalancingStrike_Timer
        if (UnbalancingStrike_Timer < diff)
        {
            DoCast(m_creature->getVictim(),SPELL_UNBALANCING_STRIKE);
            UnbalancingStrike_Timer = 30000;
        }else UnbalancingStrike_Timer -= diff;

        //DisruptingShout_Timer
        if (DisruptingShout_Timer < diff)
        {
            DoCast(m_creature->getVictim(), SPELL_DISRUPTING_SHOUT);
            DisruptingShout_Timer = 25000;
        }else DisruptingShout_Timer -= diff;

        //CommandSound_Timer
        if (CommandSound_Timer < diff)
        {
            switch (rand()%4)
            {
                case 0:
                    DoPlaySoundToSet(m_creature, SAY_COMMAND1);
                    break;
                case 1:
                    DoPlaySoundToSet(m_creature, SAY_COMMAND2);
                    break;
                case 2:
                    DoPlaySoundToSet(m_creature, SAY_COMMAND3);
                    break;
                case 3:
                    DoPlaySoundToSet(m_creature, SAY_COMMAND4);
                    break;
            }

            CommandSound_Timer = 40000;
        }else CommandSound_Timer -= diff;

        DoMeleeAttackIfReady();
    }

    void FindDeathKnight()
    {
        std::list<Creature*> DeathKnight;
        GetCreatureListWithEntryInGrid(DeathKnight, m_creature, NPC_DEATH_KNIGHT_UNDERSTUDY, 50.0f);

        if (!DeathKnight.empty())
        {
            DeathKnightList.clear();

            for(std::list<Creature*>::iterator itr = DeathKnight.begin(); itr != DeathKnight.end(); ++itr)
                DeathKnightList.push_back((*itr)->GetGUID());
        }
    }

};
CreatureAI* GetAI_boss_razuvious(Creature* pCreature)
{
    return new boss_razuviousAI(pCreature);
}

void AddSC_boss_razuvious()
{
    Script* NewScript;
    NewScript = new Script;
    NewScript->Name = "boss_razuvious";
    NewScript->GetAI = &GetAI_boss_razuvious;
    NewScript->RegisterSelf();
}
