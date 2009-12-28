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
SDName: Boss_Firemaw
SD%Complete: 100
SDComment:
SDCategory: Blackwing Lair
EndScriptData */

#include "precompiled.h"

#define SPELL_SHADOWFLAME       22539
#define SPELL_WINGBUFFET        23339
#define SPELL_FLAMEBUFFET       23341

struct MANGOS_DLL_DECL boss_firemawAI : public ScriptedAI
{
    boss_firemawAI(Creature* pCreature) : ScriptedAI(pCreature) {Reset();}

    uint32 ShadowFlame_Timer;
    uint32 WingBuffet_Timer;
    uint32 FlameBuffet_Timer;

    void Reset()
    {
        ShadowFlame_Timer = 30000;                          //These times are probably wrong
        WingBuffet_Timer = 24000;
        FlameBuffet_Timer = 5000;
    }

    void Aggro(Unit* pWho)
    {
        m_creature->SetInCombatWithZone();
    }

    void UpdateAI(const uint32 diff)
    {
        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;

        //ShadowFlame_Timer
        if (ShadowFlame_Timer < diff)
        {
            DoCast(m_creature->getVictim(),SPELL_SHADOWFLAME);
            ShadowFlame_Timer = urand(15000, 18000);
        }else ShadowFlame_Timer -= diff;

        //WingBuffet_Timer
        if (WingBuffet_Timer < diff)
        {
            DoCast(m_creature->getVictim(),SPELL_WINGBUFFET);
            if (m_creature->getThreatManager().getThreat(m_creature->getVictim()))
                m_creature->getThreatManager().modifyThreatPercent(m_creature->getVictim(),-75);

            WingBuffet_Timer = 25000;
        }else WingBuffet_Timer -= diff;

        //FlameBuffet_Timer
        if (FlameBuffet_Timer < diff)
        {
            DoCast(m_creature->getVictim(),SPELL_FLAMEBUFFET);
            FlameBuffet_Timer = 5000;
        }else FlameBuffet_Timer -= diff;

        DoMeleeAttackIfReady();
    }
};
CreatureAI* GetAI_boss_firemaw(Creature* pCreature)
{
    return new boss_firemawAI(pCreature);
}

void AddSC_boss_firemaw()
{
    Script *newscript;
    newscript = new Script;
    newscript->Name = "boss_firemaw";
    newscript->GetAI = &GetAI_boss_firemaw;
    newscript->RegisterSelf();
}
