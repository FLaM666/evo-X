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
SDName: Boss_Razorgore
SD%Complete: 50
SDComment: Needs additional review. Phase 1 NYI (Grethok the Controller)
SDCategory: Blackwing Lair
EndScriptData */

#include "precompiled.h"

//Razorgore Phase 2 Script

#define SAY_EGGS_BROKEN1        -1469022
#define SAY_EGGS_BROKEN2        -1469023
#define SAY_EGGS_BROKEN3        -1469024
#define SAY_DEATH               -1469025

#define SPELL_CLEAVE            22540
#define SPELL_WARSTOMP          24375
#define SPELL_FIREBALLVOLLEY    22425
#define SPELL_CONFLAGRATION     23023

struct MANGOS_DLL_DECL boss_razorgoreAI : public ScriptedAI
{
    boss_razorgoreAI(Creature* pCreature) : ScriptedAI(pCreature) {Reset();}

    uint32 Cleave_Timer;
    uint32 WarStomp_Timer;
    uint32 FireballVolley_Timer;
    uint32 Conflagration_Timer;

    void Reset()
    {
        Cleave_Timer = 15000;                               //These times are probably wrong
        WarStomp_Timer = 35000;
        FireballVolley_Timer = 7000;
        Conflagration_Timer = 12000;
    }

    void Aggro(Unit* pWho)
    {
        m_creature->SetInCombatWithZone();
    }

    void JustDied(Unit* Killer)
    {
        DoScriptText(SAY_DEATH, m_creature);
    }

    void UpdateAI(const uint32 diff)
    {
        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;

        //Cleave_Timer
        if (Cleave_Timer < diff)
        {
            DoCast(m_creature->getVictim(),SPELL_CLEAVE);
            Cleave_Timer = urand(7000, 10000);
        }else Cleave_Timer -= diff;

        //WarStomp_Timer
        if (WarStomp_Timer < diff)
        {
            DoCast(m_creature->getVictim(),SPELL_WARSTOMP);
            WarStomp_Timer = urand(15000, 25000);
        }else WarStomp_Timer -= diff;

        //FireballVolley_Timer
        if (FireballVolley_Timer < diff)
        {
            DoCast(m_creature->getVictim(),SPELL_FIREBALLVOLLEY);
            FireballVolley_Timer = urand(12000, 15000);
        }else FireballVolley_Timer -= diff;

        //Conflagration_Timer
        if (Conflagration_Timer < diff)
        {
            DoCast(m_creature->getVictim(),SPELL_CONFLAGRATION);
            //We will remove this threat reduction and add an aura check.

            //if (m_creature->getThreatManager().getThreat(m_creature->getVictim()))
            //m_creature->getThreatManager().modifyThreatPercent(m_creature->getVictim(),-50);

            Conflagration_Timer = 12000;
        }else Conflagration_Timer -= diff;

        // Aura Check. If the gamer is affected by confliguration we attack a random gamer.
        if (m_creature->getVictim()->HasAura(SPELL_CONFLAGRATION,0))
        {
            Unit* target = NULL;
            target = SelectUnit(SELECT_TARGET_RANDOM,1);
            if (target)
                m_creature->TauntApply(target);
        }

        DoMeleeAttackIfReady();
    }
};

CreatureAI* GetAI_boss_razorgore(Creature* pCreature)
{
    return new boss_razorgoreAI(pCreature);
}

void AddSC_boss_razorgore()
{
    Script *newscript;
    newscript = new Script;
    newscript->Name = "boss_razorgore";
    newscript->GetAI = &GetAI_boss_razorgore;
    newscript->RegisterSelf();
}
